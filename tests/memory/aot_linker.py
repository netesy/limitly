#!/usr/bin/env python3
"""Link test executables with the same sanitizer runtime as their AOT archive."""
import os
import shlex
import sys

command = shlex.split(os.environ.get("CXX", "g++"))
sanitizers = os.environ.get("LYMAR_AOT_SANITIZERS", "")
if sanitizers:
    command.append("-fsanitize=" + sanitizers)
os.execvp(command[0], command + sys.argv[1:])
