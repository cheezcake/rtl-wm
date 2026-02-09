#ifndef lint
static char sccs_id[] = "@(#)try_sat.c	5.3  9/1/88";
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
#include "twin.h"
#include "gravity.h"
#include "check.h"

bool
Trial_Satisfied(winp, sizep)
    Tilwin *winp;
    Size *sizep;
{
    Size min_size, 
	 max_size, 
	 original_size;
    bool not_changed = TRUE;
    
    original_size = *sizep;
    
    /* check global mins */
    min_size = Tilwin_Get_Absolute_Minimums();
    if (Get_Width(*sizep) < Get_Width(min_size))
        Get_Width(*sizep) = Get_Width(min_size);
    if (Get_Height(*sizep) < Get_Height(min_size))
	Get_Height(*sizep) = Get_Height(min_size);

    /* check minimums */
    if (Tilwin_Get_Global_Option(ENFORCE_MINIMUMS) == TRUE) {
        min_size = Tilwin_Get_Min(winp);
        if (Get_Width(*sizep) < Get_Width(min_size))
	    Get_Width(*sizep) = Get_Width(min_size);
        if (Get_Height(*sizep) < Get_Height(min_size))
	    Get_Height(*sizep) = Get_Height(min_size);
    }

    max_size = Tilwin_Get_Desktop_Size();
    if (Get_Width(*sizep) > Get_Width(max_size))
        Get_Width(*sizep) = Get_Width(max_size);
    if (Get_Height(*sizep) > Get_Height(max_size))
        Get_Height(*sizep) = Get_Height(max_size);

    if (Tilwin_Get_Global_Option(ENFORCE_MAXIMUMS) == TRUE) {
        min_size = Tilwin_Get_Max(winp);
        if (Get_Width(*sizep) > Get_Width(min_size))
	    Get_Width(*sizep) = Get_Width(min_size);
        if (Get_Height(*sizep) > Get_Height(min_size))
	    Get_Height(*sizep) = Get_Height(min_size);
    }
    
    if (Get_Width(original_size) != Get_Width(*sizep) ||
	Get_Height(original_size) != Get_Height(*sizep))
	    not_changed = FALSE;

    return(not_changed);
}
