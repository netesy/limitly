# API Documentation: `printf.lm`

## Overview

Standard Library Format Printf Submodule

Template-based positional format substitution.

## Symbols

- **Function**: [`printf_template`](#printf_template)

---

### `printf_template` <a id="printf_template"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn printf_template(template: str, args: list): str
```

Interpolates ordered argument values into `{}` placeholders within a template string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `template` | Text template containing `{}` format tokens. |
| `args` | Positional values to format and substitute into tokens. |

#### Returns

Interpolated string.

#### Example: Idiomatic Usage

```lymar
var msg = printf_template("Hello {}, you have {} messages", ["Alice", 5]);
```

---

