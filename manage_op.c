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

#include "userglobD.h"
#include "twin.h"

#ifndef USERWIN_DEFINE
#include "uwinD.h"
#endif

#ifndef TILWIN_DEFINE
#include "twinD.h"
#endif

#include "client.h"
#include "closed.h"
#include "draw.h"
#include "drawicon.h"
#include "drawwin.h"
#include "layout.h"
#include "profile.h"
#include "region.h"
#include "tool.h"

/* ------------------------------------------------------------ */

#define COMPUTE_DISTANCE(pt1, pt2) \
    (((Get_PtX(pt1) - Get_PtX(pt2)) * (Get_PtX(pt1) - Get_PtX(pt2))) + \
     ((Get_PtY(pt1) - Get_PtY(pt2)) * (Get_PtY(pt1) - Get_PtY(pt2))))


#define window_excursion(win,opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Tilwin_Get_Window_Option(win,opt); \
    Tilwin_Set_Window_Option(win,opt,val); \
    code; \
    Tilwin_Set_Window_Option(win,opt,temp_val); \
}

#define window_restrict_excursion(win,opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Tilwin_Get_Window_Option(win,opt); \
    Tilwin_Set_Window_Option( win, opt, (temp_val && val) ); \
    code; \
    Tilwin_Set_Window_Option(win,opt,temp_val); \
}

#define window_join_excursion(win,opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Tilwin_Get_Window_Option(win,opt); \
    Tilwin_Set_Window_Option( win, opt, (temp_val || val) ); \
    code; \
    Tilwin_Set_Window_Option(win,opt,temp_val); \
}
    
#define global_excursion(opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Tilwin_Get_Global_Option(opt); \
    Tilwin_Set_Global_Option(opt,val); \
    code; \
    Tilwin_Set_Global_Option(opt,temp_val); \
}
    
#define global_restrict_excursion(opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Tilwin_Get_Global_Option(opt); \
    Tilwin_Set_Global_Option( opt, (temp_val && val) ); \
    code; \
    Tilwin_Set_Global_Option(opt,temp_val); \
}

#define user_window_excursion(uwin,opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Userwin_Get_Window_Option(uwin,opt); \
    Userwin_Set_Window_Option( uwin, opt, val ); \
    code; \
    Userwin_Set_Window_Option(uwin,opt,temp_val); \
}

#define user_window_join_excursion(uwin,opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Userwin_Get_Window_Option(uwin,opt); \
    Userwin_Set_Window_Option( uwin, opt, (temp_val || val) ); \
    code; \
    Userwin_Set_Window_Option(uwin,opt,temp_val); \
}
    
#define user_global_excursion(opt,val,code) \
{ \
    bool temp_val; \
    temp_val = UserGlobals_Get_Option(opt); \
    UserGlobals_Set_Option( opt, val ); \
    code; \
    UserGlobals_Set_Option(opt,temp_val); \
}
    
#define user_global_restrict_excursion(opt,val,code) \
{ \
    bool temp_val; \
    temp_val = UserGlobals_Get_Option(opt); \
    UserGlobals_Set_Option( opt, (temp_val && val) ); \
    code; \
    UserGlobals_Set_Option(opt,temp_val); \
}
    
#define user_global_join_excursion(opt,val,code) \
{ \
    bool temp_val; \
    temp_val = UserGlobals_Get_Option(opt); \
    UserGlobals_Set_Option( opt, (temp_val || val) ); \
    code; \
    UserGlobals_Set_Option(opt,temp_val); \
}

#define min_excursion(win,code) \
{ \
    Size temp_min; \
    temp_min = Tilwin_Get_Min(win); \
    Tilwin_Set_Min( win, Tilwin_Get_Size(win) ); \
    code; \
    Tilwin_Set_Min( win, temp_min ); \
}

/* ------------------------------------------------------------ */

#define height_excursion(winp,code) \
{ \
    if ( Tilwin_Get_Size(winp).height < \
              Tilwin_Get_Previous_Size(winp).height ) \
        window_excursion( winp, FIXED_HEIGHT, TRUE, code ) \
    else \
    { \
        Size temp_min, temp_siz; \
        temp_siz = temp_min = Tilwin_Get_Min(winp); \
        temp_siz.height = Tilwin_Get_Size(winp).height; \
        Tilwin_Set_Min( winp, temp_siz ); \
        code; \
        Tilwin_Set_Min( winp, temp_min ); \
    } \
}

/* ------------------------------------------------------------ */

