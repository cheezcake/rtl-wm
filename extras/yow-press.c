/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                  Yow: A Zippy Example X11 Application
                  ------------------------------------

                              Mark Biggers
                    biggers%siemens.com@princeton.edu
                             (609) 734-3325
                              
                              Ellis Cohen
                       Ellis.Cohen@a.gp.cs.cmu.edu
                             (609) 734-6524
                              
                    Siemens RTL Tiled Window Project
                           105 College Rd East
                           Princeton NJ 08540

                               15 Dec 1987

Though the X11 protocol is now stable, the interaction between
application programs and window managers is still evolving.
While there are still some disagreements about these interactions,
we think that application writers will benefit from an example
program that reflects the current state.  Where there are
disagreements about usage, we will try to indicate what they
are.

The application, "Yow", was originally built to exercise our own
window manager.  It has evolved based on input from a variety of
individuals who are building real applications to better fit their
needs.

Yow is quite a bit longer and more complex than Dave Rosenthal's very
helpful "Hello World" program for a number of reasons.  First, it is
divided into a number of functions, each of which is a chunk that can
easily be reused or adapted.  Also, there are a number of specific
additional features provided and issues addressed.  These are discussed
in the notes that follow the code.

Yow is divided into two parts.  The first part is application
independent, and contains functions taken from a library (RTLib) we
have developed locally.  Applications share a variety of global variables
with the RTLib functions.  The RTLib functions generally DO need to be
called in the order they are invoked by Yow.

The first half of the program could be copied and either included
directly in an application or placed in a separate file.
Many users will additionally want to adapt RTLib_Process_Arguments and
RTLib_Get_Resources to their own needs.

Only the second and shorter half of the program is specific to the Yow
application.

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*  ************************************************************
 *  Yow is a simple zippy application that provides an example of how
 *  to use X11 to draw in a window and interact with a window manager.
 *  Yow centers a string in a window, and responds to button presses
 *  by enlarging or shrinking the window
 *  ************************************************************
 */

/* Copyright (c) 1987 Siemens Corporate Research and Support, Inc.,
 * Princeton, NJ.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the name of
 * Siemens not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.  Siemens makes no representations about the
 * suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 */
#ifndef lint
static char sccs_id[] = "@(#)yow.c	1.7 4/12/88  Copyright (c) 1987, Siemens Corporate Research and Support, Inc.";
#endif

#include <stdio.h>
#include <errno.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <sys/types.h>
#include <sys/timeb.h>

extern char  *malloc(), *getenv();
extern Window  XCreateSimpleWindow();

#define IS_NULL(s)  ((s) == (char *) 0)

/* ------------------------------------------------------------ */

#define DEFAULT_BORDER_WIDTH 2

/* ------------------------------------------------------------ */

#define INCLUDE_HOST_NAME         1  /* See Note 8 */
#define SET_ICON_FROM_WINDOW_NAME 1  /* See Note 8 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

    /* X structures SHARED WITH APPLICATION */

Display	   *dpy;          /* The display used */
int        screen;        /* The screen on the display */
Window     parent_window; /* The window in which to open the client window */
Window     window;        /* The client window */
XFontStruct  *fontp;      /* The font used for drawing */
GC         gc;            /* The graphics context used for drawing */

    /* desired & min geometry SHARED WITH APPLICATION */

unsigned int min_width, min_height;
unsigned int desired_width, desired_height;
int  desired_x, desired_y;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

    /* static string & hint storage */

static unsigned char host_str[100];
static char window_name_str[100];
static XSizeHints size_hint;
static char *resource_class;

/* ------------------------------------------------------------ */

    /* possible command line args */

static char *display = (char *) NULL;
static char *resource_name = (char *) NULL;
static char *window_name = (char *) NULL;
static char *icon_name = (char *) NULL;
static char *foreground_color = (char *) NULL;
static char *background_color = (char *) NULL;
static char *border_color = (char *) NULL;
static char *border_width = (char *) NULL;
static char *font = (char *) NULL;
static char *parent = (char *) NULL;
static char *geometry = (char *) NULL;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

    /* Process the command line.  Optional arguents are
     *   -r <resource name>
     *   -w <window name>
     *   -i <icon name>
     *   -c <foreground color>
     *   -b <background color>
     *   -e <border color>
     *   -s <border width>
     *   -p <parent window>
     *   -f <font name>
     *   -g <initial geometry>
     *   -d <display:screen>
     *
     *  See Note 1
     */

