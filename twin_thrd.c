#ifndef lint
static char sccs_id[] = "@(#)twin_thrd.c	5.3  9/1/88";
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

#include "state.h"

/* ------------------------------------------------------------ */

#define Dist(pt1,pt2) \
    ( ( ((pt1).x - (pt2).x)*((pt1).x - (pt2).x) ) +  \
      ( ((pt1).y - (pt2).y)*((pt1).y - (pt2).y) ) )

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Thread_Nearest( pt )
    TWPoint pt;
{
    Tilwin *head, *winp, *prev, *cur;
    WinpHandle handle;
    int dist;

    head = WINP_NULL;

    handle = State_Gen_Open_Windows();
    while ( (winp = State_Coerce(handle)) != WINP_NULL )
    {
        dist = Dist( pt, winp->center );

        prev = WINP_NULL;
        cur = head;  
        while ( ( cur != WINP_NULL ) &&
                ( dist > Dist( pt, cur->center ) ) )
        {
            prev = cur;
            cur = (Tilwin *)Tilwin_Get_Data(cur);
        }

        Tilwin_Put_Data( winp, cur );
        if ( prev == WINP_NULL )
            head = winp;
        else
            Tilwin_Put_Data( prev, winp );

        State_Next_Window(&handle);
    }
    return (Tilwinp)head;
    
}

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Thread_Vertly_Nearest( pt )
    TWPoint pt;
{
    Tilwin *head, *winp, *prev, *cur;
    WinpHandle handle;
    int dist;

    head = WINP_NULL;

    handle = State_Gen_Open_Windows();
    while ( (winp = State_Coerce(handle)) != WINP_NULL )
    {
        dist = ABS( pt.y - winp->center.y );

        prev = WINP_NULL;
        cur = head;  
        while ( ( cur != WINP_NULL ) &&
                ( dist > ABS( pt.y - cur->center.y ) ) )
        {
            prev = cur;
            cur = (Tilwin *)Tilwin_Get_Data(cur);
        }

        Tilwin_Put_Data( winp, cur );
        if ( prev == WINP_NULL )
            head = winp;
        else
            Tilwin_Put_Data( prev, winp );

        State_Next_Window(&handle);
    }
    return (Tilwinp)head;
    
}

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Thread_Horizly_Nearest( pt )
    TWPoint pt;
{
    Tilwin *head, *winp, *prev, *cur;
    WinpHandle handle;
    int dist;

    head = WINP_NULL;

    handle = State_Gen_Open_Windows();
    while ( (winp = State_Coerce(handle)) != WINP_NULL )
    {
        dist = ABS( pt.x - winp->center.x );

        prev = WINP_NULL;
        cur = head;  
        while ( ( cur != WINP_NULL ) &&
                ( dist > ABS( pt.x - cur->center.x ) ) )
        {
            prev = cur;
            cur = (Tilwin *)Tilwin_Get_Data(cur);
        }

        Tilwin_Put_Data( winp, cur );
        if ( prev == WINP_NULL )
            head = winp;
        else
            Tilwin_Put_Data( prev, winp );

        State_Next_Window(&handle);
    }
    return (Tilwinp)head;
    
}

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Thread_Farthest( pt )
    TWPoint pt;
{
    Tilwin *head, *winp, *prev, *cur;
    WinpHandle handle;
    int dist;

    head = WINP_NULL;

    handle = State_Gen_Open_Windows();
    while ( (winp = State_Coerce(handle)) != WINP_NULL )
    {
        dist = Dist( pt, winp->center );

        prev = WINP_NULL;
        cur = head;  
        while ( ( cur != WINP_NULL ) &&
                ( dist < Dist( pt, cur->center ) ) )
        {
            prev = cur;
            cur = (Tilwin *)Tilwin_Get_Data(cur);
        }

        Tilwin_Put_Data( winp, cur );
        if ( prev == WINP_NULL )
            head = winp;
        else
            Tilwin_Put_Data( prev, winp );

        State_Next_Window(&handle);
    }
    return (Tilwinp)head;
    
}

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Thread_Vertly_Farthest( pt )
    TWPoint pt;
{
    Tilwin *head, *winp, *prev, *cur;
    WinpHandle handle;
    int dist;

    head = WINP_NULL;

    handle = State_Gen_Open_Windows();
    while ( (winp = State_Coerce(handle)) != WINP_NULL )
    {
        dist = ABS( pt.y - winp->center.y );

        prev = WINP_NULL;
        cur = head;  
        while ( ( cur != WINP_NULL ) &&
                ( dist < ABS( pt.y - cur->center.y ) ) )
        {
            prev = cur;
            cur = (Tilwin *)Tilwin_Get_Data(cur);
        }

        Tilwin_Put_Data( winp, cur );
        if ( prev == WINP_NULL )
            head = winp;
        else
            Tilwin_Put_Data( prev, winp );

        State_Next_Window(&handle);
    }
    return (Tilwinp)head;
    
}

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Thread_Horizly_Farthest( pt )
    TWPoint pt;
{
    Tilwin *head, *winp, *prev, *cur;
    WinpHandle handle;
    int dist;

    head = WINP_NULL;

    handle = State_Gen_Open_Windows();
    while ( (winp = State_Coerce(handle)) != WINP_NULL )
    {
        dist = ABS( pt.x - winp->center.x );

        prev = WINP_NULL;
        cur = head;  
        while ( ( cur != WINP_NULL ) &&
                ( dist < ABS( pt.x - cur->center.x ) ) )
        {
            prev = cur;
            cur = (Tilwin *)Tilwin_Get_Data(cur);
        }

        Tilwin_Put_Data( winp, cur );
        if ( prev == WINP_NULL )
            head = winp;
        else
            Tilwin_Put_Data( prev, winp );

        State_Next_Window(&handle);
    }
    return (Tilwinp)head;
    
}

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Thread_Nearest_Position()
{
    Tilwin *head, *winp, *prev, *cur;
    WinpHandle handle;
    int dist;

    head = WINP_NULL;

    handle = State_Gen_Open_Windows();
    while ( (winp = State_Coerce(handle)) != WINP_NULL )
    {
        dist = Dist( winp->position, winp->center );

        prev = WINP_NULL;
        cur = head;  
        while ( ( cur != WINP_NULL ) &&
                ( dist > Dist( cur->position, cur->center ) ) )
        {
            prev = cur;
            cur = (Tilwin *)Tilwin_Get_Data(cur);
        }

        Tilwin_Put_Data( winp, cur );
        if ( prev == WINP_NULL )
            head = winp;
        else
            Tilwin_Put_Data( prev, winp );

        State_Next_Window(&handle);
    }
    return (Tilwinp)head;
    
}

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Reverse_Thread( head )
    Tilwinp head;
{
    Tilwin *prev, *cur, *next;
    
    prev = WINP_NULL;
    cur = (Tilwin *)head;  
    while ( cur != WINP_NULL )
    {
        next = (Tilwin *)Tilwin_Get_Data( cur );
        Tilwin_Put_Data( cur, prev );
        prev = cur;
        cur = next;
    }
    return (Tilwinp)prev;   
}

