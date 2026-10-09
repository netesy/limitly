# Memory model implementation audit

Historical baseline: commit `b4909d6`. Subsequent implementation and remaining
limits are documented in [shared-memory-contracts.md](shared-memory-contracts.md).

Audit date: 2026-10-08. Repository: Lymar `dev`, including the pending Param/file
lowering and target runtime-linking fixes. The audit does not change the memory
model, LIR format, reference representation, or public object ABI.

**The current implementation does not establish the full safety guarantee
described by the memory model.** It implements useful static move checks and
tested region ownership/reclamation, but does not implement end-to-end checked
generational references. Several static checks can be bypassed. Successful
sanitizer runs on the regression suite do not constitute a proof of safety for
all accepted programs.

## What `src/memory` actually does

Repository searches covered header includes and uses of the declared APIs outside
this directory. `nm -C bin/lymar` found no `LM::Memory::` symbols. Symbol absence
alone would not exclude inlining; the lack of API call sites is the stronger
evidence. These are header-only files, so being included does not mean their
allocator or safety machinery executes.

| File | Inclusion and actual use | Assessment |
| --- | --- | --- |
| `model.hh` (564 lines) | Included by the type checker, memory checker, and type-checker implementation. No callers instantiate its allocation/linear/reference proof templates or invoke its assertion APIs. | Dormant C++ type-level model, not a proof engine for Lymar ASTs. |
| `compiler.hh` (134 lines) | Included by `frontend/memory_checker.hh`. Its `CompileTimeRegion`, `CompileTimeAllocation`, validation helpers, no-op macros and allocator hooks have no production callers. | Included but unused API; the checker uses its own state instead. |
| `runtime.hh` (130 lines) | No repository include sites found. | Unused stale near-duplicate of `compiler.hh`, despite its name. It defines the same types/functions in the same namespace, with a different `is_linear_type` rule. Do not include both as a runtime fix. |
| `memory.hh` (678 lines) | Included by `lir/generator.hh` and `backend/types.hh`; no production `MemoryManager`, `DefaultAllocator`, `Region`, `Linear`, `Ref` or `Unsafe` API users found. | Dormant alternative allocator/runtime, not the VM or standalone AOT heap. |
| `analyzer.hh` (1113 lines) | Included only through `memory.hh`; no active `MemoryAnalyzer` instances or access-recording hooks found. | Dormant allocator telemetry, not a safety validator or measurements of the executing VM heap. |

Do not simply wire these files into the existing runtime. First retire or isolate
the duplicates, repair the alternative runtime, and decide which implementation
is authoritative. Removing unused includes may reduce compile work, but that is
a separate cleanup, not a memory-safety fix. No files in `src/memory` were edited
or deleted by this audit.

## Dormant implementation defects

These findings concern `src/memory`, which the production execution paths do not
use. They are not demonstrations of the same bugs in the VM region allocator.

1. **Address reuse makes a stale `Ref` valid again.** `Region::create` records the
   current scope generation at the address. `deallocate<T>` puts the address in a
   reuse pool. A new allocation in the same scope receives the same generation.
   `Ref::isValid` compares only address lookup and that generation.
2. **Scope exit and region destruction skip object destructors.** They call the
   untyped allocator's `deallocate` rather than a recorded type-erased destructor.
   `deallocate<T>` runs destructors, but the scope cleanup path does not.
3. **`Unsafe::allocate` returns memory from a destroyed temporary allocator.**
   `DefaultAllocator()` owns pools whose destructor frees their chunks before the
   returned small-allocation pointer is used. `Unsafe::deallocate` also creates
   an unrelated allocator. An isolated ASan probe reports heap-use-after-free.
4. **Other allocator hazards remain:** `Unsafe::resize` copies `new_size` without
   limiting it to the old allocation size; `allocateZeroed` does not check
   multiplication overflow; `DefaultAllocator::allocate` ignores its alignment
   argument; `MemoryPool::allocate` expands shared vectors after releasing its
   lock. These are source findings, not all separately exercised sanitizer cases.
5. **The reference abstraction is inconsistent.** `Ref::get` returns an unchecked
   pointer, and the last reference destroys its target, which gives the view
   owning behavior rather than a simple borrow. Region lifetime itself is an
   unchecked raw pointer in the reference.
6. **The formal templates are incomplete.** `GenRef` contains the tautology
   `Alloc::region::id == Alloc::region::id`; a reference generation less than the
   region generation is permitted. An isolated instantiation with allocation
   generation 2 and reference generation 1 compiles. `RefManager::is_valid_ref`
   is always false, `LinearMove` preserves its input types, and some assertions
   depend on members absent from their documented type arguments.

The isolated `memory.hh` probe printed:

```text
same-address=1 stale-ref-valid=1 stale-read=9
scope-destructors=0
```

The first object held 7; it was deallocated and replaced by a new object holding
9. The old reference accepted the replacement. The scope test created an object
with a destructor that increments a counter, then exited the scope. Temporary
probe sources and logs are in `/tmp/lymar-memory-audit` for this workspace; they
are not an installed production dependency.

