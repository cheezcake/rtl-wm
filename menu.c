#ifndef lint
static char sccs_id[] = "@(#)menu.c	5.2  6/5/89";
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
#include <stdlib.h>
#include "copyright.h"

/*
  RTL Menu Package Version 1.2
  by Joe Camaratta and Mike Berman, Siemens RTL, Princeton NJ, 1988

  menu.c: menu utility and support functions.

  Originally hacked by Adam J. Richter, based on the menu package for xterm.
  ( misc.c  X10/6.6 )

*/

/*

Copyright 1985, 1986, 1987 by the Massachusetts Institute of Technology

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting
documentation, and that the name of M.I.T. not be used in
advertising or publicity pertaining to distribution of the
software without specific, written prior permission.
M.I.T. makes no representations about the suitability of
this software for any purpose.	It is provided "as is"
without express or implied warranty.

*/

/*
 * Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.
 *
 *			   All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of Digital Equipment
 * Corporation not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior permission.
 *
 *
 * DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#include "rtlmenuP.h"
#include <X11/X10.h>
#include "gray1_32.h"	  /* filled out to 32x32 pixels (works on color) */
#include "arrow_icon.h"
#include "arrow_ic32.h" /* filled out to 32x32 pixels (works on color) */
#include "check_ic32.h"
#define MakeEven(x) ((x%2 == 0)? x : x-1)
#define	InvertPlane		1

static char def_menu_font[] = "8x13";
Menu MenuDefault;
char *MenuDefaultFont;
static XAssocTable *menu_table;
static XAssocTable *item_table;
static bool tables_initialized = FALSE;
RTLMenuItem AddMenuItem(), Display_Menu(), MenuGetItem(),
	    MenuItemByName(), MenuItemByData(), GetInitialItem();
bool	    DisposeItem(), SetItemCheck(), SetItemDisable(),
	    SetItemText();
void	    DisposeMenu(), InitMenu(), Undisplay_Menu(), MenuInvert(),
	    PlacePointer(), Draw_Menu(), Draw_Item(),  SetInitialItem(),
	    ClearInitialItem();
RTLMenu	    NewMenu(), MenuGetMenu();
int	    ItemGetMiddleY();

static bool Recalc_Menu(RTLMenu menu);
static RTLMenuItem MoveMenu(RTLMenu menu, int ev_x, int ev_y);
static bool MapMenu(RTLMenu menu);
static void Generate_Menu_Entries(RTLMenu menu);
static void UnmapMenu(RTLMenu menu);
static bool SetupMenuWindow(RTLMenu menu);
static bool SetupItems(RTLMenu menu);
static void SetInputMask(RTLMenu menu, Mask mask);


/*
 * AddMenuItem() adds a menu item to an existing menu, at the end of the
 * list, which are number sequentially from zero.  The menuitem index is
 * return, or NULL if failed.
 */

RTLMenuItem 
AddMenuItem(menu)
    RTLMenu menu;
{
    RTLMenuItem menuitem, *next;
    
    if(!menu || ItemIsNull(menuitem = (RTLMenuItem)allocate(MenuItem, 1)))
	return(NULLITEM);
    bzero((char *)menuitem, sizeof(MenuItem));
    ItemText(menuitem) = NULL;
    ItemTextLength(menuitem) = 0;
    
    for(next = MenuItemsPtr(menu) ;
	*next; next = ItemNextPtr(*next));
    
    *next = menuitem;

    SetMenuFlag(menu, menuChanged);

    return(menuitem);
}

/*
 * DisposeItem() releases the memory allocated for the given indexed
 * menuitem.  Nonzero is returned if an item was actual disposed of.
 * It also checks to see whether the item we're disposing is the
 * initial item for the menu -- if so, null out the initial item.
 */
bool
DisposeItem(menu, item)
    RTLMenu menu;
    RTLMenuItem item;
{
    RTLMenuItem *next, *last, menuitem;
    
    if (MenuIsNull(menu) || ItemIsNull(item))
	return(FALSE);
    next = MenuItemsPtr(menu);
    do 
    {
	if(ItemIsNull(*next))
	    return(FALSE);
	last = next;
	next = ItemNextPtr(*next);
    }
    while((*last != item) && !ItemIsNull(*next));
    menuitem = *last;
    *last = *next;
    if (ItemWindow(menuitem)) {
	XDeleteAssoc(MenuDisplay((Menu *)menu),
		     item_table, ItemWindow(menuitem));
	XDestroyWindow(MenuDisplay((Menu *)menu), ItemWindow(menuitem));
    }
    if (ItemIsInitialItem(menu, menuitem))
	ClearInitialItem(menu);

    str_free(ItemText(menuitem));
    free((char*)menuitem);

    SetMenuFlag(menu, menuChanged);
    return(TRUE);
}

