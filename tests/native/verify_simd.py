# Roadmap item 4 verification: SIMD auto-vectorization of fused numeric streams.
#
# Checks:
#   1. Fused numeric stream benchmark builds and runs under AOT with vectorization (-O2)
#   2. Scalar run (LYMAR_NO_VECTORIZE=1) builds, runs, and produces byte-identical output
#   3. Interpreter VM (lymar run) produces byte-identical output (behavioral equivalence)
#   4. Emitted assembly reflects vectorization optimization (assembly diff between vectorized and scalar)
#
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BIN = ROOT / "bin" / ("lymar.exe" if os.name == "nt" else "lymar")
BENCH = Path("tests") / "native" / "simd_stream_bench.lm"


def main():
    if not BIN.exists():
        print(f"FAIL: missing compiler binary {BIN}")
        return 1
    if not (ROOT / BENCH).exists():
        print(f"FAIL: missing benchmark source {BENCH}")
        return 1

    out = ROOT / "scratch"
    out.mkdir(parents=True, exist_ok=True)

    # 1. Run via VM (reference behavior)
    vm_run = subprocess.run([str(BIN), "run", str(BENCH)], capture_output=True, text=True, cwd=ROOT)
    if vm_run.returncode != 0:
        print("FAIL: VM execution of simd_stream_bench failed")
        print(vm_run.stdout + vm_run.stderr)
        return 1
    vm_out = vm_run.stdout.strip()
    if "simd_stream_bench ok: 1584 946 2144" not in vm_out:
        print(f"FAIL: unexpected VM output: {vm_out}")
        return 1
    print("PASS: VM execution produced correct benchmark results")

    # 2. Build and run AOT with vectorization enabled (-O2)
    vec_exe = out / ("simd_bench_vec.exe" if os.name == "nt" else "simd_bench_vec")
    res = subprocess.run([str(BIN), "build", str(BENCH), "-O", "2", "--no-cache", "-o", str(vec_exe)],
                         capture_output=True, text=True, cwd=ROOT)
    if res.returncode != 0:
        print("FAIL: AOT build with vectorization failed")
        print(res.stdout + res.stderr)
        return 1
    vec_run = subprocess.run([str(vec_exe)], capture_output=True, text=True)
    if vec_run.returncode != 0:
        print("FAIL: vectorized AOT executable failed")
        print(vec_run.stdout + vec_run.stderr)
        return 1
    vec_out = vec_run.stdout.strip()
    if vec_out != vm_out:
        print(f"FAIL: vectorized AOT output differs from VM:\n  VM:  {vm_out}\n  AOT: {vec_out}")
        return 1
    print("PASS: vectorized AOT execution matches VM reference")

    # 3. Build and run AOT with LYMAR_NO_VECTORIZE=1 (scalar path)
    novec_exe = out / ("simd_bench_novec.exe" if os.name == "nt" else "simd_bench_novec")
    scalar_env = dict(os.environ, LYMAR_NO_VECTORIZE="1")
    res = subprocess.run([str(BIN), "build", str(BENCH), "-O", "2", "--no-cache", "-o", str(novec_exe)],
                         capture_output=True, text=True, cwd=ROOT, env=scalar_env)
    if res.returncode != 0:
        print("FAIL: AOT build with LYMAR_NO_VECTORIZE=1 failed")
        print(res.stdout + res.stderr)
        return 1
    novec_run = subprocess.run([str(novec_exe)], capture_output=True, text=True)
    if novec_run.returncode != 0:
        print("FAIL: scalar AOT executable failed")
        print(novec_run.stdout + novec_run.stderr)
        return 1
    novec_out = novec_run.stdout.strip()
    if novec_out != vec_out:
        print(f"FAIL: scalar AOT output differs from vectorized AOT:\n  vec:   {vec_out}\n  novec: {novec_out}")
        return 1
    print("PASS: scalar AOT execution matches vectorized AOT")

    # 4. Inspect assembly outputs to confirm vectorization transformation
    vec_s = out / "simd_bench_vec.s"
    novec_s = out / "simd_bench_novec.s"
    subprocess.run([str(BIN), "build", str(BENCH), "-S", "-O", "2", "--no-cache", "-o", str(vec_s)],
                   capture_output=True, text=True, cwd=ROOT)
    subprocess.run([str(BIN), "build", str(BENCH), "-S", "-O", "2", "--no-cache", "-o", str(novec_s)],
                   capture_output=True, text=True, cwd=ROOT, env=scalar_env)

    if not vec_s.exists() or not novec_s.exists():
        print("FAIL: failed to generate assembly artifacts for inspection")
        return 1

    vec_asm = vec_s.read_text(encoding="utf-8")
    novec_asm = novec_s.read_text(encoding="utf-8")

    if vec_asm == novec_asm:
        print("FAIL: vectorized assembly is identical to scalar assembly (vectorizer pass was not engaged)")
        return 1
    print("PASS: assembly diff confirms vectorizer pass affects code generation")

    print("4 verification: ALL PASSED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