void RTLib_Process_Arguments(argc, argv)
    int argc;
    char *argv[];
{
    extern char    *optarg;
    extern int      optind, opterr;
    int             c;
    Bool            errflg = False;
    
    while ((c = getopt(argc, argv, "r:w:i:c:b:e:s:p:f:g:d:")) != EOF)
    {
	switch (c)
	{
	case 'r':
	    resource_name = optarg;
	    break;
	    
	case 'w':
	    window_name = optarg;
	    break;
	    
	case 'i':
	    icon_name = optarg;
	    break;
	    
	case 'c':
	    foreground_color = optarg;
	    break;
	    
	case 'b':
	    background_color = optarg;
	    break;
	    
	case 'e':
	    border_color = optarg;
	    break;
	    
	case 's':
	    border_width = optarg;
	    break;
	    
	case 'p':
	    parent = optarg;
	    break;
	    
	case 'f':
	    font = optarg;
	    break;
	    
	case 'g':
	    geometry = optarg;
	    break;
	    
	case 'd':
	    display = optarg;
	    break;
	    
	case '?':
	    errflg = True;
	    break;
	}
    }
    
    if (errflg)
    {
	fprintf(stderr, "usage: %s", argv[0]);
	fprintf(stderr, "\n -r <resource name> -w <window name> -i <icon name>");
	fprintf(stderr, "\n -c <foreground color> -b <background> -e <border>");
	fprintf(stderr, "\n -s <border width> -p <parent window> -f <font>");
	fprintf(stderr, "\n -g <geometry> -d <display>\n");
	exit(-1);
    }
}

/* ------------------------------------------------------------ */

    /* Open a connection to the X server
     * A <display:screen> argument on the command line
     *   (as saved in "display") indicates which screen on
     *   which display controlled by the server should be used.
     * If there was no such argument, display will be NULL, and
     *   XOpenDisplay will use the contents of the DISPLAY
     *   environment variable to indicate the display and sceen.
     */

void RTLib_Open_Display()
{
    if (!(dpy = XOpenDisplay(display)))
    {
	fprintf(stderr, "Failed to open display %s...\n", display);
	exit(1);
    }

    screen = DefaultScreen(dpy);
}

/* ------------------------------------------------------------ */

    /* Error_Handler hooked into Xlib.  See Note 2 */

int RTLib_Error_Handler(dpy, error)
    Display  *dpy;
    XErrorEvent  *error;
{
    char buffer[BUFSIZ];

    XGetErrorText(dpy, error->error_code, buffer, (int) BUFSIZ);

    fprintf(stderr, "X Error <%s>\n", buffer);
    fprintf(stderr, "  Request Major code: %d\n", error->request_code);
    fprintf(stderr, "  Request Minor code: %d\n", error->minor_code);
    fprintf(stderr, "  ResourceId 0x%x\n", error->resourceid);
    fprintf(stderr, "  Error Serial #%d\n", error->serial);
    fprintf(stderr, "  Current Serial #%d\n", dpy->request);

    return 0;
}    

/* ------------------------------------------------------------ */

    /* Determines whether the window "w" exists on "dpy" */

Bool RTLib_Window_Exists( w )
    Window w;
{
    XWindowAttributes  xwa;

    return XGetWindowAttributes(dpy, w, &xwa);
}

/* ------------------------------------------------------------ */

    /* A window's resource_class is the name of the application
     *
     * A window's resource_name is used to distinguish two instances
     * of the same application.  It is taken from the first of the
     * following that applies:
     *   a -r command line argument
     *   The RESOURCE_NAME environment variable
     *   argv[0]
     *
     * See Note 3
     */

