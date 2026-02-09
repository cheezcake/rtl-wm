#ifndef lint
static char sccs_id[] = "@(#)tilemenu.c 5.2  6/5/89";
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

    
#include <stdio.h>
    
#include "basetype.h"
#include "buttonsP.h"
#include "rtlmenuX.h"
    
#include "current.h"
    
#include <X11/Xlib.h>
    
#define DEFAULT_MENU_MASK (RTLMenuOptionsMask)0x0b /* clockokay, savebits, rightoffset */

extern Display *dpy;
extern int scrn;
    
static bool initialized = FALSE;
    

/* ------------------------------------------------------------ */
TileMenu TileMenu_Create()
{
    if (!initialized)
    {
	initialized = TRUE;
	RTLMenu_Initialize(dpy, scrn, DEFAULT_MENU_MASK);
    }   
    return (TileMenu) RTLMenu_Create();
    
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*ARGSUSED*/
pointer TileMenu_Data( menu, item )
    TileMenu menu;
    TileMenuItem item;
{
    generic g;

    g = RTLMenu_Data((RTLMenuItem)item);
    return GetGenPointer(g);
}

/* ------------------------------------------------------------ */

TileMenu TileMenu_Get_Submenu( menu, str )
    TileMenu menu;
    char *str;
{
    return RTLMenu_Get_Submenu((RTLMenu)menu, str);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

TileMenuItem TileMenu_Append_String( menu, str, strval )
    TileMenu menu;
    char *str;
    char *strval;
{
    generic g;
    
    SetGenPointer(g,strval);

    return (TileMenuItem)
	RTLMenu_Append_String((RTLMenu)menu, str, g);
}

/* ------------------------------------------------------------ */

TileMenuItem TileMenu_Append_Callback( menu, backproc )
    TileMenu menu;
    VoidFunc backproc;
{
    return (TileMenuItem)
	RTLMenu_Append_Callback((RTLMenu)menu, backproc);
}

/* ------------------------------------------------------------ */

TileMenuItem TileMenu_Append_Call( menu, str, proc, ptrval )
    TileMenu menu;
    char *str;
    VoidFunc proc;
    pointer ptrval;
{
    generic g;
    
    SetGenPointer(g,ptrval);

    return (TileMenuItem)
	RTLMenu_Append_Call((RTLMenu)menu, str, proc, g);
}

/* ------------------------------------------------------------ */

TileMenuItem TileMenu_Append_Checkback( menu, str, checkproc, proc )
    TileMenu menu;
    char *str;   /* Menu string */
    BoolFunc checkproc;  /* Boolean function called when menu entry
			    is about to be displayed.  If true, then
			    the item appears checked; if false, then
			    it does not */
    VoidFunc proc;  /* function to be called when the item 
		       is selected */
{
    generic g;
    
    SetGenPointer(g,NULL);
    
    return (TileMenuItem)
	RTLMenu_Append_Checkback((RTLMenu)menu, str, checkproc, proc, g);

}
/* ------------------------------------------------------------ */

TileMenuItem TileMenu_Append_Submenu( menu, str, submenu )
    TileMenu menu;
    char *str;
    TileMenu submenu;
{
    return (TileMenuItem)
	RTLMenu_Append_Submenu((RTLMenu)menu, str, (RTLMenu)submenu);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void TileMenu_Replace_Data_By_String( menu, data, str )
    TileMenu menu;
    pointer data;
    char *str;
{
    generic g;
    
    SetGenPointer(g, data);
    
    RTLMenu_Replace_Data_By_String((RTLMenu)menu, g, str);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void TileMenu_Activate_Entry( menu, item )
    TileMenu menu;
    TileMenuItem item;
{
    RTLMenu_Activate_Entry((RTLMenu)menu, (RTLMenuItem)item);
}

/* ------------------------------------------------------------ */    

void TileMenu_Inactivate_Entry( menu, item )
    TileMenu menu;
    TileMenuItem item;
{
    RTLMenu_Inactivate_Entry((RTLMenu)menu, (RTLMenuItem)item);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

bool TileMenu_Has_Data( menu, val )
    TileMenu menu;
    pointer val;
{
    generic g;
    
    SetGenPointer(g,val);

    return RTLMenu_Has_Data((RTLMenu)menu, g);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void TileMenu_Delete_Entries( menu )
    TileMenu menu;
{
    RTLMenu_Delete_Entries((RTLMenu)menu);
}

/* ------------------------------------------------------------ */

void TileMenu_Delete_String( menu, str )
    TileMenu menu;
    char *str;
{
    RTLMenu_Delete_String((RTLMenu)menu, str);
}

/* ------------------------------------------------------------ */

void TileMenu_Delete_Data( menu, val )
    TileMenu menu;
    pointer val;
{
    generic g;
    
    SetGenPointer(g, val);
    
    RTLMenu_Delete_Data((RTLMenu)menu, g);
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*ARGSUSED*/
void TileMenu_Box( menu )
    TileMenu menu;
{
    /* Commented out */
}

/* ------------------------------------------------------------ */

/*ARGSUSED*/
void TileMenu_Enter( menu, butnum, kind, buttime )
    TileMenu menu;
    int butnum;
    enum ButKind kind;
    Time buttime;
{
    RTLPoint pos;
    
    pos.x = current_pos.x;
    pos.y = current_pos.y;
    RTLMenu_Enter((RTLMenu)menu, (unsigned int)butnum, buttime,
		  RootWindow(dpy, scrn), pos);
    XSync(dpy,0);
}
/* ------------------------------------------------------------ */

TWPoint TileMenu_Entry_Pos()
{
    RTLPoint pos; 
    TWPoint return_pos;

    pos = RTLMenu_Entry_Pos();
    return_pos.x = pos.x;
    return_pos.y = pos.y;

    return return_pos;
}

