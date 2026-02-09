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
#include <signal.h>

#include "basetype.h"
#include "buttonsP.h"

#include "uwinD.h"
#include "uwinXD.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "xio.h"
#include "assoc.h"
#include "current.h"

extern void Open_Execvp(), Open_Exec();
extern void Property_Set_Wm_State();

extern XEvent *current_Xevent;

/* ------------------------------------------------------------ */

/*ARGSUSED*/
void Client_Redraw(uwinp)
    Userwin        *uwinp;
{
/*    XExposeEvent  ev;


    ev.type = Expose;
    ev.display = dpy;
    ev.window = Userwin_XClient(uwinp);
    ev.x = 0;
    ev.y = 0;
    ev.width = 10000;		/ * large enough area to cover any window! * /
    ev.height = 10000;
    ev.count = 0;

    XSendEvent(dpy, Userwin_XClient(uwinp), False, ExposureMask,
	       (XEvent *) &ev);
*/
}

/* ------------------------------------------------------------ */

    /*  Start up an X client from the Window Manager. */

void Client_Window_Create(cmd)
    char *cmd;
{
    int pid;


    if ((pid = vfork()) == 0)
    {
/*
	int   mypid, i;

	mypid = getpid();
	setpgrp(0, mypid);

	ioctl(0, TIOCSPGRP, &pid);
*/
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	Open_Exec( cmd );

	_exit(-127);
    }
    else if (pid < 0)
    {
	fprintf(stderr, "Client_Window_Create - vfork failed!\n");
    }
	
}

/* ------------------------------------------------------------ */

    /*  Execute Startup file */

void Client_Startup(filnam)
    char *filnam;
{
    int pid;


    if ((pid = vfork()) == 0)
    {
/*
	int   mypid, i;

	mypid = getpid();
	setpgrp(0, mypid);

	ioctl(0, TIOCSPGRP, &pid);
*/
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	Open_Execvp( filnam );

	_exit(-127);
    }
    else if (pid < 0)
    {
	fprintf(stderr, "Client_Startup - vfork failed!\n");
    }
	
}

/* ------------------------------------------------------------ */

void Client_Bang(uwinp)
    Userwin  *uwinp;
{
}

/* ------------------------------------------------------------ */

void Client_Kill(uwinp)
    Userwin  *uwinp;
{
    XKillClient(dpy, Userwin_XClient(uwinp));
    XFlush(dpy);	
}

/* ------------------------------------------------------------ */

    /*  Send the current X event to the named window              */
    /*  WARNING: only works for key & button events -- to extend  */
    /*  it, add the appropriate bits to EV_MASK                   */

#define EV_MASK (KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask)

void Client_Forge_Current_Event(w)
    Window w;
{
    XEvent ev;
    
    ev = *current_Xevent;
    ev.xany.window = w;
    XSendEvent(dpy, w, False, EV_MASK, &ev);
}

/* ------------------------------------------------------------ */

    /*  Send the redirected key event to the X focus window. */

/*ARGSUSED*/
void Client_Send_Key(uwinp, ch)
    Userwin  *uwinp;
    char  ch;
{

    if (current_Xevent->type == KeyPress)
    {
	if (Region_Get_Type(current_region) == body)
	    XAllowEvents(dpy, ReplayKeyboard, CurrentTime);
	else
	    Client_Forge_Current_Event(Userwin_XClient(uwinp));
    }
}

/* ------------------------------------------------------------ */

void Client_Ignore_Key()
{}

/* ------------------------------------------------------------ */

/*ARGSUSED*/
void Client_Menu_Button_Number( num )
    int num;
{}

/* ------------------------------------------------------------ */

    /*  Send the grabbed Button event to the X client. */

/*ARGSUSED*/
void Client_Send_Button(uwinp, kind, button, pos)
    Userwin  *uwinp;
    enum ButKind  kind;
    Buttons  button;
    TWPoint  pos;
{
    if ((current_Xevent->type == ButtonPress) || (current_Xevent->type == ButtonRelease))
    {
	if (Region_Get_Type(current_region) == body)
	    XAllowEvents(dpy, ReplayPointer, CurrentTime);
	else
	    Client_Forge_Current_Event(Userwin_XClient(uwinp));
    }
}


/* ------------------------------------------------------------ */

void Client_Ignore_Button()
{}

/* ------------------------------------------------------------ */

    /*  Send the menu item chosen to the client. */

/*ARGSUSED*/
void Client_Send_String(uwinp, string)
    Userwin        *uwinp;
    char           *string;
{}

/* ------------------------------------------------------------ */

 /*  Send the mouse movement event to the client. */

/*ARGSUSED*/
void Client_Send_Mouse(uwinp, butstate, pos)
    Userwin        *uwinp;
    Button_State    butstate;
    TWPoint           pos;
{}

/* ------------------------------------------------------------ */

    /*  Notify client of mouse motion events inside its window. */

/*ARGSUSED*/
void Client_Enter(uwinp, butstate, pt)
    Userwin        *uwinp;
    Button_State    butstate;
    TWPoint           pt;
{}

/* ------------------------------------------------------------ */

    /*  Notify the X client to set focus to itself. */

/*ARGSUSED*/
void Client_Take_Focus(uwinp)
    Userwin  *uwinp;
{
    
}

/* ------------------------------------------------------------ */

void Client_Set_State( uwinp )
    Userwin *uwinp;
{
    (void)Property_Set_Wm_State(uwinp, Userwin_Wm_State(uwinp));
}

/* ------------------------------------------------------------ */

void Client_Configure_Denied( uwinp )
    Userwin *uwinp;
{}

/* ------------------------------------------------------------ */

void Client_Window_Moved( uwinp )
    Userwin *uwinp;
{}

/* ------------------------------------------------------------ */

void Client_Delete_Window( uwinp )
    Userwin *uwinp;
{}

/* ------------------------------------------------------------ */

void Client_Icon_Notify( uwinp )
    Userwin *uwinp;
{}


