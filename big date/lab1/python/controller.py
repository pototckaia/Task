import threading
import time


class Controller(object):
    def __init__(self, model, view):
        self._model = model
        self._view = view
        self.stop = False

        self._view.connect('start', self._on_start)
        self._view.connect('stop', self._on_stopt)

        self._view.show_all()

    def _on_start(self, button, *args):
        self.stop = False
        thread = threading.Thread(target=self._start_cycle)
        thread.daemon = True
        thread.start()
                  

    def _on_stopt(self, button, *args):
        self.stop = True

    def _from_rgb_to_rgba(self, red, green, blue):
        lowest = min(red, green, blue)
        a = (255 - lowest) / 255
        r = (red - lowest) / a
        g = (green - lowest) / a
        b = (blue - lowest) / a
        return r, g, b, a

    def _start_cycle(self):
        while not self.stop:
            for i, frame in enumerate(self._model.iter):
                if self.stop: 
                    break
                # print("Frame", i + 1)
                for i, rgb in enumerate(frame):
                    col = i % self._model.cols
                    row = i // self._model.rows
                    # print(col, row, rgb)
                    self._view.change_color(col, row, *self._from_rgb_to_rgba(rgb[0], rgb[1], rgb[2]))
                time.sleep(0.1)  
