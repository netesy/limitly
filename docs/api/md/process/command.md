# API Documentation: `command.lm`

## Overview

std/process/command.lm
Builder for child process invocations and subprocess execution.

## Symbols

- **Frame**: [`Output`](#Output)
- **Frame**: [`Command`](#Command)
- **Function**: [`has_space`](#has_space)

---

### `Output` <a id="Output"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Output
```

Output captured from a completed child process execution.
Contains exit status code, standard output text, and standard error text.

#### Members

- `var pub status: int` *(field)*
- `var pub stdout: str` *(field)*
- `var pub stderr: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn is_success(): bool` *(method)*

---

### `Command` <a id="Command"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Command
```

Fluent builder for configuring, spawning, and managing child processes.
Preserves arguments with embedded whitespace, allows custom environment overrides,
and configures working directories.

#### Example: Idiomatic Usage

```lymar
import std.process as process;
var out = process.Command("git")
    .arg("status")
    .arg("--short")
    .output();
print(out.stdout);
```

#### Members

- `var pub program: str` *(field)*
- `var pub args: list` *(field)*
- `var pub env_vars: dict` *(field)*
- `var pub working_dir: str` *(field)*
- `pub init(program: str)` *(constructor)*
- `pub fn arg(s: str): Command` *(method)*
- `pub fn args_list(values: list): Command` *(method)*
- `pub fn with_args(values: list): Command` *(method)*
- `pub fn env(key: str, value: str): Command` *(method)*
- `pub fn envs(vars: dict): Command` *(method)*
- `pub fn cwd(dir: str): Command` *(method)*
- `pub fn current_dir(dir: str): Command` *(method)*
- `pub fn to_string(): str` *(method)*
- `pub fn status(): int` *(method)*
- `pub fn execute(): int` *(method)*
- `pub fn output(): Output` *(method)*
- `pub fn spawn(): bool` *(method)*

---

### `has_space` <a id="has_space"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn has_space(s: str): bool
```

---

