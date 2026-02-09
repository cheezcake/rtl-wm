#ifndef lint
static char sccs_id[] = "%W%  %H%";
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

/* 
  RTL Menu Package Version 1.2
  by Joe Camaratta and Mike Berman, Siemens RTL, Princeton NJ, 1988

  rtlmenu.c: interface level for menu package
*/

#include <stdio.h>
#include <X11/Xlib.h>

#include "rtlmenuP.h"

static Display *dpy;
static int scrn;
    
static RTLPoint menu_pos;
static int initialized = 0;

extern bool SetItemText();
extern void InitMenu();
extern void DisposeMenu();
extern RTLMenu NewMenu();
extern RTLMenuItem MenuItemByName();
extern RTLMenuItem AddMenuItem();
extern RTLMenuItem MenuItemByData();
extern RTLMenuItem TrackMenu();
    
void 
RTLMenu_Initialize (display, screen, options_mask)
    Display *display;
    int screen;
    RTLMenuOptionsMask options_mask;
{

    if (initialized) return;
    dpy = display;
    scrn = screen;
    initialized = 1;
    InitMenu ("rtl", options_mask, display);
}

RTLMenu 
RTLMenu_Create()
{
    return (RTLMenu) NewMenu (dpy, scrn, FALSE);
}

void 
RTLMenu_Destroy( menu )
    RTLMenu menu;
{
    DisposeMenu (menu);
}

generic 
RTLMenu_Data( item )
    RTLMenuItem item;
{
    return ItemData(item);
}

RTLMenu 
RTLMenu_Get_Submenu( menu, str )
    RTLMenu menu;
    char *str;
{
    RTLMenuItem item = MenuItemByName (menu, str);

    if (!ItemIsNull(item))
	return (RTLMenu) ItemSubmenu(item);
    else
	return (RTLMenu)NULLMENU;
}

static void 
RTLMenu_Client_Send( item )
    RTLMenuItem item;
{
    printf ("RTLMenu_Client_Send not yet implemented for X, string = \"%s\"\n",
	    (char *) item);
}

RTLMenuItem 
RTLMenu_Append_String( menu, str, strval )
    RTLMenu menu;
    char *str;
    generic strval;
{
    RTLMenuItem item = AddMenuItem(menu);
    
    if (!ItemIsNull(item))
    {
	SetItemText(menu,item,str);
	ItemCallback(item) = (Callback)RTLMenu_Client_Send; 
	ItemData(item) = strval;
    }
    return (RTLMenuItem)item;
}

RTLMenuItem 
RTLMenu_Append_Callback( menu, backproc )
    RTLMenu menu;
    VoidFunc backproc;
{
    RTLMenuItem item = AddMenuItem(menu);
    
    if (!ItemIsNull(item))
    {
	ItemGenerator(item) = (Callback)backproc;
    }
    return (RTLMenuItem)item;
}

RTLMenuItem 
RTLMenu_Append_Call( menu, str, proc, data )
    RTLMenu menu;
    char *str;
    VoidFunc proc;
    generic data;
{
    RTLMenuItem item = AddMenuItem(menu);

    if (!ItemIsNull(item))
    {
	if (SetItemText(menu, item, str) == FALSE)
	    return NULLITEM;
	ItemCallback(item) = proc;
	ItemData(item) = data;
    }
    return (RTLMenuItem)item;
}

RTLMenuItem 
RTLMenu_Append_Checkback( menu, str, checkproc, proc, data )
    RTLMenu menu;
    char *str;	 /* Menu string */
    BoolFunc checkproc;	 /* Boolean function called when menu entry
			    is about to be displayed.  If true, then
			    the item appears checked; else no check */
    VoidFunc proc;  /* function to be called when the item selected */
    generic data; /* data associated with this item */
{
    RTLMenuItem item = AddMenuItem(menu);
    
    if (!ItemIsNull(item))
    {
	if (SetItemText(menu, item, str) == FALSE)
	    return(NULLITEM);
	ItemCallback(item) = proc;
	ItemData(item) = data;
	ItemCheckproc(item) = checkproc;
    }
    return (RTLMenuItem)item;
}

