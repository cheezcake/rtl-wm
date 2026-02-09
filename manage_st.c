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
#include "basetype.h"

#ifndef TILWIN_DEFINE
#include "twinD.h"
#endif

#ifndef USERWIN_DEFINE
#include "uwinD.h"
#endif

#include "twin.h"
#include "region.h"

extern void Manage_Init_Rtl();

extern void Manage_Start();
extern void Manage_Update_Icons();
extern void Manage_Finish();

extern void Manage_Prepare_Open();
extern bool Manage_Client_Open_Automatically();
extern void Manage_Client_Open_Icon();

/* ------------------------------------------------------------ */

/* distance between two points */
#define Dist(pt1,pt2) \
    ( ( ((pt1).x - (pt2).x)*((pt1).x - (pt2).x) ) +  \
      ( ((pt1).y - (pt2).y)*((pt1).y - (pt2).y) ) )

/* ------------------------------------------------------------ */

#ifdef WM_DEBUG
static void Manage_Walk_ThreadedDataList(lhead, func)
    pointer lhead;
    void (*func) ();
{
    Tilwinp winp;
    
    for (winp = (Tilwinp) lhead; winp != WIN_NULL;
	 winp = (Tilwinp) Tilwin_Get_Data(winp)) 
    {
	(*func)(winp);
    }
}

TWPoint print_center;
int de_bug = 100;

static void Manage_Print_Position(winp)
    Tilwinp  winp;
{
    printf("position = %d\n", Dist(Tilwin_Get_Position(winp), print_center));
}

#endif

/* ------------------------------------------------------------ */

/* delete the item after element from the linked list */
#define DELETE_AFTER(element) { \
    if (Tilwin_Get_Data(element) != (pointer) NULL) { \
        pointer p; \
        p = Tilwin_Get_Data((Tilwinp) Tilwin_Get_Data(element)); \
        Tilwin_Put_Data(element, p); \
    } \
    }

/* insert the item insertee after the item element */
#define INSERT_AFTER(element, insertee) { \
    Tilwin_Put_Data(insertee, Tilwin_Get_Data(element)); \
    Tilwin_Put_Data(element, (pointer) insertee); \
    }

/* move the item after element1 to after element2 */
#define MOVE_NEXT(element1, element2) { \
    pointer q; \
    q = Tilwin_Get_Data(element1); \
    DELETE_AFTER(element1); \
    INSERT_AFTER(element2, q); \
    }

/* ------------------------------------------------------------ */

static pointer nonlayout_head = WIN_NULL;
static pointer nonlayout_tail = WIN_NULL;
static pointer layout_head = WIN_NULL;
static pointer layout_tail = WIN_NULL;

pointer Manage_Sort_ThreadedDataList();

/* ------------------------------------------------------------ */

void Manage_Startup_Open(uwinp)
    Userwin *uwinp;
{
    TWRectangle rect;
    Size size;
    TWPoint center;
    
    Manage_Prepare_Open(uwinp);
    
    if (uwinp->layout_found == TRUE)
    {
	/* place it on the list of windows which are laid out */
	if (layout_head == (pointer) NULL) 
	    layout_head = layout_tail = uwinp->winp;
	else {
	    Tilwin_Put_Data(layout_tail, uwinp->winp);
	    layout_tail = uwinp->winp;
	}
	Tilwin_Put_Data(layout_tail, WIN_NULL);
    }
    else {
	rect = Tilwin_Get_Rectangle(uwinp->winp);
	
	COMPUTE_CENTER(rect, center);
	Tilwin_Set_Position(uwinp->winp, center);
	
	COMPUTE_SIZE(rect, size);
	Set_Min_Size(size, size, Tilwin_Get_Max(uwinp->winp));
	Set_Max_Size(size, size, Tilwin_Get_Min(uwinp->winp));
	
	/* this is hack which tell us that the desired size has not been
	   set for this class of window
	   */
	if (Same_Size(Tilwin_Get_Desired(uwinp->winp),
		      Tilwin_Get_Absolute_Minimums()))
	{
	    uwinp->regular_size = size;
	    Tilwin_Set_Desired(uwinp->winp, size);
	}
	
	if (Tilwin_Set (uwinp->winp, center, size) != TRUE)
	    (void) Tilwin_Set (uwinp->winp, center,
			       Tilwin_Get_Min(uwinp->winp));
	
	/* place it on the list of windows which are not layed out */
	if (nonlayout_head == (pointer) NULL) 
	    nonlayout_head = nonlayout_tail = uwinp->winp;
	else {
	    Tilwin_Put_Data(nonlayout_tail, uwinp->winp);
	    nonlayout_tail = uwinp->winp;
	}
	Tilwin_Put_Data(nonlayout_tail, WIN_NULL);
    }
}

