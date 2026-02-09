#ifndef lint
static char sccs_id[] = "@(#)try_grow.c	5.4  9/1/88";
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
#include "trialP.h" 

extern bool Check_Grow();
extern bool Trial_Place();


/* NOTE: Trial_Grow does NOT check to make sure that the rect
 * satisfies the min/max/FIXED requirements of the window
 */

bool
Trial_Improve_Grow(winp, rect, side, ptp, stamp,
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
    TWRectangle extension_rect, 
	      crect, 
	      desk_rect;
    
    switch (side) {
    case Left:
	if (Is_Odd_Number(Get_PtX(*ptp)) == TRUE)
	    Get_PtX(*ptp)++;
        Get_LeftX(extension_rect) = Get_PtX(*ptp);
	Get_RightX(extension_rect) = Get_LeftX(rect) - 1;
	Get_TopY(extension_rect) = Get_TopY(rect);
	Get_BottomY(extension_rect) = Get_BottomY(rect);
        break;
    case Right:
	if (Is_Even_Number(Get_PtX(*ptp)) == TRUE)
	    Get_PtX(*ptp)--;
        Get_LeftX(extension_rect) = Get_RightX(rect) + 1;
	Get_RightX(extension_rect) = Get_PtX(*ptp);
	Get_TopY(extension_rect) = Get_TopY(rect);
	Get_BottomY(extension_rect) = Get_BottomY(rect);
        break;
    case Top:
	if (Is_Odd_Number(Get_PtY(*ptp)) == TRUE)
	    Get_PtY(*ptp)++;
        Get_LeftX(extension_rect) = Get_LeftX(rect);
	Get_RightX(extension_rect) = Get_RightX(rect);
	Get_TopY(extension_rect) = Get_PtY(*ptp);
	Get_BottomY(extension_rect) = Get_TopY(rect) - 1;
        break;
    case Bottom:
	if (Is_Even_Number(Get_PtY(*ptp)) == TRUE)
	    Get_PtY(*ptp)--;
        Get_LeftX(extension_rect) = Get_LeftX(rect);
	Get_RightX(extension_rect) = Get_RightX(rect);
	Get_TopY(extension_rect) = Get_BottomY(rect) + 1;
	Get_BottomY(extension_rect) = Get_PtY(*ptp);
        break;
    case NoSide:
        extension_rect = rect;
        break;
    default:
	/* stop right here if we have a bad side */
        return(FALSE);
        /* break; */
    }
    
    /* check to make sure rectangle is on the desktop */
    desk_rect = Tilwin_Get_Desktop_Rectangle();
    if (Get_LeftX(extension_rect) < Get_LeftX(desk_rect))
	Get_LeftX(extension_rect) = Get_LeftX(desk_rect);
    if (Get_RightX(extension_rect) > Get_RightX(desk_rect))
	Get_RightX(extension_rect) = Get_RightX(desk_rect);
    if (Get_TopY(extension_rect) < Get_TopY(desk_rect))
	Get_TopY(extension_rect) = Get_TopY(desk_rect);
    if (Get_BottomY(extension_rect) > Get_BottomY(desk_rect))
	Get_BottomY(extension_rect) = Get_BottomY(desk_rect);

    if (Check_Grow(winp, extension_rect, side, ptp, stamp,
		   better, nclosed, nexpensive, naffected) == FALSE)
	return(FALSE);

    switch (side) {
    case Left:
        Get_LeftX(rect) = Get_PtX(*ptp);
        break;
    case Right:
        Get_RightX(rect) = Get_PtX(*ptp);
        break;
    case Top:
        Get_TopY(rect) = Get_PtY(*ptp);
        break;
    case Bottom:
        Get_BottomY(rect) = Get_PtY(*ptp);
        break;
    case NoSide:
        /* do nothing! */
        break;
    }

    /* check to make sure we are doing work,  as of now we have
     * no modify side */
    Tilwin_Set_Modify_Side(winp, NoSide);
    Tilwin_Set_Modify_Rectangle(winp, rect);
    crect = Tilwin_Get_Rectangle(winp);
    switch (side) {
	case Left:
	    if (Get_LeftX(rect) == Get_LeftX(crect))
		return(TRUE);
            break;
        case Right:
            if (Get_RightX(rect) == Get_RightX(crect))
		return(TRUE);
            break;
        case Top:
            if (Get_TopY(rect) == Get_TopY(crect))
		return(TRUE);
            break;
        case Bottom:
            if (Get_BottomY(rect) == Get_BottomY(crect))
		return(TRUE);
            break;
	case NoSide:
	    if (Get_LeftX(rect) == Get_LeftX(crect) &&
		Get_RightX(rect) == Get_RightX(crect) &&
		Get_TopY(rect) == Get_TopY(crect) &&
		Get_BottomY(rect) == Get_BottomY(crect) &&
		Tilwin_Is_Open(winp) == TRUE)
		return(TRUE);
	    break;
    }
    
    Tilwin_Set_Modify_Side(winp, side);
    Tilwin_Set_Modify_Rectangle(winp, rect);
    return(TRUE);
}

bool 
Trial_Grow(winp, rect, side, ptp, stamp)
    Tilwin *winp;
    TWRectangle rect;
    Side side;
    TWPoint *ptp;
    TimeStamp stamp;
{
    int big = MUCHO_WINDOWS;

    return(Trial_Improve_Grow(winp, rect, side, ptp, stamp, FALSE,
			      &big, &big, &big));
}

bool
Trial_Open(winp, rect, stamp)
    Tilwin *winp;
    TWRectangle rect;
    TimeStamp stamp;
{
    int big = MUCHO_WINDOWS;

    return(Trial_Improve_Grow(winp, rect, NoSide, (TWPoint *) NULL,
			      stamp, FALSE, &big, &big, &big));
}
