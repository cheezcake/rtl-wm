#ifndef lint
static char sccs_id[] = "@(#)manage.c	5.7  9/1/88";
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

#include "basetype.h"

#include "userglobD.h"
#include "twin.h"

#ifndef TILWIN_DEFINE
#include "twinD.h"
#endif

#ifndef USERWIN_DEFINE
#include "uwinD.h"
#endif

#include "uwinL.h"
#include "uwinvalP.h"

#include "client.h"
#include "closed.h"
#include "draw.h"
#include "drawicon.h"
#include "drawwin.h"
#include "layout.h"
#include "profile.h"
#include "region.h"

/* ------------------------------------------------------------ */

#define SWAP_BOOL( val1, val2 )  \
{  \
    bool temp;  \
    temp = val1;  \
    val1 = val2;  \
    val2 = temp;  \
}

/* ------------------------------------------------------------ */

#define SWAP_INT( val1, val2 )  \
{  \
    int temp;  \
    temp = val1;  \
    val1 = val2;  \
    val2 = temp;  \
}

/* ------------------------------------------------------------ */

#define SWAP_POS( val1, val2 )  \
{  \
    TWPoint temp;  \
    temp = val1;  \
    val1 = val2;  \
    val2 = temp;  \
}

/* ------------------------------------------------------------ */

#define SWAP_SIZE( val1, val2 )  \
{  \
    Size temp;  \
    temp = val1;  \
    val1 = val2;  \
    val2 = temp;  \
}

/* ------------------------------------------------------------ */

#define SWAP_RECT( val1, val2 )  \
{  \
    TWRectangle temp;  \
    temp = val1;  \
    val1 = val2;  \
    val2 = temp;  \
}

/* ------------------------------------------------------------ */

#define SWAP_UWINP( uwinp1, uwinp2 )  \
{  \
    Userwin *temp;  \
    temp = uwinp1;  \
    uwinp1 = uwinp2;  \
    uwinp2 = temp;  \
}

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
        Size temp_min; \
	Size temp_siz; \
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
        Size temp_min; \
	Size temp_siz; \
        temp_siz = temp_min = Tilwin_Get_Min(winp); \
        temp_siz.width = Tilwin_Get_Size(winp).width; \
        Tilwin_Set_Min( winp, temp_siz ); \
        code; \
        Tilwin_Set_Min( winp, temp_min ); \
    } \
}

static void Manage_Do_Unzoom(Userwin *uwinp, bool explicit);
static void Manage_Start_Trying();
static void Manage_Finish_Trying(bool result);

/* ------------------------------------------------------------ */

TimeStamp last_stamp;

static int winnum = 0;

Userwin *focus = UWIN_NULL;
Userwin *listener = UWIN_NULL;
Userwin *sublistener = UWIN_NULL;
Userwin *switch_listener = UWIN_NULL;
Userwin *prev_listener = UWIN_NULL;
Userwin *last_zoom = UWIN_NULL;
Userwin *touch = UWIN_NULL;
Userwin *prev_touch = UWIN_NULL;

