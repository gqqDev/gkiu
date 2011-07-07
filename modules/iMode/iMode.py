import gobject
from gi.repository import Peas
from gi.repository import PeasGtk
from gi.repository import Gtk

class iMode (gobject.GObject, Peas.Activatable):
    __gtype_name__ = 'iMode'
    ##!!def object
    object = gobject.property(type=gobject.GObject)
    def do_activate(self):
        print("iMode is enable.")

    def do_deactivate(self):
        print("iMode is disenable.")

class iModeConfigurable (gobject.GObject, PeasGtk.Configurable):
    __gtype_name__ = 'iModeConfigurable'
    def do_create_configure_widget(self):
        return Gtk.Label.new ("Hello. There's also nothing.") 