#define width_excursion(winp,code) \
{ \
    if ( Tilwin_Get_Size(winp).width < \
              Tilwin_Get_Previous_Size(winp).width ) \
        window_excursion( winp, FIXED_WIDTH, TRUE, code ) \
    else \
    { \
        Size temp_min, temp_siz; \
        temp_siz = temp_min = Tilwin_Get_Min(winp); \
        temp_siz.width = Tilwin_Get_Size(winp).width; \
        Tilwin_Set_Min( winp, temp_siz ); \
        code; \
        Tilwin_Set_Min( winp, temp_min ); \
    } \
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

extern TimeStamp last_stamp;
extern Userwin *listener;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

extern TWRectangle Manage_Neighborhood_Rectangle();
extern void Manage_Start_Open();
extern bool Manage_Finish_Sized_Open();
extern bool Manage_Finish_Unsized_Open();
extern bool Manage_Can_Try_Listener_Unzoom();
extern bool Manage_Can_Try_Self_Unzoom();
extern void Manage_Min_Max_Resizing();
extern void Manage_Finish_Resizing();
extern void Manage_Cancel_Resizing();
extern void Manage_Switch_Listener();
extern bool Manage_Unzoom_Open();


/* ------------------------------------------------------------ */

static bool Manage_Basic_Open( uwinp, center, siz )
    Userwin *uwinp;
    TWPoint center;
    Size siz;
{
    if ( Tilwin_Get_Window_Option( uwinp->winp, FIXED_SIZE ) ||
         ( Tilwin_Get_Window_Option( uwinp->winp, FIXED_WIDTH ) &&
           Tilwin_Get_Window_Option( uwinp->winp, FIXED_HEIGHT ) ) )
        return Tilwin_Open( uwinp->winp, center, siz );
    else
    {
        TWRectangle rect;
        MAKE_RECTANGLE( center, siz, rect );
        return Tilwin_Open_Nearest_In_Area( uwinp->winp, rect, center, siz );
    }
}

/* ------------------------------------------------------------ */

bool Manage_Center_Neighborhood_Open( uwinp, center, siz )
    Userwin *uwinp;
    TWPoint center;
    Size siz;
{
    TWRectangle rect;
    bool result;

    if (! UserGlobals_Get_Option(TRY_CTR_NBRHD_ON_OPEN))
        return Manage_Basic_Open( uwinp, center, siz );
    
    global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE,
        (! UserGlobals_Get_Option(
            PF_CTR_NBR_2_AUTO_CL_ON_OPEN)),
    { global_restrict_excursion( ALLOW_AUTOMATIC_SHRINK,
        (! UserGlobals_Get_Option(
            PF_CTR_NBR_2_AUTO_SHR_ON_OPEN)),
    { window_join_excursion( uwinp->winp, FIXED_SIZE,
        UserGlobals_Get_Option(PF_CTR_NBR_2_SHRINK_ON_OPEN),
    { 
        result = Manage_Basic_Open( uwinp, center, siz );
    } ) } ) } );

    if (! result )
    {
        rect = Manage_Neighborhood_Rectangle( 0.5, center, siz );
        result = Tilwin_Open_Nearest_In_Area( uwinp->winp,
            rect, center, siz );
    }

    return result;
}

/* ------------------------------------------------------------ */

static bool Manage_Edge_Neighborhood_Open( uwinp, center, siz )
    Userwin *uwinp;
    TWPoint center;
    Size siz;
{
    TWRectangle rect;
    bool result;
    
    if (! UserGlobals_Get_Option(TRY_EDGE_NEIGHBORHOOD_ON_OPEN))
        return Manage_Center_Neighborhood_Open( uwinp, center, siz );

    global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE,
        (! UserGlobals_Get_Option(
            PF_EDGE_NBR_2_AUTO_CL_ON_OPEN) ),
    { global_restrict_excursion( ALLOW_AUTOMATIC_SHRINK,
        (! UserGlobals_Get_Option(
            PF_EDGE_NBR_2_AUTO_SHR_ON_OPEN) ),
    { window_join_excursion( uwinp->winp, FIXED_SIZE,
        UserGlobals_Get_Option(PF_EDGE_NBR_2_SHRINK_ON_OPEN),
    { 
        result = Manage_Center_Neighborhood_Open( uwinp, center, siz );
    } ) } ) } );

    if ( result ) return TRUE;

    rect = Manage_Neighborhood_Rectangle( 1.0, center, siz );

    return Tilwin_Open_Nearest_In_Area( uwinp->winp, rect, center, siz );
}

/* ------------------------------------------------------------ */

