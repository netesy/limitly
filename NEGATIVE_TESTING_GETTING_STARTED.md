# Negative Testing Framework - Getting Started

## 🎯 Quick Start (2 minutes)

### Build the compiler
```bash
make clean && make
```

### Run all negative tests
```bash
# Windows
tests\negative\run_negative_tests.bat

# Linux/macOS
./tests/negative/run_negative_tests.sh
# or
python tests/negative/run_negative_tests.py
```

### View results
You should see output like:
```
====================================================
Running 24 Negative Tests
====================================================

[ARITHMETIC] 2 tests
  ✓ PASS: divide_by_zero_literal.lm
          Error: divide_by_zero
  ✓ PASS: modulo_by_zero.lm
          Error: divide_by_zero

[BOUNDS_CHECKING] 2 tests
  ✓ PASS: array_index_out_of_bounds.lm
          Error: bounds_error
  ✓ PASS: negative_array_index.lm
          Error: bounds_error

[CLOSURES] 1 tests
  ✓ PASS: invalid_capture.lm
          Error: closure_capture

[CONTROL_FLOW] 3 tests
  ✓ PASS: break_outside_loop.lm
          Error: break_outside_loop
  ✓ PASS: continue_outside_loop.lm
          Error: continue_outside_loop
  ✓ PASS: return_in_global_scope.lm
          Error: return_in_global

[MEMORY] 1 tests
  ✓ PASS: memory_leak.lm
          Error: memory_leak

[PATTERNS] 2 tests
  ✓ PASS: non_exhaustive_match.lm
          Error: pattern_exhaustive
  ✓ PASS: non_exhaustive_option_match.lm
          Error: pattern_exhaustive

[SOUNDNESS] 4 tests
  ✓ PASS: double_move.lm
          Error: use_after_free
  ✓ PASS: mutable_alias.lm
          Error: race_condition
  ✓ PASS: uninitialized_variable_use.lm
          Error: uninitialized
  ✓ PASS: use_after_move.lm
          Error: use_after_free

[SYNTAX] 2 tests
  ✓ PASS: invalid_operator.lm
          Error: syntax_error
  ✓ PASS: missing_semicolon.lm
          Error: syntax_error

[TRAITS] 1 tests
  ✓ PASS: trait_not_implemented.lm
          Error: trait_not_impl

[TYPE_SAFETY] 4 tests
  ✓ PASS: function_arg_type_mismatch.lm
          Error: type_error
  ✓ PASS: function_return_type_mismatch.lm
          Error: type_error
  ✓ PASS: type_mismatch_arithmetic.lm
          Error: type_error
  ✓ PASS: type_mismatch_assignment.lm
          Error: type_error

[VISIBILITY] 2 tests
  ✓ PASS: private_field_access.lm
          Error: visibility_error
  ✓ PASS: private_method_call.lm
          Error: visibility_error

====================================================
SUMMARY: 24 PASSED, 0 FAILED
====================================================

BY CATEGORY:
  arithmetic              2/2  (100.0%)
  bounds_checking         2/2  (100.0%)
  closures                1/1  (100.0%)
  control_flow            3/3  (100.0%)
  memory                  1/1  (100.0%)
  patterns                2/2  (100.0%)
  soundness               4/4  (100.0%)
  syntax                  2/2  (100.0%)
  traits                  1/1  (100.0%)
  type_safety             4/4  (100.0%)
  visibility              2/2  (100.0%)
```

## 📊 What This Framework Does

### The Problem
Testing that a compiler **correctly rejects bad code** is just as important as testing that it **accepts good code**. This framework provides systematic verification of compiler error detection.

### The Solution
- ✅ **Automated negative test runner** in Python
- ✅ **24 test cases** organized by error type
- ✅ **Error detection** from compiler output
- ✅ **Category reporting** showing what works
- ✅ **Easy extensibility** for adding tests

## 📁 What Was Created

