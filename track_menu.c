#ifndef lint
static char sccs_id[] = "@(#)track_menu.c	5.2  6/2/89";
#endif

/*
 * Copyright 1988 by Siemens Research and Technology Laboratories, Princeton, NJ
 *
 *                         All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of Siemens Research and Technology
 * Laboratories not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior permission.
 *
 *
 * SIEMENS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * SIEMENS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */
#include "copyright.h"

/* 
  RTL Menu Package Version 1.2
  by Joe Camaratta and Mike Berman, Siemens RTL, Princeton NJ, 1988

  track_menu.c: bring up menus and track the mouse
*/

#include "arrow_icon.h"
#include "null_icon.h"
#include "rtlmenuP.h"
#include "evsaveX.h"

#define CLICK_TIME 360 /* in milliseconds */
#define CursorLockMask (ButtonReleaseMask)

/* Event macros */

#define EventGetXCoord(rep) ((rep).xmotion.x)
#define EventGetYCoord(rep) ((rep).xmotion.y)
#define EventType(rep) ((rep).type)
#define EventXWindow(rep) ((rep).xcrossing.window)
#define EventXTime(rep) ((rep).xcrossing.time)
#define EventXMode(rep) ((rep).xcrossing.mode)
#define EventXRootX(rep) ((rep).xcrossing.x_root)
#define EventXRootY(rep) ((rep).xcrossing.y_root)
#define EventXDetail(rep) ((rep).xcrossing.detail)
#define EventMWindow(rep) ((rep).xmotion.window)
#define EventMTime(rep) ((rep).xmotion.time)
#define EventButton(rep) ((rep).xbutton.button)
#define EventBWindow(rep) ((rep).xbutton.window)
#define EventBTime(rep) ((rep).xbutton.time)
#define EventEX(rep) ((rep).xexpose.x)
#define EventEY(rep) ((rep).xexpose.y)
#define EventEWidth(rep) ((rep).xexpose.width)
#define EventEHeight(rep) ((rep).xexpose.height)
#define PointerEvent(rep) \
    ((EventType(rep) == ButtonPress) || \
     (EventType(rep) == ButtonRelease) || \
     (EventType(rep) == MotionNotify) || \
     (EventType(rep) == EnterNotify) || \
     (EventType(rep) == LeaveNotify) || \
     (EventType(rep) == FocusIn) || \
     (EventType(rep) == FocusOut))
#define KeyEvent(rep) \
    ((EventType(rep) == KeyPress) || (EventType(rep) == KeyRelease))
#define SelectChildX(menu, item, rep) \
    (TestOptionFlag(menu, fixedchild)? \
     (MenuX(menu) + ItemGetArrowPosition(item)): \
     MIN(MenuX(menu) + ItemGetArrowPosition(item),EventXRootX(rep)))

/* Possible states for the state machine */
typedef enum
{
    Initial,      /* Inside a submenu, but not any item */
    CheckTrigger, /* Inside an item that has submenu, checking for pullright */
    Leaf,         /* Inside an item with no submenu */
    Exit,         /* Preparing to exit */
    LevelControl  /* Not in any submenu, waiting to enter something */
} State;

/* functions in the menu.c module */

extern RTLMenu NewMenu();
extern void DisposeMenu ();
extern void Draw_Menu();
extern void ClearInitialItem();
extern void PlacePointer();
extern void AdjustPointer();
extern void SetInitialItem();
extern void Undisplay_Menu();
extern void MenuInvert();
extern void Draw_Item();

extern RTLMenuItem MenuItemByName ();
extern RTLMenuItem Display_Menu(); 
extern RTLMenuItem MenuGetItem();
extern RTLMenuItem GetInitialItem();
extern RTLMenu MenuGetMenu();

void LockCursor();
void UnlockCursor();
void GetNextSignificantEvent();
void PopSubmenu();
void Highlight();
void Unhighlight();
void TossExtraMoves();
void ProcessExposeEvents();

bool GrabPointer();

State LevelControlState();
State GetItemState();
State InitialState();
State CheckTriggerState();
State LeafState();