/*
 * DisposeMenu() releases the memory allocated for the given menu.
 */
void 
DisposeMenu(menu)
    RTLMenu menu;
{
    if(!menu)
	return;
    if (TestMenuFlag(menu, menuMapped))
	UnmapMenu(menu);
    while(DisposeItem(menu, MenuItems(menu)));
    if(MenuWindow(menu)) {
	XDeleteAssoc(MenuDisplay(menu), menu_table, MenuWindow((Menu *)menu));
	XDestroyWindow(MenuDisplay(menu), MenuWindow(menu));
    }
    XFreePixmap (MenuDisplay(menu), MenuGreyPixmap(menu));
    XFreePixmap (MenuDisplay(menu), MenuArrowPixmap(menu));
    XFreePixmap (MenuDisplay(menu), MenuCheckmarkPixmap(menu));
    XFreeGC (MenuDisplay(menu), MenuNormalGC(menu));
    XFreeGC (MenuDisplay(menu), MenuInvertGC(menu));
    XFreeGC (MenuDisplay(menu), MenuHighlightedGC(menu));

    if (MenuHasInitialItem(menu))
	ClearInitialItem(menu);
    free((char*) menu);
}

void 
InitMenu(name, options, display)
    char *name;
    RTLMenuOptionsMask options;
    Display *display;
{
    char *cp;

    MenuDefault.display = display;
    MenuDefault.menuFlags = menuChanged;
    
    MenuDefault.menuInitialItemText = (char *) NULL;
    MenuDefault.menuBorderWidth =
	(cp = XGetDefault(MenuDefault.display, name, "MenuBorder")) ?
	    atoi(cp) : 1; 
    MenuDefault.menuItemPad =
	(cp = XGetDefault(MenuDefault.display, name, "MenuPad")) ? atoi(cp) : 3;
    MenuDefault.delta = Default_Delta;
    /* Find a font to use -- check for defaults */
    cp = XGetDefault(MenuDefault.display, name, "MenuFont");
    if (cp == NULL)
        cp = XGetDefault(MenuDefault.display, name, "Font");
    MenuDefaultFont = (cp == NULL)? def_menu_font : cp;

    MenuDefault.menuOptions = options;
}

/*
 * ItemText changes the text of item of the menu.
 */
bool 
SetItemText(menu, item, text)
    RTLMenu menu;
    RTLMenuItem item;
    char *text;
{
    if (streql(ItemText(item), text))
	return (TRUE);
     
    str_replace(ItemText(item), text);

    ItemTextLength(item) = str_length(text);
    SetMenuFlag(menu, menuChanged);
    
    (void) Recalc_Menu (menu);
    return(TRUE);
}

/*
 * NewMenu() returns a pointer to an initialized new Menu structure, or NULL
 * if failed. The Menu structure MenuDefault contains the default menu settings.
 */
