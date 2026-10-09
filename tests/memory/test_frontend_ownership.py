"""Adversarial ownership cases from the memory audit, plus valid joins."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT = Path(__file__).resolve().parents[2]
COMPILER = Path(os.environ.get("LYMAR_EXECUTABLE", ROOT / "bin/lymar")).resolve()
class OwnershipTests(unittest.TestCase):
    def check(self, source, valid):
        with tempfile.TemporaryDirectory(prefix="lymar-ownership-") as tmp:
            path = Path(tmp) / "case.lm"
            path.write_text(source)
            result = subprocess.run([str(COMPILER), "run", str(path)], cwd=ROOT,
                                    capture_output=True, text=True, timeout=60)
            self.assertGreaterEqual(result.returncode, 0, result.stderr)
            self.assertEqual(result.returncode == 0, valid, result.stdout + result.stderr)
            self.assertNotIn("AddressSanitizer", result.stderr)
    def test_race_in_function_body(self):
        self.check('fn enclosed() {var counter=0; concurrent {task(i in 1..10) {counter=counter+1;}}} enclosed();', False)
    def test_race_in_method_body(self):
        self.check('frame Container {pub fn run() {var counter=0; concurrent {task(i in 1..10) {counter=counter+1;}}}}', False)
    def test_race_in_unsafe_body(self):
        self.check('unsafe {var counter=0; concurrent {task(i in 1..10) {counter=counter+1;}}}', False)
    def test_callable_declaration_is_not_execution(self):
        self.check('fn read_value():int {return shared[0];} var shared:[int]=[7]; read_value();', True)
    def test_callable_parameter_scope(self):
        self.check('fn view(values:[int]):int {return values[0];} var values=[9]; print(view(values)); print(values[0]);', True)
    def test_indirect_consuming_call(self):
        self.check('fn consume_values(v: [int]) {var owned=v;} var f=consume_values; var v=[1]; f(v); print(v[0]);', False)
    def test_reassigned_consuming_call(self):
        self.check('fn ordinary(v:[int]) {} fn consume_values(v:[int]) {var owned=v;} var f=ordinary; f=consume_values; var v=[1]; f(v); print(v[0]);', False)
    def test_shadowed_callable_origin(self):
        self.check('fn ordinary(v:[int]) {} fn consume_values(v:[int]) {var owned=v;} var f=consume_values; {var f=ordinary;} var v=[1]; f(v); print(v[0]);', False)
    def test_erased_owner(self):
        self.check('fn consume_values(v: [int]) {var owned=v;} var v=[1]; var a=v as any; consume_values(v); var b=a as [int]; print(b[0]);', False)
    def test_erased_alias_move(self):
        self.check('var v=[1]; var a=v as any; var b=a; print(a);', False)
    def test_shadow_does_not_restore_moved_owner(self):
        self.check('fn consume_values(v: [int]) {var owned=v;} var v=[1]; consume_values(v); {var v=[2]; print(v[0]);} print(v[0]);', False)
    def test_consumption_in_mutually_exclusive_branches(self):
        self.check('fn consume_values(v: [int]) {var owned=v;} fn test(flag:bool) {var v=[1]; if(flag){consume_values(v);}else{consume_values(v);}} test(true);', True)
    def test_scalar_shadow_is_independent(self):
        self.check('fn consume_values(v: [int]) {var owned=v;} var v=[1]; consume_values(v); {var v=2; print(v);}', True)
    def test_immutable_binding_survives_mutable_shadow(self):
        self.check('val value=1; {var value=2; value=3;} value=4;', False)
    def test_valid_erased_transfer(self):
        self.check('var v=[1]; var a=v as any; var b=a as [int]; print(b[0]);', True)
if __name__ == "__main__":
    unittest.main()
