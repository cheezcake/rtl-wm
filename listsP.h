/*
static char sccs_id[] = "@(#)listsP.h	5.4  9/1/88";
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


#define LISTS

#ifndef  STD_DEFS
#include "std_defs.h"
#endif


typedef struct node Node;

struct node
{
    struct node *prev, *next;
    pointer info;
    int id;             /* optional identifier (used in
                                       find operations)             */
};

#define NODE_NULL (Node *)NULL
#define DEFAULT_NODE_ID 0

typedef struct {
                Node *head, *tail;
               }
          List;
	  
#define LIST_NULL (List *)NULL

#define Lists_Convert_Node_Info(node, type) \
	((type)((node)->info))

#define Lists_For_Each_Node_On_List(list, node) \
            for((node)=(list)->head;node;(node)=(node)->next)
