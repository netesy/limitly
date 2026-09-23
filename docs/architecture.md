# Limit Architecture Overview

Limitly combines an expressive frontend pipeline with a low-level intermediate representation (LIR) and dual execution backends.

```
Source Code (.lm)
       │
       ▼
 ┌───────────┐
 │  Scanner  │ -> Tokens
 └─────┬─────┘
       │
       ▼
 ┌───────────┐
 │  Parser   │ -> Concrete Syntax Tree (CST) & Abstract Syntax Tree (AST)
 └─────┬─────┘
       │
       ▼
 ┌────────────────┐
 │ Module Manager │ -> Multi-file symbol graph resolution & import aliasing
 └─────┬──────────┘
       │
       ▼
 ┌──────────────┐
 │ Type Checker │ -> Static type inference, ErrorUnion checks, Contracts, Verification policy
 └─────┬────────┘
       │
       ▼
 ┌────────────────┐
 │ Memory Checker │ -> Region scope tracking, linear resource ownership validation
 └─────┬──────────┘
       │
       ▼
 ┌───────────────┐
 │ LIR Generator │ -> Lowers typed AST into register-based Limit Intermediate Representation
 └─────┬─────────┘
       │
       ├─────────────────────────────────┐
       ▼                                 ▼
 ┌───────────────┐               ┌───────────────┐
 │  Register VM  │ (run)         │ Fyra Backend  │ (build)
 │ Bytecode Exec │               │   AOT / WASM  │
 └───────────────┘               └───────────────┘
```

---

## 1. Compiler Pipeline

1. **Scanner (`src/frontend/scanner.*`)**:
   - Tokenizes UTF-8 input streams, tracks source locations (line and column), and extracts trivia and literals.
   - CLI Inspection: `limitly -tokens <source.lm>`

2. **Parser (`src/frontend/parser/`)**:
   - Top-down recursive descent parser with error recovery.
   - Emits both a Concrete Syntax Tree (CST) for tooling/formatting and an Abstract Syntax Tree (AST) for compiler analysis.
   - CLI Inspection: `limitly -cst <source.lm>` and `limitly -ast <source.lm>`

3. **Module Manager (`src/frontend/module_manager.*`)**:
   - Resolves module import graphs, path-to-identifier mappings, `show` filters, and `hide` exclusions across file boundaries.

4. **Type Checker (`src/frontend/type_checker/`)**:
   - Strongly enforces static types with local type inference.
   - Handles unified `Type?` ErrorUnions, traits, structural types, and pattern match exhaustive coverage.
   - Configurable verification policy (`--verify=strict` rejects unproven refinements; `--verify=hybrid` retains dynamic contract checks).

5. **Memory Checker (`src/frontend/memory_checker.*`)**:
   - Tracks lexical scope regions and lifetime bounds for deterministic memory management.

6. **LIR Generator (`src/lir/generator/`)**:
   - Lowers typed AST statements and expressions into flat, linear register-based instructions with 3-address operations.
   - Emits explicit basic blocks and control-flow graphs (CFG).
   - CLI Inspection: `limitly -lir <source.lm>`

7. **Dual Backends**:
   - **Bytecode Register VM (`src/backend/vm/register.*`)**: High-performance register-based virtual machine executing LIR instructions directly via the `run` command.
   - **Fyra Backend (`src/backend/fyra/`)**: Lowers LIR into Fyra IR for Ahead-of-Time (AOT) machine code compilation (X86_64, AArch64) or WebAssembly (`wasm32`) via the `build` command.

---

## 2. Memory Model

Limitly implements a **region-based, deterministic memory model**:
- Every lexical block (function, loop, compound block) constitutes a region.
- Allocations made within a region are owned by that region's lifetime.
- When execution exits a lexical scope, region allocations are reclaimed deterministically.
- Move semantics transfer ownership between regions without heap tracing overhead.

---

## 3. Concurrency Model

Limitly enforces **Structured Concurrency**:
- **`parallel` blocks**: Fork/join data parallelism across CPU cores, operating on compiler-verified disjoint slice capabilities.
- **`concurrent` blocks**: Cooperative asynchronous concurrency for I/O operations and workers.
- **Typed Channels**: Communication primitive (`channel()`, `.send()`, `.receive()`) ensuring tasks communicate without unsynchronized shared mutable memory.
