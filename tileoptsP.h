/*
static char sccs_id[] = "@(#)tileoptsP.h	5.4  9/1/88";
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

    ADJUST_PLACEMENT_FAIRLY,
    ALLOW_AUTOMATIC_CLOSE,
    ALLOW_AUTO_CLOSE_MORE_RECENT,
    ALLOW_AUTOMATIC_SHRINK,
    ALLOW_AUTO_SHRINK_MORE_RECENT,
    BEST_FIT_IS_TIGHT,
    BREAK_MINIMUMS_FAIRLY,
    ENABLE_GRAVITY,
    ENFORCE_MAXIMUMS,
    ENFORCE_MINIMUMS,
    FIRST_FIT,
    PREFER_CLOSE_TO_SHRINK,
    PREFER_AUTOMATIC_CLOSE_TO_SEARCH,
    PREFER_AUTO_SHRINK_TO_SEARCH,
    PREFER_SHRINK_TO_SEARCH,
    PRORATE_VERTICALLY_FIRST,

    LENGTH_GLOBAL_OPTIONS
} Global_Options;