void RTLib_Set_Resource_Name_And_Class(class,argv)
    char  *class;
    char  *argv[];
{
    extern char  *rindex();
    char  *nam;

    resource_class = class;

    if (IS_NULL(resource_name))
    {
        resource_name = getenv("RESOURCE_NAME");
	
	if (IS_NULL(resource_name) )
	{
	    if ( (nam = rindex(argv[0], '/')) != (char *) NULL )
	    {
		resource_name = nam + 1;
	    }
	    else
	    {
		resource_name = argv[0];
	    }
	}
    }
}

/* ------------------------------------------------------------ */

    /* Use resource_name to get resources from .Xdefaults file
     * Get any resource not already set by a command-line
     * argument.
     *
     * See Note 4
     */

void RTLib_Get_Resources()
{
    if (IS_NULL(window_name))
    	window_name = XGetDefault(dpy, resource_name, "Name");

    if (IS_NULL(icon_name))
    	icon_name = XGetDefault(dpy, resource_name, "IconName");

    if (IS_NULL(foreground_color))
    	foreground_color = XGetDefault(dpy, resource_name, "Foreground");

    if (IS_NULL(background_color))
    	background_color = XGetDefault(dpy, resource_name, "Background");

    if (IS_NULL(border_color))
    	border_color = XGetDefault(dpy, resource_name, "Border");

    if (IS_NULL(border_width))
    	 border_width = XGetDefault(dpy, resource_name, "BorderWidth");

    if (IS_NULL(font))
    	font = XGetDefault(dpy, resource_name, "BodyFont");

    if (IS_NULL(geometry))
    	geometry = XGetDefault(dpy, resource_name, "Geometry");
}

/* ------------------------------------------------------------ */

    /* Load the font */

void RTLib_Load_Font( default_font )
    char  *default_font;
{
    if ( IS_NULL(font) )
        font = default_font;
    
    if ( (fontp = XLoadQueryFont(dpy, font)) == (XFontStruct *) NULL )
    {
	fprintf(stderr, "Cannot load font %s, exiting!\n", font);
	exit(-2);
    }
}

/* ------------------------------------------------------------ */

    /* Determine the parent window specified either via the
     *   "-p" command line argument, or via the PARENT_DESKTOP
     *   environment variable.
     * If neither, or if the parent specified is not a window,
     *   the parent is the root window
     *
     * See Note 5
     */

void RTLib_Parent_Window()
{
    if (IS_NULL(parent))
    {
	parent = getenv("PARENT_DESKTOP");
    }
    
    if (IS_NULL(parent))
    {
	parent_window = RootWindow(dpy, screen);
    }
    else
    {
	parent_window = atoi(parent);
        if ( ! RTLib_Window_Exists( parent_window ) )
	    parent_window = RootWindow(dpy, screen);
    }
}

/* ------------------------------------------------------------ */

    /* Returns the parent window's width and height */

void RTLib_Parent_Size( pwidth, pheight )
    int *pwidth;
    int *pheight;
{
    XWindowAttributes xwa;

    XGetWindowAttributes( dpy, parent_window, &xwa );

    *pwidth = xwa.width;
    *pheight = xwa.height;
}

/* ------------------------------------------------------------ */

    /* Called after the application has set the minimum size
     *   and default initial size and position of the window
     *
     * If a geometry argument has been provided, then it determines
     *   the user-specified initial size and/or position
     * If no geometry argument has been provided, then
     *   leave the defaults set by the application alone.
     *
     * Set the size_hint structure appropriately
     *
     * See Note 6
     */

