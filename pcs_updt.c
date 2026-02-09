#ifndef lint
static char sccs_id[] = "@(#)pcs_updt.c	5.3  9/7/88";
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

/*	functions for updating a Tile's neighbors
 */

#include "tileD.h"
#include "tile-listP.h"

/*	Neighbors (on 'split_list') of 'old_tile' on 'side'
 *	facing 'new_tile' are set to refer to 'new_tile', if
 *	they refer to 'old_tile'.
 */
void
Update_Split_Side(split_list, side, old_tile, new_tile)
	Tile_List split_list;
	Side side;
	Tile *old_tile,
	     *new_tile;
{
	Tile *next_tile;

	TL_NEXT(next_tile, split_list);

	while (next_tile != NULL_TILE)
	{
		switch (side)
		{
		case Top:
			if (lb_stitch(next_tile) == old_tile)
				lb_stitch(next_tile) = new_tile;
		break;

		case Bottom:
			if (rt_stitch(next_tile) == old_tile)
				rt_stitch(next_tile) = new_tile;
		break;

		case Left:
			if (tr_stitch(next_tile) == old_tile)
				tr_stitch(next_tile) = new_tile;
		break;

		case Right:
			if (bl_stitch(next_tile) == old_tile)
				bl_stitch(next_tile) = new_tile;
		break;
		}

		TL_NEXT(next_tile, split_list);
	}
}

/*	Neighbors (on 'adj_list') of adjacent sides to 'side' which
 *	was split, are conditionally updated to refer to 'new_tile'
 *	if they previously referred to 'old_tile'.
 */
void
Update_Adjacent_Sides(adj_list, side, old_tile, new_tile)
	Tile_List adj_list;
	Side side;
	Tile *old_tile,
	     *new_tile;
{
	Tile *next_tile;

	TL_NEXT(next_tile, adj_list);

	while (next_tile != NULL_TILE)
	{
		switch (side)
		{
		case Top:
			if (tr_stitch(next_tile) == old_tile
			    && Top_Y(next_tile) < Top_Y(old_tile))

				tr_stitch(next_tile) = new_tile;

			if (bl_stitch(next_tile) == old_tile
			    && Bottom_Y(next_tile) < Top_Y(old_tile))

				bl_stitch(next_tile) = new_tile;
		break;

		case Bottom:
			if (tr_stitch(next_tile) == old_tile
			    && Bottom_Y(old_tile) < Top_Y(next_tile))

				tr_stitch(next_tile) = new_tile;

			if (bl_stitch(next_tile) == old_tile
			    && Bottom_Y(old_tile) < Bottom_Y(next_tile))

				bl_stitch(next_tile) = new_tile;
		break;

		case Left:
			if (rt_stitch(next_tile) == old_tile
			    && Right_X(next_tile) < Left_X(old_tile))

				rt_stitch(next_tile) = new_tile;

			if (lb_stitch(next_tile) == old_tile
			    && Left_X(next_tile) < Left_X(old_tile))

				lb_stitch(next_tile) = new_tile;
		break;

		case Right:
			if (rt_stitch(next_tile) == old_tile
			    && Right_X(old_tile) < Right_X(next_tile))

				rt_stitch(next_tile) = new_tile;

			if (lb_stitch(next_tile) == old_tile
			    && Right_X(old_tile) < Left_X(next_tile))

				lb_stitch(next_tile) = new_tile;
		break;
		}

		TL_NEXT(next_tile, adj_list);
	}
}

