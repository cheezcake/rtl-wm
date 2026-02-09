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


/*  Property package.  Parses and directs action on properties
 *  attached to X client-windows.
 */

#include "uwinD.h"
#include "uwinXD.h"
#include "manage.h"
#include "profile.h"
#include "interf.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include "assoc.h"
#include "xio.h"

#define ARGSLEN  (long) 200	/* max command line length */
#define HOSTLEN  (long) 50	/* max header title length */
#define FAILED (Status) 0

/* ------------------------------------------------------------ */

/*  Get the main window with which the transient is
 *  associated.
 *  Returns the window, or None.
 */
int
Property_Get_Dialogue_Parent(uwinp)
    Userwin *uwinp;
{
    Window  parent;

    parent = None;
    if (XGetTransientForHint(dpy, Userwin_XClient(uwinp), &parent))
    {
	/* it's possible to set the transient for hint, with no   */
	/* parent (toolkit does this) -- so make the transient    */
	/* for be the root (since we use 0 to mean not transient  */
	Userwin_XTransient_For(uwinp) = (parent	== None)? root : parent;
    }
    else
	Userwin_XTransient_For(uwinp) = None;

}

/* ------------------------------------------------------------ */

/*  Get the class of the Client window.
 */
int
Property_Get_Window_Class(uwinp)
    Userwin  *uwinp;
{
/*    Status  status; */
    XClassHint  class_hint;


    class_hint.res_class = class_hint.res_name = "";  /* for workaround */
    
/*    status = */ (void)XGetClassHint(dpy, Userwin_XClient(uwinp), &class_hint);

    /*  Workaround for Xlib bug --- should be removed eventually  */
/*    if (status != FAILED)   -- this line will replace next line */
    if (!((class_hint.res_class == "") && (class_hint.res_name == "")))
    {
	Manage_Set_Class(uwinp, class_hint.res_class,
                                class_hint.res_name);

	if (class_hint.res_class != "")
	    XFree(class_hint.res_class);
	if (class_hint.res_name != "")
	    XFree(class_hint.res_name);

    }
}

/* ------------------------------------------------------------ */

/*  Get the Client window's title, to appear in its header.
 */
int
Property_Get_Title(uwinp)
    Userwin  *uwinp;
{
    Status  status;
    char  *s = (char *) NULL;


    status = XFetchName(dpy, Userwin_XClient(uwinp), &s);

    if (status != FAILED && s != (char *) NULL)
    {
	Manage_Set_Name(uwinp, s);
/*
	fprintf(stderr, "prop: got title <%s> for client <%d>\n",
		s, Userwin_XClient(uwinp));
*/
	XFree(s);
    }
}

/* ------------------------------------------------------------ */

/*  Get the command line which invoked the Client.
 */
int
Property_Get_Command_Line(uwinp)
    Userwin  *uwinp;
{
    Status  status;
    Atom  actual_type;
    int  actual_format;
    unsigned long  nitems;
    long  bytes_after;
    unsigned char  *prop;
    

    status = XGetWindowProperty(dpy, Userwin_XClient(uwinp),
				XA_WM_COMMAND,
				(long) 0,  ARGSLEN, False,
				XA_STRING,
				&actual_type, &actual_format,
				&nitems, &bytes_after, &prop);

    if (status == Success && actual_type != None)
    {
	char  command[ARGSLEN];
	int  len;
	
	
	switch (actual_format)
	{
	case 8:
	    strncpy(command, (char *) prop,
		    (len = (ARGSLEN <= nitems) ? ARGSLEN - 1 : nitems ));

	    command[len] = '\0';
	    Interf_Client_Set_Command(uwinp, command);

/*
	    fprintf(stderr, "prop: got command <%s> for client <%d>\n",
		    command, Userwin_XClient(uwinp));
*/
	    break;


	default:
	    break;
	}

	XFree ( (char *) prop );
    } 
}

/* ------------------------------------------------------------ */

/*  Get the host machine that a Client is running on.
 */
