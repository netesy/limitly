"""Semantic regressions for VM length queries and reusable call frames."""
from pathlib import Path
import sys
import os
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'precompiled'))
from run_benchmark import ROOT, measure_run, preserve_artifacts


class VMOptimizationTests(unittest.TestCase):
    def run_source(self, source):
        compiler = ROOT / 'bin' / ('lymar.exe' if sys.platform == 'win32' else 'lymar')
        with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='vm-test-') as temp:
            path = Path(temp) / 'probe.lm'
            path.write_text(source + '\nprint("VM_OK");\n')
            artifacts = [ROOT / 'bin' / ('libcollections' + ext + suffix)
                         for ext in ('.so', '.dll', '.dylib') for suffix in ('', '.meta')]
            with preserve_artifacts(artifacts):
                _, output, _ = measure_run([str(compiler), 'run', str(path)],
                    dict(os.environ, LYMAR_HOME=str(ROOT), LYMAR_TRACE_PRECOMPILED="1"))
            self.assertEqual(output.strip(), 'VM_OK')

    def test_queue_replacement_preserves_list_aliases_and_object_identity(self):
        self.run_source('''
import std.collections.queue as queues;
frame Box { pub value: int; pub init(value: int) { self.value = value; } }
var queue = queues.Queue();
var first = Box(1);
var second = Box(2);
queue.enqueue(first);
queue.enqueue(second);
var snapshot = queue.items;
assert((queue.dequeue() as Box).value == 1);
assert(len(snapshot) == 2 and len(queue.items) == 1);
var remaining = queue.peek() as Box;
remaining.value = 9;
assert(second.value == 9 and (snapshot[1] as Box).value == 9);
assert((queue.dequeue() as Box).value == 9);
assert(queue.dequeue() == nil);
assert(len(snapshot) == 2);
''')

    def test_join_and_builder_keep_unicode_empty_parts_and_public_mutations(self):
        self.run_source('''
import std.string.builder as builders;
import std.string.join as joining;
assert(joining.join([] as [str], ",") == "");
assert(joining.join(["é", "", "世界"], ":") == "é::世界");
var embedded = _builtin_string_from_bytes([65, 0, 66]);
var joined = joining.join([embedded, "C"], ":");
assert(len(joined) == 5 and _builtin_string_byte_at(joined, 1) == 0);
var builder = builders.builder();
builder.append("é");
builder.append("");
builder.append_line("世界");
assert(builder.to_string() == "é世界\\n");
assert(builder.length() == 9);
builder.parts[0] = "Hello";
assert(builder.to_string() == "Hello世界\\n");
assert(builder.to_string() == "Hello世界\\n");
builder.clear();
assert(builder.to_string() == "" and builder.length() == 0);
''')

    @unittest.skipUnless(sys.platform == 'linux', 'Native shared module test requires Linux')
    def test_native_join_and_builder_use_existing_abi(self):
        compiler = str(ROOT / 'bin' / 'lymar')
        artifacts = [ROOT / 'bin' / ('lib' + name + '.so' + suffix)
                     for name in ('builder', 'join') for suffix in ('', '.meta')]
        with preserve_artifacts(artifacts), tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='native-join-') as temp:
            source = Path(temp) / 'probe.lm'
            source.write_text('''
import std.string.builder as builders;
import std.string.join as joining;
var builder = builders.builder();
builder.append("é");
builder.append("世界");
assert(builder.to_string() == "é世界");
assert(joining.join(["é", "", "世界"], ":") == "é::世界");
var embedded = _builtin_string_from_bytes([65, 0, 66]);
var joined = joining.join([embedded, "C"], ":");
assert(len(joined) == 5 and _builtin_string_byte_at(joined, 1) == 0);
print("NATIVE_JOIN_OK");
''')
            for name in ('builder', 'join'):
                measure_run([compiler, 'build', '-shared', 'std/string/' + name + '.lm',
                             '-o', str(ROOT / 'bin' / ('lib' + name + '.so'))])
            _, output, trace = measure_run([compiler, 'run', str(source)],
                dict(os.environ, LYMAR_HOME=str(ROOT), LYMAR_DISABLE_INTERPRETER_FALLBACK="1", LYMAR_TRACE_PRECOMPILED="1"))
            self.assertEqual(output.strip(), 'NATIVE_JOIN_OK')
            self.assertIn('PRECOMPILED_CALL: std.string.builder.StringBuilder.to_string', trace)
            self.assertIn('PRECOMPILED_CALL: std.string.join.join', trace)

    def test_lengths_preserve_runtime_values(self):
        self.run_source('''
assert(len("café 世界") == 12);
assert(len("") == 0);
assert(len(nil) == 0);
var values: [any] = [];
values[0] = values;
assert(len(values) == 1);
values[1] = "hello";
assert(len(values) == 2 and values[1] == "hello");
var mapping: {str: any} = {"self": nil};
mapping["self"] = mapping;
assert(len(mapping) == 1);
mapping["second"] = values;
assert(len(mapping) == 2);
''')

    def test_string_search_keeps_byte_offsets_and_empty_needle_behavior(self):
        self.run_source('''
assert(_builtin_string_index_of("café 世界", "世") == 6);
assert(_builtin_string_index_of("aaaaab", "aab") == 3);
assert(_builtin_string_index_of("abc", "") == -1);
assert(_builtin_string_index_of("abc", "abcd") == -1);
assert(not _builtin_string_contains("abc", ""));
assert(_builtin_string_contains("café 世界", "世界"));
''')

    def test_calls_preserve_live_values_recursion_and_captures(self):
        self.run_source('''
fn factorial(n: int): int {
    if (n <= 1) { return 1; }
    return n * factorial(n - 1);
}
fn make_adder(base: int): fn(int): int {
    return fn(value: int): int { return base + value; };
}
fn add(a: int, b: int = 7): int { return a + b; }
var keep = [11, 22, 33];
var first = make_adder(5);
var second = make_adder(100);
for (var i = 0; i < 100; i = i + 1) {
    assert(factorial(7) == 5040);
    assert(first(i) == i + 5 and second(i) == i + 100);
    assert(add(i) == i + 7);
    assert(keep[0] == 11 and keep[2] == 33);
}
''')


if __name__ == '__main__':
    unittest.main()
