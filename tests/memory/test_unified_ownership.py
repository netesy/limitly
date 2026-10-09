"""Gate B acceptance tests. Bodies, never function spellings, imply transfer."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[2]
COMPILER = Path(os.environ.get("LYMAR_EXECUTABLE", ROOT / "bin/lymar")).resolve()
class UnifiedOwnershipTests(unittest.TestCase):
    def check(self, source, valid, output=None):
        with tempfile.TemporaryDirectory(prefix="lymar-gate-b-") as tmp:
            path = Path(tmp) / "case.lm"
            path.write_text(source)
            env = dict(os.environ)
            for level in (0, 1, 2):
                result = subprocess.run([str(COMPILER), "run", "-O", str(level), str(path)], cwd=ROOT,
                    env=env, text=True, capture_output=True, timeout=30)
                self.assertGreaterEqual(result.returncode, 0, result.stderr)
                self.assertEqual(result.returncode == 0, valid, result.stdout + result.stderr)
                if not valid: self.assertIn("Ownership error", result.stdout + result.stderr)
                if output is not None: self.assertEqual(result.stdout.strip(), output)
                self.assertNotIn("Sanitizer", result.stderr)
                executable = Path(tmp) / f"case-o{level}"
                compiled = subprocess.run([str(COMPILER), "build", "-O", str(level), str(path), "-o", str(executable)],
                    cwd=ROOT, env=env, text=True, capture_output=True, timeout=120)
                self.assertGreaterEqual(compiled.returncode, 0, compiled.stderr)
                self.assertEqual(compiled.returncode == 0, valid, compiled.stdout + compiled.stderr)
                if not valid:
                    self.assertIn("Ownership error", compiled.stdout + compiled.stderr)
                    self.assertFalse(executable.exists())
                    continue
                native = subprocess.run([str(executable)], env=env, text=True, capture_output=True, timeout=30)
                self.assertEqual(native.returncode, 0, native.stdout + native.stderr)
                self.assertEqual(native.stdout, result.stdout)
                self.assertNotIn("Sanitizer", native.stderr)
    def test_real_source_reference_lowering_and_execution(self):
        source = 'fn element(xs:[[int]]):[int] {return xs[0];} var xs=[[7]]; var child=element(xs); print(child[0]); {var ys=[[9]]; child=element(ys);} print(child[0]);'
        env = dict(os.environ, LYMAR_UNIFIED_OWNERSHIP="1")
        with tempfile.TemporaryDirectory(prefix="lymar-gate-b-parity-") as tmp:
            path = Path(tmp) / "case.lm"; path.write_text(source)
            lir = subprocess.run([str(COMPILER), "-lir", str(path)], cwd=ROOT, env=env, capture_output=True, text=True, timeout=30)
            self.assertEqual(lir.returncode, 0, lir.stdout + lir.stderr)
            for operation in ('RefCreate', 'RefResolve', 'RefRelease', 'RefMove'):
                self.assertIn(operation, lir.stdout)
            for level in (0, 1, 2):
                vm = subprocess.run([str(COMPILER), "run", "-O", str(level), str(path)], cwd=ROOT, env=env, capture_output=True, text=True, timeout=30)
                self.assertEqual(vm.returncode, 0, vm.stdout + vm.stderr)
                self.assertEqual(vm.stdout.strip(), '7\n9')
            for level in (0, 1, 2):
                executable = Path(tmp) / f"case-o{level}"
                build = subprocess.run([str(COMPILER), "build", "-O", str(level), str(path), "-o", str(executable)], cwd=ROOT, env=env, capture_output=True, text=True, timeout=120)
                self.assertEqual(build.returncode, 0, build.stdout + build.stderr)
                run = subprocess.run([str(executable)], env=env, capture_output=True, text=True, timeout=30)
                self.assertEqual(run.returncode, 0, run.stdout + run.stderr)
                self.assertEqual(run.stdout, vm.stdout)
    def test_proven_local_transfer_needs_no_capability(self):
        source = 'var a=[1]; var b=a; print(b[0]);'
        with tempfile.TemporaryDirectory(prefix="lymar-gate-b-static-") as tmp:
            path = Path(tmp) / 'case.lm'; path.write_text(source)
            lir = subprocess.run([str(COMPILER), '-lir', str(path)], cwd=ROOT,
                env=dict(os.environ, LYMAR_UNIFIED_OWNERSHIP='1'), capture_output=True, text=True, timeout=30)
            self.assertEqual(lir.returncode, 0, lir.stdout + lir.stderr)
            self.assertIn('consume=', lir.stdout)
            self.assertNotIn('RefCreate', lir.stdout)
    def test_spelling_is_not_effect(self):
        self.check('fn consume_observe(x:[int]) {print(x[0]);} var a=[1]; consume_observe(a); print(a[0]);', True, '1\n1')
    def test_body_infers_transfer(self):
        self.check('fn take(x:[int]) {var owned=x;} var a=[1]; take(a); print(a);', False)
    def test_indirect_transfer(self):
        self.check('fn take(x:[int]) {var owned=x;} var f=take; var a=[1]; f(a); print(a);', False)
    def test_branch_selected_function(self):
        self.check('fn observe(x:[int]) {} fn take(x:[int]) {var owned=x;} var f=observe; if(true){f=take;}else{f=observe;} var a=[1]; f(a); print(a);', False)
    def test_mutually_exclusive_consumption(self):
        self.check('fn take(x:[int]) {var owned=x;} fn use(flag:bool) {var a=[1]; if(flag){take(a);}else{take(a);}} use(true);', True)
    def test_loop_backedge_transfer(self):
        self.check('fn take(x:[int]) {var owned=x;} var a=[1]; for(var i=0;i<2;i=i+1){take(a);}', False)
    def test_loop_borrow(self):
        self.check('fn observe(x:[int]) {print(x[0]);} var a=[1]; for(var i=0;i<2;i=i+1){observe(a);} print(a[0]);', True, '1\n1\n1')
    def test_break_has_no_backedge(self):
        self.check('fn take(x:[int]) {var owned=x;} var a=[1]; while(true){take(a); break;}', True)
    def test_shadowing(self):
        self.check('var a=[1]; {var a=[2]; var b=a; print(b[0]);} print(a[0]);', True, '2\n1')
    def test_mutable_shadow_of_immutable_binding(self):
        self.check('val value=1; {var value=2; value=3; print(value);} print(value);', True, '3\n1')
    def test_erased_transfer(self):
        self.check('var a=[1]; var b=a as any; print(a);', False)
    def test_erased_owner_transfer(self):
        self.check('var a=[1]; var b=a as any; var c=b; print(b);', False)
    def test_erased_borrow_return_provenance(self):
        self.check('fn identity(x:any):any {return x;} var a=[1]; var erased=a as any; var alias=identity(erased); var moved=erased; print(alias);', False)
    def test_erased_copy_is_borrowed(self):
        self.check('fn identity(x:any):any {var borrowed=x; return borrowed;} var a=[1]; var erased=a as any; var alias=identity(erased); print(erased); print(alias);', True, '[1]\n[1]')
    def test_recovery_cast_preserves_alias(self):
        self.check('var a=[1]; var erased=a as any; var recovered=erased as [int]; recovered[0]=8; print(erased);', True, '[8]')
    def test_returned_alias_invalidated(self):
        self.check('fn identity(x:[int]):[int] {return x;} fn take(x:[int]) {var owned=x;} var a=[1]; var alias=identity(a); take(a); print(alias);', False)
    def test_returned_alias_mutation(self):
        self.check('fn identity(x:[int]):[int] {return x;} var a=[1]; var alias=identity(a); alias[0]=7; print(a[0]);', True, '7')
    def test_higher_order_transfer(self):
        self.check('fn take(x:[int]) {var owned=x;} fn invoke(f:fn([int]):any,x:[int]) {f(x);} var a=[1]; invoke(take,a); print(a);', False)
    def test_higher_order_borrow(self):
        self.check('fn observe(x:[int]) {print(x[0]);} fn invoke(f:fn([int]):any,x:[int]) {f(x);} var a=[1]; invoke(observe,a); invoke(observe,a); print(a[0]);', True, '1\n1\n1')
    def test_unused_higher_order_body_transfer_is_checked(self):
        self.check('fn unused(f:fn(int):int):int {var owner=[1]; var moved=owner; print(owner); return 0;} print(1);', False)
    def test_unused_higher_order_parameter_transfer_is_checked(self):
        self.check('fn unused(f:fn(int):int, owner:[int]):int {var moved=owner; print(owner); return 0;} print(1);', False)
    def test_unused_higher_order_contract_remains_deferred(self):
        self.check('fn pending(f:fn([int]):nil, owner:[int]) {f(owner);} print(7);', True, '7')
    def test_default_checker_cannot_be_disabled_by_legacy_gate(self):
        with tempfile.TemporaryDirectory(prefix="lymar-default-ownership-") as tmp:
            path = Path(tmp) / 'case.lm'
            path.write_text('fn take(x:[int]) {var owned=x;} var alias=take; var owner=[1]; alias(owner); print(owner);')
            for gate in (None, '0'):
                env = dict(os.environ)
                env.pop('LYMAR_UNIFIED_OWNERSHIP', None)
                if gate is not None:
                    env['LYMAR_UNIFIED_OWNERSHIP'] = gate
                for level in (0, 1, 2):
                    for action in ('run', 'build'):
                        executable = Path(tmp) / f'case-o{level}'
                        command = [str(COMPILER), action, '-O', str(level), str(path)]
                        if action == 'build':
                            command += ['-o', str(executable)]
                        result = subprocess.run(command, cwd=ROOT, env=env, text=True,
                                                capture_output=True, timeout=30)
                        self.assertGreater(result.returncode, 0, result.stdout + result.stderr)
                        self.assertIn('Ownership error', result.stdout + result.stderr)
                        self.assertNotIn('Sanitizer', result.stderr)
                        self.assertFalse(executable.exists())
    def test_closure_capture_after_transfer(self):
        self.check('fn take(x:[int]) {var owned=x;} var a=[1]; var f=fn():int {return a[0];}; take(a); print(f());', False)
    def test_closure_borrow(self):
        self.check('var a=[1]; var f=fn():int {return a[0];}; print(f()); print(a[0]);', True, '1\n1')
    def test_recursive_transfer(self):
        self.check('fn take(x:[int],n:int) {if(n==0){var owned=x;}else{take(x,n-1);}} var a=[1]; take(a,2); print(a);', False)
    def test_early_return_join(self):
        self.check('fn take(x:[int]) {var owned=x;} fn use(flag:bool) {var a=[1]; if(flag){take(a); return;} print(a[0]);} use(false);', True, '1')
    def test_self_return_reassignment_keeps_owner(self):
        self.check('fn identity(x:[int]):[int] {return x;} var a=[7]; a=identity(a); print(a[0]);', True, '7')
    def test_projection_is_not_container_consumption(self):
        self.check('fn observe(x:any):any {return x;} fn visit(items:[any],f:fn(any):any) {var child=items[0]; f(child);} var values=[1] as [any]; visit(values,observe); print(values[0]);',True,'1')
    def test_interpolation_reads_moved_owner(self):
        self.check('var a=[1]; var moved=a; print("{a}");',False)
    def test_unsafe_transfer_is_checked(self):
        self.check('var a=[1]; unsafe {var moved=a;} print(a);',False)
    def test_function_body_transfer_is_checked(self):
        self.check('fn broken() {var a=[1]; var moved=a; print(a);} broken();',False)
    def test_method_body_transfer_is_checked(self):
        self.check('frame Box {pub fn broken() {var a=[1]; var moved=a; print(a);}}',False)
    def test_lifecycle_body_transfer_is_checked(self):
        self.check('frame Box {pub init() {var a=[1]; var moved=a; print(a);}}',False)
    def test_nested_function_body_transfer(self):
        self.check('fn outer() {fn inner() {var a=[1]; var moved=a; print(a);} inner();} outer();',False)
    def test_generation_saturation_does_not_revive_alias(self):
        self.check('fn identity(x:[int]):[int] {return x;} var a=[0]; a=[1]; a=[2]; var alias=identity(a); a=[3]; print(alias);',False)
    def test_reassignment_does_not_revive_closure(self):
        self.check('var a=[0]; a=[1]; a=[2]; var f=fn():int {return a[0];}; a=[3]; print(f());',False)
    def test_self_assignment_preserves_borrow_alias(self):
        self.check('fn identity(x:[int]):[int] {return x;} var a=[7]; var alias=identity(a); a=a; print(alias[0]);',True,'7')
    def test_returned_function_alias_borrows(self):
        self.check('fn observe(x:[int]):int {return x[0];} fn factory():fn([int]):int {return observe;} var f=factory(); var a=[7]; print(f(a)); print(a[0]);',True,'7\n7')
    def test_returned_function_alias_consumes(self):
        self.check('fn take(x:[int]):int {var moved=x; return moved[0];} fn factory():fn([int]):int {return take;} var f=factory(); var a=[7]; f(a); print(a);',False)
    def test_returned_closure_borrows(self):
        self.check('fn factory(x:[int]):fn():int {return fn():int {return x[0];};} var a=[7]; var f=factory(a); print(f()); print(a[0]);',True,'7\n7')
    def test_returned_closure_capture_after_transfer(self):
        self.check('fn factory(x:[int]):fn():int {return fn():int {return x[0];};} var a=[7]; var f=factory(a); var moved=a; print(f());',False)
    def test_constructor_effect_consumes(self):
        self.check('frame Box {pub init(x:[int]) {var moved=x;}} var a=[7]; var box=Box(a); print(a);',False)
    def test_method_effect_consumes(self):
        self.check('frame Box {pub fn take(x:[int]) {var moved=x;}} var box=Box(); var a=[7]; box.take(a); print(a);',False)
    def test_managed_any_parameter_transfer(self):
        self.check('fn own(x:[int]) {var owner=x;} fn take(x:any) {own(x as [int]);} var a=[1]; take(a); print(a[0]);', False)
    def test_consumed_any_parameter_read_in_body(self):
        self.check('fn own(x:[int]) {var owner=x;} fn use(x:any) {own(x as [int]); print(x);} var a=[1]; use(a);', False)
    def test_opaque_alias_expression_keeps_ownership_obligation(self):
        self.check('var f:fn([int]):any=nil; var a=[1]; f(a as [int]);', False)
    def test_captured_closure_any_parameter_copy(self):
        self.check('var flag=0; var copy=fn(x:any):any {print(flag); var borrowed=x; return borrowed;}; var a=[1]; var erased=a as any; var alias=copy(erased); print(erased); print(alias);', True, '0\n[1]\n[1]')
    def test_captured_closure_any_parameter_consumption(self):
        self.check('fn own(x:[int]) {var owner=x;} var flag=0; var use=fn(x:any) {print(flag); own(x); print(x);}; var a=[1]; use(a);', False)
    def test_scalar_any_parameter_copy(self):
        self.check('fn copy(x:any):any {var copied=x; return copied;} var a=7; print(copy(a)); print(a);', True, '7\n7')
    def test_managed_any_alias_call_transfer(self):
        self.check('fn own(x:[int]) {var owner=x;} fn take(x:any) {own(x as [int]);} var f=take; var a=[1]; f(a); print(a[0]);', False)
    def test_nullable_projected_frame_reassignment(self):
        self.check('frame State {pub var value:int; pub init(n:int) {self.value=n;}} var states={} as {str:State}; var st=states["missing"] as State; if(st==nil){st=State(7);} print(st.value); st=nil as State; if(st==nil){st=State(9);} print(st.value);', True, '7\n9')
    def test_nullable_declared_frame_borrow(self):
        self.check('frame State {pub var value:int; pub init(n:int) {self.value=n;}} var states={} as {str:State}; states["x"]=State(8); var st:State=nil as State; st=states["x"] as State; print(st.value);', True, '8')
    def test_nullable_reference_region_promotion(self):
        self.check('frame State {pub var value:int; pub init(n:int) {self.value=n;}} var states={} as {str:State}; var st=states["x"] as State; {st=states["y"] as State;} if(st==nil){st=State(9);} print(st.value);', True, '9')
    def test_nullable_reference_dereference_remains_checked(self):
        sources = [
            'frame State {pub var value:int;} var states={} as {str:State}; var st=states["missing"] as State; print(st.value);',
            'frame State {pub var value:int; pub fn read():int {return self.value;}} var states={} as {str:State}; var st=states["missing"] as State; print(st.read());',
            'var states={} as {str:[int]}; var st=states["missing"] as [int]; print(st[0]);',
        ]
        with tempfile.TemporaryDirectory(prefix="lymar-null-reference-") as tmp:
            env = dict(os.environ, LYMAR_UNIFIED_OWNERSHIP="1")
            for index, source in enumerate(sources):
                path = Path(tmp) / f"case{index}.lm"; path.write_text(source)
                lir = subprocess.run([str(COMPILER), "-lir", str(path)], cwd=ROOT, env=env,
                    text=True, capture_output=True, timeout=30)
                self.assertEqual(lir.returncode, 0, lir.stdout + lir.stderr)
                self.assertIn("RefResolve", lir.stdout)
                for level in (0, 1, 2):
                    vm = subprocess.run([str(COMPILER), "run", "-O", str(level), str(path)],
                        cwd=ROOT, env=env, text=True, capture_output=True, timeout=30)
                    self.assertNotEqual(vm.returncode, 0)
                    self.assertIn("reference", vm.stderr.lower())
                    executable = Path(tmp) / f"case{index}-o{level}"
                    build = subprocess.run([str(COMPILER), "build", "-O", str(level), str(path), "-o", str(executable)],
                        cwd=ROOT, env=env, text=True, capture_output=True, timeout=120)
                    self.assertEqual(build.returncode, 0, build.stdout + build.stderr)
                    native = subprocess.run([str(executable)], env=env, text=True, capture_output=True, timeout=30)
                    self.assertNotEqual(native.returncode, 0)
                    self.assertIn("reference", native.stderr.lower())
                    self.assertNotIn("Sanitizer", native.stderr)

    def test_scalar_erasure_cannot_create_nullable_object_reference(self):
        # Integer two must not be confused with the native nil word. Check
        # scalar provenance through calls and collection slots, not just literals.
        sources = [
            'frame State {pub var value:int;} var erased=VALUE as any; var st=erased as State; print(st==nil);'.replace('VALUE', value)
            for value in ('0', '2', 'false', 'true')
        ] + [
            'frame State {pub var value:int;} fn identity(x:any):any {return x;} var erased=identity(2); var st=erased as State; print(st==nil);',
            'frame State {pub var value:int;} var values=[2] as [any]; var erased=values[0]; var st=erased as State; print(st==nil);',
        ]
        with tempfile.TemporaryDirectory(prefix="lymar-scalar-reference-") as tmp:
            env = dict(os.environ, LYMAR_UNIFIED_OWNERSHIP="1")
            for index, source in enumerate(sources):
                path = Path(tmp) / f"case{index}.lm"; path.write_text(source)
                for level in (0, 1, 2):
                    vm = subprocess.run([str(COMPILER), "run", "-O", str(level), str(path)],
                        cwd=ROOT, env=env, text=True, capture_output=True, timeout=30)
                    self.assertNotEqual(vm.returncode, 0, vm.stdout + vm.stderr)
                    self.assertIn("managed object", vm.stderr.lower())
                    executable = Path(tmp) / f"case{index}-o{level}"
                    build = subprocess.run([str(COMPILER), "build", "-O", str(level), str(path), "-o", str(executable)],
                        cwd=ROOT, env=env, text=True, capture_output=True, timeout=120)
                    self.assertEqual(build.returncode, 0, build.stdout + build.stderr)
                    native = subprocess.run([str(executable)], env=env, text=True, capture_output=True, timeout=30)
                    self.assertNotEqual(native.returncode, 0, native.stdout + native.stderr)
                    self.assertIn("managed object", native.stderr.lower())
                    self.assertNotIn("Sanitizer", native.stderr)

    def test_nil_provenance_through_returns_and_collections(self):
        self.check('frame State {pub var value:int;} fn absent():any {return nil;} var values=[nil] as [any]; var first=absent() as State; var second=values[0] as State; print(first==nil); print(second==nil);', True, 'true\ntrue')

    def test_managed_string_constant_borrow_preserves_vm_identity(self):
        self.check('frame State {pub var value:int;} var erased="hello" as any; var st=erased as State; print(st==nil); print(erased);', True, 'false\nhello')

    def test_nil_and_integer_output_uses_value_provenance(self):
        self.check('var values={} as {str:int}; values["two"]=2; values["zero"]=0; print(values["missing"]); print(values["two"]); print(values["zero"]); fn erased(x:any):any {return x;} print(erased(2)); print(erased(0)); print(erased(1000000)); print(erased(nil));', True, 'nil\n2\n0\n2\n0\n1000000\nnil')

    def test_erased_float_view_matches_vm(self):
        self.check('frame State {pub var value:int;} var erased=2.0 as any; var st=erased as State; print(st==nil); print(erased);', True, 'false\n2')
    def test_implicit_nil_return_retains_erased_kind(self):
        self.check('fn empty():any {} var value=empty(); print(value); print(value==nil); frame State {pub var value:int;} var view=value as State; print(view==nil);', True, 'nil\ntrue\ntrue')
    def test_erased_nil_equality_preserves_integer_kind(self):
        self.check('fn identity(x:any):any{return x;} var value=2 as any; print(value==nil); print(nil==value); print(value!=nil); print(identity(0)==nil); print(identity(nil)==nil); print(identity(1000000)==identity(1000000)); print(identity(true)==identity(1));', True, 'false\nfalse\ntrue\nfalse\ntrue\ntrue\nfalse')
    def test_erased_boolean_output_survives_calls_and_storage(self):
        self.check('fn identity(x:any):any{return x;} var alias=identity; var values=[true as any,false as any] as [any]; var table={} as {str:any}; table["flag"]=alias(false); print(alias(true)); print(values[0]); print(values[1]); print(table["flag"]);', True, 'true\ntrue\nfalse\nfalse')
    def test_erased_scalar_branch_reassignment(self):
        self.check('var value:any=2; if(true){value=false as any;}else{value=2 as any;} print(value); value=2.5 as any; print(value); value=nil; print(value==nil);', True, 'false\n2.5\ntrue')
    def test_erased_float_direct_alias_and_higher_order_calls(self):
        self.check('fn identity(x:any):any{return x;} fn invoke(f:fn(any):any,x:any):any{return f(x);} var alias=identity; print(identity(2.5)); print(alias(3.25)); print(invoke(alias,4.5)); print((identity(2.5) as float)+1.0); print(identity(2.5)==identity(2.5));', True, '2.5\n3.25\n4.5\n3.5\ntrue')
    def test_erased_closure_captures_and_return_values(self):
        self.check('fn captured(x:any):fn():any{return fn():any{return x;};} var first=captured(false); var second=captured(2.75); print(first()); print(second());', True, 'false\n2.75')
    def test_erased_frame_slots_and_returned_float_lifetime(self):
        self.check('frame Box {pub var value:any; pub init(x:any){self.value=x;} pub fn read():any{return self.value;}} fn make():Box{return Box(2.5);} var box=make(); print(box.read()); box.value=false as any; print(box.read());', True, '2.5\nfalse')
    def test_erased_collection_scalars_preserve_kinds(self):
        self.check('fn values():[any]{return [2.5 as any,true as any,nil,2 as any];} var items=values(); print(items[0]); print(items[1]); print(items[2]); print(items[3]); print(items);', True, '2.5\ntrue\nnil\n2\n[2.5, true, nil, 2]')
    def test_erased_float_truth_and_numeric_casts_match_vm(self):
        self.check('fn identity(x:any):any{return x;} print(identity(0.0) as bool); print(identity(2.5) as bool); print(identity(2.5) as int); print(identity(false) as int); print(identity(false) as float);', True, 'false\ntrue\n2\n0\n0')

    def test_frame_parameter_runtime_shape_checks(self):
        sources = [
            'frame State {pub var value:int;} var erased=2.5 as any; var st=erased as State; print(st.value);',
            'frame State {pub var value:int;} var erased="hello" as any; var st=erased as State; print(st.value);',
            'frame State {pub var value:int;} fn read(s:State):int {return s.value;} var states={} as {str:State}; print(read(states["missing"] as State));',
            'frame State {pub var value:int;} fn write(s:State) {s.value=7;} var states={} as {str:State}; write(states["missing"] as State);',
            'frame State {pub var value:int;} fn read(s:State):int {return s.value;} var xs=[1]; var erased=xs as any; print(read(erased as State));',
            'frame State {pub var value:int;} frame Outer {pub var child:State;} fn read(s:Outer):int {return s.child.value;} var outer=Outer(); print(read(outer));',
        ]
        with tempfile.TemporaryDirectory(prefix="lymar-frame-shape-") as tmp:
            env = dict(os.environ, LYMAR_UNIFIED_OWNERSHIP="1")
            for index, source in enumerate(sources):
                path = Path(tmp) / f"case{index}.lm"; path.write_text(source)
                for level in (0, 1, 2):
                    vm = subprocess.run([str(COMPILER), "run", "-O", str(level), str(path)],
                        cwd=ROOT, env=env, text=True, capture_output=True, timeout=30)
                    self.assertNotEqual(vm.returncode, 0)
                    self.assertIn("frame", vm.stderr.lower())
                    executable = Path(tmp) / f"case{index}-o{level}"
                    build = subprocess.run([str(COMPILER), "build", "-O", str(level), str(path), "-o", str(executable)],
                        cwd=ROOT, env=env, text=True, capture_output=True, timeout=120)
                    self.assertEqual(build.returncode, 0, build.stdout + build.stderr)
                    native = subprocess.run([str(executable)], env=env, text=True, capture_output=True, timeout=30)
                    self.assertNotEqual(native.returncode, 0)
                    self.assertIn("frame", native.stderr.lower())
                    self.assertNotIn("Sanitizer", native.stderr)

    def test_global_read_before_initialization(self):
        self.check('var values:[int]; fn observe():int {return values[0];} var result=observe(); values=[7]; print(result);',False)
    def test_unused_projected_callable_contract(self):
        self.check('type Hook=fn([int]):nil; frame Box {pub var cb:Hook; pub var data:[int]; pub fn invoke(){self.cb(self.data);}} print(7);', True, '7')
    def test_unused_captured_callable_obligation(self):
        self.check('type Hook=fn([int]):nil; frame Box {pub var cb:Hook; pub var data:[int]; pub fn invoke(){self.cb(self.data);}} fn pending(box:Box):fn():nil {return fn():nil {box.invoke();};} print(7);', True, '7')
    def test_concrete_projected_callable_stays_opaque(self):
        self.check('type Hook=fn([int]):nil; frame Box {pub var cb:Hook; pub var data:[int]; pub fn invoke(){self.cb(self.data);}} var box=Box(); box.invoke();', False)
    def test_returned_capture_obligation_stays_opaque(self):
        self.check('type Hook=fn([int]):nil; frame Box {pub var cb:Hook; pub var data:[int]; pub fn invoke(){self.cb(self.data);}} fn pending(box:Box):fn():nil {return fn():nil {box.invoke();};} var box=Box(); var callback=pending(box); callback();', False)

    def test_callable_summary_dependency_invalidation(self):
        self.check('fn relay(xs:[int]) {later(xs);} fn later(xs:[int]) {var owner=xs;} var xs=[1]; relay(xs); print(xs[0]);', False)
    def test_recursive_callable_summary_dependency_invalidation(self):
        self.check('fn relay(xs:[int], n:int) {if(n==0){later(xs);}else{relay(xs,n-1);}} fn later(xs:[int]) {var owner=xs;} var xs=[1]; relay(xs,2); print(xs[0]);', False)

    def test_break_retains_owner_until_scope_cleanup(self):
        self.check('fn test_loop(){var data=[1,2,3]; while(true){break;} print(data[0]);} test_loop();', True, '1')

if __name__ == '__main__': unittest.main()
