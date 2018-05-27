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
    #my_argv.append("../bin/he_exe")
    #my_argv.append(input("Enter length of rod: "))
    #my_argv.append(input("Enter the time: "))
    #my_argv.append(input("Enter the step of length: "))
    #my_argv.append(input("Enter the step of time: "))
    #my_argv.append(input("Enter the function b(x): "))
    #
    #for i in range(7):
    #    my_argv.append("")
    #my_argv[6:13] = list(input("Enter the coeficients (7) of function phi(x):\n\t").split())

    my_argv = ["../bin/he_exe", "10", "10", "1", "0.1", "sin(x)", "1", "1", "1", "1", "1", "1", "1"]
    
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

print(expl_U0)
print()
print(expl_UT)
print()
print()
print(impl_UT)

x = np.linspace(0, int(my_argv[1]), size)

fig, ax = plt.subplots()

ax.plot(x, impl_U0, color = 'red', label = 'phi(x)')
ax.plot(x, impl_UT, color = 'green', label = 'implicit')
ax.plot(x, expl_UT, color = 'blue', label = 'explicit')

ax.set_xlabel('x')
ax.set_ylabel('u(x,T)')
# sax.set_ylim(-10, 10)
ax.legend()

plt.show()

# ppl.figure(300)
# ppl.title("Direct")
# ppl.plot(expl_UT)
# ppl.plot(impl_UT)
# ppl.plot(expl_U0)
# ppl.show()

# ppl.figure(200)
# ppl.title("Inirect")
# ppl.plot(impl_UT)
# ppl.plot(impl_U0)
# ppl.show()