bool Manage_Center_Open( uwinp, pos )
    Userwin *uwinp;
    TWPoint pos;
{
    bool result;
    Size siz;
    
    Manage_Start_Open( uwinp, FALSE );

    Tilwin_Set_Position( uwinp->winp, pos );
    uwinp->positioned = TRUE;

    siz = Tilwin_Get_Size( uwinp->winp );

    global_excursion( PREFER_CLOSE_TO_SHRINK,
        UserGlobals_Get_Option(PREFER_CL_TO_SHR_ON_CENTER_OPEN),
    { window_join_excursion( uwinp->winp, FIXED_SIZE, 
        ! UserGlobals_Get_Option(ALLOW_SHRINK_ON_CENTER_OPEN),
    {
        result = Manage_Edge_Neighborhood_Open( uwinp, pos, siz );
        if ( (! result) && ( listener != uwinp ) 
             && Manage_Can_Try_Listener_Unzoom() )
            result = Manage_Edge_Neighborhood_Open( uwinp, pos, siz );
        if ( (! result) && Manage_Can_Try_Self_Unzoom(uwinp) )
            result = Manage_Edge_Neighborhood_Open(
                         uwinp, pos, Tilwin_Get_Size( uwinp->winp ) );
    } ) } )

    return Manage_Finish_Unsized_Open( uwinp, result );
}

/* ------------------------------------------------------------ */

bool Manage_Corner_Open( uwinp, start_pos, pos, force, undesire )
    Userwin *uwinp;
    TWPoint start_pos;
    TWPoint pos;
    bool force, undesire;
{
    TWPoint center;
    Size siz;
    bool result;
    TWRectangle rect;

    Manage_Start_Open( uwinp, FALSE );

    rect.left_x = start_pos.x;
    rect.top_y = start_pos.y;
    rect.right_x = pos.x;
    rect.bottom_y = pos.y;
    COMPUTE_SIZE( rect, siz );
    COMPUTE_CENTER( rect, center );

    if (! ( UserGlobals_Get_Option(RESET_MIN_ON_DECREASE) || force ))
        Set_Max_Size( siz, siz, uwinp->prev_min )
    if( ! ( UserGlobals_Get_Option(RESET_MAX_ON_INCREASE) || force ))
        Set_Min_Size( siz, siz, uwinp->prev_max )

    if (! undesire )
    {    
        Tilwin_Set_Position( uwinp->winp, center );
        uwinp->positioned = TRUE;
        Tilwin_Set_Desired( uwinp->winp, siz );
        Tilwin_Note_Desired_Height( uwinp->winp );
        Tilwin_Note_Desired_Width( uwinp->winp );
    }

    Manage_Min_Max_Resizing( uwinp, siz, Tilwin_Get_Min( uwinp->winp ) );

    global_excursion( PREFER_CLOSE_TO_SHRINK,
        UserGlobals_Get_Option(PREFER_CL_TO_SHR_ON_CORNER_OPEN),
    { window_join_excursion( uwinp->winp, FIXED_SIZE, 
        ! UserGlobals_Get_Option(ALLOW_SHRINK_ON_CORNER_OPEN),
    {
        result = Manage_Edge_Neighborhood_Open( uwinp, center, siz );
        if ( (! result) && ( listener != uwinp )
             && Manage_Can_Try_Listener_Unzoom() )
            result = Manage_Edge_Neighborhood_Open( uwinp, center, siz );
        if ( (! result) && Manage_Can_Try_Self_Unzoom(uwinp) )
            result = Manage_Edge_Neighborhood_Open(
                         uwinp, pos, Tilwin_Get_Size( uwinp->winp ) );
    } ) } )

    if ( result )
        Manage_Finish_Resizing( uwinp, NoSide, force, undesire );
    else
        Manage_Cancel_Resizing( uwinp );
    return Manage_Finish_Sized_Open( uwinp, result );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

bool Manage_Desktop_Open( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    TWPoint center;
    bool result;

    center = Tilwin_Get_Center( uwinp->winp );

    if ( Tilwin_Get_Window_Option( uwinp->winp, FIXED_COMPLETELY ) )
        result =  Tilwin_Open( uwinp->winp, center, siz );

    else if (! uwinp->positioned )
    {
        result =  Tilwin_Open_Best_In_Area( uwinp->winp, 
                      Tilwin_Get_Desktop_Rectangle(), siz );
    }

    else if ( Userwin_Get_Window_Option( uwinp,
             REQUIRE_PREV_POS ) ) 
        return Manage_Basic_Open( uwinp, center, siz );

    else if ( Userwin_Get_Window_Option( uwinp,
             PREFER_PREV_POS ) )
    {
        center = Tilwin_Get_Position( uwinp->winp );
        global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE,
            (! UserGlobals_Get_Option(
                PF_DTOP_2_AUTO_CL_ON_AUTO_OPEN)),
        { global_restrict_excursion( ALLOW_AUTOMATIC_SHRINK,
            (! UserGlobals_Get_Option(
                PF_DTOP_2_AUTO_SHR_ON_AUTO_OPEN)),
        { window_join_excursion( uwinp->winp, FIXED_SIZE,
            UserGlobals_Get_Option(PF_DTOP_2_SHRINK_ON_AUTO_OPEN),
        {
            result = Manage_Edge_Neighborhood_Open( uwinp, center, siz );
        } ) } ) } );

        if (! result )
            result = Tilwin_Open_Nearest_In_Area( uwinp->winp, 
                   Tilwin_Get_Desktop_Rectangle(), center, siz );
    }

    else
        result = Tilwin_Open_Best_In_Area( uwinp->winp, 
               Tilwin_Get_Desktop_Rectangle(), siz );

    return result;

}

