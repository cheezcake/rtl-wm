/*
static char sccs_id[] = "@(#)buttonsD.h	5.5  9/1/88";
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




#ifndef FIELD
#include "fieldP.h"
#endif

#ifndef BUTTONS
#include "buttonsP.h"
#endif

#define Buttons_Index(but) \
    lowmasked( but, 2 )

#define Buttons_Number(but) \
    ( 1 + Buttons_Index(but) )

#define Buttons_Has_Ctrl_Down(but) \
    ( (but & CTRL_DOWN) != 0 )

#define Buttons_Has_Shift_Down(but) \
    ( (but & SHIFT_DOWN) != 0 )

#define Buttons_Match(but,matchbut) \
    ( is_set( matchbut, Buttons_Index(but) ) && \
      is_set( matchbut, 8 + extract( but, 8, 2 ) ) )

#define Buttons_Equal(but1,but2) \
    ( (but1) == (but2) )

#define Buttons_Down(butstate,but) \
    (butstate) |=  onemask( Buttons_Index(but) )      

#define Buttons_Up(butstate,but) \
    (butstate) &=  ~ onemask( Buttons_Index(but) )      

#define Buttons_Is_Down(butstate,but) \
    ( (butstate) & (but) )

#define Buttons_Is_Up(butstate,but) \
    ( ~Buttons_Is_Down(butstate,but) )

#define Buttons_Any_Down(butstate) \
    ( (butstate) != 0 )

#define Buttons_Clear(butstate) \
    (butstate) = 0

