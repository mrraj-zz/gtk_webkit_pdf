#include <utility.h>

void free_webkit(void *void_webkit) {
  webkit_wrapper *webkit = void_webkit;
  free(webkit);
}

void initialize_webkit(webkit_wrapper *webkit) {
  webkit -> print_status = Qfalse;
  webkit -> gtk_print_settings = NULL;
  webkit -> webkit_webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
}

void activate_webkit(webkit_wrapper *webkit) {
  webkit_web_view_load_uri(webkit -> webkit_webview, webkit -> webkit_url); 
  g_signal_connect(webkit -> webkit_webview, "load-finished", G_CALLBACK(webkit_load_finished), webkit);
}

void webkit_load_finished(WebKitWebView *webView, WebKitWebFrame *webkitwebframe, webkit_wrapper *webkit) {
  activate_printer(webkit);
  gtk_print_operation_set_export_filename(webkit -> gtk_print_operation, webkit -> export_filename);
  webkit -> gtk_print_operation_result = webkit_web_frame_print_full(webkit -> webkit_webframe,
                                         webkit -> gtk_print_operation, GTK_PRINT_OPERATION_ACTION_EXPORT, NULL);
  actual_print_operation(webkit);
}

void activate_printer(webkit_wrapper *webkit) {
  webkit -> webkit_webframe = webkit_web_view_get_main_frame(webkit -> webkit_webview);
  set_printer_configurations(webkit);
}

void set_printer_configurations(webkit_wrapper *webkit) {
  webkit -> gtk_print_operation = gtk_print_operation_new();
  if(webkit -> gtk_print_settings != NULL)
    gtk_print_operation_set_print_settings(webkit -> gtk_print_operation, webkit -> gtk_print_settings);
  g_signal_connect(webkit -> gtk_print_operation, "begin_print", G_CALLBACK(begin_print), NULL);
  g_signal_connect(webkit -> gtk_print_operation, "draw_page", G_CALLBACK(draw_page), NULL);
}

void actual_print_operation(webkit_wrapper *webkit) {
  if(webkit -> gtk_print_operation_result == GTK_PRINT_OPERATION_RESULT_APPLY) {
    g_object_unref(webkit -> gtk_print_settings);
    webkit -> gtk_print_settings = g_object_ref(gtk_print_operation_get_print_settings(webkit -> gtk_print_operation));
    webkit -> print_status = Qtrue;
  }
  g_object_unref(webkit -> gtk_print_operation);
  gtk_main_quit();
}

void begin_print() {
  //begin print callback
}

void draw_page() {
  //draw page callback
}
