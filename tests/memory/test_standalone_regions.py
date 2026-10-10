"""Execute genuine Fyra machine code and compare region behavior with the VM."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
import re
import platform

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
    def test_raw_worker_ownership_from_source(self):
        source = ROOT / "tests/memory/raw_worker_ownership.lm"
        lir = self.run_command([str(COMPILER), "-lir", str(source)])
        for operation in ("MemoryAlloc", "MemoryResize", "MemoryLoad", "MemoryStore"):
            self.assertIn(operation, lir)
        for level in (0, 1, 2):
            self.assertEqual(self.run_command([str(COMPILER), "run", "-O", str(level), str(source)]),
                             "RAW_WORKERS_OK\n")
            with tempfile.TemporaryDirectory(prefix="lymar-raw-workers-") as tmp:
                executable = Path(tmp) / "workers"
                self.run_command([str(COMPILER), "build", "-O", str(level), str(source), "-o", str(executable)])
                self.assertEqual(self.run_command([str(executable)]), "RAW_WORKERS_OK\n")


    def test_scalar_cfg_kinds_and_reassignment(self):
        with tempfile.TemporaryDirectory(prefix="lymar-scalar-kinds-") as tmp:
            directory = Path(tmp)
            source = directory / "scalars.lm"
            source.write_text("fn two():int{return 2;}fn zero():int{return 0;}"
                "fn assign():bool{var answer=true;answer=false;return answer;}"
                "fn looped():bool{var running=true;while(running){running=false;}return running;}"
                "fn cmp():bool{return 4<5;}"
                "print(two());print(zero());print(assign());print(looped());print(cmp());"
                "var erased:any=two();print(erased==nil);var indirect=two;print(indirect());")
            expected = "2\n0\nfalse\nfalse\ntrue\nfalse\n2\n"
            for level in (0, 1, 2):
                self.assertEqual(self.run_command([str(COMPILER), "run", "-O", str(level), str(source)]), expected)
                executable = directory / f"scalars-o{level}"
                self.run_command([str(COMPILER), "build", "-O", str(level), str(source), "-o", str(executable)])
                self.assertEqual(self.run_command([str(executable)]), expected)
                if os.sys.platform == "linux" and platform.machine() == "x86_64":
                    assembly = directory / f"scalars-o{level}.s"
                    self.run_command([str(COMPILER), "build", "-O", str(level), "-S", str(source), "-o", str(assembly)])
                    text = assembly.read_text()
                    for name in ("zero", "assign", "looped", "cmp"):
                        body = re.search(rf"^{name}:\n(.*?)^\.size {name},", text, re.M | re.S)
                        self.assertIsNotNone(body)
                        self.assertNotRegex(body.group(1), r"lymar_aot_(?:region_|call_|arg_|slot_|edge)")

    def test_raw_pointer_bytes_do_not_transfer_managed_ownership(self):
        source_text = r'''import std.ffi as ffi;
frame RawVictim {pub init(){} pub deinit(){print("DROP");}}
unsafe {
    var buffer=ffi.alloc(8);
    var copied=ffi.alloc(8);
    {var victim=RawVictim();var erased:any=victim;ffi.store_ptr(buffer,erased);ffi.memcpy(copied,buffer,8);}
    print("AFTER");ffi.free(buffer);ffi.free(copied);
}'''
        with tempfile.TemporaryDirectory(prefix="lymar-raw-no-ownership-") as tmp:
            directory = Path(tmp)
            source = directory / "raw.lm"
            source.write_text(source_text)
            for level in (0, 1, 2):
                self.assertEqual(self.run_command([str(COMPILER), "run", "-O", str(level), str(source)]), "DROP\nAFTER\n")
                executable = directory / f"raw-o{level}"
                self.run_command([str(COMPILER), "build", "-O", str(level), str(source), "-o", str(executable)])
                self.assertEqual(self.run_command([str(executable)]), "DROP\nAFTER\n")

    def test_raw_element_kinds_from_source(self):
        with tempfile.TemporaryDirectory(prefix="lymar-raw-kinds-") as tmp:
            directory = Path(tmp)
            source = directory / "kinds.lm"
            statements = ["import std.ffi as ffi; unsafe { var pointer=ffi.alloc(32);"]
            for name, value in (("i8", -42), ("u8", 250), ("i16", -12345), ("u16", 60000),
                                ("i32", -123456), ("u32", 3000000000), ("i64", -123456789), ("u64", 123456789)):
                statements.append(f"ffi.store_{name}(pointer,{value});assert(ffi.load_{name}(pointer)=={value});")
            statements.extend([
                "assert(ffi.load_i8(0)==nil);assert(ffi.load_f32(0)==nil);assert(ffi.load_f64(0)==nil);",
                "var text:any=\"3.5\";ffi.store_f64(pointer,text);assert(ffi.load_f64(pointer)==0.0);ffi.store_i32(pointer,text);assert(ffi.load_i32(pointer)==0);",
                "var flag:any=true;ffi.store_u8(pointer,flag);assert(ffi.load_u8(pointer)==0);ffi.store_f32(pointer,flag);assert(ffi.load_f32(pointer)==0.0);",
                "assert(ffi.load_u8(flag)==nil);ffi.store_u8(flag,99);",
                "ffi.memset(flag,99,8);ffi.memcpy(flag,pointer,8);assert(ffi.memcmp(flag,pointer,8)==0);ffi.free(flag);",
                "assert(ffi.alloc(-1)==nil);assert(ffi.realloc(pointer,-1)==nil);var from_null=ffi.realloc(0,16);ffi.store_u8(ffi.ptr_add(from_null,15),42);assert(ffi.load_u8(ffi.ptr_add(from_null,15))==42);ffi.free(from_null);",
                "ffi.free(text);print(text);",
                "var disguised=ffi.alloc(16);ffi.store_i64(disguised,9);ffi.store_f64(ffi.ptr_add(disguised,8),999.0);ffi.store_f64(pointer,disguised);assert(ffi.load_f64(pointer)==0.0);ffi.free(disguised);",
                "var erased:any=3.5;ffi.store_f32(pointer,erased);assert(ffi.load_f32(pointer)==3.5);",
                "ffi.store_f64(pointer,erased);assert(ffi.load_f64(pointer)==3.5);",
                "var copied=ffi.alloc(32);ffi.memset(pointer,17,32);ffi.memcpy(copied,pointer,32);assert(ffi.memcmp(copied,pointer,32)==0);",
                "ffi.store_u8(copied,19);assert(ffi.memcmp(copied,pointer,1)>0);",
                "ffi.memset(pointer,99,-1);assert(ffi.load_u8(pointer)==17);ffi.memcpy(0,pointer,8);assert(ffi.memcmp(0,pointer,8)==0);ffi.free(copied);",
                "var child=ffi.alloc(8);ffi.store_u8(child,42);ffi.store_ptr(pointer,child);",
                "var alias=ffi.load_ptr(pointer);assert(ffi.load_u8(alias)==42);",
                "ffi.free(child);ffi.free(pointer); } print(\"RAW_KINDS_OK\");"])
            source.write_text("\n".join(statements))
            for level in (0, 1, 2):
                self.assertEqual(self.run_command([str(COMPILER), "run", "-O", str(level), str(source)]), "3.5\nRAW_KINDS_OK\n")
                executable = directory / f"kinds-o{level}"
                self.run_command([str(COMPILER), "build", "-O", str(level), str(source), "-o", str(executable)])
                self.assertEqual(self.run_command([str(executable)]), "3.5\nRAW_KINDS_OK\n")

    def test_scalar_leaf_has_no_region_runtime_calls(self):
        with tempfile.TemporaryDirectory(prefix="lymar-scalar-regions-") as tmp:
            directory = Path(tmp)
            source = directory / "scalar.lm"
            source.write_text('fn choose():bool { return false; }\n'
                              'fn yes():bool { return true; }\n'
                              'fn identity(flag:bool):bool { return flag; }\n'
                              'fn dynamic(flag:bool):[int] { var xs=[7]; if(flag){xs.append(9);} return xs; }\n'
                              'var erased:any=[7];print(yes());print(choose());print(dynamic(true));print(identity(erased));\n')
            expected = "true\nfalse\n[7, 9]\n[7]\n"
            for level in (0, 1, 2):
                self.assertEqual(self.run_command([str(COMPILER), "run", "-O", str(level), str(source)]), expected)
                executable = directory / f"scalar-o{level}"
                self.run_command([str(COMPILER), "build", "-O", str(level), str(source), "-o", str(executable)])
                self.assertEqual(self.run_command([str(executable)]), expected)
                if os.sys.platform == "linux" and platform.machine() == "x86_64":
                    assembly = directory / f"scalar-o{level}.s"
                    self.run_command([str(COMPILER), "build", "-O", str(level), "-S", str(source), "-o", str(assembly)])
                    text = assembly.read_text()
                    body = re.search(r"^choose:\n(.*?)^\.size choose,", text, re.M | re.S)
                    self.assertIsNotNone(body)
                    self.assertNotRegex(body.group(1), r"lymar_aot_(?:region_|call_|arg_|slot_|edge)")

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

    def test_branch_return_and_loop_cleanup_from_source(self):
        source_text = r'''
fn select(flag:bool):[int] {
    var outer=[1];
    if(flag) { {var shadow=[2]; return shadow;} }
    else { {var shadow=[3]; return shadow;} }
    return outer;
}
fn loop_value():int {
    var sum=0;
    for(var i=0; i<4; i=i+1) {
        if(i==1) {continue;}
        {var items=[i]; sum=sum+items[0];}
        if(i==2) {break;}
    }
    return sum;
}
var first=select(true); var second=select(false);
print(first[0]); print(second[0]); print(loop_value());
'''
        with tempfile.TemporaryDirectory(prefix="lymar-cfg-memory-") as tmp:
            source = Path(tmp) / "cleanup.lm"
            source.write_text(source_text)
            lir = self.run_command([str(COMPILER), "-lir", str(source)])
            self.assertIn("RegionEnter", lir)
            self.assertIn("RegionExit", lir)
            expected = self.run_command([str(COMPILER), "run", str(source)])
            self.assertEqual(expected.splitlines(), ["2", "3", "2"])
            for level in (0, 1, 2):
                executable = Path(tmp) / f"cleanup-o{level}"
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

    def test_staged_error_payload_survives_return(self):
        with tempfile.TemporaryDirectory(prefix="lymar-aot-param-") as tmp:
            source = Path(tmp) / "errors.lm"
            source.write_text('frame Failure { pub var message: str; }\n'
                              'fn fail(text: str): int?Failure { return err(Failure(text)); }\n'
                              'for (var i=0; i<3; i=i+1) {\n'
                              'match (fail("escaped" + " payload")) {\n'
                              'val value => { assert(false); },\n'
                              'err problem => { var message = problem as str; assert(message == "escaped payload"); print(message); }\n'
                              '} }\n')
            expected = self.run_command([str(COMPILER), "run", str(source)])
            self.assertEqual(expected.splitlines(), ["escaped payload"] * 3)
            for level in (0, 1, 2):
                executable = Path(tmp) / f"errors-o{level}"
                self.run_command([str(COMPILER), "build", "-O", str(level), str(source), "-o", str(executable)])
                self.assertEqual(self.run_command([str(executable)]), expected)

    def test_std_file_open_and_binary_read(self):
        with tempfile.TemporaryDirectory(prefix="lymar-aot-files-") as tmp:
            directory = Path(tmp)
            fixture = directory / "bytes.bin"
            fixture.write_bytes(b"A\0\xffZ")
            source = directory / "files.lm"
            source.write_text('import std.io.file as file;\n'
                              f'match(file.open("{directory.as_posix()}/missing", "r")) {{\n'
                              'val value => { assert(false); }, err problem => { print("MISSING"); } }\n'
                              f'match(file.open("{fixture.as_posix()}", "rb")) {{\n'
                              'val value => { var f = value as file.File;\n'
                              'var bytes = f.read_bytes()?;\n'
                              'assert(len(bytes)==4 and bytes[0]==65 and bytes[1]==0 and bytes[2]==255 and bytes[3]==90);\n'
                              'f.close(); print("BINARY_READ"); }, err problem => { assert(false); } }\n')
            expected = self.run_command([str(COMPILER), "run", str(source)])
            self.assertEqual(expected.splitlines(), ["MISSING", "BINARY_READ"])
            for level in (0, 1, 2):
                executable = directory / f"files-o{level}"
                self.run_command([str(COMPILER), "build", "-O", str(level), str(source), "-o", str(executable)])
                self.assertEqual(self.run_command([str(executable)]), expected)

if __name__ == "__main__":
    unittest.main()
