/*
static char sccs_id[] = "@(#)uservalsP.h	5.4  9/1/88";
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
        Icon_None,
        Icon_Top, Icon_Bottom,
        Icon_Left, Icon_Right,
        Icon_Middle
} Icon_Position;


typedef enum {

    ABS_MIN_WIDTH,
    ABS_MIN_HEIGHT,

    RTL_LEFT_X,
    RTL_TOP_Y,

    FULL_WIDTH,
    FULL_HEIGHT,

    RTL_WIDTH,
    RTL_HEIGHT,

    ICON_AREA_TOP,
    ICON_AREA_BOTTOM,
    ICON_AREA_LEFT,
    ICON_AREA_RIGHT,

    BORDER_SIZE,
    OUTER_BORDER_LINEWIDTH,
    INNER_BORDER_LINEWIDTH,

    GADGET_WIDTH,

    GRAVITY,

    ICON_PLACEMENT,
    SECONDARY_ICON_PLACEMENT,

    NEIGHBORHOOD_SHRINK_FACTOR,

    LENGTH_USER_GLOBAL_VALUES
} User_Global_Values;

