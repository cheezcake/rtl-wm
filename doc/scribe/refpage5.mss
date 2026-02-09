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

3 Button Mouse
@end(heading)

@begin(verbatim, columns 2, columnMargin 1.5, boxed)
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
