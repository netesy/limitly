# Limit Language Evolution & Roadmap

This document outlines the current implementation status and future directions for the Limit programming language.

## 1. Implementation Status

### 1.1 Core Syntax & Control Flow
- **Variables**: `var` declarations with inference. (Implemented)
- **Functions**: `fn` with optional/default parameters. (Implemented)
- **Frames**: `frame` as primary object construct. (Implemented)
- **Loops**: `for`, `while`, `iter`, `loop`. (Implemented)

### 1.2 Type System
- **Primitive Types**: `int`, `uint`, `float`, `bool`, `str`, `nil`. (Implemented)
- **Optional System**: `Type?` (Implemented via ErrorUnions)
- **Union Types**: `Type1 | Type2`. (Implemented)
- **Structural Types**: `{ field: type }`. (Parser/AST: Implemented, Backend: Pending)

### 1.3 Concurrency
- **Structured Concurrency**: `concurrent` blocks and `task`. (Implemented)
- **Communication**: `channel` operations. (Implemented)
- **Parallelism**: `parallel` blocks. (Parser/AST: Implemented, Backend: Pending)

## 2. Roadmap

### 2.1 Short-Term (Current Focus)
- **First-Class Functions**: Lambdas and function-as-values.
- **Structural Type Backend**: Enabling field access and literals for structural types.
- **Standard Library Expansion**: Completing basic I/O and collection frameworks.

### 2.2 Medium-Term
- **Generics**: Parametric polymorphism for frames and functions.
- **Pattern Matching Destructuring**: Deep matching for lists and dictionaries.
- **Abstract/Final Enforcement**: Moving modifiers from stubs to enforced semantic rules.

### 2.3 Long-Term
- **AOT Performance**: Enhancing the Fyra backend for high-performance native binaries.
- **Package Management**: Official integration with Lyra.
- **IDE Support**: Full LSP implementation.
