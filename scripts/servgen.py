import struct
import random

direct_file = "../data/result_direct.bin"

rows = 4
cols = 18

with open(direct_file, "wb") as handle:
    handle.write(rows.to_bytes(4, byteorder="little", signed=False))
    handle.write(cols.to_bytes(4, byteorder="little", signed=False))
    for i in range(0, rows):
        for j in range(0, cols):
            num = random.uniform(0.0, 1.0)
            handle.write(num.to_bytes(4, byteorder="little"))