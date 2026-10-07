"""Measure validated VM workloads without changing LIR or enabling native modules."""
import argparse
import json
import os
from pathlib import Path
import statistics
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'precompiled'))
from run_benchmark import ROOT, measure_run, preserve_artifacts

WORKLOADS = {
    'queue_drain': ('''import std.collections.queue as queues;
var queue = queues.Queue();
for (var i = 0; i < 800; i = i + 1) { queue.enqueue(i); }
var total = 0;
for (var i = 0; i < 800; i = i + 1) { total += queue.dequeue() as int; }
assert(total == 319600 and queue.is_empty());
''', 319600),
    'string_builder': ('''import std.string.builder as builders;
var builder = builders.builder();
for (var i = 0; i < 2000; i = i + 1) { builder.append("01234567890123456789012345678901"); }
var total = 0;
for (var i = 0; i < 3; i = i + 1) { total += len(builder.to_string()); }
assert(total == 192000);
''', 192000),
    'string_join': ('''import std.string.join as joining;
var parts: [str] = [];
for (var i = 0; i < 1500; i = i + 1) { parts[i] = "01234567890123456789012345678901"; }
var total = 0;
for (var i = 0; i < 3; i = i + 1) { total += len(joining.join(parts, ",")); }
assert(total == 148497);
''', 148497),
    'string_search': (('var text = "' + 'abc ' * 16384 + '";\n') + '''
var total = 0;
for (var i = 0; i < 1000; i = i + 1) {
    if (_builtin_string_contains(text, "not-here")) { total += 1; }
}
assert(total == 0);
''', 0),
    'list_length': ('''var items: [int] = [];
for (var i = 0; i < 2000; i = i + 1) { items[i] = i; }
var total = 0;
for (var i = 0; i < 2000; i = i + 1) { total += len(items); }
assert(total == 4000000);
''', 4000000),
    'dict_length': ('''var items: {int: int} = {0: 0};
for (var i = 0; i < 1000; i = i + 1) { items[i] = i; }
var total = 0;
for (var i = 0; i < 2000; i = i + 1) { total += len(items); }
assert(total == 2000000);
''', 2000000),
    'function_calls': ('''fn increment(value: int): int { return value + 1; }
var total = 0;
for (var i = 0; i < 30000; i = i + 1) { total = increment(total); }
assert(total == 30000);
''', 30000),
    'collection_vector': ('''import std.collections as collections;
var vector = collections.Vector();
for (var i = 0; i < 1500; i = i + 1) { vector.push(i); }
var total = 0;
for (var i = 0; i < 1500; i = i + 1) { total += vector.get(i) as int; }
assert(total == 1124250);
''', 1124250),
    'string_methods': ('''import std.string as strings;
var text = strings.String("Hello UTF-8: café 世界");
var total = 0;
for (var i = 0; i < 10000; i = i + 1) {
    total += text.length();
    assert(text.contains("café"));
}
assert(total == 250000);
''', 250000),
}


source, expected = WORKLOADS['collection_vector']
WORKLOADS['collection_vector_direct'] = (
    source.replace('import std.collections as collections;',
                   'import std.collections.vector as collections;'), expected)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--runs', type=int, default=3)
    parser.add_argument('--output', type=Path)
    parser.add_argument('--workload', action='append', choices=tuple(WORKLOADS))
    args = parser.parse_args()
    if args.runs < 1:
        parser.error('--runs must be positive')
    compiler = ROOT / 'bin' / ('lymar.exe' if sys.platform == 'win32' else 'lymar')
    artifacts = [ROOT / 'bin' / ('libcollections' + ext + suffix)
                 for ext in ('.so', '.dll', '.dylib') for suffix in ('', '.meta')]
    results = {}
    env = dict(os.environ, LYMAR_TRACE_PRECOMPILED="1", LYMAR_HOME=str(ROOT))
    with preserve_artifacts(artifacts), tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='vm-benchmark-') as temp:
        for name in (args.workload or WORKLOADS):
            source, expected = WORKLOADS[name]
            path = Path(temp) / (name + '.lm')
            path.write_text(source + f'print("VM_DONE: {expected}", total);\n')
            times = []
            for _ in range(args.runs):
                elapsed, out, err = measure_run([str(compiler), 'run', str(path)], env)
                if out.strip() != f'VM_DONE: {expected} {expected}' or 'PRECOMPILED_CALL:' in err:
                    raise RuntimeError(f'{name}: unexpected result or native dispatch: {out}\n{err}')
                times.append(elapsed)
            results[name] = {'median_ms': statistics.median(times), 'runs_ms': times, 'result': expected}
            print(f'{name:<20} {results[name]["median_ms"]:9.2f} ms', flush=True)
    if args.output:
        args.output.write_text(json.dumps(results, indent=2) + '\n')
    print('Process timings include parsing, module loading, and execution. Collections run interpreted.')


if __name__ == '__main__':
    main()
