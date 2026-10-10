# Native computation, runtime calls, and the optimization gate

## What a builtin means

A builtin is compiler-recognized semantics, not a promise to inline or avoid
runtime services. There are four different implementation paths:

| Operation | Hosted native path | Remaining work |
| --- | --- | --- |
| Immediate integer arithmetic | Private native arithmetic with actual-kind/overflow guards | BigInt or unknown kinds retain helpers |
| Eligible float arithmetic | Unboxed private results | Boxing at boundaries; reference-bearing functions retain identity |
| Known string/list/dict length | Direct header read | Unsupported/unknown kinds retain generic semantics |
| Known frame/list/dict accesses | Typed `DirectOperations` runtime call | Permissions, liveness/bounds, mutation and ownership work |
| Contains/prefix/suffix/index-of/byte-at | Typed `DirectOperations` runtime call | Avoids generic dispatch; still a native function-pointer call |
| Many `_builtin_string_*` calls | `api->helper`, then native string implementation | Dispatch remains; allocating results need tracking |
| File/network/FFI/concurrency | Runtime/platform operations | Observable effects cannot generally disappear |

VM builtins execute native C++ implementations through the VM's dispatch path.
Standalone Fyra emits IR bodies for selected builtins, including substring and
byte lookup; those bodies can still allocate or call runtime/platform routines.
Hosted modules and standalone executables must agree semantically without sharing
every instruction or private layout.

### Concrete routing examples

`Emitter::direct_builtin` in `src/backend/native/emitter.cpp` already routes
`_builtin_string_contains`, `_builtin_string_starts_with`, `_builtin_string_ends_with`,
`_builtin_string_index_of`, `_builtin_string_byte_at` and `_builtin_string_byte_len`
through `DirectOperations`. This is typed runtime dispatch, not proof of C++
inlining or a standalone machine instruction. Do not plan to remove generic
dispatch again for operations already using this path.

Hosted `_builtin_substring` still enters `Helper::Builtin`, then calls
`lm_str_substring` and registers the owned result in `abi.cpp`. VM's special path
in `ops/vm_calls.cpp` calls that same native substring routine and registers its
allocation. VM join/list-slice/hash paths currently reuse the hosted helper.
Fyra's `emit_substring_ir` builds its own body, including allocation and copying;
`emit_string_byte_at_ir` builds a byte load. These are three distinct lowering
paths whose observable behavior needs independent parity tests.

### Reproduced safety blocker before wider direct lowering

At HEAD `6bee369`, with the later docs/updater working-tree changes (which do not
alter these backends), this existing-syntax source program:

```lymar
print(_builtin_string_byte_at("A", 1073741824));
```

returns `0` in VM. Standalone Fyra executables segfault at O0, O1 and O2 on the
tested Linux x86-64 host. `emit_string_byte_at_ir` in
`src/backend/fyra/fyra_builtin_functions.cpp` computes a byte address and loads it
without the bounds guard used by `lm_str_byte_at` in `vm_string.cpp`. Actual
generated Fyra IR also contains the unchecked `loadub`.

Reproduce with `lymar run probe.lm`, then `lymar build -O 0 probe.lm -o probe`
and execute the result; repeat with optimization levels 1 and 2. The local probe
used `LYMAR_AOT_LINKER=driver` and `LYMAR_AOT_CXX=tests/memory/aot_linker.py`.
Small invalid indices happened to return zero in both paths and did not expose
the invalid read. Matching those outputs is insufficient evidence of safety.

The current implementation repairs this lowering: negative, nil and out-of-range
receivers exit before the byte load. The standalone call boundary uses the
existing value-kind sidecar to reject erased non-string receivers. Substring
lowering clamps its end and handles negative/reversed ranges like the VM.
`tests/memory/test_builtin_proofs.py` executes real source in VM, hosted native
and standalone Fyra at O0/O1/O2, including large indices, UTF-8, embedded NULs
and erased integers, booleans, floats, lists and nil. This repairs these specific
paths; it is not a blanket safety certification of every builtin.
Erased index conversion follows `as_i64`, including truncating finite floats and
using zero for nonnumeric inputs. Shared conversion now also uses zero for
nonfinite/out-of-range floats, avoiding an undefined C++ float-to-integer cast.
Standalone tuple reads check receiver kind and bounds before loading elements.
Erased indirect calls validate name/closure representation before dereferencing;
noncallables and unresolved names follow the VM's nil-result behavior instead
of executing arbitrary data as machine code. Float results crossing the indirect
dispatch merge retain their boxed kind. Builtin function values still have an
incomplete name-materialization path: assigning `_builtin_string_byte_at` to a
local currently lowers to an uninitialized global instead of a callable name.
This functional gap is distinct from the repaired unsafe indirect dispatch.

## Stdlib inventory and implications

