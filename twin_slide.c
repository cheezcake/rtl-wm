#ifndef lint
static char sccs_id[] = "@(#)twin_slide.c	5.3  9/1/88";
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
#include <stdio.h>



/****************************************************************************
  twin_slide.c: by Michael Berman
  RTL Windows System
  last modified: August 12, 1987
  reorganized; much of the guts moved to Trial_Slide_Nearest_In_Area.
  also, fixed bug where tile could slide outside area.
  version: 0.3
  
 ****************************************************************************/

#include "basetype.h"
#include "twinD.h"
#include "twin.h"
#include "trial.h"

#define SPLIT_RECT(r) r.left_x,r.top_y,r.right_x,r.bottom_y

#define ASSERT(a,m) \
{ \
    if (!(a)) \
    {\
	printf("YOW! %s \n",m);\
    }\
}

#define Is_XY_In_Rectangle(rect, x, y) \
        ((x <= Get_RightX(rect)) && (x >= Get_LeftX(rect)) && \
	 (y <= Get_BottomY(rect)) && (y >= Get_TopY(rect)))

#define Is_Rectangle_In_Rectangle(rect1, rect2) \
(Is_XY_In_Rectangle(rect2, Get_LeftX(rect1), Get_TopY(rect1)) && \
 Is_XY_In_Rectangle(rect2, Get_LeftX(rect1), Get_BottomY(rect1)) && \
 Is_XY_In_Rectangle(rect2, Get_RightX(rect1), Get_TopY(rect1)) && \
 Is_XY_In_Rectangle(rect2, Get_RightX(rect1), Get_BottomY(rect1))) 

bool Tilwin_Slide_Farthest_In_Area();


/****************************************************************************
  TILWIN SLIDE NEAREST

  Versions:
        Tilwin_Slide_Nearest
	Tilwin_Slide_Nearest_In_Area
	Tilwin_Slide_Vert_Near_In_Area
	Tilwin_Slide_Horiz_Near_In_Area
	Tilwin_Slide_Farthest
	Tilwin_Slide_Farthest_In_Area

  Problem: Given a pointer to a window, and a point in an area,
	attempt to slide the window as close to the point as possible.
	The point passed may be outside the area; if so, map it into the
	area.  Then open the window.

  Arguments:
  	winp: pointer to open window that will slide
	rect: area within which to slide
	pt:   point to slide towards

  Modifies:
  	This routine changes the center and the rectangle for the
	sliding window to reflect its final position, and opens the window.

  Description:
        First, adjust the pt to make it within the area.
	Then, call Trial_Slide_Nearest_In_Area to do the actual sliding.
	Finally, open the window.

  ****************************************************************************/

bool Tilwin_Slide_Farthest(winp, pt)
    Tilwin *winp;
    TWPoint pt;
{
    TWRectangle Desktop;
    
    Desktop = Tilwin_Get_Desktop_Rectangle();
    return Tilwin_Slide_Farthest_In_Area(winp, Desktop, pt);
}


bool Tilwin_Slide_Farthest_In_Area(winp, rect, pt)
    Tilwin *winp;
    TWRectangle rect;
    TWPoint pt;
    /* PRECONDITIONS: 1. winp must be in rect          
          2. pt must be in rect.                       
          3. pt, winp, and rect must be on the Desktop.
       Given a winp and a point, slide the window as far from 
       point as possible, in area rect. 
       Note that if the point is equal to the center of the 
       window, it doesn't really slide to the farthest, but 
       instead always slides down and to the right.  This   
       could be fixed by adding a special case.             

       In order to make this do a better job of "clearing out" an
       area, the following heuristic was added: always slide first
       in the direction that the rectangle is already farthest from
       pt.  Since Tilwin_Slide_Nearest always tries to slide
       horizontally first, do an explicit vertical slide if required
       by this heuristic, then call Slide_Nearest. */

