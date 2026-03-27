# Absence vs Error Differentiation in Limit Language

## Overview

The Limit language differentiates between **absence** (no value) and **error** (something went wrong) using two distinct type system mechanisms:

1. **Option Types** - For representing absence of a value
2. **Error Union Types** - For representing errors that occurred

---

## 1. Absence: Option Types

### What is Absence?

Absence means "there is no value" - the operation completed successfully but has no meaningful result to return.

### Syntax

```limit
// Option type using union with nil
type MaybeInt = int | nil;
type MaybeString = str | nil;

// Optional parameters
fn greet(name: str?): str {
    if (name == nil) {
        return "Hello, stranger!";
    } else {
        return "Hello, {name}!";
    }
}
```

### Examples of Absence

```limit
// Searching for an item that doesn't exist
type SearchResult = int | str;  // int for index, str for "not found"

fn findInArray(target: int): SearchResult {
    if (target > 0) {
        return target;  // Found at index
    } else {
        return "not found";  // Absence of result
    }
}

var found = findInArray(5);      // Returns 5 (found)
var notFound = findInArray(-1);  // Returns "not found" (absence)
```

### Checking for Absence

```limit
var maybe_value: int? = 42;

// Check if value is absent
if (maybe_value == nil) {
    print("No value");
} else {
    print("Value: {maybe_value}");
}
```

### Key Characteristics of Absence

- ✅ Operation completed successfully
- ✅ No error occurred
- ✅ Result is simply "nothing" or "not applicable"
- ✅ Represented as `nil` or union with `nil`
- ✅ Predictable and expected outcome

---

## 2. Error: Error Union Types

### What is an Error?

An error means "something went wrong" - the operation failed and cannot produce the expected result.

### Syntax

```limit
// Generic error type (Type?)
fn divide(a: int, b: int): int? {
    if (b == 0) {
        return err();  // Generic error
    }
    return ok(a / b);
}

// Specific error types (Type?ErrorType)
fn safeDivide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero);  // Specific error
    }
    return ok(a / b);
}
```

### Examples of Errors

```limit
// Division by zero
fn divide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero);  // ERROR: operation failed
    }
    return ok(a / b);
}

// Index out of bounds
fn getElement(index: int): int?IndexOutOfBounds {
    if (index < 0 || index >= 100) {
        return err(IndexOutOfBounds);  // ERROR: invalid index
    }
    return ok(index);
}

// Key not found
fn getFromDict(key: str): str?KeyNotFound {
    // ... search logic ...
    return err(KeyNotFound);  // ERROR: key doesn't exist
}
```

### Error Propagation

```limit
// Using ? operator to propagate errors
fn process(): int? {
    var result = divide(10, 2)?;  // Propagate error if present
    return ok(result * 2);
}

// With error handling
fn processWithHandler(): int? {
    var result = divide(10, 0)? else {
        print("Division failed");
        return ok(0);
    };
    return ok(result);
}
```

### Error Matching

```limit
fn handleResult(result: int?): str {
    match (result) {
        ok(value) => { return "Success: {value}"; },
        err => { return "Error occurred"; }
    }
}
```

### Key Characteristics of Errors

- ❌ Operation failed
- ❌ Something went wrong
- ❌ Cannot produce expected result
- ❌ Represented as `err()` or `err(ErrorType)`
- ❌ Unexpected and exceptional outcome

---

## 3. Key Differences

### Comparison Table

| Aspect | Absence (Option) | Error (Error Union) |
|--------|------------------|-------------------|
| **Meaning** | No value | Something went wrong |
| **Syntax** | `Type?` or `Type \| nil` | `Type?ErrorType` |
| **Representation** | `nil` | `err()` or `err(ErrorType)` |
| **Success Value** | Value itself | `ok(value)` |
| **Semantics** | Expected outcome | Exceptional outcome |
| **Example** | "Not found" | "Division by zero" |
| **Handling** | Null check | Error propagation |

### Side-by-Side Examples

```limit
// ABSENCE: No value (but not an error)
type SearchResult = int | str;

fn search(target: int): SearchResult {
    if (target > 0) {
        return target;  // Found
    } else {
        return "not found";  // Absence - expected outcome
    }
}

// ERROR: Something went wrong
fn divide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero);  // Error - exceptional outcome
    }
    return ok(a / b);
}
```

