import sys
import os
import time

sys.path.append("../../build/lib")

print(time.time_ns())

import pyjournal as pyjn

wr = pyjn.create_writer("./tmp", "test", pyjn.page_size.Small, 0, False)

i = 0
while True:
    data = f'{i}, test++++++++++++++end'
    print("py write:", data)
    wr.write_bytes(100, data, len(data), 0)
    i += 1
    # time.sleep(1)
