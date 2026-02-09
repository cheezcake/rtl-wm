#ifndef lint
static char sccs_id[] = "@(#)try_sweep.c	5.3  9/1/88";
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
  try_edge_sweep.c: by Michael Berman
  RTL Windows System
  last modified: March 27, 1987
  version:  0.4
 ****************************************************************************/

#include "tileD.h"
#include "tile.h"
#include "twin.h"

#define SPLIT_RECT(r) r.left_x,r.top_y,r.right_x,r.bottom_y

/****************************************************************************
  EDGE SWEEPING
  
  Problem: 	Given a line segment which is parallel with one of the
	sides of the desktop, and which is contained within one or
	more tiles, 'sweep' it perpendicularly until it touches a new
	tile or the desktop edge.  The value returned represents the
	pixel position, on the desktop, of the furthest extent of the
	sweep.  (Note that this is NOT the same as the distance the
	edge moved; you can derive that by subtracting/adding the
	extent from/to the original edge position.)
  
  	Due to the asymmetry of corner stitching, there are two quite
	different versions of this, namely horizontal (which sweeps a
	vertical segment either to the Left or R) and vertical (sweeps
	a horizontal segment up or Down).   
  
  	This will be implemented as two boolean funtions, returning
	TRUE if the sweep was successful, and FALSE if there is a
	logical inconsistency in the arguments.  The "extent" argument
	will be a pointer to a location to give the answer, which is
	the x (in the case of horizontal) or y (in the case of
	vertical) marking the extent of the sweep.

  	The external entry point for edge sweeping is: Trial_Edge_Sweep
  
 ****************************************************************************/

/* variables with scope over all functions in this file */

Basetype current_extent;  /* best current guess at extent                 */
Side global_dir;	  /* direction of sweep, used by enumeration fcn  */
bool touched_solid_tile;  /* flag set if the enumeration fcn finds solid  */

#define ASSERT(a,m) \
{ \
    if (!(a)) \
     	printf("YOW! %s \n",m);\
}

void Enum_Horiz_Extent();
bool Vert_Sweep(), Horiz_Sweep();

bool
Trial_Edge_Sweep(p1,p2,dir,extent)
    TWPoint p1, p2;
    Side dir;
    Basetype *extent;
{
    if ((dir == Top) || (dir == Bottom))
	return(Vert_Sweep(p1,p2,dir,extent));
    else if ((dir == Left) || (dir == Right))
	return(Horiz_Sweep(p1,p2,dir,extent));
    else
	return(FALSE);
}
bool
Horiz_Sweep(p1, p2, dir, extent)
    TWPoint p1, p2;
    Side dir;
    Basetype *extent;
/**************************************************************************** 
  Arguments:
  p1, p2:    The points defining the line segment.  Since this is a
	horizontal sweep, p1.x must equal p2.x.  p1 must be above p2;
	hence p1.y <= p2.y. 
  dir:       The direction to sweep-- must be Left or Right.
  extent:    Pointer to Basetype in which result is returned.
  
  Returns:   Boolean flag indicating success/failure of sweep.

  Modifies:  *extent (parameter)

  Description: Horiz_Sweep performs a horizontal line sweep, that is,
	it simulates moving a vertical line segment in the horizontal
	direction indicated by "dir" (= Left or Right) as far as it will go
	until it first touches a solid tile.  The assumption made is
	that the line segment you start from is at the edge of a solid
	tile; therefore, it is moved one pixel in the appropriate
	direction before the sweep begins.  If after moving it is
	still on a solid tile, the original position is returned.  The
	value of the Boolean function indicates whether the sweep was
	performed; a return of "false" indicates that the arguments
	were incorrect or contradictory.  The pixel location of the
	furthest position of the sweep is returned in the Basetype
	pointed to by "extent".  Because all left tile edges are even
	and right edges odd, a left-hand sweep always returns an even
	number, while a right-hand sweep returns an odd number.

  Logic: First, the arguments are checked for consistency; if an error
	is found, return(FALSE).  Before the call, the value of
	current_extent is initialized to point to the appropriate
	desktop edge (left for a left sweep, right for a right sweep.)
	current_extent is used to store the position of the "closest"
	edge found so far.  Because the horizontal space tiles are
	required to be maximal, we simply examine each tile that the
	line segment crosses and find the tile that ends "closest" to
	the line segment, which is equivalent to the maximum extent of
	a sweep before touching a new tile.  Tiles_In_Area is used to
	enumerate the set of tiles crossed by the line segment, which 
	actually is passed as a rectangle of width 2.   The
	call to Tiles_In_Area uses the enumeration function
	Enum_Horiz_Tiles which is defined above; the result is stored
	in current_extent.  The enumeration also checks for solid tiles; 
	if found, then a flag "touched_solid_tile" is set, so that the
	unchanged edge can be returned.
 ****************************************************************************/

{
    TWRectangle Desktop_View, r;
    
    if (p1.x != p2.x)
	return(FALSE);
    r.top_y = p1.y;
    r.bottom_y = p2.y;
    if (r.top_y > r.bottom_y)
	return(FALSE);
    Desktop_View = Tilwin_Get_Desktop_Rectangle();
    switch(dir)
    {
    case Left:
	if (!Is_Even_Number(p1.x))
	    return(FALSE);
	else
	{
	    current_extent = Desktop_View.left_x;
	    r.left_x = p1.x - 2;
	    r.right_x = r.left_x + 1;
	}
	break;
    case Right:
	if (Is_Even_Number(p1.x))
	    return(FALSE);
	else
	{
	    current_extent = Desktop_View.right_x;
	    r.right_x = p1.x + 2;
	    r.left_x = r.right_x - 1;
	}
	break;
    default:
	return(FALSE);
    }
    global_dir = dir;
    touched_solid_tile = FALSE;
    Tiles_In_Area(SPLIT_RECT(r), Enum_Horiz_Extent);
    *extent = (touched_solid_tile)? p1.x : current_extent;
    ASSERT((Is_Even_Number(current_extent) && dir == Left) ||
	   (!(Is_Even_Number(current_extent)) && dir == Right),
	   "Parity error in current_extent -- Horiz_Sweep");
    return(TRUE);
}

