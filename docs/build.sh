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
mkdir -p bin

CXX=g++

CXXFLAGS="-std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I."


echo "Compiling with $CXX..."

# =============================
# Compile debugger
# =============================
echo "Compiling debugger..."
$CXX $CXXFLAGS -c -o bin/debugger.o src/common/debugger.cpp

# =============================
# Main executable
# =============================

echo "Compiling main executable..."
$CXX $CXXFLAGS -o bin/limitly \
    src/main.cpp \
    src/frontend/scanner.cpp \
    src/frontend/parser.cpp \
    src/frontend/cst.cpp \
    src/frontend/cst_printer.cpp \
    src/frontend/cst_utils.cpp \
    src/backend/backend.cpp \
    src/backend/symbol_table.cpp \
    src/backend/vm.cpp \
    src/backend/value.cpp \
    src/backend/ast_printer.cpp \
    src/backend/bytecode_printer.cpp \
    src/backend/functions.cpp \
    src/backend/closure_impl.cpp \
    src/backend/classes.cpp \
    src/backend/type_checker.cpp \
    src/backend/function_types.cpp \
    src/backend/concurrency/scheduler.cpp \
    src/backend/concurrency/thread_pool.cpp \
    src/backend/concurrency/event_loop.cpp \
    src/backend/concurrency/epoll_event_loop.cpp \
    src/backend/concurrency/concurrency_runtime.cpp \
    src/backend/concurrency/task_vm.cpp \
    src/common/builtin_functions.cpp \
    src/error/error_formatter.cpp \
    src/error/error_code_generator.cpp \
    src/error/contextual_hint_provider.cpp \
    src/error/source_code_formatter.cpp \
    src/error/console_formatter.cpp \
    src/error/error_catalog.cpp \
    bin/debugger.o

echo "limitly built successfully."


# =============================
# Test parser
# =============================
echo "Compiling test parser..."
$CXX $CXXFLAGS -o bin/test_parser \
    src/test_parser.cpp \
    src/frontend/scanner.cpp \
    src/frontend/parser.cpp \
    src/frontend/cst.cpp \
    src/frontend/cst_printer.cpp \
    src/frontend/cst_utils.cpp \
    src/frontend/ast_builder.cpp \
    src/backend/type_checker.cpp \
    src/backend/backend.cpp \
    src/backend/value.cpp \
    src/backend/ast_printer.cpp \
    src/backend/bytecode_printer.cpp \
    src/backend/functions.cpp \
    src/backend/closure_impl.cpp \
    src/backend/classes.cpp \
    src/backend/function_types.cpp \
    src/error/error_formatter.cpp \
    src/error/error_code_generator.cpp \
    src/error/contextual_hint_provider.cpp \
    src/error/source_code_formatter.cpp \
    src/error/console_formatter.cpp \
    src/error/error_catalog.cpp \
    bin/debugger.o

echo "test_parser built successfully."

# Clean up object file
rm bin/debugger.o

echo
echo "✅ Build completed successfully."
echo
echo "Available executables:"
echo "  bin/limitly      - Main language interpreter"
echo "  bin/test_parser  - Parser testing utility"
echo
