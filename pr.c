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
#include "twinD.h"
#include "state.h"
#include "uwinD.h"

/* ------------------------------------------------------------ */

static int prtitle( uwinp )
    Userwin *uwinp;
{
    char *uresclass, *uresname, *uhostname, *uname;

    uresclass = uwinp->res_class;
    uresname = uwinp->res_name;
    uhostname = uwinp->hostname;
    uname = uwinp->wmname;

    if ( (uresclass == NULL) && (uname == NULL) )
        printf( "\n#0  RTL   ");
    else
    {
        if ( uresclass == NULL )
            uresclass = "";

        if ( uresname == NULL )
            uresname = "";

        if ( uhostname == NULL )
            uhostname = "";
    
        if ( uname == NULL )
            uname = "";
    
        printf( "\n#%d   (%d)   %s: %s [%s]\n       %s\n",
                uwinp->winnum, (int)uwinp, 
                uresclass, uresname, uhostname, uname );
    }
}

/* ------------------------------------------------------------ */

static int pricon( uwinp )
    Userwin *uwinp;
{
    Tilwin *winp;
    winp = (Tilwin *)(uwinp->iconp);
    if ( Tilwin_Is_Open(winp) )
        printf( "   [ ICON ] (%d,%d)->(%d,%d)  @  (%d,%d) => (%d,%d)\n",
                winp->rect.left_x,
                winp->rect.top_y,
                winp->rect.right_x,
                winp->rect.bottom_y,
                winp->center.x,
                winp->center.y,
                winp->position.x,
                winp->position.y );
    return 0;
}

/* ------------------------------------------------------------ */

static int prwin( uwinp )
    Userwin *uwinp;
{
    Tilwin *winp;
    winp = (Tilwin *)(uwinp->winp);
    printf( "   [ %s ] %s (%d,%d)->(%d,%d)  @  (%d,%d) => (%d,%d)\n",
            (Tilwin_Is_Open(winp) ? "OPEN" : "CLOSED" ),
            (uwinp->zoomed ? " *ZOOMED* " : "" ),
            winp->rect.left_x,
            winp->rect.top_y,
            winp->rect.right_x,
            winp->rect.bottom_y,
            winp->center.x,
            winp->center.y,
            winp->position.x,
            winp->position.y );
    return 0;
}

/* ------------------------------------------------------------ */

static int prinfo( uwinp )
    Userwin *uwinp;
{
    Tilwin *winp;
    winp = (Tilwin *)(uwinp->winp);

    printf( "  size: [%d,%d]   max: [%d,%d]\n",
            winp->size.width,
            winp->size.height,
            winp->max_size.width,
            winp->max_size.height );

    printf( "   min: [%d,%d]   desire: [%d,%d]\n",
            winp->min_size.width,
            winp->min_size.height,
            winp->desired_size.width,
            winp->desired_size.height );

    if ( uwinp->zoomed)
        printf( "   regular  min: [%d,%d]   desire: [%d,%d]\n",
                uwinp->regular_min.width,
                uwinp->regular_min.height,
                uwinp->regular_size.width,
                uwinp->regular_size.height );
    else
        printf( "   ZOOM  min: [%d,%d]   desire: [%d,%d]\n",
                uwinp->zoom_min.width,
                uwinp->zoom_min.height,
                uwinp->zoom_size.width,
                uwinp->zoom_size.height );

    return 0;
}

/* ------------------------------------------------------------ */

int pru( uwinp )
    Userwin *uwinp;
{
    prtitle( uwinp );
    if ( uwinp->winp == WIN_NULL )
        pricon( uwinp );
    else if ( Tilwin_Is_Open( uwinp->winp ) )
    {
        prwin( uwinp );
        prinfo( uwinp );
        pricon( uwinp );
    }
    else
    {
        pricon( uwinp );
        prwin( uwinp );
        prinfo( uwinp );
    }
    return 0;
}

/* ------------------------------------------------------------ */

int prw( winp )
    Tilwinp winp;
{
    return pru( Userwin_Get(winp) );
}

/* ------------------------------------------------------------ */

int prn( num )
{
    Tilwinp winp;
    WinpHandle handle;
    handle = State_Gen_Closed_Windows();
    while ( (winp = (Tilwinp)State_Coerce(handle)) != WIN_NULL )
    {
        if ( Userwin_Get(winp)->winnum == num )
        {
            prw(winp);
            return 0;
        }
        State_Next_Window(&handle);
    }
    printf( "No such number\n" );
    return 0;
}

/* ------------------------------------------------------------ */

int pro()
{
    Tilwinp winp;
    WinpHandle handle;
    Userwin *uwinp;
    handle = State_Gen_Open_Windows();
    while ( (winp = (Tilwinp)State_Coerce(handle)) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->winp == winp )
        {
            prtitle( uwinp );
            prwin( uwinp );
            prinfo( uwinp );
        }
        State_Next_Window(&handle);
    }
    return 0;
}

/* ------------------------------------------------------------ */

int pri()
{
    Tilwinp winp;
    WinpHandle handle;
    Userwin *uwinp;
    handle = State_Gen_Open_Windows();
    while ( (winp = (Tilwinp)State_Coerce(handle)) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->iconp == winp )
        {
            prtitle( uwinp );
            pricon( uwinp );
        }
        State_Next_Window(&handle);
    }
    return 0;
}

/* ------------------------------------------------------------ */

int prc()
{
    Tilwinp winp;
    WinpHandle handle;
    Userwin *uwinp;
    handle = State_Gen_Closed_Windows();
    while ( (winp = (Tilwinp)State_Coerce(handle)) != WIN_NULL )
    {
        uwinp = Userwin_Get(winp);
        if ( uwinp->winp == winp )
        {
            prtitle( uwinp );
            pricon( uwinp );
        }
        State_Next_Window(&handle);
    }
    return 0;
}
