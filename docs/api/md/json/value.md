# API Documentation: `value.lm`

## Overview

std/json/value.lm
JSON Value AST node representation and primitive constructors.

## Symbols

- **Frame**: [`Value`](#Value)
- **Function**: [`make_string`](#make_string)
- **Function**: [`make_number`](#make_number)
- **Function**: [`make_bool`](#make_bool)
- **Function**: [`make_null`](#make_null)
- **Function**: [`make_array`](#make_array)
- **Function**: [`make_object`](#make_object)

---

### `Value` <a id="Value"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Value
```

Represents an immutable Abstract Syntax Tree (AST) node for a JSON value.
Encapsulates JSON primitives (null, bool, number, string) and collections (array, object).

#### Example: Idiomatic Usage

```lymar
import std.json as json;
var v = json.make_string("limitless");
print(v.is_string()); // true
```

#### Members

- `var pub kind: Type` *(field)*
- `var pub str_val: str` *(field)*
- `var pub num_val: int` *(field)*
- `var pub bool_val: bool` *(field)*
- `var pub list_val: list` *(field)*
- `var pub obj_keys: list` *(field)*
- `var pub obj_vals: list` *(field)*
- `pub fn is_null(): bool` *(method)*
- `pub fn is_string(): bool` *(method)*
- `pub fn is_number(): bool` *(method)*
- `pub fn is_bool(): bool` *(method)*
- `pub fn is_array(): bool` *(method)*
- `pub fn is_object(): bool` *(method)*

---

### `make_string` <a id="make_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_string(v: str): Value
```

Constructs a JSON string value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | Text string value. |

#### Returns

Populated `Value` node.

---

### `make_number` <a id="make_number"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_number(v: int): Value
```

Constructs a JSON number value node from a 64-bit integer.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | Integer numeric value. |

#### Returns

Populated `Value` node.

---

### `make_bool` <a id="make_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_bool(v: bool): Value
```

Constructs a JSON boolean value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | Boolean value. |

#### Returns

Populated `Value` node.

---

### `make_null` <a id="make_null"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_null(): Value
```

Constructs a JSON null value node.

#### Returns

Populated `Value` node representing null.

---

### `make_array` <a id="make_array"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_array(v: list): Value
```

Constructs a JSON array value node from a list of items.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | List of child values. |

#### Returns

Populated `Value` node representing an array.

---

### `make_object` <a id="make_object"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_object(k: list, v: list): Value
```

Constructs a JSON object value node from parallel lists of keys and values.

#### Preconditions (Contracts)

- `requires len(k) == len(v)`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `k` | List of string keys. |
| `v` | Parallel list of child values. |

#### Returns

Populated `Value` node representing an object.

---

