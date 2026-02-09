/*
static char sccs_id[] = "@(#)userglobD.h	5.5  9/1/88";
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



#ifndef USERGLOBALS
#define USERGLOBALS
#endif

#include "uservalsP.h"
#include "useroptsP.h"
#include "exploptsP.h"

/* ------------------------------------------------------------ */

extern bool user_global_options[];

#define UserGlobals_Set_Option(opt,val) \
    user_global_options[(int)(opt)] = (val)

#define UserGlobals_Get_Option(opt) \
    ( user_global_options[(int)(opt)] )

/* ------------------------------------------------------------ */

extern int user_global_values[];

#define UserGlobals_Set_Value(opt,val) \
    user_global_values[(int)(opt)] = (val)

#define UserGlobals_Get_Value(opt) \
    ( user_global_values[(int)(opt)] )

#define BORDER_SIZE_VAL  UserGlobals_Get_Value( BORDER_SIZE )
#define GADGET_WIDTH_VAL  UserGlobals_Get_Value( GADGET_WIDTH )
#define OUTER_BORDER_LINEWIDTH_VAL  UserGlobals_Get_Value( OUTER_BORDER_LINEWIDTH )
#define INNER_BORDER_LINEWIDTH_VAL  UserGlobals_Get_Value( INNER_BORDER_LINEWIDTH )

/* ------------------------------------------------------------ */

extern bool explicit[];

#define Explicit_Global_Get(opt) \
    ( explicit[(int)(opt)] )

#define Explicit_Global_Set(opt) \
    (explicit[(int)(opt)]) = TRUE

#define Explicit_Global_Clear(opt) \
    (explicit[(int)(opt)]) = FALSE
