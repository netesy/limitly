# API Documentation: `index.lm`

## Overview

Foreign Function Interface (FFI) Module
Standard C ABI Interoperability, Type Mapping, and Unmanaged Memory Operations

## Symbols

- **Type Alias**: [`c_char`](#c_char)
- **Type Alias**: [`c_short`](#c_short)
- **Type Alias**: [`c_int`](#c_int)
- **Type Alias**: [`c_long`](#c_long)
- **Type Alias**: [`c_longlong`](#c_longlong)
- **Type Alias**: [`c_uchar`](#c_uchar)
- **Type Alias**: [`c_ushort`](#c_ushort)
- **Type Alias**: [`c_uint`](#c_uint)
- **Type Alias**: [`c_ulong`](#c_ulong)
- **Type Alias**: [`c_ulonglong`](#c_ulonglong)
- **Type Alias**: [`c_size_t`](#c_size_t)
- **Type Alias**: [`c_ssize_t`](#c_ssize_t)
- **Type Alias**: [`c_ptrdiff_t`](#c_ptrdiff_t)
- **Type Alias**: [`c_float`](#c_float)
- **Type Alias**: [`c_double`](#c_double)
- **Type Alias**: [`pubptr`](#pubptr)
- **Type Alias**: [`fnptr`](#fnptr)
- **Type Alias**: [`c_bool`](#c_bool)
- **Type Alias**: [`c_void`](#c_void)
- **Function**: [`alloc`](#alloc)
- **Function**: [`free`](#free)
- **Function**: [`realloc`](#realloc)
- **Function**: [`memcpy`](#memcpy)
- **Function**: [`memset`](#memset)
- **Function**: [`memcmp`](#memcmp)
- **Function**: [`ptr_add`](#ptr_add)
- **Function**: [`_ffi_alloc`](#_ffi_alloc)
- **Function**: [`_ffi_free`](#_ffi_free)
- **Function**: [`_ffi_load_i8`](#_ffi_load_i8)
- **Function**: [`_ffi_load_u8`](#_ffi_load_u8)
- **Function**: [`_ffi_store_i8`](#_ffi_store_i8)
- **Function**: [`_ffi_ptr_add`](#_ffi_ptr_add)
- **Function**: [`ptr_sub`](#ptr_sub)
- **Function**: [`ptr_diff`](#ptr_diff)
- **Function**: [`ptr_align`](#ptr_align)
- **Function**: [`ptr_is_aligned`](#ptr_is_aligned)
- **Function**: [`load_i8`](#load_i8)
- **Function**: [`load_u8`](#load_u8)
- **Function**: [`load_i16`](#load_i16)
- **Function**: [`load_u16`](#load_u16)
- **Function**: [`load_i32`](#load_i32)
- **Function**: [`load_u32`](#load_u32)
- **Function**: [`load_i64`](#load_i64)
- **Function**: [`load_u64`](#load_u64)
- **Function**: [`load_f32`](#load_f32)
- **Function**: [`load_f64`](#load_f64)
- **Function**: [`load_ptr`](#load_ptr)
- **Function**: [`store_i8`](#store_i8)
- **Function**: [`store_u8`](#store_u8)
- **Function**: [`store_i16`](#store_i16)
- **Function**: [`store_u16`](#store_u16)
- **Function**: [`store_i32`](#store_i32)
- **Function**: [`store_u32`](#store_u32)
- **Function**: [`store_i64`](#store_i64)
- **Function**: [`store_u64`](#store_u64)
- **Function**: [`store_f32`](#store_f32)
- **Function**: [`store_f64`](#store_f64)
- **Function**: [`store_ptr`](#store_ptr)
- **Function**: [`library_load`](#library_load)
- **Function**: [`library_unload`](#library_unload)
- **Function**: [`library_get_symbol`](#library_get_symbol)
- **Function**: [`foreign_call`](#foreign_call)
- **Function**: [`call_i64_0`](#call_i64_0)
- **Function**: [`call_i64_1`](#call_i64_1)
- **Function**: [`call_i64_2`](#call_i64_2)
- **Function**: [`call_f64_2`](#call_f64_2)
- **Function**: [`call_void_1`](#call_void_1)
- **Frame**: [`CString`](#CString)
- **Function**: [`string_to_cstring`](#string_to_cstring)
- **Function**: [`cstring_to_string`](#cstring_to_string)
- **Function**: [`cstring_to_string_bounded`](#cstring_to_string_bounded)
- **Function**: [`cstring_free`](#cstring_free)
- **Function**: [`cstring_as_ptr`](#cstring_as_ptr)
- **Function**: [`cstring_from_ptr`](#cstring_from_ptr)
- **Frame**: [`ForeignFunction`](#ForeignFunction)
- **Function**: [`declare`](#declare)
- **Frame**: [`Library`](#Library)
- **Function**: [`load`](#load)
- **Function**: [`load_first`](#load_first)
- **Function**: [`callback_create`](#callback_create)
- **Function**: [`callback_ptr`](#callback_ptr)
- **Function**: [`callback_destroy`](#callback_destroy)
- **Function**: [`_ffi_callback_create`](#_ffi_callback_create)
- **Function**: [`_ffi_callback_ptr`](#_ffi_callback_ptr)
- **Function**: [`_ffi_callback_destroy`](#_ffi_callback_destroy)
- **Frame**: [`Callback`](#Callback)
- **Function**: [`create_callback`](#create_callback)

---

### `c_char` <a id="c_char"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_char = int
```

Primitive C integer types

---

### `c_short` <a id="c_short"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_short = int
```

---

### `c_int` <a id="c_int"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_int = int
```

---

### `c_long` <a id="c_long"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_long = int
```

---

### `c_longlong` <a id="c_longlong"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_longlong = int
```

---

### `c_uchar` <a id="c_uchar"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_uchar = int
```

---

### `c_ushort` <a id="c_ushort"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_ushort = int
```

---

### `c_uint` <a id="c_uint"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_uint = int
```

---

### `c_ulong` <a id="c_ulong"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_ulong = int
```

---

### `c_ulonglong` <a id="c_ulonglong"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_ulonglong = int
```

---

### `c_size_t` <a id="c_size_t"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_size_t = int
```

---

### `c_ssize_t` <a id="c_ssize_t"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_ssize_t = int
```

---

### `c_ptrdiff_t` <a id="c_ptrdiff_t"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_ptrdiff_t = int
```

---

### `c_float` <a id="c_float"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_float = float
```

---

### `c_double` <a id="c_double"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_double = float
```

---

### `pubptr` <a id="pubptr"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type pubptr = int
```

Opaque pointer types

---

### `fnptr` <a id="fnptr"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type fnptr = int
```

---

### `c_bool` <a id="c_bool"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_bool = int
```

---

### `c_void` <a id="c_void"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type c_void = int
```

---

### `alloc` <a id="alloc"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn alloc(size: int): pubptr
```

Memory Allocation Intrinsics

---

### `free` <a id="free"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn free(ptr: pubptr): nil
```

---

### `realloc` <a id="realloc"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn realloc(ptr: pubptr, new_size: int): pubptr
```

---

### `memcpy` <a id="memcpy"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn memcpy(dest: pubptr, src: pubptr, size: int): nil
```

Memory Manipulation

---

### `memset` <a id="memset"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn memset(ptr: pubptr, value: int, size: int): nil
```

---

### `memcmp` <a id="memcmp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn memcmp(ptr1: pubptr, ptr2: pubptr, size: int): int
```

---

### `ptr_add` <a id="ptr_add"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ptr_add(ptr: pubptr, offset: int): pubptr
```

Pointer Arithmetic

---

### `_ffi_alloc` <a id="_ffi_alloc"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ffi_alloc(size: int): pubptr
```

---

### `_ffi_free` <a id="_ffi_free"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ffi_free(ptr: pubptr): nil
```

---

### `_ffi_load_i8` <a id="_ffi_load_i8"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ffi_load_i8(ptr: pubptr): int
```

---

### `_ffi_load_u8` <a id="_ffi_load_u8"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ffi_load_u8(ptr: pubptr): int
```

---

### `_ffi_store_i8` <a id="_ffi_store_i8"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ffi_store_i8(ptr: pubptr, value: int): nil
```

---

### `_ffi_ptr_add` <a id="_ffi_ptr_add"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ffi_ptr_add(ptr: pubptr, offset: int): pubptr
```

---

### `ptr_sub` <a id="ptr_sub"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ptr_sub(ptr: pubptr, offset: int): pubptr
```

---

### `ptr_diff` <a id="ptr_diff"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ptr_diff(ptr1: pubptr, ptr2: pubptr): int
```

---

### `ptr_align` <a id="ptr_align"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ptr_align(ptr: pubptr, alignment: int): pubptr
```

---

### `ptr_is_aligned` <a id="ptr_is_aligned"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ptr_is_aligned(ptr: pubptr, alignment: int): bool
```

---

### `load_i8` <a id="load_i8"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_i8(ptr: pubptr): int
```

Raw Memory Loading

---

### `load_u8` <a id="load_u8"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_u8(ptr: pubptr): int
```

---

### `load_i16` <a id="load_i16"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_i16(ptr: pubptr): int
```

---

### `load_u16` <a id="load_u16"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_u16(ptr: pubptr): int
```

---

### `load_i32` <a id="load_i32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_i32(ptr: pubptr): int
```

---

### `load_u32` <a id="load_u32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_u32(ptr: pubptr): int
```

---

### `load_i64` <a id="load_i64"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_i64(ptr: pubptr): int
```

---

### `load_u64` <a id="load_u64"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_u64(ptr: pubptr): int
```

---

### `load_f32` <a id="load_f32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_f32(ptr: pubptr): float
```

---

### `load_f64` <a id="load_f64"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_f64(ptr: pubptr): float
```

---

### `load_ptr` <a id="load_ptr"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_ptr(ptr: pubptr): pubptr
```

---

### `store_i8` <a id="store_i8"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_i8(ptr: pubptr, value: int): nil
```

Raw Memory Storing

---

### `store_u8` <a id="store_u8"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_u8(ptr: pubptr, value: int): nil
```

---

### `store_i16` <a id="store_i16"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_i16(ptr: pubptr, value: int): nil
```

---

### `store_u16` <a id="store_u16"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_u16(ptr: pubptr, value: int): nil
```

---

### `store_i32` <a id="store_i32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_i32(ptr: pubptr, value: int): nil
```

---

### `store_u32` <a id="store_u32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_u32(ptr: pubptr, value: int): nil
```

---

### `store_i64` <a id="store_i64"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_i64(ptr: pubptr, value: int): nil
```

---

### `store_u64` <a id="store_u64"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_u64(ptr: pubptr, value: int): nil
```

---

### `store_f32` <a id="store_f32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_f32(ptr: pubptr, value: float): nil
```

---

### `store_f64` <a id="store_f64"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_f64(ptr: pubptr, value: float): nil
```

---

### `store_ptr` <a id="store_ptr"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn store_ptr(ptr: pubptr, value: pubptr): nil
```

---

### `library_load` <a id="library_load"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn library_load(path: str): pubptr
```

Dynamic Linking Operations

---

### `library_unload` <a id="library_unload"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn library_unload(handle: pubptr): nil
```

---

### `library_get_symbol` <a id="library_get_symbol"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn library_get_symbol(handle: pubptr, symbol: str): fnptr
```

---

### `foreign_call` <a id="foreign_call"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn foreign_call(func_ptr: fnptr, args: list, return_type: int = ..., param_types: list = ...)
```

Foreign Calls

---

### `call_i64_0` <a id="call_i64_0"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn call_i64_0(func_ptr: fnptr): int
```

Typed calls are the supported safe-wrapper building blocks. Unlike
`foreign_call`, their complete ABI signature is visible in LIR and can be
implemented identically by every backend.

---

### `call_i64_1` <a id="call_i64_1"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn call_i64_1(func_ptr: fnptr, arg1: int): int
```

---

### `call_i64_2` <a id="call_i64_2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn call_i64_2(func_ptr: fnptr, arg1: int, arg2: int): int
```

---

### `call_f64_2` <a id="call_f64_2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn call_f64_2(func_ptr: fnptr, arg1: f64, arg2: f64): f64
```

---

### `call_void_1` <a id="call_void_1"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn call_void_1(func_ptr: fnptr, arg1: pubptr): nil
```

---

### `CString` <a id="CString"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame CString
```

CString wrapper

#### Members

- `var pub ptr: pubptr` *(field)*
- `var pub length: int` *(field)*
- `var pub is_owned: int` *(field)*

---

### `string_to_cstring` <a id="string_to_cstring"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn string_to_cstring(s: str): CString
```

---

### `cstring_to_string` <a id="cstring_to_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cstring_to_string(p: pubptr): str
```

---

### `cstring_to_string_bounded` <a id="cstring_to_string_bounded"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cstring_to_string_bounded(p: pubptr, max_length: int): str?
```

Convert a foreign C string without scanning beyond caller-owned memory.
Returns nil when no terminator occurs within max_length bytes.

---

### `cstring_free` <a id="cstring_free"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cstring_free(cs: CString): nil
```

---

### `cstring_as_ptr` <a id="cstring_as_ptr"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cstring_as_ptr(cs: CString): pubptr
```

---

### `cstring_from_ptr` <a id="cstring_from_ptr"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cstring_from_ptr(p: pubptr, take_ownership: int): CString
```

---

### `ForeignFunction` <a id="ForeignFunction"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ForeignFunction
```

High-Level Foreign Function Descriptor & Call Wrapper

#### Members

- `var pub name: str` *(field)*
- `var pub func_ptr: fnptr` *(field)*
- `var pub param_types: list` *(field)*
- `var pub return_type: int` *(field)*
- `pub fn call(): any` *(method)*
- `pub fn call_list(call_args: list): any` *(method)*

---

### `declare` <a id="declare"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn declare(name: str, func_ptr: fnptr, param_types: list, return_type: int): ForeignFunction
```

---

### `Library` <a id="Library"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Library
```

High-level Library Abstraction

#### Members

- `var pub handle: pubptr` *(field)*
- `var pub path: str` *(field)*
- `var pub is_loaded: bool` *(field)*
- `pub fn symbol(symbol_name: str): fnptr` *(method)*
- `pub fn func(name: str, return_type: int, param_types: list): ForeignFunction` *(method)*
- `pub fn close(): nil` *(method)*

---

### `load` <a id="load"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load(path: str): Library
```

---

### `load_first` <a id="load_first"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_first(candidates: list): Library
```

Load the first available library from a list of candidate paths.

---

### `callback_create` <a id="callback_create"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn callback_create(func_name: str, arg_types: list, ret_type: int): int
```

---

### `callback_ptr` <a id="callback_ptr"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn callback_ptr(handle: int): fnptr
```

---

### `callback_destroy` <a id="callback_destroy"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn callback_destroy(handle: int): nil
```

---

### `_ffi_callback_create` <a id="_ffi_callback_create"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ffi_callback_create(func_name: str, arg_types: list, ret_type: int): int
```

---

### `_ffi_callback_ptr` <a id="_ffi_callback_ptr"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ffi_callback_ptr(handle: int): fnptr
```

---

### `_ffi_callback_destroy` <a id="_ffi_callback_destroy"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _ffi_callback_destroy(handle: int): nil
```

---

### `Callback` <a id="Callback"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Callback
```

#### Members

- `var pub handle: int` *(field)*
- `var pub pointer: fnptr` *(field)*
- `var pub is_open: bool` *(field)*
- `pub fn close(): nil` *(method)*

---

### `create_callback` <a id="create_callback"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_callback(func_name: str, arg_types: list, ret_type: int): Callback?
```

---