bool
Vert_Sweep(p1, p2, dir, extent)
    TWPoint p1, p2;
    Side dir;
    Basetype *extent;

/**************************************************************************** 
  Arguments:
  p1, p2: 	The points defining the line segment.  Since this is a 
	vertical sweep, p1.y must equal p2.y.  p1 must be to the left
	of p2; hence, p1.x <= p2.x;
  dir:       The direction to sweep-- must be Top or Bottom.
  extent:    pointer to Basetype in which result is returned.

  Returns:   Boolean flag indicating success/failure of sweep.

  Modifies:  *extent (parameter)

  Description:  Vert_Sweep performs a vertical line sweep, that is, it
	simulates moving a horizontal line segment in the vertical
	direction indicated by "dir" (= Top or Bottom) as far as it will
	go until it first touches a solid tile.  The assumption made is 
	that the line segment you start from is at the edge of a solid
	tile; therefore it is moved one pixel in the appropriate direction
	before the sweep begins.  If, after moving it is still on a solid
	tile, the original position is returned.  The values for the
	function and the return value *extent are the same as for
	Horiz_Sweep.  Because all top tile edges are even and bottom
	edges odd, a sweep Up will always return an even number, while
	a sweep down returns an odd number.  

  Logic: A little more complicated than the horizontal case due to the
	asymetry of corner stitching.  After checking for consistency,
	we find the initial line segment, which is one pixel above or
	below the line segment passed (depending on the direction of
	the sweep.  We find the tile(s) which
	contain the initial line segment.  If the initial line is not
	entirely within a single space tile, then the original edge is
	returned without change.  If the segment is contained
	entirely within a single space tile, then we move to the edge
	of the tile, and advance the line segment just one pixel
	further, beyond the original space tile.  This process is
	iterated until at least part of the line segment is not in a
	space tile.  (Note that if the two points of the segment are
	in different space tiles, there MUST be a solid tile somewhere
	in between.)  This process may lead to the segment crossing
	solid tiles, or to the edge of the desktop.  Once this is
	done, the y value  is "backed up" by 1.
 ****************************************************************************/

{
    Tile *tpl, *tpr;
    TWRectangle r;
    Basetype y_extent;
    
    if (p1.y != p2.y)
	return(FALSE);
    r.left_x = p1.x;
    r.right_x = p2.x;
    if (r.left_x > r.right_x)
	return(FALSE);
    if (dir == Top)
    {
	if (!Is_Even_Number(p1.y))
	    return(FALSE);
    }
    else if (dir == Bottom)
    {
	if (Is_Even_Number(p1.y))
	    return(FALSE);
    }
    else
	return(FALSE);
    y_extent = (dir == Top)? p1.y - 1: p1.y + 1;
    tpl = (Tile *)Tile_at_Point(p1.x,y_extent);
    tpr = (Tile *)Tile_at_Point(p2.x,y_extent);

    while ((tpl == tpr) &&
	   (tpl != NULL_TILE) &&
	   (Tile_Get_Type(tpl) == Space))
    {
	y_extent = (dir == Top)? Tile_Get_Corners(tpl).top_y - 1:
	                         Tile_Get_Corners(tpl).bottom_y + 1;
	tpl = (Tile *)Tile_at_Point(p1.x,y_extent);
	tpr = (Tile *)Tile_at_Point(p2.x,y_extent);
    }
    y_extent = (dir == Top)? y_extent + 1 : y_extent - 1;
    ASSERT((Is_Even_Number(y_extent) && dir == Top) ||
	   (!(Is_Even_Number(y_extent)) && dir == Bottom),
	   "Parity error in y_extent -- Vert_Sweep");
    *extent = y_extent;
    return(TRUE);
}
 
void
Enum_Horiz_Extent(tp)
    Tile *tp;

/****************************************************************************

  Arguments:
        tp:  Pointer to tile to be examined.
  
  Modifies:
        current_extent (as a side effect)
        touched_solid_tile (as a side effect)

  Description: Enum_Horiz_Extent is used by Horiz_Sweep only.  It
	looks at a tile and checks whether the left (or right,
	depending on sweep direction) edge of the tile is more
	constraining than the previous best, which is current_extent.
	We also set a flag if we hit a solid tile -- once this is
	set TRUE, any additional enums do nothing.
	This function is passed as a parameter to Tiles_In_Area, and
	executed once for each tile (tp) in the specified range. 

  Logic: The operation of the function is controlled by the variable
	current_extent, which is global to this file.  Each time
	Enum_Horiz_Extent is called (for a particular tile) it checks
	whether that tile represents a greater "extent" than the
	previous best.  That is, is this tile further to the left (or
	right) than the previous best.  The choice of left  or
	right  is determined by the value of global_dir, which is
	of scope external to Enum_Horiz_Extent. 
 ****************************************************************************/
{
    if (!touched_solid_tile) /* otherwise, don't bother */
	if (Tile_Get_Type(tp) == Space)
	{
	    if (global_dir == Left)
	    {
		if (Left_X(tp) > current_extent)
		{
		    current_extent = Left_X(tp);
		}
	    }
	    else /* global_dir == Right */
	    {
		if (Right_X(tp) < current_extent) 
		{
		    current_extent = Right_X(tp);
		}
	    }
	}
	else
	    touched_solid_tile = TRUE;
}
