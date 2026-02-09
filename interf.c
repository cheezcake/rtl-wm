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
#include <stdlib.h>
#include "copyright.h"

#include "basetype.h"

#include "client.h"
#include "closed.h"
#include "control.h"
#include "current.h"
#include "drawicon.h"
#include "drawwin.h"
#include "events.h"
#include "input.h"
#include "layout.h"
#include "manage.h"
#include "message.h"
#include "profile.h"
#include "region.h"    
#include "tilecrsr.h"
#include "tilemenu.h"
#include "twin.h"
#include "tool.h"

#include "userglobD.h"
#include "buttonsD.h"
#include "uwinD.h"
#include "uwinL.h"

#define SMDEBUG
#include "smdebug.h"

#define CLICK_TIME 290 /* in milliseconds */


Buttons TOOL_BUTTONS;
Buttons DISCONNECT_BUTTONS;
Buttons EXIT_BUTTONS;
Buttons BODY_MANAGER_MENU_BUTTONS;
Buttons BODY_USER_MENU_BUTTONS; 
Buttons HEADER_MANAGER_MENU_BUTTONS;
Buttons HEADER_USER_MENU_BUTTONS; 
Buttons ICON_OPEN_BUTTONS;
Buttons ICON_MOVE_BUTTONS;
Buttons CLOSE_BUTTONS;
Buttons REDRAW_BUTTONS;
Buttons ZOOM_BUTTONS;
Buttons ZOOM_LOCK_BUTTONS;
Buttons DESIRE_BUTTONS;
Buttons ENLARGE_BUTTONS;
Buttons MOVE_BUTTONS;
Buttons RELOCATE_BUTTONS; 
Buttons EXCHANGE_BUTTONS;
Buttons RESIZE_BUTTONS;
Buttons TOGGLE_GRAVITY_BUTTONS;
Buttons CANCEL_BUTTONS;
Buttons UNDESIRE_BUTTONS;
Buttons FORCE_RESET_MIN_MAX_BUTTONS;
Buttons FORCE_LISTENER_BUTTONS;
Buttons FORCE_ZOOM_BUTTONS;

static TileMenu manager_title_menu;
static TileMenu manager_tool_menu;
static TileMenu manager_size_menu;
static TileMenu manager_repop_menu;
static TileMenu manager_background_menu;
static TileMenu manager_icon_menu;
static TileMenu manager_window_menu;
static TileMenu manager_window_option_menu;

static Message exitmsg;
static Message pausemsg;
static Message savemsg;
static Message softmsg;
static Message hardmsg;
static Message notifymsg;
static Message groupmsg;

#define user_window_join_excursion(uwin,opt,val,code) \
{ \
    bool temp_val; \
    temp_val = Userwin_Get_Window_Option(uwin,opt); \
    Userwin_Set_Window_Option( uwin, opt, (temp_val || val) ); \
    code; \
    Userwin_Set_Window_Option(uwin,opt,temp_val); \
}


static void Interf_Press();
static void Interf_Click();
static void Interf_Seen_Down();
static void Interf_Press_UP();
static void Interf_Have_Lsnr_swInMod();
static void Interf_Grabbed_Lsnr_swInMod();
static void Interf_Have_Lsnr();
static void Interf_Grabbed_Lsnr();
static void Interf_Am_Lsnr();
static void Interf_Gbd_Sblsnr();
static void Interf_Am_Sblsnr();
static void Interf_Am_Clk_Lsnr();
static void Interf_Gbd_Clk_Sblsnr();
static void Interf_Click_Sblsnr();
static void Interf_Wait_Cmplt_Cancel();
static void Interf_Cancel_Here();
static void Interf_Wait_Complete();
static void Interf_Check_Complete();
static void Interf_Wait_For_Conf();
static void Interf_Trk_Cont_Ctr_Opng();
static void Interf_Trk_Cont_Crnr_Opng();
static void Interf_Start_Continue_Opening();
static void Interf_Track_Opening();
static void Interf_Track_Icon_Opening();
static void Interf_Start_Opening();
static void Interf_Start_Icon_Opening();
static void Interf_Open_In_Icon();
static void Interf_Track_Edge_Rszng();
static void Interf_Track_Crnr_Rszng();
static void Interf_Track_Basing_Rsz();
static void Interf_Track_Moving();
static void Interf_Track_Vert_Moving();
static void Interf_Track_Horiz_Moving();
static void Interf_Track_Icon_Moving();
static void Interf_Track_Exchanging();
static void Interf_Inside_Background();
static void Interf_Inside_Rtl();
static void Interf_Inside_Body();
static void Interf_Inside_Header();
static void Interf_Inside_Icon();
static void Interf_Inside_Zoom_Gadget();
static void Interf_Inside_Move_Gadget();
static void Interf_Inside_Side_Border();
static void Interf_Ins_Crnr_Border();


static void (*button)();

static void Interf_Signal_Button(sigkind)
enum ButKind sigkind;
{
    current_kind = sigkind;
    (*button)();
}

static Buttons down_but;
static TWPoint down_pos;

static Buttons up_but;
static TWPoint up_pos;


static bool tracking = FALSE;
static bool wait_for_click = TRUE;
static bool complete_down = FALSE;
static bool inside_client = FALSE;

static void Interf_Click_DOWN()
{
    extern void Interf_Click();
{

    extern void Interf_Seen_Down();
    extern void Interf_Press();
    down_but = current_but;
    down_pos = current_pos;
    if ( wait_for_click )
    {
        if (tracking)
            (*MOUSE)();    
        { Interf_Seen_Down(); return; }
    }
    else
    {
        wait_for_click = ! inside_client;
        Interf_Signal_Button(down);
        { Interf_Press(); return; }
    }

}
}

static void Interf_Click_UP()
{
    extern void Interf_Click();
{

    Interf_Signal_Button(up);
    { Interf_Click(); return; }

}
}

static void Interf_Click()
{
    DOWN = Interf_Click_DOWN;
    UP = Interf_Click_UP;
}


static void Interf_Seen_Down_WAIT()
{
    extern void Interf_Seen_Down();
{
 
    Interf_Signal_Button(down);
    { Interf_Click(); return; }

}
}

static void Interf_Seen_Down_DOWN()
{
    extern void Interf_Seen_Down();
{
    Input_Cancel_Wait();

    Interf_Signal_Button(down);
    down_but = current_but;
    down_pos = current_pos;
    { Interf_Seen_Down(); return; }

}
}

static void Interf_Seen_Down_UP()
{
    extern void Interf_Seen_Down();
{
    Input_Cancel_Wait();

    if ( Buttons_Equal( current_but, down_but ) )
    {
        Interf_Signal_Button(click);
    }
    else
    {
        up_pos = current_pos;
        up_but = current_but;

        current_pos = down_pos;
        current_but = down_but;

        Interf_Signal_Button(down);

        current_pos = up_pos;
        current_but = up_but;

        Interf_Signal_Button(up);
    }
    { Interf_Click(); return; }

}
}

static void Interf_Seen_Down()
{
    WAIT = Interf_Seen_Down_WAIT;
    DOWN = Interf_Seen_Down_DOWN;
    UP = Interf_Seen_Down_UP;
    Input_Wait(CLICK_TIME);
}


static void Interf_Press_WAIT()
{
    extern void Interf_Press();
{
 
    { Interf_Click(); return; }

}
}

static void Interf_Press_DOWN()
{
    extern void Interf_Press();
{
    Input_Cancel_Wait();

    down_but = current_but;
    down_pos = current_pos;
    if ( wait_for_click )
    {
        if (tracking)
            (*MOUSE)();    
        { Interf_Seen_Down(); return; }
    }
    else
    {
        Interf_Signal_Button(down);
        { Interf_Press(); return; }
    }

}
}

static void Interf_Press_UP()
{
    extern void Interf_Press();
{
    Input_Cancel_Wait();

    if ( complete_down || inside_client ||
         (! Buttons_Equal( current_but, down_but ) ) )
        Interf_Signal_Button(up);
    { Interf_Click(); return; }

}
}

static void Interf_Press()
{
    WAIT = Interf_Press_WAIT;
    DOWN = Interf_Press_DOWN;
    UP = Interf_Press_UP;
    Input_Wait(CLICK_TIME);
}



static Side current_side;
static TWPoint base_pos;
static TWPoint cancel_pos;

static bool menu_at_work = FALSE;
static bool menu_positioned = FALSE;


static void Interf_Set_Pos( pos )
    TWPoint pos;
{
    menu_positioned = FALSE;
    Input_Set_Pos( pos );
}


static TWPoint Interf_Tracking_Offset( pos )
    TWPoint pos;
{
    pos.x -= base_pos.x;
    pos.y -= base_pos.y;
    return pos;
}


static void Interf_Track_Pos( pos )
    TWPoint pos;
{
    Input_Change_Pos( Interf_Tracking_Offset( pos ) );
}


static void Interf_Track_Edge_Pos()
{
    Interf_Track_Pos( Region_Get_Edge_Pos( 
        current_uwinp, current_side, base_pos ) );
}


static void Interf_Track_Corner_Pos()
{
    Interf_Track_Pos( Region_Get_Corner_Pos(
        current_uwinp, current_side ) );
}


static TWPoint Interf_Track_Center_Pos()
{
    TWPoint offset;
    Interf_Track_Pos( Userwin_Get_Center(current_uwinp) );
    offset.x = 0;
    offset.y = 0;
    return offset;
}


static TWPoint Interf_Center_Offset()
{
    return Interf_Tracking_Offset(
        Userwin_Get_Center(current_uwinp) );
}


static TWPoint Interf_Track_Icon_Center_Pos()
{
    TWPoint offset;
    Interf_Track_Pos( Userwin_Get_Icon_Center(current_uwinp) );
    offset.x = 0;
    offset.y = 0;
    return offset;
}


static TWPoint Interf_Icon_Center_Offset()
{
    return Interf_Tracking_Offset(
        Userwin_Get_Icon_Center(current_uwinp) );
}


static bool Interf_Start_Watching()
{
    if ( tracking )
    {
        Control_Set_Cursor( watch_tilecursor );
        return TRUE;
    }
    else
        return Control_Grab_User( FALSE, watch_tilecursor );
}


static void Interf_Stop_Watching()
{
    Control_Restore_Cursor();
    if ( (! tracking) && Control_Pointer_Grabbed() )
        Control_Ungrab_User();
}


#define Interf_Watch(code)  \
{  \
    Interf_Start_Watching();  \
    code;  \
    Interf_Stop_Watching();  \
}


static bool client_watching;

static bool Interf_Client_Start_Watching()
{
    client_watching = ! ( tracking || Control_Pointer_Grabbed() );
    if ( client_watching )
        return Control_Grab_User( FALSE, watch_tilecursor );
    else
        return FALSE;
}


static void Interf_Client_Stop_Watching()
{
    extern void Interf_Reenter_Region();

    if ( client_watching )
    {
        client_watching = FALSE;    
        Interf_Reenter_Region();
    }
}


#define Interf_Client_Watch(code)  \
{  \
    Interf_Client_Start_Watching();  \
    code;  \
    Interf_Client_Stop_Watching();  \
}


static void Interf_Menu_Grab()
{
    if ( menu_positioned )
    {
        cancel_pos = TileMenu_Entry_Pos();
        base_pos = current_pos;
    }
    else
    {
        cancel_pos = down_pos;
        base_pos = down_pos;
    }

    if ( menu_at_work )
    {
        menu_at_work = FALSE;
        Input_Determine_Buttons();
    }
}


static void Interf_Reset_Menu_Pos()
{
    cancel_pos = TileMenu_Entry_Pos();
    Input_Set_Pos( cancel_pos );
    base_pos = current_pos;
    menu_positioned = FALSE;
}


static bool Interf_Start_Grabbing( cursor )
    TileCursor cursor;
{
    Interf_Menu_Grab();
    return Control_Grab_User( FALSE, cursor );
}


static bool Interf_Start_Tracking( cursor )
    TileCursor cursor;
{
    Interf_Menu_Grab();

    if (! tracking)
    {
        if (! Control_Grab_User( TRUE, cursor ))
            return FALSE;
        Control_Grab_Server();
        tracking = TRUE;
    }
    return TRUE;
}


static bool Interf_Client_Start_Tracking( cursor )
    TileCursor cursor;
{
    if (tracking)
        return FALSE;

    else if (! Control_Grab_User( TRUE, cursor ))
        return FALSE;

    Control_Grab_Server();
    tracking = TRUE;

    return TRUE;
}


static TWPoint Interf_Continue_Tracking()
{
    if ( current_kind != up )
    {
        base_pos = down_pos;
        return base_pos;
    }
    else
        return current_pos;
}


static bool change_state = FALSE;


static void Interf_Prepare_Reenter()
{
    if ( menu_positioned )
    {
        menu_positioned = FALSE;
        if ( UserGlobals_Get_Option(
                 PLACE_CSR_BACK_AFTER_MENU_OP) )
        {
            if ( (! change_state) &&
                 ( Region_Get_Type(current_region) == header ) )
                Input_Set_Pos( Region_Get_Header_Pos(
                    current_uwinp, TileMenu_Entry_Pos() ) ); 
            else
                Input_Set_Pos( TileMenu_Entry_Pos() );
        }
    }

    change_state = FALSE;

    if ( menu_at_work )
    {
        menu_at_work = FALSE;
        Input_Determine_Buttons();
    }

    if ( tracking )
    {
        tracking = FALSE;
        Control_Ungrab_Server();
        Control_Ungrab_User();
    }
    else if ( Control_Pointer_Grabbed() )
        Control_Ungrab_User();
}


static void Interf_Menu_Enter( menu, butnum, kind )
    TileMenu menu;
    int butnum;
    enum ButKind kind;
{
    extern void Interf_Reenter_Region();
        
    Input_Determine_Buttons();
    menu_at_work = TRUE;
    menu_positioned = TRUE;

    TileMenu_Enter( menu, butnum, kind, current_time );

    if ( menu_positioned )
    {
        menu_positioned = FALSE;
        if ( UserGlobals_Get_Option(PLACE_CSR_BACK_ON_CANCEL) )
            Input_Set_Pos( TileMenu_Entry_Pos() );
    }

    if ( menu_at_work )
    {
        menu_at_work = FALSE;
        Input_Determine_Buttons();
        { Interf_Reenter_Region(); return; }
    }
}



    static Userwin *current_listener = UWIN_NULL;

    static bool accept_key;
    static bool accept_non_listener;
    static bool accept_button;

    static bool key_makes_listener;
    static bool button_makes_listener;

    static bool button_sets_listener;
    static bool button_sets_sublistener;

extern void
    Interf_Have_Lsnr(), Interf_Grabbed_Lsnr(),
    Interf_Am_Lsnr(), Interf_Gbd_Sblsnr(),
    Interf_Am_Sblsnr(), Interf_Am_Clk_Lsnr(),
    Interf_Click_Sblsnr(), Interf_Gbd_Clk_Sblsnr();

static void (*insideLsnr)();
static void (*becomeLsnr)();
static void (*becomeSblsnr)();
static void (*focusIn)();
static void (*loseLsnr)();
static void (*swInMod)();
static void (*mvToUngrab)();
static void (*moveToGrab)();
static void (*moveOut)();


static void Interf_Button_Sets()
{
    button_sets_listener = button_makes_listener;
    button_sets_sublistener = FALSE;

    if ( (! Userwin_Is_Iconic(current_uwinp) ) &&
         Userwin_Input_Enabled(current_uwinp) )
    {
        if ( current_uwinp != current_listener )
        {
            if ( UserGlobals_Get_Option(FOCUS_FOLLOWS_CURSOR) )
            {
                button_sets_listener = button_makes_listener;
                button_sets_sublistener = (! button_makes_listener) &&
                    accept_key && accept_non_listener &&
                    (! key_makes_listener);
            }
            else
            {
                button_sets_listener = button_makes_listener &&
                    key_makes_listener;
                button_sets_sublistener =
                    accept_key && accept_non_listener &&
                    (! key_makes_listener);
            }
        }
    }
}


static void Interf_Manage_Focus()
{
    bool same_listener;
    bool switch_focus;

    same_listener = (current_listener == current_uwinp) ||
                    ( Manage_Get_Sublistener() == current_uwinp );

    if ( Userwin_Is_Iconic(current_uwinp) )
        switch_focus = FALSE;
    else if ( Userwin_Input_Enabled(current_uwinp) )
        switch_focus = ( accept_key &&
                         (same_listener || accept_non_listener) );
    else
        switch_focus = ( same_listener && accept_key &&
                Userwin_Takes_Focus( current_uwinp ) );

    if ( switch_focus )
        Manage_Switch_Focus(current_uwinp);
    else
        Manage_Switch_Focus(UWIN_NULL);
}