static RTLMenu current_item;
static RTLMenu current_menu;
static Window root_window;
static Display *display;
static int level;            /* submenu level */
static Time button_time;     /* time button press invoked */
static Cursor wait_cursor = None;  /* empty cursor for lock state */
static bool click_allowed;
static EventStore ev_save;
static bool locked = FALSE;

RTLMenuItem TrackMenu(root_menu, root_x, root_y, init_button, root, buttime)
    RTLMenu root_menu;    /* Pointer to root menu requested to pop up   */
    int root_x, root_y;   /* Position to start menu                     */
    int init_button;      /* The # of button used to pop up menu        */
    Window root;          /* Window label for parent of menu            */
    Time buttime;         /* timestamp for button (or 0, if CLICK == 0) */
{
    State CurrentState = LevelControl;
    XEvent Event_Reply;
    int open_x;
    bool selected = FALSE;
    RTLMenuItem selected_item;

    /* Initialize globals */

    button_time = buttime;
    root_window = root;
    level = 0;
    current_menu = root_menu;
    display = MenuDisplay(current_menu);
    click_allowed = (TestOptionFlag(current_menu, clickokay))? TRUE : FALSE;
    
    /* If not already done, set up the null cursor for lock state */
    if (wait_cursor == None)
    {
	Pixmap wc_pixmap;
	XColor fg, bg;
	
	wc_pixmap = XCreateBitmapFromData (display, root_window,
					   null_icon_bits,
					   null_icon_width, null_icon_height);
	wait_cursor = XCreatePixmapCursor (display, wc_pixmap, wc_pixmap,
					   &fg, &bg, 1, 1);
    }


    /* *** Put up initial menus, and get into correct state *** */

    AdjustPointer(current_menu, root_x, root_y);
    
    /* Get the present state, so it can be restored later */
    /* Any events on the queue when we start get saved now, restored later */
    SaveEvents (display, &ev_save, ~(unsigned long) ButtonReleaseMask);

    if (!GrabPointer() ||
	!(current_item = Display_Menu(current_menu, NULLMENU, root_x, root_y)))
    {
	CurrentState = Exit;
    }
    else
    {
	LockCursor(ItemWindow(current_item));
	open_x = root_x;
    }
    
    /* Push to appropriate previous item, if any */
    while (MenuHasInitialItem(current_menu) && (CurrentState != Exit))
    {
	ProcessExposeEvents();
	current_item = GetInitialItem(current_menu);
	ClearInitialItem(current_menu);
	
	/* if the initial item can't be selected, take first in list */
	if (ItemIsNull(current_item) || ItemIsDisabled(current_item))
	{
	    current_item = MenuItems(current_menu);
	    break;
	}
	else if (ItemIsLeaf(current_item)) /* then we're done */
	    break;
	else
	{
	    open_x += ItemGetArrowPosition(current_item);
	    Highlight(current_item); 
	    TossExtraMoves(ItemWindow(current_item)); 
	    (void)PushSubmenu(open_x);
	}
    }
    ProcessExposeEvents();
    if (CurrentState != Exit)
    {
	CurrentState = (ItemIsLeaf(current_item))? Leaf: CheckTrigger;
	if (!TestItemFlag(current_item, itemDisabled))
	    Highlight(current_item);
    }
    LockCursor(ItemWindow(current_item));
    PlacePointer(current_menu,current_item); 
    DisposeEvents(display, (Mask)(PointerMotionMask | EnterWindowMask |
				  LeaveWindowMask | ExposureMask));
    UnlockCursor();
	
    /* State Machine */

    while (CurrentState != Exit)
    {
	GetNextSignificantEvent(display, &Event_Reply, init_button);

	switch (CurrentState) 
	{
	case LevelControl:
	    CurrentState = LevelControlState(Event_Reply);
	    break;
	case Initial:
	    CurrentState = InitialState(Event_Reply);
	    break;
	case CheckTrigger:
	    CurrentState = CheckTriggerState(Event_Reply);
	    break;
	case Leaf:
	    CurrentState = LeafState(Event_Reply, &selected);
	    break;
	default:
	    CurrentState = Exit;
	    break;
	}
    }

    /* Clean up and exit */
    selected_item = (selected)? current_item : NULLITEM;
    while (level)
    {
	if (selected && !TestOptionFlag(current_menu, forgetlast))
            SetInitialItem(current_menu, current_item);
	PopSubmenu();
    }
    if (selected && !TestOptionFlag(current_menu, forgetlast))
    {
        SetInitialItem(current_menu, current_item);
    }
    Undisplay_Menu(current_menu);
    UnlockCursor();
    XUngrabPointer(display, CurrentTime);

    /* Push back any events that were lying around when menus started */
    XFlush(display);
    DisposeEvents(display,
		  (Mask) (PointerMotionMask | EnterWindowMask |
			  LeaveWindowMask));
    RestoreEvents(display, &ev_save);
    return(selected_item);
}