RTLMenu 
NewMenu(display, screen, reverse)
    Display *display;
    int screen;
    int reverse;
{
    extern Pixmap MakeGreyStipple ();
    RTLMenu menu;

    XGCValues gcValues, invertGCValues;
    static unsigned long gcMask =
	GCFunction | GCForeground | GCBackground | GCFont | GCStipple;
    static unsigned long invertgcMask = GCFont | GCFunction | GCForeground;

    /* Allocate the memory for the menu structure.  */
    if(MenuIsNull((menu = (RTLMenu)allocate(Menu, 1))))
	return(NULLMENU);

    /* Initialize to default values.   */
    *(Menu *)menu = MenuDefault;

    /* set options mask */
    MenuDisplay(menu) = display;
    MenuScreen(menu) = screen;

    /* If the menu font hasn't yet been gotten, go get it. */
    /* Try to open selected default font. If that failes, check to see      */
    /* if the one we#re opening is the "fall back" default, def_menu_font-- */
    /* if it is, exit.  Otherwise, try def_menu_font -- if that fails, exit */
    if ((MenuFontInfo(menu) = XLoadQueryFont (display, MenuDefaultFont))
         == NULL)
    {
        if (!strcmp(MenuDefaultFont,def_menu_font))
        {
            fprintf(stderr, "rtl: couldn't open font \"%s\"\n",
                    MenuDefaultFont);
            exit(1);
        }
        else
        {
            if ((MenuFontInfo(menu) = XLoadQueryFont (display, def_menu_font))
                 == NULL)
            {
                fprintf(stderr, "rtl: couldn't open font \"%s\" or \"%s\"\n",
                        MenuDefaultFont, def_menu_font);
                exit(1);
            }
        }
    }
    gcValues.font = MenuFontInfo(menu)->fid;

    /* If the menu cursor hasn't been given, make a default one. */
    MenuCursor(menu) = XCreateFontCursor (MenuDisplay(menu), XC_right_ptr);

    /* Make miscellaneous pixmaps */
    MenuArrowPixmap(menu) = XCreateBitmapFromData (MenuDisplay(menu),
					       RootWindow (display, screen),
					       arrow_32_bits,
					       arrow_32_width,
					       arrow_32_height);
    MenuGreyPixmap(menu) =	XCreateBitmapFromData (display,
					       RootWindow (display, screen),
					       gray1_32_bits,
					       gray1_32_width,
					       gray1_32_height);
    MenuCheckmarkPixmap(menu) = XCreateBitmapFromData (MenuDisplay(menu),
						   RootWindow (display, screen),
						   check_32_bits,
						   check_32_width,
						   check_32_height);
    /*
     * Initialize the default background and border pixmaps and foreground
     * and background colors (black and white).
     */
    if(reverse) {
	gcValues.foreground = WhitePixel (display, screen);
	gcValues.background = BlackPixel (display, screen);
    } else {
	gcValues.foreground = BlackPixel (display, screen);
	gcValues.background = WhitePixel (display, screen);
    }
    gcValues.stipple = MenuGreyPixmap(menu);
    gcValues.function = GXcopy;
    gcValues.subwindow_mode = IncludeInferiors;
    gcValues.graphics_exposures = False;
    MenuNormalGC(menu) =
	XCreateGC (display, RootWindow (display, screen),
		   gcMask | GCSubwindowMode | GCGraphicsExposures,  &gcValues);
    invertGCValues = gcValues;
    invertGCValues.foreground = gcValues.background;
    invertGCValues.background = gcValues.foreground;
    MenuHighlightedGC(menu) = XCreateGC (display, RootWindow (display, screen),
					 gcMask, &invertGCValues);

    gcValues.function = GXxor;
    gcValues.foreground = BlackPixel(MenuDisplay(menu), MenuScreen(menu)) ^
	WhitePixel(MenuDisplay(menu),MenuScreen(menu));
    MenuInvertGC(menu) = XCreateGC (display, RootWindow (display, screen),
				    invertgcMask, &gcValues);

    return(menu);
}

/*
 * SetItemCheck sets the check state of item of the menu to "state".
 */
bool 
SetItemCheck(menu, item, state)
    RTLMenu menu;
    RTLMenuItem item;
    int state;
{
    if (TestItemFlag(item,itemChecked)
	== state) /* Exit if unchanged */
	return (True);

    if (state)
	SetItemFlag(item, itemChecked);
    else
	ResetItemFlag(item, itemChecked);

    SetItemFlag(item, itemChanged);
    SetMenuFlag(menu, menuItemChanged);

    return(TRUE);
}

/*
 * SetItemDisable sets the disable state of item "n" of the menu to "state".
 */
bool 
SetItemDisable(menu, item, state)
    RTLMenu menu;
    RTLMenuItem item;
    int state;
{
    if (TestItemFlag(item,itemDisabled) == state) /* Exit if unchanged */
	return (True);

    if(state)
    {
	SetItemFlag(item, itemDisabled);
	/* if disabled item is currently initial item, null initial item */
	if (ItemIsInitialItem(menu, item))
	    ClearInitialItem(menu);
    }
    else
	ResetItemFlag(item, itemDisabled);

    SetItemFlag(item, itemChanged);
    SetMenuFlag(menu, menuItemChanged);

    return(TRUE);
}

RTLMenuItem 
Display_Menu(menu, parent, x, y)
    RTLMenu menu;
    RTLMenu parent;
    int x;
    int y;
{
    RTLMenuItem item;

    if (MenuIsNull(menu))
	return(FALSE);
	
    SetMenuParent(menu, parent);

    if (MenuIsNull(parent))
	MenuNested(menu) = 0;
    else
	MenuNested(menu) = MenuNested(parent) + 1;
	
    if (!SetupMenuWindow(menu))
	return NULL;
    if (TestOptionFlag(menu,savebits) &&
	(MenuSavedPixmap(menu) != (Pixmap) 0))
	SetInputMask(menu, MenuIgnoreMask);
    else
	SetInputMask(menu, MenuExposureMask);

    Generate_Menu_Entries(menu);
    if (!(item = MoveMenu(menu, x, y)) || !MapMenu(menu))
	return FALSE;

    Draw_Menu(menu);
    
    return(item);
}

