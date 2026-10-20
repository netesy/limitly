#!/usr/bin/env python3
"""Run every canonical language test through real VM and Fyra execution.

No VM failures are silently skipped. Artifacts are isolated from source files,
and an optional JSON report preserves each stage's output for diagnosis.
"""
import argparse
from collections import Counter
import difflib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tests"))
from run_tests import lymar_path, load_tests_from_file

TEST_TXT = ROOT / "tests" / "test.txt"
tests = load_tests_from_file(TEST_TXT)


def execute(command, env):
    started = time.monotonic()
    try:
        result = subprocess.run(command, cwd=ROOT, env=env, capture_output=True,
                                text=True, timeout=30)
        return dict(code=result.returncode, out=result.stdout, err=result.stderr,
                    seconds=time.monotonic() - started)
    except subprocess.TimeoutExpired as error:
        def decode(value):
            return value.decode(errors="replace") if isinstance(value, bytes) else value or ""
        return dict(code=None, out=decode(error.stdout), err=decode(error.stderr),
                    seconds=time.monotonic() - started)
    except OSError as error:
        return dict(code=None, out="", err=str(error), seconds=time.monotonic() - started)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("-target", "--target", choices=("windows", "linux", "macos"),
                        default="windows" if os.name == "nt" else "macos" if sys.platform == "darwin" else "linux")
    parser.add_argument("--levels", nargs="+", type=int, choices=(0, 1, 2), default=(0, 1, 2))
    parser.add_argument("--tests", nargs="+", help="Explicit source paths; defaults to the entire canonical suite")
    parser.add_argument("--report", type=Path, help="Write stage results to this JSON path after every case")
    args = parser.parse_args()
    env = dict(os.environ)
    records = []
    with tempfile.TemporaryDirectory(prefix="lymar-fyra-parity-") as directory:
        for number, source in enumerate(args.tests or tests):
            vm = execute([lymar_path, "run", source], env)
            for level in args.levels:
                record = dict(source=source, level=level, vm=vm)
                if vm["code"] != 0:
                    record["status"] = "vm_failure"
                else:
                    output = str(Path(directory) / (f"program-{number}-{level}" + (".exe" if args.target == "windows" else "")))
                    build = execute([lymar_path, "build", "-target", args.target,
                                     "-O", str(level), "-o", output, source], env)
                    record["build"] = build
                    if build["code"] != 0 or not Path(output).is_file():
                        record["status"] = "build_failure"
                    else:
                        native = execute([output], env)
                        record["native"] = native
                        expected = (vm["code"], vm["out"], vm["err"])
                        actual = (native["code"], native["out"], native["err"])
                        record["status"] = "pass" if actual == expected else "execution_difference"
                records.append(record)
                print(f"{source} O{level}: {record['status']}", flush=True)
                if record["status"] != "pass":
                    result = record.get("native", record.get("build", vm))
                    print(f"  exit={result['code']} ({result['seconds']:.3f}s)", flush=True)
                    if result["err"]:
                        print(result["err"], flush=True)
                    if "native" in record:
                        print("".join(difflib.unified_diff(vm["out"].splitlines(True),
                                                         result["out"].splitlines(True),
                                                         fromfile="VM", tofile=f"Fyra O{level}")), flush=True)
                if args.report:
                    args.report.write_text(json.dumps(records, indent=2) + "\n")
    counts = Counter(record["status"] for record in records)
    print(f"{len(records)} executions: {dict(counts)}")
    return 0 if counts["pass"] == len(records) and records else 1


if __name__ == "__main__":
    sys.exit(main())
