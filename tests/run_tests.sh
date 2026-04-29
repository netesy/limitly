#!/bin/bash
set -euo pipefail

LIMITLY="./bin/limitly"
FAILED=0
PASSED=0
TOTAL=0

run_test() {
  local f="$1"
  ((TOTAL+=1))
  echo "Running $f..."
  local tmp
  tmp=$(mktemp)
  "$LIMITLY" "$f" >"$tmp" 2>&1 || true
  if grep -qiE "segmentation fault|segfault" "$tmp"; then
    echo "  FAIL: $f (segfault)"
    ((FAILED+=1))
  elif grep -qE "error\[E|Error:|RuntimeError|SemanticError|BytecodeError|❌ FAIL|ASSERT.*FAIL|Assertion.*failed" "$tmp"; then
    echo "  FAIL: $f"
    grep -E "error\[E|Error:|RuntimeError|SemanticError|BytecodeError|❌ FAIL|ASSERT.*FAIL|Assertion.*failed" "$tmp" | head -n 3
    ((FAILED+=1))
  else
    echo "  PASS: $f"
    ((PASSED+=1))
  fi
  rm -f "$tmp"
}

echo "Building compiler..."
make -j4

TESTS=(
"tests/basic/variables.lm"
"tests/basic/literals.lm"
"tests/basic/control_flow.lm"
"tests/basic/print_statements.lm"
"tests/basic/list_dict_tuple.lm"
"tests/expressions/arithmetic.lm"
"tests/expressions/logical.lm"
"tests/expressions/ranges.lm"
"tests/expressions/scientific_notation.lm"
"tests/expressions/large_literals.lm"
"tests/strings/interpolation.lm"
"tests/strings/operations.lm"
"tests/loops/for_loops.lm"
"tests/loops/iter_loops.lm"
"tests/loops/while_loops.lm"
"tests/loops/match.lm"
"tests/functions/basic.lm"
"tests/functions/advanced.lm"
"tests/functions/closures.lm"
"tests/functions/first_class.lm"
"tests/types/basic.lm"
"tests/types/unions.lm"
"tests/types/options.lm"
"tests/types/advanced.lm"
"tests/types/enums.lm"
"tests/types/refined_types.lm"
"tests/types/structural_type_tests.lm"
"tests/modules/basic_import_test.lm"
"tests/modules/comprehensive_module_test.lm"
"tests/modules/show_filter_test.lm"
"tests/modules/hide_filter_test.lm"
"tests/modules/module_caching_test.lm"
"tests/modules/function_params_test.lm"
"tests/modules/alias_import_test.lm"
"tests/modules/multiple_imports_test.lm"
"tests/oop/frame_declaration.lm"
"tests/oop/traits_dynamic.lm"
"tests/oop/traits_inheritance.lm"
"tests/oop/visibility_test.lm"
"tests/oop/composition_test.lm"
"tests/concurrency/parallel_blocks.lm"
"tests/concurrency/concurrent_blocks.lm"
)

for t in "${TESTS[@]}"; do
  run_test "$t"
done

echo "PASSED=$PASSED FAILED=$FAILED TOTAL=$TOTAL"
if [[ $FAILED -gt 0 ]]; then exit 1; fi