void RTLib_Set_Initial_Geometry()
{
    int result;

    size_hint.flags = PMinSize;   /* minimum size set */
    size_hint.min_width = min_width;
    size_hint.min_height = min_height;

    if (IS_NULL(geometry))
    {
        size_hint.flags |= PSize;    /* size set by program */
    }
    else
    {
	result = XParseGeometry(geometry,
				&desired_x, &desired_y,
				&desired_width, &desired_height);
            
	if (desired_width < min_width)
	    desired_width = min_width;

	if (desired_height < min_height)
	    desired_height = min_height;


        if ( (result & (WidthValue | HeightValue)) != 0 )
            size_hint.flags |= USSize;  /* size set by user */
        else
            size_hint.flags |= PSize;   /* size set by program */


        if ( (result & (XValue | YValue)) != 0 )
            size_hint.flags |= USPosition;  /* position set by user */

        if ( (result & ( XNegative | YNegative )) != 0 )
        {
            /* Set position relative to right or bottom edge
             *   of parent window if x or y was negative
             */

            int parent_width, parent_height;
            RTLib_Parent_Size( &parent_width, &parent_height );
            if ( (result & XNegative ) != 0 )
                desired_x += parent_width - desired_width + 1;
            if ( (result & YNegative ) != 0 )
                desired_y += parent_height - desired_height + 1;
        }
    }

    size_hint.width = desired_width;
    size_hint.height = desired_height;

    size_hint.x = desired_x;
    size_hint.y = desired_y;
}

/* ------------------------------------------------------------ */

    /* Returns pixel corresponding to "color",
     *  or if that fails, "default_color"
     */

unsigned long RTLib_Get_Color( color, default_color )
    char *color;
    unsigned long default_color;
{
    XColor  xcolor;

    if (! IS_NULL(color) &&
	XParseColor(dpy, DefaultColormap(dpy, screen),
		    color, &xcolor) &&
	XAllocColor(dpy, DefaultColormap(dpy, screen), &xcolor))
    {
	return xcolor.pixel;
    }
    else
	return default_color;
}

/* ------------------------------------------------------------ */

    /* Create the window that the application will use
     *   as a subwindow of that parent window.
     */

void RTLib_Create_Window()
{
    unsigned long  border, background;
    unsigned int  border_width_val;

    border = RTLib_Get_Color( border_color,
        BlackPixel(dpy, screen) );
    background = RTLib_Get_Color( background_color,
        WhitePixel(dpy, screen) );

    if ( IS_NULL(border_width) )
        border_width_val = DEFAULT_BORDER_WIDTH;
    else
        border_width_val = atoi(border_width);

    window = XCreateSimpleWindow(dpy, parent_window,
				 desired_x, desired_y,
				 desired_width, desired_height,
				 border_width_val,
				 border,
				 background);
}

/* ------------------------------------------------------------ */

    /* Determine the host on which the application is running
     * and use it to set the WM_CLIENT_MACHINE property.
     *
     * See Note 7
     */

void RTLib_Set_Host()
{
    gethostname(host_str, 100);
    host_str[99] = '\0';
    
    XChangeProperty(dpy, window, XA_WM_CLIENT_MACHINE, XA_STRING, 8,
		    PropModeReplace, host_str, strlen(host_str));
}

/* ------------------------------------------------------------ */

    /* Set WM_CLASS_HINTS from the resource_name and resource_class
     *
     * See Note 3
     */

void RTLib_Set_Class_Hints()
{
    XClassHint class_hint;

    class_hint.res_name = resource_name;	
    class_hint.res_class = resource_class;

    XSetClassHint(dpy, window, &class_hint);
}

/* ------------------------------------------------------------ */

    /* If WM_NAME was not set via the "-w" command line argument
     * or obtained as a resource, set it automatically as
     *   resource_name @ host (resource_class)
     * Eliminate the (resource_class) if the same as the resource_name
     * Eliminate the host if INCLUDE_HOST_NAME is false
     *
     * See Note 8
     */

void RTLib_Set_Name()
{
    if (SET_ICON_FROM_WINDOW_NAME && IS_NULL(icon_name))
        icon_name = window_name;

    if (IS_NULL(window_name))
    {
	window_name = window_name_str;
        
        if ( INCLUDE_HOST_NAME )
        {
            if ( strcmp(resource_class, resource_name) == 0 )
                sprintf(window_name, "%s @ %s",
                        resource_name,
                        host_str);
            else
                sprintf(window_name, "%s @ %s (%s)",
                        resource_name,
                        host_str,
                        resource_class);
        }
        else
        {
            if ( strcmp(resource_class, resource_name) == 0 )
                strcpy( window_name, resource_name );
            else
                sprintf(window_name, "%s (%s)",
                        resource_name,
                        resource_class);
        }
    }    

    XStoreName(dpy, window, window_name);
}

