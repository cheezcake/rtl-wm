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

#include "uwinP.h"

#include "tilemenu.h"

static TileMenu manager_menu;
static TileMenuItem closed_menu_entry;
static TileMenu closed_menu;
static int num_closed;
static VoidFunc callproc;

/* ------------------------------------------------------------ */

TileMenu Closed_Init( menu, proc )
    TileMenu menu;
    VoidFunc proc;
{
    manager_menu = menu;
    closed_menu = TileMenu_Create();
    TileMenu_Box( closed_menu );
    closed_menu_entry = TileMenu_Append_Submenu( 
        manager_menu, "Closed Windows", closed_menu );
    num_closed = 0;    
    TileMenu_Inactivate_Entry( manager_menu, closed_menu_entry );
    callproc = proc;
    return closed_menu;
}

/* ------------------------------------------------------------ */

void Closed_Retitle( uwinp )
    Userwin *uwinp;
{
    TileMenu_Replace_Data_By_String( 
        closed_menu, uwinp, uwinp->title );
}

/* ------------------------------------------------------------ */

void Closed_Add( uwinp )
    Userwin *uwinp;
{
    TileMenu_Append_Call( closed_menu, 
        uwinp->title, callproc, uwinp );    
    if ( (num_closed++) == 0 ) 
        TileMenu_Activate_Entry( manager_menu, closed_menu_entry );
}

/* ------------------------------------------------------------ */

void Closed_Remove( uwinp )
    Userwin *uwinp;
{
    if ( TileMenu_Has_Data( closed_menu, uwinp ) )
    {
        TileMenu_Delete_Data( closed_menu, uwinp );
        if ( (--num_closed) == 0 ) 
            TileMenu_Inactivate_Entry( manager_menu, closed_menu_entry );
    }
}    
