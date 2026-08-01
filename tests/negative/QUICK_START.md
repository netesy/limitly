# Negative Testing Quick Start

## What Are Negative Tests?

Negative tests verify that the compiler **correctly rejects invalid programs**. A passing negative test means:
- The compiler detected an error ✓
- The compiler reported the right error type ✓
- The program was not executed ✓

## Running Tests

### 1. Build the compiler
```bash
make clean && make
```

### 2. Run negative tests
```bash
# Windows
tests\negative\run_negative_tests.bat

# Linux/macOS
./tests/negative/run_negative_tests.sh
```

### 3. View results
```
[TYPE_SAFETY] 4 tests
  ✓ PASS: type_mismatch_arithmetic.lm
          Error: type_error
  ✓ PASS: type_mismatch_assignment.lm
          Error: type_error
  ✗ FAIL: function_arg_type_mismatch.lm
          Output: Expected error not detected

[BOUNDS_CHECKING] 2 tests
  ✓ PASS: array_index_out_of_bounds.lm
  ...

SUMMARY: 18 PASSED, 6 FAILED
```

## Test Categories

```
tests/negative/
├── type_safety/           - Type system enforcement
├── bounds_checking/       - Array bounds, overflow
├── control_flow/          - break/continue/return validation
├── patterns/              - Pattern matching exhaustiveness
├── soundness/             - Memory safety invariants
├── visibility/            - Access control
├── closures/              - Closure capture rules
├── arithmetic/            - Arithmetic safety (div by zero)
├── syntax/                - Parser error detection
├── traits/                - Trait implementation
└── memory/                - Resource management
```

## Adding a New Test

1. **Choose category** (or create new one if needed)
2. **Create .lm file** with error annotation:
   ```limit
   // @error:error_category
   // Description of what should fail
   
   // Invalid code that should cause error
   ```
3. **Run tests** to verify it's discovered and fails correctly

### Example: New type safety test
```limit
// @error:type_error
// Cannot compare incompatible types

var x: str = "hello";
if (x > 5) {  // ERROR: Cannot compare string with int
    print("This should not compile");
}
```

Then run:
```bash
python tests/negative/run_negative_tests.py -c type_safety
```

## Troubleshooting

### Tests not discovered
```bash
python tests/negative/run_negative_tests.py --list
# Check if your test appears in the list
```

### Test unexpectedly passes
If a negative test passes (no error detected), the compiler might be accepting invalid code:
1. Check test is in correct directory
2. Verify error annotation is present
3. Check if code is actually invalid
4. May be a compiler bug - report it!

### Need verbose output
```bash
python tests/negative/run_negative_tests.py -v
# Shows full error messages for debugging
```

## Common Errors to Test

### Type Errors
```limit
// @error:type_error
var x: int = "not an int";
```

### Bounds Errors
```limit
// @error:bounds_error
var arr = [1, 2, 3];
var x = arr[100];
```

### Control Flow Errors
```limit
// @error:break_outside_loop
break;
```

### Memory Safety
```limit
// @error:uninitialized
var x: int;
print(x);
```

### Visibility
```limit
// @error:visibility_error
frame Secret { name: str }
var s = Secret { name: "x" };
print(s.name);
```

## Integration with CI/CD

Add to continuous integration:

```bash
#!/bin/bash
set -e  # Exit on first error

# Build
make clean && make

# Positive tests (should all pass)
python tests/run_tests.py

# Negative tests (should correctly fail)
python tests/negative/run_negative_tests.py

# If we got here, all tests passed
echo "✓ All tests passed!"
```

## Expected Baseline

Current status: **24 negative tests implemented**

```
Type Safety:        4/9 tests      (44% coverage)
Memory Safety:      4/8 tests      (50% coverage)
Control Flow:       3/4 tests      (75% coverage)
Bounds Checking:    2/6 tests      (33% coverage)
Pattern Matching:   2/3 tests      (67% coverage)
Visibility:         2/4 tests      (50% coverage)
Closures:           1/4 tests      (25% coverage)
Arithmetic:         2/5 tests      (40% coverage)
Syntax:             2/4 tests      (50% coverage)
Traits:             1/5 tests      (20% coverage)
Resource Mgmt:      1/4 tests      (25% coverage)
```

## Performance Tips

### Running specific category (faster)
```bash
python tests/negative/run_negative_tests.py -c type_safety
```

### Running in CI with timeout
```bash
timeout 300 python tests/negative/run_negative_tests.py
```

## Documentation

- `README.md` - Complete negative testing guide
- `SOUNDNESS_TESTING_PLAN.md` - Multi-phase testing strategy
- `../../.kiro/steering/PHASE3_IMPLEMENTATION_INDEX.md` - Phase 3 implementation

## Next Steps

1. ✅ Review negative tests that currently run
2. ✅ Add missing test categories
3. 🔄 Implement fuzzing (Phase 3)
4. 🔄 Add property-based tests (Phase 4)

## Quick Commands Reference

```bash
# Run all negative tests
python tests/negative/run_negative_tests.py

# Run specific category
python tests/negative/run_negative_tests.py -c type_safety

# Verbose output
python tests/negative/run_negative_tests.py -v

# List all tests
python tests/negative/run_negative_tests.py --list

# Run only syntax tests
python tests/negative/run_negative_tests.py -c syntax

# Run on Linux with custom limitly path
python tests/negative/run_negative_tests.py -p ./bin/limitly
```

## Support

For issues or questions:
1. Check `README.md` for detailed documentation
2. Review error categories in `run_negative_tests.py`
3. Look at existing tests for examples
4. Check `SOUNDNESS_TESTING_PLAN.md` for architecture
