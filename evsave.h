/*
#ifndef lint
static char sccs_id[] = "@(#)evsave.h	5.6 9/1/88  Siemens Corporate Research and Support, Inc.";
#endif
*/
/* 
  RTL Menu Package Version 1.2
  by Joe Camaratta and Mike Berman, Siemens RTL, Princeton NJ, 1988

  evsave.h: external definitions for evsave package
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

extern void SaveEvents(/* Display *, EventStore *, unsigned long */);
extern void RestoreEvents(/* Display *, EventStore * */);
extern void DisposeEvents(/* Display *, unsigned long */);
extern void DiscardEventStore(/* EventStore * */);
extern void AddEventToStore(/* EventStore *, XEvent */);
extern void RemoveEventFromStore(/* EventStore *, XEvent */);
extern EventStore GetEventStore(/* */);
extern bool EventStoreIsEmpty(/* EventStore * */);
