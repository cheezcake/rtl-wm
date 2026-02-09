#ifndef lint
static char sccs_id[] = "@(#)pcs_split.c	5.3  9/7/88";
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

/*	Split Tile 'old_tile' on the specified side along 'new_coord'.
 *	'old_tile' can be either a Solid or Space tile; however
 *	the resulting 'new_tile' is ALWAYS a Space tile.
 *
 *	Returns a pointer to a new Space tile.
 */
#include "tileD.h"
#include "tile-listP.h"
#include "tile.h"

extern Tile_List    Tile_Top_Neighbors(),
		    Tile_Bottom_Neighbors(),
		    Tile_Left_Neighbors(),
		    Tile_Right_Neighbors();

extern void		Update_Split_Side(),
			Update_Adjacent_Sides();

#ifdef WM_DEBUG 
extern void Tile_Panic();
#endif 


Tile *
Tile_Split_Top(old_tile, new_coord)
	Tile *old_tile;
	Basetype new_coord;
{
	Tile *new_tile;
	Tile *old_bl,		/* temp for old tile's new stitch value */
	     *new_tr;		/* temp for new tile's stitch */
	Tile_List split_list,	/* neighbors of side parallel to split */
		  adj_list_1,	/* neighbors of adjacent 2 sides */
		  adj_list_2;

#ifdef WM_DEBUG 
	/* If new_coord is equal to the bottom or top of the
	 * old_tile, we will create a space of zero height. */
	if(((new_coord - 1) == Top_Y(old_tile)) ||
	   (new_coord == Bottom_Y(old_tile)))
		Tile_Panic("creating a tile of zero height");
#endif 

	/*	Get neighbor lists, split old_tile along
	 *	'side', update corner stitches so 'old' & 'new'
	 *	refer to each other
	 */
	split_list = Tile_Top_Neighbors(old_tile);
	adj_list_1 = Tile_Left_Neighbors(old_tile); 
	adj_list_2 = Tile_Right_Neighbors(old_tile); 


	/* ... = Tile_at_Point(Left_X(new_tile) - 1, Bottom_Y(new_tile)) */
	old_bl = (Tile *) Tile_at_Point(Left_X(old_tile) - 1, (new_coord - 1) );

	new_tr = (Tile *) Tile_at_Point(Right_X(old_tile) + 1, new_coord);

	new_tile = allocate(Tile, 1);
	Tile_Set_Name(new_tile, tile_name++);
	Tile_Set_Type(new_tile, Space);
	Tile_Set_Win(new_tile, (pointer) NULL);
	
	Top_Y(new_tile) = Top_Y(old_tile);
	Top_Y(old_tile) = new_coord;
	Bottom_Y(new_tile) = new_coord - 1;
	Left_X(new_tile) = Left_X(old_tile);
	Right_X(new_tile) = Right_X(old_tile);

	tr_stitch(new_tile) = tr_stitch(old_tile);
	rt_stitch(new_tile) = rt_stitch(old_tile);

	lb_stitch(new_tile) = old_tile;		/* refer to one another */
	rt_stitch(old_tile) = new_tile;

	/*	Update stitches along split - CONSISTENTLY
	 */
	bl_stitch(new_tile) = old_bl;
	tr_stitch(old_tile) = new_tr;

	Update_Split_Side(split_list, Top, old_tile, new_tile);
	Update_Adjacent_Sides(adj_list_1, Top, old_tile, new_tile);
	Update_Adjacent_Sides(adj_list_2, Top, old_tile, new_tile);

	TL_FREE(split_list);
	TL_FREE(adj_list_1);
	TL_FREE(adj_list_2);

	return(new_tile);
}


Tile *
Tile_Split_Bottom(old_tile, new_coord)
	Tile *old_tile;
	Basetype new_coord;
{
	Tile *new_tile;
	Tile *old_bl, *new_tr;
	Tile_List split_list, adj_list_1, adj_list_2;

#ifdef WM_DEBUG 
	if(((new_coord + 1) == Bottom_Y(old_tile)) ||
		(new_coord == Top_Y(old_tile)))
		Tile_Panic("creating a tile of zero height");
#endif 
	split_list = Tile_Bottom_Neighbors(old_tile);
	adj_list_1 = Tile_Left_Neighbors(old_tile); 
	adj_list_2 = Tile_Right_Neighbors(old_tile); 

	old_bl = (Tile *) Tile_at_Point(Left_X(old_tile) - 1, new_coord);

	/* ... = Tile_at_Point(Right_X(new_tile) + 1, Top_Y(new_tile)) */
	new_tr = (Tile *) Tile_at_Point(Right_X(old_tile) + 1, (new_coord + 1) );

	new_tile = allocate(Tile, 1);
	Tile_Set_Name(new_tile, tile_name++);
	Tile_Set_Type(new_tile, Space);
	Tile_Set_Win(new_tile, (pointer) NULL);

	Bottom_Y(new_tile) = Bottom_Y(old_tile);
	Bottom_Y(old_tile) = new_coord;
	Top_Y(new_tile) = new_coord + 1;
	Left_X(new_tile) = Left_X(old_tile);
	Right_X(new_tile) = Right_X(old_tile);

	bl_stitch(new_tile) = bl_stitch(old_tile);
	lb_stitch(new_tile) = lb_stitch(old_tile);

	rt_stitch(new_tile) = old_tile;
	lb_stitch(old_tile) = new_tile;

	bl_stitch(old_tile) = old_bl;
	tr_stitch(new_tile) = new_tr;

	Update_Split_Side(split_list, Bottom, old_tile, new_tile);
	Update_Adjacent_Sides(adj_list_1, Bottom, old_tile, new_tile);
	Update_Adjacent_Sides(adj_list_2, Bottom, old_tile, new_tile);

	TL_FREE(split_list);
	TL_FREE(adj_list_1);
	TL_FREE(adj_list_2);

	return(new_tile);
}


