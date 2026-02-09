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

/* 
  RTL Menu Package Version 1.2
  by Joe Camaratta and Mike Berman, Siemens RTL, Princeton NJ, 1988

  evstack.c: stack implementation for X events
*/

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#include "evstackP.h"

bool EventStackIsEmpty(EventStk)
    EventStack EventStk;
{
    return (EventStk == NullStack);
}


void PushEvent(event, EventStk)
    XEvent *event;
    EventStack *EventStk;
{
    EventNode *new_node;
    
    new_node = (_EventStack)malloc(sizeof(EventNode));
    new_node->next = *(_EventStack *)EventStk;
    new_node->event = *event;
    *EventStk = (EventStack)new_node;
}

EventStack EmptyEventStack()
{
    return NullStack;
}


XEvent PopEvent(EventStk)
    EventStack *EventStk;
{
    EventNode *old_node;
    XEvent pop_event;

    old_node = *(_EventStack *)EventStk;
    *EventStk = (EventStack)old_node->next;
    pop_event = old_node->event;
    free((pointer)old_node);
    return pop_event;
}
