# Soundness Testing Plan for Limitly Language

## Objective

Establish a comprehensive soundness testing framework to verify that the Limitly compiler:
1. Correctly implements all memory safety guarantees
2. Enforces type safety invariants
3. Prevents undefined behavior
4. Rejects invalid programs with clear error messages

## Testing Phases

### Phase 1: Negative Test Infrastructure ✅ COMPLETE
- [x] Create Python test runner framework
- [x] Support for test categories and metadata
- [x] Error pattern detection
- [x] Batch/shell runners for Windows/Linux
- [x] Comprehensive README documentation

**Status**: Negative testing framework ready for use

### Phase 2: Deterministic Negative Tests (Current)

Organize existing negative test cases covering all safety invariants:

#### Type Safety (9+ tests)
- [x] Type mismatch in arithmetic operations
- [x] Type mismatch in assignments
- [x] Function argument type mismatches
- [x] Function return type mismatches
- [ ] Operator type constraints
- [ ] Collection element type checking
- [ ] Union type exhaustiveness
- [ ] Generic type constraints
- [ ] Trait implementation checking

#### Memory Safety (8+ tests)
- [x] Use of uninitialized variables
- [x] Double move/use-after-free
- [x] Use after move
- [x] Mutable aliasing violations
- [ ] Dangling pointer detection
- [ ] Null pointer dereference
- [ ] Scope escape detection
- [ ] Reference invalidation

#### Control Flow Safety (4+ tests)
- [x] Break outside loops
- [x] Continue outside loops
- [x] Return in global scope
- [ ] Break/continue in nested contexts
- [ ] Unreachable code detection
- [ ] Missing return paths

#### Bounds & Overflow (4+ tests)
- [x] Array index out of bounds
- [x] Negative array indices
- [ ] String bounds checking
- [ ] Dictionary key not found
- [ ] Integer overflow
- [ ] Allocation size overflow

#### Pattern Matching (3+ tests)
- [x] Non-exhaustive enum matches
- [x] Non-exhaustive option matches
- [ ] Unreachable patterns
- [ ] Pattern type mismatches

#### Visibility & Access Control (2+ tests)
- [x] Private field access
- [x] Private method calls
- [ ] Protected member violations
- [ ] Module export restrictions

#### Closures & Captures (1+ tests)
- [x] Invalid variable capture
- [ ] Lifetime violations in closures
- [ ] Mutable capture issues
- [ ] Move semantics in closures

#### Concurrency & Threading (Future)
- [ ] Data race detection
- [ ] Race condition in concurrent blocks
- [ ] Channel type mismatches
- [ ] Deadlock detection

#### FFI Safety (Future)
- [ ] Unsafe function calls without unsafe context
- [ ] Pointer type mismatches
- [ ] Native ABI violations
- [ ] Resource leak in FFI

#### Arithmetic Safety (Future)
- [x] Division by zero
- [x] Modulo by zero
- [ ] Negative shifts
- [ ] Overflow in math operations
- [ ] NaN/Inf handling

#### Syntax & Parsing (2+ tests)
- [x] Invalid operators
- [x] Missing semicolons
- [ ] Unmatched braces
- [ ] Invalid keywords
- [ ] Malformed expressions

#### Traits & Objects (1+ tests)
- [x] Trait not implemented
- [ ] Conflicting trait implementations
- [ ] Missing trait methods
- [ ] Wrong method signatures
- [ ] Inheritance violations

#### Resource Management (1+ tests)
- [x] Memory leak detection
- [ ] File handle leaks
- [ ] Lock deadlocks
- [ ] Channel cleanup

## Current Test Coverage

### By Category

| Category | Implemented | Total | Coverage |
|----------|-------------|-------|----------|
| Type Safety | 4 | 9 | 44% |
| Memory Safety | 4 | 8 | 50% |
| Control Flow | 3 | 4 | 75% |
| Bounds & Overflow | 2 | 6 | 33% |
| Pattern Matching | 2 | 3 | 67% |
| Visibility | 2 | 4 | 50% |
| Closures | 1 | 4 | 25% |
| Arithmetic | 2 | 5 | 40% |
| Syntax | 2 | 4 | 50% |
| Traits | 1 | 5 | 20% |
| Resource Mgmt | 1 | 4 | 25% |
| **TOTAL** | **24** | **60** | **40%** |

## Phase 3: Fuzzing Infrastructure (Planned)

After deterministic tests pass, implement fuzzing:

### Fuzzing Approach
1. **Parser Fuzzing**: Generate random valid/invalid syntax
2. **Type System Fuzzing**: Generate random type combinations
3. **Memory Safety Fuzzing**: Generate random allocation/deallocation patterns
4. **Expression Fuzzing**: Generate complex nested expressions
5. **Concurrency Fuzzing**: Generate concurrent programs with various patterns

