import os
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[2]
EXECUTABLE = Path(os.environ.get("LYMAR_SOURCE_OWNERSHIP_EXECUTABLE", ROOT / "bin/test_source_ownership")).resolve()
class SourceOwnershipTests(unittest.TestCase):
    def test_serialized_source_execution(self):
        with tempfile.TemporaryDirectory(prefix="lymar-source-ownership-") as tmp:
            env = dict(os.environ, LYMAR_UNIFIED_OWNERSHIP="1", LYMAR_AOT_LINKER="driver",
                LYMAR_AOT_RUNTIME=str(EXECUTABLE.parent / "liblymar_aot.a"),
                LYMAR_AOT_CXX=str(ROOT / "tests/memory/aot_linker.py"))
            result = subprocess.run([str(EXECUTABLE),tmp],cwd=ROOT,env=env,text=True,capture_output=True,timeout=120)
            self.assertEqual(result.returncode,0,result.stdout+result.stderr)
            self.assertEqual(result.stdout.splitlines(),["7","9","9","11","false","true","2.5","Source ownership serialization and execution passed"])
            self.assertNotIn("Sanitizer",result.stderr)
            programs = sorted(Path(tmp).glob("source-o[012]"))
            if programs: self.assertEqual(len(programs),3)
            for program in programs:
                executed = subprocess.run([str(program)],env=env,text=True,capture_output=True,timeout=30)
                self.assertEqual(executed.returncode,0,executed.stdout+executed.stderr)
                self.assertEqual(executed.stdout.strip(),"7\n9\n9\n11\nfalse\ntrue\n2.5")
                self.assertNotIn("Sanitizer",executed.stderr)
if __name__ == "__main__": unittest.main()
