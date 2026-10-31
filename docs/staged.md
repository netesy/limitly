# Compile-Time Execution Architecture: Staged Metaprogramming (`staged`)

This document specifies the redesign and implementation of the compile-time execution mechanism in the Lymar compiler architecture, replacing legacy `comptime` constructs with a native `staged` construct.

---

## 1. AST & Grammar Specifications

The `staged` construct allows stage 0 compile-time evaluation using Lymar's native language syntax without introducing secondary macro DSLs, preprocessors, or generic syntax (`<T>`).

### EBNF Grammar Rules

These rules are the implemented v1 surface. `StagedBlock` is the statement-level form that
folds constant branches inside an ordinary runtime function (Example B).

```ebnf
StagedFnDeclaration ::= "staged" "fn" Identifier "(" [ Stage0Params ] ")" ":" TypeAnnotation BlockStatement ;
Stage0Params       ::= Stage0Param { "," Stage0Param } ;
Stage0Param        ::= Identifier ":" MetaTypeName        // a type parameter
                     | Identifier ":" TypeAnnotation      // a compile-time value parameter ;
MetaTypeName       ::= "type" | "enum" | "frame" ;
TypeLiteral        ::= "type" "{" Identifier ":" TypeAnnotation { "," Identifier ":" TypeAnnotation } "}" ;
Stage0Call         ::= Identifier "(" [ Stage0Arg { "," Stage0Arg } ] ")" ;   // type position only
Stage0Arg          ::= TypeAnnotation | Literal ;
StagedBlock        ::= "staged" "{" Statement* "}" ;
```

Three spellings that an earlier draft of this document proposed are deliberately **not** part
of the grammar, because the compiler can already infer everything they would say:

- **No `staged` parameter modifier** (`staged OkType: type`). A staged function body runs
  entirely at stage 0, so every parameter of one is already a compile-time binding; the
  annotation alone decides the domain it receives: `T: type` binds a type, `n: int` binds a
  value. Kind bounds (`: enum`, `: frame`) narrow which types may bind.
- **No `staged { ... }` wrapper inside a staged fn.** The enclosing `staged fn` already puts
  the whole body at stage 0. A `staged { ... }` *block statement* inside an ordinary runtime
  function remains valid and is how dead branches get stripped (Example B).
- **No `staged` prefix at the call site.** A call appearing in a type position has no runtime
  meaning, so it is stage 0 by definition; this mirrors value position, where
  `val x = square(5);` folds with no prefix either.

One restriction the grammar already implies but is easy to miss: `Stage0Arg ::= TypeAnnotation |
Literal` means a **value** argument must be a literal. Only `INT` / `FLOAT` / `STRING` / `true` /
`false` tokens take the value-argument path in `src/frontend/parser/types.cpp`; an identifier in
that position is parsed as a type name instead. So with `const FLAG = 0;` and a
`pick(flag: int, a: type, b: type)` constructor, `var x: pick(FLAG, A, B) = ...;` fails with
*cannot find type `FLAG`* and then reports `pick`'s parameter as needing a `type` annotation.
Write the literal (`pick(0, A, B)`). Regressions: `tests/staged/staged_type_fn_test.lm` (item 5,
value-conditioned selection) and `tests/staged/staged_value_param_test.lm` (bool value argument,
value-conditioned constructor nested inside a type-only one, alias of a `pick`, and this limit).

### AST Node Representations

