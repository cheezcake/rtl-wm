/*
static char sccs_id[] = "@(#)uwinP.h	5.4  9/1/88";
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

#define USERWIN

#ifndef BASETYPE
#include "basetype.h"
#endif

#ifndef REGION
#include "regionP.h"
#endif

#ifndef TILWIN_DEFINE
#include "twinD.h"
#endif

#include "uwinoptP.h"
#include "explwoptsP.h"

#include "platformP.h"

typedef struct str_userwin Userwin;

#define UWIN_NULL (Userwin *)NULL

struct str_userwin {

    Tilwinp winp;       /* The body window */
    Tilwinp iconp;      /* The icon window if not separate */

    Region_Enum current_type;  /* body, icon, or rtl */

    int winnum;
    pointer data;
    
    char *hostname;
    char *res_class;
    char *res_name;
    char *wmname;
    char *iconname;
    char *command;
    char *identity;
    char *title;
    
    bool options[(int)LENGTH_USER_WINDOW_OPTIONS];  
    bool explicit[(int)LENGTH_EXPLICIT_WINDOW_OPTIONS];
        
    bool prepared;      /* Has window been prepared */
    bool layout;      /* Has attempt been made to lay it out? */
    bool layout_found;      /* Has window been laid out? */
    bool positioned;    /* Does window have a position */
    bool ever_opened;    /* Has window ever been opened */
    bool sized;         /* Does window have a size */
    bool listener;         /* is window the listener */
    bool regular_manual_close;
                        /* whether manual close is req when not listener */
    bool icon_positioned;    /* Does icon have a position */

    bool focus;      /* is window the focus */
    int client_state;      /* window state set by client */
    int wm_state;      /* window state set by wm */
    int startup_state; /* window state at startup */
    int group_state;   /* old state when group iconized */

    TimeStamp open_stamp;    /* TimeStamp when the window was last opened */
    TimeStamp zoom_stamp;    /* TimeStamp when the window was last zoomed */
    bool zoomed;        /* is window currently zoomed */
    TWRectangle rezoom_rect;   /* Holds the rectangles before (un)zoom */
    Size regular_min;   /* Holds the min for when window is not zoomed */
    Size regular_size;  /* Holds the size for when window is not zoomed */
    Size zoom_min;      /* Holds the min for when window is zoomed */
    Size zoom_size;     /* Holds the size for when window is zoomed */

    bool prev_positioned;
    bool prev_sized;
    bool prev_zoomed;
    int prev_group_state;
    TWRectangle prev_rezoom_rect;
    Size prev_min;
    Size prev_max;
    Size prev_desire;
    TimeStamp undo_stamp;

    Size body_min;    /* Holds the min set by the client */
    Size body_max;    /* Holds the max set by the client */

    Size client_min;    /* Holds the adjusted min set by the client */
    Size client_max;    /* Holds the adjusted max set by the client */

    int header_height;

    bool input_enabled;  /* can the window accept input */
    bool output_sent;    /* Has output been sent since window was closed */
    bool saving_state;   /* Client is saving state */
    bool soft_kill;      /* soft kill was requested */

    int connection;  /* connection id */
    Userwin *group;  /* group this window is part of */
    long messages;     /* messages this client accepts */

    TWRectangle icon_res_rect;  /* Place for res in icon */
    TWRectangle icon_host_rect;  /* Place for host in icon */
    TWRectangle icon_name_rect;  /* Place for wm in icon */
    TWRectangle icon_body_rect;  /* Place for body in icon */

    bool initially_mapped;       /* window initially mapped */
    bool initially_icon_mapped;  /* window's client icon initially
				    mapped */
    
    platform_fields    /* platform-specific fields */

};