/* ------------------------------------------------------------ */

static bool Manage_Open_Automatically( uwinp )
    Userwin *uwinp;
{
    bool result;

    global_excursion( PREFER_CLOSE_TO_SHRINK,
        UserGlobals_Get_Option(PREFER_CL_TO_SHR_ON_AUTO_OPEN),
    { window_join_excursion( uwinp->winp, FIXED_SIZE, 
        ! UserGlobals_Get_Option(ALLOW_SHRINK_ON_AUTO_OPEN),
        result = Manage_Desktop_Open( uwinp, 
            Tilwin_Checked_Desired_Size( uwinp->winp ) );
    ) } )

    return result;
}

/* ------------------------------------------------------------ */

bool Manage_Auto_Open_Automatically( uwinp )
    Userwin *uwinp;
{
    bool iconized;
    bool result;
    Size siz;

    iconized = Tilwin_Is_Open( uwinp->iconp );
    if ( iconized )
        Tilwin_Close( uwinp->iconp );

    Set_Min_Size( siz, Tilwin_Get_Size( uwinp->winp ), 
                       Tilwin_Get_Desired( uwinp->winp ) )

    window_join_excursion( uwinp->winp, FIXED_SIZE, 
        (! UserGlobals_Get_Option(ALLOW_SHRINK_ON_AUTO_OPEN)),
    {
        result = Manage_Desktop_Open( uwinp, siz );
    } )

    if ( (! result) && iconized )
        Tilwin_Open( uwinp->iconp,
                     Tilwin_Get_Center( uwinp->iconp ),
                     Tilwin_Get_Size( uwinp->iconp ) );

    return result;
}

/* ------------------------------------------------------------ */

bool Manage_User_Open_Automatically( uwinp, force_listener, force_zoom )
    Userwin *uwinp;
    bool force_listener;
    bool force_zoom;
{
    bool result;

    if ( force_listener && Userwin_Get_Window_Option(uwinp,LISTENER_TIED_TO_ZOOM) )
        force_zoom = TRUE;
    Manage_Start_Open( uwinp, force_zoom );
    
    result = Manage_Open_Automatically( uwinp );
    if (! result)
        user_global_join_excursion( UNZOOM_TIED_LSNR_IF_NECESSARY, force_listener,
        {
            if ( Manage_Can_Try_Listener_Unzoom() )
                result = Manage_Open_Automatically( uwinp );
        } )
    if ( (! result) && Manage_Can_Try_Self_Unzoom(uwinp) )
        result = Manage_Open_Automatically( uwinp );

    if (! result)
        Tilwin_Auto_Close( uwinp->winp );
    else if ( force_listener )
        Manage_Switch_Listener( uwinp );

    return Manage_Finish_Unsized_Open( uwinp, result );
}

/* ------------------------------------------------------------ */

