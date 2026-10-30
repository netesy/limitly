# Roadmap item 2a verification: `lymar build --native` compiles a foreign C
# source with the native toolchain and links its object into the artifact.
#
# Checks (executable path):
#   1. build with --native succeeds and the program runs
#   2. the foreign symbol is present in the built image
#   3. the same build without --native does not contain the symbol
#   4. a -static artifact carries the foreign object as an archive member
#
# Requires gcc/g++ and objdump/nm/ar on PATH (MSYS2 MinGW on Windows).
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BIN = ROOT / "bin" / ("lymar.exe" if os.name == "nt" else "lymar")
# The compiler derives the module name from the source path argument and an
# absolute Windows path (`C:...`) does not survive that spelling, so every
# invocation below stays relative to the repository root.
PROG = Path("tests") / "native" / "native_link_basic.lm"
SOURCE = Path("tests") / "native" / "native_probe.c"
SYMBOL = "lymar_native_probe"


def have(tool):
    return shutil.which(tool) is not None


def nm_tool():
    for name in ("objdump", "llvm-objdump"):
        if have(name):
            return name
    return None


def symbol_present(image, objdump):
    res = subprocess.run([objdump, "-t", str(image)], capture_output=True, text=True)
    return SYMBOL in res.stdout


def main():
    for tool in (BIN, ROOT / PROG, ROOT / SOURCE):
        if not Path(tool).exists():
            print(f"FAIL: missing prerequisite {tool}")
            return 1
    objdump, ar = nm_tool(), "ar" if have("ar") else None
    if objdump is None:
        print("SKIP: objdump is not available; cannot inspect linked images")
        return 0
    out = Path(os.environ.get("LYMAR_NATIVE_2A_OUT", ROOT / "scratch"))
    out.mkdir(parents=True, exist_ok=True)

    with_exe = out / "verify_2a_with.exe"
    res = subprocess.run([str(BIN), "build", str(PROG), "--native", str(SOURCE),
                          "--no-cache", "-o", str(with_exe)], capture_output=True, text=True, cwd=ROOT)
    if res.returncode != 0:
        print("FAIL: build with --native failed")
        print(res.stdout + res.stderr)
        return 1
    run = subprocess.run([str(with_exe)], capture_output=True, text=True)
    if "2a ok" not in run.stdout:
        print(f"FAIL: built program output unexpected: {run.stdout!r}")
        return 1
    if not symbol_present(with_exe, objdump):
        print(f"FAIL: {SYMBOL} missing from the --native executable")
        return 1
    print("PASS: --native executable builds, runs, and contains the foreign symbol")

    plain_exe = out / "verify_2a_plain.exe"
    res = subprocess.run([str(BIN), "build", str(PROG), "--no-cache", "-o", str(plain_exe)],
                         capture_output=True, text=True, cwd=ROOT)
    if res.returncode == 0 and symbol_present(plain_exe, objdump):
        print(f"FAIL: {SYMBOL} present without --native (link not gated on the flag)")
        return 1
    print("PASS: plain build does not contain the foreign symbol")

    # A source the toolchain rejects must fail the build, not be skipped.
    scratch = ROOT / "scratch"
    scratch.mkdir(exist_ok=True)
    broken = scratch / "verify_2a_broken.c"
    broken.write_text("int broken(void) { this is not C; }\n", encoding="utf-8")
    res = subprocess.run([str(BIN), "build", str(PROG), "--native", str(Path("scratch") / broken.name),
                          "--no-cache", "-o", str(out / "verify_2a_broken.exe")],
                         capture_output=True, text=True, cwd=ROOT)
    if res.returncode == 0:
        print("FAIL: build with a broken native source unexpectedly succeeded")
        return 1
    if "Native source compilation failed" not in (res.stdout + res.stderr):
        print("FAIL: broken-source build did not report the native compilation error")
        return 1
    print("PASS: broken native source fails the build with a clear error")

    if ar:
        archive = out / "verify_2a_with.a"
        res = subprocess.run([str(BIN), "build", str(PROG), "--native", str(SOURCE),
                              "--no-cache", "-static", "-o", str(archive)], capture_output=True, text=True, cwd=ROOT)
        if res.returncode != 0:
            print("FAIL: -static build with --native failed")
            print(res.stdout + res.stderr)
            return 1
        listing = subprocess.run([ar, "t", str(archive)], capture_output=True, text=True)
        if ".lymar-native-" not in listing.stdout:
            print("FAIL: foreign object missing from the static archive members")
            print(listing.stdout)
            return 1
        print("PASS: static archive carries the foreign object as a member")
    else:
        print("SKIP: ar is not available; static archive check skipped")

    print("2a verification: ALL PASSED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
