#ifndef lint
static char sccs_id[] = "@(#)twin_desk.c	5.3  9/1/88";
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
#include "twin.h"
#include "tile.h"
#include "gravity.h"

static bool desktop_initialized = FALSE;

void
Tilwin_Set_Desktop_Size(size)
    Size size;
{
    TWRectangle old_desktop_rect;
    
    if (Is_Odd_Number(Get_Width(size)) == TRUE)
        Get_Width(size)++;
    if (Is_Odd_Number(Get_Height(size)) == TRUE)
        Get_Height(size)++;

    desktop_size = size;

    old_desktop_rect = desktop_rect;
    Get_RightX(desktop_rect) = Get_Width(desktop_size) - 1;
    Get_BottomY(desktop_rect) = Get_Height(desktop_size) - 1;

    if (desktop_initialized == FALSE){
        desktop_initialized = TRUE;

        Get_LeftX(desktop_rect) = (Basetype) 0;
        Get_TopY(desktop_rect) = (Basetype) 0;

        Gravity_Init();
        Gravity_Insert_Edge(Get_LeftX(desktop_rect), Left);
        Gravity_Insert_Edge(Get_TopY(desktop_rect), Top);
        Gravity_Insert_Edge(Get_RightX(desktop_rect), Right);
        Gravity_Insert_Edge(Get_BottomY(desktop_rect), Bottom);
    }
    else{
    	Gravity_Delete_Edge(Get_RightX(old_desktop_rect), Right);
	Gravity_Delete_Edge(Get_BottomY(old_desktop_rect), Bottom);
        Gravity_Insert_Edge(Get_RightX(desktop_rect), Right);
        Gravity_Insert_Edge(Get_BottomY(desktop_rect), Bottom);
    }

    COMPUTE_CENTER(desktop_rect, desktop_center);

    Tile_Init_Tws(Get_LeftX(desktop_rect), Get_RightX(desktop_rect), 
                  Get_BottomY(desktop_rect), Get_TopY(desktop_rect));

    
}
