#ifndef lint
static char sccs_id[] = "@(#)commit_op.c	5.3  9/1/88";
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
#include "state.h"
#include "tile.h"
#include "win.h"

void
Commit_Operation(winp)
	Tilwin	*winp;
{
	Tilwin	*mod_winp;
	Basetype shrink_coord;
	Side side;
	TWRectangle rect, 
                    current_rect, 
		    new_rect;
	WinpHandle handle;
	
        /* Check for no-op
         */
        current_rect = Tilwin_Get_Rectangle(winp);
	new_rect = Tilwin_Get_Modify_Rectangle(winp);
	if (Get_LeftX(current_rect) == Get_LeftX(new_rect) &&
	    Get_RightX(current_rect) == Get_RightX(new_rect) &&
	    Get_TopY(current_rect) == Get_TopY(new_rect) &&
	    Get_BottomY(current_rect)==Get_BottomY(new_rect) &&
	    Tilwin_Is_Open(winp) == TRUE){
                        /* DON'T need to mark this window as just modified
                         * for the interface code
                         */
            	        return;
        }
	
	/*  Close Windows needing Closing...
	 */
	handle = State_Gen_Potentially_Closed();

	while ( (mod_winp = State_Coerce(handle)) != WINP_NULL )
	{
		State_Auto_Close((Tilwin *) mod_winp);
		Win_Close(mod_winp);
		Tilwin_Was_Automatically_Closed(mod_winp) = TRUE;
		State_Next_Window(&handle);
	}

	/*  "mark" Windows which were Modified...
	 */
	handle = State_Gen_Potentially_Modfd();

	while ( (mod_winp = State_Coerce(handle)) != WINP_NULL )
	{

		State_Open((Tilwin *) mod_winp);
		
		if (Tilwin_Get_Modify_Side(mod_winp) == Left)
		{
			shrink_coord = Get_LeftX( Tilwin_Get_Modify_Rectangle(mod_winp) );
		}
		else if (Tilwin_Get_Modify_Side(mod_winp) == Right)
		{
			shrink_coord = Get_RightX( Tilwin_Get_Modify_Rectangle(mod_winp) );
		}
		else if (Tilwin_Get_Modify_Side(mod_winp) == Top)
		{
			shrink_coord = Get_TopY( Tilwin_Get_Modify_Rectangle(mod_winp) );
		}
		else  /* (Tilwin_Get_Modify_Side(mod_winp) == Bottom) */
		{
			shrink_coord = Get_BottomY( Tilwin_Get_Modify_Rectangle(mod_winp) );
		}

		Win_Shrink(mod_winp, Tilwin_Get_Modify_Side(mod_winp),
			    shrink_coord);

		State_Next_Window(&handle);

	}

	side = Tilwin_Get_Modify_Side(winp);
	new_rect = Tilwin_Get_Modify_Rectangle(winp);
	rect = Tilwin_Get_Rectangle(winp);

        /* if the window is currently opened and the side is NoSide, then we are
         * doing a reopen so first we should close the window
	 */
        if (side == NoSide && Tilwin_Is_Open(winp) == TRUE)
            Win_Close(winp);

	State_Open((Tilwin *) winp);
    
	/* if side == NoSide we are doing a (re)open */
	if (side == NoSide)
	    Win_Open(winp, new_rect);
	/* else we are doing a resize */
	else{
	    /* shrink all sides which need to be shrunk */
	    if (side == Left || side == Top_Left || side == Bottom_Left){
		if (Get_LeftX(rect) < Get_LeftX(new_rect))
		    Win_Shrink(winp, Left, Get_LeftX(new_rect));
	    }
	    else if (side == Right || side == Top_Right || side == Bottom_Right){
		if (Get_RightX(rect) > Get_RightX(new_rect))
		    Win_Shrink(winp, Right, Get_RightX(new_rect));
	    }
	    if (side == Top || side == Top_Right || side == Top_Left){
		if (Get_TopY(rect) < Get_TopY(new_rect))
		    Win_Shrink(winp, Top, Get_TopY(new_rect));
	    }
	    else if (side == Bottom || side == Bottom_Right || side == Bottom_Left){
		if (Get_BottomY(rect) > Get_BottomY(new_rect))
		     Win_Shrink(winp, Bottom, Get_BottomY(new_rect));
	    }

	    /* enlarge all sides which need to be enlarged */
	    if (side == Left || side == Top_Left || side == Bottom_Left){
		if (Get_LeftX(rect) > Get_LeftX(new_rect))
		    Win_Enlarge(winp, Left, Get_LeftX(new_rect));
	    }
	    else if (side == Right || side == Top_Right || side == Bottom_Right){
		if (Get_RightX(rect) < Get_RightX(new_rect))
		    Win_Enlarge(winp, Right, Get_RightX(new_rect));
	    }
    
	    if (side == Top || side == Top_Right || side == Top_Left){
		if (Get_TopY(rect) > Get_TopY(new_rect))
		    Win_Enlarge(winp, Top, Get_TopY(new_rect));
	    }
	    else if (side == Bottom || side == Bottom_Right || side == Bottom_Left){
		if (Get_BottomY(rect) < Get_BottomY(new_rect))
		    Win_Enlarge(winp, Bottom, Get_BottomY(new_rect));
	    }
    }

}