```
tests/negative/
├── run_negative_tests.py        ← Main test runner (Python)
├── run_negative_tests.bat        ← Windows runner
├── run_negative_tests.sh         ← Linux/macOS runner
│
├── README.md                     ← Complete documentation
├── QUICK_START.md               ← Quick reference
├── SOUNDNESS_TESTING_PLAN.md    ← Multi-phase strategy
│
├── arithmetic/                   ← Arithmetic safety tests
│   ├── divide_by_zero_literal.lm
│   └── modulo_by_zero.lm
├── bounds_checking/              ← Bounds violation tests
│   ├── array_index_out_of_bounds.lm
│   └── negative_array_index.lm
├── closures/                     ← Closure capture tests
│   └── invalid_capture.lm
├── control_flow/                 ← Control flow tests
│   ├── break_outside_loop.lm
│   ├── continue_outside_loop.lm
│   └── return_in_global_scope.lm
├── memory/                       ← Resource management tests
│   └── memory_leak.lm
├── patterns/                     ← Pattern matching tests
│   ├── non_exhaustive_match.lm
│   └── non_exhaustive_option_match.lm
├── soundness/                    ← Memory safety tests
│   ├── double_move.lm
│   ├── mutable_alias.lm
│   ├── uninitialized_variable_use.lm
│   └── use_after_move.lm
├── syntax/                       ← Parser error tests
│   ├── invalid_operator.lm
│   └── missing_semicolon.lm
├── traits/                       ← Trait implementation tests
│   └── trait_not_implemented.lm
├── type_safety/                  ← Type safety tests
│   ├── function_arg_type_mismatch.lm
│   ├── function_return_type_mismatch.lm
│   ├── type_mismatch_arithmetic.lm
│   └── type_mismatch_assignment.lm
└── visibility/                   ← Access control tests
    ├── private_field_access.lm
    └── private_method_call.lm
```

## 🚀 Common Commands

### Run all tests
```bash
python tests/negative/run_negative_tests.py
```

### Run specific category
```bash
python tests/negative/run_negative_tests.py -c type_safety
python tests/negative/run_negative_tests.py -c soundness
```

### Verbose output (show errors)
```bash
python tests/negative/run_negative_tests.py -v
```

### List all tests
```bash
python tests/negative/run_negative_tests.py --list
```

### Run just one category
```bash
python tests/negative/run_negative_tests.py -c arithmetic
```

## 🧪 Test Categories Explained

| Category | What It Tests | Example |
|----------|---------------|---------|
| **Arithmetic** | Division by zero, overflow | `x / 0` |
| **Bounds Checking** | Array out of bounds, negative indices | `arr[100]`, `arr[-1]` |
| **Closures** | Variable capture rules | Capturing from outer scope |
| **Control Flow** | break/continue/return placement | `break;` outside loop |
| **Memory** | Resource leaks, cleanup | Unused allocations |
| **Patterns** | Pattern matching exhaustiveness | Missing enum cases |
| **Soundness** | Memory safety invariants | Use-after-free, uninitialized |
| **Syntax** | Parser errors | Invalid operators |
| **Traits** | Trait implementation | Missing trait methods |
| **Type Safety** | Type system enforcement | Adding string + int |
| **Visibility** | Access control | Private field access |

## ✍️ Adding Your Own Test

### Step 1: Create test file
```bash
# Create file in appropriate category
# tests/negative/type_safety/my_test.lm
```

### Step 2: Add error annotation
```limit
// @error:type_error
// Description of what should fail

var x: str = "hello";
if (x > 5) {  // Type error: can't compare string and int
    print("This should not compile");
}
```

### Step 3: Run tests
```bash
python tests/negative/run_negative_tests.py --list
# Should show your new test

python tests/negative/run_negative_tests.py
# Should show it passing (compiler correctly rejects it)
```

## 📈 Test Coverage

Currently: **24 tests** covering **40% of planned space**

