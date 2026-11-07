# API Documentation: `console.lm`

## Overview

std/io/console.lm
Standard input and output console management.

## Symbols

- **Frame**: [`Console`](#Console)

---

### `Console` <a id="Console"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Console
```

Standard console stream manager for terminal output and user input.
Encapsulates standard output (stdout) and standard input (stdin) operations.

#### Example: Idiomatic Usage

```lymar
import std.io.console as console;
var c = console.Console();
c.print("Hello from Console!");
```

#### Members

- `var resource: res.Resource` *(field)*
- `var writer: res.Writer` *(field)*
- `pub init()` *(constructor)*
- `pub fn print(msg: str): nil` *(method)*
- `pub fn read_line(): str` *(method)*

---

