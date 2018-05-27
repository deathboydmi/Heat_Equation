import os
import subprocess as sp
import sys
import matplotlib.pyplot as ppl
import numpy as np
import struct

my_argv = []
if len(sys.argv) == 13:
    my_argv = sys.argv
    my_argv[0] = "../bin/he_exe"
else:
    my_argv.append("../bin/he_exe")
    my_argv.append(input("Enter length of rod: "))
    my_argv.append(input("Enter the time: "))
    my_argv.append(input("Enter the step of length: "))
    my_argv.append(input("Enter the step of time: "))
    my_argv.append(input("Enter the function b(x): "))
    
    for i in range(7):
        my_argv.append("")
    my_argv[6:13] = list(input("Enter the coeficients (7) of function phi(x):\n\t").split())

    #my_argv = ["../bin/he_exe", "100", "10", "1", "0.1", "sin(x)", "1", "1", "1", "1", "1", "1", "1"]
    
print("Starting work")
func_call = sp.call(my_argv)
size = int(float(my_argv[1]) / float(my_argv[3]))

direct_file = "../data/direct_result.bin"
indirect_file = "../data/indirect_result.bin"

data_direct_first = np.empty((size), dtype = float)
data_direct_last = np.empty((size), dtype = float)
data_indirect_first = np.empty((size), dtype = float)
data_indirect_last = np.empty((size), dtype = float)

with open(direct_file, "rb") as direct_handle:
    #size = int.from_bytes(direct_handle.read(4), byteorder='little', signed=False)
    size = struct.unpack('@N', direct_handle.read(8))[0]

    for i in range(size):
        data_direct_first[i] = struct.unpack('<d', direct_handle.read(8))[0]

    for j in range(size):
        data_direct_last[j] = struct.unpack('<d', direct_handle.read(8))[0]

with open(indirect_file, "rb") as indirect_handle:
    size = struct.unpack('@N', indirect_handle.read(8))[0]
    for i in range(size):
        data_indirect_first[i] = struct.unpack('<d', indirect_handle.read(8))[0]

    for j in range(size):
        data_indirect_last[j] = struct.unpack('<d', indirect_handle.read(8))[0]

print(data_direct_first)
print()
print(data_direct_last)
print()
print()
print(data_indirect_last)

ppl.figure(300)
ppl.title("Direct")
ppl.plot(data_direct_last)
ppl.plot(data_indirect_last)
ppl.plot(data_direct_first)
ppl.show()

# ppl.figure(200)
# ppl.title("Inirect")
# ppl.plot(data_indirect_last)
# ppl.plot(data_indirect_first)
# ppl.show()