/* ------------------------------------------------------------ */

#define global_excursion(opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Tilwin_Get_Global_Option(opt); \
    Tilwin_Set_Global_Option(opt,val); \
    code; \
    Tilwin_Set_Global_Option(opt,temp_val); \
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Place_Laid_Out()
{
    Userwin *uwinp;
    Tilwinp winp;

    for (winp = (Tilwinp) layout_head; winp != WIN_NULL;
	 winp =	 Tilwin_Get_Data(winp)) 
    {
	uwinp = Userwin_Get(winp);
        if ( Userwin_Get_Window_Option( uwinp, AUTO_OPEN_ON_CREATE ) )
            Manage_Client_Open_Automatically( uwinp );
        else
            Manage_Client_Open_Icon( uwinp );
    }
}

/* ------------------------------------------------------------ */

static TWRectangle deskrect;

static TWPoint Manage_Farthest_Icon_Point()
{
    TWPoint furthest_point;

    /* find out point farthest from the icons */
    furthest_point = Tilwin_Get_Desktop_Center();

    switch ((Icon_Position) UserGlobals_Get_Value(SECONDARY_ICON_PLACEMENT)) {
      case Icon_Top:
	Get_PtY(furthest_point) = Get_BottomY(deskrect);
	break;
      case Icon_Bottom:
	Get_PtY(furthest_point) = Get_TopY(deskrect);
	break;
      case Icon_Left:
	Get_PtX(furthest_point) = Get_RightX(deskrect);
	break;
      case Icon_Right:
	Get_PtX(furthest_point) = Get_LeftX(deskrect);
	break;
      case Icon_Middle:
	Get_PtX(furthest_point) = Get_LeftX(deskrect);
	Get_PtY(furthest_point) = Get_TopY(deskrect);
	break;
    }

    switch ((Icon_Position) UserGlobals_Get_Value(ICON_PLACEMENT)) {
      case Icon_Top:
	Get_PtY(furthest_point) = Get_BottomY(deskrect);
	break;
      case Icon_Bottom:
	Get_PtY(furthest_point) = Get_TopY(deskrect);
	break;
      case Icon_Left:
	Get_PtX(furthest_point) = Get_RightX(deskrect);
	break;
      case Icon_Right:
	Get_PtX(furthest_point) = Get_LeftX(deskrect);
	break;
    }
    return furthest_point;
}

/* ------------------------------------------------------------ */

