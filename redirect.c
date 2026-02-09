
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
#include "uwinD.h"
#include "uwinXD.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "assoc.h"
#include "xio.h"
#include "tilecrsr.h"
#include "interf.h"

    
Userwin *Redirect_Get_Client_Uwinp( w )
    Window w;
{
    Userwin *uwinp;

    uwinp = (Userwin *) Assoc_Get( w );
    return ((uwinp != (Userwin *)NULL) && (w == Userwin_XClient(uwinp)))?
	uwinp : (Userwin *)NULL;
}
    

/* ------------------------------------------------------------ */

/*  FIND out if a DestroyNotify or ReparentNotify is in the queue.
 *  An UnmapNotify is a result of such Destroy or Reparent events.
 */
/*ARGSUSED*/
Bool IsDestroyResult(display, pev, args)
     Display  *display;
     XEvent  *pev;
     char  *args;
{
    Window  client;

    if (pev->type == DestroyNotify ||
	pev->type == ReparentNotify ||
	pev->type == MapNotify)
    {
	client = *( (unsigned int *) args );
	return  (Bool) ( client == ((XDestroyWindowEvent *) pev)->window );
    }
    else
    {
	return  False;
    }
}

/* ------------------------------------------------------------ */

static void Redirect_Configure( w, cev )
    Window  w;
    XConfigureRequestEvent  cev;
{
    XWindowChanges  xwc;

    xwc.x = cev.x;
    xwc.y = cev.y;
    xwc.width = cev.width;
    xwc.height = cev.height;
    xwc.border_width = cev.border_width;
    xwc.sibling = cev.above;
    xwc.stack_mode = cev.detail;
    
    XConfigureWindow(dpy, w, (unsigned int) cev.value_mask, &xwc);
}

/* ------------------------------------------------------------ */

