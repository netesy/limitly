# VM performance checks

Run from the repository root after building `bin/lymar`:

```bash
python3 tests/performance/test_vm_optimizations.py
python3 tests/performance/run_vm_benchmark.py --runs 3 --output /tmp/vm-times.json
python3 tests/precompiled/run_benchmark.py --skip-aot --runs 3
```

The VM benchmark validates each result and measures process wall time, including
parsing and module loading. It temporarily removes the collection shared library
and metadata, restores both on failure, and enables dispatch tracing to reject
native collection calls. Run it sequentially with other tests that rebuild or
move module artifacts. Select individual cases with `--workload NAME`.

The optimized VM reads built-in list/dictionary/string lengths from existing
runtime headers. String lengths remain UTF-8 byte counts. Unsupported types keep
the existing builtin validation path. This avoids recursively copying collection
graphs into frontend values and also handles cyclic containers.

Interpreted calls use registered instructions and type maps directly. Caller
register vectors move aside while a separate reusable vector holds callee values;
recursive calls and captured closures preserve live caller values. Exceptions
restore the caller's register vector and function context. Substring searches use
explicitly sized string views, retaining byte offsets, embedded NUL support and
the existing empty-needle behavior.

These changes do not modify the LIR schema, generator, native API table, tagged
value layout, or exported runtime signatures. Native modules continue using the
existing ABI. Timings are machine-dependent; tests assert results, not speed.

The default font benchmark also attempts Mode C. Its existing static/AOT backend
can stall while compiling the font library; `--skip-aot` validates the working
interpreted, precompiled and C-oracle paths. Validated A/B/D times are printed as
they become available so a Mode C failure does not hide completed measurements.

StringBuilder and std.string.join now call a bulk join builtin through the
existing CallBuiltin instruction and native Helper::Builtin ABI entry. It totals
byte lengths, allocates one output buffer and copies each part once. Queue
removal uses a bulk slice builtin that produces a separate list and preserves
object element identity. Its public items list is still replaced, so snapshots
retain their contents; queue removal remains O(n), but avoids a VM loop per item.
Generic builtin implementations support the same operations on frontend values.

Facade startup avoids a redundant resolve_all pass before the type checker,
which already resolves all imports, and avoids unused concrete syntax trees for
imported modules. Both semantic type-check passes remain in place, including
private-symbol checks, module diagnostics and post-memory-check validation.

On this machine, three-run medians changed from 201 to 5.3 ms for StringBuilder,
125 to 3.6 ms for join, 49 to 18 ms for queue draining, and 102 to 87 ms for the
facade vector workload. These are end-to-end workloads, not complexity promises.
Direct vector imports remain faster because the facade still validates every
imported module. A constant-time queue would require a different representation
or observable public-list behavior and is not part of these ABI-preserving fixes.
