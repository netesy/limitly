import subprocess
import sys
import os
import glob
import time

limitly_path = os.path.abspath("bin/limitly.exe")

tests = [
    # Basic
    "tests/basic/variables.lm",
    "tests/basic/literals.lm",
    "tests/basic/control_flow.lm",
    "tests/basic/print_statements.lm",
    "tests/basic/list_dict_tuple.lm",
    # Expressions
    "tests/expressions/arithmetic.lm",
    "tests/expressions/logical.lm",
    "tests/expressions/ranges.lm",
    "tests/expressions/scientific_notation.lm",
    "tests/expressions/large_literals.lm",
    # Strings
    "tests/strings/interpolation.lm",
    "tests/strings/operations.lm",
    # Loops
    "tests/loops/for_loops.lm",
    "tests/loops/iter_loops.lm",
    "tests/loops/while_loops.lm",
    "tests/loops/match.lm",
    "tests/loops/match_advanced.lm",
    # Functions
    "tests/functions/basic.lm",
    "tests/functions/advanced.lm",
    "tests/functions/closures.lm",
    "tests/functions/first_class.lm",
    # Types
    "tests/types/basic.lm",
    "tests/types/unions.lm",
    "tests/types/options.lm",
    "tests/types/advanced.lm",
    "tests/types/enums.lm",
    "tests/types/refined_types.lm",
    "tests/types/structural_type_tests.lm",
    # Modules
    "tests/modules/basic_import_test.lm",
    "tests/modules/comprehensive_module_test.lm",
    "tests/modules/show_filter_test.lm",
    "tests/modules/hide_filter_test.lm",
    "tests/modules/module_caching_test.lm",
    "tests/modules/function_params_test.lm",
    "tests/modules/alias_import_test.lm",
    "tests/modules/multiple_imports_test.lm",
    # OOP
    "tests/oop/frame_declaration.lm",
    "tests/oop/traits_dynamic.lm",
    "tests/oop/traits_inheritance.lm",
    "tests/oop/visibility_test.lm",
    "tests/oop/composition_test.lm",
    # Concurrency
    "tests/concurrency/parallel_blocks.lm",
    "tests/concurrency/concurrent_blocks.lm",
]

passed = 0
failed = 0
hung = 0

print("====================================================")
print("Running Limitly Tests Individually with 3s Timeout")
print("====================================================")

for test in tests:
    test_path = os.path.normpath(test)
    if not os.path.exists(test_path):
        print(f"Skipping {test_path} (does not exist)")
        continue
    
    start_time = time.time()
    try:
        res = subprocess.run(
            [limitly_path, "run", test_path],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            timeout=3.0
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
        print(f"HANG / TIMEOUT: {test} (killed after 3s)")
        hung += 1
        failed += 1

print("====================================================")
print(f"Summary: PASSED={passed}, FAILED={failed} (including HUNG={hung})")
print("====================================================")

if failed > 0:
    sys.exit(1)
else:
    sys.exit(0)
