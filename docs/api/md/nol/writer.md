# API Documentation: `writer.lm`

## Overview

Standard Library NOL Serializer / Dumper
Netesy Object Language (NOL)

## Symbols

- **Function**: [`_make_indent`](#_make_indent)
- **Function**: [`_escape_str`](#_escape_str)
- **Function**: [`dump`](#dump)
- **Function**: [`stringify`](#stringify)

---

### `_make_indent` <a id="_make_indent"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _make_indent(spaces: int): str
```

---

### `_escape_str` <a id="_escape_str"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _escape_str(s: str): str
```

---

### `dump` <a id="dump"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dump(val_obj: value.Value, indent: int = ..., level: int = ..., is_root: bool = ...): str
```

Dumps a NOL `Value` AST node to its text representation.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_obj` | Target value node to format. |
| `indent` | Spaces per indentation level (default: 2). |
| `level` | Current indentation nesting level (default: 0). |
| `is_root` | True if formatting root level of document (default: true). |

#### Returns

Serialized NOL string representation.

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(val_obj: value.Value, indent: int = ...): str
```

Serializes a NOL `Value` into formatted text.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_obj` | Target value node to serialize. |
| `indent` | Spaces per indentation level (default: 2). |

#### Returns

Formatted NOL string.

---

