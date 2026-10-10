#!/usr/bin/env python3
"""Verified GitHub release installation; activation never replaces a running binary."""
import argparse
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import platform
import re
import shlex
import shutil
import subprocess
import sys
import tarfile
import tempfile
import urllib.parse
import urllib.request
import zipfile

MAX_DOWNLOAD = 1024 * 1024 * 1024

def download(url, limit=MAX_DOWNLOAD):
    if urllib.parse.urlsplit(url).scheme != 'https':
        raise ValueError('Release downloads require HTTPS')
    request = urllib.request.Request(url, headers={'User-Agent': 'lymar-up/0.0.1', 'Accept': 'application/vnd.github+json'})
    with urllib.request.urlopen(request, timeout=60) as response:
        if urllib.parse.urlsplit(response.geturl()).scheme != 'https':
            raise ValueError('Insecure release redirect')
        payload = response.read(limit + 1)
        if len(payload) > limit:
            raise ValueError('Release response exceeds size limit')
        return payload

def target_identity():
    systems = {'Linux': 'linux', 'Darwin': 'macos', 'Windows': 'windows'}
    architectures = {'x86_64': 'x86_64', 'amd64': 'x86_64', 'aarch64': 'aarch64', 'arm64': 'aarch64', 'riscv64': 'riscv64'}
    try:
        return architectures[platform.machine().lower()] + '-' + systems[platform.system()]
    except KeyError:
        raise ValueError('No supported native release target for this host')

def resolve_release(repository, version, target):
    if not re.fullmatch(r'[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+', repository):
        raise ValueError('Repository must be OWNER/REPO')
    endpoint = 'latest' if version is None else 'tags/' + urllib.parse.quote(version, safe='')
    release = json.loads(download(f'https://api.github.com/repos/{repository}/releases/{endpoint}', 4 * 1024 * 1024))
    if release.get('draft') or (version is None and release.get('prerelease')):
        raise ValueError('Latest update must be a published stable release')
    tag = release['tag_name']
    if not re.fullmatch(r'[A-Za-z0-9_.-]+', tag) or tag in ('.', '..'):
        raise ValueError('Unsafe release tag')
    assets = release.get('assets', [])
    names = {f'lymar-{target}.tar.gz', f'lymar-{target}.zip', f'lymar-{tag}-{target}.tar.gz', f'lymar-{tag}-{target}.zip'}
    matches = [asset for asset in assets if asset['name'] in names]
    if len(matches) != 1:
        raise ValueError(f'Release {tag} must contain exactly one complete archive for {target}; found {len(matches)}')
    return tag, matches[0], assets

def verify_payload(payload, asset, assets):
    digest = asset.get('digest') or ''
    if digest.startswith('sha256:'):
        expected = digest[7:]
    else:
        checksum_assets = [item for item in assets if item['name'] == 'SHA256SUMS']
        if len(checksum_assets) != 1:
            raise ValueError('Release needs a SHA-256 asset digest or SHA256SUMS')
        matches = []
        for line in download(checksum_assets[0]['browser_download_url'], 1024 * 1024).decode('utf-8').splitlines():
            fields = line.split(maxsplit=1)
            if len(fields) == 2 and fields[1].lstrip('*') == asset['name']:
                matches.append(fields[0])
        if len(matches) != 1:
            raise ValueError('Missing or ambiguous archive checksum')
        expected = matches[0]
    if not re.fullmatch(r'[0-9a-fA-F]{64}', expected) or hashlib.sha256(payload).hexdigest() != expected.lower():
        raise ValueError('Release SHA-256 mismatch')

def extract_archive(archive, destination):
    total = 0
    count = 0
    def checked_path(name, size):
        nonlocal total, count
        path = PurePosixPath(name)
        if path.is_absolute() or '..' in path.parts or '\\' in name or ':' in name:
            raise ValueError('Unsafe archive path')
        total += size
        count += 1
        if size < 0 or total > MAX_DOWNLOAD or count > 20000:
            raise ValueError('Archive exceeds extraction limits')
        return destination.joinpath(*path.parts)
    if zipfile.is_zipfile(archive):
        with zipfile.ZipFile(archive) as package:
            for member in package.infolist():
                mode = member.external_attr >> 16
                if mode & 0o170000 not in (0, 0o100000, 0o040000):
                    raise ValueError('Archive links and special files are unsupported')
                path = checked_path(member.filename, member.file_size)
                if member.is_dir(): path.mkdir(parents=True, exist_ok=True); continue
                path.parent.mkdir(parents=True, exist_ok=True)
                with package.open(member) as source, path.open('wb') as output: shutil.copyfileobj(source, output)
                path.chmod(0o755 if mode & 0o111 else 0o644)
    else:
        with tarfile.open(archive, 'r:*') as package:
            for member in package:
                if not member.isfile() and not member.isdir():
                    raise ValueError('Archive links and special files are unsupported')
                path = checked_path(member.name, member.size)
                if member.isdir(): path.mkdir(parents=True, exist_ok=True); continue
                path.parent.mkdir(parents=True, exist_ok=True)
                with package.extractfile(member) as source, path.open('wb') as output: shutil.copyfileobj(source, output)
                path.chmod(0o755 if member.mode & 0o111 else 0o644)

