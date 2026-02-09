#ifndef lint
static char sccs_id[] = "@(#)twin_dump.c	5.4  9/1/88";
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

#include <stdio.h>
#include "tileD.h"
#include "tile.h"
#include "twinD.h"
#include "twin.h"
#include "win.h"

#define  TAG_TILE       -1	/* separator tile in tile-dump file */

FILE *dump_file = (FILE *) NULL;

static Tile dumpee;
static Tile *dumper = &dumpee;


/*	Output "appropriate" information about
 *	a tile to a file.
 *	An enumeration function...
 */
void
Tilwin_Tile_Dump(a_tile)
	Tile *a_tile;
{
	if (Tile_Get_Name(a_tile) != TAG_TILE)
	{
		Tile_Set_Name(dumper, Tile_Get_Name(a_tile));
		Tile_Set_Type(dumper, Tile_Get_Type(a_tile));

		Left_X(dumper) = Left_X(a_tile);
		Right_X(dumper) = Right_X(a_tile);
		Top_Y(dumper) = Top_Y(a_tile);
		Bottom_Y(dumper) = Bottom_Y(a_tile);

		/* this assumes null pointers are == to NULL_TILE
		 * (a valid "sentinel" tile)
		 */
		bl_stitch(dumper) = (Tile *)Tile_Get_Name(bl_stitch(a_tile));
		lb_stitch(dumper) = (Tile *)Tile_Get_Name(lb_stitch(a_tile));
		tr_stitch(dumper) = (Tile *)Tile_Get_Name(tr_stitch(a_tile));
		rt_stitch(dumper) = (Tile *)Tile_Get_Name(rt_stitch(a_tile));

		(void) fwrite((char *) dumper, sizeof(Tile), 1, dump_file);
	}
	else
	{
		(void) fwrite((char *) a_tile, sizeof(Tile), 1, dump_file);
	}
}
/*	"dump" signal signal-handler
 */

void
Tilwin_Dump()
{
	extern void Tilwin_Tile_Dump();
	extern char *mktemp();
	extern FILE *fopen();
	extern Tile *Tile_at_CP;
	Tile *CP_pointer;
	static char *dump_name = (char *) NULL;
	Tile tag;			/* marker for beginning of a dump */

	/* save the current place of Tile_at_CP so we can
	 * restore it after the dump */
	CP_pointer = Tile_at_CP;
	
	if (dump_name == (char *) NULL)
	{
		dump_name = mktemp("DumpXXXXXX");

		if ( (dump_file = fopen(dump_name, "a")) == (FILE *) NULL )
		{
			perror("Onquit");
			return;
		}
	}

	tag.name = TAG_TILE;

	Tilwin_Tile_Dump(&tag);
	Tiles_In_Area(0, 0, desktop_size.width-1, 
			desktop_size.height-1, Tilwin_Tile_Dump);

	(void) fflush(dump_file);

	/* restore Tile_at_CP */
	Tile_at_CP = CP_pointer;
	
}
