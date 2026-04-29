# Limit Architecture Overview

## 1. Compiler Pipeline

1. **Scanner**: Tokenizes source code, handling whitespace and trivia.
2. **Parser**: Produces a Concrete Syntax Tree (CST) and an Abstract Syntax Tree (AST).
3. **Module Manager**: Resolves symbols across files and manages imports.
4. **Type Checker**: Performs static analysis, type inference, and memory safety (linear types) validation.
5. **LIR Generator**: Lowers the AST into Limit Intermediate Representation (LIR).
6. **Backend**:
   - **Register VM**: Executes LIR directly for fast development cycles.
   - **Fyra AOT**: Compiles LIR to native machine code via the Fyra backend.

## 2. Memory Model

Limit uses a **region-based, deterministic memory model**. Every scope is a region. Linear types ensure single ownership, and the compiler tracks "generations" to prevent dangling references without the need for a garbage collector.

## 3. Concurrency Model

Limit implements **Structured Concurrency**. Fiber lifetimes are bound to the lexical scope of `concurrent` or `parallel` blocks. Communication is handled via typed channels.
