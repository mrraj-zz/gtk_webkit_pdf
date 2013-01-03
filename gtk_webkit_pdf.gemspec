Gem::Specification.new do |s|
  s.name        = 'gtk_webkit_pdf'
  s.version     = '0.0.0'
  s.date        = '2013-01-03'
  s.summary     = "GTK WEBKIT"
  s.description = "Generates the PDF from the HTML using GTK WEBKIT"
  s.authors     = ["Mohanraj Ramanujam"]
  s.email       = 'mohanraj.ramanujam@gmail.com'
  s.files       = Dir.glob("lib/**/*.rb") + Dir.glob("ext/**/*.{c,h}") + ['README', 'gtk_webkit_pdf.gemspec']
  s.extensions  = ["ext/gtk_webkit_pdf/extconf.rb"]
  s.executables = ["webkit"]
  s.homepage    =
    'http://rubygems.org/gems/gtk_webkit_pdf'
end
