#ifndef lint
static char sccs_id[] = "@(#)til_enlrg.c	5.3  9/7/88";
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

/* Enlarge 'tile' on its 'side' to 'coord' position. NOTE:
 * assumes that area in which enlargement is done is a
 * space tile
 */
#include "tileD.h"
#include "tile.h"

extern void	Tile_Merge();

#ifdef WM_DEBUG
extern void     Tile_Panic();
#endif

void
Tile_Enlarge(genericp, side, coord)
    Tilep genericp;
    Side side;
    Basetype coord;
{
    Tile *new_tile,
	 *tile = (Tile *) genericp;

   switch (side) {
   case Left:
#ifdef WM_DEBUG 
	if(coord >= Left_X(tile))
	    Tile_Panic("enlarge out of horizontal range");
#endif 
       new_tile = (Tile *) Tile_Create(coord, Top_Y(tile),
					Left_X(tile)-1, Bottom_Y(tile));
       Tile_Merge(tile, new_tile, Left);
       break;

   case Right:
#ifdef WM_DEBUG 
	if(coord <= Right_X(tile))
	    Tile_Panic("enlarge out of horizontal range");
#endif 
       new_tile = (Tile *) Tile_Create(Right_X(tile)+1, Top_Y(tile),
					coord, Bottom_Y(tile));
       Tile_Merge(tile, new_tile, Right);
       break;

   case Top:
#ifdef WM_DEBUG 
	if(coord >= Top_Y(tile))
	    Tile_Panic("enlarge out of vertical range");
#endif 
       new_tile = (Tile *) Tile_Create(Left_X(tile), coord,
					Right_X(tile), Top_Y(tile)-1);
       Tile_Merge(tile, new_tile, Top);
       break;

   case Bottom:
#ifdef WM_DEBUG 
	if(coord <= Bottom_Y(tile))
	    Tile_Panic("enlarge out of vertical range");
#endif 
       new_tile = (Tile *) Tile_Create(Left_X(tile), Bottom_Y(tile)+1,
					Right_X(tile), coord);
       Tile_Merge(tile, new_tile, Bottom);
       break;
   }
}