static void Interf_Have_Lsnr_insideLsnr()
{
    extern void Interf_Have_Lsnr();
{


    /* now re-entering the listener window */
/*    Control_Set_Focus(current_uwinp);*/

    /* send message to client */
    if ( Userwin_Takes_Focus( current_uwinp ) )
        Client_Take_Focus(current_uwinp);

    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Have_Lsnr_becomeLsnr()
{
    extern void Interf_Have_Lsnr();
{


/*    Control_Set_Focus(current_uwinp);*/
    Interf_Manage_Focus();

    if ( accept_key && accept_button )
    {
    	Control_Release_Grab(current_uwinp);
        { Interf_Am_Lsnr(); return; }
    }
    /* otherwise we keep the input grabbed to throw it away...  */
    else
    {
    	{ Interf_Grabbed_Lsnr(); return; }
    }


}
}

static void Interf_Have_Lsnr_becomeSblsnr()
{
    extern void Interf_Have_Lsnr();
{


    Manage_Switch_Sublistener(current_uwinp);

    if (! Userwin_Is_Iconic(current_uwinp) )
/*        Control_Set_Focus(current_uwinp)*/;
    Interf_Manage_Focus();

    if ( key_makes_listener || button_sets_listener ||
         !accept_key || !accept_button )
    {
    	{ Interf_Gbd_Sblsnr(); return; }
    }
    else
    {
    	Control_Release_Grab(current_uwinp);

        { Interf_Am_Sblsnr(); return; }
    }


}
}

static void Interf_Have_Lsnr_focusIn()
{
    extern void Interf_Have_Lsnr();
{


    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Have_Lsnr_loseLsnr()
{
    extern void Interf_Have_Lsnr();
{


    { Interf_Have_Lsnr(); return; }


}
}

static void Interf_Have_Lsnr_moveOut()
{
    extern void Interf_Have_Lsnr();
{


    { Interf_Have_Lsnr(); return; }


}
}

static void Interf_Have_Lsnr_swInMod()
{
    extern void Interf_Have_Lsnr();
{


    if ( current_listener != UWIN_NULL )
    {
        Control_Set_Focus(current_listener);
        Manage_Switch_Focus(current_listener);
        Control_Release_Grab(current_listener);
    }
    else
        Control_Unset_Focus();
    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Have_Lsnr()
{
    insideLsnr = Interf_Have_Lsnr_insideLsnr;
    becomeLsnr = Interf_Have_Lsnr_becomeLsnr;
    becomeSblsnr = Interf_Have_Lsnr_becomeSblsnr;
    focusIn = Interf_Have_Lsnr_focusIn;
    loseLsnr = Interf_Have_Lsnr_loseLsnr;
    moveOut = Interf_Have_Lsnr_moveOut;
    swInMod = Interf_Have_Lsnr_swInMod;
}



static void Interf_Grabbed_Lsnr_mvToUngrab()
{
    extern void Interf_Grabbed_Lsnr();
{


    Control_Release_Grab(current_uwinp);
    { Interf_Am_Lsnr(); return; }


}
}

static void Interf_Grabbed_Lsnr_moveToGrab()
{
    extern void Interf_Grabbed_Lsnr();
{


    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Grabbed_Lsnr_moveOut()
{
    extern void Interf_Grabbed_Lsnr();
{


    Control_Focus_Out( current_uwinp );
    { Interf_Have_Lsnr(); return; }


}
}

static void Interf_Grabbed_Lsnr_focusIn()
{
    extern void Interf_Grabbed_Lsnr();
{


    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Grabbed_Lsnr_insideLsnr()
{
    extern void Interf_Grabbed_Lsnr();
{


    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Grabbed_Lsnr_swInMod()
{
    extern void Interf_Grabbed_Lsnr();
{


    Control_Release_Grab(current_uwinp);

    { Interf_Am_Clk_Lsnr(); return; }

}
}

static void Interf_Grabbed_Lsnr()
{
    mvToUngrab = Interf_Grabbed_Lsnr_mvToUngrab;
    moveToGrab = Interf_Grabbed_Lsnr_moveToGrab;
    moveOut = Interf_Grabbed_Lsnr_moveOut;
    focusIn = Interf_Grabbed_Lsnr_focusIn;
    insideLsnr = Interf_Grabbed_Lsnr_insideLsnr;
    swInMod = Interf_Grabbed_Lsnr_swInMod;
}



static void Interf_Am_Lsnr_focusIn()
{
    extern void Interf_Am_Lsnr();
{


    Control_Restore_Grab();
    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Am_Lsnr_mvToUngrab()
{
    extern void Interf_Am_Lsnr();
{


    { Interf_Am_Lsnr(); return; }


}
}

static void Interf_Am_Lsnr_moveToGrab()
{
    extern void Interf_Am_Lsnr();
{


    /* Set Grab on listener to throw input away */
    Control_Restore_Grab();

    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Am_Lsnr_moveOut()
{
    extern void Interf_Am_Lsnr();
{


    /* Set Grab on (former) listener */
    Control_Restore_Grab();

/*    Control_Set_Focus( UWIN_NULL );*/
    { Interf_Have_Lsnr(); return; }


}
}

static void Interf_Am_Lsnr_insideLsnr()
{
    extern void Interf_Am_Lsnr();
{


    { Interf_Am_Lsnr(); return; }


}
}

static void Interf_Am_Lsnr_swInMod()
{
    extern void Interf_Am_Lsnr();
{


    { Interf_Am_Clk_Lsnr(); return; }

}
}

static void Interf_Am_Lsnr()
{
    focusIn = Interf_Am_Lsnr_focusIn;
    mvToUngrab = Interf_Am_Lsnr_mvToUngrab;
    moveToGrab = Interf_Am_Lsnr_moveToGrab;
    moveOut = Interf_Am_Lsnr_moveOut;
    insideLsnr = Interf_Am_Lsnr_insideLsnr;
    swInMod = Interf_Am_Lsnr_swInMod;
}



static void Interf_Gbd_Sblsnr_mvToUngrab()
{
    extern void Interf_Gbd_Sblsnr();
{


    /* should not get this if we move to becomeLsnr region */

    Control_Release_Grab(current_uwinp);
    { Interf_Am_Sblsnr(); return; }


}
}

static void Interf_Gbd_Sblsnr_moveToGrab()
{
    extern void Interf_Gbd_Sblsnr();
{


    { Interf_Gbd_Sblsnr(); return; }


}
}

static void Interf_Gbd_Sblsnr_moveOut()
{
    extern void Interf_Gbd_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );
/*    Control_Set_Focus( UWIN_NULL );*/

    { Interf_Have_Lsnr(); return; }


}
}

static void Interf_Gbd_Sblsnr_insideLsnr()
{
    extern void Interf_Gbd_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );

    /* now re-entering the listener window */
/*    Control_Set_Focus(current_uwinp);*/

    /* send message to client */
    if ( Userwin_Takes_Focus( current_uwinp ) )
        Client_Take_Focus(current_uwinp);

    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Gbd_Sblsnr_focusIn()
{
    extern void Interf_Gbd_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );
    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Gbd_Sblsnr_becomeLsnr()
{
    extern void Interf_Gbd_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );    

    if ( accept_key && accept_button )
    {
    	Control_Release_Grab(current_uwinp);
        { Interf_Am_Lsnr(); return; }
    }
    /* otherwise we keep the input grabbed to throw it away... */
    else
    {
    	{ Interf_Grabbed_Lsnr(); return; }
    }


}
}

static void Interf_Gbd_Sblsnr_swInMod()
{
    extern void Interf_Gbd_Sblsnr();
{


    if ( key_makes_listener || button_sets_listener ||
        !accept_key || !accept_button )
    {
    	{ Interf_Gbd_Clk_Sblsnr(); return; }
    }
    else
    {
	Control_Release_Grab(current_uwinp);
    	{ Interf_Click_Sblsnr(); return; }
    }

}
}

static void Interf_Gbd_Sblsnr()
{
    mvToUngrab = Interf_Gbd_Sblsnr_mvToUngrab;
    moveToGrab = Interf_Gbd_Sblsnr_moveToGrab;
    moveOut = Interf_Gbd_Sblsnr_moveOut;
    insideLsnr = Interf_Gbd_Sblsnr_insideLsnr;
    focusIn = Interf_Gbd_Sblsnr_focusIn;
    becomeLsnr = Interf_Gbd_Sblsnr_becomeLsnr;
    swInMod = Interf_Gbd_Sblsnr_swInMod;
}



static void Interf_Am_Sblsnr_focusIn()
{
    extern void Interf_Am_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );
    Control_Restore_Grab();
    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Am_Sblsnr_moveOut()
{
    extern void Interf_Am_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );

    /* Set Grab on (former) Sublistener */
    Control_Restore_Grab();

/*    Control_Set_Focus( UWIN_NULL );    */
    { Interf_Have_Lsnr(); return; }


}
}

static void Interf_Am_Sblsnr_insideLsnr()
{
    extern void Interf_Am_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );

    /* Set Grab on (former) Sublistener */
    Control_Restore_Grab();

    /* now re-entering the listener window */
/*    Control_Set_Focus(current_uwinp);*/

    /* send message to client */
    if ( Userwin_Takes_Focus( current_uwinp ) )
        Client_Take_Focus(current_uwinp);

    { Interf_Grabbed_Lsnr(); return; }


}
}

static void Interf_Am_Sblsnr_mvToUngrab()
{
    extern void Interf_Am_Sblsnr();
{


    { Interf_Am_Sblsnr(); return; }


}
}

static void Interf_Am_Sblsnr_moveToGrab()
{
    extern void Interf_Am_Sblsnr();
{


    /* We might have moved to non-input-accepting */
    /* area or to becomeLsnr region */

    /* Set Grab on Sublistener to throw input away */
    Control_Restore_Grab();

    { Interf_Gbd_Sblsnr(); return; }


}
}

static void Interf_Am_Sblsnr_swInMod()
{
    extern void Interf_Am_Sblsnr();
{


    if ( key_makes_listener || button_sets_listener ||
        !accept_key || !accept_button )
    {
    	{ Interf_Gbd_Clk_Sblsnr(); return; }
    }
    else
    {
	Control_Release_Grab(current_uwinp);
    	{ Interf_Click_Sblsnr(); return; }
    }

}
}

static void Interf_Am_Sblsnr()
{
    focusIn = Interf_Am_Sblsnr_focusIn;
    moveOut = Interf_Am_Sblsnr_moveOut;
    insideLsnr = Interf_Am_Sblsnr_insideLsnr;
    mvToUngrab = Interf_Am_Sblsnr_mvToUngrab;
    moveToGrab = Interf_Am_Sblsnr_moveToGrab;
    swInMod = Interf_Am_Sblsnr_swInMod;
}



static void Interf_Am_Clk_Lsnr_becomeLsnr()
{
    extern void Interf_Am_Clk_Lsnr();
{


    Control_Set_Focus(current_uwinp);
    Manage_Switch_Focus(current_uwinp);

    Control_Release_Grab(current_uwinp);

    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Am_Clk_Lsnr_becomeSblsnr()
{
    extern void Interf_Am_Clk_Lsnr();
{


    Manage_Switch_Sublistener(current_uwinp);
    if (! Userwin_Is_Iconic(current_uwinp) )
        Control_Set_Focus(current_uwinp);

    Manage_Switch_Focus(current_uwinp);

    Control_Release_Grab(current_uwinp);

    { Interf_Click_Sblsnr(); return; }


}
}

static void Interf_Am_Clk_Lsnr_insideLsnr()
{
    extern void Interf_Am_Clk_Lsnr();
{


    Control_Release_Grab(current_uwinp);
    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Am_Clk_Lsnr_loseLsnr()
{
    extern void Interf_Am_Clk_Lsnr();
{


    /* Set Grab on (former) listener */
    Control_Restore_Grab();

    Control_Unset_Focus();
    Manage_Switch_Focus( UWIN_NULL );

    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Am_Clk_Lsnr_focusIn()
{
    extern void Interf_Am_Clk_Lsnr();
{


    Control_Release_Grab(current_uwinp);
    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Am_Clk_Lsnr_mvToUngrab()
{
    extern void Interf_Am_Clk_Lsnr();
{


    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Am_Clk_Lsnr_moveToGrab()
{
    extern void Interf_Am_Clk_Lsnr();
{


    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Am_Clk_Lsnr_moveOut()
{
    extern void Interf_Am_Clk_Lsnr();
{


    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Am_Clk_Lsnr_swInMod()
{
    extern void Interf_Am_Clk_Lsnr();
{


    if (current_listener != current_uwinp)
    {
    	Control_Set_Focus( UWIN_NULL );
        Manage_Switch_Focus( UWIN_NULL );

    	Control_Restore_Grab();
    	{ Interf_Have_Lsnr(); return; }
    }
    else
    {
        if ( accept_key && accept_button )
    	{
	    { Interf_Am_Lsnr(); return; }
    	}
	else
	{
	    Control_Restore_Grab();
	    { Interf_Grabbed_Lsnr(); return; }
    	}
    }

}
}

static void Interf_Am_Clk_Lsnr()
{
    becomeLsnr = Interf_Am_Clk_Lsnr_becomeLsnr;
    becomeSblsnr = Interf_Am_Clk_Lsnr_becomeSblsnr;
    insideLsnr = Interf_Am_Clk_Lsnr_insideLsnr;
    loseLsnr = Interf_Am_Clk_Lsnr_loseLsnr;
    focusIn = Interf_Am_Clk_Lsnr_focusIn;
    mvToUngrab = Interf_Am_Clk_Lsnr_mvToUngrab;
    moveToGrab = Interf_Am_Clk_Lsnr_moveToGrab;
    moveOut = Interf_Am_Clk_Lsnr_moveOut;
    swInMod = Interf_Am_Clk_Lsnr_swInMod;
}



static void Interf_Gbd_Clk_Sblsnr_becomeLsnr()
{
    extern void Interf_Gbd_Clk_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );

    Control_Release_Grab(current_uwinp);
    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Gbd_Clk_Sblsnr_mvToUngrab()
{
    extern void Interf_Gbd_Clk_Sblsnr();
{


    Control_Release_Grab(current_uwinp);
    { Interf_Click_Sblsnr(); return; }


}
}

static void Interf_Gbd_Clk_Sblsnr_moveToGrab()
{
    extern void Interf_Gbd_Clk_Sblsnr();
{


    { Interf_Gbd_Clk_Sblsnr(); return; }


}
}

static void Interf_Gbd_Clk_Sblsnr_moveOut()
{
    extern void Interf_Gbd_Clk_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );


    if ( current_listener == UWIN_NULL )
        Control_Unset_Focus();
    else
        Control_Set_Focus( current_listener );

    Manage_Switch_Focus( current_listener );


    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Gbd_Clk_Sblsnr_focusIn()
{
    extern void Interf_Gbd_Clk_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );

    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Gbd_Clk_Sblsnr_swInMod()
{
    extern void Interf_Gbd_Clk_Sblsnr();
{


    if ( key_makes_listener || button_sets_listener ||
        !accept_key || !accept_button )
    {
    	{ Interf_Gbd_Sblsnr(); return; }
    }
    else
    {
	Control_Release_Grab(current_uwinp);
    	{ Interf_Am_Sblsnr(); return; }
    }

}
}

static void Interf_Gbd_Clk_Sblsnr()
{
    becomeLsnr = Interf_Gbd_Clk_Sblsnr_becomeLsnr;
    mvToUngrab = Interf_Gbd_Clk_Sblsnr_mvToUngrab;
    moveToGrab = Interf_Gbd_Clk_Sblsnr_moveToGrab;
    moveOut = Interf_Gbd_Clk_Sblsnr_moveOut;
    focusIn = Interf_Gbd_Clk_Sblsnr_focusIn;
    swInMod = Interf_Gbd_Clk_Sblsnr_swInMod;
}



static void Interf_Click_Sblsnr_mvToUngrab()
{
    extern void Interf_Click_Sblsnr();
{


    { Interf_Click_Sblsnr(); return; }


}
}

static void Interf_Click_Sblsnr_moveToGrab()
{
    extern void Interf_Click_Sblsnr();
{


    Control_Restore_Grab();
    { Interf_Gbd_Clk_Sblsnr(); return; }


}
}

static void Interf_Click_Sblsnr_moveOut()
{
    extern void Interf_Click_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );

    Control_Restore_Grab();


    if ( current_listener == UWIN_NULL )
        Control_Unset_Focus();
    else
        Control_Set_Focus( current_listener );

    Manage_Switch_Focus( current_listener );


    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Click_Sblsnr_focusIn()
{
    extern void Interf_Click_Sblsnr();
{


    Manage_Switch_Sublistener( UWIN_NULL );

    Control_Restore_Grab();

    { Interf_Am_Clk_Lsnr(); return; }


}
}

static void Interf_Click_Sblsnr_swInMod()
{
    extern void Interf_Click_Sblsnr();
{


    if ( key_makes_listener || button_sets_listener ||
        !accept_key || !accept_button )
    {
    	Control_Restore_Grab();
    	{ Interf_Gbd_Sblsnr(); return; }
    }
    else
    {
    	{ Interf_Am_Sblsnr(); return; }
    }

}
}

static void Interf_Click_Sblsnr()
{
    mvToUngrab = Interf_Click_Sblsnr_mvToUngrab;
    moveToGrab = Interf_Click_Sblsnr_moveToGrab;
    moveOut = Interf_Click_Sblsnr_moveOut;
    focusIn = Interf_Click_Sblsnr_focusIn;
    swInMod = Interf_Click_Sblsnr_swInMod;
}



static void Interf_Send_Button(uwinp, kind, button, pos)
    Userwin        *uwinp;
    enum ButKind    kind;
    Buttons         button;
    TWPoint           pos;
{
    Manage_Note_Input( uwinp );
    Client_Send_Button(uwinp, kind, button, pos);
}


static void Interf_Handle_Button()
{
    bool send_button;
    Userwin *current_sublistener;

    current_sublistener = Manage_Get_Sublistener();

    if ( Userwin_Input_Enabled(current_uwinp) )
    {
	if ( (current_uwinp != current_listener) &&
             (current_uwinp != current_sublistener) &&
	     (!  button_sets_listener ) &&
             (!  button_sets_sublistener ) )
            send_button = FALSE;
	else
            send_button = accept_button;

        if ( send_button )
            Interf_Send_Button( current_uwinp,
                current_kind, current_but, current_pos );
        else
            Client_Ignore_Button();

        if ( current_uwinp != current_listener )
        {
            if ( button_sets_listener )
            {
                current_listener = current_uwinp;
                Interf_Watch(
                    Manage_Switch_Listener( current_listener ) )
                (*becomeLsnr)();
            }
    
            else if ( current_uwinp != current_sublistener )
            {
                if ( button_sets_sublistener )
                    (*becomeSblsnr)();
                else if ( current_uwinp == UWIN_NULL )
                {
                    current_listener = UWIN_NULL;
                    Interf_Watch(
                        Manage_Switch_Listener( UWIN_NULL ) )
                    (*loseLsnr)();
                }
            }
        }
    }

    else if ( current_uwinp != current_listener )
    {
        if ( ( current_uwinp == UWIN_NULL ) ||
             ( Region_Get_Type(current_region) == rtl ) )
        {
            current_listener = UWIN_NULL;
            Interf_Watch(
                Manage_Switch_Listener( UWIN_NULL ) )
            (*loseLsnr)();
            Client_Ignore_Button();
        }
        else if ( accept_button )
            Interf_Send_Button( current_uwinp,
                                current_kind, current_but, current_pos );
        else if ( Userwin_Takes_Focus( current_uwinp ) )
        {
            Client_Take_Focus( current_uwinp );
            Client_Ignore_Button();
            Manage_Note_Input( current_uwinp );
        }
        else
            Client_Ignore_Button();
    }

    else if ( accept_button )
        Interf_Send_Button( current_uwinp,
    	    	    	    current_kind, current_but, current_pos );
    else
        Client_Ignore_Button();
}


static void Interf_Ignore_Key()
{
    Drawwin_Flash();
    Client_Ignore_Key();
}

static void Interf_Send_Key( uwinp, ch )
    Userwin *uwinp;
    char ch;
{
    Manage_Note_Input( uwinp );
    Client_Send_Key( uwinp, ch );
}


static void Interf_Handle_Key()
{
    bool key_makes_sublistener;
    bool send_key;
    Userwin  *current_sublistener;

    current_sublistener = Manage_Get_Sublistener();

    if ( (! inside_client) && (current_ch == 0) )
        Client_Ignore_Key();  /* Modifier Key */

    else if ( UserGlobals_Get_Option(FOCUS_FOLLOWS_CURSOR) )
    {
        if ( current_uwinp == UWIN_NULL )
            Interf_Ignore_Key();

        else if ( Userwin_Input_Enabled(current_uwinp) )
        {
            send_key = accept_key;

            if ( current_uwinp != current_listener )
            {
                key_makes_sublistener = (! key_makes_listener) &&
                    accept_key && accept_non_listener;   /* temporary */

                if ( key_makes_listener )
                {
                    current_listener = current_uwinp;
                    Interf_Watch(
                        Manage_Switch_Listener( current_listener ) )
                    (*becomeLsnr)();
                }
        
                else if (current_uwinp != current_sublistener)
                {
                    if ( key_makes_sublistener )
                        (*becomeSblsnr)();
                    else
                        send_key = FALSE;
                } 

                if ( send_key ) 
                    Interf_Send_Key( current_uwinp, current_ch );
                else
                    Interf_Ignore_Key();
            }
            else
            {
                if ( send_key )
                    Interf_Send_Key( current_uwinp, current_ch );
                else
                    Interf_Ignore_Key();
            }
        }

        else if ( current_uwinp != current_listener )
        {
            if ( key_makes_listener )
            {
                if ( accept_key && accept_non_listener )
                    Interf_Send_Key( current_uwinp, current_ch );
                else
                    Interf_Ignore_Key();
            }
            else
                Interf_Ignore_Key();
        }
    }

    else
    {
        if ( Manage_Get_Focus() == UWIN_NULL )
            Interf_Ignore_Key();
        else
            Interf_Send_Key( Manage_Get_Focus(), current_ch);
    }
}


void Interf_Handle_FocusIn( uwinp )
    Userwin  *uwinp;
{
/*
    current_uwinp = uwinp;

    current_listener = current_uwinp;
    Interf_Watch(
        Manage_Switch_Listener( current_listener ) )
    Manage_Switch_Focus( current_listener );

    (*focusIn)();

    if ( UserGlobals_Get_Option(FOCUS_FOLLOWS_CURSOR) )
        Control_Pointer_To_Window( uwinp );
*/
}


void Interf_Handle_Leave()
{
    Userwin *current_sublistener;

    current_sublistener = Manage_Get_Sublistener();

    if (current_uwinp == current_listener ||
    	current_uwinp == current_sublistener)
    {
    	(*moveOut)();
    }

    if ( UserGlobals_Get_Option(FOCUS_FOLLOWS_CURSOR) )
        Manage_Switch_Focus(UWIN_NULL);
}


void Interf_Handle_Enter()
{
    Userwin  *current_sublistener;

    current_sublistener = Manage_Get_Sublistener();

    if ( current_listener != Manage_Get_Listener() )
    {
        if ( current_listener != UWIN_NULL )
            (*moveOut)();
        current_listener = Manage_Get_Listener();
    }

    Interf_Button_Sets();

    if ( UserGlobals_Get_Option(FOCUS_FOLLOWS_CURSOR) )
        Interf_Manage_Focus();

    if (current_listener == current_uwinp)
    {
    	(*insideLsnr)();

        if ( accept_key && accept_button )
            (*mvToUngrab)();
    	else
    	    (*moveToGrab)();
    }
    else if ( current_sublistener == current_uwinp )
    {
    	if ( key_makes_listener || button_sets_listener ||
    	    !accept_key || !accept_button )
            (*moveToGrab)();
        else
            (*mvToUngrab)();
    }
    else
        (*moveOut)();
}


void Interf_Enter_Region()
{
    extern void Interf_Inside_Background();
    extern void Interf_Inside_Body();
    extern void Interf_Inside_Header();
    extern void Interf_Inside_Zoom_Gadget();
    extern void Interf_Inside_Move_Gadget();
    extern void Interf_Inside_Side_Border();
    extern void Interf_Ins_Crnr_Border();
    extern void Interf_Inside_Icon();
    extern void Interf_Inside_Rtl();

    wait_for_click = FALSE;
    inside_client = FALSE;
    Control_Set_Cursor(Region_Get_Cursor(current_uwinp,current_region));
    switch ( Region_Get_Type(current_region) )
    {
        case background:
            accept_key = FALSE;
            accept_button = FALSE;
            accept_non_listener = FALSE;
            key_makes_listener = FALSE;
            button_makes_listener = FALSE;
            { Interf_Inside_Background(); return; }
        case body:
            inside_client = TRUE;
            Client_Enter( current_uwinp, 
                current_butstate, current_pos );
            accept_key = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_KEY_IN_BODY );
            accept_button = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_BUTTON_IN_BODY );
            accept_non_listener =
                UserGlobals_Get_Option(ACCEPT_NON_LISTENER_IN_BODY);
            key_makes_listener = 
                UserGlobals_Get_Option(KEY_MAKES_LISTENER_IN_BODY);
            button_makes_listener =
                UserGlobals_Get_Option(BUTTON_MAKES_LISTENER_IN_BODY);
            Interf_Handle_Enter();
            { Interf_Inside_Body(); return; }
        case header:
            accept_key = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_KEY_IN_HEADER );
            accept_button = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_BUTTON_IN_HEADER );
            accept_non_listener =
                UserGlobals_Get_Option(ACCEPT_NON_LISTENER_IN_HEADER);
            key_makes_listener = 
                UserGlobals_Get_Option(KEY_MAKES_LISTENER_IN_HEADER);
            button_makes_listener =
                UserGlobals_Get_Option(BUTTON_MAKES_LISTENER_IN_HEADER);
            Interf_Handle_Enter();
            { Interf_Inside_Header(); return; }
        case zoom_gadget:
            accept_key = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_KEY_IN_GADGET );
            accept_button = FALSE;
            accept_non_listener =
                UserGlobals_Get_Option(ACCEPT_NON_LISTENER_IN_GADGET);
            key_makes_listener = 
                UserGlobals_Get_Option(KEY_MAKES_LISTENER_IN_GADGET);
            button_makes_listener = FALSE;
            Interf_Handle_Enter();
            { Interf_Inside_Zoom_Gadget(); return; }
        case move_gadget:
            accept_key = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_KEY_IN_GADGET );
            accept_button = FALSE;
            accept_non_listener =
                UserGlobals_Get_Option(ACCEPT_NON_LISTENER_IN_GADGET);
            key_makes_listener = 
                UserGlobals_Get_Option(KEY_MAKES_LISTENER_IN_GADGET);
            button_makes_listener = FALSE;
            Interf_Handle_Enter();
            { Interf_Inside_Move_Gadget(); return; }
        case edge:
            accept_key = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_KEY_IN_BORDER );
            accept_button = FALSE;
            accept_non_listener =
                UserGlobals_Get_Option(ACCEPT_NON_LISTENER_IN_BORDER);
            key_makes_listener = 
                UserGlobals_Get_Option(KEY_MAKES_LISTENER_IN_BORDER);
            button_makes_listener = FALSE;
            Interf_Handle_Enter();
            { Interf_Inside_Side_Border(); return; }
        case corner:
            accept_key = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_KEY_IN_BORDER );
            accept_button = FALSE;
            accept_non_listener =
                UserGlobals_Get_Option(ACCEPT_NON_LISTENER_IN_BORDER);
            key_makes_listener = 
                UserGlobals_Get_Option(KEY_MAKES_LISTENER_IN_BORDER);
            button_makes_listener = FALSE;
            Interf_Handle_Enter();
            { Interf_Ins_Crnr_Border(); return; }
        case icon:
            accept_key = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_KEY_IN_ICON );
            accept_button = Userwin_Get_Window_Option( 
                current_uwinp, ACCEPT_BUTTON_IN_ICON );
            accept_non_listener = TRUE;
            key_makes_listener = FALSE;
            button_makes_listener = FALSE;
            Interf_Handle_Enter();
            { Interf_Inside_Icon(); return; }
        case rtl:
            accept_key = FALSE;
            accept_button = FALSE;
            accept_non_listener = FALSE;
            key_makes_listener = FALSE;
            button_makes_listener = FALSE;
            Interf_Handle_Enter();
            { Interf_Inside_Rtl(); return; }
    }
}
    

void Interf_Reenter_Region()
{
    Interf_Prepare_Reenter();
    Input_Reenter();
    { Interf_Enter_Region(); return; }
}


void Interf_Enable_Input(uwinp)
    Userwin *uwinp;
{
    Userwin_Enable_Input(uwinp);
    if (current_uwinp == uwinp)
        { Interf_Reenter_Region(); return; }
}


void Interf_Disable_Input( uwinp )
    Userwin *uwinp;
{
    Userwin_Disable_Input(uwinp);
    if (current_uwinp == uwinp)
        { Interf_Reenter_Region(); return; }
}


static void Interf_Wait_Cmplt_Cancel_KEY()
{
    extern void Interf_Wait_Cmplt_Cancel();
{

    Drawwin_Flash();
    { Interf_Wait_Cmplt_Cancel(); return; }

}
}

static void Interf_Wait_Cmplt_Cancel_MOUSE()
{
    extern void Interf_Wait_Cmplt_Cancel();
{

    { Interf_Wait_Cmplt_Cancel(); return; }

}
}

static void Interf_Wait_Cmplt_Cancel_button()
{
    extern void Interf_Wait_Cmplt_Cancel();
{

    extern void Interf_Cancel_Here();
    { Interf_Cancel_Here(); return; }

}
}

static void Interf_Wait_Cmplt_Cancel()
{
    KEY = Interf_Wait_Cmplt_Cancel_KEY;
    MOUSE = Interf_Wait_Cmplt_Cancel_MOUSE;
    button = Interf_Wait_Cmplt_Cancel_button;
}



static void Interf_Cancel_Here()
{
    complete_down = Buttons_Any_Down(current_butstate);
    if ( complete_down )
        { Interf_Wait_Cmplt_Cancel(); return; }
    else
        { Interf_Reenter_Region(); return; }
}


static void Interf_Cancel()
{
    if ( UserGlobals_Get_Option(PLACE_CSR_BACK_ON_CANCEL) )
        Interf_Set_Pos( cancel_pos );

    { Interf_Cancel_Here(); return; }
}


static void Interf_Flash_Cancel()
{
    Drawwin_Flash();
    { Interf_Cancel(); return; }
}


static void Interf_Confirmed_Notify_All()
{
    Manage_Notify_All();
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Soft_Kill_All()
{
    Manage_Soft_Kill_All();
    change_state = TRUE;
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Exit()
{
    Manage_Exit();
    Control_Exit();
    exit(0);
}


static void Interf_Confirmed_Pause()
{
    extern void Pause_RTL();
    Pause_RTL();
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Icon_Notify()
{
    Client_Icon_Notify(current_uwinp);
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Group_Close()
{
    Manage_Group_Close(current_uwinp);
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Group_Open()
{
    Manage_Group_Open(current_uwinp);
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Notify()
{
    Manage_Notify(current_uwinp);
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Delete_Window()
{
    Interf_Watch(
        Manage_Delete_Window(current_uwinp) )
    change_state = TRUE;
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Soft_Kill()
{
    Interf_Watch(
        Manage_Soft_Kill(current_uwinp) )
    change_state = TRUE;
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Hard_Kill()
{
    Interf_Watch(
        Manage_Hard_Kill(current_uwinp) )
    change_state = TRUE;
    { Interf_Reenter_Region(); return; }
}


static VoidFunc act_func;
static VoidFunc cancel_func;

static void Interf_Wait_Complete_KEY()
{
    extern void Interf_Wait_Complete();
{

    Drawwin_Flash();
    { Interf_Wait_Complete(); return; }

}
}

static void Interf_Wait_Complete_MOUSE()
{
    extern void Interf_Wait_Complete();
{

    { Interf_Wait_Complete(); return; }

}
}

static void Interf_Wait_Complete_button()
{
    extern void Interf_Wait_Complete();
{

    extern void Interf_Check_Complete();

    if ( (current_kind != up) &&
         Buttons_Match(current_but,CANCEL_BUTTONS) )
        { (*cancel_func)(); return; }
    else
        { Interf_Check_Complete(); return; }

}
}

static void Interf_Wait_Complete()
{
    KEY = Interf_Wait_Complete_KEY;
    MOUSE = Interf_Wait_Complete_MOUSE;
    button = Interf_Wait_Complete_button;
}



static void Interf_Check_Complete()
{
    complete_down = Buttons_Any_Down(current_butstate);

    if ( complete_down )
        { Interf_Wait_Complete(); return; }
    else
        { (*act_func)(); return; }
}


static void Interf_Arrange( actfunc, cancelfunc )
    VoidFunc actfunc;
    VoidFunc cancelfunc;
{
    act_func = actfunc;
    cancel_func = cancelfunc;

    { Interf_Check_Complete(); return; }
}    


static void Interf_Act( actfunc )
    VoidFunc actfunc;
{
    act_func = actfunc;
    cancel_func = Interf_Cancel;

    complete_down = Buttons_Any_Down(current_butstate);

    if (! complete_down )
        { (*act_func)(); return; }
    else if ( Control_Grab_User( FALSE, watch_tilecursor ) )
        { Interf_Wait_Complete(); return; }
    else
        { (*act_func)(); return; }
}


static VoidFunc wait_prcs;


static void Interf_Confirm_Cancel()
{
    Message_Put_Down();
    { Interf_Cancel(); return; }
}


static void Interf_Wait_For_Conf_KEY()
{
    extern void Interf_Wait_For_Conf();
{

    Drawwin_Flash();
    { Interf_Wait_For_Conf(); return; }

}
}

static void Interf_Wait_For_Conf_MOUSE()
{
    extern void Interf_Wait_For_Conf();
{

    { Interf_Wait_For_Conf(); return; }

}
}

static void Interf_Wait_For_Conf_button()
{
    extern void Interf_Wait_For_Conf();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Confirm_Cancel(); return; }
    else if ( current_kind == up )
        { Interf_Wait_For_Conf(); return; }
    else
    {
        Message_Put_Down();
        { Interf_Arrange( wait_prcs, Interf_Confirm_Cancel ); return; }
    }

}
}

static void Interf_Wait_For_Conf()
{
    KEY = Interf_Wait_For_Conf_KEY;
    MOUSE = Interf_Wait_For_Conf_MOUSE;
    button = Interf_Wait_For_Conf_button;
}



static void Interf_Start_Wait_For_Confirm(msg,prcs)
    Message msg;
    VoidFunc prcs;
{
    if (! Interf_Start_Grabbing( confirmation_tilecursor ) )
        { Interf_Flash_Cancel(); return; }
    Message_Pop_Up(current_pos,msg);
    wait_prcs = prcs;
    { Interf_Wait_For_Conf(); return; }
}



static TWPoint start_pos;
static bool center_opening;
static bool good_open;
TWPoint last_pos;

static void Interf_Cancel_Opening()
{
    if ( Userwin_Is_Open(current_uwinp) )
        Drawwin_Unshow_Moving(current_uwinp);
    else if ( Userwin_Is_Iconic(current_uwinp) )
        DrawIcon_Unshow_Opening(current_uwinp);
    else if (! Userwin_Ever_Opened(current_uwinp) )
        Interf_Watch(
            Manage_Client_Open_Icon(current_uwinp) )
    { Interf_Cancel(); return; }
}

static void Interf_Finish_Opening() 
{
    if ( UserGlobals_Get_Option(PLACE_CSR_IN_GADGET_AFT_MAN_OPEN) )
        Interf_Set_Pos( Region_Gadget_Center( current_uwinp ) );
    { Interf_Reenter_Region(); return; }
}

static void Interf_Act_Center_Opening()
{
    extern void Interf_Start_Icon_Opening();
    extern void Interf_Start_Opening();
    bool result;

    if ( Userwin_Is_Open(current_uwinp) )
        Drawwin_Unshow_Moving(current_uwinp);
    else if ( Userwin_Is_Iconic(current_uwinp) )
        DrawIcon_Unshow_Opening(current_uwinp);

    Interf_Watch(
    {
        result = Manage_Center_Open(current_uwinp,current_pos);
    } )
    if ( result )
        { Interf_Finish_Opening(); return; }

    if ( (! Userwin_Is_Open(current_uwinp)) &&
         Userwin_Is_Iconic(current_uwinp) )
        { Interf_Start_Icon_Opening(); return; }
    else
        { Interf_Start_Opening(); return; }
}

static void Interf_Trk_Cont_Ctr_Opng_KEY()
{
    extern void Interf_Trk_Cont_Ctr_Opng();
{

    Drawwin_Flash();
    { Interf_Trk_Cont_Ctr_Opng(); return; }

}
}

static void Interf_Trk_Cont_Ctr_Opng_MOUSE()
{
    extern void Interf_Trk_Cont_Ctr_Opng();
{

    extern void Interf_Start_Continue_Opening();
    { Interf_Start_Continue_Opening(); return; }

}
}

static void Interf_Trk_Cont_Ctr_Opng_button()
{
    extern void Interf_Trk_Cont_Ctr_Opng();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Opening(); return; }
    else if ( current_kind != down )
    {
        if (! ( Userwin_Sized( current_uwinp ) ||
                UserGlobals_Get_Option(AUTO_PLACE_ON_UNSIZED_OPEN) ) )
            Drawwin_Flash();
        else
            { Interf_Arrange( Interf_Act_Center_Opening, Interf_Cancel_Opening ); return; }
    }
    { Interf_Trk_Cont_Ctr_Opng(); return; }

}
}

static void Interf_Trk_Cont_Ctr_Opng()
{
    KEY = Interf_Trk_Cont_Ctr_Opng_KEY;
    MOUSE = Interf_Trk_Cont_Ctr_Opng_MOUSE;
    button = Interf_Trk_Cont_Ctr_Opng_button;
}


static void Interf_Cancel_Corner_Opening()
{
    Drawwin_Undo_Open_Box();
    { Interf_Cancel_Opening(); return; }
}

static void Interf_Setup_Corner_Open()
{
    Control_Set_Cursor(corner_open_tilecursor);
    good_open = Userwin_Check_Corner_Open( current_uwinp, &start_pos, 
                                   &current_pos, Top_Left );
    last_pos = current_pos;
    if ( good_open )
        Drawwin_Good_Open_Box(start_pos,current_pos);
    else
        Drawwin_Bad_Open_Box(start_pos,current_pos);
}

static void Interf_Act_Corner_Opening()
{
    extern void Interf_Start_Continue_Opening();
    bool result;

    Drawwin_Undo_Open_Box();

    if ( Userwin_Is_Open(current_uwinp) )
        Drawwin_Unshow_Moving(current_uwinp);
    else if ( Userwin_Is_Iconic(current_uwinp) )
        DrawIcon_Unshow_Opening(current_uwinp);

    Interf_Watch(
    {
        result = 
            Manage_Corner_Open(current_uwinp,start_pos,last_pos,
                Buttons_Match(current_but,FORCE_RESET_MIN_MAX_BUTTONS),
                Buttons_Match(current_but,UNDESIRE_BUTTONS) );
    } )
    if ( result )
        { Interf_Finish_Opening(); return; }

    if ( Userwin_Is_Open(current_uwinp) )
        Drawwin_Show_Moving(current_uwinp);
    else if ( Userwin_Is_Iconic(current_uwinp) )
        DrawIcon_Show_Opening(current_uwinp);

    { Interf_Start_Continue_Opening(); return; }
}

static void Interf_Trk_Cont_Crnr_Opng_KEY()
{
    extern void Interf_Trk_Cont_Crnr_Opng();
{

    Drawwin_Flash();
    { Interf_Trk_Cont_Crnr_Opng(); return; }

}
}

static void Interf_Trk_Cont_Crnr_Opng_MOUSE()
{
    extern void Interf_Trk_Cont_Crnr_Opng();
{

    extern void Interf_Start_Continue_Opening();
    if ( (last_pos.x == current_pos.x) && (last_pos.y == current_pos.y) )
        { Interf_Trk_Cont_Crnr_Opng(); return; }    
    Drawwin_Undo_Open_Box();
    { Interf_Start_Continue_Opening(); return; }

}
}

static void Interf_Trk_Cont_Crnr_Opng_button()
{
    extern void Interf_Trk_Cont_Crnr_Opng();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Corner_Opening(); return; }
    else if ( good_open && (current_kind != down) )
        { Interf_Arrange( Interf_Act_Corner_Opening, Interf_Cancel_Corner_Opening ) ; return; }
    { Interf_Trk_Cont_Crnr_Opng(); return; }

}
}

static void Interf_Trk_Cont_Crnr_Opng()
{
    KEY = Interf_Trk_Cont_Crnr_Opng_KEY;
    MOUSE = Interf_Trk_Cont_Crnr_Opng_MOUSE;
    button = Interf_Trk_Cont_Crnr_Opng_button;
}


static void Interf_Start_Continue_Opening()
{
    center_opening = Region_Nearby(start_pos,current_pos);
    if ( center_opening )
    {
        Control_Set_Cursor(center_open_tilecursor);
        { Interf_Trk_Cont_Ctr_Opng(); return; }
    }
    else        
    {
        Interf_Setup_Corner_Open();
        { Interf_Trk_Cont_Crnr_Opng(); return; }
    }
}

static void Interf_Track_Opening_KEY()
{
    extern void Interf_Track_Opening();
{

    Drawwin_Flash();
    { Interf_Track_Opening(); return; }

}
}

static void Interf_Track_Opening_MOUSE()
{
    extern void Interf_Track_Opening();
{

    { Interf_Track_Opening(); return; }

}
}

static void Interf_Track_Opening_button()
{
    extern void Interf_Track_Opening();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Opening(); return; }
    else
    {
        Control_Set_Cursor(center_open_tilecursor);
        start_pos = Interf_Continue_Tracking();
        { Interf_Trk_Cont_Ctr_Opng(); return; }
    }

}
}

static void Interf_Track_Opening()
{
    KEY = Interf_Track_Opening_KEY;
    MOUSE = Interf_Track_Opening_MOUSE;
    button = Interf_Track_Opening_button;
}


static void Interf_Start_Opening()
{
    Control_Set_Cursor(track_open_tilecursor);
    if ( Userwin_Is_Open(current_uwinp) )
        Drawwin_Show_Moving(current_uwinp);
    { Interf_Track_Opening(); return; }
}



static void Interf_Cancel_Open_In_Icon()
{
    DrawIcon_Unshow_Opening( current_uwinp );
    { Interf_Cancel(); return; }
}

static void Interf_Track_Icon_Opening_KEY()
{
    extern void Interf_Track_Icon_Opening();
{

    Drawwin_Flash();
    { Interf_Track_Icon_Opening(); return; }

}
}

static void Interf_Track_Icon_Opening_MOUSE()
{
    extern void Interf_Track_Icon_Opening();
{

    extern void Interf_Open_In_Icon();
    if ( Manage_Locate( current_pos ) == current_uwinp )
    {
        Control_Set_Cursor(open_in_icon_tilecursor);
        { Interf_Open_In_Icon(); return; }
    }
    start_pos = current_pos;
    { Interf_Track_Icon_Opening(); return; }

}
}

static void Interf_Track_Icon_Opening_button()
{
    extern void Interf_Track_Icon_Opening();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Open_In_Icon(); return; }
    else
    {
        Control_Set_Cursor(center_open_tilecursor);
        start_pos = Interf_Continue_Tracking();
        { Interf_Trk_Cont_Ctr_Opng(); return; }
    }

}
}

static void Interf_Track_Icon_Opening()
{
    KEY = Interf_Track_Icon_Opening_KEY;
    MOUSE = Interf_Track_Icon_Opening_MOUSE;
    button = Interf_Track_Icon_Opening_button;
}


static void Interf_Continue_Icon_Opening()
{
    Control_Set_Cursor(track_open_tilecursor);
    { Interf_Track_Icon_Opening(); return; }
}

static void Interf_Start_Icon_Opening()
{
    if ( Userwin_Is_Iconic(current_uwinp) )
        DrawIcon_Show_Opening(current_uwinp);
    { Interf_Continue_Icon_Opening(); return; }
}

static void Interf_Act_Open_In_Icon()
{
    bool result;

    Interf_Watch(
    {
        result = Manage_User_Open_Automatically( current_uwinp,
             /* Buttons_Match(current_but,FORCE_LISTENER_BUTTONS), */
             FALSE,
             Buttons_Match(current_but,FORCE_ZOOM_BUTTONS) );
    } )
    if ( result )
    {
        if ( UserGlobals_Get_Option(
                 PLACE_CSR_GDGT_AFT_US_AUTO_OPEN) )
            Interf_Set_Pos( Region_Gadget_Center( current_uwinp ) );
        if ( Buttons_Match(current_but,FORCE_LISTENER_BUTTONS) )
            /* arghhh */;
    }
    else
        DrawIcon_Unshow_Opening( current_uwinp );
    { Interf_Reenter_Region(); return; }
}

static void Interf_Open_In_Icon_KEY()
{
    extern void Interf_Open_In_Icon();
{

    Drawwin_Flash();
    { Interf_Open_In_Icon(); return; }

}
}

static void Interf_Open_In_Icon_MOUSE()
{
    extern void Interf_Open_In_Icon();
{

    if ( Manage_Locate( current_pos ) == current_uwinp )
        { Interf_Open_In_Icon(); return; }
    else
        { Interf_Continue_Icon_Opening(); return; }

}
}

static void Interf_Open_In_Icon_button()
{
    extern void Interf_Open_In_Icon();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Open_In_Icon(); return; }
    else if ( current_kind != up )
        { Interf_Arrange( Interf_Act_Open_In_Icon, Interf_Cancel_Open_In_Icon ); return; }
    { Interf_Open_In_Icon(); return; }

}
}

static void Interf_Open_In_Icon()
{
    KEY = Interf_Open_In_Icon_KEY;
    MOUSE = Interf_Open_In_Icon_MOUSE;
    button = Interf_Open_In_Icon_button;
}


static void Interf_Start_Open_In_Icon()
{
    if (! Interf_Start_Tracking(open_in_icon_tilecursor))
        { Interf_Flash_Cancel(); return; }
    DrawIcon_Show_Opening( current_uwinp );
    { Interf_Open_In_Icon(); return; }
}


static bool old_gravity;

typedef bool (*BoolFunc)();
static BoolFunc resize_proc;

    
static void Interf_Setup_Edge_Resizing()
{
    extern void Interf_Track_Edge_Rszng();
    Userwin_Check_Edge_Resize( current_uwinp, &current_pos, current_side );
    last_pos = current_pos;
    Drawwin_Edge_Resize(current_uwinp, current_side, current_pos);
    { Interf_Track_Edge_Rszng(); return; }
}

static void Interf_Cancel_Edge_Resizing()
{
    Drawwin_Undo_Edge_Resize();
    Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
    { Interf_Cancel(); return; }
}

static void Interf_Act_Edge_Resizing()
{
    bool result;

    Drawwin_Undo_Edge_Resize();
    Interf_Watch(
    {
        result = (*resize_proc)(current_uwinp,last_pos,current_side,
             Buttons_Match(current_but,FORCE_RESET_MIN_MAX_BUTTONS),
             Buttons_Match(current_but,UNDESIRE_BUTTONS) );
    } )
    if ( result )
    {
        if ( UserGlobals_Get_Option(PLACE_CSR_IN_BORDER_AFTER_RESIZE) )
            Interf_Set_Pos( Region_Get_Edge_Pos( 
                current_uwinp, current_side, current_pos ) );
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
        { Interf_Reenter_Region(); return; }
    }
    else 
        { Interf_Setup_Edge_Resizing(); return; }
}

static void Interf_Track_Edge_Rszng_KEY()
{
    extern void Interf_Track_Edge_Rszng();
{

    Drawwin_Flash();
    { Interf_Track_Edge_Rszng(); return; }

}
}

static void Interf_Track_Edge_Rszng_MOUSE()
{
    extern void Interf_Track_Edge_Rszng();
{

    if ( (last_pos.x == current_pos.x) && (last_pos.y == current_pos.y) )
        { Interf_Track_Edge_Rszng(); return; }
    Drawwin_Undo_Edge_Resize();
    { Interf_Setup_Edge_Resizing(); return; }

}
}

static void Interf_Track_Edge_Rszng_button()
{
    extern void Interf_Track_Edge_Rszng();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Edge_Resizing(); return; }
    else if ( current_kind != down )
        { Interf_Arrange( Interf_Act_Edge_Resizing, Interf_Cancel_Edge_Resizing ); return; }
    { Interf_Track_Edge_Rszng(); return; }

}
}

static void Interf_Track_Edge_Rszng()
{
    KEY = Interf_Track_Edge_Rszng_KEY;
    MOUSE = Interf_Track_Edge_Rszng_MOUSE;
    button = Interf_Track_Edge_Rszng_button;
}


static void Interf_Start_Edge_Resizing()
{
    if (! Interf_Start_Tracking(
              Region_Get_Cursor(current_uwinp,current_region) ) )
        { Interf_Flash_Cancel(); return; }
    resize_proc = Manage_Resize;
    old_gravity = Tilwin_Get_Global_Option( ENABLE_GRAVITY );
    if ( Buttons_Match(current_but,TOGGLE_GRAVITY_BUTTONS) )
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, !old_gravity );
    Interf_Track_Edge_Pos();
    { Interf_Setup_Edge_Resizing(); return; }
}

    
static void Interf_Setup_Crnr_Rszng()
{
    extern void Interf_Track_Crnr_Rszng();
    Userwin_Check_Corner_Resize( current_uwinp, &current_pos, current_side );
    last_pos = current_pos;
    Drawwin_Corner_Resize(current_uwinp, current_side, current_pos);
    { Interf_Track_Crnr_Rszng(); return; }
}

static void Interf_Cancel_Crnr_Rszng()
{
    Drawwin_Undo_Corner_Resize();
    Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
    { Interf_Cancel(); return; }
}

static void Interf_Act_Crnr_Rszng()
{
    bool result;

    Drawwin_Undo_Corner_Resize();
    Interf_Watch(
    {
        result = (*resize_proc)(current_uwinp,last_pos,current_side,
             Buttons_Match(current_but,FORCE_RESET_MIN_MAX_BUTTONS),
             Buttons_Match(current_but,UNDESIRE_BUTTONS) );
    } )
    if ( result )
    {
        if ( UserGlobals_Get_Option(PLACE_CSR_IN_BORDER_AFTER_RESIZE) )
            Interf_Set_Pos( Region_Get_Corner_Pos( 
                current_uwinp, current_side ) );
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
        { Interf_Reenter_Region(); return; }
    }
    else 
        { Interf_Setup_Crnr_Rszng(); return; }
}

static void Interf_Track_Crnr_Rszng_KEY()
{
    extern void Interf_Track_Crnr_Rszng();
{

    Drawwin_Flash();
    { Interf_Track_Crnr_Rszng(); return; }

}
}

static void Interf_Track_Crnr_Rszng_MOUSE()
{
    extern void Interf_Track_Crnr_Rszng();
{

    if ( (last_pos.x == current_pos.x) && (last_pos.y == current_pos.y) )
        { Interf_Track_Crnr_Rszng(); return; }
    Drawwin_Undo_Corner_Resize();
    { Interf_Setup_Crnr_Rszng(); return; }

}
}

static void Interf_Track_Crnr_Rszng_button()
{
    extern void Interf_Track_Crnr_Rszng();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Crnr_Rszng(); return; }
    else if ( current_kind != down )
        { Interf_Arrange( Interf_Act_Crnr_Rszng, Interf_Cancel_Crnr_Rszng ); return; }
    { Interf_Track_Crnr_Rszng(); return; }

}
}

static void Interf_Track_Crnr_Rszng()
{
    KEY = Interf_Track_Crnr_Rszng_KEY;
    MOUSE = Interf_Track_Crnr_Rszng_MOUSE;
    button = Interf_Track_Crnr_Rszng_button;
}


static void Interf_Start_Crnr_Rszng()
{
    if (! Interf_Start_Tracking(
              Region_Get_Cursor(current_uwinp,current_region) ) )
        { Interf_Flash_Cancel(); return; }
    resize_proc = Manage_Resize;
    old_gravity = Tilwin_Get_Global_Option( ENABLE_GRAVITY );
    if ( Buttons_Match(current_but,TOGGLE_GRAVITY_BUTTONS) )
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, !old_gravity );
    Interf_Track_Corner_Pos();
    { Interf_Setup_Crnr_Rszng(); return; }
}



static void Interf_Setup_Basing_Rsz()
{
    current_region = Region_Nearest_Border( current_uwinp, current_pos );
    Control_Set_Cursor( Region_Get_Cursor( current_uwinp, current_region ) );
    current_side = Region_Get_Border(current_region);
}

static void Interf_Start_Resizing()
{
    Interf_Setup_Basing_Rsz();
    old_gravity = Tilwin_Get_Global_Option( ENABLE_GRAVITY );
    if ( resize_proc == Manage_Resize )
    {
        if ( Buttons_Match(current_but,TOGGLE_GRAVITY_BUTTONS) )
            Tilwin_Set_Global_Option( ENABLE_GRAVITY, !old_gravity );
    }    
    else
    {
        if ( Buttons_Match(current_but,TOGGLE_GRAVITY_BUTTONS) )
        {
            if (! old_gravity)
                Tilwin_Set_Global_Option( ENABLE_GRAVITY, TRUE );
        }
        else
        {
            if (old_gravity)
                Tilwin_Set_Global_Option( ENABLE_GRAVITY, FALSE );
        }
    }
    Interf_Continue_Tracking();
    switch( Region_Get_Type(current_region) )
    {
        case edge:
            Interf_Track_Edge_Pos();
            { Interf_Setup_Edge_Resizing(); return; }
        case corner:
            Interf_Track_Corner_Pos();
            { Interf_Setup_Crnr_Rszng(); return; }
    }
}

static void Interf_Track_Basing_Rsz_KEY()
{
    extern void Interf_Track_Basing_Rsz();
{

    Drawwin_Flash();
    { Interf_Track_Basing_Rsz(); return; }

}
}

static void Interf_Track_Basing_Rsz_MOUSE()
{
    extern void Interf_Track_Basing_Rsz();
{

    Interf_Setup_Basing_Rsz();
    { Interf_Track_Basing_Rsz(); return; }

}
}

static void Interf_Track_Basing_Rsz_button()
{
    extern void Interf_Track_Basing_Rsz();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel(); return; }
    else
        { Interf_Start_Resizing(); return; }

}
}

static void Interf_Track_Basing_Rsz()
{
    KEY = Interf_Track_Basing_Rsz_KEY;
    MOUSE = Interf_Track_Basing_Rsz_MOUSE;
    button = Interf_Track_Basing_Rsz_button;
}


static void Interf_Start_Basing_Set_Size()
{
    if (! Interf_Start_Tracking(
              Region_Get_Cursor( current_uwinp, current_region ) ) )
        { Interf_Flash_Cancel(); return; }
    Interf_Set_Pos( cancel_pos );
    Interf_Setup_Basing_Rsz();
    { Interf_Track_Basing_Rsz(); return; }
}

static void Interf_Start_Basing_Rsz()
{ 
    resize_proc = Manage_Resize;
    { Interf_Start_Basing_Set_Size(); return; }
}



bool good_move;
TWPoint move_offset;
TWPoint move_pos;

static void Interf_Setup_Moving()
{
    extern void Interf_Track_Moving();
    Size move_siz;
    last_pos = current_pos;
    move_pos.x = current_pos.x + move_offset.x;
    move_pos.y = current_pos.y + move_offset.y;
    good_move = Userwin_Check_Move( current_uwinp, &move_pos, &move_siz );
    if ( good_move )
        Drawwin_Good_Move_Box( current_uwinp, move_pos, move_siz );
    else
        Drawwin_Bad_Move_Box( current_uwinp, move_pos, move_siz );
    { Interf_Track_Moving(); return; }
}

static void Interf_Cancel_Moving()
{
    Drawwin_Undo_Move_Box();
    Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
    if ( Userwin_Is_Open(current_uwinp) )
        Drawwin_Unshow_Moving(current_uwinp);
    else if (! Userwin_Ever_Opened(current_uwinp) )
        Interf_Watch(
            Manage_Client_Open_Icon(current_uwinp) )
    { Interf_Cancel(); return; }
}

static void Interf_Act_Moving()
{
    bool result;

    Drawwin_Undo_Move_Box();
    if ( Userwin_Is_Open(current_uwinp) )
        Drawwin_Unshow_Moving(current_uwinp);
    Interf_Watch(
    {
        result = Manage_Move( current_uwinp, move_pos );
    } )
    if ( result )
    {
        if ( UserGlobals_Get_Option(PLACE_CSR_IN_GADGET_AFT_MOVE) )
            Interf_Set_Pos( Region_Gadget_Center( current_uwinp ) );
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
        { Interf_Reenter_Region(); return; }
    }
    if ( Userwin_Is_Open(current_uwinp) )
        Drawwin_Show_Moving(current_uwinp);
    { Interf_Setup_Moving(); return; }
}

static void Interf_Track_Moving_KEY()
{
    extern void Interf_Track_Moving();
{

    Drawwin_Flash();
    { Interf_Track_Moving(); return; }

}
}

static void Interf_Track_Moving_MOUSE()
{
    extern void Interf_Track_Moving();
{

    if ( (last_pos.x == current_pos.x) && (last_pos.y == current_pos.y) )
        { Interf_Track_Moving(); return; }
    Drawwin_Undo_Move_Box();
    { Interf_Setup_Moving(); return; }

}
}

static void Interf_Track_Moving_button()
{
    extern void Interf_Track_Moving();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Moving(); return; }
    else if ( good_move && (current_kind != down) )
        { Interf_Arrange( Interf_Act_Moving, Interf_Cancel_Moving ); return; }
    { Interf_Track_Moving(); return; }

}
}

