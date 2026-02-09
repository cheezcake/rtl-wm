@device(imagen300)
@style(Spacing .91, Spread .57, Indent 0)
@make(article)

@PageHeading()
@PageFooting(Center="@Value(Page)")
@Set(Page = 1)

@Modify(hd2, below 1 line, need 8, underline all, font titlefont4)
@Modify(hd3, below 1 line, need 6, underline all, font titlefont2)

@Modify(Heading, above 1.5 lines, below 1.5 lines, need 4)
@Modify(MajorHeading, above 1.5 lines, below 1.5 lines, need 4)
@Modify(SubHeading, need 5, font bodyfont, facecode c, 
        underline, centered)
@Define(HeadingAddress = Heading, Above 0, Below 0, Font SmallBodyFont)

@Define(b2 = b, Need 2 lines)
@Define(bx = b, Need 3 lines)

@modify(Verbatim, above 1 line, below 1 line, Spacing .91, Spread .57)
@modify(Format, above 1 line, below 1 line, Spacing .91, Spread .57)
@modify(Example, above 1 line, below 1 line, Spacing .91, Spread .57)
@modify(ProgramExample, above 1 line, below 1 line, Spacing .91, Spread .57)
@Modify(Quotation, above 1 line, below 1 line, Spacing .91, Spread .57)
@Modify(Itemize, above 1 line, below 1 line, Spacing .91, Spread .57)
@Modify(Enumerate, above 1 line, below 1 line, Spacing .91, Spread .57)

@Define(Abstract = Quotation, Indent 0, FaceCode i, Spacing .8,
        Above 3, Below 3)

@begin(majorheading)
Manual for the
Siemens RTL
Tiled Window Manager

Release 5.1
for use with X11R3
@end(majorheading)

@begin(heading)
Ellis S. Cohen
@begin(HeadingAddress)
Siemens Research & Technology Laboratories
105 College Road East
Princeton NJ 08540-6668
(609) 734-6524

Comments or Questions to
rtl@@cadillac.siemens.com (internet)
princeton!siemens!cadillac!rtl (uucp)
@end(HeadingAddress)

1 September 1988
@end(heading)

@begin(quotation)
Copyright 1988 by Siemens Research and Technology Laboratories, Princeton, NJ

Permission to use, copy, modify, and distribute this documentation and
the software described for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Siemens Research and Technology
Laboratories not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior permission.

SIEMENS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
SIEMENS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
@end(quotation)

@newpage()

@begin(Abstract)
This manual provides a detailed description of Release 5.1 of the Siemens
RTL Tiled Window Manager, a window manager for X11@foot<X11 and the X Window
System are trademarks of MIT> clients.

@b(A separate document, "Tutorial: Initial Setup for Using the
Siemens RTL Tiled Window Manager", should be read first by novice users
of the system.)
@end(Abstract)

Except for menus and transient pop-up windows,
a tiled window manager does not permit windows to overlap.

When an attempt is made to open, move, or resize a window, other windows
may be occupying the space needed.  This space conflict is resolved by
@begin(itemize, group, spread 0)
Shrinking, closing, or moving the windows in the way, or

Opening, moving, or resizing the window at a different size or position
than specified, or

Refusing to perform the operation.
@end(itemize)

Such @b(side effects) are a major feature distinguishing our tiled window
manager from existing overlapping window managers.

The Siemens RTL Tiled Window Manager supports an arbitrary layout of
tiled windows.
Windows may be placed anywhere; they do not necessarily line up in
columns.

The window manager does @i(not) attempt to fill the screen.
Windows have a desired size, and are not made larger than this unless
requested by the user.
Consequently, there may be blank space on the screen.

While overlapping windows are more familiar, the Siemens RTL Tiled Window
Manager has some important benefits:

@begin(Itemize)
It keeps the desktop well organized -- the desktop does not look messy.

Windows are always easy to find.  Windows cannot get lost underneath
other windows, and window headers are not obscured by other windows.

Important information is never obscured by other windows.  Obscured
windows are shrunk instead, and the application gets a chance to
reformat information to make use of the available space.

Screen space is not wasted by partially visible slivers that contain
useless information.  Windows can have their minimum size set to ensure
that all essential information can be presented.  If there
is no room on the screen for the window to be fully visible at its
minimum size, the window is automatically iconized.

Users do not have to manually move or shrink adjacent windows to keep
them fully visible when they enlarge or open a window -- the window
manager reorganizes screen space automatically.
@end(Itemize)

This release of the Siemens RTL Tiled Window Manager has the following
features:

@begin(itemize)
Automatic strategies are provided for window placement and sizing.  The
degree of automation is controlled by a variety of options.

Windows are decorated with titlebars,borders and gadgets.  The size and
presence of these decorations can be individually controlled.

Supports the X11R2 version of the conventions for Client / Window Manager
communications.

The user can save and restore window layouts.  That is, RTL is a session
manager as well as a window manager.

Both click-to-type and real-estate-driven focus models are available.

The user can specify a separate icon area and control icon layout within
it.

The wm will optionally write application-specific information over
specified regions of pixmap icons.

The user can override the client's pixmap icon.  A variety of snazzy
icons are provided for the usual applications.
    
Users can perform group-iconification -- display a single icon for a
group of top-level windows (for clients that define window groups).
    
Support is provided for both 3-button and 1-button mice.

Using preference files, users can organize applications in a class
hierarchy, for purposes of inheriting option settings.
@end(itemize)

This is the first tiled window manager developed that supports arbitrary
layouts, and is as much a research vehicle as a production-quality window
manager.  Consequently, there are an extremely large number of options
that may be set by the user (although naive users can use the default
option settings, or one of the preference files distributed with the
system).  We are particularly interested in users' experiences with
various option settings.

The manual is organized as follows:

@begin(enumerate)
@b(Windows and Icons): This describes how the window manager decorates
client windows with a header, borders and gadgets, and how they are used.
It also describes the contents, use, and placement of icons.

@b(Window Sizes and Positions): Describes minimum, maximum, and desired
sizes for both normal and zoomed windows, and desired positions.

@b(The Pointer Interface): Describes pointer related aspects of
the user interface, including the difference between the focus and the
listener window.

@b(Manager Menu): Describes the global operations that can be performed 
from the window manager menu.

@b(Window Menu): Describes the operations that can be performed on an
individual window.

@b(Icon Menu): Describes the operations that can be performed on an icon.

@b(Customization and Startup): Explains how to customize the window
manager via various files specifying tools, preference files
(which set options globally or on a per window-class basis), and startup
and layout files.  Indicates how these are used on startup.

@b(Automatic Strategies): How the window manager automatically adjusts
the size and position of windows to keep the desktop tiled and balance
competing demands for screen space.

@b(Standard X11 Properties): How standard X11 properties are used by the
window manager.

@b(Client Placement): Actions that a client can take which affect the
placement of windows.

@b(Options): Describes the options and their default values.
@end(enumerate)

Both a tutorial manual, and a separate "@b(Quick Reference Page)" are
available as part of the distribution.

