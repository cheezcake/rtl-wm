#ifndef lint
static char sccs_id[] = "@(#)check_shk.c	5.4  9/7/88";
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

#include "basetype.h"
#include "twinD.h"
#include "twin.h"
#include "goal.h"

#define max(a, b) ( a > b ? a : b)
#define min(a, b) ( a < b ? a : b)

Side
Check_Shrink(twinp, shrink_rectp, area, stamp)
    Tilwin *twinp;
    TWRectangle *shrink_rectp, 
	      area;
    TimeStamp stamp;
{
    Size min_size, 
         size;
    Side best_side;
    TWRectangle best_rect, 
              rect;
    float best_goal, 
          current_goal;

    if (Tilwin_Get_Window_Option(twinp, FIXED_SIZE) == TRUE ||
        Tilwin_Get_Window_Option(twinp, FIXED_COMPLETELY) == TRUE ||
        Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) == FALSE ||
        (Tilwin_Get_Global_Option(ALLOW_AUTO_SHRINK_MORE_RECENT) == FALSE &&
         Tilwin_Get_Window_Timestamp(twinp) > stamp))
        return (NoSide);
        
    if (Tilwin_Get_Global_Option(ENFORCE_MINIMUMS) == TRUE){
        Get_Width(min_size) = max(Get_Width(Tilwin_Get_Min(twinp)), 
                                  Get_Width(Tilwin_Get_Absolute_Minimums()));
        Get_Height(min_size) = max(Get_Height(Tilwin_Get_Min(twinp)), 
                                  Get_Height(Tilwin_Get_Absolute_Minimums()));
    }
    else
        min_size = Tilwin_Get_Absolute_Minimums();
        
    best_side = NoSide;
    best_goal = - (float) max(Get_Width(Tilwin_Get_Desktop_Size()), 
                              Get_Height(Tilwin_Get_Desktop_Size()));
    
    rect = *shrink_rectp;
    Get_LeftX(rect) = Get_RightX(area) + 1;
    COMPUTE_SIZE(rect, size);
    if (Tilwin_Get_Window_Option(twinp, FIXED_LEFT_EDGE) == FALSE &&
	Tilwin_Get_Window_Option(twinp, FIXED_WIDTH) == FALSE &&
        Get_Width(size) >= Get_Width(min_size)){
        current_goal = Goal(twinp, Tilwin_Get_Size(twinp), size);
        if (current_goal > best_goal){
            best_goal = current_goal;
            best_side = Left;
            best_rect = rect;
	}         
    }

    rect = *shrink_rectp;
    Get_RightX(rect) = Get_LeftX(area) - 1;
    COMPUTE_SIZE(rect, size);
    if (Tilwin_Get_Window_Option(twinp, FIXED_RIGHT_EDGE) == FALSE &&
	Tilwin_Get_Window_Option(twinp, FIXED_WIDTH) == FALSE &&
        Get_Width(size) >= Get_Width(min_size)){
        current_goal = Goal(twinp, Tilwin_Get_Size(twinp), size);
        if (current_goal > best_goal){
            best_goal = current_goal;
            best_side = Right;
            best_rect = rect;
	}         
    }

    rect = *shrink_rectp;
    Get_TopY(rect) = Get_BottomY(area) + 1;
    COMPUTE_SIZE(rect, size);
    if (Tilwin_Get_Window_Option(twinp, FIXED_TOP_EDGE) == FALSE &&
	Tilwin_Get_Window_Option(twinp, FIXED_HEIGHT) == FALSE &&
        Get_Height(size) >= Get_Height(min_size)){
        current_goal = Goal(twinp, Tilwin_Get_Size(twinp), size);
        if (current_goal > best_goal){
            best_goal = current_goal;
            best_side = Top;
            best_rect = rect;
	}         
    }

    rect = *shrink_rectp;
    Get_BottomY(rect) = Get_TopY(area) - 1;
    COMPUTE_SIZE(rect, size);
    if (Tilwin_Get_Window_Option(twinp, FIXED_BOTTOM_EDGE) == FALSE &&
	Tilwin_Get_Window_Option(twinp, FIXED_HEIGHT) == FALSE &&
        Get_Height(size) >= Get_Height(min_size)){
        current_goal = Goal(twinp, Tilwin_Get_Size(twinp), size);
        if (current_goal > best_goal){
            best_goal = current_goal;
            best_side = Bottom;
            best_rect = rect;
	}         
    }

    *shrink_rectp = best_rect;
    return(best_side);
}