void 
Undisplay_Menu(menu)
    RTLMenu menu;
{
    if (MenuIsNull(menu))
	return;

    SetMenuParent(menu, NULLMENU);
    MenuNested(menu) = 0;
    
    UnmapMenu(menu);
}

void 
MenuInvert(menu, w)
    RTLMenu menu;
    Window w;
{
	XFillRectangle (MenuDisplay(menu),
			w,
			MenuInvertGC(menu),
			0, 0, 
			MenuWidth(menu),
			MenuItemHeight(menu));
}

/*
 * Recalculate all of the various menu and item variables.
 */
static bool 
Recalc_Menu(menu)
    RTLMenu menu;
{
    RTLMenuItem item;
    int max, height, fontheight;
    
    /*
     * We must have already gotten the menu font.
     */
    if(!MenuFontInfo(menu))
	return(FALSE);
    /*
     * Initialize the various max width variables.
     */
    fontheight = MenuFontInfo(menu)->ascent + MenuFontInfo(menu)->descent + 2;
    height = 0;
    MenuMaxTextWidth(menu) = 0;
    /*
     * The item height is the maximum of the font height and the
     * checkbox height.
     */
    max = fontheight;
    if(checkMarkHeight > max)
	max = checkMarkHeight;

    max += 2*ItemBorder;
    max = MakeEven(max);
    MenuItemHeight(menu) = max;
    
    /*
     * Go through the menu item list.
     */
    for(item = MenuItems(menu) ; item ;
	item = ItemNext(item))
    {
	height += max;
	/*
	 * Check the text width with the max value stored in
	 * menu.
	 */
	if((ItemTextWidth(item) =
	    XTextWidth(MenuFontInfo(menu),
		       ItemText(item),
		       str_length (ItemText(item))))
	   > MenuMaxTextWidth(menu))
	    MenuMaxTextWidth(menu) = ItemTextWidth(item);
    }
    /*
     * Set the menu height and then set the menu width.
     */
    MenuHeight(menu) = height;
    MenuWidth(menu) = 4 * MenuItemPad(menu) + MenuMaxTextWidth(menu) +
	checkMarkWidth + arrow_width + (2 * ItemBorder);
    MenuItemWidth(menu) = MenuWidth(menu) - (2 * ItemBorder);
    return(TRUE);
}

/*
 * Figure out where to popup the menu, relative to the where the button was
 * pressed.
 * Returns pointer to initial item to warp to.
 */
static RTLMenuItem 
MoveMenu(menu, ev_x, ev_y)
    RTLMenu menu;
    int ev_x, ev_y;
{
    int x, y;
    int total_width, total_height;
    int offset;
    RTLMenuItem item;
    
    /*
     * Get the coordinates of the mouse when the button was pressed.
     */
    total_width = MenuWidth(menu) + 2 * MenuBorderWidth(menu);
    total_height = MenuHeight(menu) + 2 * MenuBorderWidth(menu);
    x = ev_x - MenuItemPad(menu);
    y = ev_y - MenuItemHeight(menu)/2;
    if (x < 0)
	x = 0;
    else if (TestOptionFlag(menu, rightoffset) &&
	     !MenuIsNull(MenuParent(menu)))
    {
	/* check whether parent is close to right edge... */
	/* "too close" means that child would leave < delta of its parent */
	/* visible to its left.						  */
	if (TestOptionFlag(menu, bigoffset))
	{
	    if (MenuX(MenuParent(menu)) + MenuWidth(MenuParent(menu)) > 
		DisplayWidth(MenuDisplay(menu), MenuScreen(menu)) - total_width)
		x = MenuX(MenuParent(menu))
		    - total_width + 2*MenuBorderWidth(menu);
	}
	else
	{
	    if (MenuX(MenuParent(menu)) + MenuDelta(MenuParent(menu)) > 
		DisplayWidth(MenuDisplay(menu), MenuScreen(menu)) - total_width)
	    {
		x = (MenuX(MenuParent(menu)) + MenuWidth(MenuParent(menu)) +
		     2 * MenuBorderWidth(MenuParent(menu))
		     - total_width - MenuDelta(menu));
	    }
	}
    }
    if (x + total_width > DisplayWidth(MenuDisplay(menu), MenuScreen(menu)))
	x = DisplayWidth(MenuDisplay(menu), MenuScreen(menu))
	    - total_width;

    /*
     * If we have an initial item, try to popup the menu centered
     * vertically within this item.
     */
    if(MenuHasInitialItem(menu)) {
	/*
	 * Look through the item list. "y" is the vertical position
	 * of the top of the current item and "n" is the item number.
	 */
	y = ev_y;
	offset = MenuBorderWidth(menu);
	for(item = MenuItems(menu) ; ;) {
	    /*
	     * On finding the intial item, center within this item.
	     */
	    if(ItemIsInitialItem(menu, item)) {
		offset += MenuItemHeight(menu) / 2;
		y -= offset;
		break;
	    }
	    offset += MenuItemHeight(menu);
	    /*
	     * If we run out of items, turn off the initial item
	     * and treat this as if no initial item.
	     */
	    if(!(item = ItemNext(item))) {
		ClearInitialItem(menu);
		y = ev_y - MenuItemHeight(menu)/2;
		goto noInitial;
	    }
	}
    }
noInitial:
    if (y < 0)
	y = 0;
    else if (y + total_height >
	     DisplayHeight(MenuDisplay(menu), MenuScreen(menu)))
    {
	y = DisplayHeight(MenuDisplay(menu), MenuScreen(menu))
	    - (total_height + 1);
    }
    y = MakeEven(y) + 1;
    if ((x != ev_x) || (y != ev_y))
	XMoveWindow(MenuDisplay(menu), MenuWindow(menu), x, y);
    MenuX(menu) = x;
    MenuY(menu) = y;

    if (!ItemIsInitialItem(menu, item))
	item = MenuItems(menu);
    return(item);
}

