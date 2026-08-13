import os
import subprocess
import sys

# Try to import the tests list from run_tests.py
# If that is not directly importable due to path, we append the path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
try:
    from run_tests import tests
except ImportError:
    print("Error: Could not import tests list from run_tests.py")
    sys.exit(1)

limitly_path = os.path.abspath("bin/limitly.exe" if os.name == "nt" else "bin/limitly")

def generate_fyra_ir(test_file):
    print(f"Generating Fyra IR for {test_file}...")
    try:
        # Run limitly with -fyra-ir flag
        result = subprocess.run(
            [limitly_path, "-fyra-ir", test_file],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            timeout=10.0
        )
        if result.returncode != 0:
            print(f"  WARNING: Failed to generate Fyra IR for {test_file} (return code {result.returncode})")
            print("  --- STDERR ---")
            print(result.stderr)
            print("  --------------")
            return None
        return result.stdout
    except subprocess.TimeoutExpired:
        print(f"  WARNING: Timeout expired while generating Fyra IR for {test_file}")
        return None
    except Exception as e:
        print(f"  WARNING: Exception while generating Fyra IR for {test_file}: {e}")
        return None

def main():
    generated_count = 0
    failed_count = 0

    # Ensure output base directory exists
    output_base_dir = os.path.join("tests", "fyra")
    os.makedirs(output_base_dir, exist_ok=True)

    for test in tests:
        test_path = os.path.normpath(test)
        if not os.path.exists(test_path):
            print(f"Skipping {test_path} (does not exist)")
            continue

        # Get the relative path of the test within the tests/ directory
        # e.g., tests/basic/variables.lm -> basic/variables.lm
        rel_path = os.path.relpath(test_path, "tests")

        # Change file extension from .lm to .fyra
        base_rel, _ = os.path.splitext(rel_path)
        fyra_rel_path = base_rel + ".fyra"

        # Determine full output path under tests/fyra/
        # e.g., tests/fyra/basic/variables.fyra
        output_path = os.path.join(output_base_dir, rel_path)
        output_path, _ = os.path.splitext(output_path)
        output_path += ".fyra"

        # Ensure target subdirectory exists
        os.makedirs(os.path.dirname(output_path), exist_ok=True)

        # Generate Fyra IR and save to file
        fyra_ir = generate_fyra_ir(test_path)
        if fyra_ir is not None and fyra_ir.strip():
            with open(output_path, "w", encoding="utf-8") as f:
                f.write(fyra_ir)
            print(f"  Saved to: {output_path}")
            generated_count += 1
        else:
            print(f"  FAILED to generate valid IR for: {test_path}")
            failed_count += 1

    print("====================================================")
    print(f"Generation Summary: GENERATED={generated_count}, FAILED={failed_count}")
    print("====================================================")

    if failed_count > 0:
        sys.exit(1)
    else:
        sys.exit(0)

if __name__ == "__main__":
    main()
