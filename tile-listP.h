/*
static char sccs_id[] = "@(#)tile-listP.h	5.4  9/1/88";
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


/*
 * Tile list manipulation routines
 */

typedef struct tile_element Tile_Element;
struct tile_element{
    Tile *tptr;
    Tile_Element *next;
};

typedef struct tile_list Tile_List;
struct tile_list{
    Tile_Element *first;
    Tile_Element *last;
    Tile_Element *current;
};

#define TENULL ((Tile_Element *) 0)

/* The variables in the macro definition refer to the
 * following types:
 *
 * Tile *tile
 * Tile_List list
 * Tile_Element *element
 */

/* add a tile to a list */
#define TL_ADD(tile,  list) \
{ \
     register Tile_Element *TE; \
     TE_ALLOC(TE); \
     TE->tptr = tile; \
     TE->next = TENULL; \
     if(list.first == TENULL) \
	list.first = list.last = TE; \
     else{ \
         list.last->next = TE; \
	 list.last = TE; \
     } \
}

/* free all elements on the list */
#define TL_FREE(list) \
{ \
    register Tile_Element *TE; \
    while (list.first != TENULL) { \
        TE = list.first; \
	list.first = TE->next; \
	TE_FREE(TE); \
    } \
    list.first = list.last = list.current = TENULL; \
}

/* get the next tile on a list */
#define TL_NEXT(tile, list) \
{ \
    if (list.first != TENULL) { \
        if(list.current == TENULL){ \
	    tile = list.first->tptr; \
	    list.current = list.first->next; \
	    if(list.current == TENULL){ \
	        list.current = list.first; \
	    } \
	} \
	else if (list.current == list.first) { \
	    tile = NULL_TILE; \
	} \
	else{ \
	    tile = list.current->tptr; \
	    list.current = list.current->next; \
	    if (list.current == TENULL) { \
	        list.current = list.first; \
	    } \
	} \
    } \
    else{ \
        tile = NULL_TILE; \
    } \
}

#define TE_ALLOC(element) \
{ \
    if (te_freelist == TENULL) { \
     if ((element = (Tile_Element *) malloc(sizeof(Tile_Element))) == TENULL) \
	Tile_Panic("tl_alloc malloc failed."); \
    } \
    else{ \
        element = te_freelist; \
	te_freelist = te_freelist->next; \
    } \
}

#define TE_FREE(element) \
{ \
    element->next = te_freelist; \
    te_freelist = element; \
    element = TENULL; \
}

extern Tile_Element *te_freelist;
