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

#include <stdio.h>
#include <stdlib.h>
#include "basetype.h"
#include "userglobD.h"
#include "uwinD.h"
#include "uwinXD.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "xio.h"
#include "tilecrsr.h"
#include "assoc.h"

#define ICONFONT  "6x12"


static XFontStruct  *ifontp;

extern GC
    fillGC, clearGC, xorGC, invert_body_GC;
extern Pixmap
    iconframe;

/* ------------------------------------------------------------
 *  Load icons into RTL.
 */
void
DrawIcon_Init()
{

    Icons_Load();

    if ( (ifontp = XLoadQueryFont(dpy, ICONFONT)) == (XFontStruct *) NULL )
    {
	fprintf(stderr, "DrawIcon_Init: cannot load font <%s>!\n",
		ICONFONT);
    }

}

/* ------------------------------------------------------------
 *  ??Create Icon x-window for 'uwinp'.
 *  ??Called from Manage_Create_Window.  Don't know class (yet).
 *  ??How to vary icon window size?
 *  ??How to handle Client-provided Icon windows?
 */
void
DrawIcon_Create( uwinp )
    Userwin *uwinp;
{
    unsigned long  vmask;
    XSetWindowAttributes  attrs;
    TWRectangle  rect;
    int  width, height;
    

    rect = Tilwin_Get_Rectangle( uwinp->iconp );
    width = rect.right_x - rect.left_x + 1;
    height = rect.bottom_y - rect.top_y + 1;

    
    vmask = CWEventMask | CWBackPixel;

    attrs.event_mask = ButtonPressMask | ButtonReleaseMask |
 	KeyPressMask | LeaveWindowMask | EnterWindowMask | ExposureMask;

    attrs.background_pixel = WhitePixel(dpy, scrn);

    Userwin_XIcon(uwinp) = 
	XCreateWindow(dpy, root,
		      0, 0, 
		      (unsigned) width, (unsigned) height,
		      0,
		      DefaultDepth(dpy, scrn), (unsigned int) CopyFromParent,
		      DefaultVisual(dpy, scrn), vmask, &attrs);
    
    XDefineCursor(dpy, Userwin_XIcon(uwinp), icon_tilecursor);

    /* make sure it's below transients */
    XLowerWindow(dpy, Userwin_XIcon(uwinp)); 
}

/* ------------------------------------------------------------
 *  Destroy Icon x-window for 'uwinp'.
 */
/*ARGSUSED*/
void DrawIcon_Destroy( uwinp )
    Userwin *uwinp;
{
    Assoc_Remove(Userwin_XIcon(uwinp));

    XDestroyWindow(dpy, Userwin_XIcon(uwinp));
}

/* ------------------------------------------------------------
 *
 */
void DrawIcon_Init_Rtl( uwinp )
    Userwin *uwinp;
{

    DrawIcon_Create(uwinp);

    Userwin_XParentWin(uwinp) = None;
    Userwin_XClient(uwinp) = None;
    
    Assoc_Put((char *) uwinp, Userwin_XIcon(uwinp));

    Icons_Set_Rtl_Icon(uwinp);

    uwinp->output_sent = FALSE;

    Userwin_Set_Window_Option( uwinp, CLIENT_DRAWS_ICON, FALSE );
    Userwin_Set_Window_Option( uwinp,
       INCLUDE_TITLE_IN_PIXMAP_ICON, FALSE );
}

/* ------------------------------------------------------------
 *  Draw the string at the proper position in the Icon window.
 *
 *  NOTE: We ignore the "rect" argument, since all drawing will
 *  relative to the icon window, with top-left corner at (0,0)
 */
