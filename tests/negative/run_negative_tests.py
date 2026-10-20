#!/usr/bin/env python3
"""
Negative Test Runner for Lymar Language
==========================================

Tests programs that SHOULD FAIL to compile or execute.
These tests verify that the compiler correctly rejects invalid programs
and provides appropriate error messages.
"""

import subprocess
import sys
import os
import json
from pathlib import Path
from dataclasses import dataclass
from typing import List, Dict, Optional
import time


@dataclass
class NegativeTest:
    """Represents a negative test case."""
    path: str
    category: str
    expected_error: str # Error category or pattern to expect
    description: str = ""

    def __hash__(self):
        return hash(self.path)

    def __eq__(self, other):
        if not isinstance(other, NegativeTest):
            return False
        return self.path == other.path


@dataclass
class TestResult:
    """Result of a single test execution."""
    test: NegativeTest
    passed: bool
    error_found: bool
    error_type: Optional[str]
    error_message: str
    stdout: str
    stderr: str
    duration: float
    exit_code: int


class NegativeTestRunner:
    """Runs negative tests and validates error handling."""

    VALID_ERROR_CATEGORIES = {
        "type_error", "use_after_free", "double_free", "dangling_ref",
        "uninitialized", "bounds_error", "divide_by_zero", "overflow",
        "null_deref", "race_condition", "break_outside_loop",
        "continue_outside_loop", "return_in_global", "pattern_exhaustive",
        "closure_capture", "memory_leak", "ffi_safety", "syntax_error",
        "visibility_error", "trait_not_impl", "const_expr",
        "generic_mismatch", "move_error", "shift_error",
    }

    def __init__(self, lymar_path: str, verbose: bool = False):
        self.lymar_path = lymar_path
        self.verbose = verbose
        self.results: List[TestResult] = []
        self.test_dir = Path("tests/negative")

    def discover_tests(self) -> List[NegativeTest]:
        """Discover all negative test files."""
        tests: List[NegativeTest] = []

        if not self.test_dir.exists():
            print(f"Warning: negative test directory {self.test_dir} does not exist")
            return tests

        for category_dir in sorted(self.test_dir.iterdir()):
            if not category_dir.is_dir():
                continue

            category = category_dir.name
            if category.startswith("_"):
                continue

            for test_file in sorted(category_dir.glob("*.lm")):
                test = NegativeTest(
                    path=str(test_file),
                    category=category,
                    expected_error=self._load_expected_error(test_file),
                    description=self._load_description(test_file)
                )
                tests.append(test)

        return tests

    def _load_expected_error(self, test_file: Path) -> str:
        """Load expected error from comment or metadata file."""
        json_file = test_file.with_suffix(".json")
        if json_file.exists():
            try:
                with open(json_file) as f:
                    data = json.load(f)
                    return data.get("expected_error", "syntax_error")
            except Exception:
                pass

        try:
            with open(test_file) as f:
                first_line = f.readline().strip()
                if first_line.startswith("//") and "@error:" in first_line:
                    return first_line.split("@error:")[1].strip()
        except Exception:
            pass

        return "syntax_error"

    def _load_description(self, test_file: Path) -> str:
        """Load description from second comment line."""
        try:
            with open(test_file) as f:
                lines = f.readlines()
                if len(lines) > 1 and lines[1].startswith("//"):
                    return lines[1].strip()[2:].strip()
        except Exception:
            pass
        return ""

    def run_test(self, test: NegativeTest) -> TestResult:
        """Run a single negative test."""
        start = time.time()

        try:
            result = subprocess.run(
                [self.lymar_path, "run", test.path],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=5.0
            )
            duration = time.time() - start

            if test.expected_error == "nil_bounds":
                has_error_pattern = False
                combined = result.stdout + result.stderr
                for pattern in ["error[E", "Error:", "RuntimeError", "SemanticError", "BytecodeError", "[ ] FAIL", "ASSERT FAIL", "Assertion failed"]:
                    if pattern in combined:
                        has_error_pattern = True
                        break
                passed = (result.returncode == 0) and not has_error_pattern
                error_type = "nil_bounds" if passed else "bounds_checking_failure"
                error_found = not passed
            else:
                error_found = result.returncode != 0
                error_type = self._detect_error_type(result)
                passed = error_found

            return TestResult(
                test=test,
                passed=passed,
                error_found=error_found,
                error_type=error_type,
                error_message=self._extract_error_message(result),
                stdout=result.stdout,
                stderr=result.stderr,
                duration=duration,
                exit_code=result.returncode
            )

        except subprocess.TimeoutExpired:
            duration = time.time() - start
            return TestResult(
                test=test,
                passed=False,
                error_found=False,
                error_type="timeout",
                error_message="Test exceeded 5 second timeout",
                stdout="",
                stderr="",
                duration=duration,
                exit_code=-1
            )
        except Exception as e:
            duration = time.time() - start
            return TestResult(
                test=test,
                passed=False,
                error_found=False,
                error_type="runner_error",
                error_message=str(e),
                stdout="",
                stderr="",
                duration=duration,
                exit_code=-1
            )

    def _detect_error_type(self, result: subprocess.CompletedProcess) -> Optional[str]:
        """Detect the error type from compiler output."""
        combined = result.stdout + result.stderr

        patterns = {
            "type_error": ["error[E", "type mismatch", "incompatible"],
            "use_after_free": ["use after free", "use-after-free", "dropped"],
            "double_free": ["double free", "double-free"],
            "dangling_ref": ["dangling", "reference", "freed memory"],
            "uninitialized": ["uninitialized", "not initialized"],
            "bounds_error": ["out of bounds", "bounds", "index"],
            "divide_by_zero": ["divide by zero", "division by zero"],
            "overflow": ["overflow", "too large"],
            "null_deref": ["null pointer", "null dereference"],
            "race_condition": ["race condition", "data race"],
            "break_outside_loop": ["break outside loop", "break not in loop"],
            "continue_outside_loop": ["continue outside loop", "continue not in loop"],
            "return_in_global": ["return in global"],
            "pattern_exhaustive": ["non-exhaustive", "exhaustiveness"],
            "closure_capture": ["closure", "capture"],
            "memory_leak": ["memory leak", "resource leak"],
            "ffi_safety": ["FFI", "unsafe"],
            "syntax_error": ["syntax error", "unexpected token", "expected"],
            "visibility_error": ["private", "not visible", "access denied"],
            "move_error": ["use after move", "double move", "moved value", "value moved"],
            "shift_error": ["negative shift", "shift overflow", "invalid shift"],
        }

        for error_type, error_patterns in patterns.items():
            for pattern in error_patterns:
                if pattern.lower() in combined.lower():
                    return error_type

        return None

    def _extract_error_message(self, result: subprocess.CompletedProcess) -> str:
        """Extract the first error message from output."""
        combined = result.stdout + "\n" + result.stderr
        lines = combined.split("\n")

        for line in lines:
            if "error" in line.lower() or "failed" in line.lower():
                return line.strip()

        return combined[:200] if combined else "Unknown error"

    def run_all(self, tests: List[NegativeTest]) -> None:
        """Run all negative tests."""
        if not tests:
            print("No negative tests found!")
            return

        print("=" * 70)
        print(f"Running {len(tests)} Negative Tests")
        print("=" * 70)
        print()

        by_category: Dict[str, List[NegativeTest]] = {}
        for test in tests:
            if test.category not in by_category:
                by_category[test.category] = []
            by_category[test.category].append(test)

        category_results: Dict[str, List[TestResult]] = {}
        total_passed = 0
        total_failed = 0

        for category in sorted(by_category.keys()):
            category_tests = by_category[category]
            print(f"\n[{category.upper()}] {len(category_tests)} tests")
            print("-" * 70)

            results = []
            for test in category_tests:
                result = self.run_test(test)
                results.append(result)

                if result.passed:
                    total_passed += 1
                    status = "[OK] PASS"
                else:
                    total_failed += 1
                    status = " FAIL"

                print(f" {status}: {Path(test.path).name}")
                if result.error_type:
                    print(f" Error: {result.error_type}")
                if test.description:
                    print(f" Desc: {test.description}")

                if self.verbose and not result.passed:
                    print(f" Output: {result.error_message}")

            category_results[category] = results

        print("\n" + "=" * 70)
        print(f"SUMMARY: {total_passed} PASSED, {total_failed} FAILED")
        print("=" * 70)

        if total_failed > 0:
            print("\nFAILURES:")
            for category in sorted(category_results.keys()):
                failures = [r for r in category_results[category] if not r.passed]
                if failures:
                    print(f"\n {category}:")
                    for result in failures:
                        print(f" - {Path(result.test.path).name}")
                        print(f" {result.error_message}")

        print("\nBY CATEGORY:")
        for category in sorted(category_results.keys()):
            results = category_results[category]
            passed = len([r for r in results if r.passed])
            total = len(results)
            pct = (passed / total * 100) if total > 0 else 0
            print(f" {category:20} {passed:3}/{total:3} ({pct:5.1f}%)")


