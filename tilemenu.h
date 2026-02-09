/*
static char sccs_id[] = "@(#)tilemenu.h	5.6  9/1/88";
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



#ifndef TILEMENU
#include "tilemenuP.h"
#endif

extern TileMenu TileMenu_Create();

extern void TileMenu_Destroy();
    /* menu */

/* ------------------------------------------------------------ */

extern pointer TileMenu_Data();
    /* menu, item */

extern TileMenu TileMenu_Get_Submenu();
    /* menu, str */

/* ------------------------------------------------------------ */

extern TileMenuItem TileMenu_Append_String();
    /* menu, str, strval */

extern TileMenuItem TileMenu_Append_Callback();
    /* menu, backproc */

extern TileMenuItem TileMenu_Append_Checkback();
    /* menu, str, checkproc, proc */

extern TileMenuItem TileMenu_Append_Call();
    /* menu, str, proc, ptrval */

extern TileMenuItem TileMenu_Append_Submenu();
    /* menu, str, submenu */

/* ------------------------------------------------------------ */

extern void TileMenu_Replace_Data_By_String();
    /* menu, data, str */

/* ------------------------------------------------------------ */

extern void TileMenu_Activate_Entry();
    /* menu, item */

extern void TileMenu_Inactivate_Entry();
    /* menu, item */

/* ------------------------------------------------------------ */

extern bool TileMenu_Has_Data();
    /* menu, val */

/* ------------------------------------------------------------ */

extern void TileMenu_Delete_Entries();
    /* menu */

extern void TileMenu_Delete_String();
    /* menu, str */

extern void TileMenu_Delete_Data();
    /* menu, val */

/* ------------------------------------------------------------ */

extern void TileMenu_Box();
    /* menu */

extern void TileMenu_Enter();
    /* menu, butnum, kind */

extern TWPoint TileMenu_Entry_Pos();