static void Interf_Track_Moving()
{
    KEY = Interf_Track_Moving_KEY;
    MOUSE = Interf_Track_Moving_MOUSE;
    button = Interf_Track_Moving_button;
}


static void Interf_Prepare_Moving()
{
    if ( UserGlobals_Get_Option(CENTER_CURSOR_ON_MOVE) )
        move_offset = Interf_Track_Center_Pos();
    else
        move_offset = Interf_Center_Offset();
    if ( Userwin_Is_Open(current_uwinp) )      
        Drawwin_Show_Moving(current_uwinp);
    { Interf_Setup_Moving(); return; }
}

static void Interf_Start_Moving()
{
    if (! Interf_Start_Tracking( move_tilecursor ))
        { Interf_Flash_Cancel(); return; }
    old_gravity = Tilwin_Get_Global_Option( ENABLE_GRAVITY );
    { Interf_Prepare_Moving(); return; }
}

static void Interf_Start_Gravity_Moving()
{
    if (! Interf_Start_Tracking( move_tilecursor ))
        { Interf_Flash_Cancel(); return; }
    old_gravity = Tilwin_Get_Global_Option( ENABLE_GRAVITY );
    if ( Buttons_Match(current_but,TOGGLE_GRAVITY_BUTTONS) )
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, !old_gravity );
    { Interf_Prepare_Moving(); return; }
}



