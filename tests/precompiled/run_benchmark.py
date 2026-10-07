"""Validate equivalent font work before reporting measured process timings."""
import argparse
from contextlib import contextmanager
import math
import os
from pathlib import Path
import re
import statistics
import shutil
import subprocess
import tempfile
import time

ROOT = Path(__file__).resolve().parents[2]
MARKER = re.compile(r"WORKLOAD_DONE: ([+\-0-9.eE]+)")


def measure_run(cmd, env=None, timeout=120):
    start = time.perf_counter()
    result = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, env=env, timeout=timeout)
    elapsed = (time.perf_counter() - start) * 1000
    if result.returncode:
        raise RuntimeError(f"{cmd}: exited {result.returncode}\n{result.stdout}\n{result.stderr}")
    return elapsed, result.stdout, result.stderr


def workload_result(output):
    matches = MARKER.findall(output)
    if len(matches) != 1:
        raise RuntimeError(f"Expected one completed workload, got {len(matches)}: {output}")
    value = float(matches[0])
    if not math.isfinite(value) or value <= 0:
        raise RuntimeError(f"Invalid workload result: {value}")
    return value


def run_average(cmd, runs=5, env=None, native=False):
    times, values = [], []
    for _ in range(runs):
        ms, out, err = measure_run(cmd, env)
        value = workload_result(out)
        if native:
            width_calls = re.findall(r"^PRECOMPILED_CALL: std\.font\.Font\.text_width$", err, re.MULTILINE)
            if len(width_calls) != 50 or "PRECOMPILED_CALL: std.font.load_font" not in err:
                raise RuntimeError("Mode B must load the font and execute all 50 text_width calls natively")
        times.append(ms)
        values.append(value)
    if any(not math.isclose(values[0], v, rel_tol=1e-5, abs_tol=0.01) for v in values):
        raise RuntimeError("Workload results changed between runs")
    return statistics.mean(times), values[0]


@contextmanager
def preserve_artifacts(paths):
    # Restore any user artifacts even when a build, run, or validation fails.
    with tempfile.TemporaryDirectory(prefix="lymar-artifacts-") as backup:
        saved = []
        for i, path in enumerate(paths):
            if path.exists() or path.is_symlink():
                destination = Path(backup) / str(i)
                shutil.copy2(path, destination, follow_symlinks=False)
                saved.append((path, destination))
        try:
            # Finish all backups before removing anything. Copying also works
            # when the temporary directory is on another filesystem.
            for path, _ in saved:
                path.unlink()
            yield
        finally:
            for path in paths:
                path.unlink(missing_ok=True)
            for path, destination in saved:
                shutil.copy2(destination, path, follow_symlinks=False)


