#!/bin/bash

echo "Building performance benchmark tools..."
echo "====================================="

# Build the project with benchmarks
mkdir -p build
cd build
cmake ..
make benchmark_parsers test_performance_optimization

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo ""
echo "Build successful! Running performance tests..."
echo "============================================="

# Run trivia optimization tests
echo ""
echo "=== Running Performance Optimization Tests ==="
./bin/test_performance_optimization

# Run parser benchmarks on test files
echo ""
echo "=== Running Parser Benchmarks ==="
./bin/benchmark_parsers

echo ""
echo "Performance benchmarks completed!"
echo "Check the output above for detailed performance metrics."