import pynotify

import gobject
from gi.repository import Peas
from gi.repository import PeasGtk
from Gtk import *

class Messenger (gobject.GObject, Peas.Activatable):
    __gtype_name__ = 'Messenger'
    ##!!def object
    object = gobject.property(type=gobject.GObject)
    def do_activate(self):
        print ("do nothing");
    def do_deactivate(self):
        print ("do nothing");
    def show_notify(self, msg, icon):
        print ("do nothing")

class MessengerConfigurable (gobject.GObject, PeasGtk.Configurable):
    __gtype_name__ = 'MessengerConfigurable'
    def do_create_configure_widget(self):
        return Gtk.Label.new ("I am lazy... You know...")