/* ------------------------------------------------------------ */

    /* Extend WM_NAME to append "str" to the basic WM_NAME set above
     *
     * See Note 10
     */

void RTLib_Extend_Name( str )
    char *str;
{
    char extend_name[100];
    
    strcpy( extend_name, window_name );
    strcat( extend_name, str );
    XStoreName(dpy, window, extend_name);
}

/* ------------------------------------------------------------ */

    /* If WM_ICON_NAME was not set via the "-i" command line argument
     * or obtained as a resource, or set from the window name
     * set it automatically as
     *   resource_name @ host
     * Eliminate the host if INCLUDE_HOST_NAME is false
     *
     * See Note 8
     */

void RTLib_Set_Icon_Name()
{
    char  icon_name_str[100];

    if (IS_NULL(icon_name))
    {
	icon_name = icon_name_str;

        if ( INCLUDE_HOST_NAME )
            sprintf(icon_name, "%s @ %s",
                    resource_name,
                    host_str);
        else
            strcpy( icon_name, resource_name );                    
    }

    XSetIconName(dpy, window, icon_name);
}

/* ------------------------------------------------------------ */

    /* Set WM_HINTS to indicate that the client does not take
     * responsibility for the input focus (but leaves it to the wm),
     * and that when the window is initially mapped, it should be opened
     * (rather than iconized).
     * This application does not bother to provide its own icon,
     * but leaves it to the wm to provide a default one.
     */

void RTLib_Set_WM_Hints()
{
    XWMHints  wmhints;

    wmhints.flags = InputHint | StateHint;

    wmhints.input = True;
    wmhints.initial_state = NormalState;

    XSetWMHints(dpy, window, &wmhints);
}

/* ------------------------------------------------------------ */

    /* Set the various window properties
     *
     * See Note 9
     */

void RTLib_Set_Properties( argv, argc )
    char  *argv[];
    int  argc;
{
    RTLib_Set_Class_Hints();
    RTLib_Set_Host();
    XSetCommand(dpy, window, argv, argc);
    RTLib_Set_Name();
    RTLib_Set_Icon_Name();
    XSetNormalHints(dpy, window, &size_hint);
    RTLib_Set_WM_Hints();
}

/* ------------------------------------------------------------ */

    /* Set the graphics context used for drawing in the window */

void RTLib_Set_GC()
{
    unsigned long  gcMask;
    XGCValues  gcv;

    gcMask = GCForeground | GCFunction | GCFont;
    gcv.font = fontp->fid;
    gcv.function = GXcopy;
    gcv.foreground = RTLib_Get_Color( foreground_color,
        BlackPixel(dpy, screen) );

    gc = XCreateGC(dpy, RootWindow(dpy, screen),
		   gcMask, &gcv);
}

/* ------------------------------------------------------------ */

    /* Called after the client has changed the desired window size
     *  based on the user's action
     * Check that the desired size is not less than the minimum.
     * First, request that the window is explicitly resized.
     * Then, update the size_hint and WM_NORMAL_HINTS to reflect
     *  the change
     *
     * See Note 11
     */

void RTLib_User_Resize()
{
    if ( desired_width < min_width )
	desired_width = min_width;

    if ( desired_height < min_height )
	desired_height = min_height;

    XResizeWindow(dpy, window, desired_width, desired_height);

    size_hint.flags &= ~PSize;  /*in case PSize was initially specified */
    size_hint.flags |= USSize;

    size_hint.width = desired_width;
    size_hint.height = desired_height;

    XSetNormalHints(dpy, window, &size_hint);
}

/* ------------------------------------------------------------ */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 *
 *    Everything above here is application independent
 *
 *    The code below is Yow-specifc
 *
 * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/* ------------------------------------------------------------ */

#define CLASS  "yow"		/* class of this program */

#define STR  "Smile if You Tile!"   /* string to display */

#define DEFAULT_FONT "vg-25"

#define SHOW_SIZE                 1  /* See Note 10 */
#define DESIRE_BASED              0  /* See Note 12 */

/* ------------------------------------------------------------ */

unsigned int cur_width, cur_height;   /* current window size */