static void Interf_Setup_Vert_Moving()
{
    extern void Interf_Track_Vert_Moving();
    Size move_siz;
    move_pos.x = Userwin_Get_Center(current_uwinp).x;
    move_pos.y = current_pos.y + move_offset.y;
    good_move = Userwin_Check_Move( current_uwinp, &move_pos, &move_siz );
    if ( good_move )
        Drawwin_Good_Move_Box( current_uwinp, move_pos, move_siz );
    else
        Drawwin_Bad_Move_Box( current_uwinp, move_pos, move_siz );
    { Interf_Track_Vert_Moving(); return; }
}

static void Interf_Cancel_Vert_Moving()
{
    Drawwin_Undo_Move_Box();
    Drawwin_Unshow_Moving(current_uwinp);
    Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
    { Interf_Cancel(); return; }
}

static void Interf_Act_Vert_Moving()
{
    bool result;

    Drawwin_Undo_Move_Box();
    Drawwin_Unshow_Moving(current_uwinp);
    Interf_Watch(
    {
        result = Manage_Move( current_uwinp, move_pos );
    } )
    if ( result )
    {
        if ( UserGlobals_Get_Option(PLACE_CSR_IN_GADGET_AFT_MOVE) )
            Interf_Set_Pos( Region_Gadget_Center( current_uwinp ) );
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
        { Interf_Reenter_Region(); return; }
    }
    Drawwin_Show_Moving(current_uwinp);
    { Interf_Setup_Vert_Moving(); return; }
}

