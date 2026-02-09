/*
#ifndef lint
static char sccs_id[] = "@(#)rtlmenu.h	5.5 9/1/88  Siemens Corporate Research and Support, Inc.";
#endif
*/

/* 
  RTL Menu Package Version 1.2
  by Joe Camaratta and Mike Berman, Siemens RTL, Princeton NJ, 1988

  rtlmenu.h: external definitions for rtlmenu user
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

extern void RTLMenu_Initialize(/* Display *, int, RTLMenuOptionsMask */ );
extern void RTLMenu_Destroy(/* */);
extern void RTLMenu_Replace_Data_By_String(/* RTLMenu, generic, char * */);
extern void RTLMenu_Activate_Entry(/* RTLMenu, RTLMenuItem */);
extern void RTLMenu_Inactivate_Entry(/* RTLMenu, RTLMenuItem */);
extern void RTLMenu_Delete_Entries(/* RTLMenu */);
extern void RTLMenu_Delete_String(/* RTLMenu, char * */);
extern void RTLMenu_Delete_Data(/* RTLMenu, generic */);
extern void RTLMenu_Enter(/* RTLMenu, int, Time, Window, RTLPoint */);
extern void RTLMenu_Generate_Items(/* RTLMenu, VoidFunc */);
extern void RTLMenu_Set_String(/* RTLMenu, RTLMenuItem, char * */);
extern void RTLMenu_Set_Generator(/* RTLMenuItem, VoidFunc */);
extern void RTLMenu_Set_Callback(/* RTLMenuItem, VoidFunc */);
extern void RTLMenu_Set_Submenu(/* RTLMenuItem, VoidFunc, RTLMenu */);
extern void RTLMenu_Set_Data(/* RTLMenuItem, generic */);   
extern bool RTLMenu_Has_Data(/* RTLMenu, generic */);
extern RTLMenu RTLMenu_Create(/* */);
extern RTLMenu RTLMenu_Get_Submenu(/* RTLMenu, char * */);
extern generic RTLMenu_Data(/* RTLMenu, RTLMenuItem */);
extern RTLPoint RTLMenu_Entry_Pos(/* */); 
extern RTLMenuItem RTLMenu_Append_Item(/* RTLMenu */);

/* Old append calls --- for compatibility (and convenience) */

extern RTLMenuItem RTLMenu_Append_String(/* RTLMenu, char *, generic */);
extern RTLMenuItem RTLMenu_Append_Call(/* RTLMenu, char *, VoidFunc,
					  generic */);
extern RTLMenuItem RTLMenu_Append_Checkback(/* RTLMenu, char *, BoolFunc,
					       VoidFunc, generic */);
extern RTLMenuItem RTLMenu_Append_Submenu(/* RTLMenu, char *, RTLMenu */);
extern RTLMenuItem RTLMenu_Append_Callback(/* RTLMenu, VoidFunc */);



    