void Manage_Startup_Finish()
{
    Userwin *uwinp;
    Tilwinp winp;
    TWPoint center, 
            window_center, 
            furthest_point,
            quadrant_corner;
    int number_of_windows = 0;
    Size size;
    bool result;
    
    Manage_Init_Rtl();
	
    Manage_Start();
    
    /* place all windows which have layouts */
    Manage_Place_Laid_Out();

    if (nonlayout_head == (pointer) NULL)
    {
	Manage_Finish(TRUE);
	return;
    }

    /* make sure all icons get opened */
    Manage_Update_Icons();

    deskrect = Tilwin_Get_Desktop_Rectangle();

    /* find out point farthest from the icons */
    furthest_point = Manage_Farthest_Icon_Point();

    /* sort the list in decreasing distance from furthest_point 
       (the point furthest from furthest_point first,...)
       (NOTE: the tilwinp furthest from furthest_point is the one
       closest to the icons)
     */
    nonlayout_head =
	Manage_Sort_ThreadedDataList(nonlayout_head, furthest_point);

    /* switch the list so that the tilwinp closest to furthest_point
       is first (this is the tilwinp furthest from the icons).
     */
    nonlayout_head = (pointer) Tilwin_Reverse_Thread(nonlayout_head);
    
    /* open all windows at their minumum size at the point furthest 
     * away from the icons (closest to the furthest point first...)
     */
    for (winp = (Tilwinp) nonlayout_head; winp != WIN_NULL;
	 winp =	 Tilwin_Get_Data(winp)) 
    {
	uwinp = Userwin_Get(winp);

        if ((Userwin_Get_Window_Option(uwinp, AUTO_OPEN_ON_CREATE) !=
	     TRUE) ||
	    (Userwin_Startup_State(uwinp) == IconicState) ||
	    (Userwin_Startup_State(uwinp) == InactiveState))
            Manage_Client_Open_Icon( uwinp );
        else
        {
            global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE, 
            { result = Tilwin_Open_Nearest_In_Area(winp, deskrect,
                            furthest_point, 
                            Tilwin_Get_Min(winp));
            } );
            
            if ( result )
                uwinp->ever_opened = TRUE;
            else
            {
                Manage_Client_Open_Icon( uwinp );
                uwinp->output_sent = TRUE;
                Tilwin_Auto_Close(winp);
            }
        }        
    }

    /* make sure all icons get opened */
    Manage_Update_Icons();

    /* switch the list so that the tilwinp farthest from
       furthest_point is first (this is the tilwinp closest to the
       icons)
     */
    nonlayout_head = (pointer) Tilwin_Reverse_Thread(nonlayout_head);
    
    /* reopen all windows at minimum size at their desired point
       (furthest from the furthest_point first)
     */
    for (winp = (Tilwinp) nonlayout_head; winp != WIN_NULL;
	 winp =	 Tilwin_Get_Data(winp)) 
    {
	/* only reopen open windows! */
	if (Tilwin_Is_Open(winp) != TRUE)
	    continue;
	
        global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE, 
             Tilwin_Open_Nearest_In_Area(winp, deskrect,
                                         Tilwin_Get_Position(winp),
                                         Tilwin_Get_Min(winp));
             );
    }
    
    /* try to open windows which were automatically closed */
    Tilwin_Gen_Closed_Windows();
    while ((winp = Tilwin_Next_Window()) != WIN_NULL)
    {
	uwinp = Userwin_Get(winp);
	if ((uwinp->winp == winp) &&
	    (Tilwin_Was_Automatically_Closed(winp) == TRUE))
	{
	    if (uwinp->layout_found == TRUE)
	    {
		global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
                     Tilwin_Open_Nearest_In_Area(winp, deskrect,
                                                 Tilwin_Get_Center(winp),
                                                 Tilwin_Get_Size(winp))
                     );
	    }
	    else 
	    {
		global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
                     Tilwin_Open_Nearest_In_Area(winp, deskrect,
                                                 Tilwin_Get_Position(winp),
                                                 Tilwin_Get_Min(winp))
                     );
	    }
	}
    }
    
    /* find the "center of gravity" of all windows on the screen */
    Get_PtX(center) = 0;
    Get_PtY(center) = 0;

    for (winp = (Tilwinp) nonlayout_head; winp != WIN_NULL; 
         winp = (Tilwinp) Tilwin_Get_Data(winp)) {
	if (Tilwin_Is_Open(winp) == TRUE)
	{
	    Get_PtX(center) += Get_PtX(Tilwin_Get_Position(winp));
	    Get_PtY(center) += Get_PtY(Tilwin_Get_Position(winp));
	    number_of_windows++;
	}
    }

    /* if there are no open windows, return */
    if(number_of_windows == 0)
    {
	Manage_Finish(TRUE);
	return;
    }
    
    Get_PtX(center) = Get_PtX(center) / number_of_windows;
    Get_PtY(center) = Get_PtY(center) / number_of_windows;

    /* sort the list in decreasing distance from the center of gravity
       (the point furthest from the center of gravity first,...)
     */
    nonlayout_head =
	Manage_Sort_ThreadedDataList(nonlayout_head, center);
    
    /* open all windows, farthest first, at its minimum size
       at the point in its quadrant farthest from the c.o.g.
     */
    for (winp = (Tilwinp) nonlayout_head; winp != WIN_NULL;
	 winp = Tilwin_Get_Data(winp)) {

        if  (Tilwin_Is_Open(winp) == FALSE)
	    continue;
	
	window_center = Tilwin_Get_Position(winp);
        Get_PtX(quadrant_corner) = (Get_PtX(window_center) < Get_PtX(center))?
            Get_LeftX(deskrect) : Get_RightX(deskrect);
        Get_PtY(quadrant_corner) = (Get_PtY(window_center) < Get_PtY(center))?
            Get_TopY(deskrect) : Get_BottomY(deskrect);

        global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE, 
	    global_excursion(ALLOW_AUTOMATIC_SHRINK, FALSE, 
			     Tilwin_Open_Nearest_In_Area(winp, deskrect, quadrant_corner, 
							 Tilwin_Get_Min(winp));
			     )
			 );
    }

    /* switch the list so that the tilwinp closest to the center of
       gravity is first
     */
    nonlayout_head = (pointer) Tilwin_Reverse_Thread(nonlayout_head);

    /* open all windows, closest first, at its the average of minimum
       and MIN(desired size, preferred size) size at its preferred position
     */
    for (winp = (Tilwinp) nonlayout_head; winp != WIN_NULL;
	 winp = Tilwin_Get_Data(winp)) {

	Size new_size;
	
        if (Tilwin_Is_Open(winp) == FALSE)
	    continue;

	Set_Min_Size(new_size, Tilwin_Get_Desired(winp),
		     Tilwin_Get_Previous_Size(winp));
	
        Get_Width(size) = 
            (Get_Width(new_size) + 
             Get_Width(Tilwin_Get_Min(winp))) / 2;
        Get_Height(size) =
            (Get_Height(new_size) +
             Get_Height(Tilwin_Get_Min(winp))) / 2;
        
        global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE, 
            global_excursion(ALLOW_AUTOMATIC_SHRINK, FALSE, 
                Tilwin_Open_Nearest_In_Area(winp, deskrect,
                            Tilwin_Get_Position(winp), size)));
    }

    /* switch the list so that the tilwinp farthest from the center of
       gravity is first
     */
    nonlayout_head = (pointer) Tilwin_Reverse_Thread(nonlayout_head);
    
    /* open all windows, farthest first, at MIN(desired, preferred)
       size
     */
    for (winp = (Tilwinp) nonlayout_head; winp != WIN_NULL;
	 winp = Tilwin_Get_Data(winp)) {

	Size new_size;
	
        if (Tilwin_Is_Open(winp) == FALSE)
	    continue;

	Set_Min_Size(new_size, Tilwin_Get_Desired(winp),
		     Tilwin_Get_Previous_Size(winp));

        window_center = Tilwin_Get_Position(winp);
        Get_PtX(quadrant_corner) = (Get_PtX(window_center) < Get_PtX(center))?
            Get_LeftX(deskrect) : Get_RightX(deskrect);
        Get_PtY(quadrant_corner) = (Get_PtY(window_center) < Get_PtY(center))?
            Get_TopY(deskrect) : Get_BottomY(deskrect);

        global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE, 
            global_excursion(ALLOW_AUTOMATIC_SHRINK, FALSE, 
                Tilwin_Open_Nearest_In_Area(winp, deskrect, quadrant_corner, 
                                            new_size)));
    }

    /* switch the list so that the tilwinp closest to the center of
       gravity is first
     */
    nonlayout_head = (pointer) Tilwin_Reverse_Thread(nonlayout_head);

    /* open all windows, closest first, at MAX(desired, preferred)
       size
     */
    for (winp = (Tilwinp) nonlayout_head; winp != WIN_NULL;
	 winp = Tilwin_Get_Data(winp)) {

	Size new_size;
	
        if (Tilwin_Is_Open(winp) == FALSE)
	    continue;

	Set_Max_Size(new_size, Tilwin_Get_Desired(winp),
		     Tilwin_Get_Previous_Size(winp));
	
        global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE, 
            global_excursion(ALLOW_AUTOMATIC_SHRINK, FALSE, 
                Tilwin_Open_Nearest_In_Area(winp, deskrect,
                             Tilwin_Get_Position(winp), new_size)));
    }
    
    Manage_Finish(TRUE);
}

