
#ifndef lint
static char sccs_id[] = "@(#)check_mod.c	5.3  9/1/88";
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

extern Side Check_Shrink();

/*	Can we Modify the window 'winp' overlapped
 *	by 'area'?
 *	MODIFIES window 'shrink_size' and 'modify_rect'.
 */
bool
Check_Can_Modify(winp, area, growing_direction, bestp, win_stamp, close_stamp)
	Tilwin		*winp;
	TWRectangle	area;
	Side		growing_direction;
	Basetype	*bestp;
	TimeStamp	win_stamp,	/* the timestamp of the window trying
					 * to affect winp */
			close_stamp;	/* a timestamp for which no windows
					 * more recent than should be closed */
{
	Size		new_size;
	TWRectangle	shrink_rect;
	Side		shrink_side;
	Basetype	best;
	bool		ret_val;
	
	/* don't need this (but just in case!) best = *bestp; */
	
	/*  Calculate the shrink rectangle
	 */
	shrink_rect = Tilwin_Get_Rectangle(winp);
	shrink_side = Check_Shrink(winp, &shrink_rect, area, win_stamp);

	Tilwin_Set_Modify_Rectangle(winp, shrink_rect);
	Tilwin_Set_Modify_Side(winp, shrink_side);

	if (Tilwin_Get_Modify_Side(winp) == NoSide){
	   /* window must be closed, check to see if it is OK to close it */
		if (((Tilwin_Get_Window_Option(winp, REQUIRE_MANUAL_CLOSE) == FALSE) &&
		    (Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_CLOSE) == TRUE) &&
		    ((Tilwin_Get_Global_Option(ALLOW_AUTO_CLOSE_MORE_RECENT) == TRUE) ||
		     (Tilwin_Get_Window_Timestamp(winp) <= win_stamp)) && 
		    (Tilwin_Get_Window_Timestamp(winp) <= close_stamp)))
                {
                    ret_val = TRUE;
		}
		else{	/* it is not cool to close this window */
		    Tilwin_Set_Modify_Rectangle(winp, Tilwin_Get_Rectangle(winp));
		    switch(growing_direction){
		    case Left:
			Tilwin_Set_Modify_Side(winp, Right);
		        if ((Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) == TRUE) &&
			    ((Tilwin_Get_Global_Option(ALLOW_AUTO_SHRINK_MORE_RECENT)) ||
			     (Tilwin_Get_Window_Timestamp(winp) <= win_stamp)) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_RIGHT_EDGE) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_WIDTH) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_SIZE) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_COMPLETELY) == FALSE)){
			    new_size = (Tilwin_Get_Global_Option(ENFORCE_MINIMUMS) ?
					Tilwin_Get_Min(winp) : Tilwin_Get_Absolute_Minimums());
			    Get_RightX(Tilwin_Get_Modify_Rectangle(winp)) = 
			     Get_LeftX(Tilwin_Get_Modify_Rectangle(winp))+(Get_Width(new_size) - 1);
			}
			best = Get_RightX(Tilwin_Get_Modify_Rectangle(winp)) + 1;
			ret_val = TRUE;
		        break;
		    case Right:
			Tilwin_Set_Modify_Side(winp, Left);
		        if ((Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) == TRUE) &&
			    ((Tilwin_Get_Global_Option(ALLOW_AUTO_SHRINK_MORE_RECENT)) ||
			     (Tilwin_Get_Window_Timestamp(winp) <= win_stamp)) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_LEFT_EDGE) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_WIDTH) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_SIZE) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_COMPLETELY) == FALSE)){
			    new_size = (Tilwin_Get_Global_Option(ENFORCE_MINIMUMS) ?
					Tilwin_Get_Min(winp) : Tilwin_Get_Absolute_Minimums());
			    Get_LeftX(Tilwin_Get_Modify_Rectangle(winp)) = 
			     Get_RightX(Tilwin_Get_Modify_Rectangle(winp))-(Get_Width(new_size) - 1);
			}
			best = Get_LeftX(Tilwin_Get_Modify_Rectangle(winp)) - 1;
			ret_val = TRUE;
		        break;
		    case Top:
		        if ((Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) == TRUE) &&
			    ((Tilwin_Get_Global_Option(ALLOW_AUTO_SHRINK_MORE_RECENT)) ||
			     (Tilwin_Get_Window_Timestamp(winp) <= win_stamp)) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_BOTTOM_EDGE) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_HEIGHT) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_SIZE) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_COMPLETELY) == FALSE)){
			    new_size = (Tilwin_Get_Global_Option(ENFORCE_MINIMUMS) ?
					Tilwin_Get_Min(winp) : Tilwin_Get_Absolute_Minimums());
			    Get_BottomY(Tilwin_Get_Modify_Rectangle(winp)) = 
			     Get_TopY(Tilwin_Get_Modify_Rectangle(winp))+(Get_Height(new_size) - 1);
			}
			best = Get_BottomY(Tilwin_Get_Modify_Rectangle(winp)) + 1;
			ret_val = TRUE;
		        break;
		    case Bottom:
			Tilwin_Set_Modify_Side(winp, Top);
		        if ((Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) == TRUE) &&
			    ((Tilwin_Get_Global_Option(ALLOW_AUTO_SHRINK_MORE_RECENT)) ||
			     (Tilwin_Get_Window_Timestamp(winp) <= win_stamp)) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_BOTTOM_EDGE) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_HEIGHT) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_SIZE) == FALSE) &&
			    (Tilwin_Get_Window_Option(winp, FIXED_COMPLETELY) == FALSE)){
			    new_size = (Tilwin_Get_Global_Option(ENFORCE_MINIMUMS) ?
					Tilwin_Get_Min(winp) : Tilwin_Get_Absolute_Minimums());
			    Get_TopY(Tilwin_Get_Modify_Rectangle(winp)) = 
			     Get_BottomY(Tilwin_Get_Modify_Rectangle(winp))-(Get_Height(new_size) - 1);
			}
			best = Get_TopY(Tilwin_Get_Modify_Rectangle(winp)) - 1;
			ret_val = TRUE;
		        break;
		    case NoSide:
			Tilwin_Set_Modify_Side(winp, NoSide);
			ret_val = FALSE;
		        break;
		    }
		}
        }
        else{   /* (Tilwin_Get_Modify_Side(winp) != NoSide) */
            ret_val = TRUE;
        }

	*bestp = best;
	return(ret_val);
}
