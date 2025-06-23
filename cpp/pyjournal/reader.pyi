from .frame import *


class reader:
    # def subscribe(self): pass

    def current_frame(self) -> frame: pass

    def seek_to_time(self, nanotime: int): pass

    def data_available(self) -> bool: pass

    def next(self): pass

    # def join(self): pass

    def dis_join(self): pass
