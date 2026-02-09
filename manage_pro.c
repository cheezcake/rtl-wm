#ifndef lint
static char sccs_id[] = "@(#)manage_pro.c	5.6  9/1/88";
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

#include "userglobD.h"
#include "twin.h"

#ifndef USERWIN_DEFINE
#include "uwinD.h"
#endif

#ifndef TILWIN_DEFINE
#include "twinD.h"
#endif
    
#define global_excursion(opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Tilwin_Get_Global_Option(opt); \
    Tilwin_Set_Global_Option(opt,val); \
    code; \
    Tilwin_Set_Global_Option(opt,temp_val); \
}

#define window_excursion(win,opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Tilwin_Get_Window_Option(win,opt); \
    Tilwin_Set_Window_Option(win,opt,val); \
    code; \
    Tilwin_Set_Window_Option(win,opt,temp_val); \
}

#define min_excursion(win,code) \
{ \
    Size temp_min; \
    temp_min = Tilwin_Get_Min(win); \
    Tilwin_Set_Min( win, Tilwin_Get_Size(win) ); \
    code; \
    Tilwin_Set_Min( win, temp_min ); \
}

#define min_size_excursion(win,siz,code) \
{ \
    Size temp_min; \
    temp_min = Tilwin_Get_Min(win); \
    Tilwin_Set_Min( win, siz ); \
    code; \
    Tilwin_Set_Min( win, temp_min ); \
}
    
#define user_global_excursion(opt,val,code) \
{ \
    bool temp_val; \
    temp_val = UserGlobals_Get_Option(opt); \
    UserGlobals_Set_Option( opt, val ); \
    code; \
    UserGlobals_Set_Option(opt,temp_val); \
}

#define DESIRE_ITERS 5
#define MAXIMIZE_ITERS 2
#define PRORATE_ITERS 4
#define FILL_ITERS 1

extern Userwin *listener;

static bool auto_prorate = TRUE;

extern bool Manage_Icon_Open();
extern void Manage_Start();
extern void Manage_Save_State();
extern void Manage_Finish();
extern bool Manage_Finish_Fixed_Size();
extern bool Manage_Finish_Minned();

/* ------------------------------------------------------------ */

static TWRectangle Manage_Farthest_Area( pt, rect )
    TWPoint pt;
    TWRectangle rect;
{
    TWPoint center;
    TWRectangle area;

    COMPUTE_CENTER( rect, center );
    area = Tilwin_Get_Desktop_Rectangle();

    if ( center.x > pt.x )
        area.left_x = rect.left_x;
    else if ( center.x < pt.x )
        area.right_x = rect.right_x;

    if ( center.y > pt.y )
        area.top_y = rect.top_y;
    else if ( center.y < pt.y )
        area.bottom_y = rect.bottom_y;

    return area;
}

/* ------------------------------------------------------------ */

static TWRectangle Manage_Nearest_Area( pt, rect )
    TWPoint pt;
    TWRectangle rect;
{
    TWPoint center;
    TWRectangle area;

    COMPUTE_CENTER( rect, center );
    area = Tilwin_Get_Desktop_Rectangle();

    if ( center.x > pt.x )
        area.right_x = rect.right_x;
    else if ( center.x < pt.x )
        area.left_x = rect.left_x;

    if ( center.y > pt.y )
        area.bottom_y = rect.bottom_y;
    else if ( center.y < pt.y )
        area.top_y = rect.top_y;

    return area;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Slide_Nearest()
{
    Tilwinp winp;
    Tilwinp thread_head;

    thread_head = Tilwin_Thread_Nearest_Position();

    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            Tilwin_Slide_Nearest( winp,
                Tilwin_Get_Position( winp ) );
    }
}

/* ------------------------------------------------------------ */

static void Manage_All_Desire()
{
    Tilwinp winp;
    Tilwinp thread_head;
    TWPoint center;
    Size siz;

    center = Tilwin_Position_Ctr_Of_Gravity();
    thread_head = Tilwin_Thread_Nearest( center );

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
          && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
        {
            siz = Tilwin_Checked_Desired_Size( winp );
            Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
            Tilwin_Enlarge_Nearest( winp,
                Tilwin_Get_Position(winp), siz );
        }
    } ) )
}

