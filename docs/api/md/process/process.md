# API Documentation: `process.lm`

## Overview

std/process/process.lm
Process identity, arguments, memory inspection, and subprocess execution.

## Symbols

- **Function**: [`exit`](#exit)
- **Function**: [`id`](#id)
- **Function**: [`pid`](#pid)
- **Function**: [`args`](#args)
- **Function**: [`command`](#command)
- **Function**: [`memory`](#memory)
- **Function**: [`peak_memory`](#peak_memory)
- **Function**: [`current_rss`](#current_rss)
- **Function**: [`peak_rss`](#peak_rss)
- **Function**: [`is_space_at`](#is_space_at)
- **Function**: [`to_argv`](#to_argv)
- **Function**: [`run`](#run)
- **Function**: [`exec`](#exec)

---

### `exit` <a id="exit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exit(code: int): nil
```

Terminates the process immediately with the given exit code.

> [!WARNING]
> **Warning**: Flushes standard streams and terminates without executing frame destructors.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `code` | Operating system exit code. |

---

### `id` <a id="id"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn id(): int
```

Returns the operating system Process ID (PID).

#### Returns

Process ID integer (0 when unavailable).

---

### `pid` <a id="pid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pid(): int
```

Alias for `id()`.

#### Returns

Process ID integer.

---

### `args` <a id="args"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn args(): list
```

Returns the command line arguments passed to the program, excluding the binary name.

#### Returns

List of argument strings.

---

### `command` <a id="command"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn command(): str
```

Returns the program name as invoked (argv[0]).

#### Returns

Executable invocation name.

---

### `memory` <a id="memory"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn memory(): int
```

Returns the current resident set size (RSS) in kilobytes.

#### Returns

Memory usage in KB.

---

### `peak_memory` <a id="peak_memory"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn peak_memory(): int
```

Returns the peak resident set size (RSS) in kilobytes since launch.

#### Returns

Peak memory usage in KB.

---

### `current_rss` <a id="current_rss"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn current_rss(): int
```

Alias for `memory()`.

#### Returns

Resident set size in KB.

---

### `peak_rss` <a id="peak_rss"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn peak_rss(): int
```

Alias for `peak_memory()`.

#### Returns

Peak resident set size in KB.

---

### `is_space_at` <a id="is_space_at"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_space_at(text: str, index: int): bool
```

---

### `to_argv` <a id="to_argv"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn to_argv(command_line: str): list
```

---

### `run` <a id="run"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn run(command_line: str): int
```

Spawns a shell or process command string and waits for its exit code.

#### Preconditions (Contracts)

- `requires len(command_line) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `command_line` | Raw command string to execute. |

#### Returns

Exit code (0 for success, non-zero for error, -1 if spawn failed).

---

### `exec` <a id="exec"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exec(program: str, arguments: list): int
```

Executes a program binary directly with discrete arguments and waits for its exit code.

#### Preconditions (Contracts)

- `requires len(program) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `program` | Executable binary name or path. |
| `arguments` | Vector of arguments. |

#### Returns

Exit code.

---

