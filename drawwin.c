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

/*  The Drawwin package manages Decorated client-windows
 */
#include "basetype.h"
#include "userglobD.h"
#include "uwinD.h"
#include "uwinXD.h"
#include "assoc.h"
#include "draw.h"
#include "control.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "xio.h"


extern void
    Drawwin_Config_Borders(), Drawwin_Draw_Borders(), Drawwin_Remove_Borders(),
    Drawwin_Config_Header(), Drawwin_Draw_Header(), Drawwin_Remove_Header(),
    Drawwin_Config_Gadgets(), Drawwin_Draw_Gadgets(), Drawwin_Remove_Gadgets();

extern GC
    fillGC, clearGC, xorGC, invert_body_GC;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Drawwin_Flash()
{
    Draw_Flash();
}


/* ------------------------------------------------------------ */

/*  Free all subwindows and parent of original Decorated client window
 */
void
Drawwin_Destroy(uwinp)
    Userwin *uwinp;
{

    Assoc_RemoveDecorations(uwinp);
    Control_Destroy(uwinp);
    XDestroySubwindows(dpy, Userwin_XParentWin(uwinp));
    XDestroyWindow(dpy, Userwin_XParentWin(uwinp));
}

/* ------------------------------------------------------------ */
/*ARGSUSED*/
void
Drawwin_Draw_Background( rect )
    TWRectangle rect;
{
    /* Sun-version function */
}    

/* ------------------------------------------------------------ */

bool
Drawwin_Redraw_All( rect )
    TWRectangle rect;
{

    Draw_Background_Rectangle(rect.left_x, rect.top_y,
			      rect.right_x, rect.bottom_y);

    return  TRUE;
}

/* ------------------------------------------------------------ */

/*  Create the Decorated Window.
 */
void
Drawwin_Create(uwinp)
    Userwin *uwinp;
{
    Draw_Create(uwinp);
}

/* ------------------------------------------------------------ */

/*  Start Drawwing.
 */
void
Drawwin_Start()
{
}

/* ------------------------------------------------------------ */

/*  Finish Drawwing.
 */
