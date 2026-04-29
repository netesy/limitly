#!/bin/bash
set -euo pipefail

LIMITLY="./bin/limitly"
MANIFEST="tests/test_manifest.txt"

echo "Ensuring submodule dependencies are available..."
git submodule sync --recursive >/dev/null 2>&1 || true
git submodule update --init --recursive >/dev/null 2>&1 || true
if [[ ! -f "vendor/fyra/include/ir/Module.h" ]]; then
  FYRA_URL=$(git config -f .gitmodules --get submodule.fyra.url || true)
  [[ -n "${FYRA_URL}" ]] || { echo "Missing Fyra URL in .gitmodules"; exit 1; }
  rm -rf vendor/fyra
  git clone --depth 1 "${FYRA_URL}" vendor/fyra
fi

echo "Building compiler before running tests..."
make
[[ -x "$LIMITLY" ]] || { echo "Compiler binary not found at $LIMITLY"; exit 1; }

python3 - <<'PY'
import glob, fnmatch, re, subprocess, pathlib
manifest='tests/test_manifest.txt'
rules=[]
for ln in pathlib.Path(manifest).read_text().splitlines():
    ln=ln.strip()
    if not ln or ln.startswith('#'): continue
    status,pat=ln.split('|',1)
    rules.append((status.strip(),pat.strip()))
files=sorted(glob.glob('tests/**/*.lm',recursive=True))
errpat=re.compile(r"segmentation fault|segfault|error\[E|Error:|RuntimeError|SemanticError|BytecodeError|❌ FAIL|ASSERT.*FAIL|Assertion.*failed",re.I)
counts={'pass':0,'compile_error':0,'skip':0,'fail':0}

def expected(file):
    e='pass'
    for st,pat in rules:
        if fnmatch.fnmatch(file, pat):
            e=st
    return e

for f in files:
    exp=expected(f)
    if exp=='skip':
        print(f"SKIP {f}")
        counts['skip']+=1
        continue
    
    try:
        out=subprocess.run(['./bin/limitly',f],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=20).stdout
    except subprocess.TimeoutExpired:
        out='TIMEOUT'

    has_err=bool(errpat.search(out))
    ok=(not has_err) if exp=='pass' else has_err
    if ok:
        print(f"PASS {f} (expected {exp})")
        counts[exp]+=1
    else:
        print(f"FAIL {f} (expected {exp})")
        print('\n'.join(out.splitlines()[:8]))
        counts['fail']+=1

print('=== SUMMARY ===')
for k,v in counts.items(): print(f"{k.upper()}: {v}")
raise SystemExit(1 if counts['fail'] else 0)
PY
