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
dispatch merge retain their boxed kind. Builtin function values also exposed an incomplete name-materialization path:
assigning `_builtin_string_byte_at` to a local lowered to an uninitialized global.
The callable-adapter repair described below closes this functional gap separately
from the unsafe indirect-dispatch repair.

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
VM, hosted native and standalone Fyra now retain sequentially consistent atomic
loads/stores and serialized numeric/string read-modify-write operations. These
operations remain checked runtime effects, never ordinary cached frame loads.

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

Hosted frame views reuse the fields address for fresh, unpublished frames,
verified read-only borrowed parameters, and successfully resolved references
within a straight-line interval. The first checked read establishes permission,
liveness and bounds; subsequent equal/lower field indices use direct loads.
Mutation, control-flow joins, region operations and unknown calls kill the view.
Every view begins with a checked access. Atomic receivers retain checked atomic
operations; unknown lifetime and callable effects terminate the view.

A substring used solely by the immediately following equality/inequality can
compare its clamped byte range directly, without constructing an owned temporary.
Both runtime operands must be strings; unknown kinds retain the original helper.
Escaped, retained, identity-observed or multiply-used results are not fused.
Reference operations and intervening effects prevent this proof. These private
lowering choices add neither LIR instructions nor public ABI fields.

The LIR round-trip suite tests positive and adversarial proof conditions; the
source suite also checks generated hosted C++ for retained barriers and direct
loads. General borrowed-region elimination, stack frame placement and broad
lifetime-check elimination remain separate work.

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


### Follow-up: borrowed views, atomic parity and builtin values

The concurrent raw-worker failure above was reproduced as a resize/registry race.
`realloc` could free an address before its old record was retired, allowing a
second worker to allocate that address and have its new record erased. Resize,
alias invalidation and registry retirement now share one raw-registry critical
section; allocation registration outside that section preserves heap lock order.
Stop/Continue worker failures surface at the join instead of disappearing.

The frame-view proof accepts stable read-only parameter bindings and resolved
reference origins. Mutation, consumption, reference release/move, branches and
opaque calls remain barriers. Verified source mutation and callable effects infer writable binding identities;
only those bindings receive writable capabilities. Field/index stores, mutable
call arguments and append receivers request write resolution. Canonical
verification also tracks read/write resolution through pointer copies and CFG joins, rejecting stores through a
read-resolved pointer, including after deserialization.

Builtin values materialize as conservative canonical callable adapters. Their
parameters retain erased kinds, their bodies use existing `CallBuiltin` and
`Return` operations, and normal registration/serialization supplies all backends.
Returned callable expressions use existing `CallIndirect`. No public ABI table,
serialized format or LIR instruction was added.

Atomic field RMW uses the generator's existing receiver/index/value convention.
It applies shared checked integer semantics, preserves float/string kinds, and
registers/promotes managed results before publication. Source task lowering now
balances concurrency contexts and snapshots captured registers that overlap
scheduler inputs into existing private task-context slots. Capture kinds and
stable source provenance survive remapping; void operations no longer rewrite
parameter types. Legacy cached objects without dependency files are refreshed
before linking, preventing obsolete AST layouts from corrupting compiler memory.

`tests/memory/test_remaining_blockers.py` exercises real source programs through
VM and standalone Fyra at O0/O1/O2, hosted builtin dispatch with fallback disabled,
worker capture kinds, atomic overflow, negative callable arity and worker errors,
and repeated concurrent raw resize. `test_runtime_lifetimes.cpp` includes a
contended atomic field test; the serialization test includes builtin values.

These checks establish the tested contracts, not a complete memory-safety proof.
Standalone Fyra now executes structured tasks on bounded native worker threads.
A source rendezvous test requires simultaneous workers rather than merely
checking final output. Arbitrary unsafe pointers/FFI, all target toolchains,
and general interprocedural lifetime/check elimination require separate evidence.
Unsafe LICM and alias-sensitive store elimination remain quarantined.

The style-color conflict in `std.game.gui.GUI.button` is now repaired without
relaxing `LifetimeRegistry` exclusivity. Authoritative analysis collects binding
uses across nested statements and the existing loop fixed point. A lease ends
after its block-local binding's last statement use; a nested block never ends an
enclosing binding's lease. Aliases, stored/retained values, opaque/consuming calls,
and closure captures conservatively retain lexical leases. Generation emits
existing nullable `RefRelease` and clears the handle for reassignment cleanup.
Region ownership, finalizers and destruction are unchanged. The generated
release survives registration and serialization and is checked by mandatory
LIR verification. The full language suite, including expanded IMGUI, passes.

Hosted frame views can also share the first checked address across local copies
and repeated resolution of the same capability within a safe interval. Every
reference resolution still executes; mutation, release/move, region transitions,
branches and unknown calls stop reuse. Source tests inspect emitted native code
and exercise resolved reads, mutation barriers, branches, loops and captures.
Cached addresses are keyed by their establishing instruction, not by a mutable
register number. Rebinding a receiver cannot overwrite a surviving alias's
view; redefining a resolved pointer invalidates its capability-to-view mapping.
Focused regressions cover both hazards.
The raw-worker regression varies 1/2/4/8 cores and O0/O1/O2; Partial-policy failure
tests include raw allocations that require unwinding cleanup.