def resolve_font(requested=None):
    candidates = [Path(requested)] if requested else [
        Path(os.environ.get("WINDIR", "C:/Windows")) / "Fonts" / "arial.ttf",
        Path("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"),
        Path("/usr/share/fonts/truetype/liberation2/LiberationSans-Regular.ttf"),
        Path("/System/Library/Fonts/Supplemental/Arial.ttf"),
    ]
    for path in candidates:
        if path.is_file():
            return path.resolve()
    raise RuntimeError("No benchmark font found; use --font /path/to/font.ttf")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--font")
    parser.add_argument("--runs", type=int, default=5)
    parser.add_argument("--skip-aot", action="store_true", help="Validate A/B/D only")
    parser.add_argument("--oracle-only", action="store_true", help="Validate A/D without native compilation")
    parser.add_argument("--opt-level", choices=("0", "1", "2", "3"), default="2")
    args = parser.parse_args()
    if args.runs < 1:
        parser.error("--runs must be positive")
    font = resolve_font(args.font)
    windows = os.name == "nt"
    shared_ext = ".dll" if windows else (".dylib" if os.sys.platform == "darwin" else ".so")
    static_ext = ".lib" if windows else ".a"
    compiler = str(ROOT / "bin" / ("lymar.exe" if windows else "lymar"))
    paths = [ROOT / "bin" / ("libfont" + ext + suffix)
             for ext in (".so", ".dll", ".dylib", ".a", ".lib") for suffix in ("", ".meta")]
    (ROOT / "build").mkdir(exist_ok=True)
    with preserve_artifacts(paths), tempfile.TemporaryDirectory(dir=ROOT / "build", prefix="font-benchmark-") as tmp:
        tmp = Path(tmp)
        sources = []
        # Bind exactly the same font in both workloads, independent of host defaults.
        literal = str(font).replace("\\", "\\\\").replace('"', '\\"')
        for kind in ("pure", "stb"):
            source = (ROOT / "tests" / "precompiled" / f"benchmark_workload_{kind}.lm").read_text()
            start = source.index("var font_path =")
            end = source.index("assert(font_path !=", start)
            source = source[:start] + f'var font_path = "{literal}";\n' + source[end:]
            path = tmp / f"{kind}.lm"
            path.write_text(source)
            sources.append(str(path))
        rows = {}
        rows["A. Interpreted Lymar"] = run_average([compiler, "run", sources[0]], args.runs)
        # D is an em-sized floating-point C oracle, matching std.font semantics.
        rows["D. STB C oracle"] = run_average([compiler, "run", sources[1]], args.runs)
        reference = rows["D. STB C oracle"][1]
        if not math.isclose(rows["A. Interpreted Lymar"][1], reference, rel_tol=1e-5, abs_tol=0.01):
            raise RuntimeError(f"Interpreted width {rows['A. Interpreted Lymar'][1]} differs from oracle {reference}")
        print(f"Validated A/D: total width={reference:.6f}; A={rows['A. Interpreted Lymar'][0]:.2f} ms; D={rows['D. STB C oracle'][0]:.2f} ms", flush=True)
        if args.oracle_only:
            return
        shared = ROOT / "bin" / ("libfont" + shared_ext)
        measure_run([compiler, "build", "-O", args.opt_level, "-shared", "std/font/index.lm", "-o", str(shared)], timeout=600)
        native_env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK="1", LYMAR_TRACE_PRECOMPILED="1")
        rows["B. VM + native font"] = run_average([compiler, "run", sources[0]], args.runs, native_env, native=True)
        native_ms, native_value = rows["B. VM + native font"]
        if not math.isclose(native_value, reference, rel_tol=1e-5, abs_tol=0.01):
            raise RuntimeError(f"Native width {native_value} differs from oracle {reference}")
        print(f"Validated B: total width={native_value:.6f}; B={native_ms:.2f} ms", flush=True)
        if not args.skip_aot:
            print("Building Mode C (static library and standalone AOT)...", flush=True)
            static = ROOT / "bin" / ("libfont" + static_ext)
            measure_run([compiler, "build", "-O", args.opt_level, "-static", "std/font/index.lm", "-o", str(static)], timeout=600)
            exe = tmp / ("benchmark.exe" if windows else "benchmark")
            measure_run([compiler, "build", "-O", args.opt_level, sources[0], "-o", str(exe)], timeout=600)
            rows["C. Native AOT"] = run_average([str(exe)], args.runs)
        reference = rows["D. STB C oracle"][1]
        for mode, (_, value) in rows.items():
            if not math.isclose(value, reference, rel_tol=1e-5, abs_tol=0.01):
                raise RuntimeError(f"{mode}: result {value} differs from oracle {reference}")
        print(f"Font: {font}\nCompleted iterations per run: 50")
        print(f"{'Mode':<28} | {'End-to-end mean (ms)':>20} | {'Total width':>14}")
        for mode in sorted(rows):
            ms, value = rows[mode]
            print(f"{mode:<28} | {ms:20.2f} | {value:14.6f}")
        print("Timings include process startup, font loading, and the workload. No unmeasured phase estimates.")


if __name__ == "__main__":
    main()
