class writer:

    def write_str(self,
                  msg_type: int,
                  data: str,
                  trigger_time: int
                  ): pass

    def write_bytes(self,
                    msg_type: int,
                    data: bytes,
                    length: int,
                    trigger_time: int
                    ): pass

    def write_bytes_with_time(self,
                              gen_time: int,
                              msg_type: int,
                              data: bytes,
                              length: int): pass

    def mark(self,
             trigger_time: int,
             msg_type: int): pass

    def mark_with_time(self,
                       gen_time: int,
                       msg_type: int): pass
