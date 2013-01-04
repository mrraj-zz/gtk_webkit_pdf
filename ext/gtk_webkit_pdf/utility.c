#include <utility.h>

void free_webkit(void *void_webkit) {
  webkit_wrapper *webkit = void_webkit;
  free(webkit);
}

void mark_webkit_printer(void *void_webkit) {
  webkit_wrapper *webkit = void_webkit;
  if(webkit) {
    rb_gc_mark(webkit -> data_printer);
    rb_gc_mark(webkit -> print_status);
  }
}

void activate_gtk_webkit(VALUE self) {
  WEBKIT_PTR(self);
  webkit -> data_printer = Qnil;
  webkit -> webkit_webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
  webkit_web_view_load_uri(webkit -> webkit_webview, webkit -> webkit_url); 
  g_signal_connect(webkit -> webkit_webview, "load-finished", G_CALLBACK(webkit_load_finished), (void *)self);
}

void webkit_load_finished(WebKitWebView *webView, WebKitWebFrame *webkitwebframe, void *self) {
  VALUE argv[3];
  WEBKIT_PTR(CAST_TO_VALUE(self));
  webkit -> webkit_webframe = webkit_web_view_get_main_frame(webkit -> webkit_webview);
  
  webkit -> data_printer = rb_funcall(cPrinter, rb_intern("new"), 0);
  argv[0] = CAST_TO_VALUE(self);
  argv[1] = C_TO_RUBY_STR(webkit -> dir_path);
  argv[2] = C_TO_RUBY_STR(webkit -> pdf_filename);
  webkit -> print_status = rb_funcall2(webkit -> data_printer, rb_intern("export_to_pdf"), 3, argv);
  gtk_main_quit();
}

void set_pdf_configurations(VALUE self, VALUE dir_path, VALUE pdf_filename) {
  WEBKIT_PTR(self);
  webkit -> dir_path = StringValuePtr(dir_path);
  webkit -> pdf_filename = StringValuePtr(pdf_filename);
}
