# Namespace Refactoring Guide

## Overview
This document describes the refactoring of the Limit language codebase to use a unified namespace hierarchy `LM::`.

## New Namespace Structure

```
LM::
├── Frontend::              # Language frontend (lexer/parser)
│   ├── Scanner            # Tokenization
│   ├── Parser             # Parsing
│   ├── CST::              # Concrete Syntax Tree
│   │   ├── Node           # CST nodes
│   │   ├── Printer        # CST printing
│   │   └── Utils          # CST utilities
│   ├── ASTBuilder         # AST construction
│   ├── TypeChecker        # Type checking
│   ├── MemoryChecker      # Memory safety checking
│   └── ASTOptimizer       # AST optimization
│
├── Backend::              # Language backend
│   ├── VM::               # Virtual machine
│   │   └── Register       # Register-based VM
│   ├── JIT::              # Just-In-Time compilation
│   │   ├── Backend        # JIT backend
│   │   └── Compiler       # JIT compiler
│   ├── SymbolTable        # Symbol table management
│   ├── Value              # Runtime values
│   ├── ASTPrinter         # AST printing
│   ├── Channel            # Channel communication
│   ├── Fiber              # Fiber/task management
│   ├── Task               # Task definitions
│   ├── Scheduler          # Task scheduling
│   └── CodeFormatter      # Code formatting
│
├── Memory::               # Memory management and safety
│   ├── Model              # Memory model definitions
│   ├── Compiler           # Compile-time memory checking
│   └── Runtime            # Runtime memory management
│
├── LIR::                  # Low-level Intermediate Representation
│   ├── Instruction        # LIR instructions
│   ├── Utils              # LIR utilities
│   ├── Generator          # LIR generation
│   ├── Functions          # Function handling
│   ├── BuiltinFunctions   # Built-in functions
│   ├── Types              # LIR type system
│   └── FunctionRegistry   # Function registry
│
├── Error::                # Error handling system
│   ├── Formatter          # Error formatting
│   ├── CodeGenerator      # Error code generation
│   ├── HintProvider       # Contextual hints
│   ├── SourceFormatter    # Source formatting
│   ├── ConsoleFormatter   # Console output
│   ├── Catalog            # Error catalog
│   ├── ErrorHandling      # Error handling utilities
│   ├── ErrorMessage       # Error message types
│   ├── EnhancedReporting  # Enhanced error reporting
│   └── IDEFormatter       # IDE-specific formatting
│
└── Debug::                # Debugging utilities
    └── Debugger           # Debugger implementation
```

## File Migration Map

### Frontend Files
| Old Path | New Path | Namespace |
|----------|----------|-----------|
| src/frontend/scanner.cpp | src/lm/frontend/scanner.cpp | LM::Frontend |
| src/frontend/parser.cpp | src/lm/frontend/parser.cpp | LM::Frontend |
| src/frontend/ast.hh | src/lm/frontend/ast.hh | LM::Frontend |
| src/frontend/ast_builder.cpp | src/lm/frontend/ast_builder.cpp | LM::Frontend |
| src/frontend/type_checker.cpp | src/lm/frontend/type_checker.cpp | LM::Frontend |
| src/frontend/memory_checker.cpp | src/lm/frontend/memory_checker.cpp | LM::Frontend |
| src/frontend/ast_optimizer.cpp | src/lm/frontend/ast_optimizer.cpp | LM::Frontend |
| src/frontend/cst.cpp | src/lm/frontend/cst/node.cpp | LM::Frontend::CST |
| src/frontend/cst_printer.cpp | src/lm/frontend/cst/printer.cpp | LM::Frontend::CST |
| src/frontend/cst_utils.cpp | src/lm/frontend/cst/utils.cpp | LM::Frontend::CST |

### Backend Files
| Old Path | New Path | Namespace |
|----------|----------|-----------|
| src/backend/symbol_table.cpp | src/lm/backend/symbol_table.cpp | LM::Backend |
| src/backend/value.cpp | src/lm/backend/value.cpp | LM::Backend |
| src/backend/ast_printer.cpp | src/lm/backend/ast_printer.cpp | LM::Backend |
| src/backend/register/register.cpp | src/lm/backend/vm/register.cpp | LM::Backend::VM |
| src/backend/jit/jit_backend.cpp | src/lm/backend/jit/backend.cpp | LM::Backend::JIT |
| src/backend/jit/jit.cpp | src/lm/backend/jit/compiler.cpp | LM::Backend::JIT |