Userwin *rtl_uwinp;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Init()
{
    Draw_Init();
    Region_Init();
    Drawwin_Init();
    DrawIcon_Init();

    last_stamp = 0;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static Userwin *Manage_Init_Window()
{
    Userwin *uwinp;
    uwinp = Userwin_Allocate;

    uwinp->prepared = FALSE;
    uwinp->layout = FALSE;
    uwinp->layout_found = FALSE;
    uwinp->output_sent = FALSE;
    uwinp->ever_opened = FALSE;
    uwinp->soft_kill = FALSE;
    uwinp->saving_state = FALSE;
    uwinp->client_state = NoState;
    uwinp->wm_state = NeverState;
    uwinp->group_state = GroupState;
    uwinp->current_type = body;

    uwinp->group = UWIN_NULL;
    uwinp->messages = 0;
        
    uwinp->hostname = NULL;
    uwinp->res_class = NULL;
    uwinp->res_name = NULL;
    uwinp->wmname = NULL;
    uwinp->iconname = NULL;
    uwinp->command = NULL;
    uwinp->identity = NULL;
    uwinp->title = NULL;

    uwinp->positioned = FALSE;
    uwinp->sized = FALSE;

    uwinp->focus = FALSE;
    uwinp->listener = FALSE;
    uwinp->zoomed = FALSE;

    uwinp->icon_positioned = FALSE;

    uwinp->winp = Tilwin_Create_Window( (pointer)uwinp );
    uwinp->iconp = Tilwin_Create_Window( (pointer)uwinp );

    uwinp->open_stamp = 0;
    uwinp->zoom_stamp = 0;

    Tilwin_Set_Window_Option( uwinp->iconp, FIXED_LEFT_EDGE, FALSE );
    Tilwin_Set_Window_Option( uwinp->iconp, FIXED_RIGHT_EDGE, FALSE );
    Tilwin_Set_Window_Option( uwinp->iconp, FIXED_TOP_EDGE, FALSE );
    Tilwin_Set_Window_Option( uwinp->iconp, FIXED_BOTTOM_EDGE, FALSE );

    Tilwin_Set_Window_Option( uwinp->iconp, FIXED_SIZE, TRUE );
    Tilwin_Set_Window_Option( uwinp->iconp, FIXED_COMPLETELY, FALSE );

    Tilwin_Set_Window_Option( uwinp->iconp, EXPENSIVE_TO_REDRAW, FALSE );

    Tilwin_Set_Window_Option( uwinp->iconp, REQUIRE_MANUAL_CLOSE, TRUE );

    Profile_Create( uwinp );

    return uwinp;
}

/* ------------------------------------------------------------ */

Userwin *Manage_Create_Window( )
{
    Userwin *uwinp;
    
    uwinp = Manage_Init_Window();

    uwinp->winnum = ++winnum;

    Drawwin_Create( uwinp );
    DrawIcon_Create( uwinp );

    return uwinp;
}

/* ------------------------------------------------------------ */

static void Manage_Untitle( uwinp )
    Userwin *uwinp;
{
    if ( (uwinp->hostname) != NULL )
        free( uwinp->hostname );
    if ( (uwinp->res_class) != NULL )
        free( uwinp->res_class );
    if ( (uwinp->res_name) != NULL )
        free( uwinp->res_name );
    if ( (uwinp->wmname) != NULL )
        free( uwinp->wmname );
    if ( (uwinp->iconname) != NULL )
        free( uwinp->iconname );
    if ( (uwinp->command) != NULL )
        free( uwinp->command );
    if ( (uwinp->identity) != NULL )
        free( uwinp->identity );
    if ( (uwinp->title) != NULL )
        free( uwinp->title );
}

/* ------------------------------------------------------------ */

static void Manage_Retitle( uwinp )
    Userwin *uwinp;
{
    int strsiz;
    bool has_class, has_name;

    if ( (uwinp->title) != NULL )
        free( uwinp->title );

    strsiz = 1;

    has_class = (uwinp->res_class != NULL) &&
        Userwin_Get_Window_Option( uwinp, INCLUDE_RES_CLASS_IN_TITLE );

    has_name = (uwinp->res_name != NULL) &&
        Userwin_Get_Window_Option( uwinp, INCLUDE_RES_NAME_IN_TITLE );

    if ( has_class || has_name )
    {
        strsiz +=1;

        if ( has_class )        
            strsiz += strlen(uwinp->res_class);

        if ( has_class && has_name )
            strsiz +=1;

        if ( has_name )
            strsiz += strlen(uwinp->res_name);

        strsiz +=2;
    }

    if ( (uwinp->wmname != NULL) &&
         Userwin_Get_Window_Option( uwinp, INCLUDE_NAME_IN_TITLE ) )
        strsiz += strlen(uwinp->wmname);

    if ( (uwinp->hostname != NULL) &&
         Userwin_Get_Window_Option( uwinp, INCLUDE_HOST_IN_TITLE ) )
        strsiz += (3 + strlen(uwinp->hostname));

    uwinp->title = allocate( char, strsiz );
    uwinp->title[0] = '\0';

    if ( has_class || has_name )
    {
        (void)strcat( uwinp->title, "[" );

        if ( has_class )        
            (void)strcat( uwinp->title, uwinp->res_class );

        if ( has_class && has_name )
            (void)strcat( uwinp->title, ":" );

        if ( has_name )
            (void)strcat( uwinp->title, uwinp->res_name );

        (void)strcat( uwinp->title, "] " );
    }

    if ( (uwinp->wmname != NULL) &&
         Userwin_Get_Window_Option( uwinp, INCLUDE_NAME_IN_TITLE ) )
    {
        (void)strcat( uwinp->title, uwinp->wmname );
    }

    if ( (uwinp->hostname != NULL) &&
         Userwin_Get_Window_Option( uwinp, INCLUDE_HOST_IN_TITLE ) )
    {
        (void)strcat( uwinp->title, " (" );
        (void)strcat( uwinp->title, uwinp->hostname );
        (void)strcat( uwinp->title, ")" );
    }

    if ( Tilwin_Is_Open( uwinp->winp ) )
        Drawwin_Retitle( uwinp );
    else if ( uwinp->ever_opened )
    {
        Closed_Retitle( uwinp );
        if ( Tilwin_Is_Open( uwinp->iconp ) )
            DrawIcon_Retitle(uwinp);
    }
}

/* ------------------------------------------------------------ */

void Manage_Set_Class( uwinp, res_class, res_name )
    Userwin *uwinp;
    char *res_class;
    char *res_name;
{
    if ( streql( uwinp->res_class, res_class ) &&
         streql( uwinp->res_name, res_name ) )
        return;

    if ( (uwinp->res_class) != NULL )
        free( uwinp->res_class );

    if ( res_class == NULL )
        uwinp->res_class = NULL;
    else
    {
        uwinp->res_class = 
            allocate( char, 1 + strlen(res_class) );
        (void)strcpy( uwinp->res_class, res_class );
    }

    if ( (uwinp->res_name) != NULL )
        free( uwinp->res_name );

    if ( res_name == NULL )
        uwinp->res_name = NULL;
    else
    {
        uwinp->res_name = 
            allocate( char, 1 + strlen(res_name) );
        (void)strcpy( uwinp->res_name, res_name );
    }

    Profile_Prepare( uwinp );
    uwinp->prepared = TRUE;

    Manage_Retitle( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Set_Name( uwinp, str )
    Userwin *uwinp;
    char *str;
{
    if ( (uwinp->wmname) != NULL )
        free( uwinp->wmname );

    uwinp->wmname = allocate( char, 1 + strlen(str) );
    (void)strcpy( uwinp->wmname, str );

    if ( uwinp->identity == NULL )
    {
        uwinp->identity = allocate( char, 1 + strlen(str) );
        (void)strcpy( uwinp->identity, str );
    }    

    Manage_Retitle( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Set_Icon_Name( uwinp, str )
    Userwin *uwinp;
    char *str;
{
    if ( (uwinp->iconname) != NULL )
        free( uwinp->iconname );

    uwinp->iconname = allocate( char, 1 + strlen(str) );
    (void)strcpy( uwinp->iconname, str );
    Manage_Retitle( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Set_Hostname( uwinp, str )
    Userwin *uwinp;
    char *str;
{
    if ( (uwinp->hostname) != NULL )
        free( uwinp->hostname );

    uwinp->hostname = allocate( char, 1 + strlen(str) );
    (void)strcpy( uwinp->hostname, str );
    Manage_Retitle( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Set_Command( uwinp, str )
    Userwin *uwinp;
    char *str;
{
    if ( uwinp->soft_kill )
    {
        extern void Manage_Client_Destroy();
        Manage_Client_Destroy( uwinp );
        return;
    }
    uwinp->saving_state = FALSE;

    if ( (uwinp->command) != NULL )
        free( uwinp->command );

    uwinp->command = allocate( char, 1 + strlen(str) );
    (void)strcpy( uwinp->command, str );
    Manage_Retitle( uwinp );
}

/* ------------------------------------------------------------ */

static void Manage_Prepare( uwinp )
    Userwin *uwinp;
{
    if ( (uwinp->res_class == NULL) && (uwinp->res_name == NULL) &&
	 (uwinp->wmname != NULL) )
        Manage_Set_Class( uwinp, uwinp->wmname, NULL );
}

/* ------------------------------------------------------------ */

void Manage_Layout( uwinp )
    Userwin *uwinp;
{
    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    Profile_Layout( uwinp );
    uwinp->layout = TRUE;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

Userwin *Manage_Locate(pos)
    TWPoint pos;
{
    return Userwin_Get(Tilwin_Locate(pos));
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Set_Focus( uwinp )
    Userwin *uwinp;
{
    focus = uwinp;
    if (focus != UWIN_NULL)
    {
        focus->focus = TRUE;
        if ( Tilwin_Is_Open( focus->winp ) ) 
            Drawwin_Display_Focus( focus );
    }
}
    
/* ------------------------------------------------------------ */

void Manage_Unset_Focus()
{
    if (focus != UWIN_NULL)
    {
        focus->focus = FALSE;
        if ( Tilwin_Is_Open( focus->winp ) )
            Drawwin_Display_Focus( focus );
        focus = UWIN_NULL;
    }
}
    
/* ------------------------------------------------------------ */

void Manage_Switch_Focus( uwinp )
    Userwin *uwinp;
{
    if ( uwinp != focus )
    {
        Manage_Unset_Focus();
        Manage_Set_Focus( uwinp );
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

#define Manage_Global_Client_Restrict(op) \
      global_restrict_excursion( ALLOW_AUTOMATIC_SHRINK, \
        UserGlobals_Get_Option(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT), \
      global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE, \
        UserGlobals_Get_Option(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT), op ) )
        
/* ------------------------------------------------------------ */

#define Manage_Client_Restrict(uwinp,op) \
    window_join_excursion( uwinp->winp, REQUIRE_MANUAL_CLOSE, \
        (! UserGlobals_Get_Option(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)), \
    { window_join_excursion( uwinp->winp, FIXED_COMPLETELY, \
        ( uwinp->focus && \
            (! UserGlobals_Get_Option(ALLOW_LSNR_TO_CHANGE_BY_CLIENT))), \
        Manage_Global_Client_Restrict( op ) ) } ) \
        
/* ------------------------------------------------------------ */

#define Manage_Client(op) \
{ \
    Userwin *cur_listener; \
    Userwin *cur_sublistener; \
    cur_listener = listener; \
    cur_sublistener = sublistener; \
    if ( sublistener != UWIN_NULL ) \
    { \
        if ( listener != UWIN_NULL ) \
            window_join_excursion( cur_listener->winp, REQUIRE_MANUAL_CLOSE, \
                (! UserGlobals_Get_Option(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)), \
                Manage_Client_Restrict( cur_sublistener, op ) ) \
        else \
            Manage_Client_Restrict( cur_sublistener, op ) \
    } \
    else \
    { \
        if ( listener != UWIN_NULL ) \
            Manage_Client_Restrict( cur_listener, op ) \
        else \
             Manage_Global_Client_Restrict( op ) \
    } \
}

/* ------------------------------------------------------------ */

void Manage_Set_Sublistener( uwinp )
    Userwin *uwinp;
{
    sublistener = uwinp;

    if ( Userwin_Get_Window_Option( sublistener, NOTE_LISTENER ) )
        Tilwin_Note_Use( sublistener->winp );

    if (! UserGlobals_Get_Option(ALLOW_LISTENER_TO_CLOSE))
    {
        sublistener->regular_manual_close = 
            Tilwin_Get_Window_Option( sublistener->winp, REQUIRE_MANUAL_CLOSE );
        Tilwin_Set_Window_Option( sublistener->winp, REQUIRE_MANUAL_CLOSE, TRUE );
    }
}

/* ------------------------------------------------------------ */

void Manage_Unset_Sublistener()
{
    if ( sublistener != UWIN_NULL )
    {
        if ( ( listener != UWIN_NULL ) &&
             Userwin_Get_Window_Option( listener, NOTE_LISTENER ) )
            Tilwin_Note_Use( listener->winp );

        if (! UserGlobals_Get_Option(ALLOW_LISTENER_TO_CLOSE))
            Tilwin_Set_Window_Option( sublistener->winp, REQUIRE_MANUAL_CLOSE,
                sublistener->regular_manual_close );

        sublistener = UWIN_NULL;
    }
}
    
    
/* ------------------------------------------------------------ */

void Manage_Switch_Sublistener( uwinp )
    Userwin *uwinp;
{
    if ( uwinp != sublistener )
    {
        Manage_Unset_Sublistener();
        if ( uwinp != UWIN_NULL )
            Manage_Set_Sublistener( uwinp );
    }
}

/* ------------------------------------------------------------ */

static void Manage_Set_Listener( uwinp )
    Userwin *uwinp;
{
    listener = uwinp;

    if ( listener != UWIN_NULL )
    {
        Manage_Unset_Sublistener();
    
        listener->listener = TRUE;
        Tilwin_Act_Modified( listener->winp );
    
        if ( Userwin_Get_Window_Option( listener, NOTE_LISTENER ) )
            Tilwin_Note_Use( listener->winp );
    
        if (! UserGlobals_Get_Option(ALLOW_LISTENER_TO_CLOSE))
        {
            listener->regular_manual_close = 
                Tilwin_Get_Window_Option( listener->winp, REQUIRE_MANUAL_CLOSE );
            Tilwin_Set_Window_Option( listener->winp, 
                REQUIRE_MANUAL_CLOSE, TRUE );
        }
    }
}
    
/* ------------------------------------------------------------ */

static void Manage_Unset_Listener()
{
    listener->listener = FALSE;
    Tilwin_Act_Modified( listener->winp );

    if (! UserGlobals_Get_Option(ALLOW_LISTENER_TO_CLOSE))
        Tilwin_Set_Window_Option( listener->winp, REQUIRE_MANUAL_CLOSE,
            listener->regular_manual_close );

    listener = UWIN_NULL;
}

/* ------------------------------------------------------------ */

static void Manage_Unset( uwinp )
    Userwin *uwinp;
{
    extern void Manage_Do_Unzoom();

    if ( uwinp == focus )
        Manage_Unset_Focus();

    if ( uwinp == listener )
    {
        if ( Userwin_Get_Window_Option(listener,LISTENER_TIED_TO_ZOOM) &&
             listener->zoomed )
            Manage_Do_Unzoom( listener, FALSE );
        Manage_Unset_Listener();
    }
    else if ( uwinp == sublistener )
        Manage_Unset_Sublistener();
}
        
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

TWRectangle Manage_Neighborhood_Rectangle( nbhd, center, siz )
    float nbhd;
    TWPoint center;
    Size siz;
{
    TWRectangle rect;
    int horiz, vert;
    int dhoriz, dvert;
    int factor;
    
    factor = UserGlobals_Get_Value( NEIGHBORHOOD_SHRINK_FACTOR );

    dhoriz = 100 * Tilwin_Get_Desktop_Size().width;
    dvert = 100 * Tilwin_Get_Desktop_Size().height;

    horiz = nbhd * siz.width * (dhoriz - (factor*siz.width)) / dhoriz;
    horiz += (siz.width/2);
    rect.left_x = center.x - horiz;
    rect.right_x = center.x + horiz;

    vert = nbhd * siz.height * (dvert - (factor*siz.height)) / dvert;
    vert += (siz.height/2);
    rect.top_y = center.y - vert;
    rect.bottom_y = center.y + vert;

    return rect;
}    

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static bool Manage_Neighborhood_Icon_Open( uwinp, center )
    Userwin *uwinp;
    TWPoint center;
{
    TWRectangle rect;
    Size siz;
    bool result;

    extern void Manage_Start_Trying();
    extern bool Manage_Can_Try_Listener_Unzoom();
    extern void Manage_Finish_Trying();

    siz = Tilwin_Get_Size( uwinp->iconp );

    Manage_Start_Trying();
    global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
    {
        result = Tilwin_Open( uwinp->iconp, center, siz );
        if ( (! result) && Manage_Can_Try_Listener_Unzoom() )
            result = Tilwin_Open( uwinp->iconp, center, siz );
    } )
    Manage_Finish_Trying( result );

    if ( result ) return TRUE;

    rect = Manage_Neighborhood_Rectangle( 0.75, center, siz );
    return Tilwin_Open_Nearest_In_Area( uwinp->iconp, rect, center, siz );
}

/* ------------------------------------------------------------ */

bool Manage_Icon_Open( uwinp )
    Userwin *uwinp;
{
    TWRectangle desk,iconarea, rect, area, bigger_area;
    TWPoint center;
    Size siz;
    bool first_none = FALSE;
    bool second_none = FALSE;
    bool icon_positioned;
    bool result;

    if ( ( uwinp->client_state == InactiveState ) ||
         ( uwinp->client_state == IgnoreState ) ||
         ( Userwin_Group_Closed(uwinp) &&
           ( uwinp->group != uwinp ) ) ||
         ( ! Userwin_Get_Window_Option( uwinp, SHOW_ICON ) ) )
        return FALSE;

    if ( (uwinp->icon_positioned) && 
         Userwin_Get_Window_Option( uwinp, 
             REQUIRE_PREVIOUS_ICON_POSITION ) )
    {
        if ( Manage_Neighborhood_Icon_Open( uwinp,
                 Tilwin_Get_Position( uwinp->iconp ) ) )
        return TRUE;
    }

    icon_positioned =  (uwinp->icon_positioned) && 
         ( Userwin_Get_Window_Option( uwinp, 
               PREFER_PREVIOUS_ICON_POSITION ) ||
           Userwin_Get_Window_Option( uwinp, 
               REQUIRE_PREVIOUS_ICON_POSITION ) );

    siz = Tilwin_Get_Size( uwinp->iconp );

    desk = Tilwin_Get_Desktop_Rectangle();

    if ( UserGlobals_Get_Option( USE_ICON_AREA ) )
    {
        iconarea.left_x = UserGlobals_Get_Value( ICON_AREA_LEFT );
        iconarea.right_x = UserGlobals_Get_Value( ICON_AREA_RIGHT );
        iconarea.top_y = UserGlobals_Get_Value( ICON_AREA_TOP );
        iconarea.bottom_y = UserGlobals_Get_Value( ICON_AREA_BOTTOM );
    }
    else
        iconarea = desk;

    bigger_area = area = rect = iconarea;

    switch ( (Icon_Position)UserGlobals_Get_Value(
                 SECONDARY_ICON_PLACEMENT) )
    {
        case Icon_Top:
            rect.bottom_y = iconarea.top_y + siz.height - 1;
            break;   
        case Icon_Bottom:
            rect.top_y = iconarea.bottom_y - siz.height + 1;
            break;   
        case Icon_Left:
            rect.right_x = iconarea.left_x + siz.width - 1;
            break;   
        case Icon_Right:
            rect.left_x = iconarea.right_x - siz.width + 1;
            break;   
        case Icon_None:
            second_none = TRUE;
        case Icon_Middle:
        default:
            break;
    }

    switch ( (Icon_Position)UserGlobals_Get_Value(ICON_PLACEMENT) )
    {
        case Icon_None:
            first_none = TRUE;
        default:
            break;
        case Icon_Top:
            rect.top_y = iconarea.top_y;
            rect.bottom_y = iconarea.top_y + siz.height - 1;
            area.bottom_y = iconarea.top_y + siz.height - 1;
            bigger_area.bottom_y = iconarea.top_y + (2* siz.height) - 1;
            break;
        case Icon_Bottom:
            rect.bottom_y = iconarea.bottom_y;
            rect.top_y = iconarea.bottom_y - siz.height + 1;
            area.top_y = iconarea.bottom_y - siz.height + 1;
            bigger_area.top_y = iconarea.bottom_y - (2*siz.height) + 1;
            break;
        case Icon_Left:
            rect.left_x = iconarea.left_x;
            rect.right_x = iconarea.left_x + siz.width - 1;
            area.right_x = iconarea.left_x + siz.width - 1;
            bigger_area.right_x = iconarea.left_x + (2*siz.width) - 1;
            break;
        case Icon_Right:
            rect.right_x = iconarea.right_x;
            rect.left_x = iconarea.right_x - siz.width + 1;
            area.left_x = iconarea.right_x - siz.width + 1;
            bigger_area.left_x = iconarea.right_x - (2*siz.width) + 1;
            break;
    }

    COMPUTE_CENTER( rect, center );

    if ( icon_positioned )
    {
        center = Tilwin_Get_Position( uwinp->iconp );        
        if ( first_none )
            result = Manage_Neighborhood_Icon_Open( uwinp, center );
        else
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp, 
                    area, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp, 
                    iconarea, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp, 
                    desk, center, siz );

    }
    else if ( first_none )
    {
        result = Tilwin_Open_Best_In_Area( uwinp->iconp, 
                iconarea, siz );
        if (! result)
            result = Tilwin_Open_Best_In_Area( uwinp->iconp, 
                    desk, siz );
    }

    else if (second_none)
    {
        result = Tilwin_Open_Best_In_Area( uwinp->iconp, 
                area, siz );
        if (! result)
            result = Tilwin_Open_Best_In_Area( uwinp->iconp, 
                bigger_area, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                iconarea, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                desk, center, siz );
    }
    else
    {
        result = Tilwin_Open_Nearest_In_Area( uwinp->iconp, 
                area, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp, 
                bigger_area, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                iconarea, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                desk, center, siz );
    }

    if ( result && !uwinp->icon_positioned )
    {
        uwinp->icon_positioned = TRUE;
        Tilwin_Set_Position( uwinp->iconp,
            Tilwin_Get_Center( uwinp->iconp ) );
    }

    return result;
}

/* ------------------------------------------------------------ */

void Manage_Update_Icons()
{
    Tilwinp winp;
    Userwin *uwinp;
    bool keep_updating;

    if ( UserGlobals_Get_Option(USE_ICONS) )
    {
        Tilwin_Gen_Just_Opened_Windows();
        while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
        {
            uwinp = Userwin_Get(winp);
            if ( ( uwinp->winp == winp ) && Tilwin_Is_Open( uwinp->iconp ) )
                Tilwin_Close( uwinp->iconp );
        }
    
        Tilwin_Gen_Just_Modified_Windows();
        while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
        {
            uwinp = Userwin_Get(winp);
            if ( ( uwinp->winp == winp ) && Tilwin_Is_Open( uwinp->iconp ) )
                Tilwin_Close( uwinp->iconp );
        }
    
        keep_updating = TRUE;
        while ( keep_updating )
        {
            keep_updating = FALSE;
            Tilwin_Gen_Closed_Windows();
            while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
            {
                uwinp = Userwin_Get(winp);
                if (  ( uwinp->iconp == winp )
                   && ( ! Tilwin_Is_Open( uwinp->winp ) )
                   && uwinp->ever_opened )
                    keep_updating |= Manage_Icon_Open( uwinp );
            }
        }
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static bool drawing = FALSE;
static bool redrawing = FALSE;

/* ------------------------------------------------------------ */

static void Manage_Update_Desktop()
{
    Tilwinp winp;
    Userwin *uwinp;

    Drawwin_Start();

    Tilwin_Gen_Just_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->current_type == body )
        {
            Manage_Unset( uwinp );
            Drawwin_Close( uwinp,
                (! Tilwin_Is_Covered( 
                       Tilwin_Get_Previous_Rectangle( winp ) ) ) );
            uwinp->output_sent = FALSE;
            if ( ( uwinp->client_state != IgnoreState ) &&
                 ( uwinp->client_state != NeverState ) )
                Closed_Add( uwinp );
        }
        else
        {
            DrawIcon_Close( uwinp );
        }

        if (! ( Tilwin_Is_Open(uwinp->winp) ||
                Tilwin_Is_Open(uwinp->iconp) ) )
        {
            if ( uwinp->client_state == IgnoreState )
                uwinp->wm_state = IgnoreState;
            else
                uwinp->wm_state = InactiveState;

            /* Window may be destroyed or rtl icon */

            if ( uwinp->client_state != NeverState )
                Client_Set_State( uwinp );
        }
    }

    Tilwin_Gen_Just_Modified_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);        
        if ( ( ! uwinp->positioned ) &&
             ( uwinp->current_type == body ) )
            Tilwin_Set_Position( winp,
                Tilwin_Get_Center( winp ) );
    }

    if ( drawing )
    {
        Tilwin_Gen_Just_Modified_Windows();
        while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
        {
            uwinp = Userwin_Get(winp);        
            if ( uwinp->current_type == body )
                Drawwin_Draw( uwinp );
            else
                DrawIcon_Draw( uwinp );
        }
    }
    else
    {
        Tilwin_Gen_Just_Modified_Windows();
        while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
            if ( Tilwin_Was_Actually_Modified(winp) || redrawing )
            {
                uwinp = Userwin_Get(winp);        
                if ( uwinp->current_type != body )
                    DrawIcon_Move_Close( uwinp );
                else if ( uwinp == switch_listener )
                    Drawwin_Listener_Move_Close( uwinp,
                        (! Tilwin_Is_Covered( 
                            Tilwin_Get_Previous_Rectangle( winp ) ) ) );
                else
                    Drawwin_Move_Close( uwinp,
                        (! Tilwin_Is_Covered( 
                            Tilwin_Get_Previous_Rectangle( winp ) ) ) );
            }
    
        Tilwin_Gen_Just_Modified_Windows();
        while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
        {
            uwinp = Userwin_Get(winp);        
            if ( Tilwin_Was_Actually_Modified(winp) || redrawing )
            {
                if ( uwinp->current_type != body )
                {
                    DrawIcon_Move_Open( uwinp );
                    if ( redrawing )
                        DrawIcon_Redraw( uwinp );
                }
                else if ( uwinp == switch_listener )
                    Drawwin_Listener_Move_Open( uwinp );
                else
                {
                    Drawwin_Move_Open( uwinp );
		    if ( redrawing )
                        Drawwin_Retitle( uwinp );
		}
            }
        }

        if ( listener != prev_listener )
        {
            if ( ( listener != UWIN_NULL ) &&
                 Tilwin_Was_Just_Modified( listener->winp ) &&
                 (! Tilwin_Was_Actually_Modified( listener->winp )) &&
                 ( listener->current_type == body ) )
                Drawwin_Display_Wrapping( listener );

            if ( ( prev_listener != UWIN_NULL ) &&
                 Tilwin_Was_Just_Modified( prev_listener->winp ) &&
                 (! Tilwin_Was_Actually_Modified( prev_listener->winp )) &&
                 ( prev_listener->current_type == body ) )
                Drawwin_Display_Wrapping( prev_listener );
        }
        else
        {
            if ( ( touch != UWIN_NULL ) &&
                 Tilwin_Was_Just_Modified( touch->winp ) &&
                 (! Tilwin_Was_Actually_Modified( touch->winp )) &&
                 ( touch->current_type == body ) )
                Drawwin_Display_Wrapping( touch );
        }
    }

    Tilwin_Gen_Just_Opened_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( winp == uwinp->winp )
        {
            uwinp->current_type = body;
            uwinp->sized = TRUE;
            if ( ! uwinp->positioned )
                Tilwin_Set_Position( winp,
                    Tilwin_Get_Center( winp ) );
            Drawwin_Open( uwinp );
            Closed_Remove( uwinp );
            uwinp->wm_state = NormalState;
        }
        else
        {
            if ( uwinp != rtl_uwinp )
                uwinp->current_type = icon;
            DrawIcon_Open( uwinp );
            if ( Userwin_Get_Window_Option( uwinp, CLIENT_DRAWS_ICON ) )
                uwinp->wm_state = ClientIconState;
            else
                uwinp->wm_state = IconicState;
        }
        if ( uwinp->current_type != rtl )
            Client_Set_State( uwinp );
    }   

    if (! drawing )
    {
        Tilwin_Gen_Just_Closed_Windows();
        while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
        {
            uwinp = Userwin_Get(winp);
            if ( uwinp->winp == winp )
                Drawwin_Unmap( uwinp );                       
        }
    }

    Drawwin_Finish();

    switch_listener = UWIN_NULL;
    prev_touch = touch;
    touch = UWIN_NULL;
}    
        
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Save_State( uwinp )
    Userwin *uwinp;
{
    uwinp->undo_stamp = Tilwin_Get_Timestamp();

    uwinp->prev_positioned = uwinp->positioned;
    uwinp->prev_sized = uwinp->sized;
    uwinp->prev_zoomed = uwinp->zoomed;

    uwinp->prev_group_state = uwinp->group_state;

    uwinp->prev_desire = Tilwin_Get_Desired( uwinp->winp );
    uwinp->prev_min = Tilwin_Get_Min( uwinp->winp );
    uwinp->prev_max = Tilwin_Get_Max( uwinp->winp );

    uwinp->prev_rezoom_rect = uwinp->rezoom_rect;
}

/* ------------------------------------------------------------ */

static void Manage_Exchange_State( uwinp )
    Userwin *uwinp;
{
    Size temp_size;

    if ( last_stamp != uwinp->undo_stamp )
        return;

    SWAP_BOOL( uwinp->prev_positioned, uwinp->positioned )
    SWAP_BOOL( uwinp->prev_sized, uwinp->sized )
    SWAP_BOOL( uwinp->prev_zoomed, uwinp->zoomed )

    SWAP_INT( uwinp->prev_group_state, uwinp->group_state )

    SWAP_RECT( uwinp->prev_rezoom_rect, uwinp->rezoom_rect )

    temp_size = Tilwin_Get_Desired( uwinp->winp );
    Tilwin_Set_Desired( uwinp->winp, uwinp->prev_desire );
    uwinp->prev_desire = temp_size;

    temp_size = Tilwin_Get_Min( uwinp->winp );
    Tilwin_Set_Min( uwinp->winp, uwinp->prev_min );
    uwinp->prev_min = temp_size;

    temp_size = Tilwin_Get_Max( uwinp->winp );
    Tilwin_Set_Max( uwinp->winp, uwinp->prev_max );
    uwinp->prev_max = temp_size;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Cant_Undo()
{
    prev_listener = listener;
    Tilwin_Start_Transaction();
    Tilwin_Commit_Transaction();
    last_stamp = Tilwin_Get_Timestamp();
}

/* ------------------------------------------------------------ */

void Manage_Start()
{
    if ( Tilwin_Transaction_Depth() == 0 )
        prev_listener = listener;
    Tilwin_Start_Transaction();
}

/* ------------------------------------------------------------ */

static void Manage_Restart()
{
    Tilwin_Abort_Transaction();
    Tilwin_Start_Transaction();
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

extern bool Manage_Repopulate_Since();
extern bool Manage_Aggressive_Repopulation();

/* ------------------------------------------------------------ */

static bool Manage_Unzoom_Repopulation()
{
    TimeStamp repop_since;
    Tilwinp winp;
    Userwin *uwinp;
    bool result = FALSE;

    repop_since = last_stamp;

    Tilwin_Gen_Just_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( ( uwinp->current_type == body ) &&
             ( ( uwinp->zoomed ) ||
               ( ( uwinp->undo_stamp == last_stamp ) &&
                 ( uwinp->prev_zoomed ) ) ) )
        {
            if (! UserGlobals_Get_Option(
                      ONLY_REPOP_SINCE_ON_AUTO_UNZOOM) )
                repop_since = (TimeStamp)0;
            else if ( uwinp->zoom_stamp < repop_since )
                repop_since = uwinp->zoom_stamp;
        }
    }

    Tilwin_Gen_Just_Modified_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( ( uwinp->current_type == body ) &&
             (! uwinp->zoomed ) &&
             ( uwinp->undo_stamp == last_stamp ) &&
             ( uwinp->prev_zoomed ) )
        {
            if (! UserGlobals_Get_Option(
                      ONLY_REPOP_SINCE_ON_AUTO_UNZOOM) )
                repop_since = (TimeStamp)0;
            else if ( uwinp->zoom_stamp < repop_since )
                repop_since = uwinp->zoom_stamp;
        }
    }
    
    if ( repop_since < last_stamp )
    {
        user_global_join_excursion( 
            REQUIRE_PREV_POS_ON_AUTO_REPOP, TRUE,
            {
                if ( Manage_Repopulate_Since( 
                         repop_since, FALSE, FALSE, TRUE ) )
                    result = TRUE;
            } )
        if ( Manage_Repopulate_Since( 
                 repop_since, FALSE, FALSE, TRUE ) )
            result = TRUE;
    }
    
    return result;
}

/* ------------------------------------------------------------ */

static bool Manage_Finish_Repopulation()
{
    bool result;

    result = FALSE;

    if ( UserGlobals_Get_Option(AUTO_REPOPULATE_LAST) )
        if ( Manage_Repopulate_Since( 
            last_stamp, FALSE, FALSE, TRUE ) )
            result = TRUE;

    if ( UserGlobals_Get_Option(ALLOW_AGGRESSIVE_REPOPULATION) )
        if ( Manage_Aggressive_Repopulation() )
            result = TRUE;

    if ( UserGlobals_Get_Option(
             AUTO_REPOPULATE_ON_AUTO_UNZOOM) )
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
        {
            if ( Manage_Unzoom_Repopulation() )
                result = TRUE;
        } )
        

    return result;
}

/* ------------------------------------------------------------ */

extern void Manage_Auto_Prorate();
extern void Manage_Ordered_Desire();

void Manage_Finish( result )
    bool result;
{
    extern void Manage_Ordered_Desire();
    bool allow_repop_shrink, can_repop, can_size;

    if ( Tilwin_Transaction_Depth() > 1 )
        Tilwin_Commit_Transaction();

    else if (! result)
    {
        Tilwin_Abort_Transaction();
        Draw_Flash();
    }

    else
    {
        last_stamp = Tilwin_Get_Timestamp();

        allow_repop_shrink = 
             Tilwin_Get_Global_Option(ALLOW_AUTOMATIC_SHRINK) &&
             Tilwin_Get_Global_Option(ALLOW_AUTO_SHRINK_MORE_RECENT) &&
             UserGlobals_Get_Option(
                 ALLOW_AUTO_SHRINK_ON_AUTO_REPOP);

        can_repop =  Layout_Done() || 
                     UserGlobals_Get_Option( ENABLE_AUTO_REPOP_DURING_LAYOUT );

        can_size =  Layout_Done() || 
                    UserGlobals_Get_Option( ENABLE_AUTO_SIZING_DURING_LAYOUT );

        Manage_Update_Icons();

        if ( allow_repop_shrink && can_size &&
             UserGlobals_Get_Option(AUTO_DESIRED_ENLARGE) )
            Manage_Ordered_Desire();

        if ( can_repop && Manage_Finish_Repopulation() )
            Manage_Update_Icons();            

        if ( can_size &&
             UserGlobals_Get_Option(AUTO_DESIRED_ENLARGE) )       
            Manage_Ordered_Desire();

        if ( can_size &&
             UserGlobals_Get_Option(AUTO_PRORATE) )
            while ( TRUE )
            {
                Manage_Auto_Prorate();

                if ( can_size && 
                     UserGlobals_Get_Option(
                         TRY_REPOP_AGAIN_AFT_AUTO_PRORATE) &&
                     Manage_Finish_Repopulation() )
                    Manage_Update_Icons();
                else
                    break;
            }
        
        Manage_Update_Desktop();
        Tilwin_Commit_Transaction();
    }

}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

bool Manage_Finish_Fixed_Completely( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result && ( uwinp != UWIN_NULL ) )
      window_excursion( uwinp->winp, FIXED_COMPLETELY, TRUE,
        Manage_Finish( TRUE ) )
    else
        Manage_Finish( result );
    return result;
}

/* ------------------------------------------------------------ */

bool Manage_Finish_Fixed_Size( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result && ( uwinp != UWIN_NULL ) )
      window_excursion( uwinp->winp, FIXED_SIZE, TRUE,
        Manage_Finish( TRUE ) )
    else
        Manage_Finish( result );
    return result;
}

/* ------------------------------------------------------------ */

bool Manage_Finish_Locked( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result && ( uwinp != UWIN_NULL ) )
      window_excursion( uwinp->winp, REQUIRE_MANUAL_CLOSE, TRUE,
        Manage_Finish( TRUE ) )
    else
        Manage_Finish( result );
    return result;
}

/* ------------------------------------------------------------ */

bool Manage_Finish_Minned( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result && ( uwinp != UWIN_NULL ) )
        min_excursion( uwinp->winp,
          window_excursion( uwinp->winp, REQUIRE_MANUAL_CLOSE, TRUE,
            Manage_Finish( TRUE ) ) )
    else
        Manage_Finish( result );
    return result;
}

/* ------------------------------------------------------------ */

#define Manage_Client_Finish_Minned(uwinp,op)  \
    Manage_Client(  \
    {  \
        op;  \
        Manage_Finish_Minned( uwinp, TRUE );  \
    } )

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Undo_Start()
{
    Tilwinp winp;
    Userwin *uwinp;

    Tilwin_Undo();

    Tilwin_Gen_Just_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->winp == winp )
            Manage_Exchange_State( uwinp );
    }

    Tilwin_Gen_Just_Modified_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->winp == winp )
            Manage_Exchange_State( uwinp );
    }

    Tilwin_Gen_Just_Opened_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->winp == winp )
            Manage_Exchange_State( uwinp );
    }

    Tilwin_Continue_Transaction();

    if ( listener != prev_listener )
    {
        if ( listener != UWIN_NULL )
        {
            listener->listener = FALSE;
            Tilwin_Act_Modified( listener->winp );
        }

        SWAP_UWINP( listener, prev_listener )

        touch = prev_touch;

        if ( listener != UWIN_NULL )
        {
            listener->listener = TRUE;
            Tilwin_Act_Modified( listener->winp );
        }
    }

}

