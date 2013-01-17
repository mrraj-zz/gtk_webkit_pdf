require 'mkmf'

dir_config('gtk', '/usr/include/gtk-3.0', '/usr/lib/i386-linux-gnu/')
dir_config('gtklinux', '/usr/lib/i386-linux-gnu/gtk-2.0/include', '')
dir_config('glib', '/usr/include/glib-2.0', '')

dir_config('gliblinux', '/usr/lib/i386-linux-gnu/glib-2.0/include/', '')
dir_config('cairo', '/usr/include/cairo', '')
dir_config('gdkpixbuf', '/usr/include/gdk-pixbuf-2.0/', '')

dir_config('atk', '/usr/include/atk-1.0', '/usr/lib')
dir_config('webkitgtk', '/usr/include/webkitgtk-1.0', '/usr/lib/webkitgtk-1.0-0')
dir_config('libsoup', '/usr/include/libsoup-2.4/', '')

dir_config('pango', '/usr/include/pango-1.0', '')

have_header('gtk/gtk.h')
have_header('webkit/webkit.h')

have_library('gtk-3')
have_library('webkitgtk-3.0')

$CFLAGS << ' -Wall' unless $CFLAGS.split.include?('-Wall')
$CFLAGS << ' -Werror' unless $CFLAGS.split.include?('-Werror')
$CFLAGS << ' -fpic' unless $CFLAGS.split.include?('-fpic')

create_makefile("gtk_webkit_pdf/webkit")
