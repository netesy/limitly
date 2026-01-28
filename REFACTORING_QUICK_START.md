# Namespace Refactoring - Quick Start Guide

## What Was Done

The Limit language codebase has been reorganized under a unified `LM::` namespace hierarchy. All 79 source files have been copied to their new locations in `src/lm/`.

### Directory Structure

```
src/lm/
├── frontend/              # LM::Frontend
│   ├── cst/              # LM::Frontend::CST
│   ├── scanner.hh/cpp
│   ├── parser.hh/cpp
│   ├── ast.hh
│   ├── ast_builder.hh/cpp
│   ├── type_checker.hh/cpp
│   ├── memory_checker.hh/cpp
│   └── ast_optimizer.hh/cpp
│
├── backend/               # LM::Backend
│   ├── vm/               # LM::Backend::VM
│   ├── jit/              # LM::Backend::JIT
│   ├── symbol_table.hh/cpp
│   ├── value.hh/cpp
│   ├── ast_printer.hh/cpp
│   ├── types.hh
│   ├── memory.hh
│   ├── env.hh
│   ├── channel.hh
│   ├── fiber.hh
│   ├── task.hh
│   ├── scheduler.hh
│   └── code_formatter.hh/cpp
│
├── memory/                # LM::Memory
│   ├── model.hh
│   ├── compiler.hh
│   └── runtime.hh
│
├── lir/                   # LM::LIR
│   ├── instruction.hh/cpp
│   ├── utils.hh/cpp
│   ├── generator.hh/cpp
│   ├── functions.hh/cpp
│   ├── builtin_functions.hh/cpp
│   ├── types.hh/cpp
│   └── function_registry.hh/cpp
│
├── error/                 # LM::Error
│   ├── formatter.hh/cpp
│   ├── code_generator.hh/cpp
│   ├── hint_provider.hh/cpp
│   ├── source_formatter.hh/cpp
│   ├── console_formatter.hh/cpp
│   ├── catalog.hh/cpp
│   ├── error_handling.hh/cpp
│   ├── error_message.hh
│   ├── enhanced_error_reporting.hh/cpp
│   └── ide_formatter.hh/cpp
│
├── debug/                 # LM::Debug
│   ├── debugger.hh/cpp
│
└── lm.hh                  # Master header
```

## What Needs to Be Done

### Step 1: Add Namespace Declarations

Each file needs to be wrapped in namespace declarations. Here's the pattern:

**Header files (.hh):**
```cpp
#ifndef LM_COMPONENT_HH
#define LM_COMPONENT_HH

namespace LM {
namespace ComponentNamespace {

// Your declarations here

} // namespace ComponentNamespace
} // namespace LM

#endif // LM_COMPONENT_HH
```

**Implementation files (.cpp):**
```cpp
#include "lm/component.hh"

namespace LM {
namespace ComponentNamespace {

// Your implementations here

} // namespace ComponentNamespace
} // namespace LM
```

### Step 2: Update Include Paths

Replace old includes with new ones:

```cpp
// Old
#include "frontend/scanner.hh"
#include "backend/value.hh"
#include "lir/generator.hh"

// New
#include "lm/frontend/scanner.hh"
#include "lm/backend/value.hh"
#include "lm/lir/generator.hh"
```

### Step 3: Update Header Guards

Change header guards to follow the new pattern:

```cpp
// Old
#ifndef SCANNER_H
#define SCANNER_H

// New
#ifndef LM_SCANNER_HH
#define LM_SCANNER_HH
```

## Automated Migration

A PowerShell script is provided to help with automated updates:

```bash
powershell -ExecutionPolicy Bypass -File migrate_namespaces.ps1
```

This script will:
- Update all include paths
- Update header guards
- Prepare files for manual namespace additions

## Manual Namespace Updates

After running the script, you'll need to manually add namespace declarations. Here's a checklist:

### Frontend (10 files)
- [ ] scanner.hh/cpp → `namespace LM::Frontend`
- [ ] parser.hh/cpp → `namespace LM::Frontend`
- [ ] ast.hh → `namespace LM::Frontend`
- [ ] ast_builder.hh/cpp → `namespace LM::Frontend`
- [ ] type_checker.hh/cpp → `namespace LM::Frontend`
- [ ] memory_checker.hh/cpp → `namespace LM::Frontend`
- [ ] ast_optimizer.hh/cpp → `namespace LM::Frontend`
- [ ] cst/node.hh/cpp → `namespace LM::Frontend::CST`
- [ ] cst/printer.hh/cpp → `namespace LM::Frontend::CST`
- [ ] cst/utils.hh/cpp → `namespace LM::Frontend::CST`

