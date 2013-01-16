#include<ruby.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include<printer.h>

VALUE cPrinter = Qnil;

static VALUE printer_allocate(VALUE klass) {
  printer_wrapper *printer;
  VALUE data_object = Data_Make_Struct(klass, printer_wrapper, 0, free_printer, printer);
  return data_object;
}

static VALUE c_webkit_webframe_to_pdf(VALUE self, VALUE source) {
  VALUE temp_path;
  WEBKIT_PRINTER_PTR(self, source);
  gtk_init(NULL, NULL);

  //PRINTER CONFIGURATIONS
  set_printer_configurations(self);

  //EXPORT PDF FROM WEBKIT WEBFRAME
  temp_path = rb_funcall(self, rb_intern("temp_path"), 0, 0);
  gtk_print_operation_set_export_filename(printer -> gtk_print_operation, StringValuePtr(temp_path));
  printer -> gtk_print_operation_result = webkit_web_frame_print_full(webkit -> webkit_webframe,
                                         printer -> gtk_print_operation, GTK_PRINT_OPERATION_ACTION_EXPORT, NULL);

  if(printer -> gtk_print_operation_result == GTK_PRINT_OPERATION_RESULT_APPLY) {
    g_object_unref(printer -> gtk_print_settings);
    printer -> gtk_print_settings = g_object_ref(gtk_print_operation_get_print_settings(printer -> gtk_print_operation));
    printer -> print_status = Qtrue;
  }
  g_object_unref(printer -> gtk_print_operation);
  return printer -> print_status == Qtrue ? self : Qnil;
}

void init_printer() {
  cPrinter = rb_define_class_under(cGTK, "Printer", rb_cObject);
  rb_define_alloc_func(cPrinter, printer_allocate);

  rb_define_method(cPrinter, "webkit_webframe_to_pdf", c_webkit_webframe_to_pdf, 1);
}
