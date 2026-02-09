/*
static char sccs_id[] = "@(#)basetype.h	5.5  9/1/88";
*/

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


/*   Base type definitions for the Tiling Window Manager.
 *
 *   ONLY type definitions go here - general macros go in std_defs.h!
 */

#ifndef BASETYPE

#define BASETYPE

#include "std_defs.h"


typedef int	Basetype;

typedef struct
{
    Basetype width,
        height;
} Size;


typedef struct
{
    Basetype  left_x,		/* point at Top Left corner */
        top_y,
        right_x,		/* point at Bottom Right */
        bottom_y;
} TWRectangle;


typedef enum
{
    Top, Bottom, Left, Right,
    Top_Left, Top_Right, Bottom_Left, Bottom_Right,
    NoSide
} Side;


typedef struct
{
    Basetype x, y;
} TWPoint;


/*  Macros for basetypes
 */
#define  Get_Width(_size)        (_size).width
#define  Get_Height(_size)       (_size).height

#define  Get_LeftX(_rect)	(_rect).left_x
#define  Get_RightX(_rect)	(_rect).right_x
#define  Get_TopY(_rect)	(_rect).top_y
#define  Get_BottomY(_rect)	(_rect).bottom_y

#define  Get_PtX(_point)	(_point).x
#define  Get_PtY(_point)	(_point).y


/*  setting sizes
 */
#define Set_Min_Size(siz,siz1,siz2) \
{ \
    if ((siz1).width < (siz2).width) \
        (siz).width = (siz1).width; \
    else \
        (siz).width = (siz2).width; \
    if ((siz1).height < (siz2).height) \
        (siz).height = (siz1).height; \
    else \
        (siz).height = (siz2).height; \
}

#define Set_Max_Size(siz,siz1,siz2) \
{ \
    if ((siz1).width > (siz2).width) \
        (siz).width = (siz1).width; \
    else \
        (siz).width = (siz2).width; \
    if ((siz1).height > (siz2).height) \
        (siz).height = (siz1).height; \
    else \
        (siz).height = (siz2).height; \
}

#define Same_Size(siz1,siz2) \
    ( ( (siz1).width == (siz2).width ) && \
      ( (siz1).height == (siz2).height ) )

#define Same_Rect(rect1,rect2) \
    ( ( (rect1).left_x == (rect2).left_x ) && \
      ( (rect1).right_x == (rect2).right_x ) && \
      ( (rect1).top_y == (rect2).top_y ) && \
      ( (rect1).bottom_y == (rect2).bottom_y ) )

#define COMPUTE_CENTER(_rect, _location) \
    { \
    Get_PtX((_location)) = 1 + (Get_LeftX((_rect)) + Get_RightX((_rect))) / 2; \
    Get_PtY((_location)) = 1 + (Get_TopY((_rect)) + Get_BottomY((_rect))) / 2; \
    }

#define COMPUTE_SIZE(_rect, _size) \
    { \
    Get_Width(_size) = Get_RightX(_rect) - Get_LeftX(_rect) + 1; \
    Get_Height(_size) = Get_BottomY(_rect) - Get_TopY(_rect) + 1; \
    }

#define MAKE_RECTANGLE(_location, _size, _rect) \
    { \
    Get_LeftX(_rect) = Get_PtX(_location) - (Get_Width(_size) / 2) ; \
    Get_RightX(_rect) = Get_PtX(_location) + ((Get_Width(_size) / 2) - 1); \
    Get_TopY(_rect) = Get_PtY(_location) - (Get_Height(_size) / 2) ; \
    Get_BottomY(_rect) = Get_PtY(_location) + ((Get_Height(_size) / 2) - 1); \
    if (Is_Odd_Number(Get_LeftX(_rect))) \
      if (Is_Odd_Number(Get_PtX(_location))) \
         { Get_LeftX(_rect)-- ; Get_RightX(_rect)-- ;} \
      else \
         { Get_LeftX(_rect)++ ; Get_RightX(_rect)++ ;} \
    if (Is_Odd_Number(Get_TopY(_rect))) \
      if (Is_Odd_Number(Get_PtY(_location))) \
         { Get_TopY(_rect)-- ; Get_BottomY(_rect)-- ;} \
      else \
         { Get_TopY(_rect)++ ; Get_BottomY(_rect)++ ;} \
    }

#endif  /* BASETYPE */
