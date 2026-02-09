/*
static char sccs_id[] = "@(#)defaults1.i	5.3  9/1/88";
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

static void Profile_Defaults()
{
    Tilwin_Set_Global_Option( ADJUST_PLACEMENT_FAIRLY, TRUE );
    Tilwin_Set_Global_Option( ALLOW_AUTOMATIC_CLOSE, TRUE );
    Tilwin_Set_Global_Option( ALLOW_AUTO_CLOSE_MORE_RECENT, TRUE );
    Tilwin_Set_Global_Option( ALLOW_AUTOMATIC_SHRINK, TRUE );
    Tilwin_Set_Global_Option( ALLOW_AUTO_SHRINK_MORE_RECENT, TRUE );
    Tilwin_Set_Global_Option( BEST_FIT_IS_TIGHT, FALSE );
    Tilwin_Set_Global_Option( BREAK_MINIMUMS_FAIRLY, TRUE );
    Tilwin_Set_Global_Option( ENABLE_GRAVITY, TRUE );
    Tilwin_Set_Global_Option( ENFORCE_MAXIMUMS, TRUE );
    Tilwin_Set_Global_Option( ENFORCE_MINIMUMS, TRUE );
    Tilwin_Set_Global_Option( FIRST_FIT, FALSE );
    Tilwin_Set_Global_Option( PREFER_CLOSE_TO_SHRINK, TRUE );
    Tilwin_Set_Global_Option( PREFER_AUTOMATIC_CLOSE_TO_SEARCH, FALSE );
    Tilwin_Set_Global_Option( PREFER_AUTO_SHRINK_TO_SEARCH, FALSE );
    Tilwin_Set_Global_Option( PREFER_SHRINK_TO_SEARCH, FALSE );
    Tilwin_Set_Global_Option( PRORATE_VERTICALLY_FIRST, TRUE );

    /* ------------------------------------------------------------ */

    Tilwin_Set_Default_Option( EXPENSIVE_TO_REDRAW, FALSE );
    Tilwin_Set_Default_Option( FIXED_COMPLETELY, FALSE );
    Tilwin_Set_Default_Option( FIXED_BOTTOM_EDGE, FALSE );
    Tilwin_Set_Default_Option( FIXED_TOP_EDGE, FALSE );
    Tilwin_Set_Default_Option( FIXED_LEFT_EDGE, FALSE );
    Tilwin_Set_Default_Option( FIXED_RIGHT_EDGE, FALSE );
    Tilwin_Set_Default_Option( FIXED_SIZE, FALSE );
    Tilwin_Set_Default_Option( FIXED_HEIGHT, FALSE );
    Tilwin_Set_Default_Option( FIXED_WIDTH, FALSE );
    Tilwin_Set_Default_Option( REQUIRE_MANUAL_CLOSE, FALSE );
    Tilwin_Set_Default_Option( SHRINK_BASED_ON_CURRENT_SIZE, FALSE );
    Tilwin_Set_Default_Option( WEIGHTED_SHRINK, FALSE );

    /* ------------------------------------------------------------ */
        /* Global Semantic Options */

    UserGlobals_Set_Option( ALLOW_AGGRESSIVE_REPOPULATION, TRUE );

    UserGlobals_Set_Option( 
        ALLOW_AUTO_SHRINK_ON_AUTO_REPOP, FALSE );
    UserGlobals_Set_Option( 
        ALLOW_AUTO_SHRINK_ON_EXPL_REPOP, TRUE );

    UserGlobals_Set_Option( ALLOW_AUTO_SHRINK_ON_EXCHANGE, TRUE );
    UserGlobals_Set_Option( ALLOW_AUTO_CLOSE_ON_EXCHANGE, FALSE );

    UserGlobals_Set_Option( ALLOW_AUTOMATIC_SHRINK_BY_CLIENT, TRUE );
    UserGlobals_Set_Option( ALLOW_AUTOMATIC_CLOSE_BY_CLIENT, TRUE );

    UserGlobals_Set_Option( ALLOW_LISTENER_TO_CLOSE, TRUE );
    UserGlobals_Set_Option( ALLOW_LSNR_TO_CHANGE_BY_CLIENT, FALSE );
    UserGlobals_Set_Option( ALLOW_LSNR_TO_CLOSE_BY_CLIENT, FALSE );

    UserGlobals_Set_Option( ALLOW_SHRINK_ON_AUTO_OPEN, TRUE );
    UserGlobals_Set_Option( ALLOW_SHRINK_ON_CENTER_OPEN, TRUE );
    UserGlobals_Set_Option( ALLOW_SHRINK_ON_CORNER_OPEN, FALSE );
    UserGlobals_Set_Option( ALLOW_SHRINK_ON_RESIZE, FALSE );

    UserGlobals_Set_Option( AUTO_DESIRED_ENLARGE, TRUE );

    UserGlobals_Set_Option( AUTO_PRORATE, FALSE );
    UserGlobals_Set_Option( AUTO_PRORATE_LOCALLY, TRUE );

    UserGlobals_Set_Option( AUTO_REPOPULATE_LAST, FALSE );
    UserGlobals_Set_Option( AUTO_REPOPULATE_ON_AUTO_UNZOOM, TRUE );
    UserGlobals_Set_Option( AUTO_REPOPULATE_ON_CLOSE, TRUE );
    UserGlobals_Set_Option( AUTO_REPOP_ON_DESKTOP_RESIZE, TRUE );
    UserGlobals_Set_Option( AUTO_REPOP_ON_EXPLICIT_UNZOOM, TRUE );

    UserGlobals_Set_Option( BIASED_AUTO_PRORATE, FALSE );
    UserGlobals_Set_Option( BIASED_EXPLICIT_PRORATE, FALSE );

    UserGlobals_Set_Option( ENABLE_AUTO_REPOP_DURING_LAYOUT, FALSE );
    UserGlobals_Set_Option( ENABLE_AUTO_SIZING_DURING_LAYOUT, FALSE );

    UserGlobals_Set_Option( FULL_SCREEN, FALSE );

    UserGlobals_Set_Option( ONLY_REPOP_SINCE_ON_AUTO_UNZOOM, TRUE );
    UserGlobals_Set_Option( ONLY_REPOPULATE_SINCE_ON_CLOSE, TRUE );
    UserGlobals_Set_Option(
        ONLY_REPOP_SINCE_ON_EXPL_UNZOOM, TRUE );

    UserGlobals_Set_Option( PREFER_CL_TO_SHR_ON_AUTO_OPEN, FALSE );
    UserGlobals_Set_Option( PREFER_CL_TO_SHR_ON_CENTER_OPEN, FALSE );
    UserGlobals_Set_Option( PREFER_CL_TO_SHR_ON_CORNER_OPEN, TRUE );
    UserGlobals_Set_Option( PREFER_CL_TO_SHR_ON_EXCHANGE, FALSE ); 
    UserGlobals_Set_Option( PREFER_CL_TO_SHR_ON_RESIZE, TRUE );

    UserGlobals_Set_Option( PREFER_EXC_LOC_ON_ICONIZING, TRUE );
    UserGlobals_Set_Option( PREFER_EXCHANGED_LOC_ON_OPENING, TRUE );

    UserGlobals_Set_Option(
        PREFER_PREV_POS_ON_AUTO_REPOP, TRUE );
    UserGlobals_Set_Option(
        PREFER_PREV_POS_ON_EXPL_REPOP, TRUE );

    UserGlobals_Set_Option( 
        PF_CTR_NBR_2_AUTO_CL_ON_OPEN, FALSE );  
    UserGlobals_Set_Option( 
        PF_CTR_NBR_2_AUTO_SHR_ON_OPEN, FALSE );
    UserGlobals_Set_Option( 
        PF_CTR_NBR_2_SHRINK_ON_OPEN, FALSE );
    UserGlobals_Set_Option( 
        PF_EDGE_NBR_2_AUTO_CL_ON_OPEN, FALSE );
    UserGlobals_Set_Option( 
        PF_EDGE_NBR_2_AUTO_SHR_ON_OPEN, FALSE );
    UserGlobals_Set_Option( 
        PF_EDGE_NBR_2_SHRINK_ON_OPEN, FALSE );

    UserGlobals_Set_Option( 
        PF_DTOP_2_AUTO_CL_ON_AUTO_OPEN, TRUE );
    UserGlobals_Set_Option( 
        PF_DTOP_2_AUTO_SHR_ON_AUTO_OPEN, TRUE );
    UserGlobals_Set_Option( 
        PF_DTOP_2_SHRINK_ON_AUTO_OPEN, TRUE );

    UserGlobals_Set_Option( 
        PREF_SLD_TO_AUTO_CL_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( 
        PREF_SLD_TO_AUTO_SHR_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( 
        PREF_SLD_TO_SHRINK_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( 
        PF_CTR_NBR_2_AUTO_CL_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( 
        PF_CTR_NBR_2_AUTO_SHR_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( 
        PF_CTR_NBR_2_SHRINK_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( 
        PF_EDGE_NBR_2_AUTO_CL_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( 
        PF_EDGE_NBR_2_AUTO_SHR_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( 
        PF_EDGE_NBR_2_SHRINK_ON_RESIZE, FALSE );

    UserGlobals_Set_Option( PREFER_UNZOOM_TO_CLOSE, TRUE );

    UserGlobals_Set_Option( PRORATE_LOCALLY, TRUE );

    UserGlobals_Set_Option( REPOPULATE_STRICTLY, FALSE );
    UserGlobals_Set_Option( REPOPULATE_AUTO_CLOSED_ONLY, TRUE );

    UserGlobals_Set_Option(
        REQUIRE_PREV_POS_ON_AUTO_REPOP, TRUE );
    UserGlobals_Set_Option(
        REQUIRE_PREV_POS_ON_EXPL_REPOP, FALSE );

    UserGlobals_Set_Option( RESET_MAX_ON_INCREASE, TRUE );
    UserGlobals_Set_Option( RESET_MAX_ON_SHRINK, FALSE );

    UserGlobals_Set_Option( RESET_MIN_ON_DECREASE, TRUE );
    UserGlobals_Set_Option( RESET_MIN_ON_ENLARGE, FALSE );
    UserGlobals_Set_Option( RESET_TIED_ZOOMED_MIN_ON_ENLARGE, FALSE );
    UserGlobals_Set_Option( RESET_MIN_MAX_ON_UNSZD_MAN_OPEN, TRUE );

    UserGlobals_Set_Option( RESET_ZOOM_MIN, FALSE );
    UserGlobals_Set_Option( RESET_ZOOM_MIN_ALLOWS_DECREASE, FALSE );
    UserGlobals_Set_Option( RESET_ZOOM_MIN_USES_DESIRE, TRUE );

    UserGlobals_Set_Option( TREAT_MOVE_LIKE_RELOCATE, FALSE );

    UserGlobals_Set_Option( TRY_CTR_NBRHD_ON_EXCHANGE, FALSE );

    UserGlobals_Set_Option( TRY_CTR_NBRHD_ON_OPEN, FALSE );
    UserGlobals_Set_Option( TRY_EDGE_NEIGHBORHOOD_ON_OPEN, FALSE );

    UserGlobals_Set_Option( TRY_SLIDING_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( TRY_CTR_NBRHD_ON_RESIZE, FALSE );
    UserGlobals_Set_Option( TRY_EDGE_NEIGHBORHOOD_ON_RESIZE, FALSE );

    UserGlobals_Set_Option( TRY_REPOP_AGAIN_AFT_AUTO_PRORATE, TRUE );

    UserGlobals_Set_Option( UNZOOM_TIED_LSNR_IF_NECESSARY, FALSE );

    UserGlobals_Set_Option( ZOOM_ON_CREATE, FALSE );

    /* ------------------------------------------------------------ */
        /* Global Interface Options */

    UserGlobals_Set_Option( ACCEPT_NON_LISTENER_IN_BODY, TRUE );
    UserGlobals_Set_Option( ACCEPT_NON_LISTENER_IN_BORDER, FALSE );
    UserGlobals_Set_Option( ACCEPT_NON_LISTENER_IN_GADGET, FALSE );
    UserGlobals_Set_Option( ACCEPT_NON_LISTENER_IN_HEADER, TRUE );

    UserGlobals_Set_Option( AUTO_PLACE_ON_ICON_OPEN, FALSE );
    UserGlobals_Set_Option( AUTO_PLACE_ON_MENU_OPEN, FALSE );
    UserGlobals_Set_Option( AUTO_PLACE_ON_UNSIZED_OPEN, TRUE );

    UserGlobals_Set_Option( BUTTON_MAKES_LISTENER_IN_BODY, TRUE );
    UserGlobals_Set_Option( BUTTON_MAKES_LISTENER_IN_HEADER, TRUE );

    UserGlobals_Set_Option( CENTER_CURSOR_ON_MOVE, TRUE );
    UserGlobals_Set_Option( CENTER_CURSOR_ON_RELOCATE, TRUE );

    UserGlobals_Set_Option( CLEAR_BODY_ON_REDRAW, TRUE );

    UserGlobals_Set_Option( CLOSE_IN_HEADER, FALSE );
    UserGlobals_Set_Option( CLOSE_IN_CORNER_BORDER, FALSE );
    UserGlobals_Set_Option( CLOSE_IN_SIDE_BORDER, FALSE );
    UserGlobals_Set_Option( CLOSE_IN_MOVE_GADGET, TRUE );
    UserGlobals_Set_Option( CLOSE_IN_ZOOM_GADGET, TRUE );

    UserGlobals_Set_Option( DESIRE_IN_HEADER, FALSE );
    UserGlobals_Set_Option( DESIRE_IN_CORNER_BORDER, FALSE );
    UserGlobals_Set_Option( DESIRE_IN_SIDE_BORDER, FALSE );
    UserGlobals_Set_Option( DESIRE_IN_MOVE_GADGET, FALSE );
    UserGlobals_Set_Option( DESIRE_IN_ZOOM_GADGET, TRUE );

    UserGlobals_Set_Option( DISTINGUISH_CORNER_BORDERS, TRUE );
    UserGlobals_Set_Option(
        DISTNGSH_CORNER_BORDERS_BY_INV, TRUE );

    UserGlobals_Set_Option( DRAW_X_ON_MOVE, TRUE );
    UserGlobals_Set_Option( DRAW_X_ON_OPEN, TRUE );
    UserGlobals_Set_Option( DRAW_X_ON_RESIZE, TRUE );

    UserGlobals_Set_Option( ENLARGE_IN_HEADER, FALSE );
    UserGlobals_Set_Option( ENLARGE_IN_CORNER_BORDER, FALSE );
    UserGlobals_Set_Option( ENLARGE_IN_SIDE_BORDER, FALSE );
    UserGlobals_Set_Option( ENLARGE_IN_MOVE_GADGET, FALSE );
    UserGlobals_Set_Option( ENLARGE_IN_ZOOM_GADGET, TRUE );

    UserGlobals_Set_Option( EXCHANGE_IN_HEADER, FALSE );
    UserGlobals_Set_Option( EXCHANGE_IN_ICON, TRUE );
    UserGlobals_Set_Option( EXCHANGE_IN_CORNER_BORDER, FALSE );
    UserGlobals_Set_Option( EXCHANGE_IN_SIDE_BORDER, FALSE );
    UserGlobals_Set_Option( EXCHANGE_IN_MOVE_GADGET, TRUE );
    UserGlobals_Set_Option( EXCHANGE_IN_ZOOM_GADGET, FALSE );

    UserGlobals_Set_Option(
        INCL_BGRND_MENU_IN_WINDOW_MENU, TRUE );

    UserGlobals_Set_Option( KEY_MAKES_LISTENER_IN_BODY, TRUE );
    UserGlobals_Set_Option( KEY_MAKES_LISTENER_IN_BORDER, FALSE );
    UserGlobals_Set_Option( KEY_MAKES_LISTENER_IN_GADGET, FALSE );
    UserGlobals_Set_Option( KEY_MAKES_LISTENER_IN_HEADER, FALSE );

    UserGlobals_Set_Option( FOCUS_FOLLOWS_CURSOR, TRUE );

    UserGlobals_Set_Option( MANAGER_MENU_IN_BODY, FALSE );
    UserGlobals_Set_Option( MANAGER_MENU_IN_HEADER, TRUE );
    UserGlobals_Set_Option( MANAGER_MENU_IN_ICON, TRUE );
    UserGlobals_Set_Option( MANAGER_MENU_IN_CORNER_BORDER, FALSE );
    UserGlobals_Set_Option( MANAGER_MENU_IN_SIDE_BORDER, FALSE );
    UserGlobals_Set_Option( MANAGER_MENU_IN_MOVE_GADGET, FALSE );
    UserGlobals_Set_Option( MANAGER_MENU_IN_ZOOM_GADGET, FALSE );

    UserGlobals_Set_Option( MIDDLE_MENU, FALSE );

    UserGlobals_Set_Option( MOVE_IN_HEADER, TRUE );
    UserGlobals_Set_Option( MOVE_IN_ICON, TRUE );
    UserGlobals_Set_Option( MOVE_IN_CORNER_BORDER, TRUE );
    UserGlobals_Set_Option( MOVE_IN_SIDE_BORDER, TRUE );
    UserGlobals_Set_Option( MOVE_IN_MOVE_GADGET, TRUE );
    UserGlobals_Set_Option( MOVE_IN_ZOOM_GADGET, FALSE );

    UserGlobals_Set_Option( PLACE_CSR_IN_BODY_NOT_BORDER, TRUE );
    UserGlobals_Set_Option( PLACE_CSR_IN_BODY_NOT_GADGET, TRUE );

    UserGlobals_Set_Option( 
        PLACE_CSR_IN_BORDER_AFTER_RESIZE, FALSE );

    UserGlobals_Set_Option( 
        PLACE_CSR_GDGT_AFT_CL_AUTO_OPEN, FALSE );
    UserGlobals_Set_Option(
        PLACE_CSR_GDGT_AFT_US_AUTO_OPEN, TRUE );
    UserGlobals_Set_Option(
        PLACE_CSR_IN_GADGET_AFT_MAN_OPEN, TRUE );

    UserGlobals_Set_Option(
        PLACE_CSR_IN_GADGET_AFT_EXCHANGE, TRUE );
    UserGlobals_Set_Option(
        PLACE_CSR_IN_GADGET_AFT_MOVE, TRUE );

    UserGlobals_Set_Option( PLACE_CSR_IN_ICON_AFTER_CLOSE, FALSE );

    UserGlobals_Set_Option( PLACE_CSR_BACK_AFTER_MENU_OP, TRUE );
    UserGlobals_Set_Option( PLACE_CSR_BACK_ON_CANCEL, TRUE );

    UserGlobals_Set_Option( REDRAW_IN_HEADER, TRUE );
    UserGlobals_Set_Option( REDRAW_IN_ICON, FALSE );
    UserGlobals_Set_Option( REDRAW_IN_CORNER_BORDER, TRUE );
    UserGlobals_Set_Option( REDRAW_IN_SIDE_BORDER, TRUE );
    UserGlobals_Set_Option( REDRAW_IN_MOVE_GADGET, FALSE );
    UserGlobals_Set_Option( REDRAW_IN_ZOOM_GADGET, FALSE );

    UserGlobals_Set_Option( RELOCATE_IN_HEADER, FALSE );
    UserGlobals_Set_Option( RELOCATE_IN_CORNER_BORDER, FALSE );
    UserGlobals_Set_Option( RELOCATE_IN_SIDE_BORDER, FALSE );
    UserGlobals_Set_Option( RELOCATE_IN_MOVE_GADGET, TRUE );
    UserGlobals_Set_Option( RELOCATE_IN_ZOOM_GADGET, FALSE );

    UserGlobals_Set_Option( RESIZE_IN_HEADER, FALSE );
    UserGlobals_Set_Option( RESIZE_IN_CORNER_BORDER, TRUE );
    UserGlobals_Set_Option( RESIZE_IN_SIDE_BORDER, TRUE );
    UserGlobals_Set_Option( RESIZE_IN_MOVE_GADGET, FALSE );
    UserGlobals_Set_Option( RESIZE_IN_ZOOM_GADGET, FALSE );

    UserGlobals_Set_Option( SHOW_LISTENER_IN_BORDERS, FALSE );
    UserGlobals_Set_Option( SHOW_LISTENER_IN_HEADER, TRUE );
    UserGlobals_Set_Option( SHOW_FOCUS_IN_BORDERS, TRUE );
    UserGlobals_Set_Option( SHOW_FOCUS_IN_HEADER, FALSE );

    UserGlobals_Set_Option( USE_CORNER_BORDERS, TRUE );

    UserGlobals_Set_Option( USE_ICON_AREA, FALSE );
    UserGlobals_Set_Option( USE_ICONS, TRUE );
    UserGlobals_Set_Option( USE_RTL_ICON, TRUE );

    UserGlobals_Set_Option( USER_MENU_IN_BODY, FALSE );
    UserGlobals_Set_Option( USER_MENU_IN_HEADER, FALSE );
    UserGlobals_Set_Option( USER_MENU_IN_SIDE_BORDER, FALSE );
    UserGlobals_Set_Option( USER_MENU_IN_CORNER_BORDER, FALSE );
    UserGlobals_Set_Option( USER_MENU_IN_ICON, FALSE );
    UserGlobals_Set_Option( USER_MENU_IN_MOVE_GADGET, FALSE );
    UserGlobals_Set_Option( USER_MENU_IN_ZOOM_GADGET, FALSE );

    UserGlobals_Set_Option( ZOOM_IN_HEADER, FALSE );
    UserGlobals_Set_Option( ZOOM_IN_CORNER_BORDER, FALSE );
    UserGlobals_Set_Option( ZOOM_IN_SIDE_BORDER, FALSE );
    UserGlobals_Set_Option( ZOOM_IN_MOVE_GADGET, FALSE );
    UserGlobals_Set_Option( ZOOM_IN_ZOOM_GADGET, TRUE );

    /* ------------------------------------------------------------ */

    Userwin_Set_Default_Option( ACCEPT_BUTTON_IN_BODY, TRUE );
    Userwin_Set_Default_Option( ACCEPT_BUTTON_IN_HEADER, TRUE );
    Userwin_Set_Default_Option( ACCEPT_BUTTON_IN_ICON, TRUE );

    Userwin_Set_Default_Option( ACCEPT_KEY_IN_BODY, TRUE );
    Userwin_Set_Default_Option( ACCEPT_KEY_IN_BORDER, TRUE );
    Userwin_Set_Default_Option( ACCEPT_KEY_IN_GADGET, TRUE );
    Userwin_Set_Default_Option( ACCEPT_KEY_IN_HEADER, TRUE );
    Userwin_Set_Default_Option( ACCEPT_KEY_IN_ICON, TRUE );

    Userwin_Set_Default_Option( AGGRESSIVELY_REPOPULATE, FALSE );

    Userwin_Set_Default_Option( ALLOW_SHRINK_ON_UNZOOM, TRUE );
    Userwin_Set_Default_Option( ALLOW_SHRINK_ON_AUTO_UNZOOM, TRUE );

    Userwin_Set_Default_Option( ALLOW_ZOOM_CLOSE, TRUE );

    Userwin_Set_Default_Option( AUTO_OPEN_ON_CREATE, TRUE );
    Userwin_Set_Default_Option( AUTO_OPEN_ON_WRITE, FALSE );

    Userwin_Set_Default_Option( AUTO_PLACE_ON_CLIENT_OPEN, TRUE );

    Userwin_Set_Default_Option( AUTO_RESATISFY_ON_RESET_MINMAX, TRUE );

    Userwin_Set_Default_Option( CLIENT_DRAWS_ICON, FALSE );
    Userwin_Set_Default_Option( CLIENT_PROVIDES_HEADER, FALSE );

    Userwin_Set_Default_Option( CONSIDER_FOR_REPOPULATION, TRUE );

    Userwin_Set_Default_Option( ENFORCE_CLIENT_MINIMUMS, TRUE );
    Userwin_Set_Default_Option( ENFORCE_CLIENT_MAXIMUMS, FALSE );

    Userwin_Set_Default_Option( LISTENER_TIED_TO_ZOOM, FALSE );

    Userwin_Set_Default_Option( FORCE_SHRINK_ON_UNZOOM, TRUE );
    Userwin_Set_Default_Option( FORCE_SHRINK_ON_AUTO_UNZOOM, FALSE );

    Userwin_Set_Default_Option( GLASS_CLIENT, FALSE );

    Userwin_Set_Default_Option( ICON_DRAWN_BY_CLIENT, FALSE );

    Userwin_Set_Default_Option( INCLUDE_RES_CLASS_IN_TITLE, TRUE ); 
    Userwin_Set_Default_Option( INCLUDE_RES_CLASS_IN_ICON_TITLE, TRUE ); 
    Userwin_Set_Default_Option( INCLUDE_RES_NAME_IN_TITLE, FALSE ); 
    Userwin_Set_Default_Option( INCLUDE_RES_NAME_IN_ICON_TITLE, FALSE ); 
    Userwin_Set_Default_Option( INCLUDE_NAME_IN_TITLE, TRUE ); 
    Userwin_Set_Default_Option( INCLUDE_NAME_IN_ICON_TITLE, TRUE ); 
    Userwin_Set_Default_Option( INCLUDE_HOST_IN_TITLE, TRUE );
    Userwin_Set_Default_Option( INCLUDE_HOST_IN_ICON_TITLE, TRUE );

    Userwin_Set_Default_Option( INCLUDE_TITLE_IN_HEADER, TRUE );
    Userwin_Set_Default_Option( INCLUDE_TITLE_IN_PIXMAP_ICON, FALSE );
    Userwin_Set_Default_Option( INCLUDE_TITLE_IN_CLIENT_ICON, FALSE );

    Userwin_Set_Default_Option( INVERT_ICON_WHEN_PENDING, TRUE );

    Userwin_Set_Default_Option( NOTE_LISTENER, TRUE );
    Userwin_Set_Default_Option( NOTE_LISTENER_INPUT, FALSE );
    Userwin_Set_Default_Option( NOTE_CLOSED_INPUT, FALSE );
    Userwin_Set_Default_Option( NOTE_CLOSED_OUTPUT, FALSE );
    Userwin_Set_Default_Option( NOTE_OPEN_INPUT, FALSE );
    Userwin_Set_Default_Option( NOTE_OPEN_OUTPUT, FALSE );

    Userwin_Set_Default_Option( PREFER_PREVIOUS_ICON_POSITION, TRUE );
    Userwin_Set_Default_Option( PREFER_PREV_POS, TRUE );
    Userwin_Set_Default_Option( REQUIRE_PREVIOUS_ICON_POSITION, FALSE );
    Userwin_Set_Default_Option( REQUIRE_PREV_POS, FALSE );

    Userwin_Set_Default_Option( SAVE_IN_LAYOUT, TRUE );

    Userwin_Set_Default_Option( SHOW_ICON, TRUE );

    Userwin_Set_Default_Option( USE_BORDERS, TRUE );
    Userwin_Set_Default_Option( USE_GADGETS, TRUE );
    Userwin_Set_Default_Option( USE_HEADER, TRUE );
    Userwin_Set_Default_Option( USE_MOVE_GADGET, TRUE );

    Userwin_Set_Default_Option( ZOOM_FULL_EXPLICIT, FALSE );
    Userwin_Set_Default_Option( ZOOM_FULL_HEIGHT, FALSE );
    Userwin_Set_Default_Option( ZOOM_FULL_WIDTH, FALSE );

    Userwin_Set_Default_Option( ZOOM_ON_OPEN, FALSE );

    /* ------------------------------------------------------------ */

    UserGlobals_Set_Value( ICON_PLACEMENT, (int)Icon_Top );
    UserGlobals_Set_Value( 
        SECONDARY_ICON_PLACEMENT, (int)Icon_Left );

    UserGlobals_Set_Value( NEIGHBORHOOD_SHRINK_FACTOR, 50 );

    UserGlobals_Set_Value( GRAVITY, 12 );

    UserGlobals_Set_Value( RTL_LEFT_X, 0 );
    UserGlobals_Set_Value( RTL_TOP_Y, 0 );

    UserGlobals_Set_Value( RTL_WIDTH, 540 );
    UserGlobals_Set_Value( RTL_HEIGHT, 600 );

    UserGlobals_Set_Value( FULL_WIDTH, 1150 );
    UserGlobals_Set_Value( FULL_HEIGHT, 894 );

    UserGlobals_Set_Value( BORDER_SIZE, 5 );
    UserGlobals_Set_Value( OUTER_BORDER_LINEWIDTH, 2 );
    UserGlobals_Set_Value( INNER_BORDER_LINEWIDTH, 1 );

    UserGlobals_Set_Value( GADGET_WIDTH, 12 );

    /* ------------------------------------------------------------ */

    Userwin_Set_Default_Value( HEADER_HEIGHT, 16 );

    Userwin_Set_Default_Value( ICON_WIDTH, 64 );
    Userwin_Set_Default_Value( ICON_HEIGHT, 64 );

    Userwin_Set_Default_Value( ICON_BODY_TOP, 2 );
    Userwin_Set_Default_Value( ICON_BODY_BOTTOM, 61 );
    Userwin_Set_Default_Value( ICON_BODY_LEFT, 2 );
    Userwin_Set_Default_Value( ICON_BODY_RIGHT, 61 );

    Userwin_Set_Default_Value( ICON_RES_TOP, 2 );
    Userwin_Set_Default_Value( ICON_RES_BOTTOM, 10 );
    Userwin_Set_Default_Value( ICON_RES_LEFT, 2 );
    Userwin_Set_Default_Value( ICON_RES_RIGHT, 61 );

    Userwin_Set_Default_Value( ICON_HOST_TOP, 12 );
    Userwin_Set_Default_Value( ICON_HOST_BOTTOM, 20 );
    Userwin_Set_Default_Value( ICON_HOST_LEFT, 2 );
    Userwin_Set_Default_Value( ICON_HOST_RIGHT, 61 );

    Userwin_Set_Default_Value( ICON_NAME_TOP, 22 );
    Userwin_Set_Default_Value( ICON_NAME_BOTTOM, 61 );
    Userwin_Set_Default_Value( ICON_NAME_LEFT, 2 );
    Userwin_Set_Default_Value( ICON_NAME_RIGHT, 61 );
}