/*ARGSUSED*/
static void
DrawIcon_Draw_String(icon, rect, offset, s)
    Window  icon;
    TWRectangle  rect;
    TWRectangle  offset;
    char  *s;
{
    int  x0, y0, x1, y1;
    char  strs[16][16];
    int  ilin, nlin, ichar, nchar; 
    short  height;


    if (ifontp == (XFontStruct *) NULL)
	return;

    x0 = ifontp->max_bounds.width;
    y0 = height = ifontp->max_bounds.ascent + ifontp->max_bounds.descent;

    x1 = x0 + offset.right_x;
    x0 += offset.left_x;
    y1 = y0 + offset.bottom_y;
    y0 += offset.top_y;
    
    nlin = ( y1 - y0 + 1 ) / (1 + height);

    if ( nlin > 0 )
	nlin--;
    ilin = 0;
    
    while ( ilin <= nlin )
    {
        while ( *s == ' ' )
            s++;
        if ( *s == 0 ) break;

        ichar = nchar = Draw_Num_Drawables(s, ifontp, x1 - x0 + 1, 1000);
        if ( nchar == 0 ) break;

        if ( (s[nchar] != 0) && ( ilin < nlin ) )
            while ( (ichar >= 0) && (s[ichar] != ' ') && (s[ichar] != '/') )
                ichar--;
        ichar--;
        if ( ichar < 0 )
            ichar = nchar - 1;
        else
            while ( s[ichar] == ' ' )
                ichar--;
        
        (void) strncpy( strs[ilin], s, ichar + 1 );
        strs[ilin][ichar+1] = 0;
        ilin++;

        s = &s[ichar+1];
    }
    
    nlin = ilin;

    for ( ilin = 0; ilin < nlin; ilin++ )
    {
	XDrawString(dpy, icon, fillGC,
		    x0, y0 + ( ( ilin * (y1 - y0 + 1) ) / nlin ),
		    strs[ilin],
		    strlen(strs[ilin]));
    }
}

/* ------------------------------------------------------------
 *  Draw client info in its Icon window.
 */
static void 
DrawIcon_Draw_Info( uwinp )
    Userwin *uwinp;
{
    char *str;
    int strsiz = 1;
    bool has_class, has_name;

    has_class = (uwinp->res_class != NULL) &&
        Userwin_Get_Window_Option( uwinp,
            INCLUDE_RES_CLASS_IN_ICON_TITLE );

    has_name = (uwinp->res_name != NULL) &&
        Userwin_Get_Window_Option( uwinp,
            INCLUDE_RES_NAME_IN_ICON_TITLE );

    if ( has_class || has_name )
    {
        if ( has_class )        
            strsiz += strlen(uwinp->res_class);

        if ( has_class && has_name )
            strsiz +=1;

        if ( has_name )
            strsiz += strlen(uwinp->res_name);

        str = allocate( char, strsiz );
        str[0] = '\0';

        if ( has_class )        
            (void)strcat( str, uwinp->res_class );

        if ( has_class && has_name )
            (void)strcat( str, ":" );

        if ( has_name )
            (void)strcat( str, uwinp->res_name );

        DrawIcon_Draw_String(Userwin_XIcon(uwinp),
			     Tilwin_Get_Rectangle( uwinp->iconp ),
			     uwinp->icon_res_rect,
			     str);
        free( str );
    }


    if ( Userwin_Get_Window_Option( uwinp,
             INCLUDE_HOST_IN_ICON_TITLE ) &&
         (uwinp->hostname != NULL) )
        DrawIcon_Draw_String(Userwin_XIcon(uwinp),
			     Tilwin_Get_Rectangle( uwinp->iconp ),
			     uwinp->icon_host_rect,
			     uwinp->hostname);

    if ( Userwin_Get_Window_Option( uwinp,
             INCLUDE_NAME_IN_ICON_TITLE ) )
    {
        if (uwinp->iconname != NULL)
	    DrawIcon_Draw_String(Userwin_XIcon(uwinp),
				 Tilwin_Get_Rectangle( uwinp->iconp ),
				 uwinp->icon_name_rect,
				 uwinp->iconname);
	
        else if (uwinp->wmname != NULL)
	    DrawIcon_Draw_String(Userwin_XIcon(uwinp),
				 Tilwin_Get_Rectangle( uwinp->iconp ),
				 uwinp->icon_name_rect,
				 uwinp->wmname);
    }
}

