#ifndef lint
static char sccs_id[] = "@(#)twin_rsz.c	5.3  9/1/88";
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
#include "commit.h"
#include "win.h"
#include "gravity.h"

extern bool Tilwin_Open_Best_In_Area();
extern TWRectangle desktop_rect;

bool
Tilwin_Check_Resize(winp, adr_pt, dir, min_size, max_size)
    Tilwinp winp;
    TWPoint *adr_pt;
    Side dir;
    Size min_size, 
	 max_size;
{
    Tilwin *twinp = (Tilwin *)winp;
    TWRectangle rect, 
              grect;

    /* check incoming sizes (the points are check when adjusted
     * for gravity)
     */
    if (Is_Odd_Number(Get_Width(min_size)) == TRUE)
        Get_Width(min_size)++;
    if (Is_Odd_Number(Get_Height(min_size)) == TRUE)
        Get_Height(min_size)++;
    if (Is_Odd_Number(Get_Width(max_size)) == TRUE)
        Get_Width(max_size)++;
    if (Is_Odd_Number(Get_Height(max_size)) == TRUE)
        Get_Height(max_size)++;

    /* if the window is open, remove it's edges from the gravity lists so they
     * don't interfere with the placement
     */
    if (Tilwin_Is_Open(twinp) == TRUE){
        grect = Tilwin_Get_Rectangle(twinp);
        Gravity_Delete_Edge(Get_LeftX(grect), Left);
        Gravity_Delete_Edge(Get_RightX(grect), Right);
        Gravity_Delete_Edge(Get_TopY(grect), Top);
        Gravity_Delete_Edge(Get_BottomY(grect), Bottom);
    }

    rect = Tilwin_Get_Rectangle(twinp);

    if (dir == Left || dir == Top_Left || dir == Bottom_Left)
        Get_LeftX(rect) = Get_PtX(*adr_pt);
    else if (dir == Right || dir == Top_Right || dir == Bottom_Right)
	Get_RightX(rect) = Get_PtX(*adr_pt);
    if (dir == Top || dir == Top_Left || dir == Top_Right)
	Get_TopY(rect) = Get_PtY(*adr_pt);
    else if (dir == Bottom || dir == Bottom_Left || dir == Bottom_Right)
	Get_BottomY(rect) = Get_PtY(*adr_pt);

    (void) Trial_Place(&rect, dir, min_size, max_size);
    
    if (dir == Left || dir == Top_Left || dir == Bottom_Left)
        Get_PtX(*adr_pt) = Get_LeftX(rect);
    else if (dir == Right || dir == Top_Right || dir == Bottom_Right)
	Get_PtX(*adr_pt) = Get_RightX(rect);
    if (dir == Top || dir == Top_Left || dir == Top_Right)
	Get_PtY(*adr_pt) = Get_TopY(rect);
    else if (dir == Bottom || dir == Bottom_Left || dir == Bottom_Right)
	Get_PtY(*adr_pt) = Get_BottomY(rect);
    

    if (Tilwin_Is_Open(twinp) == TRUE){
        Gravity_Insert_Edge(Get_LeftX(grect), Left);
        Gravity_Insert_Edge(Get_RightX(grect), Right);
        Gravity_Insert_Edge(Get_TopY(grect), Top);
        Gravity_Insert_Edge(Get_BottomY(grect), Bottom);
    }

    return(TRUE);

}

#define SWAP_VALUE(option, value, hold)\
    {\
	hold = Tilwin_Get_Window_Option(winp, option);\
	Tilwin_Set_Window_Option(winp, option, value);\
    }

