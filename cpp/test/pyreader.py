import sys
import os
import time

sys.path.append("../../build/lib")

print(time.time_ns())

import pyjournal as pyjn

rd = pyjn.create_reader(False)

pyjn.reader_join(rd, "./tmp", "test", 0, pyjn.page_size.Small, 0)

while True:
    if rd.data_available():
        frame = rd.current_frame()
        if frame:
            print(frame.data_as_string)
        rd.next()
    else:
        time.sleep(1)
