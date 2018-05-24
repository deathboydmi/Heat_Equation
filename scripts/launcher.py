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
rows = int.from_bytes(direct_handle.read(4), byteorder='little', signed=False)
cols = int.from_bytes(direct_handle.read(4), byteorder='little', signed=False)

print(rows)
print(cols)

data_direct = np.empty((rows, cols), dtype = float)

direct_handle.close()

