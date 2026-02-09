/*
static char sccs_id[] = "@(#)uwinD.h	5.6  9/1/88";
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

#define USERWIN_DEFINE
        
#ifndef USERWIN
#include "uwinP.h"
#endif

#ifndef TILWIN_DEFINE
#include "twinD.h"
#endif

#ifndef USERGLOBALS
#include "userglobD.h"
#endif

#include "twin.h"

/* ------------------------------------------------------------ */

#define GroupState -3
#define NeverState -2
#define NoState -1
#define DontCareState 0
#define NormalState 1
#define ClientIconState 2
#define IconicState 3
#define InactiveState 4
#define IgnoreState 5

#define Userwin_Allocate \
    ( allocate(Userwin,1) )

#define Userwin_Deallocate(uwinp) \
    free( uwinp )
    
#define Userwin_Get(winp) \
    ((Userwin *)(Tilwin_Get_Window_Id(winp)))

#define Userwin_Get_Window_Option(uwinp,opt) \
    ( (uwinp)->options[(int)(opt)] )
   
#define Userwin_Set_Window_Option(uwinp,opt,val) \
    ((uwinp)->options[(int)(opt)]) = (val)

#define Explicit_Window_Get(uwinp,opt) \
    ( (uwinp)->explicit[(int)(opt)] )

#define Explicit_Window_Set(uwinp,opt) \
    ((uwinp)->explicit[(int)(opt)]) = TRUE

#define Explicit_Window_Clear(uwinp,opt) \
    ((uwinp)->explicit[(int)(opt)]) = FALSE

/* ------------------------------------------------------------ */

extern Size abs_min_siz, abs_max_siz;

#define Userwin_Check_Min(uwinp) \
    ( (! UserGlobals_Get_Option( RESET_MIN_ON_DECREASE ) ) ? \
          Tilwin_Get_Min( (uwinp)->winp ) : \
      Userwin_Get_Window_Option( (uwinp), ENFORCE_CLIENT_MINIMUMS ) ? \
          (uwinp)->client_min : abs_min_siz )

#define Userwin_Check_Max(uwinp) \
    ( (! UserGlobals_Get_Option( RESET_MAX_ON_INCREASE ) ) ? \
          Tilwin_Get_Max( (uwinp)->winp ) : \
      Userwin_Get_Window_Option( (uwinp), ENFORCE_CLIENT_MAXIMUMS ) ? \
          (uwinp)->client_max : abs_max_siz )

#define Userwin_Check_Center_Open(uwinp,pos) \
    Tilwin_Check_Corner_Open((uwinp)->winp,pos)

#define Userwin_Check_Move(uwinp,posp,sizp) \
    Tilwin_Check_Center_Open((uwinp)->winp,posp,sizp)

#define Userwin_Check_Corner_Open(uwinp,sposp,cposp,side) \
    Tilwin_Check_Corner_Open( (uwinp)->winp, sposp, cposp, side, \
        Userwin_Check_Min(uwinp), Userwin_Check_Max(uwinp) )

#define Userwin_Check_Edge_Resize(uwinp,posp,side) \
    Tilwin_Check_Resize((uwinp)->winp,posp,side, \
        Userwin_Check_Min(uwinp), Userwin_Check_Max(uwinp) )

#define Userwin_Check_Corner_Resize(uwinp,posp,side) \
    Tilwin_Check_Resize((uwinp)->winp,posp,side, \
        Userwin_Check_Min(uwinp), Userwin_Check_Max(uwinp) )

/* ------------------------------------------------------------ */

#define Userwin_Get_Center(uwinp) \
    Tilwin_Get_Center((uwinp)->winp)

#define Userwin_Get_Size(uwinp) \
    Tilwin_Get_Size((uwinp)->winp)

#define Userwin_Get_Rectangle(uwinp) \
    Tilwin_Get_Rectangle((uwinp)->winp)

#define Userwin_Get_Previous_Rectangle(uwinp) \
    Tilwin_Get_Previous_Rectangle((uwinp)->winp)

#define Userwin_Is_Open(uwinp) \
    Tilwin_Is_Open((uwinp)->winp)

#define Userwin_Stayed_Still(uwinp) \
    ( (! Tilwin_Was_Just_Changed((uwinp)->winp)) || \
      (! Tilwin_Was_Actually_Modified((uwinp)->winp)) )

