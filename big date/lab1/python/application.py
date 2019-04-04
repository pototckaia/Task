import model as m
import view as v
import controller as c

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gio


class Application(Gtk.Application):
    def __init__(self):
        app_id = 'org.iea.example'
        flags = Gio.ApplicationFlags.FLAGS_NONE

        super(Application, self).__init__(application_id=app_id, flags=flags)

    def do_activate(self):
        model = m.Model()
        c.Controller(model, v.View(model.cols, model.rows, application=self))

    def do_startup(self):
        Gtk.Application.do_startup(self)