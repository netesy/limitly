"""Compare real stdlib exports with isolated source/native artifacts.

Native dispatch is checked in an untimed traced run. Five alternating fresh
process pairs then run with fallback disabled and tracing disabled. CPU timing
covers only the source workload; wall timing also includes import and startup.
"""
import argparse
import json
import os
from pathlib import Path
import re
import shutil
import statistics
import subprocess
import tempfile
import time

ROOT = Path(__file__).resolve().parents[2]
cases={
'math':('std.math.arithmetic','std/math/arithmetic.lm','arithmetic','var total=0.0;for(var i=0;i<3000;i=i+1){total=total+mod.sqrt(2.25);}', 'sqrt',3000),
'string':('std.string','std/string/index.lm','string','var total=0;for(var i=0;i<20000;i=i+1){if(mod.contains("the quick brown fox jumps over the lazy dog", "brown")){total=total+1;}}','contains',20000),
'builder':('std.string.builder','std/string/builder.lm','builder','var b=mod.StringBuilder();for(var i=0;i<10000;i=i+1){b.append("abcd");}var total=len(b.to_string());','StringBuilder.append',10000),
'vector':('std.collections.vector','std/collections/vector.lm','vector','var v=mod.Vector();for(var i=0;i<10000;i=i+1){v.push(i);}var total=0;for(var i=0;i<10000;i=i+1){total=total+(v.get(i) as int);}','Vector.push',10000),
'hashmap':('std.collections.hashmap','std/collections/hashmap.lm','hashmap','var v=mod.HashMap();for(var i=0;i<2000;i=i+1){v.put("key-{i}",i);}var total=0;for(var i=0;i<2000;i=i+1){if(v.contains_key("key-{i}")){total=total+1;}}','HashMap.put',2000),
'base64':('std.encoding.base64','std/encoding/base64.lm','base64','var bytes=[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15];var total=0;for(var i=0;i<2000;i=i+1){total=total+len(mod.encode_base64(bytes));}','encode_base64',2000)
}
EXPECTED = {'math': 4500, 'string': 20000, 'builder': 40000,
            'vector': 49995000, 'hashmap': 2000, 'base64': 48000}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--runs', type=int, default=5)
    parser.add_argument('--case', choices=tuple(cases), action='append')
    args = parser.parse_args()
    if args.runs < 1:
        parser.error('--runs must be positive')
    compiler = str(ROOT / 'bin' / ('lymar.exe' if os.name == 'nt' else 'lymar'))
    extension = '.dll' if os.name == 'nt' else ('.dylib' if os.sys.platform == 'darwin' else '.so')
    env = {k: v for k, v in os.environ.items() if k not in (
        'LYMAR_HOME', 'LYMAR_DISABLE_INTERPRETER_FALLBACK', 'LYMAR_TRACE_PRECOMPILED',
        'LD_PRELOAD', 'LYMAR_KEEP_NATIVE_SOURCE')}
    with tempfile.TemporaryDirectory(prefix='lymar-module-benchmark-') as tmp:
        root = Path(tmp)
        for case in args.case or cases:
            module, source, stem, work, export, count = cases[case]
            directory = root / case
            for mode in ('source', 'native'):
                destination = directory / mode
                (destination / 'bin').mkdir(parents=True)
                shutil.copytree(ROOT / 'std', destination / 'std')
            program = directory / 'check.lm'
            program.write_text('import ' + module + ' as mod;\nvar started=clock();\n' + work +
                '\nprint("CPU_MS: {(clock()-started)*1000.0}");print("RESULT: {total}");\n')
            build_start = time.perf_counter()
            built = subprocess.run([compiler, 'build', '-O2', '-shared', source, '-o',
                'bin/lib' + stem + extension], cwd=directory / 'native', env=env,
                text=True, capture_output=True, timeout=180)
            if built.returncode:
                raise RuntimeError(f'{case}: native build failed\n{built.stdout}\n{built.stderr}')
            build_ms = (time.perf_counter() - build_start) * 1000
            data = {mode: [] for mode in ('source', 'native')}
            outputs = []
            for sample in range(args.runs + 1):
                # Alternate ordering to avoid consistently benefiting one mode.
                modes = ('source', 'native') if sample % 2 == 0 else ('native', 'source')
                for mode in modes:
                    run_env = dict(env)
                    if sample == 0:
                        run_env['LYMAR_TRACE_PRECOMPILED'] = '1'
                    if mode == 'native':
                        run_env['LYMAR_DISABLE_INTERPRETER_FALLBACK'] = '1'
                    start = time.perf_counter()
                    result = subprocess.run([compiler, 'run', str(program)],
                        cwd=directory / mode, env=run_env, text=True,
                        capture_output=True, timeout=60)
                    wall = (time.perf_counter() - start) * 1000
                    if result.returncode:
                        raise RuntimeError(f'{case}/{mode}: {result.stdout}\n{result.stderr}')
                    if sample == 0 and mode == 'native':
                        marker = 'PRECOMPILED_CALL: ' + module + '.' + export + '\n'
                        if result.stderr.count(marker) != count:
                            raise RuntimeError(f'{case}: expected {count} native {export} calls')
                    if mode == 'source' and 'PRECOMPILED_CALL:' in result.stderr:
                        raise RuntimeError(f'{case}: source control loaded native code')
                    outputs.append(re.search(r'RESULT: (.+)', result.stdout)[1])
                    cpu = float(re.search(r'CPU_MS: ([0-9.]+)', result.stdout)[1])
                    if sample > 0:
                        data[mode].append({'cpu_ms': cpu, 'wall_ms': wall})
            if len(set(outputs)) != 1:
                raise RuntimeError(f'{case}: source/native output mismatch: {outputs}')
            if float(outputs[0]) != EXPECTED[case]:
                raise RuntimeError(f'{case}: workload result {outputs[0]} is not {EXPECTED[case]}')
            print(json.dumps({'case': case, 'result': outputs[0], 'build_ms': build_ms,
                'validated_native_calls': count, 'samples': data,
                'median_cpu_ms': {mode: statistics.median(row['cpu_ms'] for row in data[mode]) for mode in data},
                'median_wall_ms': {mode: statistics.median(row['wall_ms'] for row in data[mode]) for mode in data}}), flush=True)


if __name__ == '__main__':
    main()
