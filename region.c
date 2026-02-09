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

#ifndef TILEMENU
#include "tilemenuP.h"
#endif

#ifndef REGION
#include "regionP.h"
#endif

#include "userglobD.h"

#include "bodyreg.h"
#include "tilecrsr.h"

#include "uwinD.h"

/* ------------------------------------------------------------ */

TWRegion back_region;

TWRegion header_region;
TWRegion body_region;

TWRegion left_region;
TWRegion right_region;
TWRegion top_region;
TWRegion bottom_region;

TWRegion top_left_region;
TWRegion top_right_region;
TWRegion bottom_left_region;
TWRegion bottom_right_region;

TWRegion zoom_gadget_region;
TWRegion move_gadget_region;

TWRegion rtl_region;
TWRegion icon_region;

/* ------------------------------------------------------------ */

void Region_Init()
{
    back_region.region_enum = background;

    header_region.region_enum = header;

    body_region.region_enum = body;


    left_region.region_enum = edge;
    left_region.region_info.side = Left;

    right_region.region_enum = edge;
    right_region.region_info.side = Right;

    top_region.region_enum = edge;
    top_region.region_info.side = Top;

    bottom_region.region_enum = edge;
    bottom_region.region_info.side = Bottom;

    top_left_region.region_enum = corner;
    top_left_region.region_info.side = Top_Left;

    top_right_region.region_enum = corner;
    top_right_region.region_info.side = Top_Right;

    bottom_left_region.region_enum = corner;
    bottom_left_region.region_info.side = Bottom_Left;

    bottom_right_region.region_enum = corner;
    bottom_right_region.region_info.side = Bottom_Right;

    zoom_gadget_region.region_enum = zoom_gadget;
    move_gadget_region.region_enum = move_gadget;


    icon_region.region_enum = icon;

    rtl_region.region_enum = rtl;
}

/* ------------------------------------------------------------ */

TWRegion Region_Make_Edge( side )
    Side side;
{
    TWRegion region;

    region.region_enum = edge;
    region.region_info.side = side;
    return region;
}

/* ------------------------------------------------------------ */

TWRegion Region_Make_Corner( side )
    Side side;
{
    TWRegion region;

    region.region_enum = corner;
    region.region_info.side = side;
    return region;
}

/* ------------------------------------------------------------ */

Size Region_Minimum_Size()
{
    Size siz;
    siz.width = (5 + 2*BORDER_SIZE_VAL + 2*GADGET_WIDTH_VAL) & (~1);
    siz.height = (5 + 2*BORDER_SIZE_VAL + 20) & (~1);
    return siz;
}

/* ------------------------------------------------------------ */

    /* Given a point on the desktop, returns that point translated */
    /* to the body of the icon */

static TWPoint Region_Icon_Translate( uwinp, pt )
    Userwin *uwinp;
    TWPoint pt;
{
    TWPoint result;

    result.x = pt.x - uwinp->icon_body_rect.left_x;
    result.y = pt.y - uwinp->icon_body_rect.top_y;

    return result;
}

/* ------------------------------------------------------------ */

    /* Given a point on the desktop, returns that point translated */
    /* to the body of the window */

TWPoint Region_Translate( uwinp, pt )
    Userwin *uwinp;
    TWPoint pt;
{
    TWPoint result;

    result.x = pt.x - Userwin_Get_Rectangle(uwinp).left_x;
    result.y = pt.y - Userwin_Get_Rectangle(uwinp).top_y;
    
    if ( Userwin_Get_Window_Option( uwinp, USE_BORDERS ) )
    {
        result.x -= BORDER_SIZE_VAL;
        result.y -= BORDER_SIZE_VAL;
    }

    if ( Userwin_Get_Window_Option( uwinp, USE_HEADER ) )
    {
        result.y -= uwinp->header_height;
        result.y -= INNER_BORDER_LINEWIDTH_VAL;
    }

    return result;
}

/* ------------------------------------------------------------ */

