"""Package commands and dependency resolution through the committed Lyra API."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class LyraIntegrationTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(prefix='lyra-integration-')
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.compiler = Path(os.environ.get('LYMAR_EXECUTABLE', ROOT / 'bin/lymar')).resolve()
        self.lyra = Path(os.environ.get('LYRA_EXECUTABLE', ROOT / 'bin/lyra')).resolve()
        self.env = dict(os.environ, LYMAR_EXECUTABLE=str(self.compiler))

    def run_command(self, args, cwd, valid=True):
        result = subprocess.run([str(args[0]), *args[1:]], cwd=cwd, env=self.env,
                                capture_output=True, text=True, timeout=60)
        self.assertEqual(result.returncode, 0 if valid else 1, result.stdout + result.stderr)
        return result

    def package(self, name, dependency=''):
        directory = self.root / name
        (directory / 'src').mkdir(parents=True)
        (directory / 'lymar.nol').write_text(
            f'package: {{ name: "{name}", version: "0.0.1" }}\ndependencies: {{{dependency}}}\n')
        return directory

    def test_in_process_init_and_thin_cli(self):
        directory = self.root / 'fresh'
        directory.mkdir()
        self.run_command([self.compiler, 'init'], directory)
        self.assertTrue((directory / 'lymar.nol').is_file())
        self.assertTrue((directory / 'src/main.lm').is_file())
        result = self.run_command([self.compiler, 'run'], directory)
        self.assertEqual(result.stdout.strip(), 'Hello, Lymar!')
        self.assertEqual(self.run_command([self.lyra, 'run'], directory).stdout, result.stdout)

    def test_transitive_dependencies_run_build_and_commands(self):
        transitive = self.package('transitive')
        (transitive / 'src/transitive_api.lm').write_text('pub fn answer(): int { return 42; }')
        dep = self.package('dep', 'transitive: {path: "../transitive"}')
        (dep / 'src/dep_api.lm').write_text('import transitive_api as other; pub fn answer(): int {return other.answer();}')
        app = self.package('app', 'dep: {path: "../dep"}')
        (app / 'src/main.lm').write_text('import dep_api as dep; print(dep.answer());')
        self.assertEqual(self.run_command([self.compiler, 'run'], app).stdout.strip(), '42')
        self.assertTrue((app / 'lymar.lock').is_file())
        for command in ('deps', 'tree'):
            result = self.run_command([self.compiler, command], app)
            self.assertIn('dep', result.stdout)
            self.assertEqual(self.run_command([self.lyra, command], app).stdout, result.stdout)
        for level in (0, 1, 2):
            executable = app / f'app-o{level}'
            self.run_command([self.compiler, 'build', '-O', str(level), '-o', str(executable)], app)
            self.assertEqual(self.run_command([executable], app).stdout.strip(), '42')

    def test_existing_feature_gated_dependency(self):
        dep = self.package('dep')
        (dep / 'src/dep_api.lm').write_text('pub fn answer(): int { return 42; }')
        app = self.package('app', 'dep: {path: "../dep", features: ["extra"]}')
        (app / 'src/main.lm').write_text('import dep_api as dep; print(dep.answer());')
        self.run_command([self.compiler, 'run'], app, False)
        result = self.run_command([self.compiler, 'run', '--features', 'extra'], app)
        self.assertEqual(result.stdout.strip(), '42')

    def test_missing_dependency_rejected_before_execution(self):
        app = self.package('app', 'missing: {path: "../missing"}')
        (app / 'src/main.lm').write_text('print("MUST_NOT_EXECUTE");')
        for command in ('run', 'build', 'deps'):
            result = self.run_command([self.compiler, command], app, False)
            self.assertIn('dependency', result.stderr.lower())
            self.assertNotIn('MUST_NOT_EXECUTE', result.stdout)

    def test_canonical_cycle_rejected(self):
        app = self.package('app', 'other: {path: "../other"}')
        self.package('other', 'app: {path: "../other/../app"}')
        (app / 'src/main.lm').write_text('print("MUST_NOT_EXECUTE");')
        result = self.run_command([self.compiler, 'run'], app, False)
        self.assertIn('circular dependency', result.stderr)

    def test_malformed_manifest_rejected(self):
        app = self.package('app')
        (app / 'lymar.nol').write_text('package: { broken')
        (app / 'src/main.lm').write_text('print("MUST_NOT_EXECUTE");')
        result = self.run_command([self.compiler, 'run'], app, False)
        self.assertIn('manifest', result.stderr.lower())
        self.assertNotIn('MUST_NOT_EXECUTE', result.stdout)

    def test_standalone_source_without_manifest(self):
        source = self.root / 'plain.lm'
        source.write_text('print(7);')
        self.assertEqual(self.run_command([self.compiler, 'run', str(source)], self.root).stdout.strip(), '7')


if __name__ == '__main__':
    unittest.main()
