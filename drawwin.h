/*
static char sccs_id[] = "@(#)drawwin.h	5.5  9/1/88";
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



#ifndef BASETYPE
#include "basetype.h"
#endif

extern void Drawwin_Init();

extern void Drawwin_Flash();

extern void Drawwin_Initial_Size();
    /* Userwin *uwinp */
    /* Size siz */

extern void Drawwin_Start();

extern void Drawwin_Finish();

extern void Drawwin_Create();
    /* uwinp */

extern void Drawwin_Prepare();
    /* uwinp */

extern void Drawwin_Insert();
    /* uwinp */

extern void Drawwin_Withdraw();
    /* uwinp */

extern void Drawwin_Destroy();
    /* uwinp */

extern void Drawwin_Draw_Background();
    /* rect */

extern bool Drawwin_Redraw_All();
    /* rect */

extern void Drawwin_Unmap();
    /* uwinp */

extern void Drawwin_Close();
    /* uwinp */

extern void Drawwin_Open();
    /* uwinp */

extern void Drawwin_Move_Open();
    /* uwinp */

extern void Drawwin_Move_Close();
    /* uwinp */

extern void Drawwin_Listener_Move_Open();
    /* uwinp */

extern void Drawwin_Listener_Move_Close();
    /* uwinp */

extern void Drawwin_Redraw();
    /* uwinp */

extern void Drawwin_Draw();
    /* uwinp */

extern void Drawwin_Display_Focus();
    /* uwinp */

extern void Drawwin_Display_Wrapping();
    /* uwinp */

extern void Drawwin_Retitle();
    /* uwinp */

extern void Drawwin_Show_Moving();
    /* uwinp */

extern void Drawwin_Unshow_Moving();
    /* uwinp */

extern void Drawwin_Good_Open_Box();
    /* spos, cpos */

extern void Drawwin_Bad_Open_Box();
    /* spos, cpos */

extern void Drawwin_Undo_Open_Box();

extern void Drawwin_Edge_Resize();
    /* uwinp, side, pos */

extern void Drawwin_Undo_Edge_Resize();

extern void Drawwin_Corner_Resize();
    /* uwinp, side, pos */

extern void Drawwin_Undo_Corner_Resize();

extern void Drawwin_Good_Move_Box();
    /* spos, cpos */

extern void Drawwin_Bad_Move_Box();
    /* spos, cpos */

extern void Drawwin_Undo_Move_Box();
