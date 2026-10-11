"""Execute source regressions through the VM and every supported Fyra level."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
COMPILER = os.environ.get("LYMAR_EXECUTABLE", str(ROOT / "bin/lymar"))


class FyraValueParityTests(unittest.TestCase):
    def test_source_outputs(self):
        sources = (
            "tests/types/basic.lm",
            "tests/strings/interpolation.lm",
            "tests/loops/match_advanced.lm",
            "tests/stdlib/collections/priority_queue_test.lm",
        )
        env = dict(os.environ, LYMAR_AOT_LINKER="driver",
                   LYMAR_AOT_CXX=str(ROOT / "tests/memory/aot_linker.py"))
        with tempfile.TemporaryDirectory(prefix="lymar-value-parity-") as directory:
            probe = Path(directory) / "parameter_assignments.lm"
            probe.write_text("""
fn steps(n:int):int {
    var result=0;
    while(n>0) { n=n-1;result=result+1;if(result==5) {break;} }
    return result;
}
fn branch(value:int, yes:bool):int {if(yes) {value=7;}return value;}
assert(steps(3)==3);assert(steps(0)==0);
assert(branch(2,true)==7);assert(branch(2,false)==2);
print("PARAMETER_ASSIGNMENTS_OK");
""")
            for source in (*sources, str(probe)):
                vm = subprocess.run([COMPILER, "run", source], cwd=ROOT, env=env,
                                    capture_output=True, text=True, timeout=30)
                self.assertEqual(vm.returncode, 0, vm.stdout + vm.stderr)
                for level in (0, 1, 2):
                    with self.subTest(source=source, level=level):
                        output = str(Path(directory) / ("program.exe" if os.name == "nt" else "program"))
                        build = subprocess.run([COMPILER, "build", "-O", str(level),
                                                source, "-o", output], cwd=ROOT, env=env,
                                               capture_output=True, text=True, timeout=30)
                        self.assertEqual(build.returncode, 0, build.stdout + build.stderr)
                        native = subprocess.run([output], cwd=ROOT, env=env,
                                                capture_output=True, text=True, timeout=30)
                        self.assertEqual((native.returncode, native.stdout, native.stderr),
                                         (vm.returncode, vm.stdout, vm.stderr))
                        self.assertNotIn("Sanitizer", native.stderr)


if __name__ == "__main__":
    unittest.main()
