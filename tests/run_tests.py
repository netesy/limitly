import subprocess
import sys
import os
import glob
import time

limitly_path = os.path.abspath("bin/limitly.exe" if os.name == "nt" else "bin/limitly")

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
    # Stdlib - Core
    "tests/stdlib/core/string_test.lm",
    "tests/stdlib/core/math_test.lm",
    "tests/stdlib/core/option_result_test.lm",
    "tests/stdlib/core/string_option_result_test.lm",
    "tests/stdlib/core_module_test.lm",
    # Stdlib - IO
    "tests/stdlib/io/io_test.lm",
    "tests/stdlib/io/io_extended_test.lm",
    # Stdlib - Collections
    "tests/stdlib/collections/list_test.lm",
    "tests/stdlib/collections/vector_test.lm",
    "tests/stdlib/collections/queue_stack_test.lm",
    "tests/stdlib/collections/queue_stack_bitset_test.lm",
    "tests/stdlib/collections/arraylist_test.lm",
    "tests/stdlib/collections/priority_queue_test.lm",
    "tests/stdlib/collections_module_test.lm",
    # Stdlib - Collections - Tree (skip - requires trait method dispatch support)
    # "tests/stdlib/collections/tree_test.lm",
    # Stdlib - Algorithm
    "tests/stdlib/algorithm_module_test.lm",
    # Stdlib - Iterator
    "tests/stdlib/iterator/iterator_test.lm",
    "tests/stdlib/iterator_module_test.lm",
    # Stdlib - Math
    "tests/stdlib/math_module_test.lm",
    # Stdlib - String
    "tests/stdlib/string_module_test.lm",
    # Stdlib - Unicode
    "tests/stdlib/unicode_module_test.lm",
    # Stdlib - Regex
    "tests/stdlib/regex_module_test.lm",
    # Stdlib - Algorithm (skip - requires tuple type system improvements)
    # "tests/stdlib/algorithm/algorithm_test.lm",
    # Stdlib - Search
    "tests/stdlib/search/search_test.lm",
    # Stdlib - Range
    "tests/stdlib/range/range_test.lm",
    # Stdlib - Sort
    "tests/stdlib/sort/sort_test.lm",
    # Stdlib - Path
    "tests/stdlib/path/path_test.lm",
    # Stdlib - SemVer
    "tests/stdlib/semver_test.lm",
    # Stdlib - FS
    "tests/stdlib/fs/fs_test.lm",
    # Stdlib - Crypto
    "tests/stdlib/crypto/hash_test.lm",
    "tests/stdlib/crypto/random_test.lm",
    # Stdlib - Net
    "tests/stdlib/net/net_test.lm",
    # Stdlib - HTTP
    "tests/stdlib/http/http_test.lm",
    # Stdlib - WSS
    "tests/stdlib/wss/wss_test.lm",
    # Regression - Type Ownership Refactor
    "tests/regression/ownership_refactor_test.lm",
    # Regression - Trait Dispatch
    "tests/regression/trait_dispatch_test.lm",
]

# Tests that need extra time (resource creation, crypto, network)
slow_tests = {
    "tests/stdlib/crypto/hash_test.lm",
    "tests/stdlib/crypto/random_test.lm",
    "tests/stdlib/net/net_test.lm",
    "tests/stdlib/http/http_test.lm",
    "tests/stdlib/wss/wss_test.lm",
    "tests/stdlib/fs/fs_test.lm",
    "tests/stdlib/io/io_extended_test.lm",
    "tests/stdlib/semver_test.lm",
    "tests/stdlib/math_module_test.lm",
}

passed = 0
failed = 0
hung = 0

print("====================================================")
print("Running Limitly Tests Individually (3s/10s Timeout)")
print("====================================================")

for test in tests:
    test_path = os.path.normpath(test)
    if not os.path.exists(test_path):
        print(f"Skipping {test_path} (does not exist)")
        continue
    
    timeout = 10.0 if test in slow_tests else 3.0
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