/* ------------------------------------------------------------ */

static void Manage_All_Maximize()
{
    Tilwinp winp;
    Tilwinp thread_head;
    TWPoint center;
    Size siz;

    center = Tilwin_Position_Ctr_Of_Gravity();
    thread_head = Tilwin_Thread_Nearest( center );

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
          && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
        {
            siz = Tilwin_Checked_Max_Size( winp );
            Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
            Tilwin_Enlarge_Nearest( winp,
                Tilwin_Get_Position(winp), siz );
        }
    } ) )
}

/* ------------------------------------------------------------ */

static void Manage_All_Previous()
{
    Tilwinp winp;
    Tilwinp thread_head;
    TWPoint center;
    Size siz;

    center = Tilwin_Position_Ctr_Of_Gravity();
    thread_head = Tilwin_Thread_Nearest( center );

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
          && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
        {
            siz = Tilwin_Checked_Previous_Size( winp );
            Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
            Tilwin_Enlarge_Nearest( winp,
                Tilwin_Get_Position(winp), siz );
        }
    } ) )
}

/* ------------------------------------------------------------ */

static void Manage_Slide_Desire()
{
    Manage_Slide_Nearest();
    Manage_Slide_Nearest();
    Manage_All_Desire();
}

/* ------------------------------------------------------------ */

static void Manage_Slide_Maximize()
{
    Manage_Slide_Nearest();
    Manage_Slide_Nearest();
    Manage_All_Maximize();
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static Tilwinp plow_head;

static void Manage_Start_Plow( rect, pt )
    TWRectangle rect;
    TWPoint pt;
{
    TWPoint center;
    Tilwinp winp;

    COMPUTE_CENTER( rect, center );

    plow_head = Tilwin_Thread_Farthest( center );

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
    {
        for ( winp = plow_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY) )
            {
		Tilwin_Act_Modified( winp );
                Tilwin_Set_Size( winp, Tilwin_Checked_Min_Size( winp ) );
                Tilwin_Slide_Farthest_In_Area( winp,
                    Manage_Farthest_Area( pt,
                        Tilwin_Get_Rectangle( winp ) ),
                    pt );
            }
        }                
    } ) )
}

/* ------------------------------------------------------------ */

static void Manage_Plow_Back()
{
    Tilwinp winp;
    TWRectangle rect;
    Size siz;
    TWPoint pt;

    plow_head = Tilwin_Reverse_Thread( plow_head );
    
    for ( winp = plow_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if ( Tilwin_Is_Open( winp ) &&
             (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY) ) )
        {
            siz = Tilwin_Get_Size(winp);
            pt = Tilwin_Get_Previous_Center(winp);

            if (! Tilwin_Open( winp, pt, siz ) )
            {
                MAKE_RECTANGLE( pt, siz, rect )

                Tilwin_Open_Nearest_In_Area( winp,
                    Manage_Nearest_Area(
                        Tilwin_Get_Center(winp), rect ),
                    pt, siz );
            }
        }
    }
}

/* ------------------------------------------------------------ */

static void Manage_Plow_Restore()
{
    Tilwinp winp;
    TWRectangle rect;
    Size siz;
    TWPoint pt;
    Size minsiz;

    plow_head = Tilwin_Reverse_Thread( plow_head );
    
    for ( winp = plow_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if ( Tilwin_Is_Open( winp ) &&
             (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY) ) )
        {
            siz = Tilwin_Get_Previous_Size(winp);
            pt = Tilwin_Get_Previous_Center(winp);

            if (! Tilwin_Open( winp, pt, siz ) )
            {
                MAKE_RECTANGLE( pt, siz, rect )
                rect = Manage_Nearest_Area(
                    Tilwin_Get_Center(winp), rect );

                Tilwin_Enlarge_Nearest_In_Area( winp, rect, pt, siz );
                
                minsiz = Tilwin_Good_Size( winp,
                    Tilwin_Get_Size( winp ) );

                min_size_excursion( winp, minsiz,
                    Tilwin_Open_Nearest_In_Area( winp, rect, pt, siz ) )
            }
        }
    }
}

/* ------------------------------------------------------------ */