def main():
    """Main entry point."""
    import argparse

    parser = argparse.ArgumentParser(
        description="Run negative tests for Lymar language"
    )
    parser.add_argument(
        "-v", "--verbose",
        action="store_true",
        help="Verbose output with error details"
    )
    parser.add_argument(
        "-p", "--path",
        default="bin/lymar.exe" if os.name == "nt" else "bin/lymar",
        help="Path to Lymar executable"
    )
    parser.add_argument(
        "-c", "--category",
        help="Run only tests in specific category"
    )
    parser.add_argument(
        "--list",
        action="store_true",
        help="List all discovered tests and exit"
    )

    args = parser.parse_args()

    lymar_path = os.path.abspath(args.path)
    if not os.path.exists(lymar_path):
        print(f"Error: Lymar executable not found at {lymar_path}")
        sys.exit(1)

    runner = NegativeTestRunner(lymar_path, verbose=args.verbose)
    tests = runner.discover_tests()

    if args.list:
        print(f"Found {len(tests)} negative tests:")
        for test in sorted(tests, key=lambda t: t.category):
            print(f" [{test.category:15}] {test.path}")
        return

    if args.category:
        tests = [t for t in tests if t.category == args.category]
        if not tests:
            print(f"No tests found in category: {args.category}")
            sys.exit(1)

    runner.run_all(tests)

    failed = len([r for r in runner.results if not r.passed])
    sys.exit(1 if failed > 0 else 0)


if __name__ == "__main__":
    main()
