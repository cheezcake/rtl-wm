#ifndef lint
static char sccs_id[] = "@(#)interf_in1.c	5.3  9/1/88";
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

#define DISALLOWED 0x000;

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

extern short TOOL_BUTTONS;
extern short DISCONNECT_BUTTONS;
extern short EXIT_BUTTONS;
extern short BODY_MANAGER_MENU_BUTTONS;
extern short BODY_USER_MENU_BUTTONS; 
extern short HEADER_MANAGER_MENU_BUTTONS;
extern short HEADER_USER_MENU_BUTTONS; 
extern short ICON_OPEN_BUTTONS; 
extern short ICON_MOVE_BUTTONS;
extern short CLOSE_BUTTONS;
extern short REDRAW_BUTTONS;
extern short ZOOM_BUTTONS;
extern short ZOOM_LOCK_BUTTONS;
extern short DESIRE_BUTTONS;
extern short ENLARGE_BUTTONS;
extern short MOVE_BUTTONS;
extern short RELOCATE_BUTTONS; 
extern short EXCHANGE_BUTTONS;
extern short RESIZE_BUTTONS;
extern short TOGGLE_GRAVITY_BUTTONS;
extern short CANCEL_BUTTONS;
extern short UNDESIRE_BUTTONS;
extern short FORCE_RESET_MIN_MAX_BUTTONS;
extern short FORCE_LISTENER_BUTTONS;
extern short FORCE_ZOOM_BUTTONS;

void Interf_Init_Buttons()
{

    DESIRE_BUTTONS = ANY_BUTTON | NONE_SHIFT_CTRL;
    ZOOM_BUTTONS = ANY_BUTTON | JUST_SHIFT;
    ENLARGE_BUTTONS = ANY_BUTTON | JUST_CTRL;

    ICON_OPEN_BUTTONS = ANY_BUTTON | NONE_SHIFT_CTRL;

    RESIZE_BUTTONS = ANY_BUTTON | NOT_SHIFT;

    TOGGLE_GRAVITY_BUTTONS = ANY_BUTTON | JUST_CTRL;
    FORCE_RESET_MIN_MAX_BUTTONS = ANY_BUTTON | JUST_SHIFT;
    UNDESIRE_BUTTONS = ANY_BUTTON | JUST_CTRL;
    FORCE_LISTENER_BUTTONS = ANY_BUTTON | HAS_SHIFT;
    FORCE_ZOOM_BUTTONS = ANY_BUTTON | HAS_CTRL;
    TOOL_BUTTONS  = ANY_BUTTON | DISALLOWED;

    RELOCATE_BUTTONS = ANY_BUTTON | NONE_SHIFT_CTRL;
    EXCHANGE_BUTTONS = ANY_BUTTON | JUST_CTRL;
    MOVE_BUTTONS = ANY_BUTTON | JUST_SHIFT;
    ICON_MOVE_BUTTONS = ANY_BUTTON | JUST_SHIFT;

    CANCEL_BUTTONS = ANY_BUTTON | BOTH_SHIFT_CTRL;
    CLOSE_BUTTONS = ANY_BUTTON | BOTH_SHIFT_CTRL;
    EXIT_BUTTONS = ANY_BUTTON | DISALLOWED;
    DISCONNECT_BUTTONS = ANY_BUTTON | BOTH_SHIFT_CTRL;

    REDRAW_BUTTONS = ANY_BUTTON | BOTH_SHIFT_CTRL;

    HEADER_MANAGER_MENU_BUTTONS = ANY_BUTTON | NOT_JUST_ONE_SHIFT_CTRL;
}
