/*
static char sccs_id[] = "@(#)platformP.h	5.4  9/1/88";
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

#define PLATFORM

#ifndef X_H
#include <X11/X.h>
#endif

typedef struct
{
    Window parent;		 /* parent "root" of Decorated X-RTL window */
    Window top_border;		 /* ...and the decorations */
    Window left_border;
    Window right_border;
    Window bottom_border;
    Window top_left;		 /* the corner border windows (4) */
    Window top_right;
    Window bottom_left;
    Window bottom_right;
    Window header;
    Window zoom_gadget;
    Window move_gadget;
    Window client;		 /* the client's X window */
    Window icon;		 /* icon X window */
    Window client_icon;		 /* client's icon window - a property */
    Window transient_for;        
} XFrame;

#define platform_fields  \
    int border_width; \
    Pixmap iconmask; \
    Pixmap iconpix;  \
    Pixmap iconpix_pending;  \
    bool ignore_unmap;	 /* ignore Unmap on X-reparent of client */  \
    XFrame xframe;	 /* the decorated X-client window */



