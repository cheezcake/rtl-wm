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


#include "uwinD.h"
#include "tilecrsr.h"


/*ARGSUSED*/
void 
Bodyreg_Create_If_Not_Pres(uwinp, region_id)
    Userwin        *uwinp;
    int             region_id;
{
}

/*ARGSUSED*/
void 
Bodyreg_Destroy_Regions(uwinp)
    Userwin        *uwinp;
{
}


/*ARGSUSED*/
void 
Bodyreg_Def_Rect_For_Region(uwinp, region_id, left, top, width, height)
    Userwin        *uwinp;
    int             region_id;
    int             left, top, width, height;
{
}


/*ARGSUSED*/
void 
Bodyreg_Link_Region(uwinp, region_id1, region_id2)
    Userwin        *uwinp;
    int             region_id1, region_id2;
{
}


/*ARGSUSED*/
void 
Bodyreg_Name_Region(uwinp, region_id, name)
    Userwin        *uwinp;
    int             region_id;
    char           *name;
{
}


/*ARGSUSED*/
BodyRegion 
Bodyreg_Locate(uwinp, pt)
    Userwin        *uwinp;
    TWPoint           pt;
{
    return  NULL;
}


/*ARGSUSED*/
TileCursor 
Bodyreg_Get_Cursor(uw, bodyregion)
    Userwin        *uw;
    BodyRegion      bodyregion;
{
    return  standard_tilecursor;
}


/*ARGSUSED*/
void
Bodyreg_Set_Cursor(uw, font_index, c)
    Userwin	*uw;
    int		font_index, c;
{
}


/*ARGSUSED*/
TileMenu 
Bodyreg_Get_Menu(uwinp, bodyregion)
    Userwin        *uwinp;
    BodyRegion      bodyregion;
{
    return ((TileMenu) NULL);
}


/*ARGSUSED*/
void 
Bodyreg_Menu_Item(uwinp, string)
    Userwin        *uwinp;
    char           *string;
{
}
