#ifndef lint
static char sccs_id[] = "@(#)try_place.c	5.3  9/1/88";
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
#include "twin.h"
#include "gravity.h"
#include "check.h"

/* Checks to see if the given rectangle meets the global and window-specific
 * (if appropriate) minimum and maximum requirements.  Adjusts the rectangle
 * with respect to gravity (if appropriate). Checks adjusted rectangle to make 
 * sure min-max criteria are still meet.  Return TRUE if the rectangle has been 
 * changed,  otherwise return FALSE.
 * NOTE:  This routine assumes the following partial ordering on the elements
 * abs_min (absolute minimums), win_min, win_max, and abs_max (absolute
 * maximums):
 * 	abs_min <= win_max, abs_min <= abs_max, 
 *	win_min <= win_max, win_min <= abs_max
 * However if this ordering does not hold (e.g. win_max < win_min), the maximum
 * constraints are satisfied at the expense of violating the minimum
 * constraints.
 */ 

bool
Trial_Place(rectp, side, win_min, win_max)
    TWRectangle *rectp;
    Side side;
    Size win_min, 
	 win_max;
{
    Size size, 
         original_size,
	 abs_min, abs_max;
    TWPoint location;
    TWRectangle rect,
                original_rect;
    Basetype left_diff, right_diff, 
	     top_diff, bottom_diff;
    bool changed = FALSE;
    
    rect = *rectp;
    original_rect = *rectp;

    COMPUTE_SIZE(rect, size);
    COMPUTE_CENTER(rect, location);
    
    /* check rectangle against absolute minimums */
    abs_min = Tilwin_Get_Absolute_Minimums();
    if (Get_Width(size) < Get_Width(abs_min)){
        switch (side) {
	case Left:
	case Top_Left:
	case Bottom_Left:
	    Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(abs_min) - 1);
            COMPUTE_SIZE(rect, size);
	    break;
	case Right:
	case Top_Right:
	case Bottom_Right:
	    Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(abs_min) - 1);
            COMPUTE_SIZE(rect, size);
	    break;
    	case NoSide:
	    Get_Width(size) = Get_Width(abs_min);
	    MAKE_RECTANGLE(location, size, rect);
	    break;
	}
        changed = TRUE;
    }
    if (Get_Height(size) < Get_Height(abs_min)){
	switch (side){
	case Top:
	case Top_Left:
	case Top_Right:
	    Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(abs_min) - 1);
            COMPUTE_SIZE(rect, size);
	    break;
	case Bottom:
	case Bottom_Left:
	case Bottom_Right:
	    Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(abs_min) - 1);
	    COMPUTE_SIZE(rect, size);
	    break;
	case NoSide:
	    Get_Height(size) = Get_Height(abs_min);
	    MAKE_RECTANGLE(location, size, rect);
	    break;
	}
	changed = TRUE;
    }

    /* check rectangle against window minimums (if appropriate) */
    if (Tilwin_Get_Global_Option(ENFORCE_MINIMUMS) == TRUE){
        if (Get_Width(size) < Get_Width(win_min)){
	    switch (side) {
	    case Left:
	    case Top_Left:
	    case Bottom_Left:
		Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(win_min) - 1);
                COMPUTE_SIZE(rect, size);
		break;
	    case Right:
	    case Top_Right:
	    case Bottom_Right:
		Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(win_min) - 1);
                COMPUTE_SIZE(rect, size);
		break;
	    case NoSide:
		Get_Width(size) = Get_Width(win_min);
	        MAKE_RECTANGLE(location, size, rect);
		break;
	    }
	    changed = TRUE;
        }
	if (Get_Height(size) < Get_Height(win_min)){
	    switch (side){
	    case Top:
	    case Top_Left:
	    case Top_Right:
		Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(win_min) - 1);
                COMPUTE_SIZE(rect, size);
		break;
	    case Bottom:
	    case Bottom_Left:
	    case Bottom_Right:
		Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(win_min) - 1);
                COMPUTE_SIZE(rect, size);
		break;
	    case NoSide:
	        Get_Height(size) = Get_Height(win_min);
		MAKE_RECTANGLE(location, size, rect);
		break;
	    }
	    changed = TRUE;
        }
      }

    /* check rectangle against the desktop size */
    abs_max = Tilwin_Get_Desktop_Size();
    if (Get_Width(size) > Get_Width(abs_max)){
        switch (side) {
	case Left:
	case Top_Left:
	case Bottom_Left:
	    Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(abs_max) - 1);
            COMPUTE_SIZE(rect, size);
	    break;
	case Right:
	case Top_Right:
	case Bottom_Right:
	    Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(abs_max) - 1);
            COMPUTE_SIZE(rect, size);
	    break;
    	case NoSide:
	    Get_Width(size) = Get_Width(abs_max);
	    MAKE_RECTANGLE(location, size, rect);
	    break;
	}
	changed = TRUE;
    }
    if (Get_Height(size) > Get_Height(abs_max)){
	switch (side){
	case Top:
	case Top_Left:
	case Top_Right:
	    Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(abs_max) - 1);
            COMPUTE_SIZE(rect, size);
	    break;
	case Bottom:
	case Bottom_Left:
	case Bottom_Right:
	    Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(abs_max) - 1);
            COMPUTE_SIZE(rect, size);
	    break;
	case NoSide:
	    Get_Height(size) = Get_Height(abs_max);
	    MAKE_RECTANGLE(location, size, rect);
	    break;
	}
	changed = TRUE;
    }

    /* check the rectangle against window max (if appropriate) */
    if (Tilwin_Get_Global_Option(ENFORCE_MAXIMUMS) == TRUE){
        if (Get_Width(size) > Get_Width(win_max)){
	    switch (side) {
	    case Left:
	    case Top_Left:
	    case Bottom_Left:
		Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(win_max) - 1);
                COMPUTE_SIZE(rect, size);
		break;
	    case Right:
	    case Top_Right:
	    case Bottom_Right:
		Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(win_max) - 1);
                COMPUTE_SIZE(rect, size);
		break;
	    case NoSide:
		Get_Width(size) = Get_Width(win_max);
		MAKE_RECTANGLE(location, size, rect);
		break;
	    }
	    changed = TRUE;
        }
	if (Get_Height(size) > Get_Height(win_max)){
	    switch (side){
	    case Top:
	    case Top_Left:
	    case Top_Right:
		Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(win_max) - 1);
                COMPUTE_SIZE(rect, size);
		break;
	    case Bottom:
	    case Bottom_Left:
	    case Bottom_Right:
		Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(win_max) - 1);
                COMPUTE_SIZE(rect, size);
		break;
	    case NoSide:
		Get_Height(size) = Get_Height(win_max);
		MAKE_RECTANGLE(location, size, rect);
		break;
	    }
	    changed = TRUE;
        }
      }
    
    /* adjust the rectangle for gravity */
    if (side == Left || side == Top_Left || side == Bottom_Left)
    	Get_LeftX(rect) = Gravity_Adjust_Edge(Get_LeftX(rect), Left);
    else if (side == Right || side == Top_Right || side == Bottom_Right)
	Get_RightX(rect) = Gravity_Adjust_Edge(Get_RightX(rect), Right);

    if (side == Top || side == Top_Left || side == Top_Right)
	Get_TopY(rect) = Gravity_Adjust_Edge(Get_TopY(rect), Top);
    else if (side == Bottom || side == Bottom_Left || side == Bottom_Right)
	Get_BottomY(rect) = Gravity_Adjust_Edge(Get_BottomY(rect), Bottom);

    if (side == NoSide) {
	/* original_size is the size the obeys mins and maxes */
	COMPUTE_SIZE(rect, original_size);
	Gravity_Adjust(&rect);
	
	/* if the size has changed, restore the original size by
	   finding the edge which is furthest from the nearest gravity
	   point and changing that edge.
	 */
	COMPUTE_SIZE(rect, size);
	if (Get_Width(size) != Get_Width(original_size)) {
	    left_diff = Gravity_Difference(Get_LeftX(original_rect), Left);
	    right_diff = Gravity_Difference(Get_RightX(original_rect), Right);
	    if (left_diff <= right_diff)
	       Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(original_size) - 1);
	    else
	       Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(original_size) - 1);
	}
	if (Get_Height(size) != Get_Height(original_size)) {
	    top_diff = Gravity_Difference(Get_TopY(original_rect), Top);
	    bottom_diff = Gravity_Difference(Get_BottomY(original_rect), Bottom);
	    if (top_diff <= bottom_diff)
	       Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(original_size) - 1);
	    else
	       Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(original_size) - 1);
	}
    }
    
    /* changes due to gravity may have caused mins or maxs to be violated.
     * Check appropriate mins and maxs again.  This is the same code as above
     * except when side == NoSide.
     */

    COMPUTE_SIZE(rect, size);
    
    abs_min = Tilwin_Get_Absolute_Minimums();
    if (Get_Width(size) < Get_Width(abs_min)){
        switch (side) {
	case Left:
	case Top_Left:
	case Bottom_Left:
	    Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(abs_min) - 1);
	    break;
	case Right:
	case Top_Right:
	case Bottom_Right:
	    Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(abs_min) - 1);
	    break;
    	case NoSide:
	    break;
	}
        COMPUTE_SIZE(rect, size);
        changed = TRUE;
    }
    if (Get_Height(size) < Get_Height(abs_min)){
	switch (side){
	case Top:
	case Top_Left:
	case Top_Right:
	    Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(abs_min) - 1);
	    break;
	case Bottom:
	case Bottom_Left:
	case Bottom_Right:
	    Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(abs_min) - 1);
	    break;
	case NoSide:
	    break;
	}
        COMPUTE_SIZE(rect, size);
	changed = TRUE;
    }


    if (Tilwin_Get_Global_Option(ENFORCE_MINIMUMS) == TRUE){
        if (Get_Width(size) < Get_Width(win_min)){
	    switch (side) {
	    case Left:
	    case Top_Left:
	    case Bottom_Left:
		Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(win_min) - 1);
		break;
	    case Right:
	    case Top_Right:
	    case Bottom_Right:
		Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(win_min) - 1);
		break;
	    case NoSide:
		break;
	    }
            COMPUTE_SIZE(rect, size);
            changed = TRUE;
        }
	if (Get_Height(size) < Get_Height(win_min)){
	    switch (side){
	    case Top:
	    case Top_Left:
	    case Top_Right:
		Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(win_min) - 1);
		break;
	    case Bottom:
	    case Bottom_Left:
	    case Bottom_Right:
		Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(win_min) - 1);
		break;
	    case NoSide:
		    break;
	    }
            COMPUTE_SIZE(rect, size);
	    changed = TRUE;
        }
      }

    abs_max = Tilwin_Get_Desktop_Size();
    if (Get_Width(size) > Get_Width(abs_max)){
        switch (side) {
	case Left:
	case Top_Left:
	case Bottom_Left:
	    Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(abs_max) - 1);
	    break;
	case Right:
	case Top_Right:
	case Bottom_Right:
	    Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(abs_max) - 1);
	    break;
    	case NoSide:
	    break;
	}
        COMPUTE_SIZE(rect, size);
	changed = TRUE;
    }
    if (Get_Height(size) > Get_Height(abs_max)){
	switch (side){
	case Top:
	case Top_Left:
	case Top_Right:
	    Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(abs_max) - 1);
	    break;
	case Bottom:
	case Bottom_Left:
	case Bottom_Right:
	    Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(abs_max) - 1);
	    break;
	case NoSide:
	    break;
	}
        COMPUTE_SIZE(rect, size);
	changed = TRUE;
    }

    if (Tilwin_Get_Global_Option(ENFORCE_MAXIMUMS) == TRUE){
        if (Get_Width(size) > Get_Width(win_max)){
	    switch (side) {
	    case Left:
	    case Top_Left:
	    case Bottom_Left:
		Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(win_max) - 1);
		break;
	    case Right:
	    case Top_Right:
	    case Bottom_Right:
		Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(win_max) - 1);
		break;
	    case NoSide:
		break;
	    }
	    changed = TRUE;
	}
	if (Get_Height(size) > Get_Height(win_max)){
	    switch (side){
	    case Top:
	    case Top_Left:
	    case Top_Right:
		Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(win_max) - 1);
		break;
	    case Bottom:
	    case Bottom_Left:
	    case Bottom_Right:
		Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(win_max) - 1);
		break;
	    case NoSide:
		break;
	    }
	    changed = TRUE;
        }
      }

#ifdef WM_DEBUG
    COMPUTE_SIZE(rect, size);
#endif

    /* return the "new" rectangle */
    *rectp = rect;
    return(changed);
}
