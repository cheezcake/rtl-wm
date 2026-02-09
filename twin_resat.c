#ifndef lint
static char sccs_id[] = "@(#)twin_resat.c	5.3  9/1/88";
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
#include "trial.h"
#include "commit.h"
#include "win.h"

bool
Tilwin_Is_Satisfied(winp)
    Tilwinp winp;
{
    Tilwin *twinp = (Tilwin *)winp;
    Size size;
    
    size = Tilwin_Get_Size(twinp);
    return(Trial_Satisfied(twinp, &size));
}

bool Tilwin_Satisfied_By_Size(winp, size)
    Tilwinp winp;
    Size size;
{
    Tilwin *twinp = (Tilwin *)winp;

    return(Trial_Satisfied(twinp, &size));
}
