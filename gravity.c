#ifndef lint
static char sccs_id[] = "@(#)gravity.c	5.3  9/1/88";
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

#include <stdlib.h>
#include "copyright.h"

/*	Align edges of Resized or newly Opened Window
 *	with "nearby" edges of other Windows - "Gravity"
 */
#include "basetype.h"
#include "twinD.h"
#include "twin.h"

typedef struct an_edge	Edge;
struct an_edge
{
	Basetype edge_coord;		/* axis coordinate of edge(s) */
	int ref_count;			/* number of edges with this coord */
	Edge *next_edge;
};

#define  min(a, b)		( ((a) < (b)) ? (a) : (b) )

static Edge x_edge_list,		/* sentinels for edge lists */
	    y_edge_list;


/*	Gravity initialization
 */
void
Gravity_Init()
{
	x_edge_list.next_edge = (Edge *) NULL;
	y_edge_list.next_edge = (Edge *) NULL;
}


/*	Insert an edge into an edge_list in non-decreasing order
 *	of coordinate value.  Increment the reference count for
 *	that edge (more than one edge may exist at a given coordinate).
 *	THIS FUNCTION MUST BE THE FIRST LIST FUNCTION CALLED!
 */
void
Gravity_Insert_Edge(edge_coord, side) 
	Basetype edge_coord;
	Side side;
{
	Edge *prev_edge, *p_edge, *tmp_edge;

	switch (side)
	{
	case Top:
	case Bottom:
		prev_edge = &y_edge_list;
		p_edge = prev_edge -> next_edge;
	break;

	case Left:
	case Right:
		prev_edge = &x_edge_list;
		p_edge = prev_edge -> next_edge;
	break;
	}
	
	if (p_edge == (Edge *) NULL)	/* first edge added to list */
	{
		tmp_edge = allocate(Edge, 1);
		tmp_edge -> edge_coord = edge_coord;
		tmp_edge -> ref_count = 1;
		tmp_edge -> next_edge = (Edge *) NULL;
		prev_edge -> next_edge = tmp_edge;
	}
	else				/* insert edge in order on list */
		do
		{
			if (edge_coord == p_edge -> edge_coord)
			{
			/* at least one edge at this coord exists, so... */
				p_edge -> ref_count += 1;
				break;
			}
			else if (edge_coord < p_edge -> edge_coord)
			{
				tmp_edge = allocate(Edge, 1);
				tmp_edge -> edge_coord = edge_coord;
				tmp_edge -> ref_count = 1;
				tmp_edge -> next_edge = p_edge;
				prev_edge -> next_edge = tmp_edge;
				break;
			}
			else  /* (p_edge -> edge_coord < edge_coord) */
			{
				if (p_edge -> next_edge == (Edge *) NULL)

				/* then add this largest-value edge
				   at end of list... */
				{
					tmp_edge = allocate(Edge, 1);
					tmp_edge -> edge_coord = edge_coord;
					tmp_edge -> ref_count = 1;
					tmp_edge -> next_edge = (Edge *) NULL;
					p_edge -> next_edge = tmp_edge;
					break;
				}
			}
			prev_edge = p_edge;
		}
		while ( (p_edge = p_edge -> next_edge) != (Edge *) NULL );
}


/*	Delete an Edge from the given edge_list.
 *	Decrement the reference count for that Edge.
 *	If the ref count goes to zero, remove that Edge
 *	(element) from the list.
 */
void
Gravity_Delete_Edge(coord, side)
	Basetype coord;
	Side side;
{
	Edge *p_edge, *prev_edge;

	switch (side)
	{
	case Top:
	case Bottom:
		prev_edge = &y_edge_list;
		p_edge = prev_edge -> next_edge;
	break;

	case Left:
	case Right:
		prev_edge = &x_edge_list;
		p_edge = prev_edge -> next_edge;
	break;
	}
	
	while (p_edge != (Edge *) NULL)
	{
		if (p_edge -> edge_coord == coord)
		{
			p_edge -> ref_count -= 1;

			if (p_edge -> ref_count == 0)
			{
				prev_edge -> next_edge = p_edge -> next_edge;
				free((char *)p_edge);
			}
			break;
		}
		prev_edge = p_edge;
		p_edge = p_edge -> next_edge;
	}
}


