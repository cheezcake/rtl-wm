#ifndef lint
static char sccs_id[] = "@(#)twin_tmp.c	5.4  9/1/88";
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
#include "trial.h"
#include "state.h"

extern TWPoint desktop_center;

#define global_excursion(opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Tilwin_Get_Global_Option(opt); \
    Tilwin_Set_Global_Option(opt,val); \
    code; \
    Tilwin_Set_Global_Option(opt,temp_val); \
}

#define Tilwin_Calc_Location_Size(location, size, rect) \
{ \
    TWRectangle rct; \
    rct.left_x = ((rect).left_x + 1) & (~1); \
    rct.right_x = ((rect).right_x - 1) | 1; \
    rct.top_y = ((rect).top_y + 1) & (~1); \
    rct.bottom_y = ((rect).bottom_y - 1) | 1; \
    COMPUTE_CENTER(rect, location); \
    COMPUTE_SIZE(rect, size); \
}
    
extern TWRectangle desktop_rect;
extern bool Tilwin_Resize();
extern bool Tilwin_Open();
bool Tilwin_Can_Open();

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static TWRectangle 
Tilwin_Stretch(win, rect, side)
    Tilwin *win;
    TWRectangle rect;
    Side side;
{
    /* don't ask. */
    Tilwin *twinp = win;
    TWPoint pt;
    TWRectangle current_rect;
    
    if ( rect.top_y < desktop_rect.top_y )
        rect.top_y = desktop_rect.top_y;
    if ( rect.bottom_y > desktop_rect.bottom_y )
        rect.bottom_y = desktop_rect.bottom_y;
    if ( rect.left_x < desktop_rect.left_x )
        rect.left_x = desktop_rect.left_x;
    if ( rect.right_x > desktop_rect.right_x ) 
        rect.right_x = desktop_rect.right_x;

    current_rect = Tilwin_Get_Rectangle(twinp);
    
    switch (side){
        case Left:
            Get_PtX(pt) = Get_LeftX(rect);
            Get_LeftX(rect) = Get_LeftX(current_rect);
            break;
       case Right:
            Get_PtX(pt) = Get_RightX(rect);
            Get_RightX(rect) = Get_RightX(current_rect);
            break;
       case Top:
            Get_PtY(pt) = Get_TopY(rect);
            Get_TopY(rect) = Get_TopY(current_rect);
            break;
       case Bottom:
            Get_PtY(pt) = Get_BottomY(rect);
            Get_BottomY(rect) = Get_BottomY(current_rect);
            break;
    }

    (void) Trial_Grow(twinp, rect, side, &pt, State_Get_Timestamp());

    switch (side){
        case Left:
            Get_LeftX(rect) = Get_PtX(pt);
            break;
       case Right:
            Get_RightX(rect) = Get_PtX(pt);
            break;
       case Top:
            Get_TopY(rect) = Get_PtY(pt);
            break;
       case Bottom:
            Get_BottomY(rect) = Get_PtY(pt);
            break;
    }
    
    return(rect);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static TWRectangle Tilwin_Stretch_Top_Bottom( win, rect, siz )
    Tilwin *win;
    TWRectangle rect;
    Size siz;
{
    if (! Tilwin_Get_Window_Option(win,FIXED_TOP_EDGE))
    {
        rect.top_y = rect.bottom_y - (siz.height - 1);
        rect = Tilwin_Stretch( win, rect, Top );
    }    
    if (! Tilwin_Get_Window_Option(win,FIXED_BOTTOM_EDGE))
    {
        rect.bottom_y = rect.top_y + (siz.height - 1);
        rect = Tilwin_Stretch( win, rect, Bottom );
    }
    return rect;
}

/* ------------------------------------------------------------ */

static TWRectangle Tilwin_Stretch_Bottom_Top( win, rect, siz )
    Tilwin *win;
    TWRectangle rect;
    Size siz;
{
    if (! Tilwin_Get_Window_Option(win,FIXED_BOTTOM_EDGE))
    {
        rect.bottom_y = rect.top_y + (siz.height - 1);
        rect = Tilwin_Stretch( win, rect, Bottom );
    }    
    if (! Tilwin_Get_Window_Option(win,FIXED_TOP_EDGE))
    {
        rect.top_y = rect.bottom_y - (siz.height - 1);
        rect = Tilwin_Stretch( win, rect, Top );
    }
    return rect;
}

/* ------------------------------------------------------------ */

static TWRectangle Tilwin_Stretch_Left_Right( win, rect, siz )
    Tilwin *win;
    TWRectangle rect;
    Size siz;
{
    if (! Tilwin_Get_Window_Option(win,FIXED_LEFT_EDGE))
    {
        rect.left_x = rect.right_x - (siz.width - 1);
        rect = Tilwin_Stretch( win, rect, Left );
    }    
    if (! Tilwin_Get_Window_Option(win,FIXED_RIGHT_EDGE))
    {
        rect.right_x = rect.left_x + (siz.width - 1);
        rect = Tilwin_Stretch( win, rect, Right );
    }
    return rect;
}

/* ------------------------------------------------------------ */

static TWRectangle Tilwin_Stretch_Right_Left( win, rect, siz )
    Tilwin *win;
    TWRectangle rect;
    Size siz;
{
    if (! Tilwin_Get_Window_Option(win,FIXED_RIGHT_EDGE))
    {
        rect.right_x = rect.left_x + (siz.width - 1);
        rect = Tilwin_Stretch( win, rect, Right );
    }    
    if (! Tilwin_Get_Window_Option(win,FIXED_LEFT_EDGE))
    {
        rect.left_x = rect.right_x - (siz.width - 1);
        rect = Tilwin_Stretch( win, rect, Left );
    }
    return rect;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static TWRectangle Tilwin_Stretch_Nearest( winp, rect, siz, pt )
    Tilwin *winp;
    TWRectangle rect;
    Size siz;
    TWPoint pt;
{
    TWPoint center;
    bool vert_first;
    Size try_siz, rect_siz;
    
    Tilwin_Calc_Location_Size( center, rect_siz, rect);
        
    if ( siz.height <= rect_siz.height )
        vert_first = TRUE;
    else if ( siz.width <= rect_siz.width )
        vert_first = FALSE;
    else if ( Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) &&
         (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) ) )
        vert_first = TRUE;
    else if ( Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) &&
         (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) ) )
        vert_first = FALSE;
    else
        vert_first = Tilwin_Get_Global_Option(PRORATE_VERTICALLY_FIRST);

    if ( vert_first )
    {
        try_siz = siz;
        if ( pt.y < center.y )
        {
            try_siz.height = ( (siz.height + rect_siz.height)/2 + center.y - pt.y ) & (~1);
            if ( try_siz.height > siz.height )
                try_siz.height = siz.height;
            rect = Tilwin_Stretch_Top_Bottom( winp, rect, try_siz );
            rect = Tilwin_Stretch_Bottom_Top( winp, rect, siz );
        }
        else
        {
            try_siz.height = ( (siz.height + rect_siz.height)/2 + pt.y - center.y ) & (~1);
            if ( try_siz.height > siz.height )
                try_siz.height = siz.height;
            rect = Tilwin_Stretch_Bottom_Top( winp, rect, try_siz );
            rect = Tilwin_Stretch_Top_Bottom( winp, rect, siz );
        }

        try_siz = siz;
        if ( pt.x < center.x )
        {
            try_siz.width = ( (siz.width + rect_siz.width)/2 + center.x - pt.x ) & (~1);
            if ( try_siz.width > siz.width )
                try_siz.width = siz.width;
            rect = Tilwin_Stretch_Left_Right( winp, rect, try_siz );
            rect = Tilwin_Stretch_Right_Left( winp, rect, siz );
        }
        else
        {
            try_siz.width = ( (siz.width + rect_siz.width)/2 + pt.x - center.x ) & (~1);
            if ( try_siz.width > siz.width )
                try_siz.width = siz.width;
            rect = Tilwin_Stretch_Right_Left( winp, rect, try_siz );
            rect = Tilwin_Stretch_Left_Right( winp, rect, siz );
        }
    }
    else
    {
        try_siz = siz;
        if ( pt.x < center.x )
        {
            try_siz.width = ( (siz.width + rect_siz.width)/2 + center.x - pt.x ) & (~1);
            if ( try_siz.width > siz.width )
                try_siz.width = siz.width;
            rect = Tilwin_Stretch_Left_Right( winp, rect, try_siz );
            rect = Tilwin_Stretch_Right_Left( winp, rect, siz );
        }
        else
        {
            try_siz.width = ( (siz.width + rect_siz.width)/2 + pt.x - center.x ) & (~1);
            if ( try_siz.width > siz.width )
                try_siz.width = siz.width;
            rect = Tilwin_Stretch_Right_Left( winp, rect, try_siz );
            rect = Tilwin_Stretch_Left_Right( winp, rect, siz );
        }

        try_siz = siz;
        if ( pt.y < center.y )
        {
            try_siz.height = ( (siz.height + rect_siz.height)/2 + center.y - pt.y ) & (~1);
            if ( try_siz.height > siz.height )
                try_siz.height = siz.height;
            rect = Tilwin_Stretch_Top_Bottom( winp, rect, try_siz );
            rect = Tilwin_Stretch_Bottom_Top( winp, rect, siz );
        }
        else
        {
            try_siz.height = ( (siz.height + rect_siz.height)/2 + pt.y - center.y ) & (~1);
            if ( try_siz.height > siz.height )
                try_siz.height = siz.height;
            rect = Tilwin_Stretch_Bottom_Top( winp, rect, try_siz );
            rect = Tilwin_Stretch_Top_Bottom( winp, rect, siz );
        }
    }
    
    return rect;
}

