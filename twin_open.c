#ifndef lint
static char sccs_id[] = "@(#)twin_open.c	5.3  9/1/88";
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
#include "gravity.h"
#include "win.h"

extern TWRectangle desktop_rect;

bool
Tilwin_Open(winp, location, size)
    Tilwinp winp;
    TWPoint location;
    Size size;
{
    Tilwin *twinp = (Tilwin *)winp;
    TWRectangle rect, 
	      current_rect, 
              grect,
	      arect;

    State_Start_Operation();
    
    /* if the window is open, remove it's edges from the gravity list
       so they don't interfere with the placement
     */
    if (Tilwin_Is_Open(twinp) == TRUE){
        grect = Tilwin_Get_Rectangle(twinp);
        Gravity_Delete_Edge(Get_LeftX(grect), Left);
        Gravity_Delete_Edge(Get_RightX(grect), Right);
        Gravity_Delete_Edge(Get_TopY(grect), Top);
        Gravity_Delete_Edge(Get_BottomY(grect), Bottom);
    }

    /* check to make sure size width and height are even */
    if (Is_Odd_Number(Get_Width(size)) == TRUE)
        Get_Width(size)--;
    if (Is_Odd_Number(Get_Height(size)) == TRUE)
        Get_Height(size)--;

    MAKE_RECTANGLE(location, size, rect);
    current_rect = Tilwin_Get_Rectangle(twinp);

    /* check to see if the rectangle given us (implicitly by the location and
     * size) satisfied fixed edge options
     */
    if (Tilwin_Get_Window_Option(twinp, FIXED_LEFT_EDGE) == TRUE){
        Get_LeftX(rect) = Get_LeftX(current_rect);
        Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(size) - 1);
	/* adjust for gravity (preserving min/max requirements) */
	(void) Trial_Place(&rect, Right, Tilwin_Get_Min(twinp), 
						Tilwin_Get_Max(twinp));
    }
    else if (Tilwin_Get_Window_Option(twinp, FIXED_RIGHT_EDGE) == TRUE){
        Get_RightX(rect) = Get_RightX(current_rect);
        Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(size) - 1);
	(void) Trial_Place(&rect, Left, Tilwin_Get_Min(twinp), 
					       Tilwin_Get_Max(twinp));
    }
    else{
	/* NOTE: Trail_Place adjusts both the width and the height of the
	 * rectangle when given a side of NoSide, 
	 * we are only interested in adjusting the width here
	 */
	arect = rect;
	(void) Trial_Place(&arect, NoSide, Tilwin_Get_Min(twinp), 
						Tilwin_Get_Max(twinp));
	Get_LeftX(rect) = Get_LeftX(arect);
	Get_RightX(rect) = Get_RightX(arect);
    }

    if (Tilwin_Get_Window_Option(twinp, FIXED_TOP_EDGE) == TRUE) {
        Get_TopY(rect) = Get_TopY(current_rect);
        Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(size) - 1);
	(void) Trial_Place(&rect, Bottom, Tilwin_Get_Min(twinp), 
						 Tilwin_Get_Max(twinp));
    }
    else if (Tilwin_Get_Window_Option(twinp, FIXED_BOTTOM_EDGE) == TRUE) {
        Get_BottomY(rect) = Get_BottomY(current_rect);
        Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(size) - 1);
	(void) Trial_Place(&rect, Top, Tilwin_Get_Min(twinp), 
					      Tilwin_Get_Max(twinp));
    }
    else{
	/* NOTE: Trail_Place adjusts both the width and the height of the
	 * rectangle when given a side of NoSide, 
	 * we are only interested in adjusting the height here
	 */
	arect = rect;
	(void) Trial_Place(&arect, NoSide, Tilwin_Get_Min(twinp), 
						Tilwin_Get_Max(twinp));
	Get_TopY(rect) = Get_TopY(arect);
	Get_BottomY(rect) = Get_BottomY(arect);
    }

    /* if the window is open, restore the edges to the gravity list */
    if (Tilwin_Is_Open(twinp) == TRUE) {
	Gravity_Insert_Edge(Get_LeftX(grect), Left);
	Gravity_Insert_Edge(Get_RightX(grect), Right);
	Gravity_Insert_Edge(Get_TopY(grect), Top);
	Gravity_Insert_Edge(Get_BottomY(grect), Bottom);
    }

    /* check to make sure rectangle is on the desktop, if not fail */
    if (Get_LeftX(rect) < Get_LeftX(desktop_rect) ||
	Get_RightX(rect) > Get_RightX(desktop_rect) ||
	Get_TopY(rect) < Get_TopY(desktop_rect) ||
	Get_BottomY(rect) > Get_BottomY(desktop_rect)) {
	return(FALSE);
    }
    
    /* try to open the window */
    if (Trial_Open(twinp, rect, State_Get_Timestamp()) == TRUE) {
	Commit_Operation(twinp);
	return(TRUE);
    }
    else  {
	return(FALSE);
    }
}