In addition, an 18 minute videotaped demonstration of the system
(previously shown as part of the video program at both CHI+GI '87
in Toronto and Interact '87 in Stuttgart) is available for loan
by writing to 

@begin(Verbatim)
    Software Technology Department
    Siemens RTL
    105 College Rd East,
    Princeton NJ, 08540.
@end(Verbatim)

@section(Windows and Icons)

@subsection(Windows)

Windows created by an X11 client are reparented within a larger window
owned by the window manager.  In addition to the client's window,
the larger window is @i(decorated) by the window manager with
a border, a header, and two "gadgets".

The border is used primarily for resizing -- the sides for
one-dimensional resizing, and the corners for two-dimensional resizing.
A window's border is shown in reverse image when that window is the
@b(focus) -- that is, when a key press would be transmitted to the
client which owns the window.  The border is also used for initiating
constrained window moves.

The border described is provided by the window manager, not the one that
X11 supports as part of the basic window structure.  In fact the window
manager hides the client's border while it is running.

The header can display the window class, the window name, and/or
the client machine on which the application is running.
It is also used for popping up a menu of window operations.
A window's header is shown in reverse image when that window is the
@b(listener) -- that is, when it is the last window which has received input.

To the left of the header is the @b(zoom gadget) -- it is used for
"zooming" and "unzooming" windows, and for enlarging a window
to its desired or maximum size.  When a window is unzoomed, the
gadget displays a "closed box", and when it is zoomed, it displays an
"open box".

It is possible to tie listener to zoom -- that is, whenever a window becomes
the listener, it is automatically zoomed, and when it is no longer the
listener, it is automatically unzoomed.  Windows so tied have a
horizontal line through their zoom gadget.

To the right of the header is the @b(move gadget) -- it is used for
moving, relocating, and exchanging windows.

Various options are available for setting the sizes of decorations, and
for determining, on a per-window basis, whether they should used.

@subsection(Icons)

When a window is closed, the window title is placed in a submenu
of the window manager menu, and an icon for the window may
optionally be displayed.

Through the @c(WM_HINTS) standard property, X11 allows the client to
provide an icon pixmap which will be displayed when the window is
iconized.  Through preference files, the user can specify an icon pixmap,
and this will override the one provided by the client.

If an icon pixmap is not provided, a default icon
is created by the window manager containing the window class,
the icon name (or window name if no icon name is provided), and/or
the client machine.

Preferences can designate the area of the screen to be used
for icons and can specify the layout of the icons within that area.

X11 allows clients to indicate a client icon window in the @c(WM_HINTS) 
structure -- that is, a window into which the client can draw, which acts
as an icon.  Client icon windows are not supported in release 5.1.
However, if a client attempts to map a client icon, a default icon, or
one containing an icon pixmap (if provided) is used instead.

Icons provide a limited input channel to the client.  Key presses when
the icon window is the focus may optionally be routed to the client.  In
addition, mouse button combinations that are not interpreted by the
window manager may also be routed to the the client, and may be used by
clients that wish to put up special icon menus or take other actions.

A special icon, the Siemens RTL icon, may be included on the screen.
Through it, the main window manager menu may be popped up (though it may
also be popped up from the background or as a submenu of each window
menu).

@section(Window Sizes and Positions)

Windows have a @b(user minimum) size and a @b(user maximum)
size which may be set by the user.  A window will be closed if less than
the minimum space is available for the window, and those operations which
enlarge a window (Enlarge, Expand, and Fill) will never enlarge a window
above its maximum size.

Windows also have a @b(client minimum) and a @b(client
maximum) size -- set by a client using the X11 standard
property @c(WM_NORMAL_HINTS).
The client minimum and maximum are optionally enforced.  If they are
enforced, the user minimum may not be set smaller than the client
minimum, and the user maximum may not be set larger than the client
maximum.

Windows have a a @b(desired size).  Whenever a window is
explicitly resized (by either the user or the client), its desired size
is set to this size.
Whenever possible, the window manager tries to ensure that a window is at
least as large as its desired size, enlarging a window to its desired
size when space becomes available.  The desired size may also be set by a
client using @c(WM_NORMAL_HINTS). 

Users may leave windows in their normal state, or they may zoom them
(later unzooming them to restore them back to their normal state).
There are separate @b(desired) and @b(user minimum) sizes
for the normal and zoomed states.
The window manager ensures that the zoomed sizes are
always at least as large as their normal (unzoomed) counterparts.

Windows have a @b(desired position) -- a location at which the window
manager tries to keep the window centered.
Each time the user manually changes the size or placement of a window,
its center becomes the new desired position.

The client may change the desired position by specifying the
top-left of the window in @c(WM_NORMAL_HINTS).  If a size is specified in 
@c(WM_NORMAL_HINTS) as well, then the center of the rectangle determined
by that size and the top_left coordinates are taken to be the new desired
position.  If no size is specified, then the current window size is used.

Icon sizes are fixed, although, if the @b(icon_pixmap) is changed, the
icon size will change as well.

Like windows, icons have a @b(desired position), and this changes when
the user moves the icon.  The client can change the icon desired position
by specifying a new position using @c(WM_HINTS).

@section(The Pointer Interface)

@begin(quotation)
@b(NOTE:)
This manual descibes the default user interface based on a three button
mouse with the default meanings for mouse button usage.  These defaults
may be changed.
A @b(Quick Reference Page) is available for this default interface, as
well as for the default interface provided for use of a one-button mouse.
See the section on Customizations and Startup.
@end(quotation)

We have adopted a number of important principles that relate to use of the
pointer, which are described below.
We believe these contribute to the pleasant "feel" of the system.

@subsection(Mouse Button Model)

@subheading(Press-Move-Release vs Click-Move-Click)

The press-move-release, and the click-move-click buttoning styles are
interchangeable.
For example, to begin moving a window, the user can hold the SHIFT key
down while using the middle button of a border.
@begin(itemize)
For the press-move-release style, the user can
@i(press) the middle button in the border, hold it down while
moving the mouse to another location, and then @i(release) the button.

For the click-move-click style,
the user can @i(click) the middle button in the border,
move the mouse to another location, and then
@i(click) again.
@end(itemize)

@subheading(Cancellation while Tracking)

Every operation that involves mouse movement is cancellable at any
time by pressing the right mouse button.
For example, after pressing or clicking the middle button in the
border, the user can begin moving the
window around.
At any time, if the right button is pressed,
(whether the middle button is
being held down or was clicked), the move is cancelled,
and the pointer is (optionally) moved back to the position at
which the operation was started.

@subheading(Redundancy of Buttons and Decorations)

In the default interface, the left button is used for sizing windows,
the middle button for moving windows, and the right button for
popping up menus and cancelling operations.

There is a redundant correspondence between the button used and the
decoration used.  For example, the zoom gadget is used for sizing
operations, and is primarily used with the left button.
The move gadget is primarily used with the middle button, and
popping up menus is done in the header with the right button.

This redundancy provides a certain amount of flexibility.
First, it means that a three button mouse is not necessary.
The decoration in which a button is pressed,
could, along with modifier keys (e.g. SHIFT and CTRL) be used to
distinguish operations.

On the other hand, the decorations can be made optional.
In fact, windows are not required to have borders, headers or gadgets
(and can even have just the zoom but not the move gadget).
To support this, the bindings of operations to decorations are specified
by options and can be changed so that, for example, all
operations can be performed from the borders.

@subheading(Consistent use of CTRL and SHIFT)

CTRL and SHIFT are used as modifiers to distinguish similar sorts of
operations.  For example, there are three kinds of move operations
obtained by using the middle button in the move gadget:  @b(Relocate),
used for changing the size and location of a window, uses
no modifiers; @b(Move), for moving a window at its current size, requires
the SHIFT key; and @b(Exchange) requires the CTRL key.

Use of both CTRL and SHIFT is reserved for special cases.
CTRL and SHIFT left or middle button in either gadget redraws the window.
CTRL and SHIFT right button (the "cancel" button) in either gadget
closes the window.

@subsection(Feedback)

@subheading(Watch Cursor)

When the system is completing a user operation, or a client operation
that may affect screen layout, a watch cursor is
displayed, and input is queued.

@subheading(Cursor shows State)

In the midst of tracking a window operation, the cursor indicates both
the operation and the state.
For example, during the @b(Move) operation, the cursor changes to a hand.
There are some operations (such as @b(Relocate), discussed later) 
where the state may change during the operation.
When the state changes, the cursor changes as well.

@subheading(Cursor indicates Pointer Position)

When the system is @i(not) in the midst of tracking a window operation,
the cursor changes to indicate the sort of decoration in which it is
positioned.
For instance, there are eight different sorts of border areas
(four sides and the four corners), and a different cursor for each one.
The cursor changes immediately when it moves from one to another.
Consequently, there is no need to guess (from the position alone) whether
the cursor is in the header or border, or in a side border vs. a corner
border.

@subheading(Confirmation)

Some irrevocable operations (e.g. deleting a window, saving the layout,
exiting from the window manager) require confirmation.  The cursor
changes to a question mark in this case.  To cancel the operation, the
right ( "cancel" ) button is used.  The left or middle buttons confirm
the operation.

@subheading(Rubber Banding during Tracking)

Rubber-banding is used to provide feedback about the final window size
during resizing, moving, and opening a window.  This is especially
important because of @b(gravity), which adjusts the edge of the
rubber-band when it is near the edge of another window.

@subheading(Warping)

After an operation is completed, the pointer (optionally) is warped to a
position where the operation can be easily modified.
For example, after moving a window, the pointer is placed in the move
gadget so that it can be moved again.

@subsection(Focus and Listener)

Our window manager distinguishes between the @b(focus) -- the window
to which a keypress would currently be sent, and the @b(listener) -- the
window to which input was last directed.

@subheading(Focus Follows Pointer)

When the option @b(focusFollowsPointer) is on, a "Real-Estate-Driven"
interface is used -- the focus is the
window which contains the pointer.  However, if the client has
set the input field in @c(WM_HINTS) for that window to @i(false), there will
be no focus when the pointer is in the window; the client must
explicitly set the input focus to obtain keyboard input.

When the option @b(focusFollowsPointer) is off, the interface changes
to "Click-To-Type" -- the user must click a
mouse button in the window in order to change the focus (and since the
click is sent to the client, the listener changes as well).  If the
client has set the input field in @c(WM_HINTS) for that window to @i(false),
then the click is reported to the client, but the current focus and
listener are simply deselected; as described above, the client must
explicitly set the input focus to obtain keyboard input. 

@subheading(Preventing Client Side Effects to an Active Listener)

When the listener window is also the focus, we call it an @b(active
listener).  Since input has just been sent to it and the pointer remains
within it, it is actively in use, and the window manager treats such
windows specially for the reason described below. 

X11 clients can open, move or resize a window independently
of the user.
Such actions may be unpredictable -- they may happen at any time -- and
they may affect other windows, causing them to shrink or close.
Such asynchronous unpredictable actions can be especially annoying when
they affect the window in which the user is currently working.

Consequently, as an option, it is possible to prevent a listener from being
closed, and to prevent an active listener from being resized or moved as
a side effect of an operation performed by a client.

@subheading(Listener Tied To Zoom)

Some overlapping window managers automatically raise a window when it
becomes the listener, on the belief that a window in use should be
completely visible.
We allow a window to be zoomed when it becomes the listener for a similar
reason.

In our tiled window manager, a window may be shrunk as a result of side
effects caused by operations on other windows.  When it becomes the
listener, the user may desire that it be zoomed to an effective working
size.  When the window is no longer the listener, it may be allowed to be
unzoomed.  This behavior ensues if the window option
@b(listenerTiedToZoom) is on.

If the window option @b(zoomTiedToDesire) is set, then a window's zoom
desire size is taken to be it's normal desire size -- that is, when the
window is zoomed, it is zoomed to its normal desired size. 

@subheading(Preventing a Change of Listener)

Users may wish to direct input to another window without
changing the listener.  There are two reasons why this is useful:

@begin(Enumerate)
The listener is generally prevented from being closed as a side effect
of an operation by a client.  The user may want to retain this property
of the current listener while temporarily typing into another window.

Even though the user has tied a window's listener to zoom, he may only need
to temporarily type something in it (e.g. start a compilation) and there
is no reason to zoom it (and correspondingly unzoom the current listener if
it is tied as well).
@end(Enumerate)

If @b(focusFollowsPointer) is on, the user may simply move the
pointer to the @i(header) of the other window and type.
Input is directed to that window's client.
However, the original listener remains unchanged, and
is still prevented from being closed (but not moved or resized) as a
side effect of a client operation.
The temporary listener is prevented
from being closed, moved or resized while it is the focus.

If @b(focusFollowsPointer) is off, the user may obtain the same
result by clicking in the header of the other window.  To return the
focus to the original listener, the user just leaves the temporary listener
window.

@section(Manager Menu)

Pressing or clicking the right button in the background or in the RTL
icon will pop up the main manager menu.  This menu also appears as a
submenu of the window menu.  It contains the following entries:

@begin(Enumerate)
@b2(Redraw All) -- Redraws the screen

@b2(Lock Screen) -- Locks the screen until the user types a password.

@begin(multiple)
@b2(Closed Windows) -- Pops up a submenu of all closed windows.
Selecting one opens it.
Depending upon an option, the user either will
be asked to place it, or a place will be found automatically for it.

If the user is asked to place it, the cursor changes to a dotted box and
the corresponding icon (if it is open) will be highlighted.
The user can then move the pointer into the icon (the cursor will change
to a draped box) and click to have
the window opened automatically at a position
selected by the window manager.

Alternately, the user can leave the pointer outside of the icon.
Double clicking will place the window with its center at (or near) the
pointer.

However, just pressing (or single clicking) changes the cursor again, to
an "anchored arrow" signifying that the user is to size the window.
The current pointer location becomes the top left corner of the window.
The user can then move the pointer to specify the bottom right corner.

Releasing (or clicking again) finishes the sizing and places the
window at or near the size and position specified.  The
window's desired size is set to the size indicated by the user unless the
CTRL button is depressed.
@end(Multiple)

@b2(Tools) -- Pops up a submenu of applications.
Clicking on one of these runs the corresponding application.
The section on customization describes how the Tools submenu is
specified.

@b2(Prorate) -- Fairly reallocates space to the windows based upon their
minimum and desired sizes.

@b2(Fill) -- Allows each window to grow to its maximum size in an attempt
to use up screen space.

@b2(Undo) -- Undoes the last operation by the user which changed the
layout of the screen.

@begin(Multiple)
@b2(Repopulate) -- Reopens closed windows.  A submenu indicates three
kinds of repopulation:

@begin(Itemize, spread 0, above 0, group)

@b(Repopulate Auto) -- Attempts to reopen windows that were automatically
closed.

@b(Repopulate All) -- Attempts to reopen all closed windows.

@b(Repopulate Last) -- Attempts to reopen windows which were
automatically closed during the previous window operation.
@end(Itemize)
@end(Multiple)

@b2(Read Profile) -- Rereads a user profile and updates option
settings in existing windows corresponding to options that have changed
in the profile.  See the Customization and Options sections for more
information.

@begin(Multiple)
@b2(Finish Layout) or @b(Save Layout) -- When the window manager is
initially started up, the windows already on the screen are matched
against ones described in the @b(.rtl.layout) file; when one matches, the
window's size, position, state, and options are restored from the
information associated with window in the saved layout file.
The same is done even after the window manager is already running and a
client initially maps a new window or icon.

Until every saved window in
@b(.rtl.layout) is matched by an opened window or icon,
certain automatic strategies used by the window manager to balance screen
space are disabled in order to allow the saved layout to be precisely
restored.

In the meantime, "@b(Finish Layout)" appears in the window manager menu.
If an expected window does not open for some reason (host down,
program bombs, etc.), the user can tell the window manager to @i(treat)
the layout as finished by selecting "@b(Finish Layout)".

Alternately, by specifying the flag "-f"  when the @b(rtl) is
started, the windows on the screen when @b(rtl) is started are laid out,
but then, the layout is @i(treated) as finished and "@b(Finish Layout)"
does not appear.  If you specify the flag "-i", then the layout file
is ignored entirely.

When "@b(Finish Layout)" does not appear, "@b(Save Layout)" appears in
its place.
Selecting "@b(Save Layout)" saves information about all open and closed
windows and their icons in @b(.rtl.layout).
@end(Multiple)

@b2(Notify All) -- Send a @c(BANG!) message to all windows that accept the
message.
Not implemented in Release 5.1.

@b2(Soft Kill All) -- If a client has a window that accepts a @c(BANG!)
message, the message is sent to that window.
When each such client has updated the @c(WM_COMMAND) property of its
accepting window, the wm kills the client.  All other clients (all
clients in release 5.1) are killed immediately.

@b2(Hard Exit) -- Kills all clients and exits the window manager.

@b2(Detach Manager) -- Opens all client windows and exits the
window manager.
@end(Enumerate)

@section(Window Menu)

Pressing or clicking the right button in the header or border of a window
pops up a menu of entries which apply to that window.
Most of the window operations which can be invoked through the menu can
also be invoked, as indicated in parentheses, by buttoning the mouse in a
border or gadget.

@begin(Enumerate)
@b2(Title) -- Moving the pointer to the right of the menu entry displays
the full window title (in case the window header is too small to fully
display it).

@b2(Redraw) (@c(CTRL SHIFT LEFT/MIDDLE BUTTON in GADGET))  -- Redraws the
window.

@b2(Manager) -- Pops up the main window manager menu.

@b2(Close) (@c(CTRL SHIFT RIGHT BUTTON in GADGET)) -- Closes the window.

@b2(Group Close) -- If the window is part of a window group, hides all
windows and icons in the group and opens an icon for the group leader.
If not part of a group, acts like @b(Close).

@begin(multiple)
@b2(Resize) (@c(LEFT BUTTON in BORDER)) -- For resizing the window.

The user moves the pointer on or near the appropriate place on the window
border to determine the side or corner to be resized.  The cursor changes
to indicate which one would be selected.

The user then presses or clicks (with any but the right button) to begin
resizing.  If the button is clicked with SHIFT depressed, then gravity is
disabled (though if gravity is currently disabled by an option setting,
SHIFT enables it).

The mouse is then tracked by a window outline, which will be bounded by
the client minimum and client maximum size if these are enforced.
Depending upon option settings, the window outline may also be bounded by
the user minimum and maximum size.
If they are not so bounded, and the user resizes the window above the
user maximum or below the user minimum size, the user maximum or minimum
size will be reset.

Releasing or re-clicking the mouse button finishes the resize.  The
window's desired size is set to the size indicated by the user unless the
CTRL button is depressed.
@end(multiple)

@begin(Multiple) 
@b2(Relocate) (@c(MIDDLE BUTTON in MOVE-GADGET)) -- For relocating the
window to a new location possibly with a new size.

The cursor changes to a dotted box and is warped to the center of the
window.  The user then can move the pointer to another location.

Double clicking will relocate the window with its center at (or near) the
pointer.

However, just pressing (or single clicking) changes the cursor again, to
an "anchored arrow" signifying that the user is to size the window.
The current pointer location becomes the top left corner of the window.
The user can then move the pointer to specify the bottom right corner.

Releasing (or clicking again) finishes the sizing and relocates the
window at or near the size and position specified.  The
window's desired size is set to the size indicated by the user unless the
CTRL button is depressed.
@end(Multiple)

@begin(Multiple)
@b2(Move) (@c(SHIFT MIDDLE BUTTON in MOVE-GADGET)) -- For moving the
window at its current size to a new location.  The cursor changes to a
hand and is warped to the center of the window.  The user then can move
the pointer to another location.

Clicking finishes the move and places the window exactly where specified.

(@c(MIDDLE BUTTON in BORDER)) also initiates a move.  In the side border,
the move is constrained in one dimension.  If the @c(SHIFT) key is held
down as well, gravity is toggled during the move.
@end(Multiple)

@begin(Multiple)
@b2(Exchange) (@c(CTRL MIDDLE BUTTON in MOVE-GADGET)) -- Used for
exchanging the location of two windows, or of a window and an icon.  The
cursor changes to a pair of opposite pointing arrows.  The user can then
move the pointer to an icon or another window.

Clicking in a window exchanges the locations of the two windows.
Clicking in an icon closes the open window and opens the iconized
window in its place.
@end(Multiple)

@b2(Expand) -- Expands the window in the available white space
surrounding it (up to its maximum size), without affecting any other
windows.  Sets the window's desired size to the resulting size.

@b2(Desire) (@c(LEFT BUTTON in ZOOM-GADGET)) -- Enlarges the window
up to its desired size, by shrinking (but not closing) the other windows
on the screen.

@b2(Shrink) -- Shrinks the window to its minimum size.  The desired size
is not changed though, so on subsequent window operations, the window
will grow back to its desired size.

@b2(Enlarge) (@c(CTRL LEFT BUTTON in ZOOM-GADGET)) -- Makes the window as
large as possible up to its maximum size, by shrinking (but not closing)
the other windows on the screen.

@b2(Zoom) or @b(Unzoom) (@c(SHIFT LEFT BUTTON in ZOOM-GADGET)) -- Zooms
or unzooms the window.

@b2(Set Size) -- A submenu for setting the various sizes associated with
the window (Normal Min, Normal Desired, Zoom Min, Zoom Desired,
Max).  The details are the same as for Resize.

@begin(multiple)
@b2(Options) -- A submenu for setting and unsetting various window
options.  The option is set if it is checked in the menu.
Selecting the entry toggles the setting.

@begin(Itemize, spread 0, above 0, group)

@b2(Locked Open) -- prevents the window from being automatically closed.

@b2(Fixed Width) -- prevents the window's width from being automatically
changed.

@b2(Fixed Height) -- prevents the window's height from being
automatically changed.

@b2(Fixed Edges) -- prevents the window from being moved or resized
automatically.

@b2(Listener Tied To Zoom) -- Zooms (unzooms) the window when it becomes
(no longer is) the listener.

@b2(Zoom Tied To Desire) -- Uses the normal desired size in place of the
zoom desire size.

@end(Itemize)
@end(multiple)

@b2(Notify) -- Sends the @c(BANG!) message to the window if it accepts it.
Not implemented in release 5.1.

@b2(Soft Kill) --  If the window accepts the @c(BANG!) message, it is
sent to it.  When the client has updated the @c(WM_COMMAND)
property of its accepting window, the wm kills the client.
If the window does not accept the @c(BANG!) message, the client is
immediately killed.  In release 5.1, simply kills the client. 

@b2(Hard Kill) -- Kills the client.
@end(Enumerate)

@section(Icon Menu)

The icon menu is very similar to the window menu.  It is popped up by
pressing the right button inside the icon.

@begin(Enumerate)
@b2(Title) -- Displays the title.

@b2(Redraw) (@c(CTRL SHIFT LEFT/MIDDLE BUTTON))  -- Redraws the icon.

@b2(Manager) -- Pops up the main window manager menu.

@begin(Multiple)
@b2(Open) (@c(LEFT BUTTON)) -- If the icon is associated with a closed
group, restores the windows and icons of that group.

If the icon corresponds to a single window, then Open is used for opening
that window:

The cursor changes to a draped box.

The user can leave the pointer in the
icon (or move it there if the menu selection left it outside the icon),
and click, and the window will be opened automatically at a position
selected by the window manager.

Or, the user can move the pointer outside of the icon.  It will change to
a dotted box and the user can then specify the size and potentially the
location just as for a Relocate.
@end(Multiple)

@b2(Move) (@c(MIDDLE BUTTON)) -- For moving the icon to a new location.

@b2(Exchange) (@c(CTRL MIDDLE BUTTON)) -- Used for exchanging the
location of two icons, or of a window and an icon.  Exchanging two icons
exchanges their positions.  Exchanging an icon and a window closes the
open window and opens the iconized window in its place.

@b2(Options) -- The submenu for setting and unsetting various window
options.

@b2(Notify) -- Sends the @c(BANG!) message to the window if it accepts it.
Not implemented in release 5.1.

@b2(Soft Kill) (@c(CTRL SHIFT RIGHT BUTTON)) --  If the window accepts
the @c(BANG!) message, it is sent to it.  When the client has updated the
@c(WM_COMMAND) property of its accepting window, the wm kills the client.
If the window does not accept the @c(BANG!) message, the client is
immediately killed.  In release 5.1, simply kills the client. 

@b2(Hard Kill) -- Kills the client.
@end(Enumerate)

@section(Customization and Startup)

The window manager can be customized via files in three ways: by setting
options in preference files, by specifying the tools to appear in the
tools submenu, and by arranging for applications to be started up
automatically when the window manager is started.

All files opened by the window manager are looked up in the
directory named in the @b(RTLENV) environment variable, and if that
fails, in the user's home directory.

Copies of the files used by the developers may be found in the
subdirectory @b(custom) in the distribution.

@subsection(Startup)

If the "-s" flag is specified when the window manager is started up,
the file @b(.rtl.startup) is executed.
Typically it contains a shell file which starts up various applications.

If the "-l" flag is specified when starting the window manager, and a
window saved in the @b(.rtl.layout) file does not appear on the screen,
then a process is started which would open that window.  Both the host
and the command line are obtained from the layout file;  when the layout
file was saved, these were obtained respectively from the
@c(WM_CLIENT_MACHINE) and @c(WM_COMMAND) properties of the window.
Not implemented in release 5.1.

If the flag "-f" is specified when the window manager is started, then
the layout is treated as finished.  However, if the "-l" flag is
specified as well, the commands associated with missing windows are still
executed.

@subsection(Tools)

Each tool is registered in the file @b(.rtl.tools) as a pair of lines.
The first line is the name of the tool as it should appear in the tools
submenu.
The second line is a command to be executed when the menu entry is
selected.

@subsection(Preference Files)

Options that control the behavior of individual windows, or of the window
manager as a whole, are obtained from a number of preference files,
primarily ".Xdefaults", and ".rtl.preferences".  Release 5.1 reads these
files directly, and does not use the resource database described in the
Xlib manual.

Options that control the behavior of windows of a specified name or class
are additionally obtained from the files @b(.<name>.preferences)
and @b(.<class>.preferences), where "<name>" and "<class>" refer to the
resource name and resource class of the window (specified by the
@c(WM_CLASS) property).

Preferences used by window manager take the form
@begin(verbatim)
    Wm.option: value
@r(or)
    Wm.<class>.option: value
@r(or)
    Wm.<name>.option: value
@r(or)
    Wm*option: value
@end(verbatim)

@b(Wm) is the class for all window managers.  Instead of @b(Wm), @b(rtl),
the name of our window manager, can be used instead.

Some options are global and refer to the window manager as a whole.
These use the form "@b(Wm.option)".

Others are applied on a per-window basis.

Per-window options prefixed by @b(Wm) and a @i(class)
are used to determine the the value of that option for all windows of
that @i(resource-class).

Per-window options prefixed by @b(Wm) and a @i(name) are used to
determine the the value of that option for all windows of that
@i(resource-name), and override the
@i(class)-prefixed option value for that window if specified.

Options prefixed by @b(Wm*) are used to set default option values for
all windows.

The @i(resource-class) and @i(resource-name) of a window come from its
@c(WM_CLASS) property.

@begin(quotation)
@b(NOTE:) Some older applications do not set a window's @c(WM_CLASS).
In that case, its resource-class is taken to be the same as its window
name (i.e @c(WM_NAME)).
@end(quotation)

@begin(quotation)
@b(NOTE:) Some applications incorrectly use strings for the resource name
and resource class that contain spaces.  These cannot be used to
obtain options.
@end(quotation)

The order of "@b(Wm)"-, class-, and name-prefixed options in the
@b(.rtl.preferences) file is immaterial.

Users may change the any of the preference files and reread them by
selecting "Preferences" from the "Read Profile" submenu of the main
manager menu.
Any changes in the file will be immediately reflected
in all windows -- open or closed.

The file @b(.../src/defaults.i) contains the default settings for all
options.

Certain options may be changed on a per-window basis through the
"Options" entry of each window menu.  The submenu entries and the options
affected are

@begin(verbatim, group, font smallbodyfont)
     Menu Entry               Option
     ----------               ------
                              
     Locked Open              lockedOpen
     Fixed Width              fixedWidth
     Fixed Height             fixedHeight
     Fixed Edges              fixedCompletely
     Listener Tied To Zoom    listenerTiedToZoom
     Zoom Tied To Desire      zoomTiedToDesire
@end(verbatim)

When these options are changed explicitly through the "Options" submenu,
changes made to them via rereading preference files will
have no effect.  The current values of these options are saved for each
window in the @b(.rtl.layout) file and are restored as each window is
reopened when the window manager is restarted.

@subsection(Profile Menu)

The file @b(.rtl.profiles) menu is used for adding additional entries
to the "Read Profile" submenu.

Each profile is registered in the file @b(.rtl.profiles) as a pair of
lines.
The first line is the name of the profile as it should appear in the
"Read Profile" submenu.
The second line contains a list of preference files (separated by
blanks) to be read when the menu entry is selected.

These named preference files, like all other customization files opened
by the window manager, are looked up in the directory named in the
@b(RTLENV) environment variable, and if that fails, in the user's home
directory.  Support is also provided for files named by paths beginning
with "/" (absolute path names) and with "~" (paths rooted in a user's
home directory).

When an entry is selected from the "Read Profile" submenu, the
standard preference files are read first, before the files
associated with the menu entry.
Thus the additional preference files can be used to add or override
options specified in the standard preference files.

There are a number of additional preference files included with the
distribution.  These illustrate many of the issues described in the
section below on "Automatic Strategies".

@subsection(Button Semantics)

The file @b(.../src/interf_init.c) in the distribution determines the
association of mouse buttons / modifier combinations (e.g. CTRL Middle
Button) with a particular window manager action.

Part of the file @b(.../src/defaults.i) (look for "Global Interface
Options") determines whether a particular mouse
button / modifier combination takes effect in a specified region
(e.g. header, border, gadget, etc.).

By changing these files and recompiling, these associations can be
changed.

In particular, the files @b(.../src/interf_init_one.c) and 
@b(.../src/defaults_one.i) in the distribution contain the
default settings for a one-button mouse.

@section(Automatic Strategies)

The Siemens RTL Tiled Window Manager can automatically adjust the size
and position of windows to balance competing demands for screen space, or
it can be completely prevented from doing so.

In the simplest case, windows are placed exactly at the size and location
that the user specifies.  Via options, it is possible to prevent windows
from ever being automatically shrunk or closed, and to ensure that
windows opened automatically are reopened exactly at their previous
location.  If a window cannot be opened, moved or resized exactly as
specified without causing side effects, the window manager will refuse to
do the operation.

The options permit considerably more flexibility.  There are large number
of options that control automatic behavior and they are described in
detail in the "Options" section.  In this section, we attempt to describe
some of the more common changes in behavior that our users have explored.

@subsection(Default Automatic Behavior)

The default option settings, those in effect if no preference files are
read at all, provide what we consider the minimum automatic behavior that
a user would find acceptable:

@begin(itemize)
Windows may automatically be shrunk and closed (except for an active
listener as a result of a client's action).  This may be prevented on a
per-window basis as a result of setting "Locked Open", "Fixed Width",
Fixed Height", or "Fixed Edges" in the "Options" submenu of a window
menu.

When space is available, windows which were shrunk regrow towards their
desired sizes, though they may not necessarily be located at their exact
original position.

When the window manager automatically places a window, an attempt is made
to place it at its previous location, even if other windows have to be
shrunk or closed.  If this fails, however, the window is opened at the
best location nearby.

When a window is unzoomed, an attempt is made to open (or
"@b(repopulate)") windows which were automatically closed
since the window was zoomed, but only at their previous positions, and
only if no other windows will be shrunk or closed.
A similar attempt is made when a window is explicitly closed -- to
repopulate windows automatically closed since the window was
opened.

@end(itemize)

@subsection(Neighborhood Placement)

When a window is opened or moved, it may not be possible to place
it exactly at the size and location specified.
Options are available which allow it to be placed nearby its specified
location and/or shrunk below its desired size.

By nearby, we mean within a "neighborhood" of the specified location.
Two kinds of neighborhoods are supported:

@begin(Itemize,group)
A window is placed within a @b(center neighborhood)
if the window as actually placed contains the center of the window as it
was specified.

A window is placed within an @b(edge neighborhood) if the window as
actually placed overlaps the window as it was specified.
@end(Itemize)

Pure neighborhoods, as defined above, are somewhat excessive for larger
windows. For example, the edge neighborhood of a window 1/3 the height
and 1/3 the width of the screen which is placed at the center of the
screen consists of the entire screen -- that is, it could be placed
anywhere.

Therefore, we include a @b(neighborhoodShrinkFactor) option which
shrinks neighborhoods relative to the window size. 

A number of @b(try..) options determine whether neighborhoods are to be
used at all.

An excessively large number of @b(prefer...) options determine
whether neighborhoods are to used in preference to closing or shrinking
adjacent windowa, or shrinking the window being explicitly affected
below its desired size.

@subsection(Resize)

When the user resizes a window, the operation fails by default if the
size specified cannot be attained.  An option permits the window to be
resized to a smaller size, but this is not always desired.

To avoid a failed resize, or simply to prevent other windows from being
shrunk or closed, an option permits a resized window to "slide".
For example, if the user attempts to enlarge a window by resizing its
left edge, and a window is on its left, but there is space on its right,
the window will grow to the right instead of to the left.

It is also possible to set options that will move a window being resized
if the resize fails or would close or shrink other windows.

@subsection(Listener Tied to Zoom)

When a window has the option @b(listenerTiedToZoom) set, it will be
enlarged to its zoom size when it becomes the listener.
Depending on various other options, when it is no longer the listener, it
may shrink to its unzoomed size, or just shrink enough to allow adjacent
window to grow back towards their desired size.
In particular, if another window becomes the listener, it will shrink to
provide space for the new listener to zoom.

Some users prefer all windows to have @b(listenerTiedToZoom) set.
The effect is similar to overlapping window systems that raise
a window when it becomes the listener, and that allow the window to
be covered again when another window becomes the listener.

Some users prefer the window option @b(zoomTiedToDesire) to be set as
well, so that when a window becomes the listener, it is enlarged to
its current desired size, rather than a separate zoom size.

When a window is zoomed, it may become so large that other windows may
close.  The option @b(automaticRepopulateOnAutoUnzoom) reopens them
if possible, providing the illusion that they were hidden by the zoomed
window, and were then exposed when the window was unzoomed.

@subsection(Moving Conflicting Windows)

When a window is being opened, resized, or moved, the window manager
appears to move other windows, which occupy the needed space,
out of the way.
This appears to happen for two reasons.

@begin(Itemize)
A window in the way is actually shrunk, say on its left, to make room,
and then (because @b(autoDesiredEnlarge) is set), it grows towards its
right (where there is blank space) back to its desired size.  Thus it
appears to move to the right.

@begin(multiple)
A window in the way is actually closed.  However, the option
@b(autoRepoulateLast) is set, and this tries to reopen windows closed
during an operation.
To achieve the effect of moving the window nearby, either
the option
@b(preferPreviousPositionOnAutoRepopulate) or the option
@b(preferPreviousPosition)
should be set.
This will attempt to reopen the window as near as possible to its
previous location.

Beware: Neither the option @b(requirePreviousPosition) nor the option
@b(requirePreviousPositionOnAutoRepopulate) should be set in
conjunction with @b(autoRepoulateLast),  since they will force the
window to be opened exactly at its previous location, and this will
naturally fail.
@end(multiple)
@end(Itemize)

@subsection(Automatic Unzooming)

When a window is being opened, resized, or moved, one or more of the
windows in the way may be zoomed.  Two options determine whether the
window manager should automatically unzoom the window rather than simply
closing it or refusing to do the operation -- @b(preferUnzoomToClose)
and @b(unzoomTiedListenerIfNecessary).

The option @b(preferUnzoomToClose) will unzoom a window rather than
closing it.

However, the listener window is treated specially.  For various reasons, the
listener may not be permitted to close.  In particular, the default setting
for the option @b(allowListenerToCloseByClient) prevents clients
from performing an operation (like opening a window) that would allow the
listener to be closed.  To allow the listener to be unzoomed in this
situation, the option @b(unzoomTiedListenerIfNecessary) should be
set.

@subsection(Automatic Prorating)

The option @b(autoProrate) fairly reallocates screen space after
each window operation, based on the minimum and desired size of each
window.  This may cause windows to shrink.  However, the previous two
windows that had their desired sizes reset will not be shrunk below their
desired sizes.

If the option @b(biasedAutoProrate) is additionally set, then
after each operation, it gives as much space as possible to
the listener without closing other windows on the screen.

To both make windows as large as possible when they become the listener,
and ensure that the window at least attains its zoom minimum,
the options
@b(autoProrate), @b(biasedAutoProrate) and @b(listenerTiedToZoom)
can all be set.

@section(Standard X11 Properties)

Release 5.1 of the Siemens RTL Tiled Window Manager supports the standard
properties described in the Inter Client Communications Conventions
Manual as released on the V11R2 tape.
The properties and their uses are described below.

@begin(enumerate)

@begin(Multiple)
@c(WM_TRANSIENT_FOR)@*

Windows which are transient pop-ups and have extremely short lifetimes
may have the @b(override-redirect) attribute set so the window manager
will not be involved.  However, if the transient window has a long enough
lifetime that its size or position may need to be manipulated by the
user, @b(override-redirect) should not be used.  Instead, the window's
@c(WM_TRANSIENT_FOR) property should be set to refer to the window with
which it is associated.  The Siemens RTL Tiled Window Manager will not
tile such a window -- it will sit above the tiled desktop.
It has no decorations and can be moved, mapped and unmapped only by the
client.

@end(Multiple)

@begin(Multiple)
@c(WM_CLASS)@*

@c(WM_CLASS) is a structure containing two strings: @b(res_name) and
@b(res_class).

The @b(res_class) field identifues the application.
The @b(res_name) field is a string that more specifically identifies the
instance of the application.

They are used in the @b(.rtl.layout) file for distinguishing windows on
startup, and for setting the window options from preferences files.

Both optionally appear in the window header and in icons.
@end(Multiple)

@begin(Multiple)
@c(WM_COMMAND)@*

Holds the command that would be used to restart the application --
typically the command used to run the application initially.
The window manager saves it in the layout file for identifying a window,
and for restarting the application.

If the "-l" flag is specified when starting the window manager, and a
window saved in the @b(.rtl.layout) file does not appear on the screen,
then its corresponding command is executed (not in Release 5.1).

@end(Multiple)

@begin(Multiple)
@c(WM_CLIENT_MACHINE)@*

The machine on which the application is running.
Typically set once, but
may be changed by applications which migrate from machine to machine.
It optionally appears in the window header and icon, and is used in the
layout file for identifying windows.
@end(Multiple)

@begin(Multiple)
@c(WM_NAME)@*

Information about the application or its current state
which is optionally placed in the window header.  It also is used
in an icon when @c(WM_ICON_NAME) is not provided.  
@end(Multiple)


@begin(Multiple)
@c(WM_ICON_NAME)@*

Information about the application or its current state
which is optionally placed in an icon.
@end(Multiple)

@begin(Multiple)
@c(WM_NORMAL_HINTS)@*

In release 5.1, only the size, position, minimum, and maximum sizes are
used.
@end(Multiple)

@begin(Multiple)
@c(WM_HINTS)@*

The @b(input) field determines whether the window manager or the client is
responsible for setting the input focus.  See the section on "Focus
Follows Pointer".

The @b(initial_state) is used to initially determine the display state of
a window when it is first mapped by
the client, and can later be used to change the display state.  See the
section on "Client Placement".

The @b(icon_pixmap) is used to determine the contents of an icon.
If no icon_pixmap is provided, a default icon is built from @c(WM_CLASS),
@c(WM_ICON_NAME) (or @c(WM_NAME)) and/or @c(WM_CLIENT_MACHINE).

The client may provide an @b(icon_window), but release 5.1 of the window
manager will not map it.  An attempt to map it will cause the icon pixmap
(or default icon) to be mapped instead.

The @b(icon_mask) is ignored in release 5.1.

The @b(window_group) field specifies a "group leader".  All windows
with the same group leader are part of the same group.  The user can
close the whole group, and the icon for the group ledaer is displayed.
@end(Multiple)

@end(enumerate)

@section(Client Placement)

A client can affect the size, location, and presence of a tiled window
by setting properties (particularly @c(WM_NORMAL_HINTS) and
@c(WM_HINTS)), by mapping or
unmapping a window, by attempting to map a client icon, or by attempting
to reconfigure a window.  These are discussed below.

@subsection(Initial Window and Icon Mapping)

When a window is newly created, it or its icon will eventually be
opened.
An attempt to open the window may fail if there is not enough room on the
screen for it, and if windows in the way cannot be shrunk or closed.
In that case, the window's title is placed in the menu of closed windows,
and if icons are to be used, the icon is opened.
If the icon cannot be opened immediately (due to lack of available
space), it will be subsequently opened at the earliest opportunity.  

A window or icon initially will be opened when one of the following two
events occurs:

@begin(enumerate)

@begin(Multiple)
The client maps the window:
@begin(Itemize)
If the window matches one in the saved layout file (@b(.rtl.layout)):
Either the window or icon will be open based on which was open when the
layout was saved.  If the window is opened, it will be zoomed if it
was when the layout was saved.

@begin(multiple)
If the window does not match one in the saved layout file (or there
is no saved layout file), and @c(WM_HINTS) indicates an @b(initial state)
of

@begin(itemize,group,spread 0)
Ignore or Inactive: Neither window nor icon is opened.

Iconic: The icon is opened if icons are in use.

ClientIcon or Normal: The window is opened unzoomed.

DontCare, or the @b(initial state) was not set: The window is opened if
the window's option @b(autoOpenOnCreate) is set; else, the icon is
opened.
@end(Itemize)
@end(multiple)
@end(Itemize)
@end(Multiple)

@begin(Multiple)
The client maps its client icon window:
@begin(Itemize)
If the window matches one in the saved layout file (@b(.rtl.layout)):
Either the window or icon will be open based on which was open when the
layout was saved.  If the window is opened, it will be zoomed if it
was when the layout was saved.

@begin(multiple)
If the window does not match one in the saved layout file (or there
is no saved layout file), and @c(WM_HINTS) indicates an @b(initial state)
of

@begin(itemize,group,spread 0)
Ignore or Inactive: Neither window or icon is opened.

Iconic or Normal: The icon is opened if icons are in use.

ClientIcon: The window is opened unzoomed.

DontCare, or the @b(initial state) was not set: The window is opened if
the window's option @b(autoOpenOnCreate) is set; else, the icon is
opened.
@end(Itemize)
@end(multiple)
@end(Itemize)
@end(Multiple)

@end(Enumerate)

@subsection(Initial Size and Placement)

A window's initial size is determined by the size specified
when the window was created.
This may be overridden by a size specified by a client in setting
@c(WM_NORMAL_HINTS).
This may be overridden by the
@c(DESIRED_HEIGHT) and/or @c(DESIRED_WIDTH) preferences.

A window's initial position is determined by the size specified
when the window was created.
This may be overridden by a position specified by a client in setting
@c(WM_NORMAL_HINTS).

However, when a window matches one in the saved layout file,
both its size and position are taken from the layout
file.  

When a window is to be initially mapped, it will be automatically placed
by the window manager under the following conditions:
@begin(itemize)
The size and position are both specified via @c(WM_NORMAL_HINTS),
and none of the options @b(ignoreSizeHints), @b(ignoreInitialSizeHints),
@b(ignorePositionHints), or @b(ignoreInitialPositionHints) are set.

The window option @b(autoPlaceOnClientOpen) is set, the size has
been specified, and neither @b(ignoreSizeHints) or
@b(ignoreInitialSizeHints) has been set.

The window option @b(autoPlaceOnClientOpen) is set, and the global
option @b(autoPlaceOnUnsizedOpen) is set.
@end(itemize)

If none of these conditions holds, the user is asked to place the window
manually.  This is indicated by a change in the cursor.

When the window is being automatically placed and its position has
been provided and the window option
@b(requirePreviousPosition) is set, it will be opened exactly where
specified;  if it cannot be opened there, it will be iconized instead.
If @b(preferPreviousPosition) is set instead, it will be opened as
close as posssible to the provided position.
Otherwise, the window is opened at the "best" possible location -- a
place where it interferes least with other windows currently on the
screen.

When the window manager is initially started, client windows and icons
may already be open.  These are treated as if they were explicitly mapped
by the client after the window manager started up.  However, if such a
window does not match a window saved in the layout file, it is always
placed as close as possible to its current size and position.

@subsection(Subsequent Window and Icon Mapping and Unmapping)

A later attempt by a client to map a window has the following
effect depending upon the value of @c(WM_HINTS).@b(initial_state).

@begin(itemize,group,spread 0)
Ignore, Inactive, Iconic, or ClientIcon: No effect

Normal, DontCare, or @b(initial_state) was not set: The window is
opened at or near its previous location depending on the
options @b(requirePreviousPosition) or @b(preferPreviousPosition).
If neither is set, the "best" location is found.
If no location can be found, it remains iconized.
An attempt is always made to map it at its desired size.
The window will be zoomed if it was zoomed when it was last open.
@end(Itemize)

When a client unmaps its window, this has the following effect depending
upon @c(WM_HINTS).@b(initial_state).

@begin(itemize,group,spread 0)
Ignore, Inactive or Iconic: No effect

ClientIcon: Remap the window.

Normal, DontCare, or @b(initial_state) was not set: The 
pixmap or default icon is opened.
@end(Itemize)

Attempt by a client to map its client icon window (other than the
first time) has the following effect depending upon the value of
@c(WM_HINTS).@b(initial_state).

@begin(itemize,group,spread 0)
Ignore, Inactive, Iconic, or ClientIcon: No effect

Normal, DontCare, or @b(initial_state) was not set: The 
pixmap or default icon is opened.
@end(Itemize)

@subsection(Configure)

When a client changes the size or position of a tiled window via
XConfigureWindow, the window manager attempts to comply.
If just the size has been changed, the window is enlarged or shrunk.
If the position has been changed, the window is moved as close as
possible to the specified location.

An attempt to change the border width will be ignored; the window manager
forces the border width to zero.

Attempts to change the stacking order will also be ignored; tiled windows
do not overlap and are all on the same level.

Note that transient windows are not tiled, and attempts to reconfigure
them will will succeed as requested, except that attempting to
place a transient window below a tiled window will place it below all
transient windows, but above all tiled windows.

@subsection(Size Hints)

Clients setting @c(WM_NORMAL_HINTS) while
a window is open can cause changes in the size or location of the
window.

If the option @b(autoResatisfyOnResetMinmax) is set,
and the window no longer satisfies its client minimum or maximum size,
an attempt will be made to enlarge or shrink the window.  Even if the
window cannot be enlarged, it will not be automatically closed.
However subsequent user operations will enforce the client minimum size
if @b(enforceClientMinimums) is set.

If a new size was specified, it becomes the normal or zoom desired size.

If either a size or position was specified, and
@b(autoResatisfyOnResetMinmax) is set, then an attempt is made to
change the size or position of the window.

Both position and size can be specified as provided by either the user or
program.  If either is specified as user supplied, then the hint
is treated as a direct effect of a user action.  Consequently, the
limits on client actions ordinarily determined by the option
@b(allowAutomaticCloseByClient), the option
@b(allowAutomaticShrinkByClient),
@b(allowListenerToChangeByClient), and
@b(allowListenerToCloseByClient) do not apply.

@subsection(WM_HINTS)

Our window manager supports dynamic changes to @c(WM_HINTS).  In
particular, changes in the @b(initial_state) field are treated as
direction to change the display state of the window:

The states have the following effects:

@begin(itemize, group)
@b(Ignore): Closes the window or icon if either was open, and removes
it from the closed menu list.

@b(Inactive): Closes the window or icon if either was open.

@b(Iconic): Closes the window if it was open. Opens an icon if icons are
in use.

@b(Normal or ClientIcon): Opens the window if it was closed.

@b(DontCare): No change.
@end(itemize)

Changes to the other supported fields -- @b(input), @b(icon_pixmap),
@b(icon_x), @b(icon_y), @b(icon_window), and @b(window_group)
take immediate effect as well.

@section(Options)

Options are specified in Preference Files as described in the section of
that name.

Options may either be @b(global), referring to the window manager as
a whole, or per-@b(window).

Options may either be @i(boolean), in which case they take on the values
@b(on) and @b(off), @i(numeric), in which case, they take on numeric
@b(values), or @i(strings).

Options and values may be @b(semantic), in which case they control the
decisions made by the window manager, or they may strictly be
@b(interface)-related -- that is, they simply control the way the screen
looks.

This section, then, is divided into a number of parts, based on the
orthogonal distinctions of @b(global) vs per-@b(window), boolean
@b(option) vs @b(value) vs @b(string), and @b(semantic) vs.
@b(interface)-related.
Each section contains a list of the relevant option names with their
default value.

@subsection(Global Semantic Options)

@begin(itemize, font smallbodyfont)
@bx(allowAggressiveRepopulation): on@*
If on, attempts to open automatically closed windows with the
@b(aggressivelyRepopulate) option on whenever possible.

@bx(allowAutomaticClose): on@*
Determines whether windows can be closed automatically (as a side
effect of an operation on another window).

@bx(allowAutomaticCloseMoreRecent): on@*
If @b(allowAutomaticClose) is on, but this option is off, then a
window can be closed as a result of a side effect on another
window only if the other window has been used more recently.

@bx(allowAutomaticShrink): on@*
Determines whether windows can be shrunk automatically (as a side
effect of an operation on another window).

@bx(allowAutomaticShrinkMoreRecent): on@*
If @b(allowAutomaticShrink) is on, but this option is off, then a
window can be shrunk as a result of a side effect on another
window only if the other window has been used more recently.

@bx(allowAutomaticShrinkOnAutoRepopulate): off@*
@b(allowAutomaticShrinkOnExplicitRepopulate): on@*
Determines whether windows on the screen can be shrunk as a
result of a Repopulate.  Explicit repopulates are those
done when the user selects Repopulate from the menu.
Automatic repopulates include all other
attempt by the window manager to automatically open a closed window.

@bx(allowAutomaticCloseOnExchange): off@*
@b(allowAutomaticShrinkOnExchange): on@*
Determines whether the other windows on the screen can be shrunk
or closed as a side effect of an Exchange.

@bx(allowAutomaticCloseByClient): on@*
@b(allowAutomaticShrinkByClient): on@*
When a client invokes a window operation, these options determine
whether other windows on the screen can be shrunk or closed as a
side effect.

@bx(allowListenerToClose): on@*
If off, then the window which is the listener cannot close as
a side effect of an operation on another window.

@bx(allowListenerToChangeByClient): off@*
@b(allowListenerToCloseByClient): off@*
When a client invokes a window operation, these options determine
whether an active listener can be shrunk or closed as a side effect.

@bx(allowShrinkOnAutoOpen): on@*
@b(allowShrinkOnCenterOpen): on@*
@b(allowShrinkOnCornerOpen): off@*
An attempt to place a window may not succeed if surrounding
windows are in the way which cannot be shrunk or closed.  In that
case, the window being placed may have to be made smaller than
its desired size.  These options determine whether that is
permitted.  A corner open is one where the new location and
corners of the window are chosen by the user.  A center open is
one where only the center is chosen by the user.  If they are not
set and shrinking is necessary, the operation will fail.

@bx(allowShrinkOnResize): off@*
When a user explicitly resizes a window, the size selected
may be too large -- that is, adjacent windows may not be able to be
shrunk or closed.
If the option is on, the window will be
made as large as possible up to the size requested.  If it is off, the
resize will fail.

@bx(autoDesiredEnlarge): on@*
If on, then an attempt is made after every operation to enlarge
each window to its desired size without moving or shrinking other
windows.

@bx(autoProrate): off@*
If on, then automatically prorates after each operation.

@bx(autoRepopulateLast): off@*
If on, then if a window is closed automatically during an
operation, an attempt is made to reopen it.  The window may
appear to have been moved, but it was closed and then reopened.

@bx(autoRepopulateOnAutoUnzoom): on@*
@b(autoRepopulateOnExplicitUnzoom): on@*
These determine whether an attempt is made to repopulate closed
windows following an unzoom.  An automatic unzoom occurs when a
zoomed window which has @b(listenerTiedToZoom) is no longer the
listener.
If the window is destroyed, then repopulation will be done if
either of these options is set. 

@bx(autoRepopulateOnClose): on@*
This determines whether an attempt is made to repopulate closed
windows following an explicit close of the window or the termination of
the client.

@bx(biasedAutoProrate): off@*
When set, forces automatic prorating to make the most recently used
windows the largest.

@bx(enableAutoRepopulationDuringLayout): off@*
@b(enableAutoSizingDuringLayout): off@*
When initially starting the window manager, if these options are
off, then automatic repopulation, automatic enlargement to
desired size, and automatic prorating are disabled until all
windows matching entries in @b(.rtl.layout) have been created.

@bx(enableGravity): on@*
Uses gravity to line up windows.

@bx(onlyRepopulateSinceOnAutoUnzoom): on@*
@b(onlyRepopulateSinceOnExplicitUnzoom): on@*
If on, then following an unzoom or destroy, only windows closed
since the window was zoomed will be reopened.

@bx(onlyRepopulateSinceOnClose): on@*
If on, then following an explicit close or destroy, only windows
closed since the window was last opened will be reopened.

@bx(preferCloseToShrinkOnAutoOpen): off@*
@b(preferCloseToShrinkOnCenterOpen): off@*
@b(preferCloseToShrinkOnCornerOpen): on@*
@b(preferCloseToShrinkOnExchange): off@*
@b(preferCloseToShrinkOnResize): on@*
Determine whether it is better to close other windows or to
shrink the window being operated upon (assuming both are
permitted by other options).

@bx(preferExchangedLocationOnIconizing): on@*
When exchanging an iconized window and an open window, determines
whether the preferred location of the icon for the newly closed
window is its previous icon position, or the position of the
currently icon.

@bx(preferExchangedLocationOnOpening): on@*
If the option is set when exchanging an iconized window and an
open window, and if the currently closed window has not been
positioned or does not require placement at its previous
position, then an attempt is made to place the newly opened
window at the location of the window it is being exchanged with.

@bx(preferPreviousPositionOnAutoRepopulate): on@*
@b(preferPreviousPositionOnExplicitRepopulate): on@*
When a window is being repopulated, determines if an attempt is
first made to place it at its previous location.

@bx(preferCenterNeighborhoodToAutomaticCloseOnOpen): off@*
@b(preferCenterNeighborhoodToAutomaticShrinkOnOpen): off@*
@b(preferCenterNeighborhoodToShrinkOnOpen): off@*
When a window is being placed at a location, it may be placed
anywhere where that location is inside the window -- that is
called its "center neighborhood" -- depending upon the
@b(tryCenterNeighborhood...) options.  If none of these options
are set, the center neighborhood will only be tried if the window
cannot be exactly placed where requested.  These options
additionally try the center neighborhood if exact placement would
succeed, but would close (@b(AutomaticClose)) or shrink
(@b(AutomaticShrink)) other windows or
would cause the window being opened to shrink (@b(Shrink)).

@bx(preferEdgeNeighborhoodToAutomaticCloseOnOpen): off@*
@b(preferEdgeNeighborhoodToAutomaticShrinkOnOpen): off@*
@b(preferEdgeNeighborhoodToShrinkOnOpen): off@*
When a window is being placed at a location, it may be placed
anywhere where the window would overlap with the exact location
-- that is called its "center neighborhood" -- depending upon the
@b(tryEdgeNeighborhood...) options.  If none of these options are
set, the edge neighborhood will only be tried if the window
cannot be exactly placed closer.  These options additionally try
the edge neighborhood if closer placement would succeed, but
would close (@b(AutomaticClose)) or shrink
(@b(AutomaticShrink)) other windows or
would cause the window being opened to shrink (@b(Shrink)).

@bx(preferDesktopToAutomaticCloseOnAutoOpen): on@*
@b(preferDesktopToAutomaticShrinkOnAutoOpen): on@*
@b(preferDesktopToShrinkOnAutoOpen): on@*
When a window is automatically opened, it may express a
preference for being placed at its previous location.  If it
cannot be opened there (or in a neighborhood of it), we
will try to place it anywhere on the desktop.  These options
additionally try the entire desktop if closer placement would
succeed, but would close (@b(AutomaticClose)) or shrink
(@b(AutomaticShrink)) other windows or
would cause the window being opened to shrink (@b(Shrink)).

@bx(preferSlidingToAutomaticCloseOnResize): off@*
@b(preferSlidingToAutomaticShrinkOnResize): off@*
@b(preferSlidingToShrinkOnResize): off@*
When a window is being resized in one direction, another window may be
in its way.  In that case, we try resizing it in the other
direction if @b(trySlidingOnResize) is set.  These options
additionally try sliding if resizing would succeed, but would
close (@b(AutomaticClose)) or shrink
(@b(AutomaticShrink)) other windows or
would cause the window being opened to shrink (@b(Shrink)).

@bx(preferCenterNeighborhoodToAutomaticCloseOnResize): off@*
@b(preferCenterNeighborhoodToAutomaticShrinkOnResize): off@*
@b(preferCenterNeighborhoodToShrinkOnResize): off@*
@b(preferEdgeNeighborhoodToAutomaticCloseOnResize): off@*
@b(preferEdgeNeighborhoodToAutomaticShrinkOnResize): off@*
@b(preferEdgeNeighborhoodToShrinkOnResize): off@*
When a window is resized, it may be moved within its center
or edge neighborhoods if the resize or sliding resize cannot be
done or cause windows to close or shrink.  These options control
when movement within the neighborhood is tried.

@bx(preferUnzoomToClose): on@*
When a zoomed window cannot be opened on an explicit or
repopulating open, unzooming may allow the window to open.
This option determines whether unzooming is allowed in this case.

@bx(prorateVerticallyFirst): on@*
The current prorating algorithm prorates in each dimension
separately.  This option determines whether to prorate vertically
first.

@bx(repopulateStrictly): off@*
Windows are repopulated most recently closed first.  If a closed
window cannot be repopulated, and this option is on, then no
attempt is made to repopulate other windows closed less recently.

@bx(repopulateAutoClosedOnly): on@*
If this option is set, then no attempt is made to repopulate
windows which were explicitly closed on an explicit repopulate.

@bx(requirePreviousPositionOnAutoRepopulate): on@*
@b(requirePreviousPositionOnExplicitRepopulate): off@*
When a window is being repopulated, these options require that it
be placed at its previous position.

@bx(resetZoomMin): off@*
@b(resetZoomMinAllowsDecrease): off@*
@b(resetZoomMinUsesDesire): on@*
If @b(resetZoomMin) is set alone, then zooming a window sets the
zoom_min of the window to be its current (pre-zoom) size.
If @b(resetZoomMinUsesDesire) is set along with it, then the
the zoom min is set to the smaller of the current and
normal desired size.
If @b(resetZoomMinAllowsDecrease) is not set, the zoom min will
not be decreased as a result of this.

@bx(treatMoveLikeRelocate): off@*
If set, then a Move acts just like a Relocate in terms of allowed
placement.  If it is not set, then moving a window requires that
it be placed at its current size (without shrinking) and at the
exact location indicated by the user.

@bx(tryCenterNeighborhoodOnExchange): off@*
Determines whether windows being exchanged can be placed in
each others center neighborhoods, or whether they must be placed at
exactly the same position.

@bx(tryCenterNeighborhoodOnOpen): off@*
@b(tryEdgeNeighborhoodOnOpen): off@*
Determines whether edge and center neighborhoods can be used when
placing a window.

@bx(trySlidingOnResize): off@*
@b(tryCenterNeighborhoodOnResize): off@*
@b(tryEdgeNeighborhoodOnResize): off@*
Determines whether sliding, edge and center neighborhoods can be
used when resizing a window.

@bx(tryRepopulateAgainAfterAutoProrate): on@*
When automatically prorating, we repopulate before prorating.
This options determines whether to try repopulating after
prorating as well (followed, if necessary by re-prorating and
repopulating etc.)

@bx(unzoomTiedListenerIfNecessary): off@*
If an operation would fail, this option determines whether to
unzoom the listener if it has @b(listenerTiedToZoom) set and try the
operation again.
@end(itemize)

@subsection(Global Semantic Values)

@begin(itemize, font smallbodyfont)
@b(absMinWidth): 38@*
@b(absMinHeight): 34@*
The absolute minimum size of a window (including header and border).

@bx(gravity): 12@*
The number of pixels within which gravity operates

@bx(iconPlacement): 1@*
Where icons should be placed within the icon area (or within the root
if no icon area is used):
@begin(format, group, font smallbodyfont)
    0: In no particular place
    1: Across the Top
    2: Across the Bottom
    3: Along the Left Side
    4: Along the Right Side
@end(format)

@begin(multiple)
@b(secondaryIconPlacement): 3@*
Where icons should be placed within the region determined by
@b(iconPlacement).
@begin(format, group, font smallbodyfont)
    0: In no special place
    1: At the top (for Left & Right @b(iconPlacement))
    2: At the bottom (for Left & Right @b(iconPlacement))
    3: At the left (for Top & Bottom @b(iconPlacement))
    4: At the right (for Top & Bottom @b(iconPlacement))
    5: In the middle
@end(Format)
@end(multiple)

@begin(multiple)
@b(neighborhoodShrinkFactor): 50@*
A factor by which the window of a neighborhood is shrunk relative
to the window size.  Expressed as a percent from 0 to 100.
The higher the shrink factor, the smaller the neighborhood for large
windows.

If a window has width w, the @b(neighborhoodShrinkFactor) is 100*f,
and the desktop width is d then the width of the side border of
the neighborhood surrounding the window (on each side)
@begin(Format, group, font smallbodyfont)
    for a center neighborhood is
        w * ( d - (f * w) ) / (2 * d)
    and for an edge neighborhood is
        w * ( d - (f * w) ) / d
@end(format)
And similarly for the length.
Consider a window whose width is half that of the desktop.
With a @b(neighborhoodShrinkFactor) of 0, the border for a center
neighborhood is 1/4 of the desktop width.  For a factor of 50,
the border is 3/16 of the desktop width.  For a factor of 100,
the border is just 1/8 of the desktop width.
@end(multiple)
@end(itemize)

@subsection(Global Interface Options)

@begin(itemize, font smallbodyfont)
@b(acceptNonListenerInBody): on@*
@b(acceptNonListenerInBorder): off@*
@b(acceptNonListenerInGadget): off@*
@b(acceptNonListenerInHeader): on@*
Determines whether keyboard input will be passed to a client
if the pointer is in the named region, and the window is not
the listener.

@bx(autoPlaceOnIconOpen): off@*
If on, a single click in an icon automatically places the opened
window.  If off, a double click is required, and a single click
permits manual placement.

@bx(autoPlaceOnMenuOpen): off@*
If on, selecting a closed window from the menu of closed windows
automatically places it.  If off, the window must be manually
placed.

@bx(autoPlaceOnUnsizedOpen): on@*
If off, and a size has not been provided for a window via a hint, a
preference, or the layout file, then manual placement is required when it
is initially opened.

@bx(buttonMakesListenerInBody): on@*
@b(buttonMakesListenerInHeader): on@*
Determines whether clicking a mouse button in the named region
makes the window the listener when @b(focusFollowsPointer) is on.
If it is not on, clicking makes the window the listener only if the
corresponding @b(keyMakesListener...) is on as well; otherwise it is used
for temporarily typing without changing the listener if the corresponding
@b(acceptNonListener...) is on as well.

@bx(centerPointerOnMove): on@*
@b(centerPointerOnRelocate): on@*
Determines whether to move the pointer to the middle of the window
when moving or relocating it, or to leave it where it is.

@bx(closeInHeader): off@*
@b(closeInCornerBorder): off@*
@b(closeInSideBorder): off@*
@b(closeInMoveGadget): on@*
@b(closeInZoomGadget): on@*
Determines whether the appropriate mouse clicks in the named
regions cause the window to close.

@bx(desireInHeader): off@*
@b(desireInCornerBorder): off@*
@b(desireInSideBorder): off@*
@b(desireInMoveGadget): off@*
@b(desireInZoomGadget): on@*
Determines whether the appropriate mouse clicks in the named
regions cause the window to grow to its desired size.

@bx(distinguishCornerBorders): on@*
@b(distinguishCornerBordersByInverse): on@*
Determines whether the corner borders are distinguished, and if
so, whether by drawing an outline, or by inverting it.

@bx(drawXOnMove): on@*
@b(drawXOnOpen): on@*
@b(drawXOnResize): on@*
Determines whether an X is drawn along with the window outline
when tracking the named operations

@bx(enlargeInHeader): off@*
@b(enlargeInCornerBorder): off@*
@b(enlargeInSideBorder): off@*
@b(enlargeInMoveGadget): off@*
@b(enlargeInZoomGadget): on@*
Determines whether the appropriate mouse clicks in the named
regions cause the window to grow to its maximum size.

@bx(exchangeInHeader): off@*
@b(exchangeInCornerBorder): on@*
@b(exchangeInSideBorder): off@*
@b(exchangeInMoveGadget): on@*
@b(exchangeInZoomGadget): off@*
@b(exchangeInIcon): on@*
Determines whether the appropriate mouse clicks in the named
regions initiate the Exchange operation.

@bx(includeBackgroundMenuInWindowMenu): on@*
Determines whether each window menu has the main window manager
menu as a submenu.

@bx(keyMakesListenerInBody): on@*
@b(keyMakesListenerInBorder): off@*
@b(keyMakesListenerInGadget): off@*
@b(keyMakesListenerInHeader): off@*
Determines whether typing a key with the pointer in the named
region causes the window to become the listener.

@bx(focusFollowsPointer): on@*
If on, the focus is real-estate driven.  If off, the click-to-type
model is used.

@bx(managerMenuInHeader): on@*
@b(managerMenuInCornerBorder): on@*
@b(managerMenuInSideBorder): on@*
@b(managerMenuInMoveGadget): off@*
@b(managerMenuInZoomGadget): off@*
@b(managerMenuInIcon): on@*
Determines whether the appropriate mouse clicks in the named
regions bring up a window menu.

@bx(middleMenu): off@*
If on, then the role of the middle and right buttons in the
default interface are switched. (Horrible Hack!)

@bx(moveInHeader): off@*
@b(moveInCornerBorder): on@*
@b(moveInSideBorder): on@*
@b(moveInMoveGadget): on@*
@b(moveInZoomGadget): off@*
@b(moveInIcon): on@*
Determines whether the appropriate mouse clicks in the named
regions initiate the Move operation.

@bx(placePointerInBodyInsteadOfGadget): on@*
If on, then the following options place the pointer in the body
just below the move gadget rather in the move gadget itself.

@bx(placePointerInGadgetAfterClientAutoOpen): off@*
@b(placePointerInGadgetAfterUserAutoOpen): on@*
@b(placePointerInGadgetAfterManualOpen): on@*
If on, then the pointer is placed in the window's move gadget
after the window is opened (1) by the client and placed
automatically, (2) by the user and placed automatically,
(3) by the user and placed manually.  If off, the pointer stays
where it is.

@bx(placePointerInGadgetAfterExchange): on@*
@b(placePointerInGadgetAfterMove): on@*
If on, then the pointer is placed in the window's move gadget
after the window is exchanged, moved or relocated.

@bx(placePointerInBodyInsteadOfBorder): off@*
If on, then the following option place the pointer in the body
just inside the border rather in the border itself.

@b(placePointerInBorderAfterResize): on@*
If on, then the pointer is placed in the window's border
after the window is resized.

@bx(placePointerInIconAfterClose): off@*
If on, then after explicitly closing a window, the pointer is
placed in its icon.

@bx(placePointerBackAfterMenuOperation): on@*
If on, then completing a menu operation that doesn't involve
tracking, the pointer is moved back to its position when the
menu was first raised.

@bx(placePointerBackOnCancel): on@*
If on, then after cancelling an operation, the pointer is moved
back to its position when the operation was initiated.

@bx(redrawInHeader): off@*
@b(redrawInCornerBorder): on@*
@b(redrawInSideBorder): on@*
@b(redrawInMoveGadget): on@*
@b(redrawInZoomGadget): on@*
@b(redrawInIcon): on@*
Determines whether the appropriate mouse clicks in the named
regions redraw the window.

@bx(relocateInHeader): off@*
@b(relocateInCornerBorder): off@*
@b(relocateInSideBorder): off@*
@b(relocateInMoveGadget): on@*
@b(relocateInZoomGadget): off@*
Determines whether the appropriate mouse clicks in the named
regions initiate the Relocate operation.

@bx(resizeInHeader): off@*
@b(resizeInCornerBorder): on@*
@b(resizeInSideBorder): on@*
@b(resizeInMoveGadget): off@*
@b(resizeInZoomGadget): off@*
Determines whether the appropriate mouse clicks in the named
regions initiate the Resize operation.

@bx(showListenerInBorders): off@*
@b(showListenerInHeader): on@*
@b(showFocusInBorders): on@*
@b(showFocusInHeader): off@*
When a window becomes the listener or focus, either the header or
border can be reversed.

@bx(useCornerBorders): on@*
Determines whether the corner window borders are active --
essentially controls whether corner resizing is allowed without
the menu.

@bx(useIconArea): off@*
If on, then the @b(iconArea...) options specify a preferred area
for icons.

@bx(useIcons): on@*
If on, closed windows are represented by icons.

@bx(useRtlIcon): on@*
If on and icons are in use, then a special RTL icon is visible
with special meanings for window clicks.

@bx(zoomInHeader): off@*
@b(zoomInCornerBorder): off@*
@b(zoomInSideBorder): off@*
@b(zoomInMoveGadget): off@*
@b(zoomInZoomGadget): on@*
Determines whether the appropriate mouse clicks in the named
regions zoom and unzoom the window.
@end(itemize)

@subsection(Global Interface Values)

@begin(itemize, font smallbodyfont)
@b(borderSize): 5@*
@b(outerBorderLinewidth): 2@*
@b(innerBorderLinewidth): 1@*
The size of window borders, and the width of the inner and outer
lines of the border.

@bx(gadgetWidth): 12@*
The width of the gadgets

@bx(iconAreaTop)@*
@b(iconAreaBottom)@*
@b(iconAreaLeft)@*
@b(iconAreaRight)@*
If @b(useIconArea) is set, these specify the preferred area of the
root in which icons are to be placed.  There are no default values.

@end(itemize)

@subsection(Window Semantic Options)

@begin(itemize, font smallbodyfont)
@b(aggressivelyRepopulate): off@*
Determines whether this window is to be aggressively repopulated
if the global option @b(allowAggressiveRepopulation) allows it.

@bx(allowShrinkOnUnzoom): on@*
@b(allowShrinkOnAutoUnzoom): on@*
Determines whether the window is allowed to be shrunk when it is
unzoomed in order to allow adjacent windows to be enlarged back
to their desired size or to allow windows to be repopulated.

@bx(allowZoomClose): on@*
Determines whether other windows are allowed to be closed in
order to allow this window to be zoomed.

@bx(autoOpenOnCreate): on@*
Determines whether the window is to be opened automatically when
it is created. Used if @c(WM_HINTS) indicates DontCareState (or if
@b(initial_state) is not provided) and if there is no matching layout.

@bx(autoResatisfyOnResetMinmax): on@*
When a client resets the client minimum or maximum size,
determines whether or not the window should change size
immediately if necessary, or wait until the window is operated
upon.

@bx(considerForRepopulation): on@*
Determines whether the window is to be considered for
repopulation

@bx(enforceClientMinimums): on@*
@b(enforceClientMaximums): off@*
Determines whether minimums and maximums set by the client are to
be enforced or not.

@bx(expensiveToRedraw): off@*
The system tries to avoid having side effects upon windows
which are expensive to redraw

@bx(fixedSize): off@*
@b(fixedHeight): off@*
@b(fixedWidth): off@*
If a window has its width or height (size means both width and
height) fixed, then that dimension cannot be changed as a side
effect of an operation on another window, and the window cannot
be automatically shrunk in that dimension when it is being placed
or resized.

@bx(fixedCompletely): off@*
A window which is fixed completely has all of its edges fixed.

@bx(forceShrinkOnUnzoom): on@*
@b(forceShrinkOnAutoUnzoom): off@*
When a window is unzoomed, determines whether it is to be shrunk
to its normal desired size. 

@bx(ignoreInitialPositionHints): off@*
@b(ignoreInitialSizeHints): off@*
@b(ignorePositionHints): off@*
@b(ignoreSizeHints): off@*
Determines whether to use the size and positions hints provided
in @c(WM_NORMAL_HINTS).

@bx(listenerTiedToZoom): off@*
A window with listener tied to zoom is automatically zoomed when it
becomes the listener, and is automatically unzoomed when it loses
the listener.

@bx(noteListener): on@*
Open windows are ordered in terms of most recent use for a
variety of reasons.  A window is "used" when it is opened.
This option determines whether becoming the listener constitutes "use" as
well.

@bx(preferPreviousIconPosition): on@*
When the icon is placed, prefer placing it as near to its
previous location as possible within the constraints of
the icon area and @b(iconPlacement).

@bx(requirePreviousIconPosition): off@*
When the icon is placed, try first to place it at its previous icon
position, even if that is not within the constraints of
the icon area and @b(iconPlacement).

@bx(preferPreviousPosition): on@*
@b(requirePreviousPosition): off@*
When a window is automatically placed, determines whether it
prefers or requires to be reopened at its previous position.

@bx(requireManualClose): off@*
If on, then the window may not be closed as a side effect of an
operation on another window.

@bx(saveInLayout): on@*
Determines whether an entry for this window is saved in
@b(.rtl.layout) when a Save Layout operation is done.

@bx(zoomFullExplicit): off@*
@b(zoomFullHeight): off@*
@b(zoomFullWidth): off@*
Determines whether zooming always causes the window
to grow to the full width and or height of the desktop.

@bx(zoomOnOpen): off@*
If set, then automatically zooms the window each time it is
opened.

@bx(zoomTiedToDesire): off@*
When set, zoom a window to its normal desired size, rather than to its
zoom desired size.

@end(itemize)

@subsection(Window Semantic Values)

These options initialize window sizes.  All sizes include
space for borders and headers.

@begin(itemize, font smallbodyfont)
@bx(normalDesiredWidth)@*
@b(normalDesiredHeight)@*
Specifies the initial desired window size.  Overrides
the initial window size specified by the client.

@b(zoomDesiredWidth)@*
@b(zoomDesiredHeight)@*
Specifies the desired size when the window is
first zoomed.

@bx(clientMinWidth)@*
@b(clientMinHeight)@*
@b(clientMaxWidth)@*
@b(clientMaxHeight)@*
Overrides the minimum and maxmum sizes specified by the client.

@bx(userNormalMinWidth)@*
@b(userNormalMinHeight)@*
@b(userZoomMinWidth)@*
@b(userZoomMinHeight)@*
Specifies the initial user minimum size when the window is
normal (unzoomed) and zoomed.

@bx(iconWidth): 64@*
@b(iconHeight): 64@*
Width and height of default icons (produced by RTL
when no pixmap has been provided).
@end(itemize)

@subsection(Window Interface Options)

@begin(itemize, font smallbodyfont)

@bx(acceptButtonInBody): on@*
@b(acceptButtonInHeader): on@*
@b(acceptButtonInIcon): on@*
Determines whether a button press can ever be passed to the
client when the pointer is in the named region.

@bx(acceptKeyInBody): on@*
@b(acceptKeyInHeader): on@*
@b(acceptKeyInGadget): on@*
@b(acceptKeyInBorder, ): on@*
@b(acceptKeyInIcon): on@*
Determines whether a key press can ever be passed to the
client when the pointer is in the named region.

@bx(autoPlaceOnClientOpen): on@*
Determines whether automatic or manual placement is used when the
client opens the window.

@bx(includeResClassInTitle): on@*
@b(includeResClassInIconTitle): on@*
@b(includeResNameInTitle): off@*
@b(includeResNameInIconTitle): off@*
@b(includeNameInTitle): on@*
@b(includeNameInIconTitle): on@*
@b(includeHostInTitle): on@*
@b(includeHostInIconTitle): on@*
Determines whether the manager should include the the res_class,
res_name, the window or icon name, and the host name in the window or
icon title.
But see just below ...

@bx(includeTitleInHeader): on@*
Determines whether the window title should be displayed in the window
header.

@bx(includeTitleInPixmapIcon): off@*
Determine whether the icon title should be drawn on top of the pixmap
icon if one has been supplied by either the client or via the preferences
file.

@bx(useBorders): on@*
@b(useGadgets): on@*
@b(useHeader): on@*
@b(useMoveGadget): on@*
Determines whether the various regions of the window should be
drawn.

@end(itemize)

@subsection(Window Interface Values)

@begin(itemize, font smallbodyfont)
@b(headerHeight): 16@*
The height of the window's header.

@bx(iconResTop): 2@*
@b(iconResBottom): 10@*
@b(iconResLeft): 2@*
@b(iconResRight): 61@*
Determines where the window resource class and resource name appear
in the icon

@bx(iconHostTop): 12@*
@b(iconHostBottom): 20@*
@b(iconHostLeft): 2@*
@b(iconHostRight): 61@*
Determines where the host name appears in the icon.

@bx(iconNameTop): 22@*
@b(iconNameBottom): 61@*
@b(iconNameLeft): 2@*
@b(iconNameRight): 61@*
Determines where the icon name appears in the icon.
@end(itemize)

@subsection(Window Semantic Strings)

@begin(itemize, font smallbodyfont)
@bx(iconPixmapFile)@*
Names a file containing an icon pixmap (in the standard X11 
bitmap format).  Overrides the pixmap provided by the client.

@bx(superClass)@*
The string names a superclass.  The window will inherit all options
from its superclass unless explicitly overridden.
@end(itemize)

@section(Acknowledgements)

Mike Berman, Mark Biggers, and Joe Camaratta have shared
in the design and implementation of major parts of the system.

In addition, Kevin Kelly has worked on automatic
placement and prorating, 
Pete Litwinowicz worked on the original Andrew-based client
interface, and Adam Richter helped with the interface to X11.

@newpage()

@modify(verbatim, font smallBodyFont,
       spacing .8, spread .5, facecode t)

@modify(quotation, font smallBodyFont, justification off,
       spacing .8, spread .5, facecode i, above 0, below 0,
       leftmargin +3, rightmargin 0)

@modify(heading, spacing 1, spread .7)

@define(ttl = text, underline all, font bodyfont)

@begin(heading)
Quick Reference Page
Siemens RTL Tiled Window Manager
Release 5.1 for use with X11R3

3 Button Mouse
@end(heading)

@begin(verbatim, columns 2, columnMargin 1, boxed)
@begin(Verbatim, group)
@ttl(Borders)

            LEFT   -- @r(Resize)
      SHIFT LEFT   -- @r(Resize*)

            MIDDLE -- @r(Move)
      SHIFT MIDDLE -- @r(Move*)

            RIGHT  -- @r(Window Menu)

@begin(Quotation)
Side borders constrain move and resize
@end(Quotation)
@end(Verbatim)
@begin(Verbatim, group)
@ttl(Zoom Gadget)

            LEFT   -- @r(Desire)
      SHIFT LEFT   -- @r(Zoom / Unzoom)
       CTRL LEFT   -- @r(Enlarge)
 CTRL SHIFT LEFT   -- @r(Redraw)

 CTRL SHIFT MIDDLE -- @r(Redraw)

 CTRL SHIFT RIGHT  -- @r(Close)

@end(verbatim)
@begin(Verbatim, group)
@ttl(Move Gadget)

 CTRL SHIFT LEFT   -- @r(Redraw)

            MIDDLE -- @r(Relocate)
      SHIFT MIDDLE -- @r(Move)
       CTRL MIDDLE -- @r(Exchange)
 CTRL SHIFT MIDDLE -- @r(Redraw)

 CTRL SHIFT RIGHT  -- @r(Close)

@end(verbatim)
@begin(Verbatim, group)
@ttl(Header)

            MIDDLE -- @r(Move)
      SHIFT MIDDLE -- @r(Move*)

            RIGHT  -- @r(Window Menu)

@begin(Quotation)
All other combinations are transmitted to the client
@end(Quotation)

@begin(Quotation)
@center(*  Toggles gravity during operation)
@end(Quotation)
@end(verbatim)
@newcolumn()
@begin(Verbatim, group)
@ttl(Icon)

            LEFT   -- @r(Open)
 CTRL SHIFT LEFT   -- @r(Redraw)

            MIDDLE -- @r(Move)
      SHIFT MIDDLE -- @r(Move*)
       CTRL MIDDLE -- @r(Exchange)
 CTRL SHIFT MIDDLE -- @r(Redraw)

            RIGHT  -- @r(Icon Menu)
 CTRL SHIFT RIGHT  -- @r(Soft Kill)


@begin(Quotation)
All other combinations are transmitted to the client
@end(Quotation)

@begin(Quotation)
Note: When opening the icon, double clicking automatically places the
window.  A single press or click allows the user to place it manually.
@end(Quotation)
@end(verbatim)
@begin(Verbatim, group)
@ttl(Rtl Icon)

            LEFT   -- @r(Deselect Listener)
 CTRL SHIFT LEFT   -- @r(Redraw All)

            MIDDLE -- @r(Move)
      SHIFT MIDDLE -- @r(Move*)
       CTRL MIDDLE -- @r(Exchange)
 CTRL SHIFT MIDDLE -- @r(Redraw All)

            RIGHT  -- @r(Main Manager Menu)

@begin(Quotation)
All other combinations deselect the listener as well
@end(Quotation)
@end(verbatim)
@begin(Verbatim, group)
@ttl(Background)

            LEFT   -- @r(Deselect Listener)
 CTRL SHIFT LEFT   -- @r(Redraw All)

 CTRL SHIFT MIDDLE -- @r(Redraw All)

            RIGHT  -- @r(Main Manager Menu)

@begin(Quotation)
All other combinations deselect the listener as well
@end(Quotation)
@end(verbatim)
@end(verbatim)

@begin(Quotation)
To cancel an operation,
press the @t(RIGHT) mouse button.

A question mark cursor is a request for confirmation.
Click the @t(LEFT) or @t(MIDDLE) mouse button to confirm,
the @t(RIGHT) mouse button to cancel.
@end(quotation)

@newpage()

@begin(heading)
Quick Reference Page
Siemens RTL Tiled Window Manager
Release 5.1 for use with X11R3

1 Button Mouse
@end(heading)

@begin(verbatim, columns 2, columnMargin 1, boxed)
@begin(Verbatim, group)
@ttl(Borders)

       NONE  -- @r(Resize)
      SHIFT  -- @r(Move)
       CTRL  -- @r(Resize*)
 CTRL SHIFT  -- @r(Redraw)

@begin(Quotation)
*  Toggles gravity during operation
@end(Quotation)

@begin(Quotation)
Side borders constrain move and resize
@end(Quotation)
@end(Verbatim)
@begin(Verbatim, group)
@ttl(Zoom Gadget)

       NONE  -- @r(Desire)
      SHIFT  -- @r(Zoom / Unzoom)
       CTRL  -- @r(Enlarge)
 CTRL SHIFT  -- @r(Close)

@end(verbatim)
@begin(Verbatim, group)
@ttl(Move Gadget)

       NONE  -- @r(Relocate)
      SHIFT  -- @r(Move)
       CTRL  -- @r(Exchange)
 CTRL SHIFT  -- @r(Close)

@end(verbatim)
@begin(Verbatim, group)
@ttl(Header)

       NONE  -- @r(Window Menu)
      SHIFT  -- @r(Move)
       CTRL  -- @r(Sent to client)
 CTRL SHIFT  -- @r(Redraw)

@end(verbatim)
@newcolumn()
@begin(Verbatim, group)
@ttl(Icon)

       NONE  -- @r(Open)
      SHIFT  -- @r(Move)
       CTRL  -- @r(Exchange)
 CTRL SHIFT  -- @r(Icon Menu)

@begin(Quotation)
Note: When opening the icon, double clicking automatically places the
window.  A single press or click allows the user to place it manually.
@end(Quotation)
@end(verbatim)
@begin(Verbatim, group)
@ttl(Rtl Icon)

       NONE  -- @r(Main Manager Menu)
      SHIFT  -- @r(Move)
       CTRL  -- @r(Exchange)
 CTRL SHIFT  -- @r(Main Manager Menu)

@end(verbatim)
@begin(Verbatim, group)
@ttl(Background)

       NONE  -- @r(Main Manager Menu)
      SHIFT  -- @r(Deselect Listener)
       CTRL  -- @r(Deselect Listener)
 CTRL SHIFT  -- @r(Redraw All)

@end(verbatim)
@end(verbatim)

@begin(Quotation)
To cancel an operation,
hold @t(CTRL) and @t(SHIFT) while releasing or clicking the mouse
button.

A question mark cursor is a request for confirmation.
Click the mouse button to confirm,
hold @t(CTRL) and @t(SHIFT) and click the mouse button
to cancel.
@end(quotation)

