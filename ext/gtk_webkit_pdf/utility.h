#ifndef utility_h__
#define utility_h__
#include<ruby.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <stdlib.h>

  typedef struct {
    WebKitWebView *webkit_webview;
    WebKitWebFrame *webkit_webframe;

    char *webkit_url;
    char *dir_path;
    char *pdf_filename;
    VALUE print_status;
    VALUE data_printer;
  } webkit_wrapper;

  extern void webkit_load_finished(WebKitWebView *webView, WebKitWebFrame *webkitwebframe, void *self);
  
  extern void free_webkit(void *void_webkit);
  extern void mark_webkit_printer(void *void_webkit);
  extern void activate_gtk_webkit(VALUE self);
  extern void set_pdf_configurations(VALUE self, VALUE dir_path, VALUE pdf_filename);

  extern void init_printer();
  extern VALUE cPrinter;

  #define WEBKIT_PTR(self) webkit_wrapper *webkit; \
    Data_Get_Struct(self, webkit_wrapper, webkit);

  #define C_TO_RUBY_STR(str) rb_str_new2(str)

  #define RUBY_TO_C_STR(str) StringValuePtr(str)
  
  #define CAST_TO_VALUE(value) (VALUE)value

  #define STR_CON_CAT(dir, name) pdf_path = malloc(strlen(RUBY_TO_C_STR(dir)) + strlen(RUBY_TO_C_STR(name)) + 1); \
    if(pdf_path != NULL) { \
      strcpy(pdf_path, RUBY_TO_C_STR(dir)); \
      strcpy(&pdf_path[strlen(RUBY_TO_C_STR(dir))], RUBY_TO_C_STR(name)); \
    } \

#endif
