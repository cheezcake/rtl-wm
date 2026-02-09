/*
static char sccs_id[] = "@(#)twinI.h	5.4  9/1/88";
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

#define TILWIN_INTERN

#include "basetype.h"

#ifndef TILWIN
#include "twinP.h"
#endif

typedef struct str_window Tilwin;

#define WINP_NULL (Tilwin *)NULL

struct str_window
{
	pointer		id;		/* window ID */
        pointer         data;           /* for the user */


	TWRectangle	rect,		/* current rectangle position */
			prev_rect,	/* previous "rect" */
			modify_rect;	/* potential modification rect */

	Size		min_size,
			max_size,
			size,

			modify_size,	/* potential modification size */
			open_size,
			prev_size,	/* previous open_size */

                        desired_size;

	Side		modify_side;

	TWPoint		center,
			prev_center;

        TWPoint         position;
        
	bool		options[ (int) LENGTH_WINDOW_OPTIONS ];

	bool		Am_I_Open;
	bool		prev_Am_I_Open;

	bool		Was_Auto_Closed;

	long		affect_stamp;	/* was just affected */
	long		modify_stamp;	/* was just modified */

	long		timestamp,	/* Use or Close relative timestamp */
			prev_timestamp;	/* for Undo operation*/

	long		open_priority;
	long		size_priority;
	
	pointer		tilep;		/* pointer to associated Tile */

	Tilwin		*openp;		/* Open Lists thread */
	Tilwin		*closedp;		/* Closed Lists thread */

	Tilwin		*justp;		/* Just Opened/Modified thread(s) */
					/* or Just Closed thread */

	Tilwin		*potentmp;	/* Potentially Modified thread */
	Tilwin		*potentcp;	/* Potentially Closed thread */

        long            height_stamp;   /* When desired height set */
        long            width_stamp;   /* When desired width set */

};

