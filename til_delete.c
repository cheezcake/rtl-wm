#ifndef lint
static char sccs_id[] = "@(#)til_delete.c	5.3  9/7/88";
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

/****************************************************************************
 *The purpose of Tile_Delete is to "delete" the given tile.  Note
 *that the tile is never really deleted, it is marked as a space
 *tile and the area that was contained inside the tile is returned
 *to maximal horizontal strips with respect to the rest of the
 *screen
 ****************************************************************************/
#include "tileD.h"
#include "tile-listP.h"
#include "tile.h"

extern Tile *Tile_at_CP;
extern Tile *Tile_Split_Top (), *Tile_Split_Bottom ();
extern void  Tile_Merge();
extern Tile_List Tile_Right_Neighbors (), Tile_Left_Neighbors ();
extern Tile *Marry_Neighbors();

void
Tile_Delete(genericp)
Tilep genericp;
{
	Tile_List Rneighbors, Lneighbors;
	Tile *next_nbr;
	Tile *top_tile, *bottom_tile;
	Tile *stitch;
	TWRectangle old_area;
	Tile *tilep = (Tile *) genericp;

	/* set the current tile pointer (used by Tile_at_Point)
	* to a VALID neighbor tile
	*/
	if ( bl_stitch(tilep) != NULL_TILE )
		Tile_at_CP = bl_stitch(tilep);
	else if ( lb_stitch(tilep) != NULL_TILE )
		Tile_at_CP = lb_stitch(tilep);
	else if ( tr_stitch(tilep) != NULL_TILE )
		Tile_at_CP = tr_stitch(tilep);
	else if ( rt_stitch(tilep) != NULL_TILE )
		Tile_at_CP = rt_stitch(tilep);

	Tile_Set_Type (tilep, Space);

	if (Tile_at_CP == tilep)		/* then only 1 tile exists */
		return;

    	/* Need to keep around the upper-left and lower-right
	 * corners of the original area
	 */
	old_area.left_x = Left_X (tilep);
	old_area.top_y = Top_Y (tilep);
	old_area.right_x = Right_X (tilep);
	old_area.bottom_y = Bottom_Y (tilep);
	

	/* for each right neighbor of the original tile,
	 * split the tile and/or the neighbor (if it is
	 * a Space tile) so that the maximal horizontal
	 * strip property is regained
	 */
	Rneighbors = Tile_Right_Neighbors(tilep);
	Lneighbors = Tile_Left_Neighbors(tilep);

	TL_NEXT(next_nbr, Rneighbors);

	while (next_nbr != NULL_TILE)
	{
		if (Tile_Get_Type(next_nbr) == Space)
			tilep = Marry_Neighbors(tilep, next_nbr);

		TL_NEXT(next_nbr, Rneighbors);
	}
	TL_FREE(Rneighbors)


	/* for each left neighbor of the original tile,
	 * if that left neighbor is a space tile, treat it
	 * as the original tile above
	 */
	TL_NEXT(tilep, Lneighbors);

	while (tilep != NULL_TILE)
	{
		if (Tile_Get_Type(tilep) == Space)
		{
			Rneighbors = Tile_Right_Neighbors(tilep);
			TL_NEXT(next_nbr, Rneighbors);

			while (next_nbr != NULL_TILE)
			{
				if (Tile_Get_Type(next_nbr) == Space)
					tilep = Marry_Neighbors(tilep, next_nbr);

				TL_NEXT(next_nbr, Rneighbors);
			}
			TL_FREE(Rneighbors)
		}
		TL_NEXT(tilep, Lneighbors);
	}
	TL_FREE (Lneighbors)


	/* see if the top and bottom strips of the original
	 * tile can be merged
	 */
	bottom_tile = (Tile *) Tile_at_Point(old_area.left_x, old_area.bottom_y);

	if ( (stitch = lb_stitch(bottom_tile)) != NULL_TILE &&
	     Tile_Get_Type(stitch) == Space )
	{
		if (Left_X(bottom_tile) == Left_X(stitch) &&
		    Right_X(bottom_tile) == Right_X(stitch))

			Tile_Merge(bottom_tile, stitch, Bottom);
	}

	top_tile = (Tile *) Tile_at_Point(old_area.left_x, old_area.top_y);

	if ( (stitch = rt_stitch(top_tile)) != NULL_TILE &&
	     Tile_Get_Type(stitch) == Space )
	{
		if (Left_X(top_tile) == Left_X(stitch) &&
		    Right_X(top_tile) == Right_X(stitch))

			Tile_Merge(top_tile, stitch, Top);
	}
}


/****************************************************************************
 * Marry_Neighbors takes a space tile and its neighbor (which should
 * also be a space tile, OR ELSE!) and does vertical splits and
 * horizontal merges to regain the maximal horizontal strip property.
 * It returns either 'tile' or the space tile split off of the bottom of 
 * 'tile' (note: the size of the returned tile may (most probably) will differ
 * from the size of 'tile')
 ****************************************************************************
 */
Tile *
Marry_Neighbors(tile, neighbor)
Tile *tile;
Tile *neighbor;
{
      Tile *return_tile;
      Basetype top;
      Basetype bottom;

      return_tile = tile;

      if(Top_Y(tile) > Top_Y(neighbor))
	top = Top_Y(tile);
      else
	top = Top_Y(neighbor);
		
      if(Bottom_Y(tile) < Bottom_Y(neighbor))
	bottom = Bottom_Y(tile);
      else
	bottom = Bottom_Y(neighbor);

      if(Top_Y(tile) != top)
	Tile_Split_Top(tile, top);
      else if(Top_Y(neighbor) != top)
        Tile_Split_Top(neighbor, top);

      if(Bottom_Y(tile) != bottom)
        return_tile = Tile_Split_Bottom(tile, bottom);
      else if(Bottom_Y(neighbor) != bottom)
        Tile_Split_Bottom(neighbor, bottom);

      (void) Tile_Merge(tile, neighbor, Right);
      return(return_tile);
}
