#ifndef lint
static char sccs_id[] = "@(#)win.c	5.3  9/1/88";
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

#include "basetype.h"
#include "twinD.h"
#include "tile.h"
#include "tileD.h"
#include "state.h"
#include "gravity.h"

void
Win_Open(winp, rect)
    Tilwin *winp;
    TWRectangle rect;
{
    TWPoint location;
    Size size;

    Gravity_Insert_Edge(Get_LeftX(rect), Left);
    Gravity_Insert_Edge(Get_RightX(rect), Right);
    Gravity_Insert_Edge(Get_TopY(rect), Top);
    Gravity_Insert_Edge(Get_BottomY(rect), Bottom);

    Tilwin_Get_Rectangle(winp) = rect;
    COMPUTE_CENTER(rect, location);
    Tilwin_Get_Center(winp) = location;
    COMPUTE_SIZE(rect, size);
    Tilwin_Get_Size(winp) = size;

    Tilwin_Get_Tile(winp) = Tile_Create(Get_LeftX(rect), 
			    Get_TopY(rect), Get_RightX(rect), Get_BottomY(rect));
    Tile_Set_Win((Tile *) Tilwin_Get_Tile(winp), (pointer) winp);
    
}

void
Win_Shrink(winp, side, coord)
    Tilwin *winp;
    Side side;
    Basetype coord;
{
    TWPoint location;
    Size size;
    
    switch (side) {
    case Top:
	Gravity_Delete_Edge(Get_TopY(Tilwin_Get_Rectangle(winp)), Top);
        Get_TopY(Tilwin_Get_Rectangle(winp)) = coord;
        break;
    case Bottom:
	Gravity_Delete_Edge(Get_BottomY(Tilwin_Get_Rectangle(winp)), Bottom);
        Get_BottomY(Tilwin_Get_Rectangle(winp)) = coord;
        break;
    case Left:
	Gravity_Delete_Edge(Get_LeftX(Tilwin_Get_Rectangle(winp)), Left);
        Get_LeftX(Tilwin_Get_Rectangle(winp)) = coord;
        break;
    case Right:
	Gravity_Delete_Edge(Get_RightX(Tilwin_Get_Rectangle(winp)), Right);
        Get_RightX(Tilwin_Get_Rectangle(winp)) = coord;
        break;
    }

    Gravity_Insert_Edge(coord, side);

    COMPUTE_CENTER(Tilwin_Get_Rectangle(winp), location);
    Tilwin_Get_Center(winp) = location;
    COMPUTE_SIZE(Tilwin_Get_Rectangle(winp), size);
    Tilwin_Get_Size(winp) = size;

    Tile_Shrink(Tilwin_Get_Tile(winp), side, coord);

}

void
Win_Enlarge(winp, side, coord)
    Tilwin *winp;
    Side side;
    Basetype coord;
{
    TWPoint location;
    Size size;
    
    switch (side) {
    case Top:
	Gravity_Delete_Edge(Get_TopY(Tilwin_Get_Rectangle(winp)), Top);
        Get_TopY(Tilwin_Get_Rectangle(winp)) = coord;
        break;
    case Bottom:
	Gravity_Delete_Edge(Get_BottomY(Tilwin_Get_Rectangle(winp)), Bottom);
        Get_BottomY(Tilwin_Get_Rectangle(winp)) = coord;
        break;
    case Left:
	Gravity_Delete_Edge(Get_LeftX(Tilwin_Get_Rectangle(winp)), Left);
        Get_LeftX(Tilwin_Get_Rectangle(winp)) = coord;
        break;
    case Right:
	Gravity_Delete_Edge(Get_RightX(Tilwin_Get_Rectangle(winp)), Right);
        Get_RightX(Tilwin_Get_Rectangle(winp)) = coord;
        break;
    }

    Gravity_Insert_Edge(coord, side);

    COMPUTE_CENTER(Tilwin_Get_Rectangle(winp), location);
    Tilwin_Get_Center(winp) = location;
    COMPUTE_SIZE(Tilwin_Get_Rectangle(winp), size);
    Tilwin_Get_Size(winp) = size;

    Tile_Enlarge(Tilwin_Get_Tile(winp), side, coord);

}

void
Win_Close(winp)
    Tilwin *winp;
{
    TWRectangle rect;
    
    rect = Tilwin_Get_Rectangle(winp);
    
    Gravity_Delete_Edge(Get_LeftX(rect), Left);
    Gravity_Delete_Edge(Get_RightX(rect), Right);
    Gravity_Delete_Edge(Get_TopY(rect), Top);
    Gravity_Delete_Edge(Get_BottomY(rect), Bottom);

    Tile_Delete(Tilwin_Get_Tile(winp));
    Tilwin_Get_Tile(winp) = (Tilep) NULL;
}

/*	Add the window associated with the Solid 'tilep'
 *	to the Potentially Modified List
 */
void
Win_Add_List(tilep) 
	Tilep tilep; 
{ 
	if (Tile_Get_Type((Tile *)tilep) == Solid) 
	    State_Insert_Potentially_Modfd((Tilwin *)Tile_Get_Win((Tile *)tilep));
} 

void
Win_Add_Modified(tilep)
	Tilep tilep;
{
    if (Tile_Get_Type((Tile *)tilep) == Solid)
        State_Insert_Just_Modified((Tilwin *)Tile_Get_Win((Tile *)tilep));
}

/* called by Tilwin_Is_Covered.  If a space tile is handed to Win_Is_Covered, 
 * it sets the global flag no_space_tile_in_area to FALSE.
 */

extern bool no_space_tile_in_area;

void
Win_Is_Covered(tilep)
    Tilep tilep;
{
    if (Tile_Get_Type((Tile *)tilep) == Space)
        no_space_tile_in_area = FALSE;
}
