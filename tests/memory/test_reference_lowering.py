"""Check reference results from the VM, native module and actual Fyra executables."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[2]
EXECUTABLE = Path(os.environ.get("LYMAR_REFERENCE_TEST_EXECUTABLE", ROOT / "bin/test_reference_lowering")).resolve()
class ReferenceLoweringTests(unittest.TestCase):
    def test_execution(self):
        with tempfile.TemporaryDirectory(prefix="lymar-references-") as tmp:
            env = dict(os.environ, LYMAR_AOT_LINKER="driver",
                       LYMAR_AOT_RUNTIME=str(EXECUTABLE.parent / "liblymar_aot.a"),
                       LYMAR_AOT_CXX=str(ROOT / "tests/memory/aot_linker.py"),
                       LYMAR_NATIVE_CXX=str(ROOT / "tests/memory/aot_linker.py"))
            result = subprocess.run([str(EXECUTABLE), tmp], cwd=ROOT, env=env,
                                    text=True, capture_output=True, timeout=120)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn("Reference VM/native/AOT lowering", result.stdout)
            self.assertEqual(result.stdout.splitlines().count("41"), 2)
            programs = sorted(Path(tmp).glob("checked-o[012]"))
            if programs:
                self.assertEqual(len(programs), 3)
            for program in programs:
                run = subprocess.run([str(program)], env=env, text=True, capture_output=True, timeout=30)
                self.assertEqual(run.returncode, 0, run.stdout + run.stderr)
                self.assertEqual(run.stdout.strip(), "41")
                self.assertNotIn("Sanitizer", run.stderr)
if __name__ == "__main__":
    unittest.main()
