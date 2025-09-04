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

CXXFLAGS="-std=c++17 -Wall -Wextra -pedantic -I."


echo "Compiling with $CXX..."

# =============================
# Main executable
# =============================

$CXX $CXXFLAGS -o bin/limitly \
    src/main.cpp \
    src/frontend/scanner.cpp \
    src/frontend/parser.cpp \
    src/backend/backend.cpp \
    src/backend/vm.cpp \
    src/backend/ast_printer.cpp \
    src/backend/functions.cpp \
    src/backend/classes.cpp \
    src/backend/concurrency/scheduler.cpp \
    src/backend/concurrency/thread_pool.cpp \
    src/backend/concurrency/event_loop.cpp \
    src/backend/concurrency/epoll_event_loop.cpp \
    src/debugger.cpp

echo "limitly built successfully."


# =============================
# Test parser
# =============================
$CXX $CXXFLAGS -o bin/test_parser \
    src/test_parser.cpp \
    src/frontend/scanner.cpp \
    src/frontend/parser.cpp \
    src/backend/backend.cpp \
    src/backend/ast_printer.cpp \
    src/backend/functions.cpp \
    src/backend/classes.cpp \
    src/debugger.cpp

echo "test_parser built successfully."

# =============================
# Unit tests
# =============================
$CXX $CXXFLAGS -o bin/test_event_loop \
    tests/unit/test_event_loop.cpp \
    src/backend/concurrency/event_loop.cpp \
    src/backend/concurrency/epoll_event_loop.cpp \
    src/backend/concurrency/kqueue_event_loop.cpp \
    src/backend/concurrency/iocp_event_loop.cpp

echo "test_event_loop built successfully."

# =============================
# Code formatter
# =============================

$CXX $CXXFLAGS -o bin/format_code \
    src/format_code.cpp \
    src/frontend/scanner.cpp \
    src/frontend/parser.cpp \
    src/backend/code_formatter.cpp \
    src/debugger.cpp


echo "format_code built successfully."

# =============================
# Summary
# =============================
echo
echo "✅ Build completed successfully."
echo
echo "Run the main executable:"
echo "  ./bin/limitly"
echo
echo "Run the test parser:"
echo "  ./bin/test_parser sample.lm"
echo
echo "Run the code formatter:"
echo "  ./bin/format_code sample.lm"
echo
echo "Run the AOT compiler:"
echo "  ./bin/compile sample.lm sample.o"
echo
