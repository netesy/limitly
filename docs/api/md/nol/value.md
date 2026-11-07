# API Documentation: `value.lm`

## Overview

Standard Library NOL Value Representation
Netesy Object Language (NOL)

## Symbols

- **Frame**: [`Value`](#Value)
- **Function**: [`make_null`](#make_null)
- **Function**: [`make_bool`](#make_bool)
- **Function**: [`make_int`](#make_int)
- **Function**: [`make_float`](#make_float)
- **Function**: [`make_string`](#make_string)
- **Function**: [`make_array`](#make_array)
- **Function**: [`make_object`](#make_object)
- **Function**: [`make_empty_object`](#make_empty_object)

---

### `Value` <a id="Value"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Value
```

Represents an abstract syntax tree (AST) node for a NOL value.
Encapsulates primitives (null, booleans, integers, floats, strings) and
structured composite containers (arrays and objects).

#### Members

- `var pub kind: Type` *(field)*
- `var pub bool_val: bool` *(field)*
- `var pub int_val: int` *(field)*
- `var pub float_val: float` *(field)*
- `var pub str_val: str` *(field)*
- `var pub array_val: list` *(field)*
- `var pub obj_keys: list` *(field)*
- `var pub obj_vals: list` *(field)*
- `pub fn is_null(): bool` *(method)*
- `pub fn is_bool(): bool` *(method)*
- `pub fn is_int(): bool` *(method)*
- `pub fn is_float(): bool` *(method)*
- `pub fn is_string(): bool` *(method)*
- `pub fn is_array(): bool` *(method)*
- `pub fn is_object(): bool` *(method)*
- `pub fn as_bool(): bool` *(method)*
- `pub fn as_int(): int` *(method)*
- `pub fn as_float(): float` *(method)*
- `pub fn as_string(): str` *(method)*
- `pub fn as_array(): list` *(method)*
- `pub fn count(): int` *(method)*
- `pub fn get(key: str): any` *(method)*
- `pub fn set(key: str, value_node: any)` *(method)*

---

### `make_null` <a id="make_null"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_null(): Value
```

Creates a new NOL null literal value node.

#### Returns

`Value` instance of kind `Null`.

---

### `make_bool` <a id="make_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_bool(v: bool): Value
```

Creates a new NOL boolean value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | Boolean primitive value. |

#### Returns

`Value` instance of kind `Bool`.

---

### `make_int` <a id="make_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_int(v: int): Value
```

Creates a new NOL integer value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | Integer primitive value. |

#### Returns

`Value` instance of kind `Int`.

---

### `make_float` <a id="make_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_float(v: float): Value
```

Creates a new NOL float value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | Float primitive value. |

#### Returns

`Value` instance of kind `Float`.

---

### `make_string` <a id="make_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_string(v: str): Value
```

Creates a new NOL string value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | String text value. |

#### Returns

`Value` instance of kind `String`.

---

### `make_array` <a id="make_array"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_array(v: list): Value
```

Creates a new NOL array value node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | List of child value elements. |

#### Returns

`Value` instance of kind `Array`.

---

### `make_object` <a id="make_object"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_object(keys: list, vals: list): Value
```

Creates a new NOL object value node from parallel keys and values.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `keys` | List of object field keys. |
| `vals` | List of object field values. |

#### Returns

`Value` instance of kind `Object`.

---

### `make_empty_object` <a id="make_empty_object"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_empty_object(): Value
```

Creates a new empty NOL object value node.

#### Returns

Empty `Value` instance of kind `Object`.

---