Tile *
Tile_Split_Left(old_tile, new_coord)
	Tile *old_tile;
	Basetype new_coord;
{
	Tile *new_tile;
	Tile *old_lb, *new_rt;
	Tile_List split_list, adj_list_1, adj_list_2;

#ifdef WM_DEBUG 
	if(((new_coord - 1) == Left_X(old_tile)) ||
		(new_coord == Right_X(old_tile)))
		Tile_Panic("creating a tile of zero width");
#endif 
	split_list = Tile_Left_Neighbors(old_tile);
	adj_list_1 = Tile_Top_Neighbors(old_tile); 
	adj_list_2 = Tile_Bottom_Neighbors(old_tile); 


	old_lb = (Tile *) Tile_at_Point(new_coord, Bottom_Y(old_tile) + 1);

	/* ... = Tile_at_Point(Right_X(new_tile), Top_Y(new_tile) - 1) */
	new_rt = (Tile *) Tile_at_Point( (new_coord - 1), Top_Y(old_tile) - 1);


	new_tile = allocate(Tile, 1);
	Tile_Set_Name(new_tile, tile_name++);
	Tile_Set_Type(new_tile, Space);
	Tile_Set_Win(new_tile, (pointer) NULL);

	Left_X(new_tile) = Left_X(old_tile);
	Left_X(old_tile) = new_coord;
	Right_X(new_tile) = new_coord - 1;
	Bottom_Y(new_tile) = Bottom_Y(old_tile);
	Top_Y(new_tile) = Top_Y(old_tile);

	bl_stitch(new_tile) = bl_stitch(old_tile);
	lb_stitch(new_tile) = lb_stitch(old_tile);

	tr_stitch(new_tile) = old_tile;
	bl_stitch(old_tile) = new_tile;

	rt_stitch(new_tile) = new_rt;
	lb_stitch(old_tile) = old_lb;

	Update_Split_Side(split_list, Left, old_tile, new_tile);
	Update_Adjacent_Sides(adj_list_1, Left, old_tile, new_tile);
	Update_Adjacent_Sides(adj_list_2, Left, old_tile, new_tile);

	TL_FREE(split_list);
	TL_FREE(adj_list_1);
	TL_FREE(adj_list_2);

	return(new_tile);
}


Tile *
Tile_Split_Right(old_tile, new_coord)
	Tile *old_tile;
	Basetype new_coord;
{
	Tile *new_tile;
	Tile *old_lb, *new_rt;
	Tile_List split_list, adj_list_1, adj_list_2;

#ifdef WM_DEBUG 
	if(((new_coord + 1) == Right_X(old_tile)) ||
		(new_coord == Left_X(old_tile)))
		Tile_Panic("creating a tile of zero height");
#endif 
	split_list = Tile_Right_Neighbors(old_tile);
	adj_list_1 = Tile_Top_Neighbors(old_tile); 
	adj_list_2 = Tile_Bottom_Neighbors(old_tile); 


	/* ... = Tile_at_Point(Left_X(new_tile), Bottom_Y(new_tile) + 1) */
	old_lb = (Tile *) Tile_at_Point( (new_coord + 1), Bottom_Y(old_tile) + 1);

	new_rt = (Tile *) Tile_at_Point(new_coord, Top_Y(old_tile) - 1);


	new_tile = allocate(Tile, 1);
	Tile_Set_Name(new_tile, tile_name++);
	Tile_Set_Type(new_tile, Space);
	Tile_Set_Win(new_tile, (pointer) NULL);

	Right_X(new_tile) = Right_X(old_tile);
	Right_X(old_tile) = new_coord;
	Left_X(new_tile) = new_coord + 1;
	Bottom_Y(new_tile) = Bottom_Y(old_tile);
	Top_Y(new_tile) = Top_Y(old_tile);

	tr_stitch(new_tile) = tr_stitch(old_tile);
	rt_stitch(new_tile) = rt_stitch(old_tile);

	bl_stitch(new_tile) = old_tile;
	tr_stitch(old_tile) = new_tile;

	rt_stitch(old_tile) = new_rt;
	lb_stitch(new_tile) = old_lb;
	
	Update_Split_Side(split_list, Right, old_tile, new_tile);
	Update_Adjacent_Sides(adj_list_1, Right, old_tile, new_tile);
	Update_Adjacent_Sides(adj_list_2, Right, old_tile, new_tile);

	TL_FREE(split_list);
	TL_FREE(adj_list_1);
	TL_FREE(adj_list_2);

	return(new_tile);
}

