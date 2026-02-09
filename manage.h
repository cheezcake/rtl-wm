/*
static char sccs_id[] = "@(#)manage.h	5.7  9/1/88";
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



#ifndef BASETYPE
#include "basetype.h"
#endif

#ifndef USERWIN
#include "uwinP.h"
#endif

extern Userwin *focus;
extern Userwin *sublistener;
extern Userwin *listener;

#define Manage_Get_Focus() \
    ( focus )

#define Manage_Get_Sublistener() \
    ( sublistener )

#define Manage_Get_Listener() \
    ( listener )

extern void Manage_Init();
extern void Manage_Init_Rtl();

extern void Manage_Start();

extern void Manage_Finish();
    /* bool */

extern void Manage_Layout();

extern void Manage_Finish_Layout();

extern void Manage_Note_Output();
extern void Manage_Note_Input();

extern void Manage_Redraw();
    /* uwinp */

extern void Manage_Redraw_All();

extern void Manage_Start_Repaint();

extern void Manage_Repaint_Rect();
    /* rect */

extern void Manage_Finish_Repaint();

extern void Manage_Set_Desktop_Size();
    /* desksiz */

extern void Manage_Resize_Desktop();
    /* desksiz */

extern void Manage_Resize_Repaint();

extern Userwin *Manage_Create_Window();

extern void Manage_Eliminate_Window();

extern Userwin *Manage_Locate();
    /* pos */

extern void Manage_Zoom();
    /* uwinp */

extern void Manage_Unzoom();
    /* uwinp */

extern void Manage_Toggle_Zoom();
    /* uwinp */

extern void Manage_Toggle_Zoom_Lock();
    /* uwinp */

extern void Manage_Set_Focus();

extern void Manage_Unset_Focus();
extern void Manage_Switch_Focus();
    /* uwinp */

extern void Manage_Switch_Listener();
    /* uwinp */

extern void Manage_Set_Sublistener();
extern void Manage_Switch_Sublistener();
    /* uwinp */

extern void Manage_Unset_Sublistener();

extern void Manage_Close();
    /* uwinp */

extern void Manage_Undo();

extern void Manage_Repopulate_Last();

extern void Manage_Repopulate_All();

extern bool Manage_Move();
    /* uwinp, pos */

extern bool Manage_Icon_Move();
    /* uwinp, pos */

extern bool Manage_Exchange();
    /* uwinp, exch_uwinp */

extern bool Manage_Center_Open();
    /* uwinp, pos */

extern bool Manage_Corner_Open();
    /* uwinp, start_pos, pos, force, undesire */

extern bool Manage_User_Open_Automatically();
    /* uwinp */

extern bool Manage_Client_Open_Automatically();
    /* uwinp */

extern bool Manage_Auto_Open_Automatically();
    /* uwinp */

extern void Manage_Startup_Open();
extern void Manage_Startup_Finish();

extern void Manage_Determine_Startup_State();

extern void Manage_Client_Open();

extern void Manage_Initial_Geometry();
extern void Manage_Client_Configure();
    /* uwinp, rect */

extern void Manage_Client_Set_Normal_Hints();
extern void Manage_Client_Set_Geometry_Hints();

extern void Manage_Client_Reset_Min_Max();
    /* uwinp, min_size, max_size */

extern void Manage_Client_Close();
    /* uwinp */

extern void Manage_Destroy();

extern void Manage_Client_Destroy();
    /* uwinp */

extern bool Manage_Set_Regular_Min_Size();
    /* uwinp, pos, side, force, ctrl */

extern bool Manage_Set_Regular_Desired_Size();
    /* uwinp, pos, side, force, ctrl */

extern bool Manage_Set_Zoom_Min_Size();
    /* uwinp, pos, side, force, ctrl */

extern bool Manage_Set_Zoom_Desired_Size();
    /* uwinp, pos, side, force, ctrl */

extern bool Manage_Set_Max_Size();
    /* uwinp, pos, side, force, ctrl */

extern bool Manage_Resize();
    /* uwinp, pos, side, force, undesire */

extern void Manage_Set_Class();
    /* uwinp, res_class, res_name */

extern void Manage_Set_Name();
    /* uwinp, str */

extern void Manage_Set_Icon_Name();
    /* uwinp, str */

extern void Manage_Set_Hostname();
    /* uwinp, str */

extern void Manage_Set_Command();
    /* uwinp, str */

extern void Manage_Notify();
    /* uwinp */

extern void Manage_Delete_Window();
    /* uwinp */

extern void Manage_Soft_Kill();
    /* uwinp */

extern void Manage_Hard_Kill();
    /* uwinp */

extern void Manage_Notify_All();

extern void Manage_Soft_Kill_All();

extern void Manage_Exit();

extern void Manage_Contract();
    /* uwinp */

extern void Manage_Expand();
    /* uwinp */

extern void Manage_Desire();
    /* uwinp */

extern void Manage_Shrink();
    /* uwinp */

extern void Manage_Enlarge();
    /* uwinp */

extern void Manage_Profile();
    /* filnam */

extern void Manage_Prorate();

extern void Manage_Fill();

extern void Manage_Desire();
/* uwinp */

extern void Manage_Prepare_Open();

extern void Manage_Client_Open_Icon();
extern void Manage_Client_Close_Icon();

extern void Manage_Client_Set_State();

extern void Manage_Client_Change_State();

extern void Manage_Group_Open();
extern void Manage_Group_Close();
extern void Manage_Want_State();
extern void Manage_Client_Set_Group();
extern void Manage_Client_Set_Messages();

extern void Manage_Client_Set_Icon_Position();
extern void Manage_Client_Set_Icon_Size();

