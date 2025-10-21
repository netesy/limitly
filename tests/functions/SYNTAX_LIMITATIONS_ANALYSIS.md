# Syntax Limitations for Function Composition and Currying

## Current Status Summary

Based on comprehensive testing, here are the specific syntax limitations preventing function composition and currying implementation:

## 🚫 **Critical Limitations (Blocking Implementation)**

### 1. **Function Calling Mechanism Missing**
```lm
// ❌ DOESN'T WORK - Core limitation
var increment = fn(x: int): int { return x + 1; };
var result = increment(5);  // Syntax exists but VM doesn't support it
```

**Impact**: Without function calling, composition and currying are impossible to implement.

**Error**: No VM opcode for `CALL_CLOSURE` - closures are created but cannot be invoked.

### 2. **Function Type Signatures Not Supported**
```lm
// ❌ DOESN'T WORK - Parser limitation
fn compose(f: fn(int): int, g: fn(int): int): fn(int): int {
    // Parser error: "Expected type name for definition"
    return fn(x: int): int { return f(g(x)); };
}
```

**Impact**: Cannot specify precise function parameter types, making type-safe composition impossible.

**Current Workaround**: Use generic `function` type, but loses type safety.

### 3. **Complex Nested Function Runtime Errors**
```lm
// ❌ RUNTIME ERRORS - VM limitation
fn createComposer(): function {
    return fn(f: function): function {  // END_FUNCTION error
        return fn(g: function): function {  // PUSH_LAMBDA error
            return fn(x: int): int {
                // Would implement composition here
                return x;
            };
        };
    };
}
```

**Impact**: Deep nesting required for currying causes VM crashes.

**Errors**: `END_FUNCTION reached outside of function call`, `PUSH_LAMBDA: lambda function not found`

## 🔧 **Syntax Limitations (Missing Language Features)**

### 4. **No Composition Operators**
```lm
// ❌ DESIRED SYNTAX - Not implemented
var composed = f ∘ g;           // Mathematical composition
var piped = value |> f |> g;    // Pipe operator
var chained = f.then(g);        // Method chaining
```

**Impact**: No elegant syntax for function composition.

**Current State**: No parser support for these operators.

### 5. **No Currying Syntax**
```lm
// ❌ DESIRED SYNTAX - Not implemented
fn add(a: int, b: int): int { return a + b; }

// Auto-currying (Haskell-style)
var addTen = add(10);  // Partial application
var result = addTen(5); // Complete application

// Explicit currying
var curriedAdd = curry(add);
var addTen = curriedAdd(10);
```

**Impact**: No built-in currying support, must implement manually.

### 6. **No Partial Application Syntax**
```lm
// ❌ DESIRED SYNTAX - Not implemented
var addTen = partial(add, 10);
var multiplyByTwo = partial(multiply, _, 2);  // Placeholder syntax
```

**Impact**: No convenient partial application mechanism.

## 📋 **What Currently Works (Foundation)**

### ✅ **Function Creation and Storage**
```lm
// ✅ WORKS
fn add(a: int, b: int): int { return a + b; }
var addFunc: function = add;

var lambda = fn(x: int): int { return x * 2; };
```

### ✅ **Function Parameters and Return Values**
```lm
// ✅ WORKS
fn acceptFunction(f: function): function {
    return f;  // Can pass and return functions
}

fn createFunction(): function {
    return fn(x: int): int { return x; };
}
```

### ✅ **Variable Capture in Closures**
```lm
// ✅ WORKS
fn createAdder(n: int): function {
    return fn(x: int): int {
        return x + n;  // Captures 'n' correctly
    };
}
```

## 🛠 **Implementation Requirements for Composition and Currying**

### **Phase 1: Essential Infrastructure**

1. **Function Calling Mechanism**
   ```lm
   // Must implement:
   var f = fn(x: int): int { return x + 1; };
   var result = f(5);  // ← This must work
   ```

2. **Specific Function Types**
   ```lm
   // Must implement:
   fn compose(f: fn(int): int, g: fn(int): int): fn(int): int {
       return fn(x: int): int { return f(g(x)); };
   }
   ```

3. **Nested Function Stability**
   ```lm
   // Must fix runtime errors in deep nesting
   fn level1(): function {
       return fn(): function {
           return fn(): int { return 42; };
       };
   }
   ```

### **Phase 2: Composition Implementation**

Once Phase 1 is complete, composition can be implemented:

```lm
// Basic composition function
fn compose(f: fn(int): int, g: fn(int): int): fn(int): int {
    return fn(x: int): int {
        return f(g(x));  // Now possible with function calling
    };
}

// Usage
var increment = fn(x: int): int { return x + 1; };
var double = fn(x: int): int { return x * 2; };
var composed = compose(double, increment);
var result = composed(5);  // Should return 12
```

### **Phase 3: Currying Implementation**

```lm
// Generic currying function (simplified for 2 parameters)
fn curry2(f: fn(int, int): int): fn(int): fn(int): int {
    return fn(a: int): fn(int): int {
        return fn(b: int): int {
            return f(a, b);  // Call original function with both args
        };
    };
}

// Usage
var add = fn(a: int, b: int): int { return a + b; };
var curriedAdd = curry2(add);
var addTen = curriedAdd(10);
var result = addTen(5);  // Should return 15
```

### **Phase 4: Advanced Syntax (Future)**

```lm
// Pipe operator
var result = 5 |> increment |> double;

// Composition operator  
var composed = double ∘ increment;

// Auto-currying
fn add(a: int)(b: int): int { return a + b; }  // Curried by default
```

## 🎯 **Priority Order for Implementation**

1. **CRITICAL**: Function calling mechanism (`closure(args)`)
2. **HIGH**: Function type signatures (`fn(Type): ReturnType`)
3. **HIGH**: Fix nested function runtime errors
4. **MEDIUM**: Implement `compose()` function
5. **MEDIUM**: Implement `curry()` function
6. **LOW**: Add composition operators (`∘`, `|>`)
7. **LOW**: Add auto-currying syntax

## 📊 **Current Capability Assessment**

| Feature | Status | Blocker |
|---------|--------|---------|
| Function creation | ✅ Working | None |
| Function storage | ✅ Working | None |
| Function parameters | ✅ Working | Type specificity |
| Function calling | ❌ Missing | VM implementation |
| Function composition | ❌ Blocked | Function calling |
| Function currying | ❌ Blocked | Function calling |
| Partial application | ❌ Blocked | Function calling |
| Pipe operators | ❌ Missing | Parser support |

**Conclusion**: The foundation for functional programming is solid (closure memory management, function creation, variable capture), but the essential function calling mechanism is the primary blocker preventing composition and currying implementation.