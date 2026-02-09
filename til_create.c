#ifndef lint
static char sccs_id[] = "@(#)til_create.c	5.3  9/7/88";
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

/*	Create a new Tile defined by the rectangular area.
 *
 *	Returns pointer to new "Tilep".
 */
#include "tileD.h"
#include "tile.h"

extern Tile *Tile_Split_Top(),
	    *Tile_Split_Bottom(),
	    *Tile_Split_Left(),
	    *Tile_Split_Right();

extern void Tile_Merge();
#ifdef WM_DEBUG
extern void Tile_Panic();
#endif

Tilep
Tile_Create(area_left_x, area_top_y, area_right_x, area_bottom_y)
	Basetype area_left_x, area_top_y, area_right_x, area_bottom_y;
{
	Tile *center_tile,
	     *edge_tile,			/* left or right edge */
	     *prev_left_tile = NULL_TILE,
	     *prev_right_tile = NULL_TILE;
	     
	Tile *growing_tile = NULL_TILE; 	/* growing Solid tile */

#ifdef WM_DEBUG
	/* make sure values past to us make sense */
	if (area_left_x >= area_right_x ||
            area_top_y >= area_bottom_y)
	        Tile_Panic("trying to create a nonsense tile");
#endif
		
	/*    If the Top edge of 'area' does NOT lie on the top edge of
	 *    a Space tile, then split that Space tile vertically
	 */
	center_tile = (Tile *) Tile_at_Point(area_left_x, area_top_y);
#ifdef WM_DEBUG
	if (center_tile == NULL_TILE)
	    Tile_Panic("trying to create a tile off of the desktop");
#endif
	
	if (area_top_y != Top_Y(center_tile))
		(void) Tile_Split_Top(center_tile, area_top_y);

	/*    If the Bottom edge of 'area' does NOT lie on the bottom edge of
	 *    another Space tile...
	 */
	edge_tile = (Tile *) Tile_at_Point(area_right_x, area_bottom_y);
#ifdef WM_DEBUG
	if (edge_tile == NULL_TILE)
	    Tile_Panic("trying to create a tile off of the desktop");
#endif

	if (area_bottom_y != Bottom_Y(edge_tile))
		(void) Tile_Split_Bottom(edge_tile, area_bottom_y);

	do
	{
	/*    Split Space tile into Left, Center and Right Space
	 *    tiles, merging with previous left (right) tiles if
	 *    possible...
	 */
		if (area_left_x != Left_X(center_tile))
		{
			edge_tile = Tile_Split_Left(center_tile,
						area_left_x);

			/* if the rightmost top tile is not
			 * the NULL_TILE AND is a Space
			 * tile AND has its left and right
			 * edges equal to the left and
			 * right edges of edge tile, merge
			 * the two tiles for reform maximal
			 * horizontal stips.
			 */
			if (rt_stitch(edge_tile) != NULL_TILE &&
			    Tile_Get_Type(rt_stitch(edge_tile)) == Space &&
			    Left_X(edge_tile) == Left_X(rt_stitch(edge_tile)) &&
			    Right_X(edge_tile) == Right_X(rt_stitch(edge_tile)))
			        Tile_Merge(edge_tile, rt_stitch(edge_tile), Top);

			prev_left_tile = edge_tile;
		}
		else
		    prev_left_tile = NULL_TILE;

		if (area_right_x != Right_X(center_tile))
		{
			edge_tile = Tile_Split_Right(center_tile,
						area_right_x);

			/* See comment above for explanation */
			if (rt_stitch(edge_tile) != NULL_TILE &&
			    Tile_Get_Type(rt_stitch(edge_tile)) == Space &&
			    Left_X(edge_tile) == Left_X(rt_stitch(edge_tile)) &&
			    Right_X(edge_tile) == Right_X(rt_stitch(edge_tile)))
			        Tile_Merge(edge_tile, rt_stitch(edge_tile), Top);

			prev_right_tile = edge_tile;
		}
		else
		    prev_right_tile = NULL_TILE;

		if (growing_tile == NULL_TILE)
			growing_tile = center_tile;
		else
			Tile_Merge(growing_tile, center_tile, Bottom);


		center_tile = (Tile *) Tile_at_Point(Left_X(growing_tile),
					(Bottom_Y(growing_tile) + 1));

	}
	while ( center_tile != NULL_TILE &&
		Top_Y(center_tile) < area_bottom_y );

	/* see if we can merge along the bottom of the space
	 * tiles on the left and right sides of the newly
	 * created solid tile */

	if (prev_left_tile != NULL_TILE) {
	    edge_tile = lb_stitch(prev_left_tile);

		/* merge only Space tiles */
		if(edge_tile != NULL_TILE &&
		   Tile_Get_Type(edge_tile) == Space)
		  if (Left_X(edge_tile) == Left_X(prev_left_tile)
		      && Right_X(edge_tile) == Right_X(prev_left_tile))
			Tile_Merge(edge_tile, prev_left_tile, Top);
	}

	if (prev_right_tile != NULL_TILE) {
	    edge_tile = lb_stitch(prev_right_tile);
		
		if(edge_tile != NULL_TILE &&
		   Tile_Get_Type(edge_tile) == Space)
		  if (Left_X(edge_tile) == Left_X(prev_right_tile)
		      && Right_X(edge_tile) == Right_X(prev_right_tile))
			Tile_Merge(edge_tile, prev_right_tile, Top);
	}

	Tile_Set_Name(growing_tile, tile_name++);
	Tile_Set_Type(growing_tile, Solid);

	return ( (Tilep) growing_tile );
}

