import subprocess
import sys
import os
import time

limitly_path = os.path.abspath("bin/limitly.exe" if os.name == "nt" else "bin/limitly")

# Focused tests for trait dispatch, callable fields, and any type behavior
debug_tests = [
    # Regression - Callable Function Fields
    "tests/regression/callable_field_test.lm",
    # Regression - Trait Method Dispatch
    "tests/regression/trait_method_dispatch_test.lm",
    # Regression - Trait Dispatch (original)
    "tests/regression/trait_dispatch_test.lm",
    # Stdlib - Iterator (tests trait-based iterator abstractions)
    "tests/stdlib/iterator/iterator_test.lm",
    # OOP - Traits Dynamic (tests trait polymorphism)
    "tests/oop/traits_dynamic.lm",
    # OOP - Traits Inheritance (tests trait hierarchies)
    "tests/oop/traits_inheritance.lm",
]

passed = 0
failed = 0
hung = 0

print("====================================================")
print("Debug Tests: Traits, Callable Fields, Any Type")
print("====================================================")

for test in debug_tests:
    test_path = os.path.normpath(test)
    if not os.path.exists(test_path):
        print(f"Skipping {test_path} (does not exist)")
        continue
    
    timeout = 10.0
    start_time = time.time()
    try:
        res = subprocess.run(
            [limitly_path, "run", test_path],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            timeout=timeout
        )
        duration = time.time() - start_time
        
        # Check output for typical error patterns
        has_error_pattern = False
        for pattern in ["error[E", "Error:", "RuntimeError", "SemanticError", "BytecodeError", "❌ FAIL", "ASSERT FAIL", "Assertion failed"]:
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
