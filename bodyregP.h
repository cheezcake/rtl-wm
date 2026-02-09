/*
static char sccs_id[] = "@(#)bodyregP.h	5.2  9/1/88";
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


#define BODYREGION

#ifndef BASETYPE
#include "basetype.h"
#endif

#ifndef LISTS
#include "listsP.h"
#endif

#ifndef TILEMENU
#include "tilemenuP.h"
#endif

#ifndef TILECURSOR
#include "tilecrsrP.h"
#endif

typedef struct {
               TileMenu menu;
               TileCursor cursor;
               } MenuAndCurs;
	       

typedef struct bodyregion {
                 int regionid;
                 int menucursor_regionid; /* where to get menu and cursor defs
                					   */
                 struct bodyregion *menucursor_bodyregion;
		 TWRectangle *rect;
                 TileMenu menu;
		 TileCursor cursor;
                 char *regionname;
		 }  *BodyRegion;
		
	       

		
