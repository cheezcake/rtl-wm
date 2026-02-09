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

/*  The "Assoc" package is the front-end to the X
 *  association table, where X resource ==> (is mapped to)
 *  some Tiled-Window resource.
 */

#include "uwinXD.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/X10.h>
#include "xio.h"


#define ASSOC_TABLE_SIZE 64	/* ?? upper limit on number of dec. wins! */

static XAssocTable  *xa_table;

/* ------------------------------------------------------------
 *  Create the Association table. 
 *  Failure to create this table should be treated as fatal!
 */
bool
Assoc_InitTable()
{
    extern XAssocTable  *XCreateAssocTable();


    return  ( ((xa_table = XCreateAssocTable(ASSOC_TABLE_SIZE))
	       == (XAssocTable *) NULL ) ? 
	     FALSE : TRUE );
}

/* ------------------------------------------------------------
 *  Add Tiled-Window resource to AssocTable, keyed by X resource
 */
void
Assoc_Put(twp, xid)
    char *twp;
    XID  xid;
{

    XMakeAssoc(dpy, xa_table, xid, twp);
}

/* ------------------------------------------------------------
 *  Get Tiled-Window resource from AssocTable, keyed by X resource
 */
char *
Assoc_Get(xid)
    XID  xid;
{
    extern char  *XLookUpAssoc();


    return (XLookUpAssoc(dpy, xa_table, xid));
}

/* ------------------------------------------------------------
 *  Remove Window resource from AssocTable, keyed by X resource
 */
int
Assoc_Remove(xid)
    XID  xid;
{
    XDeleteAssoc(dpy, xa_table, xid);
}

/* ------------------------------------------------------------
 *  Remove X resources -- Tiled-Window resource association pairs
 */
void
Assoc_RemoveDecorations(uwinp)
    Userwin  *uwinp;
{

    XDeleteAssoc(dpy, xa_table, Userwin_XParentWin(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XTopBorder(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XLeftBorder(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XRightBorder(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XBottomBorder(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XTopLeftCorner(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XTopRightCorner(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XBottomLeftCorner(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XBottomRightCorner(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XHeader(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XZoomGadget(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XMoveGadget(uwinp));
    XDeleteAssoc(dpy, xa_table, Userwin_XClient(uwinp));
}


/*  Add a Decorated X Client-Window's resources to AssocTable
 */
void
Assoc_AddDecorations(uwinp)
    Userwin  *uwinp;
{

    XMakeAssoc(dpy, xa_table, Userwin_XParentWin(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XTopBorder(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XLeftBorder(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XRightBorder(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XBottomBorder(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XTopLeftCorner(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XTopRightCorner(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XBottomLeftCorner(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XBottomRightCorner(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XHeader(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XZoomGadget(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XMoveGadget(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XClient(uwinp), (char *) uwinp);
    XMakeAssoc(dpy, xa_table, Userwin_XIcon(uwinp), (char *) uwinp);
}

static XAssocTable *xid_table;

void
Assoc_Xid_InitTable()
{
    extern XAssocTable *XCreateAssocTable();
    
    xid_table = XCreateAssocTable(ASSOC_TABLE_SIZE);
}

XID
Assoc_Xid_Get(xid)
    XID xid;
{
    return((XID) XLookUpAssoc(dpy, xid_table, xid));
}

void
Assoc_Xid_Remove(xid)
    XID xid;
{
    XDeleteAssoc(dpy, xid_table, xid);
}

void
Assoc_Xid_Put(ptr, xid)
    XID ptr;
    XID xid;
{
    XMakeAssoc(dpy, xid_table, xid, (XPointer)ptr);
}
