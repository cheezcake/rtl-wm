#ifndef lint
static char sccs_id[] = "@(#)pcs_enum.c	5.3  9/7/88";
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

#include "tileD.h"
#include "tile-listP.h"
#include "tile.h"

/*	Visit all Tiles within the specified area.
 */
int
Tiles_In_Area(left_x, top_y, right_x, bottom_y, enum_func)
	Basetype left_x, top_y, right_x, bottom_y;
	void (*enum_func)();
{
	extern void enumerate();
	Tile *tilep;

	/*	find top-leftmost tile in area
	 */
	tilep = (Tile *) Tile_at_Point(left_x, top_y);

	/*	while the current tile is still in the area
	 */
	while (tilep != NULL_TILE && Top_Y(tilep) <= bottom_y)
	{
		enumerate(tilep, left_x, top_y, right_x, bottom_y, enum_func);
		tilep = (Tile *) Tile_at_Point(left_x, Bottom_Y(tilep) + 1);
	}
}


void
enumerate(tilep, left_x, top_y, right_x, bottom_y, enum_func)
	Tile *tilep;
	Basetype left_x, top_y, right_x, bottom_y;
	void (*enum_func)();
{
	extern Tile_List Tile_Right_Neighbors();
	Tile_List neighbors;
	Tile *nbr_tile;

	/*	R1 - enumerate the tile
	 */
	(*enum_func)((Tilep)tilep);

	/*	R2 - if the right edge of the tile is outside of the
	 *	search area, return
	 */
	if (right_x <= Right_X(tilep))
		return;

	/*	otherwise, use the neighbor finding algorithm
	 */
	neighbors = Tile_Right_Neighbors(tilep);
	TL_NEXT(nbr_tile, neighbors);

	while (nbr_tile != NULL_TILE)
	{
		/*	R3 - if the neighbor intersects the search area...
		 */
		if (top_y <= Bottom_Y(nbr_tile) && Top_Y(nbr_tile) <= bottom_y)

			/*	R4 - if the bottom left corner of a
		 	 *	neighbor touches the current tile,
		 	 *	then enumerate that neighbor
		 	 */
			if (bl_stitch(nbr_tile) == tilep)
	
				enumerate(nbr_tile, left_x, top_y,
					  right_x, bottom_y, enum_func);
	
			/*	R5 - or, if the bottom edge of the search
			 *	area cuts both the current tile and the
			 *	neighbor, then enumerate the neighbor
			 */
			else if (bottom_y <= Bottom_Y(tilep)
				 && bottom_y <= Bottom_Y(nbr_tile))
	
				enumerate(nbr_tile, left_x, top_y,
					  right_x, bottom_y, enum_func);

		TL_NEXT(nbr_tile, neighbors);
	}
	TL_FREE(neighbors);
}

