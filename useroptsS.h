/*
static char sccs_id[] = "@(#)useroptsS.h	5.4  9/1/88";
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

char *(user_global_strs[(int)LENGTH_USER_GLOBAL_OPTIONS]) = {

    "acceptNonListenerInBody",
    "acceptNonListenerInBorder",
    "acceptNonListenerInGadget",
    "acceptNonListenerInHeader",

    "allowAggressiveRepopulation",

    "allowAutomaticShrinkOnAutoRepopulate",
    "allowAutomaticShrinkOnExplicitRepopulate",

    "allowAutomaticShrinkOnExchange",
    "allowAutomaticCloseOnExchange",

    "allowAutomaticShrinkByClient",
    "allowAutomaticCloseByClient",

    "allowListenerToClose",
    "allowListenerToChangeByClient",
    "allowListenerToCloseByClient",

    "allowShrinkOnAutoOpen",
    "allowShrinkOnCenterOpen",
    "allowShrinkOnCornerOpen",
    "allowShrinkOnResize",

    "autoDesiredEnlarge",

    "autoPlaceOnIconOpen",
    "autoPlaceOnMenuOpen",
    "autoPlaceOnUnsizedOpen",

    "autoProrate",
    "autoProrateLocally",

    "autoRepopulateLast",
    "autoRepopulateOnAutoUnzoom",
    "autoRepopulateOnClose",
    "autoRepopulateOnDesktopResize",
    "autoRepopulateOnExplicitUnzoom",

    "biasedAutoProrate",
    "biasedExplicitProrate",

    "buttonMakesListenerInBody",
    "buttonMakesListenerInHeader",

    "centerCursorOnMove",
    "centerCursorOnRelocate",

    "clearBodyOnRedraw",

    "closeInHeader",
    "closeInCornerBorder",
    "closeInSideBorder",
    "closeInMoveGadget",
    "closeInZoomGadget",

    "desireInHeader",
    "desireInCornerBorder",
    "desireInSideBorder",
    "desireInMoveGadget",
    "desireInZoomGadget",

    "distinguishCornerBorders",
    "distinguishCornerBordersByInverse",

    "drawXOnMove",
    "drawXOnOpen",
    "drawXOnResize",

    "enableAutoRepopulationDuringLayout",    
    "enableAutoSizingDuringLayout",    

    "enlargeInHeader",
    "enlargeInCornerBorder",
    "enlargeInSideBorder",
    "enlargeInMoveGadget",
    "enlargeInZoomGadget",

    "exchangeInHeader",
    "exchangeInIcon",
    "exchangeInCornerBorder",
    "exchangeInSideBorder",
    "exchangeInMoveGadget",
    "exchangeInZoomGadget",

    "fullScreen",

    "includeBackgroundMenuInWindowMenu",

    "keyMakesListenerInBody",
    "keyMakesListenerInBorder",
    "keyMakesListenerInGadget",
    "keyMakesListenerInHeader",

    "focusFollowsCursor",

    "managerMenuInBody",
    "managerMenuInCornerBorder",
    "managerMenuInHeader",
    "managerMenuInIcon",
    "managerMenuInSideBorder",
    "managerMenuInMoveGadget",
    "managerMenuInZoomGadget",

    "middleMenu",

    "moveCursorOnClientOpen",
    "moveCursorOnManualOpen",
    "moveCursorToIconOnClose",

    "moveInHeader",
    "moveInIcon",
    "moveInCornerBorder",
    "moveInSideBorder",
    "moveInMoveGadget",
    "moveInZoomGadget",

    "onlyRepopSinceOnAutoUnzoom",
    "onlyRepopulateSinceOnClose",
    "onlyRepopulateSinceOnExplicitUnzoom",

    "placeCursorInBodyInsteadOfBorder",
    "placeCursorInBodyInsteadOfGadget",

    "placeCursorInBorderAfterResize",

    "placeCursorInGadgetAfterClientAutoOpen",
    "placeCursorInGadgetAfterUserAutoOpen",
    "placeCursorInGadgetAfterManualOpen",

    "placeCursorInGadgetAfterExchange",
    "placeCursorInGadgetAfterMove",

    "placeCursorInIconAfterClose",

    "placeCursorBackAfterMenuOperation",
    "placeCursorBackOnCancel",

    "preferCloseToShrinkOnAutoOpen",
    "preferCloseToShrinkOnCenterOpen",
    "preferCloseToShrinkOnCornerOpen",
    "preferCloseToShrinkOnExchange",
    "preferCloseToShrinkOnResize",

    "preferExchangedLocationOnIconizing",
    "preferExchangedLocationOnOpening",

    "preferPreviousPositionOnAutoRepopulate",
    "preferPreviousPositionOnExplicitRepopulate",

    "preferCenterNeighborhoodToAutomaticCloseOnOpen",
    "preferCenterNeighborhoodToAutomaticShrinkOnOpen",
    "preferCenterNeighborhoodToShrinkOnOpen",
    "preferEdgeNeighborhoodToAutomaticCloseOnOpen",
    "preferEdgeNeighborhoodToAutomaticShrinkOnOpen",
    "preferEdgeNeighborhoodToShrinkOnOpen",

    "preferDesktopToAutomaticCloseOnAutoOpen",
    "preferDesktopToAutomaticShrinkOnAutoOpen",
    "preferDesktopToShrinkOnAutoOpen",

    "preferSlidingToAutomaticCloseOnResize",
    "preferSlidingToAutomaticShrinkOnResize",
    "preferSlidingToShrinkOnResize",
    "preferCenterNeighborhoodToAutomaticCloseOnResize",
    "preferCenterNeighborhoodToAutomaticShrinkOnResize",
    "preferCenterNeighborhoodToShrinkOnResize",
    "preferEdgeNeighborhoodToAutomaticCloseOnResize",
    "preferEdgeNeighborhoodToAutomaticShrinkOnResize",
    "preferEdgeNeighborhoodToShrinkOnResize",

    "preferUnzoomToClose",

    "prorateLocally",

    "redrawInHeader",
    "redrawInIcon",
    "redrawInCornerBorder",
    "redrawInSideBorder",
    "redrawInMoveGadget",
    "redrawInZoomGadget",

    "relocateInHeader",
    "relocateInCornerBorder",
    "relocateInSideBorder",
    "relocateInMoveGadget",
    "relocateInZoomGadget",

    "repopulateStrictly",
    "repopulateAutoClosedOnly",

    "requirePreviousPositionOnAutoRepopulate",
    "requirePreviousPositionOnExplicitRepopulate",

    "resetMaxOnIncrease",
    "resetMaxOnShrink",

    "resetMinOnDecrease",
    "resetMinOnEnlarge",
    "resetMinMaxOnUnsizedManualOpen",
    "resetTiedZoomedMinOnEnlarge",

    "resetZoomMin",
    "resetZoomMinAllowsDecrease",
    "resetZoomMinUsesDesire",

    "resizeInHeader",
    "resizeInCornerBorder",
    "resizeInSideBorder",
    "resizeInMoveGadget",
    "resizeInZoomGadget",

    "showListenerInBorders",
    "showListenerInHeader",
    "showFocusInBorders",
    "showFocusInHeader",

    "treatMoveLikeRelocate",

    "tryCenterNeighborhoodOnExchange",

    "tryCenterNeighborhoodOnOpen",
    "tryEdgeNeighborhoodOnOpen",

    "trySlidingOnResize",
    "tryCenterNeighborhoodOnResize",
    "tryEdgeNeighborhoodOnResize",

    "tryRepopulateAgainAfterAutoProrate",

    "unzoomTiedListenerIfNecessary",

    "useCornerBorders",

    "useIconArea",
    "useIcons",
    "useRtlIcon",

    "userMenuInBody",
    "userMenuInHeader",
    "userMenuInSideBorder",
    "userMenuInCornerBorder",
    "userMenuInIcon",
    "userMenuInMoveGadget",
    "userMenuInZoomGadget",

    "zoomInHeader",
    "zoomInCornerBorder",
    "zoomInSideBorder",
    "zoomInMoveGadget",
    "zoomInZoomGadget",

    "zoomOnCreate" };


