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
Tutorial:
Initial Setup for Using the
Siemens RTL
Tiled Window Manager

Release 5
for use with X11R2
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

17 June 1988
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

@begin(Abstract)
This tutorial describes how to become an initial user of the Siemens @b(rtl)
Tiled Window Manager.
It assumes that you already know how to start the X11R2@foot<
X11 and the X Window System are trademarks of MIT> server
and are familiar with X11 applications.

The tutorial explains how to set up customization files, how to set up
your initial window layout along with per-window options, and how to save
that layout.
Once the layout is saved, it will automatically be recreated when you
start up the system in the future.

A @b(Quick Reference Page) describing the actions associated with mouse
buttons, and a @b(Manual) are also available.
@end(Abstract)

Except for menus and transient pop-up windows,
the @b(rtl) window manager does not permit windows to overlap.
Because of this, @b(rtl) has features and
constraints not found in other window managers.
Getting your environment set up so that you can use @b(rtl) effectively
takes some extra time.  IT IS WORTH IT!

@section(Preparation)

First, make sure that you have the following two files in your
home directory:

@begin(itemize)
@b(.rtl.tools) -- initializes a menu from which you can easily
start up new applications once @b(rtl) is running.

@b(.rtl.preferences) -- specifies global and per-window-class options
that control both the semantics and the appearance of @b(rtl).
@end(itemize)

Find out where the @b(rtl) distribution is located on your filesystem.
In the @b(custom) subdirectory, you will find example
@b(.rtl.tools) and @b(.rtl.preferences) files that we use at our lab.

@begin(quotation)
@b(NOTE:)
If you don't use a @b(.rtl.preferences) file, defaults are chosen that
provide a fairly conservative interface.  The @b(.rtl.preferences) file in
the @b(custom) subdirectory allows windows to be automatically moved
and resized a bit more easily and tailors the interface specifically
for individual applications.  The last section of the manual describes the
options in detail.
@end(quotation)

@begin(quotation)
@b(NOTE:)
The @b(.rtl.preferences) file in the @b(custom) subdirectory has a number
of "@b(iconPixmapFile)" entries.  These designate a file containing
a bitmap to be used for the corresponding application's icon.
The bitmap files are stored in the @b(custom) subdirectory.  Make
sure that the path to the @b(custom) subdirectory is correct for
the "@b(iconPixmapFile)" entries.
@end(quotation)

The Customization section of the manual has information about additional ways
you can customize your environment.

@section(Starting up RTL and your Applications)

Once your X server is running, you can start up @b(rtl).
If X clients are already mapped, @b(rtl) will tile them.

Now, start up the remaining applications you typically want
running.

Some applications request to be initially iconized
via their @c(WM_HINTS) property,@foot<Each X11 window can have
various "properties" associated with it.  Some of these
properties are set by clients to communicate with the window manager.
See section 9.1 of the Xlib manual if you want more information.>
and @b(rtl) will do so.  Otherwise, the window is initially
mapped.

By default, the option @b(autoPlaceOnClientOpen) is on, which means that
@b(rtl) will automatically find a place for the window.

If you have set it off in your preference file, you may be asked to
place it automatically, depending upon whether the client has specified
an initial size and position (in the @c(WM_NORMAL_HINTS) property).

@begin(itemize)
If the client provided both a size and position hint, the window
will be placed automatically, though because of tiling, not necessarily
at exactly the size or position requested.

Otherwise, you will asked to determine
both its size and position.  The cursor will change to a dotted box.
Pressing or clicking the left mouse button designates the top-left
corner.  Releasing or re-clicking designates the bottom-right corner.
Pressing the right mouse button iconizes the window instead.
(For a one-button mouse, hold CTRL and SHIFT and click to iconize).
@end(itemize)

Some clients set bogus initial window positions (usually <0,0>), and are
automatically placed by @b(rtl) even when that is not appropriate.
You can tell @b(rtl) to ignore the initial position set by the
client by setting the option @b(ignoreInitialPositionHints) for those
clients.

If you do not like the layout, you can change it by resizing or moving
windows around.  See the @b(Quick Reference Page) which explains how to
use the mouse buttons, or see the @b(Manual) for more details.

@section(Client Minimum and Maximum Size)

Many clients set a reasonable @b(client minimum size) via the
@c(WM_NORMAL_HINTS) property.  Some do not.
You can tell by trying to resize the window.
By default, the window manager will not allow the window to be
made smaller than its client minimum size.

If the size set by the client seems too small, you can
override it by setting "@b(clientMinimumWidth)" and
"@b(clientMinimumHeight)" in your preferences file.
If you reread your preferences file (via the "@b(Read Profile)" entry
in the manager menu), these will affect future applications
of the same class.

You can also set "@b(clientMaximumWidth)" and "@b(clientMaximumHeight)"
to override the client's maximum size hint.

@section(User Minimum Size)

When a window is enlarged or opened, an adjacent window may be
shrunk automatically by @b(rtl).  A window is never shrunk
any smaller than its @b(user minimum size).
The wm will not let you make the @b(user minimum size) smaller
than the @b(client minimum size).

You may set a window's user minimum size by selecting
"@b(Set Size)" from a window's menu, and then selecting
"@b(Normal Min)" from the submenu.  You can then press or click
on a side or corner, and resize to indicate the minimum size.

You can set the user minimum size on a per-window-class basis
by setting "@b(userNormalMinWidth)" and "@b(userNormalMinHeight)"
in your preferences files, but these will not be applied to
existing windows.

If you plan to zoom the window, you can set the zoom minimum size
similarly.

@section(Per Window Options)

By selecting "@b(Options)" from a window menu, a submenu
indicates various per-window options that you can select:

@begin(itemize)

@b2(Locked Open) -- prevents the window from being automatically closed.

@b2(Fixed Width) -- prevents the window's width from being automatically
changed.

@b2(Fixed Height) -- prevents the window's height from being
automatically changed.

@b2(Fixed Edges) -- prevents the window from being moved or resized
automatically.

@b2(Listener Tied To Zoom) -- Zooms (unzooms) the window when it becomes
(no longer is) the listener.

@end(Itemize)

These options can be set on a per-window-class basis by setting the
corresponding options in the preferences file.
See the Customization section of the Manual.

@section(Save the Layout)

Once you have the windows where you want them, have
set the minimum size of your windows, and have determined their
per-window options, you are ready to save the layout.

Select "@b(Save Layout)" from the manager menu.  A question mark
cursor asks for confirmation.  Click with the left button to confirm,
with the right button to cancel.
(For a one-button mouse, hold CTRL and SHIFT and click to cancel).

Selecting "@b(Save Layout)" saves information about all open and closed
windows and their icons in @b(.rtl.layout) file in your home directory.

@section(Build a Startup File)

Now that you know which applications you typically like running, you can
build a shell file that starts them up.

If you name the shell file @b(.rtl.startup), and put in your
home directory, it will automatically get executed, if you
invoke @b(rtl) with the "-s" flag

@section(Restarting)

When you subsequently start @b(rtl), the @b(.rtl.layout) file will be
read in and will be used to match up applications that have already
started or which you will start up in the future.

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

When the layout has been finished, in whatever way, "@b(Save
Layout)" appears in the place of "@b(Finish Layout)", allowing the user
to change the layout, and resave it, overwriting the old layout file.

Enjoy!
