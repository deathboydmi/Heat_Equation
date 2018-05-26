import subprocess as sp
import sys
import matplotlib.pyplot as ppl
import numpy as np
import struct

print("Starting work")
#insert path and prog name here etc.
#func_call = sp.call("../bin/solver")

direct_file = "../data/direct_result.bin"
indirect_file = "../data/indirect_result.bin"

direct_handle = open(direct_file, "rb")
#size = int.from_bytes(direct_handle.read(4), byteorder='little', signed=False)
size = struct.unpack('@N', direct_handle.read(8))[0]

data_direct_first = np.empty((size), dtype = float)
data_direct_last = np.empty((size), dtype = float)
data_indirect_first = np.empty((size), dtype = float)
data_indirect_last = np.empty((size), dtype = float)

for i in range(0, size):
    data_direct_first[i] = struct.unpack('<d', direct_handle.read(8))[0]

for j in range(0, size):
    data_direct_last[j] = struct.unpack('<d', direct_handle.read(8))[0]

with open(indirect_file, "rb") as indirect_handle:
    size = struct.unpack('@N', indirect_handle.read(8))[0]
    for i in range(0, size):
        data_indirect_first[i] = struct.unpack('<d', indirect_handle.read(8))[0]

    for j in range(0, size):
        data_indirect_last[j] = struct.unpack('<d', indirect_handle.read(8))[0]

print(data_direct_first)
print(data_direct_last)
print()
print(data_indirect_first)
print(data_indirect_last)

ppl.figure(300)
ppl.title("Direct")
ppl.plot(data_direct_last)
ppl.plot(data_direct_first)
ppl.show()

ppl.figure(200)
ppl.title("Inirect")
ppl.plot(data_indirect_last)
ppl.plot(data_indirect_first)
ppl.show()

direct_handle.close()
