#ifndef lint
static char sccs_id[] = "@(#)twin_set.c	5.3  9/1/88";
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
#include "state.h"
#include "trial.h"

extern bool Tilwin_Open();

bool
Tilwin_Set(winp, location, size)
    Tilwinp winp;
    TWPoint location;
    Size size;
{
    Tilwin *twinp = (Tilwin *)winp;
    TWRectangle rect, 
              current_rect;

    if (Is_Odd_Number(Get_Width(size)) == TRUE)
        Get_Width(size)--;
    if (Is_Odd_Number(Get_Height(size)) == TRUE)
        Get_Height(size)--;

    if (Tilwin_Is_Open(twinp) == TRUE)
	return(Tilwin_Open(winp, location, size));
    else{
        State_Start_Operation();
        
	/* if the size does not meet the min/max criteria, fail */
	if (Trial_Satisfied(twinp, &size) == FALSE)
	    return(FALSE);
    
        MAKE_RECTANGLE(location, size, rect);
        current_rect = Tilwin_Get_Rectangle(twinp);

        /* check to see if the rectangle given us (implicitly by the location and
         * size) satisfied fixed edge options
         */
        if (Tilwin_Get_Window_Option(twinp, FIXED_LEFT_EDGE) == TRUE){
            Get_LeftX(rect) = Get_LeftX(current_rect);
            Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(size) - 1);
        }
        else if (Tilwin_Get_Window_Option(twinp, FIXED_RIGHT_EDGE) == TRUE){
            Get_RightX(rect) = Get_RightX(current_rect);
            Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(size) - 1);
        }
	
        if (Tilwin_Get_Window_Option(twinp, FIXED_TOP_EDGE) == TRUE) {
            Get_TopY(rect) = Get_TopY(current_rect);
            Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(size) - 1);
        }
        else if (Tilwin_Get_Window_Option(twinp, FIXED_BOTTOM_EDGE) == TRUE) {
            Get_BottomY(rect) = Get_BottomY(current_rect);
            Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(size) - 1);
        }

        COMPUTE_CENTER(rect, Tilwin_Get_Center(winp));
        Tilwin_Get_Size(winp) = size;
        Tilwin_Get_Rectangle(winp) = rect;
        return(TRUE);
    }
}

bool
Tilwin_Set_Size(winp, size)
    Tilwinp winp;
    Size size;
{
    Tilwin *twinp = (Tilwin *)winp;
    TWRectangle rect, 
              current_rect, 
              arect;
    TWPoint location;

    if (Is_Odd_Number(Get_Width(size)) == TRUE) Get_Width(size)--; 
    if (Is_Odd_Number(Get_Height(size)) == TRUE) Get_Height(size)--; 

    if (Trial_Satisfied(twinp, &size) == FALSE)
        return(FALSE);
        
    current_rect = Tilwin_Get_Rectangle(twinp);
    location = Tilwin_Get_Center(twinp);
    
    if (Tilwin_Get_Window_Option(twinp, FIXED_LEFT_EDGE) == TRUE){
        Get_LeftX(rect) = Get_LeftX(current_rect);
        Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(size) - 1);
    }
    else if (Tilwin_Get_Window_Option(twinp, FIXED_RIGHT_EDGE) == TRUE){
        Get_RightX(rect) = Get_RightX(current_rect);
        Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(size) - 1);
    }
    else{
        MAKE_RECTANGLE(location, size, arect);
        Get_LeftX(rect) = Get_LeftX(arect);
        Get_RightX(rect) = Get_RightX(arect);
    }

    if (Tilwin_Get_Window_Option(twinp, FIXED_RIGHT_EDGE) == TRUE){
        Get_TopY(rect) = Get_TopY(current_rect);
        Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(size) - 1);
    }
    else if (Tilwin_Get_Window_Option(twinp, FIXED_BOTTOM_EDGE) == TRUE){
        Get_BottomY(rect) = Get_BottomY(current_rect);
        Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(size) - 1);
    }
    else{
        MAKE_RECTANGLE(location, size, arect);
        Get_TopY(rect) = Get_TopY(arect);
        Get_BottomY(rect) = Get_BottomY(arect);
    }

    COMPUTE_CENTER(rect, location);
    
    return(Tilwin_Set(winp, location, size));
}
