#!/usr/bin/env bash
set -euo pipefail

LIMITLY="${LIMITLY:-./bin/limitly}"
ROOT="${1:-tests}"

if [[ ! -x "$LIMITLY" ]]; then
  echo "error: limitly binary not found at $LIMITLY" >&2
  exit 1
fi

PROBE_FILE="tests/basic/literals.lm"
if ! "$LIMITLY" -aot "$PROBE_FILE" >/tmp/limitly_fyra_probe.log 2>&1; then
  if rg -q "libfyra\.a not linked|Fyra AOT backend unavailable" /tmp/limitly_fyra_probe.log; then
    echo "warning: libfyra is unavailable in this environment; cannot execute embedded Fyra AOT tests" >&2
    exit 2
  fi
fi

mapfile -t TEST_FILES < <(find "$ROOT" -type f -name '*.lm' \
  | rg -v '/(oop|classes)/' \
  | sort)

TOTAL=0
PASSED=0
FAILED=0

for test_file in "${TEST_FILES[@]}"; do
  ((TOTAL+=1))
  out_base="${test_file%.lm}"
  rm -f "$out_base" "$out_base.exe" "$out_base.wasm" "$out_base.wasi"

  if "$LIMITLY" -aot "$test_file" > /tmp/limitly_fyra_compile.log 2>&1; then
    produced="$out_base"
    [[ -x "$produced" ]] || produced="$out_base.exe"

    if [[ -x "$produced" ]]; then
      if "$produced" > /tmp/limitly_fyra_run.log 2>&1; then
        echo "PASS $test_file"
        ((PASSED+=1))
      else
        echo "FAIL $test_file (runtime)"
        sed -n '1,40p' /tmp/limitly_fyra_run.log
        ((FAILED+=1))
      fi
    else
      echo "FAIL $test_file (no executable emitted)"
      sed -n '1,40p' /tmp/limitly_fyra_compile.log
      ((FAILED+=1))
    fi
  else
    echo "FAIL $test_file (compile)"
    sed -n '1,40p' /tmp/limitly_fyra_compile.log
    ((FAILED+=1))
  fi

done

echo "---"
echo "Fyra non-OOP summary: total=$TOTAL passed=$PASSED failed=$FAILED"
[[ $FAILED -eq 0 ]]
