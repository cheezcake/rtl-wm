/*
static char sccs_id[] = "@(#)twinoptsP.h	5.4  9/1/88";
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



typedef enum
{
        EXPENSIVE_TO_REDRAW,
	FIXED_COMPLETELY,
	FIXED_BOTTOM_EDGE,
	FIXED_TOP_EDGE,
	FIXED_LEFT_EDGE,
	FIXED_RIGHT_EDGE,
	FIXED_SIZE,
        FIXED_HEIGHT,
        FIXED_WIDTH,
	REQUIRE_MANUAL_CLOSE,
        SHRINK_BASED_ON_CURRENT_SIZE,
        WEIGHTED_SHRINK,
	LENGTH_WINDOW_OPTIONS			/* always LAST in this list! */
} Window_Options;
