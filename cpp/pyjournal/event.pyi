class event:
    def __init__(self):
        self.gen_time = ''
        self.trigger_time = ''
        self.msg_type = ''
        self.source = ''
        self.dest = ''
        self.data_length = ''
        self.data_as_bytes = ''
        self.data_as_string = ''

    def to_string(self) -> str: pass