static void Interf_Track_Vert_Moving_KEY()
{
    extern void Interf_Track_Vert_Moving();
{

    Drawwin_Flash();
    { Interf_Track_Vert_Moving(); return; }

}
}

static void Interf_Track_Vert_Moving_MOUSE()
{
    extern void Interf_Track_Vert_Moving();
{

    Drawwin_Undo_Move_Box();
    { Interf_Setup_Vert_Moving(); return; }

}
}

static void Interf_Track_Vert_Moving_button()
{
    extern void Interf_Track_Vert_Moving();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Vert_Moving(); return; }
    else if ( good_move && (current_kind != down) )
        { Interf_Arrange( Interf_Act_Vert_Moving, Interf_Cancel_Vert_Moving ); return; }
    { Interf_Track_Vert_Moving(); return; }

}
}

static void Interf_Track_Vert_Moving()
{
    KEY = Interf_Track_Vert_Moving_KEY;
    MOUSE = Interf_Track_Vert_Moving_MOUSE;
    button = Interf_Track_Vert_Moving_button;
}


static void Interf_Start_Vert_Moving()
{
    if (! Interf_Start_Tracking( move_tilecursor ))
        { Interf_Flash_Cancel(); return; }
    old_gravity = Tilwin_Get_Global_Option( ENABLE_GRAVITY );
    if ( Buttons_Match(current_but,TOGGLE_GRAVITY_BUTTONS) )
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, !old_gravity );
    if ( UserGlobals_Get_Option(CENTER_CURSOR_ON_MOVE) )
        move_offset = Interf_Track_Center_Pos();
    else
        move_offset = Interf_Center_Offset();
    Drawwin_Show_Moving(current_uwinp);
    Control_Set_Cursor( move_tilecursor );
    { Interf_Setup_Vert_Moving(); return; }
}



static void Interf_Setup_Horiz_Moving()
{
    extern void Interf_Track_Horiz_Moving();
    Size move_siz;
    move_pos.x = current_pos.x + move_offset.x;
    move_pos.y = Userwin_Get_Center(current_uwinp).y;
    good_move = Userwin_Check_Move( current_uwinp, &move_pos, &move_siz );
    if ( good_move )
        Drawwin_Good_Move_Box( current_uwinp, move_pos, move_siz );
    else
        Drawwin_Bad_Move_Box( current_uwinp, move_pos, move_siz );
    { Interf_Track_Horiz_Moving(); return; }
}

static void Interf_Cancel_Horiz_Moving()
{
    Drawwin_Undo_Move_Box();
    Drawwin_Unshow_Moving(current_uwinp);
    Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
    { Interf_Cancel(); return; }
}

static void Interf_Act_Horiz_Moving()
{
    bool result;

    Drawwin_Undo_Move_Box();
    Drawwin_Unshow_Moving(current_uwinp);
    Interf_Watch(
    {
        result = Manage_Move( current_uwinp, move_pos );
    } )
    if ( result )
    {
        if ( UserGlobals_Get_Option(PLACE_CSR_IN_GADGET_AFT_MOVE) )
            Interf_Set_Pos( Region_Gadget_Center( current_uwinp ) );
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
        { Interf_Reenter_Region(); return; }
    }
    Drawwin_Show_Moving(current_uwinp);
    { Interf_Setup_Horiz_Moving(); return; }
}

static void Interf_Track_Horiz_Moving_KEY()
{
    extern void Interf_Track_Horiz_Moving();
{

    Drawwin_Flash();
    { Interf_Track_Horiz_Moving(); return; }

}
}

static void Interf_Track_Horiz_Moving_MOUSE()
{
    extern void Interf_Track_Horiz_Moving();
{

    Drawwin_Undo_Move_Box();
    { Interf_Setup_Horiz_Moving(); return; }

}
}

static void Interf_Track_Horiz_Moving_button()
{
    extern void Interf_Track_Horiz_Moving();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Horiz_Moving(); return; }
    else if ( good_move && (current_kind != down) )
        { Interf_Arrange( Interf_Act_Horiz_Moving, Interf_Cancel_Horiz_Moving ); return; }
    { Interf_Track_Horiz_Moving(); return; }

}
}

static void Interf_Track_Horiz_Moving()
{
    KEY = Interf_Track_Horiz_Moving_KEY;
    MOUSE = Interf_Track_Horiz_Moving_MOUSE;
    button = Interf_Track_Horiz_Moving_button;
}


static void Interf_Start_Horiz_Moving()
{
    if (! Interf_Start_Tracking( move_tilecursor ))
        { Interf_Flash_Cancel(); return; }
    old_gravity = Tilwin_Get_Global_Option( ENABLE_GRAVITY );
    if ( Buttons_Match(current_but,TOGGLE_GRAVITY_BUTTONS) )
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, !old_gravity );
    if ( UserGlobals_Get_Option(CENTER_CURSOR_ON_MOVE) )
        move_offset = Interf_Track_Center_Pos();
    else
        move_offset = Interf_Center_Offset();
    Drawwin_Show_Moving(current_uwinp);
    Control_Set_Cursor( move_tilecursor );
    { Interf_Setup_Horiz_Moving(); return; }
}



static void Interf_Setup_Icon_Moving()
{
    extern void Interf_Track_Icon_Moving();
    Size move_siz;
    move_pos.x = current_pos.x + move_offset.x;
    move_pos.y = current_pos.y + move_offset.y;
    good_move = Userwin_Check_Icon_Move( current_uwinp, &move_pos, &move_siz );
    if ( good_move )
        DrawIcon_Good_Move_Box( current_uwinp, move_pos, move_siz );
    else
        DrawIcon_Bad_Move_Box( current_uwinp, move_pos, move_siz );
    { Interf_Track_Icon_Moving(); return; }
}

static void Interf_Cancel_Icon_Moving()
{
    DrawIcon_Undo_Move_Box();
    DrawIcon_Unshow_Moving(current_uwinp);
    Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
    { Interf_Cancel(); return; }
}

static void Interf_Act_Icon_Moving()
{
    bool result;

    DrawIcon_Undo_Move_Box();
    DrawIcon_Unshow_Moving(current_uwinp);
    Interf_Watch(
    {
        result = Manage_Icon_Move( current_uwinp, move_pos );
    } )
    if ( result )
    {
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, old_gravity );
        { Interf_Reenter_Region(); return; }
    }
    DrawIcon_Show_Moving(current_uwinp);
    { Interf_Setup_Icon_Moving(); return; }
}

static void Interf_Track_Icon_Moving_KEY()
{
    extern void Interf_Track_Icon_Moving();
{

    Drawwin_Flash();
    { Interf_Track_Icon_Moving(); return; }

}
}

static void Interf_Track_Icon_Moving_MOUSE()
{
    extern void Interf_Track_Icon_Moving();
{

    DrawIcon_Undo_Move_Box();
    { Interf_Setup_Icon_Moving(); return; }

}
}

static void Interf_Track_Icon_Moving_button()
{
    extern void Interf_Track_Icon_Moving();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Icon_Moving(); return; }
    else if ( good_move && (current_kind != down) )
        { Interf_Arrange( Interf_Act_Icon_Moving, Interf_Cancel_Icon_Moving ); return; }
    { Interf_Track_Icon_Moving(); return; }

}
}

static void Interf_Track_Icon_Moving()
{
    KEY = Interf_Track_Icon_Moving_KEY;
    MOUSE = Interf_Track_Icon_Moving_MOUSE;
    button = Interf_Track_Icon_Moving_button;
}


static void Interf_Start_Icon_Moving()
{
    if (! Interf_Start_Tracking( move_tilecursor ))
        { Interf_Flash_Cancel(); return; }
    old_gravity = Tilwin_Get_Global_Option( ENABLE_GRAVITY );
    if ( UserGlobals_Get_Option(CENTER_CURSOR_ON_MOVE) )
        move_offset = Interf_Track_Icon_Center_Pos();
    else
        move_offset = Interf_Icon_Center_Offset();
    DrawIcon_Show_Moving(current_uwinp);
    Control_Set_Cursor( move_tilecursor );
    { Interf_Setup_Icon_Moving(); return; }
}

static void Interf_Start_Gravity_Icon_Moving()
{
    if (! Interf_Start_Tracking( move_tilecursor ))
        { Interf_Flash_Cancel(); return; }
    old_gravity = Tilwin_Get_Global_Option( ENABLE_GRAVITY );
    if ( Buttons_Match(current_but,TOGGLE_GRAVITY_BUTTONS) )
        Tilwin_Set_Global_Option( ENABLE_GRAVITY, !old_gravity );
    if ( UserGlobals_Get_Option(CENTER_CURSOR_ON_MOVE) )
        move_offset = Interf_Track_Icon_Center_Pos();
    else
        move_offset = Interf_Icon_Center_Offset();
    DrawIcon_Show_Moving(current_uwinp);
    Control_Set_Cursor( move_tilecursor );
    { Interf_Setup_Icon_Moving(); return; }
}



Userwin *exchange_uwinp;
bool good_exchange;

static void Interf_Show_Exchanging()
{
    if ( Userwin_Is_Iconic( current_uwinp ) )
        DrawIcon_Show_Moving( current_uwinp );
    else
        Drawwin_Show_Moving( current_uwinp );
}

static void Interf_Unshow_Exchanging()
{
    if ( Userwin_Is_Iconic( current_uwinp ) )
        DrawIcon_Unshow_Moving( current_uwinp );
    else
        Drawwin_Unshow_Moving( current_uwinp );
}

static void Interf_Setup_Exchanging() 
{
    extern void Interf_Track_Exchanging();
    exchange_uwinp = Manage_Locate( current_pos );
    good_exchange = 
        (   ( exchange_uwinp != current_uwinp )
         && ( exchange_uwinp != UWIN_NULL )   );
    if ( good_exchange )
        Control_Set_Cursor(good_exchange_tilecursor);
    else
        Control_Set_Cursor(bad_exchange_tilecursor);
    { Interf_Track_Exchanging(); return; }
}

static void Interf_Cancel_Exchanging()
{
    Interf_Unshow_Exchanging();
    { Interf_Cancel(); return; }
}

static void Interf_Act_Exchanging()
{
    bool result;

    Interf_Unshow_Exchanging();
    Interf_Watch(
    {
        result = Manage_Exchange( current_uwinp, exchange_uwinp );
    } )
    if ( result )
    {
        if ( UserGlobals_Get_Option(
                 PLACE_CSR_IN_GADGET_AFT_EXCHANGE) &&
             (! Userwin_Is_Iconic( current_uwinp ) ) )
            Interf_Set_Pos( Region_Gadget_Center( current_uwinp ) );
        { Interf_Reenter_Region(); return; }
    }
    Interf_Show_Exchanging();
    { Interf_Setup_Exchanging(); return; }
}

static void Interf_Track_Exchanging_KEY()
{
    extern void Interf_Track_Exchanging();
{

    Drawwin_Flash();
    { Interf_Track_Exchanging(); return; }

}
}

static void Interf_Track_Exchanging_MOUSE()
{
    extern void Interf_Track_Exchanging();
{

    { Interf_Setup_Exchanging(); return; }

}
}

static void Interf_Track_Exchanging_button()
{
    extern void Interf_Track_Exchanging();
{

    if ( Buttons_Match(current_but,CANCEL_BUTTONS) )
        { Interf_Cancel_Exchanging(); return; }
    else if ( good_exchange && ( current_kind != down ) )
        { Interf_Arrange( Interf_Act_Exchanging, Interf_Cancel_Exchanging ); return; }
    else
        Drawwin_Flash();
    { Interf_Setup_Exchanging(); return; }

}
}

static void Interf_Track_Exchanging()
{
    KEY = Interf_Track_Exchanging_KEY;
    MOUSE = Interf_Track_Exchanging_MOUSE;
    button = Interf_Track_Exchanging_button;
}


static void Interf_Start_Exchanging()
{
    if (! Interf_Start_Tracking( bad_exchange_tilecursor ) )
        { Interf_Flash_Cancel(); return; }
    Interf_Show_Exchanging();
    { Interf_Setup_Exchanging(); return; }
}



static void Interf_Start_Relocating()
{
    if (! Interf_Start_Tracking(track_open_tilecursor))
        { Interf_Flash_Cancel(); return; }
    if ( UserGlobals_Get_Option(CENTER_CURSOR_ON_RELOCATE) )
        Interf_Track_Center_Pos();
    { Interf_Start_Opening(); return; }
}


static void Interf_Close()
{
    Interf_Watch(
        Manage_Close(current_uwinp) )
    if ( UserGlobals_Get_Option(PLACE_CSR_IN_ICON_AFTER_CLOSE) &&
         Userwin_Is_Iconic(current_uwinp) )
        Interf_Set_Pos( Userwin_Get_Icon_Center(current_uwinp) );
    change_state = TRUE;
    { Interf_Reenter_Region(); return; }
}    