RTLMenuItem 
RTLMenu_Append_Submenu( menu, str, submenu )
    RTLMenu menu;
    char *str;
    RTLMenu submenu;
{
    RTLMenuItem item = AddMenuItem(menu);
    
    if (!ItemIsNull(item))
    {
	if (SetItemText(menu, item, str) == FALSE)
	    return(NULLITEM);
	SetItemSubmenu(item, submenu);
    }
    return (RTLMenuItem)item;
}

void 
RTLMenu_Replace_Data_By_String( menu, data, str )
    RTLMenu menu;
    generic data;
    char *str;
{
    RTLMenuItem item = MenuItemByName(menu, str);

    if (!ItemIsNull(item))
	ItemData(item) =  data;
} 

void 
RTLMenu_Activate_Entry( menu, item )
    RTLMenu menu;
    RTLMenuItem item;
{
    (void)SetItemDisable(menu, item, FALSE);
}

void 
RTLMenu_Inactivate_Entry( menu, item )
    RTLMenu menu;
    RTLMenuItem item;
{
    (void)SetItemDisable(menu, item, TRUE);
}

bool 
RTLMenu_Has_Data( menu, val )
    RTLMenu menu;
    generic val;
{
    RTLMenuItem item = MenuItemByData(menu, val);
    
    return (!ItemIsNull(item));
}

void 
RTLMenu_Delete_Entries( menu )
    RTLMenu menu;
{
    while (DisposeItem(menu, MenuItems(menu)));
}

void 
RTLMenu_Delete_String( menu, str )
    RTLMenu menu;
    char *str;
{
    RTLMenuItem item = MenuItemByName(menu, str);

    if (!ItemIsNull(item))
	(void) DisposeItem (menu, item);
}

void 
RTLMenu_Delete_Data( menu, val )
    RTLMenu menu;
    generic val;
{
    RTLMenuItem item = MenuItemByData(menu, val);

    if (!ItemIsNull(item))
	(void) DisposeItem(menu, item);

}

void 
RTLMenu_Enter( menu, butnum, buttime, base_window, pos )
    RTLMenu menu;
    unsigned int butnum;
    Time buttime;
    Window base_window;
    RTLPoint pos;
{
    RTLMenuItem selected;

    menu_pos = pos;
    if (TestOptionFlag(menu, savebits))
	XGrabServer(dpy);
    selected = TrackMenu (menu, menu_pos.x, menu_pos.y,
			   (int)butnum, base_window, buttime);
    if (TestOptionFlag(menu, savebits))
	XUngrabServer(dpy);
    if (!ItemIsNull(selected))
	(ItemCallback(selected)) (menu, selected);
}

RTLPoint 
RTLMenu_Entry_Pos()
{
    /* menu_pos is a global static that gets set by the call to */
    /* XQueryPointer that is used by the TrackMenu call.	*/
       
    return menu_pos;
}

void 
RTLMenu_Generate_Items(menu, proc)
    /* apply VoidFunc proc to each item in the menu, with	*/
    /* arguments menu and menuItem				*/
    RTLMenu menu;
    VoidFunc proc;
{
    RTLMenuItem item;

    for (item = MenuItems(menu);
	 !ItemIsNull(item); item = ItemNext(item))
    {
	(proc)(menu, item);
    }
    return;
}

RTLMenuItem 
RTLMenu_Append_Item(menu)
    RTLMenu menu;
{
    return (RTLMenuItem)AddMenuItem(menu);
}

void 
RTLMenu_Set_String(menu, item, menu_str)
    RTLMenu menu;
    RTLMenuItem item;
    char *menu_str;
{
    if (!ItemIsNull(item))
	(void) SetItemText(menu, item, menu_str);
}

void 
RTLMenu_Set_Generator(item, generator)
    RTLMenuItem item;
    VoidFunc generator;
{
    if (!ItemIsNull(item))
	ItemGenerator(item) = generator;
}

void 
RTLMenu_Set_Data(item, data)
    RTLMenuItem item;
    generic data;
{
    if (!ItemIsNull(item))
	ItemData(item) = data;
}

    
