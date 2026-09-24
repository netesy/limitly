import os, sys, subprocess, tempfile
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from run_tests import tests, limitly_path

results = {
    'pass': [],
    'mismatch': [],
    'build_fail': [],
    'crash': [],
}

for test in tests:
    test_path = os.path.normpath(test)
    if not os.path.exists(test_path):
        continue
    
    # 1. Expected output from VM
    r_vm = subprocess.run([limitly_path, 'run', test_path], capture_output=True, text=True, timeout=30)
    expected_out = r_vm.stdout
    
    # 2. Build AOT
    bin_path = os.path.join(tempfile.gettempdir(), f'test_bin_{os.path.basename(test_path)}.exe')
    if os.path.exists(bin_path):
        try: os.remove(bin_path)
        except: pass
        
    r_build = subprocess.run([limitly_path, 'build', '-target', 'windows', '-O', '2', '-o', bin_path, test_path], capture_output=True, text=True, timeout=30)
    if r_build.returncode != 0:
        results['build_fail'].append((test_path, r_build.stderr))
        continue
        
    # 3. Run AOT
    try:
        r_aot = subprocess.run([bin_path], capture_output=True, text=True, timeout=10)
        if r_aot.returncode != 0:
            results['crash'].append((test_path, r_aot.returncode, r_aot.stdout, r_aot.stderr))
        elif r_aot.stdout != expected_out:
            results['mismatch'].append((test_path, expected_out, r_aot.stdout))
        else:
            results['pass'].append(test_path)
    except subprocess.TimeoutExpired:
        results['crash'].append((test_path, 'TIMEOUT', '', ''))
    finally:
        if os.path.exists(bin_path):
            try: os.remove(bin_path)
            except: pass

total_count = len(results['pass']) + len(results['mismatch']) + len(results['build_fail']) + len(results['crash'])
print(f"Total tests run: {total_count}")
print(f"Passed: {len(results['pass'])}")
print(f"Mismatches: {len(results['mismatch'])}")
print(f"Build fails: {len(results['build_fail'])}")
print(f"Crashes / Non-zero exit: {len(results['crash'])}")

print("\n=== PASSED TESTS ===")
for t in results['pass']:
    print(f"  [PASS] {t}")

if results['mismatch']:
    print("\n=== MISMATCHED TESTS ===")
    for t, exp, act in results['mismatch']:
        print(f"  [MISMATCH] {t}")
        print(f"    Expected: {repr(exp)}")
        print(f"    Actual:   {repr(act)}")

if results['build_fail']:
    print("\n=== BUILD FAILS ===")
    for t, err in results['build_fail']:
        print(f"  [BUILD FAIL] {t}: {err}")

if results['crash']:
    print("\n=== RUNTIME CRASHES / NON-ZERO EXIT ===")
    for t, code, out, err in results['crash']:
        print(f"  [CRASH] {t} (exit code {code})")
        if out:
            last_lines = [l for l in out.strip().splitlines() if l.strip()]
            if last_lines:
                print(f"    Last output: {last_lines[-1]}")
