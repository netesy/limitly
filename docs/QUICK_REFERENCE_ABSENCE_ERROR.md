# Quick Reference: Absence vs Error

## At a Glance

```limit
// ABSENCE: No value (but operation succeeded)
type MaybeInt = int | nil;
var x: MaybeInt = nil;  // No value

// ERROR: Operation failed
fn divide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero);  // Failed
    }
    return ok(a / b);  // Succeeded
}
```

---

## Syntax Comparison

### Absence (Option Types)

```limit
// Declaration
type MaybeInt = int | nil;
var x: int? = 42;

// Check
if (x == nil) { /* absent */ }
if (x != nil) { /* present */ }

// Use
print("Value: {x}");
```

### Error (Error Union Types)

```limit
// Declaration
fn process(): int?DivisionByZero { }
var result: int?DivisionByZero = ok(42);

// Check
match (result) {
    ok(value) => { /* success */ },
    err => { /* error */ }
}

// Propagate
var x = process()?;

// Handle
var x = process()? else { /* handle error */ };
```

---

## Decision Tree

```
Does the operation complete successfully?
├─ YES, but no value to return?
│  └─ Use ABSENCE (Option Type)
│     Type: int? or int | nil
│     Value: nil
│
└─ NO, something went wrong?
   └─ Use ERROR (Error Union Type)
      Type: int?ErrorType
      Value: err(ErrorType)
```

---

## Common Patterns

### Pattern 1: Optional Value
```limit
// Absence: Value might not exist
type MaybeUser = User | nil;
var user: MaybeUser = nil;  // No user found
```

### Pattern 2: Fallible Operation
```limit
// Error: Operation might fail
fn divide(a: int, b: int): int?DivisionByZero {
    if (b == 0) return err(DivisionByZero);
    return ok(a / b);
}
```

### Pattern 3: Search Result
```limit
// Absence: Item not found (but search succeeded)
type SearchResult = int | str;  // int=index, str="not found"
var result = search(target);
```

### Pattern 4: Validation
```limit
// Error: Validation failed
fn validate(age: int): int?InvalidAge {
    if (age < 0) return err(InvalidAge);
    return ok(age);
}
```

---

## Error Propagation

```limit
// Propagate errors up
fn process(): int? {
    var x = divide(10, 2)?;  // If error, return it
    return ok(x * 2);
}

// Handle errors locally
fn processWithHandler(): int? {
    var x = divide(10, 0)? else {
        print("Error!");
        return ok(0);
    };
    return ok(x);
}
```

---

## Type Signatures

### Absence
```limit
// Optional parameter
fn greet(name: str?): str

// Optional return
fn find(): int | nil

// Union with nil
type Maybe<T> = T | nil
```

### Error
```limit
// Generic error
fn process(): int?

// Specific error
fn divide(): int?DivisionByZero

// Multiple errors
fn complex(): int?Error1, Error2
```

---

## Checking Values

### Absence
```limit
if (x == nil) { /* absent */ }
if (x != nil) { /* present */ }
```

### Error
```limit
match (result) {
    ok(value) => { /* success */ },
    err => { /* error */ }
}
```

---

## Key Differences

| | Absence | Error |
|---|---------|-------|
| **Meaning** | No value | Failed |
| **Syntax** | `Type?` | `Type?ErrorType` |
| **Value** | `nil` | `err()` |
| **Success** | Value | `ok(value)` |
| **Check** | `== nil` | `match` |
| **Propagate** | No | Yes (`?`) |

---

## Examples

### Absence Example
```limit
// Search that returns "not found"
type SearchResult = int | str;

fn search(target: int): SearchResult {
    if (target > 0) {
        return target;  // Found at index
    } else {
        return "not found";  // Absence - expected
    }
}

var result = search(-1);  // Returns "not found"
```

### Error Example
```limit
// Division that can fail
fn divide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero);  // Error - exceptional
    }
    return ok(a / b);
}

var result = divide(10, 0);  // Returns err(DivisionByZero)
```

---

## Remember

- **Absence** = "No value, but that's okay" ✅
- **Error** = "Something went wrong" ❌

Use the type system to make this distinction clear!
