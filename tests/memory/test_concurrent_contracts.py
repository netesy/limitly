"""Source-level concurrent capture isolation and shared atomic identity."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
COMPILER = os.environ.get('LYMAR_EXECUTABLE', str(ROOT / 'bin/lymar'))
FRAME = '''frame Cell {pub var number:int;pub init(){self.number=0;}}
frame Source {pub var cell:Cell;pub init(){self.cell=Cell();}pub fn get():Cell{return self.cell;}}
'''

class ConcurrentContractTests(unittest.TestCase):
    def command(self, command, env=None):
        result = subprocess.run(command, cwd=ROOT, env=env, text=True, capture_output=True, timeout=60)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return result.stdout

    def test_mutating_closure_isolation(self):
        forms = (
            'var change=fn(){borrowed.number+=1;};',
            'fn write(value:Cell){value.number+=1;}var change=fn(){write(source.get());};',
            'var original=fn(){borrowed.number+=1;};var change=original;',
            'var original=fn(){borrowed.number+=1;};var change:any=original;',
            'var change=fn(){borrowed.number+=1;};var wrapper=change;change=wrapper;',
            'fn make(value:Cell):fn(){return fn(){value.number+=1;};}var change=make(borrowed);',
            'var change=fn(){borrowed.number+=1;};fn higher(action:any){action();}var outer=change;change=fn(){higher(outer);};',
        )
        with tempfile.TemporaryDirectory(prefix='lymar-isolation-') as temporary:
            source = Path(temporary) / 'probe.lm'
            for form in forms:
                with self.subTest(form=form):
                    source.write_text(FRAME + 'fn probe(){var source=Source();var borrowed=source.get();' + form + 'concurrent(cores=4){task(i in 1..8){change();}}}probe();')
                    for level in (0, 1, 2):
                        result = subprocess.run([COMPILER, 'run', '-O', str(level), str(source)], cwd=ROOT, text=True, capture_output=True, timeout=60)
                        self.assertNotEqual(result.returncode, 0, result.stdout + result.stderr)
                        self.assertIn('concurrent callable mutates captured', result.stdout + result.stderr)
                        executable = Path(temporary) / f'invalid-o{level}'
                        compiled = subprocess.run([COMPILER, 'build', '-O', str(level), str(source), '-o', str(executable)], cwd=ROOT, text=True, capture_output=True, timeout=60)
                        self.assertNotEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
                        self.assertIn('concurrent callable mutates captured', compiled.stdout + compiled.stderr)
                        self.assertFalse(executable.exists())

    def test_atomic_cell_is_shared_and_shadowing_is_distinct(self):
        text = '''var count:atomic=0;var change=fn(){count+=1;};
concurrent(cores=4){task(i in 1..8){var step=0;while(step<200){change();step+=1;}var count:atomic=5;count-=1;assert(count==4);}}
assert(count==1600);count-=1;assert(count==1599);count=7;assert(count==7);print("SHARED_ATOMIC_OK");'''
        with tempfile.TemporaryDirectory(prefix='lymar-shared-atomic-') as temporary:
            source = Path(temporary) / 'probe.lm'
            source.write_text(text)
            lir = self.command([COMPILER, '-lir', str(source)])
            for operation in ('NewFrame', 'FrameFieldAtomicAdd', 'FrameFieldAtomicSub', 'FrameGetFieldAtomic', 'FrameSetFieldAtomic'):
                self.assertIn(operation, lir)
            for level in (0, 1, 2):
                with self.subTest(level=level):
                    self.assertEqual(self.command([COMPILER, 'run', '-O', str(level), str(source)]), 'SHARED_ATOMIC_OK\n')
                    executable = Path(temporary) / f'probe-o{level}'
                    env = dict(os.environ, LYMAR_AOT_LINKER='driver', LYMAR_AOT_CXX=str(ROOT / 'tests/memory/aot_linker.py'))
                    self.command([COMPILER, 'build', '-O', str(level), str(source), '-o', str(executable)], env)
                    self.assertEqual(self.command([str(executable)]), 'SHARED_ATOMIC_OK\n')

    def execute_both(self, text, expected):
        with tempfile.TemporaryDirectory(prefix='lymar-concurrent-execution-') as temporary:
            source = Path(temporary) / 'probe.lm';source.write_text(text)
            for level in (0,1,2):
                with self.subTest(level=level):
                    self.assertEqual(self.command([COMPILER,'run','-O',str(level),str(source)]),expected)
                    executable=Path(temporary)/f'probe-o{level}'
                    env=dict(os.environ,LYMAR_AOT_LINKER='driver',LYMAR_AOT_CXX=str(ROOT/'tests/memory/aot_linker.py'))
                    self.command([COMPILER,'build','-O',str(level),str(source),'-o',str(executable)],env)
                    self.assertEqual(self.command([str(executable)]),expected)

    def test_native_raw_workers(self):
        self.execute_both((ROOT/'tests/memory/raw_worker_ownership.lm').read_text(),'RAW_WORKERS_OK\n')

    def test_worker_local_mutating_closure_is_valid(self):
        self.execute_both('concurrent(cores=2){task(i in 1..2){var local=[0];var change=fn(){local[0]+=1;};change();assert(local[0]==1);}}print("LOCAL_CAPTURE_OK");','LOCAL_CAPTURE_OK\n')

    def test_workers_overlap(self):
        self.execute_both('var arrived:atomic=0;var output=channel();concurrent(cores=4,timeout=500ms){task(i in 1..4){arrived+=1;while(arrived<4){}output.send(i);}}var total=0;iter(value in output){total+=value;}assert(total==10);print("RENDEZVOUS_OK");','RENDEZVOUS_OK\n')

    def test_partial_failure_runs_destructors(self):
        self.execute_both('frame Tracked {pub number:int;pub init(){self.number=1;}pub deinit(){print("CLEANED");}}concurrent(cores=1,on_error=Partial){task(i in 1..4){var value=Tracked();assert(i!=2,"PARTIAL_FAILURE");}}print("CLEANUP_OK");','CLEANED\nCLEANED\nCLEANUP_OK\n')

    def test_native_worker_error_policies(self):
        with tempfile.TemporaryDirectory(prefix='lymar-native-errors-') as temporary:
            source=Path(temporary)/'probe.lm'
            for policy in ('Stop','Continue'):
                source.write_text('concurrent(cores=4,on_error='+policy+'){task(i in 1..8){assert(false,"WORKER_FAILURE");}}')
                for level in (0,1,2):
                    with self.subTest(policy=policy,level=level):
                        executable=Path(temporary)/f'probe-{policy}-o{level}'
                        env=dict(os.environ,LYMAR_AOT_LINKER='driver',LYMAR_AOT_CXX=str(ROOT/'tests/memory/aot_linker.py'))
                        self.command([COMPILER,'build','-O',str(level),str(source),'-o',str(executable)],env)
                        result=subprocess.run([str(executable)],cwd=ROOT,text=True,capture_output=True,timeout=60)
                        self.assertNotEqual(result.returncode,0,result.stdout+result.stderr)
                        self.assertIn('WORKER_FAILURE',result.stdout+result.stderr)

if __name__ == '__main__':
    unittest.main()