/* ------------------------------------------------------------ */

void Manage_Undo()
{
    Tilwinp winp;
    Userwin *uwinp;

    Manage_Undo_Start();

    if ( UserGlobals_Get_Option(USE_ICONS) )
    {
        Tilwin_Gen_Just_Closed_Windows();
        while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
        {
            uwinp = Userwin_Get(winp);
            if (! ( Tilwin_Is_Open( uwinp->winp ) ||
                    Tilwin_Is_Open( uwinp->iconp ) ) )
                Manage_Icon_Open( uwinp );
        }
    }

    user_global_excursion( AUTO_PRORATE, FALSE,
        user_global_excursion( AUTO_REPOPULATE_LAST, FALSE,
        user_global_excursion( ALLOW_AGGRESSIVE_REPOPULATION, FALSE,
            Manage_Finish( TRUE )
        ) ) )
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Redraw( uwinp )
    Userwin *uwinp;
{
    if ( uwinp->current_type == body )
        Drawwin_Redraw(uwinp);
    else
        DrawIcon_Redraw(uwinp);
}

/* ------------------------------------------------------------ */

void Manage_Redraw_All()
{
    Tilwinp winp;

    if ( Drawwin_Redraw_All( Tilwin_Get_Desktop_Rectangle() ) )
        return;

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
        Manage_Redraw( Userwin_Get(winp) );
}

/* ------------------------------------------------------------ */

void Manage_Finish_Layout()
{
    Manage_Start();
    Layout_Finish();
    Manage_Finish( TRUE );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Initial_Icon_Open( uwinp )
    Userwin *uwinp;
{
    Manage_Start();
    Tilwin_Note_Use( uwinp->winp );
    if ( uwinp->client_state != IgnoreState )
    {
        Closed_Add( uwinp );
        if ( UserGlobals_Get_Option(USE_ICONS) )
        {
            if (! uwinp->layout_found )
                Manage_Icon_Open( uwinp );
            else
                global_excursion( ENABLE_GRAVITY, FALSE,
                  user_window_excursion( uwinp,
                    REQUIRE_PREVIOUS_ICON_POSITION, TRUE,
                    Manage_Icon_Open( uwinp ) ) )
        }
    }
    Manage_Finish( TRUE );
}

/* ------------------------------------------------------------ */

void Manage_Prepare_Open( uwinp )
    Userwin *uwinp;
{
    if (! uwinp->layout)
        Manage_Layout( uwinp );

    Tilwin_Set_Position( uwinp->winp,
        Tilwin_Get_Center( uwinp->winp ) );

    Tilwin_Set_Position( uwinp->iconp,
        Tilwin_Get_Center( uwinp->iconp ) );
        
    Drawwin_Insert( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Note_Output( uwinp )
    Userwin *uwinp;
{
    if (! uwinp->layout)
        Manage_Layout( uwinp );

    if ( Tilwin_Is_Open( uwinp->winp ) )
    {
        if ( Userwin_Get_Window_Option( uwinp, NOTE_OPEN_OUTPUT ) )
            Tilwin_Note_Use( uwinp->winp );
    }
    else if ( Userwin_Get_Window_Option( uwinp, NOTE_CLOSED_OUTPUT ) )
        Tilwin_Note_Use( uwinp->winp );

    if (! uwinp->output_sent)
    {
        uwinp->output_sent = TRUE;
        if ( Tilwin_Is_Open(uwinp->iconp) )
            DrawIcon_Note_Output( uwinp );
    }
}         

/* ------------------------------------------------------------ */

void Manage_Note_Input( uwinp )
    Userwin *uwinp;
{
    if ( Tilwin_Is_Open( uwinp->winp ) )
    {
        if ( Userwin_Get_Window_Option( uwinp, NOTE_OPEN_INPUT ) )
            Tilwin_Note_Use( uwinp->winp );
        else if ( ( uwinp == listener ) &&
                  Userwin_Get_Window_Option( uwinp, NOTE_LISTENER_INPUT ) )
            Tilwin_Note_Use( uwinp->winp );
    }
    else if ( Userwin_Get_Window_Option( uwinp, NOTE_CLOSED_INPUT ) )
        Tilwin_Note_Use( uwinp->winp );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Init_Rtl()
{
    Userwin *uwinp;
    
    Manage_Start();
    uwinp = Manage_Init_Window();
    rtl_uwinp = uwinp;
    
    uwinp->winnum = 0;
    uwinp->connection = -1;

    uwinp->client_state = NeverState;
    uwinp->current_type = rtl;
    uwinp->layout = TRUE;
    uwinp->layout_found = TRUE;

    Userwin_Set_Window_Option( uwinp, SHOW_ICON,
        UserGlobals_Get_Option(USE_RTL_ICON) );

    Tilwin_Set_Window_Option( uwinp->iconp, FIXED_SIZE, TRUE );

    Userwin_Set_Window_Option( uwinp, SAVE_IN_LAYOUT, FALSE );
    Userwin_Set_Window_Option( uwinp, CONSIDER_FOR_REPOPULATION, FALSE );

    DrawIcon_Init_Rtl( uwinp );

    if ( UserGlobals_Get_Option(USE_ICONS) )
        Manage_Icon_Open( uwinp );

    Manage_Finish( TRUE );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Start_Repaint()
{
    Tilwin_Start_Transaction();
}

/* ------------------------------------------------------------ */

void Manage_Repaint_Rect( rect )
    TWRectangle rect;
{
    Tilwin_Modify_Covered_Windows( rect );
    Drawwin_Draw_Background( rect );
}

/* ------------------------------------------------------------ */

void Manage_Finish_Repaint()
{
    Tilwinp winp;
    Tilwin_Commit_Transaction();

    Tilwin_Gen_Just_Modified_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        Manage_Redraw( Userwin_Get(winp) );
    }

    Manage_Cant_Undo();
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Set_Desktop_Size( desksiz )
    Size desksiz;
{
    Tilwin_Set_Desktop_Size( desksiz );
    Drawwin_Draw_Background( Tilwin_Get_Desktop_Rectangle() );
}

/* ------------------------------------------------------------ */

static void Manage_Reorganize_Desktop( desksiz )
    Size desksiz;
{
    Tilwinp winp, head, middle, tail;
    Userwin *uwinp;
    TWPoint center;
    TWPoint pos;
    TWRectangle rect;
    Size siz;
    Size old_desksiz;
    TWRectangle old_deskrect, deskrect;

    head = middle = tail = WIN_NULL;

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->current_type != body )
        {
            if ( UserGlobals_Get_Option(USE_ICONS) &&
                 ( uwinp != rtl_uwinp ) )
            {
                if ( tail == WIN_NULL ) tail = winp;
                if ( middle == WIN_NULL ) middle = winp;
                Tilwin_Put_Data( winp, head );
                head = winp;
            }
        }
        else if ( Tilwin_Get_Window_Option( winp, REQUIRE_MANUAL_CLOSE ) )
        {
            if ( middle == WIN_NULL )
            {
                if ( tail == WIN_NULL ) tail = winp;
                Tilwin_Put_Data( winp, head );
                head = winp;
                middle = winp;
            }
            else if ( middle == tail )
            {
                Tilwin_Put_Data( tail, winp );
                Tilwin_Put_Data( winp, WIN_NULL );
                tail = winp;
                middle = winp;
            }
            else
            {
                Tilwin_Put_Data( winp, Tilwin_Get_Data( middle ) );
                Tilwin_Put_Data( middle, winp );
                middle = winp;
            }
        }
        else
        {
            if ( head == WIN_NULL )
                head = winp;
            else
                Tilwin_Put_Data( tail, winp );
            Tilwin_Put_Data( winp, WIN_NULL );
            tail = winp;
        }

        Tilwin_Auto_Close( winp );
    }
        
    old_desksiz = Tilwin_Get_Desktop_Size();
    old_deskrect = Tilwin_Get_Desktop_Rectangle();
    Tilwin_Set_Desktop_Size( desksiz );
    desksiz = Tilwin_Get_Desktop_Size();
    deskrect = Tilwin_Get_Desktop_Rectangle();
    
    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);

        if ( uwinp->winp == winp )
            Manage_Retitle( uwinp );

        center = Tilwin_Get_Center( winp );
        pos = Tilwin_Get_Position( winp );
        rect = Tilwin_Get_Rectangle( winp );

        siz = Tilwin_Get_Size( winp );

        if ( desksiz.width < old_desksiz.width )
        {
            siz.width =  ( siz.width * desksiz.width ) /
                old_desksiz.width;
            center.x = ( center.x * desksiz.width ) /
                old_desksiz.width;
            pos.x = ( pos.x * desksiz.width ) /
                old_desksiz.width;
        }
        else if ( rect.right_x == old_deskrect.right_x )
        {
            center.x += ( desksiz.width - old_desksiz.width );
            pos.x += ( desksiz.width - old_desksiz.width );
        }
        else if ( rect.left_x != 0 )
        {
            center.x = ( center.x * desksiz.width ) /
                old_desksiz.width;
            pos.x = ( pos.x * desksiz.width ) /
                old_desksiz.width;
        }

        if ( desksiz.height < old_desksiz.height )
        {
            siz.height =  ( siz.height * desksiz.height ) /
                old_desksiz.height;
            center.y = ( center.y * desksiz.height ) /
                old_desksiz.height;
            pos.y = ( pos.y * desksiz.height ) /
                old_desksiz.height;
        }
        else if ( rect.bottom_y == old_deskrect.bottom_y )
        {
            center.y += ( desksiz.height - old_desksiz.height );
            pos.y += ( desksiz.height - old_desksiz.height );
        }
        else if ( rect.top_y != 0 )
        {
            center.y = ( center.y * desksiz.height ) /
                old_desksiz.height;
            pos.y = ( pos.y * desksiz.height ) /
                old_desksiz.height;
        }

        Set_Min_Size( siz, siz, Tilwin_Get_Max( winp ) )
        Set_Max_Size( siz, siz, Tilwin_Get_Min( winp ) )

        Tilwin_Set( winp, center, siz );
        Tilwin_Set_Position( winp, pos );
    }

    if ( UserGlobals_Get_Option(USE_ICONS) )
        Manage_Icon_Open( rtl_uwinp );

    for ( winp = head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->current_type == body )
            Tilwin_Open_Nearest_In_Area( winp, deskrect,
                Tilwin_Get_Center( winp ), Tilwin_Get_Size( winp ) );
        else if ( UserGlobals_Get_Option(USE_ICONS) )
            Manage_Icon_Open( uwinp );
    }

    if ( UserGlobals_Get_Option(AUTO_REPOP_ON_DESKTOP_RESIZE) )
        Manage_Repopulate_Since( (TimeStamp)0, TRUE, FALSE, TRUE );

}

/* ------------------------------------------------------------ */

void Manage_Resize_Desktop( desksiz )
    Size desksiz;
{
    drawing = TRUE;
    Manage_Start();
    Manage_Reorganize_Desktop( desksiz );
    Drawwin_Draw_Background( Tilwin_Get_Desktop_Rectangle() );
    Manage_Finish( TRUE );
    drawing = FALSE;
    Manage_Cant_Undo();
}    

/* ------------------------------------------------------------ */

void Manage_Profile( filnam )
    char *filnam;
{
    int primary, secondary;
    Userwin *uwinp;
    Tilwinp winp;

    Manage_Start();

    secondary = UserGlobals_Get_Value( SECONDARY_ICON_PLACEMENT);
    primary = UserGlobals_Get_Value( ICON_PLACEMENT);

    if (! UserGlobals_Get_Option(ALLOW_LISTENER_TO_CLOSE))
    {
        if ( listener != UWIN_NULL )
            Tilwin_Set_Window_Option( listener->winp, REQUIRE_MANUAL_CLOSE,
                                      listener->regular_manual_close );
        if ( sublistener != UWIN_NULL )
            Tilwin_Set_Window_Option( sublistener->winp, REQUIRE_MANUAL_CLOSE,
                                      sublistener->regular_manual_close );
    }

    Profile_Update( filnam );

    Userwin_Set_Window_Option( rtl_uwinp, SHOW_ICON,
        UserGlobals_Get_Option(USE_RTL_ICON) );

    Manage_Reorganize_Desktop( Tilwin_Get_Desktop_Size() );

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->iconp == winp )
        {
            if ( ( secondary !=
                   UserGlobals_Get_Value(SECONDARY_ICON_PLACEMENT) ) ||
                 ( primary !=
                   UserGlobals_Get_Value(ICON_PLACEMENT) ) )
                Tilwin_Set_Position( winp, Tilwin_Get_Center( winp ) );
        }
    }

    if (! UserGlobals_Get_Option(ALLOW_LISTENER_TO_CLOSE))
    {
        if ( listener != UWIN_NULL )
            Tilwin_Set_Window_Option( listener->winp, 
                REQUIRE_MANUAL_CLOSE, TRUE );
        if ( sublistener != UWIN_NULL )
            Tilwin_Set_Window_Option( sublistener->winp, 
                REQUIRE_MANUAL_CLOSE, TRUE );
    }

    redrawing = TRUE;
    Manage_Finish( TRUE );
    redrawing = FALSE;
}
        
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

#define Manage_Set_Rezoom_Horizontal(uwinp,op) \
{ \
    if ( Tilwin_Get_Rectangle(uwinp->winp).left_x == 0 ) \
        window_excursion( uwinp->winp, FIXED_LEFT_EDGE, TRUE, op ) \
    else if ( Tilwin_Get_Rectangle(uwinp->winp).right_x == \
              ( Tilwin_Get_Desktop_Size().width - 1 ) ) \
        window_excursion( uwinp->winp, FIXED_RIGHT_EDGE, TRUE, op ) \
    else if ( Tilwin_Get_Rectangle(uwinp->winp).left_x == \
              uwinp->rezoom_rect.left_x ) \
        window_excursion( uwinp->winp, FIXED_LEFT_EDGE, TRUE, op ) \
    else if ( Tilwin_Get_Rectangle(uwinp->winp).right_x == \
              uwinp->rezoom_rect.right_x ) \
        window_excursion( uwinp->winp, FIXED_RIGHT_EDGE, TRUE, op ) \
    else op; \
}

/* ------------------------------------------------------------ */

#define Manage_Set_Rezoom_Vertical(uwinp,op) \
{ \
    if ( Tilwin_Get_Rectangle(uwinp->winp).top_y == 0 ) \
        window_excursion( uwinp->winp, FIXED_TOP_EDGE, TRUE, op ) \
    else if ( Tilwin_Get_Rectangle(uwinp->winp).bottom_y == \
              ( Tilwin_Get_Desktop_Size().height - 1 ) ) \
        window_excursion( uwinp->winp, FIXED_BOTTOM_EDGE, TRUE, op ) \
    else if ( Tilwin_Get_Rectangle(uwinp->winp).top_y == \
              uwinp->rezoom_rect.top_y ) \
        window_excursion( uwinp->winp, FIXED_TOP_EDGE, TRUE, op ) \
    else if ( Tilwin_Get_Rectangle(uwinp->winp).bottom_y == \
              uwinp->rezoom_rect.bottom_y ) \
        window_excursion( uwinp->winp, FIXED_BOTTOM_EDGE, TRUE, op ) \
    else op; \
}

/* ------------------------------------------------------------ */

static bool Manage_Rezoom( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    bool result;

    Manage_Set_Rezoom_Vertical( uwinp,
        Manage_Set_Rezoom_Horizontal( uwinp,
            result = Tilwin_Set_Size( uwinp->winp, siz ) ) );
    return result;
}

/* ------------------------------------------------------------ */

static bool Manage_Rezoom_In_Area( uwinp, rect, pt, siz )
    Userwin *uwinp;
    TWRectangle rect;
    TWPoint pt;
    Size siz;
{
    bool result;

    Manage_Set_Rezoom_Vertical( uwinp,
        Manage_Set_Rezoom_Horizontal( uwinp,
            result = Tilwin_Open_Nearest_In_Area(
                uwinp->winp, rect, pt, siz ) ) );
    return result;
}

/* ------------------------------------------------------------ */

static bool Manage_Neighborhood_Rezoom( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    TWRectangle rect;
    TWPoint pt;
    bool result;

    pt = Tilwin_Get_Center( uwinp->winp );
    rect = Manage_Neighborhood_Rectangle( 0.5, pt, siz );

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
    { window_excursion( uwinp->winp, FIXED_SIZE, TRUE,
    { 
        result = Manage_Rezoom( uwinp, siz );
        if (! result)
            result = Manage_Rezoom_In_Area( uwinp, rect, pt, siz );
    } ) } );

    if (! result)
        result = Tilwin_Open_Nearest_In_Area( uwinp->winp, rect, pt, siz );

    return result;
}