static void Interf_Invoke()
{
    Tool_Invoke(0);
    { Interf_Reenter_Region(); return; }
}

static void Interf_Redraw_All()
{
    Manage_Redraw_All();
    { Interf_Reenter_Region(); return; }
}

static void Interf_Redraw()
{
    Manage_Redraw( current_uwinp );
    { Interf_Reenter_Region(); return; }
}

static void Interf_Enlarge()
{
    Interf_Watch(
        Manage_Enlarge(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Desire()
{
    Interf_Watch(
        Manage_Desire(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Toggle_Zoom()
{
    Interf_Watch(
        Manage_Toggle_Zoom(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Toggle_Zoom_Lock()
{
    Interf_Watch(
        Manage_Toggle_Zoom_Lock(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Open()
{
    bool result;

    Interf_Watch(
    {
        result = Manage_User_Open_Automatically(
             current_uwinp, FALSE, FALSE );
    } )
    if ( result &&
         UserGlobals_Get_Option(
             PLACE_CSR_GDGT_AFT_US_AUTO_OPEN) )
        Interf_Set_Pos( Region_Gadget_Center(current_uwinp) );
    { Interf_Reenter_Region(); return; }
}



static void Interf_Inside_Background_ENTER()
{
    extern void Interf_Inside_Background();
{

    { Interf_Enter_Region(); return; }

}
}

static void Interf_Inside_Background_KEY()
{
    extern void Interf_Inside_Background();
{

    Interf_Handle_Key();
    { Interf_Inside_Background(); return; }

}
}

static void Interf_Inside_Background_button()
{
    extern void Interf_Inside_Background();
{

    if ( Buttons_Match( current_but, TOOL_BUTTONS ) )
    {
        if (current_kind != up)
            { Interf_Act( Interf_Invoke ); return; }
    }
    else if ( Buttons_Match( current_but, REDRAW_BUTTONS ) )
    {
        if (current_kind != up)
            { Interf_Act( Interf_Redraw_All ); return; }
    }
    else if ( Buttons_Match( current_but, HEADER_MANAGER_MENU_BUTTONS ) )
    {
        if (current_kind != up)
        {
            { Interf_Menu_Enter( manager_background_menu, Buttons_Number(current_but ), current_kind ); return; }
        }
    }
    else
    {
        Interf_Handle_Button();
        { Interf_Inside_Background(); return; }
    }

}
}

static void Interf_Inside_Background()
{
    ENTER = Interf_Inside_Background_ENTER;
    KEY = Interf_Inside_Background_KEY;
    button = Interf_Inside_Background_button;
}



static void Interf_Leave()
{
    Interf_Handle_Leave();
    current_uwinp = UWIN_NULL;
    current_region = Region_Locate( current_uwinp, current_pos );
    { Interf_Enter_Region(); return; }
}


static void Interf_Inside_Rtl_LEAVE()
{
    extern void Interf_Inside_Rtl();
{

    { Interf_Leave(); return; }

}
}

static void Interf_Inside_Rtl_ENTER()
{
    extern void Interf_Inside_Rtl();
{

    { Interf_Enter_Region(); return; }

}
}

static void Interf_Inside_Rtl_KEY()
{
    extern void Interf_Inside_Rtl();
{

    Drawwin_Flash();
    { Interf_Inside_Rtl(); return; }

}
}

static void Interf_Inside_Rtl_button()
{
    extern void Interf_Inside_Rtl();
{

    if ( UserGlobals_Get_Option(REDRAW_IN_ICON) &&
            Buttons_Match( current_but, REDRAW_BUTTONS ) )
    {
        if (current_kind != up)
            { Interf_Act( Interf_Redraw_All ); return; }
    }
    else if ( UserGlobals_Get_Option(EXCHANGE_IN_ICON) &&
            Buttons_Match(current_but,EXCHANGE_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Start_Exchanging(); return; }
    }
    else if ( UserGlobals_Get_Option(MOVE_IN_ICON) &&
            Buttons_Match(current_but,ICON_MOVE_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Start_Gravity_Icon_Moving(); return; }
    }
    else if ( Buttons_Match( current_but, EXIT_BUTTONS ) )
    {
        if (current_kind != up)
            { Interf_Start_Wait_For_Confirm(exitmsg,Interf_Confirmed_Exit); return; }
    }
    else if ( Buttons_Match( current_but, HEADER_MANAGER_MENU_BUTTONS ) )
    {
        if ( current_kind != up )
            { Interf_Menu_Enter( manager_background_menu, Buttons_Number(current_but ), current_kind ); return; }
    }
    else
    {
        Interf_Handle_Button();
        { Interf_Inside_Rtl(); return; }
    }
    { Interf_Inside_Rtl(); return; }

}
}

static void Interf_Inside_Rtl()
{
    LEAVE = Interf_Inside_Rtl_LEAVE;
    ENTER = Interf_Inside_Rtl_ENTER;
    KEY = Interf_Inside_Rtl_KEY;
    button = Interf_Inside_Rtl_button;
}



static void Interf_Inside_Body_LEAVE()
{
    extern void Interf_Inside_Body();
{

    { Interf_Leave(); return; }

}
}

static void Interf_Inside_Body_ENTER()
{
    extern void Interf_Inside_Body();
{

    { Interf_Enter_Region(); return; }

}
}

static void Interf_Inside_Body_MOUSE()
{
    extern void Interf_Inside_Body();
{

    Client_Send_Mouse(current_uwinp, 
        current_butstate, current_pos);
    { Interf_Inside_Body(); return; }

}
}

static void Interf_Inside_Body_KEY()
{
    extern void Interf_Inside_Body();
{

    Interf_Handle_Key();
    { Interf_Inside_Body(); return; }

}
}

static void Interf_Inside_Body_button()
{
    extern void Interf_Inside_Body();
{

    if ( UserGlobals_Get_Option(MANAGER_MENU_IN_BODY) && 
            Buttons_Match(current_but,BODY_MANAGER_MENU_BUTTONS) )
    {
        if ( current_kind != up ) 
            { Interf_Menu_Enter( manager_window_menu, Buttons_Number(current_but), current_kind ); return; }
    }
    else if ( UserGlobals_Get_Option(USER_MENU_IN_BODY)
         && Buttons_Match(current_but,BODY_USER_MENU_BUTTONS) )
    {
        if ( current_kind != up ) 
            { Interf_Menu_Enter( Region_Get_Menu(current_uwinp,current_region), Buttons_Number(current_but), current_kind ); return; }
    }
    else
        Interf_Handle_Button();
    { Interf_Inside_Body(); return; }

}
}

static void Interf_Inside_Body()
{
    LEAVE = Interf_Inside_Body_LEAVE;
    ENTER = Interf_Inside_Body_ENTER;
    MOUSE = Interf_Inside_Body_MOUSE;
    KEY = Interf_Inside_Body_KEY;
    button = Interf_Inside_Body_button;
}



static void Interf_Inside_Header_LEAVE()
{
    extern void Interf_Inside_Header();
{

    { Interf_Leave(); return; }

}
}

static void Interf_Inside_Header_ENTER()
{
    extern void Interf_Inside_Header();
{

    { Interf_Enter_Region(); return; }

}
}

static void Interf_Inside_Header_KEY()
{
    extern void Interf_Inside_Header();
{

    Interf_Handle_Key();
    { Interf_Inside_Header(); return; }

}
}

static void Interf_Inside_Header_button()
{
    extern void Interf_Inside_Header();
{

    if ( UserGlobals_Get_Option(REDRAW_IN_HEADER) &&
        Buttons_Match(current_but,REDRAW_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Act( Interf_Redraw ); return; }
    }
    else if ( UserGlobals_Get_Option(CLOSE_IN_HEADER) &&
        Buttons_Match(current_but,CLOSE_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Act( Interf_Close ); return; }
    }
    else if ( UserGlobals_Get_Option(ZOOM_IN_HEADER) &&
            Buttons_Match(current_but,ZOOM_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Act( Interf_Toggle_Zoom ); return; }
    }
    else if ( UserGlobals_Get_Option(DESIRE_IN_HEADER) &&
            Buttons_Match(current_but,DESIRE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Desire ); return; }
    }
    else if ( UserGlobals_Get_Option(ENLARGE_IN_HEADER) &&
            Buttons_Match(current_but,ENLARGE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Enlarge ); return; }
    }
    else if ( UserGlobals_Get_Option(RESIZE_IN_HEADER) &&
            Buttons_Match(current_but,RESIZE_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Start_Basing_Rsz(); return; }
    }
    else if ( UserGlobals_Get_Option(RELOCATE_IN_HEADER) &&
            Buttons_Match(current_but,RELOCATE_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Start_Relocating(); return; }
    }
    else if ( UserGlobals_Get_Option(EXCHANGE_IN_HEADER) &&
            Buttons_Match(current_but,EXCHANGE_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Start_Exchanging(); return; }
    }
    else if ( UserGlobals_Get_Option(MOVE_IN_HEADER) &&
            Buttons_Match(current_but,MOVE_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Start_Gravity_Moving(); return; }
    }
    if ( UserGlobals_Get_Option(USER_MENU_IN_HEADER) && 
        Buttons_Match(current_but,HEADER_USER_MENU_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Menu_Enter( Region_Get_Menu(current_uwinp,current_region), Buttons_Number(current_but), current_kind ); return; }
    }
    else if ( UserGlobals_Get_Option(MANAGER_MENU_IN_HEADER) && 
        Buttons_Match(current_but,HEADER_MANAGER_MENU_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Menu_Enter( manager_window_menu, Buttons_Number(current_but), current_kind ); return; }
    }
    else
        Interf_Handle_Button();
    { Interf_Inside_Header(); return; }

}
}

static void Interf_Inside_Header()
{
    LEAVE = Interf_Inside_Header_LEAVE;
    ENTER = Interf_Inside_Header_ENTER;
    KEY = Interf_Inside_Header_KEY;
    button = Interf_Inside_Header_button;
}



static void Interf_Inside_Icon_LEAVE()
{
    extern void Interf_Inside_Icon();
{

    { Interf_Leave(); return; }

}
}

static void Interf_Inside_Icon_ENTER()
{
    extern void Interf_Inside_Icon();
{

    { Interf_Enter_Region(); return; }

}
}

static void Interf_Inside_Icon_KEY()
{
    extern void Interf_Inside_Icon();
{

    Interf_Handle_Key();
    { Interf_Inside_Icon(); return; }

}
}

static void Interf_Inside_Icon_button()
{
    extern void Interf_Inside_Icon();
{

    if ( Buttons_Match(current_but,ICON_OPEN_BUTTONS) )
    {
        if ( Userwin_Group_Closed( current_uwinp ) )
        {
            if (current_kind != up)
                { Interf_Start_Wait_For_Confirm(groupmsg,Interf_Confirmed_Group_Open); return; }
        }
        else if ( Userwin_Notifies_Icon( current_uwinp ) )
        {
            if (current_kind != up)
                { Interf_Start_Wait_For_Confirm(notifymsg,Interf_Confirmed_Icon_Notify); return; }
        }
        else
        {
            if ( UserGlobals_Get_Option(AUTO_PLACE_ON_ICON_OPEN) )
            {
                if ( UserGlobals_Get_Option(AUTO_PLACE_ON_UNSIZED_OPEN) || 
                     Userwin_Sized( current_uwinp ) )
                {
                    if ( current_kind != up )
                        { Interf_Act( Interf_Open ); return; }
                }
                else if ( current_kind != up )
                {
                    if (! Interf_Start_Tracking(track_open_tilecursor))
                        { Interf_Flash_Cancel(); return; }
                    { Interf_Start_Opening(); return; }
                }
            }
            else if ( current_kind != up )
            {
                if ( Manage_Get_Focus() == current_uwinp )
                    Manage_Switch_Focus( UWIN_NULL );
                { Interf_Start_Open_In_Icon(); return; }
            }
        }
    }
    else if ( UserGlobals_Get_Option(REDRAW_IN_ICON) &&
            Buttons_Match(current_but,REDRAW_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Act( Interf_Redraw ); return; }
    }
    else if ( UserGlobals_Get_Option(EXCHANGE_IN_ICON) &&
            Buttons_Match(current_but,EXCHANGE_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Start_Exchanging(); return; }
    }
    else if ( UserGlobals_Get_Option(MOVE_IN_ICON) &&
            Buttons_Match(current_but,ICON_MOVE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Gravity_Icon_Moving(); return; }
    }
    else if ( UserGlobals_Get_Option(USER_MENU_IN_ICON) &&
            Buttons_Match(current_but,HEADER_USER_MENU_BUTTONS) )
    {
        if ( current_kind != up ) 
            { Interf_Menu_Enter( Region_Get_Menu(current_uwinp,current_region), Buttons_Number(current_but), current_kind ); return; }
    }
    else if ( UserGlobals_Get_Option(MANAGER_MENU_IN_ICON) && 
            Buttons_Match(current_but,HEADER_MANAGER_MENU_BUTTONS) )
    {
        if ( current_kind != up ) 
            { Interf_Menu_Enter( manager_icon_menu, Buttons_Number(current_but), current_kind ); return; }
    }
    else if ( Buttons_Match(current_but,DISCONNECT_BUTTONS) )
    {
        if (current_kind != up)
            { Interf_Start_Wait_For_Confirm(hardmsg,Interf_Confirmed_Hard_Kill); return; }
    }
    else
        Interf_Handle_Button();
    { Interf_Inside_Icon(); return; }

}
}

static void Interf_Inside_Icon()
{
    LEAVE = Interf_Inside_Icon_LEAVE;
    ENTER = Interf_Inside_Icon_ENTER;
    KEY = Interf_Inside_Icon_KEY;
    button = Interf_Inside_Icon_button;
}



static void Interf_Inside_Zoom_Gadget_LEAVE()
{
    extern void Interf_Inside_Zoom_Gadget();
{

    { Interf_Leave(); return; }

}
}

static void Interf_Inside_Zoom_Gadget_ENTER()
{
    extern void Interf_Inside_Zoom_Gadget();
{

    { Interf_Enter_Region(); return; }

}
}

static void Interf_Inside_Zoom_Gadget_KEY()
{
    extern void Interf_Inside_Zoom_Gadget();
{

    Interf_Handle_Key();
    { Interf_Inside_Zoom_Gadget(); return; }

}
}

static void Interf_Inside_Zoom_Gadget_button()
{
    extern void Interf_Inside_Zoom_Gadget();
{

    if ( UserGlobals_Get_Option(REDRAW_IN_ZOOM_GADGET) &&
        Buttons_Match(current_but,REDRAW_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Redraw ); return; }
    }
    else if ( UserGlobals_Get_Option(CLOSE_IN_ZOOM_GADGET) &&
        Buttons_Match(current_but,CLOSE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Close ); return; }
    }
    else if ( UserGlobals_Get_Option(ZOOM_IN_ZOOM_GADGET) &&
            Buttons_Match(current_but,ZOOM_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Toggle_Zoom ); return; }
    }
    else if ( UserGlobals_Get_Option(DESIRE_IN_ZOOM_GADGET) &&
            Buttons_Match(current_but,DESIRE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Desire ); return; }
    }
    else if ( UserGlobals_Get_Option(ENLARGE_IN_ZOOM_GADGET) &&
            Buttons_Match(current_but,ENLARGE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Enlarge ); return; }
    }
    else if ( UserGlobals_Get_Option(RESIZE_IN_ZOOM_GADGET) &&
            Buttons_Match(current_but,RESIZE_BUTTONS) )
    {
        if ( current_kind != up )
        {
            current_side = Top_Left;
            current_region = Region_Make_Corner( Top_Left );
            { Interf_Start_Crnr_Rszng(); return; }
        }
    }
    else if ( UserGlobals_Get_Option(RELOCATE_IN_ZOOM_GADGET) &&
            Buttons_Match(current_but,RELOCATE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Relocating(); return; }
    }
    else if ( UserGlobals_Get_Option(EXCHANGE_IN_ZOOM_GADGET) &&
        Buttons_Match(current_but,EXCHANGE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Exchanging(); return; }
    }
    else if ( UserGlobals_Get_Option(MOVE_IN_ZOOM_GADGET) &&
        Buttons_Match(current_but,MOVE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Moving(); return; }
    }
    { Interf_Inside_Zoom_Gadget(); return; }

}
}

static void Interf_Inside_Zoom_Gadget()
{
    LEAVE = Interf_Inside_Zoom_Gadget_LEAVE;
    ENTER = Interf_Inside_Zoom_Gadget_ENTER;
    KEY = Interf_Inside_Zoom_Gadget_KEY;
    button = Interf_Inside_Zoom_Gadget_button;
}



static void Interf_Inside_Move_Gadget_LEAVE()
{
    extern void Interf_Inside_Move_Gadget();
{

    { Interf_Leave(); return; }

}
}

static void Interf_Inside_Move_Gadget_ENTER()
{
    extern void Interf_Inside_Move_Gadget();
{

    { Interf_Enter_Region(); return; }

}
}

static void Interf_Inside_Move_Gadget_KEY()
{
    extern void Interf_Inside_Move_Gadget();
{

    Interf_Handle_Key();
    { Interf_Inside_Move_Gadget(); return; }

}
}

static void Interf_Inside_Move_Gadget_button()
{
    extern void Interf_Inside_Move_Gadget();
{

    if ( UserGlobals_Get_Option(REDRAW_IN_MOVE_GADGET) &&
        Buttons_Match(current_but,REDRAW_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Redraw ); return; }
    }
    else if ( UserGlobals_Get_Option(CLOSE_IN_MOVE_GADGET) &&
        Buttons_Match(current_but,CLOSE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Close ); return; }
    }
    else if ( UserGlobals_Get_Option(RESIZE_IN_MOVE_GADGET) &&
            Buttons_Match(current_but,RESIZE_BUTTONS) )
    {
        if ( current_kind != up )
        {
            current_side = Top_Right;
            current_region = Region_Make_Corner( Top_Right );
            { Interf_Start_Crnr_Rszng(); return; }
        }
    }
    else if ( UserGlobals_Get_Option(RELOCATE_IN_MOVE_GADGET) &&
            Buttons_Match(current_but,RELOCATE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Relocating(); return; }
    }
    else if ( UserGlobals_Get_Option(EXCHANGE_IN_MOVE_GADGET) &&
            Buttons_Match(current_but,EXCHANGE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Exchanging(); return; }
    }
    else if ( UserGlobals_Get_Option(MOVE_IN_MOVE_GADGET) &&
            Buttons_Match(current_but,MOVE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Moving(); return; }
    }
    else if ( UserGlobals_Get_Option(ZOOM_IN_MOVE_GADGET) &&
            Buttons_Match(current_but,ZOOM_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Toggle_Zoom ); return; }
    }
    else if ( UserGlobals_Get_Option(DESIRE_IN_MOVE_GADGET) &&
            Buttons_Match(current_but,DESIRE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Desire ); return; }
    }
    else if ( UserGlobals_Get_Option(ENLARGE_IN_MOVE_GADGET) &&
            Buttons_Match(current_but,ENLARGE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Enlarge ); return; }
    }
    { Interf_Inside_Move_Gadget(); return; }

}
}

