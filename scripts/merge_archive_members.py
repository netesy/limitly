#!/usr/bin/env python3
"""Merge the object members of one static archive into another.

Used to absorb the toolchain's static libffi archive into liblymar_aot.a so
the standalone runtime is self-contained for both the Fyra internal linker
and target C++ drivers. Missing source archives are skipped silently so
platforms without a static libffi (e.g. macOS SDK stubs) keep working.
"""
import subprocess
import sys
import tempfile
from pathlib import Path


def main():
    if len(sys.argv) < 3:
        print("usage: merge_archive_members.py <target.a> <source.a> [ar]", file=sys.stderr)
        return 2
    target = Path(sys.argv[1])
    source = Path(sys.argv[2])
    ar = sys.argv[3] if len(sys.argv) > 3 else "ar"
    if not source.is_file():
        print(f"merge_archive_members: {source} not found; skipping", file=sys.stderr)
        return 0
    with tempfile.TemporaryDirectory(prefix="lymar-merge-") as td:
        subprocess.run([ar, "x", str(source.resolve())], cwd=td, check=True)
        members = sorted(str(p) for p in Path(td).glob("*.o"))
        if members:
            subprocess.run([ar, "r", str(target.resolve()), *members], check=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
