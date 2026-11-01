# Lymar Feature Gap Roadmap

What Lymar still needs to become the batteries-included systems language it aims to be,
what actually matters, and in what order to build it.

- Status verified against the codebase on 2026-11-01.
- Ranked by **capability**: does it let you express something no existing mechanism can?
  Anything that only saves lines is implemented as sugar over the existing mechanism,
  never as a parallel one (AGENTS.md: no "thousand features doing the same thing").
- Every item is checked against the **Backend Conformance rule**: LIR is the canonical
  language interface; backends must not require generator changes, and any new LIR
  instruction must be implemented on **both** VM and Fyra, in lock-step with
  `LIR_OP_LIST` + verifier + serializer, before it ships.

---

## Active Roadmap Summary

| # | Item | Class | New LIR surface? | Cost | Depends on |
|---|---|---|---|---|---|
| 1 | Generators (`yield`) over a coroutine substrate | Sugar / Substrate | Fix/wire effect & fiber ops | Med | — |
| 2 | SIMD Phase 2: Explicit vector types (`f32x4`, ...) | Capability | Yes (vector ops across VM & Fyra) | Med–High | 1 |
| 3 | GPU / shaders + unified GPU-CPU memory | Capability (major) | Yes (new backend surface) | High | 1, 2 |

**Completed & Shipped (historical milestone summary):**
- **Item 1 & 1b (`staged fn` & `staged frame`):** Complete comptime evaluation, type functions, kind bounds (`: type`, `: enum`, `: frame`), VM fallback executor with syscall fence, parity harness, monomorphization, constructor steering, `Option(T)`, library Result deleted in favor of native fallibles (`T?`).
- **Item 2 (`C interop` & native linking):** Foreign `.c/.cpp` linking (`--native`, manifest `[native]`), automated C header binding generation (`--bind-header`), and declarative header imports (`import "c:header.h" from "lib"`).
- **Item 4 Phase 1 (`SIMD auto-vectorization`):** Transparent stream fusion lowering to affine SSA loops vectorized by Fyra at `-O2`.
- **Item 5 (`Installer backends`):** `lymar pack` / `lyra pack` self-contained `.deb` and WiX `.msi` emission.
- **Item 6 (`Hot reload & tooling`):** `--watch` mode, LSP `workspace/didChangeWatchedFiles`, and DAP `reload`/`hotReload`.
- **Standard library transition:** 320 modules, 100% passing tests (124/124), facade re-exports upgraded to `pub import ... show ...;`, list concatenations cleaned.

---

## Foundation: Current Execution-Model Facts

These facts shape the remaining active items and are the ground truth the plan assumes:

- **Concurrency today is OS-thread fork-join.** `parallel`/`concurrent`/`task`/`worker`
  lower to `SchedulerInit → SchedulerAddTask → SchedulerRun` plus `CapabilityAcquire/
  Release`. With `cores>1` and multiple tasks the VM spawns real `std::thread`s, each a
  separate `RegisterVM` sharing the parent heap; otherwise it runs a sequential loop. It
  supports timeouts, error policies (Stop/Partial/Continue), cancellation, and disjoint
  parallel-slice checks. AOT parallelism uses OS threads over a thread-local heap.
- **The fiber/coroutine substrate is designed but not driven.** `Fiber`, `Scheduler`
  (ready/suspend/resume), and a `Fiber`-parking `Channel` exist, but the interpreter never
  creates or runs fibers — `RegisterVM::get_current_fiber()` returns `nullptr`
  unconditionally.
- **Channels are consumed by polling, not blocking.** `iter (x in ch)`, `worker`, and the
  scheduler consumer all emit `ChannelPoll` (non-blocking; `iter` exits on first empty).
  The blocking ops `ChannelSend` (when full) and `ChannelRecv` (when empty) call
  `current_fiber->suspend()` and therefore would null-deref — not reachable in current
  tests only because consumption uses poll and no test drives real producer/consumer
  blocking.
