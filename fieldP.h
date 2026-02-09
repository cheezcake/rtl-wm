/*
static char sccs_id[] = "@(#)fieldP.h	5.4  9/1/88";
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
#define FIELD
#endif

#define unshifted(i,fld) ( (i) >> (fld) )
    /* returns i shifted right fld spaces */

#define shifted(i,fld) ( (i) << (fld) )
    /* returns i shifted left fld spaces */

/* ----------------------------------------------------------------- */

#define lowmask(wid) ( (1 << wid) - 1 )
    /* returns a mask of the rightmost wid bits */

#define mask(fld,wid) shifted( lowmask(wid), fld )
    /* returns a mask of width wid at field fld */

#define onemask(fld) shifted( 1, fld )
    /* returns a mask with a bit in fld */

/* ----------------------------------------------------------------- */

#define lowmasked(i,wid) ( i & lowmask(wid) )
    /* returns the bottom wid bits of i */

#define masked(i,fld,wid) ( i & mask(fld,wid) )
    /* returns i masked by the wid bits at field fld */

#define onemasked(i,fld) ( i & onemask(fld) )
    /* returns i masked by bit at fld */

/* ----------------------------------------------------------------- */

#define extract(i,fld,wid) ( unshifted(i,fld) & lowmask(wid) )
    /* returns the wid bits of i at filed fld */

#define intract(i,fld,wid) shifted( lowmasked(i,wid), fld )
    /* returns i placed in field fld with width wid */

/* ----------------------------------------------------------------- */

#define is_set(i,fld) onemasked(i,fld)
    /* returns non-zero if bit fld is set */

#define any_set(i,fld,wid) masked(i,fld,wid)
    /* returns non-zero if any bit in fld,wid is set */

#define all_set(i,fld,wid) ( masked(i,fld,wid) == mask(fld,wid) )
    /* returns true if all bits in fld,wid is set */

