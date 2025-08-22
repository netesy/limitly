#!/bin/bash

echo "========================================"
echo "Running Limit Language Test Suite (Verbose)"
echo "========================================"

LIMITLY="./bin/limitly.exe"
FAILED=0
PASSED=0
TOTAL=0

run_test_verbose() {
    TOTAL=$((TOTAL + 1))
    echo ""
    echo "----------------------------------------"
    echo "Running $1"
    echo "----------------------------------------"
    "$LIMITLY" "$1"
    if [ $? -eq 0 ]; then
        echo "  RESULT: PASS"
        PASSED=$((PASSED + 1))
    else
        echo "  RESULT: FAIL"
        FAILED=$((FAILED + 1))
    fi
}

echo ""
echo "=== BASIC TESTS ==="
run_test_verbose "tests/basic/variables.lm"
run_test_verbose "tests/basic/literals.lm"
run_test_verbose "tests/basic/control_flow.lm"
run_test_verbose "tests/basic/print_statements.lm"

echo ""
echo "=== EXPRESSION TESTS ==="
run_test_verbose "tests/expressions/arithmetic.lm"
run_test_verbose "tests/expressions/comparison.lm"
run_test_verbose "tests/expressions/logical.lm"
run_test_verbose "tests/expressions/ranges.lm"

echo ""
echo "=== STRING TESTS ==="
run_test_verbose "tests/strings/interpolation.lm"
run_test_verbose "tests/strings/operations.lm"

echo ""
echo "=== LOOP TESTS ==="
run_test_verbose "tests/loops/for_loops.lm"
run_test_verbose "tests/loops/iter_loops.lm"
run_test_verbose "tests/loops/while_loops.lm"

echo ""
echo "=== FUNCTION TESTS ==="
run_test_verbose "tests/functions/basic_functions.lm"
run_test_verbose "tests/functions/advanced_functions.lm"

echo ""
echo "=== CLASS TESTS ==="
run_test_verbose "tests/classes/basic_classes.lm"
run_test_verbose "tests/classes/inheritance.lm"

echo ""
echo "=== CONCURRENCY TESTS ==="
run_test_verbose "tests/concurrency/parallel_blocks.lm"
run_test_verbose "tests/concurrency/concurrent_blocks.lm"

echo ""
echo "=== INTEGRATION TESTS ==="
run_test_verbose "tests/integration/comprehensive.lm"
run_test_verbose "tests/integration/error_handling.lm"

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
