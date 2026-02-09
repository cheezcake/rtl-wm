/*
static char sccs_id[] = "@(#)tile.h	5.6  9/1/88";
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



#ifndef TILE
#include "tileP.h"
#endif

#define TILE_EXTERN

extern void	Tile_Init_Tws();

	/* Basetype left_x, right_x, bottom_y, top_y */

extern int	Tiles_In_Area();
	/* Basetype left_x, top_y, right_x, bottom_y
	 * int (*enum_func)()
	 */

extern Tilep	Tile_Create();
	/* Basetype area_left_x, area_top_y, area_right_x, area_bottom_y */

extern void	Tile_Delete();
	/* Tilep tilep */

extern void	Tile_Enlarge();
	/* Tilep tilep;
	 * Side side;
	 * Basetype coord;
	 */

extern Tilep	Tile_at_Point();
	/* Basetype x, y */

extern void	Tile_Shrink();
	/* Tilep tilep;
	 * Side side;
	 * Basetype coord;
	 */

extern void	Tile_Shrink_Desktop();
	/* Side side;
	 * Basetype coord;
	 */

extern void	Tile_Enlarge_Desktop();
	/* Side side;
	 * Basetype coord;
	 */

extern void Tile_Update_Max_Hor_Strips();
extern void Tile_Update_Max_Ver_Strips();
extern void Tile_Create_Max_Hor_Strips();
extern void Tile_Create_Max_Ver_Strips();
extern void Tile_Create_Hor_Prorate_Graph();
extern void Tile_Create_Ver_Prorate_Graph();