static void Interf_Inside_Move_Gadget()
{
    LEAVE = Interf_Inside_Move_Gadget_LEAVE;
    ENTER = Interf_Inside_Move_Gadget_ENTER;
    KEY = Interf_Inside_Move_Gadget_KEY;
    button = Interf_Inside_Move_Gadget_button;
}



static void Interf_Inside_Side_Border_LEAVE()
{
    extern void Interf_Inside_Side_Border();
{

    { Interf_Leave(); return; }

}
}

static void Interf_Inside_Side_Border_ENTER()
{
    extern void Interf_Inside_Side_Border();
{

    { Interf_Enter_Region(); return; }

}
}

static void Interf_Inside_Side_Border_KEY()
{
    extern void Interf_Inside_Side_Border();
{

    Interf_Handle_Key();
    { Interf_Inside_Side_Border(); return; }

}
}

static void Interf_Inside_Side_Border_button()
{
    extern void Interf_Inside_Side_Border();
{

    if ( UserGlobals_Get_Option(ZOOM_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,ZOOM_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Toggle_Zoom ); return; }
    }
    else if ( UserGlobals_Get_Option(DESIRE_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,DESIRE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Desire ); return; }
    }
    else if ( UserGlobals_Get_Option(ENLARGE_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,ENLARGE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Enlarge ); return; }
    }
    else if ( UserGlobals_Get_Option(REDRAW_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,REDRAW_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Redraw ); return; }
    }
    else if ( UserGlobals_Get_Option(CLOSE_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,CLOSE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Close ); return; }
    }
    else if ( UserGlobals_Get_Option(RESIZE_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,RESIZE_BUTTONS) )
    {
        if ( current_kind != up )
        {
            current_side = Region_Get_Border(current_region);
            { Interf_Start_Edge_Resizing(); return; }
        }
    }
    else if ( UserGlobals_Get_Option(RELOCATE_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,RELOCATE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Relocating(); return; }
    }
    else if ( UserGlobals_Get_Option(EXCHANGE_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,EXCHANGE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Exchanging(); return; }
    }
    else if ( UserGlobals_Get_Option(MOVE_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,MOVE_BUTTONS) )
    {
        if ( current_kind != up )
        {
            switch ( Region_Get_Border(current_region) )
            {
                case Top:
                case Bottom:
                    { Interf_Start_Vert_Moving(); return; }
                case Left:
                case Right:
                    { Interf_Start_Horiz_Moving(); return; }
            }
        }
    }
    else if ( UserGlobals_Get_Option(USER_MENU_IN_SIDE_BORDER) &&
            Buttons_Match(current_but,HEADER_USER_MENU_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Menu_Enter( Region_Get_Menu(current_uwinp,current_region), Buttons_Number(current_but), current_kind ); return; }
    }
    else if ( UserGlobals_Get_Option(MANAGER_MENU_IN_SIDE_BORDER) && 
            Buttons_Match(current_but,HEADER_MANAGER_MENU_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Menu_Enter( manager_window_menu, Buttons_Number(current_but), current_kind ); return; }
    }
    { Interf_Inside_Side_Border(); return; }

}
}

static void Interf_Inside_Side_Border()
{
    LEAVE = Interf_Inside_Side_Border_LEAVE;
    ENTER = Interf_Inside_Side_Border_ENTER;
    KEY = Interf_Inside_Side_Border_KEY;
    button = Interf_Inside_Side_Border_button;
}



static void Interf_Ins_Crnr_Border_LEAVE()
{
    extern void Interf_Ins_Crnr_Border();
{

    { Interf_Leave(); return; }

}
}

static void Interf_Ins_Crnr_Border_ENTER()
{
    extern void Interf_Ins_Crnr_Border();
{

    { Interf_Enter_Region(); return; }

}
}

static void Interf_Ins_Crnr_Border_KEY()
{
    extern void Interf_Ins_Crnr_Border();
{

    Interf_Handle_Key();
    { Interf_Ins_Crnr_Border(); return; }

}
}

static void Interf_Ins_Crnr_Border_button()
{
    extern void Interf_Ins_Crnr_Border();
{

    if ( UserGlobals_Get_Option(ZOOM_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,ZOOM_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Toggle_Zoom ); return; }
    }
    else if ( UserGlobals_Get_Option(DESIRE_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,DESIRE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Desire ); return; }
    }
    else if ( UserGlobals_Get_Option(ENLARGE_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,ENLARGE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Enlarge ); return; }
    }
    else if ( UserGlobals_Get_Option(REDRAW_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,REDRAW_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Redraw ); return; }
    }
    else if ( UserGlobals_Get_Option(CLOSE_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,CLOSE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Act( Interf_Close ); return; }
    }
    else if ( UserGlobals_Get_Option(RESIZE_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,RESIZE_BUTTONS) )
    {
        if ( current_kind != up )
        {
            current_side = Region_Get_Border(current_region);
            { Interf_Start_Crnr_Rszng(); return; }
        }
    }
    else if ( UserGlobals_Get_Option(RELOCATE_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,RELOCATE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Relocating(); return; }
    }
    else if ( UserGlobals_Get_Option(EXCHANGE_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,EXCHANGE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Exchanging(); return; }
    }
    else if ( UserGlobals_Get_Option(MOVE_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,MOVE_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Start_Gravity_Moving(); return; }
    }
    else if ( UserGlobals_Get_Option(USER_MENU_IN_CORNER_BORDER) &&
            Buttons_Match(current_but,HEADER_USER_MENU_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Menu_Enter( Region_Get_Menu(current_uwinp,current_region), Buttons_Number(current_but), current_kind ); return; }
    }
    else if ( UserGlobals_Get_Option(MANAGER_MENU_IN_CORNER_BORDER) && 
            Buttons_Match(current_but,HEADER_MANAGER_MENU_BUTTONS) )
    {
        if ( current_kind != up )
            { Interf_Menu_Enter( manager_window_menu, Buttons_Number(current_but), current_kind ); return; }
    }
    { Interf_Ins_Crnr_Border(); return; }

}
}

static void Interf_Ins_Crnr_Border()
{
    LEAVE = Interf_Ins_Crnr_Border_LEAVE;
    ENTER = Interf_Ins_Crnr_Border_ENTER;
    KEY = Interf_Ins_Crnr_Border_KEY;
    button = Interf_Ins_Crnr_Border_button;
}



static void Interf_Manage_Icon_Open( uwinp )
    Userwin *uwinp;
{
    if ( Userwin_Group_Closed( uwinp ) )
        Manage_Want_State( uwinp, IconicState );
    else
        Interf_Client_Watch(
            Manage_Client_Open_Icon( uwinp ) )
}

/* ------------------------------------------------------------ */

static void Interf_Manage_Open( uwinp )
    Userwin *uwinp;
{
    bool result;
    current_uwinp = uwinp;

    if ( Userwin_Group_Closed( uwinp ) )
        Manage_Want_State( uwinp, NormalState );

    else if ( Userwin_Get_Window_Option( uwinp, AUTO_PLACE_ON_CLIENT_OPEN )
              && ( UserGlobals_Get_Option(AUTO_PLACE_ON_UNSIZED_OPEN) ||
                   Userwin_Sized( uwinp ) ) )
    {
        Interf_Client_Watch(
        {
            result = Manage_Client_Open_Automatically( uwinp );
            if ( result &&
                 UserGlobals_Get_Option(
                     PLACE_CSR_GDGT_AFT_CL_AUTO_OPEN) )
                Interf_Set_Pos( Region_Gadget_Center( uwinp ) );
        } )
    }
    else if ( Userwin_Ever_Opened(uwinp) )
    {
        if (! Interf_Client_Start_Tracking(track_open_tilecursor))
            Drawwin_Flash();
        else
            { Interf_Start_Opening(); return; }
    }
    else    
    {
        if (! Interf_Client_Start_Tracking(track_open_tilecursor))
        {
            Drawwin_Flash();
            Interf_Client_Watch(
                Manage_Client_Open_Icon(uwinp) )
        }
        else
            { Interf_Start_Opening(); return; }
    }
}

/* ------------------------------------------------------------ */

void Interf_Client_Open( uwinp )
    Userwin *uwinp;
{
    int state;
    
    state = Userwin_State(uwinp);

    if ( ! Userwin_Ever_Opened( uwinp ) )
    {
        Manage_Prepare_Open( uwinp );

        if ( (state == NormalState) ||
             (state == ClientIconState) ||
             ( ( Userwin_Laid_Out(uwinp) ||
                 (state == NoState) || (state == DontCareState) ) &&
               Userwin_Get_Window_Option( uwinp, AUTO_OPEN_ON_CREATE ) ) )
        {
            user_window_join_excursion( uwinp, AUTO_PLACE_ON_CLIENT_OPEN,
                ( Userwin_Sized(uwinp) && Userwin_Positioned(uwinp) ),
                Interf_Manage_Open( uwinp ) )
        }
        else
            Interf_Manage_Icon_Open( uwinp );
    }
    else if ( (! Userwin_Is_Open( uwinp )) &&
              ( (state == NoState) || 
                (state == DontCareState) ||
                (state == NormalState) ) )
        Interf_Manage_Open( uwinp );
}


void Interf_Client_Note_Output( uwinp )
    Userwin *uwinp;
{
    int state;
    
    state = Userwin_State(uwinp);
    Manage_Note_Output( uwinp );

    if ( ! Userwin_Ever_Opened( uwinp ) )
    {
        Manage_Prepare_Open( uwinp );

        if ( (state == NormalState) ||
             (state == ClientIconState) ||
             ( ( Userwin_Laid_Out(uwinp) ||
                 (state == NoState) || (state == DontCareState) ) &&
               ( Userwin_Get_Window_Option( uwinp, AUTO_OPEN_ON_CREATE ) ||
                 Userwin_Get_Window_Option( uwinp, AUTO_OPEN_ON_WRITE ) ) ) )
        {
            user_window_join_excursion( uwinp, AUTO_PLACE_ON_CLIENT_OPEN,
                ( Userwin_Sized(uwinp) && Userwin_Positioned(uwinp) ),
                Interf_Manage_Open( uwinp ) )
        }
        else
            Interf_Manage_Icon_Open( uwinp );
    }            
    else if ( (! Userwin_Is_Open( uwinp )) &&
              ( (state == NoState) || 
                (state == DontCareState) ||
                (state == NormalState) ) &&
              Userwin_Get_Window_Option( uwinp, AUTO_OPEN_ON_WRITE ) )
        Interf_Manage_Open( uwinp );
}


void Interf_Client_Icon_Open( uwinp )
    Userwin *uwinp;
{
    int state;
    
    state = Userwin_State(uwinp);

    if ( ! Userwin_Ever_Opened( uwinp ) )
    {
        Manage_Prepare_Open( uwinp );

        if ( ( state == ClientIconState ) ||
             ( Userwin_Laid_Out(uwinp) &&
               Userwin_Get_Window_Option( uwinp, AUTO_OPEN_ON_CREATE ) ) )
        {
            user_window_join_excursion( uwinp, AUTO_PLACE_ON_CLIENT_OPEN,
                ( Userwin_Sized(uwinp) && Userwin_Positioned(uwinp) ),
                Interf_Manage_Open( uwinp ) )
        }
        else
            Interf_Manage_Icon_Open( uwinp );
    }
    else if ( Userwin_Is_Open( uwinp ) &&
              ( (state == NoState) || 
                (state == DontCareState) ||
                (state == NormalState) ) )
        Interf_Manage_Icon_Open( uwinp );
}


void Interf_Client_Close( uwinp )
    Userwin *uwinp;
{
    int state;
    
    state = Userwin_State(uwinp);

    if ( ! Userwin_Ever_Opened( uwinp ) )
    {
        Manage_Prepare_Open( uwinp );

        if ( ( state == ClientIconState ) ||
             ( Userwin_Laid_Out(uwinp) &&
               Userwin_Get_Window_Option( uwinp, AUTO_OPEN_ON_CREATE ) ) )
        {
            user_window_join_excursion( uwinp, AUTO_PLACE_ON_CLIENT_OPEN,
                ( Userwin_Sized(uwinp) && Userwin_Positioned(uwinp) ),
                Interf_Manage_Open( uwinp ) )
        }
        else
            Interf_Manage_Icon_Open( uwinp );
    }
    else if (! Userwin_Group_Closed( uwinp ) )
    {
        if ( state == ClientIconState )
            Drawwin_Open( uwinp );
        else 
            Interf_Client_Watch(
                Manage_Client_Close( uwinp ) )
    }
}


void Interf_Client_Icon_Close( uwinp )
    Userwin *uwinp;
{
    if ( Userwin_Ever_Opened( uwinp ) )
        Interf_Client_Watch(
            Manage_Client_Close_Icon( uwinp ) )
}


void Interf_Client_Set_State( uwinp, state )
    Userwin *uwinp;
    int state;
{
    if ( ! Userwin_Ever_Opened( uwinp ) )
        Manage_Client_Set_State( uwinp, state );
    else
        Interf_Client_Watch(
            Manage_Client_Change_State( uwinp, state ) )
}


void Interf_Client_Set_Group( uwinp, group )
    Userwin *uwinp;
    Userwin *group;
{
    if ( ! Userwin_Ever_Opened( uwinp ) )
        Manage_Client_Set_Group( uwinp, group );
    else
        Interf_Client_Watch(
            Manage_Client_Set_Group( uwinp, group ) )
}


void Interf_Client_Set_Icon_Size( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    if (! Userwin_Is_Iconic( uwinp ) )
        Manage_Client_Set_Icon_Size( uwinp, siz );
    else
        Interf_Client_Watch(
            Manage_Client_Set_Icon_Size( uwinp, siz ) )
}


void Interf_Client_Set_Icon_Position( uwinp, pt )
    Userwin *uwinp;
    TWPoint pt;
{
    if (! Userwin_Is_Iconic( uwinp ) )
        Manage_Client_Set_Icon_Position( uwinp, pt );
    else
        Interf_Client_Watch(
            Manage_Client_Set_Icon_Position( uwinp, pt ) )
}



void Interf_Client_Startup()
{
    Interf_Client_Watch(
        Manage_Startup_Finish() )
}


void Interf_Client_Set_Command( uwinp, str )
    Userwin *uwinp;
    char *str;
{
    if ( Userwin_Command_Effect( uwinp ) )
        Interf_Client_Watch(
            Manage_Set_Command( uwinp, str ) )
    else
        Manage_Set_Command( uwinp, str );
}


void Interf_Client_Configure( uwinp, flags, top_left, bodsiz, detail )
    Userwin *uwinp;
    unsigned long flags;
    TWPoint top_left;
    Size bodsiz;
    int detail;
{
    if ( Userwin_Is_Open( uwinp ) )
        Interf_Client_Watch(
            Manage_Client_Configure( uwinp, flags, top_left, bodsiz, detail )
        )
    else
        Manage_Client_Configure( uwinp, flags, top_left, bodsiz, detail );
}


void Interf_Client_Destroy( uwinp )
    Userwin *uwinp;
{
    if ( Userwin_Is_Open( uwinp ) || Userwin_Is_Iconic( uwinp ) )
        Interf_Client_Watch(
            Manage_Client_Destroy( uwinp ) )
    else
        Manage_Client_Destroy( uwinp );
}


void Interf_Client_Reset_Min_Max( uwinp, minsiz, maxsiz )
    Userwin *uwinp;
    Size minsiz, maxsiz;
{
    if ( Userwin_Is_Open( uwinp ) )
        Interf_Client_Watch(
            Manage_Client_Reset_Min_Max( uwinp, minsiz, maxsiz ) )
    else
        Manage_Client_Reset_Min_Max( uwinp, minsiz, maxsiz );
}


void Interf_Client_Set_Normal_Hints( uwinp, flags,
                            min_size, max_size, incr_size,
                            min_aspect, max_aspect, base_size )
    Userwin *uwinp;
    long flags;
    Size min_size, max_size, incr_size, base_size;
    TWPoint min_aspect, max_aspect;
{
    if ( Userwin_Is_Open( uwinp ) )
        Interf_Client_Watch(
            Manage_Client_Set_Normal_Hints( uwinp, flags,
                            min_size, max_size, incr_size,
                            min_aspect, max_aspect, base_size ) )
    else
        Manage_Client_Set_Normal_Hints( uwinp, flags,
                        min_size, max_size, incr_size,
                        min_aspect, max_aspect, base_size );
}


void Interf_Client_Set_Geometry_Hints( uwinp, flags,
                            top_left, size )
    Userwin *uwinp;
    long flags;
    TWPoint top_left;
    Size size;
{
    if ( Userwin_Is_Open( uwinp ) )
        Interf_Client_Watch(
            Manage_Client_Set_Geometry_Hints( uwinp, flags,
                            top_left, size ) )
    else
        Manage_Client_Set_Geometry_Hints( uwinp, flags,
                        top_left, size );
}



static void Interf_Menu_Redraw_All()
{
    Manage_Redraw_All();
    { Interf_Reenter_Region(); return; }
}

