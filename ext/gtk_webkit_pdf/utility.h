#ifndef utility_h__
#define utility_h__
#include<ruby.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <stdlib.h>

  typedef struct {
    WebKitWebView *webkit_webview;
    WebKitWebFrame *webkit_webframe;

    VALUE printer;
  } webkit_wrapper;

  extern void webkit_load_finished(WebKitWebView *webView, WebKitWebFrame *webkitwebframe, void *self);
  
  extern void free_webkit(void *void_webkit);
  extern void mark_webkit_printer(void *void_webkit);

  extern void init_printer();
  extern VALUE cPrinter;

  #define WEBKIT_PTR(self) webkit_wrapper *webkit; \
    Data_Get_Struct(self, webkit_wrapper, webkit);

  #define C_TO_RUBY_STR(str) rb_str_new2(str)

  #define RUBY_TO_C_STR(str) StringValuePtr(str)

#endif
