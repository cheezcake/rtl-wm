/*
static char sccs_id[] = "@(#)gravity.h	5.3  9/1/88";
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

#ifndef BASETYPE
#include "basetype.h"
#endif

#define GRAVITY


extern void		Gravity_Insert_Edge();
	/* Basetype edge_coord;
	 * Side side;
	 */

extern void		Gravity_Delete_Edge();
	/* Basetype edge_coord;
	 * Side side;
	 */

extern void		Gravity_Adjust();
	/* TWRectangle *rectp;
	 */

extern Basetype		Gravity_Adjust_Edge();
	/* Basetype edge_coord;
	 * Side side;
	 */

extern void Gravity_Init();

extern Basetype Gravity_Difference();