void
Drawwin_Finish()
{
    XFlush(dpy);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void
Drawwin_Display_Focus( uwinp )
    Userwin *uwinp;
{
    int  width, height;			/* parent window's dimensions */
    TWRectangle  rect;

    
    rect = Userwin_Get_Rectangle(uwinp);

    width = rect.right_x - rect.left_x + 1;
    height = rect.bottom_y - rect.top_y + 1;

    if ( UserGlobals_Get_Option(SHOW_FOCUS_IN_BORDERS) )
    {
        if (Userwin_Get_Window_Option( uwinp, USE_BORDERS ) )
	    Drawwin_Draw_Borders(uwinp, width, height);
    }

    if ( UserGlobals_Get_Option(SHOW_FOCUS_IN_HEADER) )
    {
        if (Userwin_Get_Window_Option( uwinp, USE_HEADER ) )
	    Drawwin_Draw_Header(uwinp, width, height);
    }
}

/* ------------------------------------------------------------ */

void
Drawwin_Retitle(uwinp)
    Userwin *uwinp;
{
    TWRectangle rect;
    

    rect = Userwin_Get_Rectangle(uwinp);

    Drawwin_Draw_Header(uwinp,
			rect.right_x - rect.left_x + 1,
			rect.bottom_y - rect.top_y + 1);
}

/* ------------------------------------------------------------ */

/*  re-configure the dimensions of the X windows composing the
 *  Decorated Client window (and draw the D.C. window decorations)
 */
void
Drawwin_Display_Wrapping(uwinp)
    Userwin	*uwinp;
{
    int  width, height;		/* parent window's dimensions */
    TWRectangle  tw_rect;


    tw_rect = Userwin_Get_Rectangle(uwinp);
    
    width = tw_rect.right_x - tw_rect.left_x + 1;
    height = tw_rect.bottom_y - tw_rect.top_y + 1;


    if (Userwin_Get_Window_Option( uwinp, USE_BORDERS ))
    {
	Drawwin_Draw_Borders(uwinp, width, height);
    }

    if (Userwin_Get_Window_Option( uwinp, USE_HEADER ))
    {
	Drawwin_Draw_Header(uwinp, width, height);

	if (Userwin_Get_Window_Option( uwinp, USE_GADGETS ))
	{
	    Drawwin_Draw_Gadgets(uwinp, width, height);
	}
    }
}


/*  Setup the dimensions of the Decorated Window.
 */
static void
Drawwin_Config_Wrapping(uwinp)
    Userwin  *uwinp;
{
    int  left_x, top_y;
    int  width, height,		/* parent window's dimensions */
         cwidth, cheight;	/* client window's dimensions */
    TWRectangle  tw_rect;


    tw_rect = Userwin_Get_Rectangle(uwinp);
    
    left_x = top_y = 0;
    cwidth = width = tw_rect.right_x - tw_rect.left_x + 1;
    cheight = height = tw_rect.bottom_y - tw_rect.top_y + 1;


    if (Userwin_Get_Window_Option( uwinp, USE_BORDERS ))
    {
	Drawwin_Config_Borders(uwinp, width, height);

	left_x += BORDER_SIZE_VAL;
	top_y += BORDER_SIZE_VAL;
	cwidth -= (2 * BORDER_SIZE_VAL);
	cheight -= (2 * BORDER_SIZE_VAL);
    }
    else
    {
	Drawwin_Remove_Borders(uwinp);
    }


    if (Userwin_Get_Window_Option( uwinp, USE_HEADER ))
    {
	Drawwin_Config_Header(uwinp, width, height);

	top_y += (uwinp->header_height + INNER_BORDER_LINEWIDTH_VAL);
	cheight -= (uwinp->header_height + INNER_BORDER_LINEWIDTH_VAL);


	if (Userwin_Get_Window_Option( uwinp, USE_GADGETS ))
	{
	    Drawwin_Config_Gadgets(uwinp, width, height);
	}
	else
	{
	    Drawwin_Remove_Gadgets(uwinp);
	}
    }
    else
    {
	Drawwin_Remove_Gadgets(uwinp);
	Drawwin_Remove_Header(uwinp);
    }


    Draw_ConfigWin(Userwin_XClient(uwinp),
		   left_x, top_y,
		   cwidth, cheight);

    Draw_ConfigWin(Userwin_XParentWin(uwinp),
		   tw_rect.left_x, tw_rect.top_y,
		   width, height);
}


/*  Get client position and size relative to its Parent.
 *  Useful when an annoying client tries to Re-parent itself
 *  back to the root window! 
 *
 *  Code borrowed from Drawwin_Config_Wrapping().
 */
int
Drawwin_Client_Position(uwinp, px, py, pwd, pht)
    Userwin  *uwinp;
    int  *px, *py;		/* these are all Returned */
    unsigned int  *pwd, *pht;
{
    TWRectangle  rect;


    rect = Userwin_Get_Rectangle(uwinp);
    
    *pwd = rect.right_x - rect.left_x + 1;
    *pht = rect.bottom_y - rect.top_y + 1;

    *px = *py = 0;

    if (Userwin_Get_Window_Option( uwinp, USE_BORDERS ))
    {
	*px += BORDER_SIZE_VAL;
	*py += BORDER_SIZE_VAL;
    }

    if (Userwin_Get_Window_Option( uwinp, USE_HEADER ))
    {
	*py += (uwinp->header_height + INNER_BORDER_LINEWIDTH_VAL);
    }

}    

    
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*  Unmap the Decorated Win if its size changed on the Move
 *  Operation.
 */
/*ARGSUSED*/
void Drawwin_Move_Close( uwinp, clear )
    Userwin *uwinp;
    bool clear;
{
    /* make it work with X -- always unmap */
    /*  --- removed for efficiency, and to make focus --- */
    /*      work correctly                                */
/*    XUnmapWindow(dpy, Userwin_XParentWin(uwinp)); */
}

/* ------------------------------------------------------------ */

void Drawwin_Listener_Move_Close( uwinp, clear )
    Userwin *uwinp;
    bool clear;
{
    int grab_result;
    unsigned int ev_mask = PointerMotionMask | ButtonPressMask | ButtonReleaseMask;
    
    grab_result = XGrabPointer(dpy, root, False, ev_mask,
			       GrabModeAsync, GrabModeAsync,
			       Userwin_XClient(uwinp), (Cursor) None,
			       CurrentTime);
    Drawwin_Move_Close( uwinp, clear );
}
    
/* ------------------------------------------------------------ */

/*  Redraw the Decorated Window on completion of the Move
 *  Operation.  If the DW's size is unchanged, reconfigure
 *  PARENT window only, and Notify the client of the Move.
 */
void Drawwin_Move_Open( uwinp )
    Userwin *uwinp;
{
    TWRectangle window_rect;
    int new_x, new_y;
    
    /* find the x-y position for the window */

    window_rect = Userwin_Get_Rectangle(uwinp);
    new_x = Get_LeftX(window_rect);
    new_y = Get_TopY(window_rect);

    if ( Userwin_Size_Changed(uwinp) == FALSE )
    {
	/* Just move it w/o resize */
	XMoveWindow(dpy, Userwin_XParentWin(uwinp), new_x, new_y);
    }
    else
    {
	Drawwin_Config_Wrapping(uwinp);
    }
    /* send WM_MOVED message --- needs to be added here */

    /*  ensure remap of Client when its Icon is Closed...
	mike says --- ??????
     */
    /* XMapWindow(dpy, Userwin_XParentWin(uwinp)); */
}

/* ------------------------------------------------------------ */

void Drawwin_Listener_Move_Open( uwinp )
    Userwin *uwinp;
{
    Drawwin_Move_Open( uwinp );
    XUngrabPointer(dpy, CurrentTime);
}

/* ------------------------------------------------------------ */

/*  Finish Close operation
 */
void Drawwin_Unmap(uwinp)
    Userwin *uwinp;
{
    XUnmapSubwindows(dpy, Userwin_XParentWin(uwinp));
    XUnmapWindow(dpy, Userwin_XParentWin(uwinp));
}

/* ------------------------------------------------------------ */

/*  Begin Close operation -
 *
 *  if Window will be covered by other Windows when it's un-mapped,
 *  then it's not "in the clear" (will cause flashing), so Lower it.
 */
/*ARGSUSED*/
void
Drawwin_Close(uwinp, clear)
    Userwin  *uwinp;
    bool  clear;
{
    XLowerWindow(dpy, Userwin_XParentWin(uwinp));
}

/* ------------------------------------------------------------ */

void Drawwin_Open( uwinp )
    Userwin *uwinp;
{
    Drawwin_Config_Wrapping(uwinp);
}

/* ------------------------------------------------------------ */

/* ARGSUSED */
void Drawwin_Draw( uwinp )
    Userwin *uwinp;
{
}

/* ------------------------------------------------------------ */
/*  This is the only place where X Expose events aren't there
 *  to make the x-client redraw its window.
 */
void Drawwin_Redraw( uwinp )
    Userwin *uwinp;
{
    TWRectangle  rect;


    rect = Userwin_Get_Rectangle(uwinp);

    Draw_Background_Rectangle(rect.left_x, rect.top_y,
			      rect.right_x, rect.bottom_y);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*  Invert Client Window's image, upon a Move Operation
 */
void Drawwin_Show_Moving( uwinp )
    Userwin *uwinp;
{
    Size window_size;

    window_size = Userwin_Get_Size(uwinp);
    XFillRectangle(dpy, (Drawable) Userwin_XParentWin(uwinp), invert_body_GC,
		   0, 0, window_size.width, window_size.height);
}

/* ------------------------------------------------------------ */

/*  Revert Client Window's image to "standard" color - Move
 *  Operation was completed or cancelled.
 */
void Drawwin_Unshow_Moving( uwinp )
    Userwin *uwinp;
{

    Drawwin_Show_Moving( uwinp );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static int old_x0, old_y0, old_x1, old_y1;

int
Drawwin_Draw_Box(x0, y0, x1, y1, draw_x)
    int  x0, y0, x1, y1;
    bool  draw_x;
{
    XPoint  points[8];
    XPoint  *pt = points;
    

    pt   -> x = x0;
    pt++ -> y = y0;
    
    pt   -> x = x1;		/* Box - top side */
    pt++ -> y = y0;

    pt   -> x = x1;		/* right side */
    pt++ -> y = y1;
    
    pt   -> x = x0;		/* bottom side */
    pt++ -> y = y1;
    
    pt   -> x = x0;		/* left side */
    pt++ -> y = y0;
    

    if (draw_x == TRUE)		/* should we draw cross-hatch (X)? */
    {
	pt   -> x = x1;
	pt++ -> y = y1;
    
	pt   -> x = x0;
	pt++ -> y = y1;
    
	pt   -> x = x1;
	pt++ -> y = y0;
    }

    XDrawLines(dpy, root, xorGC, points, pt - points, CoordModeOrigin);


    pt = points;		/* "double" the left, bottom and right sides */

    pt   -> x = x0 + 1;
    pt++ -> y = y0 + 1;
    
    pt   -> x = x1 - 1;		/* Box - top side */
    pt++ -> y = y0 + 1;

    pt   -> x = x1 - 1;		/* right side */
    pt++ -> y = y1 - 1;

    pt   -> x = x0 + 1;		/* bottom side */
    pt++ -> y = y1 - 1;

    pt   -> x = x0 + 1;		/* left side */
    pt++ -> y = y0 + 1;

    XDrawLines(dpy, root, xorGC, points, pt - points, CoordModeOrigin);
}    


void Drawwin_Good_Open_Box( start_pos, pos )
    TWPoint start_pos;
    TWPoint pos;
{

    old_x0 = start_pos.x;
    old_y0 = start_pos.y;
    old_x1 = pos.x;
    old_y1 = pos.y;

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_OPEN) );
}

/* ------------------------------------------------------------ */

void Drawwin_Bad_Open_Box( start_pos, pos )
    TWPoint start_pos;
    TWPoint pos;
{

    Drawwin_Good_Open_Box(start_pos, pos);
}

/* ------------------------------------------------------------ */

void Drawwin_Undo_Open_Box()
{

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_OPEN) );
}