- **Algebraic-effect ops (`EffectPerform`/`EffectHandle`/`EffectResume`) are inert:** on
  the VM they are guarded by the always-null fiber; on Fyra they only pass the payload
  through. The frontend never emits them.
- **Lazy iteration already exists** as the `std.iterator.Iterator` trait — two members,
  `has_next(): bool` and `next(): any` — with
  `map/filter/take/skip/chain/zip/enumerate/flat_map` adapters.
- **Auto-vectorization (Phase 1) is active in AOT**, but no explicit vector types exist
  in the language.

---

## Active Work Items

### 1. Generators (`yield`) over a coroutine substrate  [Sugar / Substrate]

A generator is a lazy producer. Laziness and all adapters already exist as the `Iterator`
trait, so `yield` is **sugar that must desugar onto `Iterator`** and produce no new
sequence type.

Under the hood this needs the one genuinely missing piece: a **driven fiber/coroutine
runtime**. `yield` = suspend the current fiber; the consumer's `next()` = resume it once
(one-shot continuation). This is a *new capability* at the runtime layer, but presented as
*existing-surface sugar* at the language layer.

**Build Steps:**
1. **Wire the fiber driver:** Make `get_current_fiber()` real, instantiate a fiber context per
   generator instance, and drive suspend/resume in the interpreter dispatch loop (VM) with a
   matching Fyra lowering.
2. **Resume-with-value semantics:** Give the effect ops (or a dedicated generator resume op)
   resume-with-value semantics so `yield` carries its produced value; update `LIR_OP_LIST` +
   verifier + serializer + both backends in lock-step.
3. **Desugar `yield`:** Desugar `yield` statements into a synthesized `Iterator`
   implementation; `iter (x in gen())` reuses the existing `iter` lowering. No new loop form,
   no new container type.
4. **Fix channel blocking & termination:** While the fiber substrate exists, make blocking
   `ChannelSend` and `ChannelRecv` suspend a live fiber (eliminating the null-deref risk), and
   define channel-iteration termination correctly (stop on *closed*, not on first empty poll).
5. **Verification & Tests:** Tests across VM, `lymar build` (AOT), and `-lir` dump; negative
   test ensuring `yield` outside a generator is a compile-time error.

---

### 2. SIMD Phase 2: Explicit vector types  [Capability]

Phase 1 (transparent auto-vectorization of fused numeric streams) is complete. Phase 2 introduces
first-class vector types for explicit data-parallel computing without relying entirely on loop
optimization heuristics.

**Build Steps:**
1. **Primitive Vector Types:** Introduce fixed-width vector types (`f32x4`, `f64x2`, `i32x4`,
   `u8x16`) into the type system as first-class primitive types.
2. **Canonical LIR Vector Ops:** Add vector arithmetic (`VecAdd`, `VecSub`, `VecMul`, `VecDiv`),
   bitwise/logical operations, and shuffle/blend instructions to `LIR_OP_LIST`.
3. **Dual Backend Implementation:** Implement canonical vector instructions on both the VM
   (portable software emulation) and Fyra (x86_64 AVX/SSE and ARM Neon lowering).
4. **Interoperability & Casts:** Define explicit load/store operations between arrays/slices and
   vector types with strict alignment checks.
5. **Benchmarks & Regressions:** Comprehensive test suite asserting numerical equivalence between
   VM emulation and Fyra native execution.

---

### 3. GPU / shaders and unified GPU-CPU memory  [Capability — Major]

The goal is native accelerator compute baked directly into Lymar: **SIMD and GPU-CPU pointer
mappings in the language itself**, enabling GPU programming without legacy graphics API baggage
(the "No Graphics API" direction) and authoring shaders directly in Lymar.

**Where things stand:**
The runtime currently models graphics with virtualized `GpuBuffer` / `GpuPipeline` / `GpuBindings`
in `src/runtime/software_graphics.hh` — a software reference model that runs without a GPU backend.
There is no real GPU driver path, no shader compilation, and no unified CPU-GPU memory.