/* ------------------------------------------------------------ */

static bool Manage_Neighborhood_Unzoom_Open( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    TWRectangle rect;
    TWPoint pt;
    bool result;

    pt = Tilwin_Get_Center( uwinp->winp );
    rect = Tilwin_Get_Rectangle( uwinp->winp );

    result = Manage_Rezoom_In_Area( uwinp, rect, pt, siz );

    if (! result)
        result = Tilwin_Open_Nearest_In_Area( 
            uwinp->winp, rect, pt, siz ); 

    if ( (! result) && 
         (! Userwin_Get_Window_Option( 
             uwinp, REQUIRE_PREV_POS ) ) )
        result = Tilwin_Open_Nearest_In_Area( 
            uwinp->winp,
            Tilwin_Get_Desktop_Rectangle(),
            pt, siz );

    return result;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Setup_Zoom( uwinp, full )
    Userwin *uwinp;
    bool full;
{
    Size siz;

    Manage_Save_State( uwinp );

    uwinp->zoomed = TRUE;

    uwinp->regular_min = Tilwin_Get_Min(uwinp->winp);
    uwinp->regular_size = Tilwin_Get_Desired(uwinp->winp);

    if ( full )
    {
        if ( Userwin_Get_Window_Option( uwinp, ZOOM_FULL_HEIGHT ) )
            uwinp->zoom_size.height = Tilwin_Get_Desktop_Size().height;
        if ( Userwin_Get_Window_Option( uwinp, ZOOM_FULL_WIDTH ) )
            uwinp->zoom_size.width = Tilwin_Get_Desktop_Size().width;
    }

    if ( UserGlobals_Get_Option( RESET_ZOOM_MIN ) )
    {
        if ( UserGlobals_Get_Option( RESET_ZOOM_MIN_USES_DESIRE ) )
            Set_Min_Size( siz, uwinp->regular_size,
                Tilwin_Get_Size( uwinp->winp ) )
        else
            siz = Tilwin_Get_Size( uwinp->winp );

        if ( UserGlobals_Get_Option( RESET_ZOOM_MIN_ALLOWS_DECREASE ) )
            uwinp->zoom_min = siz;
        else
            Set_Max_Size( uwinp->zoom_min, uwinp->zoom_min, siz )
    }

    if ( Userwin_Get_Window_Option( uwinp, ZOOM_TIED_TO_DESIRE ) )
    {
        uwinp->zoom_min = uwinp->zoom_size = uwinp->regular_size;
    }

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MINIMUMS ) )
    {
        Set_Max_Size( uwinp->zoom_min, uwinp->zoom_min,
                      uwinp->client_min )
        Set_Max_Size( uwinp->zoom_size, uwinp->zoom_size,
                      uwinp->client_min )
    }

    Set_Max_Size( uwinp->zoom_min, uwinp->zoom_min,
                  uwinp->regular_min )
    Set_Max_Size( uwinp->zoom_size, uwinp->zoom_size,
                  uwinp->regular_size )

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MAXIMUMS ) )
    {
        Set_Min_Size( uwinp->zoom_min, uwinp->zoom_min,
                      uwinp->client_max )
        Set_Min_Size( uwinp->zoom_size, uwinp->zoom_size,
                      uwinp->client_max )
    }

    Tilwin_Set_Min( uwinp->winp, uwinp->zoom_min );
    Tilwin_Set_Desired( uwinp->winp, uwinp->zoom_size );

}

/* ------------------------------------------------------------ */

static void Manage_Setup_Unzoom( uwinp )
    Userwin *uwinp;
{
    Manage_Save_State( uwinp );

    uwinp->zoomed = FALSE;

    uwinp->zoom_min = Tilwin_Get_Min(uwinp->winp);
    uwinp->zoom_size = Tilwin_Get_Desired(uwinp->winp);

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MAXIMUMS ) )
    {
        Set_Min_Size( uwinp->regular_min, uwinp->regular_min,
                      uwinp->client_max )
        Set_Min_Size( uwinp->regular_size, uwinp->regular_size,
                      uwinp->client_max )
    }

    Set_Min_Size( uwinp->regular_min, uwinp->regular_min,
                  uwinp->zoom_min )
    Set_Min_Size( uwinp->regular_size, uwinp->regular_size,
                  uwinp->zoom_size )

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MINIMUMS ) )
    {
        Set_Max_Size( uwinp->regular_min, uwinp->regular_min,
                      uwinp->client_min )
        Set_Max_Size( uwinp->regular_size, uwinp->regular_size,
                      uwinp->client_min )
    }

    Tilwin_Set_Min( uwinp->winp, uwinp->regular_min );
    Tilwin_Set_Desired( uwinp->winp, uwinp->regular_size );
}

/* ------------------------------------------------------------ */

static Size Manage_Get_Zoom_Size( uwinp )
    Userwin *uwinp;
{
    Size cursiz, siz;

    cursiz = Tilwin_Get_Size(uwinp->winp);

    Set_Max_Size( siz, uwinp->zoom_size, uwinp->zoom_min )

    if ( Tilwin_Is_Open( uwinp->winp ) &&
         ( siz.width < cursiz.width ) &&
         ( siz.height < cursiz.height ) )
        siz = cursiz;

    return Tilwin_Checked_Size( uwinp->winp, siz );
}

/* ------------------------------------------------------------ */

static Size Manage_Get_Unzoom_Open_Size( uwinp )
    Userwin *uwinp;
{
    Size siz;

    Set_Max_Size( siz, uwinp->zoom_size, uwinp->regular_min )

    return Tilwin_Checked_Size( uwinp->winp, siz );
}

/* ------------------------------------------------------------ */

static Size Manage_Get_Closed_Unzoom_Size( uwinp )
    Userwin *uwinp;
{
    Size siz;

    Set_Max_Size( siz, uwinp->regular_size, uwinp->regular_min )
    Set_Min_Size( siz, siz, Tilwin_Get_Size(uwinp->winp) )

    return Tilwin_Checked_Size( uwinp->winp, siz );
}

/* ------------------------------------------------------------ */

static Size Manage_Get_Open_Unzoom_Size( uwinp )
    Userwin *uwinp;
{
    Size siz;

    COMPUTE_SIZE( uwinp->rezoom_rect, siz );
    Set_Min_Size( siz, siz, uwinp->regular_size )
    Set_Min_Size( siz, siz, Tilwin_Get_Size(uwinp->winp) )
    Set_Max_Size( siz, siz, uwinp->regular_min )

    return Tilwin_Checked_Size( uwinp->winp, siz );
}

/* ------------------------------------------------------------ */

static bool Manage_Followup_Zoom( uwinp )
    Userwin *uwinp;
{
    Size siz;
    bool result;

    siz = Manage_Get_Zoom_Size( uwinp );

    if ( ( siz.width < uwinp->zoom_min.width ) ||
         ( siz.height < uwinp->zoom_min.height ) )
        result = FALSE;
    else         
        global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE,
            Userwin_Get_Window_Option( uwinp, ALLOW_ZOOM_CLOSE ),
            {
                result = Manage_Neighborhood_Rezoom( uwinp, siz );
            } )

    if ( result )
    {
        Set_Max_Size( siz, siz, 
                      Tilwin_Get_Previous_Size( uwinp->winp ) );

        global_restrict_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
            global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
                Tilwin_Enlarge_Nearest( uwinp->winp, 
                    Tilwin_Get_Previous_Center( uwinp->winp ),
                    siz ) ) )

        Tilwin_Act_Modified( uwinp->winp );
        uwinp->zoom_stamp = Tilwin_Get_Timestamp();
        uwinp->rezoom_rect = Tilwin_Get_Previous_Rectangle( uwinp->winp );
    }
    else
        Manage_Setup_Unzoom( uwinp );

    return result;
}

/* ------------------------------------------------------------ */

static void Manage_Followup_Unzoom( uwinp, explicit )
    Userwin *uwinp;
    bool explicit;
{
    bool force_repop;
    bool force_shrink;
    bool allow_shrink;
    TimeStamp repop_since;
    TWPoint pt;
    Size siz;

    if (! Tilwin_Is_Open( uwinp->winp ) )
        Manage_Rezoom( uwinp, Manage_Get_Closed_Unzoom_Size( uwinp ) );
    else
    {
        Tilwin_Act_Modified( uwinp->winp );

        if ( explicit )
        {
            allow_shrink = 
                Userwin_Get_Window_Option(uwinp,ALLOW_SHRINK_ON_UNZOOM);
            force_shrink = 
                Userwin_Get_Window_Option(uwinp,FORCE_SHRINK_ON_UNZOOM);
            force_repop = UserGlobals_Get_Option(
                               AUTO_REPOP_ON_EXPLICIT_UNZOOM);
            if ( UserGlobals_Get_Option(
                     ONLY_REPOP_SINCE_ON_EXPL_UNZOOM) )
                repop_since = uwinp->zoom_stamp;
            else
                repop_since = (TimeStamp)0;
        }
        else 
        {
            allow_shrink = 
                Userwin_Get_Window_Option(uwinp,ALLOW_SHRINK_ON_UNZOOM) &&
                Userwin_Get_Window_Option(uwinp,ALLOW_SHRINK_ON_AUTO_UNZOOM);
            force_shrink = 
                Userwin_Get_Window_Option(uwinp,FORCE_SHRINK_ON_UNZOOM) &&
                Userwin_Get_Window_Option(uwinp,FORCE_SHRINK_ON_AUTO_UNZOOM);
            force_repop = UserGlobals_Get_Option(
                               AUTO_REPOPULATE_ON_AUTO_UNZOOM);
            if ( UserGlobals_Get_Option(
                     ONLY_REPOP_SINCE_ON_AUTO_UNZOOM) )
                repop_since = uwinp->zoom_stamp;
            else
                repop_since = (TimeStamp)0;
        }

        if ( allow_shrink || force_shrink )
        {
            COMPUTE_CENTER( uwinp->rezoom_rect, pt );
            siz = Manage_Get_Open_Unzoom_Size( uwinp );
            global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
            { 
                if ( Tilwin_Set( uwinp->winp, pt, siz ) )
                    Tilwin_Set_Position( uwinp->winp, pt );
                else
                    Manage_Rezoom( uwinp, siz );
            } )
        }

        if ( force_repop )
        {
            user_global_excursion( 
                REQUIRE_PREV_POS_ON_AUTO_REPOP, TRUE,
                Manage_Repopulate_Since( repop_since, FALSE, FALSE, TRUE ) );
        }

        if ( UserGlobals_Get_Option(AUTO_DESIRED_ENLARGE) )
	    window_excursion( uwinp->winp, FIXED_SIZE, TRUE,
	        Manage_Ordered_Desire() );

        if ( allow_shrink && (! force_shrink) )
            global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
                global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        {
            if ( UserGlobals_Get_Option(AUTO_DESIRED_ENLARGE) )
                Tilwin_Enlarge_Nearest( uwinp->winp, 
                    Tilwin_Get_Previous_Center( uwinp->winp ),
                    Tilwin_Get_Previous_Size( uwinp->winp ) );
            else
                Tilwin_Open_Nearest_In_Area( uwinp->winp,
                    Tilwin_Get_Previous_Rectangle( uwinp->winp ),
                    Tilwin_Get_Previous_Center( uwinp->winp ),
                    Tilwin_Get_Previous_Size( uwinp->winp ) );
        } ) )

        if ( force_repop )
        {
            Manage_Repopulate_Since( repop_since,
                FALSE, FALSE, TRUE );
        }
    }

    uwinp->rezoom_rect = Tilwin_Get_Previous_Rectangle( uwinp->winp );
}

/* ------------------------------------------------------------ */

static bool Manage_Followup_Unzoom_Open( uwinp )
    Userwin *uwinp;
{
    bool result;

    result = Manage_Neighborhood_Unzoom_Open( uwinp, 
                 Manage_Get_Unzoom_Open_Size( uwinp ) );
    if ( result )
        uwinp->rezoom_rect = Tilwin_Get_Previous_Rectangle( uwinp->winp );
    else
        Manage_Setup_Zoom( uwinp, FALSE );

    return result;
}
        
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static bool Manage_Do_Zoom( uwinp, explicit )
    Userwin *uwinp;
    bool explicit;
{
    bool full;

    full =
        (
            ( Userwin_Get_Window_Option(uwinp,ZOOM_FULL_EXPLICIT) && 
              explicit )
        &&
            (
                Userwin_Get_Window_Option(uwinp,ZOOM_FULL_WIDTH)
            || 
                Userwin_Get_Window_Option(uwinp,ZOOM_FULL_HEIGHT)
            )
        );

    Manage_Setup_Zoom( uwinp, full );
    return Manage_Followup_Zoom( uwinp );
}

/* ------------------------------------------------------------ */

