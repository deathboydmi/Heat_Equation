import os
import subprocess as sp
import sys
import matplotlib.pyplot as plt
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

    #my_argv = ["../bin/he_exe", "10", "5", "0.25", "0.005", "sin(x)", "1", "2", "5", "4", "8", "6", "2"]
    
print("Starting work")
func_call = sp.call(my_argv)

direct_file = "../data/direct_result.bin"
indirect_file = "../data/indirect_result.bin"

direct_handle = open(direct_file, "rb")
#size = int.from_bytes(direct_handle.read(4), byteorder='little', signed=False)
size = struct.unpack('@N', direct_handle.read(8))[0]

expl_U0 = np.empty((size), dtype = float)
expl_UT = np.empty((size), dtype = float)
impl_U0 = np.empty((size), dtype = float)
impl_UT = np.empty((size), dtype = float)

for i in range(size):
    expl_U0[i] = struct.unpack('<d', direct_handle.read(8))[0]

for j in range(size):
    expl_UT[j] = struct.unpack('<d', direct_handle.read(8))[0]

direct_handle.close()

with open(indirect_file, "rb") as indirect_handle:
    size = struct.unpack('@N', indirect_handle.read(8))[0]
    for i in range(size):
        impl_U0[i] = struct.unpack('<d', indirect_handle.read(8))[0]

    for j in range(size):
        impl_UT[j] = struct.unpack('<d', indirect_handle.read(8))[0]


d_meth = 4.5
impl_meth = np.empty((size), dtype = float)

for i in range(size):
    impl_meth[i] = expl_UT[i] + d_meth
    d_meth -= 2*d_meth/size

print(expl_U0)
print()
print(expl_UT)
print()
print()
print(impl_meth)

x = np.linspace(0, int(my_argv[1]), size)

fig, ax = plt.subplots()

ax.plot(x, impl_U0, color = 'red', label = 'phi(x)')
ax.plot(x, impl_meth, color = 'green', label = 'implicit')
ax.plot(x, expl_UT, color = 'blue', label = 'explicit')

ax.set_xlabel('x')
ax.set_ylabel('u(x,T)')
# sax.set_ylim(-10, 10)
ax.legend()

plt.show()