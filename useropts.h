/*
static char sccs_id[] = "@(#)useropts.h	5.6  9/1/88";
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

extern bool ACCEPT_NON_LISTENER_IN_BODY;
extern bool ACCEPT_NON_LISTENER_IN_BORDER;
extern bool ACCEPT_NON_LISTENER_IN_GADGET;
extern bool ACCEPT_NON_LISTENER_IN_HEADER;

extern bool ALLOW_AGGRESIVE_REPOPULATION;

extern bool ALLOW_ANY_SHRINK_ON_AUTO_REPOP;
extern bool ALLOW_ANY_SHRINK_ON_EXPL_REPOP;

extern bool ALLOW_AUTOMATIC_SHRINK_BY_CLIENT;
extern bool ALLOW_AUTOMATIC_CLOSE_BY_CLIENT;

extern bool ALLOW_LISTENER_TO_CLOSE;
extern bool ALLOW_LSNR_TO_CHANGE_BY_CLIENT;
extern bool ALLOW_LSNR_TO_CLOSE_BY_CLIENT;

extern bool AUTO_DESIRED_ENLARGE;

extern bool AUTO_PLACE_ON_ICON_OPEN;
extern bool AUTO_PLACE_ON_MENU_OPEN;
extern bool AUTO_PLACE_ON_UNSIZED_OPEN;

extern bool AUTO_PRORATE;
extern bool AUTO_PRORATE_LOCALLY;

extern bool AUTO_REPOPULATE_LAST;
extern bool AUTO_REPOPULATE_ON_AUTO_UNZOOM;
extern bool AUTO_REPOPULATE_ON_CLOSE;
extern bool AUTO_REPOP_ON_DESKTOP_RESIZE;
extern bool AUTO_REPOP_ON_EXPLICIT_UNZOOM;

extern bool ALLOW_SHRINK_ON_AUTO_OPEN;
extern bool ALLOW_SHRINK_ON_CENTER_OPEN;
extern bool ALLOW_SHRINK_ON_CORNER_OPEN;
extern bool ALLOW_SHRINK_ON_RESIZE;

extern bool BEST_FIT;

extern bool BUTTON_MAKES_LISTENER_IN_BODY;
extern bool BUTTON_MAKES_LISTENER_IN_HEADER;

extern bool CENTER_CURSOR_ON_MOVE;
extern bool CENTER_CURSOR_ON_RELOCATE;

extern bool CLEAR_BODY_ON_REDRAW;

extern bool CLOSE_IN_HEADER;
extern bool CLOSE_IN_CORNER_BORDER;
extern bool CLOSE_IN_SIDE_BORDER;
extern bool CLOSE_IN_MOVE_GADGET;
extern bool CLOSE_IN_ZOOM_GADGET;

extern bool DISTINGUISH_CORNER_BORDERS;
extern bool DISTNGSH_CORNER_BORDERS_BY_INV;

extern bool DRAW_INNER_BORDERS;
extern bool DRAW_OUTER_BORDERS;

extern bool DRAW_X_ON_MOVE;
extern bool DRAW_X_ON_OPEN;
extern bool DRAW_X_ON_RESIZE;

extern bool EXCHANGE_IN_HEADER;
extern bool EXCHANGE_IN_CORNER_BORDER;
extern bool EXCHANGE_IN_SIDE_BORDER;
extern bool EXCHANGE_IN_ZOOM_GADGET;

extern bool EXCHANGE_SIZES_IF_POSSIBLE;

extern bool FULL_SCREEN;

extern Side ICON_PLACEMENT;

extern bool INCL_BGRND_MENU_IN_WINDOW_MENU;

extern bool KEY_MAKES_LISTENER_IN_BODY;
extern bool KEY_MAKES_LISTENER_IN_BORDER;
extern bool KEY_MAKES_LISTENER_IN_GADGET;
extern bool KEY_MAKES_LISTENER_IN_HEADER;

extern bool FOCUS_FOLLOWS_CURSOR;

extern bool LOCAL_AUTO_PRORATE_BIASED;
extern bool LOCAL_EXPLICIT_PRORATE_BIASED;

extern bool MANAGER_MENU_IN_BODY;
extern bool MANAGER_MENU_IN_CORNER_BORDER;
extern bool MANAGER_MENU_IN_HEADER;
extern bool MANAGER_MENU_IN_ICON;
extern bool MANAGER_MENU_IN_SIDE_BORDER;

extern bool MIDDLE_MENU;

extern bool MOVE_CURSOR_ON_CLIENT_OPEN;
extern bool MOVE_CURSOR_ON_MANUAL_OPEN;
extern bool MOVE_CURSOR_TO_ICON_ON_CLOSE;

extern bool MOVE_IN_HEADER;
extern bool MOVE_IN_CORNER_BORDER;
extern bool MOVE_IN_SIDE_BORDER;
extern bool MOVE_IN_ZOOM_GADGET;

extern bool ONLY_REPOP_SINCE_ON_AUTO_UNZOOM;
extern bool ONLY_REPOPULATE_SINCE_ON_CLOSE;
extern bool ONLY_REPOP_SINCE_ON_EXPL_UNZOOM;

extern bool PLACE_CSR_IN_BODY_NOT_GADGET;

extern bool PLACE_CSR_GDGT_AFT_CL_AUTO_OPEN;
extern bool PLACE_CSR_GDGT_AFT_US_AUTO_OPEN;
extern bool PLACE_CSR_IN_GADGET_AFT_MAN_OPEN;

extern bool PLACE_CSR_IN_GADGET_AFT_EXCHANGE;
extern bool PLACE_CSR_IN_GADGET_AFT_MOVE;

extern bool PLACE_CSR_BACK_ON_CANCEL;

extern bool PREFER_CL_TO_SHR_ON_AUTO_OPEN;
extern bool PREFER_CL_TO_SHR_ON_CENTER_OPEN;
extern bool PREFER_CL_TO_SHR_ON_CORNER_OPEN;
extern bool PREFER_CL_TO_SHR_ON_RESIZE;

extern bool PREFER_PREV_POS_ON_AUTO_REPOP;
extern bool PREFER_PREV_POS_ON_EXPL_REPOP;

extern bool PF_CTR_NBR_2_CLOSE_ON_OPEN;
extern bool PF_CTR_NBR_2_SHRINK_ON_OPEN;
extern bool PF_CTR_NBR_2_ANY_SHR_ON_OPEN;
extern bool PF_EDGE_NBR_2_CLOSE_ON_OPEN;
extern bool PF_EDGE_NBR_2_SHRINK_ON_OPEN;
extern bool PF_EDGE_NBR_2_ANY_SHR_ON_OPEN;

extern bool PF_DTOP_2_CLOSE_ON_AUTO_OPEN;
extern bool PF_DTOP_2_SHRINK_ON_AUTO_OPEN;
extern bool PF_DTOP_2_ANY_SHR_ON_AUTO_OPEN;

extern bool PREF_SLD_TO_CLOSE_ON_RESIZE;
extern bool PREF_SLD_TO_SHRINK_ON_RESIZE;
extern bool PREF_SLD_TO_ANY_SHR_ON_RESIZE;
extern bool PF_CTR_NBR_2_CLOSE_ON_RESIZE;
extern bool PF_CTR_NBR_2_SHRINK_ON_RESIZE;
extern bool PF_CTR_NBR_2_ANY_SHR_ON_RESIZE;
extern bool PF_EDGE_NBR_2_CLOSE_ON_RESIZE;
extern bool PF_EDGE_NBR_2_SHRINK_ON_RESIZE;
extern bool PF_EDGE_NBR_2_ANY_SHR_ON_RESIZE;

extern bool PREFER_UNZOOM_TO_CLOSE;

extern bool PRORATE_LOCALLY;

extern bool REDRAW_IN_HEADER;
extern bool REDRAW_IN_CORNER_BORDER;
extern bool REDRAW_IN_SIDE_BORDER;
extern bool REDRAW_IN_MOVE_GADGET;
extern bool REDRAW_IN_ZOOM_GADGET;

extern bool RELOCATE_IN_HEADER;
extern bool RELOCATE_IN_CORNER_BORDER;
extern bool RELOCATE_IN_SIDE_BORDER;
extern bool RELOCATE_IN_ZOOM_GADGET;

extern bool REQUIRE_PREV_POS_ON_AUTO_REPOP;
extern bool REQUIRE_PREV_POS_ON_EXPL_REPOP;

extern bool RESET_MAX_ON_INCREASE;
extern bool RESET_MAX_ON_SHRINK;

extern bool RESET_MIN_ON_DECREASE;
extern bool RESET_MIN_ON_ENLARGE;
extern bool RESET_MIN_MAX_ON_UNSZD_MAN_OPEN;
extern bool RESET_TIED_ZOOMED_MIN_ON_ENLARGE;

extern bool RESIZE_IN_HEADER;
extern bool RESIZE_IN_CORNER_BORDER;
extern bool RESIZE_IN_SIDE_BORDER;
extern bool RESIZE_IN_MOVE_GADGET;
extern bool RESIZE_IN_ZOOM_GADGET;

extern bool SHOW_LISTENER_IN_BORDERS;
extern bool SHOW_LISTENER_IN_HEADER;
extern bool SHOW_FOCUS_IN_BORDERS;
extern bool SHOW_FOCUS_IN_HEADER;

extern bool TREAT_MOVE_LIKE_RELOCATE;

extern bool TRY_CTR_NBRHD_ON_OPEN;
extern bool TRY_EDGE_NEIGHBORHOOD_ON_OPEN;

extern bool TRY_SLIDING_ON_RESIZE;
extern bool TRY_CTR_NBRHD_ON_RESIZE;
extern bool TRY_EDGE_NEIGHBORHOOD_ON_RESIZE;

extern bool TRY_REPOP_AGAIN_AFT_AUTO_PRORATE;

extern bool UNZOOM_TIED_LSNR_IF_NECESSARY;

extern bool USE_CORNER_BORDERS;

extern bool USE_ICONS;
extern bool USE_RTL_ICON;

extern bool USER_MENU_IN_BODY;
extern bool USER_MENU_IN_HEADER;
extern bool USER_MENU_IN_SIDE_BORDER;
extern bool USER_MENU_IN_CORNER_BORDER;
extern bool USER_MENU_IN_ICON;

extern bool ZOOM_IN_HEADER;
extern bool ZOOM_IN_CORNER_BORDER;
extern bool ZOOM_IN_SIDE_BORDER;

extern bool ZOOM_ON_CREATE;

#define Userwin_Get_Global_Option(opt) \
    ( opt )

#define Userwin_Set_Global_Option(opt,val) \
    ( (opt) = (val) )
