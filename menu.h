/*
#ifndef lint
static char sccs_id[] = "@(#)menu.h	5.5 9/1/88  Siemens Corporate Research and Support, Inc.";
#endif
*/

/* 
  RTL Menu Package Version 1.0
  by Joe Camaratta and Mike Berman, Siemens RTL, Princeton NJ, 1987

  menu.h: external function declarations for menu package
*/

extern MenuItem *AddMenuItem();
extern bool     DisposeItem();
extern void     DisposeMenu();
extern void     InitMenu();
extern bool     SetItemText();
extern Menu     *NewMenu();
extern bool     SetItemCheck();
extern bool     SetItemDisable();
extern MenuItem *Display_Menu();
extern void     Undisplay_Menu();
extern void     MenuInvert();
extern void     PlacePointer();
extern void     Draw_Menu();
extern void     Draw_Item();

extern MenuItem *MenuGetItem();
extern MenuItem *MenuItemByName();
extern MenuItem *MenuItemByData();
extern Menu     *MenuGetMenu();
extern int      ItemGetMiddleY();
extern void     SetInitialItem();
extern void     ClearInitialItem();
extern MenuItem *GetInitialItem();

extern MenuItem *TrackMenu();