```cpp
namespace LM::Frontend::AST {
 // Represents a compile-time evaluated block statement
 struct StagedBlockStatement : public Statement {
 std::shared_ptr<BlockStatement> body;
 };

 // Represents a compile-time evaluated expression
 struct StagedExpr : public Expression {
 std::shared_ptr<Expression> expression;
 };

 // A staged function: `isStaged` plus a return annotation. When that annotation is the
 // meta type `type`, the function is a type constructor, callable only from type positions.
 struct FunctionDeclaration : public Statement {
 std::string name;
 std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> params;
 std::optional<std::shared_ptr<TypeAnnotation>> returnType;
 bool isStaged = false;
 };

 // A type annotation that is a stage-0 constructor call, e.g. `nullable(int)` or
 // `vector(8, int)`. Value arguments keep their expression here because a type annotation
 // cannot carry a constant.
 struct TypeAnnotation : public ASTNode {
 std::string typeName;
 bool isStagedCall = false;
 std::string stagedCallName;
 std::vector<std::shared_ptr<TypeAnnotation>> stagedCallArgs;
 std::shared_ptr<Expression> stagedCallValueArg = nullptr;
 };

 // `type { field: T, ... }` — a structural type produced by a stage-0 fold.
 struct TypeLiteralExpr : public Expression {
 std::shared_ptr<TypeAnnotation> annotation;
 TypePtr resolvedType = nullptr;   // filled by the staged fold
 };
}
```

---

## 2. Compiler Pipeline Integration

Compile-time staged evaluation occurs strictly **DURING Semantic Analysis / Type Checking**, after initial AST parsing and symbol resolution, but before Lower Intermediate Representation (LIR) generation.

### Pipeline Flowchart

```
 ┌───────────────────────────────┐
 │ Parse AST │
 └───────────────┬───────────────┘
 │
 
 ┌─────────────────────────────────────────────────────────────────┐
 │ PASS 1: Type Checking & Static Contract Checking │
 │ - Check static contracts: contract(sizeof(T) == 16) │
 │ - Verify staged function arguments and enum/union bounds │
 └───────────────────────────────┬─────────────────────────────────┘
 │
 
 ┌─────────────────────────────────────────────────────────────────┐
 │ PASS 2: Staged Evaluator (Compile-time Interpreter) │
 │ - Execute staged { ... } blocks │
 │ - Evaluate staged functions that return types/unions/enums │
 │ - Replace staged AST nodes with concrete literal AST nodes │
 └───────────────────────────────┬─────────────────────────────────┘
 │
 
 ┌─────────────────────────────────────────────────────────────────┐
 │ PASS 3: Behavioral Contract Lowering │
 │ - Lower function preconditions: requires(x > 0) │
 │ - Lower function postconditions: ensures(result != null) │
 │ - Inject explicit runtime guard/trap AST nodes into bodies │
 └───────────────────────────────┬─────────────────────────────────┘
 │
 
 ┌───────────────────────────────┐
 │ LIR / Bytecode Gen │
 └───────────────────────────────┘
```

### Pipeline Pseudocode

```cpp
void CompilePipeline::run(std::shared_ptr<AST::Program> ast) {
 // Stage 1: Parsing
 Parser parser(scanner);
 auto ast = parser.parse();

 // Stage 2: Semantic Analysis + Staged Evaluation
 TypeChecker typeChecker(typeSystem, symbolDb);

 // Staged evaluation executes inside type checking
 for (auto& stmt : ast->statements) {
 if (auto stagedStmt = std::dynamic_pointer_cast<AST::StagedStatement>(stmt)) {
 // 1. Type check staged construct first
 typeChecker.check_statement(stagedStmt);

 // 2. Evaluate stage 0 node
 auto foldedNode = typeChecker.evaluate_staged_statement_node(stagedStmt->block);

 // 3. Re-validate folded AST node
 typeChecker.check_statement(foldedNode);

 // 4. Replace staged node with concrete folded AST node
 stmt = foldedNode;
 }
 }

 // Stage 3: LIR Lowering
 LIR::Generator lirGen;
 auto lirProgram = lirGen.generate_program(typeCheckerResult);
}
```

---

## 3. Code Examples

### Example A: Dynamic Tagged Union Creation using `staged`

Metaprogramming and code specialization are achieved without generics by evaluating `staged` functions that accept/return native types, tagged unions, and enums.

