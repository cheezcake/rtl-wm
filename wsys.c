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

/*  This module is the window creation and mapping interface
 *  of Rtl to X-windows.
 */
#include "uwinD.h"
#include "uwinXD.h"
#include "manage.h"
#include "interf.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include "assoc.h"
#include "xio.h"
#include "control.h"

#define NoState -1
#define ClientIconState 2
#define IgnoreState 5

#define CLIENT_SELECT	    /* def'd if you want StructNotify
                               * on Client Windows!
                               * (eliminates spurious events) */

#ifdef CLIENT_SELECT
#define notify StructureNotifyMask |
#define subnotify SubstructureNotifyMask |
#endif

#ifndef CLIENT_SELECT
#define notify
#define subnotify
#endif

/* ------------------------------------------------------------ */

int Wsys_Initial_Geometry( uwinp, x, y, width, height)
    Userwin *uwinp;
    int  x, y, width, height;
{
    TWPoint  pt;
    Size  size;

    pt.x = x;
    pt.y = y;
    size.width = width;
    size.height = height;
    
    Manage_Initial_Geometry(uwinp, pt, size);
}

/* ------------------------------------------------------------ */

/*  Map a Decorated Client window, upon a MapRequest
 *  from the X-server. */

int Wsys_Map( uwinp )
    Userwin  *uwinp;
{
    Interf_Client_Open(uwinp);
}

/* ------------------------------------------------------------ */

/* Prepare a window to be opened
 */

Userwin *Wsys_Prepare(client)
    Window client;
{
    Userwin  *uwinp;
    XWindowChanges  wc;

    uwinp = Manage_Create_Window();	 /* create Rtl Tiled Win */
    Userwin_XClient(uwinp) = client;
    Userwin_XClient_Icon(uwinp) = (Window) NULL;
    Userwin_Border_Width(uwinp) = 0;
    
    Assoc_Put((char *) uwinp, client);

    uwinp->iconpix = None;
    Property_Get_Window_Class(uwinp);
    Property_Get_Title(uwinp);
    Property_Get_Command_Line(uwinp);
    Property_Get_Hostname(uwinp);
    Property_Get_Icon_Title(uwinp);
    Property_Get_Normal_Size_Hints(uwinp);
    Property_Get_Wm_Hints(uwinp);
    Property_Get_Wm_State(uwinp);
    Property_Get_Dialogue_Parent(uwinp);
   
    if (Userwin_XTransient_For(uwinp) == None)
    {
	Assoc_AddDecorations(uwinp);

	wc.border_width = 0;		 /* Remove Client's border */
	XConfigureWindow(dpy, client, CWBorderWidth, &wc);

	XSelectInput(dpy, Userwin_XParentWin(uwinp), /* Parent event mask */
		     subnotify
		     SubstructureRedirectMask |
		     FocusChangeMask | LeaveWindowMask | ExposureMask);

	XSelectInput(dpy, client,		 /* mask for Client events */
		     notify
		     EnterWindowMask | PropertyChangeMask);

	Interf_Enable_Input(uwinp);
	Control_Grab_Input(Userwin_XParentWin(uwinp));
    }

    return(uwinp);
}
    
/* ------------------------------------------------------------ */

/*  Create a Decorated client-window upon a CreateNotify
 *  from the X-server. */   

int Wsys_Create( client, attrs)
    Window  client;
    XWindowAttributes attrs;
{
    Userwin  *uwinp;

    uwinp = Wsys_Prepare(client);

    if(Userwin_XTransient_For(uwinp) == None)
    {
	Userwin_Border_Width(uwinp) = attrs.border_width;
	Wsys_Initial_Geometry( uwinp, attrs.x, attrs.y,
			      attrs.width, attrs.height );
	Property_Get_Geometry_Hints(uwinp);
    }
}

/* ------------------------------------------------------------ */

/*  Create a Decorated client-window or client Icon,
 *  upon startup of Rtl under the X-server. */

int Wsys_Open( client, attrs )
    Window  client;
    XWindowAttributes  attrs;
{
    Userwin *uwinp;

    uwinp = Wsys_Prepare(client);

    if(Userwin_XTransient_For(uwinp) == None)
    {
	Userwin_Border_Width(uwinp) = attrs.border_width;
	
	Userwin_Initially_Mapped(uwinp) = (attrs.map_state != IsUnmapped);
	if (Userwin_XClient_Icon(uwinp) != (Window) NULL)
	{
	    XWindowAttributes icon_attrs;

	    XGetWindowAttributes(dpy,
				 Userwin_XClient_Icon(uwinp),
				 &icon_attrs);	

	    Userwin_Initially_Icon_Mapped(uwinp) =
		(icon_attrs.map_state != IsUnmapped);
	}
	else
	    Userwin_Initially_Icon_Mapped(uwinp) = FALSE;
    
	Manage_Determine_Startup_State(uwinp);

	Wsys_Initial_Geometry(uwinp, attrs.x, attrs.y,
			      attrs.width, attrs.height);
	    
    
	if (Userwin_Startup_State(uwinp) != IgnoreState)
	    Manage_Startup_Open(uwinp);
	else
	    Manage_Eliminate_Window(uwinp);
    }
}

/* ------------------------------------------------------------ */

static void
Wsys_Get_Startup_Parameters(w, icon, state)
    Window w;
    Window *icon;
    int *state;
{
    XWMHints  *ph;
    
    *state = NoState;
    *icon = (Window) NULL;
    
    if ((ph = XGetWMHints(dpy, w)) != (XWMHints *) NULL )
    {
	if (ph->flags & IconWindowHint)
	{
	    *icon = ph->icon_window;
	}
	if (ph->flags & StateHint)
	{
	    *state = ph->initial_state;
	}
	XFree( (char *) ph );
    }
}

/* ------------------------------------------------------------ */

    /*  If any X-clients already exist, put them in Tiled Desktop */

void Wsys_Startup()
{
    Window parent;
    Window *children;
    Window icon;
    Window w;
    XWindowAttributes attrs;
    unsigned int nchildren;
    int state;
    int ix;

    Assoc_Xid_InitTable();

    if (XQueryTree(dpy, root, &root, &parent, &children, &nchildren))
    {
	for (ix=0; ix < nchildren; ix++)
	{
	    w = children[ix];
	    Wsys_Get_Startup_Parameters(w, &icon, &state);
	    /* put icon in assoc table with window as data */
	    if (icon != (Window) NULL)
		Assoc_Xid_Put((XID)w, (XID) icon);
	}
	
        for (ix=0; ix < nchildren; ix++)
        {
	    w = children[ix];

            XGetWindowAttributes(dpy, w, &attrs);

            if (attrs.override_redirect == False)
            {
		if (Assoc_Xid_Get((XID) w) == (XID) NULL)
		    Wsys_Open(w, attrs);
		else
		{
		    Assoc_Xid_Remove((XID) w);
		    XUnmapWindow(dpy, w);
		}
            }
	}
        Draw_Set_Background();
        
        Interf_Client_Startup();
    }

    XFree(children);
    XFlush(dpy);
}
	



