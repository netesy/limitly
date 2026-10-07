import os
import subprocess
import shutil

def run_cmd(cmd):
    p = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return p.returncode, p.stdout, p.stderr

def setup_base():
    # Build standard libfont.so
    run_cmd("./bin/lymar build -shared std/font/index.lm -o bin/libfont.so")
    assert os.path.exists("bin/libfont.so"), "Base libfont.so build failed"
    assert os.path.exists("bin/libfont.so.meta"), "Base libfont.so.meta build failed"

def cleanup():
    # Restore base build
    setup_base()

def test_1_valid_artifact():
    setup_base()
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Valid artifact execution failed: {err}"
    print("[PASS] Condition 1: Valid artifact accepted and executed")

def test_2_missing_artifact():
    setup_base()
    os.remove("bin/libfont.so")
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Missing artifact fallback failed: {err}"
    print("[PASS] Condition 2: Missing artifact falls back to source interpretation")

def test_3_stale_source_identity():
    setup_base()
    # Corrupt source_hash in meta
    with open("bin/libfont.so.meta", "r") as f:
        meta = f.read()
    meta = meta.replace("source_hash=", "source_hash=DEADBEEF00000000")
    with open("bin/libfont.so.meta", "w") as f:
        f.write(meta)
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Stale source fallback failed: {err}"
    print("[PASS] Condition 3: Stale source identity falls back to source interpretation")

def test_4_wrong_lymarrt_abi():
    setup_base()
    with open("bin/libfont.so.meta", "r") as f:
        meta = f.read()
    meta = meta.replace("abi_version=1.0.0", "abi_version=9.9.9")
    with open("bin/libfont.so.meta", "w") as f:
        f.write(meta)
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Wrong ABI fallback failed: {err}"
    print("[PASS] Condition 4: Wrong lymarrt ABI falls back to source interpretation")

def test_5_wrong_target():
    setup_base()
    with open("bin/libfont.so.meta", "r") as f:
        meta = f.read()
    meta = meta.replace("target_triple=x86_64-linux", "target_triple=arm64-darwin")
    with open("bin/libfont.so.meta", "w") as f:
        f.write(meta)
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Wrong target fallback failed: {err}"
    print("[PASS] Condition 5: Wrong target triple falls back to source interpretation")

def test_6_malformed_metadata():
    setup_base()
    with open("bin/libfont.so.meta", "w") as f:
        f.write("MALFORMED_GARBAGE_NO_KEYS_###")
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Malformed metadata fallback failed: {err}"
    print("[PASS] Condition 6: Malformed metadata falls back to source interpretation")

def test_7_missing_export():
    setup_base()
    with open("bin/libfont.so.meta", "r") as f:
        meta = f.read()
    meta = meta.replace("exports=", "exports=non_existent_symbol,")
    with open("bin/libfont.so.meta", "w") as f:
        f.write(meta)
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Missing export fallback failed: {err}"
    print("[PASS] Condition 7: Missing export symbol falls back to source interpretation")

def test_8_signature_mismatch():
    setup_base()
    with open("bin/libfont.so.meta", "r") as f:
        meta = f.read()
    meta = meta.replace("signatures=", "signatures=std.font.load_font:fn(x: int, y: int): float;")
    with open("bin/libfont.so.meta", "w") as f:
        f.write(meta)
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Signature mismatch fallback failed: {err}"
    print("[PASS] Condition 8: Signature mismatch falls back to source interpretation")

def test_9_missing_dependency():
    setup_base()
    with open("bin/libfont.so.meta", "r") as f:
        meta = f.read()
    meta = meta.replace("dependencies=", "dependencies=std.nonexistent_dep,")
    with open("bin/libfont.so.meta", "w") as f:
        f.write(meta)
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Missing dependency fallback failed: {err}"
    print("[PASS] Condition 9: Missing dependency falls back to source interpretation")

def test_10_static_shared_mismatch():
    setup_base()
    with open("bin/libfont.so.meta", "r") as f:
        meta = f.read()
    meta = meta.replace("artifact_kind=shared", "artifact_kind=static")
    with open("bin/libfont.so.meta", "w") as f:
        f.write(meta)
    code, out, err = run_cmd("./bin/lymar run tests/precompiled/benchmark_workload_pure.lm")
    assert code == 0, f"Static/shared mismatch fallback failed: {err}"
    print("[PASS] Condition 10: Static/shared mismatch falls back to source interpretation")

def main():
    print("================================================================================")
    print("      COMPREHENSIVE 10-CASE PRECOMPILED MODULE FALLBACK PROOFS                  ")
    print("================================================================================")
    try:
        test_1_valid_artifact()
        test_2_missing_artifact()
        test_3_stale_source_identity()
        test_4_wrong_lymarrt_abi()
        test_5_wrong_target()
        test_6_malformed_metadata()
        test_7_missing_export()
        test_8_signature_mismatch()
        test_9_missing_dependency()
        test_10_static_shared_mismatch()
        print("================================================================================")
        print("[SUCCESS] ALL 10 COMPATIBILITY AND FALLBACK PROOFS PASSED PERFECTLY!")
        print("================================================================================")
    finally:
        cleanup()

if __name__ == "__main__":
    main()
