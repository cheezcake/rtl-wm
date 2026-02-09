#ifndef lint
static char sccs_id[] = "%W%  %H%";
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
#include "copyright.h"

#include <stdio.h>
#include <X11/Xlib.h>

int errorStatus = False;
int xerror_forceCoreDump = False;


/*  Handler for error events from Xlib procedures.
 *  Borrowed from clients/wm/errHndlr.c...
 */
int
Error_Handler(dpy, error)
    Display  *dpy;
    XErrorEvent  *error;
{
    char buffer[BUFSIZ];


    XGetErrorText(dpy, error->error_code, buffer, BUFSIZ);

    (void) fprintf(stderr, "RTL: X Error <%s>\n", buffer);
    (void) fprintf(stderr, "  Request Major code: %d\n", error->request_code);
    (void) fprintf(stderr, "  Request Minor code: %d\n", error->minor_code);
    (void) fprintf(stderr, "  ResourceId: %d\n", error->resourceid);
    (void) fprintf(stderr, "  Error Serial #%d\n", error->serial);
    //(void) fprintf(stderr, "  Current Serial #%d\n", dpy->request);

    errorStatus = True;

    if (xerror_forceCoreDump) {
	int *foo = (int*) 0;

	fprintf (stderr, "Forcing core dump.\n");

	*foo = 50;
    }

    return 0;
}    