int
Property_Get_Hostname(uwinp)
    Userwin  *uwinp;
{
    Status  status;
    Atom  actual_type;
    int  actual_format;
    unsigned long  nitems;
    long  bytes_after;
    unsigned char  *prop;
    
/*XXXX
    if (UserGlobals_Get_Option(WM_CLIENT_MACHINE) == FALSE)
	return;
*/
    status = XGetWindowProperty(dpy, Userwin_XClient(uwinp),
				XA_WM_CLIENT_MACHINE,
				(long) 0,  HOSTLEN, False,
				XA_STRING,
				&actual_type, &actual_format,
				&nitems, &bytes_after, &prop);

    if (status == Success && actual_type != None)
    {
	char  hostname[HOSTLEN];
	int  len;
	
	
	switch (actual_format)
	{
	case 8:
	    strncpy(hostname, (char *) prop,
		    (len = (HOSTLEN <= nitems) ? HOSTLEN - 1 : nitems ));

	    hostname[len] = '\0';
	    Manage_Set_Hostname(uwinp, hostname);

/*
	    fprintf(stderr, "prop: got hostname <%s> for client <%d>\n",
		    hostname, Userwin_XClient(uwinp));
*/
	    break;


	default:
	    break;
	}

	XFree ( (char *) prop );
    } 
}

/* ------------------------------------------------------------ */

/*  Set the icon title for a Client.
 */
int
Property_Get_Icon_Title(uwinp)
    Userwin  *uwinp;
{
    Status  status;
    char  *s = (char *) NULL;


    status = XGetIconName(dpy, Userwin_XClient(uwinp), &s);

    if (status != FAILED && s != (char *) NULL)
    {
	Manage_Set_Icon_Name(uwinp, s);
/*
	fprintf(stderr, "prop: got Icon title <%s> for client <%d>\n",
		s, Userwin_XClient(uwinp));
*/
	XFree(s);
    }
}

/* ------------------------------------------------------------ */

/*  Get size hints for a Client Tiled window in its Normal state.
 */
int
Property_Get_Normal_Size_Hints(uwinp)
    Userwin  *uwinp;
{
    XSizeHints  hints;       /* RETURNed by GetNormalHints */
    Status  status;
    

    status = XGetNormalHints(dpy, Userwin_XClient(uwinp), &hints);

    if (status != FAILED)
    {
	Size  min_size, max_size, incr_size, base_size;

	min_size.width = hints.min_width;
	min_size.height = hints.min_height;
	max_size.width = hints.max_width;
	max_size.height = hints.max_height;
	incr_size.width = hints.width_inc;
	incr_size.height = hints.height_inc;
        base_size = min_size;
	
	Interf_Client_Set_Normal_Hints(uwinp,
				       hints.flags,
				       min_size,
				       max_size,
				       incr_size,
				       hints.min_aspect,
				       hints.max_aspect,
                                       base_size);
    }
}

int
Property_Get_Geometry_Hints(uwinp)
    Userwin *uwinp;
{
    XSizeHints  hints;       /* RETURNed by GetNormalHints */
    Status  status;
    

    status = XGetNormalHints(dpy, Userwin_XClient(uwinp), &hints);

    if (status != FAILED)
    {
	TWPoint pt;
	Size  size;

	pt.x = hints.x;
	pt.y = hints.y;
	size.width = hints.width;
	size.height = hints.height;
	
	Interf_Client_Set_Geometry_Hints(uwinp,
					 hints.flags,
					 pt, size);
    }
}

/* ------------------------------------------------------------ */

Size Property_Pixmap_Size( pix )
    Pixmap pix;
{
    Window w;
    int x, y;
    unsigned int width, height;
    unsigned int border_width;
    unsigned int depth;
    Size siz;

    XGetGeometry( dpy, pix, &w, &x, &y,
                  &width, &height,
                  &border_width, &depth );

    siz.width = width;
    siz.height = height;
    
    return siz;
}

/* ------------------------------------------------------------ */

/*  Get the Window Manager hints to Rtl for a Client.
 */