bool Manage_Fixed_Open( uwinp )
    Userwin *uwinp;
{
    bool result;
    
    Manage_Start_Open( uwinp, FALSE );

    result = Tilwin_Open( uwinp->winp, 
                 Tilwin_Get_Center( uwinp->winp ),
                 Tilwin_Get_Size( uwinp->winp ) );

    if ( (! result) && Manage_Can_Try_Listener_Unzoom() )
    {
        result = Tilwin_Open( uwinp->winp, 
             Tilwin_Get_Center( uwinp->winp ),
             Tilwin_Get_Size( uwinp->winp ) );
    }

    return Manage_Finish_Sized_Open( uwinp, result );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

    /* Returns true if any repopulation occurred */

bool Manage_Repopulate_Since( stamp, explicit, strict, only_auto_close )
    TimeStamp stamp;
    bool explicit;
    bool strict;
    bool only_auto_close;
{
    Tilwinp winp;
    Userwin *uwinp;
    bool prev_prefer, prev_require, allow_shrink;
    TimeStamp cur_stamp;
    bool result;

    strict = strict ||
        UserGlobals_Get_Option( REPOPULATE_STRICTLY );

    result = FALSE;
    
    if ( explicit )
    {
        prev_prefer = UserGlobals_Get_Option(
                          PREFER_PREV_POS_ON_EXPL_REPOP);
        prev_require = UserGlobals_Get_Option(
                           REQUIRE_PREV_POS_ON_EXPL_REPOP);
        allow_shrink = UserGlobals_Get_Option(
                           ALLOW_AUTO_SHRINK_ON_EXPL_REPOP);
    }
    else
    {
        prev_prefer = UserGlobals_Get_Option(
                          PREFER_PREV_POS_ON_AUTO_REPOP);
        prev_require = UserGlobals_Get_Option(
                           REQUIRE_PREV_POS_ON_AUTO_REPOP);
        allow_shrink = UserGlobals_Get_Option(
                           ALLOW_AUTO_SHRINK_ON_AUTO_REPOP);
    }

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        cur_stamp = Tilwin_Get_Window_Timestamp(winp);
        if ( cur_stamp < stamp ) break;
        uwinp = Userwin_Get(winp);
        if ( ( uwinp->winp == winp )
           && Userwin_Get_Window_Option(uwinp,CONSIDER_FOR_REPOPULATION)
           && ( uwinp->ever_opened )
           && ( (! only_auto_close) || 
                Tilwin_Was_Automatically_Closed(winp) ) )
        {
            global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
            { global_restrict_excursion( 
                ALLOW_SHRINK_ON_AUTO_OPEN,
                    UserGlobals_Get_Option(ALLOW_AUTOMATIC_SHRINK)
                    || explicit,
            { global_restrict_excursion( 
                ALLOW_AUTOMATIC_SHRINK, allow_shrink,
            { user_window_join_excursion( uwinp,
                PREFER_PREV_POS, prev_prefer,
            { user_window_join_excursion( uwinp,
                REQUIRE_PREV_POS, prev_require,
            {
                if ( Manage_Auto_Open_Automatically( uwinp ) )
                    result = TRUE;
                else if ( UserGlobals_Get_Option(PREFER_UNZOOM_TO_CLOSE) &&
                          (uwinp->zoomed) &&
                          Manage_Unzoom_Open( uwinp ) )
                    result = TRUE;
                else if ( strict )
                    stamp = cur_stamp;
            } ) } ) } ) } ) } )
        }
    }

    return result;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

bool Manage_Aggressive_Repopulation()
{
    Tilwinp winp;
    Userwin *uwinp;
    bool prev_prefer, prev_require, allow_shrink;
    bool result;

    result = FALSE;
    
    prev_prefer = UserGlobals_Get_Option(
                      PREFER_PREV_POS_ON_AUTO_REPOP);
    prev_require = UserGlobals_Get_Option(
                       REQUIRE_PREV_POS_ON_AUTO_REPOP);
    allow_shrink = UserGlobals_Get_Option(
                       ALLOW_AUTO_SHRINK_ON_AUTO_REPOP);

        Tilwin_Gen_Closed_Windows();
        while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
        {
            uwinp = Userwin_Get(winp);
            if ( ( uwinp->winp == winp )
               && Userwin_Get_Window_Option(uwinp,CONSIDER_FOR_REPOPULATION)
               && Userwin_Get_Window_Option(uwinp,AGGRESSIVELY_REPOPULATE)
               && Tilwin_Was_Automatically_Closed(winp)
               && uwinp->ever_opened )
            {
                global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
                { global_restrict_excursion( 
                    ALLOW_SHRINK_ON_AUTO_OPEN,
                        UserGlobals_Get_Option(ALLOW_AUTOMATIC_SHRINK),
                { global_restrict_excursion( 
                    ALLOW_AUTOMATIC_SHRINK, allow_shrink,
                { user_window_join_excursion( uwinp,
                    PREFER_PREV_POS, prev_prefer,
                { user_window_join_excursion( uwinp,
                    REQUIRE_PREV_POS, prev_require,
                { 
                    if ( Manage_Auto_Open_Automatically( uwinp ) )
                        result = TRUE;
                    else if ( UserGlobals_Get_Option(PREFER_UNZOOM_TO_CLOSE) &&
                              (uwinp->zoomed) &&
                              Manage_Unzoom_Open( uwinp ) )
                        result = TRUE;
                } ) } ) } ) } ) } )
            }
        }

    return result;
}
        
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