static void Manage_Finish_Plow()
{
    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
    {
        Manage_Plow_Back();
        Manage_Plow_Restore();
        Manage_Slide_Nearest();
        Manage_Slide_Nearest();
	Manage_All_Previous();
        Manage_All_Desire();
    } ) )
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Ordered_Desire()
{
    Tilwinp winp;
    Tilwinp thread_head;
    Size siz;
    TWPoint center;
    float good;
    int i;

    center = Tilwin_Position_Ctr_Of_Gravity();
    thread_head = Tilwin_Thread_Nearest( center );

    for ( i = 1; i <= DESIRE_ITERS; i++ )
    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
    {    
        good = (float)(i) / (float)DESIRE_ITERS;
        
        for ( winp = thread_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if  ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
               || (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
            {
                siz = Tilwin_Checked_Good_Desired_Size( winp, good );
                Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
                Tilwin_Enlarge_Nearest( winp,
                    Tilwin_Get_Previous_Center(winp), siz );
            }
        }
    } ) )
}

/* ------------------------------------------------------------ */

static void Manage_Local_Prorate()
{
    Manage_Ordered_Desire();
    Manage_Slide_Desire();
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Fair_Vertical_Desire()
{
    Tilwinp thread_head;
    Size siz;
    TWPoint center;
    Tilwinp winp;
    Tilwinp latest;
    float good;
    int iter;
    int prorate_iters;

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        siz = Tilwin_Checked_Min_Size( winp );
        siz.width = Tilwin_Get_Size(winp).width;
        Tilwin_Set_Size( winp, siz );
    }

    center.x = Tilwin_Get_Desktop_Center().x;
    center.y = Tilwin_Get_Desktop_Rectangle().top_y;
    thread_head = Tilwin_Thread_Vertly_Nearest( center ); 

    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            Tilwin_Slide_Vertly_Nearest( winp, center );
    }

    if (auto_prorate)
    {
        prorate_iters = PRORATE_ITERS - 2;
        for ( iter = 1; iter <= 2; iter++ )
        {
            if (iter == 1)
                center.y = Tilwin_Get_Desktop_Rectangle().bottom_y;
            else
                center.y = Tilwin_Get_Desktop_Rectangle().top_y;
            thread_head = Tilwin_Thread_Vertly_Nearest( center ); 
    
            latest = Tilwin_Get_Latest_Height( iter );
            for ( winp = thread_head;  winp != WIN_NULL;  
                  winp = (Tilwinp)Tilwin_Get_Data(winp) )
            {
                if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
                {
                    Tilwin_Slide_Vertly_Nearest( winp, center );
    
                    if (winp == latest)
                    {
                        siz = Tilwin_Checked_Desired_Size( winp );
                        siz.width = Tilwin_Get_Size(winp).width;
                        Tilwin_Enlarge_Nearest( winp, center, siz );
                    }
                }
            }
        }
    }
    else
        prorate_iters = PRORATE_ITERS;

    for ( iter = 1; iter <= prorate_iters; iter++ )
    {    
        good = (float)(2*iter-1) / (float)(2*prorate_iters);
    
        center.y = Tilwin_Get_Desktop_Rectangle().bottom_y;
        thread_head = Tilwin_Thread_Vertly_Nearest( center ); 

        for ( winp = thread_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            {
                Tilwin_Slide_Vertly_Nearest( winp, center );

                if (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) )
                {
                    siz = Tilwin_Checked_Good_Desired_Size( winp, good );
                    Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
                    siz.width = Tilwin_Get_Size(winp).width;
                    Tilwin_Enlarge_Nearest( winp, center, siz );
                }
            }
        }
    
        center.y = Tilwin_Get_Desktop_Rectangle().top_y;
        thread_head = Tilwin_Thread_Vertly_Nearest( center ); 

        good = (float)(iter) / (float)(prorate_iters);

        for ( winp = thread_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
                Tilwin_Slide_Vertly_Nearest( winp, center );
            {
                if (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) )
                {
                    siz = Tilwin_Checked_Good_Desired_Size( winp, good );
                    Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
                    siz.width = Tilwin_Get_Size(winp).width;
                    Tilwin_Enlarge_Nearest( winp, center, siz );
                }
            }
        }
    }

    center.y = Tilwin_Get_Desktop_Rectangle().bottom_y;
    thread_head = Tilwin_Thread_Vertly_Nearest( center ); 

    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            Tilwin_Slide_Vertly_Nearest( winp,
                Tilwin_Get_Position( winp ) );
    }
}