static 
bool MapMenu(menu)
    RTLMenu menu;
{
    if (! TestMenuFlag(menu, menuMapped))
	ResetMenuItemHighlighted(menu);
    if (TestOptionFlag(menu,savebits))
    {
	if ((MenuSavedPixmap(menu) == (Pixmap) 0) ||
	    (MenuOldWidth(menu) != MenuWidth(menu)) ||
	    (MenuOldHeight(menu) != MenuHeight(menu)) ||
	    (MenuOldBorderWidth(menu) != MenuBorderWidth(menu)))
	{
	    if (MenuSavedPixmap(menu) != (Pixmap) 0)
		XFreePixmap(MenuDisplay(menu), MenuSavedPixmap(menu));
	    MenuSavedPixmap(menu) =
		XCreatePixmap(MenuDisplay(menu), 
			      RootWindow(MenuDisplay(menu), MenuScreen(menu)), 
			      MenuWidth(menu) + 2*MenuBorderWidth(menu),
			      MenuHeight(menu) + 2*MenuBorderWidth(menu),
			      DefaultDepth(MenuDisplay(menu), MenuScreen(menu)));
	    MenuOldWidth(menu) = MenuWidth(menu);
	    MenuOldHeight(menu) = MenuHeight(menu);
	    MenuOldBorderWidth(menu) = MenuBorderWidth(menu);
	}
	else
	    SetInputMask(menu, MenuExposureMask);
	    
	if (MenuSavedPixmap(menu) != (Pixmap) 0) { 
	    SetInputMask(menu, MenuIgnoreMask);
	    XCopyArea(MenuDisplay(menu), 
		      RootWindow(MenuDisplay(menu), MenuScreen(menu)),
		      MenuSavedPixmap(menu),
		      MenuNormalGC(menu),
		      MenuX(menu), 
		      MenuY(menu), 
		      (unsigned int) (MenuWidth(menu) + 2*MenuBorderWidth(menu)), 
		      (unsigned int) (MenuHeight(menu) + 2*MenuBorderWidth(menu)), 
		      0, 0);
	}
	else
	    SetInputMask(menu, MenuExposureMask);
    }
    XRaiseWindow(MenuDisplay(menu), MenuWindow(menu));
    XMapWindow(MenuDisplay(menu), MenuWindow(menu));
    SetMenuFlag(menu, menuMapped);
    return(TRUE);
}

void 
PlacePointer(menu, item)
    RTLMenu menu;
    RTLMenuItem item;
{
    int y;
    
    y = ItemGetMiddleY(item);
    XWarpPointer(MenuDisplay(menu), None,
		 RootWindow(MenuDisplay(menu), MenuScreen(menu)), 
		 0, 0, 0, 0, 
		 MenuX(menu) + MenuItemPad(menu), y);
}

