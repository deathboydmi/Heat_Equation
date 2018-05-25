import struct
import random

direct_file = "../data/result_direct.bin"

size = 8

with open(direct_file, "wb") as handle:
    handle.write(size.to_bytes(4, byteorder="little", signed=False))
    for i in range(0, size):
        num = i
        handle.write(struct.pack('<d', num))