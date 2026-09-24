#!/bin/bash
set -e

# Delegate to build_tests.py which runs valid AOT tests and checks expected output
python3 "$(dirname "$0")/build_tests.py" "$@"
