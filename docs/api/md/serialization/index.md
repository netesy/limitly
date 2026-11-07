# API Documentation: `index.lm`

## Overview

Serialization: JSON string escaping and length-prefixed binary framing.

Both halves are pure functions over a `str`, so this module exports free
functions rather than a frame that holds no state and only exists to let its
methods call one another. Operations that can reject their input return
`str?Error`; unwrap with `?`, `? else { return ...; }` or
`match (v) { val x => ..., err e => ... }`.

The binary format is deliberately minimal: a payload is prefixed with its
byte length as a big-endian 32-bit value, and the typed variant adds a
one-byte type id in front of that length.

## Symbols

- **Function**: [`json_encode`](#json_encode)
- **Function**: [`json_decode`](#json_decode)
- **Function**: [`json_encode_object`](#json_encode_object)
- **Function**: [`json_encode_array`](#json_encode_array)
- **Function**: [`binary_encode`](#binary_encode)
- **Function**: [`binary_decode`](#binary_decode)
- **Function**: [`binary_encode_typed`](#binary_encode_typed)
- **Function**: [`binary_decode_typed`](#binary_decode_typed)
- **Function**: [`binary_type_of`](#binary_type_of)
- **Function**: [`int_to_bytes`](#int_to_bytes)
- **Function**: [`bytes_to_int`](#bytes_to_int)

---

### `json_encode` <a id="json_encode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn json_encode(value: str): str
```

Escape `value` and wrap the result in double quotes. Never fails.

---

### `json_decode` <a id="json_decode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn json_decode(value: str): str?
```

Undo json_encode. Rejects input that is not wrapped in double quotes, which
is what an unquoted JSON scalar or an empty string looks like here.

---

### `json_encode_object` <a id="json_encode_object"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn json_encode_object(obj: dict): str
```

`{"key":value,...}` in dictionary iteration order. Dictionaries are walked
with the two-variable form, `iter (key, value in dict)`.

---

### `json_encode_array` <a id="json_encode_array"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn json_encode_array(arr: list): str
```

`[value,...]` in list order.

---

### `binary_encode` <a id="binary_encode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn binary_encode(value: str): str
```

---

### `binary_decode` <a id="binary_decode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn binary_decode(value: str): str?
```

---

### `binary_encode_typed` <a id="binary_encode_typed"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn binary_encode_typed(data: str, type_id: int): str
```

`[type_id:1][length:4][payload]`.

---

### `binary_decode_typed` <a id="binary_decode_typed"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn binary_decode_typed(value: str): str?
```

---

### `binary_type_of` <a id="binary_type_of"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn binary_type_of(value: str): int?
```

The type id stored by binary_encode_typed, so a decoder can dispatch on it
before reading the payload.

---

### `int_to_bytes` <a id="int_to_bytes"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn int_to_bytes(value: int, num_bytes: int): str
```

Big-endian, most significant byte first.

---

### `bytes_to_int` <a id="bytes_to_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn bytes_to_int(bytes: str): int
```

---

