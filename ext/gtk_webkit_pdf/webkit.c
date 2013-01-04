#include <ruby.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <webkit.h>

VALUE cGTK = Qnil;
VALUE cWebkit = Qnil;

static VALUE c_new(VALUE self, VALUE webkit_url) {
  webkit_wrapper *webkit;
  VALUE argv[1];
  VALUE data_object = Data_Make_Struct(self, webkit_wrapper, mark_webkit_printer, free_webkit, webkit);
  webkit -> webkit_url = StringValuePtr(webkit_url);

  argv[0] = webkit_url;
  rb_obj_call_init(data_object, 1, argv);
  return data_object;
}

static VALUE c_convert_to_pdf(VALUE self, VALUE dir_path, VALUE pdf_filename) {
  WEBKIT_PTR(self);
  gtk_init(NULL, NULL);
  set_pdf_configurations(self, dir_path, pdf_filename);
  activate_gtk_webkit(self);
  gtk_main();
  return webkit -> print_status;
}

void Init_webkit(void) {
  cGTK = rb_define_module("GTK");
  cWebkit = rb_define_class_under(cGTK, "Webkit", rb_cObject);
  rb_define_singleton_method(cWebkit, "new", c_new, 1);
  rb_define_method(cWebkit, "convert_to_pdf", c_convert_to_pdf, 2);

  init_printer();
}
