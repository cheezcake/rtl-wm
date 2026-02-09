/*
static char sccs_id[] = "@(#)draw.h	5.5  9/1/88";
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


#ifndef DRAW
#include "drawP.h"
#endif

extern void Draw_Init();

extern void Draw_Create();
/*    Userwin *uwinp;
 */

extern void Draw_ConfigWin();
/*  Window  win;
    int  left_x, top_y;
    int  width, height;
 */

extern void Draw_Start();
    /* x0,y0,x1,y1 */

extern void Draw_Finish();

extern void Draw_Flash();

extern void Draw_Line();
    /* x0,y0,x1,y1 */

extern void Draw_Horizontal();
    /* width, y, x0, x1 */

extern void Draw_Vertical();
    /* width, x, y0, y1 */

extern void Draw_Xor_Line();
    /* x0,y0,x1,y1 */

extern void Draw_Xor_Horizontal();
    /* y,x0,x1 */

extern void Draw_Xor_Vertical();
    /* y,x0,x1 */

extern void Draw_Clear_Rectangle();
    /* x0,y0,x1,y1 */
extern void Draw_Background_Rectangle();
    /* x0,y0,x1,y1 */
extern void Draw_Fill_Rectangle();
    /* x0,y0,x1,y1 */
extern void Draw_Fill_Xor_Rectangle();
    /* x0,y0,x1,y1 */

extern void Draw_Rectangle();
    /* width,x0,y0,x1,y1 */

extern void Draw_Xor_Rectangle();
    /* x0,y0,x1,y1 */

extern void Draw_Pixrect();
    /* pixp,x0,y0,x1,y1 */

extern int Draw_Open();
    /* fontstr */

extern int Draw_Font_Height();
    /* fontid */

extern int Draw_Num_Drawables();
    /* str, fontid, width */

extern void Draw_Centered_String();
    /* str, fontid, x0, y0, x1, y1 */

extern void Draw_Vert_Centered_String();
    /* str, fontid, x0, y0, x1, y1 */

extern int Draw_Get_Frame_Width();

extern int Draw_Get_Frame_Height();
