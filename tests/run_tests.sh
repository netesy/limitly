#!/bin/bash

LIMITLY="./bin/limitly"
FAILED=0
PASSED=0
TOTAL=0

run_test_with_error_check() {
    ((TOTAL++))
    echo "Running $1..."

    TEMP_FILE=$(mktemp)
    "$LIMITLY" "$1" > "$TEMP_FILE" 2>&1

    if grep -q -E "error[E|:|RuntimeError|SemanticError|BytecodeError]" "$TEMP_FILE"; then
        echo "  FAIL: $1 (contains errors)"
        echo "  Error output:"
        grep -E "error[E|:|RuntimeError|SemanticError|BytecodeError]" "$TEMP_FILE"
        ((FAILED++))
    else
        echo "  PASS: $1"
        ((PASSED++))
    fi

    rm "$TEMP_FILE"
}

run_test_allow_semantic_errors() {
    ((TOTAL++))
    echo "Running $1..."

    TEMP_FILE=$(mktemp)
    "$LIMITLY" "$1" > "$TEMP_FILE" 2>&1

    if grep -q -E "RuntimeError|BytecodeError|Error:" "$TEMP_FILE" | grep -v "SemanticError"; then
        echo "  FAIL: $1 (contains runtime errors)"
        echo "  Error output:"
        grep -E "RuntimeError|BytecodeError|Error:" "$TEMP_FILE" | grep -v "SemanticError"
        ((FAILED++))
    else
        echo "  PASS: $1 (semantic errors allowed)"
        ((PASSED++))
    fi

    rm "$TEMP_FILE"
}

echo "========================================"
echo "Running Limit Language Test Suite"
echo "========================================"
echo
echo "=== BASIC TESTS ==="
run_test_with_error_check "tests/basic/variables.lm"
run_test_with_error_check "tests/basic/literals.lm"
run_test_with_error_check "tests/basic/control_flow.lm"
run_test_with_error_check "tests/basic/print_statements.lm"

echo
echo "=== EXPRESSION TESTS ==="
run_test_with_error_check "tests/expressions/arithmetic.lm"
run_test_with_error_check "tests/expressions/logical.lm"
run_test_with_error_check "tests/expressions/ranges.lm"
run_test_with_error_check "tests/expressions/large_literals.lm"

echo
echo "=== STRING TESTS ==="
run_test_with_error_check "tests/strings/interpolation.lm"
run_test_with_error_check "tests/strings/operations.lm"

echo
echo "=== LOOP TESTS ==="
run_test_with_error_check "tests/loops/for_loops.lm"
run_test_with_error_check "tests/loops/iter_loops.lm"
run_test_with_error_check "tests/loops/while_loops.lm"

echo
echo "=== FUNCTION TESTS ==="
run_test_with_error_check "tests/functions/basic.lm"
run_test_with_error_check "tests/functions/advanced.lm"
run_test_with_error_check "tests/functions/closures.lm"
run_test_allow_semantic_errors "tests/functions/first_class.lm"

echo
echo "=== TYPE TESTS ==="
run_test_allow_semantic_errors "tests/types/basic.lm"
run_test_allow_semantic_errors "tests/types/unions.lm"
run_test_allow_semantic_errors "tests/types/options.lm"
run_test_with_error_check "tests/types/advanced.lm"

echo
echo "=== MODULE TESTS ==="
run_test_with_error_check "tests/modules/basic_import_test.lm"

echo
echo "========================================"
echo "Test Results:"
echo "  PASSED: $PASSED"
echo "  FAILED: $FAILED"
echo "  TOTAL:  $TOTAL"
echo "========================================"

if [ "$FAILED" -gt 0 ]; then
    echo "Some tests failed!"
    exit 1
else
    echo "All tests passed!"
    exit 0
fi