void AdjustPointer(menu, x, y)
    RTLMenu menu;
    int x, y;
{
    if (y == 0)
	XWarpPointer(MenuDisplay(menu), None,
		     RootWindow(MenuDisplay(menu), MenuScreen(menu)),
		     0, 0, 0, 0, x, 1);
    else if (y == (DisplayHeight(MenuDisplay(menu),
				 MenuScreen(menu)) - 1))
	XWarpPointer(MenuDisplay(menu), None,
		     RootWindow(MenuDisplay(menu), MenuScreen(menu)),
		     0, 0, 0, 0,
		     x, DisplayHeight(MenuDisplay(menu),
				      MenuScreen(menu)) - 2);
}


    
static void 
Generate_Menu_Entries (menu)
    RTLMenu menu;
{
    RTLMenuItem item;
    for (item = MenuItems(menu); item; (item = ItemNext(item))) {
	if (ItemGenerator(item)) {
	    char *newText;
	    
	    (ItemGenerator(item)) (&newText, &ItemCallback(item));
	    SetItemText (menu, item, newText);
	}
	
	if (ItemCheckproc(item))
	    SetItemCheck (menu, item, (ItemCheckproc(item))(menu,item));
    }
    (void) SetupMenuWindow (menu);
}

/* Draw the entire menu in the blank window. */
void 
Draw_Menu(menu)
    RTLMenu menu;
{
    RTLMenuItem item;
    
    ResetMenuFlag(menu, menuChanged);
    /* For each item in the list, first draw any check mark and then
       draw the rest of it. */
    for(item = MenuItems(menu) ; item ; item = ItemNext(item)) {
	if (TestOptionFlag(menu, savebits))
	{
	    /* go ahead and draw it, don't wait for exposes */
	    Draw_Item(menu, item, 0, 0, (int)MenuWidth(menu),(int)MenuItemHeight(menu));
	}
    }
}

/*
 * Draw the item  at vertical position y.
 */
void 
Draw_Item(menu, item, fill_x, fill_y, fill_width, fill_height)
    RTLMenu menu;
    RTLMenuItem item;
    int fill_x, fill_y, fill_width, fill_height;
{
    int y;  /* baseline */
    int x = MenuItemPad(menu);
    int x1 = 2 * MenuItemPad(menu) + checkMarkWidth;
    int pad;
    int high;
    XGCValues gcValues;

    if (TestItemFlag(item, itemDisabled))
    {
	gcValues.fill_style = FillOpaqueStippled;
	XChangeGC(MenuDisplay(menu), MenuNormalGC(menu),
		  (GCFillStyle), &gcValues);
    }
	
    high = (MenuItemHighlighted(menu) == item);
    
    if (high)
    {
	XSetFunction(MenuDisplay(menu), MenuNormalGC(menu), GXset);
	XFillRectangle(MenuDisplay(menu), ItemWindow(item),
		       MenuNormalGC(menu), fill_x, fill_y,
		       fill_width, fill_height);
	XSetFunction(MenuDisplay(menu), MenuNormalGC(menu), GXcopyInverted);
    }
    else
	XClearArea(MenuDisplay(menu), ItemWindow(item),
		   fill_x, fill_y, fill_width, fill_height, False);
    
    /*
     * Draw the check mark, possibly dimmed, wherever is necessary.
     */
    if(TestItemFlag(item, itemChecked)){
	XCopyPlane (MenuDisplay(menu), MenuCheckmarkPixmap(menu),
		    ItemWindow(item),
		    MenuNormalGC(menu),
		    0, 0, check_32_width, check_32_height,
		    (int) x, (MenuItemHeight(menu) - checkMarkHeight) / 2,
		    (unsigned long) 1);
    }

    /* Draw submenu indicator arrow */
    if(ItemSubmenu(item)) {
	XCopyPlane (MenuDisplay(menu), MenuArrowPixmap(menu),
		    ItemWindow(item),
		    MenuNormalGC(menu),
		    0, 0,
		    arrow_32_width, arrow_32_height,
		    (int) (x + MenuItemWidth(menu) -
			   arrow_width - MenuItemPad(menu)),
		    (MenuItemHeight(menu) - arrow_height) / 2 - 1,
		    (unsigned long) 1);
    }
    /*
     * Draw the text, centered vertically.
     */
    pad = (MenuItemHeight(menu) - 
	   (MenuFontInfo(menu)->ascent + MenuFontInfo(menu)->descent)) / 2;
    y = MenuItemHeight(menu) - pad - MenuFontInfo(menu)->descent;
    
    XDrawString (MenuDisplay(menu), ItemWindow(item), 
		 (high? MenuHighlightedGC(menu) : MenuNormalGC(menu)),
		 x1, y, ItemText(item), ItemTextLength(item));
    if (high)
	XSetFunction(MenuDisplay(menu), MenuNormalGC(menu), GXcopy);
    if (TestItemFlag(item, itemDisabled))
    { 
	gcValues.fill_style = FillSolid;
	XChangeGC(MenuDisplay(menu), MenuNormalGC(menu),
		  (GCFillStyle), &gcValues);
    }
       
}

/*
 * UnmapMenu() unmaps a menu, if it is currently mapped.
 */
