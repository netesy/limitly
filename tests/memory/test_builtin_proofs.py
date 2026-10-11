"""Source execution and emitted-code proofs; no handcrafted-only acceptance."""
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest
import sys
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tests/precompiled'))
from run_benchmark import preserve_artifacts

COMPILER = os.environ.get('LYMAR_EXECUTABLE', str(ROOT / 'bin/lymar'))
SOURCE = r'''
fn byte(s: any, index: any): int { return _builtin_string_byte_at(s, index); }
assert(byte("A", 0) == 65);
assert(byte("A", -1) == 0);
assert(byte("A", 1) == 0);
assert(byte("A", 1073741824) == 0);
assert(byte("", 0) == 0);
assert(byte(nil, 0) == 0);
assert(byte(8, 0) == 0);
assert(byte(true, 0) == 0);
assert(byte([65], 0) == 0);
assert(byte(2.5, 0) == 0);
assert(byte("ABC", 1.75) == 66);
assert(byte("ABC", "1") == 65);
assert(byte("ABC", true) == 65);
assert(byte("ABC", nil) == 65);
assert(byte("ABC", 1e100) == 65);
var huge=1e100;
assert((huge as int)==0); assert(((huge as any) as int)==0);
assert(byte("é", 0) == 195 and byte("é", 1) == 169);
assert(byte("A\0B", 1) == 0 and byte("A\0B", 2) == 66);
assert(_builtin_substring("ABC", -1, 2) == "");
assert(_builtin_substring("ABC", 1, -1) == "");
assert(_builtin_substring("ABC", 2, 1) == "");
assert(_builtin_substring("ABC", 1, 1073741824) == "BC");
assert(_builtin_substring("ABC", 1073741824, 1073741825) == "");
assert(_builtin_substring("A\0B", 1, 3) == "\0B");
assert(_builtin_substring("ABC", "1", 1.75) == "A");
fn invoke(action:any):any { return action(0); }
assert(invoke(nil)==nil); assert(invoke(8)==nil); assert(invoke(2.5)==nil);
assert(invoke((200000,2))==nil); assert(invoke("not_a_function")==nil);
assert(invoke("lymar_aot_alloc")==nil);
fn tuple_at(index:int):any { var pair=(1,2); return pair[index]; }
assert(tuple_at(0)==1); assert(tuple_at(-1)==nil); assert(tuple_at(2)==nil);
assert(tuple_at(1073741824)==nil);
fn decimal_return():float { return 2.5; }
var decimal_alias=decimal_return;
assert(decimal_alias()==2.5);
print("BUILTIN_BOUNDS_OK");
'''
MODULE = r'''
frame Pair { pub var a:int; pub var b:int; pub init(){self.a=3;self.b=4;} }
frame Holder { pub var item:Pair?; pub init(){self.item=nil;} }
frame PairSource { pub var item:Pair; pub init(){self.item=Pair();} pub fn get():Pair{return self.item;} }
fn retain(holder:Holder, value:Pair) { holder.item=value; }
pub fn published_reads():int { var p=Pair(); var holder=Holder(); retain(holder,p); var z=p.b; return z+p.b; }
pub fn fresh_reads():int { var p=Pair(); var z=p.b; return z+p.b; }
fn change(p:Pair) { p.b=9; }
pub fn mutation_barrier():int { var p=Pair(); var z=p.b; change(p); return z+p.b; }
pub fn borrowed(p:Pair):int { var z=p.b; return z+p.b; }
pub fn borrowed_mutation(p:Pair):int { var z=p.b; change(p); return z+p.b; }
pub fn resolved_reads(source:PairSource):int {var p=source.get();var z=p.b;return z+p.a;}
pub fn resolved_mutation(source:PairSource):int {var p=source.get();var z=p.b;p.b=9;return z+p.b;}
pub fn branch_reads(p:Pair, flag:bool):int {var z=p.b;if(flag){z=z+1;}return z+p.b;}
pub fn ignored(argument:any):int { return 2; }
pub fn byte(text:any,index:any):int { return _builtin_string_byte_at(text,index); }
pub fn same_slice(text:any, start:any, end:any, needle:any):bool {
    return _builtin_substring(text,start,end)==needle;
}
pub fn different_slice(text:str, start:int, end:int, needle:str):bool {
    return _builtin_substring(text,start,end)!=needle;
}
pub fn escaped_slice(text:str,start:int,end:int):str { return _builtin_substring(text,start,end); }
'''

