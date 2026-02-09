#ifndef lint
static char sccs_id[] = "@(#)til_find.c	5.3  9/7/88";
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

/*	Return (pointer to) Tile containing
 *	the point (x , y)  -- actually a Tilep.
 *
 *	MODIFIES: Tile_at_CP
 */
#include "tileD.h"
#include "twin.h"

extern Tile *Tile_at_CP;

#ifdef WM_DEBUG
extern void Tile_Panic();
#endif


Tilep
Tile_at_Point(x, y)
	Basetype x, y;
{
	Tile *tilep = Tile_at_CP;

	if ( x < 0 || Get_Width(Tilwin_Get_Desktop_Size()) - 1 < x  ||
	     y < 0 || Get_Height(Tilwin_Get_Desktop_Size()) - 1 < y )
		return ( (Tilep) NULL_TILE );

	FOREVER
	{
		if (Top_Y(tilep) <= y)

			if (y <= Bottom_Y(tilep))

			/* tile is within vertical range, check horizontal
			 */
				if (Left_X(tilep) <= x)

					if (x <= Right_X(tilep)) 

					/* then tile contains (x, y) - done
					 */
						break;
					
					else		/* move "right" in X */
						tilep = tr_stitch(tilep);

				else			/* move "left" in X */
					tilep = bl_stitch(tilep);

			else				/* move "down" in Y */
				tilep = lb_stitch(tilep);

		else				/* move "up" in Y */
			tilep = rt_stitch(tilep);
	}

	if (tilep != NULL_TILE)
		Tile_at_CP = tilep;
#ifdef WM_DEBUG 
	else
		Tile_Panic("tile at Current Position is null tile");
#endif 
	return ( (Tilep) tilep );
}

