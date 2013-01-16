Gem::Specification.new do |s|
  s.name        = 'gtk_webkit_pdf'
  s.version     = '0.0.2'
  s.date        = Time.now.strftime("%Y-%m-%d")
  s.summary     = "GTK WEBKIT"
  s.homepage    = "https://github.com/mohanraj-ramanujam/gtk_webkit_pdf"
  s.description = "Generates the PDF from the HTML using GTK WEBKIT"
  s.authors     = ["Mohanraj Ramanujam"]
  s.email       = 'mohanraj.ramanujam@gmail.com'
  s.files       = Dir.glob("lib/**/*.rb") + Dir.glob("ext/**/*.{c,h}") + ['README', 'gtk_webkit_pdf.gemspec']
  s.extensions  = ["ext/gtk_webkit_pdf/extconf.rb"]
  s.executables = ["webkit"]
  s.add_dependency('rails')
end
