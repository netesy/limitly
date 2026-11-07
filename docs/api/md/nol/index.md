# API Documentation: `index.lm`

## Overview

Standard Library NOL Module Facade
Nominal Object Language (NOL)

## Symbols

- **Function**: [`parse`](#parse)
- **Function**: [`stringify`](#stringify)

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): document.Document?
```

Parses a NOL serialized string into a structured `Document`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | NOL source text. |

#### Returns

Parsed `Document` instance, or error if parsing failed.

#### Example: Idiomatic Usage

```lymar
var doc = nol.parse("[package]\nname: \"test\"")?;
```

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(val_obj: value.Value, indent: int = ...): str
```

Serializes a NOL value or root document to NOL text format.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_obj` | Value AST node to serialize. |
| `indent` | Spaces per indentation level (default: 2). |

#### Returns

Formatted NOL string.

---

