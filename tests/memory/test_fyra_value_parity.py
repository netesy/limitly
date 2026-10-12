"""Execute source regressions through the VM and every supported Fyra level."""
import os
from pathlib import Path
import subprocess
import shlex
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
COMPILER = os.environ.get("LYMAR_EXECUTABLE", str(ROOT / "bin/lymar"))


class FyraValueParityTests(unittest.TestCase):
    def test_source_outputs(self):
        sources = (
            "tests/types/basic.lm",
            "tests/graphics_triangle_test.lm",
            "tests/text_render_test.lm",
            "tests/retained_ui_test.lm",
            "tests/game/test_imgui.lm",
            "tests/basic/literals.lm",
            "tests/expressions/large_literals.lm",
            "tests/stdlib/time_module_test.lm",
            "tests/stdlib/crypto/hash_test.lm",
            "tests/types/advanced.lm",
            "tests/ffi/test_trampoline.lm",
            "tests/ffi/test_hardening.lm",
            "tests/stdlib/regex_module_test.lm",
            "tests/compress/test_compress.lm",
            "tests/regex/test_regex_matches.lm",
            "tests/types/refined_types.lm",
            "tests/types/enums.lm",
            "tests/oop/traits_dynamic.lm",
            "tests/stdlib/core/string_test.lm",
            "tests/stdlib/string_module_test.lm",
            "tests/stdlib/collections/vector_test.lm",
            "tests/stdlib/iterator_module_test.lm",
            "tests/stdlib/algorithm_module_test.lm",
            "tests/stdlib/math_module_test.lm",
            "tests/strings/interpolation.lm",
            "tests/loops/match_advanced.lm",
            "tests/stdlib/collections/priority_queue_test.lm",
        )
        env = dict(os.environ, LYMAR_AOT_LINKER="driver",
                   LYMAR_AOT_CXX=str(ROOT / "tests/memory/aot_linker.py"))
        with tempfile.TemporaryDirectory(prefix="lymar-value-parity-") as directory:
            probe = Path(directory) / "parameter_assignments.lm"
            probe.write_text("""
fn steps(n:int):int {
    var result=0;
    while(n>0) { n=n-1;result=result+1;if(result==5) {break;} }
    return result;
}
fn branch(value:int, yes:bool):int {if(yes) {value=7;}return value;}
frame Defaults {pub var unset:any;pub var unset_flag:bool;pub init() {}}
var defaults=Defaults();assert(defaults.unset==nil);assert(len(defaults.unset)==0);
assert(defaults.unset_flag==nil);
var nullable:any=nil;assert(len(nullable)==0);
var flags={"enabled":true,"disabled":false} as {str:bool};
assert(flags["absent"]==nil);
var missing_flag=flags["absent"];assert(missing_flag==nil);
assert(flags["enabled"]==true);assert(flags["disabled"]==false);
fn default_flag(flags:{str:bool},key:str,fallback:bool):bool {
    if(flags[key]!=nil) {return flags[key];}
    return fallback;
}
assert(default_flag(flags,"absent",true)==true);
assert(default_flag(flags,"absent",false)==false);
assert(default_flag(flags,"disabled",true)==false);
assert(steps(3)==3);assert(steps(0)==0);
assert(branch(2,true)==7);assert(branch(2,false)==2);
print("PARAMETER_ASSIGNMENTS_OK");
""")
            representation = Path(directory) / "representation_boundaries.lm"
            long_text = "AbC" * 150
            dictionaries = "\n".join(
                "print({" + ",".join(f'\"k{i}\":{i}' for i in range(count)) + "});"
                for count in (3, 9, 11, 15))
            representation.write_text(
                'import std.string as strings;\n'
                + f'var text="  {long_text}  ";\n'
                + f'assert(len(text)=={len(long_text)+4});\n'
                + f'assert(strings.trim(text)=="{long_text}");\n'
                + f'assert(strings.to_lower(strings.trim(text))=="{long_text.lower()}");\n'
                + f'assert(strings.to_upper(strings.trim(text))=="{long_text.upper()}");\n'
                + 'fn multiply(a:float,b:float):float {return a*b;}\n'
                + 'assert(multiply(3.5,2.0)==7.0);\n'
                + 'var a:any=-2.5;var b:any=3.75;assert(a<b);assert(b>a);assert(a<=a);assert(b>=a);\n'
                + 'print([a,b,true,nil] as [any]);print((a,true,"tuple"));\n'
                + 'print(_builtin_string_from_bytes([65,0,66]));\n'
                + dictionaries + '\nprint("REPRESENTATION_BOUNDARIES_OK");\n')
            hashes = Path(directory) / "hash_resource.lm"
            hashes.write_text("""
import std.internal.runtime as rt;
var h=rt.create(rt.RT_HASH_ENGINE, []);assert(h!=-1);
assert(rt.call(h,rt.OP_OPEN,["sha256"])==true);
assert(rt.call(h,rt.OP_WRITE,["a"])==true);
assert(rt.call(h,rt.OP_WRITE,["bc"])==true);
assert(rt.call(h,rt.OP_READ,[])=="ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
assert(rt.call(h,rt.OP_OPEN,["md5"])==true);
assert(rt.call(h,rt.OP_WRITE,["abc"])==true);
print(rt.call(h,rt.OP_READ,[]));
assert(rt.call(h,rt.OP_OPEN,["invalid"])==false);
rt.destroy(h);print("HASH_RESOURCE_OK");
""")
            pixels = Path(directory) / "graphics_pixels.lm"
            pixels.write_text("""
import std.internal.runtime as rt;
var graphics=rt.create(rt.RT_GRAPHICS,[]);assert(graphics!=-1);
assert(rt.call(graphics,rt.OP_OPEN,[8,8])==true);
assert(rt.call(graphics,rt.OP_FILL,[8,8,0.0,0.0,0.0,1.0])==true);
assert(rt.call(graphics,rt.OP_DRAW_RECT,[2.0,2.0,3.0,2.0,1.0,0.0,0.0,1.0])==true);
assert(rt.call(graphics,rt.OP_READ,[2,2])==4278190335);
assert(rt.call(graphics,rt.OP_READ,[4,3])==4278190335);
assert(rt.call(graphics,rt.OP_READ,[5,3])==255);
assert(rt.call(graphics,rt.OP_PUSH,[3,0,1,8])==true);
assert(rt.call(graphics,rt.OP_DRAW_RECT,[0.0,0.0,8.0,8.0,0.0,1.0,0.0,1.0])==true);
assert(rt.call(graphics,rt.OP_POP,[])==true);
assert(rt.call(graphics,rt.OP_READ,[3,0])==16711935);
assert(rt.call(graphics,rt.OP_READ,[2,0])==255);
assert(rt.call(graphics,rt.OP_END_PASS,[])==true);
var checksum=0;
for(var y=0;y<8;y=y+1) {
    for(var x=0;x<8;x=x+1) {checksum=(checksum+(rt.call(graphics,rt.OP_READ,[x,y]) as int))%1000000007;}
}
print(checksum);rt.destroy(graphics);print("GRAPHICS_PIXELS_OK");
""")
            (Path(directory) / "alpha.lm").write_text('pub var beta_gamma:int=11;pub var shared_context:int=33;')
            (Path(directory) / "alpha_beta.lm").write_text('pub var gamma:int=22;pub var shared_context:int=44;')
            globals_probe = Path(directory) / "global_identities.lm"
            globals_probe.write_text("""
import alpha as first;
import alpha_beta as second;
assert(first.beta_gamma==11);assert(second.gamma==22);
assert(first.shared_context==33);assert(second.shared_context==44);
print("GLOBAL_IDENTITIES_OK");
""")
            extra = [str(pixels), str(globals_probe)]
            if os.name == "posix":
                library_source = Path(directory) / "thread_callback.cpp"
                library_source.write_text("""
#include <thread>
#include <cstdint>
extern "C" int64_t invoke_worker(int64_t (*callback)()) {
    int64_t answer=0;
    std::thread worker([&] {answer=callback();});
    worker.join();return answer;
}
""")
                library = Path(directory) / "thread_callback.so"
                command = shlex.split(os.environ.get("CXX", "g++"))
                command += ["-std=c++17", "-dynamiclib" if sys.platform == "darwin" else "-shared",
                            "-fPIC", "-pthread", str(library_source), "-o", str(library)]
                compiled = subprocess.run(command, cwd=ROOT, env=env, capture_output=True, text=True, timeout=30)
                self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
                threaded = Path(directory) / "thread_callback.lm"
                threaded.write_text("""
import std.ffi as ffi;
pub fn callback_leaf():int {return 42;}
pub fn callback_outer():int {
    unsafe {
        var handle=ffi.callback_create("callback_leaf",[],ffi.TYPE_I64);
        var pointer=ffi.callback_ptr(handle);
        var answer=ffi.call_i64_0(pointer);
        ffi.callback_destroy(handle);return answer;
    }
}
unsafe {
    var library=ffi.library_load("LIBRARY_PATH");
    var invoke=ffi.library_get_symbol(library,"invoke_worker");
    var handle=ffi.callback_create("callback_outer",[],ffi.TYPE_I64);
    var pointer=ffi.callback_ptr(handle);
    var answer=ffi.foreign_call(invoke,[pointer] as [any],ffi.TYPE_I64,[ffi.TYPE_PTR]);
    assert(answer==42);ffi.callback_destroy(handle);ffi.library_unload(library);
    print("THREADED_CALLBACK_OK");
}
""".replace("LIBRARY_PATH", str(library)))
                extra.append(str(threaded))
            for source in (*extra, *sources, str(probe), str(representation), str(hashes)):
                vm = subprocess.run([COMPILER, "run", "-I", directory, source], cwd=ROOT, env=env,
                                    capture_output=True, text=True, timeout=30)
                self.assertEqual(vm.returncode, 0, source + "\n" + vm.stdout + vm.stderr)
                for level in (0, 1, 2):
                    with self.subTest(source=source, level=level):
                        output = str(Path(directory) / ("program.exe" if os.name == "nt" else "program"))
                        build = subprocess.run([COMPILER, "build", "-I", directory, "-O", str(level),
                                                source, "-o", output], cwd=ROOT, env=env,
                                               capture_output=True, text=True, timeout=30)
                        self.assertEqual(build.returncode, 0, build.stdout + build.stderr)
                        native = subprocess.run([output], cwd=ROOT, env=env,
                                                capture_output=True, text=True, timeout=30)
                        self.assertEqual((native.returncode, native.stdout, native.stderr),
                                         (vm.returncode, vm.stdout, vm.stderr))
                        self.assertNotIn("Sanitizer", native.stderr)


if __name__ == "__main__":
    unittest.main()
