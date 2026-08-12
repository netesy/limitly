#!/usr/bin/env python3
"""
Negative Test Runner for Limitly Language
==========================================

Tests programs that SHOULD FAIL to compile or execute.
These tests verify that the compiler correctly rejects invalid programs
and provides appropriate error messages.

Each negative test is expected to:
1. Fail compilation with specific error categories
2. Produce meaningful error messages
3. Exit with non-zero status code

Test Organization:
- tests/negative/soundness/       - Memory safety, use-after-free, dangling refs, move semantics
- tests/negative/type_safety/     - Type errors, incompatible operations
- tests/negative/bounds_checking/ - Bounds checking, array/string/dict/tuple indexing
- tests/negative/concurrency/     - Race conditions, data races, parallel/concurrent safety
- tests/negative/memory/          - Resource leaks, uninit vars, file handle leaks
- tests/negative/patterns/        - Pattern matching exhaustiveness
- tests/negative/control_flow/    - Break/continue outside loops, return in global scope
- tests/negative/closures/        - Closure capture errors, lifetime violations
- tests/negative/arithmetic/      - Arithmetic overflow, divide by zero, shift errors
- tests/negative/syntax/          - Syntax errors
- tests/negative/traits/          - Trait implementation errors
- tests/negative/visibility/      - Visibility/access control errors
"""

import subprocess
import sys
import os
import json
from pathlib import Path
from dataclasses import dataclass
from typing import List, Dict, Optional, Set
import time


