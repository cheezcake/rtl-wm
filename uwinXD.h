/*
static char sccs_id[] = "@(#)uwinXD.h	5.6 9/1/88  Siemens Corporate Research and Support, Inc.";
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

#ifndef USERWIN
#include "uwinP.h"
#endif

#define Userwin_XParentWin(uwinp)	uwinp->xframe.parent
#define Userwin_XTopBorder(uwinp)	uwinp->xframe.top_border
#define Userwin_XLeftBorder(uwinp)	uwinp->xframe.left_border
#define Userwin_XRightBorder(uwinp)	uwinp->xframe.right_border
#define Userwin_XBottomBorder(uwinp)	uwinp->xframe.bottom_border
#define Userwin_XTopLeftCorner(uwinp)	(uwinp)->xframe.top_left
#define Userwin_XTopRightCorner(uwinp)	(uwinp)->xframe.top_right
#define Userwin_XBottomLeftCorner(uwinp)	(uwinp)->xframe.bottom_left
#define Userwin_XBottomRightCorner(uwinp)	(uwinp)->xframe.bottom_right
#define Userwin_XHeader(uwinp)		(uwinp)->xframe.header
#define Userwin_XZoomGadget(uwinp)	(uwinp)->xframe.zoom_gadget
#define Userwin_XMoveGadget(uwinp)	(uwinp)->xframe.move_gadget
#define Userwin_XClient(uwinp)		(uwinp)->xframe.client
#define Userwin_XIcon(uwinp)		(uwinp)->xframe.icon
#define Userwin_XClient_Icon(uwinp)	(uwinp)->xframe.client_icon
#define Userwin_XTransient_For(uwinp)   (uwinp)->xframe.transient_for
#define Userwin_Border_Width(uwinp)     (uwinp)->border_width