```lymar
// Define error enum discriminant
enum MathError {
 DivisionByZero,
 Overflow
}

// Staged function constructing a tailored Result type.
// `ErrType: enum` is a kind bound: only an enum type may be passed there.
staged fn make_result_type(OkType: type, ErrType: enum): type {
 return type {
 is_ok: bool,
 ok_value: OkType,
 err_value: ErrType
 };
}

// Specialized type instantiated at stage 0
type IntResult = make_result_type(int, MathError);

fn result_is_ok(r: IntResult): bool {
 return r.is_ok;
}

// A frame whose fields match satisfies the folded structural type.
frame IntResultImpl {
 pub var is_ok: bool;
 pub var ok_value: int;
 pub var err_value: MathError;
}

var ok_result = IntResultImpl();
ok_result.is_ok = true;
ok_result.ok_value = 42;
assert(result_is_ok(ok_result));
```

This listing is the executable form; it is mirrored by `tests/staged/staged_type_fn_test.lm`.
Two things it deliberately avoids, both independent of `staged`:

- **Object literals.** `IntResult { is_ok: false, ... }` is not implemented in the checker, so a
  value of a stage-0 structural type is supplied as a frame with matching fields. Note also that
  reading a field of a folded structural type only lowers when a real argument pins the layout —
  an uncalled function whose parameter is the bare structural type fails in LIR generation.
- **Comparing enum values.** `==`/`!=` on variants follows value semantics (same enum, same
  variant, equal payload) because the LIR generator lowers it to `GetTag`/`CmpEQ`/`GetPayload`,
  and stage 0 now carries enum values in its constant model, so enum comparisons inside `staged`
  fold. `match` was and is unaffected. See `docs/roadmaps.md` item 1 for the fix and the
  remaining native-`assert` caveat noted below.

### Example B: Enum-Driven Compile-Time Conditional Branch Stripping

Conditional branches evaluated inside `staged { ... }` blocks are resolved at stage 0. Unreached branches are stripped from the AST before LIR emission.

```lymar
enum TargetPlatform {
 Linux,
 Windows,
 Wasm
}

const CURRENT_PLATFORM = TargetPlatform.Linux;

fn execute_sys_call() {
 staged {
 if (CURRENT_PLATFORM == TargetPlatform.Linux) {
 print("Executing Linux syscall");
 } elif (CURRENT_PLATFORM == TargetPlatform.Windows) {
 print("Executing Win32 API");
 } else {
 print("Executing Wasm import");
 }
 }
}
```

**Folded AST Output (Post Stage 0 Evaluation):**
The `Windows` and `Wasm` branches are stripped completely before lowering to LIR:
```lymar
fn execute_sys_call() {
 print("Executing Linux syscall");
}
```

> **Verified.** This listing prints `Executing Linux syscall` on both the VM and a native build:
> stage 0 evaluates `CURRENT_PLATFORM == TargetPlatform.Linux` from the enum constants, strips the
> `Windows`/`Wasm` branches, and the residual body is a single `print`. Regression:
> `tests/staged/staged_enum_test.lm` proves the stripping (if the fold did not happen both branches
> would run), and `tests/types/enum_equality.lm` covers runtime equality. Enum equality is lowered
> by the LIR generator over `GetTag`/`CmpEQ`/`GetPayload`, so both backends share one definition;
> an enum whose variants carry no payload compiles to a single tag compare.

---

## 4. Safety & Sandboxing Rules

To prevent compile-time memory corruption, infinite loops, or host resource exhaustion, the `StagedEvaluator` enforces strict sandboxing bounds during stage 0 execution:

| Parameter | Lymar | Enforcement Action |
| :--- | :--- | :--- |
| **Maximum Recursion Depth** | `1,000` stack frames | Aborts stage 0 pass with `SemanticError`: *"maximum recursion depth exceeded"* |
| **Maximum Loop / Instruction Cap** | `1,000,000` instructions | Aborts stage 0 pass with `SemanticError`: *"instruction limit exceeded"* |
| **Memory Allocation Bound** | `64 MB` total heap | Rejects compile-time allocation with `SemanticError`: *"allocation limit exceeded"* |
| **Isolation Boundary** | Two executors, one rule | The AST folder has no interpreter that could reach the host; the stage-0 VM runs behind a static instruction **allowlist** plus a call fence. Neither can leave the language |

