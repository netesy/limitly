#!/usr/bin/env python3
"""
Unified Test Harness for Lymar Compiler
Runs positive, build, negative, and fuzzing tests to prevent regressions.
"""

import subprocess
import sys
import os
from pathlib import Path

def run_command(cmd, cwd=None):
    """Run a command and return (success, output, stderr)"""
    try:
        result = subprocess.run(
            cmd,
            cwd=cwd,
            shell=True,
            capture_output=True,
            text=True,
            timeout=300  # 5 minute timeout
        )
        return result.returncode == 0, result.stdout, result.stderr
    except subprocess.TimeoutExpired:
        return False, "", "Command timed out"
    except Exception as e:
        return False, "", str(e)

def main():
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    python_bin = sys.executable or "python3"

    print("=" * 70)
    print("Unified Test Harness for Lymar Compiler")
    print("=" * 70)
    print()

    # Track overall success
    all_passed = True

    # 1. POSITIVE TESTS
    print("Running POSITIVE tests...")
    print("-" * 70)
    success, stdout, stderr = run_command(
        f"{python_bin} tests/run_tests.py",
        cwd=project_root
    )

    if success:
        print("[x] POSITIVE tests PASSED")
        for line in stdout.split('\n'):
            if 'Summary:' in line or 'PASSED=' in line:
                print(f"    {line}")
    else:
        print("[ ] POSITIVE tests FAILED")
        all_passed = False
        lines = stdout.split('\n')
        for line in lines[-10:]:
            if line.strip():
                print(f"    {line}")

    print()

    # 2. BUILD TESTS
    print("Running BUILD tests...")
    print("-" * 70)
    success, stdout, stderr = run_command(
        f"{python_bin} tests/build_tests.py",
        cwd=project_root
    )

    if success:
        print("[x] BUILD tests PASSED")
        for line in stdout.split('\n'):
            if 'executions:' in line:
                print(f"    {line}")
    else:
        print("[ ] BUILD tests FAILED")
        all_passed = False
        lines = (stdout + stderr).split('\n')
        for line in lines[-10:]:
            if line.strip():
                print(f"    {line}")

    print()

    # 3. NEGATIVE TESTS
    print("Running NEGATIVE tests...")
    print("-" * 70)
    success, stdout, stderr = run_command(
        f"{python_bin} tests/negative/run_negative_tests.py",
        cwd=project_root
    )

    if success:
        print("[x] NEGATIVE tests PASSED")
        for line in stdout.split('\n'):
            if 'SUMMARY:' in line or 'PASSED' in line:
                print(f"    {line}")
    else:
        print("[ ] NEGATIVE tests FAILED")
        all_passed = False
        lines = stdout.split('\n')
        for line in lines:
            if 'SUMMARY:' in line or 'BY CATEGORY:' in line:
                print(f"    {line}")

    print()

    # 4. FUZZING TESTS
    print("Running FUZZING tests...")
    print("-" * 70)
    success, stdout, stderr = run_command(
        f"{python_bin} tests/fuzz_test_suite.py --num-runs 20",
        cwd=project_root
    )

    if success:
        print("[x] FUZZING tests PASSED")
        for line in stdout.split('\n'):
            if 'Total Fuzz Runs' in line or 'Passed/Detected' in line:
                print(f"    {line}")
    else:
        print("[ ] FUZZING tests FAILED")
        all_passed = False
        lines = stdout.split('\n')
        for line in lines[-10:]:
            if line.strip():
                print(f"    {line}")

    print()
    print("=" * 70)

    if all_passed:
        print("[x] ALL TESTS PASSED")
        print("=" * 70)
        return 0
    else:
        print("[ ] SOME TESTS FAILED")
        print("=" * 70)
        print()
        print("Run individual test suites for details:")
        print(f"  {python_bin} tests/run_tests.py             # Positive tests")
        print(f"  {python_bin} tests/build_tests.py           # Build tests")
        print(f"  {python_bin} tests/negative/run_negative_tests.py # Negative tests")
        print(f"  {python_bin} tests/fuzz_test_suite.py       # Fuzzing tests")
        return 1

if __name__ == "__main__":
    sys.exit(main())
