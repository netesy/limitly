import subprocess
import os

def test_reachability():
    lm_file = "tests/precompiled/fixture_reachability.lm"
    so_file = "bin/libfixture.so"
    meta_file = "bin/libfixture.so.meta"

    os.makedirs("tests/precompiled", exist_ok=True)
    with open(lm_file, "w") as f:
        f.write("""
pub fn exported_entry(): int {
    return private_helper();
}

fn private_helper(): int {
    return 42;
}

fn private_dead_code(): int {
    return 999;
}
""")

    res = subprocess.run(f"./bin/lymar build -shared {lm_file} -o {so_file}", shell=True, capture_output=True, text=True)
    assert res.returncode == 0, f"Build failed: {res.stderr}"

    assert os.path.exists(meta_file), "Meta file missing"
    with open(meta_file, "r") as f:
        meta_content = f.read()

    print("=== META FILE EXPORTS ===")
    print(meta_content)

    assert "exported_entry" in meta_content, "exported_entry should be exported"
    assert "private_dead_code" not in meta_content, "private_dead_code should NOT be in exported symbols metadata"

    print("[SUCCESS] Fyra reachability test passed successfully!")

if __name__ == "__main__":
    test_reachability()
