module GTK
  class Webkit
    attr_accessor :webkit_url

    def initialize(webkit_url)
      @webkit_url = webkit_url
    end
  end
end

#require the SO(shared object) file
require "gtk_webkit_pdf/webkit"
