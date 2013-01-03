#include <ruby.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <webkit.h>

VALUE cGTK = Qnil;
VALUE cWebkit = Qnil;

static VALUE c_new(VALUE self, VALUE webkit_url, VALUE export_filename) {
  webkit_wrapper *webkit;
  VALUE argv[2];
  VALUE data_object = Data_Make_Struct(self, webkit_wrapper, 0, free_webkit, webkit);
  webkit -> webkit_url = StringValuePtr(webkit_url);
  webkit -> export_filename = StringValuePtr(export_filename);

  argv[0] = webkit_url;
  argv[1] = export_filename;
  rb_obj_call_init(data_object, 2, argv);
  return data_object;
}

static VALUE c_convert_to_pdf(VALUE self) {
  webkit_wrapper *webkit;
  gtk_init(NULL, NULL);
  Data_Get_Struct(self, webkit_wrapper, webkit);
  initialize_webkit(webkit);
  activate_webkit(webkit);
  gtk_main();
  return webkit -> print_status;
}

void Init_webkit(void) {
  cGTK = rb_define_module("GTK");
  cWebkit = rb_define_class_under(cGTK, "Webkit", rb_cObject);
  rb_define_singleton_method(cWebkit, "new", c_new, 2);
  rb_define_method(cWebkit, "convert_to_pdf", c_convert_to_pdf, 0);
}