TWRectangle Region_Body_Rectangle( uwinp )
    Userwin *uwinp;
{
    TWRectangle rect;

    rect = Userwin_Get_Rectangle(uwinp);
    if ( Userwin_Get_Window_Option( uwinp, USE_BORDERS ) )
    {
        rect.left_x += BORDER_SIZE_VAL;
        rect.top_y += BORDER_SIZE_VAL;
        rect.right_x -= BORDER_SIZE_VAL;
        rect.bottom_y -= BORDER_SIZE_VAL;
    }

    if ( Userwin_Get_Window_Option( uwinp, USE_HEADER ) )
    {
        rect.top_y += uwinp->header_height;
        rect.top_y += INNER_BORDER_LINEWIDTH_VAL;
    }

    return rect;
}

/* ------------------------------------------------------------ */

Size Region_Body_Size( uwinp )
    Userwin *uwinp;
{
    Size siz;
    TWRectangle rect;

    rect = Region_Body_Rectangle(uwinp);
    COMPUTE_SIZE( rect, siz );
    return siz;
}

/* ------------------------------------------------------------ */

Size Region_Icon_Body_Size( uwinp )
    Userwin *uwinp;
{
    Size siz;
    TWRectangle rect;

    rect = uwinp->icon_body_rect;
    COMPUTE_SIZE( rect, siz );
    return siz;
}

/* ------------------------------------------------------------ */

    /*  Given a body rectangle, return the corresponding window rect */

TWRectangle Region_Adjust_Rectangle( uwinp, rect )
    Userwin *uwinp;
    TWRectangle rect;
{
    TWRectangle result;
    result = rect;
    
    if ( Userwin_Get_Window_Option( uwinp, USE_BORDERS ) )
    {
        result.left_x -= BORDER_SIZE_VAL;
        result.right_x += BORDER_SIZE_VAL;
        result.top_y -= BORDER_SIZE_VAL;
        result.bottom_y += BORDER_SIZE_VAL;
    }

    if ( Userwin_Get_Window_Option( uwinp, USE_HEADER ) )
    {
        result.top_y -= uwinp->header_height;
        result.top_y -= INNER_BORDER_LINEWIDTH_VAL;
    }

    return result;
}

/* ------------------------------------------------------------ */

    /*  Given a body size, return the corresponding window size */

Size Region_Adjust_Size( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    Size result;
    
    if ( Userwin_Get_Window_Option( uwinp, USE_BORDERS ) )
    {
        result.width = siz.width + 2 * BORDER_SIZE_VAL;
        result.height = siz.height + 2 * BORDER_SIZE_VAL;
    }
    else
        result = siz;

    if ( Userwin_Get_Window_Option( uwinp, USE_HEADER ) )
    {
        result.height += uwinp->header_height;
        result.height += INNER_BORDER_LINEWIDTH_VAL;
    }

    return result;
}

/* ------------------------------------------------------------ */

    /*  Given a window size, return the corresponding body size */

Size Region_Unadjust_Size( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    Size result;
    
    if ( Userwin_Get_Window_Option( uwinp, USE_BORDERS ) )
    {
        result.width = siz.width - 2 * BORDER_SIZE_VAL;
        result.height = siz.height - 2 * BORDER_SIZE_VAL;
    }
    else
        result = siz;

    if ( Userwin_Get_Window_Option( uwinp, USE_HEADER ) )
    {
        result.height -= uwinp->header_height;
        result.height -= INNER_BORDER_LINEWIDTH_VAL;
    }

    return result;
}

/* ------------------------------------------------------------ */

