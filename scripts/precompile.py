"""Build hosted and standalone module artifacts without shell-specific recipes.

Explicit precompile requests rebuild both artifacts: the compiler owns dependency
validation, and a timestamp on index.lm alone cannot validate imported modules.
"""
import argparse
from pathlib import Path
import subprocess
import sys


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', required=True)
    parser.add_argument('--output-dir', required=True)
    parser.add_argument('--platform', choices=('windows', 'linux', 'macos'), required=True)
    parser.add_argument('--artifacts', choices=('shared', 'static'), nargs='+', default=['shared', 'static'])
    parser.add_argument('--modules', nargs='+', required=True)
    args = parser.parse_args(argv)
    compiler = str(Path(args.compiler).resolve())
    destination = Path(args.output_dir)
    destination.mkdir(parents=True, exist_ok=True)
    shared = {'windows': '.dll', 'linux': '.so', 'macos': '.dylib'}[args.platform]
    static = '.lib' if args.platform == 'windows' else '.a'
    for module in args.modules:
        if not module.startswith('std.') or not all(part.isidentifier() for part in module.split('.')):
            parser.error(f'invalid standard module: {module}')
        source = Path(*module.split('.'))
        source = source / 'index.lm' if source.is_dir() else source.with_suffix('.lm')
        if not source.is_file():
            parser.error(f'module source does not exist: {source}')
        for artifact in args.artifacts:
            kind, extension = ('-shared', shared) if artifact == 'shared' else ('-static', static)
            output = destination / ('lib' + module.split('.')[-1] + extension)
            print(f'[PRECOMPILE] {module} -> {output}', flush=True)
            subprocess.run([compiler, 'build', '-target', args.platform, kind,
                            str(source), '-o', str(output)], check=True)
            if not output.is_file() or not Path(str(output) + '.meta').is_file():
                raise RuntimeError(f'compiler did not produce artifact and metadata: {output}')
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (subprocess.CalledProcessError, OSError, RuntimeError) as error:
        print(f'Precompilation failed: {error}', file=sys.stderr)
        sys.exit(1)
