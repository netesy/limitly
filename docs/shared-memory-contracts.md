# Shared memory contracts and implementation status

This change removes the unused `src/memory/runtime.hh` duplicate. It moves the
standalone ownership implementation from the Fyra backend into
`src/memory/aot_runtime.cpp`; necessary allocation, cleanup, resource and reference
validation support remains executable runtime code.

## Authoritative components

- `model.hh` defines ownership/effect facts and generation/lifetime predicates.
  The former C++ templates had no production instantiations and could not prove
  properties of a Lymar AST; they were replaced rather than connected as a false
  safety proof.
- `ownership.hh` / `ownership.cpp` supply the authoritative, AST-inferred binding,
  provenance and callable-effect facts. There is no legacy ownership checker or
  alternate environment-selected interpretation.
- `lir_analysis.hh` infers conservative parameter effects and proves one closed
  local-borrow optimization. Unknown operations produce `Unspecified` effects.
- `contracts.hh` implements shared checked capabilities for VM/native and AOT.
  Identity allocation is atomic across registries, survives reset, and refuses
  wraparound. Creating a reference captures allocation identity. Resolution checks
  liveness, address reuse and write permission; conflicting readers/writers and
  consumption while borrowed fail. Tokens supplied to another registry fail.
  Borrow records belong to a dynamic region instance; scope exit ends them even
  when their allocation was promoted. Intrusive per-region capability lists make
  that cleanup proportional to the exiting region's live references.
- `memory.hh` supplies the allocator used by standalone AOT and VM raw memory.
  It also repairs the alternative typed Region/Linear/Ref wrappers. Telemetry
  remains opt-in through `MemoryManager(enableAudit)` or `setAuditMode`; disabling
  audit avoids constructing `MemoryAnalyzer` and opening `memory.log`.
- `analyzer.hh` supplies that optional telemetry. It is not a safety proof.

VM managed list/frame/string constructors still use their established canonical
object implementations. Graph ownership and finalizer traversal remain adapters
in the VM and standalone heap; this change does not replace every VM constructor
with the C++ typed `Region` wrapper.

## Canonical LIR and ABI

New architecture-independent operations are appended, preserving old opcode
ordinals:

| Operation | Contract |
| --- | --- |
| `RefCreate` | Create a capability for managed object `a`; `imm=0` is read-only, `imm=1` exclusive writable. |
| `RefResolve` | Validate capability `a`, then yield its pointer; `imm=1` additionally requires write permission. |
| `RefMove` | Move a capability to an ancestor region (`imm=0` selects the caller), invalidating the old token. The allocation must already outlive the target. |
| `RefRelease` | End a capability. Releasing twice is an error. |
| `OwnershipConsume` | Change an allocation's identity, refusing active borrows. |

All five have VM dispatch, native helper lowering and standalone Fyra helper
lowering. They are effectful: optimizers cannot delete or hoist validation merely
because the result is unused. Mutation, cleanup, raw memory and callback/resource
operations also retain their effects.

Function parameter/result effects and return-borrow origin are carried in
`LIR_Function`; calls carry argument effects. Serialization version **1** persists
these fields and rejects invalid effect tags/counts/origins and trailing data.
The public native helper ABI is **1**, and generated modules report/check that
constant. Artifact freshness is `lymar-0.0.1-abi1-lir1-ownership-projections`, forcing older
precompiled artifacts to rebuild. Public object headers stay eight bytes, list
and tuple layouts stay 32 bytes, and capability tokens remain one machine word.
The allocator prefix is private and is not the language object ABI.

`RefResolve` yields an internal pointer, not a capability that may safely be
retained forever. Lowering must resolve immediately before access and preserve
borrow/lifetime facts across intervening operations. Ordinary unannotated Lymar
aliases and FFI raw pointers have not all been converted to capabilities.

## Compile-time fast path

A fresh `ListCreate` immediately followed by `RefCreate`, `RefResolve` and
`RefRelease`, with no other token uses, proves the capability cannot conflict,
escape or expire during resolution. That sequence becomes an ordinary pointer
move. An escaping token, intervening operation, permission mismatch or malformed
sequence defeats this proof. General region allocation and destructor execution
cannot disappear just because lexical scopes are known at compile time.

This is deliberately a small proof rule. Function effects for opaque calls remain
unknown; the compiler does not manufacture a whole-program ownership proof.

## Frontend repairs

The compiler now preserves move state across variable shadowing, tracks consuming
function aliases and reassignment, transfers linear ownership through erasure to
`any`, and joins mutually exclusive branch states instead of checking them as
sequential executions. These repairs cover the reproduced audit bypasses and
preserve a valid one-consumption-per-branch program.

Gate B is enabled by default. `ownership.cpp` supplies the authoritative AST
facts used by TypeChecker, MemoryChecker and LIR generation. Binding identities,
branch joins, terminating loop fixed points and body-derived callable effects
replace independent ownership transitions and consuming-name heuristics.
MemoryChecker retains bounds, region annotation and concurrency responsibilities.
The former `LYMAR_UNIFIED_OWNERSHIP` variable no longer selects legacy rules.
The old TypeChecker ownership maps, name-based callable heuristic, separate
MemoryChecker generation/reference tables and dormant proof wrappers have been
removed. Lexical symbol scopes retain `val`/`const` immutability; canonical LIR
and the shared lifetime registry retain cleanup, generation and reference checks.

Higher-order declarations are checked even when unused. Local ownership violations
are errors; effects depending on unknown callback parameters remain obligations
discharged at concrete calls. Opaque calls are not treated as proven safe. Facts,
callable effects and returned-alias provenance survive function registration and
serialized LIR, whose ownership and region contracts are verified before execution
and around optimization. These acceptance results are not a complete static safety
guarantee for every alias, raw pointer or FFI boundary.

## Allocator repairs

Pool expansion is synchronized; alignment and allocation arithmetic are checked.
Over-aligned allocations keep their original malloc base for release. Object
identity changes on address reuse, scope cleanup invokes recorded destructors,
and references/linear wrappers check region lifetime before access. References
borrow their targets instead of destroying them when their last copy disappears.
`Unsafe` uses a persistent allocator, checks zeroing multiplication, and limits
resize copying to the old allocation size.

AOT archive construction now replaces the archive atomically rather than leaving
obsolete object members after a source rename.

## Validation and performance

The added checks exercise stale address reuse, reset, cross-registry tokens,
conflicting borrows, write permission, destructor execution, alignment, resizing,
ownership regressions, serialized effects and actual VM/native/AOT reference
results. Existing region/font/collection tests remain relevant.

A seven-run allocation microbenchmark measured medians of 72.535 ms before and
71.066 ms after for 500,000 standalone allocations/frees. This small difference
is not evidence of a general VM or executable speedup. Compile-time elimination
removes capability overhead only for its proven local case. Language benchmark
results and sanitizer outcomes are recorded separately after validation.

The historical audit in `memory-safety-audit.md` describes the baseline before
this implementation. Raw-pointer/FFI boundaries and exhaustive alias/borrow proofs
remain limits on a full safety claim.