/* ------------------------------------------------------------ */

static TWRectangle Tilwin_Stretch_Farthest( winp, rect, siz, pt )
    Tilwin *winp;
    TWRectangle rect;
    Size siz;
    TWPoint pt;
{
    TWPoint center;
    bool vert_first;
        
    if ( siz.height <= Tilwin_Get_Size(winp).height )
        vert_first = TRUE;
    else if ( siz.width <= Tilwin_Get_Size(winp).width )
        vert_first = FALSE;
    else if ( Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) &&
         (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) ) )
        vert_first = TRUE;
    else if ( Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) &&
         (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) ) )
        vert_first = FALSE;
    else
        vert_first = Tilwin_Get_Global_Option(PRORATE_VERTICALLY_FIRST);

    center = Tilwin_Get_Center(winp);

    if ( vert_first )
    {
        if ( pt.y > center.y )
            rect = Tilwin_Stretch_Top_Bottom( winp, rect, siz );
        else
            rect = Tilwin_Stretch_Bottom_Top( winp, rect, siz );
        if ( pt.x > center.x )
            rect = Tilwin_Stretch_Left_Right( winp, rect, siz );
        else
            rect = Tilwin_Stretch_Right_Left( winp, rect, siz );
    }
    else
    {
        if ( pt.x > center.x )
            rect = Tilwin_Stretch_Left_Right( winp, rect, siz );
        else
            rect = Tilwin_Stretch_Right_Left( winp, rect, siz );
        if ( pt.y > center.y )
            rect = Tilwin_Stretch_Top_Bottom( winp, rect, siz );
        else
            rect = Tilwin_Stretch_Bottom_Top( winp, rect, siz );
    }
    
    return rect;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