def smoke_test(home):
    binary = home / 'bin' / ('lymar.exe' if os.name == 'nt' else 'lymar')
    for required in (binary, home / 'std/string/index.lm', home / 'scripts/update.py'):
        if not required.is_file(): raise ValueError(f'Incomplete release: missing {required.relative_to(home)}')
    environment = dict(os.environ, LYMAR_HOME=str(home))
    result = subprocess.run([str(binary), '--help'], env=environment, capture_output=True, text=True, timeout=30)
    if result.returncode or 'Lymar' not in result.stdout: raise ValueError('Release compiler help check failed')
    with tempfile.TemporaryDirectory(prefix='lymar-up-smoke-') as temporary:
        source = Path(temporary) / 'smoke.lm'
        source.write_text('import std.string as strings;\nassert(strings.starts_with("lymar", "ly"));\nprint("LYMAR_UPDATE_OK");\n')
        result = subprocess.run([str(binary), 'run', str(source)], env=environment, capture_output=True, text=True, timeout=30)
        if result.returncode or result.stdout.strip() != 'LYMAR_UPDATE_OK': raise ValueError('Release compiler execution check failed')

def activate(prefix, home):
    binary = home / 'bin' / ('lymar.exe' if os.name == 'nt' else 'lymar')
    launchers = prefix / 'bin'
    launchers.mkdir(parents=True, exist_ok=True)
    # Bash launchers match scripts/install.sh, including MSYS2 installations.
    text = '#!/usr/bin/env bash\nexport LYMAR_HOME=' + shlex.quote(home.as_posix()) + '\nexec ' + shlex.quote(binary.as_posix()) + ' "$@"\n'
    descriptor, temporary = tempfile.mkstemp(prefix='.lymar-up-', dir=launchers)
    try:
        with os.fdopen(descriptor, 'w') as output: output.write(text)
        os.chmod(temporary, 0o755)
        os.replace(temporary, launchers / 'lymar')
    finally:
        if os.path.exists(temporary): os.unlink(temporary)

def install(prefix, tag, target, asset, payload):
    releases = prefix / 'share/lymar/releases'
    releases.mkdir(parents=True, exist_ok=True)
    # Repository/tag names can be reused: isolate by actual archive digest.
    destination = releases / f'{tag}-{target}-{hashlib.sha256(payload).hexdigest()}'
    if destination.exists():
        raise ValueError('This release is already installed; existing files will not be overwritten')
    with tempfile.TemporaryDirectory(prefix='.staging-', dir=releases) as temporary:
        archive = Path(temporary) / asset['name']
        archive.write_bytes(payload)
        home = Path(temporary) / 'home'
        home.mkdir()
        extract_archive(archive, home)
        smoke_test(home)
        home.rename(destination)
    try:
        activate(prefix, destination)
    except Exception:
        shutil.rmtree(destination)
        raise
    return destination

def default_prefix(current_home):
    if current_home:
        home = Path(current_home).resolve()
        for candidate in (home, *home.parents):
            if candidate.name == 'lymar' and candidate.parent.name == 'share':
                return candidate.parent.parent
    return Path.home() / '.local'

def main(argv=None):
    parser = argparse.ArgumentParser(description='Update Lymar from a verified GitHub release (Python 3.9+, Bash/MSYS2 launcher).')
    parser.add_argument('--repo', default='lymarlang/lymar', help='GitHub OWNER/REPO (default: lymarlang/lymar)')
    parser.add_argument('--version', help='Exact release tag; default is latest stable release')
    parser.add_argument('--prefix', type=Path, help='Installation prefix; defaults to current installation or ~/.local')
    parser.add_argument('--check', action='store_true', help='Show available release without installing')
    parser.add_argument('--current-home', help=argparse.SUPPRESS)
    args = parser.parse_args(argv)
    try:
        target = target_identity()
        tag, asset, assets = resolve_release(args.repo, args.version, target)
        if args.check:
            print(f'{args.repo}: {tag} ({target}, {asset["name"]})')
            return 0
        payload = download(asset['browser_download_url'])
        verify_payload(payload, asset, assets)
        home = install((args.prefix or default_prefix(args.current_home)).resolve(), tag, target, asset, payload)
        print(f'Installed {tag} at {home}; use the prefix/bin/lymar launcher. Previous installations were retained.')
        return 0
    except Exception as error:
        print(f'Lymar update failed: {error}', file=sys.stderr)
        return 1

if __name__ == '__main__':
    sys.exit(main())
