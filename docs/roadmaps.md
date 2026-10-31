# Lymar Feature Gap Roadmap

What Lymar still needs to become the batteries-included systems language it aims to be,
what actually matters, and in what order to build it.

- Status verified against the codebase on 2026-10-31 (test counts and trait signatures
  re-measured by running the suites, not carried forward).
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
| 1 | Finish `staged fn` (compile-time execution) — folding, type path, sandbox done | Essential | No (folds at AST; VM-fallback reuses canonical LIR) | Med | — |
| 1b | Staged frames — mint **new** named frames at comptime (done; `Option(T)` shipped, library Result deleted in favor of native fallibles) | Essential | No (stage 0 emits ordinary frame ASTs) | Med | 1; iter prerequisites (closed) |
| 2 | Seamless C interop + foreign `.c/.cpp` linking | Capability | No (reuses existing FFI ops) | Med | 1 (comptime bindings) |
| 3 | Generators (`yield`) over a coroutine substrate | Sugar | Fix existing effect ops | Med | — |
| 4 | SIMD: auto-vectorize fused numeric streams (Phase 1 done) | Capability | Phase 1: no; Phase 2: yes | Med–High | 3 (fusion input) |
| 5 | Installer backends (`.msi` / `.deb`) (done) | Tooling | No | Low | — |
| 6 | Hot reload + LSP/build integration (done) | Tooling | No | Med | 1 |
| 7 | GPU / shaders + unified GPU-CPU memory | Capability | Yes (new backend surface) | High | 1, 4 |

**Deferred (by cost/need, revisit on request):** explicit SIMD vector *types* ·
first-class module values (functors) · reentrant/multi-shot continuations · a general
algebraic-effect DSL.

**Already strong (no work needed):** Lyra package manager + git-sourced dependencies ·
LSP/DAP core · CLI `test`/`bench`/`lint`/`doc`/`profile` · own-codegen (Fyra, no LLVM) ·
structured `parallel`/`concurrent`/`task`/`worker`.

**The stdlib transition is complete as of 2026-10-31.** `std.option` and `std.result` are
folded into `std.core`; the specialised `OptionInt`/`OptionStr`/`ResultInt`/`ResultStr`
frames and the `ok_int`/`err_int`/`ok_str`/`err_str`/`ok_bool` helpers are deleted, and
their former callers (serialization, http.server, wss.server, debug) now declare
`T?`/`T?Error` and return `ok()`/`err(Error(...))`. `std.serialization` was rewritten as
free functions over a `str`, which also removed the two `iter`-inside-a-frame-method
sites that faulted with 0xC0000005.

Verification: `python scripts/audit_stdlib.py` imports every module in `std/` and reports
**322 modules, 322 OK, 0 FAIL** (two files were removed as misplaced or duplicated:
`std/collections/collection_utils.lm`, which duplicated `iterator.collect`, and
`std/crypto/random_test.lm`, a test living in the library). The positive suite is
117/117, the memory negative tree is 90/90, and the staged parity harness matches
byte-for-byte on all five staged tests.

The two compiler defects this surfaced are **fixed as of 2026-10-31**: `iter`
inside a frame method now compiles (linear-mode loop lowering for methods), and
the single-variable `iter (key in dict)` binds the key, matching what the type
checker declares. Both were verified on VM **and** AOT (item 1b prerequisites,
below); the stdlib workarounds can be retired on the next std pass.
`docs/language.md` §4.2 and AGENTS.md document the supported behavior.

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
- **Lazy iteration already exists** as the `std.iterator.Iterator` trait — two members,
  `has_next(): bool` and `next(): any` — with
  `map/filter/take/skip/chain/zip/enumerate/flat_map` adapters.
- **`staged` folds constant values** at type-check time and strips dead branches.
  `staged fn` folds value-returning calls with compile-time-constant arguments into
  literals (v1 subset: `val`/`var` constants, `if`/`elif`/`else`, nested staged calls,
  `return`); the body is executed by the type checker and never reaches LIR. Type-level
  returns are implemented: a `staged fn` annotated `: type` folds, in type position, to a
  concrete type (union, structural, passed-through type parameter, existing enum type, or
  value-conditioned selection). Type parameters carry kind bounds (`: type`, `: enum`,
  `: frame`). Enum *types* flow through stage-0 as arguments and results; synthesizing a
  *new* enum (fresh variants) at stage 0 is not implemented.
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

> **Status:** value folding and the type-level path are implemented (incl. nested-call
> shadowing at both the value and type level, and decimal return fidelity), enum values joined the
> stage-0 constant model so enum-driven branches fold and strip, and the sandbox bounds from
> `docs/staged.md` section 4 are enforced (depth / step / byte budgets, host-call refusal). Build
> steps 4 and 5 are done: non-foldable staged bodies now run on an embedded Register VM behind a
> fail-closed opcode allowlist and a call fence, and the two executors are reconciled by the
> `LYMAR_STAGE0_FORCE_VM` parity harness plus the consolidated test set (117 positive / 90 negative).

