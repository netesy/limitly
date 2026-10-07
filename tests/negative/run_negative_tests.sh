#!/bin/bash
# Negative Test Runner for Lymar Language (Linux/macOS)
# Tests that programs SHOULD FAIL compilation/execution

LYMAR_PATH="${LYMAR_PATH:-./bin/lymar}"

if [ ! -f "$LYMAR_PATH" ]; then
    echo "Error: Lymar executable not found at $LYMAR_PATH"
    exit 1
fi

# Run negative tests with Python
python3 tests/negative/run_negative_tests.py -p "$LYMAR_PATH" "$@"
exit $?
