#include <utility.h>

void free_webkit(void *void_webkit) {
  webkit_wrapper *webkit = void_webkit;
  free(webkit);
}

void mark_webkit_printer(void *void_webkit) {
  webkit_wrapper *webkit = void_webkit;
  if(webkit) {
    rb_gc_mark(webkit -> printer);
  }
}

void webkit_load_finished(WebKitWebView *webView, WebKitWebFrame *webkitwebframe, void *self) {
  VALUE argv[1], printer;
  WEBKIT_PTR((VALUE)self);
  webkit -> webkit_webframe = webkit_web_view_get_main_frame(webkit -> webkit_webview);
  
  argv[0] = (VALUE)self;
  printer = rb_funcall(cPrinter, rb_intern("new"), 0, 0);
  webkit -> printer = rb_funcall2(printer, rb_intern("webkit_webframe_to_pdf"), 1, argv);
  gtk_main_quit();
}
