"""Exercise numeric lowering through real source and the tagged module ABI."""
import os
from pathlib import Path
import tempfile
import unittest

from run_benchmark import ROOT, measure_run, preserve_artifacts
import test_benchmark


MODULE = '''
fn step(value: float): float { return value * 1.25 + 0.5; }
pub fn chain(value: float): float {
    var answer = value;
    for (var i = 0; i < 12; i = i + 1) { answer = step(answer); }
    return answer;
}
pub fn arithmetic(a: int, b: int): [any] {
    return [a + b, a - b, a * b, a / b, a % b];
}
pub fn floating(a: float, b: float): [any] {
    return [a + b, a - b, a * b, a / b, a % b];
}
pub fn erased(value: float): any { return step(value); }
fn erased_step(value: any): any { return (value as float) + 0.25; }
pub fn bridge(value: float): float { return erased_step(value * 2.0) as float; }
pub fn lifetime(value: float): float {
    var answer = value + 0.25;
    for (var i = 0; i < 5; i = i + 1) {
        var temporary = [answer];
        if (temporary[0] != answer) { return -99.0; }
    }
    return answer + 0.5;
}
pub fn special(): [any] {
    var nan_value = "nan" as float;
    var fresh = nan_value + 0.0;
    return [nan_value == nan_value, fresh == nan_value,
            nan_value < 1.0, nan_value <= 1.0,
            (2 as any) == nil, (true as any),
            -2.75 as int, 2.75 as int, 4 as float];
}
pub fn higher(value: float): float {
    var operation = fn(x: float): float { return x * 2.5; };
    return operation(value);
}
'''


class NativeNumericContractTests(unittest.TestCase):
    def test_overflow_erasure_calls_and_nested_region_lifetimes(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='numeric_contract_') as tmp:
            directory = Path(tmp)
            name = directory.name
            module = directory / (name + '.lm')
            module.write_text(MODULE)
            check = directory / 'check.lm'
            check.write_text(f'''import build.{name}.{name} as numeric;
print(numeric.chain(2.0));
print(numeric.erased(2.0));
assert(numeric.lifetime(2.0) == 2.75);
assert(numeric.higher(2.0) == 5.0);
assert(numeric.bridge(2.0) == 4.25);
print(numeric.special());
print(numeric.arithmetic(1152921504606846975, 1));
print(numeric.arithmetic(-1152921504606846976, -1));
print(numeric.arithmetic(4000000000, 4000000000));
print(numeric.arithmetic(-19, 3));
print(numeric.arithmetic(19, 0));
print(numeric.floating(-2.75, 1.5));
print(numeric.floating(2.0, 0.0));
print(numeric.floating("inf" as float, 2.0));
print("NUMERIC_CONTRACT_OK");
''')
            extension = '.dll' if os.name == 'nt' else ('.dylib' if os.sys.platform == 'darwin' else '.so')
            library = ROOT / 'bin' / ('lib' + name + extension)
            compiler = test_benchmark.BenchmarkValidationTests.compiler()
            with preserve_artifacts([library, Path(str(library) + '.meta')]):
                _, expected, _ = measure_run([compiler, 'run', str(check)])
                self.assertIn('NUMERIC_CONTRACT_OK', expected)
                for level in (0, 1, 2):
                    with self.subTest(optimization=level):
                        measure_run([compiler, 'build', '-shared', f'-O{level}',
                                     str(module.relative_to(ROOT)), '-o', str(library)])
                        env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK='1',
                                   LYMAR_TRACE_PRECOMPILED='1')
                        _, actual, trace = measure_run([compiler, 'run', str(check)], env)
                        self.assertEqual(actual, expected)
                        for export in ('chain', 'erased', 'bridge', 'lifetime', 'special', 'higher', 'arithmetic', 'floating'):
                            self.assertIn(f'PRECOMPILED_CALL: build.{name}.{name}.{export}', trace)


if __name__ == '__main__':
    unittest.main()
