/*
#ifndef lint
static char sccs_id[] = "@(#)rtlmenuSH.h	5.5 9/1/88  Siemens Corporate Research and Support, Inc.";
#endif
*/

/*
  RTL Menu Package Version 1.2
  by Joe Camaratta and Mike Berman, Siemens RTL, Princeton NJ, 1988

  rtlmenuSH.h: shared declarations for RTLMenu package
*/

/*

Copyright 1988 by
	Siemens Corporate Research and Support, Inc., Princeton, New Jersey

Permission to use, copy, modify, and distribute this software
and its documentation for any purpose and without fee is
hereby granted, provided that the above copyright notice
appear in all copies and that both that copyright notice and
this permission notice appear in supporting documentation, and
that the name of Siemens not be used in advertising or
publicity pertaining to distribution of the software without
specific, written prior permission.  Siemens makes no
representations about the suitability of this software for any
purpose.  It is provided "as is" without express or implied
warranty.

*/

#include <stdio.h>

#ifndef STD_DEFS
#include "std_defs.h"
#endif

#include <X11/Xlib.h>

/* flags for menu operation */

typedef unsigned int RTLMenuOptionsMask;

#define clickokay   (1L<<0) /* click-click equivalent to press-release  */
#define savebits    (1L<<1) /* attempt to save/restore area under menu  */
#define fixedchild  (1L<<2) /* pull up child in fixed (horizontal)      */
                            /* position relative to parent              */
#define rightoffset (1L<<3) /* when pulling up on right edge, should    */
                            /* child be offset to left, allowing parent */
                            /* to remain visible                        */
#define bigoffset   (1L<<4) /* valid only when rightoffset=1.  Offset   */
                            /* child far enough to see most of parent;  */
                            /* else, just enough to get back to parent. */
#define forgetlast  (1L<<5) /* ordinarily, last menu selection is       */
                            /* recalled and returned to; if this set,   */
                            /* don't do this.                           */

enum generic_tag {long_gen, pointer_gen};

typedef struct _gen 
{
    enum generic_tag tag;
    union  
    {
	long l;
	pointer p;
    }
    val;
}
generic;

/* Generic type manipulation */

#define SetGenLong(g,i) (g.tag = long_gen, g.val.l = i)
#define GetGenLong(g) ((g.tag == long_gen)? g.val.l: 0)
#define CastGenLong(g,i) (SetGenLong(g,i), g)
#define GenLongP(g) (g.tag == long_gen)

#define SetGenPointer(g,pt) (g.tag = pointer_gen, g.val.p = pt)
#define GetGenPointer(g) ((g.tag == pointer_gen)? g.val.p: (pointer)NULL)
#define CastGenPointer(g,pt) (SetGenPointer(g,pt), g)
#define GenPointerP(g) (g.tag == pointer_gen)

#define EqualGen(a,b) \
    ((a.tag != b.tag)? FALSE : \
     ((a.tag == long_gen)? (a.val.l == b.val.l) : (a.val.p == b.val.p)))

typedef pointer RTLMenu;
typedef pointer RTLMenuItem;
typedef struct _RTLPoint
{
    int x, y;
}
RTLPoint;

typedef bool (*BoolFunc)();



