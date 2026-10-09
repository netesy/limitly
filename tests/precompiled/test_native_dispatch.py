"""Exercise stack-backed exported arguments, including nested VM callbacks."""
import os
import subprocess
import sys
import shlex
from pathlib import Path
import tempfile
import unittest

from run_benchmark import ROOT, measure_run, preserve_artifacts
import test_benchmark


class NativeDispatchTests(unittest.TestCase):
    @unittest.skipUnless(sys.platform.startswith('linux'), 'ELF cache fixture')
    def test_cache_registration_clear_and_abi_rejection(self):
        with tempfile.TemporaryDirectory(prefix='lymar-dispatch-cache-') as tmp:
            directory = Path(tmp)
            libraries = []
            cxx = shlex.split(os.environ.get('CXX', 'g++'))
            object_dir = Path(os.environ.get('LYMAR_TEST_OBJECT_DIR', ROOT / 'build/obj/release'))
            for number, version in ((11, 1), (22, 1), (33, 99)):
                source = directory / f'entry{number}.cpp'
                library = directory / f'entry{number}.so'
                source.write_text(f'''#include <cstdint>
#include <cstddef>
extern "C" uint32_t lymar_module_abi_version() {{ return {version}; }}
extern "C" uint64_t answer(const void*,void*,const uint64_t*,size_t) asm("cache.answer");
extern "C" uint64_t answer(const void*,void*,const uint64_t*,size_t) {{ return ({number}ULL<<3)|1ULL; }}
''')
                subprocess.run([*cxx, '-shared', '-fPIC', str(source), '-o', str(library)], check=True)
                libraries.append(str(library))
            executable = directory / 'check'
            subprocess.run([*cxx, '-std=c++20', '-O2', '-Isrc',
                            'tests/precompiled/test_dispatch_cache.cpp',
                            str(object_dir / 'liblymar.a'), str(object_dir / 'libfyra.a'),
                            '-lffi', '-ldl', '-pthread', '-o', str(executable)], cwd=ROOT, check=True)
            result = subprocess.run([str(executable), *libraries], text=True,
                                    capture_output=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn('Dispatch cache invalidation and ABI rejection passed', result.stdout)

    def test_direct_operation_permissions_bounds_and_promotion(self):
        with tempfile.TemporaryDirectory(prefix='lymar-direct-operations-') as tmp:
            executable = Path(tmp) / 'check'
            cxx = shlex.split(os.environ.get('CXX', 'g++'))
            object_dir = Path(os.environ.get('LYMAR_TEST_OBJECT_DIR', ROOT / 'build/obj/release'))
            subprocess.run([*cxx, '-std=c++20', '-O2', '-Isrc',
                            'tests/precompiled/test_direct_operations.cpp',
                            str(object_dir / 'liblymar.a'), str(object_dir / 'libfyra.a'),
                            '-lffi', '-ldl', '-pthread', '-o', str(executable)], cwd=ROOT, check=True)
            result = subprocess.run([str(executable)], text=True, capture_output=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn('Direct operation bounds, frame validation, atomic access and promotion passed', result.stdout)

    def test_zero_large_arity_and_reentrant_callbacks(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='dispatch_') as tmp:
            directory = Path(tmp)
            name = directory.name
            parameters = ', '.join(f'a{i}: int' for i in range(70))
            arguments = ', '.join(str(i) for i in range(70))
            module = directory / (name + '.lm')
            module.write_text('pub fn zero(): int { return 42; }\n'
                              f'pub fn wide({parameters}): int {{ return a0 + a63 + a69; }}\n'
                              'pub fn invoke(callback: fn(int): int, value: int): int {\n'
                              '    return callback(value) + value;\n}\n'
                              'pub fn boundaries(): [any] { var xs=[7]; xs[0]=9; append(xs,11); '
                              'var d={"k":12}; d["k"]=13; return [xs[0],xs[1],xs[-1],xs[99],d["k"],d["missing"]]; }\n'
                              'pub fn strings(): [any] { return [_builtin_string_contains("abc", "b"), '
                              '_builtin_string_starts_with("abc", "a"), _builtin_string_ends_with("abc", "c"), '
                              '_builtin_string_index_of("abc", "b"), _builtin_string_byte_len("abc"), '
                              '_builtin_string_byte_at("abc", 2)]; }\n')
            check = directory / 'check.lm'
            check.write_text(f'''import build.{name}.{name} as native;
fn callback(value: int): int {{ return native.zero() + value; }}
for (var i = 0; i < 20; i = i + 1) {{
    assert(native.zero() == 42);
    assert(native.wide({arguments}) == 132);
    assert(native.invoke(callback, i) == 42 + i * 2);
}}
print(native.boundaries());
print(native.strings());
print("DISPATCH_OK");
''')
            extension = '.dll' if os.name == 'nt' else ('.dylib' if os.sys.platform == 'darwin' else '.so')
            library = ROOT / 'bin' / ('lib' + name + extension)
            compiler = test_benchmark.BenchmarkValidationTests.compiler()
            with preserve_artifacts([library, Path(str(library) + '.meta')]):
                _, expected, _ = measure_run([compiler, 'run', str(check)])
                for level in (0, 1, 2):
                    with self.subTest(optimization=level):
                        measure_run([compiler, 'build', '-shared', f'-O{level}',
                                     str(module.relative_to(ROOT)), '-o', str(library)])
                        env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK='1',
                                   LYMAR_TRACE_PRECOMPILED='1')
                        _, actual, trace = measure_run([compiler, 'run', str(check)], env)
                        self.assertEqual(actual, expected)
                        prefix = f'PRECOMPILED_CALL: build.{name}.{name}.'
                        self.assertEqual(trace.count(prefix + 'wide\n'), 20)
                        self.assertEqual(trace.count(prefix + 'invoke\n'), 20)
                        self.assertEqual(trace.count(prefix + 'zero\n'), 40)


if __name__ == '__main__':
    unittest.main()