---

## 4. Type System Implementation

### Option Types (Absence)

```limit
// Implemented as union types
type Option<T> = T | nil;

// Examples
type MaybeInt = int | nil;
type MaybeString = str | nil;

// Optional parameters
fn process(value: int?): str {
    if (value == nil) {
        return "No value";
    } else {
        return "Value: {value}";
    }
}
```

### Error Union Types (Error)

```limit
// Generic error union
type Result<T> = T?;  // Can be T or error

// Specific error union
type Result<T, E> = T?E;  // Can be T or error E

// Examples
type DivideResult = int?DivisionByZero;
type SearchResult = int?NotFound;

// Multiple error types
type MultiError = int?DivisionByZero, IndexOutOfBounds;
```

---

## 5. Built-in Error Types

```limit
// Common error types
DivisionByZero
IndexOutOfBounds
KeyNotFound
TypeMismatch
NullPointer
IOError
NetworkError
PermissionDenied
Overflow
Timeout
```

---

## 6. Practical Patterns

### Pattern 1: Absence Check

```limit
// Check for absence
var maybe_value: int? = 42;

if (maybe_value == nil) {
    print("No value");
} else {
    print("Value: {maybe_value}");
}
```

### Pattern 2: Error Propagation

```limit
// Propagate errors up the call stack
fn process(): int? {
    var result = divide(10, 2)?;  // Propagate if error
    return ok(result * 2);
}
```

### Pattern 3: Error Handling

```limit
// Handle errors locally
fn processWithHandler(): int? {
    var result = divide(10, 0)? else {
        print("Error occurred");
        return ok(0);
    };
    return ok(result);
}
```

### Pattern 4: Pattern Matching

```limit
// Match on both success and error
fn handleResult(result: int?): str {
    match (result) {
        ok(value) => { return "Success: {value}"; },
        err => { return "Error occurred"; }
    }
}
```

---

## 7. When to Use Each

### Use Absence (Option Types) When:

✅ The operation completed successfully
✅ There's simply no value to return
✅ The absence is an expected outcome
✅ Examples:
- Searching for an item that doesn't exist
- Getting an optional configuration value
- Checking if a condition is met

### Use Error (Error Union Types) When:

❌ The operation failed
❌ Something went wrong
❌ The error is exceptional
❌ Examples:
- Division by zero
- File not found
- Network timeout
- Invalid input

---

## 8. Type Checking

### Compile-Time Validation

```limit
// Type checker validates error handling
fn divide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero);  // ✅ Correct
    }
    return ok(a / b);
}

// Error propagation must be compatible
fn process(): int?DivisionByZero {
    var result = divide(10, 2)?;  // ✅ Compatible error type
    return ok(result);
}

// Incompatible error types are caught
fn incompatible(): int?IndexOutOfBounds {
    var result = divide(10, 2)?;  // ❌ Error: DivisionByZero not compatible
    return ok(result);
}
```

---

## 9. Summary

### Absence vs Error

| Feature | Absence | Error |
|---------|---------|-------|
| **Represents** | No value | Failure |
| **Type** | `Type?` or `Type \| nil` | `Type?ErrorType` |
| **Value** | `nil` | `err()` or `err(ErrorType)` |
| **Success** | Value itself | `ok(value)` |
| **Check** | `== nil` | Pattern match or `?` operator |
| **Propagate** | Not applicable | `?` operator |
| **Handle** | Null check | Error handling |

### Key Takeaway

- **Absence** = "No value, but that's okay" (expected)
- **Error** = "Something went wrong" (exceptional)

The Limit language uses the type system to make this distinction explicit and enforces proper handling at compile time.

---

## Test File References

- **Option Types**: `tests/types/options.lm`
- **Error Handling**: `tests/error_handling/basic_error_checks.lm`
- **Union Types**: `tests/types/unions.lm`
- **Discriminated Unions**: `tests/types/discriminated_unions.lm`

---

## Related Documentation

- `.kiro/steering/syntax.md` - Language syntax reference
- `language_design.md` - Language design principles
- `COMPREHENSIVE_TYPE_TESTS.md` - Type system test documentation