### Backend (7 files)
- [ ] symbol_table.hh/cpp → `namespace LM::Backend`
- [ ] value.hh/cpp → `namespace LM::Backend`
- [ ] ast_printer.hh/cpp → `namespace LM::Backend`
- [ ] vm/register.hh/cpp → `namespace LM::Backend::VM`
- [ ] jit/backend.hh/cpp → `namespace LM::Backend::JIT`
- [ ] jit/compiler.hh/cpp → `namespace LM::Backend::JIT`

### Memory (3 files)
- [ ] model.hh → `namespace LM::Memory`
- [ ] compiler.hh → `namespace LM::Memory`
- [ ] runtime.hh → `namespace LM::Memory`

### LIR (7 files)
- [ ] instruction.hh/cpp → `namespace LM::LIR`
- [ ] utils.hh/cpp → `namespace LM::LIR`
- [ ] generator.hh/cpp → `namespace LM::LIR`
- [ ] functions.hh/cpp → `namespace LM::LIR`
- [ ] builtin_functions.hh/cpp → `namespace LM::LIR`
- [ ] types.hh/cpp → `namespace LM::LIR`
- [ ] function_registry.hh/cpp → `namespace LM::LIR`

### Error (10 files)
- [ ] formatter.hh/cpp → `namespace LM::Error`
- [ ] code_generator.hh/cpp → `namespace LM::Error`
- [ ] hint_provider.hh/cpp → `namespace LM::Error`
- [ ] source_formatter.hh/cpp → `namespace LM::Error`
- [ ] console_formatter.hh/cpp → `namespace LM::Error`
- [ ] catalog.hh/cpp → `namespace LM::Error`
- [ ] error_handling.hh/cpp → `namespace LM::Error`
- [ ] error_message.hh → `namespace LM::Error`
- [ ] enhanced_error_reporting.hh/cpp → `namespace LM::Error`
- [ ] ide_formatter.hh/cpp → `namespace LM::Error`

### Debug (1 file)
- [ ] debugger.hh/cpp → `namespace LM::Debug`

## Testing the Refactoring

### 1. Verify Compilation
```bash
make clean
make
```

### 2. Run Tests
```bash
./tests/run_tests.bat
```

### 3. Check for Errors
Look for:
- Compilation errors (namespace issues)
- Linking errors (missing symbols)
- Runtime errors (initialization issues)

## Cleanup

Once everything compiles and tests pass:

```bash
# Remove old directories
rmdir /s /q src/frontend
rmdir /s /q src/backend
rmdir /s /q src/lir
rmdir /s /q src/error
rmdir /s /q src/memory
rmdir /s /q src/common
```

## Documentation

Several documentation files have been created:

1. **NAMESPACE_REFACTORING.md** - Complete migration plan with file mappings
2. **src/lm/NAMESPACE_GUIDE.md** - Usage guide with code examples
3. **MEMORY_NAMESPACE_INTEGRATION.md** - Memory namespace details
4. **REFACTORING_STATUS.md** - Current status and detailed checklist
5. **REFACTORING_QUICK_START.md** - This file

## Key Files

- **src/lm/lm.hh** - Master header that includes all components
- **migrate_namespaces.ps1** - Automated migration script
- **Makefile** - Updated with new file paths

## Usage After Refactoring

### Using the Master Header
```cpp
#include "lm/lm.hh"

using namespace LM;
using namespace LM::Frontend;
using namespace LM::Backend;
```

### Using Specific Components
```cpp
#include "lm/frontend/scanner.hh"
#include "lm/backend/value.hh"
#include "lm/lir/generator.hh"

using namespace LM::Frontend;
using namespace LM::Backend;
using namespace LM::LIR;
```

### Fully Qualified Names
```cpp
#include "lm/frontend/scanner.hh"

LM::Frontend::Scanner scanner(source);
```

## Troubleshooting

### Compilation Errors

**Error**: `error: 'Scanner' is not a member of 'LM::Frontend'`
- Make sure the namespace declaration is in the file
- Check that the header guard is correct

**Error**: `fatal error: lm/frontend/scanner.hh: No such file or directory`
- Verify the file exists in the new location
- Check that the include path is correct

### Include Path Issues

Make sure your build system includes the project root:
```bash
g++ -I. -c myfile.cpp
```

## Support

For detailed information, see:
- `NAMESPACE_REFACTORING.md` - Complete migration plan
- `src/lm/NAMESPACE_GUIDE.md` - Namespace usage guide
- `REFACTORING_STATUS.md` - Detailed status and checklist

## Summary

The refactoring provides:
- ✅ Organized namespace hierarchy
- ✅ Clear component separation
- ✅ Master header for convenience
- ✅ Automated migration tools
- ✅ Comprehensive documentation
- ✅ Backward compatibility through master header

All functionality remains the same; only the organization has changed.