{
    TWPoint corner, WindowCenter;

    /* Determine the quadrant in which the window is contained,
       select corner farthest away, then slide near it.         */
    COMPUTE_CENTER(Tilwin_Get_Rectangle(winp), WindowCenter);
    Get_PtX(corner) = (Get_PtX(WindowCenter) < Get_PtX(pt))?
	Get_LeftX(rect) : Get_RightX(rect);
    Get_PtY(corner) = (Get_PtY(WindowCenter) < Get_PtY(pt))?
	Get_TopY(rect) : Get_BottomY(rect);
    if (ABS(Get_PtY(WindowCenter) - Get_PtY(pt)) >
	ABS(Get_PtX(WindowCenter) - Get_PtX(pt)))
	Tilwin_Slide_Vert_Near_In_Area(winp, rect, corner);
    return Tilwin_Slide_Nearest_In_Area(winp, rect, corner);
}

	
    
 
bool
Tilwin_Slide_Nearest(winp, pt)
    Tilwin *winp;
    TWPoint pt;
{
    TWRectangle Desktop;

    Desktop = Tilwin_Get_Desktop_Rectangle();
    return Tilwin_Slide_Nearest_In_Area(winp, Desktop, pt);
}

bool
Tilwin_Slide_Nearest_In_Area(winp, rect, pt)
    Tilwin *winp;
    TWRectangle rect;
    TWPoint pt;
{
    TWRectangle try, check_rect;
    TWPoint cntr, slide_to_pt, open_cntr;
    Size sz;
    
    sz = Tilwin_Get_Size(winp);
    
    /* decide where we *really* want to slide to -- has to be within */
    /* rect area.                                                    */
    /* make a rectangle of the appropriate size, centered on the pt, */
    /* and check whether it lies within the area.                    */
    MAKE_RECTANGLE(pt, sz, check_rect);
    if (!Is_Rectangle_In_Rectangle(check_rect,rect))
    {
	if (Get_LeftX(check_rect) < Get_LeftX(rect)) 
	{
	    Get_LeftX(check_rect) = Get_LeftX(rect);
	    Get_RightX(check_rect) =
		Get_LeftX(check_rect) + (Get_Width(sz) - 1);
	}
	else if (Get_RightX(check_rect) > Get_RightX(rect))
	{
	    Get_RightX(check_rect) = Get_RightX(rect);
	    Get_LeftX(check_rect) =
		Get_RightX(check_rect) - (Get_Width(sz) - 1);
	}
	if (Get_TopY(check_rect) < Get_TopY(rect))
	{
	    Get_TopY(check_rect) = Get_TopY(rect);
	    Get_BottomY(check_rect) =
		Get_TopY(check_rect) + (Get_Height(sz) - 1);
	}
	else if (Get_BottomY(check_rect) > Get_BottomY(rect))
	{
	    Get_BottomY(check_rect) = Get_BottomY(rect);
	    Get_TopY(check_rect) =
		Get_BottomY(check_rect) - (Get_Height(sz) - 1);
	}
	ASSERT(!((Get_LeftX(check_rect) < Get_LeftX(rect)) &&
		 (Get_RightX(check_rect) > Get_RightX(rect))),
	       "rectangle can't fit (horiz) in area!");
	ASSERT(!((Get_TopY(check_rect) < Get_TopY(rect)) &&
		 (Get_BottomY(check_rect) > Get_BottomY(rect))),
	       "rectangle can't fit (vert) in area!");
	COMPUTE_CENTER(check_rect, slide_to_pt);
    }
    else
	slide_to_pt = pt;
    try = Tilwin_Get_Rectangle(winp);
    cntr = Tilwin_Get_Center(winp);

    open_cntr = Trial_Slide_Nearest_In_Area(try, rect, cntr, slide_to_pt, sz);
    return Tilwin_Open((Tilwinp)winp, open_cntr, Tilwin_Get_Size(winp));
}

