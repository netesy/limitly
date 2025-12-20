#!/bin/bash

LIMITLY="./bin/limitly"
FAILED=0
PASSED=0
TOTAL=0

run_jit_test() {
    ((TOTAL++))
    local test_file="$1"
    local base_name="${test_file%.lm}"
    local exp_file="$base_name.exp"
    local out_file="$base_name.out"
    local exec_file="$base_name"

    echo "Running JIT test: $test_file..."

    # Compile with -jit flag
    "$LIMITLY" -jit "$test_file" -o "$exec_file"
    if [ $? -ne 0 ]; then
        echo "  FAIL: Compilation failed"
        ((FAILED++))
        return
    fi

    # Run the executable
    "./$exec_file" > "$out_file"
    if [ $? -ne 0 ]; then
        echo "  FAIL: Execution failed"
        ((FAILED++))
        rm "$exec_file" "$out_file"
        return
    fi

    # Compare output with expected
    if ! diff -u "$exp_file" "$out_file"; then
        echo "  FAIL: Output mismatch"
        ((FAILED++))
    else
        echo "  PASS"
        ((PASSED++))
    fi

    rm "$exec_file" "$out_file"
}


echo "========================================"
echo "Running Limit JIT Test Suite"
echo "========================================"
echo

run_jit_test "tests/jit/string_test.lm"
run_jit_test "tests/jit/string_var_test.lm"

echo
echo "========================================"
echo "JIT Test Results:"
echo "  PASSED: $PASSED"
echo "  FAILED: $FAILED"
echo "  TOTAL:  $TOTAL"
echo "========================================"

if [ "$FAILED" -gt 0 ]; then
    echo "Some JIT tests failed!"
    exit 1
else
    echo "All JIT tests passed!"
    exit 0
fi
