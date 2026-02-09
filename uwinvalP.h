/*
static char sccs_id[] = "@(#)uwinvalP.h	5.4  9/1/88";
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


typedef enum {

    HEADER_HEIGHT,

    ICON_WIDTH,
    ICON_HEIGHT,

    ICON_BODY_TOP,
    ICON_BODY_BOTTOM,
    ICON_BODY_LEFT,
    ICON_BODY_RIGHT,

    ICON_RES_TOP,
    ICON_RES_BOTTOM,
    ICON_RES_LEFT,
    ICON_RES_RIGHT,

    ICON_HOST_TOP,
    ICON_HOST_BOTTOM,
    ICON_HOST_LEFT,
    ICON_HOST_RIGHT,

    ICON_NAME_TOP,
    ICON_NAME_BOTTOM,
    ICON_NAME_LEFT,
    ICON_NAME_RIGHT,

    CLIENT_MIN_WIDTH,
    CLIENT_MIN_HEIGHT,
    CLIENT_MAX_WIDTH,
    CLIENT_MAX_HEIGHT,

    NORMAL_DESIRED_WIDTH,
    NORMAL_DESIRED_HEIGHT,
    ZOOM_DESIRED_WIDTH,
    ZOOM_DESIRED_HEIGHT,

    USER_NORMAL_MIN_WIDTH,
    USER_NORMAL_MIN_HEIGHT,
    USER_ZOOM_MIN_WIDTH,
    USER_ZOOM_MIN_HEIGHT,
 
    USER_MAX_WIDTH,
    USER_MAX_HEIGHT,

    LENGTH_USER_WINDOW_VALUES
} User_Window_Values;