static void Manage_Do_Unzoom( uwinp, explicit )
    Userwin *uwinp;
    bool explicit;
{
    Manage_Setup_Unzoom( uwinp );
    Manage_Followup_Unzoom( uwinp, explicit );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static Userwin *unzoomed_listener;

/* ------------------------------------------------------------ */

static void Manage_Start_Trying()
{
    unzoomed_listener = UWIN_NULL;
}

/* ------------------------------------------------------------ */

bool Manage_Can_Try_Listener_Unzoom()
{
    if ( UserGlobals_Get_Option(UNZOOM_TIED_LSNR_IF_NECESSARY) &&
         ( listener != UWIN_NULL ) &&
         Userwin_Get_Window_Option(listener,LISTENER_TIED_TO_ZOOM) &&
         listener->zoomed )
    {
        Manage_Setup_Unzoom( listener );
        unzoomed_listener = listener;
        return TRUE;
    }
    else
        return FALSE;
}

/* ------------------------------------------------------------ */

static void Manage_Finish_Trying( result )
    bool result;
{
    if ( unzoomed_listener != UWIN_NULL )
    {
        if ( result )
            Manage_Followup_Unzoom( unzoomed_listener, FALSE );
        else
            Manage_Setup_Zoom( unzoomed_listener, FALSE );
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

bool Manage_Unzoom_Open( uwinp )
    Userwin *uwinp;
{
    bool iconized;
    bool result;

    iconized = Tilwin_Is_Open( uwinp->iconp );
    if ( iconized )
        Tilwin_Close( uwinp->iconp );

    Manage_Setup_Unzoom( uwinp );
    result = Manage_Followup_Unzoom_Open( uwinp );
    if ( (! result) && iconized )
        Tilwin_Open( uwinp->iconp,
                     Tilwin_Get_Center( uwinp->iconp ),
                     Tilwin_Get_Size( uwinp->iconp ) );

    return result;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Zoom( uwinp )
    Userwin *uwinp;
{
    bool result;

    Manage_Start();
    Manage_Start_Trying();
    result = Manage_Do_Zoom( uwinp, TRUE );
    if ( (! result) && Manage_Can_Try_Listener_Unzoom() )
        result = Manage_Do_Zoom( uwinp, TRUE );
    Manage_Finish_Trying( result );
    Tilwin_Note_Desired_Width( uwinp->winp );
    Tilwin_Note_Desired_Height( uwinp->winp );
    last_zoom = uwinp;
    touch = uwinp;
    Manage_Finish_Minned( uwinp, result );
}

/* ------------------------------------------------------------ */

void Manage_Unzoom( uwinp )
    Userwin *uwinp;
{
    if ( ( uwinp == last_zoom ) &&
         ( uwinp->zoom_stamp == last_stamp ) )
        Manage_Undo_Start();
    else
    {
        Manage_Start();
        Manage_Do_Unzoom( uwinp, TRUE );
    }
    touch = uwinp;
    Manage_Finish( TRUE );
}

/* ------------------------------------------------------------ */

void Manage_Toggle_Zoom( uwinp )
    Userwin *uwinp;
{
    if ( uwinp->zoomed )
        Manage_Unzoom( uwinp );
    else
        Manage_Zoom( uwinp );
}
    
/* ------------------------------------------------------------ */

void Manage_Toggle_Zoom_Lock( uwinp )
    Userwin *uwinp;
{
    if ( Userwin_Tied_Listener(uwinp) )
    {
        Userwin_Dont_Tie_Listener( uwinp );
        Manage_Start();
        Tilwin_Act_Modified( uwinp->winp );
        touch = uwinp;
        Manage_Finish( TRUE );
    }
    else
    {   
        Userwin_Allow_Tie_Listener( uwinp );
        if ( ( uwinp == listener ) && (! uwinp->zoomed) )
            Manage_Zoom( uwinp );
        else if ( ( uwinp != listener ) && ( uwinp->zoomed ) )
            Manage_Unzoom( uwinp );
        else
        {
            Manage_Start();
            Tilwin_Act_Modified( uwinp->winp );
            touch = uwinp;
            Manage_Finish( TRUE );
        }
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Switch_Listener( uwinp )
    Userwin *uwinp;
{
    Userwin *old_listener;
    bool unzoom_old;
    bool zoom_new;
    bool listener_zooming;
    bool transact;
    TimeStamp zoom_stamp = (TimeStamp)0;

    switch_listener = uwinp;

    unzoom_old = (listener != UWIN_NULL) && (listener->zoomed) &&
                 Userwin_Get_Window_Option(listener,LISTENER_TIED_TO_ZOOM);

    zoom_new = (uwinp != UWIN_NULL) && (!uwinp->zoomed) &&
               Userwin_Get_Window_Option(uwinp,LISTENER_TIED_TO_ZOOM);

    listener_zooming = unzoom_old || zoom_new;

    transact = listener_zooming ||
               ( UserGlobals_Get_Option(AUTO_PRORATE) &&
                 UserGlobals_Get_Option(BIASED_AUTO_PRORATE) );

    old_listener = listener;

    if ( unzoom_old )
        zoom_stamp = listener->zoom_stamp;

    if ( unzoom_old &&
         UserGlobals_Get_Option(AUTO_REPOPULATE_ON_AUTO_UNZOOM) &&
         ( listener == last_zoom ) &&
         ( zoom_stamp == last_stamp ) )
    {
        Manage_Undo_Start();
        unzoom_old = FALSE;
        if ( zoom_new )
            last_zoom = UWIN_NULL;
    }
    else if ( listener_zooming )
    {
        Manage_Start();
        if (! unzoom_old)
            last_zoom = uwinp;
    }
    else if ( transact )
        Manage_Start();

    if ( listener != UWIN_NULL )
    {
        Manage_Unset_Listener();
        if ( unzoom_old )
            Manage_Setup_Unzoom( old_listener );
        else if (! transact)
            Drawwin_Display_Wrapping( old_listener );
    }

    Manage_Set_Listener(uwinp);

    if ( listener != UWIN_NULL )
    {
        if ( zoom_new )
        {
            if ( Manage_Do_Zoom( listener, FALSE ) && 
                 ( zoom_stamp != (TimeStamp)0 ) )
                listener->zoom_stamp = zoom_stamp;
        }
        else if (! transact)
            Drawwin_Display_Wrapping( listener );
    }

    if ( unzoom_old )
    {
        if ( listener == UWIN_NULL )
            Manage_Followup_Unzoom( old_listener, FALSE );
        else
            min_excursion( listener->winp,
                Manage_Followup_Unzoom( old_listener, FALSE ) )
    }

    if ( transact )
        Manage_Finish_Minned( listener, TRUE );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static bool Manage_Resatisfy( uwinp )
    Userwin *uwinp;
{
    bool result;
    Size siz;

    Manage_Save_State( uwinp );
    result = Tilwin_Is_Satisfied( uwinp->winp );
    if (! result )
    {
        siz = Tilwin_Get_Size( uwinp->winp );
        Set_Max_Size( siz, siz, Tilwin_Get_Min( uwinp->winp ) )
        Set_Min_Size( siz, siz, Tilwin_Get_Max( uwinp->winp ) )
        if ( Tilwin_Is_Open(uwinp->winp) )
            result = Manage_Neighborhood_Rezoom( uwinp, siz );
        else
            result = Manage_Rezoom( uwinp, siz );
    }
    return result;
}

/* ------------------------------------------------------------ */

void Manage_Client_Reset_Min_Max( uwinp, min_size, max_size )
    Userwin *uwinp;
    Size min_size;
    Size max_size;
{
    Size siz;
    bool has_min, has_max, result;

    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    has_max = ( max_size.width > 0 ) && ( max_size.height > 0 );
    has_min = ( min_size.width >= 0 ) && ( min_size.height >= 0 );

    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MAX_WIDTH ) )
        max_size.width = uwinp->body_max.width;
    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MAX_HEIGHT ) )
        max_size.height = uwinp->body_max.height;

    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MIN_WIDTH ) )
        min_size.width = uwinp->body_min.width;
    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MIN_HEIGHT ) )
        min_size.height = uwinp->body_min.height;

    if ( has_min )
        Set_Max_Size( max_size, max_size, min_size )
    
    if ( has_max )
    {
        uwinp->body_max = max_size;
        uwinp->client_max = Region_Adjust_Size( uwinp, max_size );
        if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MAXIMUMS ) )
        {    
            Set_Min_Size( siz, Tilwin_Get_Max( uwinp->winp ), 
                          uwinp->client_max )
            Tilwin_Set_Max( uwinp->winp, siz );
            Set_Min_Size( siz, siz, Tilwin_Get_Desired( uwinp->winp ) )
            Tilwin_Set_Desired( uwinp->winp, siz );
        }
    }
    
    if ( has_min )
    {
        uwinp->body_min = min_size;
        uwinp->client_min = Region_Adjust_Size( uwinp, min_size );
        if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MINIMUMS ) )
        {    
            Set_Max_Size( siz, Tilwin_Get_Min( uwinp->winp ), 
                          uwinp->client_min )
            Tilwin_Set_Min( uwinp->winp, siz );
            Set_Max_Size( siz, siz, Tilwin_Get_Desired( uwinp->winp ) )
            Tilwin_Set_Desired( uwinp->winp, siz );
        }
    }

    if ( Same_Size( Tilwin_Get_Min(uwinp->winp),
                    Tilwin_Get_Max(uwinp->winp) ) )
        uwinp->sized = TRUE;                    

    if (! uwinp->ever_opened)
        return;

    if (! Tilwin_Is_Open( uwinp->winp ))
        Manage_Resatisfy( uwinp );
    else if ( Userwin_Get_Window_Option( uwinp, AUTO_RESATISFY_ON_RESET_MINMAX ) )
    {
        Manage_Start();
        Manage_Client( 
        {
            result = Manage_Resatisfy( uwinp );
        } )
        Manage_Finish_Minned( uwinp, result );
        Manage_Cant_Undo();
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static Size Manage_Calc_Size( siz, rect, side, pos )
    Size siz;
    TWRectangle rect;
    Side side;
    TWPoint pos;
{
    
    switch (side)
    {
        case Top:
        case Top_Left:
        case Top_Right:
            siz.height = 1 + rect.bottom_y - pos.y;
            break;
        case Bottom:
        case Bottom_Left:
        case Bottom_Right:
            siz.height = 1 + pos.y - rect.top_y;
            break;
        default:
            break;
    }
    
    switch (side)
    {
        case Left:
        case Top_Left:
        case Bottom_Left:
            siz.width = 1 + rect.right_x - pos.x;
            break;
        case Right:
        case Top_Right:
        case Bottom_Right:
            siz.width = 1 + pos.x - rect.left_x;
            break;
        default:
            break;
    }

    return siz;
}

/* ------------------------------------------------------------ */

bool Manage_Set_Regular_Min_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = Tilwin_Get_Rectangle( uwinp->winp );

    Manage_Start();

    if (! uwinp->zoomed)
        uwinp->regular_min = Tilwin_Get_Min( uwinp->winp );
    uwinp->regular_min = 
        Manage_Calc_Size( uwinp->regular_min, rect, side, pos );

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MAXIMUMS ) )
        Set_Min_Size( uwinp->regular_min, uwinp->regular_min,
                      uwinp->client_max )

    Set_Min_Size( uwinp->regular_min, uwinp->regular_min,
                  Tilwin_Get_Max( uwinp->winp ) )

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MINIMUMS ) )
        Set_Max_Size( uwinp->regular_min, uwinp->regular_min,
                      uwinp->client_min )

    max_size = Tilwin_Get_Max( uwinp->winp );
    if ( UserGlobals_Get_Option(RESET_MAX_ON_INCREASE) || force )
        Set_Max_Size( max_size, max_size, uwinp->regular_min )
    else
        Set_Min_Size( uwinp->regular_min, uwinp->regular_min, max_size )
    Tilwin_Set_Max( uwinp->winp, max_size );

    if (! uwinp->zoomed)
    {
        Set_Max_Size( uwinp->regular_size, uwinp->regular_min,
                      Tilwin_Get_Desired( uwinp->winp ) )
        Tilwin_Set_Min( uwinp->winp, uwinp->regular_min );
        Tilwin_Set_Desired( uwinp->winp, uwinp->regular_size );
    }
    else
    {
        Set_Max_Size( uwinp->regular_size, uwinp->regular_size,
                      uwinp->regular_min )
        Set_Max_Size( uwinp->zoom_min, uwinp->regular_min,
                      Tilwin_Get_Min( uwinp->winp ) )
        Set_Max_Size( uwinp->zoom_size, uwinp->zoom_min,
                      Tilwin_Get_Desired( uwinp->winp ) )
        Tilwin_Set_Min( uwinp->winp, uwinp->zoom_min );
        Tilwin_Set_Desired( uwinp->winp, uwinp->zoom_size );
    }

    Manage_Resatisfy( uwinp );

    Manage_Finish( TRUE );
    return TRUE;
}    

/* ------------------------------------------------------------ */

bool Manage_Set_Zoom_Min_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = Tilwin_Get_Rectangle( uwinp->winp );

    Manage_Start();

    if ( uwinp->zoomed )
        uwinp->zoom_min = Tilwin_Get_Min( uwinp->winp );
    uwinp->zoom_min = 
        Manage_Calc_Size( uwinp->zoom_min, rect, side, pos );

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MAXIMUMS ) )
        Set_Min_Size( uwinp->zoom_min, uwinp->zoom_min,
                      uwinp->client_max )

    Set_Min_Size( uwinp->regular_min, uwinp->regular_min,
                  Tilwin_Get_Max( uwinp->winp ) )

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MINIMUMS ) )
        Set_Max_Size( uwinp->zoom_min, uwinp->zoom_min,
                      uwinp->client_min )

    max_size = Tilwin_Get_Max( uwinp->winp );
    if ( UserGlobals_Get_Option(RESET_MAX_ON_INCREASE) || force )
        Set_Max_Size( max_size, max_size, uwinp->zoom_min )
    else
        Set_Min_Size( uwinp->zoom_min, uwinp->zoom_min, max_size )
    Tilwin_Set_Max( uwinp->winp, max_size );

    if ( uwinp->zoomed )
    {
        Set_Max_Size( uwinp->zoom_size, uwinp->zoom_min,
                      Tilwin_Get_Desired( uwinp->winp ) )
        Tilwin_Set_Min( uwinp->winp, uwinp->zoom_min );
        Tilwin_Set_Desired( uwinp->winp, uwinp->zoom_size );
    }
    else
    {
        Set_Max_Size( uwinp->zoom_size, uwinp->zoom_size,
                      uwinp->zoom_min )
        Set_Min_Size( uwinp->regular_min, uwinp->zoom_min,
                      Tilwin_Get_Min( uwinp->winp ) )
        Tilwin_Set_Min( uwinp->winp, uwinp->regular_min );
    }

    Manage_Resatisfy( uwinp );

    Manage_Finish( TRUE );
    return TRUE;
}    

/* ------------------------------------------------------------ */

bool Manage_Set_Regular_Desired_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = Tilwin_Get_Rectangle( uwinp->winp );

    Manage_Start();

    if (! uwinp->zoomed )
    {
        uwinp->regular_size = Tilwin_Get_Desired( uwinp->winp );
        uwinp->regular_min = Tilwin_Get_Min( uwinp->winp );
    }
    else
        uwinp->zoom_min = Tilwin_Get_Min( uwinp->winp );

    uwinp->regular_size = 
        Manage_Calc_Size( uwinp->regular_size, rect, side, pos );

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MAXIMUMS ) )
        Set_Min_Size( uwinp->regular_size, uwinp->regular_size,
                      uwinp->client_max )

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MINIMUMS ) )
        Set_Max_Size( uwinp->regular_size, uwinp->regular_size,
                      uwinp->client_min )

    max_size = Tilwin_Get_Max( uwinp->winp );
    if ( UserGlobals_Get_Option(RESET_MAX_ON_INCREASE) || force )
        Set_Max_Size( max_size, max_size, uwinp->regular_size )
    else
        Set_Min_Size( uwinp->regular_size, uwinp->regular_size, max_size )
    Tilwin_Set_Max( uwinp->winp, max_size );

    if ( UserGlobals_Get_Option(RESET_MIN_ON_DECREASE) || force )
        Set_Min_Size( uwinp->regular_min, uwinp->regular_min,
                      uwinp->regular_size )
    else
        Set_Max_Size( uwinp->regular_size, uwinp->regular_size,
                      uwinp->regular_min )

    if (! uwinp->zoomed)
    {
        Tilwin_Set_Min( uwinp->winp, uwinp->regular_min );
        Tilwin_Set_Desired( uwinp->winp, uwinp->regular_size );
    }
    else
    {
        Set_Max_Size( uwinp->zoom_size, uwinp->regular_size,
                      Tilwin_Get_Size( uwinp->winp ) )
        Tilwin_Set_Desired( uwinp->winp, uwinp->zoom_size );
    }

    Manage_Finish( TRUE );
    return TRUE;
}    

/* ------------------------------------------------------------ */

bool Manage_Set_Zoom_Desired_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = Tilwin_Get_Rectangle( uwinp->winp );

    Manage_Start();

    if ( uwinp->zoomed )
    {
        uwinp->zoom_size = Tilwin_Get_Desired( uwinp->winp );
        uwinp->zoom_min = Tilwin_Get_Min( uwinp->winp );
    }
    else
        uwinp->regular_min = Tilwin_Get_Min( uwinp->winp );

    uwinp->zoom_size = 
        Manage_Calc_Size( uwinp->zoom_size, rect, side, pos );

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MAXIMUMS ) )
        Set_Min_Size( uwinp->zoom_size, uwinp->zoom_size,
                      uwinp->client_max )

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MINIMUMS ) )
        Set_Max_Size( uwinp->zoom_size, uwinp->zoom_size,
                      uwinp->client_min )

    max_size = Tilwin_Get_Max( uwinp->winp );
    if ( UserGlobals_Get_Option(RESET_MAX_ON_INCREASE) || force )
        Set_Max_Size( max_size, max_size, uwinp->zoom_size )
    else
        Set_Min_Size( uwinp->zoom_size, uwinp->zoom_size, max_size )
    Tilwin_Set_Max( uwinp->winp, max_size );

    if ( UserGlobals_Get_Option(RESET_MIN_ON_DECREASE) || force )
        Set_Min_Size( uwinp->zoom_min, uwinp->zoom_min,
                      uwinp->zoom_size )
    else
        Set_Max_Size( uwinp->zoom_size, uwinp->zoom_size,
                      uwinp->zoom_min )

    if (uwinp->zoomed)
    {
        Tilwin_Set_Min( uwinp->winp, uwinp->zoom_min );
        Tilwin_Set_Desired( uwinp->winp, uwinp->zoom_size );
    }
    else
    {
        if ( UserGlobals_Get_Option(RESET_MIN_ON_DECREASE) || force )
        {
            Set_Min_Size( uwinp->regular_min, uwinp->regular_min,
                          uwinp->zoom_size )
            Tilwin_Set_Min( uwinp->winp, uwinp->regular_min );
        }
        else
        {
            Set_Max_Size( uwinp->zoom_size, uwinp->zoom_size,
                          uwinp->regular_min )
        }
        Set_Min_Size( uwinp->regular_size, uwinp->zoom_size,
                      Tilwin_Get_Size( uwinp->winp ) )
        Tilwin_Set_Desired( uwinp->winp, uwinp->regular_size );
    }

    Manage_Finish( TRUE );
    return TRUE;
}

/* ------------------------------------------------------------ */

bool Manage_Set_Max_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = Tilwin_Get_Rectangle( uwinp->winp );

    Manage_Start();

    max_size = Manage_Calc_Size(
        Tilwin_Get_Max( uwinp->winp), rect, side, pos );

    if (uwinp->zoomed)
        uwinp->zoom_min = Tilwin_Get_Min( uwinp->winp );
    else
        uwinp->regular_min = Tilwin_Get_Min( uwinp->winp );

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MAXIMUMS ) )
        Set_Min_Size( max_size, max_size, uwinp->client_max )

    if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MINIMUMS ) )
        Set_Max_Size( max_size, max_size, uwinp->client_min )

    if ( UserGlobals_Get_Option(RESET_MIN_ON_DECREASE) || force )
    {
        Set_Min_Size( uwinp->regular_min, uwinp->regular_min,
                      max_size )
        Set_Min_Size( uwinp->zoom_min, uwinp->zoom_min,
                      max_size )
    }
    else
    {
        Set_Max_Size( max_size, max_size, uwinp->regular_min )
        Set_Max_Size( max_size, max_size, uwinp->zoom_min )
    }
    Tilwin_Set_Max( uwinp->winp, max_size );

    if ( uwinp->zoomed )
    {
        Set_Min_Size( uwinp->zoom_size, max_size,
                      Tilwin_Get_Desired( uwinp->winp ) )
        Tilwin_Set_Desired( uwinp->winp, uwinp->zoom_size );
        Set_Min_Size( uwinp->regular_size, uwinp->regular_size, max_size )
        Tilwin_Set_Min( uwinp->winp, uwinp->zoom_min );
    }
    else
    {
        Set_Min_Size( uwinp->regular_size, max_size,
                      Tilwin_Get_Desired( uwinp->winp ) )
        Tilwin_Set_Desired( uwinp->winp, uwinp->regular_size );
        Set_Min_Size( uwinp->zoom_size, uwinp->zoom_size, max_size )
        Tilwin_Set_Min( uwinp->winp, uwinp->regular_min );
    }

    Manage_Resatisfy( uwinp );

    Manage_Finish( TRUE );
    return TRUE;
}    

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Min_Max_Resizing( uwinp, siz1, siz2 )
    Userwin *uwinp;
    Size siz1, siz2;
{
    Size siz;

    Set_Min_Size( siz, siz1, siz2 )
    Tilwin_Set_Min( uwinp->winp, siz );    
    Set_Max_Size( siz, siz1, siz2 )
    Tilwin_Set_Max( uwinp->winp, siz );
}

/* ------------------------------------------------------------ */

void Manage_Cancel_Resizing( uwinp )
    Userwin *uwinp;
{
    Tilwin_Set_Min( uwinp->winp, uwinp->prev_min );
    Tilwin_Set_Max( uwinp->winp, uwinp->prev_max );
}

/* ------------------------------------------------------------ */

void Manage_Finish_Resizing( uwinp, side, force, undesire )
    Userwin *uwinp;
    Side side;
    bool force, undesire;
{
    Size newmin, newmax;
    Size siz, prevsiz, desired;
    bool horiz, vert, enlarge;
    
    horiz = ( side != NoSide ) && ( side != Top ) && ( side != Bottom );
    vert = ( side != NoSide ) && ( side != Left ) && ( side != Right );

    newmin = uwinp->prev_min;
    newmax = uwinp->prev_max;

    if ( uwinp->sized )
        prevsiz = Tilwin_Get_Previous_Size( uwinp->winp );
    else
    {
        prevsiz = newmin;
        if ( UserGlobals_Get_Option(RESET_MIN_MAX_ON_UNSZD_MAN_OPEN) )
        {
            force = TRUE;
            horiz = TRUE;
            vert = TRUE;
        }
    }

    siz = Tilwin_Get_Size( uwinp->winp );

    if (! undesire)
    {
        desired = Tilwin_Get_Desired( uwinp->winp );
    
        enlarge = (desired.width > prevsiz.width) ||
                  (desired.height > prevsiz.height);

        if ( horiz )
        {
            if ( desired.width >= prevsiz.width )
            {
                if ( force || UserGlobals_Get_Option(RESET_MIN_ON_ENLARGE) || 
                     ( UserGlobals_Get_Option(RESET_TIED_ZOOMED_MIN_ON_ENLARGE) &&
                       (uwinp->zoomed) &&
                       Userwin_Get_Window_Option(uwinp,LISTENER_TIED_TO_ZOOM) ) )
                    newmin.width = siz.width;
            }
            else
            {
                if ( (! enlarge) &&
                     ( force || UserGlobals_Get_Option(RESET_MAX_ON_SHRINK) ) )
                    newmax.width = siz.width;
            }
        }
    
        if ( vert )
        {
            if ( desired.height >= prevsiz.height )
            {
                if ( force || UserGlobals_Get_Option(RESET_MIN_ON_ENLARGE) || 
                     ( UserGlobals_Get_Option(
                           RESET_TIED_ZOOMED_MIN_ON_ENLARGE) &&
                       (uwinp->zoomed) &&
                       Userwin_Get_Window_Option(uwinp,LISTENER_TIED_TO_ZOOM) ) )
                    newmin.height = siz.height;
            }
            else
            {
                if ( (! enlarge) &&
                     ( force || UserGlobals_Get_Option(RESET_MAX_ON_SHRINK) ) )
                    newmax.height = siz.height;
            }
        }
    }
    
    if ( UserGlobals_Get_Option(RESET_MIN_ON_DECREASE) || force )
        Set_Min_Size( newmin, newmin, siz )
    
    if ( UserGlobals_Get_Option(RESET_MAX_ON_INCREASE) || force )
        Set_Max_Size( newmax, newmax, siz )

    Tilwin_Set_Min( uwinp->winp, newmin );
    Tilwin_Set_Max( uwinp->winp, newmax );

    Set_Min_Size( siz, newmax, Tilwin_Get_Desired(uwinp->winp) )
    Set_Max_Size( siz, newmin, siz )
    Tilwin_Set_Desired( uwinp->winp, siz );

}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static bool Manage_Slide_Resize( uwinp, center, siz, side )
    Userwin *uwinp;
    TWPoint center;
    Size siz;
    Side side;
{
    bool result;
    Size shrinksiz;
    Side shrinkside = NoSide;
    
    if (! UserGlobals_Get_Option(TRY_SLIDING_ON_RESIZE))
        return Tilwin_Resize( uwinp->winp, siz, side );

    global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE,
        (! UserGlobals_Get_Option(
            PREF_SLD_TO_AUTO_CL_ON_RESIZE)),
    { global_restrict_excursion( ALLOW_AUTOMATIC_SHRINK,
        (! UserGlobals_Get_Option(
            PREF_SLD_TO_AUTO_SHR_ON_RESIZE)),
    { window_join_excursion( uwinp->winp, FIXED_SIZE,
        UserGlobals_Get_Option(PREF_SLD_TO_SHRINK_ON_RESIZE),
    { 
        result = Tilwin_Resize( uwinp->winp, siz, side );
    } ) } ) } );

    if ( result ) return TRUE;

    shrinksiz = Tilwin_Get_Size( uwinp->winp );

    switch (side)
    {
        case Top:
        case Top_Left:
        case Top_Right:
            if ( siz.height < shrinksiz.height )
            {
                shrinkside = Top;
                shrinksiz.height = siz.height;
            }
            break;
        case Bottom:
        case Bottom_Left:
        case Bottom_Right:
            if ( siz.height < shrinksiz.height )
            {
                shrinkside = Bottom;
                shrinksiz.height = siz.height;
            }
            break;
        default:
            break;
    }
    
    switch (side)
    {
        case Left:
        case Top_Left:
        case Bottom_Left:
            if ( siz.width < shrinksiz.width )
            {
                shrinkside = Left;
                shrinksiz.width = siz.width;
            }
            break;
        case Right:
        case Top_Right:
        case Bottom_Right:
            if ( siz.width < shrinksiz.width )
            {
                shrinkside = Right;
                shrinksiz.width = siz.width;
            }
            break;
        default:
            break;
    }

    if ( shrinkside != NoSide )
        Tilwin_Resize( uwinp->winp, shrinksiz, shrinkside );

    return Tilwin_Enlarge_Nearest( uwinp->winp, center, siz );
}

