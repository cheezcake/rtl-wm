#ifndef lint
static char sccs_id[] = "@(#)pcs_merge.c	5.3  9/7/88";
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

extern Tile_List    Tile_Top_Neighbors(),
		    Tile_Bottom_Neighbors(),
		    Tile_Left_Neighbors(),
		    Tile_Right_Neighbors();

extern Tile *Tile_at_CP;

extern void Update_Split_Side();

#ifdef WM_DEBUG 
extern void Tile_Panic();
#endif 


/*	Merge adjacent Space Tiles, 'merge_tile' and 'old_tile', along
 *	the specified side of 'merge_tile' ('old_tile' is destroyed).
 */
void
Tile_Merge(merge_tile, old_tile, side)
	Tile *merge_tile,
	      *old_tile;
	Side side;
{
	Tile_List   list_1,	/* lists of neighbors for 3 sides of a Tile */
		    list_2,
		    list_3;

#ifdef WM_DEBUG 
	/* Check to see if the tiles being merged are of
	 * the same type. If not, panic */
	if (Tile_Get_Type(merge_tile) != Tile_Get_Type(old_tile)) {
	     Tile_Panic("trying to merge tiles of different type");
	}
#endif 

	switch (side)	/* Get lists of neighbors for 3 sides */
			/* and update coordinates to reflect the merge */
	{			
	case Top:
		list_1 = Tile_Top_Neighbors(old_tile); 
		list_2 = Tile_Left_Neighbors(old_tile); 
		list_3 = Tile_Right_Neighbors(old_tile); 

		Top_Y(merge_tile) = Top_Y(old_tile);
		rt_stitch(merge_tile) = rt_stitch(old_tile);
		tr_stitch(merge_tile) = tr_stitch(old_tile);

		Update_Split_Side(list_1, Top, old_tile, merge_tile);
		Update_Split_Side(list_2, Left, old_tile, merge_tile);
		Update_Split_Side(list_3, Right, old_tile, merge_tile);
		break;
	
	case Left:
		list_1 = Tile_Top_Neighbors(old_tile); 
		list_2 = Tile_Left_Neighbors(old_tile); 
		list_3 = Tile_Bottom_Neighbors(old_tile); 

		Left_X(merge_tile) = Left_X(old_tile);
		lb_stitch(merge_tile) = lb_stitch(old_tile);
		bl_stitch(merge_tile) = bl_stitch(old_tile);

		Update_Split_Side(list_1, Top, old_tile, merge_tile);
		Update_Split_Side(list_2, Left, old_tile, merge_tile);
		Update_Split_Side(list_3, Bottom, old_tile, merge_tile);
		break;

	case Right:
		list_1 = Tile_Top_Neighbors(old_tile); 
		list_2 = Tile_Right_Neighbors(old_tile); 
		list_3 = Tile_Bottom_Neighbors(old_tile); 

		Right_X(merge_tile) = Right_X(old_tile);
		rt_stitch(merge_tile) = rt_stitch(old_tile);
		tr_stitch(merge_tile) = tr_stitch(old_tile);

		Update_Split_Side(list_1, Top, old_tile, merge_tile);
		Update_Split_Side(list_2, Right, old_tile, merge_tile);
		Update_Split_Side(list_3, Bottom, old_tile, merge_tile);
		break;

	case Bottom:
		list_1 = Tile_Left_Neighbors(old_tile); 
		list_2 = Tile_Right_Neighbors(old_tile); 
		list_3 = Tile_Bottom_Neighbors(old_tile); 

		Bottom_Y(merge_tile) = Bottom_Y(old_tile);
		lb_stitch(merge_tile) = lb_stitch(old_tile);
		bl_stitch(merge_tile) = bl_stitch(old_tile);

		Update_Split_Side(list_1, Left, old_tile, merge_tile);
		Update_Split_Side(list_2, Right, old_tile, merge_tile);
		Update_Split_Side(list_3, Bottom, old_tile, merge_tile);
		break;
	}

	TL_FREE(list_1);
	TL_FREE(list_2);
	TL_FREE(list_3);

	Tile_at_CP = merge_tile;
	free( (char *) old_tile );
	old_tile = NULL_TILE;
}

