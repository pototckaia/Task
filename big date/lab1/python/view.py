import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk, GObject


class View(Gtk.ApplicationWindow):

    __gsignals__ = {
        'start': (GObject.SignalFlags.RUN_FIRST, None, ()),
        'stop': (GObject.SignalFlags.RUN_FIRST, None, ())
    }

    def __init__(self, col, row, **kw):
        super(View, self).__init__(default_width=200, 
                                   default_height=200, **kw)

        self._main_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL)

        self._button_start = Gtk.ToggleButton("Button")
        self._button_start.connect("toggled", self._on_button_toggled)
        self._button_start.set_active(False)
        
        self._main_box.add(self._button_start)

        self._column_spacing =  10
        self._row_spacing = 10

        self._grid = Gtk.Grid(column_spacing=self._column_spacing, 
                              row_spacing=self._row_spacing)
        self._main_box.add(self._grid)

        self._number_of_columns = col
        self._number_of_rows = row
        
        self._cell_width = 20
        self._cell_height = 20

        self._create_table()
        self.add(self._main_box)


    def _on_button_toggled(self, button):
        if button.get_active():
            self.emit('start')
        else:
            self.emit('stop')


    def change_color(self, column, row, red, green, blue, alpha):
        a = self._grid.get_child_at(self._cell_width*column, self._cell_height*row)
        a.override_background_color(Gtk.StateFlags.NORMAL, 
            Gdk.RGBA(red, green, blue, alpha))



    def _create_table(self):
        for column in range(self._number_of_columns):
            for row in range(self._number_of_rows):
                self._grid.attach(Gtk.Label(), 
                                self._cell_width*column, self._cell_height*row, 
                                self._cell_width, self._cell_height)


