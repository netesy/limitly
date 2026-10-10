#!/usr/bin/env python3
"""Package an already built distribution in the format consumed by lymar up."""
import argparse
import hashlib
from pathlib import Path
import re
import shutil
import sys
import tarfile
import tempfile
from update import target_identity, smoke_test

def package(root, output, tag, include_precompiled=False):
    if not re.fullmatch(r'[A-Za-z0-9_.-]+', tag) or tag in ('.', '..'):
        raise ValueError('Unsafe release tag')
    target = target_identity()
    extension = '.exe' if target.endswith('-windows') else ''
    output.mkdir(parents=True, exist_ok=True)
    archive = output / f'lymar-{tag}-{target}.tar.gz'
    if archive.exists(): raise ValueError('Release archive already exists')
    with tempfile.TemporaryDirectory(prefix='lymar-release-') as temporary:
        home = Path(temporary)
        (home / 'bin').mkdir()
        shutil.copy2(root / 'bin' / ('lymar' + extension), home / 'bin')
        if (root / 'bin' / ('lyra' + extension)).is_file():
            shutil.copy2(root / 'bin' / ('lyra' + extension), home / 'bin')
        for name in ('liblymar_aot.a', 'liblymar_aot.lib'):
            if (root / 'bin' / name).is_file(): shutil.copy2(root / 'bin' / name, home / 'bin')
        if (root / 'bin/runtimes').is_dir(): shutil.copytree(root / 'bin/runtimes', home / 'bin/runtimes')
        for name in ('lymar_ssl', 'stb_image'):
            for suffix in ('.so', '.dll', '.dylib'):
                library = root / 'bin' / ('lib' + name + suffix)
                if library.is_file(): shutil.copy2(library, home / 'bin')
        if include_precompiled:
            for metadata in (root / 'bin').glob('*.meta'):
                binary = metadata.with_suffix('')
                if binary.suffix not in ('.so', '.dll', '.dylib') or not binary.is_file(): continue
                shutil.copy2(binary, home / 'bin')
                shutil.copy2(metadata, home / 'bin')
        shutil.copytree(root / 'std', home / 'std')
        (home / 'scripts').mkdir()
        shutil.copy2(root / 'scripts/update.py', home / 'scripts/update.py')
        smoke_test(home)
        try:
            with tarfile.open(archive, 'w:gz') as output_tar:
                for path in sorted(home.rglob('*')):
                    output_tar.add(path, arcname=path.relative_to(home), recursive=False)
        except Exception:
            archive.unlink(missing_ok=True)
            raise
    digest = hashlib.sha256(archive.read_bytes()).hexdigest()
    checksum_file = output / 'SHA256SUMS'
    with checksum_file.open('a') as checksums: checksums.write(f'{digest}  {archive.name}\n')
    return archive

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--tag', required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--include-precompiled', action='store_true')
    args = parser.parse_args()
    try:
        print(package(Path(__file__).resolve().parent.parent, args.output, args.tag, args.include_precompiled))
        return 0
    except Exception as error:
        print(f'Release packaging failed: {error}', file=sys.stderr)
        return 1

if __name__ == '__main__': sys.exit(main())