A textual scan of `std/**/*.lm` at commit `6bee369` found 337 `_builtin_*` call
occurrences across 14 names. This is a static source inventory, not an execution
profile; ordinary builtins and FFI calls are additional runtime boundaries.

278 occurrences were `_builtin_substring`, 12 string-from-bytes, and 11 byte-at.
The remaining names were case conversion, contains/prefix/suffix, trimming,
replacement, joining, searching, list slicing, and byte hashing. Occurrences
include duplicated facade/implementation sources and do not predict runtime cost.

Replacing all runtime calls with inline language functions is not a sound goal.
Inlining removes a call boundary, not required allocation, destruction, OS effects,
locking, bounds checks, BigInt behavior, or FFI lifetimes. Reimplementing substring
with repeated string concatenation could make its algorithm worse.

Use direct numeric/length/byte operations where semantics are known. Give search,
hashing and predicates shared native algorithms without frontend `Value` conversion.
Retain one native allocation path for owned substring/join/replace results. For a
substring used only in an adjacent comparison now has a conservative fused-byte
predicate proof described below. General parser lookahead and borrowed views still
need additional lifetime proofs. No source syntax change is required.

Current hot font code also uses `ByteReader.read_u8/read_u16`, frame fields and
ordinary LIR operations. Most `_builtin_substring` source occurrences are therefore
not an explanation for the measured font-width bottleneck.

## Measured baseline

For the matched 1,000-call width workload, checksum 466750 was preserved. Private
numeric/pair lowering reduced allocation requests from 2,817,175 to 1,460,175 and
requested bytes from 161,281,929 to 64,479,929. These are allocation-request totals,
not live or peak memory. Instrumented native width execution counted zero arithmetic
helpers and tuple allocation helpers, but 15,284,000 region operations and 3,698,000
checked frame accesses. Counters are not a CPU-time attribution.

Timing batches disagreed. The last five-run alternating medians were 997.579 ms
before and 1037.88 ms after. No stable speedup or STB pixel-performance parity was
established. Precompilation packages native code; it cannot make runtime-heavy
generated computation efficient by itself. Static linking offers packaging and
optimization opportunities, not an automatic cure.

## Revised surgical sequence

0. **Restore builtin safety parity.** Repair the reproduced unchecked Fyra byte
   access before broader direct lowering. Audit substring boundary/clamping behavior
   and atomic frame ordering with explicit source tests; do not assume either is
   correct because ordinary valid-input tests pass. Mark known operations checked
   or proven safe rather than treating every generated IR body as a trusted leaf.
1. **Attribute work and define effects.** Split region counts into lexical
   enter/exit, native-call enter/leave, tracking and promotion by function. Separate
   frame checks from field loads. Derive allocation, invalidation, cleanup, callback,
   escape and concurrency effects from canonical LIR and known callees. Use a finite
   fixed point for recursion. Unknown calls remain conservative. Existing ownership
   summaries alone are not allocation or cleanup proofs.
2. **Remove proven scalar promotions first.** Prove actual value kind and valid
   active target on every CFG path. Immediate scalars have no allocation graph.
   Retain target errors where validity is not proven; annotations and erased `any`
   are insufficient. This is separate from eliminating a scope's region.
3. **Extend region proof to borrowed leaves.** Accept parameterized borrowed reads
   only with proven owner lifetimes and no scope-owned allocation, destruction,
   reference invalidation, escape or unknown call. Prove native-call cleanup
   unnecessary separately; it promotes return graphs and unwinds remaining scopes.
   Arithmetic overflow can allocate, so integer annotations are not enough.
4. **Validate frame views once per valid interval.** Known layout and constant
   indices establish bounds. Owner/reference facts establish liveness and permission.
   Reuse the fields pointer until an operation can invalidate it. Receiver validity
   does not establish stable field contents. Unknown callbacks/FFI/destruction kill
   the proof unless their effects establish otherwise.
5. **Lower proven accesses and fuse safe byte predicates.** Preserve canonical
   frame operations while giving backends recomputable verified proof information.
   Hosted native code uses direct field loads; VM avoids redundant checks and Fyra
   lowers equivalent accesses. Scalar-replace eligible local frames; retain exported
   tagged objects. Use borrowed views/fused comparisons only after their lifetime
   and error/output semantics are proven.
6. **Optimize representation and algorithms separately.** Typed private signatures,
   byte-oriented storage and rasterizer changes need their own measurements. Preserve
   reusable canonical LIR and verified native artifacts behind normal imports. Offer
   static linking for deployment/whole-program opportunities after computation is
   efficient.

Proofs must be checked before optimization and recomputed/invalidated after relevant
transformations or deserialization. Do not enable the quarantined alias-sensitive
store elimination or LICM implementations as a shortcut.