All AST nodes folded by `staged` evaluation must pass a re-validation pass in the `TypeChecker` to guarantee memory safety and semantic correctness prior to LIR generation.

### What is enforced, and how it is charged

> **Implemented.** The bounds live in `TypeChecker` (`STAGE0_MAX_DEPTH` / `STAGE0_MAX_STEPS` /
> `STAGE0_MAX_BYTES`) and every stage-0 interpreter entry point charges them through
> `TypeChecker::stage0_charge`.

- **One budget per compilation.** The step and byte counters are never reset mid-run, so splitting
  the same work across many staged calls cannot buy more compile time than doing it in one. This
  matters because the v1 body subset has no loops: the shape that actually runs away is
  *recursion* — direct or mutual — not iteration.
- **Steps** are charged once per AST node the stage-0 interpreter executes
  (`exec_staged_stmt`, `fold_stage0_expr`, `resolve_staged_type_expr`, and the `staged { ... }`
  stripper `evaluate_staged_statement_node`/`evaluate_staged_expression`), plus one per resolved
  type-constructor call. That is the closest honest analogue of "instructions" for an AST walker.
- **Bytes** are charged for what the fold *retains*: each folded literal (`sizeof LiteralExpr`)
  and each synthesized type (the `Type` header plus one entry per field/branch). Folded output is
  what survives into LIR, so it is the only allocation a sandbox can meaningfully limit; the
  evaluator's transient maps are bounded by the step cap instead.
- **Which bound trips first is a property of the program, not of the checker.** A fold that builds
  nodes trips the byte bound (an exponential staged `fib` reports *allocation limit* first); a fold
  that loops over the environment trips the step bound. Both are hard stops.
- **The first exhaustion latches.** One `SemanticError` is reported and the flag stays set, so the
  recursion unwinding back out through the same exceeded limit does not emit an error per frame.
- **Isolation is structural, not a filter.** Stage 0 is a constant folder inside the type checker:
  it has no interpreter that could reach the OS, so there is nothing to sandbox away. What it must
  do is *refuse* rather than silently leave an unreduced call behind, so any callee in a staged fn
  body that is not a registered `staged fn` is rejected: *"cannot call 'name' at compile time --
  stage 0 executes staged fns only and has no host access"*. Residual code inside a `staged { ... }`
  block in a runtime function is **not** affected — that is a compile-time *branch decision*, and
  whatever survives is ordinary runtime code.
- **Regressions:** `tests/negative/staged/staged_recursion_depth.lm`,
  `tests/negative/staged/staged_instruction_limit.lm`,
  `tests/negative/staged/staged_host_call.lm`. Run them with
  `python tests/memory/run_negative_validation.py` (the dedicated
  `tests/negative/run_negative_tests.py` is broken at HEAD — its indentation was flattened, see
  `docs/roadmaps.md` item 1).

---

## 5. The second executor: the stage-0 VM

> **Implemented.** `src/frontend/type_checker/staged_vm.cpp`. The AST folder stays the canonical
> evaluator; the VM exists for the bodies the folder does not implement, and both fold the same
> way — the result becomes a `CallExpr::foldedConst` literal, so nothing downstream can tell which
> executor produced it.

The folder implements `val`/`var`, `if`/`elif`/`else`, `return`, and nested staged calls. It does not
implement loops or local mutation, and it never will well: those are the parts a real interpreter
already gives you, with the runtime's own semantics for free. So a staged body that uses them is
type-checked, lowered to one LIR function, fenced, and executed on the embedded `RegisterVM` before
the fold continues.