bool
Tilwin_Check_Corner_Open(winp, start_pt, adr_pt, corner, min_size, max_size)
    Tilwinp winp;
    TWPoint *start_pt;
    TWPoint *adr_pt;
    Side corner;
    Size min_size, 
	 max_size;
{
    Tilwin *twinp = (Tilwin *)winp;
    TWRectangle rect,
              grect;
    Side opp_corner;
    
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

    switch (corner) {
    case Top_Left:
	if (Tilwin_Get_Window_Option(twinp, FIXED_LEFT_EDGE) == TRUE)
	    Get_PtX(*start_pt) = Get_LeftX(Tilwin_Get_Rectangle(twinp));
	else
	    Get_PtX(*start_pt) = Gravity_Adjust_Edge(Get_PtX(*start_pt), Left);
	if (Tilwin_Get_Window_Option(twinp, FIXED_TOP_EDGE) == TRUE)
	    Get_PtY(*start_pt) = Get_TopY(Tilwin_Get_Rectangle(twinp));
	else
	    Get_PtY(*start_pt) = Gravity_Adjust_Edge(Get_PtY(*start_pt), Top);

        Get_LeftX(rect) = Get_PtX(*start_pt);
	Get_TopY(rect) = Get_PtY(*start_pt);
	Get_RightX(rect) = Get_PtX(*adr_pt);
	Get_BottomY(rect) = Get_PtY(*adr_pt);
	opp_corner = Bottom_Right;
        break;
    case Top_Right:
	if (Tilwin_Get_Window_Option(twinp, FIXED_RIGHT_EDGE) == TRUE)
	    Get_PtX(*start_pt) = Get_RightX(Tilwin_Get_Rectangle(twinp));
	else
	    Get_PtX(*start_pt) = Gravity_Adjust_Edge(Get_PtX(*start_pt), Right);
	if (Tilwin_Get_Window_Option(twinp, FIXED_TOP_EDGE) == TRUE)
	    Get_PtY(*start_pt) = Get_TopY(Tilwin_Get_Rectangle(twinp));
	else
	    Get_PtY(*start_pt) = Gravity_Adjust_Edge(Get_PtY(*start_pt), Top);

        Get_LeftX(rect) = Get_PtX(*adr_pt);
	Get_TopY(rect) = Get_PtY(*start_pt);
	Get_RightX(rect) = Get_PtX(*start_pt);
	Get_BottomY(rect) = Get_PtY(*adr_pt);
	opp_corner = Bottom_Left;
        break;
    case Bottom_Left:
	if (Tilwin_Get_Window_Option(twinp, FIXED_LEFT_EDGE) == TRUE)
	    Get_PtX(*start_pt) = Get_LeftX(Tilwin_Get_Rectangle(twinp));
	else
	    Get_PtX(*start_pt) = Gravity_Adjust_Edge(Get_PtX(*start_pt), Left);
	if (Tilwin_Get_Window_Option(twinp, FIXED_BOTTOM_EDGE) == TRUE)
	    Get_PtY(*start_pt) = Get_BottomY(Tilwin_Get_Rectangle(twinp));
	else
	    Get_PtY(*start_pt) = Gravity_Adjust_Edge(Get_PtY(*start_pt), Bottom);

        Get_LeftX(rect) = Get_PtX(*start_pt);
	Get_TopY(rect) = Get_PtY(*adr_pt);
	Get_RightX(rect) = Get_PtX(*adr_pt);
	Get_BottomY(rect) = Get_PtY(*start_pt);
	opp_corner = Top_Right;
        break;
    case Bottom_Right:
	if (Tilwin_Get_Window_Option(twinp, FIXED_RIGHT_EDGE) == TRUE)
	    Get_PtX(*start_pt) = Get_RightX(Tilwin_Get_Rectangle(twinp));
	else
	    Get_PtX(*start_pt) = Gravity_Adjust_Edge(Get_PtX(*start_pt), Left);
	if (Tilwin_Get_Window_Option(twinp, FIXED_BOTTOM_EDGE) == TRUE)
	    Get_PtY(*start_pt) = Get_BottomY(Tilwin_Get_Rectangle(twinp));
	else
	    Get_PtY(*start_pt) = Gravity_Adjust_Edge(Get_PtY(*start_pt), Bottom);

        Get_LeftX(rect) = Get_PtX(*adr_pt);
	Get_TopY(rect) = Get_PtY(*adr_pt);
	Get_RightX(rect) = Get_PtX(*start_pt);
	Get_BottomY(rect) = Get_PtY(*start_pt);
	opp_corner = Top_Left;
        break;
    }
    
    /* if the rectangle is changed by gravity and/or min/max adjustments,
     * reflect the changes in the given points.
     */
    (void) Trial_Place(&rect, opp_corner, min_size, max_size);
    switch (corner) {
	case Top_Left:
	    Get_PtX(*start_pt) = Get_LeftX(rect);
	    Get_PtY(*start_pt) = Get_TopY(rect);
	    Get_PtX(*adr_pt) = Get_RightX(rect);
	    Get_PtY(*adr_pt) = Get_BottomY(rect);
	    break;
	case Top_Right:
	    Get_PtX(*start_pt) = Get_RightX(rect);
	    Get_PtY(*start_pt) = Get_TopY(rect);
	    Get_PtX(*adr_pt) = Get_LeftX(rect);
	    Get_PtY(*adr_pt) = Get_BottomY(rect);	    
	    break;
	case Bottom_Left:
	    Get_PtX(*start_pt) = Get_LeftX(rect);
	    Get_PtY(*start_pt) = Get_BottomY(rect);
	    Get_PtX(*adr_pt) = Get_RightX(rect);
	    Get_PtY(*adr_pt) = Get_TopY(rect);	    
	    break;
	case Bottom_Right:
	    Get_PtX(*start_pt) = Get_RightX(rect);
	    Get_PtY(*start_pt) = Get_BottomY(rect);
	    Get_PtX(*adr_pt) = Get_LeftX(rect);
	    Get_PtY(*adr_pt) = Get_TopY(rect);	    
	    break;
    }

    if (Tilwin_Is_Open(twinp) == TRUE){
        Gravity_Insert_Edge(Get_LeftX(grect), Left);
        Gravity_Insert_Edge(Get_RightX(grect), Right);
        Gravity_Insert_Edge(Get_TopY(grect), Top);
        Gravity_Insert_Edge(Get_BottomY(grect), Bottom);
    }

    return(TRUE);
}