A further source probe exposed captured parent capabilities being resolved in
the worker's empty lifetime registry. Read resolution now searches only the
structured VM ancestry under each owner's heap lock, then performs the original
generation/permission check. Ancestor capabilities cannot be upgraded to writes,
moved or released by workers; unrelated VMs still reject them. This is scoped
read delegation during the join, not global capability-table lookup. Source
VM/Fyra tests cover captured borrowed frames, and runtime tests reject a token
from an unrelated VM.
Capability registers are captured as well as value registers. Reserved low
slots use the existing task-context snapshot slots; high handles extend the
private captured prefix. Each task/worker restores the enclosing reference map
after lowering. A `TaskGetField` capability load establishes an unknown token,
not a static validity proof, so resolution checks remain mandatory. The source
serialization regression includes a low-slot borrowed-list worker capture.

Captured scalar `atomic` bindings now hold private shared cells. Reads, stores,
and add/sub compound updates use the existing atomic frame operations; captures
retain cell identity instead of copying the integer. Shadowed bindings have
distinct cells. The source suite checks shared closure updates and generated LIR
through VM and standalone Fyra O0/O1/O2. Other atomic compound operators are
currently rejected rather than lowered to an unsafe load/compute/store sequence.

Authoritative callable summaries now preserve captured mutation effects, including
aliases and returned-alias origins. Task analysis rejects mutation of enclosing
non-atomic bindings through closures, higher-order calls and erased callables.
Assignment to copied scalar parameters remains legal. These effects survive
registration and serialization, and mandatory verification rejects undeclared
mutated captures. No new syntax, LIR instruction or public ABI field is added;
experimental serialized artifacts must be rebuilt for the added semantic facts.

Standalone scheduling uses synchronized shared allocation/reference metadata and
thread-local invocation/region state. Task contexts snapshot both low and high
captured registers. Captured capabilities retain read-only delegation; foreign
worker writes, moves and releases remain forbidden. Native channels synchronize
queue contents and erased value kinds. Workers join before captured regions can
retire. Worker failures propagate explicitly through generated control flow so
cleanup does not depend on C++ unwinding across generated machine frames.
Source tests cover raw allocations, Stop/Continue/Partial error policies, and
finalizers during failed-worker cleanup. Timeouts are cooperative: an opaque
blocking FFI call cannot be forcibly interrupted, and all started workers must
still join. Native thread availability on other targets, including Wasm, needs
separate validation. These checks do not establish complete memory safety.
Broad check elimination remains deferred; unsafe optimizations remain quarantined.

The serialized borrowed-worker regression also exposed a Fyra register-allocation
bug: a late-layout scheduler branch reused a spill home for a register-slot
address still live into an earlier-layout join. A metadata call overwrote that
home and cleanup then wrote through a null address. Fyra's liveness analysis
already computes CFG-aware live-before/live-after sets; its bounding allocation
intervals now include those sets rather than only explicit-use positions and
loop latches. The independent allocator regression fails on the unchanged Fyra
baseline and passes with this repair. The repair lives in the independent Fyra repository, published before Lymar
updates its gitlink. No Lymar AST or ownership-checker dependency is introduced
into Fyra.

Fyra's loop-unroll legality check now accepts a verified linear iteration path
with a separate latch block. Both main and remainder clones include every block
on that path; interior branches, interior PHIs and exits remain excluded. The
independent multi-accumulator regression and full codegen suite pass. This
repair does not enable Lymar's quarantined LICM or store elimination.

Worker guard insertion updates PHIs only on transferred successor edges. Fyra
liveness solves the authoritative dataflow with a predecessor worklist,
preserving the same transfer equations and CFG-aware spill intervals. Per-instruction sets use dense
value indices and are materialized once after the block fixed point. A separate
set-based test oracle checks before/after queries on loop and PHI values. The
older block-set solver and its private maps had no consumers and are removed.
Acyclic functions skip loop-latch discovery after a complete topological proof.
Dominator intersections use dense bitsets with the same transfer equations,
avoiding individual tree-node allocations. The fixed point visits all CFG
components in reverse postorder instead of physical layout order. Set depths
and pointer-order indices are cached within the analysis. An independent
set-based oracle checks the dominance relation on the branch/loop/Phi fixture.
Immediate-dominator selection
verifies the deepest strict-dominator candidate once and retains the original
search when that proof fails. These changes address compiler analysis cost from
large checked-call CFGs; they remove no runtime permission or lifetime checks.
The independent reverse-layout regression keeps a value live through 1,000
out-of-order blocks, alongside the existing loop and PHI regressions.

### Current validation boundary

The normal memory gate passes runtime/contracts, LIR round-trip, 15 frontend,
80 ownership, source-to-serialized VM/Fyra O0/O1/O2, reference lowering, two
builtin proofs, 11 blocker tests and seven concurrency tests. The language gate
passes 102 programs, standalone region tests pass ten cases, and hosted native
ABI/numeric tests pass four cases. All ten artifact compatibility cases pass.
The independent Fyra codegen suite passes,
including the liveness and dominance oracles and multi-block loop unrolling.

ASan/UBSan passes the runtime/contracts, LIR, frontend, 80 ownership, reference,
builtin, 11 blocker and seven concurrency tests. The full serialized-source
fixture still exceeds its unchanged 120-second limit during Fyra O2 compilation;
its VM execution and Fyra O0/O1 stages complete. Therefore the complete sanitizer
gate remains blocked. These targeted repairs do not establish complete memory
safety. Compiler analysis latency in this instrumented fixture, other target
execution, opaque FFI interruption and broader lifetime proofs remain priorities.