TWRegion Region_Locate( uwinp, pt )
    Userwin *uwinp;
    TWPoint pt;
{
    int win_height, win_width;
    int offset_x, offset_y;
    int offset;

    if ( uwinp == UWIN_NULL ) return back_region;

    if ( uwinp->current_type == rtl ) return rtl_region;
    if ( uwinp->current_type == icon ) 
    {
        icon_region.region_info.bodyregion =
            Bodyreg_Locate( uwinp, Region_Icon_Translate(uwinp, pt) );
        return icon_region;
    }

    win_height = Userwin_Get_Size(uwinp).height;
    win_width = Userwin_Get_Size(uwinp).width;

    offset_x = pt.x - Userwin_Get_Rectangle(uwinp).left_x;
    offset_y = pt.y - Userwin_Get_Rectangle(uwinp).top_y;

    if ( Userwin_Get_Window_Option( uwinp, USE_BORDERS ) )
    {
        if ( offset_x < BORDER_SIZE_VAL )
        {
            if ( UserGlobals_Get_Option(USE_CORNER_BORDERS) )
            {
                if ( offset_y < (2 * BORDER_SIZE_VAL) )
                    return top_left_region;
                else if ( offset_y >= (win_height - 2 * BORDER_SIZE_VAL) )
                    return bottom_left_region;
                else
                    return left_region;
            }
                else
                    return left_region;
        }
        else if ( offset_x >= (win_width - BORDER_SIZE_VAL) )
        {
            if ( UserGlobals_Get_Option(USE_CORNER_BORDERS) )
            {
                if ( offset_y < (2 * BORDER_SIZE_VAL) )
                    return top_right_region;
                else if ( offset_y >= (win_height - 2 * BORDER_SIZE_VAL) )
                    return bottom_right_region;
                else
                    return right_region;
            }
            else
                return right_region;
        }
        else if ( offset_y < BORDER_SIZE_VAL )
        {
            if ( UserGlobals_Get_Option(USE_CORNER_BORDERS) )
            {
                if ( offset_x < (2 * BORDER_SIZE_VAL) )
                    return top_left_region;
                else if ( offset_x >= (win_width - 2 * BORDER_SIZE_VAL) )
                    return top_right_region;
                else
                    return top_region;
            }
            else
                return top_region;
        }
        else if ( offset_y >= (win_height - BORDER_SIZE_VAL) )
        {
            if ( UserGlobals_Get_Option(USE_CORNER_BORDERS) )
            {
                if ( offset_x < (2 * BORDER_SIZE_VAL) )
                    return bottom_left_region;
                else if ( offset_x >= (win_width - 2 * BORDER_SIZE_VAL) )
                    return bottom_right_region;
                else
                    return bottom_region;
            }
            else
                return bottom_region;
        }
        else
            offset = BORDER_SIZE_VAL + INNER_BORDER_LINEWIDTH_VAL;
    }
    else
        offset = INNER_BORDER_LINEWIDTH_VAL;

    if ( Userwin_Get_Window_Option( uwinp, USE_HEADER ) &&
         ( offset_y < (offset + uwinp->header_height) ) )
    {
        if ( Userwin_Get_Window_Option( uwinp, USE_GADGETS ) )
        {        
            if ( offset_x < (offset + GADGET_WIDTH_VAL) )
                return zoom_gadget_region;
            else if ( ( Userwin_Get_Window_Option( uwinp, USE_MOVE_GADGET ) ) &&
                    ( offset_x >= ( win_width - ( offset + GADGET_WIDTH_VAL ) ) ) )
                return move_gadget_region;
            else
                return header_region;
        }
        else
            return header_region;
    }
    else
    {
        body_region.region_info.bodyregion =
            Bodyreg_Locate( uwinp, Region_Translate(uwinp, pt) );
        return body_region;
    }
}

/* ------------------------------------------------------------ */

TWRectangle Region_Header_Rect( uwinp )
    Userwin *uwinp;
{
    TWRectangle rect;
    rect = Userwin_Get_Rectangle(uwinp);

    if ( Userwin_Get_Window_Option( uwinp,USE_BORDERS ) )
    {
        rect.top_y += BORDER_SIZE_VAL;
        rect.left_x += BORDER_SIZE_VAL;
        rect.right_x -= BORDER_SIZE_VAL;
    }

    rect.bottom_y = rect.top_y;
    if ( Userwin_Get_Window_Option( uwinp, USE_HEADER ) )
    {
        rect.bottom_y += uwinp->header_height;
        rect.bottom_y += INNER_BORDER_LINEWIDTH_VAL;
    }
    

    if ( Userwin_Get_Window_Option( uwinp, USE_GADGETS ) )
    {        
        rect.left_x += GADGET_WIDTH_VAL;
        if ( Userwin_Get_Window_Option( uwinp, USE_MOVE_GADGET ) )
            rect.right_x -= GADGET_WIDTH_VAL;
    }
    return rect;
}