/* ------------------------------------------------------------
 *  Draw Icon pixmap in its x-window.
 */
int
DrawIcon_Display( uwinp )
    Userwin *uwinp;
{
    TWRectangle  rect;
    unsigned int  width, height;
    GC  gc;

    rect = Tilwin_Get_Rectangle( uwinp->iconp );
    width = rect.right_x - rect.left_x + 1;
    height = rect.bottom_y - rect.top_y + 1;
    
    XClearWindow(dpy, uwinp->xframe.icon);
    
    gc = DefaultGC(dpy, scrn);

    /* flash the icon, and leave a border behind */

    XFillRectangle(dpy, uwinp->xframe.icon, invert_body_GC,
                   0, 0, width, height);
    XFlush(dpy);
    XFillRectangle(dpy, uwinp->xframe.icon, invert_body_GC,
                   1, 1, width-2, height-2);


    if ( Userwin_Get_Window_Option( uwinp, CLIENT_DRAWS_ICON ) )
    {
        if ( uwinp->iconpix != None )
            XCopyPlane(dpy, uwinp->iconpix,
		       uwinp->xframe.icon,
		       gc, 1, 1, width-2, height-2, 1, 1,
		       (unsigned long) 1);

        if ( Userwin_Get_Window_Option( uwinp,
                 INCLUDE_TITLE_IN_CLIENT_ICON ) )
            DrawIcon_Draw_Info( uwinp );
    }
    else if ( (uwinp->output_sent) && (uwinp->iconpix_pending != None) )
    {
        XCopyPlane(dpy, uwinp->iconpix_pending,
		   uwinp->xframe.icon,
		   gc, 0, 0, width, height, 0, 0,
		   (unsigned long) 1);

        if ( Userwin_Get_Window_Option( uwinp,
                 INCLUDE_TITLE_IN_PIXMAP_ICON ) )
            DrawIcon_Draw_Info( uwinp );
    }
    else
    {
        if ( uwinp->iconpix != None )
            XCopyPlane(dpy, uwinp->iconpix,
		       uwinp->xframe.icon,
		       gc, 1, 1, width-2, height-2, 1, 1,
		       (unsigned long) 1);

        if ( uwinp->output_sent &&
             Userwin_Get_Window_Option( uwinp, INVERT_ICON_WHEN_PENDING ) )
            XFillRectangle(dpy, uwinp->xframe.icon, invert_body_GC,
                           0, 0, width, height);

            if ( ( uwinp->iconpix == None ) ||
                 Userwin_Get_Window_Option( uwinp,
                     INCLUDE_TITLE_IN_PIXMAP_ICON ) )
                DrawIcon_Draw_Info( uwinp );
    }
}

/* ------------------------------------------------------------
 *  Unmap Icon on a closing Move operation.
 */
void DrawIcon_Move_Close( uwinp )
    Userwin *uwinp;
{
/*   don't think we need to do this....       */
/*   XUnmapWindow(dpy, Userwin_XIcon(uwinp)); */
}

/* ------------------------------------------------------------
 */
void DrawIcon_Close( uwinp )
    Userwin *uwinp;
{

    XUnmapWindow(dpy, Userwin_XIcon(uwinp)); 

}

/* ------------------------------------------------------------
 *  Move Icon (window) to new location.
 */
void DrawIcon_Move_Open( uwinp )
    Userwin *uwinp;
{
    TWRectangle  rect;
    Size icon_size;
    XWindowChanges ch;
    
    rect = Tilwin_Get_Rectangle(uwinp->iconp);
    ch.x = Get_LeftX(rect);
    ch.y = Get_TopY(rect);
    
    icon_size = Tilwin_Get_Size(uwinp->iconp);
    ch.width  = Get_Width(icon_size);
    ch.height = Get_Height(icon_size);
    
    XConfigureWindow(dpy, Userwin_XIcon(uwinp),
		     (unsigned int)(CWX | CWY | CWWidth | CWHeight),
		     &ch);

    XMapWindow(dpy, Userwin_XIcon(uwinp));
}

