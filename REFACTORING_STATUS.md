# Namespace Refactoring Status

## Completed ✅

### Phase 1: Directory Structure
- [x] Created new `src/lm/` directory hierarchy
- [x] Created subdirectories for each namespace:
  - `src/lm/frontend/` with `cst/` subdirectory
  - `src/lm/backend/` with `vm/` and `jit/` subdirectories
  - `src/lm/memory/`
  - `src/lm/lir/`
  - `src/lm/error/`
  - `src/lm/debug/`

### Phase 2: File Migration
- [x] Copied all frontend files to `src/lm/frontend/`
- [x] Copied all backend files to `src/lm/backend/`
- [x] Copied all memory files to `src/lm/memory/`
- [x] Copied all LIR files to `src/lm/lir/`
- [x] Copied all error system files to `src/lm/error/`
- [x] Copied debug files to `src/lm/debug/`
- [x] Created master header `src/lm/lm.hh`

### Phase 3: Documentation
- [x] Created `NAMESPACE_REFACTORING.md` with complete migration plan
- [x] Created `src/lm/NAMESPACE_GUIDE.md` with usage examples
- [x] Created `migrate_namespaces.ps1` script for automated updates
- [x] Updated `Makefile` with new file paths

## In Progress 🔄

### Phase 4: Namespace Updates
The following files need namespace declarations added:

**Frontend Files**:
- [ ] `src/lm/frontend/scanner.hh/cpp` → `namespace LM::Frontend`
- [ ] `src/lm/frontend/parser.hh/cpp` → `namespace LM::Frontend`
- [ ] `src/lm/frontend/ast.hh` → `namespace LM::Frontend`
- [ ] `src/lm/frontend/ast_builder.hh/cpp` → `namespace LM::Frontend`
- [ ] `src/lm/frontend/type_checker.hh/cpp` → `namespace LM::Frontend`
- [ ] `src/lm/frontend/memory_checker.hh/cpp` → `namespace LM::Frontend`
- [ ] `src/lm/frontend/ast_optimizer.hh/cpp` → `namespace LM::Frontend`
- [ ] `src/lm/frontend/cst/node.hh/cpp` → `namespace LM::Frontend::CST`
- [ ] `src/lm/frontend/cst/printer.hh/cpp` → `namespace LM::Frontend::CST`
- [ ] `src/lm/frontend/cst/utils.hh/cpp` → `namespace LM::Frontend::CST`

**Backend Files**:
- [ ] `src/lm/backend/symbol_table.hh/cpp` → `namespace LM::Backend`
- [ ] `src/lm/backend/value.hh/cpp` → `namespace LM::Backend`
- [ ] `src/lm/backend/ast_printer.hh/cpp` → `namespace LM::Backend`
- [ ] `src/lm/backend/types.hh` → `namespace LM::Backend`
- [ ] `src/lm/backend/vm/register.hh/cpp` → `namespace LM::Backend::VM`
- [ ] `src/lm/backend/jit/backend.hh/cpp` → `namespace LM::Backend::JIT`
- [ ] `src/lm/backend/jit/compiler.hh/cpp` → `namespace LM::Backend::JIT`

**Memory Files**:
- [ ] `src/lm/memory/model.hh` → `namespace LM::Memory`
- [ ] `src/lm/memory/compiler.hh` → `namespace LM::Memory`
- [ ] `src/lm/memory/runtime.hh` → `namespace LM::Memory`

**LIR Files**:
- [ ] `src/lm/lir/instruction.hh/cpp` → `namespace LM::LIR`
- [ ] `src/lm/lir/utils.hh/cpp` → `namespace LM::LIR`
- [ ] `src/lm/lir/generator.hh/cpp` → `namespace LM::LIR`
- [ ] `src/lm/lir/functions.hh/cpp` → `namespace LM::LIR`
- [ ] `src/lm/lir/builtin_functions.hh/cpp` → `namespace LM::LIR`
- [ ] `src/lm/lir/types.hh/cpp` → `namespace LM::LIR`
- [ ] `src/lm/lir/function_registry.hh/cpp` → `namespace LM::LIR`

**Error System Files**:
- [ ] `src/lm/error/formatter.hh/cpp` → `namespace LM::Error`
- [ ] `src/lm/error/code_generator.hh/cpp` → `namespace LM::Error`
- [ ] `src/lm/error/hint_provider.hh/cpp` → `namespace LM::Error`
- [ ] `src/lm/error/source_formatter.hh/cpp` → `namespace LM::Error`
- [ ] `src/lm/error/console_formatter.hh/cpp` → `namespace LM::Error`
- [ ] `src/lm/error/catalog.hh/cpp` → `namespace LM::Error`
- [ ] `src/lm/error/error_handling.hh/cpp` → `namespace LM::Error`
- [ ] `src/lm/error/error_message.hh` → `namespace LM::Error`
- [ ] `src/lm/error/enhanced_error_reporting.hh/cpp` → `namespace LM::Error`
- [ ] `src/lm/error/ide_formatter.hh/cpp` → `namespace LM::Error`