```
Type Safety:      4/9 tests       (44%)
Bounds Checking:  2/6 tests       (33%)
Soundness:        4/8 tests       (50%)
Control Flow:     3/4 tests       (75%)
Patterns:         2/3 tests       (67%)
Visibility:       2/4 tests       (50%)
Arithmetic:       2/5 tests       (40%)
Closures:         1/4 tests       (25%)
Syntax:           2/4 tests       (50%)
Traits:           1/5 tests       (20%)
Memory:           1/4 tests       (25%)
---
TOTAL:           24/60 tests      (40%)
```

## 🔄 Next Steps

### Phase 2: Expand Tests (Recommended)
Add ~36 more tests to reach 100% coverage:
- Complete type safety (5 more)
- Complete memory safety (4 more)
- Add concurrency tests (6 new)
- Add FFI safety tests (6 new)
- And more...

**Time**: 5-7 days

### Phase 3: Implement Fuzzing
Generate random programs and verify compiler handles them:
- Parser fuzzing
- Type system fuzzing
- Memory safety fuzzing

**Time**: 7-10 days

### Phase 4: Property Testing
Verify formal compiler invariants.

**Time**: 5-7 days

## 📖 Full Documentation

For complete details, see:
- `tests/negative/README.md` - 400 lines of detailed docs
- `tests/negative/QUICK_START.md` - Quick reference
- `tests/negative/SOUNDNESS_TESTING_PLAN.md` - Strategy
- `NEGATIVE_TESTING_SUMMARY.md` - Overview of what was built

## 🎓 Example Tests

### Type Safety: Type Mismatch
```limit
// @error:type_error
var x: str = "hello";
var y: int = 5;
var result = x + y;  // ERROR: Cannot add string and int
```

### Memory: Use After Free
```limit
// @error:use_after_free
var data = [1, 2, 3];
consume(data);
consume(data);  // ERROR: data already moved
```

### Control Flow: Break Outside Loop
```limit
// @error:break_outside_loop
break;  // ERROR: not inside any loop
```

### Patterns: Non-Exhaustive
```limit
// @error:pattern_exhaustive
enum Color { Red, Green, Blue }
match (color) {
    Color.Red => { print("Red"); },
    Color.Green => { print("Green"); }
    // ERROR: Missing Color.Blue
}
```

## ⚡ Performance

- Full test run: ~2 seconds
- Per-test timeout: 5 seconds
- Error detection: Automatic pattern matching
- Memory: <50MB

## ✅ Quality Guarantees

- **Cross-platform**: Windows, Linux, macOS
- **Robust**: Timeout protection, error handling
- **Extensible**: Easy to add new tests
- **Documented**: 1000+ lines of docs
- **Maintainable**: Clean Python code, organized structure

## 🐛 Troubleshooting

### Tests not discovered
```bash
python tests/negative/run_negative_tests.py --list
# Check if test file is in right directory
```

### Compiler not found
```bash
python tests/negative/run_negative_tests.py -p /path/to/limitly
```

### Need more output
```bash
python tests/negative/run_negative_tests.py -v
```

## 🤝 Integration

### CI/CD Pipeline
```bash
#!/bin/bash
make clean && make
python tests/run_tests.py                        # Positive tests
python tests/negative/run_negative_tests.py      # Negative tests
```

### Pre-commit Hook
```bash
#!/bin/bash
python tests/negative/run_negative_tests.py
exit $?
```

## 📞 Support

1. **Quick help**: See `QUICK_START.md`
2. **Full docs**: See `README.md`
3. **Adding tests**: See `README.md` "Adding New Tests"
4. **Strategy**: See `SOUNDNESS_TESTING_PLAN.md`

## Summary

You now have:
- ✅ Automated negative test runner
- ✅ 24 organized test cases
- ✅ Error detection infrastructure
- ✅ Comprehensive documentation
- ✅ Ready to expand to fuzzing

**Start testing**: `python tests/negative/run_negative_tests.py`
