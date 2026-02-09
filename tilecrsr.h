/*
static char sccs_id[] = "@(#)tilecrsr.h	5.3  9/1/88";
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

#ifndef TILECURSOR
#include "tilecrsrP.h"
#endif
	
extern TileCursor standard_tilecursor;
extern TileCursor background_tilecursor;
extern TileCursor body_tilecursor;

extern TileCursor menu_tilecursor;

extern TileCursor question_tilecursor;
extern TileCursor confirmation_tilecursor;

extern TileCursor header_tilecursor;
extern TileCursor icon_tilecursor;

extern TileCursor gadget_tilecursor;
extern TileCursor move_gadget_tilecursor;
extern TileCursor zoom_gadget_tilecursor;

extern TileCursor left_tilecursor;
extern TileCursor right_tilecursor;
extern TileCursor top_tilecursor;
extern TileCursor bottom_tilecursor;

extern TileCursor top_left_tilecursor;
extern TileCursor bottom_left_tilecursor;
extern TileCursor top_right_tilecursor;
extern TileCursor bottom_right_tilecursor;

extern TileCursor track_open_tilecursor;
extern TileCursor corner_open_tilecursor;
extern TileCursor center_open_tilecursor;
extern TileCursor open_in_icon_tilecursor;

extern TileCursor move_tilecursor;
extern TileCursor move_icon_tilecursor;

extern TileCursor good_exchange_tilecursor;
extern TileCursor bad_exchange_tilecursor;

extern TileCursor watch_tilecursor;

/* ------------------------------------------------------------ */

extern void TileCursor_Init();

extern void TileCursor_Set();
    /* tilecursor */

extern TileCursor TileCursor_Make();

