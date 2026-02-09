
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

Check_Select( evstr, str )
    char *evstr;
    char *str;
{
/*    printf( "%s: %s\n", evstr, str ); */
}

Check_Select_WAIT( str )
    char *str;
{
    Check_Select( "WAIT", str );
}

Check_Select_UP( str )
    char *str;
{
    Check_Select( "UP", str );
}

Check_Select_DOWN( str )
    char *str;
{
    Check_Select( "DOWN", str );
}

Check_Select_KEY( str )
    char *str;
{
    Check_Select( "KEY", str );
}

Check_Select_MOUSE( str )
    char *str;
{
}

Check_Select_mouse( str )
    char *str;
{
}

Check_Select_button( str )
    char *str;
{
    Check_Select( "button", str );
}

Check_Select_leave( str )
    char *str;
{
    Check_Select( "leave", str );
}

Check_Select_reenter( str )
    char *str;
{
    Check_Select( "reenter", str );
}

Check_Event( id )
{
/*     printf( "%d\n", id ); */
}