/*	Return "vector" (magnitude * direction) to an edge
 *	which is closest in value to the edge given, of all
 *	the edges on edge_list
 */
static Basetype
Gravity_Closest_Edge(edge_coord, edge_list)
	Basetype edge_coord;
	Edge edge_list;
{
	Basetype floor_coord = (Basetype) 0;
        Basetype floor_dist, ceil_dist;
	Edge *p_edge = edge_list.next_edge;

	if (p_edge == (Edge *) NULL)
		return(0);

	while (p_edge != (Edge *) NULL)
	{
		if (edge_coord < p_edge -> edge_coord)
		{
			ceil_dist =  p_edge -> edge_coord - edge_coord;

			if (p_edge == edge_list.next_edge)
				return(ceil_dist);

			if ( abs(floor_dist = floor_coord - edge_coord)
				<= ceil_dist )
				return(floor_dist);
			else
				return (ceil_dist);
		}
		else if (edge_coord == p_edge -> edge_coord)
			return(0);
	
		else /* (p_edge -> edge_coord < edge_coord) */
		{
			floor_coord = p_edge -> edge_coord;
			p_edge = p_edge -> next_edge;
		}
	}

	return(floor_coord - edge_coord); /* edge_coord > last edge on list */
}


/*	Local gravity and edge (even/odd) adjustment.
 */
Basetype
Gravity_Adjust_Edge(coord, side)
	Basetype coord;
	Side side;
{
	Basetype vector;    /* magnitude and direction of gravity */

	if (Tilwin_Get_Global_Option(ENABLE_GRAVITY) == TRUE)
	{
		switch (side)
		{
		case Left:
		case Right:
			vector = Gravity_Closest_Edge(coord, x_edge_list);
		break;
		
		case Top:
		case Bottom:
			vector = Gravity_Closest_Edge(coord, y_edge_list);
		break;
		}

		/* if magnitude of vector is greater than range of gravity...
		 */
		if (Tilwin_Get_Gravity() < abs(vector))
			vector = 0;

		coord += vector;    /* side value adjusted for gravity */
	}

	switch (side)
	{
	case Left:		/* Left and Top sides have EVEN values */
	case Top:
		if (Is_Odd_Number(coord))
			coord++;
	break;

	case Right:		/* Right and Bottom sides have ODD values */
	case Bottom:
		if (Is_Even_Number(coord))
			coord--;
	break;
	}

	return(coord);
}


/*	Local gravity and edge (even/odd) adjustment for a TWRectangle.
 */
void
Gravity_Adjust(rectp)
	TWRectangle *rectp;
{
	rectp -> left_x   = Gravity_Adjust_Edge(rectp -> left_x, Left);
	rectp -> right_x  = Gravity_Adjust_Edge(rectp -> right_x, Right);
	rectp -> top_y    = Gravity_Adjust_Edge(rectp -> top_y, Top);
	rectp -> bottom_y = Gravity_Adjust_Edge(rectp -> bottom_y, Bottom);
}

Basetype
Gravity_Difference(coord, side)
    Basetype coord;
    Side side;
{
    Basetype diff;
    
    switch (side) {
    case Left:
    case Right:
        diff = Gravity_Closest_Edge(coord, x_edge_list);
        break;
    case Top:
    case Bottom:
        diff = Gravity_Closest_Edge(coord, y_edge_list);
        break;
    }

    return(abs(diff));
}
#ifdef WM_DEBUG
#include <stdio.h>

void 
Gravity_Print_Lists()
{
    Edge *x_edge = x_edge_list.next_edge;
    Edge *y_edge = y_edge_list.next_edge;

    printf("X Edge List\n");
    while (x_edge != (Edge *) NULL) {
        printf("%d ", x_edge->edge_coord);
        x_edge = x_edge->next_edge;
    }

    printf("\nY Edge List\n");
    while (y_edge != (Edge *) NULL) {
        printf("%d ", y_edge->edge_coord);
        y_edge = y_edge->next_edge;
    }

    printf("\n");
}
#endif
