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

#include "basetype.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include "uwinXD.h"
#include "assoc.h"
#include "xio.h"
#include "tilecrsr.h"
#include "evsaveX.h"

/* ------------------------------------------------------------ */

bool send_mouse_events = FALSE;
bool pointer_grabbed = FALSE;
bool keyboard_grabbed = FALSE;

static Cursor previous_cursor;
static Cursor current_cursor;

/* ---------------------------------------------------------------------- */

void Control_Set_Cursor( tilecursor )
    TileCursor tilecursor;
{
    previous_cursor = current_cursor;
    current_cursor = tilecursor;

    if ( pointer_grabbed &&
         (previous_cursor != tilecursor) &&
         (tilecursor != None) )

        XChangeActivePointerGrab(dpy,
             PointerMotionMask |
             ButtonPressMask | ButtonReleaseMask,
             (Cursor) tilecursor, CurrentTime);
}

/* ---------------------------------------------------------------------- */

void Control_Restore_Cursor()
{
    current_cursor = previous_cursor;
    if ( pointer_grabbed && (previous_cursor != None) )

        XChangeActivePointerGrab(dpy,
             PointerMotionMask |
             ButtonPressMask | ButtonReleaseMask,
             (Cursor) previous_cursor, CurrentTime);
}

/* ------------------------------------------------------------ */

bool Control_Grab_User( send_mouse, tilecursor )
    bool send_mouse;
    TileCursor tilecursor;
{
    unsigned int  ev_mask;

    send_mouse_events = send_mouse;

    if ( send_mouse )
        ev_mask = PointerMotionMask | ButtonPressMask | ButtonReleaseMask;
    else
        ev_mask = ButtonPressMask | ButtonReleaseMask;

    if (XGrabPointer(dpy, root, False, ev_mask,
		     GrabModeAsync, GrabModeAsync,
		     (Window) None, (Cursor) tilecursor,
		     CurrentTime) == GrabSuccess)
    {
	pointer_grabbed = TRUE;
        previous_cursor = current_cursor;
        current_cursor = tilecursor;
	XFlush(dpy);	
        return TRUE;
    }
    else
	pointer_grabbed = FALSE;
    return pointer_grabbed;
}

/* ------------------------------------------------------------ */

void Control_Ungrab_User()
{
    pointer_grabbed = FALSE;
    send_mouse_events = FALSE;

      /* Play back events stored while grabbed */
    RestoreEvents(dpy, &stackp);
    XUngrabPointer(dpy, CurrentTime);
    XFlush(dpy);
}

/* ------------------------------------------------------------ */

void Control_Grab_Server()
{
    XGrabServer(dpy);
    XFlush(dpy);
}

/* ------------------------------------------------------------ */

void Control_Ungrab_Server()
{
    XUngrabServer(dpy);
    XFlush(dpy);
}

/* ------------------------------------------------------------ */

void Control_Set_Focus( uwinp )
    Userwin *uwinp;
{
    if (uwinp == (Userwin *) NULL)
    {
	XSetInputFocus(dpy, PointerRoot, RevertToPointerRoot, CurrentTime);
    }
    else
    {					/* XXXX Kludge here! XXXX */
	XWindowAttributes  xwa;
	

	XGetWindowAttributes(dpy, Userwin_XClient(uwinp), &xwa);

	if (xwa.map_state == IsUnmapped)
	{
	    XSetInputFocus(dpy, Userwin_XIcon(uwinp),
			   RevertToPointerRoot, CurrentTime);
	}
	else
	{
	    XSetInputFocus(dpy, Userwin_XClient(uwinp),
			   RevertToPointerRoot, CurrentTime);
	}
    }
}

/* ------------------------------------------------------------ */

void Control_Focus_Out( uwinp )
    Userwin *uwinp;
{}

/* ------------------------------------------------------------ */

void Control_Unset_Focus()
{
    XSetInputFocus(dpy, None, RevertToPointerRoot, CurrentTime);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static Window  last_ungrabbed_window = None;

/* ------------------------------------------------------------ */

/*  Post a Passive Grab (input redirection) on input to the
 *  client's window.  We want to know if anything is typed/moused
 *  in that window.
 */

void Control_Grab_Input(w)
    Window  w;
{
    XGrabButton(dpy, (unsigned int) AnyButton, (unsigned int) AnyModifier,
		w,
		False,
		(unsigned int) (ButtonPressMask | ButtonReleaseMask),
		GrabModeSync, GrabModeAsync,
		None,
		None);

    XGrabKey(dpy, (unsigned int) AnyKey, (unsigned int) AnyModifier,
	     w,
	     False,
	     GrabModeAsync, GrabModeSync);
}

/* ------------------------------------------------------------ */

void Control_Restore_Grab()
{
    if ( last_ungrabbed_window != None )
    {
	Control_Grab_Input(last_ungrabbed_window);
	last_ungrabbed_window = None;
    }
}

/* ------------------------------------------------------------ */
 /*  Release passive input grabs on keyboard and mouse buttons */

void Control_Release_Grab(uwinp)
    Userwin  *uwinp;
{

    if (last_ungrabbed_window != None)
    {
	Control_Restore_Grab();
    }

    XUngrabKey(dpy, (unsigned int) AnyKey, (unsigned int) AnyModifier,
	       Userwin_XParentWin(uwinp));

    XUngrabButton(dpy, (unsigned int) AnyButton, (unsigned int) AnyModifier, 
		  Userwin_XParentWin(uwinp));

    last_ungrabbed_window = Userwin_XParentWin(uwinp);
}

void Control_Destroy(uwinp)
    Userwin *uwinp;
{
    if (last_ungrabbed_window == Userwin_XParentWin(uwinp))
	last_ungrabbed_window = None;
}


bool Control_Pointer_To_Window(uwinp)
    Userwin *uwinp;
{
    int grab_status;
    
    grab_status = XGrabPointer(dpy, root, True, None,
			       GrabModeAsync, GrabModeAsync,
			       Userwin_XClient(uwinp), None, CurrentTime);
    if (grab_status == GrabSuccess)
	XUngrabPointer(dpy, CurrentTime);
    return (grab_status == GrabSuccess);
}

void Control_Exit()
{
    XSync(dpy, 1);
}



