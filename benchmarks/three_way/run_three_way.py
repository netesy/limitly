"""Three-way binding benchmark: direct `import "c:"` vs precompiled Lymar
module vs native pure-Lymar, each in VM and AOT (--opt-level 2).

Workload (identical math in all modes): 2M iterations of a Vec2 step
(v = v + d) plus dot accumulation (acc += v.x*v.x + v.y*v.y) on f64 values.

Modes:
  cimport - mode_c.lm: CDVec2 (16-byte struct) params/returns through the
            ForeignCallDirect native-ABI path, 2 calls/iteration.
  module  - mode_module.lm: kernel.lm compiled `-shared` into bin/libkernel
            .dll(+meta); `import kernel` dispatches natively in the VM.
  pure    - mode_pure.lm: the same math inlined with scalar floats.

Each run prints CPU_MS / NS_PER_ITER / RESULT; the runner checks RESULT
parity across all six runs and prints a table.
"""
import argparse
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
HERE = Path(__file__).resolve().parent
BIN = ROOT / "bin" / ("lymar.exe" if os.name == "nt" else "lymar")
SCRATCH = ROOT / "scratch" / "three_way"
N = 2_000_000


def run(cmd, cwd, timeout=300):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=cwd,
                          timeout=timeout)


def parse(out):
    return {
        "cpu_ms": float(re.search(r"CPU_MS:\s*([0-9.eE+-]+)", out).group(1)),
        "ns": float(re.search(r"NS_PER_ITER:\s*([0-9.eE+-]+)", out).group(1)),
        "result": re.search(r"RESULT: (.+)", out).group(1).strip(),
    }


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--runs", type=int, default=1)
    ap.add_argument("--skip-aot", action="store_true")
    args = ap.parse_args()

    if SCRATCH.exists():
        shutil.rmtree(SCRATCH)
    work_mod = SCRATCH / "module"
    (work_mod / "bin").mkdir(parents=True)
    shutil.copy(HERE / "kernel.lm", work_mod / "kernel.lm")
    shutil.copy(HERE / "mode_module.lm", work_mod / "mode_module.lm")

    results = {}

    # --- Precompile the Lymar module (mode B artifact) ---
    res = run([str(BIN), "build", "-O2", "-shared", "kernel.lm",
               "-o", "bin/libkernel.dll"], work_mod, timeout=300)
    if res.returncode != 0:
        print("FAIL: kernel module build\n" + res.stdout + res.stderr)
        return 1
    print("built bin/libkernel.dll (+meta)")

    modes = [
        # (key, program path, run cwd, aot build cwd)
        ("cimport", HERE / "mode_c.lm", ROOT, ROOT),
        ("module", work_mod / "mode_module.lm", work_mod, work_mod),
        ("pure", HERE / "mode_pure.lm", ROOT, ROOT),
    ]

    for key, prog, vm_cwd, aot_cwd in modes:
        # VM
        best = None
        for _ in range(args.runs):
            res = run([str(BIN), "run", str(prog)], vm_cwd, timeout=600)
            if res.returncode != 0:
                print(f"FAIL: VM {key}\n{res.stdout}\n{res.stderr}")
                return 1
            row = parse(res.stdout)
            best = row if best is None or row["cpu_ms"] < best["cpu_ms"] else best
        results[("vm", key)] = best
        print(f"VM   {key:8s} {best['cpu_ms']:10.2f} ms  {best['ns']:8.2f} ns/op  {best['result']}")

        if args.skip_aot:
            continue
        # AOT
        exe = SCRATCH / f"{key}_aot.exe"
        res = run([str(BIN), "build", "--opt-level", "2", "-target", "windows",
                   str(prog), "-o", str(exe)], aot_cwd, timeout=600)
        if res.returncode != 0:
            print(f"FAIL: AOT build {key}\n{res.stdout}\n{res.stderr}")
            return 1
        # cimport exes link libcimport_fixture.dll as a load-time import.
        dll = ROOT / "tests" / "native" / "libcimport_fixture.dll"
        if dll.exists():
            shutil.copy(dll, SCRATCH / dll.name)
        best = None
        for _ in range(args.runs):
            res = run([str(exe)], vm_cwd, timeout=600)
            if res.returncode != 0:
                print(f"FAIL: AOT run {key}\n{res.stdout}\n{res.stderr}")
                return 1
            row = parse(res.stdout)
            best = row if best is None or row["cpu_ms"] < best["cpu_ms"] else best
        results[("aot", key)] = best
        print(f"AOT  {key:8s} {best['cpu_ms']:10.2f} ms  {best['ns']:8.2f} ns/op  {best['result']}")

    # Parity: identical RESULT strings within each backend.
    ok = True
    for backend in ("vm", "aot"):
        vals = {k: results[(backend, k)]["result"] for k in ("cimport", "module", "pure")
                if (backend, k) in results}
        if len(set(vals.values())) != 1:
            ok = False
            print(f"PARITY FAIL ({backend}): {vals}")
    print("PARITY:", "OK" if ok else "MISMATCH")
    (SCRATCH / "results.json").write_text(json.dumps(
        {f"{b}/{k}": v for (b, k), v in results.items()}, indent=2))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