/* ------------------------------------------------------------ */

TWPoint Region_Get_Header_Pos( uwinp, pos )
    Userwin *uwinp;
    TWPoint pos;
{
    TWRectangle rect;
    
    rect = Region_Header_Rect( uwinp );

    if ( pos.x < rect.left_x )
        pos.x = rect.left_x;
    else if ( pos.x > rect.right_x )
        pos.x = rect.right_x;

    if ( pos.y < rect.top_y )
        pos.y = rect.top_y;
    else if ( pos.y > rect.bottom_y )
        pos.y = rect.bottom_y;
                     
    return pos;
}

/* ------------------------------------------------------------ */

TWPoint Region_Get_Edge_Pos( uwinp, side, pos )
    Userwin *uwinp;
    Side side;
    TWPoint pos;
{
    switch ( side )
    {
        case Left:
            pos.x = Userwin_Get_Rectangle(uwinp).left_x;
            break;
        case Right:
            pos.x = Userwin_Get_Rectangle(uwinp).right_x;
            break;
        case Top:
            pos.y = Userwin_Get_Rectangle(uwinp).top_y;
            break;
        case Bottom:
            pos.y = Userwin_Get_Rectangle(uwinp).bottom_y;
            break;
    }
    return pos;
}

/* ------------------------------------------------------------ */

TWPoint Region_Get_Corner_Pos( uwinp, side )
    Userwin *uwinp;
    Side side;
{
    TWPoint pos;
    switch ( side )
    {
        case Top_Left:
            pos.y = Userwin_Get_Rectangle(uwinp).top_y;
            pos.x = Userwin_Get_Rectangle(uwinp).left_x;
            break;
        case Top_Right:
            pos.y = Userwin_Get_Rectangle(uwinp).top_y;
            pos.x = Userwin_Get_Rectangle(uwinp).right_x;
            break;
        case Bottom_Left:
            pos.y = Userwin_Get_Rectangle(uwinp).bottom_y;
            pos.x = Userwin_Get_Rectangle(uwinp).left_x;
            break;
        case Bottom_Right:
            pos.y = Userwin_Get_Rectangle(uwinp).bottom_y;
            pos.x = Userwin_Get_Rectangle(uwinp).right_x;
            break;
    }
    return pos;
}

/* ------------------------------------------------------------ */

    /* Given a window and a point, returns the border region
       of the window nearest the point */

TWRegion Region_Nearest_Border( uwinp, pos )
    Userwin *uwinp;
    TWPoint pos;
{
    int lx, rx, ty, by;
    lx = Userwin_Get_Rectangle(uwinp).left_x + 2 * BORDER_SIZE_VAL;
    rx = Userwin_Get_Rectangle(uwinp).right_x - 2 * BORDER_SIZE_VAL;
    ty = Userwin_Get_Rectangle(uwinp).top_y + 2 * BORDER_SIZE_VAL;
    by = Userwin_Get_Rectangle(uwinp).bottom_y - 2 * BORDER_SIZE_VAL;
        /* Check for corner regions */
    if ( UserGlobals_Get_Option(USE_CORNER_BORDERS) )
    {
        if (pos.x <= lx )
        {
            if (pos.y <= ty) return top_left_region;
            else if (pos.y >= by) return bottom_left_region;
        }
        else if (pos.x >= rx)
        {
            if (pos.y <= ty) return top_right_region;
            else if (pos.y >= by) return bottom_right_region;
        }
    }
        /* Figure out which edge */
    if ( (pos.y - by)*(rx - lx) > (pos.x - lx)*(ty - by) )
    {
        if ( (pos.y - by)*(lx - rx) > (pos.x - rx)*(ty - by) )
            return right_region;
        else return bottom_region;
    }
    else
    {
        if ( (pos.y - by)*(lx - rx) > (pos.x - rx)*(ty - by) )
            return top_region;
        else return left_region;
    }
}

