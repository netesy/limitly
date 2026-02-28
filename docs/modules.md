# Module System Documentation

## Overview

The Limit programming language includes a comprehensive module system that allows you to organize code into reusable modules and import functionality from other files.

## Basic Module Import

### Simple Import
```limit
import path.to.module as alias;
```

### Example
```limit
// math_utils.lm
var PI = 3.14159;
var E = 2.71828;

fn square(x) {
    return x * x;
}
```

```limit
// main.lm
import math_utils as math;

print(math.PI);        // 3.14159
print(math.E);         // 2.71828
var result = math.square(5);  // 25
```

## Module Aliasing

You can import the same module with different aliases:

```limit
import utils.math as math;
import utils.math as mathematics;

print(math.PI);         // 3.14159
print(mathematics.PI);  // 3.14159 (same module, different alias)
```

## Import Filters

### Show Filter
Only import specific identifiers from a module:

```limit
import utils.math as math show PI, E;

print(math.PI);  // ✓ Available
print(math.E);   // ✓ Available
// math.square(5);  // ❌ Not available (not in show list)
```

### Hide Filter
Import everything except specific identifiers:

```limit
import utils.math as math hide square;

print(math.PI);  // ✓ Available
print(math.E);   // ✓ Available
// math.square(5);  // ❌ Not available (hidden)
```

### Multiple Identifiers
```limit
import utils.math as math show PI, E, square;
import utils.string as str hide internal_function, debug_var;
```

## Nested Directory Imports

Modules can be organized in nested directories:

```limit
// utils/math/advanced.lm
var GOLDEN_RATIO = 1.618;

// main.lm
import utils.math.advanced as advanced;
print(advanced.GOLDEN_RATIO);
```

## Module Caching

Modules are cached after first import. Subsequent imports of the same module return the cached version:

```limit
import utils.math as math1;
import utils.math as math2;  // Uses cached version

// Both aliases reference the same module instance
print(math1.PI);  // 3.14159
print(math2.PI);  // 3.14159
```

## Current Limitations

The module system is currently in the early stages of development. While the syntax for importing modules is parsed by the compiler, the virtual machine (VM) and runtime do not yet support module loading or execution.

This means that:
- **No code from imported modules can be executed.** This includes calling functions, accessing variables, or using any other definitions from another file.
- **All `import` statements will be parsed without error**, but they will not have any effect at runtime.

## Error Handling

### Missing Module
```limit
// import nonexistent.module as missing;
// Error: Could not open module file: nonexistent/module.lm
```

### Missing Property
```limit
import utils.math as math;
// print(math.nonexistent_property);
// Error: Property 'nonexistent_property' not found in dictionary
```

## Best Practices

### 1. Use Descriptive Aliases
```limit
// Good
import utils.string_operations as strings;
import utils.math_functions as math;

// Avoid
import utils.string_operations as s;
import utils.math_functions as m;
```

### 2. Group Related Imports
```limit
// Utility imports
import utils.math as math;
import utils.string as strings;
import utils.file as files;

// Business logic imports
import models.user as user_model;
import services.auth as auth_service;
```

### 3. Use Filters Judiciously
```limit
// Only import what you need
import large_utility_module as utils show needed_function, needed_constant;

// Hide internal/debug functions
import debug_module as debug hide internal_debug, verbose_logging;
```

### 4. Organize Module Files
```
project/
├── main.lm
├── utils/
│   ├── math.lm
│   ├── string.lm
│   └── file.lm
├── models/
│   ├── user.lm
│   └── product.lm
└── services/
    ├── auth.lm
    └── database.lm
```

## Testing

The module system includes comprehensive tests covering:

- ✅ Basic import and variable access
- ✅ Module aliasing
- ✅ Show/hide filters
- ✅ Nested directory imports
- ✅ Module caching
- ✅ Multiple module imports
- 🚧 Function calls with parameters (known limitation)
- 🚧 Error handling improvements (in progress)

## Future Enhancements

Planned improvements to the module system:

1. **Full Function Support**: Complete implementation of function calls with parameters and return values
2. **Better Error Messages**: More descriptive error messages for common issues
3. **Circular Import Detection**: Detect and handle circular import dependencies
4. **Module Metadata**: Access to module information and documentation
5. **Dynamic Imports**: Runtime module loading capabilities