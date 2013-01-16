module GTK
  class Middleware
    def initialize(app, options = {}, conditions = {})
      @app        = app
      @options    = options
      @conditions = conditions
    end

    def call(env)
      @request = Rack::Request.new(env)
      @render_pdf = false

      convert_pdf_request_to_html(env) if pdf_request?
      status, headers, response = @app.call(env)

      if @render_pdf && headers['Content-Type'] =~ /text\/html|application\/xhtml\+xml/
        body = response.respond_to?(:body) ? response.body : response.join
        body = body.join if body.is_a?(Array)

        printer = GTK::Webkit.new(prepend_absolute_path(body, env), 0).gtk_printer
        body = printer.pdf_content
        response = [body]

        headers.delete 'ETag'
        headers.delete 'Cache-Control'

        headers['Content-Length'] = (body.respond_to?(:bytesize) ? body.bytesize : body.size).to_s
        headers['Content-Type'] = 'application/pdf'
      end
      [status, headers, response]
    end

    private
    def prepend_absolute_path(body, env)
      prepend_path = "#{env['rack.url_scheme']}://#{env['HTTP_HOST']}/"
      body.gsub(/(href|src)=(['"])\/([^\"']*|[^"']*)['"]/, '\1=\2' + prepend_path + '\3\2')
    end    

    def convert_pdf_request_to_html(env)
      @render_pdf = true
      path = @request.path.sub(%r{\.pdf$}, '')
      %w(PATH_INFO REQUEST_URI).each{ |e| env[e] = path }
      env['HTTP_ACCEPT'] = concat(env['HTTP_ACCEPT'], Rack::Mime.mime_type('.html'))
      env['Rack-Middleware-Gtk-Webkit-Pdf'] = "true"
    end

    def concat(accepts, type)
      (accepts || '').split(',').unshift(type).compact.join(',')
    end

    def pdf_request?
      @request.path.match(/\.pdf$/)
    end
  end
end