bool
Tilwin_Resize(winp, siz, dir)
    Tilwinp winp;
    Size siz;
    Side dir;
{
    Tilwin *twinp = (Tilwin *)winp;
    TWRectangle rect, 
	      desired_rect, 
	      current_rect;
    TWPoint best_pt, 
          pt;
    Side width_side, 
	 height_side;
    bool fixed_width, fixed_height, 
	 old_left, old_right, old_top, old_bottom, 
	 ret_val;
    Size size, 
	 org_size;
	 

    /* check to make sure siz width and height are even */
    if (Is_Odd_Number(Get_Width(siz)) == TRUE)
        Get_Width(siz)--;
    if (Is_Odd_Number(Get_Height(siz)) == TRUE)
        Get_Height(siz)--;

    rect = Tilwin_Get_Rectangle(twinp);
    
    switch (dir){
        case Left:
            Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(siz) - 1);
        break;
        case Right:
            Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(siz) - 1);
        break;
        case Top:
            Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(siz) - 1);
        break;
        case Bottom:
            Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(siz) - 1);
        break;
        case Top_Left:
            Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(siz) - 1);
            Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(siz) - 1);
        break;
        case Top_Right:
            Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(siz) - 1);
            Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(siz) - 1);
        break;
        case Bottom_Left:
            Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(siz) - 1);
            Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(siz) - 1);
        break;
        case Bottom_Right:
            Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(siz) - 1);
            Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(siz) - 1);
        break;
        default:
            return(FALSE);
    }

    width_side = height_side = NoSide;
    
    /* check horizontal rectangle */
    if (dir != Top && dir != Bottom){
        fixed_width = Tilwin_Get_Window_Option(twinp, FIXED_SIZE) ||
		      Tilwin_Get_Window_Option(twinp, FIXED_WIDTH);

	/* check to make sure the point is on the desktop */
	if (Get_LeftX(rect) < Get_LeftX(desktop_rect)){
	    if (fixed_width)
		return(FALSE);
	    else
		Get_LeftX(rect) = Get_LeftX(desktop_rect);
	}
	else if (Get_RightX(rect) > Get_RightX(desktop_rect)){
	    if (fixed_width)
		return(FALSE);
	    else
		Get_RightX(rect) = Get_RightX(desktop_rect);
	}
		
        /* compute the horizontal rectangle of the resized window */
	if (dir == Left || dir == Top_Left || dir == Bottom_Left){
	    width_side = Left;
	}
	else if (dir == Right || dir == Top_Right || dir == Bottom_Right){
	    width_side = Right;
	}

	/* if the width is fixed and that width does not satisfy min/max
	 * requirements, fail
	 */
	if (fixed_width == TRUE){
	    COMPUTE_SIZE(rect, size);
	    org_size = size;
	    if (Trial_Satisfied(twinp, &size) == FALSE)
		if (Get_Width(size) != Get_Width(org_size))
		    return(FALSE);
	}
	/* else call Trial_Place to adjust the new point wrt gravity and make
	 * sure the windows min/max are satisfied
	 */
	else{
	    (void) Trial_Place(&rect, width_side, Tilwin_Get_Min(twinp), 
							 Tilwin_Get_Max(twinp));
	    /* make sure that adjustments did not push the rectangle off of the
	     * desktop
	     */
	    if (Get_LeftX(rect) < Get_LeftX(desktop_rect) ||
		Get_RightX(rect) > Get_RightX(desktop_rect))
		    return(FALSE);

	    if (width_side == Left)
		Get_PtX(pt) = Get_LeftX(rect);
	    else
		Get_PtX(pt) = Get_RightX(rect);
	}
    }    

    /* check vertical rectangle */
    if (dir != Left && dir != Right){
        fixed_height = Tilwin_Get_Window_Option(twinp, FIXED_SIZE) ||
		      Tilwin_Get_Window_Option(twinp, FIXED_HEIGHT);
	/* check to make sure the point is on the desktop */
	if (Get_TopY(rect) < Get_TopY(desktop_rect)){
	    if (fixed_height)
		return(FALSE);
	    else
		Get_TopY(rect) = Get_TopY(desktop_rect);
	}
	else if (Get_BottomY(rect) > Get_BottomY(desktop_rect)){
	    if (fixed_height)
		return(FALSE);
	    else
		Get_BottomY(rect) = Get_BottomY(desktop_rect);
	}
		
        /* compute the vertical rectangle of the resized window */
	if (dir == Top || dir == Top_Left || dir == Top_Right){
	    height_side = Top;
	}
	else if (dir == Bottom || dir == Bottom_Left || dir == Bottom_Right){
	    height_side = Bottom;
	}

	/* if the height is fixed and that height does not satisfy min/max
	 * requirements, fail
	 */
	if (fixed_height == TRUE){
	    COMPUTE_SIZE(rect, size);
	    org_size = size;
	    if (Trial_Satisfied(twinp, &size) == FALSE)
		if (Get_Height(size) != Get_Height(org_size))
		    return(FALSE);
	}
	/* else call Trial_Place to adjust the new point wrt gravity and make
	 * sure the windows min/max are satisfied
	 */
	else{
	    (void) Trial_Place(&rect, height_side, Tilwin_Get_Min(twinp), 
							 Tilwin_Get_Max(twinp));
	    /* make sure that adjustments did not push the rectangle off of the
	     * desktop
	     */
	    if (Get_TopY(rect) < Get_TopY(desktop_rect) ||
		Get_BottomY(rect) > Get_BottomY(desktop_rect))
		    return(FALSE);

	    if (height_side == Top)
		Get_PtY(pt) = Get_TopY(rect);
	    else
		Get_PtY(pt) = Get_BottomY(rect);
	}
    }

    desired_rect = rect;	/* rectangle to be used if we are to an open */
    current_rect = Tilwin_Get_Rectangle(twinp);	 /* rectangle for resizes */
    best_pt = pt;

    switch (dir) {
    case Left:
	/* if the size or width is fixed, we are in an "all or nothing" case,
	 * therefore just do an open
	 */
	if (fixed_width == TRUE)
		ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp());
	/* else try to resize in the specified direction the window as much 
	 * as possible 
	 */
	else{
            (void) Trial_Grow(twinp, current_rect, dir, &best_pt, State_Get_Timestamp());
            Get_LeftX(current_rect) = Get_PtX(best_pt);
            (void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
            ret_val = TRUE;
        }
	/* if we were successful, commit the operation */
	if (ret_val == TRUE)
	    Commit_Operation(twinp);
	break;
    case Right:
	if (fixed_width == TRUE)
		ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp());
	else{
            (void) Trial_Grow(twinp, current_rect, dir, &best_pt, State_Get_Timestamp());
            Get_RightX(current_rect) = Get_PtX(best_pt);
            (void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
            ret_val = TRUE;
        }
	if (ret_val == TRUE)
	    Commit_Operation(twinp);
	break;
    case Top:
	if (fixed_height == TRUE)
		ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp());
	else{
            (void) Trial_Grow(twinp, current_rect, dir, &best_pt, State_Get_Timestamp());
            Get_TopY(current_rect) = Get_PtY(best_pt);
            (void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
            ret_val = TRUE;
        }
	if (ret_val == TRUE)
	    Commit_Operation(twinp);
	break;		
    case Bottom:
	if (fixed_height == TRUE)
		ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp());
	else{
            (void) Trial_Grow(twinp, current_rect, dir, &best_pt, State_Get_Timestamp());
            Get_BottomY(current_rect) = Get_PtY(best_pt);
            (void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
            ret_val = TRUE;
        }
	if (ret_val == TRUE)
	    Commit_Operation(twinp);
	break;		
    case Top_Left:
	/* if the width and height are both TRUE, do an open */
	if (fixed_width == TRUE && fixed_height == TRUE){
	    if ((ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp())) == TRUE)
		Commit_Operation(twinp);
	}
	/* else if just the width is fixed, do an open on the width and, if
	 * this succeeds, do a resize on the height */
	else if (fixed_width == TRUE){
	    Get_LeftX(current_rect) = Get_LeftX(desired_rect);
	    if ((ret_val = Trial_Open(twinp, current_rect, State_Get_Timestamp())) == TRUE){
		(void) Trial_Grow(twinp, current_rect, Top, &best_pt, State_Get_Timestamp());
		Get_TopY(current_rect) = Get_PtY(best_pt);
		(void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
		Commit_Operation(twinp);
	    }
	}
	/* else if just the height is fixed, do an open on the height and, if 
	 * this succeeds, do a resize on the width */
	else if (fixed_height == TRUE){
	    Get_TopY(current_rect) = Get_TopY(desired_rect);
	    if ((ret_val = Trial_Open(twinp, current_rect, State_Get_Timestamp())) == TRUE){
		(void) Trial_Grow(twinp, current_rect, Left, &best_pt, State_Get_Timestamp());
		Get_LeftX(current_rect) = Get_PtX(best_pt);
		(void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
		Commit_Operation(twinp);
	    }
	}
	/* else neither direction is fixed, so try to do an open to resize the
	 * window, if this fails use Open_Best_In_Area */
	else{
	    if ((ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp())) == TRUE)
		Commit_Operation(twinp);
	    else{
	        SWAP_VALUE(FIXED_LEFT_EDGE, FALSE, old_left);
		SWAP_VALUE(FIXED_RIGHT_EDGE, TRUE, old_right);
		SWAP_VALUE(FIXED_TOP_EDGE, FALSE, old_top);
		SWAP_VALUE(FIXED_BOTTOM_EDGE, TRUE, old_bottom);
		COMPUTE_SIZE(rect, size);
		if ((ret_val = Tilwin_Open_Best_In_Area(winp, desired_rect, size)) == TRUE)
		    Commit_Operation(twinp);
	        SWAP_VALUE(FIXED_LEFT_EDGE, old_left, old_left);
		SWAP_VALUE(FIXED_RIGHT_EDGE, old_right, old_right);
		SWAP_VALUE(FIXED_TOP_EDGE, old_top, old_top);
		SWAP_VALUE(FIXED_BOTTOM_EDGE, old_bottom, old_bottom);
	    }
	}
        break;
    case Top_Right:
	/* if the width and height are both TRUE, do an open */
	if (fixed_width == TRUE && fixed_height == TRUE){
	    if ((ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp())) == TRUE)
		Commit_Operation(twinp);
	}
	/* else if just the width is fixed, do an open on the width and, if
	 * this succeeds, do a resize on the height */
	else if (fixed_width == TRUE){
	    Get_RightX(current_rect) = Get_RightX(desired_rect);
	    if ((ret_val = Trial_Open(twinp, current_rect, State_Get_Timestamp())) == TRUE){
		(void) Trial_Grow(twinp, current_rect, Top, &best_pt, State_Get_Timestamp());
		Get_TopY(current_rect) = Get_PtY(best_pt);
		(void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
		Commit_Operation(twinp);
	    }
	}
	/* else if just the height is fixed, do an open on the height and, if 
	 * this succeeds, do a resize on the width */
	else if (fixed_height == TRUE){
	    Get_TopY(current_rect) = Get_TopY(desired_rect);
	    if ((ret_val = Trial_Open(twinp, current_rect, State_Get_Timestamp())) == TRUE){
		(void) Trial_Grow(twinp, current_rect, Right, &best_pt, State_Get_Timestamp());
		Get_RightX(current_rect) = Get_PtX(best_pt);
		(void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
		Commit_Operation(twinp);
	    }
	}
	/* else neither direction is fixed, so try to do an open to resize the
	 * window, if this fails use Open_Best_In_Area */
	else{
	    if ((ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp())) == TRUE)
		Commit_Operation(twinp);
	    else{
	        SWAP_VALUE(FIXED_LEFT_EDGE, TRUE, old_left);
		SWAP_VALUE(FIXED_RIGHT_EDGE, FALSE, old_right);
		SWAP_VALUE(FIXED_TOP_EDGE, FALSE, old_top);
		SWAP_VALUE(FIXED_BOTTOM_EDGE, TRUE, old_bottom);
		COMPUTE_SIZE(rect, size);
		if ((ret_val = Tilwin_Open_Best_In_Area(winp, desired_rect, size)) == TRUE)
		    Commit_Operation(twinp);
	        SWAP_VALUE(FIXED_LEFT_EDGE, old_left, old_left);
		SWAP_VALUE(FIXED_RIGHT_EDGE, old_right, old_right);
		SWAP_VALUE(FIXED_TOP_EDGE, old_top, old_top);
		SWAP_VALUE(FIXED_BOTTOM_EDGE, old_bottom, old_bottom);
	    }
	}
        break;
    case Bottom_Left:
	/* if the width and height are both TRUE, do an open */
	if (fixed_width == TRUE && fixed_height == TRUE){
	    if ((ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp())) == TRUE)
		Commit_Operation(twinp);
	}
	/* else if just the width is fixed, do an open on the width and, if
	 * this succeeds, do a resize on the height */
	else if (fixed_width == TRUE){
	    Get_LeftX(current_rect) = Get_LeftX(desired_rect);
	    if ((ret_val = Trial_Open(twinp, current_rect, State_Get_Timestamp())) == TRUE){
		(void) Trial_Grow(twinp, current_rect, Bottom, &best_pt, State_Get_Timestamp());
		Get_BottomY(current_rect) = Get_PtY(best_pt);
		(void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
		Commit_Operation(twinp);
	    }
	}
	/* else if just the height is fixed, do an open on the height and, if 
	 * this succeeds, do a resize on the width */
	else if (fixed_height == TRUE){
	    Get_BottomY(current_rect) = Get_BottomY(desired_rect);
	    if ((ret_val = Trial_Open(twinp, current_rect, State_Get_Timestamp())) == TRUE){
		(void) Trial_Grow(twinp, current_rect, Left, &best_pt, State_Get_Timestamp());
		Get_LeftX(current_rect) = Get_PtX(best_pt);
		(void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
		Commit_Operation(twinp);
	    }
	}
	/* else neither direction is fixed, so try to do an open to resize the
	 * window, if this fails use Open_Best_In_Area */
	else{
	    if ((ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp())) == TRUE)
		Commit_Operation(twinp);
	    else{
	        SWAP_VALUE(FIXED_LEFT_EDGE, FALSE, old_left);
		SWAP_VALUE(FIXED_RIGHT_EDGE, TRUE, old_right);
		SWAP_VALUE(FIXED_TOP_EDGE, TRUE, old_top);
		SWAP_VALUE(FIXED_BOTTOM_EDGE, FALSE, old_bottom);
		COMPUTE_SIZE(rect, size);
		if ((ret_val = Tilwin_Open_Best_In_Area(winp, desired_rect, size)) == TRUE)
		    Commit_Operation(twinp);
	        SWAP_VALUE(FIXED_LEFT_EDGE, old_left, old_left);
		SWAP_VALUE(FIXED_RIGHT_EDGE, old_right, old_right);
		SWAP_VALUE(FIXED_TOP_EDGE, old_top, old_top);
		SWAP_VALUE(FIXED_BOTTOM_EDGE, old_bottom, old_bottom);
	    }
	}
        break;
    case Bottom_Right:
	/* if the width and height are both TRUE, do an open */
	if (fixed_width == TRUE && fixed_height == TRUE){
	    if ((ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp())) == TRUE)
		Commit_Operation(twinp);
	}
	/* else if just the width is fixed, do an open on the width and, if
	 * this succeeds, do a resize on the height */
	else if (fixed_width == TRUE){
	    Get_RightX(current_rect) = Get_RightX(desired_rect);
	    if ((ret_val = Trial_Open(twinp, current_rect, State_Get_Timestamp())) == TRUE){
		(void) Trial_Grow(twinp, current_rect, Bottom, &best_pt, State_Get_Timestamp());
		Get_BottomY(current_rect) = Get_PtY(best_pt);
		(void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
		Commit_Operation(twinp);
	    }
	}
	/* else if just the height is fixed, do an open on the height and, if 
	 * this succeeds, do a resize on the width */
	else if (fixed_height == TRUE){
	    Get_BottomY(current_rect) = Get_BottomY(desired_rect);
	    if ((ret_val = Trial_Open(twinp, current_rect, State_Get_Timestamp())) == TRUE){
		(void) Trial_Grow(twinp, current_rect, Right, &best_pt, State_Get_Timestamp());
		Get_RightX(current_rect) = Get_PtX(best_pt);
		(void) Trial_Open(twinp, current_rect, State_Get_Timestamp());
		Commit_Operation(twinp);
	    }
	}
	/* else neither direction is fixed, so try to do an open to resize the
	 * window, if this fails use Open_Best_In_Area */
	else{
	    if ((ret_val = Trial_Open(twinp, desired_rect, State_Get_Timestamp())) == TRUE)
		Commit_Operation(twinp);
	    else{
	        SWAP_VALUE(FIXED_LEFT_EDGE, TRUE, old_left);
		SWAP_VALUE(FIXED_RIGHT_EDGE, FALSE, old_right);
		SWAP_VALUE(FIXED_TOP_EDGE, TRUE, old_top);
		SWAP_VALUE(FIXED_BOTTOM_EDGE, FALSE, old_bottom);
		COMPUTE_SIZE(rect, size);
		if ((ret_val = Tilwin_Open_Best_In_Area(winp, desired_rect, size)) == TRUE)
		    Commit_Operation(twinp);
	        SWAP_VALUE(FIXED_LEFT_EDGE, old_left, old_left);
		SWAP_VALUE(FIXED_RIGHT_EDGE, old_right, old_right);
		SWAP_VALUE(FIXED_TOP_EDGE, old_top, old_top);
		SWAP_VALUE(FIXED_BOTTOM_EDGE, old_bottom, old_bottom);
	    }
	}
        break;
    }

    return(ret_val);
}
