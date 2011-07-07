# this file is main file of imui.
# imui is a module for gkiu.

import gobject
from gi.repository import Peas
from gi.repository import PeasGtk
from gi.repository import Gtk

# import imui_windows
# import imui_config

class Imui (gobject.GObject, Peas.Activatable):
    __gtype_name__ = 'Imui'
    ##!!def object
    object = gobject.property(type=gobject.GObject)
    def do_activate(self):
        print ("IMUI started.")

    def do_deactivate(self):
        print ("IMUI will be end.")

    def do_update_state(self):
        print ("do update state")

class ImuiConfigurable (gobject.GObject, PeasGtk.Configurable):
    __gtype_name__ = 'ImuiConfigurable'
    def do_create_configure_widget(self):
        return Gtk.Label.new ("The developers are too lazy.\nThere's nothing.")
