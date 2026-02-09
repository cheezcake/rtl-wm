/*
static char sccs_id[] = "@(#)client.h	5.5  9/1/88";
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



extern void Client_Enter();
    /* uwinp, butstate, pos */

extern void Client_Send_Mouse();
    /* uwinp, butstate, pos */

extern void Client_Send_Button();
    /* uwinp, kind, button, pos */

extern void Client_Send_Key();
    /* uwinp, ch */

extern void Client_Ignore_Key();
extern void Client_Ignore_Button();

extern void Client_Send_String();
    /* uwinp, str */

/* ------------------------------------------------------------ */

extern void Client_Menu_Button_Number();
    /* num */

/* ------------------------------------------------------------ */

extern void Client_Kill();
    /* uwinp */

extern void Client_Redraw();
    /* uwinp */

extern void Client_Window_Create();
    /* str */

extern void Client_Startup();
    /* str */

extern void Client_Take_Focus();
    /* uwinp */

extern void Client_Bang();
    /* uwinp */

extern void Client_Set_State();
    /* uwinp */

extern void Client_Configure_Denied();
    /* uwinp */

extern void Client_Window_Moved();
    /* uwinp */

extern void Client_Delete_Window();
    /* uwinp */

extern void Client_Icon_Notify();
    /* uwinp */

