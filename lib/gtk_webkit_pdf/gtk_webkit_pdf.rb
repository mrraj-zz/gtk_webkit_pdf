module GTK
  class Webkit
    attr_accessor :webkit_url, :export_filename

    def initialize(webkit_url, export_filename)
      @webkit_url = webkit_url
      @export_filename = export_filename
    end
  end
end

#require the SO(shared object) file
require "gtk_webkit_pdf/webkit"
