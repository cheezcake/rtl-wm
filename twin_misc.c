#ifndef lint
static char sccs_id[] = "@(#)twin_misc.c	5.3  9/1/88";
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

#include "twinD.h"
#include "state.h"
#include "tileD.h"
#include "tile.h"
#include "win.h"

Tilwinp
Tilwin_Locate(pt)
    TWPoint pt;
{
    Tilep tilep;

    tilep = Tile_at_Point(Get_PtX(pt), Get_PtY(pt));

#ifdef WM_DEBUG
    t_global = (Tile *) tilep;
    if (tilep != (Tilep) NULL)
        tw_global = (Tilwin *) Tile_Get_Win((Tile *) tilep);
    else
        tw_global = (Tilwin *) NULL;
#endif
    
    if (tilep == (Tilep) NULL_TILE ||
	Tile_Get_Type((Tile *) tilep) == Space)
        return(WIN_NULL);
    else    
	return( (Tilwinp) Tile_Get_Win((Tile *) tilep));
}

Tilwinp
Tilwin_Locate_Window(id)
    pointer id;
{
    Tilwin *winp;
    WinpHandle handle;
    
    handle = State_Gen_Open_Windows();
    while ((winp = State_Coerce(handle)) != WINP_NULL) {
        if (Tilwin_Get_Window_Id(((Tilwinp) winp)) == id)
	    return((Tilwinp)winp);
	    State_Next_Window(&handle);
    }

    handle = State_Gen_Closed_Windows();
    while ((winp = State_Coerce(handle)) != WINP_NULL) {
        if (Tilwin_Get_Window_Id(((Tilwinp)winp)) == id)
	    return((Tilwinp)winp);
	    State_Next_Window(&handle);
    }
        
    return(WIN_NULL);
}

void
Tilwin_Modify_Covered_Windows(rect)
    TWRectangle rect;
{

	Tiles_In_Area(Get_LeftX(rect), Get_TopY(rect),
		      Get_RightX(rect), Get_BottomY(rect), 
		      Win_Add_Modified);
}

/* Returns FALSE if any tile in the area defined by rect is
 * a space tile.  Communication with Win_Is_Covered is accomplished through
 * the use of the global variable no_space_tile_in_area.
 */

bool no_space_tile_in_area;

bool
Tilwin_Is_Covered(rect)
    TWRectangle rect;
{

    no_space_tile_in_area = TRUE;
    Tiles_In_Area(Get_LeftX(rect), Get_TopY(rect),
	          Get_RightX(rect), Get_BottomY(rect), 
		  Win_Is_Covered);

    return(no_space_tile_in_area);
    
}

void 
Tilwin_Prorate()
{
}
