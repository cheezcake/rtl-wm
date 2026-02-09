/*
static char sccs_id[] = "@(#)state.h	5.7  9/1/88";
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


#ifndef STATE
#include "stateP.h"
#endif

extern int State_Transaction_Depth();

extern void State_Set_Window_Timestamp();
/* winp, stamp */

extern void State_Note_Use();
/* winp */

extern bool State_Was_Just_Modified();
/*    Tilwin *winp; */

extern void State_Act_Modified();
/*    Tilwin *winp; */

extern void State_Insert_Just_Modified();
/*    Tilwin *winp; */

extern void State_Start_Operation();

extern void State_Start_Transaction();
extern void State_Commit_Transaction();
extern void State_Abort_Transaction();
extern void State_Continue_Transaction();

extern void State_Create();
/*    Tilwin *winp; */

extern void State_Destroy();
/*    Tilwin *winp; */

extern void State_Manual_Close();
/*    Tilwin *winp; */

extern void State_Auto_Close();
/*    Tilwin *winp; */

extern void State_Open();
/*    Tilwin *winp; */

extern TimeStamp State_Get_Timestamp();

extern WinpHandle State_Gen_Open_Windows();

extern WinpHandle State_Gen_Closed_Windows();

extern WinpHandle State_Gen_Just_Opened_Windows();

extern WinpHandle State_Gen_Just_Modified_Windows();

extern WinpHandle State_Gen_Just_Closed_Windows();

extern void State_Next_Window();
    /* WinpHandle *handle */

extern void State_Undo();

/****************************************************************************
 * appended to original state.h
 ****************************************************************************
 */

extern void State_Potential_Clear();
extern WinpHandle State_Gen_Potentially_Modfd();
extern WinpHandle State_Gen_Potentially_Closed();
extern void State_Insert_Potentially_Modfd();
extern void State_Insert_Potentially_Closed();
extern void State_Remove_Potentially_Modfd();
extern void State_Remove_Potentially_Closed();
extern void State_Flip_Just_Lists();
extern bool State_Currently_Transacting();
extern void State_Swap();
