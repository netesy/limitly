#!/usr/bin/env python3
"""Weaken non-export globals in a Lymar shared-module object.

Each `lymar build -shared` module compiles to a self-contained C++ object.
Its public contract is the set of `extern "C"` wrappers whose asm labels are
the module-qualified `std.font.*` symbol names. The module-specific helpers
(namespace N / NativeScope) are renamed per-module in the generated source
before compilation; what remains are standard-library ODR instantiations
(typeinfo, vtables, operator==) that are byte-identical across modules but
emitted as strong symbols. Weakening them lets the linker deduplicate the
definitions safely when several module objects are archived together.

usage: font_obj_privatize.py <obj> -- <nm> <objcopy>
"""
import subprocess
import sys
from pathlib import Path

GLOBAL_TYPES = {"T", "D", "B", "R", "C", "W", "V"}
PUBLIC_PREFIX = "std.font."


def defined(path, nm):
    out = subprocess.run([nm, "--defined-only", str(path)],
                         check=True, capture_output=True, text=True).stdout
    syms = set()
    for line in out.splitlines():
        parts = line.split()
        if len(parts) >= 3 and parts[1] in GLOBAL_TYPES:
            syms.add(parts[2])
    return syms


def main():
    argv = sys.argv[1:]
    if "--" not in argv:
        print(__doc__, file=sys.stderr)
        return 2
    sep = argv.index("--")
    positional, tools = argv[:sep], argv[sep + 1:]
    if len(positional) != 1 or len(tools) < 2:
        print(__doc__, file=sys.stderr)
        return 2
    obj = Path(positional[0])
    nm, objcopy = tools[0], tools[1]

    # lymar_module_abi_version_<module> is already unique per object; weakening
    # it would change its COFF type and break the dllexport entry.
    private = sorted(s for s in defined(obj, nm)
                     if not s.startswith(PUBLIC_PREFIX)
                     and not s.startswith("lymar_module_abi_version"))
    if not private:
        return 0
    args = [objcopy]
    for sym in private:
        args.append(f"--weaken-symbol={sym}")
    args.append(str(obj))
    subprocess.run(args, check=True)
    print(f"font_obj_privatize: weakened {len(private)} symbols in {obj.name}",
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