static void Interf_User_Open()
{
    if ( UserGlobals_Get_Option(AUTO_PLACE_ON_MENU_OPEN) &&
         ( UserGlobals_Get_Option(AUTO_PLACE_ON_UNSIZED_OPEN) || 
           Userwin_Sized( current_uwinp ) ) )
    {
        { Interf_Open(); return; }
    }
    else
    {
        if (! Interf_Start_Tracking(track_open_tilecursor))
            { Interf_Flash_Cancel(); return; }
        if ( Userwin_Is_Iconic(current_uwinp) )
            { Interf_Start_Icon_Opening(); return; }
        else
            { Interf_Start_Opening(); return; }
    }
}

static void Interf_Menu_Open( menu, item )
    TileMenu menu;
    TileMenuItem item;
{   
    current_uwinp = (Userwin *)TileMenu_Data(menu,item);
    if ( Userwin_Group_Closed( current_uwinp ) )
        { Interf_Start_Wait_For_Confirm(groupmsg,Interf_Confirmed_Group_Open); return; }
    else
        { Interf_User_Open(); return; }
}


static void Interf_Profile( menu, item )
    TileMenu menu;
    TileMenuItem item;
{
    bool follows;
    follows = UserGlobals_Get_Option(FOCUS_FOLLOWS_CURSOR);
    Interf_Watch(
        Manage_Profile( TileMenu_Data(menu,item) ) )
    if ( follows != UserGlobals_Get_Option(FOCUS_FOLLOWS_CURSOR) )
        (*swInMod)();
    { Interf_Reenter_Region(); return; }
}


static void Interf_Menu_Invoke( menu, item )
    TileMenu menu;
    TileMenuItem item;
{
    Tool_Invoke( (int)TileMenu_Data(menu,item) );
    { Interf_Reenter_Region(); return; }
}


static void Interf_Menu_Prorate()
{
    Interf_Watch(
        Manage_Prorate() )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Fill()
{
    Interf_Watch(
        Manage_Fill() )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Undo()
{
    Interf_Watch(
        Manage_Undo() )
    { Interf_Reenter_Region(); return; }
}


static void Interf_Menu_Repopulate_Auto()
{
    Interf_Watch(
        Manage_Repopulate_All( FALSE, TRUE ) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Repopulate_All()
{
    Interf_Watch(
        Manage_Repopulate_All( FALSE, FALSE ) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Repopulate_Last()
{
    Interf_Watch(
        Manage_Repopulate_Last() )
    { Interf_Reenter_Region(); return; }
}


static void Interf_Confirmed_Save_Layout()
{
    if (! Layout_Save() )
        Drawwin_Flash();
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Save_Layout()
{
    { Interf_Start_Wait_For_Confirm( savemsg, Interf_Confirmed_Save_Layout ); return; }
}

static void Interf_Confirmed_Finish_Layout()
{
    Interf_Watch(
        Manage_Finish_Layout() );
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Finish_Layout()
{
    { Interf_Start_Wait_For_Confirm( savemsg, Interf_Confirmed_Finish_Layout ); return; }
}

static void Interf_Menu_Generate_Layout( strp, procp )
    char **strp;
    VoidFunc *procp;
{
    if ( Layout_Done() )
    {
        *strp = "Save Layout";
        *procp = Interf_Menu_Save_Layout;
    }
    else
    {
        *strp = "Finish Layout";
        *procp = Interf_Menu_Finish_Layout;
    }
}


static void Interf_Menu_Notify_All()
{
    { Interf_Start_Wait_For_Confirm( notifymsg, Interf_Confirmed_Notify_All ); return; } }

static void Interf_Menu_Soft_Kill_All()
{
    { Interf_Start_Wait_For_Confirm( exitmsg, Interf_Confirmed_Soft_Kill_All ); return; } }

static void Interf_Menu_Exit()
{
    { Interf_Start_Wait_For_Confirm( exitmsg, Interf_Confirmed_Exit ); return; }
}

static void Interf_Menu_Pause()
{
    { Interf_Start_Wait_For_Confirm( exitmsg, Interf_Confirmed_Pause ); return; }
}



static void Interf_Menu_Redraw()
{
    Manage_Redraw(current_uwinp);
    { Interf_Reenter_Region(); return; }
}
    
static void Interf_Menu_Close()
{
    { Interf_Close(); return; }
}

static void Interf_Menu_Resize()
{
    { Interf_Start_Basing_Rsz(); return; }
}

static void Interf_Menu_Set_Size( menu, item )
    TileMenu menu;
    TileMenuItem item;
{   
    resize_proc = (BoolFunc)TileMenu_Data(menu,item);
    { Interf_Start_Basing_Set_Size(); return; }
}

static void Interf_Menu_Move()
{
    Interf_Reset_Menu_Pos();
    { Interf_Start_Moving(); return; }
}

static void Interf_Menu_Relocate()
{
    { Interf_Start_Relocating(); return; }
}

static void Interf_Menu_Exchange()
{
    { Interf_Start_Exchanging(); return; }
}

static void Interf_Menu_Enlarge()
{
    Interf_Watch(
        Manage_Enlarge(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Expand()
{
    Interf_Watch(
        Manage_Expand(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Desire()
{
    Interf_Watch(
        Manage_Desire(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Shrink()
{
    Interf_Watch(
        Manage_Shrink(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}


static void Interf_Menu_Zoom()
{
    Interf_Watch(
        Manage_Zoom(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Unzoom()
{
    Interf_Watch(
        Manage_Unzoom(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Generate_Zoom( strp, procp )
    char **strp;
    VoidFunc *procp;
{
    if ( Userwin_Is_Zoomed( current_uwinp ) )
    {
        *strp = "Unzoom";
        *procp = Interf_Menu_Unzoom;
    }
    else
    {
        *strp = "Zoom";
        *procp = Interf_Menu_Zoom;
    }
}


static void Interf_Menu_Generate_Title( strp, procp )
    char **strp;
    VoidFunc *procp;
{
    *strp = Userwin_Title( current_uwinp );
    *procp = Interf_Reenter_Region;
}


static bool Interf_Menu_Check_Locked_Open()
{    
    return ! Userwin_Allows_Close( current_uwinp );
}

static void Interf_Menu_Toggle_Locked_Open()
{    
    if ( Userwin_Allows_Close( current_uwinp ) ) 
        Userwin_Dont_Close(current_uwinp)
    else
        Userwin_Allow_Close(current_uwinp);
    { Interf_Reenter_Region(); return; }
}


static bool Interf_Menu_Check_Fixed_Width()
{    
    return ! Userwin_Allows_Change_Width( current_uwinp );
}

static void Interf_Menu_Toggle_Fixed_Width()
{    
    if ( Userwin_Allows_Change_Width( current_uwinp ) ) 
        Userwin_Dont_Change_Width(current_uwinp)
    else
        Userwin_Allow_Change_Width(current_uwinp);
    { Interf_Reenter_Region(); return; }
}


static bool Interf_Menu_Check_Fixed_Height()
{    
    return ! Userwin_Allows_Change_Height( current_uwinp );
}

static void Interf_Menu_Toggle_Fixed_Height()
{    
    if ( Userwin_Allows_Change_Height( current_uwinp ) ) 
        Userwin_Dont_Change_Height(current_uwinp)
    else
        Userwin_Allow_Change_Height(current_uwinp);
    { Interf_Reenter_Region(); return; }
}


static bool Interf_Menu_Check_Fixed_Edges()
{    
    return ! Userwin_Allows_Change( current_uwinp );
}

static void Interf_Menu_Toggle_Fixed_Edges()
{    
    if ( Userwin_Allows_Change( current_uwinp ) ) 
        Userwin_Dont_Change(current_uwinp)
    else
        Userwin_Allow_Change(current_uwinp);
    { Interf_Reenter_Region(); return; }
}


static bool Interf_Menu_Check_Tied_Listener()
{    
    return Userwin_Tied_Listener( current_uwinp );
}

static void Interf_Menu_Toggle_Tied_Listener()
{    
    Interf_Watch(
        Manage_Toggle_Zoom_Lock(current_uwinp) )
    { Interf_Reenter_Region(); return; }
}


static bool Interf_Menu_Check_Tied_Desire()
{    
    return Userwin_Tied_Desire( current_uwinp );
}

static void Interf_Menu_Toggle_Tied_Desire()
{    
    if ( Userwin_Tied_Desire( current_uwinp ) ) 
        Userwin_Dont_Tie_Desire(current_uwinp)
    else
        Userwin_Allow_Tie_Desire(current_uwinp);
    { Interf_Reenter_Region(); return; }
}



static void Interf_Menu_Group_Close()
{
    if ( Userwin_Group_Closed( current_uwinp ) )
    {
        Drawwin_Flash();
        { Interf_Reenter_Region(); return; }
    }
    else
        { Interf_Start_Wait_For_Confirm( groupmsg, Interf_Confirmed_Group_Close ); return; }
}

static void Interf_Menu_Notify()
{
    { Interf_Start_Wait_For_Confirm( notifymsg, Interf_Confirmed_Notify ); return; }
}

static void Interf_Menu_Soft_Kill()
{
    { Interf_Start_Wait_For_Confirm( softmsg, Interf_Confirmed_Soft_Kill ); return; }
}

static void Interf_Menu_Delete_Window()
{
    { Interf_Start_Wait_For_Confirm( softmsg, Interf_Confirmed_Delete_Window ); return; }
}

static void Interf_Menu_Hard_Kill()
{
    { Interf_Start_Wait_For_Confirm( hardmsg, Interf_Confirmed_Hard_Kill ); return; }
}



static void Interf_Menu_Icon_Redraw()
{
    Manage_Redraw(current_uwinp);
    { Interf_Reenter_Region(); return; }
}

static void Interf_Menu_Icon_Move()
{
    { Interf_Start_Icon_Moving(); return; }
}

static void Interf_Menu_Icon_Open()
{
    if ( Userwin_Group_Closed( current_uwinp ) )
        { Interf_Start_Wait_For_Confirm(groupmsg,Interf_Confirmed_Group_Open); return; }
    else
        { Interf_Start_Open_In_Icon(); return; }
}


static void Interf_Menu_Gen_Icon_Open( strp, procp )
    char **strp;
    VoidFunc *procp;
{
    *procp = Interf_Menu_Icon_Open;
    if ( Userwin_Group_Closed( current_uwinp ) )
        *strp = "Group Open";
    else
        *strp = "Open";
}


Interf_Init_Menus()
{
    TileMenuItem tool_item;

    manager_tool_menu = TileMenu_Create();

    manager_repop_menu = TileMenu_Create();

    TileMenu_Append_Call( manager_repop_menu,
         "Repopulate Auto", Interf_Menu_Repopulate_Auto, NULL );
    TileMenu_Append_Call( manager_repop_menu,
         "Repopulate All", Interf_Menu_Repopulate_All, NULL );
    TileMenu_Append_Call( manager_repop_menu,
         "Repopulate Last", Interf_Menu_Repopulate_Last, NULL );

    manager_background_menu = TileMenu_Create();
    TileMenu_Append_Call( manager_background_menu,
         "Redraw All", Interf_Menu_Redraw_All, NULL );
    Closed_Init( manager_background_menu, Interf_Menu_Open );
    tool_item = TileMenu_Append_Submenu( manager_background_menu,
         "Tools", manager_tool_menu );
    TileMenu_Append_Call( manager_background_menu,
         "Prorate", Interf_Menu_Prorate, NULL );
    TileMenu_Append_Call( manager_background_menu,
         "Fill", Interf_Menu_Fill, NULL );
    TileMenu_Append_Call( manager_background_menu,
         "Undo", Interf_Menu_Undo, NULL );
    TileMenu_Append_Submenu( manager_background_menu,
         "Repopulate", manager_repop_menu );
    Profile_Init( manager_background_menu, Interf_Profile );
    TileMenu_Append_Callback( manager_background_menu,
         Interf_Menu_Generate_Layout );
    TileMenu_Append_Call( manager_background_menu,
         "Notify All", Interf_Menu_Notify_All, NULL );
    TileMenu_Append_Call( manager_background_menu,
         "Soft Kill All", Interf_Menu_Soft_Kill_All, NULL );
    TileMenu_Append_Call( manager_background_menu,
         "Hard Exit", Interf_Menu_Exit, NULL );
    TileMenu_Append_Call( manager_background_menu,
         "Detach Manager", Interf_Menu_Pause, NULL );

    if (! Tool_Init( manager_tool_menu, Interf_Menu_Invoke ) )
        TileMenu_Inactivate_Entry( manager_background_menu, tool_item );

    manager_size_menu = TileMenu_Create();
    TileMenu_Append_Call( manager_size_menu,
        "Normal Min", Interf_Menu_Set_Size,
        (pointer)Manage_Set_Regular_Min_Size );
    TileMenu_Append_Call( manager_size_menu,
        "Normal Desired", Interf_Menu_Set_Size,
        (pointer)Manage_Set_Regular_Desired_Size );
    TileMenu_Append_Call( manager_size_menu,
        "Zoom Min", Interf_Menu_Set_Size,
        (pointer)Manage_Set_Zoom_Min_Size );
    TileMenu_Append_Call( manager_size_menu,
        "Zoom Desired", Interf_Menu_Set_Size,
        (pointer)Manage_Set_Zoom_Desired_Size );
    TileMenu_Append_Call( manager_size_menu,
        "Max", Interf_Menu_Set_Size,
        (pointer)Manage_Set_Max_Size );

    manager_window_option_menu = TileMenu_Create();
    TileMenu_Append_Checkback( manager_window_option_menu,
        "Locked Open", Interf_Menu_Check_Locked_Open,
                       Interf_Menu_Toggle_Locked_Open );
    TileMenu_Append_Checkback( manager_window_option_menu,
        "Fixed Width", Interf_Menu_Check_Fixed_Width,
                       Interf_Menu_Toggle_Fixed_Width );
    TileMenu_Append_Checkback( manager_window_option_menu,
        "Fixed Height", Interf_Menu_Check_Fixed_Height,
                        Interf_Menu_Toggle_Fixed_Height );
    TileMenu_Append_Checkback( manager_window_option_menu,
        "Fixed Edges", Interf_Menu_Check_Fixed_Edges,
                       Interf_Menu_Toggle_Fixed_Edges );
    TileMenu_Append_Checkback( manager_window_option_menu,
        "Listener Tied To Zoom", Interf_Menu_Check_Tied_Listener,
                                Interf_Menu_Toggle_Tied_Listener );
    TileMenu_Append_Checkback( manager_window_option_menu,
        "Zoom Tied To Desire", Interf_Menu_Check_Tied_Desire,
                               Interf_Menu_Toggle_Tied_Desire );

    manager_title_menu = TileMenu_Create();
    TileMenu_Append_Callback( manager_title_menu,
         Interf_Menu_Generate_Title );

    manager_window_menu = TileMenu_Create();
    TileMenu_Append_Submenu( manager_window_menu,
         "Title", manager_title_menu );
    TileMenu_Append_Call( manager_window_menu,
         "Redraw", Interf_Menu_Redraw, NULL );
    if ( UserGlobals_Get_Option(INCL_BGRND_MENU_IN_WINDOW_MENU) )
        TileMenu_Append_Submenu( manager_window_menu,
            "Manager", manager_background_menu );
    TileMenu_Append_Call( manager_window_menu,
         "Close", Interf_Menu_Close, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Group Close", Interf_Menu_Group_Close, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Resize", Interf_Menu_Resize, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Relocate", Interf_Menu_Relocate, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Move", Interf_Menu_Move, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Exchange", Interf_Menu_Exchange, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Expand", Interf_Menu_Expand, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Desire", Interf_Menu_Desire, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Shrink", Interf_Menu_Shrink, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Enlarge", Interf_Menu_Enlarge, NULL );
    TileMenu_Append_Callback( manager_window_menu,
         Interf_Menu_Generate_Zoom );
    TileMenu_Append_Submenu( manager_window_menu,
         "Set Size", manager_size_menu );
    TileMenu_Append_Submenu( manager_window_menu,
         "Options", manager_window_option_menu );
    TileMenu_Append_Call( manager_window_menu,
         "Notify", Interf_Menu_Notify, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Soft Kill", Interf_Menu_Soft_Kill, NULL );
    TileMenu_Append_Call( manager_window_menu,
         "Hard Kill", Interf_Menu_Hard_Kill, NULL );

    manager_icon_menu = TileMenu_Create();
    TileMenu_Append_Submenu( manager_icon_menu,
         "Title", manager_title_menu );
    TileMenu_Append_Call( manager_icon_menu,
         "Redraw", Interf_Menu_Icon_Redraw, NULL );
    if ( UserGlobals_Get_Option(INCL_BGRND_MENU_IN_WINDOW_MENU) )
        TileMenu_Append_Submenu( manager_icon_menu,
            "Manager", manager_background_menu );
    TileMenu_Append_Callback( manager_icon_menu,
         Interf_Menu_Gen_Icon_Open );
    TileMenu_Append_Call( manager_icon_menu,
         "Group Close", Interf_Menu_Group_Close, NULL );
    TileMenu_Append_Call( manager_icon_menu,
         "Move", Interf_Menu_Icon_Move, NULL );
    TileMenu_Append_Call( manager_icon_menu,
         "Exchange", Interf_Menu_Exchange, NULL );
    TileMenu_Append_Submenu( manager_icon_menu,
         "Options", manager_window_option_menu );
    TileMenu_Append_Call( manager_icon_menu,
         "Notify", Interf_Menu_Notify, NULL );
    TileMenu_Append_Call( manager_icon_menu,
         "Soft Kill", Interf_Menu_Soft_Kill, NULL );
    TileMenu_Append_Call( manager_icon_menu,
         "Hard Kill", Interf_Menu_Hard_Kill, NULL );
}


void Interf_Init()
{
    extern void Interf_Init_Buttons();
    extern void Open_Init();

    Open_Init();
    TileCursor_Init();
    Interf_Init_Buttons();
    Interf_Init_Menus();
    Interf_Click();
}


void Interf_Reset()
{
    Interf_Enter_Region();
    if ( UserGlobals_Get_Option(FOCUS_FOLLOWS_CURSOR) )
        Interf_Have_Lsnr();
    else
        Interf_Am_Clk_Lsnr();
}