/* ------------------------------------------------------------
 *  Open the Icon.  (Call Move_Open?)
 */
void DrawIcon_Open(uwinp)
    Userwin *uwinp;
{
    DrawIcon_Move_Open(uwinp);
}

/* ------------------------------------------------------------
 *  Re-configure Icon window on a reset of RTL profile.
 */
/*ARGSUSED*/
void DrawIcon_Draw( uwinp )
    Userwin *uwinp;
{
/*XXXXXXXX*/
}

/* ------------------------------------------------------------
 *  Re-display Icon window.
 */
void DrawIcon_Redraw( uwinp )
    Userwin *uwinp;
{

    DrawIcon_Display( uwinp );
}

/* ------------------------------------------------------------
 *  Reset Icon title in its window.
 */
void
DrawIcon_Retitle( uwinp )
    Userwin *uwinp;
{

    DrawIcon_Display( uwinp );
}

/* ------------------------------------------------------------
 *  Display pending-I/O pixmap in Icon window, upon
 *  pending I/O in the x-window.
 */
void DrawIcon_Note_Output( uwinp )
    Userwin *uwinp;
{

    DrawIcon_Display( uwinp );
}

/* ------------------------------------------------------------
 *  Invert Icon window's image, upon a Move Operation.
 */
void DrawIcon_Show_Moving( uwinp )
    Userwin *uwinp;
{
    TWRectangle  rect;
    unsigned int  width, height;


    rect = Tilwin_Get_Rectangle( uwinp->iconp );
    width = rect.right_x - rect.left_x + 1;
    height = rect.bottom_y - rect.top_y + 1;

    XFillRectangle(dpy, uwinp->xframe.icon, invert_body_GC,
		   0, 0, width, height);
}

/* ------------------------------------------------------------
 *  Revert Icon window's image to "standard" color - Move
 *  Operation was completed or cancelled.
 */
void DrawIcon_Unshow_Moving( uwinp )
    Userwin *uwinp;
{
    DrawIcon_Show_Moving( uwinp );
}

/* ------------------------------------------------------------
 */
void DrawIcon_Show_Opening( uwinp )
    Userwin *uwinp;
{
    DrawIcon_Show_Moving( uwinp );
}

/* ------------------------------------------------------------
 */
void DrawIcon_Unshow_Opening( uwinp )
    Userwin *uwinp;
{
    DrawIcon_Unshow_Moving( uwinp );
}

/* ============================================================ */

static int old_x0, old_y0, old_x1, old_y1;

/*ARGSUSED*/
static void DrawIcon_Calc_Move_Rect( uwinp, pos, siz )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
{
    int xdif, ydif;


    xdif = siz.width/2;
    ydif = siz.height/2;

    old_x0 = pos.x - xdif + 1;
    old_y0 = pos.y - ydif + 1;
    old_x1 = pos.x + xdif;
    old_y1 = pos.y + ydif;
}

/* ------------------------------------------------------------
 */
/*ARGUSED*/
void DrawIcon_Good_Move_Box( uwinp, pos, siz )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
{

    DrawIcon_Calc_Move_Rect(uwinp,pos,siz);    

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_MOVE) );
}

/* ------------------------------------------------------------
 */
void DrawIcon_Bad_Move_Box( uwinp, pos, siz )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
{

    DrawIcon_Good_Move_Box(uwinp,pos,siz);
}

/* ------------------------------------------------------------
 */
void DrawIcon_Undo_Move_Box()
{

    Drawwin_Draw_Box( old_x0, old_y0, old_x1, old_y1,
		     UserGlobals_Get_Option(DRAW_X_ON_MOVE) );
}
