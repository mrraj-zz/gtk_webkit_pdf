module GTK
  if defined?(Rails)
    class Railtie < Rails::Railtie
      initializer 'gtk_webkit_pdf.register' do |app|
        ActionController::Base.send :include, GTK::ControllersHelper

        if Rails::VERSION::MINOR > 0 && Rails.configuration.assets.enabled
          ActionView::Base.send :include, AssetsHelper
        else
          ActionView::Base.send :include, ViewsHelper
        end
      end
    end
  end

  if Mime::Type.lookup_by_extension(:pdf).nil?
    Mime::Type.register('application/pdf', :pdf)
  end
end
