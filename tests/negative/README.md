# Negative Test Suite for Limitly Language

## Overview

The negative test suite verifies that the Limitly compiler correctly **rejects invalid programs** and reports appropriate errors. These tests are essential for validating the soundness of the type system, memory safety, and other compile-time checks.

## Philosophy

- **Negative tests MUST FAIL compilation** - A passing negative test means the compiler rejected invalid code
- **Each test represents one safety property** - Organized by what safety invariant is being tested
- **Error patterns are documented** - Each test specifies what error should occur

## Test Categories

### Type Safety (`type_safety/`)
Tests that the compiler enforces static typing:
- `type_mismatch_arithmetic.lm` - Cannot mix incompatible types in arithmetic
- `type_mismatch_assignment.lm` - Cannot assign wrong type to variable
- `function_arg_type_mismatch.lm` - Function arguments must match declared types
- `function_return_type_mismatch.lm` - Return values must match declared type

**Examples:**
```limit
// Type mismatch in arithmetic
var x: str = "hello";
var y: int = 5;
var result = x + y;  // ERROR: Cannot add string and int
```

### Bounds Checking (`bounds_checking/`)
Tests that array/collection bounds are enforced:
- `array_index_out_of_bounds.lm` - Index beyond array size
- `negative_array_index.lm` - Negative indices not allowed

**Examples:**
```limit
var arr = [1, 2, 3];
var x = arr[10];  // ERROR: Index out of bounds (only 0-2 valid)
var y = arr[-1];  // ERROR: Negative index
```

### Control Flow (`control_flow/`)
Tests that control flow statements are used correctly:
- `break_outside_loop.lm` - Break only valid inside loops
- `continue_outside_loop.lm` - Continue only valid inside loops
- `return_in_global_scope.lm` - Return only valid inside functions

**Examples:**
```limit
fn some_function() {
    break;  // ERROR: break not inside loop
}

var x = 5;
return x;  // ERROR: return not in function
```

### Pattern Matching (`patterns/`)
Tests pattern matching exhaustiveness:
- `non_exhaustive_match.lm` - All enum variants must be matched
- `non_exhaustive_option_match.lm` - Option types must handle Some and None

**Examples:**
```limit
enum Color { Red, Green, Blue }

match (color) {
    Color.Red => { print("Red"); },
    Color.Green => { print("Green"); }
    // ERROR: Missing Color.Blue case
}
```

### Memory Soundness (`soundness/`)
Tests memory safety invariants:
- `uninitialized_variable_use.lm` - Cannot use uninitialized variables
- `double_move.lm` - Cannot move same value twice
- `use_after_move.lm` - Cannot use value after it's moved
- `mutable_alias.lm` - Cannot have multiple mutable references

**Examples:**
```limit
var x: int;
print(x);  // ERROR: x not initialized

var data = [1, 2, 3];
consume(data);
consume(data);  // ERROR: data already moved (use-after-free)
```

### Visibility (`visibility/`)
Tests access control:
- `private_field_access.lm` - Cannot access private fields
- `private_method_call.lm` - Cannot call private methods

**Examples:**
```limit
frame Person {
    name: str,  // private by default
}

var p = Person { name: "Alice" };
print(p.name);  // ERROR: name is private
```

### Arithmetic Safety (`arithmetic/`)
Tests arithmetic error detection:
- `divide_by_zero_literal.lm` - Division by zero
- `modulo_by_zero.lm` - Modulo by zero

**Examples:**
```limit
var y = 10 / 0;  // ERROR: Division by zero
var z = 10 % 0;  // ERROR: Modulo by zero
```

## Test Metadata Format

Each test can specify expected error using a comment:

```limit
// @error:type_error
// Test description

// ... test code ...
```

Or using a JSON file (name.json):

```json
{
    "expected_error": "type_error",
    "description": "Test description"
}
```

## Running Tests

### Run all negative tests:
```bash
# Windows
tests\negative\run_negative_tests.bat

# Linux/macOS
./tests/negative/run_negative_tests.sh
```

### Run specific category:
```bash
python tests/negative/run_negative_tests.py -c type_safety
python tests/negative/run_negative_tests.py -c bounds_checking
```

### Verbose output:
```bash
python tests/negative/run_negative_tests.py -v
```

### List all tests:
```bash
python tests/negative/run_negative_tests.py --list
```

## Error Categories

The runner recognizes these error types:

- `type_error` - Type mismatch or incompatible operations
- `use_after_free` - Memory already freed/dropped
- `double_free` - Freeing already-freed memory
- `dangling_ref` - Reference to freed/dropped memory
- `uninitialized` - Use of uninitialized variable
- `bounds_error` - Array/string bounds violation
- `divide_by_zero` - Division or modulo by zero
- `overflow` - Arithmetic overflow
- `null_deref` - Null pointer dereference
- `race_condition` - Data race detected
- `break_outside_loop` - Break statement outside loop
- `continue_outside_loop` - Continue statement outside loop
- `return_in_global` - Return statement in global scope
- `pattern_exhaustive` - Non-exhaustive pattern match
- `closure_capture` - Invalid closure capture
- `memory_leak` - Resource leak
- `ffi_safety` - FFI safety violation
- `syntax_error` - Parser error
- `visibility_error` - Private member access
- `trait_not_impl` - Trait not implemented
- `const_expr` - Non-const expr in const context
- `generic_mismatch` - Generic type mismatch

## Adding New Tests

1. Create a `.lm` file in appropriate category subdirectory
2. Add error annotation at top:
   ```limit
   // @error:error_category
   // Description of what should fail
   ```
3. Write invalid code that demonstrates the error
4. Run: `python tests/negative/run_negative_tests.py --list` to verify it's discovered

Example:
```limit
// @error:type_error
// Cannot compare string with int

var x: str = "hello";
if (x > 5) {
    print("This should fail");
}
```

## Integration with CI/CD

Add to continuous integration pipeline:

```bash
# Build the compiler
make clean && make

# Run positive tests (should all pass)
python tests/run_tests.py

# Run negative tests (should all fail to compile)
python tests/negative/run_negative_tests.py

# If any test passes that should fail, CI fails
if [ $? -ne 0 ]; then
    exit 1
fi
```

## Future Enhancements

- [ ] Property-based testing with generated invalid programs
- [ ] Mutation testing to verify test coverage
- [ ] Machine learning to generate more negative tests
- [ ] Regression testing for compiler bugs
- [ ] Error message validation (check specific messages)
- [ ] Performance benchmarking for error detection

## Related Documentation

- `PHASE3_IMPLEMENTATION_INDEX.md` - Phase 3 implementation guide
- `../../.kiro/steering/AGENTS.md` - Language specification
- `../../.kiro/steering/syntax.md` - Language syntax reference
