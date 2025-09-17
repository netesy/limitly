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

CXXFLAGS="-std=c++17 -Wall -Wextra -pedantic -I. -Isrc/"


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
# Note: embedding workflow is currently disabled.
# The project contains a `lembed` generator and `tools/make_embedded.*` helpers
# to produce standalone interpreter binaries with embedded bytecode. Those
# steps are intentionally not run as part of the default build because earlier
# automated embedding attempts caused linker and generator issues.

echo
echo "✅ Build completed successfully."
echo
echo "Embedding tools are present but disabled from this default build."
echo "To generate an embedded interpreter, build the project then run the lembed"
echo "generator and the make_embedded helper scripts manually:"
echo
echo "  ./bin/lembed -embed-source <src> <name> -build"
echo "  OR"
echo "  python tools/goembed.py <bytecode.txt> <name> src/lembed_generated && tools/make_embedded.sh <name>"
echo
