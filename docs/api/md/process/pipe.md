# API Documentation: `pipe.lm`

## Overview

std/process/pipe.lm
Inter-process pipe streams and unidirectional I/O channels.

## Symbols

- **Frame**: [`PipeReader`](#PipeReader)
- **Frame**: [`PipeWriter`](#PipeWriter)
- **Frame**: [`PipePair`](#PipePair)
- **Frame**: [`Pipe`](#Pipe)
- **Function**: [`create_pipe`](#create_pipe)

---

### `PipeReader` <a id="PipeReader"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PipeReader
```

Reader endpoint of an inter-process pipe.

#### Members

- `var pub resource: res.Resource` *(field)*
- `pub init(r: res.Resource)` *(constructor)*
- `pub fn read(): str` *(method)*
- `pub fn read_all(): str` *(method)*
- `pub fn read_line(): str` *(method)*
- `pub fn is_open(): bool` *(method)*
- `pub fn close(): nil` *(method)*

---

### `PipeWriter` <a id="PipeWriter"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PipeWriter
```

Writer endpoint of an inter-process pipe.

#### Members

- `var pub resource: res.Resource` *(field)*
- `pub init(r: res.Resource)` *(constructor)*
- `pub fn write(content: str): bool` *(method)*
- `pub fn write_line(line: str): bool` *(method)*
- `pub fn flush(): bool` *(method)*
- `pub fn is_open(): bool` *(method)*
- `pub fn close(): nil` *(method)*

---

### `PipePair` <a id="PipePair"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PipePair
```

Unidirectional pipe pair combining a reader and a writer endpoint.

#### Members

- `var pub reader: PipeReader` *(field)*
- `var pub writer: PipeWriter` *(field)*
- `pub init(r: PipeReader, w: PipeWriter)` *(constructor)*
- `pub fn write(content: str): bool` *(method)*
- `pub fn write_line(line: str): bool` *(method)*
- `pub fn read(): str` *(method)*
- `pub fn read_all(): str` *(method)*
- `pub fn read_line(): str` *(method)*
- `pub fn is_open(): bool` *(method)*
- `pub fn close(): nil` *(method)*

---

### `Pipe` <a id="Pipe"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Pipe
```

Self-contained inter-process pipe.

#### Members

- `var pub reader: PipeReader` *(field)*
- `var pub writer: PipeWriter` *(field)*
- `pub init()` *(constructor)*
- `pub fn write(content: str): bool` *(method)*
- `pub fn write_line(line: str): bool` *(method)*
- `pub fn read(): str` *(method)*
- `pub fn read_all(): str` *(method)*
- `pub fn read_line(): str` *(method)*
- `pub fn is_open(): bool` *(method)*
- `pub fn close(): nil` *(method)*

---

### `create_pipe` <a id="create_pipe"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_pipe(): PipePair
```

Creates a new unidirectional inter-process pipe pair.

#### Returns

`PipePair` containing reader and writer endpoints.

---