static void 
UnmapMenu(menu)
    RTLMenu menu;
{
    if(!menu || !(TestMenuFlag(menu, menuMapped)))
	return;
    XUnmapWindow(MenuDisplay(menu), MenuWindow(menu));
/*    XClearWindow (MenuDisplay(menu), MenuWindow(menu));*/

    if (TestOptionFlag(menu, savebits))
    {
	if (MenuSavedPixmap(menu))
	    XCopyArea (MenuDisplay(menu),
		       MenuSavedPixmap(menu),
		       RootWindow (MenuDisplay(menu), MenuScreen(menu)),
		       MenuNormalGC(menu),
		       0, 0, 
		       MenuWidth(menu) + 2*MenuBorderWidth(menu),
		       MenuHeight(menu) + 2*MenuBorderWidth(menu),
		       MenuX(menu), MenuY(menu));
	
    }
    
    ResetMenuFlag(menu, menuMapped);
}

static bool 
SetupMenuWindow (menu)
    RTLMenu menu;
{
    int changed = TestMenuFlag(menu, (menuChanged | menuItemChanged));

    if (tables_initialized == FALSE) {
	tables_initialized = TRUE;
	if ((menu_table = XCreateAssocTable(Menu_Table_Size))
	    == (XAssocTable *) NULL)
	    return FALSE;
	if ((item_table = XCreateAssocTable(Item_Table_Size))
	    == (XAssocTable *) NULL)
	    return FALSE;
    }
	
    /*
     * If the entire menu has changed, throw away any saved pixmap and
     * then call RecalcMenu().
     */
    
    if(changed & menuChanged) {
	if(!Recalc_Menu(menu))
	    return FALSE;
	changed &= ~menuItemChanged;
    }

    if(!MenuWindow(menu)) {
	static unsigned long valuemask =
	    CWOverrideRedirect | CWBorderPixel | CWBackPixel;
	XSetWindowAttributes attributes;

	attributes.override_redirect = True;
	attributes.border_pixel =
	    XBlackPixel (MenuDisplay(menu), MenuScreen(menu));
	attributes.background_pixel = 
	    XWhitePixel (MenuDisplay(menu), MenuScreen(menu));
	
	if((MenuWindow(menu) =
	    XCreateWindow(MenuDisplay(menu), 
			  RootWindow (MenuDisplay(menu),
				      MenuScreen(menu)),
			  0, 0,
			  MenuWidth(menu), MenuHeight(menu),
			  MenuBorderWidth(menu),
			  DefaultDepth(MenuDisplay(menu),
				       MenuScreen(menu)),
			  InputOutput, 
			  DefaultVisual(MenuDisplay(menu),
					MenuScreen(menu)),
			  valuemask, &attributes)
	    ) == (Window)0)
	    return FALSE;
	else if (SetupItems(menu) == FALSE)
	    return FALSE;
	    
	XMakeAssoc(MenuDisplay(menu), menu_table, MenuWindow(menu),
		   (char *) menu);
	XMapSubwindows(MenuDisplay(menu), MenuWindow(menu));

	XDefineCursor(MenuDisplay(menu), MenuWindow(menu),
		      MenuCursor(menu));
    }
    else if(changed & menuChanged) {
	XResizeWindow(MenuDisplay(menu), MenuWindow(menu),
		      MenuWidth(menu), MenuHeight(menu));
	if (SetupItems(menu) == FALSE)
	    return FALSE;
	XMapSubwindows(MenuDisplay(menu), MenuWindow(menu));
    }

    return TRUE;
}

static bool 
SetupItems(menu)
    RTLMenu menu;
{
    int y;
    RTLMenuItem item;
    int changed = TestMenuFlag(menu, (menuChanged | menuItemChanged));
    
    for (item = MenuItems(menu), y = 0;
	 item;
	 y += MenuItemHeight(menu), item = ItemNext(item)) {
	 if (!ItemWindow(item)) {
	     static unsigned long valuemask =
		 CWOverrideRedirect | CWBorderPixel | CWBackPixel;
	     XSetWindowAttributes attributes;
	     attributes.override_redirect = True;
	     attributes.border_pixel =
		 XBlackPixel (MenuDisplay(menu), MenuScreen(menu));
	     attributes.background_pixel = 
		 XWhitePixel (MenuDisplay(menu), MenuScreen(menu));

	     if((ItemWindow(item) =
		 XCreateWindow(MenuDisplay(menu), 
			       MenuWindow(menu),
			       0, y, 
			       MenuItemWidth(menu), 
			       MenuItemHeight(menu)-(2 * ItemBorder), 
			       ItemBorder,
			       DefaultDepth(MenuDisplay(menu),
					    MenuScreen(menu)),
			       InputOutput, 
			       DefaultVisual(MenuDisplay(menu),
					     MenuScreen(menu)),
			       valuemask, &attributes)
		 ) == (Window) 0)
		return FALSE;
	     SetItemMenu(item, menu);
	     XMakeAssoc(MenuDisplay(menu), item_table, ItemWindow(item),
		       (char *) item);
	     XDefineCursor(MenuDisplay(menu), ItemWindow(item),
			  MenuCursor(menu));
	}
	else if(changed & menuChanged) {
	    XResizeWindow(MenuDisplay(menu), ItemWindow(item),
			  MenuItemWidth(menu), 
			  MenuItemHeight(menu) - (2 * ItemBorder));
	    XMoveWindow(MenuDisplay(menu), ItemWindow(item), 0, y);
	}
    }
    return TRUE;
}

