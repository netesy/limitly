# API Documentation: `index.lm`

## Overview

Standard Library Command-Line Interface (CLI) Module

Provides command-line argument parsing, flag evaluation, and positional option extraction.

## Symbols

- **Frame**: [`ArgParser`](#ArgParser)

---

### `ArgParser` <a id="ArgParser"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ArgParser
```

Parser for command-line arguments and boolean execution flags.

#### Example: Idiomatic Usage

```lymar
var parser = ArgParser("myapp");
parser.parse(["myapp", "-v", "input.txt"]);
if (parser.has_flag("-v")) {
    print("Verbose mode enabled");
}
```

#### Members

- `var pub program_name: str` *(field)*
- `var pub options: dict` *(field)*
- `var pub args: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn parse(argv: list)` *(method)*
- `pub fn has_flag(flag: str): bool` *(method)*
- `pub fn get_args(): list` *(method)*

---