bool
Tilwin_Check_Center_Open(winp, adr_pt, sizep)
    Tilwinp winp;
    TWPoint *adr_pt;
    Size *sizep;
{
    Tilwin *twinp = (Tilwin *) winp;
    TWRectangle rect,
              grect;
    
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

    *sizep = Tilwin_Get_Size(twinp);
    (void) Trial_Satisfied(twinp, sizep);
    MAKE_RECTANGLE(*adr_pt, *sizep, rect);
    
    if (Tilwin_Get_Window_Option(twinp, FIXED_LEFT_EDGE) == TRUE){
	Get_LeftX(rect) = Get_LeftX(Tilwin_Get_Rectangle(twinp));
	Get_RightX(rect) = Get_LeftX(rect) + (Get_Width(*sizep) - 1);
    }
    else if (Tilwin_Get_Window_Option(twinp, FIXED_RIGHT_EDGE) == TRUE){
	Get_RightX(rect) = Get_RightX(Tilwin_Get_Rectangle(twinp));
	Get_LeftX(rect) = Get_RightX(rect) - (Get_Width(*sizep) - 1);
    }

    if (Tilwin_Get_Window_Option(twinp, FIXED_TOP_EDGE) == TRUE){
	Get_TopY(rect) = Get_TopY(Tilwin_Get_Rectangle(twinp));
	Get_BottomY(rect) = Get_TopY(rect) + (Get_Height(*sizep) - 1);
    }
    else if (Tilwin_Get_Window_Option(twinp, FIXED_BOTTOM_EDGE) == TRUE){
	Get_BottomY(rect) = Get_BottomY(Tilwin_Get_Rectangle(twinp));
	Get_TopY(rect) = Get_BottomY(rect) - (Get_Height(*sizep) - 1);
    }

    /* by using *sizep as both the min and the max we can adjust the rectangle
     * for gravity while holding the size fixed
     */
    (void) Trial_Place(&rect, NoSide, *sizep, *sizep);
    
    COMPUTE_CENTER(rect, *adr_pt);

    if (Tilwin_Is_Open(twinp) == TRUE){
        Gravity_Insert_Edge(Get_LeftX(grect), Left);
        Gravity_Insert_Edge(Get_RightX(grect), Right);
        Gravity_Insert_Edge(Get_TopY(grect), Top);
        Gravity_Insert_Edge(Get_BottomY(grect), Bottom);
    }

    return(TRUE);
}