/* ------------------------------------------------------------ */

/* sort a list of tilwinps threaded by the data field.
   the order of the list is non-increasing in terms of the
   euclidean distance from the point pt to the value returned by
   Tilwin_Get_Position for each tilwinp (i.e. the tilwinp whose
   position is furthest from point is first, ..., the tilwinp whose
   position  is closest to point is last)
 */
pointer Manage_Sort_ThreadedDataList(lhead, pt)
    pointer lhead;
    TWPoint pt;
{
    pointer ptr;
    pointer max;
    pointer max_prev;
    pointer sorted;
    pointer unsorted;
    pointer prev;
    int max_distance;
    
    if (lhead == (pointer) NULL)
	return((pointer) NULL);
    
    /* the window farthest from the pt */
    max = lhead;
    max_prev = (pointer) NULL;
    max_distance = Dist(Tilwin_Get_Position(max), pt);

    for (ptr = Tilwin_Get_Data(lhead), prev = lhead; 
         ptr != (pointer) NULL;
         prev = ptr, ptr = Tilwin_Get_Data(ptr)) {

        if (Dist(Tilwin_Get_Position(ptr), pt) > max_distance) {
            max_distance = Dist(Tilwin_Get_Position(ptr), pt);
            max = ptr;
            max_prev = prev;
        }
    }

    /* if the window farthest from the pt is not at the lhead of the list,
     * put it there
     */
    if (max_prev != (pointer) NULL) {
        DELETE_AFTER(max_prev);
        Tilwin_Put_Data(max, lhead);
        lhead = max;
    }

    /* sort the rest of the list (using an insertion sort) */
    for (sorted = lhead, unsorted = Tilwin_Get_Data(lhead);
         unsorted != (pointer) NULL;) {

        max = unsorted;
        max_prev = (pointer) NULL;
        max_distance = Dist(Tilwin_Get_Position(max), pt);

        for (ptr = Tilwin_Get_Data(unsorted), prev = unsorted;
             ptr != (pointer) NULL;
             prev = ptr, ptr = Tilwin_Get_Data(ptr)) {

            if (Dist(Tilwin_Get_Position(ptr), pt) > max_distance) {
                max_distance = Dist(Tilwin_Get_Position(ptr), pt);
                max = ptr;
                max_prev = prev;
            }
        }

        if (max_prev == (pointer) NULL) {
            sorted = unsorted;
            unsorted = Tilwin_Get_Data(unsorted);
        }
        else {
            MOVE_NEXT(max_prev, sorted);
            sorted = Tilwin_Get_Data(sorted);
        }
    }

    return(lhead);
}

