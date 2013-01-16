module GTK
  class Printer
    attr_accessor :tempfile

    def initialize
      @tempfile = Tempfile.new(Time.now.to_s)
    end

    def pdf_content; File.read(tempfile); end

    def export(base_url, name)
      File.open(File.join(base_url, name), 'w+'){ |f| f.write pdf_content }
    end

    def temp_path; tempfile.path; end

    def delete_pdf; tempfile.delete; end
  end
end
