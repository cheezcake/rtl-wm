/*
static char sccs_id[] = "@(#)tileD.h	5.5  9/1/88";
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



#ifndef TILE_INTERN
#include "tileI.h"
#endif

#define TILE_DEFINE


#define  NULL_TILE	Null_Tile

#define  Tile_Get_Name(tilep)		((tilep) -> name)
#define  Tile_Set_Name(tilep, a_name)	((tilep) -> name = (a_name))

#define  Tile_Get_Corners(tilep)	((tilep) -> corners)
#define  Tile_Set_Corners(tilep, rect)	((tilep) -> corners = (rect))

#define  Tile_Get_Type(tilep)		((tilep) -> tile_type)
#define  Tile_Set_Type(tilep, type)	((tilep) -> tile_type = (type))

#define  Tile_Get_Win(tilep)		((Tile *) (tilep) -> my_win)
#define  Tile_Set_Win(tilep, winp)	((tilep) -> my_win = (char *) (winp))

#define  Tile_Get_Hor_Edge(tilep)	((tilep) -> hor)
#define  Tile_Set_Hor_Edge(tilep, edge) ((tilep) -> hor = (char *) (edge))

#define  Tile_Get_Ver_Edge(tilep)	((tilep) -> ver)
#define  Tile_Set_Ver_Edge(tilep, edge) ((tilep) -> ver = (char *) (edge))


/*	tile system Coordinate manipulation macros
 */

/*	tile coordinate macros
 */
#define  Left_X(tile_ptr)	((tile_ptr) -> corners.left_x)
#define  Right_X(tile_ptr)	((tile_ptr) -> corners.right_x)
#define  Bottom_Y(tile_ptr)	((tile_ptr) -> corners.bottom_y)
#define  Top_Y(tile_ptr)	((tile_ptr) -> corners.top_y)

/* is tile enclosed within area?
 *
#define  Tile_In_Area(tile_ptr, area) \
	(  area -> left_x    <=  Left_X(tile_ptr) \
	&& Right_X(tile_ptr) <=  area -> right_x \
	&& area -> bottom_y  <=  Bottom_Y(tile_ptr) \
	&& Top_Y(tile_ptr)   <=  area -> top_y )
*/


/*	tile system Stitch manipulation macros
 */
#define  bl_stitch(tilep)  ((tilep) -> bl)	/* Bottom-most Left neighbor */

#define  lb_stitch(tilep)  ((tilep) -> lb)	/* Left-most Bottom neighbor */

#define  tr_stitch(tilep)  ((tilep) -> tr)	/* Top-most Right neighbor */

#define  rt_stitch(tilep)  ((tilep) -> rt)	/* Right-most Top neighbor */

#ifdef WM_DEBUG
extern Tile *t_global;
#endif

