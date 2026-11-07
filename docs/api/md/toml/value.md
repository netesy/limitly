# API Documentation: `value.lm`

## Overview

std/toml/value.lm
TOML Value AST node representation and primitive constructors.

## Symbols

- **Frame**: [`Value`](#Value)
- **Function**: [`make_string`](#make_string)
- **Function**: [`make_number`](#make_number)
- **Function**: [`make_bool`](#make_bool)
- **Function**: [`make_object`](#make_object)

---

### `Value` <a id="Value"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Value
```

Represents an immutable TOML value AST node.
Encapsulates string, integer, boolean, and key-value table objects.

#### Members

- `var pub kind: Type` *(field)*
- `var pub str_val: str` *(field)*
- `var pub num_val: int` *(field)*
- `var pub bool_val: bool` *(field)*
- `var pub obj_keys: list` *(field)*
- `var pub obj_vals: list` *(field)*
- `pub fn is_string(): bool` *(method)*
- `pub fn is_number(): bool` *(method)*
- `pub fn is_bool(): bool` *(method)*
- `pub fn is_object(): bool` *(method)*

---

### `make_string` <a id="make_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_string(v: str): Value
```

Constructs a TOML string value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | String content. |

#### Returns

Populated `Value` node.

---

### `make_number` <a id="make_number"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_number(v: int): Value
```

Constructs a TOML integer number value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | Integer value. |

#### Returns

Populated `Value` node.

---

### `make_bool` <a id="make_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_bool(v: bool): Value
```

Constructs a TOML boolean value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | Boolean value. |

#### Returns

Populated `Value` node.

---

### `make_object` <a id="make_object"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_object(k: list, v: list): Value
```

Constructs a TOML table/object value node.

#### Preconditions (Contracts)

- `requires len(k) == len(v)`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `k` | List of string keys. |
| `v` | Parallel list of value nodes. |

#### Returns

Populated `Value` node.

---

