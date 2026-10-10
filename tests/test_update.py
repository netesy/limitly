"""Release selection, integrity, extraction, and transactional activation tests."""
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tarfile
import tempfile
import unittest
import zipfile
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import update

def archive_bytes(entries):
    buffer = io.BytesIO()
    with tarfile.open(fileobj=buffer, mode='w:gz') as archive:
        for name, contents, mode in entries:
            entry = tarfile.TarInfo(name); entry.size = len(contents); entry.mode = mode
            archive.addfile(entry, io.BytesIO(contents))
    return buffer.getvalue()

class UpdateTests(unittest.TestCase):
    def test_release_selection(self):
        release = {'tag_name': 'v0.0.1', 'assets': [{'name': 'lymar-v0.0.1-x86_64-linux.tar.gz'}]}
        with patch.object(update, 'download', return_value=json.dumps(release).encode()) as request:
            tag, asset, _ = update.resolve_release('lymarlang/lymar', None, 'x86_64-linux')
            self.assertEqual(tag, 'v0.0.1')
            self.assertIn('/releases/latest', request.call_args.args[0])
            update.resolve_release('lymarlang/lymar', 'v0.0.1', 'x86_64-linux')
            self.assertIn('/releases/tags/v0.0.1', request.call_args.args[0])

    def test_missing_ambiguous_prerelease_and_unsafe_tag(self):
        asset = {'name': 'lymar-x86_64-linux.zip'}
        for release in ({'tag_name': 'v1', 'assets': []}, {'tag_name': 'v1', 'assets': [asset, asset]},
                        {'tag_name': 'v1', 'prerelease': True, 'assets': [asset]},
                        {'tag_name': '../escape', 'assets': [asset]}):
            with self.subTest(release=release), patch.object(update, 'download', return_value=json.dumps(release).encode()):
                with self.assertRaises(ValueError): update.resolve_release('owner/repo', None, 'x86_64-linux')

    def test_digest_and_checksums(self):
        digest = hashlib.sha256(b'archive').hexdigest()
        update.verify_payload(b'archive', {'digest': 'sha256:' + digest}, [])
        with self.assertRaises(ValueError): update.verify_payload(b'wrong', {'digest': 'sha256:' + digest}, [])
        with patch.object(update, 'download', return_value=(digest + '  lymar.zip\n').encode()):
            update.verify_payload(b'archive', {'name': 'lymar.zip'}, [{'name': 'SHA256SUMS', 'browser_download_url': 'https://example.invalid/checksums'}])
        with self.assertRaises(ValueError): update.verify_payload(b'archive', {'name': 'lymar.zip'}, [])

    def test_https_required(self):
        with self.assertRaises(ValueError): update.download('http://example.invalid/archive')

    def test_traversal_and_links_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary); archive = directory / 'input.tar.gz'; destination = directory / 'home'; destination.mkdir()
            for name in ('../escape', '/escape', 'C:/escape', 'a\\escape'):
                archive.write_bytes(archive_bytes([(name, b'x', 0o644)]))
                with self.subTest(name=name), self.assertRaises(ValueError): update.extract_archive(archive, destination)
            with tarfile.open(archive, 'w:gz') as package:
                link = tarfile.TarInfo('link'); link.type = tarfile.SYMTYPE; link.linkname = '../escape'; package.addfile(link)
            with self.assertRaises(ValueError): update.extract_archive(archive, destination)

    def test_host_target_mapping(self):
        for system, machine, target in [('Windows', 'AMD64', 'x86_64-windows'), ('Darwin', 'arm64', 'aarch64-macos'), ('Linux', 'riscv64', 'riscv64-linux')]:
            with patch.object(update.platform, 'system', return_value=system), patch.object(update.platform, 'machine', return_value=machine):
                self.assertEqual(update.target_identity(), target)
        with patch.object(update.platform, 'machine', return_value='unknown'):
            with self.assertRaises(ValueError): update.target_identity()

    def test_zip_extraction_and_traversal(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary); archive = directory / 'release.zip'; destination = directory / 'home'; destination.mkdir()
            with zipfile.ZipFile(archive, 'w') as package: package.writestr('std/module.lm', 'content')
            update.extract_archive(archive, destination)
            self.assertEqual((destination / 'std/module.lm').read_text(), 'content')
            with zipfile.ZipFile(archive, 'w') as package: package.writestr('../outside', 'bad')
            with self.assertRaises(ValueError): update.extract_archive(archive, destination)

    def test_check_mode_does_not_download_or_install(self):
        with patch.object(update, 'target_identity', return_value='x86_64-linux'), \
             patch.object(update, 'resolve_release', return_value=('v1', {'name': 'release.tar.gz'}, [])), \
             patch.object(update, 'download') as download, patch.object(update, 'install') as install:
            self.assertEqual(update.main(['--check']), 0)
            download.assert_not_called(); install.assert_not_called()

    def test_prefix_from_versioned_installation(self):
        with tempfile.TemporaryDirectory() as temporary:
            prefix = Path(temporary)
            self.assertEqual(update.default_prefix(str(prefix / 'share/lymar/releases/v1')), prefix.resolve())

    @unittest.skipIf(os.name == 'nt', 'POSIX executable fixture; Windows targeting tested separately')
    def test_install_and_activation_failure_preserve_previous_launcher(self):
        payload = archive_bytes([
            ('bin/lymar', b'#!/bin/sh\nif [ "$1" = "--help" ]; then echo Lymar; else echo LYMAR_UPDATE_OK; fi\n', 0o755),
            ('std/string/index.lm', b'// fixture\n', 0o644), ('scripts/update.py', b'# fixture\n', 0o644)])
        with tempfile.TemporaryDirectory(prefix='lymar update spaces ') as temporary:
            prefix = Path(temporary); (prefix / 'bin').mkdir(); launcher = prefix / 'bin/lymar'; launcher.write_text('old launcher')
            with patch.object(update, 'activate', side_effect=OSError('denied')):
                with self.assertRaises(OSError): update.install(prefix, 'v1', 'x86_64-linux', {'name': 'release.tar.gz'}, payload)
            self.assertEqual(launcher.read_text(), 'old launcher')
            home = update.install(prefix, 'v1', 'x86_64-linux', {'name': 'release.tar.gz'}, payload)
            self.assertTrue(home.is_dir())
            result = subprocess.run([str(launcher), '--help'], capture_output=True, text=True, check=True)
            self.assertIn('Lymar', result.stdout)
            with self.assertRaises(ValueError): update.install(prefix, 'v1', 'x86_64-linux', {'name': 'release.tar.gz'}, payload)

    def test_incomplete_release_does_not_activate(self):
        with tempfile.TemporaryDirectory() as temporary:
            prefix = Path(temporary); (prefix / 'bin').mkdir(); launcher = prefix / 'bin/lymar'; launcher.write_text('old launcher')
            payload = archive_bytes([('std/string/index.lm', b'', 0o644)])
            with self.assertRaises(ValueError): update.install(prefix, 'v1', update.target_identity(), {'name': 'release.tar.gz'}, payload)
            self.assertEqual(launcher.read_text(), 'old launcher')

    def test_cli_help_and_bad_option(self):
        for arguments, expected in ((['--help'], 0), (['--unknown-option'], 2)):
            result = subprocess.run([str(ROOT / 'bin/lymar'), 'up', *arguments], capture_output=True, text=True)
            self.assertEqual(result.returncode, expected, result.stdout + result.stderr)

if __name__ == '__main__': unittest.main()
