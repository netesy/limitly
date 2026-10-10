"""Real-source parity and emitted-code checks for native representation fast paths."""
import os
from pathlib import Path
import tempfile
import subprocess
import shlex
import unittest

from run_benchmark import ROOT, measure_run, preserve_artifacts
import test_benchmark


MODULE = '''
fn metrics(a: int, b: int): (int, int) { return (a, b); }
pub fn project(a: int, b: int): int {
    var pair = metrics(a, b);
    return pair[0] + pair[1];
}
pub fn alias_project(a: int, b: int): int {
    var pair = metrics(a, b);
    var alias = pair;
    return alias[0];
}
pub fn escaped_pair(a: int, b: int): (int, int) { return metrics(a, b); }
pub fn mutated_pair(a: int, b: int): int {
    var pair = metrics(a, b);
    pair[0] = 7;
    return pair[0];
}
pub fn identity(a: int, b: int): bool {
    var first = metrics(a, b);
    var second = metrics(a, b);
    return first == second;
}
fn mixed(a: any): (any, int) { return (a, 2); }
pub fn mixed_project(a: any): any {
    var pair = mixed(a);
    return pair[0];
}
pub fn lengths(text: str, values: [int]): [int] {
    return [len(text), len(values)];
}
pub fn erased_lengths(text: any, values: any): [int] {
    return [len(text), len(values), len(nil)];
}
pub fn invalid_length(value: any): int { return len(value); }
pub fn erased_math(a: any, b: any): [any] {
    return [a + b, a - b, a * b, a / b, a % b];
}
pub fn erased_copy(a: any, b: any): [bool] {
    var answer = a + b;
    var copied = answer;
    return [answer == copied, (answer as any) == (copied as any)];
}
'''


class NativeRepresentationTests(unittest.TestCase):
    def test_pair_proof_rejects_unknown_or_observable_uses(self):
        with tempfile.TemporaryDirectory(prefix='lymar-pair-proof-') as tmp:
            executable = Path(tmp) / 'check'
            objects = Path(os.environ.get('LYMAR_TEST_OBJECT_DIR', ROOT / 'build/obj/release'))
            cxx = shlex.split(os.environ.get('CXX', 'g++'))
            subprocess.run([*cxx, '-std=c++20', '-O2', '-Isrc',
                            'tests/precompiled/test_aggregate_lowering.cpp',
                            str(objects / 'liblymar.a'), str(objects / 'libfyra.a'),
                            '-lffi', '-ldl', '-pthread', '-o', str(executable)], cwd=ROOT, check=True)
            result = subprocess.run([str(executable)], text=True, capture_output=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn('Pair proof rejects mutation', result.stdout)

    def test_lengths_erasure_and_guarded_numeric_operations(self):
        compiler = test_benchmark.BenchmarkValidationTests.compiler()
        extension = '.dll' if os.name == 'nt' else ('.dylib' if os.sys.platform == 'darwin' else '.so')
        with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='native_repr_') as tmp:
            directory = Path(tmp)
            name = directory.name
            module = directory / (name + '.lm')
            module.write_text(MODULE)
            check = directory / 'check.lm'
            check.write_text(f'''import build.{name}.{name} as probe;
print(probe.project(19, 3));
print(probe.project(1152921504606846975, 1));
print(probe.project(1152921504606846976, 1));
print(probe.alias_project(19, 3));
print(probe.escaped_pair(19, 3));
print(probe.mutated_pair(19, 3));
print(probe.identity(19, 3));
print(probe.mixed_project(2.75));
print(probe.mixed_project([1, 2, 3]));
print(probe.lengths("", [] as [int]));
print(probe.lengths("hé😀", [1, 2, 3]));
print(probe.erased_lengths("hé😀", [1, 2, 3]));
print(probe.erased_lengths({{ "key": 1 }}, [1, 2, 3]));
print(probe.erased_math(19, 3));
print(probe.erased_math(1152921504606846975, 1));
print(probe.erased_math(-1152921504606846976, -1));
print(probe.erased_math(4000000000, 4000000000));
print(probe.erased_math(2.75, -1.5));
print(probe.erased_math(2.0, 0.0));
print(probe.erased_math("inf" as float, 2.0));
print(probe.erased_math("nan" as float, 2.0));
print(probe.erased_copy(2.5, 0.25));
print(probe.erased_copy("nan" as float, 0.0));
print(probe.erased_math("hello", " world"));
print("NATIVE_REPRESENTATION_OK");
''')
            library = ROOT / 'bin' / ('lib' + name + extension)
            with preserve_artifacts([library, Path(str(library) + '.meta')]):
                _, expected, _ = measure_run([compiler, 'run', str(check)])
                self.assertIn('[7, 3]', expected)
                self.assertIn('NATIVE_REPRESENTATION_OK', expected)
                invalid = directory / 'invalid.lm'
                invalid.write_text(f'import build.{name}.{name} as probe; print(probe.project(1, 2)); print(probe.invalid_length((1, 2))); print("SHOULD_NOT_RUN");')
                rejected = subprocess.run([compiler, 'run', str(invalid)], cwd=ROOT, text=True, capture_output=True, timeout=30)
                self.assertIn('unsupported type Tuple', rejected.stderr)
                self.assertNotIn('SHOULD_NOT_RUN', rejected.stdout)
                for level in (0, 1, 2):
                    with self.subTest(optimization=level):
                        build_env = dict(os.environ, LYMAR_KEEP_NATIVE_SOURCE='1')
                        measure_run([compiler, 'build', '-shared', f'-O{level}',
                                     str(module.relative_to(ROOT)), '-o', str(library)], build_env)
                        sources = list(library.parent.glob(library.name + '.lymar-*.cpp'))
                        self.assertEqual(len(sources), 1)
                        try:
                            generated = sources[0].read_text()
                            self.assertIn('=scope.track(native_length(api,ctx,', generated)
                            self.assertIn('_pair(api,ctx,argv,2)', generated)
                            self.assertIn('native_pair_set(api,ctx,', generated)
                            self.assertIn('if(a.small() && b.small())', generated)
                            self.assertIn('if(allow_fast && op!=HMod', generated)
                            self.assertNotIn('if(typed && a.small() && b.small()) {\n    int64_t', generated)
                        finally:
                            sources[0].unlink()
                        env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK='1',
                                   LYMAR_TRACE_PRECOMPILED='1')
                        _, actual, trace = measure_run([compiler, 'run', str(check)], env)
                        self.assertEqual(actual, expected)
                        rejected = subprocess.run([compiler, 'run', str(invalid)], cwd=ROOT, env=env, text=True, capture_output=True, timeout=30)
                        self.assertIn('unsupported type Tuple', rejected.stderr)
                        self.assertNotIn('SHOULD_NOT_RUN', rejected.stdout)
                        # Dispatch traces are emitted after successful calls; the throwing
                        # export cannot produce one. Fallback is disabled and the
                        # preceding successful export proves this artifact loaded.
                        self.assertIn(f'PRECOMPILED_CALL: build.{name}.{name}.project', rejected.stderr)
                        for export in ('project', 'alias_project', 'escaped_pair', 'mutated_pair', 'identity', 'mixed_project', 'lengths', 'erased_lengths', 'erased_math', 'erased_copy'):
                            self.assertIn(f'PRECOMPILED_CALL: build.{name}.{name}.{export}', trace)


if __name__ == '__main__':
    unittest.main()
