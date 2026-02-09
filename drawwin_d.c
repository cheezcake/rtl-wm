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

/*  The Drawwin package manages Decorated client windows
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "basetype.h"
#include "userglobD.h"
#include "uwinD.h"
#include "uwinXD.h"
#include "draw.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "xio.h"

#define HEADER_FONT	"6x12"


GC  fillGC, clearGC, xorGC, invert_body_GC;
XFontStruct  *fontp;


static void Drawwin_Config_Corners(Userwin *uwinp, int width, int height);
static int Drawwin_Draw_Corner_Lines(Window parent, GC gc, int width, int height);
static int Drawwin_Draw_Corners(Window parent, GC gc, int width, int height);

/*-----------------------------------------------------------------*/

/*  Font and drawing function set-up
 *  ?? Could get foreground/background colors from interface/options
 */
void
Drawwin_Init()
{
    XGCValues  gcv;
    unsigned long  vmask;
    
    
    if ( (fontp = XLoadQueryFont(dpy, HEADER_FONT)) == NULL )
    {
	fprintf(stderr, "XLoadFont failed\n");
	exit(1);
    }


    vmask = GCForeground | GCFont;
    gcv.foreground = BlackPixel(dpy, scrn);
    gcv.font = fontp->fid;
    fillGC = XCreateGC(dpy, root, vmask, &gcv);

    gcv.foreground = WhitePixel(dpy, scrn);
    clearGC = XCreateGC(dpy, root, vmask, &gcv);


    gcv.foreground = 0xfd;
    gcv.line_width = 0;
    gcv.function = GXxor;
    gcv.subwindow_mode = IncludeInferiors;
    xorGC = XCreateGC(dpy, root,
		      GCForeground | GCLineWidth | 
		      GCFunction | GCSubwindowMode,
		      &gcv);

    gcv.function = GXxor;
    gcv.foreground = BlackPixel(dpy, scrn) ^ WhitePixel(dpy,scrn);
    invert_body_GC = XCreateGC(dpy, root,
			       GCForeground | GCFunction | GCSubwindowMode, &gcv);
}

/*-----------------------------------------------------------------*/

void
Drawwin_Config_Borders(uwinp, width, height)
    Userwin  *uwinp;
    int  width, height;		/* dimensions of parent window */
{
    
    Draw_ConfigWin(Userwin_XTopBorder(uwinp),
		      0,
		      0,
		      width,
		      BORDER_SIZE_VAL);
    
    Draw_ConfigWin(Userwin_XLeftBorder(uwinp),
		      0,
		      BORDER_SIZE_VAL,
		      BORDER_SIZE_VAL,
		      height - (2 * BORDER_SIZE_VAL));
    
    
    Draw_ConfigWin(Userwin_XRightBorder(uwinp),
		      width - BORDER_SIZE_VAL,
		      BORDER_SIZE_VAL,
		      BORDER_SIZE_VAL,
		      height - (2 * BORDER_SIZE_VAL));
    
    
    Draw_ConfigWin(Userwin_XBottomBorder(uwinp),
		      0,
		      height - BORDER_SIZE_VAL,
		      width,
		      BORDER_SIZE_VAL);
    
    
    if (UserGlobals_Get_Option(USE_CORNER_BORDERS) == TRUE)
    {
	Drawwin_Config_Corners(uwinp, width, height);
    }
}

    
/*  Draw the representation of the Border windows in the
 *  parent window
 */
