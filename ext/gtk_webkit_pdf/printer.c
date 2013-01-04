#include<ruby.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include<printer.h>

VALUE cPrinter = Qnil;

static VALUE c_printer_new(VALUE self) {
  printer_wrapper *printer;
  VALUE data_object = Data_Make_Struct(self, printer_wrapper, 0, free_printer, printer);
  gtk_init(NULL, NULL);
  init_printer_configurations(data_object);
  return data_object;
}

static VALUE c_export_to_pdf(VALUE self, VALUE source, VALUE directory_path, VALUE file_name) {
  char *pdf_path;
  WEBKIT_PRINTER_PTR(self, source);
  STR_CON_CAT(directory_path, file_name);
  gtk_print_operation_set_export_filename(printer -> gtk_print_operation, pdf_path);
  printer -> gtk_print_operation_result = webkit_web_frame_print_full(webkit -> webkit_webframe,
                                         printer -> gtk_print_operation, GTK_PRINT_OPERATION_ACTION_EXPORT, NULL);

  if(printer -> gtk_print_operation_result == GTK_PRINT_OPERATION_RESULT_APPLY) {
    g_object_unref(printer -> gtk_print_settings);
    printer -> gtk_print_settings = g_object_ref(gtk_print_operation_get_print_settings(printer -> gtk_print_operation));
    printer -> print_status = Qtrue;
  }
  g_object_unref(printer -> gtk_print_operation);
  return printer -> print_status;
}

void init_printer() {
  cPrinter = rb_define_class_under(cGTK, "Printer", rb_cObject);
  rb_define_singleton_method(cPrinter, "new", c_printer_new, 0);
  rb_define_private_method(cPrinter, "export_to_pdf", c_export_to_pdf, 3);
}
