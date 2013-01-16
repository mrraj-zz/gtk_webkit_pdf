module GTK
  module ControllersHelper
    def self.included(base)
      return if base != ActionController::Base

      base.class_eval do
        alias_method_chain :render, :gtk_webkit_pdf
      end
    end

    def render_with_gtk_webkit_pdf(options = {}, *args, &block)
      if options.is_a?(Hash) && options.has_key?(:pdf)
        make_and_send_pdf(options.delete(:pdf), render_options(options))
      else
        render_without_gtk_webkit_pdf(options, *args, &block)
      end
    end

    def make_and_send_pdf(pdf_name = nil, options = {})
      html_string = render_to_string(options)
      gtk_printer = GTK::Webkit.new(html_string, 0).gtk_printer
      send_data(gtk_printer.pdf_content, :file_name => pdf_name+'.pdf', :type => 'application/pdf', :disposition => options[:disposition])
    end

    private
    def render_options(options = {})
      options[:template] = File.join(controller_path, action_name)
      options[:layout] ||= false
      options[:file] ? options.merge(:file => options[:file]) : options
    end
  end
end