@dataclass
class NegativeTest:
    """Represents a negative test case."""
    path: str
    category: str
    expected_error: str  # Error category or pattern to expect
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
    
    # Error categories that the compiler should produce
    VALID_ERROR_CATEGORIES = {
        "type_error",           # Type mismatch, incompatible operations
        "use_after_free",       # Memory already freed/dropped
        "double_free",          # Freeing already-freed memory
        "dangling_ref",         # Reference to freed/dropped memory
        "uninitialized",        # Use of uninitialized variable
        "bounds_error",         # Array/string bounds violation
        "divide_by_zero",       # Division or modulo by zero
        "overflow",             # Arithmetic overflow
        "null_deref",           # Null pointer dereference
        "race_condition",       # Data race detected
        "break_outside_loop",   # Break statement outside loop
        "continue_outside_loop",# Continue statement outside loop
        "return_in_global",     # Return statement in global scope
        "pattern_exhaustive",   # Non-exhaustive pattern match
        "closure_capture",      # Invalid closure capture
        "memory_leak",          # Resource leak (var dropped without cleanup)
        "ffi_safety",           # FFI safety violation
        "syntax_error",         # Parser error
        "visibility_error",     # Private member access
        "trait_not_impl",       # Trait not implemented
        "const_expr",           # Non-const expr in const context
        "generic_mismatch",     # Generic type mismatch
        "move_error",           # Move semantics violations (use after move, double move)
        "shift_error",          # Invalid shift operations (negative shift, shift overflow)
    }
    
    def __init__(self, limitly_path: str, verbose: bool = False):
        self.limitly_path = limitly_path
        self.verbose = verbose
        self.results: List[TestResult] = []
        self.test_dir = Path("tests/negative")
    
    def discover_tests(self) -> List[NegativeTest]:
        """Discover all negative test files."""
        tests: List[NegativeTest] = []
        
        if not self.test_dir.exists():
            print(f"Warning: negative test directory {self.test_dir} does not exist")
            return tests
        
        # Scan subdirectories for test files
        for category_dir in sorted(self.test_dir.iterdir()):
            if not category_dir.is_dir():
                continue
            
            category = category_dir.name
            if category.startswith("_"):  # Skip internal dirs
                continue
            
            # Look for .lm files and .json metadata
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
        # First check for .json metadata
        json_file = test_file.with_suffix(".json")
        if json_file.exists():
            try:
                with open(json_file) as f:
                    data = json.load(f)
                    return data.get("expected_error", "syntax_error")
            except:
                pass
        
        # Fall back to reading first comment line
        try:
            with open(test_file) as f:
                first_line = f.readline().strip()
                if first_line.startswith("//"):
                    # Extract error type: // @error:type_error
                    if "@error:" in first_line:
                        error_type = first_line.split("@error:")[1].strip()
                        return error_type
        except:
            pass
        
        return "syntax_error"  # Default
    
    def _load_description(self, test_file: Path) -> str:
        """Load description from second comment line."""
        try:
            with open(test_file) as f:
                lines = f.readlines()
                if len(lines) > 1 and lines[1].startswith("//"):
                    desc = lines[1].strip()[2:].strip()
                    return desc
        except:
            pass
        return ""
    
    def run_test(self, test: NegativeTest) -> TestResult:
        """Run a single negative test."""
        start = time.time()
        
        try:
            result = subprocess.run(
                [self.limitly_path, "run", test.path],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=5.0
            )
            duration = time.time() - start
            
            # Check for error indicators
            if test.expected_error == "nil_bounds":
                # For bounds checking returning nil, we expect exit code 0 (safe execution)
                # and no errors reported on stdout/stderr
                has_error_pattern = False
                combined = result.stdout + result.stderr
                for pattern in ["error[E", "Error:", "RuntimeError", "SemanticError", "BytecodeError", "❌ FAIL", "ASSERT FAIL", "Assertion failed"]:
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
                passed=False,  # Timeout is a failure
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
        
        # Check for specific error patterns
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
        
        # Group by category
        by_category: Dict[str, List[NegativeTest]] = {}
        for test in tests:
            if test.category not in by_category:
                by_category[test.category] = []
            by_category[test.category].append(test)
        
        # Run tests by category
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
                    status = "✓ PASS"
                else:
                    total_failed += 1
                    status = "✗ FAIL"
                
                print(f"  {status}: {Path(test.path).name}")
                if result.error_type:
                    print(f"          Error: {result.error_type}")
                if test.description:
                    print(f"          Desc:  {test.description}")
                
                if self.verbose and not result.passed:
                    print(f"          Output: {result.error_message}")
            
            category_results[category] = results
        
        # Summary
        print("\n" + "=" * 70)
        print(f"SUMMARY: {total_passed} PASSED, {total_failed} FAILED")
        print("=" * 70)
        
        # Detailed failures
        if total_failed > 0:
            print("\nFAILURES:")
            for category in sorted(category_results.keys()):
                failures = [r for r in category_results[category] if not r.passed]
                if failures:
                    print(f"\n  {category}:")
                    for result in failures:
                        print(f"    - {Path(result.test.path).name}")
                        print(f"      {result.error_message}")
        
        # Stats by category
        print("\nBY CATEGORY:")
        for category in sorted(category_results.keys()):
            results = category_results[category]
            passed = len([r for r in results if r.passed])
            total = len(results)
            pct = (passed / total * 100) if total > 0 else 0
            print(f"  {category:20} {passed:3}/{total:3} ({pct:5.1f}%)")


def main():
    """Main entry point."""
    import argparse
    
    parser = argparse.ArgumentParser(
        description="Run negative tests for Limitly language"
    )
    parser.add_argument(
        "-v", "--verbose",
        action="store_true",
        help="Verbose output with error details"
    )
    parser.add_argument(
        "-p", "--path",
        default="bin/limitly.exe" if os.name == "nt" else "bin/limitly",
        help="Path to Limitly executable"
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
    
    # Get absolute path
    limitly_path = os.path.abspath(args.path)
    if not os.path.exists(limitly_path):
        print(f"Error: Limitly executable not found at {limitly_path}")
        sys.exit(1)
    
    runner = NegativeTestRunner(limitly_path, verbose=args.verbose)
    tests = runner.discover_tests()
    
    if args.list:
        print(f"Found {len(tests)} negative tests:")
        for test in sorted(tests, key=lambda t: t.category):
            print(f"  [{test.category:15}] {test.path}")
        return
    
    # Filter by category if specified
    if args.category:
        tests = [t for t in tests if t.category == args.category]
        if not tests:
            print(f"No tests found in category: {args.category}")
            sys.exit(1)
    
    # Run tests
    runner.run_all(tests)
    
    # Exit code based on results
    failed = len([r for r in runner.results if not r.passed])
    sys.exit(1 if failed > 0 else 0)


if __name__ == "__main__":
    main()