/* ------------------------------------------------------------ */

static bool Manage_Cntr_Neighborhood_Rsz( uwinp, center, siz, side )
    Userwin *uwinp;
    TWPoint center;
    Size siz;
    Side side;
{
    bool result;
    TWRectangle rect;

    if (! UserGlobals_Get_Option(TRY_CTR_NBRHD_ON_RESIZE))
        return Manage_Slide_Resize( uwinp, center, siz, side );
    
    global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE,
        (! UserGlobals_Get_Option(
            PF_CTR_NBR_2_AUTO_CL_ON_RESIZE) ),
    { global_restrict_excursion( ALLOW_AUTOMATIC_SHRINK,
        (! UserGlobals_Get_Option(
            PF_CTR_NBR_2_AUTO_SHR_ON_RESIZE) ),
    { window_join_excursion( uwinp->winp, FIXED_SIZE,
        UserGlobals_Get_Option(
            PF_CTR_NBR_2_SHRINK_ON_RESIZE),
    { 
        result = Manage_Slide_Resize( uwinp, center, siz, side );
    } ) } ) } );

    if ( result ) return TRUE;

    rect = Manage_Neighborhood_Rectangle( 0.5, center, siz );

    return Tilwin_Open_Nearest_In_Area( uwinp->winp, rect, center, siz );
}

/* ------------------------------------------------------------ */

static bool Manage_Edge_Neighborhood_Resize( uwinp, center, siz, side )
    Userwin *uwinp;
    TWPoint center;
    Size siz;
    Side side;
{
    bool result;
    TWRectangle rect;

    if (! UserGlobals_Get_Option(TRY_EDGE_NEIGHBORHOOD_ON_RESIZE))
        return Manage_Cntr_Neighborhood_Rsz( uwinp, center, siz, side );    

    global_restrict_excursion( ALLOW_AUTOMATIC_CLOSE,
        (! UserGlobals_Get_Option(
            PF_EDGE_NBR_2_AUTO_CL_ON_RESIZE) ),
    { global_restrict_excursion( ALLOW_AUTOMATIC_SHRINK,
        (! UserGlobals_Get_Option(
            PF_EDGE_NBR_2_AUTO_SHR_ON_RESIZE) ),
    { window_join_excursion( uwinp->winp, FIXED_SIZE,
        UserGlobals_Get_Option(PF_EDGE_NBR_2_SHRINK_ON_RESIZE),
    { 
        result = Manage_Cntr_Neighborhood_Rsz( uwinp, center, siz, side );
    } ) } ) } );

    if ( result ) return TRUE;

    rect = Manage_Neighborhood_Rectangle( 1.0, center, siz );

    return Tilwin_Open_Nearest_In_Area( uwinp->winp, rect, center, siz );
}

/* ------------------------------------------------------------ */

bool Manage_Resize( uwinp, pos, side, force, undesire )
    Userwin *uwinp;
    Side side;
    TWPoint pos;
    bool force, undesire;
{
    Size siz, desired;
    TWPoint center;
    TWRectangle rect;
    bool result;

    siz = Tilwin_Get_Size( uwinp->winp );
    rect = Tilwin_Get_Rectangle( uwinp->winp );
    siz = Manage_Calc_Size( siz, rect, side, pos );

    if (! ( UserGlobals_Get_Option(RESET_MIN_ON_DECREASE) || force ))
        Set_Max_Size( siz, siz, uwinp->prev_min )
    if (! ( UserGlobals_Get_Option(RESET_MAX_ON_INCREASE) || force ))
        Set_Min_Size( siz, siz, uwinp->prev_max )
    
    desired = Tilwin_Get_Desired( uwinp->winp );

    switch (side)
    {
        case Top:
        case Top_Left:
        case Top_Right:
            rect.top_y = rect.bottom_y - siz.height + 1;
            desired.height = siz.height;
            break;
        case Bottom:
        case Bottom_Left:
        case Bottom_Right:
            rect.bottom_y = rect.top_y + siz.height - 1;
            desired.height = siz.height;
            break;
        default:
            break;
    }
    
    switch (side)
    {
        case Left:
        case Top_Left:
        case Bottom_Left:
            rect.left_x = rect.right_x - siz.width + 1;
            desired.width = siz.width;
            break;
        case Right:
        case Top_Right:
        case Bottom_Right:
            rect.right_x = rect.left_x + siz.width - 1;
            desired.width = siz.width;
            break;
        default:
            break;
    }

    COMPUTE_CENTER( rect, center );

    switch (side)
    {
        case Top:
        case Bottom:
            center.x = Tilwin_Get_Position(uwinp->winp).x;
            break;
        case Left:
        case Right:
            center.y = Tilwin_Get_Position(uwinp->winp).y;
            break;
        default:
            break;
    }

    Manage_Start();
    Manage_Save_State( uwinp );

    if (! undesire)
    {
        Tilwin_Set_Desired( uwinp->winp, desired );
        if ( ( side != Top ) && ( side != Bottom ) )
            Tilwin_Note_Desired_Width( uwinp->winp );
        if ( ( side != Left ) && ( side != Right ) )
            Tilwin_Note_Desired_Height( uwinp->winp );
        Tilwin_Set_Position( uwinp->winp, center );
        uwinp->positioned = TRUE;
    }

    Manage_Min_Max_Resizing( uwinp, siz, Tilwin_Get_Size( uwinp->winp ) );

    Manage_Start_Trying();
    global_excursion( PREFER_CLOSE_TO_SHRINK,
        UserGlobals_Get_Option(PREFER_CL_TO_SHR_ON_RESIZE),
    { window_join_excursion( uwinp->winp, FIXED_SIZE,
        ! UserGlobals_Get_Option(ALLOW_SHRINK_ON_RESIZE),
    {
        result = Same_Size( Tilwin_Get_Size( uwinp->winp ), siz ) ||
                 (  Manage_Edge_Neighborhood_Resize( uwinp, center, siz, side )
                 && Tilwin_Was_Just_Modified( uwinp->winp ) );
        if ( (! result) &&
             ( listener != uwinp ) &&
             Manage_Can_Try_Listener_Unzoom() )
            result = Manage_Edge_Neighborhood_Resize( uwinp, center, siz, side )
                 && Tilwin_Was_Just_Modified( uwinp->winp );

    } ) } )
    Manage_Finish_Trying( result );

    if ( result )
        Manage_Finish_Resizing( uwinp, side, force, undesire );
    else
        Manage_Cancel_Resizing( uwinp );

    height_excursion( uwinp->winp,
       width_excursion( uwinp->winp,
           window_excursion( uwinp->winp, REQUIRE_MANUAL_CLOSE, TRUE,
			    Manage_Finish( result ) ) ) );
    

    return result;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static bool zoom_forced;

/* ------------------------------------------------------------ */

void Manage_Start_Open( uwinp, force_zoom )
    Userwin *uwinp;
    bool force_zoom;
{
    Manage_Start();
    Manage_Start_Trying();
    Manage_Save_State( uwinp );

    zoom_forced = FALSE;
    if (! Tilwin_Is_Open( uwinp->winp ))
    {
        if ( Tilwin_Is_Open( uwinp->iconp ) )
            Tilwin_Close( uwinp->iconp );
        if ( Userwin_Get_Window_Option( uwinp, ZOOM_ON_OPEN ) ||
             ( (! uwinp->ever_opened ) &&
               UserGlobals_Get_Option(ZOOM_ON_CREATE) ) )
            force_zoom = TRUE;
        if ( force_zoom && (! uwinp->zoomed) )
        {
            zoom_forced = TRUE;
            Manage_Do_Zoom( uwinp, FALSE );
        }
    }
}

/* ------------------------------------------------------------ */

bool Manage_Can_Try_Self_Unzoom( uwinp )
    Userwin *uwinp;
{
    bool result;
    result = UserGlobals_Get_Option(PREFER_UNZOOM_TO_CLOSE)
             && (uwinp->zoomed)
             && (! Tilwin_Is_Open( uwinp->winp ) );
    if ( result )
    {
        zoom_forced = FALSE;
        Manage_Do_Unzoom( uwinp, FALSE );
    }
    return result;
}

/* ------------------------------------------------------------ */

bool Manage_Finish_Unsized_Open( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result )
    {	
        uwinp->open_stamp = Tilwin_Get_Timestamp();
        uwinp->ever_opened = TRUE;
    }
    else if ( zoom_forced )
        Manage_Do_Unzoom( uwinp, FALSE );
    Manage_Finish_Trying( result );
    return Manage_Finish_Locked( uwinp, result );
}

/* ------------------------------------------------------------ */

bool Manage_Finish_Sized_Open( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result )
    {
        uwinp->open_stamp = Tilwin_Get_Timestamp();
        uwinp->ever_opened = TRUE;
    }
    else if ( zoom_forced )
        Manage_Do_Unzoom( uwinp, FALSE );
    Manage_Finish_Trying( result );
    return Manage_Finish_Minned( uwinp, result );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

bool Manage_Move( uwinp, pos )
    Userwin *uwinp;
    TWPoint pos;
{
    bool result;

    Manage_Start();
    Tilwin_Set_Position( uwinp->winp, pos );
    uwinp->positioned = TRUE;
    if ( (! uwinp->ever_opened ) ||
         UserGlobals_Get_Option(TREAT_MOVE_LIKE_RELOCATE) )
    {
        uwinp->ever_opened = TRUE;
        return Manage_Finish_Minned( uwinp,
            Manage_Center_Open( uwinp, pos ) );
    }
    else
    {
        Manage_Start_Trying();
        result = Tilwin_Open( uwinp->winp, pos, 
                    Tilwin_Get_Size( uwinp->winp ) );
        if ( (! result) && ( listener != uwinp )
             && Manage_Can_Try_Listener_Unzoom() )
            result = Tilwin_Open( uwinp->winp, pos, 
                    Tilwin_Get_Size( uwinp->winp ) );
        Manage_Finish_Trying( result );
        return Manage_Finish_Fixed_Completely( uwinp, result );
    }
}

/* ------------------------------------------------------------ */

