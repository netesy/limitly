# API Documentation: `index.lm`

## Overview

std/process/index.lm
Public facade for std.process: the process as an entity.

## Symbols

- **Frame**: [`Process`](#Process)
- **Function**: [`exit`](#exit)
- **Function**: [`run`](#run)
- **Function**: [`exec`](#exec)
- **Function**: [`id`](#id)
- **Function**: [`pid`](#pid)
- **Function**: [`args`](#args)
- **Function**: [`command`](#command)
- **Function**: [`memory`](#memory)
- **Function**: [`peak_memory`](#peak_memory)
- **Function**: [`current_rss`](#current_rss)
- **Function**: [`peak_rss`](#peak_rss)

---

### `Process` <a id="Process"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Process
```

Object-oriented interface to the current process identity and lifecycle.

#### Members

- `pub init()` *(constructor)*
- `pub fn exit(code: int): nil` *(method)*
- `pub fn run(cmd_str: str): int` *(method)*
- `pub fn exec(program: str, arguments: list): int` *(method)*
- `pub fn id(): int` *(method)*
- `pub fn pid(): int` *(method)*
- `pub fn args(): list` *(method)*
- `pub fn command(): str` *(method)*
- `pub fn memory(): int` *(method)*
- `pub fn peak_memory(): int` *(method)*
- `pub fn current_rss(): int` *(method)*
- `pub fn peak_rss(): int` *(method)*

---

### `exit` <a id="exit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exit(code: int): nil
```

Terminates the process immediately with the given exit code.

---

### `run` <a id="run"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn run(cmd_str: str): int
```

Spawns a command string and waits for its integer exit code.

---

### `exec` <a id="exec"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exec(program: str, arguments: list): int
```

Executes a program binary directly with an argument list.

---

### `id` <a id="id"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn id(): int
```

Returns the operating system PID.

---

### `pid` <a id="pid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pid(): int
```

Returns the operating system PID.

---

### `args` <a id="args"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn args(): list
```

Returns the program's command line arguments.

---

### `command` <a id="command"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn command(): str
```

Returns the program name as invoked.

---

### `memory` <a id="memory"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn memory(): int
```

Returns current memory usage in KB.

---

### `peak_memory` <a id="peak_memory"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn peak_memory(): int
```

Returns peak memory usage in KB.

---

### `current_rss` <a id="current_rss"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn current_rss(): int
```

Alias for `memory()`.

---

### `peak_rss` <a id="peak_rss"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn peak_rss(): int
```

Alias for `peak_memory()`.

---

