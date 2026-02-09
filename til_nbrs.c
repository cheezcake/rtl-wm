#ifndef lint
static char sccs_id[] = "@(#)til_nbrs.c	5.3  9/7/88";
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


/*	neighbor-finding functions
 *	for cross-stitched tile management
 */
#include "tileD.h"
#include "tile.h"
#include "tile-listP.h"

#ifdef WM_DEBUG
extern void     Tile_Panic();
#endif

Tile_List
Tile_Right_Neighbors(tilep)
	Tile *tilep;
{
	Tile_List tile_list;
	Tile *next_neighbor = tr_stitch(tilep);

	tile_list.first = tile_list.last = tile_list.current = TENULL;
	
	while (next_neighbor != NULL_TILE
	       && Bottom_Y(tilep) >= Top_Y(next_neighbor))
	{
		TL_ADD(next_neighbor, tile_list);
		next_neighbor = lb_stitch(next_neighbor);
	}

	return(tile_list);
}


Tile_List
Tile_Left_Neighbors(tilep)
	Tile *tilep;
{
	Tile_List tile_list;
	Tile *next_neighbor = bl_stitch(tilep);

	tile_list.first = tile_list.last = tile_list.current = TENULL;
	while (next_neighbor != NULL_TILE
	       && Top_Y(tilep) <= Bottom_Y(next_neighbor))
	{
		TL_ADD(next_neighbor, tile_list);
		next_neighbor = rt_stitch(next_neighbor);
	}

	return(tile_list);
}


Tile_List
Tile_Top_Neighbors(tilep)
	Tile *tilep;
{
	Tile_List tile_list;
	Tile *next_neighbor = rt_stitch(tilep);

	tile_list.first = tile_list.last = tile_list.current = TENULL;
	while (next_neighbor != NULL_TILE
	       && Left_X(tilep) <= Right_X(next_neighbor))
	{
		TL_ADD(next_neighbor, tile_list);
		next_neighbor = bl_stitch(next_neighbor);
	}

	return(tile_list);
}


Tile_List
Tile_Bottom_Neighbors(tilep)
	Tile *tilep;
{
	Tile_List tile_list;
	Tile *next_neighbor = lb_stitch(tilep);

	tile_list.first = tile_list.last = tile_list.current = TENULL;
	while (next_neighbor != NULL_TILE
	       && Left_X(next_neighbor) <= Right_X(tilep))
	{
		TL_ADD(next_neighbor, tile_list);
		next_neighbor = tr_stitch(next_neighbor);
	}

	return(tile_list);
}

