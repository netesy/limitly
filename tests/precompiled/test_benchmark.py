import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

from run_benchmark import ROOT, measure_run, preserve_artifacts, resolve_font, workload_result


class BenchmarkValidationTests(unittest.TestCase):
    def test_rejects_missing_zero_duplicate_and_nonfinite_results(self):
        for output in ("Failed to load font", "WORKLOAD_DONE: 0", "WORKLOAD_DONE: 1e999",
                       "WORKLOAD_DONE: 1\nWORKLOAD_DONE: 1"):
            with self.subTest(output=output), self.assertRaises(RuntimeError):
                workload_result(output)
        self.assertEqual(workload_result("WORKLOAD_DONE: 23337.5"), 23337.5)

    def test_rejects_failed_process_even_with_a_result_marker(self):
        with self.assertRaises(RuntimeError):
            measure_run([sys.executable, "-c", "print('WORKLOAD_DONE: 42'); raise SystemExit(1)"])

    def test_restores_existing_artifacts_after_failure(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "libfont.so"
            path.write_text("original")
            with self.assertRaises(RuntimeError):
                with preserve_artifacts([path]):
                    path.write_text("replacement")
                    raise RuntimeError("failed benchmark")
            self.assertEqual(path.read_text(), "original")

    def test_addition_evaluates_side_effecting_operands_once(self):
        source = '''
frame Counter {
    pub var value: int;
    pub init() { self.value = 0; }
    pub fn next(): int { self.value = self.value + 1; return self.value; }
}
var counter = Counter();
var sum = counter.next() + counter.next();
assert(sum == 3, "Addition evaluated its operands twice");
assert(counter.value == 2, "Unexpected side effects");
print("OPERANDS_OK");
'''
        with tempfile.TemporaryDirectory(dir=ROOT / "build", prefix="operand_") as tmp:
            path = Path(tmp) / "check.lm"
            path.write_text(source)
            _, output, _ = measure_run([self.compiler(), "run", str(path)])
            self.assertEqual(output.strip(), "OPERANDS_OK")

    def test_native_scalar_calls_match_interpretation(self):
        extension = ".dll" if os.name == "nt" else (".dylib" if sys.platform == "darwin" else ".so")
        with tempfile.TemporaryDirectory(dir=ROOT / "build", prefix="native_") as tmp:
            directory = Path(tmp)
            name = directory.name
            module = directory / f"{name}.lm"
            module.write_text('pub fn add(a: int, b: int): int { return a + b; }\n'
                              'pub fn scale(a: float, b: float): float { return a * b; }\n')
            check = directory / "check.lm"
            check.write_text(f'import build.{name}.{name} as probe;\n'
                             'assert(probe.add(19, 23) == 42, "Native integer mismatch");\n'
                             'assert(probe.scale(2.5, 4.0) == 10.0, "Native float mismatch");\n'
                             'print("SCALARS_OK");\n')
            library = ROOT / "bin" / ("lib" + name + extension)
            with preserve_artifacts([library, Path(str(library) + ".meta")]):
                _, interpreted, _ = measure_run([self.compiler(), "run", str(check)])
                measure_run([self.compiler(), "build", "-shared", str(module.relative_to(ROOT)), "-o", str(library)])
                env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK="1", LYMAR_TRACE_PRECOMPILED="1")
                _, native, trace = measure_run([self.compiler(), "run", str(check)], env)
                self.assertEqual(native, interpreted)
                self.assertIn("PRECOMPILED_CALL:", trace)
                self.assertEqual(native.strip(), "SCALARS_OK")

    def test_module_search_paths_survive_type_checking(self):
        with tempfile.TemporaryDirectory() as tmp:
            directory = Path(tmp)
            (directory / "probe.lm").write_text('pub fn answer(): int { return 42; }\n')
            source = directory / "check.lm"
            source.write_text('import probe; assert(probe.answer() == 42); print("MODULE_OK");\n')
            for args, env in ((["-I", tmp], dict(os.environ)),
                              ([], dict(os.environ, LYMAR_HOME=tmp))):
                with self.subTest(args=args):
                    # Keep the program outside its module's directory so direct
                    # current-directory lookup cannot mask a missing search path.
                    outside = directory / "outside"
                    outside.mkdir(exist_ok=True)
                    result = subprocess.run([self.compiler(), "run", *args, str(source)],
                                            cwd=outside, env=env, capture_output=True, text=True)
                    self.assertEqual(result.returncode, 0, result.stderr)
                    self.assertEqual(result.stdout.strip(), "MODULE_OK")

    def test_native_dependency_changes_invalidate_existing_artifacts(self):
        with tempfile.TemporaryDirectory(dir=ROOT / "build", prefix="dependency_") as tmp:
            directory = Path(tmp)
            name = directory.name
            dependency = directory / "helper.lm"
            dependency.write_text("pub fn value(): int { return 42; }\n")
            module = directory / f"{name}.lm"
            module.write_text(f"import build.{name}.helper as helper;\n"
                              "pub fn value(): int { return helper.value(); }\n")
            check = directory / "check.lm"
            check.write_text(f'import build.{name}.{name} as probe; print("VALUE: {{probe.value()}}");')
            library = ROOT / "bin" / ("lib" + name + ".so")
            env = dict(os.environ, LYMAR_TRACE_PRECOMPILED="1")
            with preserve_artifacts([library, Path(str(library) + ".meta")]):
                measure_run([self.compiler(), "build", "-shared", str(module.relative_to(ROOT)), "-o", str(library)])
                _, native, trace = measure_run([self.compiler(), "run", str(check)], env)
                self.assertIn("VALUE: 42", native)
                self.assertIn("PRECOMPILED_CALL:", trace)
                timestamp = dependency.stat()
                dependency.write_text("pub fn value(): int { return 43; }\n")
                os.utime(dependency, ns=(timestamp.st_atime_ns, timestamp.st_mtime_ns))
                _, updated, trace = measure_run([self.compiler(), "run", str(check)], env)
                self.assertIn("VALUE: 43", updated)
                self.assertNotIn("PRECOMPILED_CALL:", trace)

    def test_native_objects_preserve_aliases_mutations_and_returns(self):
        module_source = '''
frame Box {
    pub var amount: float;
    pub var items: [int];
    pub init(amount: float, items: [int]) { self.amount = amount; self.items = items; }
    pub fn increase(): float { self.amount = self.amount + 1.5; return self.amount; }
}
pub fn mutate(box: Box, labels: {str: int}): Box {
    box.items[0] = box.items[0] + 7;
    box.amount = box.amount + 2.5;
    labels["answer"] = 42;
    return box;
}
pub fn make_box(): Box { return Box(3.5, [10, 20]); }
pub fn pair(box: Box): (int, float) { return (box.items[0], box.amount); }
pub fn greet(text: str): str { return text + "!"; }
pub fn outcome(valid: bool): Box? {
    if (valid) { return ok(make_box()); }
    return err();
}
pub fn make_adder(base: int): fn(int): int {
    return fn(amount: int): int { return base + amount; };
}
pub fn closure_sum(base: int): int {
    var next = fn(amount: int): int { return base + amount; };
    return next(4);
}
frame Node {
    pub var next: any;
    pub init() { self.next = nil; }
}
pub fn cycle(a: Node, b: Node): Node {
    a.next = b;
    b.next = a;
    return a;
}
'''
        with tempfile.TemporaryDirectory(dir=ROOT / "build", prefix="objects_") as tmp:
            directory = Path(tmp)
            name = directory.name
            module = directory / f"{name}.lm"
            module.write_text(module_source)
            check = directory / "check.lm"
            check.write_text(f'import build.{name}.{name} as probe;\n' + '''
var original = probe.Box(1.0, [5]);
var labels: {str: int} = {"answer": 0};
var alias = probe.mutate(original, labels);
assert(original.items[0] == 12);
assert(labels["answer"] == 42);
alias.amount = 8.0;
assert(original.amount == 8.0);
assert(original.increase() == 9.5);
var created = probe.make_box();
assert(created.items[1] == 20);
var pair = probe.pair(created);
assert(pair.0 == 10 and pair.1 == 3.5);
assert(probe.greet("hello") == "hello!");
match (probe.outcome(true)) {
    val box => { assert(box.amount == 3.5); assert(box.items[0] == 10); },
    err e => { assert(false, "Native result lost its object payload"); }
}
match (probe.outcome(false)) {
    val box => { assert(false, "Native error returned success"); },
    err e => { print("ERROR_OK"); }
}
assert(probe.closure_sum(6) == 10);
var adder = probe.make_adder(5);
assert(adder(7) == 12);
var first = probe.Node();
var second = probe.Node();
var cycle = probe.cycle(first, second);
assert(cycle.next == second and second.next == first);
print("OBJECTS_OK");
''')
            library = ROOT / "bin" / ("lib" + name + ".so")
            with preserve_artifacts([library, Path(str(library) + ".meta")]):
                _, interpreted, _ = measure_run([self.compiler(), "run", str(check)])
                measure_run([self.compiler(), "build", "-shared", str(module.relative_to(ROOT)), "-o", str(library)])
                env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK="1", LYMAR_TRACE_PRECOMPILED="1")
                _, native, trace = measure_run([self.compiler(), "run", str(check)], env)
                self.assertEqual(native, interpreted)
                for function in ("mutate", "make_box", "pair", "greet", "outcome", "closure_sum", "make_adder", "make_adder.__lambda_0", "cycle"):
                    self.assertIn(f"PRECOMPILED_CALL: build.{name}.{name}.{function}", trace)

    def test_full_font_module_metrics_and_rendering_match_interpretation(self):
        try:
            font = resolve_font()
        except RuntimeError as error:
            self.skipTest(str(error))
        source = '''import std.font as font;
match (font.load_font(FONT_PATH)) {
    val f => {
        assert(f.is_valid);
        var gid = f.get_glyph_index(65);
        assert(gid > 0);
        var metrics = f.get_metrics(16.0);
        var typo = f.get_typo_metrics(16.0);
        var glyph = f.get_glyph_metrics(gid, 16.0);
        print("METRICS: {metrics.ascent},{metrics.descent},{metrics.line_gap},{metrics.line_height},{metrics.units_per_em}");
        print("TYPO: {typo.ascent},{typo.descent},{typo.line_height}");
        print("GLYPH: {gid},{glyph.advance_width},{glyph.left_side_bearing},{glyph.width},{glyph.height}");
        assert(f.text_width("", 16.0) == 0.0);
        print("TEXT: {f.text_width(\"AVAV Hello\", 16.0)},{f.text_width(\"AVAV Hello\", 32.0)},{f.text_height(\"AV\", 16.0)}");
        print("KERN: {f.get_kern_advance(gid, f.get_glyph_index(86), 16.0)},{f.get_kern_advance_codepoint(65,86,16.0)}");
        var normal = f.render_glyph(gid, 16.0);
        var subpixel = f.render_glyph_subpixel(gid, 16.0, 2, 2, 0.5, 0.0);
        var sdf = f.render_glyph_sdf(gid, 16.0, 2, 128.0, 1.0);
        assert(normal.width > 0 and normal.height > 0 and len(normal.pixels) > 0);
        assert(subpixel.width > 0 and subpixel.height > 0 and len(subpixel.pixels) > 0);
        assert(sdf.width > 0 and sdf.height > 0 and len(sdf.pixels) > 0);
        var sum_normal = 0;
        for (var i = 0; i < len(normal.pixels); i = i + 1) { sum_normal = sum_normal + normal.pixels[i]; }
        var sum_subpixel = 0;
        for (var i = 0; i < len(subpixel.pixels); i = i + 1) { sum_subpixel = sum_subpixel + subpixel.pixels[i]; }
        var sum_sdf = 0;
        for (var i = 0; i < len(sdf.pixels); i = i + 1) { sum_sdf = sum_sdf + sdf.pixels[i]; }
        print("RENDER: {normal.width},{normal.height},{normal.x_offset},{normal.y_offset},{sum_normal}");
        print("SUBPIXEL: {subpixel.width},{subpixel.height},{sum_subpixel}");
        print("SDF: {sdf.width},{sdf.height},{sum_sdf}");
        print("COUNT: {font.get_num_fonts(f.path)},{font.get_num_fonts_from_bytes(f.reader.data)}");
        match (font.load_font_from_bytes(f.reader.data, "memory.ttf")) {
            val copied => { assert(copied.is_valid); assert(copied.text_width("AV",16.0) == f.text_width("AV",16.0)); },
            err e => { assert(false, "Native in-memory loading failed"); }
        }
    },
    err e => { assert(false, "Font test did not load a font"); }
}
match (font.load_font("__missing_native_font__.ttf")) {
    val f => { assert(false, "Missing font loaded successfully"); },
    err e => { print("MISSING_FONT_OK"); }
}
print("FONT_NATIVE_OK");
'''
        literal = str(font).replace("\\", "\\\\").replace('"', '\\"')
        with tempfile.TemporaryDirectory(dir=ROOT / "build", prefix="font_check_") as tmp:
            path = Path(tmp) / "check.lm"
            path.write_text(source.replace("FONT_PATH", '"' + literal + '"'))
            artifacts = [ROOT / "bin" / ("libfont" + ext + suffix)
                         for ext in (".so", ".dll", ".dylib", ".a", ".lib") for suffix in ("", ".meta")]
            with preserve_artifacts(artifacts):
                _, interpreted, _ = measure_run([self.compiler(), "run", str(path)])
                library = ROOT / "bin" / "libfont.so"
                measure_run([self.compiler(), "build", "-shared", "std/font/index.lm", "-o", str(library)], timeout=600)
                env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK="1", LYMAR_TRACE_PRECOMPILED="1")
                _, native, trace = measure_run([self.compiler(), "run", str(path)], env)
                self.assertEqual(native, interpreted)
                self.assertIn("FONT_NATIVE_OK", native)
                for method in ("get_metrics", "get_typo_metrics", "get_glyph_metrics", "render_glyph", "render_glyph_subpixel", "render_glyph_sdf", "text_width"):
                    self.assertIn("PRECOMPILED_CALL: std.font.Font." + method, trace)
                for function in ("load_font_from_bytes", "get_num_fonts", "get_num_fonts_from_bytes"):
                    self.assertIn("PRECOMPILED_CALL: std.font." + function, trace)

    @staticmethod
    def compiler():
        return str(ROOT / "bin" / ("lymar.exe" if os.name == "nt" else "lymar"))


if __name__ == "__main__":
    (ROOT / "build").mkdir(exist_ok=True)
    unittest.main()
