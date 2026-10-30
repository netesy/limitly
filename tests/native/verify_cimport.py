# Roadmap item 2c verification: `import "c:<header>" [from "<lib>"] [...] as <ns>;`
# parses and drives the header->binding pipeline automatically at compile time.
#
# Checks:
#   1. Full import with alias: `import "c:..." from "..." as cfix;` -> all functions callable
#   2. Brace-select filter:    `import "c:..." from "..." { fixture_answer };` -> only filtered symbol
#   3. `show` filter:          `import "c:..." from "..." show fixture_add;`  -> only shown symbol
#   4. System header:          `import "c:stdio.h" as cstdio;` -> binding generated (runtime call optional)
#   5. Cache reuse: rerun does not regenerate the .lm module
#
# Requires gcc on PATH (MSYS2 MinGW on Windows).
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BIN = ROOT / "bin" / ("lymar.exe" if os.name == "nt" else "lymar")
FIXTURE_HDR = ROOT / "tests" / "native" / "cimport_fixture.h"
FIXTURE_SRC = ROOT / "tests" / "native" / "cimport_fixture.c"
CACHE_DIR = ROOT / ".cache" / "bindings"
SCRATCH = ROOT / "scratch"


def have(tool):
    return shutil.which(tool) is not None


def shared_lib_name(base):
    if os.name == "nt":
        return base + ".dll"
    if sys.platform == "darwin":
        return "lib" + base + ".dylib"
    return "lib" + base + ".so"


def run(cmd, cwd=ROOT, timeout=20):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=cwd, timeout=timeout)