## The executing implementation

### Frontend

`src/lymar.cpp` invokes `TypeCheckerFactory`, then `MemoryCheckerFactory`, then
type checking again. The checks are real, but do not invoke the `src/memory`
template proof model.

`frontend/type_checker/memory.cpp` and the type-checker expression/statement
handlers maintain move, generation, reference, scope and field maps. Ordinary
use after moving a list is rejected. However:

- Consuming calls are inferred by `is_consuming_callee` from a function name
  beginning with `consume`, not from an ownership effect in its signature.
  Indirect calls do not preserve this inference.
- Much of the ownership state is keyed by variable spelling rather than a unique
  binding identity. Shadowing can replace the state of an outer moved binding.
- Erasing a value to `any` does not preserve the owner/reference relation needed
  to invalidate that view after a move.
- Branches are checked sequentially rather than by a sound ownership-state join.
  The same value consumed once in each mutually exclusive branch is rejected
  as a double move. This is a demonstrated false positive, not a safety breach.

`frontend/memory_checker.cpp` maintains a second, inconsistent model: variable
initialization/calls are described as copies/borrows by default, while the type
checker treats some of them as moves. Its `check_statement` does not dispatch
function declarations or frame method bodies. The type checker does visit
functions; this finding concerns the separate memory-checker pass, not the
absence of all checking in function bodies. Its `create_reference`,
`mark_variable_moved`, `insert_make_linear` and `insert_make_ref` have definitions
but no call sites in that implementation. The declared generational-reference
tracking therefore does not form a complete executed analysis.

### Reproduced active compiler gaps

The following probes use supported syntax. The baseline direct consuming call
rejects subsequent access, while these variants are accepted:

```lymar
fn consume_values(values: [int]) {}
var finish = consume_values;
var values = [1];
finish(values);
print(values[0]); // accepted, prints 1
```

```lymar
fn consume_values(values: [int]) {}
var values = [1];
var erased = values as any;
consume_values(values);
var recovered = erased as [int];
print(recovered[0]); // accepted, prints 1
```

```lymar
fn consume_values(values: [int]) {}
var values = [1];
consume_values(values);
{ var values = [2]; print(values[0]); }
print(values[0]); // accepted, prints 1 after printing 2
```

Changing the direct call to `consume_values(values)` in the first probe causes a
use-after-move diagnostic. These demonstrate broken ownership/invalidation
semantics. They do **not** demonstrate physical use-after-free: the VM keeps the
allocations alive under its region rules in these examples.

### AST to LIR

`AST::MemoryInfo` has region, generation, linear/reference/moved flags,
reference target and drop metadata. The LIR does not preserve that full contract.
The generator emits lexical `RegionEnter`, `RegionExit`, `RegionMove` and frame
cleanup. The annotation-based enter/exit helper functions are intentionally
empty because generator scopes own balanced cleanup; they cannot also serve as
generation/reference lowering.

`LIR_Function` has machine register types and in-memory language-type maps, but
no explicit parameter ownership/borrow effects or checked-reference operations.
The `LIR1` serializer does not preserve the language-type maps, AST memory
metadata, or ownership effects. Existing `Mov` and `Copy` do not encode whether a
source capability is consumed or a borrowed capability is created.

### VM, native modules and standalone Fyra

The VM has actual allocation ownership, fresh region-entry IDs, ancestor graph
promotion, cycle-safe reclamation, destructor dispatch, constant copies and
callback/resource cleanup. Native modules use the host helper API for those
operations. Standalone Fyra uses private C++ ownership helpers rather than the
`src/memory` classes.

Those implementations store region membership in sidecars. Neither the tagged
VM reference value nor the standalone pointer captures an allocation generation
and a region epoch that is validated before dereference. Fresh invocation IDs
distinguish recursive region entries; they are not the same guarantee as checked
generational references. VM reset restarts its region-ID counter, so durable
cross-reset handles would additionally need a session epoch.

This establishes tested lifetime management for the covered managed graphs.
It does not establish complete affine/linear consumption, exclusive mutable
borrowing, stale-reference rejection after reuse, all FFI retention rules, or
cross-architecture backend equivalence. Unsafe raw memory remains outside a safe
managed-reference guarantee.

## What needs to reach LIR and the backends

Use one semantic model, independent of backend or CPU. At minimum preserve:

| Information | Required purpose |
| --- | --- |
| Unique binding and allocation identities | Shadowing must not reset another binding's ownership; aliases must refer to the same allocation identity. |
| Owned/shared/immutable-borrow/mutable-borrow classification | Distinguish consumption from alias creation and enforce mutable exclusivity. |
| Function parameter and return ownership effects | Preserve effects through direct calls, function values, methods, closures, imports and native/FFI boundaries. |
| Borrow origin and live interval | Tie a view to its owner and invalidate it on owner consumption or region expiry. |
| Object generation, region instance and epoch | Detect a stale capability even when addresses or lexical region IDs are reused. |
| Type-erased drop/finalizer and pointer-field descriptors | Clean up correctly and preserve graph identity through frames, containers and erased values. |
| Verified control-flow state | Join ownership states across branches and iterate to a fixed point for loops; check all exits and returns. |

