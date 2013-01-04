#include <printer_utility.h>

void free_printer(void *void_printer) {
  printer_wrapper *printer = void_printer;
  free(printer);
}

void init_printer_configurations(VALUE self) {
  PRINTER_PTR(self);
  printer -> gtk_print_settings = NULL;
  printer -> gtk_print_operation = gtk_print_operation_new();

  if(printer -> gtk_print_settings != NULL)
    gtk_print_operation_set_print_settings(printer -> gtk_print_operation, printer -> gtk_print_settings);

  g_signal_connect(printer -> gtk_print_operation, "begin_print", G_CALLBACK(begin_print), NULL);
  g_signal_connect(printer -> gtk_print_operation, "draw_page", G_CALLBACK(draw_page), NULL);
}

void begin_print() {
  //begin print callback
}

void draw_page() {
  //draw page callback
}
