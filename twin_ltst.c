#ifndef lint
static char sccs_id[] = "@(#)twin_ltst.c	5.5  9/1/88";
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
#include "state.h"
#include "twinD.h"

#define MAXKTH 20

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Get_Latest_Height( kth )
    int kth;
{
    WinpHandle handle;
    Tilwin *winp;
    int curkth = 0;
    Tilwin *(winps[MAXKTH+1]);
    int i;

    if ( kth > MAXKTH )
        kth = MAXKTH;
    
    handle = State_Gen_Open_Windows();
    while ((winp = State_Coerce(handle)) != WINP_NULL)
    {
        i = curkth;
        while ( ( i > 0 ) &&
                ( winps[i-1]->height_stamp <
                  winp->height_stamp ) )
        {
            winps[i] = winps[i-1];
            i--;     
        }

        if ( i < kth )
        {
            winps[i] = winp;
            if ( curkth < kth )
                curkth++;
        }                        
        
	State_Next_Window(&handle);
    }

    if ( ( curkth == kth ) && ( winps[kth-1]->height_stamp > 0 ) )
        return (Tilwinp)(winps[kth-1]);
    else
        return WIN_NULL;
}

/* ------------------------------------------------------------ */

Tilwinp Tilwin_Get_Latest_Width( kth )
    int kth;
{
    WinpHandle handle;
    Tilwin *winp;
    int curkth = 0;
    Tilwin *(winps[MAXKTH+1]);
    int i;

    if ( kth > MAXKTH )
        kth = MAXKTH;
    
    handle = State_Gen_Open_Windows();
    while ((winp = State_Coerce(handle)) != WINP_NULL)
    {
        i = curkth;
        while ( ( i > 0 ) &&
                ( winps[i-1]->width_stamp <
                  winp->width_stamp ) )
        {
            winps[i] = winps[i-1];
            i--;     
        }

        if ( i < kth )
        {
            winps[i] = winp;
            if ( curkth < kth )
                curkth++;
        }                        
        
	State_Next_Window(&handle);
    }

    if ( ( curkth == kth ) && ( winps[kth-1]->width_stamp > 0 ) )
        return (Tilwinp)(winps[kth-1]);
    else
        return WIN_NULL;
}
