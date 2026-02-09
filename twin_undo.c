#ifndef lint
static char sccs_id[] = "@(#)twin_undo.c	5.3  9/1/88";
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
#include "twinD.h"
#include "state.h"
#include "win.h"

static void
Tilwin_Do_Undo()
{
    Tilwin *winp;
    WinpHandle handle;
    
    /* close windows which were opened by the previous
     * operation
     */
    handle = State_Gen_Just_Opened_Windows();
    while ((winp = State_Coerce(handle)) != WINP_NULL){
	Win_Close((Tilwin *)winp);
	State_Next_Window(&handle);
    }

    /* close all windows on that were modified by the last operation, they
     * will be reopened at their old location and size later
     */
    handle = State_Gen_Just_Modified_Windows();
    while ((winp = State_Coerce(handle)) != WINP_NULL) {
	Win_Close((Tilwin *)winp);
	State_Next_Window(&handle);
    }

    /* swap the previous and current values of
     * "important" twin fields and switch the Just_Opened
     *  and Just_Closed lists
     */
    State_Undo();

    /* reopen windows modified by the last operation at their old location and
     * size
     */
    handle = State_Gen_Just_Modified_Windows();
    while ((winp = State_Coerce(handle)) != WINP_NULL) {
	Win_Open((Tilwin *)winp, Tilwin_Get_Rectangle(winp));
	State_Next_Window(&handle);
    }

    /* open windows which were closed by the previous
     * operation
     */
    handle = State_Gen_Just_Opened_Windows();
    while ((winp = State_Coerce(handle)) != WINP_NULL) {
	Win_Open((Tilwin *)winp, Tilwin_Get_Rectangle(winp));
	State_Next_Window(&handle);
    }

}

void
Tilwin_Undo()
{
    if (State_Transaction_Depth() == 0)
        Tilwin_Do_Undo();

}

void Tilwin_Abort_Transaction()
{
    Tilwin_Do_Undo();
    State_Abort_Transaction();
}



