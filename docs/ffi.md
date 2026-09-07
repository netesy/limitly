# Foreign Function Interface (FFI) in Limitly (`std.ffi`)

`std.ffi` provides standard, typed C ABI interoperability for Limitly, allowing standard C and C++ dynamic libraries (`.so`, `.dll`, `.dylib`) to be loaded and called safely without exposing internal VM object headers or memory region semantics.

---

## 1. High-Level Public API

```limit
import std.ffi as ffi;

fn main() {
    unsafe {
        // Load foreign library
        var lib = ffi.load("./libexample.so");
        assert(lib.is_loaded, "Failed to load library");

        // Declare function signature
        var add = lib.func("add_i32", ffi.TYPE_I32, [ffi.TYPE_I32, ffi.TYPE_I32]);

        // Invoke native function
        var result = add.call(10, 32);
        print(result); // 42

        lib.close();
    }
}
```

---

## 2. ABI Type Mapping Table

| Limit Type Identification (`std.ffi`) | Native C Type | C++ Type |
|---|---|---|
| `ffi.TYPE_I8` | `int8_t` | `int8_t` |
| `ffi.TYPE_U8` | `uint8_t` | `uint8_t` |
| `ffi.TYPE_I16` | `int16_t` | `int16_t` |
| `ffi.TYPE_U16` | `uint16_t` | `uint16_t` |
| `ffi.TYPE_I32` | `int32_t` | `int32_t` |
| `ffi.TYPE_U32` | `uint32_t` | `uint32_t` |
| `ffi.TYPE_I64` | `int64_t` / `long long` | `int64_t` |
| `ffi.TYPE_U64` | `uint64_t` | `uint64_t` |
| `ffi.TYPE_F32` | `float` | `float` |
| `ffi.TYPE_F64` | `double` | `double` |
| `ffi.TYPE_PTR` | `void*` / `const char*` | `void*` |
| `ffi.TYPE_VOID` | `void` | `void` |

---

## 3. Unmanaged Memory Operations

Raw unmanaged memory allocation and direct pointer reads/writes require an `unsafe` block:

```limit
import std.ffi as ffi;

unsafe {
    var ptr = ffi.alloc(16);
    ffi.store_i32(ptr, 42);
    var val = ffi.load_i32(ptr);
    ffi.free(ptr);
}
```

Available low-level intrinsics in `std.ffi`:
- `alloc(size: int): pubptr`
- `free(ptr: pubptr): nil`
- `realloc(ptr: pubptr, new_size: int): pubptr`
- `load_i8`, `load_u8`, `load_i16`, `load_u16`, `load_i32`, `load_u32`, `load_i64`, `load_u64`, `load_f32`, `load_f64`, `load_ptr`
- `store_i8`, `store_u8`, `store_i16`, `store_u16`, `store_i32`, `store_u32`, `store_i64`, `store_u64`, `store_f32`, `store_f64`, `store_ptr`
- `memcpy`, `memset`, `memcmp`
- `ptr_add`, `ptr_sub`, `ptr_diff`, `ptr_align`, `ptr_is_aligned`

---

## 4. CString Helpers and Lifetime Rules

```limit
var c_str = ffi.string_to_cstring("Hello C");
var ret_len = strlen_func.call(c_str.ptr);
ffi.cstring_free(c_str);
```

### Memory Ownership Summary
| Value / Boundary | Allocator | Owner | Freeing Rule |
|---|---|---|---|
| Limit String (`str`) | Limit Runtime GC/VM | Limit VM | Managed by Limit VM; passed as read-only C string pointer across FFI |
| `ffi.string_to_cstring()` | Host `malloc()` via `std.ffi` | Limit `CString` holder | Explicitly freed via `ffi.cstring_free()` |
| Native C Allocation (`malloc`) | Native C Library | Native C Library | Native C library owns and frees |
