
/*  Copyright (c) 1987 Siemens Corporate Research and Support, Inc.
 *  All rights reserved.
 */
#ifndef lint
static char sccs_id[] = "@(#)pr.c	1.1 12/16/87  Copyright (c) 1987, Siemens Corporate Research and Support, Inc.";
#endif

#include <stdio.h>

#include "std_defs.h"
#include "basetype.h"
#include "twinD.h"
#include "stateP.h"
#include "uwinD.h"

/* ------------------------------------------------------------ */

static int prtitle( uwinp )
    Userwin *uwinp;
{
    char *uclass, *utitle;

    
    uclass = uwinp->window_class;
    utitle = uwinp->title;

    if ( (uclass == NULL) && (utitle == NULL) )
    {
        printf( "\n#0  RTL   ");
    }
    else
    {
        if ( uclass == NULL )
            uclass = "";
    
        if ( utitle == NULL )
            utitle = "";
    
        printf( "#%d   (%d)",
	       uwinp->winnum, (int)uwinp);

        printf( "%s: %s",
                uclass, utitle );
    }

    return 0;
    
}

/* ------------------------------------------------------------ */

static int pricon( uwinp )
    Userwin *uwinp;
{
    Tilwin *winp;



    winp = (Tilwin *)(uwinp->iconp);

    if ( Tilwin_Is_Open(winp) )
    {
        printf( "[ ICON ] topleft (%d,%d)",
	       winp->rect.left_x,
	       winp->rect.top_y);

        printf( "bottom right (%d,%d)",
	       winp->rect.right_x,
	       winp->rect.bottom_y);
	
        printf( "center @ (%d,%d)",
	       winp->center.x,
	       winp->center.y);
    }

    return 0;
    
}

/* ------------------------------------------------------------ */

static int prwin( uwinp )
    Userwin *uwinp;
{
    Tilwin *winp;



    winp = (Tilwin *)(uwinp->winp);

    printf( "[ %s ] %s",
	   (Tilwin_Is_Open(winp) ? "OPEN" : "CLOSED"),
	   (uwinp->zoomed ? " *ZOOMED* " : "" ));

    printf( "top left (%d,%d)",
	   winp->rect.left_x,
	   winp->rect.top_y);
    
    printf( "bottom right (%d,%d)",
	   winp->rect.right_x,
	   winp->rect.bottom_y);
    
    printf( "center @ (%d,%d)",
	   winp->center.x,
	   winp->center.y);

    return 0;
    
}

/* ------------------------------------------------------------ */

static int prinfo( uwinp )
    Userwin *uwinp;
{
    Tilwin *winp;


    
    winp = (Tilwin *)(uwinp->winp);

    printf( " size: [%d,%d]",
	   winp->size.width,
	   winp->size.height);

    printf( " max: [%d,%d]",
            winp->max_size.width,
            winp->max_size.height);


    printf( " min: [%d,%d]",
	   winp->min_size.width,
	   winp->min_size.height);

    printf( " desire: [%d,%d]",
            winp->desired_size.width,
            winp->desired_size.height);


    if ( uwinp->zoomed)
    {
	printf( " regular_min: [%d,%d]",
	       uwinp->regular_min.width,
	       uwinp->regular_min.height);

	printf( "  desire: [%d,%d]",
	       uwinp->regular_size.width,
	       uwinp->regular_size.height);
    }
    else
    {
	printf( " Zoom min: [%d,%d]",
	       uwinp->zoom_min.width,
	       uwinp->zoom_min.height);

	printf( "  desire: [%d,%d]",
	       uwinp->zoom_size.width,
	       uwinp->zoom_size.height);
    }

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



    handle = State_Generate_Closed_Windows();
    while ( (winp = (Tilwinp)State_Coerce(handle)) != WIN_NULL )
    {
        if ( Userwin_Get(winp)->winnum == num )
        {
            prw(winp);
            return;
        }
        State_Next_Window(&handle);
    }

    printf( "No such number..." );

    return 0;
    
}

/* ------------------------------------------------------------ */

int pro()
{
    Tilwinp winp;
    WinpHandle handle;
    Userwin *uwinp;
    handle = State_Generate_Open_Windows();
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
    handle = State_Generate_Open_Windows();
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
    handle = State_Generate_Closed_Windows();
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
