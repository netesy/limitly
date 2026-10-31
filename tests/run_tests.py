"""
Lymar Test Suite Runner
"""

import subprocess
import sys
import os
import glob
import time

lymar_path = os.path.abspath(os.environ.get("LYMAR_EXECUTABLE", "bin/lymar.exe" if os.name == "nt" else "bin/lymar"))

# LYMAR_NO_CACHE=1 compiles every test cold. A cached artifact can make a broken
# source file look green, so use this when std/ or the compiler changed.
no_cache = os.environ.get("LYMAR_NO_CACHE", "") == "1"

def load_tests_from_file(file_path):
    test_files = []
    if not os.path.exists(file_path):
        return test_files
    with open(file_path, "r") as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith("#"):
                test_files.append(line)
    return test_files

test_manifest_path = os.path.join(os.path.dirname(__file__), "test.txt")
tests = load_tests_from_file(test_manifest_path)

# Tests that need extra time (resource creation, crypto, network)
slow_tests = {
 "tests/lir/devirtualization_lir_test.lm",
 "tests/stdlib/crypto/hash_test.lm",
 "tests/stdlib/net/net_test.lm",
 "tests/stdlib/io/io_extended_test.lm",
 "tests/stdlib/semver_test.lm",
 "tests/stdlib/math_module_test.lm",
 "tests/stdlib/io_module_test.lm",
 "tests/stdlib/fs_module_test.lm",
 "tests/stdlib/path_module_test.lm",
 "tests/stdlib/env_module_test.lm",
 "tests/stdlib/process_module_test.lm",
 "tests/stdlib/time_module_test.lm",
 "tests/stdlib/random_module_test.lm",
 "tests/stdlib/parse_module_test.lm",
 "tests/stdlib/format_module_test.lm",
 "tests/interactive_controls_test.lm",
 "tests/ffi/test_font_lib.lm",
 "tests/stdlib/collections/queue_stack_bitset_test.lm",
}

if __name__ == "__main__":
    passed = 0
    failed = 0
    hung = 0

    print("====================================================")
    print("Running Lymar Tests Individually (3s/10s Timeout)")
    print("====================================================")

    for test in tests:
        test_path = os.path.normpath(test)
        if not os.path.exists(test_path):
            print(f"Skipping {test_path} (does not exist)")
            continue

        timeout = (25.0 if test in slow_tests else 3.0) * float(os.environ.get(
            "LYMAR_TEST_TIMEOUT_SCALE", "8" if no_cache else "1"))
        cmd = [lymar_path, "run", test_path]
        if no_cache:
            cmd.append("--no-cache")
        start_time = time.time()
        try:
            res = subprocess.run(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=timeout
            )
            duration = time.time() - start_time

            # Check output for typical error patterns
            has_error_pattern = False
            for pattern in ["error[E", "Error:", "RuntimeError", "SemanticError", "BytecodeError", "[ ] FAIL", "ASSERT FAIL", "Assertion failed"]:
                if pattern in res.stdout or pattern in res.stderr:
                    has_error_pattern = True
                    break

            if res.returncode == 0 and not has_error_pattern:
                print(f"PASS: {test} ({duration:.2f}s)")
                passed += 1
            else:
                print(f"FAIL: {test} (exit code: {res.returncode})")
                print("--- STDOUT ---")
                print(res.stdout)
                print("--- STDERR ---")
                print(res.stderr)
                print("--------------")
                failed += 1

        except subprocess.TimeoutExpired:
            print(f"HANG / TIMEOUT: {test} (killed after {timeout}s)")
            hung += 1
            failed += 1

    print("====================================================")
    print(f"Summary: PASSED={passed}, FAILED={failed} (including HUNG={hung})")
    print("====================================================")

    if failed > 0:
        sys.exit(1)
    else:
        sys.exit(0)
