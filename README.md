# rtl-wm

Siemens RTL tiled window manager from the X11R3 contrib tape. Patched for
gcc.

Details from Christoph Lohmann from 19 Dec 2011:

Greetings comrades,

I am proud to announce, that we (Paul Onyschuk an I) got the
Siemens RTL Tiled Window Manager to work on modern systems. It
was one of the early tiled window managers and has some ideas
of dwm, but is something different. Just try it out.

At [0] is the source of the patched rtl, to compile with
modern gcc versions. You will need liboldX[1] for the compila-
tion.

Instructions:

        % tar -xzf rtl-5.2-working.tar.gz
        % cd rtl
        % mxmkmf && make && make install
        # will install to /usr/bin
        % cat > ~/.rtl.tools
        XTerm
        <Tab>xterm
        <Ctrl+D>
        % rtl

Now use the right mouse button to use the menus. The .rtl.tools
file is needed, so you are able to at least start an xterm from
within rtl.

There seem to many yet untouched features in rtl, which are doc-
umented in the doc/ directory.

-- 
There's a video from Siemens about it which is on YouTube:
https://www.youtube.com/watch?v=IOxIUeroIVQ