/* ------------------------------------------------------------ */

static void Manage_Fair_Horizontal_Desire()
{
    Tilwinp thread_head;
    Size siz;
    TWPoint center;
    Tilwinp winp;
    Tilwinp latest;
    float good;
    int iter;
    int prorate_iters;

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        siz = Tilwin_Checked_Min_Size( winp );
        siz.height = Tilwin_Get_Size(winp).height;
        Tilwin_Set_Size( winp, siz );
    }

    center.y = Tilwin_Get_Desktop_Center().y;
    center.x = Tilwin_Get_Desktop_Rectangle().left_x;
    thread_head = Tilwin_Thread_Horizly_Nearest( center ); 

    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            Tilwin_Slide_Horizly_Nearest( winp, center );
    }

    if ( auto_prorate )
    {
        prorate_iters = PRORATE_ITERS - 2;
        for ( iter = 1; iter <= 2; iter++ )
        {
            if (iter == 1)
                center.x = Tilwin_Get_Desktop_Rectangle().right_x;
            else
                center.x = Tilwin_Get_Desktop_Rectangle().left_x;
            thread_head = Tilwin_Thread_Horizly_Nearest( center ); 
    
            latest = Tilwin_Get_Latest_Width( iter );
            for ( winp = thread_head;  winp != WIN_NULL;  
                  winp = (Tilwinp)Tilwin_Get_Data(winp) )
            {
                if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
                {
                    Tilwin_Slide_Horizly_Nearest( winp, center );
    
                    if (winp == latest)
                    {
                        siz = Tilwin_Checked_Desired_Size( winp );
                        siz.height = Tilwin_Get_Size(winp).height;
                        Tilwin_Enlarge_Nearest( winp, center, siz );
                    }
                }
            }
        }
    }
    else
        prorate_iters = PRORATE_ITERS;

    for ( iter = 1; iter <= prorate_iters; iter++ )
    {    
        good = (float)(2*iter-1) / (float)(2*prorate_iters);
    
        center.x = Tilwin_Get_Desktop_Rectangle().right_x;
        thread_head = Tilwin_Thread_Horizly_Nearest( center ); 

        for ( winp = thread_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            {
                Tilwin_Slide_Horizly_Nearest( winp, center );

                if (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) )
                {
                    siz = Tilwin_Checked_Good_Desired_Size( winp, good );
                    Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
                    siz.height = Tilwin_Get_Size(winp).height;
                    Tilwin_Enlarge_Nearest( winp, center, siz );
                }
            }
        }
    
        center.x = Tilwin_Get_Desktop_Rectangle().left_x;
        thread_head = Tilwin_Thread_Horizly_Nearest( center ); 

        good = (float)(iter) / (float)(prorate_iters);

        for ( winp = thread_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
                Tilwin_Slide_Horizly_Nearest( winp, center );
            {
                if (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) )
                {
                    siz = Tilwin_Checked_Good_Desired_Size( winp, good );
                    Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
                    siz.height = Tilwin_Get_Size(winp).height;
                    Tilwin_Enlarge_Nearest( winp, center, siz );
                }
            }
        }
    }

    center.x = Tilwin_Get_Desktop_Rectangle().right_x;
    thread_head = Tilwin_Thread_Horizly_Nearest( center ); 

    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            Tilwin_Slide_Horizly_Nearest( winp,
                Tilwin_Get_Position( winp ) );
    }
}

/* ------------------------------------------------------------ */

