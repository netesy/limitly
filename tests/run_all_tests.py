#!/usr/bin/env python3
"""
Unified Test Harness for Limitly Compiler
Runs both positive and negative tests to prevent regressions
"""

import subprocess
import sys
import os
from pathlib import Path

def run_command(cmd, cwd=None):
    """Run a command and return (success, output)"""
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
    
    print("=" * 70)
    print("Unified Test Harness for Limitly Compiler")
    print("=" * 70)
    print()
    
    # Track overall success
    all_passed = True
    
    # Run positive tests
    print("Running POSITIVE tests...")
    print("-" * 70)
    success, stdout, stderr = run_command(
        "python tests/run_tests.py",
        cwd=project_root
    )
    
    if success:
        print("✅ POSITIVE tests PASSED")
        # Extract summary from output
        for line in stdout.split('\n'):
            if 'Summary:' in line or 'PASSED=' in line:
                print(f"  {line}")
    else:
        print("❌ POSITIVE tests FAILED")
        all_passed = False
        # Show last few lines of output for context
        lines = stdout.split('\n')
        for line in lines[-10:]:
            if line.strip():
                print(f"  {line}")
    
    print()
    
    # Run negative tests
    print("Running NEGATIVE tests...")
    print("-" * 70)
    success, stdout, stderr = run_command(
        "python tests/negative/run_negative_tests.py",
        cwd=project_root
    )
    
    if success:
        print("✅ NEGATIVE tests PASSED")
        # Extract summary from output
        for line in stdout.split('\n'):
            if 'SUMMARY:' in line or 'PASSED' in line:
                print(f"  {line}")
    else:
        print("❌ NEGATIVE tests FAILED")
        all_passed = False
        # Show summary from output
        lines = stdout.split('\n')
        for line in lines:
            if 'SUMMARY:' in line or 'BY CATEGORY:' in line:
                print(f"  {line}")
    
    print()
    print("=" * 70)
    
    if all_passed:
        print("✅ ALL TESTS PASSED")
        print("=" * 70)
        return 0
    else:
        print("❌ SOME TESTS FAILED")
        print("=" * 70)
        print()
        print("Run individual test suites for details:")
        print("  python tests/run_tests.py           # Positive tests")
        print("  python tests/negative/run_negative_tests.py  # Negative tests")
        return 1

if __name__ == "__main__":
    sys.exit(main())