/* ============================================================ */

static void Drawwin_Calc_Move_Rect( pos, siz )
    TWPoint pos;
    Size siz;
{
    int xdif, ydif;


    xdif = siz.width/2;
    ydif = siz.height/2;

    old_x0 = pos.x - xdif + 1;
    old_y0 = pos.y - ydif + 1;
    old_x1 = pos.x + xdif;
    old_y1 = pos.y + ydif;
}

/* ------------------------------------------------------------ */

/*ARGSUSED*/
void Drawwin_Good_Move_Box( uwinp, pos, siz )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
{

    Drawwin_Calc_Move_Rect(pos, siz);

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_MOVE) );
}

/* ------------------------------------------------------------ */

void Drawwin_Bad_Move_Box( uwinp, pos, siz )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
{

    Drawwin_Good_Move_Box(uwinp, pos, siz);
}

/* ------------------------------------------------------------ */

void Drawwin_Undo_Move_Box()
{

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_MOVE) );
}

/* ============================================================ */

static void Drawwin_Calc_Edge_Resize( uwinp, side, pos )
    Userwin *uwinp;
    Side side;
    TWPoint pos;
{

    old_x0 = Userwin_Get_Rectangle(uwinp).left_x;
    old_y0 = Userwin_Get_Rectangle(uwinp).top_y;
    old_x1 = Userwin_Get_Rectangle(uwinp).right_x;
    old_y1 = Userwin_Get_Rectangle(uwinp).bottom_y;

    switch(side)
    {
        case Left:
            old_x0 = pos.x;
            break;
        case Top:
            old_y0 = pos.y;
            break;
        case Right:
            old_x1 = pos.x;
            break;
        case Bottom:
            old_y1 = pos.y;
            break;
    }

}

