require 'gtk_webkit_pdf/gtk_printer_pdf'
require 'gtk_webkit_pdf/gtk_controllers_helper_pdf'
require 'gtk_webkit_pdf/gtk_views_helper_pdf'
require 'gtk_webkit_pdf/gtk_railtie_pdf'
require 'gtk_webkit_pdf/gtk_middleware_pdf'
require 'gtk_webkit_pdf/webkit'

module GTK
  class Webkit
    VERSION  = "0.0.2"
    CONTENT  = 0
    FILEPATH = 1
    HTTP_URI = 2

    attr_accessor :source, :format, :options

    def initialize(source, format, options = {})
      @source  = source
      @format  = format
      @options = { :mime_type => 'text/html', :encoding => 'UTF-8' }.merge(options)
      raise WebkitError, 'format should be 0 or 1 or 2' unless [CONTENT, FILEPATH, HTTP_URI].member?(@format)
    end

    def gtk_printer
      @gtk_printer ||= generate_pdf
    end

    private
    def source_content
      File.read(@source) if @format == FILEPATH
    end
  end

  class WebkitError < StandardError
  end
end