bool GrabPointer()
{
    int tries = 10;

    while((XGrabPointer(display,
			RootWindow(display, MenuScreen(current_menu)),
			True, CursorLockMask, GrabModeAsync, 
			GrabModeAsync, None,
			wait_cursor, CurrentTime) != GrabSuccess)
	  && tries--)
	sleep(1);
    if (tries)
	return(TRUE);
    else
	return(FALSE);
}

/* Lock the cursor: make it disappear, and ignore events it generates.  */
/* Optionally, confine it to a single window.                           */
/* (Using "None" for confine_window doesn't confine it.    )            */
void LockCursor(confine_window)
    Window confine_window;
{
    int result;
    
    locked = TRUE;
    result = XGrabPointer(display,
			  RootWindow(display, MenuScreen(current_menu)),
			  True, CursorLockMask, GrabModeAsync, 
			  GrabModeAsync, confine_window,
			  wait_cursor, CurrentTime);
    return;
}

/* Unlock (and unconfine) the cursor.  */
void UnlockCursor()
{
    int result;

    if (locked)
    {
	locked = FALSE;
	result = XGrabPointer(display, 
			      RootWindow(display, MenuScreen(current_menu)),
			      True, MenuEventMask,
			      GrabModeAsync, GrabModeAsync, None,
			      MenuCursor(current_menu), CurrentTime);
    }
    return;
    
}

/* Keep getting the X events, until finding one that may be interesting */
/* to the operation of the state machine. */
void GetNextSignificantEvent(displ,Event_Reply,init_button)
    Display *displ;
    XEvent *Event_Reply;
    int init_button;		/* the button that initiated the menu */
{
    XEvent Next_Event_Reply;
    bool InsignificantEvent = True;
    
    /* Loop as long as any of a number of "insignificant" events */
    /* are found; when the event no longer matches one of the tests, */
    /* it is assumed to be "significant" and returned.*/
    do
    {
	XNextEvent(displ, Event_Reply);

	/* If this event is an "enter", check whether there is a   */
	/* "leave" for the same window already in the queue,       */
	/* immediately following it; if so, throw them both out    */
	/* and get the next event                                  */
	/* NOTE: might try to look further ahead, but this is      */
	/* tricky because other events might intervene.            */
	if ((EventType(*Event_Reply) == EnterNotify) &&
	    (EventXMode(*Event_Reply) == NotifyNormal) &&
	    (QLength(displ) > 0) &&
	    (MenuGetMenu(current_menu, EventXWindow(*Event_Reply))
	     != current_menu))
	{
	    XPeekEvent(displ,&Next_Event_Reply);
	    if ((EventType(Next_Event_Reply) == LeaveNotify) &&
		(EventXMode(Next_Event_Reply) == NotifyNormal) &&
		(EventXWindow(Next_Event_Reply) == EventXWindow(*Event_Reply)))
	    {
		XNextEvent(displ, Event_Reply);
		XNextEvent(displ, Event_Reply);
	    }
	}
	if (EventNotSignificant(*Event_Reply, init_button))
	{
	    if (!(PointerEvent(*Event_Reply) || KeyEvent(*Event_Reply)
		  || EventType(*Event_Reply) == Expose))
	    {
		/* might be significant elsewhere -- save it for later */
		AddEventToStore(&ev_save, *Event_Reply);
	    }
	}
	else
	    InsignificantEvent = FALSE;
    }
    while (InsignificantEvent);
    return;
    
}

