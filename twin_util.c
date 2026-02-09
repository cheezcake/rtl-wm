#ifndef lint
static char sccs_id[] = "@(#)twin_util.c	5.3  9/1/88";
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

#include "twin.h"
#include "twinD.h"

/* ------------------------------------------------------------ */

TWPoint Tilwin_Center_Of_Gravity()
{
    TWPoint center;
    Tilwinp winp;
    int knt = 0;

    center.x = 0;
    center.y = 0;

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        center.x += Tilwin_Get_Center(winp).x;  
        center.y += Tilwin_Get_Center(winp).y;  
        knt++;
    }

    if ( knt == 0 )
        return Tilwin_Get_Desktop_Center();

    center.x = center.x / knt;
    center.y = center.y / knt;
    
    return center;
}

/* ------------------------------------------------------------ */

TWPoint Tilwin_Position_Ctr_Of_Gravity()
{
    TWPoint center;
    Tilwinp winp;
    int knt = 0;

    center.x = 0;
    center.y = 0;

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        center.x += Tilwin_Get_Position(winp).x;  
        center.y += Tilwin_Get_Position(winp).y;  
        knt++;
    }

    if ( knt == 0 )
        return Tilwin_Get_Desktop_Center();

    center.x = center.x / knt;
    center.y = center.y / knt;
    
    return center;
}

/* ------------------------------------------------------------ */

Size Tilwin_Checked_Size( winp, chksiz )
    Tilwinp winp;
    Size chksiz;
{
    Size siz;
    siz = Tilwin_Get_Size( winp );
    if  ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
       && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) )
            siz.width = chksiz.width;
        if (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) )
            siz.height = chksiz.height;
    }
    return siz;
}

/* ------------------------------------------------------------ */

Size Tilwin_Checked_Previous_Size( winp )
    Tilwinp winp;
{
    Size siz;
    siz = Tilwin_Get_Size( winp );
    if  ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
       && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) )
            siz.width = Tilwin_Get_Previous_Size(winp).width;
        if (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) )
            siz.height = Tilwin_Get_Previous_Size(winp).height;
    }
    return siz;
}

/* ------------------------------------------------------------ */

Size Tilwin_Good_Size( winp, siz )
    Tilwinp winp;
    Size siz;
{
    Size desired, minsiz;
    float gwidth, gheight;

    siz = Tilwin_Get_Size( winp );
    if  ( Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY )
       || Tilwin_Get_Window_Option( winp, FIXED_SIZE ) )
        return siz;

    desired = Tilwin_Get_Desired(winp);
    minsiz = Tilwin_Get_Min(winp);
    
    if ( desired.width == minsiz.width )
        gwidth = 1;
    else
        gwidth = ( siz.width - minsiz.width ) /
                 ( desired.width - minsiz.width );
    
    if ( desired.height == minsiz.height )
        gheight = 1;
    else
        gheight = ( siz.height - minsiz.height ) /
                 ( desired.height - minsiz.height );

    if ( gwidth < gheight )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) )
            siz.height = minsiz.height +
                gwidth * ( desired.height - minsiz.height );
    }
    else if ( gwidth > gheight )    
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) )
            siz.width = minsiz.width +
                gheight * ( desired.width - minsiz.width );
    }

    return siz;
}

/* ------------------------------------------------------------ */

Size Tilwin_Checked_Min_Size( winp )
    Tilwinp winp;
{
    Size siz;
    siz = Tilwin_Get_Size( winp );
    if  ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
       && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) )
            siz.width = Tilwin_Get_Min(winp).width;
        if (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) )
            siz.height = Tilwin_Get_Min(winp).height;
    }
    return siz;
}

/* ------------------------------------------------------------ */

Size Tilwin_Checked_Desired_Size( winp )
    Tilwinp winp;
{
    Size siz;
    siz = Tilwin_Get_Size( winp );
    if  ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
       && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) )
            siz.width = Tilwin_Get_Desired(winp).width;
        if (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) )
            siz.height = Tilwin_Get_Desired(winp).height;
    }
    return siz;
}

