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

#include "uwinD.h"

#include "region.h"

bool user_defaults[(int)LENGTH_USER_WINDOW_OPTIONS];

/* ------------------------------------------------------------ */

void Userwin_Setup_Sizes( uwinp )
    Userwin *uwinp;
{
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
}

/* ------------------------------------------------------------ */

void Userwin_Followup_Sizes( uwinp )
    Userwin *uwinp;
{
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
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Userwin_Enforce_Client_Min( uwinp )
    Userwin *uwinp;
{
    Size max_size;

    if ( Userwin_Get_Window_Option( uwinp,
             ENFORCE_CLIENT_MINIMUMS ) )
    {    
        Set_Max_Size( uwinp->regular_min, uwinp->regular_min, 
                      uwinp->client_min )
        Set_Max_Size( uwinp->regular_size, uwinp->regular_size, 
                      uwinp->client_min )
        Set_Max_Size( uwinp->zoom_min, uwinp->zoom_min, 
                      uwinp->client_min )
        Set_Max_Size( uwinp->zoom_size, uwinp->zoom_size, 
                      uwinp->client_min )
        Set_Max_Size( max_size, Tilwin_Get_Max( uwinp->winp ),
                      uwinp->client_min )
        Tilwin_Set_Max( uwinp->winp, max_size );
    }
}

/* ------------------------------------------------------------ */

void Userwin_Enforce_Client_Max( uwinp )
    Userwin *uwinp;
{
    Size max_size;

    if ( Userwin_Get_Window_Option( uwinp,
             ENFORCE_CLIENT_MAXIMUMS ) )
    {    
        Set_Min_Size( max_size, Tilwin_Get_Max( uwinp->winp ),
                      uwinp->client_max )
        Tilwin_Set_Max( uwinp->winp, max_size );
        Set_Min_Size( uwinp->regular_size, uwinp->regular_size, 
                      uwinp->client_max )
        Set_Min_Size( uwinp->regular_min, uwinp->regular_min, 
                      uwinp->client_max )
        Set_Min_Size( uwinp->zoom_size, uwinp->zoom_size, 
                      uwinp->client_max )
        Set_Min_Size( uwinp->zoom_min, uwinp->zoom_min, 
                      uwinp->client_max )
    }
}

/* ------------------------------------------------------------ */

void Userwin_Enforce_Client_Sizes( uwinp )
    Userwin *uwinp;
{
    Userwin_Enforce_Client_Max( uwinp );
    Userwin_Enforce_Client_Min( uwinp );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Userwin_Client_Min_Max( uwinp )
    Userwin *uwinp;
{
    Size siz;

    uwinp->client_max =
        Region_Adjust_Size( uwinp, uwinp->body_max );
    uwinp->client_min =
        Region_Adjust_Size( uwinp, uwinp->body_min );

    siz.width = UserGlobals_Get_Value( FULL_WIDTH );
    siz.height = UserGlobals_Get_Value( FULL_HEIGHT );
    Set_Min_Size( uwinp->client_max, 
                  uwinp->client_max, siz );

    siz.width = UserGlobals_Get_Value( ABS_MIN_WIDTH );
    siz.height = UserGlobals_Get_Value( ABS_MIN_HEIGHT );
    Set_Max_Size( uwinp->client_min, 
                  uwinp->client_min, siz );

    Set_Max_Size( uwinp->client_max,
                  uwinp->client_max, uwinp->client_min );
}

/* ------------------------------------------------------------ */

void Userwin_Body_Min( uwinp )
    Userwin *uwinp;
{
    Userwin_Client_Min_Max( uwinp );

    Set_Max_Size( uwinp->client_max,
                  uwinp->client_max, uwinp->client_min );
}

/* ------------------------------------------------------------ */

void Userwin_Body_Max( uwinp )
    Userwin *uwinp;
{
    Userwin_Client_Min_Max( uwinp );

    Set_Min_Size( uwinp->client_min,
                  uwinp->client_min, uwinp->client_max );
}

/* ------------------------------------------------------------ */

void Userwin_Body_Min_Max( uwinp )
    Userwin *uwinp;
{
    Userwin_Client_Min_Max( uwinp );

    Set_Max_Size( uwinp->client_max,
                  uwinp->client_max, uwinp->client_min );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Userwin_Check_Sizes( uwinp )
    Userwin *uwinp;
{
    Size max_size;

    Set_Max_Size( max_size, uwinp->regular_min, uwinp->zoom_min );
    Set_Max_Size( max_size, max_size, Tilwin_Get_Max( uwinp->winp ) );
    Tilwin_Set_Max( uwinp->winp, max_size );

    Set_Max_Size( uwinp->regular_size, uwinp->regular_size, 
                  uwinp->regular_min );
    Set_Min_Size( uwinp->regular_size, uwinp->regular_size, 
                  max_size );

    Set_Max_Size( uwinp->zoom_min, uwinp->zoom_min, uwinp->regular_min );
    Set_Max_Size( uwinp->zoom_size, uwinp->zoom_size, uwinp->regular_size );

    Set_Max_Size( uwinp->zoom_size, uwinp->zoom_size, uwinp->zoom_min );
    Set_Min_Size( uwinp->zoom_size, uwinp->zoom_size, max_size );
}

/* ------------------------------------------------------------ */

void Userwin_Bound_Size( uwinp )
    Userwin *uwinp;
{
    Size siz;

    siz = Tilwin_Get_Size( uwinp->winp );
    Set_Min_Size( siz, siz, Tilwin_Get_Max(uwinp->winp) );
    Set_Max_Size( siz, siz, Tilwin_Get_Min(uwinp->winp) );
    Tilwin_Set_Size( uwinp->winp, siz );
}
