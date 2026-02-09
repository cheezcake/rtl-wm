#ifndef lint
static char sccs_id[] = "@(#)til_shrink.c	5.3  9/7/88";
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

/*	shrink 'tile' on its 'side' at 'coord' position
 */
#include <stdio.h>
#include "tileD.h"

extern Tile *Tile_Split_Left(),
	*Tile_Split_Right(),
	*Tile_Split_Top(),
	*Tile_Split_Bottom();

extern void Tile_Delete();

#ifdef WM_DEBUG 
extern void Tile_Panic();
#endif 


void
Tile_Shrink(genericp, side, coord)
	Tilep genericp;
	Side side;
	Basetype coord;
{
	Tile *Sp,
	     *tile = (Tile *) genericp;

	/*   	Split off a new Space Tile (Sp) along the
	 *	shrunken side of the old tile...
	 */
	switch (side)
	{
	case Left:
#ifdef WM_DEBUG
		if(coord <= Left_X(tile) || coord >= Right_X(tile))
		    Tile_Panic("shrink out of horizontal range");
#endif		    
		Sp = Tile_Split_Left(tile, coord);
	break;

	case Right:
#ifdef WM_DEBUG
		if(coord <= Left_X(tile) || coord >= Right_X(tile))
		    Tile_Panic("shrink out of horizontal range");
#endif		    
		Sp = Tile_Split_Right(tile, coord);
	break;

	case Top:
#ifdef WM_DEBUG
		if(coord <= Top_Y(tile) || coord >= Bottom_Y(tile))
		    Tile_Panic("shrink out of vertical range");
#endif
		Sp = Tile_Split_Top(tile, coord);
	break;

	case Bottom:
#ifdef WM_DEBUG
		if(coord <= Top_Y(tile) || coord >= Bottom_Y(tile))
		    Tile_Panic("shrink out of vertical range");
#endif
		Sp = Tile_Split_Bottom(tile, coord);
	break;
	}

	Tile_Delete( (Tilep) Sp );
}
