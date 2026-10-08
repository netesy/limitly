"""Run negative programs, including the intentional nil-bounds success cases."""
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
COMPILER = Path(os.environ.get("LYMAR_EXECUTABLE", str(ROOT / "bin/lymar"))).resolve()


def main():
    passed = failed = 0
    for path in sorted((ROOT / "tests/negative").rglob("*.lm")):
        expect_success = "// @error:nil_bounds" in path.read_text()
        try:
            result = subprocess.run([str(COMPILER), "run", str(path)], cwd=ROOT,
                                    capture_output=True, text=True, timeout=60)
            diagnostics = result.stdout + result.stderr
            sanitizer_failure = any(marker in diagnostics for marker in (
                "AddressSanitizer", "LeakSanitizer", "runtime error:"))
            valid = (result.returncode == 0) == expect_success
            # Signals and sanitizer aborts are not valid language rejections.
            valid = valid and result.returncode >= 0 and not sanitizer_failure
            if valid:
                passed += 1
            else:
                failed += 1
                print(f"FAIL: {path.relative_to(ROOT)} (exit {result.returncode})", flush=True)
                print(diagnostics, flush=True)
        except subprocess.TimeoutExpired:
            failed += 1
            print(f"TIMEOUT: {path.relative_to(ROOT)}", flush=True)
    print(f"Negative validation: {passed} passed, {failed} failed", flush=True)
    return bool(failed)


if __name__ == "__main__":
    sys.exit(main())