/* ------------------------------------------------------------ */

    /* Update WM_NAME to display current height and width
     *  if SHOW_SIZE is set.   See Note 10.
     */

void Yow_Extend_Current_Size()
{
    char sizstr[20];
    
    if ( SHOW_SIZE )
    {
        sprintf( sizstr, "  < %d, %d >", cur_width, cur_height );
        RTLib_Extend_Name( sizstr );
    }
}
    
/* ------------------------------------------------------------ */

    /* Set the current window width and height
     *   based on information from the ConfigureNotify event
     * Update WM_NAME to display current height and width
     */

void Yow_Set_Current_Size(xconfigure)
    XConfigureEvent  xconfigure;
{
    cur_width = xconfigure.width;
    cur_height = xconfigure.height;
    Yow_Extend_Current_Size();
}

/* ------------------------------------------------------------ */

    /* Set the minimum window size so that "str" can be completely
     *   shown in the font.
     *   default initial size to 1.3 * the minimum size,
     *   and the default initial position is (0,0)
     * Initialize cur_width and cur_height from the desired counterparts
     *   after they have been adjusted by RTLib
     *
     * See Note 6
     */

void Yow_Set_Initial_Geometry( str )
    char *str;
{
    min_width = 4 + XTextWidth(fontp, str, strlen(str));
    min_height = 4 + fontp->max_bounds.ascent + fontp->max_bounds.descent;

    desired_width  = 1.3 * min_width;
    desired_height = 1.3 * min_height;
    desired_x = 0;
    desired_y = 0;
    
    RTLib_Set_Initial_Geometry();
    
    cur_width = desired_width;
    cur_height = desired_height;
}
 
/* ------------------------------------------------------------ */

    /* Shift Button 1 increases the desired window size by 10%
     * Shift Button 2 decreases the desired window size by 10%
     * Shift Button 3 means unmap the window
     * Ctrl Shift any button means exit
     * 
     * If DESIRE_BASED
     *   then increase or decrease based on the desired size
     *   else base it on the current window size
     *
     * See Note 12
     */

void Yow_Button_Press(xbutton)
    XButtonEvent  xbutton;
{
    if ( !(xbutton.state & ShiftMask) )
        return;
    
/*    if (xbutton.state & ControlMask)
        exit(0);*/

    if (xbutton.button == Button3)  /* unmap */
    {
        XUnmapWindow( dpy, window );
        return;
    }

    if (! DESIRE_BASED)
    {
        desired_height = cur_height;
        desired_width = cur_width;
    }

    if (xbutton.button == Button1)   /* increase size */
    {
        desired_height = desired_height * 1.1;
        desired_width = desired_width * 1.1;
    }
    else if (xbutton.button == Button2)   /* decrease size */
    {
        desired_height = desired_height / 1.1;
        desired_width = desired_width / 1.1;
    }

    RTLib_User_Resize();
}
    
/* ------------------------------------------------------------ */

    /* Draw a string "str", centered in the window */

void Yow_Center_String(str)
    char  *str;
{
    int  xc, yc;

    xc = (cur_width - XTextWidth(fontp, str, strlen(str))) / 2;
    yc = (cur_height +
	  fontp->max_bounds.ascent - fontp->max_bounds.descent) / 2;

    XClearWindow(dpy, window);
    XDrawString(dpy, window, gc, xc, yc, str, strlen(str));
}

/* ------------------------------------------------------------ */

