#!python

import sys
import re
import subprocess

def QuoteCppString(str):
	str = str.replace("\\", "\\\\")
	str = str.replace("\"", "\\\"")
	return "\"" + str + "\""

def ino_translate(ino, obj):
    cpp_file = re.sub('\.o(bj)?$', '.cpp', obj)
    pattern = re.compile(r"(?m)^\s*#\s*include\s*[<\"]Arduino\.h[>\"]")

    with open(ino) as infile:
        with open(cpp_file, mode='w') as outfile:
            lines = infile.readlines()

            if len([l for l in lines if pattern.match(l)]) == 0:
                outfile.write("#include <Arduino.h>\n")
                outfile.write("#line 1 %s\n" % QuoteCppString(ino))

                for l in lines:
                    outfile.write(l)

    return cpp_file


args = sys.argv

invoke_args = None
compile_file = None
output_file = None

while len(args) > 0:
    arg = args.pop(0)

    if invoke_args is not None:
        invoke_args.append(arg)

    if   arg == "--":
        invoke_args = []
    elif arg == "-o":
        arg = args.pop(0)
        invoke_args.append(arg)
        output_file = arg
    elif arg == "-c":
        arg = args.pop(0)
        invoke_args.append(arg)
        compile_file = arg

if compile_file is not None:
    cpp_file = ino_translate(compile_file, output_file)
    invoke_args[invoke_args.index(compile_file)] = cpp_file
    ret = subprocess.run(invoke_args)
    sys.exit(ret.returncode)
else:
    ret = subprocess.run(invoke_args)
    sys.exit(ret.returncode)

