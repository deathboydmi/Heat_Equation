import subprocess as sp
import sys
import matplotlib.pyplot as ppl
import numpy as np
import struct

print("Starting work")
#insert path and prog name here etc.
#func_call = sp.call("../bin/solver")

direct_file = "../data/direct_result.bin"
indirect_file = "../data/result_indirect.bin"

direct_handle = open(direct_file, "rb")
#size = int.from_bytes(direct_handle.read(4), byteorder='little', signed=False)
size = struct.unpack('@N', direct_handle.read(8))[0]

data_direct_first = np.empty((size), dtype = float)
data_direct_last = np.empty((size), dtype = float)

print(size)

for i in range(0, size):
    data_direct_first[i] = struct.unpack('<d', direct_handle.read(8))[0]

for j in range(0, size):
    data_direct_last[j] = struct.unpack('<d', direct_handle.read(8))[0]

print(data_direct_first)
print(data_direct_last)

ppl.plot(data_direct_last)
ppl.plot(data_direct_first)
ppl.show()

direct_handle.close()