### Memory Files
| Old Path | New Path | Namespace |
|----------|----------|-----------|
| src/memory/model.hh | src/lm/memory/model.hh | LM::Memory |
| src/memory/compiler.hh | src/lm/memory/compiler.hh | LM::Memory |
| src/memory/runtime.hh | src/lm/memory/runtime.hh | LM::Memory |

### LIR Files
| Old Path | New Path | Namespace |
|----------|----------|-----------|
| src/lir/lir.cpp | src/lm/lir/instruction.cpp | LM::LIR |
| src/lir/lir_utils.cpp | src/lm/lir/utils.cpp | LM::LIR |
| src/lir/generator.cpp | src/lm/lir/generator.cpp | LM::LIR |
| src/lir/functions.cpp | src/lm/lir/functions.cpp | LM::LIR |
| src/lir/builtin_functions.cpp | src/lm/lir/builtin_functions.cpp | LM::LIR |
| src/lir/lir_types.cpp | src/lm/lir/types.cpp | LM::LIR |
| src/lir/function_registry.cpp | src/lm/lir/function_registry.cpp | LM::LIR |

### Error System Files
| Old Path | New Path | Namespace |
|----------|----------|-----------|
| src/error/error_formatter.cpp | src/lm/error/formatter.cpp | LM::Error |
| src/error/error_code_generator.cpp | src/lm/error/code_generator.cpp | LM::Error |
| src/error/contextual_hint_provider.cpp | src/lm/error/hint_provider.cpp | LM::Error |
| src/error/source_code_formatter.cpp | src/lm/error/source_formatter.cpp | LM::Error |
| src/error/console_formatter.cpp | src/lm/error/console_formatter.cpp | LM::Error |
| src/error/error_catalog.cpp | src/lm/error/catalog.cpp | LM::Error |

### Debug Files
| Old Path | New Path | Namespace |
|----------|----------|-----------|
| src/common/debugger.cpp | src/lm/debug/debugger.cpp | LM::Debug |

## Migration Steps

### Phase 1: File Organization ✅
- [x] Create new directory structure under `src/lm/`
- [x] Copy all source files to new locations
- [x] Create master header `src/lm/lm.hh`

### Phase 2: Namespace Updates (IN PROGRESS)
- [ ] Update all header guards to use new paths
- [ ] Add namespace declarations to all files
- [ ] Update include paths in all files
- [ ] Update class/function names if needed

### Phase 3: Build System Updates
- [ ] Update Makefile with new file paths
- [ ] Update CMakeLists.txt with new file paths
- [ ] Verify compilation with new structure

### Phase 4: Cleanup
- [ ] Remove old source directories
- [ ] Update documentation
- [ ] Verify all tests pass

## Namespace Declaration Pattern

All files should follow this pattern:

```cpp
// Header files (.hh)
#ifndef LM_COMPONENT_HH
#define LM_COMPONENT_HH

namespace LM {
namespace ComponentNamespace {

// Declarations here

} // namespace ComponentNamespace
} // namespace LM

#endif // LM_COMPONENT_HH

// Implementation files (.cpp)
#include "lm/component.hh"

namespace LM {
namespace ComponentNamespace {

// Implementations here

} // namespace ComponentNamespace
} // namespace LM
```

## Include Path Updates

### Old Pattern
```cpp
#include "frontend/scanner.hh"
#include "backend/value.hh"
#include "lir/generator.hh"
```

### New Pattern
```cpp
#include "lm/frontend/scanner.hh"
#include "lm/backend/value.hh"
#include "lm/lir/generator.hh"
```

## Compilation Flags

Update compiler include paths:
```bash
# Old
-I. -Isrc/backend/jit

# New
-I. -Isrc/lm/backend/jit
```

## Testing

After refactoring:
1. Verify compilation: `make clean && make`
2. Run parser tests: `./bin/test_parser.exe tests/basic/print_statements.lm`
3. Run full test suite: `./tests/run_tests.bat`
4. Check for any remaining old includes or namespaces

## Notes

- The refactoring maintains backward compatibility through the master header `lm.hh`
- All functionality remains the same; only organization changes
- The namespace hierarchy makes code organization clearer and reduces naming conflicts
- Future additions should follow the established namespace structure
