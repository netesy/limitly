#!/bin/bash

echo "Building and testing ErrorCodeGenerator..."

# Create bin directory if it doesn't exist
mkdir -p ../../bin

# Compile the test
g++ -std=c++17 -I../../src -o ../../bin/test_error_code_generator test_error_code_generator.cpp ../../src/error_code_generator.cpp

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Compilation successful. Running tests..."
echo

# Run the test
../../bin/test_error_code_generator

echo
echo "Test execution completed."