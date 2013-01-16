#ifndef printer_utility_h__
  #define printer_utility_h__

  #include <ruby.h>
  #include <gtk/gtk.h>
  #include <webkit/webkit.h>
  #include <stdlib.h>
  #include <utility.h>

typedef struct {
  GtkPrintSettings *gtk_print_settings;
  GtkPrintOperation *gtk_print_operation;
  GtkPrintOperationResult gtk_print_operation_result;
  VALUE print_status;
} printer_wrapper;

extern void free_printer(void *void_printer);
extern void set_printer_configurations(VALUE self);
extern void begin_print();
extern void draw_page();
 
extern VALUE cGTK;

  #define PRINTER_PTR(self) printer_wrapper *printer; \
    Data_Get_Struct(self, printer_wrapper, printer);

  #define WEBKIT_PRINTER_PTR(printer_self, webkit_self) webkit_wrapper *webkit; \
    printer_wrapper *printer; \
    Data_Get_Struct(webkit_self, webkit_wrapper, webkit); \
    Data_Get_Struct(printer_self, printer_wrapper, printer);

#endif
