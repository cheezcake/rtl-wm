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
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include "xio.h"
#include "twin.h"
#include "uwinD.h"
#include "uwinXD.h"

/*  Cleanup and exit the Rtl Manager.  Called from menus or signal.
 */

void Pause_RTL()
{
    Userwin *uwinp;
    Tilwinp winp;
    XWindowChanges wc;
    
    Draw_Reset_Background();

    XDefineCursor(dpy, root, (XID) XC_X_cursor);
    Draw_Set_Mouse_Control(-2, 0);		   /* reset mouse vals */

    XSetInputFocus(dpy, PointerRoot, RevertToPointerRoot, CurrentTime);
    
    Tilwin_Gen_Open_Windows();
    while ((winp = Tilwin_Next_Window()) != WIN_NULL)
    {
	uwinp = Userwin_Get(winp);

	if (uwinp->current_type == rtl)
	    continue;
	
	if (Userwin_Border_Width(uwinp) > 0)
	{
	    wc.border_width = Userwin_Border_Width(uwinp);
	    XConfigureWindow(dpy, Userwin_XClient(uwinp),
			     CWBorderWidth, &wc);
	}
    }
    
    Tilwin_Gen_Closed_Windows();
    while ((winp = Tilwin_Next_Window()) != WIN_NULL)
    {
	uwinp = Userwin_Get(winp);

	if (uwinp->current_type == rtl)
	    continue;

	if (Userwin_Border_Width(uwinp) > 0)
	{
	    wc.border_width = Userwin_Border_Width(uwinp);
	    XConfigureWindow(dpy, Userwin_XClient(uwinp),
			     CWBorderWidth, &wc);
	}
    }
    
    XCloseDisplay(dpy);

    fprintf(stderr, "\nHope you enjoyed using RTL Tiled Windows under X!\n");
    exit(0);
}


/*ARGSUSED*/
void
Exit(sig, code, scp)
    int sig, code;
    struct sigcontext *scp;
{

    Pause_RTL();
}    