main(argc, argv)
    int argc;
    char *argv[];
{
    XEvent  ev;
    
    RTLib_Process_Arguments(argc, argv);

    RTLib_Open_Display();
    XSetErrorHandler(RTLib_Error_Handler);

    RTLib_Set_Resource_Name_And_Class(CLASS,argv);
    RTLib_Get_Resources();
    RTLib_Parent_Window();
    RTLib_Load_Font( DEFAULT_FONT );
    Yow_Set_Initial_Geometry( STR );

    RTLib_Create_Window();
    RTLib_Set_Properties(argv, argc);
    Yow_Extend_Current_Size();
    RTLib_Set_GC();

    XSelectInput(dpy, window,
		 ExposureMask | ButtonPressMask | StructureNotifyMask | KeyPressMask );

    XMapWindow(dpy, window);

    for (;;)
    {
	XNextEvent(dpy, &ev);
	printf("%d\n",ev.type);
	
	switch(ev.type & 0x7f)            /* See Note 13 */
	{
            case Expose:
                if (ev.xexpose.count == 0)
                    Yow_Center_String(STR);
                break;
    
            case ButtonPress:
                Yow_Button_Press(ev.xbutton);
		break;

	    case ConfigureNotify:
		Yow_Set_Current_Size(ev.xconfigure);

            default:
                break;
	}
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

1) RTLib_Process_Arguments processes command line arguments.  These can
be used for specifying the display, the initial geometry, and various
resources.  We use one character arguments.  They are not standard, but
then again, there really is no standard here anyway.

Eventually, command line parsing should be handled by the Xrm faciilties
(in particular XrmParseCommand), however, they are currently in the
process of being changed.

Many users will wish to replace or adapt this function to handle
application-specific arguments.  In any case, processing of
arguments should be done early in the program.

------------------------------

2) RTLib_Error_Handler provides an error handler.  Errors resulting from X
server requests are printed out in a standard format.

------------------------------

3) RTLib_Set_Resource_Name_And_Class and RTLib_Set_Class_Hints set
WM_CLASS.  WM_CLASS was added to Standard Properties somewhat late and is
not set by XSetStandardProperties.  It consists of two fields: res_class,
and res_name.  These are used both by the application and by the window
manager to obtain resources for the client.

res_class should be set to the name of the application -- in this case,
"yow".

res_name is used to more specifically identify an instance of the
application, to distinguish it from other running instances.  The
distinction can be based either on the invocation or on the environment.

By default, res_name should be set to the name by which the application
was invoked -- argv[0] in Unix systems.  This should be overridden if the
RESOURCE_NAME environment variable is set (in Unix anyway).  Finally,
this should be overridden if a specific command line argument (we use
"-r") is provided.

The reader should be warned that there is no general consensus regarding
the setting of res_name.  However, this model has evolved through
our interactions with a number of application writers, and seems to
satisfy everyone's needs.

------------------------------

4) RTLib_Get_Resources shows how to get a variety of resources based on
WM_CLASS using the XGetDefault facilities.  We would prefer using the Xrm
facilities, however, they are in the process of being changed.
XGetDefault requires that resources be obtained solely using res_name.
When the Xrm facilities become stable, resources should be able to be
obtained based both on res_name and res_class.

Many users will wish to replace or adapt this function to handle
application-specific resources.  In any case, obtaining resources
should be done early in the program -- as soon as the resource name is
set.

------------------------------

5) RTLib_Parent_Window sets the parent window which may be specified,
either via a PARENT_DESKTOP environment variable, or via a -p command
line argument.  If neither, the parent window is the root.  The
application's window will be opened within the parent window.

The use of a parent window is not standard.  We are strongly urging that
clients use this model however.  There WILL be window managers that wish
to operate within a window rather than taking over the entire screen.
Applications that do not check for a parent window will not be able to
work in such an environment.

------------------------------

6) The yow-specific Yow_Set_Initial_Geometry sets the minimum window
size so that a specified string can always be shown.  The default
initial desired window size is set 1.3 times larger than this, and the
default position for the window is the upper left hand corner.

The application-independent RTLib_Set_Initial_Geometry is then called to
override the default if a geometry argument or resource has been
provided.
The desired size is used both in initially creating the window, and in
setting the size_hint structure, used to initialize WM_NORMAL_HINTS when
the window is later actually created.

------------------------------

7) RTLib_Set_Host sets WM_CLIENT_MACHINE to be the host machine on which
the client is running.  Window managers need to use this for a variety of
reasons.  Some may optionally show arrange to show it in the window
header (See Note 8).  Others may use it to distinguish between two
instances of an application that are running on different clients (where
res_name is not used to distinguish them) for the purposes of saving and
restoring layouts.

 ------------------------------

