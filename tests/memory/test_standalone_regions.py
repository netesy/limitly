"""Execute genuine Fyra machine code and compare region behavior with the VM."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
COMPILER = Path(os.environ.get("LYMAR_EXECUTABLE", ROOT / "bin/lymar")).resolve()

GRAPH_SOURCE = r'''
frame Box {
    pub var items: [int];
    pub init(items: [int]) { self.items = items; }
    pub deinit() { assert(self.items[0] == 42); print("FINALIZED"); }
}
fn make_box(): Box { return Box([42, 43]); }
var escaped = make_box();

fn temporary_box() { var temporary = Box([42]); }
temporary_box();

{ var alias = escaped; assert(alias.items[1] == 43); }

var nested = [] as [[int]];
{ var inner = [42, 43]; nested.append(inner); }
assert(nested[0][1] == 43, "Container store must promote the entire child graph");
fn grow(): [int] {
    var values = [] as [int];
    for (var n = 0; n < 200; n = n + 1) { values.append(n); }
    return values;
}
var grown = grow();
fn use_maker(make: fn(): [int]): [int] { return make(); }
var indirectly_returned = use_maker(grow);
assert(indirectly_returned[199] == 199, "Indirect call must propagate pointer return ownership");
fn text(): str { return "hello" + " world"; }
var escaped_text = text();
assert(escaped_text == "hello world", "String allocation must survive return");
assert(len(grown) == 200 and grown[199] == 199, "Resized payload must survive return");
frame Node {
    pub var next: any;
    pub init() { self.next = nil; }
}
fn make_cycle(): Node {
    var a = Node(); var b = Node();
    a.next = b; b.next = a;
    return a;
}
var cycle = make_cycle();
assert(cycle.next != nil, "Cyclic graph must survive promotion");
fn mixed(a: float, b: int, c: float, d: int, e: int, f: int, g: int, h: int, i: int): float {
    return a + c + (b + d + e + f + g + h + i) as float;
}
assert(mixed(1.5, 1, 2.5, 2, 3, 4, 5, 6, 7) == 32.0, "Mixed register/stack argument ABI");
print("Standalone graph/finalizer/resize/ABI regression passed");
'''

class StandaloneRegionTests(unittest.TestCase):
    def run_command(self, arguments):
        result = subprocess.run(arguments, cwd=ROOT, text=True, capture_output=True, timeout=120)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertNotIn("Sanitizer", result.stderr)
        return result.stdout

    def test_region_lifetimes_match_vm_at_all_optimization_levels(self):
        with tempfile.TemporaryDirectory(prefix="lymar-aot-regions-") as tmp:
            directory = Path(tmp)
            graph = directory / "graphs.lm"
            graph.write_text(GRAPH_SOURCE)
            for source in (ROOT / "tests/memory/region_lifetime_regression.lm", graph):
                expected = self.run_command([str(COMPILER), "run", str(source)])
                self.assertIn("regression passed", expected)
                if source == graph:
                    self.assertEqual(expected.splitlines(), ["FINALIZED", "Standalone graph/finalizer/resize/ABI regression passed", "FINALIZED"])
                for level in (0, 1, 2):
                    with self.subTest(source=source.name, optimization=level):
                        executable = directory / f"{source.stem}-o{level}"
                        self.run_command([str(COMPILER), "build", "-O", str(level), str(source), "-o", str(executable)])
                        self.assertEqual(self.run_command([str(executable)]), expected)

    def test_optimized_external_side_effects_and_failures_are_preserved(self):
        with tempfile.TemporaryDirectory(prefix="lymar-aot-assert-") as tmp:
            source, executable = Path(tmp) / "fail.lm", Path(tmp) / "fail"
            source.write_text('frame ExitProbe { pub init() {} pub deinit() { print("FINALIZE_ON_EXIT"); } }\n'
                              'var probe = ExitProbe(); print("BEFORE_FAILURE"); assert(false); print("UNREACHABLE");')
            self.run_command([str(COMPILER), "build", "-O", "2", str(source), "-o", str(executable)])
            result = subprocess.run([str(executable)], text=True, capture_output=True, timeout=30)
            self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
            self.assertIn("BEFORE_FAILURE", result.stdout)
            self.assertIn("Assertion failed", result.stdout)
            self.assertIn("FINALIZE_ON_EXIT", result.stdout)
            self.assertNotIn("UNREACHABLE", result.stdout)

if __name__ == "__main__":
    unittest.main()