/* ------------------------------------------------------------ */

/*ARGSUSED*/
void Drawwin_Edge_Resize( uwinp, side, pos )
    Userwin *uwinp;
    Side side;
    TWPoint pos;
{

    Drawwin_Calc_Edge_Resize( uwinp, side, pos );

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_RESIZE) );
}

/* ------------------------------------------------------------ */

void Drawwin_Undo_Edge_Resize()
{

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_RESIZE) );
}

/* ============================================================ */

static void Drawwin_Calc_Corner_Resize( uwinp, side, pos )
    Userwin *uwinp;
    Side side;
    TWPoint pos;
{

    old_x0 = Userwin_Get_Rectangle(uwinp).left_x;
    old_y0 = Userwin_Get_Rectangle(uwinp).top_y;
    old_x1 = Userwin_Get_Rectangle(uwinp).right_x;
    old_y1 = Userwin_Get_Rectangle(uwinp).bottom_y;

    switch(side)
    {
        case Top_Left:
            old_x0 = pos.x;
            old_y0 = pos.y;
            break;
        case Bottom_Left:
            old_x0 = pos.x;
            old_y1 = pos.y;
            break;
        case Top_Right:
            old_x1 = pos.x;
            old_y0 = pos.y;
            break;
        case Bottom_Right:
            old_x1 = pos.x;
            old_y1 = pos.y;
            break;
    }

}

/* ------------------------------------------------------------ */

/*ARGSUSED*/
void Drawwin_Corner_Resize( uwinp, side, pos )
    Userwin *uwinp;
    Side side;
    TWPoint pos;
{

    Drawwin_Calc_Corner_Resize(uwinp, side, pos);

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_RESIZE) );
}

/* ------------------------------------------------------------ */

void Drawwin_Undo_Corner_Resize()
{

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_RESIZE) );
}

void Drawwin_Insert(uwinp)
    Userwin *uwinp;
{
    XChangeSaveSet(dpy, Userwin_XClient(uwinp), SetModeInsert);
    XReparentWindow(dpy, Userwin_XClient(uwinp),
		    Userwin_XParentWin(uwinp), 0, 0);
}

void Drawwin_Withdraw(uwinp)
    Userwin *uwinp;
{
    XChangeSaveSet(dpy, Userwin_XClient(uwinp), SetModeDelete);
    XReparentWindow(dpy, Userwin_XClient(uwinp),
		    RootWindow(dpy, scrn), 0, 0);
}

void Drawwin_Prepare(uwinp)
    Userwin *uwinp;
{
}
