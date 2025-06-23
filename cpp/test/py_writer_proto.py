import sys
import os
import time
import test_pb2 as test_proto

sys.path.append("../lib")

print(time.time_ns())

import pyjournal as pyjn

wr = pyjn.create_writer("./tmp", "test", pyjn.page_size.Small, 0, False)

i = 0
while True:
    # data = f'{i}, test++++++++++++++end'
    test = test_proto.Test()
    test.int_value = i
    test.string_value = f'{i}, test++++++++++++++end'
    data = test.SerializeToString()
    print("py write:", data)
    wr.write_bytes(100, data, len(data))
    i += 1
    # time.sleep(1)
