# Compile-Time Execution Architecture: Staged Metaprogramming (`staged`)

This document specifies the redesign and implementation of the compile-time execution mechanism in the Limitly compiler architecture, replacing legacy `comptime` constructs with a native `staged` construct.

---

## 1. AST & Grammar Specifications

The `staged` construct allows stage 0 compile-time evaluation using Limitly's native language syntax without introducing secondary macro DSLs, preprocessors, or generic syntax (`<T>`).

### EBNF Grammar Grammar Rules
```ebnf
StagedStatement     ::= "staged" ( BlockStatement | VarDeclaration | FunctionDeclaration | Statement ) ;
StagedBlock         ::= "staged" "{" Statement* "}" ;
StagedExpr          ::= "staged" ( "{" Statement* "}" | Expression ) ;
StagedParam         ::= "staged" Identifier ":" TypeAnnotation ;
StagedFnDeclaration ::= "staged" "fn" Identifier "(" FunctionParameters? ")" [ ":" TypeAnnotation ] BlockStatement ;
```

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

    // Parameter tagged for stage 0 evaluation
    struct StagedParam {
        std::string name;
        std::shared_ptr<TypeAnnotation> type;
        bool isStaged = true;
    };

    // Unified staged statement node
    struct StagedStatement : public Statement {
        std::shared_ptr<Statement> declaration;
        std::shared_ptr<BlockStatement> block;
        std::shared_ptr<Expression> expression;
    };
}
```

---

## 2. Compiler Pipeline Integration

Compile-time staged evaluation occurs strictly **DURING Semantic Analysis / Type Checking**, after initial AST parsing and symbol resolution, but before Lower Intermediate Representation (LIR) generation.

### Pipeline Flowchart

```
                  ┌───────────────────────────────┐
                  │          Parse AST            │
                  └───────────────┬───────────────┘
                                  │
                                  ▼
 ┌─────────────────────────────────────────────────────────────────┐
 │ PASS 1: Type Checking & Static Contract Checking                │
 │ - Check static contracts: contract(sizeof(T) == 16)             │
 │ - Verify staged function arguments and enum/union bounds        │
 └───────────────────────────────┬─────────────────────────────────┘
                                  │
                                  ▼
 ┌─────────────────────────────────────────────────────────────────┐
 │ PASS 2: Staged Evaluator (Compile-time Interpreter)             │
 │ - Execute staged { ... } blocks                                 │
 │ - Evaluate staged functions that return types/unions/enums      │
 │ - Replace staged AST nodes with concrete literal AST nodes       │
 └───────────────────────────────┬─────────────────────────────────┘
                                  │
                                  ▼
 ┌─────────────────────────────────────────────────────────────────┐
 │ PASS 3: Behavioral Contract Lowering                            │
 │ - Lower function preconditions: requires(x > 0)                 │
 │ - Lower function postconditions: ensures(result != null)        │
 │ - Inject explicit runtime guard/trap AST nodes into bodies      │
 └───────────────────────────────┬─────────────────────────────────┘
                                  │
                                  ▼
                  ┌───────────────────────────────┐
                  │       LIR / Bytecode Gen      │
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

```limit
// Define error enum discriminant
enum MathError {
    DivisionByZero,
    Overflow
}

// Staged function constructing a tailored Result tagged union
staged fn make_result_type(staged OkType: type, staged ErrType: enum) {
    staged {
        return type {
            is_ok: bool,
            ok_value: OkType,
            err_value: ErrType
        };
    }
}

// Specialized type instantiated at stage 0
type IntResult = staged make_result_type(int, MathError);

fn divide(a: int, b: int): IntResult {
    if (b == 0) {
        return IntResult { is_ok: false, ok_value: 0, err_value: MathError.DivisionByZero };
    }
    return IntResult { is_ok: true, ok_value: a / b, err_value: MathError.DivisionByZero };
}
```

### Example B: Enum-Driven Compile-Time Conditional Branch Stripping

Conditional branches evaluated inside `staged { ... }` blocks are resolved at stage 0. Unreached branches are stripped from the AST before LIR emission.

```limit
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
```limit
fn execute_sys_call() {
    print("Executing Linux syscall");
}
```

---

## 4. Safety & Sandboxing Rules

To prevent compile-time memory corruption, infinite loops, or host resource exhaustion, the `StagedEvaluator` enforces strict sandboxing bounds during stage 0 execution:

| Parameter | Limit | Enforcement Action |
| :--- | :--- | :--- |
| **Maximum Recursion Depth** | `1,000` stack frames | Aborts stage 0 pass with `SemanticError`: *"maximum recursion depth exceeded"* |
| **Maximum Loop / Instruction Cap** | `1,000,000` instructions | Aborts stage 0 pass with `SemanticError`: *"instruction limit exceeded"* |
| **Memory Allocation Bound** | `64 MB` total heap | Rejects compile-time allocation with `SemanticError`: *"allocation limit exceeded"* |
| **Isolation Boundary** | Sandboxed AST interpreter | No direct host system calls, host file system, or raw pointer operations permitted |

All AST nodes folded by `staged` evaluation must pass a re-validation pass in the `TypeChecker` to guarantee memory safety and semantic correctness prior to LIR generation.
