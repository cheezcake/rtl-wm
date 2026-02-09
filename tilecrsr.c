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

#include "std_defs.h"
#include "tilecrsrP.h"
#include "control.h"
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include "xio.h"
/*
#define XDefineCursor(a, b, c)
#define XLoadQueryFont(a, b)  1024
#define XCreateFontCursor(a, b) 1
#define XSetFont(a, b, c)
*/
/* ------------------------------------------------------------ */

TileCursor standard_tilecursor;
TileCursor background_tilecursor;
TileCursor body_tilecursor;

TileCursor menu_tilecursor;

TileCursor question_tilecursor;
TileCursor confirmation_tilecursor;

TileCursor header_tilecursor;
TileCursor icon_tilecursor;

TileCursor gadget_tilecursor;
TileCursor move_gadget_tilecursor;
TileCursor zoom_gadget_tilecursor;

TileCursor left_tilecursor;
TileCursor right_tilecursor;
TileCursor top_tilecursor;
TileCursor bottom_tilecursor;

TileCursor top_left_tilecursor;
TileCursor bottom_left_tilecursor;
TileCursor top_right_tilecursor;
TileCursor bottom_right_tilecursor;

TileCursor track_open_tilecursor;
TileCursor corner_open_tilecursor;
TileCursor center_open_tilecursor;
TileCursor open_in_icon_tilecursor;

TileCursor move_tilecursor;
TileCursor move_icon_tilecursor;

TileCursor good_exchange_tilecursor;
TileCursor bad_exchange_tilecursor;

TileCursor watch_tilecursor;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void TileCursor_Init()
{
    XFontStruct  *font;
    GC  gc;
    

    font = (XFontStruct *) XLoadQueryFont(dpy, "cursor");
    gc = DefaultGC(dpy, scrn);
    XSetFont(dpy, gc, font->fid);

    standard_tilecursor = XCreateFontCursor(dpy, XC_top_left_arrow);
    background_tilecursor = standard_tilecursor;
    body_tilecursor = standard_tilecursor;
    menu_tilecursor = standard_tilecursor;

    question_tilecursor = XCreateFontCursor(dpy, XC_question_arrow);
    confirmation_tilecursor = question_tilecursor;
    
    header_tilecursor = XCreateFontCursor(dpy, XC_rtl_logo);
    icon_tilecursor = header_tilecursor;
    
    gadget_tilecursor = XCreateFontCursor(dpy, XC_iron_cross);
    zoom_gadget_tilecursor = gadget_tilecursor;

    move_gadget_tilecursor = XCreateFontCursor(dpy, XC_draped_box);
    open_in_icon_tilecursor = move_gadget_tilecursor;
    
    left_tilecursor = XCreateFontCursor(dpy, XC_left_side);
    right_tilecursor = XCreateFontCursor(dpy, XC_right_side);
    top_tilecursor = XCreateFontCursor(dpy, XC_top_side);
    bottom_tilecursor = XCreateFontCursor(dpy, XC_bottom_side);
    
    top_left_tilecursor = XCreateFontCursor(dpy, XC_top_left_corner);
    bottom_left_tilecursor = XCreateFontCursor(dpy, XC_bottom_left_corner);
    top_right_tilecursor = XCreateFontCursor(dpy, XC_top_right_corner);
    bottom_right_tilecursor = XCreateFontCursor(dpy, XC_bottom_right_corner);
    
    track_open_tilecursor = XCreateFontCursor(dpy, XC_dotbox);
    corner_open_tilecursor = bottom_right_tilecursor;
    center_open_tilecursor = XCreateFontCursor(dpy, XC_sizing);
    
    move_tilecursor = XCreateFontCursor(dpy, XC_hand2);
    move_icon_tilecursor = move_tilecursor;
    
    good_exchange_tilecursor = XCreateFontCursor(dpy, XC_exchange);
    bad_exchange_tilecursor = good_exchange_tilecursor;

    watch_tilecursor = XCreateFontCursor(dpy, XC_watch);
    
}

/* ---------------------------------------------------------------------- */

/*ARGSUSED*/
TileCursor
TileCursor_Make(fi, c)
    int         fi, c;
{}
