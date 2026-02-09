/*
static char sccs_id[] = "@(#)drawicon.h	5.5  9/1/88";
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

extern void DrawIcon_Init();

extern void DrawIcon_Flash();

extern void DrawIcon_Init_Rtl();
    /* uwinp */

extern void DrawIcon_Initial_Size();
    /* uwinp */

extern void DrawIcon_Create();
    /* uwinp */

extern void DrawIcon_Destroy();
    /* uwinp */

extern void DrawIcon_Close();
    /* uwinp */

extern void DrawIcon_Open();
    /* uwinp */

extern void DrawIcon_Move_Open();
    /* uwinp */

extern void DrawIcon_Move_Close();
    /* uwinp */

extern void DrawIcon_Redraw();
    /* uwinp */

extern void DrawIcon_Draw();
    /* uwinp */

extern void DrawIcon_Retitle();
    /* uwinp */

extern void DrawIcon_Note_Output();
    /* uwinp */

extern void DrawIcon_Good_Move_Box();
    /* uwinp, pos, siz */

extern void DrawIcon_Bad_Move_Box();
    /* uwinp, pos, siz */

extern void DrawIcon_Undo_Move_Box();

extern void DrawIcon_Show_Moving();
    /* uwinp */

extern void DrawIcon_Unshow_Moving();
    /* uwinp */

extern void DrawIcon_Show_Opening();
    /* uwinp */

extern void DrawIcon_Unshow_Opening();
    /* uwinp */