8) RTLib_Set_Name and RTLib_Set_Icon_Name automatically set WM_NAME and
WM_ICON_NAME if they are not provided either as arguments or from a
defaults file.  We have found that many users like to see the name of the
host on which the application is runnning in the window and icon.  Thus,
by default, we set WM_NAME to be

    res_name @ host (res_class)   [if res_name != res_class]
    res_name @ host               [if res_name == res_class]

and WM_ICON_NAME to be

    res_name @ host

There is some disagreement about whether the host should be included
by the client or by the window manager.  We believe that it would be
best for the window manager to determine which properties (e.g. WM_NAME,
WM_CLIENT_MACHINE, etc.) are displayed in windows and icons based on
defaults, and our window manager does this.
However, there are a number of window managers, such as wm, that do not
allow this possibility, and only show WM_NAME or WM_ICON_NAME. 
For the time being, we feel we must recommend that clients include the
hosts in the names.  However, the inclusion of the host name is
controlled by the constant INCLUDE_HOST_NAME.

Also, if the window name has been provided as an argument or from a
defaults file, but the icon name has not been, there is no clear
model of how to set the icon name.  If the constant
SET_ICON_FROM_WINDOW_NAME is 1, we set it to the provided window name.
If it is 0, we still set it to "res_name @ host" (or just "res_name").

------------------------------

9) RTLib sets the WM_CLASS property first.  This is important because
many window managers use res_name and res_class to set default options
and values for the window.  Properties that are set later may then
override these defaults, though a well-written window manager should be
able to handle properties set in any order.

Note that RTLib does not set WM_ZOOM_HINTS.  There is some controversy
over Zoom Hints, and it is likely that they will either be eliminated or
replaced in the near future.

------------------------------

10) Clients generally may wish other information to appear in the window
title.  RTLib_Extend_Name can be used to append a changing
application-specified string to WM_NAME.  Yow_Extend_Current_Size
optionally (based on the constant SHOW_SIZE) uses this function to append
the window's current size to WM_NAME and update it when the size changes.

------------------------------

11) RTLib_User_Resize is used when the client wants to resize its window.
REsizing is accomplished by both calling XResizeWindow and resetting
WM_NORMAL_HINTS.  This is a simplification of a more complex protocol
that has been proposed by DEC.  That protocol would be used when an
application needs to redraw itself even if its new size request cannot be
met at all.

------------------------------

12) Yow_Button_Press highlights an important issue that users should be
aware of -- the difference between a window's desired size, and its
current size.  When a client requests that a window's size be changed
(as in RTLib_User_Resize) to a new desired size, the window manager may
intercept the request and, because of layout constraints, grow the window
to some smaller size, or not even change it at all.  Thus the window's
current size may be different than its desired size.

If the user presses button1 (with shift depressed), the window size will
grow by 10%.  If button2 is pressed instead, the window size is shrunk by
10%.  By default, the basis for shrinking is the current size.  By
setting the constant DESIRED_BASED to 1, the basis for shrinking is the
current desired size.  On window managers that do not constrain layout,
there should be no difference, since the current and desired size are the
same.  On the Siemens RTL Tiled Window Manager, which will be available
shortly, the difference is quite dramatic.

Pressing button3 (with shift depressed) unmaps the window.  This is a
good test of window manager capabilities.  A window manager should open
a default icon when the window is unmapped.

------------------------------

13) In main, after obtaining the next event ev, the high order bit
in ev.type is masked out.  This bit is turned on by the X protocol
when the event was caused by a client XSendEvent rather than by
the server directly.  If the bit is not turned off, the case statement
based on ev.type will not work correctly.

XSendEvent is used in a number of ways.  Clients that wish to execute
scripts to play back canned demos can cause events this way.

In addition, window managers may use XSendEvent.  For example, when a
window manager reparents a window and then moves it, the client does not
receive a ConfigureNotify event.  A pending proposal suggests that all
window managers send a synthetic ConfigureNotify (using XSendEvent) in
this case.

The Siemens RTL Tiled Window Manager uses XSendEvent in a different way
-- it (optionally) uses XSendEvent to send key and button presses typed
while the cursor is in the window header on to the client (acting as if
the cursor were in the client's window).

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
