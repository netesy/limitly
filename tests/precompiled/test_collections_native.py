"""Check native collection exports, facade discovery, and shared font objects."""
import os
from pathlib import Path
import tempfile
import unittest

from run_benchmark import ROOT, measure_run, preserve_artifacts, resolve_font
from test_benchmark import BenchmarkValidationTests


class NativeCollectionsTests(unittest.TestCase):
    def test_precompiled_collections_share_font_objects(self):
        font = resolve_font()
        literal = str(font).replace('\\', '\\\\').replace('"', '\\"')
        source = '''import std.collections as collections;
import std.collections.vector as vector_module;
import std.font as font;
var vector = collections.Vector();
vector.push(1);
vector.push(2);
vector.insert(1, 9);
assert(vector.len() == 3 and vector.get(1) == 9);
assert(vector.remove(1) == 9);
var sequence = vector.iterator();
assert(sequence.next() == 1 and sequence.next() == 2);
var list = collections.List();
list.append("hello");
assert(list.set(0, "world"));
assert(list.get(0) == "world");
var queue = collections.Queue();
queue.enqueue(11);
queue.enqueue(22);
assert(queue.dequeue() == 11 and queue.peek() == 22);
var stack = collections.Stack();
stack.push(10);
stack.push(20);
assert(stack.pop() == 20 and stack.peek() == 10);
var map = collections.HashMap();
map.put("answer", 42);
match (map.get("answer")) {
    val answer => { assert(answer == 42); },
    err e => { assert(false, "Native collection lost its value"); }
}
var bits = collections.BitSet(130);
bits.set(64);
assert(bits.contains(64));
bits.unset(64);
assert(not bits.contains(64));
fn compare_numbers(left: any, right: any): int {
    return (right as int) - (left as int);
}
var priority = collections.PriorityQueue(fn(left: any, right: any): int {
    return (right as int) - (left as int);
});
priority.push(5);
priority.push(1);
priority.push(3);
assert(priority.pop() == 5 and priority.pop() == 3 and priority.pop() == 1);
match (font.load_font(FONT_PATH)) {
    val f => {
        var fonts = vector_module.Vector();
        fonts.push(f);
        var shared = fonts.get(0) as font.Font;
        assert(shared.is_valid);
        assert(shared.text_width("AV", 16.0) == f.text_width("AV", 16.0));
        shared.path = "shared-native-font";
        assert(f.path == "shared-native-font");
        print("WIDTH: {shared.text_width(\"AV\", 16.0)}");
    },
    err e => { assert(false, "Native font did not load"); }
}
print("COLLECTIONS_AND_FONT_OK");
'''
        artifacts = [ROOT / 'bin' / ("lib" + name + ext + suffix)
                     for name in ('collections', 'font')
                     for ext in ('.so', '.dll', '.dylib', '.a', '.lib') for suffix in ('', '.meta')]
        compiler = BenchmarkValidationTests.compiler()
        with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='collections_native_') as tmp:
            path = Path(tmp) / 'check.lm'
            path.write_text(source.replace('FONT_PATH', '"' + literal + '"'))
            with preserve_artifacts(artifacts):
                _, expected, _ = measure_run([compiler, 'run', str(path)])
                for name in ('collections', 'font'):
                    measure_run([compiler, 'build', '-shared', f'std/{name}/index.lm', '-o',
                                 str(ROOT / 'bin' / f'lib{name}.so')], timeout=600)
                env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK='1', LYMAR_TRACE_PRECOMPILED='1')
                _, native, trace = measure_run([compiler, 'run', str(path)], env)
                self.assertEqual(native, expected)
                for name in ('vector.Vector.push', 'vector.VectorIterator.next', 'list.List.append',
                             'queue.Queue.dequeue', 'stack.Stack.pop', 'hashmap.HashMap.put',
                             'priority_queue.PriorityQueue.push'):
                    self.assertIn('PRECOMPILED_CALL: std.collections.' + name, trace)
                self.assertIn('PRECOMPILED_CALL: std.font.Font.text_width', trace)
                # Importing a leaf directly must also discover the umbrella library.
                path.write_text('import std.collections.vector as v; var value = v.Vector(); '
                                'value.push(42); assert(value.get(0) == 42); print("LEAF_OK");')
                _, leaf, trace = measure_run([compiler, 'run', str(path)], env)
                self.assertIn('LEAF_OK', leaf)
                self.assertIn('PRECOMPILED_CALL: std.collections.vector.Vector.push', trace)


if __name__ == '__main__':
    (ROOT / 'build').mkdir(exist_ok=True)
    unittest.main()
