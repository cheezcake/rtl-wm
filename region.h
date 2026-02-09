/*
static char sccs_id[] = "@(#)region.h	5.6  9/1/88";
*/

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


#ifndef BASETYPE
#include "basetype.h"
#endif

#ifndef REGION
#include "regionP.h"
#endif

#ifndef TILECURSOR
#include "tilecrsrP.h"
#endif

#ifndef TILEMENU
#include "tilemenuP.h"
#endif

extern TWRegion back_region;

extern TWRegion header_region;
extern TWRegion body_region;

extern TWRegion left_region;
extern TWRegion right_region;
extern TWRegion top_region;
extern TWRegion bottom_region;

extern TWRegion top_left_region;
extern TWRegion top_right_region;
extern TWRegion bottom_left_region;
extern TWRegion bottom_right_region;

extern TWRegion zoom_gadget_region;
extern TWRegion move_gadget_region;

extern TWRegion rtl_region;
extern TWRegion icon_region;

extern void Region_Init();

extern Size Region_Minimum_Size();

extern TWPoint Region_Translate();
/* Userwin *uwinp */
/* TWPoint pt */
    /* Given a point on the desktop, returns that point translated */
    /* to the body of the window */

extern Size Region_Body_Size();
/* Userwin *uwinp */

extern Size Region_Icon_Body_Size();
/* Userwin *uwinp */

extern TWRectangle Region_Body_Rectangle();
/* Userwin *uwinp */

extern TWRectangle Region_Adjust_Rectangle();
/* Userwin *uwinp */
/* TWRectangle rect */
    /*  Given a body rect, return the corresponding window rect */

extern Size Region_Adjust_Size();
/* Userwin *uwinp */
/* Size siz */
    /*  Given a body size, return the corresponding window size */

extern Size Region_Unadjust_Size();
/* Userwin *uwinp */
/* Size siz */
    /*  Given a window size, return the corresponding body size */

extern TWRegion Region_Locate();
/* Userwin *uwinp */
/* TWPoint pt */
/*	Returns the region of the window in which the point is located */

extern TWRegion Region_Make_Edge();
/* Userwin *uwinp */
/* Side side */
/*	Returns the region of the window with the given edge */

extern TWRegion Region_Make_Corner();
/* Userwin *uwinp */
/* Side side */
/*	Returns the region of the window with the given corner */

extern TWRectangle Region_Header_Rect();
/* Userwin *uwinp */
/*      Returns rectangle of uwinp's header */

extern TWPoint Region_Get_Header_Pos();
/* Userwin *uwinp */
/* TWPoint pos */
/*      Returns pos warped to be inside header */

extern TWPoint Region_Gadget_Center();
/* Userwin *uwinp */
/*      Returns center of MOVE (or ZOOM) gadget */

extern TWPoint Region_Get_Edge_Pos();
/* Userwin *uwinp */
/* Side side */
/* TWPoint pt */
/*      Returns point with edge adjusted to far edge of side */

extern TWPoint Region_Get_Corner_Pos();
/* Userwin *uwinp */
/* Side side */
/*      Returns end point of corner */

extern TWRegion Region_Nearest_Border();
/* Userwin *uwinp */
/* TWPoint pos */
/*      Returns the region in win nearest pos */

extern bool Region_Nearby();
/* TWPoint pos1 */
/* TWPoint pos2 */
/*      Indicates if pos1 is nearby pos2 */

extern bool Region_Equal();
/* Region rgn1 */
/* Region rgn2 */

extern TileCursor Region_Get_Cursor();
/* Userwin *uwinp */
/* Region regn */

extern TileMenu Region_Get_Menu();
/* Userwin *uwinp */
/* Region regn */

#define Region_Is_Iconic(rgn) \
    ( ( (rgn).region_enum == icon ) || ( (rgn).region_enum == rtl ) )