Frame access can have zero **validation overhead** for proven cases, not zero
memory-access cost. Current fields-pointer indirection remains unless scalar
replacement removes it. Atomic accesses are not candidates for ordinary loads:
Fyra currently groups atomic get/set with non-atomic lowering in `builder.cpp`;
atomicity and ordering need explicit backend tests before extending this work to
concurrent fields.

Each stage must pass source-based positives/negatives, stale references, alias
mutation, recursion, early returns, errors, finalizers, FFI reentrancy and worker
lifetime tests. Require VM/Fyra O0/O1/O2, hosted native, serialized restoration,
sanitizers, artifact checks, matching outputs, emitted-code evidence and measured
operation reductions. No proof means retaining the safe path.

The implemented phase supplies conservative effects, scalar-promotion removal,
fresh-frame views and adjacent substring predicates. General region and frame-check
elimination still require additional proofs.

### Implemented conservative proof boundaries

`src/memory/effect_analysis.hh` recomputes finite, monotone call effects from
canonical LIR, including recursive calls. Unknown operations and indirect calls
retain all effects; retention and consumption block frame-view reuse. Its
caller-object query is not a proof that a callee's own regions can disappear.
Field stores conservatively publish aliases unless CFG value provenance proves
the stored value immediate. This does not rely solely on frontend retention flags.

Scalar graph promotions are removed only when CFG dataflow proves an immediate
integer, boolean or nil on every incoming path. Full LIR verification precedes
elimination, preserving invalid-target diagnostics. Unused parameters no longer
prevent a closed constant-return body from proving region management unnecessary;
used or erased parameters still cannot establish scalar provenance by annotation.

Hosted frame views reuse the fields address only for fresh, unpublished frames
within a straight-line interval. The first checked read establishes permission,
liveness and bounds; subsequent equal/lower field indices use direct loads.
Mutation, control-flow joins, region operations and unknown calls kill the view.
Borrowed and atomic receivers retain their checked paths.

A substring used solely by the immediately following equality/inequality can
compare its clamped byte range directly, without constructing an owned temporary.
Both runtime operands must be strings; unknown kinds retain the original helper.
Escaped, retained, identity-observed or multiply-used results are not fused.
Reference operations and intervening effects prevent this proof. These private
lowering choices add neither LIR instructions nor public ABI fields.

The LIR round-trip suite tests positive and adversarial proof conditions; the
source suite also checks generated hosted C++ for retained barriers and direct
loads. General borrowed-region elimination, atomic backend parity, stack frame
placement and broad lifetime-check elimination remain separate work.

### Targeted measurements and validation

On Linux x86-64, seven alternating O2 hosted runs of 20,000 substring comparisons
returned the identical count, 20,000, with interpreter fallback disabled. Median
source-timed CPU time fell from 18.580 ms to 13.511 ms (27.3%). The comparison used
the emitter built from HEAD `6bee369` versus the new emitter in the same current
host; this isolates native lowering rather than comparing two complete compiler
revisions. Compilation and import time are outside the timed loop.

Separate malloc/calloc/realloc instrumentation between the workload's clock
snapshots counted 120,051 versus 51 allocation requests and 5,427,629 versus
7,653 requested bytes. These totals include workload overhead, exclude imports,
and are neither peak memory nor an allocation-free claim for general strings.
This is a substring-predicate microbenchmark, not evidence of font/STB parity.

Reproduce with a baseline compiler built from the earlier emitter:

```sh
python3 tests/precompiled/run_proof_benchmark.py --baseline /path/to/baseline/lymar --runs 7
python3 tests/memory/test_builtin_proofs.py -v
make linux lir-test memory-tests aot-region-tests
```

The source proof suite verifies VM, standalone Fyra and hosted execution at
O0/O1/O2, plus generated direct loads and retained mutation/publication barriers.
The final language run passed 102 cases; precompiled regressions passed 33 cases;
all 10 artifact compatibility cases passed. ASan/UBSan runs passed the 80 ownership
cases, frontend, serialization, reference, region, runtime and new builtin tests.

An existing concurrent raw-worker probe remains intermittent despite its individual
suite passing. A controlled VM comparison restored HEAD's optimizer, emitter and
value conversion: 7/200 baseline runs and 6/200 current runs failed the sum assertion.
A temporary diagnostic probe observed missing channel results (six/seven instead
of eight), while worker exceptions are swallowed in `ops/concurrency.cpp`.
This does not establish the underlying race's cause and is a blocker to claiming
complete memory safety. No timeout or negative diagnostic was weakened.

**Next gate:** widen borrowed-frame/lifetime proofs and validate atomic backend
semantics, and diagnose the concurrent worker failure before broad check elimination.
Shared semantics are authoritative;
inline code, direct runtime calls and backend IR are implementation choices.
