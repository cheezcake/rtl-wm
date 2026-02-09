/*
static char sccs_id[] = "@(#)uwinL.h	5.6  9/1/88";
*/

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
        
#ifndef USERWIN_DEFINE
#include "uwinD.h"
#endif

/* ------------------------------------------------------------ */

#define Userwin_Allows_Close(uwinp) \
    (! Tilwin_Get_Window_Option( (uwinp)->winp, REQUIRE_MANUAL_CLOSE ) )

#define Userwin_Dont_Close(uwinp) \
{ \
    Tilwin_Set_Window_Option( (uwinp)->winp, REQUIRE_MANUAL_CLOSE, TRUE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_REQUIRE_MANUAL_CLOSE ); \
    ( (uwinp)->regular_manual_close ) = TRUE; \
}

#define Userwin_Allow_Close(uwinp) \
{ \
    Tilwin_Set_Window_Option( (uwinp)->winp, REQUIRE_MANUAL_CLOSE, FALSE ); \
    (uwinp)->regular_manual_close = FALSE; \
    Explicit_Window_Set( uwinp, EXPLICIT_REQUIRE_MANUAL_CLOSE ); \
}

/* ------------------------------------------------------------ */

#define Userwin_Allows_Change_Size(uwinp) \
    (! Tilwin_Get_Window_Option( (uwinp)->winp, FIXED_SIZE ) )

#define Userwin_Dont_Change_Size(uwinp) \
{ \
    Tilwin_Set_Window_Option( (uwinp)->winp, FIXED_SIZE, TRUE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_FIXED_SIZE ); \
}

#define Userwin_Allow_Change_Size(uwinp) \
{ \
    Tilwin_Set_Window_Option( (uwinp)->winp, FIXED_SIZE, FALSE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_FIXED_SIZE ); \
}

/* ------------------------------------------------------------ */

#define Userwin_Allows_Change_Width(uwinp) \
    (! Tilwin_Get_Window_Option( (uwinp)->winp, FIXED_WIDTH ) )

#define Userwin_Dont_Change_Width(uwinp) \
{ \
    Tilwin_Set_Window_Option( (uwinp)->winp, FIXED_WIDTH, TRUE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_FIXED_WIDTH ); \
}

#define Userwin_Allow_Change_Width(uwinp) \
{ \
    Tilwin_Set_Window_Option( (uwinp)->winp, FIXED_WIDTH, FALSE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_FIXED_WIDTH ); \
}

/* ------------------------------------------------------------ */

#define Userwin_Allows_Change_Height(uwinp) \
    (! Tilwin_Get_Window_Option( (uwinp)->winp, FIXED_HEIGHT ) )

#define Userwin_Dont_Change_Height(uwinp) \
 { \
   Tilwin_Set_Window_Option( (uwinp)->winp, FIXED_HEIGHT, TRUE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_FIXED_HEIGHT ); \
}

#define Userwin_Allow_Change_Height(uwinp) \
{ \
    Tilwin_Set_Window_Option( (uwinp)->winp, FIXED_HEIGHT, FALSE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_FIXED_HEIGHT ); \
}

/* ------------------------------------------------------------ */

#define Userwin_Allows_Change(uwinp) \
    (! Tilwin_Get_Window_Option( (uwinp)->winp, FIXED_COMPLETELY ) )

#define Userwin_Dont_Change(uwinp) \
{ \
    Tilwin_Set_Window_Option( (uwinp)->winp, FIXED_COMPLETELY, TRUE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_FIXED_COMPLETELY ); \
}

#define Userwin_Allow_Change(uwinp) \
{ \
    Tilwin_Set_Window_Option( (uwinp)->winp, FIXED_COMPLETELY, FALSE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_FIXED_COMPLETELY ); \
}

/* ------------------------------------------------------------ */

#define Userwin_Tied_Listener(uwinp) \
    ( Userwin_Get_Window_Option( uwinp, LISTENER_TIED_TO_ZOOM ) )

#define Userwin_Dont_Tie_Listener(uwinp) \
{ \
    Userwin_Set_Window_Option( uwinp, LISTENER_TIED_TO_ZOOM, FALSE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_LISTENER_TIED_TO_ZOOM ); \
}

#define Userwin_Allow_Tie_Listener(uwinp) \
{ \
    Userwin_Set_Window_Option( uwinp, LISTENER_TIED_TO_ZOOM, TRUE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_LISTENER_TIED_TO_ZOOM ); \
}

/* ------------------------------------------------------------ */

#define Userwin_Tied_Desire(uwinp) \
    ( Userwin_Get_Window_Option( uwinp, ZOOM_TIED_TO_DESIRE ) )

#define Userwin_Dont_Tie_Desire(uwinp) \
{ \
    Userwin_Set_Window_Option( uwinp, ZOOM_TIED_TO_DESIRE, FALSE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_ZOOM_TIED_TO_DESIRE ); \
}

#define Userwin_Allow_Tie_Desire(uwinp) \
{ \
    Userwin_Set_Window_Option( uwinp, ZOOM_TIED_TO_DESIRE, TRUE ); \
    Explicit_Window_Set( uwinp, EXPLICIT_ZOOM_TIED_TO_DESIRE ); \
}

/* ------------------------------------------------------------ */