**Why the folder is not simply replaced.** Two of its jobs have no LIR representation at all:
the type domain (`: type` parameters, type constructors, unions, `: enum`/`: frame` kind bounds —
LIR's `Type` is an ABI tag, not a language type), and phase order (a folded constant changes the
*type* of the expression around it, so folding has to happen while the program is being typed, not
after). The VM is therefore an additional executor for scalar bodies, never the only one.

**Routing is syntactic.** `staged_body_needs_vm()` inspects the AST shape *before* anything is
folded, so a body is never evaluated twice and never reported both as "unsupported" and by the
other executor. This matters because `add_error` prints as it records: there is no way to try a
route speculatively and discard its diagnostics.

**The fence is an allowlist, not a denylist.** Stage 0 may execute arithmetic, logic, comparison,
control flow, conversion, string building, fallible values, enums, aggregates, region
bookkeeping, and named calls. Every other opcode is refused — including any opcode added later,
which is the point: introducing a new instruction does not quietly acquire compile-time access.
Module globals (`LoadGlobal`) and frame construction are refused for the same reason: at fold time
no module has been initialised and no runtime method has been lowered, so the value they would
read does not exist.

**A call is the part that actually needs guarding.** `Call` is not a safe opcode: dispatch reaches
precompiled native shared libraries for any exported symbol. So a call is permitted only when it
targets the staged fn itself, another `staged fn` (prepared and registered on demand, which is what
makes loops and recursion and helper calls compose), a `_builtin_*` intrinsic, or a deterministic
language builtin. `print`, `input`, `time`, `clock`, `random`, and `sleep` are refused because a
compile-time value must be a pure function of its inputs.

**Bounds.** The opcode fence says what may run, not how long, so `RegisterVM` carries an
instruction budget set to `STAGE0_MAX_STEPS` and throws when it is spent — a `staged fn` with a
non-advancing loop is a compile error, not a hung compiler. The counter is disabled by default
(`SIZE_MAX`) so runtime execution pays one predicted compare. Compile-time functions are erased
from both registries when the evaluation ends, so a `staged fn` can never reach code generation,
the cache, or an export list.

**Checking the two executors against each other.** `LYMAR_STAGE0_FORCE_VM=1` routes *every*
value-shaped staged body through the VM, including the ones the folder handles. Run the suite
normally and then forced and the two runs must agree; that is the parity gate, and it is what makes
removing the folder later an ordinary deletion. Use `--no-cache`: the compiled program is cached
per source file, and a cached program never re-folds, so a forced run over cached files proves
nothing.

**What crosses the boundary.** Numbers, bools and **unit-variant enums** cross into the VM. An
enum argument is rebuilt in the VM's own boxed representation — `MakeEnum`'s 3-field frame
`[tag, payload, variant_name]` with the variant tag in field 0 — so a body's `m == Mode.Fast` lowers
to the very `GetTag` compare the folder answers. Handing over the bare tag as an `int` would instead
compare unequal against the boxed enum the body builds and silently fold a wrong constant. Because
`try_stage0_enum_value` treats a variant with associated values as a call rather than a value, a
stage-0 enum argument is always a unit variant, so the payload and name fields stay `nil` and the
equality is a single tag compare (the frame is reclaimed by the VM destructor like any boxed
argument). A **type-valued** parameter still refuses: LIR has no representation for a language type
(LIR's `Type` is an ABI tag), so type-shaped bodies stay on the folder. Default parameter values are
likewise refused rather than silently read from uninitialised registers.

- **Regressions:** `tests/staged/staged_vm_test.lm` (loop, local mutation, self-recursion, a nested
  staged call inside a loop, and an enum argument folded on the VM under a loop), and
  `tests/negative/staged/staged_vm_{host_call,opcode,instruction_budget}.lm`. Under
  `LYMAR_STAGE0_FORCE_VM=1` `tests/staged/staged_enum_test.lm` folds its enum-valued arguments on the
  VM and prints the same result the folder produces.