void
Drawwin_Draw_Borders(uwinp, width, height)
    Userwin  *uwinp;
    int  width, height;			/* dimensions of parent window */
{
    XRectangle  rects[4];
    XRectangle  *pr = rects;
    Window  parent = Userwin_XParentWin(uwinp);
    

    /*  Draw 4 FILLED rects to make the borders
     *  (top, left, right and bottom borders)
     */
    pr -> x = 0;
    pr -> y = 0;
    pr -> width  = width;
    pr++ -> height = BORDER_SIZE_VAL;
    
    pr -> x = 0;
    pr -> y = BORDER_SIZE_VAL;
    pr -> width  = BORDER_SIZE_VAL;
    pr++ -> height = height;

    pr -> x = width - BORDER_SIZE_VAL;
    pr -> y = 0;
    pr -> width  = BORDER_SIZE_VAL;
    pr++ -> height = height;

    pr -> x = 0;
    pr -> y = height - BORDER_SIZE_VAL;
    pr -> width  = width;
    pr++ -> height = BORDER_SIZE_VAL;

    XFillRectangles(dpy, parent, fillGC, rects, pr - rects);

    
    if ((UserGlobals_Get_Option(SHOW_FOCUS_IN_BORDERS) && uwinp->focus) ||
	(UserGlobals_Get_Option(SHOW_LISTENER_IN_BORDERS) && uwinp->listener))
    {
	if (UserGlobals_Get_Option(DISTINGUISH_CORNER_BORDERS) == TRUE &&
	    UserGlobals_Get_Option(USE_CORNER_BORDERS) == TRUE)
	{
	    if ( UserGlobals_Get_Option(DISTNGSH_CORNER_BORDERS_BY_INV))
	    {
		Drawwin_Draw_Corners(parent, clearGC, width, height);
	    }
	    else
	    {
		Drawwin_Draw_Corner_Lines(parent, clearGC, width, height);
	    }
	}
    }
    else  /* show border lines by CLEARing rects, offset by linewidths... */
    {
	pr = rects;

	pr -> x = OUTER_BORDER_LINEWIDTH_VAL;
	pr -> y = OUTER_BORDER_LINEWIDTH_VAL;
	pr -> width  = width - (2 * OUTER_BORDER_LINEWIDTH_VAL);
	pr++ -> height = BORDER_SIZE_VAL -
	    (OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
	
	pr -> x = OUTER_BORDER_LINEWIDTH_VAL;
	pr -> y = OUTER_BORDER_LINEWIDTH_VAL;
	pr -> width  = BORDER_SIZE_VAL -
	    (OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
	pr++ -> height = height - (2 * OUTER_BORDER_LINEWIDTH_VAL);
	
	pr -> x = width - BORDER_SIZE_VAL + INNER_BORDER_LINEWIDTH_VAL;
	pr -> y = OUTER_BORDER_LINEWIDTH_VAL;
	pr -> width  = BORDER_SIZE_VAL -
	    (OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
	pr++ -> height = height - (2 * OUTER_BORDER_LINEWIDTH_VAL);
	
	pr -> x = OUTER_BORDER_LINEWIDTH_VAL;
	pr -> y = height - BORDER_SIZE_VAL + INNER_BORDER_LINEWIDTH_VAL;
	pr -> width  = width - (2 * OUTER_BORDER_LINEWIDTH_VAL);
	pr++ -> height = BORDER_SIZE_VAL - 
	    (OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);

	XFillRectangles(dpy, parent, clearGC, rects, pr - rects);
	

	if (UserGlobals_Get_Option(DISTINGUISH_CORNER_BORDERS) == TRUE &&
	    UserGlobals_Get_Option(USE_CORNER_BORDERS) == TRUE)
	{
	    if ( UserGlobals_Get_Option(DISTNGSH_CORNER_BORDERS_BY_INV))
	    {
		Drawwin_Draw_Corners(parent, fillGC, width, height);
	    }
	    else  /* just draw lines to highlight the corner borders */
	    {
		Drawwin_Draw_Corner_Lines(parent, fillGC, width, height);
	    }
	}
    }
}


/*  Remove (but don't destroy the resources associated with)
 *  all border windows
 */
void
Drawwin_Remove_Borders(uwinp)
    Userwin  *uwinp;
{
    XUnmapWindow(dpy, Userwin_XTopBorder(uwinp));
    XUnmapWindow(dpy, Userwin_XLeftBorder(uwinp));
    XUnmapWindow(dpy, Userwin_XRightBorder(uwinp));
    XUnmapWindow(dpy, Userwin_XBottomBorder(uwinp));
}

/*-----------------------------------------------------------------*/

/*  Create the corner border windows, as part of the
 *  decorated-client window
 */
static void
Drawwin_Config_Corners(uwinp, width, height)
    Userwin  *uwinp;
    int  width, height;
{
    
    Draw_ConfigWin(Userwin_XTopLeftCorner(uwinp),
		   0,
		   0,
		   2 * BORDER_SIZE_VAL,
		   2 * BORDER_SIZE_VAL);
    
    Draw_ConfigWin(Userwin_XTopRightCorner(uwinp),
		   width - (2 * BORDER_SIZE_VAL),
		   0,
		   2 * BORDER_SIZE_VAL,
		   2 * BORDER_SIZE_VAL);
    
    Draw_ConfigWin(Userwin_XBottomLeftCorner(uwinp),
		   0,
		   height - (2 * BORDER_SIZE_VAL),
		   2 * BORDER_SIZE_VAL,
		   2 * BORDER_SIZE_VAL);
    
    Draw_ConfigWin(Userwin_XBottomRightCorner(uwinp),
		   width - (2 * BORDER_SIZE_VAL),
		   height - (2 * BORDER_SIZE_VAL),
		   2 * BORDER_SIZE_VAL,
		   2 * BORDER_SIZE_VAL);
}


static int
Drawwin_Draw_Corners(parent, gc, width, height)
    Window  parent;
    GC  gc;
    int  width, height;
{    
    XRectangle  rects[8];
    XRectangle  *pr = rects;

    
    pr -> x = OUTER_BORDER_LINEWIDTH_VAL;	 /* top left */
    pr -> y = OUTER_BORDER_LINEWIDTH_VAL;
    pr -> width  = BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    pr++ -> height = 2 * BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);

    pr -> x = OUTER_BORDER_LINEWIDTH_VAL;
    pr -> y = OUTER_BORDER_LINEWIDTH_VAL;
    pr -> width = 2 * BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    pr++ -> height = BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    
						 /* top right */
    pr -> x = width - BORDER_SIZE_VAL + INNER_BORDER_LINEWIDTH_VAL;
    pr -> y = OUTER_BORDER_LINEWIDTH_VAL;
    pr -> width = BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    pr++ -> height = 2 * BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    
    pr -> x = width - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    pr -> y = OUTER_BORDER_LINEWIDTH_VAL;
    pr -> width = 2 * BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    pr++ -> height = BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    
    
    pr -> x = OUTER_BORDER_LINEWIDTH_VAL;	 /* bottom left */
    pr -> y = height - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    pr -> width  = BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    pr++ -> height = (2 * BORDER_SIZE_VAL) -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    
    pr -> x = OUTER_BORDER_LINEWIDTH_VAL;
    pr -> y = height - BORDER_SIZE_VAL + INNER_BORDER_LINEWIDTH_VAL;
    pr -> width = 2 * BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    pr++ -> height = BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    
						 /* bottom right */
    pr -> x = width - BORDER_SIZE_VAL + INNER_BORDER_LINEWIDTH_VAL;
    pr -> y = height - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    pr -> width = BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    pr++ -> height = (2 * BORDER_SIZE_VAL) -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    
    pr -> x = width - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    pr -> y = height - BORDER_SIZE_VAL + INNER_BORDER_LINEWIDTH_VAL;
    pr -> width = 2 * BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
    pr++ -> height = BORDER_SIZE_VAL -
	(OUTER_BORDER_LINEWIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);

    
    XFillRectangles(dpy, parent, gc, rects, pr - rects);
}


/*  Draw distinguishing lines for Corner Borders.
 */
static int
Drawwin_Draw_Corner_Lines(parent, gc, width, height)
    Window  parent;
    GC  gc;
    int  width, height;
{
    XGCValues  gcv;
    unsigned long  vmask;
    XSegment  segments[8];
    XSegment  *psg = segments;
    

    vmask = GCLineWidth;
    gcv.line_width = INNER_BORDER_LINEWIDTH_VAL;

    XChangeGC(dpy, gc, vmask, &gcv);

    
						 /* top left corner */
    psg -> x1 = 0;
    psg -> y1 = 2 * BORDER_SIZE_VAL - INNER_BORDER_LINEWIDTH_VAL;
    psg -> x2 = BORDER_SIZE_VAL - 1;
    psg++ -> y2 = 2 * BORDER_SIZE_VAL - INNER_BORDER_LINEWIDTH_VAL;
    
    psg -> x1 = 2 * BORDER_SIZE_VAL - INNER_BORDER_LINEWIDTH_VAL;
    psg -> y1 = 0;
    psg -> x2 = 2 * BORDER_SIZE_VAL - INNER_BORDER_LINEWIDTH_VAL;
    psg++ -> y2 = BORDER_SIZE_VAL - 1;
    
    
    psg -> x1 = width - BORDER_SIZE_VAL;	 /* top right corner */
    psg -> y1 = 2 * BORDER_SIZE_VAL - INNER_BORDER_LINEWIDTH_VAL;
    psg -> x2 = width - 1;
    psg++ -> y2 = 2 * BORDER_SIZE_VAL - INNER_BORDER_LINEWIDTH_VAL;
    
    psg -> x1 = width - 2 * BORDER_SIZE_VAL + INNER_BORDER_LINEWIDTH_VAL;
    psg -> y1 = 0;
    psg -> x2 = width - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    psg++ -> y2 = BORDER_SIZE_VAL - 1;
    
    
    psg -> x1 = 0;			       /* bottom left corner */
    psg -> y1 = height - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    psg -> x2 = BORDER_SIZE_VAL - 1;
    psg++ -> y2 = height - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    
    psg -> x1 = (2 * BORDER_SIZE_VAL) - INNER_BORDER_LINEWIDTH_VAL;
    psg -> y1 = height - BORDER_SIZE_VAL;
    psg -> x2 = (2 * BORDER_SIZE_VAL) - INNER_BORDER_LINEWIDTH_VAL;
    psg++ -> y2 = height - 1;
    
    
    psg -> x1 = width - BORDER_SIZE_VAL;	 /* bottom right corner */
    psg -> y1 = height - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    psg -> x2 = width - 1;
    psg++ -> y2 = height - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    
    psg -> x1 = width - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    psg -> y1 = height - BORDER_SIZE_VAL;
    psg -> x2 = width - (2 * BORDER_SIZE_VAL) + INNER_BORDER_LINEWIDTH_VAL;
    psg++ -> y2 = height - 1;
    
    
    XDrawSegments(dpy, parent, gc, segments, psg - segments);
}


/*-----------------------------------------------------------------*/

/*  Create the header window, as part of the
 *  decorated-client window
 */
void
Drawwin_Config_Header(uwinp, width, height)
    Userwin  *uwinp;
    int  width, height;
{
    int  left_x, top_y;


    left_x = 0;
    top_y = 0;
    height = uwinp->header_height + INNER_BORDER_LINEWIDTH_VAL;


    if (Userwin_Get_Window_Option( uwinp, USE_BORDERS ))
    {
	left_x += BORDER_SIZE_VAL;;
	top_y += BORDER_SIZE_VAL;
	width -= (2 * BORDER_SIZE_VAL);
    }

    Draw_ConfigWin(Userwin_XHeader(uwinp),
		   left_x, top_y,
		   width, height);
}


/*  Draw the header and its contents (string)
 */
void
Drawwin_Draw_Header(uwinp, width, height)
    Userwin  *uwinp;
    int  width, height;
{
    int  left_x, top_y;
    Window  parent = Userwin_XParentWin(uwinp);
    GC  titleGC;


    left_x = 0;
    top_y = 0;
    height = uwinp->header_height + INNER_BORDER_LINEWIDTH_VAL;

    if (Userwin_Get_Window_Option(uwinp, USE_BORDERS))
    {
	left_x += BORDER_SIZE_VAL;
	top_y += BORDER_SIZE_VAL;
	width -= (2 * BORDER_SIZE_VAL);
    }

    if (Userwin_Get_Window_Option( uwinp, USE_GADGETS ))
    {
        left_x += (GADGET_WIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
	width -= (GADGET_WIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);

        if (Userwin_Get_Window_Option(uwinp, USE_MOVE_GADGET))
	{
	    width -= (GADGET_WIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL);
	}
    }


    if ((UserGlobals_Get_Option(SHOW_FOCUS_IN_HEADER) && uwinp->focus) ||
	(UserGlobals_Get_Option(SHOW_LISTENER_IN_HEADER) && uwinp->listener))
    {
	XFillRectangle(dpy, parent, fillGC, left_x, top_y,
		       (unsigned) width, (unsigned) height);

	titleGC = clearGC;
    }
    else
    {
	/*  create the Inner Border line in the header...
	 */
	XFillRectangle(dpy, parent, clearGC, left_x, top_y,
		       (unsigned) width,
		       (unsigned) height - INNER_BORDER_LINEWIDTH_VAL);

	XFillRectangle(dpy, parent, fillGC,
		       left_x,
		       top_y + height - INNER_BORDER_LINEWIDTH_VAL,
		       (unsigned) width,
		       (unsigned) INNER_BORDER_LINEWIDTH_VAL);

	titleGC = fillGC;
    }


#define TITLE_NCHARS  100

    if ( (uwinp->title != (char *) NULL) &&
         Userwin_Get_Window_Option( uwinp, INCLUDE_TITLE_IN_HEADER ) )
    {
	char  s[TITLE_NCHARS];
	int  nc;


	nc = Draw_Num_Drawables(uwinp->title,
				fontp,
				width - fontp->max_bounds.width,
				TITLE_NCHARS);

        strncpy(s, uwinp->title, nc);
        s[nc] = '\0';


	/*  Position title string at 1 char position from left of header,
	 *  and "font-height" position from top of header.
	 *  This positioning affects the above calcs...
	 */
	XDrawString(dpy, parent, titleGC,
		    left_x + fontp->max_bounds.width,
		    top_y + fontp->max_bounds.ascent,
		    s, nc);
    }

}


/*  Remove the Header window from the decorated client window
 */
void
Drawwin_Remove_Header(uwinp)
    Userwin *uwinp;
{
    XUnmapWindow(dpy, Userwin_XHeader(uwinp));
}

/*-----------------------------------------------------------------*/

/*  Create the Gadget subwindows
 */
/*ARGSUSED*/
void
Drawwin_Config_Gadgets(uwinp, width, height)
    Userwin  *uwinp;
    int  width, height;
{
    int  left_x, top_y;
    int  g_width, g_height;
    

    g_width = GADGET_WIDTH_VAL + INNER_BORDER_LINEWIDTH_VAL;
    g_height = uwinp->header_height + INNER_BORDER_LINEWIDTH_VAL;
    
    if (Userwin_Get_Window_Option( uwinp, USE_BORDERS ))  /* zoom gadget */
    {
	left_x = top_y = BORDER_SIZE_VAL;
    }
    else
    {
	left_x = top_y = 0;
    }

    Draw_ConfigWin(Userwin_XZoomGadget(uwinp),
		   left_x, top_y,
		   g_width, g_height);

    
    if (Userwin_Get_Window_Option(uwinp, USE_MOVE_GADGET)) /* move gadget */
    {
	left_x = (Userwin_Get_Window_Option( uwinp, USE_BORDERS )) ?
	    width - BORDER_SIZE_VAL - g_width + 1 :
		width - g_width;

	Draw_ConfigWin(Userwin_XMoveGadget(uwinp),
		       left_x, top_y,
		       g_width, g_height);
    }
    else
    {
	XUnmapWindow(dpy, Userwin_XMoveGadget(uwinp));
    }
}


/*  Draw the representation of the desired Gadgets
 */
/*ARGSUSED*/
void
Drawwin_Draw_Gadgets(uwinp, width, height)
    Userwin  *uwinp;
    int  width, height;
{
    unsigned int  border_width, inner_border_width;
    Window  parent = Userwin_XParentWin(uwinp);



    border_width = (Userwin_Get_Window_Option( uwinp, USE_BORDERS )) ?
	BORDER_SIZE_VAL : 0;

    inner_border_width = (Userwin_Get_Window_Option( uwinp, USE_BORDERS )) ?
	INNER_BORDER_LINEWIDTH_VAL : 0;


    XFillRectangle(dpy, parent, fillGC,		       /* Zoom gadget */
		   0 + border_width,
		   0 + border_width,
		   (unsigned) (GADGET_WIDTH_VAL + inner_border_width),
		   (unsigned) (uwinp->header_height + inner_border_width));

    XFillRectangle(dpy, parent, clearGC,
		   0 + border_width,
		   0 + border_width,
		   (unsigned) (GADGET_WIDTH_VAL),
		   (unsigned) (uwinp->header_height));

    if (uwinp->zoomed)
    {
	XDrawRectangle(dpy, parent, fillGC,
		       0 + border_width + 2,
		       0 + border_width + 2,
		       (unsigned) (GADGET_WIDTH_VAL - 5),
		       (unsigned) (uwinp->header_height - 5));
    }
    else
    {
	XFillRectangle(dpy, parent, fillGC,
		       0 + border_width + (GADGET_WIDTH_VAL / 2) - 2,
		       0 + border_width + (uwinp->header_height / 2) - 2,
		       (unsigned) 4,
		       (unsigned) 4);
    }

    if (Userwin_Get_Window_Option(uwinp, LISTENER_TIED_TO_ZOOM) == TRUE)
    {
	XDrawLine(dpy, parent, fillGC,
		  0 + border_width,
		  0 + border_width + (uwinp->header_height / 2),
		  0 + border_width + GADGET_WIDTH_VAL - 1,
		  0 + border_width + (uwinp->header_height / 2));
    }


    if (Userwin_Get_Window_Option(uwinp, USE_MOVE_GADGET) == TRUE)
    {

	/*  Clear Move Gadget's area.
	 */
	XFillRectangle(dpy, parent, clearGC,
		       width - GADGET_WIDTH_VAL - border_width - inner_border_width,
		       0 + border_width,
		       (unsigned) (GADGET_WIDTH_VAL + inner_border_width),
		       (unsigned) (uwinp->header_height + inner_border_width));

	/*  Draw left border of gadget.
	 */
	XFillRectangle(dpy, parent, fillGC,
		       width - GADGET_WIDTH_VAL - border_width - inner_border_width,
		       0 + border_width,
		       inner_border_width,
		       (unsigned) (uwinp->header_height + inner_border_width));

	/*  Draw bottom border of gadget/header.
	 */
	XFillRectangle(dpy, parent, fillGC,
		       width - GADGET_WIDTH_VAL - border_width - inner_border_width,
		       0 + border_width + uwinp->header_height,
		       (unsigned) GADGET_WIDTH_VAL,
		       inner_border_width);
    }
}


/*  Remove the Gadget windows from the decorated window
 */
void
Drawwin_Remove_Gadgets(uwinp)
    Userwin *uwinp;
{
    XUnmapWindow(dpy, Userwin_XZoomGadget(uwinp));

    XUnmapWindow(dpy, Userwin_XMoveGadget(uwinp));
}
