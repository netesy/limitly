#!/usr/bin/env python3
"""Import-audit every module under std/.

For each `std/**.lm` this derives the module name a consumer would write
(`std/collections/list.lm` -> `std.collections.list`, `std/collections/index.lm`
-> `std.collections`), emits a one-line probe that imports it, compiles that
probe with the VM, and records the result.

Import alone is the right unit: it forces the module to be parsed, resolved,
type-checked and lowered without requiring a callable entry point, so a module
that only breaks when called is out of scope by design (tests/ covers behaviour).

Usage:
    python scripts/audit_stdlib.py              # summary + failures
    python scripts/audit_stdlib.py -v           # one line per module
    python scripts/audit_stdlib.py --group      # group failures by error signature
    python scripts/audit_stdlib.py --no-cache   # cold compile every probe
"""

from __future__ import annotations

import argparse
import collections
import concurrent.futures
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STD = os.path.join(ROOT, "std")
LYMAR = os.path.join(ROOT, "bin", "lymar.exe")

# Errors that mean "this module cannot be imported at all".
ERROR_MARKERS = ("error:", "Type Check Error", "Parse Error", "Semantic Error",
                 "Unknown expression type", "cannot find", "undefined")


def module_name(rel_path: str) -> str:
    """std/collections/list.lm -> std.collections.list ; std/foo/index.lm -> std.foo"""
    parts = rel_path.replace(os.sep, "/")[:-3].split("/")
    if parts[-1] == "index":
        parts = parts[:-1]
    return ".".join(parts)


def discover() -> list[tuple[str, str]]:
    found = []
    for dirpath, _dirnames, filenames in os.walk(STD):
        for name in sorted(filenames):
            if not name.endswith(".lm"):
                continue
            full = os.path.join(dirpath, name)
            rel = os.path.relpath(full, ROOT)
            found.append((rel, module_name(rel)))
    found.sort()
    return found


def probe_one(item: tuple[str, str], workdir: str, no_cache: bool = False) -> dict:
    rel, mod = item
    probe = os.path.join(workdir, mod.replace(".", "_") + ".lm")
    with open(probe, "w", encoding="utf-8", newline="\n") as handle:
        handle.write("import %s;\n" % mod)
    cmd = [LYMAR, "run", probe]
    if no_cache:
        # A cached artifact can hide a broken source file: the suite reporting
        # green while `--no-cache` faults means exactly that. Use this for a
        # cold verification after touching std/.
        cmd.append("--no-cache")
    try:
        proc = subprocess.run(
            cmd,
            cwd=ROOT, capture_output=True, text=True, timeout=120,
        )
    except subprocess.TimeoutExpired:
        return {"rel": rel, "mod": mod, "status": "TIMEOUT", "detail": ">120s"}
    out = (proc.stdout or "") + (proc.stderr or "")
    if proc.returncode == 0:
        return {"rel": rel, "mod": mod, "status": "OK", "detail": ""}
    lines = [ln.strip() for ln in out.splitlines() if ln.strip()]
    detail = ""
    for ln in lines:
        if any(m in ln for m in ERROR_MARKERS):
            detail = ln
            break
    if not detail:
        detail = lines[0] if lines else "exit=%d" % proc.returncode
    return {"rel": rel, "mod": mod, "status": "FAIL", "detail": detail}


def signature(detail: str) -> str:
    """Collapse a diagnostic to a comparable key so failures group by cause."""
    d = re.sub(r"`[^`]*`", "`X`", detail)
    d = re.sub(r"'[^']*'", "'X'", d)
    d = re.sub(r"\d+", "N", d)
    return d[:120]


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("-v", "--verbose", action="store_true")
    ap.add_argument("--group", action="store_true")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--no-cache", action="store_true",
                    help="compile each probe cold instead of reusing cached artifacts")
    args = ap.parse_args()

    if not os.path.exists(LYMAR):
        print("missing compiler: %s" % LYMAR)
        return 2

    items = discover()
    results = []
    with tempfile.TemporaryDirectory(prefix="lymar_stdcmp_") as tmp:
        with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
            for res in pool.map(lambda it: probe_one(it, tmp, args.no_cache), items):
                results.append(res)

    ok = [r for r in results if r["status"] == "OK"]
    bad = [r for r in results if r["status"] != "OK"]

    if args.verbose:
        for r in results:
            mark = "OK  " if r["status"] == "OK" else "FAIL"
            print("%s %-44s %s" % (mark, r["mod"], r["detail"]))

    print("stdlib import audit: %d modules, %d OK, %d FAIL"
          % (len(results), len(ok), len(bad)))

    if args.group and bad:
        buckets = collections.defaultdict(list)
        for r in bad:
            buckets[signature(r["detail"])].append(r["mod"])
        for sig, mods in sorted(buckets.items(), key=lambda kv: -len(kv[1])):
            print("\n[%d] %s" % (len(mods), sig))
            for m in mods[:12]:
                print("    " + m)
            if len(mods) > 12:
                print("    ... %d more" % (len(mods) - 12))
    elif bad:
        print("\nfailing modules:")
        for r in bad:
            print("  %-44s %s" % (r["mod"], r["detail"]))

    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
