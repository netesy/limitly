#!/bin/bash

echo "Running benchmarks..."

# Build the project first
echo "Building the Limit language..."
./build.sh

echo ""
echo "----------------------------------------"
echo "Running Limit benchmark..."
echo "----------------------------------------"
./bin/limitly benchmarks/loop_benchmark.lm

echo ""
echo "----------------------------------------"
echo "Running Python benchmark..."
echo "----------------------------------------"
python3 benchmarks/loop_benchmark.py

echo ""
echo "Benchmarks complete."
