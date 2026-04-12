#!/bin/bash
FAILED=0
PASSED=0
TOTAL=0
EXCLUDE_LIST=(
    "tests/functions/first_class.lm"
    "tests/types/enums.lm"
)
is_excluded() {
    for excluded in "${EXCLUDE_LIST[@]}"; do
        if [[ "$1" == "$excluded" ]]; then
            return 0
        fi
    done
    return 1
}
run_aot_windows_test() {
    local source_file=$1
    if is_excluded "$source_file"; then
        echo "Skipping excluded test: $source_file"
        return
    fi
    TOTAL=$((TOTAL + 1))
    echo "Running Windows AOT Test: $source_file..."
    local exe_file="${source_file%.lm}.exe"
    ./bin/limitly build windows x86_64 2 "$source_file" > /dev/null 2>&1
    if [ ! -f "$exe_file" ]; then
        echo "  FAIL: $source_file (AOT compilation failed)"
        FAILED=$((FAILED + 1))
        return
    fi
    wine "$exe_file" > /dev/null 2>&1
    local run_status=$?
    if [ $run_status -ne 0 ]; then
        echo "  FAIL: $source_file (Wine execution failed with status $run_status)"
        FAILED=$((FAILED + 1))
    else
        echo "  PASS: $source_file"
        PASSED=$((PASSED + 1))
    fi
    rm -f "$exe_file"
}
echo "========================================"
echo "Running Limit Windows AOT Test Suite"
echo "========================================"
for f in tests/basic/*.lm; do run_aot_windows_test "$f"; done
for f in tests/expressions/*.lm; do run_aot_windows_test "$f"; done
for f in tests/loops/*.lm; do run_aot_windows_test "$f"; done
for f in tests/functions/*.lm; do run_aot_windows_test "$f"; done
for f in tests/types/*.lm; do run_aot_windows_test "$f"; done
echo "========================================"
echo "Windows AOT Test Results:"
echo "  PASSED: $PASSED"
echo "  FAILED: $FAILED"
echo "  TOTAL:  $TOTAL"
echo "========================================"
