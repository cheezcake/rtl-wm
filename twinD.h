/*
static char sccs_id[] = "@(#)twinD.h	5.5  9/1/88";
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



#ifndef TILWIN_DEFINE
#define TILWIN_DEFINE
#endif

#ifndef TILWIN_INTERN
#include "twinI.h"
#endif

#include "tileoptsP.h"

#define  Tilwin_Get_Window_Id(winp) \
    ( ((winp) == WIN_NULL) ? (pointer)NULL : (((Tilwin *)(winp))->id) )
#define  Tilwin_Set_Window_Id(winp, id) \
    (((Tilwin *) (winp)) -> id) = (pointer) (id)

#define  Tilwin_Get_Data(winp) \
    (((Tilwin *)(winp))->data)
#define  Tilwin_Put_Data(winp,val) \
    (((Tilwin *)(winp))->data) = (pointer)(val)

#define  Tilwin_Get_Window_Option(winp,opt) \
    ( ((Tilwin *)(winp)) -> options[ (int) opt ] )

#define  Tilwin_Set_Window_Option(winp,opt,val) \
    ( ((Tilwin *)(winp)) -> options[ (int) opt ] ) = (val)

#define  Tilwin_Get_Rectangle(winp) \
    (((Tilwin *)(winp)) -> rect)

#define Tilwin_Get_Modify_Side(winp) \
    (((Tilwin *)(winp)) -> modify_side)
#define Tilwin_Set_Modify_Side(winp, side) \
    (((Tilwin *) (winp)) -> modify_side) = (side)

#define Tilwin_Get_Modify_Rectangle(winp) \
    (((Tilwin *)(winp)) -> modify_rect)
#define Tilwin_Set_Modify_Rectangle(winp, rect) \
    (((Tilwin *)(winp)) -> modify_rect) = (rect)

#define  Tilwin_Get_Size(winp) \
    (((Tilwin *)(winp)) -> size)
#define  Tilwin_Get_Center(winp) \
    (((Tilwin *)(winp))->center)

#define  Tilwin_Get_Min(winp) \
    (((Tilwin *)(winp)) -> min_size)
#define  Tilwin_Set_Min(winp, size) \
    { \
        (((Tilwin *)(winp)) -> min_size).height = (1+ (size).height ) & (~1); \
        (((Tilwin *)(winp)) -> min_size).width = (1+ (size).width ) & (~1); \
    }

#define  Tilwin_Get_Max(winp) \
    (((Tilwin *)(winp)) -> max_size)
#define  Tilwin_Set_Max(winp, size) \
    { \
        (((Tilwin *)(winp)) -> max_size).height = (1+ (size).height ) & (~1); \
        (((Tilwin *)(winp)) -> max_size).width = (1+ (size).width ) & (~1); \
    }

#define  Tilwin_Get_Desired(winp) \
    (((Tilwin *)(winp)) -> desired_size)
#define  Tilwin_Set_Desired(winp, size) \
    { \
        (((Tilwin *)(winp)) -> desired_size).height = ( (size).height ) & (~1); \
        (((Tilwin *)(winp)) -> desired_size).width = ( (size).width ) & (~1); \
    }


#define  Tilwin_Is_Open(winp) \
    (((Tilwin *)(winp)) -> Am_I_Open)
#define  Tilwin_Was_Previously_Open(winp) \
    (((Tilwin *)(winp)) -> prev_Am_I_Open)

#define  Tilwin_Was_Automatically_Closed(winp) \
    (((Tilwin *)(winp)) -> Was_Auto_Closed)

#define  Tilwin_Get_Previous_Rectangle(winp) \
    (((Tilwin *)(winp)) -> prev_rect)
#define  Tilwin_Get_Previous_Size(winp) \
    (((Tilwin *)(winp)) -> prev_size)
#define  Tilwin_Get_Previous_Center(winp) \
    (((Tilwin *)(winp)) -> prev_center)

#define  Tilwin_Get_Window_Timestamp(winp) \
    (((Tilwin *)(winp)) -> timestamp)

#define  Tilwin_Just_Created(winp) \
    ( Tilwin_Get_Window_Timestamp(winp) == 0 )

#define  Tilwin_Was_Actually_Modified(winp) \
    (! Same_Rect( ((Tilwin *)(winp))->rect, ((Tilwin *)(winp))->prev_rect ) )

#define Tilwin_Size_Changed(winp) \
    ( ( ((Tilwin *)winp)->size.width !=  \
        ((Tilwin *)winp)->prev_size.width )  \
    ||  \
      ( ((Tilwin *)winp)->size.height !=  \
        ((Tilwin *)winp)->prev_size.height ) )

/* ------------------------------------------------------------ */

#define  Tilwin_Get_Window_Option(winp,opt) \
    ( ((Tilwin *)(winp)) -> options[ (int) opt ] )

#define  Tilwin_Set_Window_Option(winp,opt,val) \
    ( ((Tilwin *)(winp)) -> options[ (int) opt ] ) = (val)

extern bool globals[];

#define Tilwin_Set_Global_Option(opt,val) \
    globals[(int)(opt)] = (val)

#define Tilwin_Get_Global_Option(opt) \
    ( globals[(int)(opt)] )

#define Tilwin_Get_Tile(winp) \
    (((Tilwin *)(winp)) -> tilep)

#define Tilwin_Get_Position(winp) \
    (((Tilwin *)(winp)) -> position)

#define Tilwin_Set_Position(winp, pt) \
    (((Tilwin *)(winp)) -> position = (pt))

#define Tilwin_Get_Open_Priority(winp) \
    (((Tilwin *)(winp)) -> open_priority)

#define Tilwin_Set_Open_Priority(winp, pri) \
    (((Tilwin *) (winp)) -> open_priority = (pri))

#define Tilwin_Get_Size_Priority(winp) \
    (((Tilwin *)(winp)) -> size_priority)

#define Tilwin_Set_Size_Priority(winp, pri) \
    (((Tilwin *) (winp)) -> size_priority = (pri))

#define Tilwin_Note_Desired_Height(winp) \
    ((Tilwin *)(winp))->height_stamp = Tilwin_Get_Timestamp()
#define Tilwin_Note_Desired_Width(winp) \
    ((Tilwin *)(winp))->width_stamp = Tilwin_Get_Timestamp()

#ifdef WM_DEBUG
extern Tilwin *tw_global;
#endif
