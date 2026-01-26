# Old Parallel Blocks Test - Failure Analysis

## Why the Old Version Failed

The old `parallel_blocks.lm` test had multiple issues that prevented it from running:

### Issue #1: Type Mismatch in List Initialization ❌

**Code**:
```limit
var results: list = 0;
```

**Error**:
```
error[E200][SemanticError]: Type mismatch: expected List, found Int64
```

**Reason**: The type annotation says `list` but the initialization value is `0` (an Int64). Lists cannot be initialized with scalar values.

**Fix**: Use proper list initialization or use a channel:
```limit
var results = channel();  // ✅ Correct
```

---

### Issue #2: 2D List Type Annotation ❌

**Code**:
```limit
var matrix: list[100][100] = 0;
```

**Problem**: 
- `list[100][100]` is not valid syntax for 2D lists in Limit
- Trying to initialize with scalar `0`
- The type system doesn't support parameterized list types like this

**Fix**: Use channels or properly initialized lists:
```limit
var results = channel();  // ✅ Correct for parallel blocks
```

---

### Issue #3: List Index Assignment Compiles to `dict_set` ❌

**Code**:
```limit
results[i] = i * 2;
```

**Generated LIR**:
```
dict_set r11, r13, r18  // ❌ Wrong! Should be list_set
```

**Reason**: The backend compiler is incorrectly treating list index assignment as dictionary assignment. This is a **backend bug** in the LIR generator.

**Impact**: Even if the list was properly initialized, assignment would fail because:
- `dict_set` expects a dictionary, not a list
- Lists need `list_set` or similar operation
- This causes runtime errors

**Fix**: The backend needs to distinguish between:
- `dict[key] = value` → `dict_set`
- `list[index] = value` → `list_set` (or similar)

---

### Issue #4: Bare `parallel {}` Block ⚠️

**Code**:
```limit
parallel {
    iter(i in 0..999) {
        ...
    }
}
```

**Status**: Actually compiles! But semantically incorrect.

**Problem**: 
- Bare `parallel` without `cores=N` parameter
- Parser accepts it but doesn't enforce the parameter requirement
- Should require `parallel(cores=N)` syntax

**Fix**: Use explicit cores parameter:
```limit
parallel(cores=4) {  // ✅ Correct
    iter(i in 0..99) {
        ...
    }
}
```

---

### Issue #5: `cores=Auto` Parameter ⚠️

**Code**:
```limit
parallel(cores=Auto, timeout=60s, grace=1s, on_error=Continue)
```

**Status**: Compiles but `Auto` is not a valid value.

**Problem**:
- `Auto` is parsed as an identifier, not a keyword
- Should be a numeric value like `cores=4` or `cores=8`
- Advanced parameters (timeout, grace, on_error) are parsed but not fully implemented in VM

**Fix**: Use numeric core count:
```limit
parallel(cores=4)  // ✅ Correct
```

---

## Summary of Issues

| Issue | Type | Severity | Status |
|-------|------|----------|--------|
| List initialization with scalar | Type Error | Critical | ❌ Fails at type check |
| 2D list type annotation | Syntax Error | Critical | ❌ Fails at type check |
| List index assignment → dict_set | Backend Bug | Critical | ❌ Fails at LIR generation |
| Bare parallel block | Semantic | Medium | ⚠️ Compiles but wrong |
| cores=Auto parameter | Semantic | Low | ⚠️ Compiles but wrong |

---

## Working Solution

The corrected version uses:

```limit
// ✅ Proper initialization with channels
var results = channel();

// ✅ Explicit cores parameter
parallel(cores=4) {
    // ✅ Use iter for parallel blocks
    iter(i in 0..99) {
        // ✅ Use channel.send() for communication
        results.send(i * 2);
    }
}

// ✅ Collect results from channel
iter (result in results) {
    print("Result: {result}");
}
```

---

## Backend Bug: List Index Assignment

The most critical issue is that list index assignment is being compiled to `dict_set` instead of the appropriate list operation. This needs to be fixed in the LIR generator:

**File**: `src/lir/generator.cpp`

**Issue**: When compiling `list[index] = value`, the backend should:
1. Detect that the target is a list (not a dict)
2. Generate `list_set` or equivalent operation
3. Currently generates `dict_set` which is incorrect

**Impact**: Makes list mutation impossible in parallel blocks, forcing use of channels instead.

---

## Recommendations

1. **Fix the backend bug** - Distinguish list vs dict index assignment
2. **Enforce cores parameter** - Make `cores=N` required for parallel blocks
3. **Validate parameter values** - Reject `cores=Auto`, require numeric values
4. **Improve error messages** - Provide clearer guidance on proper syntax
5. **Update documentation** - Show correct parallel block patterns with channels
