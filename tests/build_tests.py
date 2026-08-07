#!/usr/bin/env python3
import sys
import os
import subprocess
import time
import difflib

# Add project root and script directory to sys.path to allow imports
script_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.dirname(script_dir)
if project_root not in sys.path:
    sys.path.insert(0, project_root)
if script_dir not in sys.path:
    sys.path.insert(0, script_dir)

try:
    from tests.run_tests import tests, slow_tests, limitly_path
except ImportError:
    # Fallback/Direct import if run_tests is in the current directory
    from run_tests import tests, slow_tests, limitly_path

# Target platform detection
if os.name == 'nt':
    target_platform = "windows"
elif sys.platform == 'darwin':
    target_platform = "macos"
else:
    target_platform = "linux"

total = 0
passed = 0
failed = 0
build_failures = 0
runtime_failures = 0
output_mismatches = 0
timeouts = 0

print("====================================================")
print(f"Running Limitly AOT Validation Tests ({target_platform.upper()})")
print("====================================================")

for test in tests:
    test_path = os.path.normpath(test)
    if not os.path.exists(test_path):
        print(f"Skipping {test_path} (does not exist)")
        continue

    total += 1
    print(f"Testing {test_path}...")

    # 1. Run the test with the interpreter to get the expected output
    try:
        interpreter_res = subprocess.run(
            [limitly_path, "run", test_path],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            timeout=30.0
        )
        expected_stdout = interpreter_res.stdout
        expected_stderr = interpreter_res.stderr
        expected_exit_code = interpreter_res.returncode
    except subprocess.TimeoutExpired:
        # If the interpreter itself times out, we cannot validate.
        print(f"  [SKIPPED] Interpreter timed out on {test_path}")
        total -= 1
        continue
    except Exception as e:
        print(f"  [SKIPPED] Interpreter failed to run {test_path}: {e}")
        total -= 1
        continue

    # 2. Determine platform-specific executable name
    output_bin = test_path[:-3] # remove '.lm'
    if os.name == 'nt':
        output_bin += ".exe"
    output_bin = os.path.abspath(output_bin)

    # 3. Build using Fyra backend
    build_cmd = [
        limitly_path, "build",
        "-target", target_platform,
        "-O", "2",
        "-o", output_bin,
        test_path
    ]

    build_success = False
    try:
        build_res = subprocess.run(
            build_cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            timeout=30.0
        )
        if build_res.returncode == 0 and os.path.exists(output_bin):
            build_success = True
        else:
            build_reason = f"limitly build exited with code {build_res.returncode}"
            build_stdout = build_res.stdout
            build_stderr = build_res.stderr
    except subprocess.TimeoutExpired:
        build_reason = "limitly build timed out (30s limit)"
        build_stdout = ""
        build_stderr = ""
    except Exception as e:
        build_reason = f"limitly build failed to execute: {e}"
        build_stdout = ""
        build_stderr = ""

    if not build_success:
        print(f"  [FAIL] Build Failed: {test_path}")
        print(f"  Reason: {build_reason}")
        if build_stdout:
            print("  --- Build STDOUT ---")
            print(build_stdout)
        if build_stderr:
            print("  --- Build STDERR ---")
            print(build_stderr)
        build_failures += 1
        failed += 1
        continue

    # 4. Execute the generated binary
    actual_stdout = ""
    actual_stderr = ""
    actual_exit_code = -1
    run_timeout = False
    run_exception = None

    try:
        # Enforce maximum runtime of 30 seconds
        run_res = subprocess.run(
            [output_bin],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            timeout=30.0
        )
        actual_stdout = run_res.stdout
        actual_stderr = run_res.stderr
        actual_exit_code = run_res.returncode
    except subprocess.TimeoutExpired:
        run_timeout = True
    except Exception as e:
        run_exception = e

    # Clean up generated executable
    if os.path.exists(output_bin):
        try:
            os.remove(output_bin)
        except Exception:
            pass

    # 5. Validation and Reporting
    if run_timeout:
        print(f"  [FAIL] Timeout: {test_path}")
        print("  Reason: Executable exceeded maximum runtime of 30 seconds")
        timeouts += 1
        failed += 1
        continue

    if run_exception:
        print(f"  [FAIL] Runtime Failure: {test_path}")
        print(f"  Reason: Failed to execute binary: {run_exception}")
        runtime_failures += 1
        failed += 1
        continue

    if actual_exit_code != 0:
        print(f"  [FAIL] Runtime Failure: {test_path}")
        print(f"  Reason: Executable exited with non-zero status code: {actual_exit_code}")
        print("  Expected Output:")
        print(expected_stdout)
        print("  Actual Output:")
        print(actual_stdout)
        if actual_stderr:
            print("  Actual STDERR:")
            print(actual_stderr)
        runtime_failures += 1
        failed += 1
        continue

    # Check exact match for stdout and stderr
    stdout_match = (actual_stdout == expected_stdout)
    stderr_match = (actual_stderr == expected_stderr)

    if stdout_match and stderr_match:
        print(f"  [PASS] {test_path}")
        passed += 1
    else:
        print(f"  [FAIL] Output Mismatch: {test_path}")
        print(f"  Exit code: {actual_exit_code}")

        # Determine specific failure reason
        if not stdout_match and not stderr_match:
            print("  Reason: Standard output and standard error mismatches")
        elif not stdout_match:
            print("  Reason: Standard output mismatch")
        else:
            print("  Reason: Standard error mismatch")

        print("  Expected Output:")
        print(expected_stdout)
        print("  Actual Output:")
        print(actual_stdout)

        # Show unified diffs
        if not stdout_match:
            print("  --- STDOUT Diff (Expected vs Actual) ---")
            expected_lines = expected_stdout.splitlines(keepends=True)
            actual_lines = actual_stdout.splitlines(keepends=True)
            diff = difflib.unified_diff(
                expected_lines,
                actual_lines,
                fromfile="expected_stdout",
                tofile="actual_stdout"
            )
            print("".join(diff))

        if not stderr_match:
            print("  --- STDERR Diff (Expected vs Actual) ---")
            expected_lines = expected_stderr.splitlines(keepends=True)
            actual_lines = actual_stderr.splitlines(keepends=True)
            diff = difflib.unified_diff(
                expected_lines,
                actual_lines,
                fromfile="expected_stderr",
                tofile="actual_stderr"
            )
            print("".join(diff))

        output_mismatches += 1
        failed += 1

print("\n====================================================")
print("AOT Validation Summary:")
print("====================================================")
print(f"Total tests:       {total}")
print(f"Passed:            {passed}")
print(f"Failed:            {failed}")
print(f"  Build failures:  {build_failures}")
print(f"  Runtime failures:{runtime_failures}")
print(f"  Output mismatches:{output_mismatches}")
print(f"  Timeouts:        {timeouts}")
print("====================================================")

if failed > 0:
    sys.exit(1)
else:
    sys.exit(0)
