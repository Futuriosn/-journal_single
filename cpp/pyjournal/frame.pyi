from event import *


class frame(event):
    def __init__(self):
        self.gen_time = ''
        self.trigger_time = ''
        self.source = ''
        self.dest = ''
        self.msg_type = ''
        self.frame_length = ''
        self.header_length = ''
        self.data_length = ''
        self.address = ''
        self.data_as_bytes = ''
        self.data_as_string = ''
        self.data_address = ''

    def has_data(self) -> bool: pass
