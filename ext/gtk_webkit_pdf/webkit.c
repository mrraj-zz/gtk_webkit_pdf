#include <ruby.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <webkit.h>

VALUE cGTK = Qnil;
VALUE cWebkit = Qnil;

static VALUE webkit_allocate(VALUE klass) {
  webkit_wrapper *webkit;
  VALUE data_object = Data_Make_Struct(klass, webkit_wrapper, mark_webkit_printer, free_webkit, webkit);
  return data_object;
}

static VALUE c_generate_pdf(VALUE self) {
  VALUE source, content;
  WEBKIT_PTR(self);  

  webkit -> webkit_webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
  source = rb_iv_get(self, "@source");

  switch(NUM2INT(rb_iv_get(self, "@format"))) {
    case 0:
      webkit_web_view_load_string(webkit -> webkit_webview, StringValuePtr(source), NULL, NULL, "file://");
      break;
    case 1:
      content = rb_funcall(self, rb_intern("source_content"), 0, 0);
      webkit_web_view_load_html_string(webkit -> webkit_webview, StringValuePtr(content), "file://");
      break;
    case 2:
      webkit_web_view_load_uri(webkit -> webkit_webview, StringValuePtr(source));
      break;
  }
  g_signal_connect(webkit -> webkit_webview, "load-finished", G_CALLBACK(webkit_load_finished), (void *)self);
  gtk_main();
  return webkit -> printer;
}

void Init_webkit(void) {
  gtk_init(NULL, NULL);
  cGTK = rb_define_module("GTK");
  cWebkit = rb_define_class_under(cGTK, "Webkit", rb_cObject);

  rb_define_alloc_func(cWebkit, webkit_allocate);
  rb_define_method(cWebkit, "generate_pdf", c_generate_pdf, 0);

  init_printer();
}
