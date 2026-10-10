"""Portable make precompile command construction and failure propagation."""
import importlib.util
from pathlib import Path
import tempfile
import unittest
import os
import shlex
import subprocess
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('precompile', ROOT / 'scripts/precompile.py')
driver = importlib.util.module_from_spec(spec)
spec.loader.exec_module(driver)


class PrecompileDriverTests(unittest.TestCase):
    def test_shared_only_is_explicit(self):
        with tempfile.TemporaryDirectory() as tmp:
            def compile_module(args, **kwargs):
                output = Path(args[-1])
                output.touch()
                Path(str(output) + '.meta').touch()
            with patch.object(driver.subprocess, 'run', side_effect=compile_module) as run:
                driver.main(['--compiler', 'bin/lymar', '--output-dir', tmp,
                             '--platform', 'windows', '--artifacts', 'shared',
                             '--modules', 'std.string'])
                self.assertEqual(run.call_count, 1)
                self.assertEqual(run.call_args.args[0][4], '-shared')

    def test_windows_process_argument_quoting(self):
        with tempfile.TemporaryDirectory() as tmp:
            source = Path(tmp) / 'quote.cpp'
            executable = Path(tmp) / ('quote.exe' if os.name == 'nt' else 'quote')
            source.write_text(r'''
#include "backend/native/process_arguments.hh"
#include <cassert>
int main() {
    using LM::Backend::Native::quote_windows_argument;
    assert(quote_windows_argument("") == R"("")");
    assert(quote_windows_argument(R"(C:\Program Files\g++.exe)") == R"("C:\Program Files\g++.exe")");
    assert(quote_windows_argument(R"(C:\ends with slash\)") == R"("C:\ends with slash\\")");
    assert(quote_windows_argument(R"(a\"b)") == R"("a\\\"b")");
    assert(quote_windows_argument("%PATH% & !HOME!") == R"("%PATH% & !HOME!")");
}
''')
            subprocess.run([*shlex.split(os.environ.get('CXX', 'c++')), '-std=c++20',
                            '-I' + str(ROOT / 'src'), str(source), '-o', str(executable)], check=True)
            subprocess.run([str(executable)], check=True)

    def test_platform_outputs_and_paths_with_spaces(self):
        for platform, extensions in (('windows', ('.dll', '.lib')),
                                     ('linux', ('.so', '.a')),
                                     ('macos', ('.dylib', '.a'))):
            with self.subTest(platform=platform), tempfile.TemporaryDirectory(prefix='precompile space ') as tmp:
                calls = []
                def compile_module(args, **kwargs):
                    self.assertTrue(kwargs['check'])
                    self.assertEqual(args[0], str(Path(tmp) / 'compiler with spaces.exe'))
                    self.assertEqual(args[2:4], ['-target', platform])
                    self.assertEqual(args[5], str(Path('std/string/index.lm')))
                    calls.append(args)
                    output = Path(args[-1])
                    output.touch()
                    Path(str(output) + '.meta').touch()
                with patch.object(driver.subprocess, 'run', side_effect=compile_module):
                    driver.main(['--compiler', str(Path(tmp) / 'compiler with spaces.exe'),
                                 '--output-dir', tmp, '--platform', platform, '--modules', 'std.string'])
                self.assertEqual([Path(call[-1]).suffix for call in calls], list(extensions))

    def test_failed_shared_build_stops_before_static(self):
        with tempfile.TemporaryDirectory() as tmp:
            error = driver.subprocess.CalledProcessError(1, 'compiler')
            with patch.object(driver.subprocess, 'run', side_effect=error) as run:
                with self.assertRaises(driver.subprocess.CalledProcessError):
                    driver.main(['--compiler', 'bin/lymar', '--output-dir', tmp,
                                 '--platform', 'windows', '--modules', 'std.string'])
                self.assertEqual(run.call_count, 1)

    def test_missing_metadata_is_failure(self):
        with tempfile.TemporaryDirectory() as tmp:
            with patch.object(driver.subprocess, 'run'):
                with self.assertRaisesRegex(RuntimeError, 'artifact and metadata'):
                    driver.main(['--compiler', 'bin/lymar', '--output-dir', tmp,
                                 '--platform', 'windows', '--modules', 'std.string'])


if __name__ == '__main__':
    unittest.main()