int
Property_Get_Wm_Hints(uwinp)
    Userwin  *uwinp;
{
    XWMHints  *ph;


    if ( (ph = XGetWMHints(dpy, Userwin_XClient(uwinp))) != (XWMHints *) NULL )
    {
	if (ph->flags & InputHint)
	{
	    if (ph->input == True)
		Userwin_Enable_Input( uwinp );
	    else
		Userwin_Disable_Input( uwinp );
	}

	if (ph->flags & StateHint)
	{
	    Interf_Client_Set_State(uwinp, ph->initial_state);
	}

	if (ph->flags & IconPixmapHint)
	{
	    if (! Profile_Supplies_Pixmap( uwinp ) )
            {
		uwinp->iconpix = ph->icon_pixmap;
                Interf_Client_Set_Icon_Size( uwinp,
                    Property_Pixmap_Size( ph->icon_pixmap ) ); 
            }
	}

	if (ph->flags & IconWindowHint)
	{
	    if(Userwin_XClient_Icon(uwinp) == (Window) NULL)
	    {
		Assoc_Xid_Put((XID)Userwin_XClient(uwinp),
			  (XID) ph->icon_window);
	    }
	    else
	    {
		Assoc_Xid_Remove((XID)Userwin_XClient_Icon(uwinp));
		Assoc_Xid_Put((XID)Userwin_XClient(uwinp),
			  (XID) ph->icon_window);
	    }
	    Userwin_XClient_Icon(uwinp) = ph->icon_window;
	}
	
	if (ph->flags & IconPositionHint)
	{
            TWPoint pt;;
            
            pt.x = ph->icon_x;
            pt.y = ph->icon_y;
            Interf_Client_Set_Icon_Position( uwinp, pt ); 
	}

	if (ph->flags & IconMaskHint)
        {
/*            uwinp->iconmask = ph->icon_mask; */
        }
        
        if (ph->flags & WindowGroupHint) 
        {
            Userwin *group;
            group = (Userwin *)Assoc_Get( ph->window_group );
            Interf_Client_Set_Group( uwinp, group );
        }

	XFree( (char *) ph );
    }
}

/* ------------------------------------------------------------ */

#define WM_STATE "XA_WM_STATE"
#define WM_STATE_FORMAT 32
#define WM_STATE_LEN (long) 2       /* window state length */

typedef struct 
    {
        int state;
	Window icon;
    } Xwmstate;
    
static Atom wm_state = (Atom) 0;

/* ------------------------------------------------------------ */
    
int
Property_Get_Wm_State(uwinp)
    Userwin *uwinp;
{
    Status  status;
    Atom  actual_type;
    int  actual_format;
    unsigned long  nitems;
    unsigned long  bytes_after;
    Xwmstate *wms;

    if (wm_state == (Atom) 0)
	wm_state = XInternAtom(dpy, WM_STATE, False);

    status = XGetWindowProperty(dpy, Userwin_XClient(uwinp),
				wm_state,
				(long) 0, (long) WM_STATE_LEN,
				False,
				wm_state,
				&actual_type, &actual_format,
				&nitems, &bytes_after,
				(unsigned char **) &wms);

    if (status == Success && actual_type != None)
    {
	Userwin_Wm_State(uwinp) = wms->state;
	XFree((char *) wms);
    }
    else
	Userwin_Wm_State(uwinp) = NeverState;
}

/* ------------------------------------------------------------ */

void 
Property_Set_Wm_State(uwinp, state)
    Userwin *uwinp;
    int state;
{
    Xwmstate wms;

    wms.state = state;
    wms.icon = Userwin_XIcon(uwinp);

    if (wm_state == (Atom) 0)
	wm_state = XInternAtom(dpy, WM_STATE, False);

    XChangeProperty(dpy, Userwin_XClient(uwinp),
		    wm_state, wm_state, WM_STATE_FORMAT,
		    PropModeReplace, 
		    (unsigned char *) &wms, WM_STATE_LEN);

    Userwin_Wm_State(uwinp) = state;
}


