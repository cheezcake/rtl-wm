@device(imagen300)

@style(Spacing .8, Spread .5, Indent 0)

@modify(verbatim, font smallBodyFont,
       spacing .8, spread .5, facecode t)

@modify(quotation, font smallBodyFont, justification off,
       spacing .8, spread .5, facecode i, above 0, below 0,
       leftmargin +3, rightmargin 0)

@modify(heading, spacing 1, spread .7)

@define(ttl = text, underline all, font bodyfont)

@make(article)

@begin(heading)
Quick Reference Page
Siemens RTL Tiled Window Manager
Release 5 for use with X11R2

1 Button Mouse
@end(heading)

@begin(verbatim, columns 2, columnMargin 1.5, boxed)
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