static void Manage_Fair_Vertical_Maximize()
{
    Tilwinp thread_head;
    Size siz;
    TWPoint center;
    Tilwinp winp;
    float good;
    int iter;

    center.x = Tilwin_Get_Desktop_Center().x;
    center.y = Tilwin_Get_Desktop_Rectangle().top_y;
    thread_head = Tilwin_Thread_Vertly_Nearest( center ); 

    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            Tilwin_Slide_Vertly_Nearest( winp, center );
    }

    for ( iter = 1; iter <= FILL_ITERS; iter++ )
    {    
        good = (float)(2*iter-1) / (float)(2*FILL_ITERS);
    
        center.y = Tilwin_Get_Desktop_Rectangle().bottom_y;
        thread_head = Tilwin_Thread_Vertly_Nearest( center ); 

        for ( winp = thread_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            {
                Tilwin_Slide_Vertly_Nearest( winp, center );

                if (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) )
                {
                    siz = Tilwin_Checked_Good_Max_Size( winp, good );
                    Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
                    siz.width = Tilwin_Get_Size(winp).width;
                    Tilwin_Enlarge_Nearest( winp, center, siz );
                }
            }
        }
    
        center.y = Tilwin_Get_Desktop_Rectangle().top_y;
        thread_head = Tilwin_Thread_Vertly_Nearest( center ); 

        good = (float)(iter) / (float)(FILL_ITERS);

        for ( winp = thread_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
                Tilwin_Slide_Vertly_Nearest( winp, center );
            {
                if (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) )
                {
                    siz = Tilwin_Checked_Good_Max_Size( winp, good );
                    Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
                    siz.width = Tilwin_Get_Size(winp).width;
                    Tilwin_Enlarge_Nearest( winp, center, siz );
                }
            }
        }
    }

    center.y = Tilwin_Get_Desktop_Rectangle().bottom_y;
    thread_head = Tilwin_Thread_Vertly_Nearest( center ); 

    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            Tilwin_Slide_Vertly_Nearest( winp,
                Tilwin_Get_Position( winp ) );
    }
}

/* ------------------------------------------------------------ */

static void Manage_Fair_Horizontal_Maximize()
{
    Tilwinp thread_head;
    Size siz;
    TWPoint center;
    Tilwinp winp;
    float good;
    int iter;

    center.y = Tilwin_Get_Desktop_Center().y;
    center.x = Tilwin_Get_Desktop_Rectangle().left_x;
    thread_head = Tilwin_Thread_Horizly_Nearest( center ); 

    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            Tilwin_Slide_Horizly_Nearest( winp, center );
    }

    for ( iter = 1; iter <= FILL_ITERS; iter++ )
    {    
        good = (float)(2*iter-1) / (float)(2*FILL_ITERS);
    
        center.x = Tilwin_Get_Desktop_Rectangle().right_x;
        thread_head = Tilwin_Thread_Horizly_Nearest( center ); 

        for ( winp = thread_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if  (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            {
                Tilwin_Slide_Horizly_Nearest( winp, center );

                if (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) )
                {
                    siz = Tilwin_Checked_Good_Max_Size( winp, good );
                    Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
                    siz.height = Tilwin_Get_Size(winp).height;
                    Tilwin_Enlarge_Nearest( winp, center, siz );
                }
            }
        }
    
        center.x = Tilwin_Get_Desktop_Rectangle().left_x;
        thread_head = Tilwin_Thread_Horizly_Nearest( center ); 

        good = (float)(iter) / (float)(FILL_ITERS);

        for ( winp = thread_head;  winp != WIN_NULL;  
              winp = (Tilwinp)Tilwin_Get_Data(winp) )
        {
            if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
                Tilwin_Slide_Horizly_Nearest( winp, center );
            {
                if (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) )
                {
                    siz = Tilwin_Checked_Good_Max_Size( winp, good );
                    Set_Max_Size( siz, siz, Tilwin_Get_Size(winp) );
                    siz.height = Tilwin_Get_Size(winp).height;
                    Tilwin_Enlarge_Nearest( winp, center, siz );
                }
            }
        }
    }

    center.x = Tilwin_Get_Desktop_Rectangle().right_x;
    thread_head = Tilwin_Thread_Horizly_Nearest( center ); 

    for ( winp = thread_head;  winp != WIN_NULL;  
          winp = (Tilwinp)Tilwin_Get_Data(winp) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
            Tilwin_Slide_Horizly_Nearest( winp,
                Tilwin_Get_Position( winp ) );
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Fair_Desire()
{
    Manage_Fair_Vertical_Desire();
    Manage_Fair_Horizontal_Desire();
    Manage_All_Previous();
    Manage_Slide_Desire();
    Manage_All_Previous();
}

/* ------------------------------------------------------------ */

static void Manage_Fair_Maximize()
{
    Manage_Fair_Vertical_Maximize();
    Manage_Fair_Horizontal_Maximize();
    Manage_Slide_Maximize();
}

/* ------------------------------------------------------------ */

static void Manage_Fair_Prorate()
{
    Manage_Slide_Nearest();

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
            global_excursion( ENABLE_GRAVITY, FALSE,
    {
        Manage_Fair_Desire();
    } ) ) )
}