/* Check whether the event matches one of the events considered */
/* "not significant".*/
bool EventNotSignificant(Event_Reply, init_button)
    XEvent Event_Reply;
    int init_button;
{
    /* Insignificant if not in following list */
    return (!((EventType(Event_Reply) == ButtonRelease) ||
	      (EventType(Event_Reply) == MotionNotify) ||
	      (EventType(Event_Reply) == EnterNotify) ||
	      (EventType(Event_Reply) == Expose) ||
	      (EventType(Event_Reply) == LeaveNotify))
	    ||
    /* Insignificant if leave or enter is not "Normal"  */
	    (((EventType(Event_Reply) == LeaveNotify) ||
	     (EventType(Event_Reply) == EnterNotify)) &&
	     (EventXMode(Event_Reply) != NotifyNormal))
	    ||
    /* Insignificant if hit button other than initial one */
	    ((EventType(Event_Reply) == ButtonRelease) &&
	     (EventButton(Event_Reply) != init_button))
	    ||
    /* Insignificant if it's an expose and we're in savebits mode */
	    ((EventType(Event_Reply) == Expose) &&
	     TestOptionFlag(current_menu, savebits))
	    ||
    /* Insignificant if tail end of a click -- and clicks allowed */
	    (click_allowed &&
	     (EventType(Event_Reply) == ButtonRelease) &&
	     (EventBTime(Event_Reply) - button_time < CLICK_TIME))
	    );
}

State LevelControlState(rep)
    XEvent rep;
{
    State next_state;
    RTLMenu entered_menu;
    RTLMenuItem entered_item;
    
    switch (EventType(rep))
    {
    case MotionNotify:
    case LeaveNotify: 
	next_state = LevelControl; /* loop back to this state */
	break;
    case EnterNotify:
	/* Decide whether we've entered a menu window or item window */
	entered_menu = MenuGetMenu(current_menu, EventXWindow(rep));
	entered_item = MenuGetItem(current_menu,EventXWindow(rep));
	
	if ((MenuIsNull(entered_menu)) && (ItemIsNull(entered_item)))
	    /* Must be some other window; carry on */
	    next_state = LevelControl;
	else if (!ItemIsNull(entered_item) &&
		 MenuIsDisplayed(ItemMenu(entered_item)))
	{
	    /* we entered an item, but not a window. This should only happen */
	    /* when we stayed in the parent of the current submenu.  So,     */
	    /* Pop that submenu and get to the item.                         */
	    if (level)
	    {
		LockCursor(ItemWindow(entered_item));
		PopSubmenu();
		ProcessExposeEvents();
		UnlockCursor();
		current_item = entered_item;
		Highlight(current_item);
		next_state = GetItemState(rep);
	    }
	    else /* I must be very confused... */
	    {
		next_state = Exit;
	    }
	}

	else if (!MenuIsNull(entered_menu)&&
		 MenuIsDisplayed(entered_menu))
	{
	    /* entered a menu that is displayed */
	    while ((current_menu != entered_menu) && level)
		/* drop down the menu that was entered */
		PopSubmenu();
	    ProcessExposeEvents();
	    UnlockCursor();
	    if (current_menu == entered_menu)
		next_state = Initial;
	    else
	    {
		next_state = Exit;
	    }
	}
	else 
	    next_state = LevelControl;
	break;
    case ButtonRelease:
	next_state = Exit;
	break;
    default:
	next_state = Exit;
	break;
    }
    return next_state;
}

