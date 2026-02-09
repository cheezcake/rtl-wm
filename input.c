#ifndef lint
static char sccs_id[] = "%W%  %H%";
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

#include <stdio.h>
#include <stdlib.h>

#include "basetype.h"
#include "buttonsD.h"
#include "userglobD.h"
#include "uwinXD.h"

#include "control.h"
#include "current.h"
#include "events.h"
#include "manage.h"
#include "client.h"
#include "assoc.h"
#include "tilecrsr.h"
#include "draw.h"
#include "drawwin.h"
#include "region.h"
#include "interf.h"
#include "evsaveX.h"
#include "layout.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include "evstrings.h"		/* for debugging output */

#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>

#define RTL_VERSION	"5.1"
#include "patchlevel.h"

#ifndef RTLDISPLAY
#define RTLDISPLAY NULL
#endif

#include "smdebug.h"

/* externs in xio.h */
Window  root;
Display  *dpy;
int scrn;
pointer stackp;
Window transient_plane;
  
XEvent *current_Xevent;

static Time last_button_time, timeout_time;

static bool timer_set = FALSE;

/* set to indicate we've left a window we know about, but haven't */
/* yet entered a window we do know about -- so ignore user input  */
static bool limbo;

static void Input_Update_Current_Position();
extern void Tool_Initiate();
extern void Interf_Reenter_Region();

static char  *display;

/* ------------------------------------------------------------ */

void Input_Reenter()
{
    Input_Update_Current_Position();
    
    current_uwinp = Manage_Locate( current_pos );
    current_region = Region_Locate( current_uwinp, current_pos );
}

/* ------------------------------------------------------------ */