/* ------------------------------------------------------------ */

static void Manage_Fair_Fill()
{
    Manage_Slide_Nearest();

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
            global_excursion( ENABLE_GRAVITY, FALSE,
    {
        Manage_Fair_Maximize();
    } ) ) )
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Manage_Careful_Desire( uwinp )
    Userwin *uwinp;
{
    Size siz;
    float good;
    int i;

    for ( i = 1; i <= DESIRE_ITERS; i++ )
    {    
        good = (float)(i) / (float)DESIRE_ITERS;
    
        if  ( (! Tilwin_Get_Window_Option( uwinp->winp, 
                     FIXED_COMPLETELY ) )
           || (! Tilwin_Get_Window_Option( uwinp->winp, 
                     FIXED_SIZE ) ) )
        {
            siz = Tilwin_Checked_Good_Desired_Size( uwinp->winp, good );
            Set_Max_Size( siz, siz, Tilwin_Get_Size(uwinp->winp) );
            Tilwin_Enlarge_Nearest( uwinp->winp,
                Tilwin_Get_Position(uwinp->winp), siz );
        }
    }
}

/* ------------------------------------------------------------ */

static void Manage_Plow_Desire( uwinp )
    Userwin *uwinp;
{
    TWPoint pt;

    if ( Tilwin_Get_Window_Option( uwinp->winp, FIXED_COMPLETELY ) ||
         Tilwin_Get_Window_Option( uwinp->winp, FIXED_SIZE ) )
        return;

    pt = Tilwin_Get_Center( uwinp->winp );
    Tilwin_Close( uwinp->winp );

    Manage_Start_Plow( Tilwin_Get_Rectangle( uwinp->winp ),
                       pt );

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
    {
        Tilwin_Open( uwinp->winp, pt, Tilwin_Get_Size(uwinp->winp) );
        Manage_Careful_Desire( uwinp );
    } ) )

    Manage_Finish_Plow();

}

/* ------------------------------------------------------------ */

static void Manage_Careful_Maximize( uwinp )
    Userwin *uwinp;
{
    Size siz;
    float good;
    int i;

    for ( i = 1; i <= MAXIMIZE_ITERS; i++ )
    {    
        good = (float)(i) / (float)MAXIMIZE_ITERS;
    
        if  ( (! Tilwin_Get_Window_Option( uwinp->winp, 
                     FIXED_COMPLETELY ) )
           || (! Tilwin_Get_Window_Option( uwinp->winp, 
                     FIXED_SIZE ) ) )
        {
            siz = Tilwin_Checked_Good_Max_Size( uwinp->winp, good );
            Set_Max_Size( siz, siz, Tilwin_Get_Size(uwinp->winp) );
            Tilwin_Enlarge_Nearest( uwinp->winp,
                Tilwin_Get_Position(uwinp->winp), siz );
        }
    }
}

/* ------------------------------------------------------------ */

static void Manage_Plow_Maximize( uwinp )
    Userwin *uwinp;
{
    TWPoint pt;

    if ( Tilwin_Get_Window_Option( uwinp->winp, FIXED_COMPLETELY ) ||
         Tilwin_Get_Window_Option( uwinp->winp, FIXED_SIZE ) )
        return;

    pt = Tilwin_Get_Center( uwinp->winp );
    Tilwin_Close( uwinp->winp );

    Manage_Start_Plow( Tilwin_Get_Rectangle( uwinp->winp ),
                       pt );

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
    {
        Tilwin_Open( uwinp->winp, pt, Tilwin_Get_Size(uwinp->winp) );
        Manage_Careful_Desire( uwinp );
        Manage_Careful_Maximize( uwinp );
    } ) )

    Manage_Finish_Plow();

}

/* ------------------------------------------------------------ */

