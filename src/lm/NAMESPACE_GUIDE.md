# LM:: Namespace Guide

## Overview

The Limit language compiler is organized under the `LM::` namespace hierarchy. This document explains the structure and how to use it.

## Namespace Hierarchy

```
LM::
├── Frontend::              # Language frontend (lexer/parser)
├── Backend::               # Language backend (VM/JIT)
├── Memory::                # Memory management and safety
├── LIR::                   # Low-level Intermediate Representation
├── Error::                 # Error handling system
└── Debug::                 # Debugging utilities
```

## Using the Master Header

The easiest way to include all LM components is to use the master header:

```cpp
#include "lm/lm.hh"

// Now you can use all LM components
using namespace LM;
using namespace LM::Frontend;
using namespace LM::Backend;
// etc.
```

## Component-Specific Includes

### Frontend Components

```cpp
#include "lm/frontend/scanner.hh"      // LM::Frontend::Scanner
#include "lm/frontend/parser.hh"       // LM::Frontend::Parser
#include "lm/frontend/ast.hh"          // LM::Frontend::AST nodes
#include "lm/frontend/ast_builder.hh"  // LM::Frontend::ASTBuilder
#include "lm/frontend/type_checker.hh" // LM::Frontend::TypeChecker
#include "lm/frontend/memory_checker.hh" // LM::Frontend::MemoryChecker
#include "lm/frontend/ast_optimizer.hh" // LM::Frontend::ASTOptimizer

// CST (Concrete Syntax Tree)
#include "lm/frontend/cst/node.hh"     // LM::Frontend::CST::Node
#include "lm/frontend/cst/printer.hh"  // LM::Frontend::CST::Printer
#include "lm/frontend/cst/utils.hh"    // LM::Frontend::CST utilities
```

### Backend Components

```cpp
#include "lm/backend/symbol_table.hh"  // LM::Backend::SymbolTable
#include "lm/backend/value.hh"         // LM::Backend::Value
#include "lm/backend/types.hh"         // LM::Backend type definitions
#include "lm/backend/ast_printer.hh"   // LM::Backend::ASTPrinter

// Virtual Machine
#include "lm/backend/vm/register.hh"   // LM::Backend::VM::Register

// JIT Compilation
#include "lm/backend/jit/compiler.hh"  // LM::Backend::JIT::Compiler
#include "lm/backend/jit/backend.hh"   // LM::Backend::JIT::Backend

// Concurrency
#include "lm/backend/channel.hh"       // LM::Backend::Channel
#include "lm/backend/fiber.hh"         // LM::Backend::Fiber
#include "lm/backend/task.hh"          // LM::Backend::Task
#include "lm/backend/scheduler.hh"     // LM::Backend::Scheduler
```

### Memory Management Components

```cpp
#include "lm/memory/model.hh"          // LM::Memory::Model
#include "lm/memory/compiler.hh"       // LM::Memory::Compiler
#include "lm/memory/runtime.hh"        // LM::Memory::Runtime
```

### LIR Components

```cpp
#include "lm/lir/instruction.hh"       // LM::LIR::Instruction
#include "lm/lir/utils.hh"             // LM::LIR utilities
#include "lm/lir/generator.hh"         // LM::LIR::Generator
#include "lm/lir/functions.hh"         // LM::LIR function utilities
#include "lm/lir/builtin_functions.hh" // LM::LIR built-in functions
#include "lm/lir/types.hh"             // LM::LIR type system
#include "lm/lir/function_registry.hh" // LM::LIR::FunctionRegistry
```

### Error Handling Components

```cpp
#include "lm/error/formatter.hh"       // LM::Error::Formatter
#include "lm/error/code_generator.hh"  // LM::Error::CodeGenerator
#include "lm/error/hint_provider.hh"   // LM::Error::HintProvider
#include "lm/error/source_formatter.hh" // LM::Error::SourceFormatter
#include "lm/error/console_formatter.hh" // LM::Error::ConsoleFormatter
#include "lm/error/catalog.hh"         // LM::Error::Catalog
#include "lm/error/error_handling.hh"  // LM::Error utilities
```

### Debug Components

```cpp
#include "lm/debug/debugger.hh"        // LM::Debug::Debugger
```

## Usage Examples

### Example 1: Using the Scanner

```cpp
#include "lm/frontend/scanner.hh"

using namespace LM::Frontend;

int main() {
    std::string source = "var x = 42;";
    Scanner scanner(source);
    auto tokens = scanner.scanTokens();
    
    for (const auto& token : tokens) {
        std::cout << token.lexeme << std::endl;
    }
    
    return 0;
}
```

### Example 2: Using the Parser

```cpp
#include "lm/frontend/parser.hh"
#include "lm/frontend/scanner.hh"

using namespace LM::Frontend;

int main() {
    std::string source = "fn add(a: int, b: int) -> int { return a + b; }";
    Scanner scanner(source);
    auto tokens = scanner.scanTokens();
    
    Parser parser(tokens);
    auto ast = parser.parse();
    
    // Use AST...
    return 0;
}
```

