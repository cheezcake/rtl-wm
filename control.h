/*
static char sccs_id[] = "@(#)control.h	5.6  9/1/88";
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

#ifndef STD_DEFS
#include "std_defs.h"
#endif

extern bool send_mouse_events;
extern bool pointer_grabbed;
extern bool keyboard_grabbed;

extern bool Control_Grab_User();
/*    bool send_mouse; */
/*    TileCursor cursor; */
extern void Control_Ungrab_User();

#define Control_Pointer_Grabbed()  \
    ( pointer_grabbed )
#define Control_Mousing()  \
    ( send_mouse_events )

extern void Control_Grab_Server();
extern void Control_Ungrab_Server();

extern void Control_Set_Focus();
/*    Userwin *uwinp; */

extern void Control_Focus_Out();
/*    Userwin *uwinp; */

extern void Control_Unset_Focus();

extern void Control_Grab_Input();

extern void Control_Release_Grab();
/*    Userwin *uwinp; */

extern void Control_Restore_Grab();

extern void Control_Set_Cursor();
/*    TileCursor cursor; */
extern void Control_Restore_Cursor();

extern void Control_Destroy();
/*    Userwin *uwinp   */

extern bool Control_Pointer_To_Window();
/*    Userwin *uwinp   */

extern void Control_Exit();