void Manage_Shrink( uwinp )
    Userwin *uwinp;
{
    if ( Tilwin_Get_Window_Option( uwinp->winp, FIXED_COMPLETELY ) ||
         Tilwin_Get_Window_Option( uwinp->winp, FIXED_SIZE ) )
        return;

    Manage_Start();
    
    Tilwin_Set_Size( uwinp->winp,
        Tilwin_Checked_Min_Size( uwinp->winp ) );

    Manage_Finish_Fixed_Size( uwinp, TRUE );
}

/* ------------------------------------------------------------ */

void Manage_Contract( uwinp )
    Userwin *uwinp;
{
    if ( Tilwin_Get_Window_Option( uwinp->winp, FIXED_COMPLETELY ) ||
         Tilwin_Get_Window_Option( uwinp->winp, FIXED_SIZE ) )
        return;

    Manage_Start();
    Manage_Save_State( uwinp );
    
    Tilwin_Set_Size( uwinp->winp,
        Tilwin_Checked_Min_Size( uwinp->winp ) );

    Tilwin_Set_Desired( uwinp->winp, Tilwin_Get_Size( uwinp->winp ) );
    Tilwin_Note_Desired_Width( uwinp->winp );
    Tilwin_Note_Desired_Height( uwinp->winp );

    Manage_Finish_Fixed_Size( uwinp, TRUE );
}

/* ------------------------------------------------------------ */

void Manage_Expand( uwinp )
    Userwin *uwinp;
{
    if ( Tilwin_Get_Window_Option( uwinp->winp, FIXED_COMPLETELY ) ||
         Tilwin_Get_Window_Option( uwinp->winp, FIXED_SIZE ) )
        return;

    Manage_Start();
    Manage_Save_State( uwinp );

    global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
        global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
            Tilwin_Enlarge_Nearest( uwinp->winp,
                Tilwin_Get_Position(uwinp->winp),
                Tilwin_Checked_Max_Size(uwinp->winp) ) ) )

    Tilwin_Set_Desired( uwinp->winp, Tilwin_Get_Size( uwinp->winp ) );
    Tilwin_Note_Desired_Width( uwinp->winp );
    Tilwin_Note_Desired_Height( uwinp->winp );

    Manage_Finish_Fixed_Size( uwinp, TRUE );
}

/* ------------------------------------------------------------ */

void Manage_Enlarge( uwinp )
    Userwin *uwinp;
{
    Manage_Start();
    
    Manage_Plow_Maximize( uwinp );

    Manage_Finish_Minned( uwinp, TRUE );
}

/* ------------------------------------------------------------ */

void Manage_Desire( uwinp )
    Userwin *uwinp;
{
    Manage_Start();
    
    Manage_Plow_Desire( uwinp );

    Tilwin_Note_Desired_Width( uwinp->winp );
    Tilwin_Note_Desired_Height( uwinp->winp );

    Manage_Finish_Minned( uwinp, TRUE );
}

/* ------------------------------------------------------------ */

static void Manage_Biased_Prorate()
{
    if ( (listener != UWIN_NULL) && Userwin_Is_Open(listener) )
    {
        Manage_Plow_Maximize( listener );
        window_excursion( listener->winp, FIXED_COMPLETELY, TRUE,
            Manage_Local_Prorate() )
        global_excursion( ALLOW_AUTOMATIC_CLOSE, FALSE,
            global_excursion( ALLOW_AUTOMATIC_SHRINK, FALSE,
                Manage_Careful_Maximize( listener ) ) )
    }
    else
        Manage_Fair_Prorate();
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Manage_Fill()
{
    auto_prorate = FALSE;
    Manage_Start();
    Manage_Fair_Fill();
    user_global_excursion( AUTO_PRORATE, FALSE,
        Manage_Finish( TRUE ) )
    auto_prorate = TRUE;
}

/* ------------------------------------------------------------ */

void Manage_Prorate()
{
    auto_prorate = FALSE;
    Manage_Start();
    Manage_Fair_Prorate();
    user_global_excursion( AUTO_PRORATE, FALSE,
        Manage_Finish( TRUE ) )
    auto_prorate = TRUE;
}

/* ------------------------------------------------------------ */

void Manage_Auto_Prorate()
{
    if ( UserGlobals_Get_Option(BIASED_AUTO_PRORATE) )
        Manage_Biased_Prorate();
    else
        Manage_Fair_Prorate();
}