/* ------------------------------------------------------------ */

void
Manage_Determine_Startup_State(uwinp)
    Userwin *uwinp;
{
    if(Userwin_Initially_Mapped(uwinp) == TRUE)
    {
	if(Userwin_Wm_State(uwinp) == NeverState ||
	   Userwin_Wm_State(uwinp) == IgnoreState)
	{
	    switch(Userwin_State(uwinp))
	    {
	    case IconicState:
		Userwin_Startup_State(uwinp) = IconicState;
		break;
	    case InactiveState:
		Userwin_Startup_State(uwinp) = InactiveState;
		break;
	    case IgnoreState:
		Userwin_Startup_State(uwinp) = IgnoreState;
		break;
	    default:
		Userwin_Startup_State(uwinp) = NormalState;
		break;
	    }
	}
	else
	{
	    if(Userwin_State(uwinp) == IgnoreState)
	    {
		Userwin_Startup_State(uwinp) = IgnoreState;
	    }
	    else
	    {
		switch(Userwin_Wm_State(uwinp))
		{
		case IconicState:
		    Userwin_Startup_State(uwinp) = IconicState;
		    break;
		case InactiveState:
		    Userwin_Startup_State(uwinp) = InactiveState;
		    break;
		case IgnoreState:
		    Userwin_Startup_State(uwinp) = IgnoreState;
		    break;
		default:
		    Userwin_Startup_State(uwinp) = NormalState;
		    break;
		}
	    }
	}
    }
    else if(Userwin_Initially_Icon_Mapped(uwinp) == TRUE)
    {
	switch(Userwin_State(uwinp))
	{
	case ClientIconState:
	    Userwin_Startup_State(uwinp) = NormalState;
	    break;
	case InactiveState:
	    Userwin_Startup_State(uwinp) = InactiveState;
	    break;
	case IgnoreState:
	    Userwin_Startup_State(uwinp) = IgnoreState;
	    break;
	default:
	    Userwin_Startup_State(uwinp) = IconicState;
	    break;
	}
    }
    else
    {
	if(Userwin_Wm_State(uwinp) == NeverState ||
	   Userwin_Wm_State(uwinp) == IgnoreState)
	{
	    Userwin_Startup_State(uwinp) = IgnoreState;
	}
	else
	{
	    switch(Userwin_State(uwinp))
	    {
	    case ClientIconState:
		Userwin_Startup_State(uwinp) = ClientIconState;
	        break;
	    case InactiveState:
		Userwin_Startup_State(uwinp) = InactiveState;
	        break;
	    default:
		Userwin_Startup_State(uwinp) = IconicState;
	    }
	}
    }
}