class BuiltinProofTests(unittest.TestCase):
    def command(self, args, env=None):
        result = subprocess.run(args, cwd=ROOT, env=env, text=True, capture_output=True, timeout=60)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertNotIn('Error:', result.stderr)
        return result.stdout, result.stderr

    def test_bounds_source_vm_and_standalone(self):
        with tempfile.TemporaryDirectory(prefix='lymar-builtin-bounds-') as temporary:
            directory = Path(temporary); source = directory / 'bounds.lm'; source.write_text(SOURCE)
            for level in (0, 1, 2):
                with self.subTest(level=level):
                    output, _ = self.command([COMPILER, 'run', '-O', str(level), str(source)])
                    self.assertEqual(output, 'BUILTIN_BOUNDS_OK\n')
                    binary = directory / ('bounds' + ('.exe' if os.name == 'nt' else ''))
                    env = dict(os.environ, LYMAR_AOT_LINKER='driver', LYMAR_AOT_CXX=str(ROOT / 'tests/memory/aot_linker.py'))
                    self.command([COMPILER, 'build', '-O', str(level), str(source), '-o', str(binary)], env)
                    output, _ = self.command([str(binary)])
                    self.assertEqual(output, 'BUILTIN_BOUNDS_OK\n')

    def test_hosted_proofs_and_conservative_barriers(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='memory_proof_') as temporary:
            directory = Path(temporary); name = directory.name
            module = directory / (name + '.lm'); module.write_text(MODULE)
            check = directory / 'check.lm'
            check.write_text(f'''import build.{name}.{name} as p;
assert(p.fresh_reads()==8); assert(p.mutation_barrier()==13);
assert(p.published_reads()==8);
assert(p.borrowed(p.Pair())==8); assert(p.borrowed_mutation(p.Pair())==13); assert(p.ignored([1,2])==2);
assert(p.resolved_reads(p.PairSource())==7);assert(p.resolved_mutation(p.PairSource())==13);
assert(p.branch_reads(p.Pair(),true)==9);
assert(p.byte("A",1073741824)==0); assert(p.byte("A",-1)==0);
assert(p.byte(8,0)==0); assert(p.byte(nil,0)==0); assert(p.byte([65],0)==0);
assert(p.byte("ABC",1.75)==66); assert(p.byte("ABC","1")==65); assert(p.byte("ABC",1e100)==65);
assert(p.same_slice("ABC",1,1073741824,"BC"));
assert(p.same_slice("ABC",-1,2,""));
assert(p.same_slice("ABC","1",1.75,"A"));
assert(p.same_slice("A\\0B",1,3,"\\0B"));
assert(p.same_slice(nil,0,2,""));
assert(not p.same_slice("ABC",0,1,nil));
assert(p.different_slice("ABC",0,1,"B"));
assert(p.escaped_slice("ABC",1,1073741824)=="BC");
print("HOSTED_PROOFS_OK");''')
            extension = '.dll' if os.name == 'nt' else ('.dylib' if sys.platform == 'darwin' else '.so')
            library = ROOT / 'bin' / ('lib' + name + extension)
            with preserve_artifacts([library, Path(str(library)+'.meta')]):
                expected, _ = self.command([COMPILER,'run',str(check)])
                self.assertEqual(expected,'HOSTED_PROOFS_OK\n')
                for level in (0,1,2):
                    env = dict(os.environ, LYMAR_KEEP_NATIVE_SOURCE='1')
                    self.command([COMPILER,'build','-shared','-O',str(level),str(module.relative_to(ROOT)),'-o',str(library)],env)
                    generated = list(library.parent.glob(library.name+'.lymar-*.cpp'))
                    self.assertEqual(len(generated),1)
                    try:
                        text = generated[0].read_text()
                        def body(function):
                            return text.split('// build.'+name+'.'+name+'.'+function+'\n',1)[1].split('\n// ',1)[0]
                        self.assertRegex(body('fresh_reads'), r'=scope.track\(frame_view_\d+\[1\]\)')
                        self.assertRegex(body('borrowed'), r'=scope.track\(frame_view_')
                        self.assertNotRegex(body('borrowed_mutation'), r'=scope.track\(frame_view_')
                        self.assertRegex(body('resolved_reads'), r'=scope.track\(frame_view_')
                        self.assertNotRegex(body('resolved_mutation'), r'=scope.track\(frame_view_')
                        self.assertNotRegex(body('branch_reads'), r'=scope.track\(frame_view_')
                        self.assertNotRegex(body('mutation_barrier'), r'=scope.track\(frame_view_')
                        self.assertNotRegex(body('published_reads'), r'=scope.track\(frame_view_')
                        self.assertIn('substring_equal(api,ctx,',body('same_slice'))
                        self.assertNotIn('substring_equal(api,ctx,',body('escaped_slice'))
                        if level:
                            self.assertIn('NativeScope scope(api,ctx,false)',body('ignored'))
                        output, trace = self.command([COMPILER,'run',str(check)],dict(os.environ,LYMAR_DISABLE_INTERPRETER_FALLBACK='1',LYMAR_TRACE_PRECOMPILED='1'))
                        self.assertEqual(output,expected)
                        self.assertIn('.fresh_reads',trace)
                        self.assertIn('.same_slice',trace)
                    finally:
                        for path in generated: path.unlink()

if __name__ == '__main__': unittest.main()
