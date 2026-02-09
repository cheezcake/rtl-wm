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

#include "basetype.h"
#include "userglobD.h"
#include "uwinXD.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "xio.h"
#include "tilecrsr.h"
#include "icons/background.h"

#define XBORDERWIDTH	0

/*------------------------------------------------------------*/    

void
Draw_Init()
{
}

/*-----------------------------------------------------------------*/

/*  Create a Window Decoration, type InputOnly (transparent).
 */
static Window
Draw_Create_Decoration(parent)
    Window  parent;
{
    XSetWindowAttributes  attrs;


    /* XSelectInput for edges, corners and gadgets windows
     */
    attrs.event_mask = ButtonPressMask | ButtonReleaseMask |
	KeyPressMask | EnterWindowMask;


    /*  BorderWidth and Depth are zero for class InputOnly...
     */
    return  XCreateWindow(dpy, parent,
			  0, 0,
			  (unsigned) 100, (unsigned) 100,
			  0,
			  0, InputOnly,
			  DefaultVisual(dpy, scrn), CWEventMask,
			  &attrs);
}

/*------------------------------------------------------------*/    

/*  Create the Parent and Decoration X-Windows for the Decorated
 *  Client Window
 *
 *  NOTE: all Window dimensions are bogus - they will be
 *  configured to proper size later on...
 */
void
Draw_Create(uwinp)
    Userwin *uwinp;
{
    Window  parent;
    unsigned long  vmask;
    XSetWindowAttributes  attrs;


    /*  Create the Parent (frame) Window
     */
    vmask = CWBackPixel;

    attrs.background_pixel = WhitePixel(dpy, scrn);

    parent = Userwin_XParentWin(uwinp) =
	XCreateWindow(dpy, root,
		      0, 0, 
		      (unsigned) 100, (unsigned) 100,
		      XBORDERWIDTH,
		      DefaultDepth(dpy, scrn), (unsigned int) CopyFromParent,
		      DefaultVisual(dpy, scrn), vmask, &attrs);

    /* make sure it's below transients */
    XLowerWindow(dpy, Userwin_XParentWin(uwinp));

    /*  Create the Decoration Windows
     */
    Userwin_XTopBorder(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XTopBorder(uwinp), (Cursor) top_tilecursor);
    
    Userwin_XLeftBorder(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XLeftBorder(uwinp), (Cursor)
    left_tilecursor);

    Userwin_XRightBorder(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XRightBorder(uwinp), (Cursor) right_tilecursor);

    Userwin_XBottomBorder(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XBottomBorder(uwinp), (Cursor) bottom_tilecursor);

    Userwin_XTopLeftCorner(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XTopLeftCorner(uwinp),
		  (Cursor) top_left_tilecursor);

    Userwin_XTopRightCorner(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XTopRightCorner(uwinp),
		  (Cursor) top_right_tilecursor);

    Userwin_XBottomLeftCorner(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XBottomLeftCorner(uwinp),
		  (Cursor) bottom_left_tilecursor);

    Userwin_XBottomRightCorner(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XBottomRightCorner(uwinp),
		  (Cursor) bottom_right_tilecursor);

    Userwin_XHeader(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XHeader(uwinp), (Cursor) header_tilecursor);

    Userwin_XZoomGadget(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XZoomGadget(uwinp),
		  (Cursor) zoom_gadget_tilecursor);

    Userwin_XMoveGadget(uwinp) = Draw_Create_Decoration(parent);
    XDefineCursor(dpy, Userwin_XMoveGadget(uwinp),
		  (Cursor) move_gadget_tilecursor);

}

/*-----------------------------------------------------------------*/

/*  Configure a "input region" window.
 */
void
Draw_ConfigWin(win, left_x, top_y, width, height)
    Window  win;
    int  left_x, top_y;
    int  width, height;
{
    XWindowChanges  wc;
    unsigned int  wcmask;
    
    
    wc.x = left_x;
    wc.y = top_y;
    wc.width = width;
    wc.height = height;
    wcmask = CWX | CWY | CWWidth | CWHeight;

    XConfigureWindow(dpy, win, wcmask, &wc);

    XMapWindow(dpy, win);
}

/*-----------------------------------------------------------------*/

/*  "flash" the desktop or clang the bell to get attention...
    at the moment, X doesn't have a flash -- so we can only ring
    the bell.
 */
void
Draw_Flash()
{
    XBell(dpy,0);
}

/*------------------------------------------------------------*/    

/*ARGSUSED*/
int
Draw_Font_Height(id)
    int id;
{

    return 0;
}

/*------------------------------------------------------------*/    

/*  Return the number of chars in 'fontp' that
 *  can be drawn in 'width'.
 *
 *  The limits are:  max_chars > ndc > nc.
 */
int
Draw_Num_Drawables(s, fontp, width, max_chars)
    char  *s;
    XFontStruct *fontp;
    int  width;
    int  max_chars;
{
    int  ndc,			/* number of drawable chars */
         nc;			/* number of chars in string 's' */


    for (nc = 0; *s; s++, nc++)
	;

    /*  If we have a fixed-width font...
     */
/*  if (fontstruct->per_char == (XCharStruct *) NULL)
    {
*/
    ndc = width / fontp->max_bounds.width;

    if (nc < ndc)
    {
	ndc = nc;
    }
    
    
/*    }
    else
    {
	/ * punt for now.  Watch this space (or see Xlib/XTextExt.c) * /
    }
*/
    return  ( (max_chars < ndc) ? max_chars : ndc );
}

/*------------------------------------------------------------*/    

/*ARGUSED*/
int Draw_Get_Frame_Width()
{
    return 1000;
}

/*------------------------------------------------------------*/

/*ARGSUSED*/
int Draw_Get_Frame_Height()
{
    return 900;
}

/*------------------------------------------------------------*/

/*  Redraw the Tiled Window under X by covering it with
 *  a temporary window.
 *
 *  XXXX flashing caused by temp window contrasting with client window!
 */
void
Draw_Background_Rectangle( x0, y0, x1, y1 )
    int x0, y0, x1, y1;
{
    XSetWindowAttributes  xswa;
    Visual  visual;
    Window  win;


    xswa.background_pixel = WhitePixel(dpy, scrn);
    xswa.override_redirect = True;
    visual.visualid = CopyFromParent;

    win = XCreateWindow(dpy, DefaultRootWindow(dpy),
			x0, y0,
			(unsigned) (x1 - x0 + 1),
			(unsigned) (y1 - y0 + 1),
			0, DefaultDepth(dpy, scrn),
			InputOutput, &visual,
			CWBackPixel | CWOverrideRedirect, &xswa);

    XMapWindow(dpy, win);
    XDestroyWindow(dpy, win);
    
/*    XSync(dpy, 0);*/
}

/* -----------------------------------------------------------------
 *  Set the root window to display our favorite pixmap.
 */
int
Draw_Set_Background()
{
}

/*-----------------------------------------------------------------
 *  Reset the root window background to the default pixmap.
 */
int
Draw_Reset_Background()
{
}

/*-----------------------------------------------------------------
 *  Set the acceleration/threshold levels for mouse movement.
 *
 */
int
Draw_Set_Mouse_Control(accel, thres)
{
    
}
