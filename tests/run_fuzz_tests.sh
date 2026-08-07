#!/usr/bin/env bash
# Wrapper script to run the Limitly Fuzzy Test Suite.
# It automatically runs the Python test suite and passes through any command line arguments.

set -e

# Resolve paths
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
FUZZ_SUITE_PY="${SCRIPT_DIR}/fuzz_test_suite.py"

# Check if python3 is available
if ! command -v python3 &> /dev/null; then
    echo "❌ Error: python3 is not installed or not in PATH."
    exit 1
fi

# Run the fuzzy test suite
python3 "${FUZZ_SUITE_PY}" "$@"