Do not send the C++ template classes down as runtime data. Their concepts need
an actual compiler representation, validated lowering and executable semantics.

## Do LIR and ABI need extensions?

**LIR: yes, for the advertised full model.** Existing region operations suffice
for region cleanup and graph promotion, but not for a checked borrow/reference
contract. Add canonical ownership/effect metadata and explicit borrow,
consumption/drop and checked-reference semantics. Some operations may disappear
after a valid static proof; uncertain operations must retain runtime validation.
Preserve the contract in serialization and run a verifier after transformations
and when loading precompiled LIR. Bump the serialized format/semantics version
when this is implemented. Do not invent backend-specific instructions.

**Public object-header layout: not inherently.** Eight-byte headers and the
current list/string/frame layouts can remain if generations and liveness are
stored in a runtime table.

**Checked-reference and native API contract: an extension is needed if these
references cross runtime/module boundaries.** A raw address alone cannot
distinguish an old reference from a new allocation at that address. Each reference
must capture an identity/generation at creation. Options include an opaque handle
to a reference record (which can retain a one-word `LmValue`) or a defined wider
reference representation. Validate captured identity before obtaining a raw
pointer. Merely adding a generation to the current object's header is insufficient:
an old address would read the new object's generation.

Ownership/borrow effects must also become part of exported function metadata and
FFI retention contracts. Extend/version the native helper capabilities and
precompiled metadata so old modules cannot bypass checked-reference semantics.
This is a semantic ABI extension even if existing physical object layouts and
machine calling conventions remain unchanged.

If the intended design instead proves all references statically and erases them
to raw pointers, an ABI change is not required *after a sound, complete proof*.
The current name heuristics, erased views and incomplete analysis do not provide
that proof. Runtime generations are also not a substitute for fixing the static
ownership checker.

## Fyra linker and target evidence

Fyra has an internal archive/symbol linker and ELF/PE/Mach-O image writers. The
standalone C++ runtime also needs TLS, C++ library/exception services and correct
startup/teardown. An actual internal-link attempt on x64 Linux failed on
`R_TYPE_23` (`R_X86_64_TPOFF32`) for the thread-local heap. ARM64 runtime objects
also contain `R_AARCH64_TLSDESC` relocations. The internal relocation evaluator
does not implement those TLS forms. Merely adding the archive is insufficient.

The pending integration supports `LYMAR_AOT_LINKER=auto|fyra|driver`. `auto` tries
Fyra's linker first and records its error before falling back to a target C++
driver. `fyra` exposes the failure without fallback. Target runtime archives are
selected by target architecture/OS, rather than a Linux/x64 host gate. This does
not imply that all target code generators are complete.

Validation performed in this workspace:

- The direct runtime ownership suite, four standalone regression tests and two
  target-runtime integration tests pass normally and under ASan/UBSan with leak
  detection enabled. These are targeted checks, not a full language-suite run.
- Generated x64 Linux programs match VM output at `-O0`, `-O1`, and `-O2` for
  region graphs, staged errors and `std.io.file.open`/binary reads.
- `std.font` static compilation completes at `-O0` and `-O2`; the previous Param
  and ResourceCall lowering errors are gone. The large static build remains
  expensive and is not an executed full-font AOT benchmark result.
- The private runtime ownership suite executes successfully under both
  ARM64 and RISC-V64 Linux QEMU. The Windows x64 runtime archive cross-compiles.
- A full ARM64 Lymar region program still fails in Fyra code generation on a
  missing stack slot for a global string. Windows/macOS generated executable
  behavior has not been established here. WASM helper imports are not an
  independently linked standalone ownership runtime.

A target-aware linker fixes the integration gate. It cannot supply missing
instruction/ABI lowering or missing linker TLS/CRT support.

## Recommended order

1. Define ownership and reference semantics precisely, including whether calls
   borrow or consume and what `any` preserves. Replace name-based effects with
   checked function contracts and use unique binding IDs.
2. Unify the two frontend analyses; cover functions, methods, closures and imported
   bodies, then implement CFG ownership joins and loop analysis. Add the three
   accepted bypasses above as expected-rejection regressions once fixed.
3. Extend canonical LIR/effect metadata and its serializer/verifier. Define one
   checked-reference runtime contract for VM, native modules and every Fyra target.
4. Implement reference identity/generation capture and validation, including
   address reuse, explicit drop, reset, FFI retention and concurrency. Version
   helper/module contracts; keep public object layouts where possible.
5. Extend Fyra's TLS/startup/teardown linking and complete target instruction/ABI
   coverage. Test actual generated executables on each supported target.
6. Retire or repair dormant `src/memory` implementations and integrate telemetry
   only with the authoritative runtime. Validate with adversarial reuse/reset,
   borrow, destructor and concurrency tests plus sanitizers.

The audit findings remain open; the preceding Param/region fixes must not be
described as completion of this full memory model.