### Example 3: Using the Type Checker

```cpp
#include "lm/frontend/type_checker.hh"
#include "lm/frontend/parser.hh"
#include "lm/frontend/scanner.hh"

using namespace LM::Frontend;

int main() {
    std::string source = "var x: int = 42;";
    Scanner scanner(source);
    auto tokens = scanner.scanTokens();
    
    Parser parser(tokens);
    auto ast = parser.parse();
    
    TypeChecker checker;
    auto typedAst = checker.check(ast);
    
    return 0;
}
```

### Example 4: Using the LIR Generator

```cpp
#include "lm/lir/generator.hh"
#include "lm/frontend/type_checker.hh"

using namespace LM::LIR;
using namespace LM::Frontend;

int main() {
    // ... parse and type check ...
    
    Generator generator;
    auto lir = generator.generate(typedAst);
    
    // Use LIR instructions...
    return 0;
}
```

### Example 5: Using the Register VM

```cpp
#include "lm/backend/vm/register.hh"
#include "lm/lir/generator.hh"

using namespace LM::Backend::VM;
using namespace LM::LIR;

int main() {
    // ... generate LIR ...
    
    Register vm;
    vm.execute(lir);
    
    return 0;
}
```

## Namespace Conventions

### Naming Conventions

- **Classes**: PascalCase (e.g., `Scanner`, `Parser`, `TypeChecker`)
- **Functions**: camelCase (e.g., `scanTokens`, `parseExpression`)
- **Constants**: UPPER_SNAKE_CASE (e.g., `TOKEN_EOF`, `MAX_STACK_SIZE`)
- **Enums**: PascalCase for enum class, UPPER_SNAKE_CASE for values

### File Organization

- Each namespace has its own directory
- Header files use `.hh` extension
- Implementation files use `.cpp` extension
- Related components are grouped in subdirectories

### Header Guard Pattern

```cpp
#ifndef LM_COMPONENT_HH
#define LM_COMPONENT_HH

namespace LM {
namespace ComponentNamespace {

// Declarations

} // namespace ComponentNamespace
} // namespace LM

#endif // LM_COMPONENT_HH
```

## Adding New Components

When adding new components to the LM compiler:

1. **Create the directory** under the appropriate namespace:
   ```
   src/lm/namespace/component/
   ```

2. **Create header and implementation files**:
   ```
   src/lm/namespace/component/component.hh
   src/lm/namespace/component/component.cpp
   ```

3. **Use proper namespace declarations**:
   ```cpp
   namespace LM {
   namespace Namespace {
   namespace Component {
   
   // Your code here
   
   } // namespace Component
   } // namespace Namespace
   } // namespace LM
   ```

4. **Update the master header** (`src/lm/lm.hh`):
   ```cpp
   #include "namespace/component/component.hh"
   ```

5. **Update the Makefile** with the new source files

## Migration from Old Structure

If you're migrating code from the old structure:

### Old Include
```cpp
#include "frontend/scanner.hh"
```

### New Include
```cpp
#include "lm/frontend/scanner.hh"
```

### Old Namespace Usage
```cpp
// No namespace (global scope)
Scanner scanner(source);
```

### New Namespace Usage
```cpp
using namespace LM::Frontend;
Scanner scanner(source);

// Or fully qualified
LM::Frontend::Scanner scanner(source);
```

## Best Practices

1. **Use the master header for convenience**:
   ```cpp
   #include "lm/lm.hh"
   ```

2. **Use namespace aliases for clarity**:
   ```cpp
   namespace Frontend = LM::Frontend;
   namespace Backend = LM::Backend;
   ```

3. **Avoid `using namespace` in headers** (only in implementation files)

4. **Use fully qualified names in public APIs** for clarity

5. **Group related includes together**:
   ```cpp
   // Frontend
   #include "lm/frontend/scanner.hh"
   #include "lm/frontend/parser.hh"
   
   // Backend
   #include "lm/backend/value.hh"
   ```

## Troubleshooting

### Compilation Errors

**Error**: `error: 'Scanner' is not a member of 'LM::Frontend'`

**Solution**: Make sure you're using the correct namespace:
```cpp
using namespace LM::Frontend;
// or
LM::Frontend::Scanner scanner(source);
```

**Error**: `fatal error: lm/frontend/scanner.hh: No such file or directory`

**Solution**: Check that the file exists and the include path is correct. The compiler needs `-I.` flag to find files relative to the project root.

### Include Path Issues

Make sure your build system includes the project root in the include path:
```bash
g++ -I. -Isrc/lm/backend/jit -c myfile.cpp
```

## References

- See `NAMESPACE_REFACTORING.md` for the complete migration plan
- See individual component documentation for API details
- See `src/lm/lm.hh` for the master header
