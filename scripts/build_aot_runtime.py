#!/usr/bin/env python3
"""Build the standalone runtime with the target's C++ toolchain, without a VM."""
import argparse
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--target", required=True, help="x64-linux, aarch64-linux, riscv64-linux, x64-windows, aarch64-macos, etc.")
    parser.add_argument("--cxx", default=os.environ.get("CXX", "g++"))
    parser.add_argument("--ar", default=os.environ.get("AR", "ar"))
    parser.add_argument("--cxx-arg", action="append", default=[], help="Repeat for sysroot/SDK flags; use --cxx-arg=--sysroot=PATH")
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    target = args.target.replace("x86_64-", "x64-").replace("arm64-", "aarch64-")
    parts = target.split("-")
    if len(parts) != 2:
        parser.error("--target must be ARCH-OS, without an artifact suffix")
    arch, system = parts
    machine = subprocess.check_output([args.cxx, *args.cxx_arg, "-dumpmachine"], text=True).strip().lower()
    architectures = {"x64": ("x86_64", "amd64"), "aarch64": ("aarch64", "arm64"), "riscv64": ("riscv64",), "wasm32": ("wasm32",)}
    systems = {"linux": ("linux",), "windows": ("mingw", "windows", "win32"), "macos": ("darwin", "apple"), "wasi": ("wasi",), "freebsd": ("freebsd",), "android": ("android",)}
    if arch not in architectures or system not in systems:
        parser.error("unsupported runtime target: " + target)
    if not any(machine.startswith(a) for a in architectures[arch]) or not any(s in machine for s in systems[system]):
        parser.error(f"toolchain target {machine!r} does not match {target!r}; select the correct --cxx/SDK flags")
    output = (args.output or ROOT / "bin" / "runtimes" / target / "liblymar_aot.a").resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="lymar-aot-runtime-", dir=output.parent) as temporary:
        obj = Path(temporary) / "region_runtime.o"
        archive = Path(temporary) / "liblymar_aot.a"
        subprocess.run([args.cxx, *args.cxx_arg, "-std=c++20", "-O2", "-fPIC", "-c",
                        str(ROOT / "src/backend/fyra/region_runtime.cpp"), "-o", str(obj)], check=True)
        subprocess.run([args.ar, "rcs", str(archive), str(obj)], check=True)
        os.replace(archive, output)
    print(f"Built {target} runtime: {output}")


if __name__ == "__main__":
    main()
