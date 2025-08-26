#!/bin/bash
# build.sh - Build Limit Language on Linux

set -e  # Exit immediately on error

echo "Building Limit Language on Linux..."

# =============================
# Dependency checks
# =============================
check_dep() {
    if ! command -v "$1" &> /dev/null; then
        echo "Error: '$1' is not installed or not in PATH."
        echo "Please install it with your package manager."
        exit 1
    fi
}

echo "Checking dependencies..."
check_dep g++
check_dep pkg-config

echo "All dependencies found."

# =============================
# Build setup
# =============================
mkdir -p bin

CXX=g++
CXXFLAGS="-std=c++17 -Wall -Wextra -pedantic -I. -I/usr/lib/gcc/x86_64-linux-gnu/13/include"
LDFLAGS="-L/usr/lib/gcc/x86_64-linux-gnu/13 -lgccjit"

echo "Compiling with $CXX..."

# =============================
# Main executable
# =============================
# $CXX $CXXFLAGS -o bin/limitly \
#     main.cpp \
#     frontend/scanner.cpp \
#     frontend/parser.cpp \
#     backend/backend.cpp \
#     backend/vm.cpp \
#     backend/ast_printer.cpp \
#     backend/functions.cpp \
#     backend/classes.cpp \
#     debugger.cpp \
#     $LDFLAGS

# echo "limitly built successfully."

# =============================
# Test parser
# =============================
$CXX $CXXFLAGS -o bin/test_parser \
    test_parser.cpp \
    frontend/scanner.cpp \
    frontend/parser.cpp \
    backend/backend.cpp \
    backend/ast_printer.cpp \
    backend/functions.cpp \
    backend/classes.cpp \
    debugger.cpp

echo "test_parser built successfully."

# =============================
# Code formatter
# =============================
# $CXX $CXXFLAGS -o bin/format_code \
#     format_code.cpp \
#     frontend/scanner.cpp \
#     frontend/parser.cpp \
#     backend/code_formatter.cpp \
#     debugger.cpp \
#     $LDFLAGS

# echo "format_code built successfully."

# =============================
# Compiler
# =============================
# $CXX $CXXFLAGS -o bin/compile \
#     compile.cpp \
#     frontend/scanner.cpp \
#     frontend/parser.cpp \
#     backend/jit_backend.cpp \
#     debugger.cpp \
#     $LDFLAGS

# echo "compile built successfully."

# =============================
# Summary
# =============================
echo
echo "✅ Build completed successfully."
echo
# echo "Run the main executable:"
# echo "  ./bin/limitly"
# echo
echo "Run the test parser:"
echo "  ./bin/test_parser sample.lm"
echo
# echo "Run the code formatter:"
# echo "  ./bin/format_code sample.lm"
# echo
# echo "Run the AOT compiler:"
# echo "  ./bin/compile sample.lm sample.o"
# echo