void Input_Determine_Buttons()
{
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Input_Update_Button_State( state )
    unsigned int state;
{
    if (state & Button1Mask)
	Buttons_Down( current_butstate, 0 );
    else
	Buttons_Up( current_butstate, 0 );
    if (state & Button2Mask)
	Buttons_Down( current_butstate, 1 );
    else
	Buttons_Up( current_butstate, 1 );
    if (state & Button3Mask)
	Buttons_Down( current_butstate, 2 );
    else
	Buttons_Up( current_butstate, 2 );
}    

/* ------------------------------------------------------------ */

static void Input_Update_Current_Position()
{
    Window  wroot, child;
    int  win_x, win_y;
    unsigned int  bmask;

    (void) XQueryPointer(dpy, root, &wroot, &child,
			 &current_pos.x, &current_pos.y,
			 &win_x, &win_y, &bmask);
}


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static TWRegion Input_Get_Region( w, uwinp )
    Window  w;
    Userwin *uwinp;
{
    TWRegion region;

    if (uwinp == UWIN_NULL)
        region = back_region;
    else if (uwinp->current_type == rtl)
        region = rtl_region;
    else
    {
        if (w == Userwin_XClient(uwinp))
            region = body_region;
        
        else if (w == Userwin_XHeader(uwinp))
            region = header_region;

        else if (w == Userwin_XIcon(uwinp))
            region = icon_region;

        else if (w == Userwin_XTopBorder(uwinp))
            region = top_region;
        else if (w == Userwin_XLeftBorder(uwinp))
            region = left_region;
        else if (w == Userwin_XRightBorder(uwinp))
            region = right_region;
        else if (w == Userwin_XBottomBorder(uwinp))
            region = bottom_region;

        else if (w == Userwin_XTopLeftCorner(uwinp))
            region = top_left_region;
        else if (w == Userwin_XTopRightCorner(uwinp))
            region = top_right_region;
        else if (w == Userwin_XBottomLeftCorner(uwinp))
            region = bottom_left_region;
        else if (w == Userwin_XBottomRightCorner(uwinp))
            region = bottom_right_region;

        else if (w == Userwin_XZoomGadget(uwinp))
            region = zoom_gadget_region;

        else if (w == Userwin_XMoveGadget(uwinp))
            region = move_gadget_region;
    }
    return region;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static XComposeStatus  compose_status = {NULL, 0};

static void Input_Handle_KeyPress( ev )
    XEvent *ev;
{
    char  buffer[10];
    int  n = 10;
    int  len;
    
    if (limbo == FALSE)
    {
	current_time = ev->xkey.time;
	len = XLookupString((XKeyEvent *)ev,
			    buffer, n,
			    (KeySym *) NULL,
			    &compose_status);
    
	if (len > 0)
	    current_ch = buffer[0];
	else
	    current_ch = '\0';
	
	current_pos.x = ev->xkey.x_root;
	current_pos.y = ev->xkey.y_root;
	
	
	SMTRANS(KEY);
    }
    
    XAllowEvents(dpy, AsyncKeyboard, CurrentTime);
}

/* ------------------------------------------------------------ */

#define X_TO_SUN_MSBUTTON(but)   ( (but) - 1 )

static void Input_Handle_ButtonPress( ev )
    XEvent *ev; 
{
    if (limbo == FALSE)
    {
	current_time = ev->xbutton.time;
    
	current_but = 
	    ( X_TO_SUN_MSBUTTON(ev->xbutton.button)
	     | ( ev->xbutton.state & ShiftMask ? SHIFT_DOWN : 0 )
	     | ( ev->xbutton.state & ControlMask ? CTRL_DOWN : 0 )
	     );

	current_pos.x = ev->xbutton.x_root;
	current_pos.y = ev->xbutton.y_root;

	last_button_time = ev->xbutton.time;
	
	Input_Update_Button_State( ev->xbutton.state );
	Buttons_Down( current_butstate, current_but );
	SMTRANS(DOWN);
    }
    XAllowEvents(dpy, AsyncPointer, CurrentTime);
}

/* ------------------------------------------------------------ */

static void Input_Handle_ButtonRelease( ev )
    XEvent *ev;
{
    if (limbo == FALSE)
    {
	current_time = ev->xbutton.time;
    
	current_but = 
	    ( X_TO_SUN_MSBUTTON(ev->xbutton.button)
	     | ( ev->xbutton.state & ShiftMask ? SHIFT_DOWN : 0 )
	     | ( ev->xbutton.state & ControlMask ? CTRL_DOWN : 0 )
	     );

	current_pos.x = ev->xbutton.x_root;
	current_pos.y = ev->xbutton.y_root;

	Input_Update_Button_State( ev->xbutton.state );
	Buttons_Up( current_butstate, current_but );
	SMTRANS(UP);
    }
    XAllowEvents(dpy, AsyncPointer, CurrentTime);
}

/* ------------------------------------------------------------ */

static void Input_Handle_Motion( ev )
    XEvent *ev;
{
    /*  Throw out all motion events but the last
     */
        
    while (XCheckTypedEvent(dpy, MotionNotify, ev))
	;

    Input_Update_Current_Position();
    
    current_time = ev->xmotion.time;
    
    SMTRANS(MOUSE);
}

/* ------------------------------------------------------------ */

static void Input_Handle_Enter( ev )
    XEvent *ev;
{
    Window  w;

    if (! Control_Pointer_Grabbed() )
    {
        /*  Throw out all Enter events but the last
         */
        
        while (XCheckTypedEvent(dpy, EnterNotify, ev))
            ;  

	limbo = FALSE;
	current_time = ev->xcrossing.time;
	if (ev->xcrossing.mode != NotifyGrab) 
        {
            w = ev->xcrossing.window;
            current_uwinp = (Userwin *) Assoc_Get( w ); 
            current_region = Input_Get_Region( w, current_uwinp );
            SMTRANS(ENTER);
        }
    }
}

/* ------------------------------------------------------------ */

static void Input_Handle_Leave( ev )
    XEvent *ev;
{
    Userwin *uwinp;
    Window  w;

    if (! Control_Pointer_Grabbed() )
    {
        /*  Throw out all Leave events but the last
         */
        
        while (XCheckTypedEvent(dpy, LeaveNotify, ev))
	    ;

	if (ev->xcrossing.mode == NotifyNormal)
	    limbo = TRUE;
        /*  Only notify if window we're leaving is a parent or icon.
         */
        w = ev->xcrossing.window;
        uwinp = (Userwin *) Assoc_Get( w ); 
	current_time = ev->xcrossing.time;
	
        if ( ev->xcrossing.mode == NotifyNormal && 
            uwinp != UWIN_NULL &&
            (ev->xcrossing.window == Userwin_XParentWin(uwinp) ||
             ev->xcrossing.window == Userwin_XIcon(uwinp)) &&
            uwinp == current_uwinp)
        {
            SMTRANS(LEAVE);
        }
	
    }
}

/* ------------------------------------------------------------ */

static void Input_Handle_FocusIn( ev )
    XEvent *ev;
{
    Userwin *uwinp;
    Window  w;

    if ( ev->xfocus.mode == NotifyNormal )
    {
        w = ev->xfocus.window;
        uwinp = (Userwin *) Assoc_Get( w );
        if ((uwinp != (Userwin *)NULL) &&
	    (Userwin_XTransient_For(uwinp) == None))
	    Interf_Handle_FocusIn(uwinp);
    }

}

/* ------------------------------------------------------------ */

static void Input_Handle_Expose( ev )
    XEvent *ev;
{
    Userwin *uwinp;
    Window w;

    w = ev->xexpose.window;
    uwinp = (Userwin *) Assoc_Get( w );

    if (uwinp != (Userwin *) NULL)
    {
        if (ev->xexpose.count == 0)
        {
            if (w == Userwin_XParentWin(uwinp))
            {
                Drawwin_Display_Wrapping(uwinp);
            }
            else if (w == Userwin_XIcon(uwinp))
            {
                DrawIcon_Display(uwinp);
            }
        }
    }
}

/* ------------------------------------------------------------ */

static void Input_Handle_Event(ev)
    XEvent  *ev;
{
    switch (ev->type)
    {

    case KeyPress:
        Input_Handle_KeyPress( ev );
        break;

    case ButtonPress:
        Input_Handle_ButtonPress( ev );
	break;

    case ButtonRelease:
        Input_Handle_ButtonRelease( ev );
	break;

    case MotionNotify:	     /*** Motion during Grabbed Pointer ***/
        Input_Handle_Motion( ev );
	break;

    case EnterNotify:
        Input_Handle_Enter( ev );
	break;

    case LeaveNotify:
        Input_Handle_Leave( ev );
	break;

    case FocusIn:     /*** Input focus to this win ***/
        Input_Handle_FocusIn( ev );
	break;

    case Expose:
        Input_Handle_Expose( ev );
	break;

    default:
	break;
    }

}

/* ------------------------------------------------------------
 *  Event timing routines.
 * ------------------------------------------------------------
 */
    
/* ------------------------------------------------------------
 */
static void
Input_Handle_Timer()
{	

    Input_Update_Current_Position();
    
    SMTRANS(WAIT);

    timer_set = FALSE;
}

/* ------------------------------------------------------------
 *  Cancel simulated timer.
 */
void
Input_Cancel_Wait()
{
    timer_set = FALSE;
}

/* ------------------------------------------------------------
 * Simulate an event timer, using X current timestamps
 */
void Input_Wait(timeout)
    int timeout;		/* value in milli-seconds */
{
    if (timer_set == FALSE)
    {
	/* assume event time is relative to last button press */
	timeout_time = last_button_time + timeout;
	timer_set = TRUE;
    }
}

/* ------------------------------------------------------------
 * cursor positioning
 * ------------------------------------------------------------
 */

/* ------------------------------------------------------------
 *  Relative warp of mouse position.
 */
void Input_Change_Pos( pt )
    TWPoint pt;
{

    /*      relative warp ---v    */
    XWarpPointer(dpy, None, None,
		 0, 0, 0, 0,
		 pt.x, pt.y);

    Input_Update_Current_Position();
    
}

/* ------------------------------------------------------------
 *  Resets mouse position.
 */
void
Input_Set_Pos( pt )
    TWPoint pt;
{

    XWarpPointer(dpy, None, root,
		 0, 0, 0, 0,
		 pt.x, pt.y);
    
    current_pos = pt;

    XFlush(dpy);
}

void Input_Handle_Child(sig, code, scp)
    int sig, code;
    struct sigcontext *scp;
{
    union wait status;
    struct rusage ru;
    
    (void) wait3(&status, WNOHANG, &ru);
    
}


/* ------------------------------------------------------------
 *  Rtl starts here!
 * ------------------------------------------------------------ */

static void Input_Setup()
{
    extern int Error_Handler();
    extern void Exit();
    XSetWindowAttributes attr;

    printf( "\nStarting the Siemens RTL Tiled Window Manager, " );
    printf("Version %s, Release %d\n", RTL_VERSION, PATCHLEVEL);
    fflush(stdout);

    if ( (dpy = XOpenDisplay(display)) == (Display *) NULL )
    {
	fprintf(stderr, "RTL: Could not open display device, exiting!\n");
	exit(1);
    }

    (void) signal(SIGHUP, SIG_IGN);
    (void) signal(SIGINT, Exit);
    (void) signal(SIGTERM, Exit);
    (void) signal(SIGPIPE, Exit);
    (void) signal(SIGCHLD, Input_Handle_Child);

    XSetErrorHandler(Error_Handler);

    scrn = DefaultScreen(dpy);
    root = RootWindow(dpy, scrn);

    /* create a window that is used to separate the tiled windows from */
    /* transient windows (which can be overlapped)                     */
    attr.override_redirect = True;
    transient_plane = XCreateWindow( dpy, root, 0, 0, 
				    (unsigned int) 1, (unsigned int) 1,
				    (unsigned int) 0, 0, 
				    InputOnly, CopyFromParent,
				    (unsigned int) (CWOverrideRedirect),
				    &attr );
}

/* ------------------------------------------------------------ */

static void Input_Init()
{
    extern int errorStatus;
    extern void Pause_RTL();

    errorStatus = False;

    XSelectInput(dpy, root, SubstructureRedirectMask | SubstructureNotifyMask |
		 ButtonPressMask | ButtonReleaseMask | KeyPressMask |
		 EnterWindowMask | LeaveWindowMask );

    XSync(dpy, False);

    if (errorStatus == True)
    {
	printf("\nYou must be running another window manager, bye!\n");
	Pause_RTL();
    }

    if (Assoc_InitTable() == FALSE)
    {
	fprintf(stderr, "Could not set up X resource-association table!\n");
	Pause_RTL();
    }


    /*  close TCP fd on exec() - so Tools from Menu work when RTL exits
     */
    if ((errorStatus = fcntl(ConnectionNumber(dpy), F_SETFD, 1)) == -1)
    {
        fprintf(stderr, "RTL: Child processes have TCP fd, exiting!\n");
	Pause_RTL();
    }

    XDefineCursor(dpy, root, (XID) background_tilecursor);
    Buttons_Clear( current_butstate );
    
}

/* ------------------------------------------------------------ */

static void Input_Set_Desktop_Size()
{
    Size  desksiz;
    Window	retroot;
    int  root_x, root_y;
    unsigned int  root_width, root_height;
    unsigned int  bw, depth;

    (void) XGetGeometry(dpy, (Drawable) root, &retroot,
                        &root_x, &root_y,
                        &root_width, &root_height,
                        &bw, &depth);

    UserGlobals_Set_Value( FULL_WIDTH, root_width );
    UserGlobals_Set_Value( FULL_HEIGHT, root_height );

    desksiz.width = root_width;
    desksiz.height = root_height;

    Manage_Set_Desktop_Size( desksiz );
}

/* ------------------------------------------------------------ */

static void Input_Set_Icon_Sizes()
{
    XIconSize  icon_size;

    icon_size.min_width = 64;
    icon_size.min_height = 64;
    icon_size.max_width = 64;
    icon_size.max_height = 64;
    icon_size.width_inc = 0;
    icon_size.height_inc = 0;
    
    XSetIconSizes(dpy, root, &icon_size, 1);
}

/* ------------------------------------------------------------ */

static void Input_Process_Event()
{
    XEvent ev;

    if (timer_set == TRUE && (current_time >= timeout_time))
        Input_Handle_Timer();

    if (QLength(dpy) == 0)/* XNextEvent doesn't flush anymore! (rel 2) */
        XFlush(dpy);
    XNextEvent(dpy, &ev);

    if (ev.xany.send_event == True)
    {
	/* someone sent this event to us --- ignore it */
        return;
    }

    if (ev.type == MotionNotify && (! Control_Pointer_Grabbed() ) )
        return;

    if ( Control_Pointer_Grabbed() &&
        !(ev.type == MotionNotify ||	  /* tracking the cursor. */
          ev.type == ButtonPress ||	
          ev.type == ButtonRelease))
    {
        AddEventToStore(&stackp, ev);
        return;
    }

    current_Xevent = &ev;
    
    if (ev.type < CreateNotify)
    {
        Input_Handle_Event(&ev);
    }
    else
    {
        Redirect_Handle_Event(&ev);
    }
}

/* ------------------------------------------------------------ */

main(argc,argv)
    int argc;
    char **argv;
{
    int use_startup_file = 0;
    int finish_layout = 0;
    int ignore_layout_file = 0;
    char c;
    extern void Wsys_Startup();
    
    argc--; argv++;
    while(argc)
    {
	if (strcmp(*argv, "-display") == 0)
	{
	    argc--; argv++;
	    if (argc > 0)
		display = *argv;
	}
	else if (strcmp(*argv, "-s") == 0)
	{
	    use_startup_file++;
	}
	else if (strcmp(*argv, "-f") == 0)
	{
	    finish_layout++;
	}
	else if (strcmp(*argv, "-i") == 0)
	{
	    ignore_layout_file++;
	}
	argc--; argv++;
    }

    Input_Setup();

    XGrabServer(dpy);

    Input_Set_Desktop_Size();
    Input_Init();
    Interf_Init();	/* initialize Cursors, Buttons, Menus, and Profiles */
    Manage_Init();	/* initialize drawing functions and Icons */
    Interf_Reset();

    Input_Set_Icon_Sizes();
    
    if (ignore_layout_file)
	Layout_Finish();
    
    Wsys_Startup();
    XUngrabServer(dpy);
    
    if (finish_layout)
	Layout_Finish();
    if (use_startup_file)
	Tool_Initiate();

    Interf_Reenter_Region();
    
    limbo = FALSE;
    
    FOREVER		/* window-input and client-request Event Loop */
        Input_Process_Event();
}
