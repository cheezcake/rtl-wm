#ifndef lint
static char sccs_id[] = "@(#)init_tws.c	5.3  9/7/88";
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

/*	initialization of the Tiling system
 */
#define  NULL_DEFN		/* this file defines global "null" tile */

#include "tileD.h"
#include "tile-listP.h"


Tile *Tile_at_CP;		/* reference to the tile system */

Tile *Null_Tile;		/* "null" tile - all tiles' pointers not
				   pointing to a valid tile point to this! */

int tile_name = 0;		/* internally generated tile name */

Tile_Element *te_freelist = TENULL;	/* pointer to freelist of
					 * Tile_Elements (used for memory
					 * management of list elements)
					 */

static bool tiles_initialized = FALSE;  /* flag which tell whether or not the
                                         * tiling system has already been
                                         * initialized
                                         */

/* NOTE:  on a desktop resize, this routine will be called again.  The
 * interface guarantees that there will be no solid tiles on the desktop.  
 * Therefore, the Tile_at_CP  must be a space tile and is the only such tile on
 * the desktop.
 */

void
Tile_Init_Tws(left_x, right_x, bottom_y, top_y)
	Basetype left_x, right_x, bottom_y, top_y;
{
    Tile *tilep;

    if (tiles_initialized == FALSE){
	Null_Tile = allocate(Tile, 1);
	Tile_Set_Win(Null_Tile, (pointer) NULL);
	
	tr_stitch(Null_Tile) =			/* "null" points to itself */
	rt_stitch(Null_Tile) =
	bl_stitch(Null_Tile) =
	lb_stitch(Null_Tile) = NULL_TILE;
	Tile_Set_Name(Null_Tile, tile_name++);	/* set tile ID */

        /*  the first created Tile is a Space Tile
	 */
	tilep = allocate(Tile, 1);
	Tile_Set_Name(tilep, tile_name++);	/* set tile ID */
	Tile_Set_Type(tilep, Space);
	Tile_Set_Win(tilep, (pointer) NULL);
	
	tr_stitch(tilep) =			/* set tile stitches */
	rt_stitch(tilep) =
	bl_stitch(tilep) =
	lb_stitch(tilep) = NULL_TILE;

       	Tile_at_CP = tilep;

        tiles_initialized = TRUE;
        
    }

    Left_X(Tile_at_CP)   =  left_x;		/* set tile coordinates */
    Right_X(Tile_at_CP)  =  right_x;
    Bottom_Y(Tile_at_CP) =  bottom_y;
    Top_Y(Tile_at_CP)    =  top_y;

}

