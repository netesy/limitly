"""Source regressions for callable kinds, atomic lowering and worker captures."""
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tests/precompiled'))
from run_benchmark import preserve_artifacts
COMPILER = os.environ.get('LYMAR_EXECUTABLE', str(ROOT / 'bin/lymar'))
CALLABLES = r'''
fn higher(action:any):int {return action("ABC",2);}
fn returned():any {return _builtin_string_byte_at;}
var byte=_builtin_string_byte_at;
assert(byte("ABC",1)==66);assert(higher(byte)==67);assert(returned()("ABC",0)==65);
var slice:any=_builtin_substring;
assert(slice("ABC",1,3)=="BC");assert(slice("ABC",-1,3)=="");
var output:any=print;output();output("CALLABLE_OK");output(true);output(2.5);
'''
ATOMIC = r'''
frame Counter {pub var value:any;pub init(){self.value=0;}}
var captured=10;
var output=channel();
concurrent(cores=4) {
    task(i in 1..8) {
        var counter=Counter();
        counter.value+=1;counter.value-=1;counter.value+=2;
        assert(counter.value==2);
        counter.value=2.5;counter.value+=0.5;assert(counter.value==3.0);
        counter.value=9223372036854775807;counter.value+=1;
        assert((counter.value as str)=="9223372036854775808");
        counter.value="A";counter.value+="B";assert(counter.value=="AB");
        counter.value=true;counter.value+=1;assert(counter.value==nil);
        counter.value=nil;counter.value-=1;assert(counter.value==nil);
        counter.value=1;counter.value-=2.5;assert(counter.value==-1.5);
        output.send(captured+i);
    }
}
var sum=0;iter(value in output){sum=sum+value;}
assert(sum==116);print("ATOMIC_CAPTURE_OK");
'''
class RemainingBlockerTests(unittest.TestCase):
    def command(self, command, env=None):
        result=subprocess.run(command,cwd=ROOT,env=env,text=True,capture_output=True,timeout=60)
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)
        self.assertNotIn('Error:',result.stderr)
        self.assertNotIn('Sanitizer',result.stderr)
        return result.stdout,result.stderr
    def execute_both(self,source_text,expected,operations=()):
        with tempfile.TemporaryDirectory(prefix='lymar-blockers-') as temporary:
            directory=Path(temporary);source=directory/'probe.lm';source.write_text(source_text)
            lir,_=self.command([COMPILER,'-lir',str(source)])
            for operation in operations:self.assertIn(operation,lir)
            for level in (0,1,2):
                with self.subTest(level=level):
                    output,_=self.command([COMPILER,'run','-O',str(level),str(source)])
                    self.assertEqual(output,expected)
                    executable=directory/f'probe-o{level}'
                    env=dict(os.environ,LYMAR_AOT_LINKER='driver',LYMAR_AOT_CXX=str(ROOT/'tests/memory/aot_linker.py'))
                    self.command([COMPILER,'build','-O',str(level),str(source),'-o',str(executable)],env)
                    output,_=self.command([str(executable)])
                    self.assertEqual(output,expected)
    def test_builtin_values(self):
        self.execute_both(CALLABLES,'\nCALLABLE_OK\ntrue\n2.5\n',('CallIndirect',))
    def test_atomic_kinds_and_capture_slots(self):
        self.execute_both(ATOMIC,'ATOMIC_CAPTURE_OK\n',('FrameFieldAtomicAdd','FrameFieldAtomicSub','FrameGetFieldAtomic','FrameSetFieldAtomic','TaskGetField'))
    def test_invalid_builtin_arity_is_rejected(self):
        with tempfile.TemporaryDirectory(prefix='lymar-callable-negative-') as temporary:
            directory=Path(temporary);source=directory/'invalid.lm'
            source.write_text('fn bad(action:any):any{return action("ABC");} var byte:any=_builtin_string_byte_at; bad(byte);')
            for level in (0,1,2):
                result=subprocess.run([COMPILER,'run','-O',str(level),str(source)],cwd=ROOT,text=True,capture_output=True,timeout=60)
                self.assertNotEqual(result.returncode,0,result.stdout+result.stderr)
                self.assertRegex(result.stdout+result.stderr,'(?i)(argument|arity|parameter)')
    def test_erased_worker_captures(self):
        self.execute_both('var decimal_value=2.5;var flag=true;var output=channel();concurrent(cores=4){task(i in 1..8){assert(flag);assert(decimal_value==2.5);output.send(decimal_value);}} var count=0;iter(value in output){assert(value==2.5);count=count+1;}assert(count==8);print("CAPTURE_KINDS_OK");', 'CAPTURE_KINDS_OK\n', ('TaskGetField',))
    def test_writable_returned_aliases(self):
        self.execute_both('fn first(xs:[[int]]):[int]{return xs[0];}fn change(values:[int]){values[0]=3;}var xs=[[1]];var child=first(xs);child[0]=2;assert(xs[0][0]==2);change(child);assert(xs[0][0]==3);child.append(5);assert(child[1]==5);child=first(xs);child[0]=4;assert(xs[0][0]==4);print("WRITABLE_ALIAS_OK");', 'WRITABLE_ALIAS_OK\n', ('RefCreate','RefResolve','ListSet'))
    def test_last_use_leases_and_retained_captures(self):
        self.execute_both(r'''
frame Cell {pub var number:int;pub init(){self.number=1;}}
frame Source {pub var cell:Cell;pub init(){self.cell=Cell();}pub fn get():Cell{return self.cell;}}
fn reuse(source:Source,flag:bool):int {
    var first=source.get();first.number=2;
    var prior=0;if(flag){prior=first.number;}else{prior=first.number+1;}
    var second=source.get();second.number=3;return prior+second.number;
}
fn loop_reads(source:Source):int {
    var first=source.get();var total=0;var step=0;
    while(step<3){total=total+first.number;step=step+1;}
    var second=source.get();second.number=4;return total+second.number;
}
fn captured(source:Source):int {
    var first=source.get();var action=fn():int{return first.number;};
    var unrelated=Cell();unrelated.number=7;return action()+unrelated.number;
}
assert(reuse(Source(),true)==5);assert(reuse(Source(),false)==6);
assert(loop_reads(Source())==7);assert(captured(Source())==8);
print("LAST_USE_OK");''','LAST_USE_OK\n',('RefCreate','RefRelease','RefResolve'))
    def test_parent_borrowed_frame_worker_capture(self):
        self.execute_both(r'''
frame Cell {pub var number:int;pub init(){self.number=7;}}
frame Source {pub var cell:Cell;pub init(){self.cell=Cell();}pub fn get():Cell{return self.cell;}}
fn probe():int {
    var source=Source();var borrowed=source.get();var output=channel();
    borrowed.number=7;
    concurrent(cores=4){task(i in 1..8){output.send(borrowed.number);}}
    var total=0;iter(value in output){total=total+value;}return total;
}
fn low_slot():int {
    var borrowed:Cell;var source=Source();borrowed=source.get();var output=channel();
    concurrent(cores=4){task(i in 1..8){output.send(borrowed.number);}}
    var total=0;iter(value in output){total=total+value;}return total;
}
fn tail_slot():int {
    var output=channel();var source=Source();var borrowed=source.get();
    concurrent(cores=4){task(i in 1..8){output.send(borrowed.number);}}
    var total=0;iter(value in output){total=total+value;}return total;
}
assert(probe()==56);assert(low_slot()==56);assert(tail_slot()==56);
print("BORROWED_WORKER_OK");''','BORROWED_WORKER_OK\n',('RefCreate','RefResolve','SchedulerRun','TaskGetField'))
    def test_worker_failures_are_not_swallowed(self):
        with tempfile.TemporaryDirectory(prefix='lymar-worker-errors-') as temporary:
            source=Path(temporary)/'failure.lm'
            for cores in (1,4):
                for policy in ('Stop','Continue'):
                    source.write_text(f'var output=channel();concurrent(cores={cores},on_error={policy}){{task(i in 1..8){{assert(false,"WORKER_FAILURE");}}}}')
                    result=subprocess.run([COMPILER,'run',str(source)],cwd=ROOT,text=True,capture_output=True,timeout=60)
                    self.assertNotEqual(result.returncode,0,result.stdout+result.stderr)
                    self.assertIn('WORKER_FAILURE',result.stdout+result.stderr)
    def test_raw_worker_stress(self):
        original=(ROOT/'tests/memory/raw_worker_ownership.lm').read_text()
        with tempfile.TemporaryDirectory(prefix='lymar-raw-workers-') as temporary:
            sources=[]
            for cores in (1,2,4,8):
                source=Path(temporary)/f'cores{cores}.lm'
                source.write_text(original.replace('cores=4',f'cores={cores}'));sources.append(source)
            for iteration in range(100):
                output,_=self.command([COMPILER,'run','-O',str(iteration%3),str(sources[iteration%4])])
                self.assertEqual(output,'RAW_WORKERS_OK\n')
    def test_partial_worker_failure_retains_results_and_cleans_raw(self):
        with tempfile.TemporaryDirectory(prefix='lymar-worker-partial-') as temporary:
            source=Path(temporary)/'partial.lm'
            for cores in (1,4):
                expected_count='count==1' if cores==1 else 'count<=7'
                source.write_text(f'import std.ffi as ffi;var output=channel();concurrent(cores={cores},on_error=Partial){{task(i in 1..8){{unsafe{{var pointer=ffi.alloc(16);assert(i!=2,"PARTIAL_FAILURE");output.send(i);}}}}}}var count=0;iter(value in output){{assert(value!=2);count=count+1;}}assert({expected_count});print("PARTIAL_OK");')
                output,_=self.command([COMPILER,'run',str(source)])
                self.assertEqual(output,'PARTIAL_OK\n')
    def test_hosted_builtin_values(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build',prefix='callable_probe_') as temporary:
            directory=Path(temporary);name=directory.name
            module=directory/(name+'.lm');module.write_text('pub fn verify():int {var byte:any=_builtin_string_byte_at; return byte("ABC",1);}\n')
            check=directory/'check.lm';check.write_text(f'import build.{name}.{name} as p; assert(p.verify()==66);print("HOSTED_CALLABLE_OK");')
            extension='.dll' if os.name=='nt' else '.dylib' if sys.platform=='darwin' else '.so'
            library=ROOT/'bin'/('lib'+name+extension)
            with preserve_artifacts([library,Path(str(library)+'.meta')]):
                for level in (0,1,2):
                    self.command([COMPILER,'build','-shared','-O',str(level),str(module.relative_to(ROOT)),'-o',str(library)])
                    output,trace=self.command([COMPILER,'run',str(check)],dict(os.environ,LYMAR_DISABLE_INTERPRETER_FALLBACK='1',LYMAR_TRACE_PRECOMPILED='1'))
                    self.assertEqual(output,'HOSTED_CALLABLE_OK\n');self.assertIn('.verify',trace)
if __name__=='__main__':unittest.main()
