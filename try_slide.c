#ifndef lint
static char sccs_id[] = "@(#)try_slide.c	5.3  9/1/88";
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

/****************************************************************************
  try_slide.c: by Michael Berman
  RTL Windows System
  last modified: April 24, 1987
  most of this used to be in twin_slide.c
  version: 0.1
 ****************************************************************************/

#include "basetype.h"
#include "twinD.h"
#include "twin.h"
#include "trial.h"

#define MAX_TRIES 5
#define MAX_EQ(x,y) (((x) >= (y))? x:y)
#define MIN_EQ(x,y) (((x) <= (y))? x:y)
#define EqualPoints(a,b) \
    ((Get_PtX(a) == Get_PtX(b)) && (Get_PtY(a) == Get_PtY(b)))
    
TWPoint Trial_Slide_Nearest_Horizontal(), Trial_Slide_Nearest_Vertical();

/****************************************************************************
  TRIAL SLIDE NEAREST IN AREA

  Problem: Given a rectangle (representing a window), an area, the center
        of the rectangle, a prefered point, and the size of the rectangle,
	slide the center of the rectangle as close to the prefered point as
	is possible without leaving the area.  The center of the rectangle
	after the slide is returned.

  Arguments:
        try:   The rectangle to slide.
	area:  Slide within this area.
	cntr:  Center of the rectangle.
	pt:    Point to slide towards.  (PRECONDITION: pt is in area)
	sz:    The size of the try rectangle.
	
  Description:
        By successively sliding
	horizontally (either left or right) then vertically (either up
	or down) attempt to slide closer to pt.  Sliding means a move
	of the window that crosses space tiles only.  This is 
	a heuristic and won't always get to the best possible
	position.  Slide until either 1) we reach the goal position,
	or 2) we're stuck in one position.

 ****************************************************************************/ 

TWPoint Trial_Slide_Nearest_In_Area(try, area, cntr, pt, sz)
    TWRectangle try, area;
    TWPoint cntr, pt;
    Size sz;
{    
    bool stuck = FALSE, found = FALSE;
    TWPoint new_cntr;
    TWRectangle new_try;
    
    while (!found && !stuck)
    {
	new_cntr = Trial_Slide_Nearest_Horizontal(try, area, cntr, pt, sz);
	MAKE_RECTANGLE(new_cntr, sz, new_try);
	new_cntr = Trial_Slide_Nearest_Vertical(new_try, area, new_cntr, pt, sz);
	stuck = EqualPoints(cntr, new_cntr);
	found = EqualPoints(new_cntr, pt);
	cntr = new_cntr;
	MAKE_RECTANGLE(cntr, sz, try);
    }
    return cntr;
}    

TWPoint Trial_Slide_Nearest_Horizontal(try, area, cntr, pt, sz)
    TWRectangle try, area;
    TWPoint cntr, pt;
    Size sz;
{
    Basetype extent;
    TWPoint p1, p2;
    
    if (Get_PtX(pt) < Get_PtX(cntr))	/* Left */
    {
	Get_PtX(p1) = Get_PtX(p2) = Get_LeftX(try);
	Get_PtY(p1) = Get_TopY(try);
	Get_PtY(p2) = Get_BottomY(try);
	Trial_Edge_Sweep(p1,p2,Left,&extent);
	if (extent != Get_PtX(p1))
	{
	    /* check whether still in open area -- if not, pull back */
	    Get_LeftX(try) = MAX_EQ(extent, Get_LeftX(area));
	    Get_RightX(try) = Get_LeftX(try) + (Get_Width(sz) - 1);
	    /* check if past pt... */
	    COMPUTE_CENTER(try, cntr);
	    Get_PtX(cntr) = MAX_EQ(Get_PtX(cntr), Get_PtX(pt));
	    MAKE_RECTANGLE(cntr, sz, try);
	}
    }
    else if (Get_PtX(pt) > Get_PtX(cntr))	/* Right */
    {
	Get_PtX(p1) = Get_PtX(p2) = Get_RightX(try);
	Get_PtY(p1) = Get_TopY(try);
	Get_PtY(p2) = Get_BottomY(try);
	Trial_Edge_Sweep(p1,p2,Right,&extent);
	if (extent != Get_PtX(p1))
	{
	    /* check whether still in open area -- if not, pull back */
	    Get_RightX(try) = MIN_EQ(extent, Get_RightX(area));	
	    Get_LeftX(try) = Get_RightX(try) - (Get_Width(sz) - 1);
	    /* check if past pt... */
	    COMPUTE_CENTER(try, cntr);
	    Get_PtX(cntr) = MIN_EQ(Get_PtX(cntr), Get_PtX(pt));
	    MAKE_RECTANGLE(cntr, sz, try);
	}
    }
    return cntr;
}

TWPoint Trial_Slide_Nearest_Vertical(try, area, cntr, pt, sz)
    TWRectangle try, area;
    TWPoint cntr, pt;
    Size sz;
{
    Basetype extent;
    TWPoint p1, p2;
    
    if (Get_PtY(pt) < Get_PtY(cntr))	/* Top */
    {
	Get_PtY(p1) = Get_PtY(p2) = Get_TopY(try);
	Get_PtX(p1) = Get_LeftX(try);
	Get_PtX(p2) = Get_RightX(try);
	Trial_Edge_Sweep(p1,p2,Top,&extent);
	if (extent != Get_PtY(p1))
	{
	    /* check whether still in open area -- if not, pull back */
	    Get_TopY(try) = MAX_EQ(extent, Get_TopY(area));
	    Get_BottomY(try) = Get_TopY(try) + (Get_Height(sz) - 1);
	    /* check if past pt... */
	    COMPUTE_CENTER(try, cntr);
	    Get_PtY(cntr) = MAX_EQ(Get_PtY(cntr), Get_PtY(pt));
	    MAKE_RECTANGLE(cntr, sz, try);
	}
    }
    else if (Get_PtY(pt) > Get_PtY(cntr))	/* Bottom */
    {
	Get_PtY(p1) = Get_PtY(p2) = Get_BottomY(try);
	Get_PtX(p1) = Get_LeftX(try);
	Get_PtX(p2) = Get_RightX(try);
	Trial_Edge_Sweep(p1,p2,Bottom,&extent);
	if (extent != Get_PtY(p1))
	{
	    /* check whether still in open area -- if not, pull back */
	    Get_BottomY(try) = MIN_EQ(extent, Get_BottomY(area));
	    Get_TopY(try) = Get_BottomY(try) - (Get_Height(sz) - 1);
	    /* check if past pt... */
	    COMPUTE_CENTER(try, cntr);
	    Get_PtY(cntr) = MIN_EQ(Get_PtY(cntr), Get_PtY(pt));
	    MAKE_RECTANGLE(cntr, sz, try);
	}
    }
    return cntr;
}
