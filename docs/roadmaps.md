# Lymar Feature Gap Roadmap

What Lymar still needs to become the batteries-included systems language it aims to be,
what actually matters, and in what order to build it.

- Status verified against the codebase on 2026-10-29.
- Ranked by **capability**: does it let you express something no existing mechanism can?
  Anything that only saves lines is implemented as sugar over the existing mechanism,
  never as a parallel one (AGENTS.md: no "thousand features doing the same thing").
- Every item is checked against the **Backend Conformance rule**: LIR is the canonical
  language interface; backends must not require generator changes, and any new LIR
  instruction must be implemented on **both** VM and Fyra, in lock-step with
  `LIR_OP_LIST` + verifier + serializer, before it ships.

---

## One-page summary

| # | Item | Class | New LIR surface? | Cost | Depends on |
|---|---|---|---|---|---|
| 1 | Finish `staged fn` (compile-time execution) | Essential | No (folds at AST; VM-fallback reuses canonical LIR) | Med | — |
| 2 | Seamless C interop + foreign `.c/.cpp` linking | Capability | No (reuses existing FFI ops) | Med | 1 (comptime bindings) |
| 3 | Generators (`yield`) over a coroutine substrate | Sugar | Fix existing effect ops | Med | — |
| 4 | SIMD: auto-vectorize fused numeric streams | Capability | Phase 1: no; Phase 2: yes | Med–High | 3 (fusion input) |
| 5 | Installer backends (`.msi` / `.deb`) | Tooling | No | Low | — |
| 6 | Hot reload + LSP/build integration | Tooling | No | Med | 1 |
| 7 | GPU / shaders + unified GPU-CPU memory | Capability | Yes (new backend surface) | High | 1, 4 |

**Deferred (by cost/need, revisit on request):** explicit SIMD vector *types* ·
first-class module values (functors) · reentrant/multi-shot continuations · a general
algebraic-effect DSL.

**Already strong (no work needed):** stdlib (~70+ modules) · Lyra package manager +
git-sourced dependencies · LSP/DAP core · CLI `test`/`bench`/`lint`/`doc`/`profile` ·
own-codegen (Fyra, no LLVM) · structured `parallel`/`concurrent`/`task`/`worker`.

---

## Foundation: current execution-model facts

These facts shape items 1–4 and are the ground truth the plan assumes.

- **Concurrency today is OS-thread fork-join.** `parallel`/`concurrent`/`task`/`worker`
  lower to `SchedulerInit → SchedulerAddTask → SchedulerRun` plus `CapabilityAcquire/
  Release`. With `cores>1` and multiple tasks the VM spawns real `std::thread`s, each a
  separate `RegisterVM` sharing the parent heap; otherwise it runs a sequential loop. It
  supports timeouts, error policies (Stop/Partial/Continue), cancellation, and disjoint
  parallel-slice checks (enforced in the VM, trusted/no-op in Fyra). AOT parallelism uses
  OS threads over a thread-local heap.
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
- **Lazy iteration already exists** as the `std.iterator.Iterator` trait (`next(): any`)
  with `map/filter/take/skip/chain/zip/enumerate/flat_map` adapters.
- **`staged` folds constant values** at type-check time and strips dead branches, but
  `staged fn` is rejected and type-level returns are unimplemented.
- **C access is manual and runtime-only** (`declare(name, fnptr, param_types,
  return_type)`); no header parsing or auto-binding. The FFI lowering ops
  (`ForeignCall`, `Marshal`/`Unmarshal`, `LibraryLoad/Symbol/Unload`, `CallbackCreate`)
  already exist, and the AOT build already invokes an external C/C++ compiler to produce
  `liblymar_aot.a`.
- **No SIMD exists** in LIR or Fyra. `stream_fusion` fuses `map/filter` pipelines at the
  AST level but never vectorizes.

---

## Tier A — Language capability

### 1. Finish `staged fn` — the keystone  [Essential]

