# Roadmap item 2b verification: `lymar run/build --bind-header` parses a C header,
# generates an importable .lm binding module, and calls through the FFI wrappers
# at runtime via ffi.load() (dynamic path).
#
# Checks:
#   1. Header parsing produces a .lm file in .cache/bindings/ with expected functions
#   2. The fixture .c is compiled to a shared library for dynamic loading
#   3. VM path: `lymar run bind_test.lm --bind-header` succeeds with correct results
#   4. Generated module content contains expected wrapper patterns
#
# Requires gcc on PATH (MSYS2 MinGW on Windows).
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BIN = ROOT / "bin" / ("lymar.exe" if os.name == "nt" else "lymar")
PROG = Path("tests") / "native" / "bind_test.lm"
HEADER = Path("tests") / "native" / "bind_fixture.h"
SOURCE = Path("tests") / "native" / "bind_fixture.c"


def have(tool):
    return shutil.which(tool) is not None


def main():
    for tool in (BIN, ROOT / PROG, ROOT / HEADER, ROOT / SOURCE):
        if not Path(tool).exists():
            print(f"FAIL: missing prerequisite {tool}")
            return 1
    if not have("gcc") and not have("cc"):
        print("SKIP: no C compiler available")
        return 0

    compiler = "gcc" if have("gcc") else "cc"
    out_dir = ROOT / "scratch"
    out_dir.mkdir(exist_ok=True)

    # 0. Build fixture as shared library for dynamic ffi.load()
    if os.name == "nt":
        shared_lib = out_dir / "libbind_fixture.dll"
    elif sys.platform == "darwin":
        shared_lib = out_dir / "libbind_fixture.dylib"
    else:
        shared_lib = out_dir / "libbind_fixture.so"

    res = subprocess.run(
        [compiler, "-shared", "-fPIC", "-O2", "-o", str(shared_lib),
         str(ROOT / SOURCE)],
        capture_output=True, text=True)
    if res.returncode != 0:
        print(f"FAIL: could not build shared library: {res.stderr}")
        return 1
    print(f"PASS: built shared library {shared_lib.name}")

    # Clean previous bind_fixture.lm to verify fresh generation
    bind_lm = ROOT / ".cache" / "bindings" / "bind_fixture.lm"
    if bind_lm.exists():
        bind_lm.unlink()

    # The lib path passed to ffi.load: must include the platform extension
    # since LoadLibraryA/dlopen don't auto-append on any platform.
    if os.name == "nt":
        lib_path = "./scratch/libbind_fixture.dll"
    elif sys.platform == "darwin":
        lib_path = "./scratch/libbind_fixture.dylib"
    else:
        lib_path = "./scratch/libbind_fixture.so"

    # 1. Run via VM with --bind-header to verify generation + resolution
    res = subprocess.run(
        [str(BIN), "run", str(PROG), "--bind-header", str(HEADER),
         "--bind-lib", lib_path, "-I", "."],
        capture_output=True, text=True, cwd=ROOT, timeout=15)
    if res.returncode != 0:
        print("FAIL: lymar run with --bind-header failed")
        print(res.stdout + res.stderr)
        return 1
    print("PASS: lymar run with --bind-header succeeded")

    # 2. Generated module exists and contains expected wrappers
    if not bind_lm.exists():
        print(f"FAIL: generated binding module not found at {bind_lm}")
        return 1
    content = bind_lm.read_text(encoding="utf-8")
    expected_fns = ["fixture_answer", "fixture_add", "fixture_multiply",
                    "fixture_clamp", "fixture_strlen", "fixture_increment"]
    for fn in expected_fns:
        if fn not in content:
            print(f"FAIL: generated module missing '{fn}' wrapper")
            return 1
    print("PASS: generated binding module contains all expected wrappers")

    # 3. Verify program output contains correct results
    if "42" not in res.stdout:
        print(f"FAIL: program output unexpected: {res.stdout!r}")
        return 1
    if "PASSED" not in res.stdout:
        print(f"FAIL: test did not reach PASSED marker: {res.stdout!r}")
        return 1
    print("PASS: program runs correctly (42 results verified)")

    # 4. Verify specific numeric results in output (each print adds newline)
    checks = ["fixture_answer() = \n42", "fixture_add(10, 32) = \n42",
              "fixture_clamp(0, 10, 15) = \n10"]
    for c in checks:
        if c not in res.stdout:
            print(f"FAIL: expected output line not found: '{c}'")
            print(f"  actual stdout: {res.stdout!r}")
            return 1
    print("PASS: all numeric assertions match expected values")

    print("2b verification: ALL PASSED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
