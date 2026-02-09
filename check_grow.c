
#ifndef lint
static char sccs_id[] = "@(#)check_grow.c	5.4  9/1/88";
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
#include "state.h"
#include "tile.h"
#include "win.h"

extern bool Check_Can_Modify();

bool
Check_Grow(winp, rect, side, ptp, stamp,
	   better, nclosed, nexpensive, naffected)
	Tilwin *winp;
	TWRectangle rect;
	Side side;
	TWPoint *ptp;
	TimeStamp stamp;
        bool better;
        int *nclosed;
        int *nexpensive;
        int *naffected;
{
	Tilwin *next_winp;
	bool ret_val = TRUE;
	WinpHandle handle;
	Basetype most, 
		 current_most;
	int now_closed = 0;
	int now_expensive = 0;
	int now_affected = 0;
	
	/*  Get a list of all Windows in the 'areap' area...
	 *  Determine for each Tilwin on the list, if it
	 *  can be Shrunk or Closed legally, per the Options.
	 *  If any Tilwin must be Closed or Shrunk in order to
	 *  Open the new Window, and cannot be, return failure.
	 */
	State_Potential_Clear();

	Tiles_In_Area(Get_LeftX(rect), Get_TopY(rect),
		      Get_RightX(rect), Get_BottomY(rect), 
		      Win_Add_List);

	if (side != NoSide)
	    current_most = ((side == Left || side == Right) ? 
		  	    Get_PtX(*ptp) : Get_PtY(*ptp));
	
    	handle = State_Gen_Potentially_Modfd();

	next_winp =  State_Coerce(handle);
	while (next_winp != WINP_NULL && ret_val == TRUE){

	    if (next_winp == winp){
		State_Remove_Potentially_Modfd(next_winp);
		State_Next_Window(&handle);
		next_winp = State_Coerce(handle);
		continue;
	    }

	    if (side != NoSide)
		most = ((side == Left || side == Right) ? 
		        Get_PtX(*ptp) : Get_PtY(*ptp));
	    
	    if (Check_Can_Modify(next_winp, rect, side, &most, 
				 Tilwin_Get_Window_Timestamp(winp), stamp) == FALSE){
		ret_val = FALSE;
	    }
	    else {
		switch (side) {
		case Left:
		case Top:
		    current_most = (current_most < most ? most : current_most );
		    break;
		case Right:
		case Bottom:
		    current_most = (current_most > most ? most : current_most);
		     break;
		case NoSide:
		    if (Tilwin_Get_Modify_Side(next_winp) == NoSide)
		    {
			now_closed++;
			if (better == TRUE)
			{
			    if (now_closed >= *nclosed)
				ret_val = FALSE;
			}
			else
			{
			    if (now_closed > *nclosed)
				ret_val = FALSE;
			}
		    }
		    else if (Tilwin_Get_Window_Option(next_winp,
						      EXPENSIVE_TO_REDRAW)
			     == TRUE)
		    {
			now_expensive++;
			if (better == TRUE)
			{
			    if ((now_closed == *nclosed) &&
				(now_expensive >= *nexpensive))
				ret_val = FALSE;
			}
			else
			{
			    if((now_closed == *nclosed) &&
			       (now_expensive > *nexpensive))
				ret_val = FALSE;
			}
		    }
		    now_affected++;
		    if (better == TRUE)
		    {
			if ((now_closed == *nclosed) &&
			    (now_expensive == *nexpensive) &&
			    (now_affected >= *naffected))
			    ret_val = FALSE;
		    }
		    else
		    {
			if ((now_closed == *nclosed) &&
			    (now_expensive == *nexpensive) &&
			    (now_affected > *naffected))
			    ret_val = FALSE;
		    }
		    break;
		}
	    }
		
	    /* if the window is to be closed, place it on the appropriate list */
	    if (Tilwin_Get_Modify_Side(next_winp) == NoSide) {
		    State_Remove_Potentially_Modfd(next_winp);
		    State_Insert_Potentially_Closed(next_winp);
	    }
	    
	    State_Next_Window(&handle);
	    next_winp =  State_Coerce(handle);

            /* NOTE:  we can improve this algorithm by exploiting the fact that
             * the new value of current_most may change rect so that a window
             * which was before overlapped by rect is no longer overlapped.
             * We need not call Check_Can_Modify on this window.  We leave
             * this improvement as an exercise to the reader.
             */
	}

	if (ret_val == TRUE)
	{
	    if (side != NoSide)
		if (side == Left || side == Right)
		    Get_PtX(*ptp) = current_most;
		else
		    Get_PtY(*ptp) = current_most;
	    else
	    {
		*nclosed = now_closed;
		*nexpensive = now_expensive;
		*naffected = now_affected;
	    }
	}

	return (ret_val);
}