bool
Tilwin_Slide_Horiz_Near_In_Area(winp, rect, pt)
    Tilwin *winp;
    TWRectangle rect;
    TWPoint pt;
{
    TWRectangle try, check_rect;
    TWPoint cntr, slide_to_pt, open_cntr;
    Size sz;
    
    sz = Tilwin_Get_Size(winp);
    
    /* decide where we *really* want to slide to -- has to be within */
    /* rect area.                                                    */
    /* make a rectangle of the appropriate size, centered on the pt, */
    /* and check whether it lies within the area.                    */
    MAKE_RECTANGLE(pt, sz, check_rect);
    if (!Is_Rectangle_In_Rectangle(check_rect,rect))
    {
	if (Get_LeftX(check_rect) < Get_LeftX(rect)) 
	{
	    Get_LeftX(check_rect) = Get_LeftX(rect);
	    Get_RightX(check_rect) =
		Get_LeftX(check_rect) + (Get_Width(sz) - 1);
	}
	else if (Get_RightX(check_rect) > Get_RightX(rect))
	{
	    Get_RightX(check_rect) = Get_RightX(rect);
	    Get_LeftX(check_rect) =
		Get_RightX(check_rect) - (Get_Width(sz) - 1);
	}
	ASSERT(!((Get_LeftX(check_rect) < Get_LeftX(rect)) &&
		 (Get_RightX(check_rect) > Get_RightX(rect))),
	       "rectangle can't fit (horiz) in area!");
	COMPUTE_CENTER(check_rect, slide_to_pt);
    }
    else
	slide_to_pt = pt;
    try = Tilwin_Get_Rectangle(winp);
    cntr = Tilwin_Get_Center(winp);

    open_cntr =
	Trial_Slide_Nearest_Horizontal(try, rect, cntr, slide_to_pt, sz);
    return Tilwin_Open((Tilwinp)winp, open_cntr, Tilwin_Get_Size(winp));
}
bool
Tilwin_Slide_Vert_Near_In_Area(winp, rect, pt)
    Tilwin *winp;
    TWRectangle rect;
    TWPoint pt;
{
    TWRectangle try, check_rect;
    TWPoint cntr, slide_to_pt, open_cntr;
    Size sz;
    
    sz = Tilwin_Get_Size(winp);
    
    /* decide where we *really* want to slide to -- has to be within */
    /* rect area.                                                    */
    /* make a rectangle of the appropriate size, centered on the pt, */
    /* and check whether it lies within the area.                    */
    MAKE_RECTANGLE(pt, sz, check_rect);
    if (!Is_Rectangle_In_Rectangle(check_rect,rect))
    {
	if (Get_TopY(check_rect) < Get_TopY(rect))
	{
	    Get_TopY(check_rect) = Get_TopY(rect);
	    Get_BottomY(check_rect) =
		Get_TopY(check_rect) + (Get_Height(sz) - 1);
	}
	else if (Get_BottomY(check_rect) > Get_BottomY(rect))
	{
	    Get_BottomY(check_rect) = Get_BottomY(rect);
	    Get_TopY(check_rect) =
		Get_BottomY(check_rect) - (Get_Height(sz) - 1);
	}
	ASSERT(!((Get_TopY(check_rect) < Get_TopY(rect)) &&
		 (Get_BottomY(check_rect) > Get_BottomY(rect))),
	       "rectangle can't fit (vert) in area!");
	COMPUTE_CENTER(check_rect, slide_to_pt);
    }
    else
	slide_to_pt = pt;
    try = Tilwin_Get_Rectangle(winp);
    cntr = Tilwin_Get_Center(winp);

    open_cntr = Trial_Slide_Nearest_Vertical(try, rect, cntr, slide_to_pt, sz);
    return Tilwin_Open((Tilwinp)winp, open_cntr, Tilwin_Get_Size(winp));
}
