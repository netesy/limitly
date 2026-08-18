import subprocess
import sys
import os

try:
    from tests.run_tests import tests
except ImportError:
    try:
        sys.path.append(os.path.dirname(os.path.abspath(__file__)))
        from tests.run_tests import tests
    except ImportError:
        print("Could not import tests from tests.run_tests")
        sys.exit(1)

limitly_path = os.path.abspath("bin/limitly.exe" if os.name == "nt" else "bin/limitly")
fyra_dir = "tests/fyra"
os.makedirs(fyra_dir, exist_ok=True)

passed = 0
failed = 0

for test in tests:
    test_path = os.path.normpath(test)
    if not os.path.exists(test_path):
        continue

    # Create a simplified file name, e.g., basic_variables.fyra
    base_name = os.path.basename(test_path)
    name_without_ext = os.path.splitext(base_name)[0]
    dir_name = os.path.basename(os.path.dirname(test_path))
    out_file = os.path.join(fyra_dir, f"{dir_name}_{name_without_ext}.fyra")
    
    print(f"Generating {out_file} for {test_path}...")
    
    try:
        with open(out_file, "w") as f:
            res = subprocess.run(
                [limitly_path, "-fyra-ir", test_path],
                stdout=f,
                stderr=subprocess.PIPE,
                text=True,
                timeout=10.0
            )
            
            if res.returncode == 0:
                passed += 1
            else:
                print(f"Failed to generate for {test_path} (exit code: {res.returncode})")
                failed += 1
                if res.stderr:
                    print(f"STDERR: {res.stderr}")
    except subprocess.TimeoutExpired:
         print(f"Timeout generating {test_path}")
         failed += 1
    except Exception as e:
         print(f"Error generating {test_path}: {e}")
         failed += 1

print(f"Done. Generated {passed} files. Failed to generate {failed} files.")
