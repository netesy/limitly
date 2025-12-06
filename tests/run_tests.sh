#!/bin/bash
echo "========================================"
echo "Running Limit Language Test Suite"
echo "========================================"

LIMITLY="./bin/limitly"
FAILED=0
PASSED=0
TOTAL=0

run_test_with_error_check() {
    let TOTAL+=1
    echo "Running $1..."

    TEMP_FILE=$(mktemp)
    "$LIMITLY" "$1" > "$TEMP_FILE" 2>&1

    if grep -q -E "error[E]|Error:|RuntimeError|SemanticError|BytecodeError" "$TEMP_FILE"; then
        echo "  FAIL: $1 (contains errors)"
        echo "  Error output:"
        grep -E "error[E]|Error:|RuntimeError|SemanticError|BytecodeError" "$TEMP_FILE"
        let FAILED+=1
    else
        echo "  PASS: $1"
        let PASSED+=1
    fi

    rm "$TEMP_FILE"
}


echo ""
echo "=== MODULE TESTS (focused) ==="

echo ""
echo "=== MODULE TESTS ==="
run_test_with_error_check "tests/modules/basic_import_test.lm"
run_test_with_error_check "tests/modules/comprehensive_module_test.lm"
run_test_with_error_check "tests/modules/show_filter_test.lm"
run_test_with_error_check "tests/modules/hide_filter_test.lm"
run_test_with_error_check "tests/modules/module_caching_test.lm"
run_test_with_error_check "tests/modules/error_cases_test.lm"
run_test_with_error_check "tests/modules/function_params_test.lm"
run_test_with_error_check "tests/modules/module_function_calls_test.lm"


echo ""
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