static void 
SetInputMask(menu, mask)
    RTLMenu menu;
    Mask mask;
{
    RTLMenuItem item;
    
    XSelectInput(MenuDisplay(menu), MenuWindow(menu),
		 (mask | MenuEventMask));
    for(item = MenuItems(menu) ; item ; item = ItemNext(item))
    {
	if (TestItemFlag(item, itemDisabled))
	    XSelectInput(MenuDisplay(menu), ItemWindow(item),
			 (mask | NormalItemEventMask));
	else if (ItemIsLeaf(item))
	    XSelectInput(MenuDisplay(menu), ItemWindow(item),
			 (mask | NormalItemEventMask));
	else
	    XSelectInput(MenuDisplay(menu), ItemWindow(item),
			 (mask | SubmenuItemEventMask));
    }
}

RTLMenuItem 
MenuItemByData(menu, data)
    RTLMenu menu;
    generic data;
{
    RTLMenuItem item;

    for (item = MenuItems(menu);
	 !ItemIsNull(item) && !EqualGen(ItemData(item), data);
	 item = ItemNext(item));

    return item;
}   

RTLMenuItem 
MenuItemByName (menu, name)
    RTLMenu menu;
    char *name;
{
    RTLMenuItem item;

    for (item = MenuItems(menu); item; item = ItemNext(item))
	if (streql (name, ItemText(item)))
	    return item;
    return NULLITEM;
}

RTLMenuItem 
MenuGetItem(menu, window) 
    RTLMenu menu;
    Window window;
{    
    return (RTLMenuItem)(XLookUpAssoc(MenuDisplay(menu), item_table, window));
}

RTLMenu 
MenuGetMenu(menu, window)
    RTLMenu menu;
    Window window;
{
    return (RTLMenu )(XLookUpAssoc(MenuDisplay(menu), menu_table, window));
}

int 
ItemGetMiddleY(item)
    RTLMenuItem item;
{
    Window child;
    XWindowAttributes attributes;
    int x, y;

    XGetWindowAttributes(MenuDisplay(ItemMenu(item)), ItemWindow(item), 
			 &attributes);
    XTranslateCoordinates(MenuDisplay(ItemMenu(item)), 
			  MenuWindow(ItemMenu(item)), 
			  RootWindow(MenuDisplay(ItemMenu(item)),
				     MenuScreen(ItemMenu(item))), 
			  attributes.x, attributes.y, 
			  &x, &y, &child);
    return MakeEven(y + (MenuItemHeight(ItemMenu(item))/2));
}

void 
SetInitialItem(menu, item)
    RTLMenu menu;
    RTLMenuItem item;
{
	
	if (MenuHasInitialItem(menu)) {
	    if (str_length(MenuInitialItemText(menu)) < str_length(ItemText(item)))
		MenuInitialItemText(menu) =
		    realloc(MenuInitialItemText(menu), 
			    str_length(ItemText(item)) + 1);
	}
	else
	    MenuInitialItemText(menu) =
		allocate(char,(str_length(ItemText(item)) + 1));
	str_copy(MenuInitialItemText(menu), ItemText(item));
}

void 
ClearInitialItem(menu)
    RTLMenu menu;
{
    if (MenuHasInitialItem(menu)) {
	free(MenuInitialItemText(menu));
	MenuInitialItemText(menu) = (char *) NULL;
    }
}

RTLMenuItem 
GetInitialItem(menu)
    RTLMenu menu;
{
    RTLMenuItem item;
    
    if (MenuHasInitialItem(menu)) {
	for(item = MenuItems(menu) ; item ; item = ItemNext(item)) {
	    if (ItemIsInitialItem(menu, item))
		return(item);
	}
    }
    return((RTLMenuItem) NULL);
}