Lymar deliberately has **no generics**. The only current ways to write reusable,
type-parameterized code are `any` (the dynamic escape hatch the stdlib is told not to
overuse) and traits (runtime vtable dispatch — no monomorphization). `staged fn` — a
function that runs at compile time and can return **values, types, unions, or enums** — is
the only route to static, zero-cost polymorphism, and it is the community's explicit "no
macros — comptime or bust" requirement. It is also the host mechanism items 2c and the
deferred module-values depend on.

`staged` already folds constant expressions during type checking and emits only the
residual to LIR, so nothing here touches a backend.

**Build:**
1. Implement `staged fn`: register stage-0 callables, evaluate calls with concrete args,
   fold to literals, re-validate (per `docs/staged.md` PASS-2).
2. Add the type-level path: `staged fn` returning `type`/`union`/`enum` (this is the
   generics replacement and the item's main payoff).
3. Enforce the sandbox bounds documented in `docs/staged.md` (recursion depth, instruction
   cap, memory cap, no host calls) with the specified `SemanticError`s.
4. For staged bodies beyond the foldable subset, run their LIR on an embedded Register VM
   with the syscall fence (block `ForeignCall`/`LibraryLoad`/`Channel*`) and fold the
   result as `LoadConst`.
5. Tests: `docs/staged.md` Examples A/B as regression; `tests/negative/` for bound
   violations.

### 2. Seamless C interop — and foreign `.c/.cpp` source  [Capability]

Goal: "make it work out of the box, return me a namespace," removing today's unavoidable
hand-written declarations. This adds **no new LIR semantics** — it layers on the existing
FFI lowering ops. It is capability (eliminates toil that currently cannot be avoided), and
it composes directly with `staged`.

"Can we use C source files directly?" — resolved into three tiers:

- **2a — Link foreign sources (build-system, no LIR change).** Compile project `.c/.cpp`
  with the native toolchain and link, reusing the path `scripts/build_aot_runtime.py`
  already uses to build `liblymar_aot.a` and the existing `-c/-static/-shared` outputs. The
  foreign source is compiled by cc/clang, so this is link-time integration, not a single
  LIR compilation unit.
- **2b — Header → binding generation.** Parse `.h` and auto-emit the `declare(...)` /
  `ForeignCall` bindings as a Lymar namespace, so you call a pre-built/compiled C library
  without hand-writing decls. (Note: binding against a library ≠ compiling that library's
  `.c` through Lymar.)
- **2c — Comptime translation API.** Expose a `staged fn` hook so third parties can write
  translators (C, or other languages) that produce Lymar bindings at compile time. Depends
  on item 1.

A true C→LIR source frontend (Lymar itself lowers C as one compilation unit, Zig-style) is
**out of scope**: it is a large separate effort and would have to lower to LIR to satisfy
conformance. It is the natural future consumer of 2c, not part of this plan.

**Build order:** 2a → 2b → 2c. Start with 2a (reuses existing toolchain + `-target/-arch`
flags).

### 3. Generators (`yield`) over a coroutine substrate  [Sugar]

A generator is a lazy producer. Laziness and all adapters already exist as the `Iterator`
trait, so `yield` is **sugar that must desugar onto `Iterator`** and produce no new
sequence type.

Under the hood this needs the one genuinely missing piece: a **driven fiber/coroutine
runtime**. `yield` = suspend the current fiber; the consumer's `next()` = resume it once
(one-shot continuation). This is a *new capability* at the runtime layer, but presented as
*existing-surface sugar* at the language layer.

**Build:**
1. Wire the fiber driver: make `get_current_fiber()` real, create a fiber per generator,
   and drive suspend/resume in the interpreter dispatch loop (VM) with a matching Fyra
   lowering.
2. Give the effect ops (or a dedicated generator op) resume-with-value semantics so
   `yield` carries its value; update `LIR_OP_LIST` + verifier + serializer + both backends
   in lock-step.
3. Desugar `yield` into a synthesized `Iterator` implementation; `iter (x in gen())` reuses
   the existing `iter` lowering. No new loop form, no new type.
4. Fix the surrounding channel correctness while the fiber substrate exists: make blocking
   `ChannelSend`/`ChannelRecv` suspend a live fiber (removing the null-deref), and define
   channel-iteration termination correctly (stop on *closed*, not on first empty).
5. Tests across VM, `lymar build` (AOT), and `-lir` dump; negative test — `yield` outside a
   generator is a checked error.

### 4. SIMD — auto-vectorize fused numeric streams  [Capability]

Core to Lymar's "own codegen, no LLVM" identity. The natural, already-present hook is
`stream_fusion`, which fuses `map/filter` pipelines; the missing step is turning fused,
element-wise numeric loops into vector operations.

- **Phase 1 — transparent auto-vectorization (no language surface).** The backend lowers
  fused element-wise numeric loops over fixed-width arrays into vector ops. This is a
  *backend optimization*, invisible to LIR semantics and to the programmer, so there is
  **no conformance burden** — results must simply match the scalar path. Verify equivalence
  on both VM and AOT and measure against current scalar benchmarks.
- **Phase 2 — explicit vector types (`f32x4`, …) in the language.** Deferred: this adds
  LIR surface that every backend must implement. Revisit once Phase 1 demonstrates value.

**Build:** prototype Phase 1 on one fused map→reduce benchmark over `[f32]`.

---

## Tier B — Tooling & developer experience

### 5. Installer backends (`.msi` / `.deb`)  [Tooling]

`lymar pack` produces tarballs only. Emit a native installer from the built executable,
completing the "package manager and compiler are one executable" story (Lyra already runs
in-process under `lymar`). Zero LIR surface, so conformance is trivial.

**Build:**
- `pack --deb`: an `ar` archive of `debian-binary` + `control.tar.gz` (from the
  `lymar.nol` manifest) + `data.tar.gz` (the exe). Needs no external tools.
- `pack --msi`: emit a WiX template (manifest + exe), probing for the WiX toolset the same
  way `lyra doctor` probes for `git`.
- Lyra is vendored: commit changes to the Lyra repo first, then bump the gitlink in the
  superproject and verify git status in both.

### 6. Hot reload + LSP/build integration  [Tooling]

The LSP publishes diagnostics on editor-buffer changes; there is no filesystem watcher
(`workspace/didChangeWatchedFiles`) and no rebuild-and-restart loop, so there is no hot
reload. Same tooling class as installers (no LIR surface).

**Build:** add a watched-files capability to the LSP and a `--watch` rebuild loop on the
CLI; wire a "reload" DAP request. A clean hot-reload boundary wants `staged` (item 1), so
schedule it after.

---

## Tier C — Native graphics & compute

### 7. GPU / shaders and unified GPU-CPU memory  [Capability — major]

The wishlist asks for more than a fast scalar path: it wants **SIMD and GPU-CPU pointer
mappings baked into the language**, so you can do GPU programming without the legacy
baggage of existing graphics APIs (the "No Graphics API" direction), and **write a shader
in the language itself**. This is the most ambitious item and the one most tied to Lymar's
identity as a systems language with its own codegen.

**Where things stand.** The runtime currently models graphics with virtualized
`GpuBuffer` / `GpuPipeline` / `GpuBindings` in `src/runtime/software_graphics.hh` — a
*software* model that lets programs run without a GPU backend. There is no real GPU
driver path, no shader compilation, and no unified CPU-GPU memory. Item 4 (SIMD) covers
CPU vectorization only; GPU is the wider "the same language runs on an accelerator" goal.

**Why it is high-cost and last.** This is the only active item that adds a genuinely new
**backend surface**, which puts it in direct tension with the Backend Conformance rule:
- **Unified memory / pointer mapping.** Introduce an explicit residency model over the
  existing `MemoryAlloc` / `BufferView` / `Marshal` ops (CPU pointer ↔ device handle, with
  defined sync/alias semantics) — the language must say where a value lives and how it
  crosses over.
- **Shader authoring.** A kernel is a function that must lower per target. To stay
  conformant it is expressed through the **canonical LIR** (a `FuncDef` specialized to a
  shader IR), not a separate mini-language — otherwise it becomes the "special little
  language inside" the philosophy rejects.
- **Real backends.** Wire a driver stack (Vulkan / Metal / DX12 / WebGPU) behind the same
  contract, with the software model retained as the reference path. Behavioral equivalence
  between the CPU reference path and the GPU path is mandatory before it ships.

**Plan (staged, cheapest-to-riskiest):**
1. Define the compute surface: explicit device/residency types and CPU↔GPU pointer mapping
   over existing buffer ops; document the memory model.
2. Design kernels as LIR-lowered functions; prove one trivial kernel runs identically on
   the software reference path and (behind a flag) a real device.
3. Add shader IR emission from the same lowering; keep `GpuPipeline`/`GpuBindings` as the
   runtime ABI, not a user-facing API.
4. Integrate one real backend end-to-end with conformance tests across VM and AOT.

**Build:** start with step 1 as a design doc (memory model + kernel contract) before any
codegen, because the residency model constrains items 4 and 7 and the conformance surface.

---

## Deferred (by cost/need — revisit only on request)

- **Explicit SIMD vector types.** Language surface that must be implemented on every
  backend (item 4, Phase 2).
- **First-class module values / functors.** A fourth composition mechanism atop traits +
  mixins + embed, only meaningful after `staged fn`, and niche. Would add `ModuleLoad` /
  `ModuleSymbol` LIR ops across both backends.
- **Reentrant / multi-shot continuations (`reset`/`shift`).** Genuinely novel but no
  current consumer; would need real continuation capture on VM *and* Fyra.
- **General algebraic-effect DSL (`effect`/`do`/`with`).** Redundant with fallible `?`,
  traits, frames, and `std.log`. The only non-redundant slice (one-shot continuations) is
  covered by generators in item 3.

**Open question:** the effect ops and the `Fiber` handler stack ship unused. Either repurpose
them for item 3's one-shot continuations or remove them — do not keep orphan semantics that
every backend must still maintain without any feature depending on them.

---

## Design guardrail

The fiber/coroutine layer in item 3 is an **implementation substrate, not a surface
concept**:

- No user-visible `Generator`/`Stream` type or keyword.
- `yield` must produce the existing `std.iterator.Iterator`.
- Blocking channels reuse the existing `channel` type (same construct, correct behavior),
  and the existing `concurrent`/`parallel` constructs may park on fibers internally
  (M:N) rather than becoming a second, user-selectable concurrency model.

Any feature that only works by introducing a *new surface concept the programmer must
choose between* fails the "not another way" test and is out of scope.

---

## Dependency map & build order

```
1 staged fn ──► 2c comptime translation API
             └──► 6 hot reload (stable re-eval boundary)
             └──► (future) module values

2 C interop:  2a link  →  2b header bindings  →  2c comptime (needs 1)

3 generators (yield → Iterator; drives the fiber substrate)
             └──► 4 SIMD Phase 1 (auto-vectorize fused streams) ──► Phase 2 (deferred)

5 installers ── fully independent

7 GPU / shaders + unified GPU-CPU memory ── long pole; needs 1 (kernel lowering via LIR)
   and the 4 vector model; the only item that adds a real new backend surface
```

**Build order:** `1 → 2a → 3 → 2b → 4(Phase 1) → 5 → 2c → 6 → 7`. Items 1, 5 and 2a can
start immediately; item 4 Phase 1 rides on item 3's fusion input; item 7 is the largest
and last; the deferred set stays parked.
