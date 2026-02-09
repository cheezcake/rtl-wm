/*
#ifndef lint
static char sccs_id[] = "@(#)rtlmenuD.h	5.6 9/1/88  Siemens Corporate Research and Support, Inc.";
#endif
*/

/*
  RTL Menu Package Version 1.2
  by Joe Camaratta and Mike Berman, Siemens RTL, Princeton NJ, 1988

  rtlmenuD.h: macro definitions for RTLMenus package
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

/* Menu data structure access macros */

#define TheMenu(menu) (*(Menu *)menu)
#define MenuWidth(menu) ((Menu *)menu)->menuWidth
#define MenuHeight(menu) ((Menu *)menu)->menuHeight
#define MenuOldWidth(menu) ((Menu *)menu)->menuOldWidth
#define MenuOldHeight(menu) ((Menu *)menu)->menuOldHeight
#define MenuItemWidth(menu) ((Menu *)menu)->menuItemWidth
#define MenuItemHeight(menu) ((Menu *)menu)->menuItemHeight
#define MenuFlags(menu) ((Menu *)menu)->menuFlags
#define MenuMaxTextWidth(menu) ((Menu *)menu)->menuMaxTextWidth
#define MenuBorderWidth(menu) ((Menu *)menu)->menuBorderWidth
#define MenuOldBorderWidth(menu) ((Menu *)menu)->menuOldBorderWidth
#define MenuItemPad(menu) ((Menu *)menu)->menuItemPad
#define MenuDisplay(menu) ((Menu *)menu)->display
#define MenuScreen(menu) ((Menu *)menu)->screen
#define MenuWindow(menu) ((Menu *)menu)->menuWindow
#define MenuCursor(menu) ((Menu *)menu)->menuCursor
#define MenuSavedPixmap(menu) ((Menu *)menu)->savedPixmap
#define MenuSavedImage(menu) ((Menu *)->savedImage
#define MenuSavedImageX(menu) ((Menu *)menu)->menuSavedImageX
#define MenuSavedImageY(menu) ((Menu *)menu)->menuSavedImageY
#define MenuItems(menu) ((RTLMenuItem)((Menu *)menu)->menuItems)
#define MenuItemsPtr(menu) ((RTLMenuItem *)&((Menu *)menu)->menuItems)
#define MenuFontInfo(menu) ((Menu *)menu)->menuFontInfo
#define MenuNormalGC(menu) ((Menu *)menu)->normalGC
#define MenuInvertGC(menu) ((Menu *)menu)->invertGC
#define MenuHighlightedGC(menu) ((Menu *)menu)->highlightedGC
#define MenuGreyGC(menu) ((Menu *)menu)->greyGC
#define MenuGreyPixmap(menu) ((Menu *)menu)->greyPixmap
#define MenuCheckmarkPixmap(menu) ((Menu *)menu)->checkmarkPixmap
#define MenuArrowPixmap(menu) ((Menu *)menu)->arrowPixmap
#define MenuInitialItemText(menu) ((Menu *)menu)->menuInitialItemText
#define MenuItemHighlighted(menu) ((RTLMenuItem)((Menu *)menu)->highlightedItem)
#define ResetMenuItemHighlighted(menu) (((Menu *)menu)->highlightedItem = (MenuItem *)NULL)
#define MenuNested(menu) ((Menu *)menu)->menuNested
#define MenuX(menu) ((Menu *)menu)->menuX
#define MenuY(menu) ((Menu *)menu)->menuY
#define MenuParent(menu) ((RTLMenu)((Menu *)menu)->parentMenu)
#define SetMenuParent(menu, parent) (((Menu *)menu)->parentMenu = (Menu *)parent)
#define MenuDelta(menu) ((Menu *)menu)->delta
#define MenuOptions(menu) ((Menu *)menu)->menuOptions
#define NULLMENU ((RTLMenu) NULL)

/* Menu predicates */
#define MenuIsNull(menu) (menu == NULLMENU)
#define MenuIsDisplayed(menu) (MenuFlags(menu) & menuMapped)
#define MenuHasInitialItem(menu) (MenuInitialItemText(menu) != (char *) NULL)