static void Redirect_Client_Configure( uwinp, cev )
    Userwin *uwinp;
    XConfigureRequestEvent  cev;
{
    TWPoint  pt;
    Size  size;
    
    pt.x = cev.x;
    pt.y = cev.y;
    size.width = cev.width;
    size.height = cev.height;
    
    Interf_Client_Configure( uwinp, cev.value_mask,
                            pt, size, cev.detail );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Redirect_Handle_Create_Notify( ev )
    XEvent *ev;
{
    /* Do nothing -- create stuff gets handled on first request */
}

static void Redirect_Create_New_Window( w )
    Window  w;
{  
    XWindowAttributes attrs;
    
    (void)XGetWindowAttributes(dpy, w, &attrs);
    Wsys_Create(w, attrs);
}

/* ------------------------------------------------------------ */

static void Redirect_Handle_Map_Request( ev )
    XEvent *ev;
{
    Window w;
    Userwin  *uwinp;

    w = ev->xmaprequest.window;
    uwinp = (Userwin *) Assoc_Get(w);

    if (uwinp == (Userwin *)NULL)
    {
	Redirect_Create_New_Window( w );	
	uwinp = (Userwin *) Assoc_Get(w);
    }
    
    if (Userwin_XClient(uwinp) == w)
    {
	if (Userwin_XTransient_For(uwinp) == None )
	    Wsys_Map(uwinp);
	else
	    XMapRaised(dpy, w); /* always put new transient on top */
    }
}

/* ------------------------------------------------------------ */

static void Redirect_Handle_Unmap_Notify( ev )
    XEvent *ev;
{
    Window  w;
    Userwin  *uwinp;

    w = ev->xunmap.window;
    
    if ( (uwinp = Redirect_Get_Client_Uwinp( w )) != (Userwin *)NULL )
    {
	if (ev->xunmap.from_configure == False &&
	    Userwin_Is_Open(uwinp)  )
        {
            /* ignore UnmapNotifys resulting      */
            /* from Destroy or Reparent */
            XEvent  next_ev;

            XSync(dpy, 0);
            if ( XCheckIfEvent(dpy, &next_ev, IsDestroyResult,
                               (char *) &w) )
            {
                XPutBackEvent(dpy, &next_ev);
            }
            else
                Interf_Client_Close(uwinp);
        }
    }
    else
    {
    }
}

/* ------------------------------------------------------------ */

static void Redirect_Handle_Destroy_Notify( ev )
    XEvent *ev;
{
    Userwin  *uwinp;

    if ((uwinp = Redirect_Get_Client_Uwinp( ev->xdestroywindow.window ))
	!= (Userwin *)NULL )
    {
            Interf_Client_Destroy(uwinp);
    }
    else
    {
    }
}

/* ------------------------------------------------------------ */

static void Redirect_Handle_Reparent_Notify( ev )
    XEvent *ev;
{
    Window  w;
    Userwin  *uwinp;

    w = ev->xreparent.window;
    
    if ((uwinp = Redirect_Get_Client_Uwinp( w )) != (Userwin *)NULL)
	if (ev->xreparent.parent == root)	 /* if reparented to root */
        {	
	    int  x, y;
	    unsigned int  width, height;
	    
	    Drawwin_Client_Position(uwinp, &x, &y, &width, &height);

	    XReparentWindow(dpy, w, Userwin_XParentWin(uwinp), x, y);
	}
	else 
	{					 /* not to root and is Tiled */
	    if (ev->xreparent.parent != Userwin_XParentWin(uwinp))
		Interf_Client_Destroy(uwinp);
	}
} 

/* ------------------------------------------------------------ */

static void Redirect_Handle_Config_Request( ev )
    XEvent *ev;
{
    Window  w;
    Userwin  *uwinp, *above_uwinp;
    XConfigureRequestEvent  cev;
    

    cev = ev->xconfigurerequest;
    w = cev.window;
    
    if ((uwinp = Redirect_Get_Client_Uwinp( w )) != (Userwin *)NULL)
	if ( Userwin_XTransient_For(uwinp) == None ) 
	{
	    /* note that stacking requests are ignored for tiled windows */
	    Redirect_Client_Configure( uwinp, cev );
	}
	else /* handle a transient window -- fiddle stacking requests */ 
	{
	    if (cev.value_mask & CWStackMode)
	    {
		if (cev.above == None)
		{
		    /* wants to be on the bottom -- so          */
		    /* put it above the transient plane.        */
		    cev.above = transient_plane;
		}
		else
		{
		    /* only move relative to windows that we either don't   */
		    /* know, or that we know to be transient --- otherwise, */
		    /* just put it above the transient plane                */

		    above_uwinp = (Userwin *)Assoc_Get(cev.above);
		    if ((above_uwinp != (Userwin *)NULL) &&
			(Userwin_XTransient_For(above_uwinp) == None))
		    {
			cev.above = transient_plane;
		    }
		}    
		cev.detail = Above;
	    }
	    Redirect_Configure(w, cev);		
	}
    else /* it's never been mapped --- go ahead and configure it */
	Redirect_Configure(w, cev);
    
}

/* ------------------------------------------------------------ */

static void Redirect_Handle_Property_Notify( ev )
    XEvent *ev;
{
    Userwin  *uwinp;

    if ((uwinp = Redirect_Get_Client_Uwinp( ev->xproperty.window ))
	!= (Userwin *)NULL)
    {
	switch ( (int) ev->xproperty.atom )
	{
	case XA_WM_CLASS:
	    Property_Get_Window_Class(uwinp);
	    return;
	    
	case XA_WM_TRANSIENT_FOR:
	    /* do naught */
	    return;
	    
	case XA_WM_COMMAND:
	    Property_Get_Command_Line(uwinp);
	    return;
	    
	case XA_WM_CLIENT_MACHINE:
	    Property_Get_Hostname(uwinp);
	    return;
	    
	case XA_WM_NAME:
	    Property_Get_Title(uwinp);
	    return;
	    
	case XA_WM_ICON_NAME:
	    Property_Get_Icon_Title(uwinp);
	    return;
	    
	case XA_WM_NORMAL_HINTS:
	    Property_Get_Normal_Size_Hints(uwinp);
	    Property_Get_Geometry_Hints(uwinp);
	    return;
	    
	case XA_WM_HINTS:
	    Property_Get_Wm_Hints(uwinp);
	    return;
	    
	default:
	    return;
	}
    }
}

/* ------------------------------------------------------------ */
    
/*  Handle redirected window/output requests from X clients
 */
int Redirect_Handle_Event(ev)
    XEvent *ev;
{
    switch (ev->type)
    {
    case CreateNotify:
        Redirect_Handle_Create_Notify( ev );
	break;
	
    case MapRequest:
        Redirect_Handle_Map_Request( ev );
	break;
	
    case UnmapNotify:
        Redirect_Handle_Unmap_Notify( ev );
	break;

    case DestroyNotify:
        Redirect_Handle_Destroy_Notify( ev );
	break;
	
    case ReparentNotify:
        Redirect_Handle_Reparent_Notify( ev );
	break;

    case ConfigureRequest:
        Redirect_Handle_Config_Request( ev );
	break;

    case ConfigureNotify:
	break;

    case PropertyNotify:
        Redirect_Handle_Property_Notify( ev );
        break;

    case MapNotify:
	break;

    default:
	break;
    }

    return(0);
}


int dump_frame()
{
}