#define Userwin_Size_Changed(uwinp) \
    Tilwin_Size_Changed((uwinp)->winp)

/* ------------------------------------------------------------ */

#define Userwin_Is_Iconic(uwinp) \
    Tilwin_Is_Open( (uwinp)->iconp )

#define Userwin_Check_Icon_Move(uwinp,posp,sizp) \
    Tilwin_Check_Center_Open((uwinp)->iconp,posp,sizp)

#define Userwin_Get_Icon_Center(uwinp) \
    Tilwin_Get_Center((uwinp)->iconp)

#define Userwin_Icon_Stayed_Still(uwinp) \
    ( (! Tilwin_Was_Just_Changed((uwinp)->iconp)) || \
      (! Tilwin_Was_Actually_Modified((uwinp)->iconp)) )

/* ------------------------------------------------------------ */

#define Userwin_Enable_Input(uwinp) \
    ((uwinp)->input_enabled) = TRUE

#define Userwin_Disable_Input(uwinp) \
    ((uwinp)->input_enabled) = FALSE

#define Userwin_Input_Enabled(uwinp) \
    ( ((uwinp) != UWIN_NULL) && ((uwinp)->input_enabled))

#define Userwin_Is_Zoomed(uwinp) \
    ( (uwinp)->zoomed )

#define Userwin_State(uwinp) \
    ( (uwinp)->client_state )

#define Userwin_Wm_State(uwinp) \
    ( (uwinp)->wm_state)

#define Userwin_Startup_State(uwinp) \
    ( (uwinp)->startup_state)
#define Userwin_Group_Closed(uwinp) \
    ( (uwinp)->group_state != GroupState )

#define Userwin_Sized(uwinp) \
    ( (uwinp)->sized )

#define Userwin_Positioned(uwinp) \
    ( (uwinp)->positioned )

#define Userwin_Ever_Opened(uwinp) \
    ( (uwinp)->ever_opened )

#define Userwin_Laid_Out(uwinp) \
    ( (uwinp)->layout_found )

#define Userwin_Saving_State(uwinp) \
    ( (uwinp)->saving_state )

#define Userwin_Command_Effect(uwinp) \
    ( (uwinp)->soft_kill )

#define Userwin_Title(uwinp) \
    ( (uwinp)->title )

#define Userwin_Act_Created_Open(uwinp) \
    ( ( Userwin_Get_Window_Option( (uwinp), AUTO_OPEN_ON_CREATE ) ) || \
      ( UserGlobals_Get_Option(USE_ICONS) && \
        Userwin_Get_Window_Option( (uwinp), CLIENT_DRAWS_ICON ) ) )

#define Userwin_Creates_Draw_Iconic(uwinp) \
    ( (! Userwin_Get_Window_Option( (uwinp), AUTO_OPEN_ON_CREATE ) ) && \
      UserGlobals_Get_Option(USE_ICONS) && \
      Userwin_Get_Window_Option( (uwinp), CLIENT_DRAWS_ICON ) )

/* ------------------------------------------------------------ */

#define Userwin_Denies_Configure(uwinp) \
    ( ( ((uwinp)->messages) & (1L << 0) ) != 0 )

#define Userwin_Notes_Window_Moved(uwinp) \
    ( ( ((uwinp)->messages) & (1L << 1) ) != 0 )

#define Userwin_Bangs(uwinp) \
    ( ( ((uwinp)->messages) & (1L << 2) ) != 0 )

#define Userwin_Takes_Focus(uwinp) \
    ( ( (uwinp) != UWIN_NULL ) &&  \
      ( ( ((uwinp)->messages) & (1L << 3) ) != 0 ) )

#define Userwin_Deletes_Window(uwinp) \
    ( ( ((uwinp)->messages) & (1L << 4) ) != 0 )

#define Userwin_Notifies_Icon(uwinp) \
    ( ( ((uwinp)->messages) & (1L << 5) ) != 0 )

#define Userwin_Initially_Mapped(uwinp) \
    (uwinp)->initially_mapped

#define Userwin_Initially_Icon_Mapped(uwinp) \
    (uwinp)->initially_icon_mapped
