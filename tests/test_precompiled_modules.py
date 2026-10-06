import os
import subprocess
import shutil

def run_cmd(cmd):
    p = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return p.returncode, p.stdout, p.stderr

def test_ui_and_native_leaves():
    print("================================================================================")
    print("           PRECOMPILED STD.UI, NATIVE-LEAF, & DEPENDENCY TESTS                  ")
    print("================================================================================")

    # 1. Build all precompiled shared libraries
    modules = [
        ("std/ui/index.lm", "bin/libui.so"),
        ("std/graphics/index.lm", "bin/libgraphics.so"),
        ("std/gg/index.lm", "bin/libgg.so"),
        ("std/image/index.lm", "bin/libimage.so"),
        ("std/compress/index.lm", "bin/libcompress.so"),
        ("std/regex/index.lm", "bin/libregex.so"),
        ("std/font/index.lm", "bin/libfont.so"),
    ]

    for src, out in modules:
        code, stdout, stderr = run_cmd(f"./bin/lymar build -shared {src} -o {out}")
        assert code == 0, f"Failed to build {out}: {stderr}"
        assert os.path.exists(out), f"Artifact missing: {out}"
        assert os.path.exists(out + ".meta"), f"Metadata missing: {out}.meta"

    # 2. Retained UI Test
    code, stdout, stderr = run_cmd("./bin/lymar run tests/retained_ui_test.lm")
    assert code == 0, f"Retained UI test failed: {stderr}"
    print("[PASS] Precompiled std.ui Retained Logic & Tree State verified")

    # 3. Native-leaf composition tests
    code, stdout, stderr = run_cmd("./bin/lymar run tests/std_gg_smoke.lm")
    assert code == 0, f"std.gg smoke test failed: {stderr}"
    print("[PASS] Precompiled std.gg -> Sokol native composition verified")

    code, stdout, stderr = run_cmd("./bin/lymar run tests/compress/test_compress.lm")
    assert code == 0, f"std.compress test failed: {stderr}"
    print("[PASS] Precompiled std.compress -> zlib native composition verified")

    code, stdout, stderr = run_cmd("./bin/lymar run tests/regex/test_regex_matches.lm")
    assert code == 0, f"std.regex test failed: {stderr}"
    print("[PASS] Precompiled std.regex native composition verified")

    print("[SUCCESS] All std.ui and native-leaf composition tests passed successfully!")

if __name__ == "__main__":
    test_ui_and_native_leaves()
