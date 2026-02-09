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

  evsave.c: saves/restores the X event queue
*/

#include <stdio.h>

#include "evstackX.h"
#include "evsaveP.h"

void SaveEvents(display, Stack, mask)
    Display *display;
    EventStore *Stack;
    unsigned long mask;	 /* Save only events that match mask; */
			 /* others remain on the event queue  */
{
    XEvent ev;
    bool Match = TRUE;


    *Stack = (EventStore)EmptyEventStack();

    while (XPending(display) && Match)
    {
	if (XCheckMaskEvent(display, mask, &ev))
	{
	    PushEvent(&ev, (EventStack *)Stack);
	}
	else
	    Match = FALSE;
    }
    return;
    
}

void RestoreEvents(display, Stack)
    Display *display;
    EventStore *Stack;    /* pointer to stack containing saved events */
{
    XEvent ev;

    
    while (!EventStackIsEmpty((EventStack)*Stack))
    {
	ev = PopEvent((EventStack *)Stack);
	XPutBackEvent(display, &ev);
    }
    XFlush(display);
    return;
    
}

void DisposeEvents(display, mask)
    Display *display;
    unsigned long mask;	 /* dispose events that match mask */
{
    bool Match = TRUE;
    XEvent ev;
    

    while (XPending(display) && Match)
    {
	if (XCheckMaskEvent(display, mask, &ev))
	{
	}
	else
	    Match = FALSE;
    }
    return;
    
}
	
void DiscardEventStore(Stack)
    EventStore *Stack;
{
    
    while (!EventStackIsEmpty((EventStack)*Stack))
    {
	(void) PopEvent((EventStack *)Stack);
    }
}

void AddEventToStore(Stack, ev)
    EventStore *Stack;
    XEvent ev;
{
    PushEvent(&ev, (EventStack *)Stack);
}

void RemoveEventFromStore(Stack, ev)
    EventStore *Stack;
    XEvent *ev;
{
    *ev = PopEvent((EventStack *)Stack);
}

EventStore GetEventStore()
{
    return (EventStore)EmptyEventStack();
}

bool EventStoreIsEmpty(Stack)
    EventStore *Stack;
{
    return EventStackIsEmpty((EventStack)*Stack);
}