**Debug Files**:
- [ ] `src/lm/debug/debugger.hh/cpp` → `namespace LM::Debug`

### Phase 5: Include Path Updates
All files need their include paths updated from old to new format:
- [ ] Update all `#include "frontend/..."` to `#include "lm/frontend/..."`
- [ ] Update all `#include "backend/..."` to `#include "lm/backend/..."`
- [ ] Update all `#include "lir/..."` to `#include "lm/lir/..."`
- [ ] Update all `#include "error/..."` to `#include "lm/error/..."`
- [ ] Update all `#include "common/..."` to `#include "lm/debug/..."`

### Phase 6: Header Guard Updates
All header files need updated header guards:
- [ ] Change from `#ifndef COMPONENT_H` to `#ifndef LM_COMPONENT_HH`
- [ ] Change from `#define COMPONENT_H` to `#define LM_COMPONENT_HH`
- [ ] Change from `#endif // COMPONENT_H` to `#endif // LM_COMPONENT_HH`

## Remaining Tasks 📋

### Phase 7: Build System Updates
- [ ] Verify Makefile compiles with new structure
- [ ] Update CMakeLists.txt with new file paths
- [ ] Test build on Windows (MSYS2)
- [ ] Test build on Linux

### Phase 8: Compilation and Testing
- [ ] Fix any compilation errors
- [ ] Run parser tests: `./bin/test_parser.exe tests/basic/print_statements.lm`
- [ ] Run full test suite: `./tests/run_tests.bat`
- [ ] Verify no regressions

### Phase 9: Cleanup
- [ ] Remove old `src/frontend/` directory
- [ ] Remove old `src/backend/` directory
- [ ] Remove old `src/lir/` directory
- [ ] Remove old `src/error/` directory
- [ ] Remove old `src/common/` directory (keep only if other files exist)
- [ ] Update all documentation

### Phase 10: Final Verification
- [ ] All tests pass
- [ ] No compilation warnings
- [ ] Documentation updated
- [ ] Examples work correctly

## File Renaming Summary

### Frontend Files
| Old Name | New Name | Namespace |
|----------|----------|-----------|
| cst.cpp | cst/node.cpp | LM::Frontend::CST |
| cst_printer.cpp | cst/printer.cpp | LM::Frontend::CST |
| cst_utils.cpp | cst/utils.cpp | LM::Frontend::CST |

### Backend Files
| Old Name | New Name | Namespace |
|----------|----------|-----------|
| jit_backend.cpp | jit/backend.cpp | LM::Backend::JIT |
| jit.cpp | jit/compiler.cpp | LM::Backend::JIT |
| register.cpp | vm/register.cpp | LM::Backend::VM |

### LIR Files
| Old Name | New Name | Namespace |
|----------|----------|-----------|
| lir.cpp | lir/instruction.cpp | LM::LIR |
| lir_utils.cpp | lir/utils.cpp | LM::LIR |
| lir_types.cpp | lir/types.cpp | LM::LIR |

### Error System Files
| Old Name | New Name | Namespace |
|----------|----------|-----------|
| error_formatter.cpp | error/formatter.cpp | LM::Error |
| error_code_generator.cpp | error/code_generator.cpp | LM::Error |
| contextual_hint_provider.cpp | error/hint_provider.cpp | LM::Error |
| source_code_formatter.cpp | error/source_formatter.cpp | LM::Error |
| error_catalog.cpp | error/catalog.cpp | LM::Error |

## Next Steps

1. **Run the migration script** (optional, for automated updates):
   ```bash
   powershell -ExecutionPolicy Bypass -File migrate_namespaces.ps1
   ```

2. **Manually update namespace declarations** in each file following the pattern in `NAMESPACE_GUIDE.md`

3. **Test compilation**:
   ```bash
   make clean
   make
   ```

4. **Run tests**:
   ```bash
   ./tests/run_tests.bat
   ```

5. **Fix any compilation errors** and update includes as needed

6. **Remove old directories** once everything compiles and tests pass

## Resources

- `NAMESPACE_REFACTORING.md` - Complete migration plan with file mappings
- `src/lm/NAMESPACE_GUIDE.md` - Usage guide and examples
- `migrate_namespaces.ps1` - Automated migration script
- `src/lm/lm.hh` - Master header file

## Notes

- The refactoring maintains backward compatibility through the master header
- All functionality remains the same; only organization changes
- The namespace hierarchy makes code organization clearer
- Future additions should follow the established namespace structure
- The old directories can be kept temporarily during migration for reference
