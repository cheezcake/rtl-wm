#ifndef lint
static char sccs_id[] = "@(#)twin_creat.c	5.3  9/1/88";
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
#include "mem.h"

Tilwinp
Tilwin_Create_Window(id)
    pointer id;
{
    Tilwin *winp;
    
    winp = Mem_Allocate();
    Tilwin_Set_Window_Id(winp, id);
    State_Create((Tilwin *)winp);

    winp->width_stamp = 0;
    winp->height_stamp = 0;
    winp->Was_Auto_Closed = FALSE;

    return ((Tilwinp) winp);
}

void
Tilwin_Destroy_Window(winp)
    Tilwinp winp;
{
    if (Tilwin_Is_Open(winp) != TRUE) {
        State_Destroy((Tilwin *) winp);
	Mem_Deallocate((Tilwin *) winp);
    }
}