bool Tilwin_Enlarge_Nearest( twinp, pt, siz )
    Tilwinp twinp;
    TWPoint pt;
    Size siz;
{
    Tilwin *winp = (Tilwin *) twinp;
    TWRectangle rect;
    Size stretch_siz;
    TWPoint center;
    bool result;

    siz.width = siz.width & (~1);
    siz.height = siz.height & (~1);

    if ( ( siz.width == Tilwin_Get_Size(winp).width ) &&
         ( siz.height == Tilwin_Get_Size(winp).height ) )
        return TRUE;

    rect = Tilwin_Get_Rectangle(winp);

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
    {
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
        {
            rect = Tilwin_Stretch_Nearest( winp, rect, siz, pt );
        } )
        if ( Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) )
        {
            rect = Tilwin_Stretch_Nearest( winp, rect, siz, pt );
        }
    } )
    if ( Tilwin_Get_Global_Option(PREFER_CLOSE_TO_SHRINK) &&
          Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_CLOSE) )
    {
        rect = Tilwin_Stretch_Nearest( winp, rect, siz, pt );
    }

    Tilwin_Calc_Location_Size( center, stretch_siz, rect );

    if ( ( Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ||
           Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) ) &&
         ( stretch_siz.height != siz.height ) )
         return FALSE;
    if ( ( Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ||
           Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) ) &&
         ( stretch_siz.width != siz.width ) )
         return FALSE;

    global_excursion( ENABLE_GRAVITY, FALSE,
    {
        result = Tilwin_Open( (Tilwinp)winp, center, stretch_siz );
    } )
    
    return result;
}

/* ------------------------------------------------------------ */

bool Tilwin_Enlarge_Farthest( twinp, pt, siz )
    Tilwinp twinp;
    TWPoint pt;
    Size siz;
{
    Tilwin *winp = (Tilwin *)twinp;
    TWRectangle rect;
    Size stretch_siz;
    TWPoint center;
    bool result;

    siz.width = siz.width & (~1);
    siz.height = siz.height & (~1);

    if ( ( siz.width == Tilwin_Get_Size(winp).width ) &&
         ( siz.height == Tilwin_Get_Size(winp).height ) )
        return TRUE;

    rect = Tilwin_Get_Rectangle(winp);

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
    {
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
        {
            rect = Tilwin_Stretch_Farthest( winp, rect, siz, pt );
        } )
        if ( Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) )
        {
            rect = Tilwin_Stretch_Farthest( winp, rect, siz, pt );
        }
    } )
    if ( Tilwin_Get_Global_Option(PREFER_CLOSE_TO_SHRINK) &&
         Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_CLOSE) )
    {
        rect = Tilwin_Stretch_Farthest( winp, rect, siz, pt );
    }

    Tilwin_Calc_Location_Size( center, stretch_siz, rect );

    if ( ( Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ||
           Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) ) &&
         ( stretch_siz.height != siz.height ) )
         return FALSE;
    if ( ( Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ||
           Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) ) &&
         ( stretch_siz.width != siz.width ) )
         return FALSE;


    global_excursion( ENABLE_GRAVITY, FALSE,
    {
        result = Tilwin_Open( (Tilwinp)winp, center, stretch_siz );
    } )
    
    return result;
}

/* ------------------------------------------------------------ */

