/*
static char sccs_id[] = "@(#)tileopts.h	5.6  9/1/88";
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



extern bool ADJUST_PLACEMENT_FAIRLY;
extern bool ALLOW_AUTOMATIC_CLOSE;
extern bool ALLOW_AUTO_CLOSE_MORE_RECENT;
extern bool ALLOW_AUTOMATIC_SHRINK;
extern bool ALLOW_AUTO_SHRINK_MORE_RECENT;
extern bool BEST_FIT_IS_TIGHT;
extern bool BREAK_MINIMUMS_FAIRLY;
extern bool ENABLE_GRAVITY;
extern bool ENFORCE_MAXIMUMS;
extern bool ENFORCE_MINIMUMS;
extern bool FIRST_FIT;
extern bool PREFER_CLOSE_TO_SEARCH;
extern bool PREFER_CLOSE_TO_SHRINK;
extern bool PREFER_SHRINK_TO_SEARCH;
extern bool PRORATE_VERTICALLY_FIRST;

#define Tilwin_Get_Global_Option(opt) \
    (opt)

#define Tilwin_Set_Global_Option(opt,val) \
    (opt) = (val)