/* Figure out the status of the item we've just entered */
State GetItemState(rep)
    XEvent rep;
{
    int open_x;
    State next_state;
    
    if (ItemIsNull(current_item))
    {
	next_state = Exit;
    }
    else if (MenuIsNull(current_menu))
    {
	next_state = Exit;
    }
    else if (ItemIsLeaf(current_item) ||
	     (TestItemFlag(current_item, itemDisabled)))
    {
	if (MenuHasInitialItem(current_menu))
	    ClearInitialItem(current_menu);
	next_state = Leaf;
    }
    else if (EventGetXCoord(rep) >= (int) ItemGetArrowPosition(current_item))
    {
	/* entered item in "auto pop-up zone", i.e., over pull-right arrow. */
	LockCursor(ItemWindow(current_item));
	TossExtraMoves(ItemWindow(current_item));
	if (PushSubmenu(SelectChildX(current_menu, current_item, rep)))
	{
	    LockCursor(ItemWindow(current_item));
	    PlacePointer(current_menu, current_item); 
	    next_state = LevelControl;
	    ProcessExposeEvents();
	}
	else
	    next_state = CheckTrigger;
	UnlockCursor();
    }

    else if (MenuHasInitialItem(current_menu))
    {
	/* Entered menu has initial item -- move to it */
	current_item = GetInitialItem(current_menu);
	open_x = ItemGetArrowPosition(current_item) +
	    EventXRootX(rep);	    
	ClearInitialItem(current_menu);
	LockCursor(ItemWindow(current_item));
	if (PushSubmenu(open_x))
	{
	    ProcessExposeEvents();
	    LockCursor(ItemWindow(current_item));
	    PlacePointer(current_menu, current_item); 
	    next_state = Initial;
	}
	UnlockCursor();
    }
    else /* parent pull */
	next_state = CheckTrigger;
    return next_state;
    
}

State InitialState( rep)
    XEvent rep;
{
    State next_state;
    
    switch (EventType(rep))
    {
    case EnterNotify:
	if (MenuIsNull(current_menu))
	{
	    next_state = Exit;
	}
	else if (EventXDetail(rep) == NotifyInferior)
	    next_state = Initial;
	else
	{
	    current_item = MenuGetItem(current_menu, EventXWindow(rep));
	    if (ItemIsNull(current_item))
	    {
		next_state = Exit;
	    }
	    else
	    {
		Highlight(current_item);
		next_state = GetItemState(rep);
	    }
	}
	break;
    case LeaveNotify:
	/* Decide whether we're actually leaving      */
	/* this menu for another submenu or the root, */
	/* or going into an item.                     */
	next_state = (EventXDetail(rep) == NotifyInferior)?
	    Initial : LevelControl;
	break;
    case ButtonRelease:
	next_state = Exit;
	break;
    case MotionNotify:
	next_state = Initial;
	break;
    default:
	next_state = Exit;
	break;
    }
    return next_state;
    
}

#define NotSet -1
/* Look to see if pull-right is requested */
State CheckTriggerState(rep)
    XEvent rep;
{
    State next_state = CheckTrigger;
    static int Trigger = NotSet;
    static int OldX, NewX, childX;
    
    if (MenuIsNull(current_menu) || ItemIsNull(current_item))
    {
	next_state = Exit;
	goto exit;
    }
    if (Trigger == NotSet) /* set it */
    {
	Trigger = MIN(EventGetXCoord(rep) + MenuDelta(current_menu),
		      ItemGetArrowPosition(current_item));
	NewX = NotSet;
    }
    switch (EventType(rep))
    {
    case LeaveNotify:
	next_state = Initial;
	Unhighlight(MenuGetItem(current_menu, EventXWindow(rep)));
	Trigger = NotSet;
	break;
    case EnterNotify: /* Shouldn't really happen, but ... */
	next_state = CheckTrigger;
	break;
    case ButtonRelease:
	next_state = Exit;
	Trigger = NotSet;
	break;

    case MotionNotify:
	next_state = CheckTrigger;
	OldX = NewX;
	NewX = EventGetXCoord(rep);
	if (NewX >= Trigger)
	{
	    LockCursor(ItemWindow(current_item));
	    childX = SelectChildX(current_menu, current_item, rep);
	    Trigger = NotSet;
	    if (PushSubmenu(childX))
	    {
		next_state = LevelControl;
		ProcessExposeEvents();
		LockCursor(ItemWindow(current_item));
		PlacePointer(current_menu, current_item); 
	    }
	    UnlockCursor();
	}
	else if (NewX < OldX) /* reverse motion */
	    Trigger = MIN(Trigger, NewX + MenuDelta(current_menu));
	break;
    default:
	next_state = Exit;
	break;
    }
 exit:
    return next_state;
}

