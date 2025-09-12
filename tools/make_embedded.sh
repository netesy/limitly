#!/usr/bin/env bash
if [ -z "$1" ]; then
  echo "Usage: make_embedded.sh <embed_name>"
  exit 1
fi
NAME=$1

if [ ! -f src/lembed_generated.cpp ]; then
  echo "src/lembed_generated.cpp not found. Run lembed -embed-source <src> <name> first."
  exit 1
fi

mkdir -p bin

CXX=g++
CXXFLAGS="-std=c++17 -O2 -Wall -Wextra -I."

$CXX $CXXFLAGS -o bin/limitly_${NAME} \
    src/main.cpp \
    src/frontend/scanner.cpp \
    src/frontend/parser.cpp \
    src/backend/backend.cpp \
    src/backend/vm.cpp \
    src/lembed_generated.cpp \
    src/backend/ast_printer.cpp \
    src/backend/functions.cpp \
    src/backend/classes.cpp \
    src/debugger.cpp

if [ $? -ne 0 ]; then
  echo "Failed to build embedded interpreter"
  exit 1
fi

echo "Built bin/limitly_${NAME}"
exit 0
