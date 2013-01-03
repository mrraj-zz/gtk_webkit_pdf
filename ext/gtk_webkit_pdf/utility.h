#ifndef utility_h__
#define utility_h__
#include<ruby.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <stdlib.h>

  typedef struct {
    WebKitWebView *webkit_webview;
    char *export_filename;
    char *webkit_url;
  
    WebKitWebFrame *webkit_webframe;
    GtkPrintSettings *gtk_print_settings;
    GtkPrintOperation *gtk_print_operation;
    GtkPrintOperationResult gtk_print_operation_result;
    VALUE print_status;
  } webkit_wrapper;

  extern void webkit_load_finished(WebKitWebView *webView, WebKitWebFrame *webkitwebframe, webkit_wrapper *webkit);
  extern void begin_print();
  extern void draw_page();
  
  extern void initialize_webkit(webkit_wrapper *webkit);
  extern void free_webkit(void *void_webkit);
  extern void activate_webkit(webkit_wrapper *webkit);
  extern void activate_printer(webkit_wrapper *webkit);
  extern void set_printer_configurations(webkit_wrapper *webkit);
  extern void actual_print_operation(webkit_wrapper *webkit);
#endif
