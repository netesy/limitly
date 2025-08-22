#!/bin/bash

echo "========================================"
echo "Running Limit Language Test Suite"
echo "========================================"

LIMITLY="./bin/limitly.exe"
FAILED=0
PASSED=0
TOTAL=0

run_test() {
    TOTAL=$((TOTAL + 1))
    echo "Running $1..."
    "$LIMITLY" "$1" >/dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "  PASS: $1"
        PASSED=$((PASSED + 1))
    else
        echo "  FAIL: $1"
        FAILED=$((FAILED + 1))
    fi
}

echo ""
echo "=== BASIC TESTS ==="
run_test "tests/basic/variables.lm"
run_test "tests/basic/literals.lm"
run_test "tests/basic/control_flow.lm"
run_test "tests/basic/print_statements.lm"

echo ""
echo "=== EXPRESSION TESTS ==="
run_test "tests/expressions/arithmetic.lm"
run_test "tests/expressions/comparison.lm"
run_test "tests/expressions/logical.lm"
run_test "tests/expressions/ranges.lm"

echo ""
echo "=== STRING TESTS ==="
run_test "tests/strings/interpolation.lm"
run_test "tests/strings/operations.lm"

echo ""
echo "=== LOOP TESTS ==="
run_test "tests/loops/for_loops.lm"
run_test "tests/loops/iter_loops.lm"
run_test "tests/loops/while_loops.lm"

echo ""
echo "=== FUNCTION TESTS ==="
run_test "tests/functions/basic_functions.lm"
run_test "tests/functions/advanced_functions.lm"

echo ""
echo "=== CLASS TESTS ==="
run_test "tests/classes/basic_classes.lm"
run_test "tests/classes/inheritance.lm"

echo ""
echo "=== CONCURRENCY TESTS ==="
run_test "tests/concurrency/parallel_blocks.lm"
run_test "tests/concurrency/concurrent_blocks.lm"

echo ""
echo "=== INTEGRATION TESTS ==="
run_test "tests/integration/comprehensive.lm"
run_test "tests/integration/error_handling.lm"

echo ""
echo "========================================"
echo "Test Results:"
echo "  PASSED: $PASSED"
echo "  FAILED: $FAILED"
echo "  TOTAL:  $TOTAL"
echo "========================================"

if [ $FAILED -gt 0 ]; then
    echo "Some tests failed!"
    exit 1
else
    echo "All tests passed!"
    exit 0
fi