def write_lm(path, text):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def main():
    for prereq in (BIN, FIXTURE_HDR, FIXTURE_SRC):
        if not prereq.exists():
            print(f"FAIL: missing prerequisite {prereq}")
            return 1
    if not have("gcc") and not have("cc"):
        print("SKIP: no C compiler available")
        return 0

    SCRATCH.mkdir(exist_ok=True)
    # Clean cached bindings so fresh generation is exercised
    if CACHE_DIR.exists():
        for f in CACHE_DIR.glob("cfix*.lm"):
            f.unlink()
        for f in CACHE_DIR.glob("cstdio.lm"):
            f.unlink()

    compiler = "gcc" if have("gcc") else "cc"
    lib_path_obj = SCRATCH / shared_lib_name("cimport_fixture")
    res = run([compiler, "-shared", "-fPIC", "-O2", "-o", str(lib_path_obj),
               str(FIXTURE_SRC)])
    if res.returncode != 0:
        print(f"FAIL: could not build shared library: {res.stderr}")
        return 1
    print(f"PASS: built shared library {lib_path_obj.name}")

    # Use POSIX-style relative path from ROOT for ffi.library_load()
    rel = lib_path_obj.relative_to(ROOT).as_posix()
    header_rel = FIXTURE_HDR.relative_to(ROOT).as_posix()

    # ---- Test 1: full import with alias ----
    prog1 = SCRATCH / "cimport_basic.lm"
    write_lm(prog1, f'''import std.ffi as ffi;
import "c:{header_rel}" from "./{rel}" as cfix;

fn main() {{
    print("=== 2c basic import test ===");
    var a = cfix.fixture_answer();
    assert(a == 42, "fixture_answer failed");
    print("answer="); print(a);
    var s = cfix.fixture_add(10, 32);
    assert(s == 42, "fixture_add failed");
    print("add="); print(s);
    var q = cfix.fixture_sqrt(9.0);
    assert(q == 3.0, "fixture_sqrt failed");
    print("sqrt="); print(q);
    print("BASIC_OK");
}}
''')
    res = run([str(BIN), "run", str(prog1), "-I", "."])
    if res.returncode != 0 or "BASIC_OK" not in res.stdout:
        print("FAIL: basic c: import")
        print(res.stdout + res.stderr)
        return 1
    print("PASS: full `import \"c:…\" from \"…\" as cfix;` produced a working namespace")

    gen1 = CACHE_DIR / "cfix.lm"
    if not gen1.exists():
        print(f"FAIL: expected generated module at {gen1}")
        return 1
    body = gen1.read_text(encoding="utf-8")
    for fn in ("fixture_answer", "fixture_add", "fixture_sqrt"):
        if f"pub fn {fn}" not in body:
            print(f"FAIL: generated module missing '{fn}'")
            return 1
    print("PASS: generated cfix.lm contains all three wrappers")

    # ---- Test 2: brace-select filter (only fixture_answer) ----
    prog2 = SCRATCH / "cimport_filter.lm"
    write_lm(prog2, f'''import std.ffi as ffi;
import "c:{header_rel}" from "./{rel}" as cfixo {{ fixture_answer }};

fn main() {{
    print("=== 2c brace-filter test ===");
    var a = cfixo.fixture_answer();
    assert(a == 42, "filtered fixture_answer failed");
    print("filtered_answer="); print(a);
    print("FILTER_OK");
}}
''')
    res = run([str(BIN), "run", str(prog2), "-I", "."])
    if res.returncode != 0 or "FILTER_OK" not in res.stdout:
        print("FAIL: brace-filtered c: import")
        print(res.stdout + res.stderr)
        return 1
    gen2 = CACHE_DIR / "cfixo.lm"
    if not gen2.exists():
        print(f"FAIL: expected generated module at {gen2}")
        return 1
    body2 = gen2.read_text(encoding="utf-8")
    if "pub fn fixture_answer" not in body2:
        print("FAIL: filtered module is missing the retained function")
        return 1
    if "pub fn fixture_add" in body2 or "pub fn fixture_sqrt" in body2:
        print("FAIL: filtered module still contains excluded functions")
        return 1
    print("PASS: `{ fixture_answer }` filter excluded the other symbols")

    # ---- Test 3: `show` filter (only fixture_add) ----
    prog3 = SCRATCH / "cimport_show.lm"
    write_lm(prog3, f'''import std.ffi as ffi;
import "c:{header_rel}" from "./{rel}" as cfixs show fixture_add;

fn main() {{
    var s = cfixs.fixture_add(3, 4);
    assert(s == 7, "shown fixture_add failed");
    print("shown_add="); print(s);
    print("SHOW_OK");
}}
''')
    res = run([str(BIN), "run", str(prog3), "-I", "."])
    if res.returncode != 0 or "SHOW_OK" not in res.stdout:
        print("FAIL: show-filtered c: import")
        print(res.stdout + res.stderr)
        return 1
    print("PASS: `show fixture_add` filter produced a working namespace")

    # ---- Test 4: system header (empty library path) -> parse + generate only ----
    # Verify a `c:stdio.h` binding is generated. Runtime lookup of symbols is
    # platform-dependent (Windows statically-linked CRT may not export puts),
    # so we only assert that the module is generated and parses.
    prog4 = SCRATCH / "cimport_syshdr.lm"
    write_lm(prog4, f'''import "c:stdio.h" as cstdio;
fn main() {{ print("SYSHDR_OK"); }}
''')
    # Add include dirs so stdio.h can be located (system default paths)
    res = run([str(BIN), "run", str(prog4), "-I", "."])
    if res.returncode != 0:
        # It's acceptable on strict CI to skip if stdio.h can't be found, but
        # surface other errors.
        msg = res.stderr + res.stdout
        if "cannot find C header" in msg:
            print("SKIP: stdio.h not found in default include paths")
        else:
            print("FAIL: system-header import")
            print(msg)
            return 1
    else:
        gen4 = CACHE_DIR / "cstdio.lm"
        if not gen4.exists():
            print(f"FAIL: expected system-header binding at {gen4}")
            return 1
        body4 = gen4.read_text(encoding="utf-8")
        if 'library_load("")' not in body4:
            print("FAIL: system-header binding does not use empty library path")
            return 1
        print("PASS: system header `import \"c:stdio.h\"` generated an empty-library-path module")

    # ---- Test 5: cache reuse (mtime preserved when unchanged) ----
    mtime1 = gen1.stat().st_mtime
    # Insert a tiny delay so filesystem mtime granularity is exceeded
    time.sleep(0.05)
    res = run([str(BIN), "run", str(prog1), "-I", "."])
    if res.returncode != 0 or "BASIC_OK" not in res.stdout:
        print("FAIL: cached rerun")
        print(res.stdout + res.stderr)
        return 1
    mtime2 = gen1.stat().st_mtime
    if abs(mtime2 - mtime1) > 1e-6:
        print("FAIL: c: import regenerated the binding despite no header change")
        return 1
    print("PASS: binding cache reused on second run (mtime unchanged)")

    print("2c verification: ALL PASSED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
