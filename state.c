#ifndef lint
static char sccs_id[] = "@(#)state.c	5.3  9/1/88";
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

#include "basetype.h"
#include "stateP.h"

#ifndef TILWIN_INTERN
#include "twinI.h"
#endif

static Tilwin	*Openp, *Closedp, 
		*Just_Openp, *Just_Modifiedp, *Just_Closedp;

static TimeStamp timestamp = 1;
static TimeStamp nextstamp = 1;

static int transacting = 0;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

bool State_Was_Just_Modified( winp )
    Tilwin *winp;
{
    return ( (winp->modify_stamp) == timestamp );
}

/* ------------------------------------------------------------ */

bool State_Was_Just_Changed( winp )
    Tilwin *winp;
{
    return ( (winp->affect_stamp) == timestamp );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void State_Start_Operation()
{
    if (transacting == 0)
    {
        nextstamp++;
        timestamp = nextstamp;
        Just_Modifiedp = WINP_NULL;
        Just_Openp = WINP_NULL;
        Just_Closedp = WINP_NULL;
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void State_Save( winp )
    Tilwin *winp;
{
    if ( (winp->affect_stamp) != timestamp )
    {
        winp->prev_center = winp->center;
        winp->prev_size = winp->size;
        winp->prev_rect = winp->rect;

        winp->prev_timestamp = winp->timestamp;
        winp->affect_stamp = timestamp;
        winp->prev_Am_I_Open = winp->Am_I_Open;
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void State_Insert_Closed( winp )
    Tilwin *winp;
{
    winp->closedp = Closedp;
    Closedp = winp;
}

/* ------------------------------------------------------------ */

static void State_Insert_Closed_Ordered( winp )
    Tilwin *winp;
{ 
    Tilwin *lookwin, *prevwin;
    
    lookwin = Closedp;

    prevwin = WINP_NULL;
    while ( (lookwin != WINP_NULL) && 
            ( (winp->timestamp) < (lookwin->timestamp) ) )
    {
        prevwin = lookwin;
        lookwin = lookwin->closedp;
    }
    if (prevwin == WINP_NULL)
        Closedp = winp;
    else
        prevwin->closedp = winp;
    winp->closedp = lookwin;
}

/* ------------------------------------------------------------ */

static void State_Remove_Closed(winp)
    Tilwin *winp;
{ 
    Tilwin *lookwin, *prevwin;
    
    lookwin = Closedp;

    prevwin = WINP_NULL;
    while (lookwin != winp)
    {
        prevwin = lookwin;
        lookwin = lookwin->closedp;
    }
    if (prevwin == WINP_NULL)
        Closedp = lookwin->closedp;
    else
        prevwin->closedp = lookwin->closedp;
}

/* ------------------------------------------------------------ */

static void State_Insert_Open( winp )
    Tilwin *winp;
{
    winp->openp = Openp;
    Openp = winp;
}

/* ------------------------------------------------------------ */

static void State_Insert_Open_Ordered( winp )
    Tilwin *winp;
{ 
    Tilwin *lookwin, *prevwin;
    
    lookwin = Openp;

    prevwin = WINP_NULL;
    while ( (lookwin != WINP_NULL) && 
            ( (winp->timestamp) < (lookwin->timestamp) ) )
    {
        prevwin = lookwin;
        lookwin = lookwin->openp;
    }
    if (prevwin == WINP_NULL)
        Openp = winp;
    else
        prevwin->openp = winp;
    winp->openp = lookwin;
}

/* ------------------------------------------------------------ */

static void State_Remove_Open( winp )
    Tilwin *winp;
{ 
    Tilwin *lookwin, *prevwin;
    
    lookwin = Openp;

    prevwin = WINP_NULL;
    while (lookwin != winp)
    {
        prevwin = lookwin;
        lookwin = lookwin->openp;
    }
    if (prevwin == WINP_NULL)
        Openp = lookwin->openp;
    else
        prevwin->openp = lookwin->openp;
}

/* ------------------------------------------------------------ */

static void State_Insert_Just_Closed( winp )
    Tilwin *winp;
{
    winp->modify_stamp = 0;
    winp->justp = Just_Closedp;
    Just_Closedp = winp;
}

/* ------------------------------------------------------------ */

static void State_Remove_Just_Closed( winp )
    Tilwin *winp;
{ 
    Tilwin *lookwin, *prevwin;
    
    lookwin = Just_Closedp;

    prevwin = WINP_NULL;
    while (lookwin != winp)
    {
        prevwin = lookwin;
        lookwin = lookwin->justp;
    }
    if (prevwin == WINP_NULL)
        Just_Closedp = lookwin->justp;
    else
        prevwin->justp = lookwin->justp;
}

/* ------------------------------------------------------------ */

static void State_Insert_Just_Open( winp )
    Tilwin *winp;
{
    winp->justp = Just_Openp;
    Just_Openp = winp;
}

/* ------------------------------------------------------------ */

static void State_Remove_Just_Open( winp )
    Tilwin *winp;
{ 
    Tilwin *lookwin, *prevwin;

    lookwin = Just_Openp;

    prevwin = WINP_NULL;
    while (lookwin != winp)
    {
        prevwin = lookwin;
        lookwin = lookwin->justp;
    }
    if (prevwin == WINP_NULL)
        Just_Openp = lookwin->justp;
    else
        prevwin->justp = lookwin->justp;
}

/* ------------------------------------------------------------ */

void State_Insert_Just_Modified( winp )
    Tilwin *winp;
{
    if ( (winp->modify_stamp) != timestamp )
    {
        winp->modify_stamp = timestamp;
        winp->justp = Just_Modifiedp;
        Just_Modifiedp = winp;
    }
}

/* ------------------------------------------------------------ */

static void State_Remove_Just_Modified( winp )
    Tilwin *winp;
{ 
    Tilwin *lookwin, *prevwin;

    winp->modify_stamp = 0;
    
    lookwin = Just_Modifiedp;

    prevwin = WINP_NULL;
    while (lookwin != winp)
    {
        prevwin = lookwin;
        lookwin = lookwin->justp;
    }
    if (prevwin == WINP_NULL)
        Just_Modifiedp = lookwin->justp;
    else
        prevwin->justp = lookwin->justp;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void State_Set_Window_Timestamp( winp, stamp )
    Tilwin *winp;
    TimeStamp stamp;
{
    if ( (stamp > timestamp) || (stamp <= 0)  ) return;
    winp->timestamp = stamp;
    if ( winp->Am_I_Open )
    {
        State_Remove_Open( winp );
        State_Insert_Open_Ordered( winp );
    }
    else
    {
        State_Remove_Closed( winp );
        State_Insert_Closed_Ordered( winp );
    }
}

/* ------------------------------------------------------------ */

void State_Note_Use( winp )
    Tilwin *winp;
{
    if (transacting == 0)
        nextstamp++;
    State_Set_Window_Timestamp( winp, nextstamp );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void State_Create(winp)
    Tilwin *winp;
{
    winp->timestamp = 0;
    winp->affect_stamp = 0;
    winp->modify_stamp = 0;
    winp->Am_I_Open = FALSE;
    winp->Was_Auto_Closed = FALSE;
    State_Insert_Closed_Ordered(winp);
}

/* ------------------------------------------------------------ */

void State_Destroy(winp)
    Tilwin *winp;
{
    winp->timestamp = (long) 0;
    State_Remove_Closed(winp);
    if ( (winp->affect_stamp) == timestamp )
    {
        if (winp->prev_Am_I_Open)
            State_Remove_Just_Closed(winp);
    }
}

/* ------------------------------------------------------------ */

void State_Manual_Close( winp )
    Tilwin *winp;
{
    State_Save(winp);
    State_Remove_Open(winp);
    winp->Am_I_Open = FALSE;
    winp->Was_Auto_Closed = FALSE;
    if (! winp->prev_Am_I_Open)
    {
        State_Remove_Just_Open(winp);
        winp->timestamp = winp->prev_timestamp;
        State_Insert_Closed_Ordered(winp);
    }
    else
    {
        if ( State_Was_Just_Modified(winp) )
            State_Remove_Just_Modified(winp);
        State_Insert_Just_Closed(winp);
        winp->timestamp = timestamp;
        State_Insert_Closed(winp);
    }
}

/* ------------------------------------------------------------ */

void State_Auto_Close( winp )
    Tilwin *winp;
{
    State_Manual_Close( winp );
    winp->Was_Auto_Closed = TRUE;
    winp->center = winp->prev_center;
    winp->size = winp->prev_size;
    winp->rect = winp->prev_rect;
}

/* ------------------------------------------------------------ */

void State_Open( winp )
    Tilwin *winp;
{
    State_Save(winp);
    if (winp->Am_I_Open)
    {
        if (winp->prev_Am_I_Open)
        {
            State_Insert_Just_Modified(winp);
        }
    }
    else
    {
        State_Remove_Closed(winp);
        winp->Am_I_Open = TRUE;
        if (winp->prev_Am_I_Open)
        {
            State_Remove_Just_Closed(winp);
            State_Insert_Just_Modified(winp);
            winp->timestamp = winp->prev_timestamp;
            State_Insert_Open_Ordered(winp);
        }
        else
        {
            State_Insert_Just_Open(winp);
            winp->timestamp = timestamp;
            State_Insert_Open(winp);
        }
    }
}

/* ------------------------------------------------------------ */

void State_Act_Modified( winp )
    Tilwin *winp;
{
    if ( (transacting > 0) &&  (winp->Am_I_Open) )
    {
        State_Save(winp);
        if (winp->prev_Am_I_Open)
        {
            State_Insert_Just_Modified(winp);
        }
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

TimeStamp State_Get_Timestamp()
{

    return timestamp;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

WinpHandle State_Gen_Open_Windows()
{
        Tilwin window;
        WinpHandle handle;
        handle.winp = Openp;
        handle.offset = (int) &window.openp - (int) &window;
        return handle;
}

/* ------------------------------------------------------------ */

WinpHandle State_Gen_Closed_Windows()
{
        Tilwin window;
        WinpHandle handle;
        handle.winp = Closedp;
        handle.offset = (int) &window.closedp - (int) &window;
        return handle;
}

/* ------------------------------------------------------------ */

WinpHandle State_Gen_Just_Opened_Windows()
{
        Tilwin window;
        WinpHandle handle;
        handle.winp = Just_Openp;
        handle.offset = (int) &window.justp - (int) &window;
        return handle;
}

/* ------------------------------------------------------------ */

WinpHandle State_Gen_Just_Modified_Windows()
{
        Tilwin window;
        WinpHandle handle;
        handle.winp = Just_Modifiedp;
        handle.offset = (int) &window.justp - (int) &window;
        return handle;
}

/* ------------------------------------------------------------ */

WinpHandle State_Gen_Just_Closed_Windows()
{
        Tilwin window;
        WinpHandle handle;
        handle.winp = Just_Closedp;
        handle.offset = (int) &window.justp - (int) &window;
        return handle;
}

/* ------------------------------------------------------------ */
void
State_Next_Window( handlep )
    WinpHandle *handlep;
{
    if ( (handlep->winp) != WINP_NULL)
        handlep->winp =
           *( (Tilwin **)( ((char *)(handlep->winp)) + (handlep->offset) ) );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void State_Swap( winp )
    Tilwin *winp;
{
    TWPoint temp_center;
    Size temp_size;
    TWRectangle temp_rect;
    TimeStamp temp_stamp;
    bool temp_open;

    temp_stamp = winp->prev_timestamp;
    temp_center = winp->prev_center;
    temp_size = winp->prev_size;
    temp_rect = winp->prev_rect;
    temp_open = winp->prev_Am_I_Open;

    winp->prev_timestamp = winp->timestamp;
    winp->prev_center = winp->center;
    winp->prev_size = winp->size;
    winp->prev_rect = winp->rect;
    winp->prev_Am_I_Open = winp->Am_I_Open;

    winp->timestamp = temp_stamp;
    winp->center = temp_center;
    winp->size = temp_size;
    winp->rect = temp_rect;
    winp->Am_I_Open = temp_open;
}

/* ------------------------------------------------------------ */

void State_Undo()
{
    Tilwin *winp;
    WinpHandle handle;

    handle = State_Gen_Just_Opened_Windows();
    while ( ( winp = State_Coerce(handle) ) != WINP_NULL )
    {
        State_Swap(winp);
        State_Remove_Open(winp);
        State_Insert_Closed_Ordered(winp);
        State_Next_Window(&handle);
    }

    handle = State_Gen_Just_Modified_Windows();
    while ( ( winp = State_Coerce(handle) ) != WINP_NULL )
    {
        State_Swap(winp);
        State_Next_Window(&handle);
    }

    handle = State_Gen_Just_Closed_Windows();
    while ( ( winp = State_Coerce(handle) ) != WINP_NULL )
    {
        State_Swap(winp);
        State_Remove_Closed(winp);
        State_Insert_Open_Ordered(winp);
        State_Next_Window(&handle);
    }
    
    winp = Just_Openp;
    Just_Openp = Just_Closedp;
    Just_Closedp = winp;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

int State_Transaction_Depth()
{
    return transacting;
}

/* ------------------------------------------------------------ */

void State_Start_Transaction()
{
    State_Start_Operation();
    transacting++;
}

/* ------------------------------------------------------------ */

void State_Commit_Transaction()
{
    --transacting;
}

/* ------------------------------------------------------------ */

void State_Continue_Transaction()
{
    transacting++;
}

/* ------------------------------------------------------------ */

void State_Abort_Transaction()
{
    Just_Modifiedp = WINP_NULL;
    Just_Openp = WINP_NULL;
    Just_Closedp = WINP_NULL;
    --transacting;
}

/****************************************************************************
 * appended to original state.c
 ****************************************************************************
 */
static Tilwin *Potentially_Modfdp, *Potentially_Closedp;

void
State_Potential_Clear()
{
    Potentially_Modfdp = WINP_NULL;
    Potentially_Closedp = WINP_NULL;
}

WinpHandle
State_Gen_Potentially_Modfd()
{
    Tilwin window;
    WinpHandle handle;
    handle.winp = Potentially_Modfdp;
    handle.offset = (int) &window.potentmp - (int) &window;
    return handle;
}

WinpHandle
State_Gen_Potentially_Closed()
{
    Tilwin window;
    WinpHandle handle;
    handle.winp = Potentially_Closedp;
    handle.offset = (int) &window.potentcp - (int) &window;
    return handle;
}

void
State_Insert_Potentially_Modfd(winp)
    Tilwin *winp;
{
    winp->potentmp = Potentially_Modfdp;
    Potentially_Modfdp = winp;
}

void
State_Insert_Potentially_Closed(winp)
    Tilwin *winp;
{
    winp->potentcp = Potentially_Closedp;
    Potentially_Closedp = winp;
}


void
State_Remove_Potentially_Modfd(winp)
    Tilwin *winp;
{
    Tilwin *lookwin, *prevwin;
    
    lookwin = Potentially_Modfdp;

    prevwin = WINP_NULL;
    while (lookwin != winp) {
        prevwin = lookwin;
	lookwin = lookwin -> potentmp;
    }
    if (prevwin == WINP_NULL)
        Potentially_Modfdp = lookwin->potentmp;
    else 
	prevwin->potentmp = lookwin->potentmp;
}

void
State_Remove_Potentially_Closed(winp)
    Tilwin *winp;
{
    Tilwin *lookwin, *prevwin;
    
    lookwin = Potentially_Closedp;

    prevwin = WINP_NULL;
    while (lookwin != winp) {
        prevwin = lookwin;
	lookwin = lookwin -> potentcp;
    }
    if (prevwin == WINP_NULL)
        Potentially_Closedp = lookwin->potentcp;
    else 
	prevwin->potentcp = lookwin->potentcp;
}
