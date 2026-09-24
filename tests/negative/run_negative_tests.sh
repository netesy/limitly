#!/bin/bash
# Negative Test Runner for Limitly Language (Linux/macOS)
# Tests that programs SHOULD FAIL compilation/execution

LIMITLY_PATH="${LIMITLY_PATH:-./bin/limitly}"

if [ ! -f "$LIMITLY_PATH" ]; then
    echo "Error: Limitly executable not found at $LIMITLY_PATH"
    exit 1
fi

# Run negative tests with Python
python3 tests/negative/run_negative_tests.py -p "$LIMITLY_PATH" "$@"
exit $?