### Tools
- [cargo-fuzz](https://github.com/rust-fuzz/cargo-fuzz) (if using Rust test harness)
- [LibFuzzer](https://llvm.org/docs/LibFuzzer/) (for C++ compiler)
- Custom Python fuzzer for quick iteration

### Success Criteria
- No crashes or hangs
- Deterministic output
- All detected errors report correct error type
- All valid programs execute successfully

## Phase 4: Property-Based Testing (Future)

Generate random valid programs and verify properties:

```python
@property(settings=settings(max_examples=1000))
def test_type_system_consistency(program):
    """All type-checked programs must execute without type errors"""
    compiled = compile(program)
    assert compiled.errors == []
    result = execute(compiled)
    assert result.success
```

## Test Execution Strategy

### Local Development
```bash
# Run all negative tests
python tests/negative/run_negative_tests.py

# Run specific category
python tests/negative/run_negative_tests.py -c type_safety

# Verbose output
python tests/negative/run_negative_tests.py -v

# List tests
python tests/negative/run_negative_tests.py --list
```

### CI/CD Pipeline
```bash
# Pre-commit
make clean && make
python tests/run_tests.py          # Positive tests
python tests/negative/run_negative_tests.py  # Negative tests

# Nightly
# + Fuzzing runs
# + Extended timeout tests
# + Performance regression tests
```

## Expected Test Results

### Baseline (Current)
- Positive tests: ~80 passing
- Negative tests: 24 implemented, expecting ~100% to correctly fail

### Maturity (After Phase 2)
- Positive tests: ~80 passing
- Negative tests: 60 implemented, expecting 95%+ correct failure rate

### Production Ready (After Phase 3-4)
- Positive tests: 100+ passing
- Negative tests: 100+ implemented, expecting 99%+ correct failure rate
- Fuzzing: 1M+ generated tests, 0 compiler crashes/hangs

## Critical Invariants to Verify

### Type System
```
∀ program p, type(p) = T ⟹ execute(p).result : T
∀ values a, b, binop(a, b) ⟹ type(a), type(b) compatible
```

### Memory Safety
```
∀ variable x, use(x) ⟹ initialized(x)
∀ reference r, deref(r) ⟹ ¬dropped(r)
∀ resource r, end_of_scope(r) ⟹ released(r) ∨ moved(r)
```

### Control Flow
```
∀ break, in_loop(break)
∀ continue, in_loop(continue)
∀ return, in_function(return)
```

### Pattern Matching
```
∀ match(e), patterns_cover(all_variants(type(e)))
```

## Success Metrics

### Quality Metrics
- Error detection rate: 99%+ of invalid programs caught
- False positive rate: <1% (valid programs rejected)
- Error message clarity: 4.5/5.0 average rating
- Compilation time: <100ms for average program

### Coverage Metrics
- Statement coverage: >95% of compiler code exercised
- Branch coverage: >90% of control flow tested
- Edge case coverage: All known edge cases tested

### Performance Metrics
- Compilation time: Linear with program size
- Memory usage: <500MB for typical programs
- Test execution: <5 minutes for full suite

## Related Documentation

- `README.md` - Negative test framework guide
- `tests/run_tests.py` - Positive test runner
- `.kiro/steering/PHASE3_IMPLEMENTATION_INDEX.md` - Phase 3 implementation
- `.kiro/steering/AGENTS.md` - Language specification

## Timeline

| Phase | Duration | Status |
|-------|----------|--------|
| Phase 1: Infrastructure | 1-2 days | ✅ Complete |
| Phase 2: Deterministic Tests | 5-7 days | 🔄 In Progress (40% complete) |
| Phase 3: Fuzzing | 7-10 days | 📋 Planned |
| Phase 4: Property Testing | 5-7 days | 📋 Planned |

## Next Steps

1. **Immediate** (Today)
   - Run framework on existing negative tests
   - Verify error detection works
   - Fix any test infrastructure issues

2. **Short Term** (This week)
   - Add remaining deterministic tests (36 more)
   - Achieve 100% test coverage for Phase 2
   - Run full deterministic test suite

3. **Medium Term** (Next 2 weeks)
   - Implement fuzzing harness
   - Generate corpus of test cases
   - Analyze and fix discovered issues

4. **Long Term** (Month 2)
   - Integrate into CI/CD
   - Set up nightly fuzzing
   - Establish performance baselines

## Questions for the Team

1. What level of error message precision do we need?
2. Should fuzzing run in CI or only on-demand?
3. Are there specific safety properties we should prioritize?
4. Do we need regression tests for known compiler bugs?
