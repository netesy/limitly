# Module and Function System Requirements

## Problem Statement
The module import system and function calls are not working correctly. When importing modules and calling functions (both in modules and standalone), no output is produced, indicating issues with function execution.

## Current Issues Identified

### 1. Function Call Execution
- **Issue**: Function calls produce no output
- **Evidence**: `test()` call in `test_module_call.lm` produces no output
- **Root Cause**: Function lookup or execution mechanism failing

### 2. Module Function Access
- **Issue**: Module function calls via `module.function()` syntax not working
- **Evidence**: `my_module.greet()` produces no output
- **Root Cause**: Module property access or function execution failing

### 3. Bytecode Generation
- **Issue**: Function calls may not generate correct bytecode sequence
- **Evidence**: Missing `LOAD_VAR` before `CALL` instruction in simple function calls

## User Stories

### US1: Basic Function Calls
**As a** developer  
**I want** to define and call functions  
**So that** I can organize my code into reusable components

**Acceptance Criteria:**
- Function definitions are stored correctly in VM
- Function calls resolve the correct function
- Function execution produces expected output
- Parameters are passed correctly
- Return values work properly

### US2: Module Import and Function Access
**As a** developer  
**I want** to import modules and call their functions  
**So that** I can organize code across multiple files

**Acceptance Criteria:**
- `import module.path;` loads the module correctly
- Module functions are accessible via `module.function()` syntax
- Module variables are accessible via `module.variable` syntax
- Module execution happens in isolated environment
- Module functions can access module-level variables

### US3: Module Property Access
**As a** developer  
**I want** to access module properties using dot notation  
**So that** I can use module functions and variables naturally

**Acceptance Criteria:**
- `module.function()` calls work correctly
- `module.variable` access works correctly
- Property access generates correct bytecode
- VM handles module property resolution

## Technical Requirements

### Function System
1. **Function Definition Storage**
   - Functions stored in `userDefinedFunctions` map
   - Function start/end addresses calculated correctly
   - Parameter information preserved

2. **Function Call Resolution**
   - Function name lookup works correctly
   - Parameter binding works for all parameter types
   - Environment setup for function execution
   - Call stack management

3. **Function Execution**
   - Jump to function start address
   - Execute function body
   - Handle return statements
   - Restore previous execution context

### Module System
1. **Module Loading**
   - Module file resolution from import path
   - Module compilation and execution
   - Module environment isolation
   - Module caching for repeated imports

2. **Module Property Access**
   - `GET_PROPERTY` opcode handling for modules
   - Module environment lookup
   - Function and variable access

3. **Module Integration**
   - Module functions callable from importing code
   - Module variables accessible from importing code
   - Proper scoping and environment management

## Test Cases

### Basic Function Tests
```limit
fn greet() {
    print("Hello World!");
}
greet(); // Should output: Hello World!
```

### Module Function Tests
```limit
// my_module.lm
var message = "Hello from module!";
fn greet() {
    print(message);
}

// main.lm
import my_module;
my_module.greet(); // Should output: Hello from module!
```

### Module Variable Tests
```limit
// my_module.lm
var message = "Module variable";

// main.lm
import my_module;
print(my_module.message); // Should output: Module variable
```

## Success Criteria
1. All function calls produce expected output
2. Module imports work correctly
3. Module property access works for both functions and variables
4. No spurious output or execution errors
5. Proper error handling for missing functions/modules
6. All existing tests continue to pass