/* ------------------------------------------------------------ */

    /* Given a window, returns the center of the MOVE_GADGET,
       or, if none, the ZOOM_GADGET, of that window.
       If neither, the HEADER.
       If PLACE_CSR_IN_BODY_NOT_GADGET, return a 
       point in the body just below instead. */

TWPoint Region_Gadget_Center( uwinp )
    Userwin *uwinp;
{
    TWPoint pt;

    if ( Userwin_Get_Window_Option( uwinp, USE_MOVE_GADGET ) )
        pt.x = Userwin_Get_Rectangle(uwinp).right_x
            - BORDER_SIZE_VAL - ( GADGET_WIDTH_VAL / 2 );
    else
        pt.x = Userwin_Get_Rectangle(uwinp).left_x
            + BORDER_SIZE_VAL + ( GADGET_WIDTH_VAL / 2 );

    if ( UserGlobals_Get_Option(PLACE_CSR_IN_BODY_NOT_GADGET) )
        pt.y = Userwin_Get_Rectangle(uwinp).top_y
               + BORDER_SIZE_VAL + uwinp->header_height 
               + INNER_BORDER_LINEWIDTH_VAL + 2;
    else
        pt.y = Userwin_Get_Rectangle(uwinp).top_y
               + BORDER_SIZE_VAL + ( uwinp->header_height / 2 );

    return pt;        
}

/* ------------------------------------------------------------ */

bool Region_Nearby( pos1, pos2 )
    TWPoint pos1;
    TWPoint pos2;
{
    return
    (
        ( abs(pos1.x - pos2.x) < 20 ) &&
        ( abs(pos1.y - pos2.y) < 20 )
    );
}
        
/* ------------------------------------------------------------ */

bool Region_Equal( rgn1, rgn2 )
    TWRegion rgn1;
    TWRegion rgn2;
{
    return
    (
        (rgn1.region_enum == rgn2.region_enum) &&
        (rgn1.region_info.side == rgn2.region_info.side)
    );
}

/* ------------------------------------------------------------ */

TileCursor Region_Get_Cursor( uwinp, regn )
    Userwin *uwinp;
    TWRegion regn;
{
    switch ( regn.region_enum )
    {
        case background:
            return background_tilecursor;
        case header:
            return header_tilecursor;
        case body:
            return Bodyreg_Get_Cursor(uwinp,regn.region_info.bodyregion);
        case edge:
            switch ( regn.region_info.side )
            {
                case Left:
                    return left_tilecursor;
                case Right:
                    return right_tilecursor;
                case Top:
                    return top_tilecursor;
                case Bottom:
                    return bottom_tilecursor;
            }
        case corner:
            switch ( regn.region_info.side )
            {
                case Top_Left:
                    return top_left_tilecursor;
                case Top_Right:
                    return top_right_tilecursor;
                case Bottom_Left:
                    return bottom_left_tilecursor;
                case Bottom_Right:
                    return bottom_right_tilecursor;
            }
        case zoom_gadget:
            return zoom_gadget_tilecursor;
        case move_gadget:
            return move_gadget_tilecursor;
        case icon:
        case rtl:
            return icon_tilecursor;
    }
    return background_tilecursor;
}

TileMenu Region_Get_Menu( uwinp, regn )
    Userwin *uwinp;
    TWRegion regn;
{
    switch ( regn.region_enum )
    {
        case body:
        case icon:
            return Bodyreg_Get_Menu(uwinp,regn.region_info.bodyregion);
        default:
            return Bodyreg_Get_Menu(uwinp,NULL);
    }    

}
