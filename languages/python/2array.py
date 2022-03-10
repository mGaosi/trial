#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys

def to_cpp(filename):
    fcpp = open(filename + ".cpp", "w")
    fcpp.write("const char buf[] = \n")
    fcpp.writelines("{\n")
    with open(filename, "rb") as f:
        while True:
            data = f.read(20)
            if len(data) == 0:
                break
            fcpp.write("    ")
            for var in data:
                fcpp.write("0x{:02X}, ".format(var))
            fcpp.write("\n")
    fcpp.writelines("};\n")

if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.exit(-1)
    else:
        to_cpp(sys.argv[1])        
    sys.exit(0)