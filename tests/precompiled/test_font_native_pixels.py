"""Require native rendering, including exact pixel buffers rather than widths alone."""
import os
from pathlib import Path
import tempfile
import unittest

from run_benchmark import ROOT, measure_run, preserve_artifacts, resolve_font
import test_benchmark


class NativeFontPixelTests(unittest.TestCase):
    def test_printable_glyph_buffers_match_source(self):
        font = str(resolve_font()).replace('\\', '\\\\').replace('"', '\\"')
        source = '''import std.font as font;
match (font.load_font(FONT_PATH)) {
    val loaded => {
        var sizes = [16.0, 32.0];
        for (var code = 32; code < 127; code = code + 1) {
            iter (size in sizes) {
                var glyph = loaded.get_glyph_index(code);
                var bitmap = loaded.render_glyph(glyph, size);
                print("GLYPH: {code} {size} {bitmap.width} {bitmap.height} {bitmap.x_offset} {bitmap.y_offset}");
                print("PIXELS: {bitmap.pixels}");
            }
        }
        print("WIDTH: {loaded.text_width(\"The quick brown fox jumps over the lazy dog 1234567890\", 16.0)}");
    },
    err e => { assert(false, "Font load failed"); }
}
'''.replace('FONT_PATH', '"' + font + '"')
        artifacts = [ROOT / 'bin' / ('libfont' + ext + suffix)
                     for ext in ('.so', '.dll', '.dylib', '.a', '.lib') for suffix in ('', '.meta')]
        compiler = test_benchmark.BenchmarkValidationTests.compiler()
        extension = '.dll' if os.name == 'nt' else ('.dylib' if os.sys.platform == 'darwin' else '.so')
        with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='font_pixels_') as tmp:
            check = Path(tmp) / 'check.lm'
            check.write_text(source)
            with preserve_artifacts(artifacts):
                _, expected, _ = measure_run([compiler, 'run', str(check)])
                self.assertEqual(expected.count('PIXELS:'), 190)
                measure_run([compiler, 'build', '-O2', '-shared', 'std/font/index.lm',
                             '-o', str(ROOT / 'bin' / ('libfont' + extension))], timeout=600)
                env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK='1', LYMAR_TRACE_PRECOMPILED='1')
                _, actual, trace = measure_run([compiler, 'run', str(check)], env)
                self.assertEqual(actual, expected)
                self.assertEqual(trace.count('PRECOMPILED_CALL: std.font.Font.render_glyph\n'), 190)
                self.assertIn('PRECOMPILED_CALL: std.font.Font.text_width', trace)


if __name__ == '__main__':
    unittest.main()