/* Menu modifiers */
#define SetHighlightItem(menu, item) ((Menu *)menu)->highlightedItem = (MenuItem *) item
#define ResetHighlightItem(menu)     ((Menu *)menu)->highlightedItem = (MenuItem *) NULL
#define SetMenuFlag(menu, flag)     MenuFlags(menu) |= flag
#define ResetMenuFlag(menu,flag)    MenuFlags(menu) &= ~flag
#define TestMenuFlag(menu,flag)     (MenuFlags(menu) & flag)
#define TestOptionFlag(menu,option) (MenuOptions(menu) & option)

/* Item data structure access macros */

#define TheItem(item) (*(MenuItem *)item)
#define ItemFlags(item) ((MenuItem *)item)->itemFlags
#define ItemText(item) ((MenuItem *)item)->itemText
#define ItemTextLength(item) ((MenuItem *)item)->itemTextLength
#define ItemTextWidth(item) ((MenuItem *)item)->itemTextWidth
#define ItemNext(item) ((RTLMenuItem)((MenuItem *)item)->nextItem)
#define ItemNextPtr(item) ((RTLMenuItem *)&((MenuItem *)item)->nextItem)
#define ItemSubmenu(item) ((RTLMenu)((MenuItem *)item)->itemSubmenu)
#define SetItemSubmenu(item, submenu)  (((MenuItem *)item)->itemSubmenu = (Menu *) submenu)
#define ItemTag(item) ((MenuItem *)item)->itemTag
#define ItemGenerator(item) ((MenuItem *)item)->generator
#define ItemCheckproc(item) ((MenuItem *)item)->checkproc
#define ItemCallback(item) ((MenuItem *)item)->itemCallback
#define ItemData(item) ((MenuItem *)item)->itemData
#define ItemWindow(item) ((MenuItem *)item)->itemWindow
#define ItemMenu(item) ((RTLMenu)((MenuItem *)item)->itemMenu)
#define SetItemMenu(item, menu) (((MenuItem *)item)->itemMenu = (Menu *)menu)
#define NULLITEM ((RTLMenuItem) NULL)
#define ItemGetArrowPosition(item) \
    (((MenuItem *)item)->itemMenu->menuWidth - arrow_width)

/* Item predicates */
#define ItemIsNull(item) ((item) == NULLITEM)
#define ItemIsInitialItem(menu, item) \
    (MenuInitialItemText(menu) && \
     (streql(MenuInitialItemText(menu), ItemText(item))))
#define ItemIsLeaf(item) ((ItemSubmenu(item) == NULLMENU)? TRUE : FALSE)
#define ItemIsDisabled(item) (ItemFlags(item) & itemDisabled)

/* Item modifiers */

#define	CheckItem(menu,item)	SetItemCheck(menu,item,1)
#define	DisableItem(menu,item)	SetItemDisable(menu,item,1)
#define	EnableItem(menu,item)	SetItemDisable(menu,item,0)
#define	UncheckItem(menu,item)	SetItemCheck(menu,item,0)
#define SetItemFlag(item, flag) ItemFlags(item) |= flag
#define ResetItemFlag(item,flag) ItemFlags(item) &= ~flag
#define TestItemFlag(item,flag) (ItemFlags(item) & flag)
#define MoveItemFlag(item,flag1,flag2) \
    if (TestItemFlag(item,flag1))\
        SetItemFlag(item,flag2);\
    else\
        ResetItemFlag(item,flag2);\
    ResetItemFlag(item,flag1);

/* Masks */

#define MenuEventMask \
    ((Mask)(LeaveWindowMask | EnterWindowMask | ButtonReleaseMask))
#define NormalItemEventMask MenuEventMask
#define SubmenuItemEventMask ((Mask) (MenuEventMask | PointerMotionMask))
#define MenuIgnoreMask ((Mask) 0)
#define MenuExposureMask ((Mask) ExposureMask)

/* Magic numbers */

#define	checkMarkWidth		9
#define	checkMarkHeight		8
#define	defaultCursorWidth     16
#define	defaultCursorHeight    16
#define	defaultCursorX		1
#define	defaultCursorY		1
#define	lineSeparatorHeight	9
#define ItemBorder              1
#define Default_Delta 20      /* # pixels pulled right to get submenu */
#define Menu_Table_Size 8
#define Item_Table_Size 32