Lymar has exactly **one** compile-time capability — `staged` — and comptime evaluation,
generics, and "macros" are all things you do *with* it, not three systems. A macro
subsystem is explicitly out of scope: macro-like power comes from ordinary `staged fn`
code evaluated inside the type checker (the Zig position — no macro syntax, no `<T>`
syntax), so there is no second surface where "a call" means different things at
different phases. If `<T>`-style sugar ever ships, it must desugar to staged calls and
may never coexist as a separately-implemented instantiation machinery.

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
1. *(done)* Implement `staged fn` value folding: register stage-0 callables, evaluate
   calls with concrete args, fold to literals (`CallExpr::foldedConst`), skip staged
   bodies in codegen — no new LIR surface, so VM and AOT conform by construction.
   Regression: `tests/staged/staged_fn_test.lm`.
2. *(done)* Add the type-level path: `staged fn` returning `type`/`union`/`enum` (this is
   the generics replacement and the item's main payoff). A constructor is declared with a
   `type` return annotation and `: type` parameters, and is callable only from type
   positions — variable/parameter/type-alias annotations and staged bodies — never as a
   value expression. Annotation arguments may also be compile-time constants
   (`vector(8, int)`), which is what lets a comptime `if` select the returned type. Those
   value arguments must be **literals**: only `INT`/`FLOAT`/`STRING`/`true`/`false` tokens take
   the value-argument path in `src/frontend/parser/types.cpp`, so an identifier in that position
   is parsed as a type name — `const FLAG = 0; pick(FLAG, A, B)` fails with *cannot find type
   `FLAG`* and then reports the parameter as needing a `type` annotation. Write the literal.
   Regressions: `tests/staged/staged_type_fn_test.lm` (item 5, value-conditioned selection) and
   `tests/staged/staged_value_param_test.lm` (bool value argument, a value-conditioned
   constructor nested inside a type-only one, an alias of a `pick`, and the literal-only limit).
   Type parameters carry a **kind bound**: `: type` accepts any type, `: enum` and `: frame`
   accept only that kind and report a violation at the call site (`requires an enum type,
   found \`Frame<Money>\``). The meta names are rejected anywhere a runtime signature or
   binding could use them, so `var x: frame` and `fn f(a: enum)` fail loudly instead of
   silently becoming `any`. `docs/staged.md` Example A is written in this spelling and runs.
   Enum types are accepted as type arguments and returned as type results (verified with
   `nullable(Status)` and a zero-argument constructor returning an existing enum). What is
   *not* implemented is stage-0 construction of a brand-new enum with fresh variants; a
   constructor composes existing types instead. In Example A that means `ErrType` is supplied
   as an already-declared enum rather than being generated.
   Regression: `tests/staged/staged_type_fn_test.lm`.
3. *(done)* Enforce the sandbox bounds documented in `docs/staged.md` (recursion depth, instruction
   cap, memory cap, no host calls) with the specified `SemanticError`s. One compilation-wide budget
   charged by every stage-0 entry point (`TypeChecker::stage0_charge`); the first exhaustion latches
   so a deep unwind reports once. Points worth knowing:
   - The staged-fn fold depth was capped at 256 with a vague "depth/step limit" message; it is now
     the documented 1000 and reports *maximum recursion depth exceeded*. 1000 nested C++ frames of
     `fold_staged_body` → `exec_staged_stmt` → `fold_stage0_expr` is safe (measured, ~2 s to fail).
   - Steps and bytes are separate currencies because they stop different shapes: an exponential
     staged `fib(40)` (depth 40, 2^40 calls) trips the **byte** bound first at ~0.3 s because every
     fold produces a literal node; a fold that spins over bound names trips the **step** bound. Both
     are hard stops, and which one fires is a property of the program, not of the checker.
   - The isolation boundary needed code because a host call was previously *silently* left in the
     residual expression (failing later with "must be a compile-time constant"). Stage 0 is a
     constant folder with no interpreter that could reach the OS, so it now refuses explicitly:
     any callee in a staged fn body that is not a registered `staged fn` errors with *cannot call
     \`name\` at compile time*. A `staged { ... }` block inside a runtime function is unaffected:
     it decides a branch, and its residual statements are ordinary runtime code.
   Regressions: `tests/negative/staged/staged_{recursion_depth,instruction_limit,host_call}.lm`,
   checked by `tests/memory/run_negative_validation.py` (90 passed).
4. *(done)* For staged bodies beyond the foldable subset, run their LIR on an embedded Register VM
   with the syscall fence and fold the result as `LoadConst`. The AST folder stays canonical — the
   type domain (`: type` params, type constructors, kind bounds) has no LIR representation, and a
   folded constant changes the *type* of the expression around it, so folding has to happen while
   the program is typed. Points worth knowing:
   - Routing is **syntactic** (`TypeChecker::staged_body_needs_vm`), decided before anything folds,
     because `add_error` prints as it records: a speculative "try the VM, fall back to the folder"
     would emit diagnostics that have to be discarded, and a body would be reported twice.
   - The fence is an **allowlist**, not the denylist the step was written as. Denying
     `ForeignCall`/`LibraryLoad`/`Channel*` by name means a new opcode is sandbox-accessible until
     someone remembers to add it; refusing everything unlisted makes the omission a compile error.
     Stage 0 gets arithmetic, comparison, control flow, conversion, string building, fallible
     values, enums, aggregates, region bookkeeping, and named calls.
   - **`Call` was the hole the step did not mention.** It is not a safe opcode: VM dispatch reaches
     precompiled native shared libraries for any exported symbol. A call is allowed only to the
     staged fn itself, to another `staged fn` (lowered and registered on demand, so loops compose
     with recursion and helper calls), to a `_builtin_*` intrinsic, or to a deterministic builtin —
     with `print`/`input`/`time`/`clock`/`random`/`sleep` refused, because a compile-time value must
     be pure.
   - The fence bounds *what* runs, not *how long*: `RegisterVM::set_instruction_budget()` (off by
     default, so runtime execution pays one predicted compare) stops a non-advancing staged loop
     from hanging the compiler.
   - Lowering one function outside `generate_program` needs the **type system installed**
     (`Generator::set_type_system`): the decimal and enum paths call `type_system_->getType(...)`
     unguarded. Without it a `d4` staged body faults — found by the parity switch, not by review.
   - Compile-time functions are **erased** from `FunctionRegistry` and `LIRFunctionManager` when the
     evaluation ends, so a `staged fn` cannot leak into codegen, the cache, or an export list.
   - **Parity harness:** `LYMAR_STAGE0_FORCE_VM=1` routes every value-shaped body through the VM,
     which turns each staged test into a cross-executor equality check. It must be run with
     `--no-cache` (a cached program never re-folds), and it is what found the `d4` fault and the
     the harness that found the `d4` fault and, once the enum boundary below was closed, drove every
     staged body (including enum-valued ones) to a byte-identical VM result. This is the harness that
     makes deleting the folder a safe deletion.
   - Boundary: numbers, bools and **unit-variant enums** cross. An enum argument is rebuilt in the
     VM's own boxed representation (`MakeEnum`'s 3-field frame `[tag, payload, variant_name]`, tag in
     field 0) so a body's `m == Mode.Fast` lowers to the same `GetTag` compare the folder answers --
     passing the bare tag as an int would compare unequal against the boxed enum and fold a wrong
     constant. Payload-carrying variants are never a stage-0 *value* (`try_stage0_enum_value` refuses
     them), so the payload/name fields stay nil and equality is a single tag compare. A **type-valued**
     parameter still refuses: LIR has no representation for a type, and such bodies stay on the folder.
     Default parameter values are refused too (their defaults have no environment on the VM).
   Regressions: `tests/staged/staged_vm_test.lm` (loop, mutation, self-recursion, nested staged
   call, **enum-argument crossing under a loop** → `3628800 6 10 5 81 145` / `6 20`),
   `tests/staged/staged_enum_test.lm` (passes identically under `LYMAR_STAGE0_FORCE_VM=1`),
   `tests/negative/staged/staged_vm_{host_call,opcode,instruction_budget}.lm` (90 negative
   validations passing). Documented in `docs/staged.md` section 5.
5. *(done)* Tests consolidating the two executors. `docs/staged.md` Examples A/B are mirrored by
   live regressions -- Example A by `tests/staged/staged_type_fn_test.lm` (its `: enum`/`: frame`
   kind-bound `result_of`/`boxed` cases), Example B by `tests/staged/staged_enum_test.lm`, runtime
   enum `==` by `tests/types/enum_equality.lm`. Bound violations carry a negative per enforced limit,
   one for each executor: the folder's `staged_{recursion_depth,instruction_limit,host_call}.lm` and
   the VM's `staged_vm_{opcode,host_call,instruction_budget}.lm` (all under `// @error:type_error`).
   `tests/memory/run_negative_validation.py` drives the negative tree (**90 passed**); the positive
   manifest `tests/test.txt` (117 entries, five of them staged) runs in `run_tests.py`
   (**117 passed** as of 2026-10-31).

   **Caution — the positive suite is not deterministically green.** Four consecutive full runs
   on 2026-10-31 gave three at `117 passed / 0 failed` and one at `116 passed / 1 failed`; the
   failing file was not captured, so the flake is real but unidentified. Treat 117 as the
   expected count, not a guarantee, and re-run before quoting a green result.

**Defects found while exercising item 1 (pre-existing, outside `staged`):**

- **`==` had three different implementations; enums are now fixed in the generator.** *(fixed)*
  The pre-fix measurements are kept because the shape recurs:

  | site | enum / heap compare | result for `Status.Linux == Status.Linux` |
  | --- | --- | --- |
  | VM `src/backend/vm/ops/comparison.cpp` -> `lm_value_eq` (`vm_value.cpp:183`) | pointer identity; the PTR branch special-cases only `TYPE_STRING` / boxed strings | `false` |
  | Fyra AOT `lymar_aot_value_equal` (`src/memory/aot_runtime.cpp:1143`) | structural: `tag` + `payload` when the header is `'ENUM'` (`0x454e554d`) | `true` |
  | stage 0 `evaluate_const_expr` (`expressions.cpp:413`) | int/double only; **no** `MemberAccessExpr` case | did not fold at all |

  Root cause was **two incompatible runtime representations for one language value**.
  `MakeEnum` lowers to a heap object, not an integer tag: the VM allocates
  `lm_frame_alloc("__lir_internal_enum__", 3)` (`ops/objects.cpp:15`, which stamps `TYPE_FRAME`),
  while Fyra emits `lm_enum_new` (`fyra/builder.cpp:2360`), which writes a `'ENUM'` magic header.
  Nothing in the VM marks its enum frames with that magic, and `lm_value_eq` has no frame branch,
  so enum `==` degraded to identity on the VM. `match` was unaffected because the generator emits
  `GetTag` + an *integer* `CmpEQ` (`lir/generator/statements.cpp:2159`), which takes the
  `IS_INT && IS_INT` fast path. `print` was unaffected because `lm_value_to_string` **does** know
  the internal name (`vm_value.cpp:396`) — formatting was taught about enum frames, equality was not.

  Blast radius was wider than enums: on the VM every heap-structured value compares by identity —
  `[1,2] == [1,2]`, `{"a":1} == {"a":1}`, `(1,2) == (1,2)` and same-field frames all yielded
  `false`, while `"abc" == "abc"` yielded `true`; `c1 == c1` was `true`, confirming pure
  identity. That is a language-design question, not a backend bug (see the open question below),
  and is untouched by this fix. Enums, being value types, were not a design question.

  **Fix.** The relation is defined once, in the LIR generator
  (`lir/generator/expressions.cpp`), over `GetTag` / `CmpEQ` / `CmpNEQ` / `GetPayload` — the
  instructions `match` already depends on, so both backends already implement them faithfully
  and no new LIR surface or backend change was needed (AGENTS.md: backends must not require
  generator changes and must stay behaviorally equivalent). `==` answers `tagL == tagR` and,
  only when that holds, `payloadL == payloadR`; `!=` short-circuits the other way. Operands of two
  different enums answer statically, because `Color.Red` and `Status.Active` are both tag 0. An
  enum whose variants carry no payload lowers to a single tag compare. Stage 0 gained enum values
  (`constant_enums_`, `try_stage0_enum_value`) so `CURRENT_PLATFORM == TargetPlatform.Linux` folds
  and `docs/staged.md` Example B strips its untaken branches and prints the Linux branch.
  Two traps this ran into, worth remembering: the join must be a **jump**, not `And`/`Or` — those
  LIR ops are bitwise and `as_i64(VAL_TRUE)` is `0` on the VM, so ANDing two bools silently
  answers false; and a second, separate constant map is needed for enums rather than reusing
  `constant_ints`, so `p == 0` cannot fold against a variant tag.
  Regressions: `tests/types/enum_equality.lm`, `tests/staged/staged_enum_test.lm`.
- **Native codegen loses a value that crosses a control-flow join.** *(fixed, Fyra)*
  Found while exercising item 1's enum regression: natively, `assert` on a computed bool failed
  while the VM passed. No enums required to reproduce — the minimal case was pure integer:
  `fn intmerge(a: int, b: int): int { var r = a; if (a == 0) { r = b; } return r; }` answered `0`
  for `intmerge(0, 5)`; `boolmerge`, `andf(true, true)` and `k1 == k2` for payload variants
  (`Shape.Circle(3)`) all failed the same way. Two shapes, one cause.

  **Root cause (Fyra, x64).** `X64Architecture::emitPhiCopies` emits the edge copies that place a
  phi's incoming value before a predecessor jumps into the join. It skipped a copy when
  `getValueAsOperand(incoming) == getValueAsOperand(phi)`, reading *"same spelling, so self-copy,
  nothing to do"*. That inference is only valid on the text (`-S`) path, where a value's operand
  **is** the physical register it was allocated to. The object path keeps every value in a
  lazily-allocated frame slot (`emitStoreResult` always stores to `getStackOffset`) and ignores
  physical registers entirely, while `getValueAsOperand` still reports the register the linear-scan
  allocator handed out. Two unrelated values can therefore share a register spelling while living
  in different slots — param `%1` and the merge phi both printed `rsi` but sat at `-0x78(%rbp)` and
  `-0xa8(%rbp)`. The copy was dropped, the phi's slot was never written on the taken edge, and the
  join read uninitialised stack.
  Two traps that cost the most time here, worth remembering: **`-S` output is not evidence about the
  object path** (it runs the register-materialising pipeline, so the same function looks correct
  there — only `objdump` on the real `.exe` showed the empty block and the phi slot written on one
  edge); and **the SSA construction was innocent** (the post-`PhiInsertion`/`SSARenamer` dump already
  had both incoming values, which is why the search had to move into codegen).

  **Fix** is one condition in `vendor/fyra/src/target/architecture/x64/X64Architecture.cpp`: the
  skip applies only when `cg.getTextStream()`. On the object path the copy is always emitted — a
  genuine self-copy is a harmless slot-to-itself load/store, and skipping it is what broke the join.
  First attempt (comparing `getStackOffset` in both modes) had to be reverted: a phi's slot is
  allocated lazily, so asking for it before emission throws *Missing stack slot*. Verified against
  the VM at `-O0/-O1/-O2/-O3`, and natively for `tests/types/enum_equality.lm` and
  `tests/staged/staged_enum_test.lm` (both previously failed natively). Per AGENTS.md this is a Fyra
  repository change: commit Fyra first, then update the superproject gitlink.
  Related design question, still open: should `==` on plain frames and collections be identity or
  structural? Move-by-default semantics (`var m3 = m1` reports "use of moved binding") suggests
  frames are resources, so structural frame equality may be deliberately out of scope; enums,
  being value types, are not.
- **Object literals are not checker-supported.** `Point { x: 1, y: 2 }` reports "Unknown
  expression type" and a bogus type mismatch, independent of any staged code, so stage-0
  structural types are exercised by passing field-compatible frames to annotated parameters.
- **Reading a field of a folded structural type lowers only when an argument pins the
  layout.** An uncalled function taking `IntResult` fails in LIR generation ("Unknown field or
  method: is_ok"); the same function called with a matching frame works.
- **`tests/negative/run_negative_tests.py` does not parse.** *(open, pre-existing, tooling)* Every
  line's leading indentation was flattened to a single space, so `__init__`'s body sits at the same
  level as its `def` and the script dies with `IndentationError: expected an indented block after
  function definition on line 102`. The negative tree is therefore driven by
  `tests/memory/run_negative_validation.py`, which walks the same directory and is stricter (it
  rejects signal exits and sanitizer aborts); that is what the sandbox regressions above are
  verified with, 90 passed. Repairing the dedicated runner is a mechanical re-indent of 431 lines
  and deserves its own pass.
- **AOT/VM divergence in `iter` loops, surfaced while verifying the item-1b
  prerequisites.** *(fixed, both backends verified at -O0/-O1/-O2)* Two distinct causes, one
  in Fyra, one in the LIR→Fyra lowering:
  - **Fyra O2 `LoopRotate` broke `break`-inside-`iter`.** Its exit-phi machinery only ever
    gives the exit block the incoming pair `{preheader-init, latch}`. A `break` edge reaches
    the loop exit from a block that is **not part of the natural loop** (the backward walk
    from the latch never reaches a block that only flows to the exit), so rotation left that
    edge without a phi incoming and `emitPhiCopies` silently dropped the copy — the join
    read an uninitialized slot (`0` / garbage at -O2 only, correct at -O0/-O1). Fix: refuse
    rotation when the exit block has any predecessor outside `{header, latch}` —
    conservative, in keeping with the pass's other bail-outs (`vendor/fyra`
    `src/transforms/LoopRotate.cpp`). A Fyra-repo change: commit Fyra first, then bump the
    superproject gitlink.
  - **Raw small ints travelled with object-pointer value kinds.** `iter` bindings were
    stamped `any`/`Ptr` at every generator site, and the typed-primitive list fast path
    loads the **raw unboxed word**, so AOT consumers applied the object-kind model to plain
    integers: `1` printed as `true`, `2` as `nil`, and dict-value sums went wrong — at
    **every** opt level, linear and CFG modes alike. Fix at the source: the LIR generator
    stamps the iter binding with the container's concrete integer element/key/value
    language type when one is known (`raw_int_iter_type`,
    `src/lir/generator/statements.cpp`), and the Fyra builder propagates it (the
    `ListIndex` fast path retypes the load to `I64`; `Mov` keeps a concrete scalar kind
    into an `any` binding instead of forcing `Ptr`). The VM path is untouched; AOT output
    is now byte-identical to the VM for `break`-in-`iter`, list-`iter` and dict-`iter`
    probes.

### 1b. Staged frames — the generics replacement for data shapes  [Essential]

> **Status:** implemented 2026-10-31. `staged frame Name(P: type, ...) { ... }`
> parses, kind-bound meta-parameters (`: type` / `: enum` / `: frame`, spelled
> exactly as item 1 step 2) are validated at the request site, and each distinct
> type-argument tuple mints one ordinary nominal frame before codegen runs — the
> generated frames are plain AST, so every backend conforms by construction.
> Verified: positive suite 121/121, negative tree 94/94 (four new staged-frame
> guards), stdlib audit 321/321, and AOT≡VM on `tests/staged/staged_frame_test.lm`
> (single/two/nested parameters, frame-kind arguments, trait conformance, cache
> reuse, cross-import-spelling nominal identity).
>
> What shipped beyond the sketch below: **constructor steering** — a construction
> written with the template name (`var b: Box(int) = Box(42);`, also qualified as
> `core.Box(42)`) is resolved against the instantiation the annotation already
> requested and the callee is rewritten to the generated frame, so the checker and
> the generator see an ordinary frame constructor. Bare template construction with
> no type context is rejected by design. Nominal identity is keyed on the
> template's declared name, so `Option(int)`, `core.Option(int)` and
> `option.Option(int)` are the same frame regardless of import spelling.
>
> Stdlib outcome differs from step 4 as written: `Option` landed as the staged
> `Option(T: type)` in `std/core/option.lm`, but **no `Result(T, E)` frame ships**.
> The language's native `T?` / `T?Error` + `ok`/`err`/`?`/`? else`/`match` already
> *are* a Result with real stack propagation; a library Result would be a parallel,
> weaker error mechanism (AGENTS.md: staged frames do not replace fallible types).
> `std/core/result.lm` and its `Ok`/`Err` helpers were deleted; `std/core/index.lm`
> carries the migration map.
>
> Two defects surfaced during verification, both **pre-existing and orthogonal to
> staged frames** (each reproduces with hand-written frames, no staged syntax):
> - **AOT indirect calls are broken.** Calling an `fn`-typed parameter returns
>   garbage under AOT (`tests/functions/first_class.lm` fails today: VM prints
>   `addFunc(3, 4) = 7`, AOT prints `2`). Staged frames merely inherit this: std
>   `Option.map`/`filter` are correct on VM, wrong on AOT, identically to a
>   hand-written frame of the same shape. The AOT test tree (`tests/aot/`, one
>   file) has never covered function-typed parameters. Fixing this lives in the
>   Fyra submodule and is its own work item.
> - **Deterministic compiler segfault** on one legal staged-frame shape (a two-
>   parameter template instantiated with a locally-declared `Error` frame —
>   `scratch/sf_result_typed.lm`); a semantically identical file compiles clean,
>   so the trigger is input-shape-sensitive in scan/parse/check, not semantics.
>   The crashing shape is not in std (Result was deleted), but a compiler must
>   never segfault on valid input and this needs a debugged repro → fix.

`staged fn : type` can pick, alias, union and compose **existing** types. It cannot
mint a new one — and the remaining generics gap is exactly a *shape-generating*
need: `Option(T)` and `Result(T, E)` are per-`T` **frames** with fields, an `init`,
constructors (`Some(v)`, `Ok(v)`) and methods (`.map()`, `.unwrap()`). A staged fn
returns the annotation but no constructor and no methods; the only escape hatch is
hand-declaring a monomorphic frame per `T` (what `tests/staged/staged_type_fn_test.lm`
does), which is more code than `any` and is the layer the stdlib transition just
deleted. Staged frames make that layer generated instead of hand-written.

Design intent — `staged frame` is a frame **template**, instantiated on demand:

```lymar
staged frame Option(T: type) {
    pub var tag: int;               // 0 = None, 1 = Some
    pub var value: T;

    pub fn unwrap(): T {
        if (self.tag == 0) { return err(); }
        return self.value;
    }
}

var x: Option(int);                 // type position = instantiation request
```

- **Demand-driven monomorphization.** A use of `Option(int)` in a type position
  registers the request; each distinct argument tuple generates exactly one real
  frame, cached. The generated artifact is an *ordinary* frame — same fields,
  `init`/`deinit` lifecycle, same vtable dispatch, lowered through the existing
  frame path. **No new LIR surface**, so VM and AOT conform by construction
  (Backend Conformance rule: the generator must not change for a backend).
- **Nominal identity.** `Option(int)` and `Option(str)` are distinct, unrelated
  frames; there is no runtime type-erasure tag on the value, no `any` in the
  representation. Kind bounds (`: type`, `: enum`, `: frame`) carry over from
  item 1 step 2, so a template only accepts the kinds its body can actually use.
- **No `<T>` syntax.** `Name(args)` in type position reuses the parser path that
  item 1 step 2 established for annotation arguments like `vector(8, int)` — one
  compile-time spelling, per the "no parallel mechanisms" rule. If `<T>` sugar ever
  ships it must desugar to this, never to a second instantiation machinery.

**Build:**
1. Frontend: parse `staged frame Name(P: type, ...) { ... }` — a frame body whose
   field types, `init` and method signatures may mention the meta-parameters.
   Kind-bound spelling identical to item 1 step 2; reject instantiation *inside* a
   `staged frame` body (recursion is guarded centrally in step 2, not per-template).
2. Checker: instantiation requests. Resolve `Name(args)` in annotation/parameter/
   alias positions against registered templates; canonicalize the argument tuple
   (type identity, not spelling); one generated frame per distinct tuple; depth and
   count caps charged through `TypeChecker::stage0_charge` so `Option(Option(Option(…)))`
   runaway fails closed with the documented sandbox errors.
3. Synthesis: substitute meta-arguments into field types, `init`, and method
   bodies, then register the result as a regular `frame` **before** codegen runs.
   Generated methods are ordinary methods — `iter` (including inside frame methods,
   now that the prerequisite is fixed), fallible returns, trait conformance all work
   with no special cases.
4. Stdlib: express `Option`/`Result` shapes in `std.core` as staged frames and
   delete the remaining hand-written per-type wrappers; `T?` / `T?Error` sugar
   stays the preferred spelling where it suffices (AGENTS.md: staged frames do not
   replace fallible types, they generate the shapes fallible types cannot).
5. Tests: positives (nominal identity, nested instantiation, method dispatch,
   trait conformance of a generated frame, AOT≡VM parity at -O0/-O1/-O2), negatives
   (kind-bound violation at the request site, over-depth runaway, unknown
   template), and the staged-parity harness extended to drive every generated
   body through `LYMAR_STAGE0_FORCE_VM`-style reconciliation.

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
  LIR compilation unit. *(done)*

  > **Build step 2a is done.** `lymar build` accepts repeatable `--native <file.c|.cpp>`
  > (+ `--native-include/--native-cflag/--native-link`), and a project manifest's
  > `[native] sources/include_dirs/cflags/link_libs` entries are merged automatically, so
  > `lymar build` in a project "just works" with no flags. Each foreign source is compiled
  > to a temporary object by the target toolchain (`gcc`/`g++`, cross-prefixed like the AOT
  > driver table, overridable with `LYMAR_AOT_CC`/`LYMAR_AOT_CXX`) and then contributed to
  > every link path: the Fyra internal linker via `BackendBuilder::addObject` (executables,
  > shared images, and - since this step - static archives, which now store input objects as
  > real members), the target-driver fallback (objects beside the program object, extra
  > libraries after the runtime archive), and both host shared-module emitters. Proof:
  > `tests/native/verify_native_link.py` (symbol present in the `--native` exe, absent in
  > the plain exe, archive member in the `-static` artifact) plus
  > `scratch/native_2a_proj`-style manifest builds. Calling into the linked code is 2b's
  > job; today an *unreferenced* foreign object is dead-stripped from executables by the
  > linker, which is expected archive semantics, not a gap.
- **2b — Header → binding generation.** Parse `.h` and auto-emit the `declare(...)` /
  `ForeignCall` bindings as a Lymar namespace, so you call a pre-built/compiled C library
  without hand-writing decls. (Note: binding against a library ≠ compiling that library's
  `.c` through Lymar.) *(done)*

  > **Build step 2b is done.** `lymar run/build` accepts repeatable
  > `--bind-header <file.h>` (+ `--bind-lib <path>` / `--bind-namespace <name>`), and
  > a project manifest's `[native] headers/bind_libs` entries are merged automatically.
  > A hand-written C declaration-subset parser (`src/backend/native/header_parser.cpp`)
  > extracts function declarations (skipping preprocessor, comments, structs, enums,
  > function-pointer params), maps C types to std.ffi typed call helpers, and emits a
  > complete `.lm` module with lazy library load and per-function wrappers. The generated
  > module is written to `.cache/bindings/<name>.lm` and that directory is added to the
  > `ModuleManager` include path, so user code simply writes
  > `import mylib; mylib.add(3, 4)`. Uses only existing std.ffi intrinsics
  > (`library_load`/`library_get_symbol`/`call_i64_0/1/2`/`call_f64_2`/`call_void_1`/
  > `foreign_call`) — no new LIR ops. Proof: `tests/native/verify_bind_header.py`
  > (builds a shared lib from fixture `.c`, runs the generated binding via VM, asserts
  > correct results for 0-arg/1-arg/2-arg/3-arg/float/void functions).
- **2c — Comptime translation API.** Expose a `staged fn` hook so third parties can write
  translators (C, or other languages) that produce Lymar bindings at compile time. Depends
  on item 1. *(done — realized as a declarative `import "c:..."` syntax instead of a
  `staged fn` API, so no sandbox changes were required and the same 2b pipeline is
  triggered automatically during module resolution.)*

> **Build step 2c is done.** Users write
> ```lymar
> import "c:math_ops.h" from "libmath_ops" as math;              // full header
> import "c:math_ops.h" from "libmath_ops" as math { add_points }; // cherry-pick
> import "c:stdio.h" as cstdio;                                   // system header (empty lib path)
> ```
> The parser accepts a bare `STRING` after `import`, an optional `from "<lib>"` clause
> (stored as `ImportStatement::fromLibrary`), an optional brace-select `{ IDENT, ... }`
> filter (mapped to a `Show` filter), and existing `show/hide`/`as` forms. A new module
> `src/frontend/cheader_import.{hh,cpp}` runs the 2b pipeline (`parse_header` +
> `generate_bindings`) at compile time. `ModuleManager::extract_metadata` calls the
> resolver before adding the dependency, rewrites `modulePath` to the resulting namespace,
> and adds `.cache/bindings` to the include path so downstream resolution proceeds
> through the ordinary Lymar module machinery. System headers (no `from` clause) emit
> `ffi.library_load("")`, and `lymarrt_library_open("")` returns the process handle
> (`GetModuleHandleA(NULL)` / `dlopen(NULL, RTLD_LAZY|RTLD_GLOBAL)`) to resolve CRT
> symbols. Include dirs come from `--native-include`, the project manifest, `gcc -E -Wp,-v`
> probing, `LYMAR_HOME/include`, and per-file source directory. Bindings are cached in
> `.cache/bindings/<ns>.lm` and reused when the header mtime is older. Proof:
> `tests/native/verify_cimport.py` (four variants + cache-reuse check).

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
  on both VM and AOT and measure against current scalar benchmarks. *(done)*

  > **Build step 4 is done (Phase 1).** The `stream_fusion` AST pass lowers fused
  > numeric streams (map, filter, fold) into straight-line, affine loop structures.
  > Filter lowering emits reconvergent diamond branches (`if (cond) { ... }`)
  > instead of multiple loop-header backedges, ensuring loops form natural SSA loops
  > compatible with Fyra's `LoopVectorizer` and `LoopRotate` at `-O2`. The verification
  > harness opt-out `LYMAR_NO_VECTORIZE=1` disables backend loop and SLP vectorization so
  > the identical bytecode is emitted scalar. Proof: `tests/native/verify_simd.py`
  > (exercises `tests/native/simd_stream_bench.lm` across VM, vectorized AOT at `-O2`,
  > and scalar AOT with `LYMAR_NO_VECTORIZE=1`, asserting exact output equivalence and
  > confirming assembly differences).
- **Phase 2 — explicit vector types (`f32x4`, …) in the language.** Deferred: this adds
  LIR surface that every backend must implement. Revisit once Phase 1 demonstrates value.

---

## Tier B — Tooling & developer experience

### 5. Installer backends (`.msi` / `.deb`)  [Tooling]

`lymar pack` produces tarballs only. Emit a native installer from the built executable,
completing the "package manager and compiler are one executable" story (Lyra already runs
in-process under `lymar`). Zero LIR surface, so conformance is trivial. *(done)*

> **Build step 5 is done.** `lymar pack` / `lyra pack` supports `--deb` and `--msi`
> targets alongside the default source tarball. `--deb` writes a fully self-contained
> Unix `ar` archive containing `debian-binary` (`2.0\n`), `control.tar.gz` (populated from
> `lymar.nol` package metadata, author/maintainer, description, and target architecture),
> and `data.tar.gz` (installing the compiled executable to `/usr/local/bin/<name>`),
> requiring zero external packaging tools and validated by `dpkg-deb`. `--msi` emits a WiX
> XML definition template (`<name>.wxs`) and probes for the WiX toolset (`wix` or
> `candle`/`light`) to invoke compilation when available, cleanly falling back to
> template emission. Lyra submodule updated and committed in lock-step. Proof:
> `tests/test_installer_pack.py` (creates a test package, verifies source packaging,
> builds and inspects `.deb` structure with `ar` and `dpkg-deb`, and checks generated `.wxs`).

### 6. Hot reload + LSP/build integration  [Tooling]

The LSP publishes diagnostics on editor-buffer changes; there is no filesystem watcher
(`workspace/didChangeWatchedFiles`) and no rebuild-and-restart loop, so there is no hot
reload. Same tooling class as installers (no LIR surface). *(done)*

> **Build step 6 is done.** Added CLI `--watch` / `-w` flags for `lymar run` and
> `lymar build` that monitor entry sources, project `src/` trees, and manifests,
> triggering automatic rebuild and restart on change (honoring `LYMAR_WATCH_ONCE=1` for
> automated testing). Extended the LSP server (`src/lsp.cpp`) to advertise the
> `workspace.didChangeWatchedFiles` capability during `initialize`, invalidating dependency
> graphs and updating diagnostics when external file modifications occur. Wired the custom
> `reload` and `hotReload` request handler in the DAP server (`src/dap/dap_server.cpp`) to
> facilitate hot reload under debugging sessions. Proof: `tests/test_hot_reload.py`
> (verifies CLI `run --watch` and `build --watch`, LSP `workspace/didChangeWatchedFiles`
> capability and notification handling, and DAP `reload` request processing).

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
