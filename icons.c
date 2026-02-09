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

#include "basetype.h"
#include "uwinD.h"
#include "assoc.h"
#include "draw.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "xio.h"

#include "icons/rtl_icon.h"

static Pixmap
    rtl_icon;

/* ------------------------------------------------------------ */

/*  Load the Icons as Pixmaps from their bitmap data.
 */
int
Icons_Load()
{

    rtl_icon = (Pixmap) XCreateBitmapFromData(dpy, root,
					      rtl_icon_bits,
					      rtl_icon_width,
					      rtl_icon_height);
}

/* ------------------------------------------------------------ */

/*  Free Icon pixmaps. ??NOT called from anywhere, yet.
 */
int
Icons_Destroy()
{

    XFreePixmap(dpy, rtl_icon);
}


/* ------------------------------------------------------------ */

static Size Icons_Pixmap_Size( pix )
    Pixmap pix;
{
    Window w;
    int x, y;
    unsigned int width, height;
    unsigned int border_width;
    unsigned int depth;
    Size siz;

    XGetGeometry( dpy, pix, &w, &x, &y,
                  &width, &height,
                  &border_width, &depth );

    siz.width = width;
    siz.height = height;
    
    return siz;
}

/* ------------------------------------------------------------ */

static Pixmap icon_pixmap;

static bool Icons_Read_Bitmap_File( filnam )
    char *filnam;
{
    int  width, height;
    int  x_hot, y_hot;
    int  status;

    status = XReadBitmapFile(dpy, root, filnam,
 			 &width, &height,
			 &icon_pixmap, &x_hot, &y_hot);

	/*??  These pixmaps should be Freed somewhere
	 *??  when Rtl exits!
	 */

    return (status == BitmapSuccess);
}

/* ------------------------------------------------------------ */

/*  Set the Icon pixmap for a window */

Size Icons_Set( uwinp, siz, filnam )
    Userwin *uwinp;
    Size siz;
    char  *filnam;			/* filename for pixmap */
{
    extern bool Open_Read_With();

    uwinp->iconpix_pending = None;

    if ( filnam != NULL )
    {
        if ( Open_Read_With( filnam, Icons_Read_Bitmap_File ) )
	    uwinp->iconpix = icon_pixmap;
    }

    if ( uwinp->iconpix == None )
        return siz;
    else
        return Icons_Pixmap_Size( uwinp->iconpix );        

}

/* ------------------------------------------------------------ */

/*  Set the special RTL icon pixmap.
 */
int
Icons_Set_Rtl_Icon(uwinp)
    Userwin *uwinp;
{

    uwinp->iconpix = rtl_icon;
}