bool Manage_Icon_Move( uwinp, pos )
    Userwin *uwinp;
    TWPoint pos;
{
    bool result;

    Manage_Start();
    Tilwin_Set_Position( uwinp->iconp, pos );
    if ( UserGlobals_Get_Option(TREAT_MOVE_LIKE_RELOCATE) )
        result = Manage_Neighborhood_Icon_Open( uwinp, pos );
    else
    {
        Manage_Start_Trying();
        result = Tilwin_Open( uwinp->iconp, pos, 
                    Tilwin_Get_Size( uwinp->iconp ) );
        if ( (! result) && Manage_Can_Try_Listener_Unzoom() )
            result = Tilwin_Open( uwinp->iconp, pos, 
                    Tilwin_Get_Size( uwinp->iconp ) );
        Manage_Finish_Trying( result );
    }
    if ( result )
        window_excursion( uwinp->iconp, FIXED_COMPLETELY, TRUE,
            Manage_Finish( result ) )
    else
        Manage_Finish( FALSE );
    return result;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

#define Configure_Has_X(flags)  \
    ( ( (flags) & (1L << 0) ) != 0 )
#define Configure_Has_Y(flags)  \
    ( ( (flags) & (1L << 1) ) != 0 )
#define Configure_Has_Width(flags)  \
    ( ( (flags) & (1L << 2) ) != 0 )
#define Configure_Has_Height(flags)  \
    ( ( (flags) & (1L << 3) ) != 0 )

#define Configure_Has_Position(flags) \
    ( Configure_Has_X(flags) || Configure_Has_Y(flags) )
#define Configure_Has_Size(flags) \
    ( Configure_Has_Width(flags) || Configure_Has_Height(flags) )

/* ------------------------------------------------------------ */

static void Manage_User_Open_Configure( uwinp, pos, siz,
        pos_act, siz_act )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
    bool pos_act, siz_act;
{
    bool result = TRUE;

    if ( pos_act && siz_act )
    {
        result = Manage_Center_Neighborhood_Open( uwinp, pos, siz );
    }

    else if ( pos_act )
    {
        result = Manage_Center_Neighborhood_Open( uwinp, pos,
            Tilwin_Get_Desired( uwinp->winp ) );
    }

    else if ( siz_act )
    {
        result = Manage_Center_Neighborhood_Open( uwinp,
            Tilwin_Get_Center( uwinp->winp ), siz );
    }

    if (! result)
        Draw_Flash();
}

/* ------------------------------------------------------------ */

void Manage_Client_Configure( uwinp, flags, top_left, bodsiz, detail )
    Userwin *uwinp;
    unsigned long flags;
    TWPoint top_left;
    Size bodsiz;
    int detail;
{
    TWPoint center;
    Size tempsiz, siz, desired;
    TWRectangle rect;
    
    Manage_Start();

    rect = Region_Body_Rectangle( uwinp );

    COMPUTE_SIZE( rect, tempsiz );

    if ( Configure_Has_Width(flags) )
        tempsiz.width = bodsiz.width;
    if ( Configure_Has_Height(flags) )
        tempsiz.height = bodsiz.height;

    if ( Configure_Has_X(flags) )
        rect.left_x = top_left.x;
    if ( Configure_Has_Y(flags) )
        rect.top_y = top_left.y;

    rect.right_x = rect.left_x + tempsiz.width - 1;
    rect.bottom_y = rect.top_y + tempsiz.height - 1;

    rect = Region_Adjust_Rectangle( uwinp, rect );

    COMPUTE_CENTER( rect, center );
    COMPUTE_SIZE( rect, siz );

    if ( Configure_Has_Size(flags) )
	uwinp->sized = TRUE;
    if ( Configure_Has_Position(flags) )
    {
	uwinp->positioned = TRUE;
        Tilwin_Set_Position( uwinp->winp, center );
    }

    if ( Userwin_Get_Window_Option( uwinp,
             ENFORCE_CLIENT_MINIMUMS ) )
        Set_Max_Size( siz, siz, uwinp->client_min );

    if ( Userwin_Get_Window_Option( uwinp,
             ENFORCE_CLIENT_MAXIMUMS ) )
        Set_Min_Size( siz, siz, uwinp->client_max );

    Set_Min_Size( tempsiz, 
        Tilwin_Get_Min( uwinp->winp ), siz );
    Tilwin_Set_Min( uwinp->winp, tempsiz );
    Set_Max_Size( tempsiz, 
        Tilwin_Get_Max( uwinp->winp ), siz );
    Tilwin_Set_Max( uwinp->winp, tempsiz );

    desired = Tilwin_Get_Desired( uwinp->winp );
    if ( Configure_Has_Width(flags) )
        desired.width = siz.width;
    if ( Configure_Has_Height(flags) )
        desired.height = siz.height;
    Tilwin_Set_Desired( uwinp->winp, desired );

    if (! Tilwin_Was_Actually_Modified( uwinp->winp ))
        Client_Configure_Denied( uwinp );

    if (! Tilwin_Is_Open( uwinp->winp ) )
    {
        Tilwin_Set( uwinp->winp, center, siz );
        Manage_Finish_Minned( uwinp, TRUE );
        Manage_Cant_Undo();
    }
    else
    {
        Manage_User_Open_Configure( uwinp, center, siz,
            Configure_Has_Position(flags),
            Configure_Has_Size(flags) );
        Manage_Finish_Minned( uwinp, TRUE );
    }
}

/* ------------------------------------------------------------ */

void Manage_Client_Set_Icon_Size( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    Tilwin_Set_Min( uwinp->iconp, siz );
    Tilwin_Set_Max( uwinp->iconp, siz );
    Tilwin_Set_Desired( uwinp->iconp, siz );

    if ( Tilwin_Is_Open( uwinp->iconp ) )
    {
        Manage_Client(
        {
            Manage_Start();
            Tilwin_Set_Size( uwinp->iconp, siz );
            Manage_Finish( TRUE );
        } )
        Manage_Cant_Undo();
    }
    else
        Tilwin_Set_Size( uwinp->iconp, siz );
}

/* ------------------------------------------------------------ */

void Manage_Client_Set_Icon_Position( uwinp, pt )
    Userwin *uwinp;
    TWPoint pt;
{
    uwinp->icon_positioned = TRUE;
    Tilwin_Set_Position( uwinp->iconp, pt );

    if ( Tilwin_Is_Open( uwinp->iconp ) )
    {
        Manage_Client(
        {
            Manage_Start();
            Manage_Icon_Open( uwinp );
            Manage_Finish( TRUE );
        } )
        Manage_Cant_Undo();
    }
    else
        Tilwin_Set( uwinp->iconp, pt, Tilwin_Get_Size( uwinp->iconp ) );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

#define Size_Hints_User_Position(flags)  \
    ( ( (flags) & (1L << 0) ) != 0 )
#define Size_Hints_User_Size(flags)  \
    ( ( (flags) & (1L << 1) ) != 0 )
#define Size_Hints_Client_Position(flags)  \
    ( ( (flags) & (1L << 2) ) != 0 )
#define Size_Hints_Client_Size(flags)  \
    ( ( (flags) & (1L << 3) ) != 0 )
#define Size_Hints_Position(flags)  \
    ( ( (flags) & ((1L << 2) | (1L << 0)) ) != 0 )
#define Size_Hints_Size(flags)  \
    ( ( (flags) & ((1L << 3) | (1L << 1)) ) != 0 )
#define Size_Hints_Min(flags)  \
    ( ( (flags) & (1L << 4) ) != 0 )
#define Size_Hints_Max(flags)  \
    ( ( (flags) & (1L << 5) ) != 0 )
#define Size_Hints_Base(flags)  \
    ( ( (flags) & (1L << 8) ) != 0 )

#define Manage_Use_Size(uwinp,flags)  \
    ( Size_Hints_Size(flags) &&  \
      (! Userwin_Get_Window_Option( uwinp, IGNORE_SIZE_HINTS ) ) &&  \
      ( uwinp->ever_opened ||  \
        (! Userwin_Get_Window_Option( uwinp, \
           IGNORE_INITIAL_SIZE_HINTS ) ) ) )

#define Manage_Use_Position(uwinp,flags)  \
    ( Size_Hints_Position(flags) &&  \
      (! Userwin_Get_Window_Option( uwinp, IGNORE_POSITION_HINTS ) ) &&  \
      ( uwinp->ever_opened ||  \
        (! Userwin_Get_Window_Option( uwinp,  \
           IGNORE_INITIAL_POSITION_HINTS ) ) ) )

/* ------------------------------------------------------------ */

static void Manage_Act_Hints_Open( uwinp, pos, siz, pos_act, siz_act )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
    bool pos_act, siz_act;
{
    bool result;

    if ( pos_act )
            result = Manage_Center_Neighborhood_Open(
                         uwinp, pos, siz );

    else if ( siz_act )
        result = Manage_Center_Neighborhood_Open(
                         uwinp, Tilwin_Get_Center( uwinp->winp ), siz );

    if (! result)
        Draw_Flash();
}

/* ------------------------------------------------------------ */

static void Manage_Act_Hints_Closed( uwinp, pos, siz, pos_act, siz_act )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
    bool pos_act, siz_act;
{
    if ( pos_act && siz_act )
        Tilwin_Set( uwinp->winp, pos, siz );

    else if ( pos_act )
        Tilwin_Set( uwinp->winp, pos, Tilwin_Get_Center( uwinp->winp ) );

    else if ( siz_act )
        Tilwin_Set( uwinp->winp, Tilwin_Get_Center( uwinp->winp ), siz );
}

/* ------------------------------------------------------------ */

void Manage_Client_Set_Geometry_Hints( uwinp, flags,
                                       top_left, size )
    Userwin *uwinp;
    long flags;
    TWPoint top_left;
    Size size;
{
    Size siz;
    TWRectangle rect;
    TWPoint pos;
    bool pos_act, siz_act;
    bool by_user;

    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    Manage_Start();
    Manage_Save_State( uwinp );

    if ( uwinp->zoomed )
    {
        uwinp->zoom_min = Tilwin_Get_Min(uwinp->winp);
        uwinp->zoom_size = Tilwin_Get_Desired(uwinp->winp);
    }
    else
    {
        uwinp->regular_min = Tilwin_Get_Min(uwinp->winp);
        uwinp->regular_size = Tilwin_Get_Desired(uwinp->winp);
    }

    by_user =
        ( Size_Hints_User_Position(flags) || 
          Size_Hints_User_Size(flags) );

    /* - - - - - - - - - - - - - - - - - - - - - - - - */

    if (! Manage_Use_Size( uwinp, flags) )
        size = Region_Unadjust_Size( uwinp, uwinp->regular_size );

    rect = Region_Body_Rectangle( uwinp );
    if ( Manage_Use_Position( uwinp, flags) )
    {
        uwinp->positioned = TRUE;
        rect.top_y = top_left.y;        
        rect.left_x = top_left.x;
    }
    rect.right_x = rect.left_x + size.width - 1;
    rect.bottom_y = rect.top_y + size.height - 1;

    rect = Region_Adjust_Rectangle( uwinp, rect );

    COMPUTE_CENTER( rect, pos );
    if ( Manage_Use_Position( uwinp, flags ) )
        Tilwin_Set_Position( uwinp->winp, pos );

    COMPUTE_SIZE( rect, size );
    if ( ! uwinp->ever_opened )
    {
        if ( Profile_Supplies_User_Value( uwinp, NORMAL_DESIRED_WIDTH ) )
            size.width = uwinp->regular_size.width;
        if ( Profile_Supplies_User_Value( uwinp, NORMAL_DESIRED_HEIGHT ) )
            size.height = uwinp->regular_size.height;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - */

    siz_act = Size_Hints_User_Size(flags);

    if ( Userwin_Get_Window_Option( uwinp,
             ENFORCE_CLIENT_MINIMUMS ) )
        Set_Max_Size( size, size, uwinp->client_min );

    if ( Userwin_Get_Window_Option( uwinp,
             ENFORCE_CLIENT_MAXIMUMS ) )
        Set_Min_Size( size, size, uwinp->client_max );

    if ( Size_Hints_User_Size(flags) )
    {
        if ( UserGlobals_Get_Option(RESET_MIN_ON_DECREASE) )
            Set_Min_Size( uwinp->regular_min, uwinp->regular_min, size )
        else
            Set_Max_Size( size, size, uwinp->regular_min );

        if ( UserGlobals_Get_Option(RESET_MAX_ON_INCREASE) )
        {
            Set_Max_Size( siz, Tilwin_Get_Max( uwinp->winp ), size );
            Tilwin_Set_Max( uwinp->winp, siz );
        }
        else
            Set_Min_Size( size, size, Tilwin_Get_Max( uwinp->winp ) );
    }
    else
    {
        Set_Min_Size( size, size, Tilwin_Get_Max( uwinp->winp ) );
        Set_Max_Size( size, size, uwinp->regular_min );
    }

    if ( Manage_Use_Size( uwinp, flags ) )
    {
        uwinp->sized = TRUE;
        uwinp->regular_size = size;
    }
    else
        if ( uwinp->zoomed )
            siz_act = FALSE;

    /* - - - - - - - - - - - - - - - - - - - - - - - - */

    pos_act = Size_Hints_User_Position(flags);

    Set_Max_Size( uwinp->zoom_size,
                  uwinp->zoom_size, uwinp->regular_size );
    Set_Max_Size( uwinp->zoom_min,
                  uwinp->zoom_min, uwinp->regular_min );

    if ( uwinp->zoomed )
    {
        Tilwin_Set_Min( uwinp->winp, uwinp->zoom_min );
        Tilwin_Set_Desired( uwinp->winp, uwinp->zoom_size );
    }
    else
    {
        Tilwin_Set_Min( uwinp->winp, uwinp->regular_min );
        Tilwin_Set_Desired( uwinp->winp, uwinp->regular_size );
    }

    if ( (! ( siz_act || pos_act ) ) ||
         ( (! uwinp->ever_opened) && uwinp->layout_found ) )
    {
        Manage_Finish( TRUE );
        if (! by_user)
            Manage_Cant_Undo();
    }
    else if (! Userwin_Is_Open(uwinp) )
    {
        Manage_Act_Hints_Closed( uwinp, pos, size,
                                        pos_act, siz_act );
        Manage_Finish( TRUE );
        Manage_Cant_Undo();
    }
    else if ( by_user )
    {
        Manage_Act_Hints_Open( uwinp, pos, size, 
                                       pos_act, siz_act );
        Manage_Finish_Minned( uwinp, TRUE );
    }
    else
        Manage_Client_Finish_Minned( uwinp,
            Manage_Act_Hints_Open( uwinp, pos, size,
                                      pos_act, siz_act ) );
}

/* ------------------------------------------------------------ */

void Manage_Initial_Geometry( uwinp, top_left, bodsiz )
    Userwin *uwinp;
    TWPoint top_left;
    Size bodsiz;
{
    TWPoint center;
    Size siz;
    TWRectangle rect;

    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    rect.left_x = top_left.x;
    rect.top_y = top_left.y;

    rect.right_x = rect.left_x + bodsiz.width - 1;
    rect.bottom_y = rect.top_y + bodsiz.height - 1;

    rect = Region_Adjust_Rectangle( uwinp, rect );

    COMPUTE_CENTER( rect, center );

    COMPUTE_SIZE( rect, siz );
    if ( Profile_Supplies_User_Value( uwinp, NORMAL_DESIRED_WIDTH ) )
        siz.width = uwinp->regular_size.width;
    if ( Profile_Supplies_User_Value( uwinp, NORMAL_DESIRED_HEIGHT ) )
        siz.height = uwinp->regular_size.height;

    Set_Min_Size( siz, siz, Tilwin_Get_Max( uwinp->winp ) );
    Set_Max_Size( siz, siz, Tilwin_Get_Min( uwinp->winp ) );

    Tilwin_Set_Desired( uwinp->winp, siz );
    Tilwin_Set( uwinp->winp, center, siz );
}

/* ------------------------------------------------------------ */

void Manage_Client_Set_Normal_Hints( uwinp, flags,
                            min_size, max_size, incr_size,
                            min_aspect, max_aspect, base_size )
    Userwin *uwinp;
    long flags;
    Size min_size, max_size, incr_size, base_size;
    TWPoint min_aspect, max_aspect;
{
    Size siz;
    bool act = FALSE;

    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    Manage_Start();
    Manage_Save_State( uwinp );

    if ( uwinp->zoomed )
    {
        uwinp->zoom_min = Tilwin_Get_Min(uwinp->winp);
        uwinp->zoom_size = Tilwin_Get_Desired(uwinp->winp);
    }
    else
    {
        uwinp->regular_min = Tilwin_Get_Min(uwinp->winp);
        uwinp->regular_size = Tilwin_Get_Desired(uwinp->winp);
    }

    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MAX_WIDTH ) )
        max_size.width = uwinp->body_max.width;
    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MAX_HEIGHT ) )
        max_size.height = uwinp->body_max.height;

    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MIN_WIDTH ) )
        min_size.width = uwinp->body_min.width;
    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MIN_HEIGHT ) )
        min_size.height = uwinp->body_min.height;

    /* - - - - - - - - - - - - - - - - - - - - - - - - */

    if ( Size_Hints_Max(flags) )
    {
        if ( Size_Hints_Min(flags) )
            Set_Max_Size( max_size, max_size, min_size )
        else if ( Size_Hints_Base(flags) )
        {
            min_size = base_size;
            Set_Max_Size( max_size, max_size, min_size )
        }

        uwinp->client_max = Region_Adjust_Size( uwinp, max_size );
        if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MAXIMUMS ) )
        {    
            if ( Userwin_Get_Window_Option( uwinp,
                     AUTO_RESATISFY_ON_RESET_MINMAX ) )
                act = TRUE;

            Set_Min_Size( siz, Tilwin_Get_Max( uwinp->winp ), 
                          uwinp->client_max )
            Tilwin_Set_Max( uwinp->winp, siz );
            
            Set_Min_Size( uwinp->regular_min,
                          uwinp->regular_min, uwinp->client_max );

            Set_Min_Size( uwinp->regular_size,
                          uwinp->regular_size, uwinp->client_max )
        }
    }
    
    if ( Size_Hints_Min(flags) || Size_Hints_Base(flags) )
    {
        uwinp->body_min = min_size;
        uwinp->client_min = Region_Adjust_Size( uwinp, min_size );
        if ( Userwin_Get_Window_Option( uwinp, ENFORCE_CLIENT_MINIMUMS ) )
        {    
            if ( Userwin_Get_Window_Option( uwinp,
                     AUTO_RESATISFY_ON_RESET_MINMAX ) )
                act = TRUE;

            Set_Max_Size( siz, Tilwin_Get_Min( uwinp->winp ),
                          uwinp->client_min )
            Tilwin_Set_Min( uwinp->winp, siz );

            Set_Max_Size( uwinp->regular_min,
                          uwinp->regular_min, uwinp->client_min );

            Set_Max_Size( uwinp->regular_size,
                          uwinp->regular_size, uwinp->client_min );
        }
    }

    if ( Same_Size( Tilwin_Get_Min(uwinp->winp),
                    Tilwin_Get_Max(uwinp->winp) ) )
        uwinp->sized = TRUE;                    

    Set_Max_Size( uwinp->zoom_size,
                  uwinp->zoom_size, uwinp->regular_size );
    Set_Max_Size( uwinp->zoom_min,
                  uwinp->zoom_min, uwinp->regular_min );

    if ( uwinp->zoomed )
    {
        Tilwin_Set_Min( uwinp->winp, uwinp->zoom_min );
        Tilwin_Set_Desired( uwinp->winp, uwinp->zoom_size );
    }
    else
    {
        Tilwin_Set_Min( uwinp->winp, uwinp->regular_min );
        Tilwin_Set_Desired( uwinp->winp, uwinp->regular_size );
    }

    if ( !act ||
         ( (! uwinp->ever_opened) && uwinp->layout_found ) )
    {
        Manage_Finish( TRUE );
        Manage_Cant_Undo();
    }
    else if (! Userwin_Is_Open(uwinp) )
    {
        Manage_Resatisfy( uwinp );
        Manage_Finish( TRUE );
        Manage_Cant_Undo();
    }
    else
        Manage_Client_Finish_Minned( uwinp,
        {
            if( ! Manage_Resatisfy( uwinp ) )
                Draw_Flash();
        } )       
}
        
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

extern bool Manage_Fixed_Open();
extern bool Manage_User_Open_Automatically();

/* ------------------------------------------------------------ */

