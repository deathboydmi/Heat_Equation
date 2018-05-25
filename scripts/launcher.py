import subprocess as sp
import sys
import matplotlib
import numpy as np
import struct

print("Starting work")
#insert path and prog name here etc.
#func_call = sp.call("../bin/solver")

direct_file = "../data/result_direct.bin"
indirect_file = "../data/result_indirect.bin"

direct_handle = open(direct_file, "rb")
size = int.from_bytes(direct_handle.read(4), byteorder='little', signed=False)

print(size)

data_direct = np.empty((size), dtype = float)

for i in range(0, size):
    data_direct[i] = struct.unpack('<d', direct_handle.read(8))[0]

print(data_direct)

direct_handle.close()