/* ------------------------------------------------------------ */

Size Tilwin_Checked_Good_Desired_Size( winp, good )
    Tilwinp winp;
    float good;
{
    Size siz;
    siz = Tilwin_Get_Size( winp );
    if  ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
       && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) )
            siz.width =  good * Tilwin_Get_Desired(winp).width +
                      (1-good)* Tilwin_Get_Min(winp).width;
        if (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) )
            siz.height =  good * Tilwin_Get_Desired(winp).height +
                       (1-good)* Tilwin_Get_Min(winp).height;
    }
    return siz;
}

/* ------------------------------------------------------------ */

Size Tilwin_Checked_Max_Size( winp )
    Tilwinp winp;
{
    Size siz;
    siz = Tilwin_Get_Size( winp );
    if  ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
       && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) )
            siz.width = Tilwin_Get_Max( winp ).width;
        if (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) )
            siz.height = Tilwin_Get_Max( winp ).height;
    }
    return siz;
}

/* ------------------------------------------------------------ */

Size Tilwin_Checked_Good_Max_Size( winp, good )
    Tilwinp winp;
    float good;
{
    Size siz;
    siz = Tilwin_Get_Size( winp );
    if  ( (! Tilwin_Get_Window_Option( winp, FIXED_COMPLETELY ) )
       && (! Tilwin_Get_Window_Option( winp, FIXED_SIZE ) ) )
    {
        if (! Tilwin_Get_Window_Option( winp, FIXED_WIDTH ) )
            siz.width =  good * Tilwin_Get_Max(winp).width +
                      (1-good)* Tilwin_Get_Desired(winp).width;
        if (! Tilwin_Get_Window_Option( winp, FIXED_HEIGHT ) )
            siz.height =  good * Tilwin_Get_Max(winp).height +
                       (1-good)* Tilwin_Get_Desired(winp).height;
    }
    return siz;
}

/* ------------------------------------------------------------ */

void Tilwin_Slide_Vertly_Farthest( winp, pt )
    Tilwinp winp;
    TWPoint pt;
{
    TWPoint center;
    
    center = Tilwin_Get_Center(winp);
    pt.x = center.x;
    
    if ( center.y == pt.y )
        center.y = Tilwin_Get_Position(winp).y;

    if ( center.y < pt.y )
        pt.y = Tilwin_Get_Desktop_Rectangle().top_y;
    else
        pt.y = Tilwin_Get_Desktop_Rectangle().bottom_y;

    Tilwin_Slide_Nearest( winp, pt );
}

/* ------------------------------------------------------------ */

void Tilwin_Slide_Horizly_Farthest( winp, pt )
    Tilwinp winp;
    TWPoint pt;
{
    TWPoint center;
    
    center = Tilwin_Get_Center(winp);
    pt.y = center.y;
    
    if ( center.x == pt.x )
        center.x = Tilwin_Get_Position(winp).x;

    if ( center.x < pt.x )
        pt.x = Tilwin_Get_Desktop_Rectangle().left_x;
    else
        pt.x = Tilwin_Get_Desktop_Rectangle().right_x;

    Tilwin_Slide_Nearest( winp, pt );
}

/* ------------------------------------------------------------ */

void Tilwin_Slide_Vertly_Nearest( winp, pt )
    Tilwinp winp;
    TWPoint pt;
{
    pt.x = Tilwin_Get_Center(winp).x;
    Tilwin_Slide_Nearest( winp, pt );
}

/* ------------------------------------------------------------ */

void Tilwin_Slide_Horizly_Nearest( winp, pt )
    Tilwinp winp;
    TWPoint pt;
{
    pt.y = Tilwin_Get_Center(winp).y;
    Tilwin_Slide_Nearest( winp, pt );
}