void Tilwin_Enlarge_Nearest_In_Area( winp, rect, pt, siz )
    Tilwin *winp;
    TWRectangle rect;
    TWPoint pt;
    Size siz;
{
    TWRectangle old_desktop_rect;

    old_desktop_rect = desktop_rect;

    if ( rect.left_x > desktop_rect.left_x )
        desktop_rect.left_x = rect.left_x;
    if ( rect.right_x < desktop_rect.right_x )
        desktop_rect.right_x = rect.right_x;
    if ( rect.top_y > desktop_rect.top_y )
        desktop_rect.top_y = rect.top_y;
    if ( rect.bottom_y < desktop_rect.bottom_y )
        desktop_rect.bottom_y = rect.bottom_y;

    Tilwin_Enlarge_Nearest( (Tilwinp)winp, pt, siz );

    desktop_rect = old_desktop_rect;
}

/* ------------------------------------------------------------ */

void Tilwin_Enlarge_Farthest_In_Area( winp, rect, pt, siz )
    Tilwin *winp;
    TWRectangle rect;
    TWPoint pt;
    Size siz;
{
    TWRectangle old_desktop_rect;

    old_desktop_rect = desktop_rect;

    if ( rect.left_x > desktop_rect.left_x )
        desktop_rect.left_x = rect.left_x;
    if ( rect.right_x < desktop_rect.right_x )
        desktop_rect.right_x = rect.right_x;
    if ( rect.top_y > desktop_rect.top_y )
        desktop_rect.top_y = rect.top_y;
    if ( rect.bottom_y < desktop_rect.bottom_y )
        desktop_rect.bottom_y = rect.bottom_y;

    Tilwin_Enlarge_Farthest( (Tilwinp)winp, pt, siz );

    desktop_rect = old_desktop_rect;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

#define grid_mult 2
#define grid_min 3

/* ------------------------------------------------------------ */

static bool Tilwin_Open_Grid_Nearest( winp, rect, pt, siz )
    Tilwin *winp;
    TWRectangle rect;
    TWPoint pt;
    Size siz;
{
    int i, j;
    int gran_top, gran_bottom, gran_left, gran_right;
    int max_top, max_bottom, max_left, max_right;
    int diff_top, diff_bottom, diff_left, diff_right;
    bool found, done;
    TWPoint center;
    TWPoint cur_center;
    TWPoint best_pt;
    TWPoint max_pt;
    int dcur;
    int dmin;
    int extra_x, extra_y;
    TWRectangle max_rect;
    bool better;
    int num_closed;
    int num_expensive;
    int num_affected;
    int stamp;

    stamp = State_Get_Timestamp();

    num_closed = MUCHO_WINDOWS;
    num_expensive = MUCHO_WINDOWS;
    num_affected = MUCHO_WINDOWS;
    
    cur_center = Tilwin_Get_Center(winp);

    if ( Tilwin_Get_Window_Option(winp,FIXED_TOP_EDGE) )
    {
        gran_top = 0;
        gran_bottom = 0;

	Get_LeftX(max_rect) = Get_RightX(max_rect) = 0;
        Get_TopY(max_rect) = Get_TopY(rect);
        Get_BottomY(max_rect) = Get_TopY(rect) + (Get_Height(siz) - 1);
	COMPUTE_CENTER(max_rect, max_pt);
        Get_PtY(pt) = Get_PtY(max_pt);

        extra_y = 0;
    }
    else if ( Tilwin_Get_Window_Option(winp,FIXED_BOTTOM_EDGE) )
    {
        gran_top = 0;
        gran_bottom = 0;

	Get_LeftX(max_rect) = Get_RightX(max_rect) = 0;
        Get_BottomY(max_rect) = Get_BottomY(rect);
        Get_TopY(max_rect) = Get_BottomY(rect) - (Get_Height(siz) - 1);
        COMPUTE_CENTER(max_rect, max_pt);
        Get_PtY(pt) = Get_PtY(max_pt);

        extra_y = 0;
    }
    else
    {
	Get_LeftX(max_rect) = Get_RightX(max_rect) = 0;
        Get_TopY(max_rect) = Get_TopY(rect);
        Get_BottomY(max_rect) = Get_TopY(rect) + (Get_Height(siz) - 1);
	COMPUTE_CENTER(max_rect, max_pt);
        max_top = (int) Get_PtY(max_pt);
        
	Get_LeftX(max_rect) = Get_RightX(max_rect) = 0;
        Get_BottomY(max_rect) = Get_BottomY(rect);
        Get_TopY(max_rect) = Get_BottomY(rect) - (Get_Height(siz) - 1);
        COMPUTE_CENTER(max_rect, max_pt);
        max_bottom = (int) Get_PtY(max_pt);

        if ( pt.y < max_top )
            pt.y = max_top;
        else if ( pt.y > max_bottom )
            pt.y = max_bottom;
        diff_top = pt.y - max_top;
        diff_bottom =  max_bottom - pt.y;
    
        if ( diff_top == 0 )
            gran_top = 0;
        else
        {
            gran_top = ( grid_mult * diff_top ) / siz.height;
            if ( gran_top < grid_min ) gran_top = grid_min;
        }
    
        if ( diff_bottom == 0 )
            gran_bottom = 0;
        else
        {
            gran_bottom = ( grid_mult * diff_bottom ) / siz.height;
            if ( gran_bottom < grid_min ) gran_bottom = grid_min;
        }
        extra_y = ( cur_center.y >= max_top ) &&
                  ( cur_center.y <= max_bottom );
    }

    if ( Tilwin_Get_Window_Option(winp,FIXED_LEFT_EDGE) )
    {
        gran_left = 0;
        gran_right = 0;

	Get_TopY(max_rect) = Get_BottomY(max_rect) = 0;
        Get_LeftX(max_rect) = Get_LeftX(rect);
        Get_RightX(max_rect) = Get_LeftX(rect) + (Get_Width(siz) - 1);
	COMPUTE_CENTER(max_rect, max_pt);
        Get_PtX(pt) = Get_PtX(max_pt);

        extra_x = 0;
    }
    else if ( Tilwin_Get_Window_Option(winp,FIXED_RIGHT_EDGE) )
    {
        gran_left = 0;
        gran_right = 0;

	Get_TopY(max_rect) = Get_BottomY(max_rect) = 0;
        Get_RightX(max_rect) = Get_RightX(rect);
        Get_LeftX(max_rect) = Get_RightX(rect) - (Get_Width(siz) - 1);
        COMPUTE_CENTER(max_rect, max_pt);
        Get_PtX(pt) = Get_PtX(max_pt);

        extra_x = 0;
    }
    else
    {
	Get_TopY(max_rect) = Get_BottomY(max_rect) = 0;
        Get_LeftX(max_rect) = Get_LeftX(rect);
        Get_RightX(max_rect) = Get_LeftX(rect) + (Get_Width(siz) - 1);
	COMPUTE_CENTER(max_rect, max_pt);
        max_left = (int) Get_PtX(max_pt);

	Get_TopY(max_rect) = Get_BottomY(max_rect) = 0;
        Get_RightX(max_rect) = Get_RightX(rect);
        Get_LeftX(max_rect) = Get_RightX(rect) - (Get_Width(siz) - 1);
        COMPUTE_CENTER(max_rect, max_pt);
        max_right = (int) Get_PtX(max_pt);

        if ( pt.x < max_left )
            pt.x = max_left;
        else if ( pt.x > max_right )
            pt.x = max_right;
        diff_left = pt.x - max_left;
        diff_right =  max_right - pt.x;
    
        if ( diff_left == 0 )
            gran_left = 0;
        else
        {
            gran_left = ( grid_mult * diff_left ) / siz.height;
            if ( gran_left < grid_min ) gran_left = grid_min;
        }
    
        if ( diff_right == 0 )
            gran_right = 0;
        else
        {
            gran_right = ( grid_mult * diff_right ) / siz.height;
            if ( gran_right < grid_min ) gran_right = grid_min;
        }
        extra_x = ( cur_center.x >= max_left ) &&
                  ( cur_center.x <= max_right );
    }

    found = FALSE;
    done = FALSE;

    for ( i = -gran_left; i <= (gran_right + extra_x); i++ )
    {
        if ( done ) break;
        if ( i < 0 )
            center.x = pt.x + ( ( i * diff_left ) / gran_left );
        else if ( i == 0 )
            center.x = pt.x;
        else if ( i > gran_right )
            center.x = cur_center.x;
        else
            center.x = pt.x + ( ( i * diff_right ) / gran_right );

        for ( j = -gran_top; j <= (gran_bottom + extra_y); j++ )
        {
            if ( done ) break;
            if ( j < 0 )
                center.y = pt.y + ( ( j * diff_top ) / gran_top );
            else if ( j == 0 )
                center.y = pt.y;
            else if ( j > gran_bottom )
                center.y = cur_center.y;
            else
                center.y = pt.y + ( ( j * diff_bottom ) / gran_bottom );

            dcur = ( (center.y - pt.y) * (center.y - pt.y) ) +
                   ( (center.x - pt.x) * (center.x - pt.x) );

            if ( ( num_affected > 0 ) || ( dcur < dmin ) )
            {
                better = found && ( dcur >= dmin );

                MAKE_RECTANGLE( center, siz, rect );

                if ( Trial_Improve_Open( winp, rect, stamp, better,
                     &num_closed, &num_expensive, &num_affected ) )
                {
                    found = TRUE;
                    best_pt = center;
                    dmin = dcur;
                    if ( Tilwin_Get_Global_Option( FIRST_FIT ) )
                        done = TRUE;
                }
            }
        }
    }

    if ( found )
        return Tilwin_Open( (Tilwinp)winp, best_pt, siz );
    else
        return FALSE;

}

/* ------------------------------------------------------------ */

static bool Tilwin_Open_Grid_Farthest( winp, rect, pt, siz )
    Tilwin *winp;
    TWRectangle rect;
    TWPoint pt;
    Size siz;
{
    int i, j;
    int gran_top, gran_bottom, gran_left, gran_right;
    int max_top, max_bottom, max_left, max_right;
    int diff_top, diff_bottom, diff_left, diff_right;
    bool found, done;
    TWPoint center;
    TWPoint cur_center;
    TWPoint best_pt;
    TWPoint max_pt;
    int dcur;
    int dmax;
    int extra_x, extra_y;
    TWRectangle max_rect;
    bool better;
    int num_closed;
    int num_expensive;
    int num_affected;
    int stamp;

    stamp = State_Get_Timestamp();

    num_closed = MUCHO_WINDOWS;
    num_expensive = MUCHO_WINDOWS;
    num_affected = MUCHO_WINDOWS;

    cur_center = Tilwin_Get_Center(winp);

    if ( Tilwin_Get_Window_Option(winp,FIXED_TOP_EDGE) )
    {
        gran_top = 0;
        gran_bottom = 0;

	Get_LeftX(max_rect) = Get_RightX(max_rect) = 0;
        Get_TopY(max_rect) = Get_TopY(rect);
        Get_BottomY(max_rect) = Get_TopY(rect) + (Get_Height(siz) - 1);
	COMPUTE_CENTER(max_rect, max_pt);
        Get_PtY(pt) = Get_PtY(max_pt);

        extra_y = 0;
    }
    else if ( Tilwin_Get_Window_Option(winp,FIXED_BOTTOM_EDGE) )
    {
        gran_top = 0;
        gran_bottom = 0;

	Get_LeftX(max_rect) = Get_RightX(max_rect) = 0;
        Get_BottomY(max_rect) = Get_BottomY(rect);
        Get_TopY(max_rect) = Get_BottomY(rect) - (Get_Height(siz) - 1);
        COMPUTE_CENTER(max_rect, max_pt);
        Get_PtY(pt) = Get_PtY(max_pt);

        extra_y = 0;
    }
    else
    {
	Get_LeftX(max_rect) = Get_RightX(max_rect) = 0;
        Get_TopY(max_rect) = Get_TopY(rect);
        Get_BottomY(max_rect) = Get_TopY(rect) + (Get_Height(siz) - 1);
	COMPUTE_CENTER(max_rect, max_pt);
        max_top = (int) Get_PtY(max_pt);
        
	Get_LeftX(max_rect) = Get_RightX(max_rect) = 0;
        Get_BottomY(max_rect) = Get_BottomY(rect);
        Get_TopY(max_rect) = Get_BottomY(rect) - (Get_Height(siz) - 1);
        COMPUTE_CENTER(max_rect, max_pt);
        max_bottom = (int) Get_PtY(max_pt);

        if ( pt.y < max_top )
            pt.y = max_top;
        else if ( pt.y > max_bottom )
            pt.y = max_bottom;
        diff_top = pt.y - max_top;
        diff_bottom =  max_bottom - pt.y;
    
        if ( diff_top == 0 )
            gran_top = 0;
        else
        {
            gran_top = ( grid_mult * diff_top ) / siz.height;
            if ( gran_top < grid_min ) gran_top = grid_min;
        }
    
        if ( diff_bottom == 0 )
            gran_bottom = 0;
        else
        {
            gran_bottom = ( grid_mult * diff_bottom ) / siz.height;
            if ( gran_bottom < grid_min ) gran_bottom = grid_min;
        }
        extra_y = ( cur_center.y >= max_top ) &&
                  ( cur_center.y <= max_bottom );
    }

    if ( Tilwin_Get_Window_Option(winp,FIXED_LEFT_EDGE) )
    {
        gran_left = 0;
        gran_right = 0;

	Get_TopY(max_rect) = Get_BottomY(max_rect) = 0;
        Get_LeftX(max_rect) = Get_LeftX(rect);
        Get_RightX(max_rect) = Get_LeftX(rect) + (Get_Width(siz) - 1);
	COMPUTE_CENTER(max_rect, max_pt);
        Get_PtX(pt) = Get_PtX(max_pt);

        extra_x = 0;
    }
    else if ( Tilwin_Get_Window_Option(winp,FIXED_RIGHT_EDGE) )
    {
        gran_left = 0;
        gran_right = 0;

	Get_TopY(max_rect) = Get_BottomY(max_rect) = 0;
        Get_RightX(max_rect) = Get_RightX(rect);
        Get_LeftX(max_rect) = Get_RightX(rect) - (Get_Width(siz) - 1);
        COMPUTE_CENTER(max_rect, max_pt);
        Get_PtX(pt) = Get_PtX(max_pt);

        extra_x = 0;
    }
    else
    {
	Get_TopY(max_rect) = Get_BottomY(max_rect) = 0;
        Get_LeftX(max_rect) = Get_LeftX(rect);
        Get_RightX(max_rect) = Get_LeftX(rect) + (Get_Width(siz) - 1);
	COMPUTE_CENTER(max_rect, max_pt);
        max_left = (int) Get_PtX(max_pt);

	Get_TopY(max_rect) = Get_BottomY(max_rect) = 0;
        Get_RightX(max_rect) = Get_RightX(rect);
        Get_LeftX(max_rect) = Get_RightX(rect) - (Get_Width(siz) - 1);
        COMPUTE_CENTER(max_rect, max_pt);
        max_right = (int) Get_PtX(max_pt);

        if ( pt.x < max_left )
            pt.x = max_left;
        else if ( pt.x > max_right )
            pt.x = max_right;
        diff_left = pt.x - max_left;
        diff_right =  max_right - pt.x;
    
        if ( diff_left == 0 )
            gran_left = 0;
        else
        {
            gran_left = ( grid_mult * diff_left ) / siz.height;
            if ( gran_left < grid_min ) gran_left = grid_min;
        }
    
        if ( diff_right == 0 )
            gran_right = 0;
        else
        {
            gran_right = ( grid_mult * diff_right ) / siz.height;
            if ( gran_right < grid_min ) gran_right = grid_min;
        }
        extra_x = ( cur_center.x >= max_left ) &&
                  ( cur_center.x <= max_right );
    }

    found = FALSE;
    done = FALSE;

    for ( i = -gran_left; i <= (gran_right + extra_x); i++ )
    {
        if ( done ) break;
        if ( i < 0 )
            center.x = pt.x + ( ( i * diff_left ) / gran_left );
        else if ( i == 0 )
            center.x = pt.x;
        else if ( i > gran_right )
            center.x = cur_center.x;
        else
            center.x = pt.x + ( ( i * diff_right ) / gran_right );

        for ( j = -gran_top; j <= (gran_bottom + extra_y); j++ )
        {
            if ( done ) break;
            if ( j < 0 )
                center.y = pt.y + ( ( j * diff_top ) / gran_top );
            else if ( j == 0 )
                center.y = pt.y;
            else if ( j > gran_bottom )
                center.y = cur_center.y;
            else
                center.y = pt.y + ( ( j * diff_bottom ) / gran_bottom );

            dcur = ( (center.y - pt.y) * (center.y - pt.y) ) +
                   ( (center.x - pt.x) * (center.x - pt.x) );

            if ( ( num_affected > 0 ) || ( dcur > dmax ) )
            {
                better = found && ( dcur <= dmax );

                MAKE_RECTANGLE( center, siz, rect );

                if ( Trial_Improve_Open( winp, rect, stamp, better,
                     &num_closed, &num_expensive, &num_affected ) )
                {
                    found = TRUE;
                    best_pt = center;
                    dmax = dcur;
                    if ( Tilwin_Get_Global_Option( FIRST_FIT ) )
                        done = TRUE;
                }
            }
        }
    }

    if ( found )
        return Tilwin_Open( (Tilwinp)winp, best_pt, siz );
    else
        return FALSE;

}

/* ------------------------------------------------------------ */

bool Tilwin_Open_Nearest_In_Area( twinp, rect, pt, siz )
    Tilwinp twinp;
    TWRectangle rect;
    TWPoint pt;
    Size siz;
{
    Tilwin *winp = (Tilwin *)twinp;
    bool result;
    Size minsiz;

    if ( rect.top_y < desktop_rect.top_y )
        rect.top_y = desktop_rect.top_y;
    if ( rect.bottom_y > desktop_rect.bottom_y )
        rect.bottom_y = desktop_rect.bottom_y;
    if ( rect.left_x < desktop_rect.left_x )
        rect.left_x = desktop_rect.left_x;
    if ( rect.right_x > desktop_rect.right_x ) 
        rect.right_x = desktop_rect.right_x;

    siz.width = siz.width & (~1);
    siz.height = siz.height & (~1);

    minsiz = siz;
    
    if (! Tilwin_Get_Window_Option(winp,FIXED_SIZE) )
    {
        if (! Tilwin_Get_Window_Option(winp,FIXED_WIDTH))
            minsiz.width = winp->min_size.width;
        if (! Tilwin_Get_Window_Option(winp,FIXED_HEIGHT))
            minsiz.height = winp->min_size.height;
    }

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
    {
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
        {
            result = Tilwin_Open_Grid_Nearest( winp, rect, pt, siz );
        } )
        if ( (! result) && Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) )
            result = Tilwin_Open_Grid_Nearest( winp, rect, pt, siz );
    } )

    if (! result)
    {
        if ( Tilwin_Get_Global_Option(PREFER_CLOSE_TO_SHRINK) )
        {
            if ( Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_CLOSE) )
                result = Tilwin_Open_Grid_Nearest( winp, rect, pt, siz );
        
            if ( (! result) && (! Same_Size(siz,minsiz)) )
            {
                global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
                {
                    global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
                    {
                        result = Tilwin_Open_Grid_Nearest( winp, rect, pt, minsiz );
                    } )
                    if ( (! result) && Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) )
                        result = Tilwin_Open_Grid_Nearest( winp, rect, pt, minsiz );
                } )
                if ( result )
                    Tilwin_Enlarge_Nearest_In_Area( winp, rect, pt, siz );
            }
        }
        else
        {
            if (! Same_Size(siz,minsiz))
            {
                global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
                {
                    global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
                    {
                        result = Tilwin_Open_Grid_Nearest( winp, rect, pt, minsiz );
                    } )
                    if ( (! result) && Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) )
                        result = Tilwin_Open_Grid_Nearest( winp, rect, pt, minsiz );
                } )
                if ( result )
                    Tilwin_Enlarge_Nearest_In_Area( winp, rect, pt, siz );
            }
        
            if ( (! result) &&
                 Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_CLOSE) )
                result = Tilwin_Open_Grid_Nearest( winp, rect, pt, siz );
        }
    }

    if ( (! result) && (! Same_Size(siz,minsiz)) &&
         Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_CLOSE) )
    {
        result = Tilwin_Open_Grid_Nearest( winp, rect, pt, minsiz );
        if ( result )
            Tilwin_Enlarge_Nearest_In_Area( winp, rect, pt, siz );
    }

    if ( result )
        Tilwin_Slide_Nearest_In_Area( winp, rect, pt );

    return result;

}

