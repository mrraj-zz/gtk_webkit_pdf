require 'mkmf'

$CFLAGS << " -I /usr/include/gtk-2.0/ -I /usr/include/glib-2.0/ -Wall -Werror -fpic -I /usr/lib/i386-linux-gnu/glib-2.0/include/ -I /usr/include/cairo/ -I /usr/include/pango-1.0/ -I /usr/lib/i386-linux-gnu/gtk-2.0/include -I /usr/include/gdk-pixbuf-2.0/ -I /usr/include/atk-1.0/ -I /usr/include/webkitgtk-1.0/ -I /usr/include/libsoup-2.4/"

$LIBS << " -L /usr/lib/i386-linux-gnu/ -lgtk-3 -L /usr/lib/webkitgtk-1.0-0/ -lwebkitgtk-3.0"
create_makefile("gtk_webkit_pdf/webkit")
