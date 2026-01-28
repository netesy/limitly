# Memory Namespace Integration

## Overview

The memory management files have been integrated into the `LM::Memory::` namespace as part of the comprehensive namespace refactoring.

## Memory Files

The following memory management files have been migrated to `src/lm/memory/`:

### Files Migrated
- `src/memory/model.hh` → `src/lm/memory/model.hh`
- `src/memory/compiler.hh` → `src/lm/memory/compiler.hh`
- `src/memory/runtime.hh` → `src/lm/memory/runtime.hh`

## Namespace Structure

```
LM::Memory::
├── Model              # Memory model definitions
├── Compiler           # Compile-time memory checking
└── Runtime            # Runtime memory management
```

## Usage

### Including Memory Components

```cpp
#include "lm/memory/model.hh"      // LM::Memory::Model
#include "lm/memory/compiler.hh"   // LM::Memory::Compiler
#include "lm/memory/runtime.hh"    // LM::Memory::Runtime
```

### Using the Master Header

```cpp
#include "lm/lm.hh"

using namespace LM::Memory;
```

## Integration Points

### Frontend Integration
Memory checking is performed during the frontend phase:
- `LM::Frontend::MemoryChecker` uses `LM::Memory::Model` for memory safety analysis
- Compile-time memory validation happens before code generation

### Backend Integration
Runtime memory management is handled by:
- `LM::Backend::VM::Register` uses `LM::Memory::Runtime` for memory operations
- `LM::Backend::JIT::Compiler` uses `LM::Memory::Compiler` for JIT memory handling

### LIR Integration
Memory operations are represented in the LIR:
- `LM::LIR::Instruction` includes memory-related operations
- `LM::LIR::Generator` generates memory instructions from AST

## Memory Model Components

### Model (model.hh)
Defines the memory model for the Limit language:
- Memory regions and allocation strategies
- Ownership and borrowing rules
- Lifetime tracking

### Compiler (compiler.hh)
Compile-time memory checking:
- Static analysis of memory safety
- Lifetime verification
- Borrow checking

### Runtime (runtime.hh)
Runtime memory management:
- Allocation and deallocation
- Garbage collection
- Memory profiling

## Next Steps

1. **Add namespace declarations** to memory files:
   ```cpp
   namespace LM {
   namespace Memory {
   
   // Declarations
   
   } // namespace Memory
   } // namespace LM
   ```

2. **Update include paths** in files that use memory components:
   ```cpp
   // Old
   #include "memory/model.hh"
   
   // New
   #include "lm/memory/model.hh"
   ```

3. **Update references** to memory classes:
   ```cpp
   // Old
   Model model;
   
   // New
   LM::Memory::Model model;
   // or with using namespace
   using namespace LM::Memory;
   Model model;
   ```

## Related Documentation

- `NAMESPACE_REFACTORING.md` - Complete refactoring plan
- `src/lm/NAMESPACE_GUIDE.md` - Namespace usage guide
- `REFACTORING_STATUS.md` - Current refactoring status