State LeafState(rep,selected)
    XEvent rep;
    bool *selected;
{
    State next_state;
    
    switch(EventType(rep))
    {
    case LeaveNotify:
	Unhighlight(MenuGetItem(current_menu, EventXWindow(rep)));
	next_state = Initial;
	break;
    case ButtonRelease:
	if (!TestItemFlag(current_item, itemDisabled)) 
	    *selected = TRUE;
	next_state = Exit;
	break;
    case EnterNotify:
    case MotionNotify: /* if events set right, this never happens */
	next_state = Leaf;
	break;
    default:
	next_state = Exit;
	break;
    }
    return next_state;
}

bool PushSubmenu(x)
    int x;
{
    int y;  
    bool pushed;
    RTLMenuItem new_current_item;
    
    if (ItemIsNull(current_item))
    {
	pushed = FALSE;
    }
    else if (MenuIsNull(ItemSubmenu(current_item)))
    {
	pushed = FALSE;
    }	
    else if (ItemIsNull(MenuItems(ItemSubmenu(current_item))))
	/* submenu has no items -- don't push, but not an error */
	pushed = FALSE;
    else
    {
	y =  ItemGetMiddleY(current_item);
	++level;
	    
	if (new_current_item =
	    Display_Menu(ItemSubmenu(current_item), current_menu, x, y))
	{
	    XFlush(display);
	    current_menu = ItemSubmenu(current_item);
	    current_item = new_current_item;
	    pushed = TRUE;
	}
	else
	{
	    pushed = FALSE;
	}
    }
    return pushed;
}

void PopSubmenu()
{
    RTLMenu parent;
    RTLMenuItem item;
    
    --level;
    parent = MenuParent(current_menu);
    Undisplay_Menu(current_menu);
    current_menu = parent;
    if (!MenuIsNull(current_menu))
    {
	item = MenuItemHighlighted(current_menu);
	if (!ItemIsNull(item))
	{
	    current_item = item;
	}
    }
    
    return;
    
}

void Highlight(item)
    RTLMenuItem item;
{
    RTLMenuItem old_highlight;
    
    
    old_highlight = MenuItemHighlighted(current_menu);
    if ((item != old_highlight) && /* else, already highlighted */
	(!ItemIsNull(item)))
    {
	if (!ItemIsNull(old_highlight))
	    Unhighlight(old_highlight); 
	if (!TestItemFlag(current_item, itemDisabled)) 
	{
	    MenuInvert(ItemMenu(item), ItemWindow(item));
	    SetHighlightItem(ItemMenu(item), item);
	}
    }
    return;
    
}

void Unhighlight(item)
    RTLMenuItem item;
{
    if (!ItemIsNull(item))
    {
	if (MenuItemHighlighted(current_menu) == item)
	{
	    MenuInvert(ItemMenu(item), ItemWindow(item));
	    ResetHighlightItem(ItemMenu(item));
	}
    }
    return;
    
}

void TossExtraMoves(window)
    Window window;
{
    XEvent ev;


    while (XCheckTypedWindowEvent(display, window, MotionNotify, &ev));

    return;
    
}

void ProcessExposeEvents()
{
    RTLMenuItem item;
    XEvent ev;

    if (!TestOptionFlag(current_menu, savebits))
    {
	XSync(display,0);
	
	while (XCheckTypedEvent(display, Expose, &ev))
	{
	    item = MenuGetItem(current_menu, EventXWindow(ev));
	    if (!ItemIsNull(item))
		Draw_Item(ItemMenu(item), item, EventEX(ev), EventEY(ev),
			  EventEWidth(ev), EventEHeight(ev));
	}
    }
    return;
}