/* ------------------------------------------------------------ */

bool Tilwin_Open_Farthest_In_Area( twinp, rect, pt, siz )
    Tilwinp twinp;
    TWRectangle rect;
    TWPoint pt;
    Size siz;
{
    Tilwin *winp = (Tilwin *)twinp;
    bool result;
    Size minsiz;

    if ( rect.top_y < desktop_rect.top_y )
        rect.top_y = desktop_rect.top_y;
    if ( rect.bottom_y > desktop_rect.bottom_y )
        rect.bottom_y = desktop_rect.bottom_y;
    if ( rect.left_x < desktop_rect.left_x )
        rect.left_x = desktop_rect.left_x;
    if ( rect.right_x > desktop_rect.right_x ) 
        rect.right_x = desktop_rect.right_x;

    siz.width = siz.width & (~1);
    siz.height = siz.height & (~1);

    minsiz = siz;
    
    if (! Tilwin_Get_Window_Option(winp,FIXED_SIZE) )
    {
        if (! Tilwin_Get_Window_Option(winp,FIXED_WIDTH))
            minsiz.width = winp->min_size.width;
        if (! Tilwin_Get_Window_Option(winp,FIXED_HEIGHT))
            minsiz.height = winp->min_size.height;
    }

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
    {
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
        {
            result = Tilwin_Open_Grid_Farthest( winp, rect, pt, siz );
        } )
        if ( (! result) && Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) )
            result = Tilwin_Open_Grid_Farthest( winp, rect, pt, siz );
    } )

    if (! result)
    {
        if ( Tilwin_Get_Global_Option(PREFER_CLOSE_TO_SHRINK) )
        {
            if ( Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_CLOSE) )
                result = Tilwin_Open_Grid_Farthest( winp, rect, pt, siz );
        
            if ( (! result) && (! Same_Size(siz,minsiz)) )
            {
                global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
                {
                    global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
                    {
                        result = Tilwin_Open_Grid_Farthest( winp, rect, pt, minsiz );
                    } )
                    if ( (! result) && Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) )
                        result = Tilwin_Open_Grid_Farthest( winp, rect, pt, minsiz );
                } )
                if ( result )
                    Tilwin_Enlarge_Farthest_In_Area( winp, rect, pt, siz );
            }
        }
        else
        {
            if (! Same_Size(siz,minsiz))
            {
                global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
                {
                    global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
                    {
                        result = Tilwin_Open_Grid_Farthest( winp, rect, pt, minsiz );
                    } )
                    if ( (! result) && Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) )
                        result = Tilwin_Open_Grid_Farthest( winp, rect, pt, minsiz );
                } )
                if ( result )
                    Tilwin_Enlarge_Farthest_In_Area( winp, rect, pt, siz );
            }
        
            if ( (! result) &&
                 Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_CLOSE) )
                result = Tilwin_Open_Grid_Farthest( winp, rect, pt, siz );
        }
    }

    if ( (! result) && (! Same_Size(siz,minsiz)) &&
         Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_CLOSE) )
    {
        result = Tilwin_Open_Grid_Farthest( winp, rect, pt, minsiz );
        if ( result )
            Tilwin_Enlarge_Farthest_In_Area( winp, rect, pt, siz );
    }

    if ( result )
        Tilwin_Slide_Farthest_In_Area( winp, rect, pt );

    return result;

}

/* ------------------------------------------------------------ */

bool Tilwin_Open_Best_In_Area( twinp, rect, siz )
    Tilwinp twinp;
    TWRectangle rect;
    Size siz;
{
    return Tilwin_Open_Farthest_In_Area( twinp, rect,
        desktop_center, siz );
}
