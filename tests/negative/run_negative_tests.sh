#!/bin/bash
# Negative Test Runner for Lymar Language (Linux/macOS)
# Tests that programs SHOULD FAIL compilation/execution

LIMITLY_PATH="${LIMITLY_PATH:-./bin/lymar}"

if [ ! -f "$LIMITLY_PATH" ]; then
    echo "Error: Lymar executable not found at $LIMITLY_PATH"
    exit 1
fi

# Run negative tests with Python
python3 tests/negative/run_negative_tests.py -p "$LIMITLY_PATH" "$@"
exit $?
