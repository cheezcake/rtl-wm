/*
static char sccs_id[] = "@(#)buttonsP.h	5.2  9/1/88";
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


#ifndef BUTTONS
#define BUTTONS
#endif

#ifndef FIELD
#include "fieldP.h"
#endif

enum ButKind { up, down, click };

/* ------------------------------------------------------------ */

typedef short Buttons;
/* bits 0 and 1 specify the button that was changed */
/* bit 8 is whether SHIFT was down */
/* bit 9 is whether CTRL was down */

#define LEFT_BUTTON_NUMBER 1
#define MIDDLE_BUTTON_NUMBER 2
#define RIGHT_BUTTON_NUMBER 3

#define CTRL_DOWN 0x200
#define SHIFT_DOWN 0x100    

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

typedef short Match_Buttons;
/* bits 0,1, and 2 correspond to buttons 0,1, and 2 */
/* bits 8-11 correspond to logical operators on CTRL and SHIFT */

#define LEFT_BUTTON 0x1
#define MIDDLE_BUTTON 0x2
#define RIGHT_BUTTON 0x4

#define NOT_LEFT_BUTTON 0x6
#define NOT_MIDDLE_BUTTON 0x5
#define NOT_RIGHT_BUTTON 0x3

#define ANY_BUTTON 0x7

#define NOT_BUTTONS(but) ( 7 - (but) )

/* ------------------------------------------------------------ */

#define NONE_SHIFT_CTRL 0x100
#define JUST_SHIFT 0x200
#define NOT_CTRL 0x300
#define JUST_CTRL 0x400
#define NOT_SHIFT 0x500
#define JUST_ONE_SHIFT_CTRL 0x600
#define NOT_BOTH_SHIFT_CTRL 0x700

#define BOTH_SHIFT_CTRL 0x800
#define NOT_JUST_ONE_SHIFT_CTRL 0x900
#define HAS_SHIFT 0xa00
#define NOT_JUST_CTRL 0xb00
#define HAS_CTRL 0xc00
#define NOT_JUST_SHIFT 0xd00
#define SOME_SHIFT_CTRL 0xe00

#define DONT_CARE 0xf00

/* ------------------------------------------------------------ */

typedef short Button_State;
/* bits 0,1,2 corresponds to buttons 1,2,3 being down */

