#!/bin/bash
echo "Building runtime string library..."

# Compile runtime_string.c into object file
gcc -c runtime_string.c -o runtime_string.o

if [ $? -ne 0 ]; then
    echo "Error: Failed to compile runtime_string.c"
    exit 1
fi

# Create static library
ar rcs limitly_runtime.a runtime_string.o

if [ $? -ne 0 ]; then
    echo "Error: Failed to create static library"
    exit 1
fi

echo "Runtime string library built successfully: limitly_runtime.a"
