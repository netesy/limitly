"""Compare hosted substring fusion with a supplied baseline compiler.

Both artifacts execute in the current host, with interpreter fallback disabled.
Build/import work is outside the source-timed workload. Optional LD_PRELOAD
instrumentation is run separately from the timing samples.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import statistics
import sys
import tempfile

from run_benchmark import ROOT, measure_run, preserve_artifacts


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--baseline', required=True, type=Path)
    parser.add_argument('--compiler', type=Path, default=ROOT / 'bin/lymar')
    parser.add_argument('--runs', type=int, default=5)
    parser.add_argument('--iterations', type=int, default=20000)
    parser.add_argument('--preload', type=Path)
    args = parser.parse_args()
    if args.runs < 1 or args.iterations < 1:
        parser.error('runs and iterations must be positive')
    extension = '.dll' if os.name == 'nt' else ('.dylib' if sys.platform == 'darwin' else '.so')
    with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='substring_proof_') as temporary:
        folder = Path(temporary); name = folder.name
        module = folder / (name + '.lm')
        module.write_text('''fn same_slice(text:str, first:int, last:int, needle:str):bool {
    return _builtin_substring(text,first,last)==needle;
}
pub fn batch(text:str, needle:str, repetitions:int):int {
    var count=0; var i=0;
    while(i<repetitions){ if(same_slice(text,2,8,needle)){count=count+1;} i=i+1; }
    return count;
}
''')
        check = folder / 'check.lm'
        check.write_text(f'''import build.{name}.{name} as p;
var began=clock(); var count=p.batch("ABCDEFGHIJ","CDEFGH",{args.iterations});
var elapsed=(clock()-began)*1000.0;
assert(count=={args.iterations}); print("RESULT: {{count}}"); print("CPU_MS: {{elapsed}}");''')
        library = ROOT / 'bin' / ('lib' + name + extension)
        metadata = Path(str(library) + '.meta')
        results = {label: {'samples_ms': [], 'compiler_sha256': hashlib.sha256(compiler.read_bytes()).hexdigest()}
                   for label, compiler in [('before', args.baseline.resolve()), ('after', args.compiler.resolve())]}
        command = [str(args.compiler.resolve()), 'run', str(check)]
        env = dict(os.environ, LYMAR_DISABLE_INTERPRETER_FALLBACK='1')
        with preserve_artifacts([library, metadata]):
            for label, compiler in [('before', args.baseline), ('after', args.compiler)]:
                measure_run([str(compiler.resolve()), 'build', '-shared', '-O', '2',
                             str(module.relative_to(ROOT)), '-o', str(library)])
                shutil.copyfile(library, folder / (label + extension))
                shutil.copyfile(metadata, folder / (label + '.meta'))
            def activate(label):
                shutil.copyfile(folder / (label + extension), library)
                shutil.copyfile(folder / (label + '.meta'), metadata)
            for _ in range(args.runs):
                for label in ('before', 'after'):
                    activate(label)
                    _, output, _ = measure_run(command, env)
                    if f'RESULT: {args.iterations}\n' not in output:
                        raise RuntimeError('mismatched output: ' + output)
                    results[label]['samples_ms'].append(float(output.split('CPU_MS: ')[1].splitlines()[0]))
            for label in ('before', 'after'):
                activate(label)
                validation = dict(env, LYMAR_TRACE_PRECOMPILED='1')
                if args.preload:
                    validation['LD_PRELOAD'] = str(args.preload.resolve())
                _, output, trace = measure_run(command, validation)
                if f'.{name}.batch' not in trace:
                    raise RuntimeError('native dispatch not demonstrated: ' + trace)
                results[label]['median_ms'] = statistics.median(results[label]['samples_ms'])
                results[label]['validation_output'] = output
                results[label]['validation_trace'] = trace
        print(json.dumps(results, indent=2))


if __name__ == '__main__':
    main()