**Why it is high-cost and staged:**
This adds a genuinely new **backend surface**, requiring strict adherence to the Backend Conformance
rule:
- **Unified memory / pointer mapping:** Introduce an explicit residency model over existing
  `MemoryAlloc` / `BufferView` / `Marshal` ops (CPU pointer ↔ device handle, with defined sync/alias
  semantics) — defining where a value lives and how it crosses over.
- **Shader authoring:** A kernel is an ordinary function lowered through canonical LIR (a `FuncDef`
  specialized to shader IR), not a separate mini-language inside the compiler.
- **Hardware backends:** Wire driver stacks (Vulkan / Metal / DX12 / WebGPU) behind the same contract,
  retaining the software model as the reference path. Behavioral equivalence between CPU reference
  and GPU execution is mandatory.

**Build Steps (cheapest to riskiest):**
1. **Compute surface & residency doc:** Define device/residency types and CPU↔GPU pointer mapping
   over existing buffer ops; document the formal memory model.
2. **Kernel design in LIR:** Design kernels as LIR-lowered functions; prove a trivial kernel runs
   identically on the software reference path and (behind a flag) a real device.
3. **Shader IR emission:** Add shader IR emission (SPIR-V / WGSL) from the same lowering; keep
   `GpuPipeline`/`GpuBindings` as the runtime ABI, not a user-facing API.
4. **Hardware backend integration:** Integrate one real backend end-to-end with conformance tests
   across VM and AOT.

---

## Active Substrate & Compiler Debt

Small, specific compiler and test-harness defects to resolve alongside active items:

1. **Deterministic compiler segfault on legal staged-frame shape:**
   A two-parameter template instantiated with a locally-declared `Error` frame
   (`scratch/sf_result_typed.lm`) triggers an input-shape-sensitive crash in scan/parse/check.
   Needs a minimal debugged repro and fix.
2. **Negative test runner indentation (`tests/negative/run_negative_tests.py`):**
   Leading indentation is flattened to a single space in the script, causing an `IndentationError`.
   Needs a mechanical re-indent pass to restore the dedicated runner alongside
   `tests/memory/run_negative_validation.py`.
3. **Orphaned effect op resolution:**
   The effect ops (`EffectPerform`, `EffectHandle`, `EffectResume`) currently sit inert in the LIR.
   During Item 1 (Generators), either wire them into the live fiber suspension/resumption machinery
   or prune them to avoid maintaining dead LIR opcodes.

---

## Deferred Items (Revisit on Request)

- **First-class module values / functors:** A fourth composition mechanism atop traits + mixins +
  embed; niche and adds `ModuleLoad`/`ModuleSymbol` LIR ops.
- **Reentrant / multi-shot continuations (`reset`/`shift`):** No current consumer; requires full
  continuation capture across both VM and Fyra.
- **General algebraic-effect DSL (`effect`/`do`/`with`):** Redundant with fallible `?`, traits,
  frames, and `std.log`. One-shot continuations are covered by generators.

---

## Design Guardrail

The fiber/coroutine layer in Item 1 is an **implementation substrate, not a surface concept**:

- No user-visible `Generator` or `Stream` keyword.
- `yield` must produce the existing `std.iterator.Iterator`.
- Blocking channels reuse the existing `channel` type (same construct, correct behavior).
- Any feature that only works by introducing a *new surface concept the programmer must choose
  between* fails the "not another way" test and is out of scope.

---

## Dependency Map & Build Order

```
1 Generators & Fiber Substrate (yield → Iterator; channel blocking)
             │
             ├──► 2 SIMD Phase 2 (explicit vector types)
             │
             └──► 3 GPU / Shaders & Unified Memory (kernel lowering via LIR)
```

**Build Order:** `1 (Generators & Fiber Substrate) → 2 (SIMD Phase 2) → 3 (GPU & Unified Memory)`.
Active compiler debt items are addressed concurrently.
