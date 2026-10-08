"""Exercise runtime selection and Fyra/driver linking without masking failures."""
import json
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
COMPILER = Path(os.environ.get("LYMAR_EXECUTABLE", ROOT / "bin/lymar")).resolve()


class TargetRuntimeTests(unittest.TestCase):
    def build(self, source, output, environment, *options):
        return subprocess.run([str(COMPILER), "build", *options, str(source), "-o", str(output)],
                              cwd=ROOT, env=environment, text=True, capture_output=True, timeout=120)

    def test_target_runtime_errors_are_explicit(self):
        with tempfile.TemporaryDirectory(prefix="lymar-target-runtime-") as tmp:
            directory = Path(tmp)
            source = directory / "program.lm"
            source.write_text('print("LINKED");')
            env = dict(os.environ, LYMAR_AOT_RUNTIME=str(directory / "missing.a"))
            for platform, architecture in (("linux", "x86_64"), ("linux", "aarch64"),
                                           ("linux", "riscv64"), ("windows", "x86_64"),
                                           ("macos", "aarch64")):
                with self.subTest(platform=platform, architecture=architecture):
                    result = self.build(source, directory / "program", env,
                                        "-target", platform, "-arch", architecture)
                    self.assertNotEqual(result.returncode, 0)
                    self.assertIn("Missing standalone runtime for", result.stderr)
            result = self.build(source, directory / "program", os.environ, "-arch", "typo")
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("Unsupported architecture: typo", result.stderr)

    @unittest.skipIf(os.name == "nt", "Executable Python wrapper uses a POSIX shebang")
    def test_driver_receives_paths_as_arguments(self):
        with tempfile.TemporaryDirectory(prefix="lymar target paths ") as tmp:
            directory = Path(tmp)
            source = directory / "program with spaces.lm"
            output = directory / "result with spaces"
            log = directory / "arguments.json"
            wrapper = directory / "target driver"
            wrapper.write_text('#!/usr/bin/env python3\nimport json, os, sys\n'
                               f'open({str(log)!r}, "w").write(json.dumps(sys.argv[1:]))\n'
                               f'os.execv({str(ROOT / "tests/memory/aot_linker.py")!r}, '
                               f'[{str(ROOT / "tests/memory/aot_linker.py")!r}, *sys.argv[1:]])\n')
            wrapper.chmod(0o755)
            source.write_text('print("LINKED");')
            env = dict(os.environ, LYMAR_AOT_LINKER="driver", LYMAR_AOT_CXX=str(wrapper))
            result = self.build(source, output, env)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            arguments = json.loads(log.read_text())
            self.assertEqual(arguments[-2:], ["-o", str(output)])
            self.assertTrue(any(arg.endswith("liblymar_aot.a") for arg in arguments))
            executed = subprocess.run([str(output)], text=True, capture_output=True, timeout=30)
            self.assertEqual(executed.returncode, 0, executed.stdout + executed.stderr)
            self.assertEqual(executed.stdout.strip(), "LINKED")
            self.assertFalse(list(directory.glob("*.lymar-*.o")))


if __name__ == "__main__":
    unittest.main()
