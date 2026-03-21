#!/bin/bash

LIMITLY="./bin/limitly"
FAILED=0
PASSED=0
TOTAL=0

# Ensure limitly is built
if [ ! -f "$LIMITLY" ]; then
    echo "Error: $LIMITLY not found. Please run 'make' first."
    exit 1
fi

run_aot_test() {
    ((TOTAL++))
    SOURCE_FILE=$1
    echo "Running AOT Test: $SOURCE_FILE..."

    # Determine output executable name (same as source file without .lm)
    EXE_FILE="${SOURCE_FILE%.lm}"

    # Clean up any existing executable
    rm -f "$EXE_FILE"

    # Build the AOT executable
    # Usage: build [target] [arch] [opt_level] <source_file>
    "$LIMITLY" build linux x86_64 2 "$SOURCE_FILE" > /dev/null 2>&1
    BUILD_STATUS=$?

    if [ $BUILD_STATUS -ne 0 ]; then
        echo "  FAIL: $SOURCE_FILE (AOT compilation failed)"
        ((FAILED++))
        return
    fi

    if [ ! -f "$EXE_FILE" ]; then
        echo "  FAIL: $SOURCE_FILE (Executable not produced)"
        ((FAILED++))
        return
    fi

    # Run the executable and capture output
    TEMP_FILE=$(mktemp)
    # We need to make sure it's executable
    chmod +x "$EXE_FILE"
    ./"$EXE_FILE" > "$TEMP_FILE" 2>&1
    RUN_STATUS=$?

    if [ $RUN_STATUS -ne 0 ]; then
        echo "  FAIL: $SOURCE_FILE (Runtime crash with status $RUN_STATUS)"
        echo "  Output:"
        cat "$TEMP_FILE"
        ((FAILED++))
    else
        # For now, we just check if it ran without crashing.
        # In the future, we should compare output with expected results.
        echo "  PASS: $SOURCE_FILE"
        ((PASSED++))
    fi

    rm "$TEMP_FILE"
    rm "$EXE_FILE"
}

echo "========================================"
echo "Running Limit AOT Test Suite (Fyra Backend)"
echo "========================================"
echo

echo "=== BASIC AOT TESTS ==="
run_aot_test "tests/basic/variables.lm"
run_aot_test "tests/basic/literals.lm"
run_aot_test "tests/basic/control_flow.lm"
run_aot_test "tests/basic/print_statements.lm"

echo
echo "=== EXPRESSION AOT TESTS ==="
run_aot_test "tests/expressions/arithmetic.lm"
run_aot_test "tests/expressions/logical.lm"

echo
echo "=== LOOP AOT TESTS ==="
run_aot_test "tests/loops/for_loops.lm"
run_aot_test "tests/loops/while_loops.lm"

echo
echo "=== FUNCTION AOT TESTS ==="
run_aot_test "tests/functions/basic.lm"

echo
echo "========================================"
echo "AOT Test Results:"
echo "  PASSED: $PASSED"
echo "  FAILED: $FAILED"
echo "  TOTAL:  $TOTAL"
echo "========================================"

if [ "$FAILED" -gt 0 ]; then
    echo "Some AOT tests failed!"
    exit 1
else
    echo "All AOT tests passed!"
    exit 0
fi