bool Manage_Client_Open_Automatically( uwinp )
    Userwin *uwinp;
{
    bool result = FALSE;

    if ( ! uwinp->ever_opened )
    {
        Manage_Start();

        if ( uwinp->sized && uwinp->positioned )
            Manage_Client(
                global_excursion( ENABLE_GRAVITY, FALSE,
                {
                    result = Manage_Fixed_Open( uwinp );
                } ) )

        if (! result)
            Manage_Client(
            {
                result = Manage_User_Open_Automatically(
                             uwinp, FALSE, FALSE );
            } )

        if (! result)
            Manage_Client(
                Manage_Initial_Icon_Open( uwinp ) );

        uwinp->ever_opened = TRUE;
        Manage_Finish( TRUE );
    }
    else
        Manage_Client( 
            {
                result = Manage_User_Open_Automatically(
                             uwinp, FALSE, FALSE );
            } )

    return result;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static bool Manage_Exchange_Open( uwinp, pos, siz )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
{
    bool result;

    Manage_Start_Trying();

    result = Manage_Center_Neighborhood_Open( uwinp, pos, siz );
    if ( (! result) && Manage_Can_Try_Listener_Unzoom() )
        result = Manage_Center_Neighborhood_Open( uwinp, pos, siz );

    Manage_Finish_Trying( result );
    return result;
}

/* ------------------------------------------------------------ */

static bool Manage_Icon_Exchange_Open( uwinp, pos )
    Userwin *uwinp;
    TWPoint pos;
{
    bool result;

    result = Manage_Neighborhood_Icon_Open( uwinp, pos );
    if (! result)
        result = Manage_Icon_Open( uwinp );

    return result;
}

/* ------------------------------------------------------------ */

static bool Manage_Icon_Exchange( uwinp1, uwinp2 )
    Userwin *uwinp1, *uwinp2;
{
    bool result;
    TWPoint pt1, pt2;
    pt1 = Tilwin_Get_Center( uwinp1->iconp );
    pt2 = Tilwin_Get_Center( uwinp2->iconp );

    Tilwin_Close( uwinp1->iconp );

    global_excursion( PREFER_CLOSE_TO_SHRINK,
        UserGlobals_Get_Option(PREFER_CL_TO_SHR_ON_EXCHANGE),
      global_restrict_excursion(
        ALLOW_AUTOMATIC_CLOSE, 
            UserGlobals_Get_Option(ALLOW_AUTO_CLOSE_ON_EXCHANGE),
      global_restrict_excursion(
        ALLOW_AUTOMATIC_SHRINK,
            UserGlobals_Get_Option(ALLOW_AUTO_SHRINK_ON_EXCHANGE),
    {
        result = Manage_Icon_Exchange_Open( uwinp2, pt1 );
        if ( result )
            result = Manage_Icon_Exchange_Open( uwinp1, pt2 );
    } ) ) )

    if ( result )
    {
        Tilwin_Set_Position( uwinp1->iconp, pt2 );
        Tilwin_Set_Position( uwinp2->iconp, pt1 );
    }

    return result;
}

/* ------------------------------------------------------------ */

static bool Manage_Open_Exchange( uwinp1, uwinp2 )
    Userwin *uwinp1, *uwinp2;
{
    TWPoint pt1, pt2;
    Size siz;
    bool result;

    Manage_Restart();
    
    pt1 = Tilwin_Get_Center( uwinp1->winp );
    pt2 = Tilwin_Get_Center( uwinp2->winp );

    Tilwin_Close( uwinp1->winp );

    user_global_restrict_excursion( 
        UNZOOM_TIED_LSNR_IF_NECESSARY,
        ( ( listener != uwinp1 ) && ( listener != uwinp2 ) ),
      global_excursion( PREFER_CLOSE_TO_SHRINK,
        UserGlobals_Get_Option(PREFER_CL_TO_SHR_ON_EXCHANGE),
      global_restrict_excursion(
        ALLOW_AUTOMATIC_CLOSE, 
            UserGlobals_Get_Option(ALLOW_AUTO_CLOSE_ON_EXCHANGE),
      global_restrict_excursion(
        ALLOW_AUTOMATIC_SHRINK,
            UserGlobals_Get_Option(ALLOW_AUTO_SHRINK_ON_EXCHANGE),
    {
        siz = Tilwin_Checked_Desired_Size( uwinp2->winp );
        result = Manage_Exchange_Open( uwinp2, pt1, siz );
        if ( result )
            window_excursion( uwinp2->winp, REQUIRE_MANUAL_CLOSE, TRUE,
            {
                siz = Tilwin_Checked_Desired_Size( uwinp1->winp );
                result = Manage_Exchange_Open( uwinp1, pt2, siz );
            } )
    } ) ) ) )

    if ( result )
    {
        Tilwin_Set_Position( uwinp1->winp, pt2 );
        uwinp1->positioned = TRUE;
        Tilwin_Set_Position( uwinp2->winp, pt1 );
        uwinp2->positioned = TRUE;
    }
    return result;
}

/* ------------------------------------------------------------ */

static bool Manage_Different_Exchange( uwinp1, uwinp2 )
    Userwin *uwinp1, *uwinp2;
{
    TWPoint pt1, pt2;
    Size siz;
    bool result;
    bool repos1 = FALSE;
    bool repos2 = FALSE;

    if ( uwinp2 == rtl_uwinp ) return FALSE;

    Manage_Restart();
    
    pt1 = Tilwin_Get_Center( uwinp1->winp );
    pt2 = Tilwin_Get_Center( uwinp2->iconp );

    Tilwin_Close( uwinp1->winp );
    Tilwin_Close( uwinp2->iconp );

    user_global_restrict_excursion( 
        UNZOOM_TIED_LSNR_IF_NECESSARY,
        ( listener != uwinp1 ),
    { global_excursion( PREFER_CLOSE_TO_SHRINK,
        UserGlobals_Get_Option(PREFER_CL_TO_SHR_ON_EXCHANGE),
    { global_restrict_excursion(
        ALLOW_AUTOMATIC_CLOSE, 
            UserGlobals_Get_Option(ALLOW_AUTO_CLOSE_ON_EXCHANGE),
    { global_restrict_excursion(
        ALLOW_AUTOMATIC_SHRINK,
            UserGlobals_Get_Option(ALLOW_AUTO_SHRINK_ON_EXCHANGE),
    {
        siz = Tilwin_Checked_Desired_Size( uwinp2->winp );
        if ( UserGlobals_Get_Option(PREFER_EXCHANGED_LOC_ON_OPENING) &&
             (! ( uwinp2->positioned &&
                  Userwin_Get_Window_Option( uwinp2, 
                      REQUIRE_PREV_POS ) ) ) )
        {
            result = Manage_Exchange_Open( uwinp2, pt1, siz );
            if ( result )
                repos2 = TRUE;
        }
        if (! result)
            result = Manage_Desktop_Open( uwinp2, siz );
    } ) } ) } ) } )
    if (! result)
        return FALSE;
    window_excursion( uwinp2->winp, REQUIRE_MANUAL_CLOSE, TRUE,
    {
        if ( UserGlobals_Get_Option(
                    PREFER_EXC_LOC_ON_ICONIZING) )
        {
            if ( Manage_Neighborhood_Icon_Open( uwinp1, pt2 ) )
                repos1 = TRUE;
            else
                Manage_Icon_Open( uwinp1 );
        }
        else
            Manage_Icon_Open( uwinp1 );
    } )

    if ( repos1 )
        Tilwin_Set_Position( uwinp1->iconp, pt2 );
    if ( repos2 )
    {
        Tilwin_Set_Position( uwinp2->winp, pt1 );
        uwinp2->positioned = TRUE;
    }

    return TRUE;
}

/* ------------------------------------------------------------ */

bool Manage_Exchange( uwinp1, uwinp2 )
    Userwin *uwinp1, *uwinp2;
{
    bool open1, open2;
    bool result;

    Manage_Start();

    open1 = ( uwinp1->current_type == body );
    open2 = ( uwinp2->current_type == body );

    if ( open1 && (! open2) )
    {
        result = Manage_Different_Exchange( uwinp1, uwinp2 );
        Manage_Finish_Locked( uwinp2, result );
    }

    else if ( open2 && (! open1) )
    {
        result = Manage_Different_Exchange( uwinp2, uwinp1 );
        Manage_Finish_Locked( uwinp1, result );
    }

    else if ( (! open1) && (! open2) )
    {
        result = Manage_Icon_Exchange( uwinp1, uwinp2 );
        Manage_Finish( result );
    }

    else
    {
        result = FALSE;

        if ( UserGlobals_Get_Option(
                 TRY_CTR_NBRHD_ON_EXCHANGE) &&
             UserGlobals_Get_Option(
                 TRY_CTR_NBRHD_ON_OPEN) )
        {
            result = Manage_Open_Exchange( uwinp1, uwinp2 );
            if (! result)
                result = Manage_Open_Exchange( uwinp2, uwinp1 );
        }
    
        if (! result)
            user_global_excursion( 
                TRY_CTR_NBRHD_ON_OPEN, FALSE,
            {
                result = Manage_Open_Exchange( uwinp1, uwinp2 );
                if (! result)
                    result = Manage_Open_Exchange( uwinp2, uwinp1 );
            } )
    
        window_excursion( uwinp1->winp, REQUIRE_MANUAL_CLOSE, TRUE,
            window_excursion( uwinp2->winp, REQUIRE_MANUAL_CLOSE, TRUE,
                Manage_Finish( result ) ) );

    }

    return result;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Remove_Window( uwinp )
    Userwin *uwinp;
{
    TimeStamp stamp;

    Manage_Start();

    if ( Tilwin_Is_Open( uwinp->winp ) )
    {
        Tilwin_Close( uwinp->winp );

        if ( UserGlobals_Get_Option(AUTO_REPOPULATE_ON_CLOSE) )
        {
            if ( UserGlobals_Get_Option(AUTO_DESIRED_ENLARGE) )        
                Manage_Ordered_Desire(); 

            if ( UserGlobals_Get_Option(ONLY_REPOPULATE_SINCE_ON_CLOSE) )
                stamp = uwinp->open_stamp;
            else
                stamp = (TimeStamp)0;
            Manage_Repopulate_Since( stamp, FALSE, FALSE, TRUE );
        }
    }

    Manage_Finish( TRUE );
}

/* ------------------------------------------------------------ */

static void Manage_Remove( uwinp )
    Userwin *uwinp;
{
    if ( Tilwin_Is_Open( uwinp->winp ) )
        Tilwin_Close( uwinp->winp );
    else if ( Tilwin_Is_Open( uwinp->iconp ) )
        Tilwin_Close( uwinp->iconp );

    Closed_Remove( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Close( uwinp )
    Userwin *uwinp;
{
    extern void Manage_Contract();

    if ( uwinp->client_state != ClientIconState )
        Manage_Remove_Window( uwinp );
    else if ( Same_Size( Tilwin_Get_Min(uwinp->winp),
                         Tilwin_Get_Size(uwinp->winp) ) )
        Manage_Remove_Window( uwinp );
    else
        Manage_Contract( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Client_Close( uwinp )
    Userwin *uwinp;
{
    Manage_Client( Manage_Remove_Window( uwinp ) );
}

/* ------------------------------------------------------------ */

void Manage_Client_Open_Icon( uwinp )
    Userwin *uwinp;
{
    if ( uwinp->ever_opened )
        Manage_Client_Close( uwinp );
    else
    {
        uwinp->ever_opened = TRUE;
        Manage_Client( Manage_Initial_Icon_Open( uwinp ) )
    }
}

/* ------------------------------------------------------------ */

static void Manage_Close_Icon( uwinp )
    Userwin *uwinp;
{
    Manage_Start();
    if ( Tilwin_Is_Open( uwinp->iconp ) )
        Tilwin_Close( uwinp->iconp );
    Manage_Finish( TRUE );
}

/* ------------------------------------------------------------ */

static void Manage_Inactivate( uwinp )
    Userwin *uwinp;
{
    if ( Tilwin_Is_Open( uwinp->winp ) )
        Manage_Remove_Window( uwinp );
    else
        Manage_Close_Icon( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Client_Close_Icon( uwinp )
    Userwin *uwinp;
{
    Manage_Client( Manage_Inactivate( uwinp ) )
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Group_Close( uwinp )
    Userwin *uwinp;
{
    Tilwinp winp;
    Userwin *group;
    TimeStamp stamp;

    group = uwinp->group;
    if ( group == UWIN_NULL )
    {
        Manage_Close( uwinp );
        return;
    }
    
    Manage_Start();

    group->group = group;

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( (uwinp->group == group) &&
             (! Tilwin_Is_Open(uwinp->winp)) &&
             (! Tilwin_Is_Open(uwinp->iconp)) )
        {
            Manage_Save_State( uwinp );
            Closed_Remove( uwinp );
            uwinp->group_state = uwinp->wm_state;
        }
    }

    stamp = last_stamp;

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->group == group )
        {
            if ( uwinp->winp == winp )
                stamp = MIN( stamp, uwinp->open_stamp );

            Manage_Save_State( uwinp );
            Manage_Remove( uwinp );
            uwinp->group_state = uwinp->wm_state;
        }
    }

    if (! group->ever_opened)
        Manage_Prepare_Open( group );

    Closed_Add( uwinp );
    if ( UserGlobals_Get_Option(USE_ICONS) )
        Manage_Icon_Open( uwinp );

    if ( UserGlobals_Get_Option(AUTO_REPOPULATE_ON_CLOSE) )
    {
        if ( UserGlobals_Get_Option(AUTO_DESIRED_ENLARGE) )        
            Manage_Ordered_Desire(); 

        if (! UserGlobals_Get_Option(ONLY_REPOPULATE_SINCE_ON_CLOSE) )
            stamp = (TimeStamp)0;
        Manage_Repopulate_Since( stamp, FALSE, FALSE, TRUE );
    }

    Manage_Finish( TRUE );
}    

/* ------------------------------------------------------------ */

static void Manage_Group_Restore( uwinp )
    Userwin *uwinp;
{
    int state;

    state = uwinp->group_state;
    uwinp->group_state = GroupState;

    switch ( state )
    {
        case NeverState:
            break;

        case NoState:
        case DontCareState:
        case NormalState:
            Closed_Add( uwinp );
            Manage_User_Open_Automatically( uwinp, FALSE, FALSE );
            break;

        case ClientIconState:
        case IconicState:
        case InactiveState:
            Closed_Add( uwinp );
            if ( uwinp->client_state == ClientIconState )
                Manage_User_Open_Automatically( uwinp, FALSE, FALSE );
            else
                Manage_Icon_Open( uwinp );
            break;

        case IgnoreState:
            break;
    }
}

/* ------------------------------------------------------------ */

void Manage_Group_Open( group )
    Userwin *group;
{
    bool found = TRUE;
    Tilwinp winp;
    Userwin *uwinp;

    Manage_Start();

    Manage_Save_State( group );
    if ( Tilwin_Is_Open( group->iconp ) )
        Tilwin_Close( group->iconp );
    Closed_Remove( group );
    
    while (found)
    {
        found = FALSE;
        
        Tilwin_Gen_Closed_Windows();
        while ( (! found) &&
                ( (winp = Tilwin_Next_Window()) != WIN_NULL ) )
        {
            uwinp = Userwin_Get(winp);
            if ( Userwin_Group_Closed( uwinp ) &&
                 (uwinp->group == group) )
            {
                found = TRUE;
                Manage_Group_Restore( uwinp );
            }
        }
    }

    Manage_Finish( TRUE );
}    

/* ------------------------------------------------------------ */

void Manage_Want_State( uwinp, state )
    Userwin *uwinp;
    int state;
{
    uwinp->group_state = state;
}

/* ------------------------------------------------------------ */

static void Manage_Set_Group( uwinp, group )
    Userwin *uwinp;
    Userwin *group;
{
    Manage_Start();

    uwinp->group = group;
    if (! Userwin_Group_Closed( uwinp ) )
    {
        if ( ( group != UWIN_NULL) && Userwin_Group_Closed( group ) )
        {
            Manage_Save_State( uwinp );
            Manage_Remove( uwinp );
            uwinp->group_state = uwinp->wm_state;
        }
    }
    else if ( ( group == UWIN_NULL ) ||
              (! Userwin_Group_Closed( group ) ) )
        Manage_Group_Restore( uwinp );

    Manage_Finish( TRUE );
}

/* ------------------------------------------------------------ */

void Manage_Client_Set_Group( uwinp, group )
    Userwin *uwinp;
    Userwin *group;
{
    Manage_Client( Manage_Set_Group( uwinp, group ) )
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Client_Set_State( uwinp, state )
    Userwin *uwinp;
    int state;
{
    uwinp->client_state = state;
}

/* ------------------------------------------------------------ */

void Manage_Client_Change_State( uwinp, state )
    Userwin *uwinp;
    int state;
{
    uwinp->client_state = state;

    if ( ( state != IgnoreState ) &&
         ( uwinp->wm_state == IgnoreState ) )
        Drawwin_Insert( uwinp );
    else if ( ( state == IgnoreState ) &&
              ( uwinp->wm_state != IgnoreState ) )
        Drawwin_Withdraw( uwinp );

    if ( Userwin_Group_Closed( uwinp ) )
    {
        if ( state == IgnoreState )
        {
            if ( (uwinp->wm_state != IgnoreState) &&
                 (uwinp->group != uwinp) )
            {
                uwinp->wm_state = IgnoreState;
                Client_Set_State( uwinp );
            }
            uwinp->group_state = IgnoreState;
        }
        else
        {
            if ( uwinp->wm_state == IgnoreState )
            {
                uwinp->wm_state = InactiveState;
                uwinp->group_state = state;
                Client_Set_State( uwinp );
            }

            else if ( ( state != NoState ) && ( state != DontCareState ) )
                uwinp->group_state = state;
        }
    }
    else
    {
        switch ( state )
        {
            case NoState:
            case DontCareState:
                break;
    
            case NormalState:
            case ClientIconState:
                if (! Tilwin_Is_Open( uwinp->winp ) )
                    Manage_Client_Open_Automatically( uwinp );
                break;
    
            case IconicState:
                Manage_Client( Manage_Remove_Window( uwinp ) );
                break;
    
            case InactiveState:
                if ( Tilwin_Is_Open(uwinp->winp) ||
                     Tilwin_Is_Open(uwinp->iconp) )
                    Manage_Client( Manage_Inactivate( uwinp ) )

                uwinp->wm_state = InactiveState;
                Client_Set_State( uwinp );
                Closed_Add( uwinp );

                break;
    
            case IgnoreState:
                if ( Tilwin_Is_Open(uwinp->winp) ||
                     Tilwin_Is_Open(uwinp->iconp) )
                    Manage_Client( Manage_Inactivate( uwinp ) )

                uwinp->wm_state = IgnoreState;
                Client_Set_State( uwinp );

                Closed_Remove( uwinp );
                break;
        }
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Repopulate_Last()
{
    Manage_Start();
    Manage_Repopulate_Since( last_stamp, TRUE, FALSE, TRUE );
    Manage_Finish( TRUE );
}

/* ------------------------------------------------------------ */

void Manage_Repopulate_All( strict, only_auto_close )
    bool strict;
    bool only_auto_close;
{
    Manage_Start();
    Manage_Repopulate_Since( (TimeStamp)0, TRUE, strict, only_auto_close );
    Manage_Finish( TRUE );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Cleanup_Window( uwinp )
    Userwin *uwinp;
{
    if ( uwinp == prev_touch ) prev_touch = UWIN_NULL;
    if ( uwinp == prev_listener ) prev_listener = UWIN_NULL;
    Manage_Unset( uwinp );

    /* So Update Desktop treats correctly */
    uwinp->client_state = NeverState;

    Manage_Remove( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Eliminate_Window( uwinp )
    Userwin *uwinp;
{
    Manage_Untitle( uwinp );

    Drawwin_Destroy( uwinp );
    DrawIcon_Destroy( uwinp );

    Tilwin_Destroy_Window( uwinp->winp );
    Tilwin_Destroy_Window( uwinp->iconp );

    Userwin_Deallocate( uwinp );
}

/* ------------------------------------------------------------ */

static void Manage_Cleanup_Connection( connection )
    int connection;
{
    Tilwinp winp;
    Userwin *uwinp;

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( (uwinp->connection == connection ) &&
             ( (winp == uwinp->winp) || Tilwin_Is_Open(uwinp->winp) ) )
        {
            Manage_Cleanup_Window( uwinp );
        }
    }
}

/* ------------------------------------------------------------ */

static void Manage_Eliminate_Connection( connection )
    int connection;
{
    Tilwinp winp;
    Userwin *uwinp;
    bool killed = TRUE;

    while (killed)
    {
        killed = FALSE;
        Tilwin_Gen_Closed_Windows();
        while ( (! killed) &&
                ( (winp = Tilwin_Next_Window()) != WIN_NULL ) )
        {
            uwinp = Userwin_Get(winp);
            if ( (uwinp->connection == connection ) &&
                 ( (winp == uwinp->winp) || Tilwin_Is_Open(uwinp->winp) ) )
            {
                Manage_Eliminate_Window( uwinp );
                killed = TRUE;
            }
        }
    }
}

/* ------------------------------------------------------------ */

static void Manage_Destroy_Window( uwinp )
    Userwin *uwinp;
{
    bool zoomed;
    TimeStamp open_stamp, zoom_stamp;

    Manage_Start();

    if ( UserGlobals_Get_Option(ONLY_REPOPULATE_SINCE_ON_CLOSE) )
        open_stamp = uwinp->open_stamp;
    else
        open_stamp = (TimeStamp)0;

    zoomed = uwinp->zoomed;
    if ( UserGlobals_Get_Option(
             ONLY_REPOP_SINCE_ON_AUTO_UNZOOM) ||
         UserGlobals_Get_Option(
             ONLY_REPOP_SINCE_ON_EXPL_UNZOOM) )
        zoom_stamp = uwinp->zoom_stamp;
    else
        zoom_stamp = (TimeStamp)0;

    Manage_Cleanup_Window( uwinp );

    Manage_Update_Desktop();

    Manage_Eliminate_Window( uwinp );

    if ( UserGlobals_Get_Option(AUTO_DESIRED_ENLARGE) )        
        Manage_Ordered_Desire(); 

    if ( UserGlobals_Get_Option(AUTO_REPOPULATE_ON_CLOSE) )
        Manage_Repopulate_Since( open_stamp, FALSE, FALSE, TRUE );

    if ( zoomed && 
         UserGlobals_Get_Option(AUTO_REPOP_ON_EXPLICIT_UNZOOM) )
        Manage_Repopulate_Since( zoom_stamp, FALSE, FALSE, TRUE );

    Manage_Finish( TRUE );
}

/* ------------------------------------------------------------ */

void Manage_Client_Destroy( uwinp )
    Userwin *uwinp;
{
    Manage_Unset( uwinp );
    Manage_Client( Manage_Destroy_Window( uwinp ) );
}

/* ------------------------------------------------------------ */

void Manage_Hard_Kill( uwinp )
    Userwin *uwinp;
{
    Client_Kill( uwinp );
    Manage_Destroy_Window( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Notify( uwinp )
    Userwin *uwinp;
{
    if ( Userwin_Bangs( uwinp ) )
    {
        uwinp->saving_state = TRUE;
        Client_Bang( uwinp );
    }
    else
        Draw_Flash();
}

/* ------------------------------------------------------------ */

void Manage_Soft_Kill( uwinp )
    Userwin *uwinp;
{
    if ( Userwin_Bangs( uwinp ) )
    {
        uwinp->saving_state = TRUE;
        uwinp->soft_kill = TRUE;
        Client_Bang( uwinp );
    }
    else
    {
        Client_Kill( uwinp );
        Manage_Destroy_Window( uwinp );
    }
}

/* ------------------------------------------------------------ */

void Manage_Delete_Window( uwinp )
    Userwin *uwinp;
{
    if ( Userwin_Deletes_Window( uwinp ) )
        Client_Delete_Window( uwinp );
    else
        Manage_Soft_Kill( uwinp );
}

/* ------------------------------------------------------------ */

void Manage_Notify_All()
{
    Tilwinp winp;
    Userwin *uwinp;

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( (uwinp != rtl_uwinp) &&
             ( (winp == uwinp->winp) || Tilwin_Is_Open(uwinp->winp) ) )
        {
            if ( Userwin_Bangs( uwinp ) )
                Manage_Notify( uwinp );
        }
    }
}

/* ------------------------------------------------------------ */

void Manage_Soft_Kill_All()
{
    Tilwinp winp;
    Userwin *uwinp;
    bool killed = TRUE;

    while (killed)
    {
        killed = FALSE;
        Tilwin_Gen_Closed_Windows();
        while ( (! killed) &&
                ( (winp = Tilwin_Next_Window()) != WIN_NULL ) )
        {
            uwinp = Userwin_Get(winp);
            if ( (uwinp != rtl_uwinp) &&
                 ( (winp == uwinp->winp) || Tilwin_Is_Open(uwinp->winp) ) )
            {
                Manage_Soft_Kill( uwinp );
                killed = TRUE;
            }
        }
    }
}

/* ------------------------------------------------------------ */

void Manage_Exit()
{
    Tilwinp winp;
    Userwin *uwinp;

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( (uwinp != rtl_uwinp) &&
             ( (winp == uwinp->winp) || Tilwin_Is_Open(uwinp->winp) ) )
            Client_Kill( uwinp );
    }
}

/* ------------------------------------------------------------ */

void Manage_Client_Set_Messages( uwinp, messages )
    Userwin *uwinp;
    long messages;
{
    uwinp->messages = messages;
}
