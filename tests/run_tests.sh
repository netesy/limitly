#!/bin/bash
set -euo pipefail

LIMITLY="./bin/limitly"
FAILED=0
PASSED=0
SKIPPED=0
TOTAL=0

echo "Building compiler before running tests..."
echo "Ensuring submodule dependencies are available..."
git submodule sync --recursive >/dev/null 2>&1 || true
git submodule update --init --recursive >/dev/null 2>&1 || true

if [[ ! -f "vendor/fyra/include/ir/Module.h" ]]; then
  FYRA_URL=$(git config -f .gitmodules --get submodule.fyra.url || true)
  if [[ -z "${FYRA_URL}" ]]; then
    echo "Missing vendor/fyra and no submodule.fyra.url configured in .gitmodules."
    exit 1
  fi
  echo "Hydrating vendor/fyra from ${FYRA_URL}..."
  rm -rf vendor/fyra
  git clone --depth 1 "${FYRA_URL}" vendor/fyra
fi

if ! make; then
  echo "Build failed. Aborting tests."
  exit 1
fi

if [[ ! -x "$LIMITLY" ]]; then
  echo "Compiler binary not found at $LIMITLY after build."
  exit 1
fi

# Files that are module fixtures, samples, or intentionally invalid suites.
SKIP_PATTERNS=(
  "tests/modules/basic_module.lm"
  "tests/modules/math_module.lm"
  "tests/modules/my_module.lm"
  "tests/modules/string_module.lm"
  "tests/modules/nested/deep_module.lm"
  "tests/errors/"
  "tests/error_handling/"
  "tests/types/type_error_tests.lm"
  "tests/types/union_error_tests.lm"
  "tests/types/structural_error_tests.lm"
  "tests/modules/comprehensive_error_tests.lm"
  "tests/modules/error_tests_simple.lm"
  "tests/format/test_unformatted.lm"
)

should_skip() {
  local file="$1"
  for p in "${SKIP_PATTERNS[@]}"; do
    if [[ "$file" == "$p" || "$file" == *"$p"* ]]; then
      return 0
    fi
  done
  return 1
}

run_test_with_error_check() {
    local file="$1"
    ((TOTAL+=1))
    echo "Running $file..."

    TEMP_FILE=$(mktemp)
    "$LIMITLY" "$file" > "$TEMP_FILE" 2>&1 || true

    if grep -qi -E "segmentation fault|segfault" "$TEMP_FILE"; then
        echo "  FAIL: $file (segmentation fault detected in output)"
        cat "$TEMP_FILE"
        ((FAILED+=1))
    elif grep -q -E "error\\[E|Error:|RuntimeError|SemanticError|BytecodeError" "$TEMP_FILE"; then
        echo "  FAIL: $file (contains errors)"
        grep -E "error\\[E|Error:|RuntimeError|SemanticError|BytecodeError" "$TEMP_FILE"
        ((FAILED+=1))
    elif grep -q -E "❌ FAIL|ASSERT.*FAIL|Assertion.*failed" "$TEMP_FILE"; then
        echo "  FAIL: $file (assertion failure detected)"
        cat "$TEMP_FILE"
        ((FAILED+=1))
    else
        echo "  PASS: $file"
        ((PASSED+=1))
    fi
    rm -f "$TEMP_FILE"
}

echo "========================================"
echo "Running Limit Language Test Suite (discovery mode)"
echo "========================================"
echo

mapfile -t ALL_TESTS < <(find tests -name '*.lm' | sort)

for test_file in "${ALL_TESTS[@]}"; do
  if should_skip "$test_file"; then
    echo "Skipping $test_file (fixture/negative test)"
    ((SKIPPED+=1))
    continue
  fi
  run_test_with_error_check "$test_file"
done

echo
echo "========================================"
echo "Test Results:"
echo "  PASSED:  $PASSED"
echo "  FAILED:  $FAILED"
echo "  SKIPPED: $SKIPPED"
echo "  TOTAL:   $TOTAL"
echo "========================================"

if [ "$FAILED" -gt 0 ]; then
    echo "Some tests failed!"
    exit 1
else
    echo "All discovered tests passed!"
    exit 0
fi
