/*
static char sccs_id[] = "@(#)tileI.h	5.4  9/1/88";
*/

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



/*	Tile data structure definition.
 */

#ifndef TILE
#include "tileP.h"
#endif

#define TILE_INTERN


typedef struct str_tile Tile;
struct str_tile
{
	int		name;		/* 'name' for this tile */

	Tile_Type	tile_type;

	TWRectangle       corners;        /* corners of this tile */

	Tile		*tr,		/* Top-most right neighbor   */
			*rt,		/* Right-most top neighbor   */
			*bl,		/* Bottom-most left neighbor */
			*lb;		/* Left-most bottom neighbor */

	pointer		my_win;		/* Tilwin info associated with    */
					/* this tile (NULL if Space Tile) */

	pointer		hor,		/* Horizontal and vertical edges */
			ver;		/* for prorating graphs          */
};


#ifndef  NULL_DEFN

	extern Tile	*Null_Tile;
	extern int	tile_name;

#endif
