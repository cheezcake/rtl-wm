#ifndef lint
static char sccs_id[] = "@(#)twin_list.c	5.3  9/1/88";
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

static WinpHandle curhandle;

void Tilwin_Gen_Open_Windows()
{
    curhandle = State_Gen_Open_Windows();
}

void Tilwin_Gen_Closed_Windows()
{
    curhandle = State_Gen_Closed_Windows();
}

void Tilwin_Gen_Just_Opened_Windows()
{
    curhandle = State_Gen_Just_Opened_Windows();
}

void Tilwin_Gen_Just_Modified_Windows()
{
    curhandle = State_Gen_Just_Modified_Windows();
}

void Tilwin_Gen_Just_Closed_Windows()
{
    curhandle = State_Gen_Just_Closed_Windows();
}

Tilwinp Tilwin_Next_Window()
{
    Tilwin *winp;
    
    winp = State_Coerce(curhandle);
    State_Next_Window(&curhandle);
    return (Tilwinp) winp;
}

