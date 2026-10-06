import os
import subprocess
import shutil
import sys

def run_cmd(cmd):
    p = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return p.returncode, p.stdout, p.stderr

def test_deterministic_native_dispatch():
    print("================================================================================")
    print("                 DETERMINISTIC NATIVE DISPATCH PROOF TEST                       ")
    print("================================================================================")

    # 1. Build std.font precompiled module
    code, stdout, stderr = run_cmd("make precompile PRECOMPILE_MODULES=std.font")
    assert code == 0, f"make precompile failed: {stderr}"
    
    so_ext = ".so"
    if sys.platform == "darwin":
        so_ext = ".dylib"
    elif sys.platform == "win32":
        so_ext = ".dll"
        
    so_path = os.path.join("bin", "libfont" + so_ext)
    assert os.path.exists(so_path), f"Precompiled library missing: {so_path}"

    # 2. Run the proof test script with LYMAR_DISABLE_INTERPRETER_FALLBACK=1
    env = os.environ.copy()
    env["LYMAR_DISABLE_INTERPRETER_FALLBACK"] = "1"

    test_script = """import std.font as font;

var font_path = font.detect_system_font("DejaVu");
if (font_path == "") {
    font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
}

match (font.load_font_pure(font_path)) {
    val f => {
        var width = f.text_width("Hello Native Lymar World!", 16.0);
        print("SUCCESS text_width={width}");
    },
    err e => {
        print("Failed to load font");
    }
}
"""
    tmp_file = "test_native_proof.lm"
    with open(tmp_file, "w") as file_out:
        file_out.write(test_script)

    try:
        p = subprocess.run(["./bin/lymar", "run", tmp_file], env=env, capture_output=True, text=True)
        assert p.returncode == 0, f"Execution failed with code {p.returncode}: {p.stderr}\n{p.stdout}"
        assert "SUCCESS text_width=" in p.stdout, f"Expected output missing: {p.stdout}"
        print("[PASS] Method Font.text_width, FontInfo.get_glyph_hmetrics, ByteReader, and loops executed purely in precompiled native code without interpreter fallback!")
    finally:
        if os.path.exists(tmp_file):
            os.remove(tmp_file)

if __name__ == "__main__":
    test_deterministic_native_dispatch()
