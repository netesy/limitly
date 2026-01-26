# Matrix and Collection Robustness Test Report

## Summary
Tested lists and dictionaries for use as matrices (2D and 3D). Found several issues with collection operations that limit their robustness for matrix operations.

## Test Results

### Test 1: 2D Lists with Nested Iteration ❌

**Code**:
```limit
var matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]];
iter (row in matrix) {
    iter (elem in row) {
        sum = sum + elem;
    }
}
```

**Result**: ❌ FAILED - Nested iteration over lists doesn't work
- Outer iteration works
- Inner iteration fails (doesn't iterate over nested list elements)
- No error message, just silently fails

**Impact**: Cannot use nested lists for matrix operations with iteration

---

### Test 2: 2D Lists with Direct Indexing ✅

**Code**:
```limit
var matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]];
var row0 = matrix[0];
var elem = row0[0];
```

**Result**: ✅ WORKS - Direct indexing of nested lists works
- Can access rows: `matrix[0]` returns the first row
- Can access elements: `row[0]` returns the first element
- Values are returned as memory addresses (pointers) but are accessible

**Impact**: Can use nested lists for matrix operations with direct indexing

---

### Test 3: Dictionary Access with String Keys ❌

**Code**:
```limit
var dict = {"a": 1, "b": 2, "c": 3};
var val = dict["a"];
```

**Result**: ❌ FAILED - String key access returns `nil`
- Dictionary creation works
- Numeric key access works (returns values)
- String key access returns `nil`

**Impact**: Cannot use string keys for matrix indexing

---

### Test 4: Dictionary Access with Numeric Keys ⚠️

**Code**:
```limit
var dict = {1: "one", 2: "two", 3: "three"};
var val = dict[1];
```

**Result**: ⚠️ PARTIAL - Numeric key access works but returns pointers
- Dictionary creation works
- Numeric key access works
- Values are returned as memory addresses instead of actual values
- String values print as memory addresses

**Impact**: Can use numeric keys but values aren't properly dereferenced

---

### Test 5: Nested Dictionaries (3D Matrix) ❌

**Code**:
```limit
var matrix_3d = {
    "0": {
        "0": {"0": 1, "1": 2},
        "1": {"0": 3, "1": 4}
    }
};
var elem = matrix_3d["0"]["0"]["0"];
```

**Result**: ❌ FAILED - Nested dict access returns `nil`
- First level access returns `nil` (string key issue)
- Cannot proceed to deeper levels

**Impact**: Cannot use nested dictionaries for 3D matrices

---

## Issues Identified

### Issue #1: Nested List Iteration ❌
- **Severity**: High
- **Description**: Cannot iterate over nested lists
- **Cause**: Iterator implementation doesn't handle list-of-lists properly
- **Workaround**: Use direct indexing instead of iteration

### Issue #2: String Key Dictionary Access ❌
- **Severity**: Critical
- **Description**: Dictionary access with string keys returns `nil`
- **Cause**: Backend dict_get operation doesn't handle string keys correctly
- **Workaround**: Use numeric keys only

### Issue #3: Value Dereferencing ⚠️
- **Severity**: Medium
- **Description**: Dictionary values returned as pointers instead of dereferenced values
- **Cause**: Backend dict_get returns pointer without dereferencing
- **Workaround**: None - values are unusable

### Issue #4: Type Mismatch in Dict Operations ⚠️
- **Severity**: Medium
- **Description**: LIR uses `list_index` for dict access instead of `dict_get`
- **Cause**: Backend compiler treats dict indexing as list indexing
- **Workaround**: None - fundamental backend issue

---

## What Works ✅

1. **List Creation**: Creating nested lists works
2. **List Direct Indexing**: Accessing list elements by index works
3. **Dictionary Creation**: Creating dictionaries works
4. **Dictionary Numeric Keys**: Accessing dicts with numeric keys works (partially)

---

## What Doesn't Work ❌

1. **Nested List Iteration**: Cannot iterate over lists of lists
2. **String Key Dictionary Access**: String keys return `nil`
3. **Value Dereferencing**: Dict values not properly dereferenced
4. **3D Structures**: Cannot create or access 3D matrices

---

## Recommendations

### For 2D Matrices
- **Use**: Nested lists with direct indexing
- **Avoid**: Nested iteration
- **Example**:
```limit
var matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]];
var elem = matrix[i][j];  // ✅ Works
```

### For 3D Matrices
- **Status**: Not currently feasible
- **Reason**: Nested iteration doesn't work, string keys don't work
- **Alternative**: Use parallel blocks with channels for distributed computation

### For Dictionary-Based Matrices
- **Status**: Not recommended
- **Reason**: String keys don't work, values not dereferenced
- **Alternative**: Use lists instead

---

## Test Files Created

1. `test_matrix_2d_lists.lm` - 2D list tests (nested iteration fails)
2. `test_matrix_dict_based.lm` - Dict-based matrix tests (string keys fail)
3. `test_dict_simple_access.lm` - Simple dict access tests (string keys fail)

---

## Backend Issues to Fix

### Priority 1: String Key Dictionary Access
- **File**: `src/lir/generator.cpp` or `src/backend/vm.cpp`
- **Issue**: `dict_get` with string keys returns `nil`
- **Fix**: Ensure string keys are properly hashed and compared

### Priority 2: Value Dereferencing
- **File**: `src/backend/vm.cpp`
- **Issue**: Dictionary values returned as pointers
- **Fix**: Dereference values before returning from `dict_get`

### Priority 3: Nested List Iteration
- **File**: `src/lir/generator.cpp`
- **Issue**: Iterator doesn't handle list-of-lists
- **Fix**: Implement proper type checking for nested iterables

### Priority 4: Dict Index Operation
- **File**: `src/lir/generator.cpp`
- **Issue**: Uses `list_index` instead of `dict_get` for dict access
- **Fix**: Distinguish between list and dict indexing in backend

---

## Conclusion

**Current Status**: Collections are partially robust
- ✅ 2D lists with direct indexing work
- ❌ 2D lists with iteration don't work
- ❌ Dictionaries with string keys don't work
- ❌ 3D structures not feasible

**Recommendation**: For matrix operations, use nested lists with direct indexing only. For more complex operations, use parallel blocks with channels for distributed computation.
