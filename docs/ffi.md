# Foreign Function Interface (FFI) & Native Delegation in Limitly (`std.ffi`)

---

## 1. Overview and Core Philosophy

Limitly uses FFI as an **implementation boundary**, not as the public standard-library API. Public modules retain Limitly-owned types, fallible results (`Type?`), deterministic resource lifetimes, and backend-neutral semantics. A small, versioned native adapter per dependency exposes a stable C ABI; that adapter, rather than arbitrary third-party headers, is loaded and invoked through `std.ffi`.

This architecture follows the proven design of mature systems:
- Rust hides platform bindings behind safe `std` abstractions.
- Swift imports C/Objective-C behind Swift value and error types.
- Dart places native calls behind safe Dart-facing libraries.

---

## 2. High-Level Public API

User code interacts with foreign shared libraries (`.so`, `.dll`, `.dylib`) within `unsafe` blocks:

```limit
import std.ffi as ffi;

fn main() {
    unsafe {
        // Load foreign library
        var lib = ffi.load("./libexample.so");
        assert(lib.is_loaded, "Failed to load library");

        // Declare function signature: func(name, return_type, [param_types])
        var add = lib.func("add_i32", ffi.TYPE_I32, [ffi.TYPE_I32, ffi.TYPE_I32]);

        // Invoke native function
        var result = add.call(10, 32);
        print(result); // 42

        lib.close();
    }
}
```

---

## 3. ABI Type Mapping Table

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

## 4. Unmanaged Memory Operations

Raw unmanaged memory allocation and direct pointer reads/writes are restricted to `unsafe` blocks:

```limit
import std.ffi as ffi;

unsafe {
    var ptr = ffi.alloc(16);
    ffi.store_i32(ptr, 42);
    var val = ffi.load_i32(ptr);
    ffi.free(ptr);
}
```

### Low-Level Memory Intrinsics
- `alloc(size: int): pubptr`
- `free(ptr: pubptr): nil`
- `realloc(ptr: pubptr, new_size: int): pubptr`
- `load_i8`, `load_u8`, `load_i16`, `load_u16`, `load_i32`, `load_u32`, `load_i64`, `load_u64`, `load_f32`, `load_f64`, `load_ptr`
- `store_i8`, `store_u8`, `store_i16`, `store_u16`, `store_i32`, `store_u32`, `store_i64`, `store_u64`, `store_f32`, `store_f64`, `store_ptr`
- `memcpy`, `memset`, `memcmp`
- `ptr_add`, `ptr_sub`, `ptr_diff`, `ptr_align`, `ptr_is_aligned`

Raw allocations are ownership-tracked. `free` and `realloc` accept only pointers returned by `ffi.alloc` / `ffi.realloc`. Foreign library allocations must be reclaimed using their matching foreign destructor.

---

## 5. CString Helpers and Lifetime Rules

```limit
var c_str = ffi.string_to_cstring("Hello C");
var ret_len = strlen_func.call(c_str.ptr);
ffi.cstring_free(c_str);
```

For foreign strings whose allocation is not controlled by Limitly, use `cstring_to_string_bounded(ptr, capacity)` to prevent buffer overruns if a NUL terminator is absent.

### Memory Ownership Summary
| Value / Boundary | Allocator | Owner | Freeing Rule |
|---|---|---|---|
| Limit String (`str`) | Limit Runtime / VM | Limit VM | Managed by Limit VM; passed as read-only pointer across FFI |
| `ffi.string_to_cstring()` | Host `malloc()` via `std.ffi` | Limit `CString` holder | Explicitly freed via `ffi.cstring_free()` |
| Native C Allocation | Native C Library | Native C Library | Native library owns and frees |

---

## 6. Standard-Library Delegation Architecture

Every FFI-backed standard module follows a strict 3-tier layering model:

1. **Safe Limitly Facade**: Validates arguments, owns native resource handles, exposes typed fallible returns (`Type?`), and never exposes raw pointers to user code.
2. **Private Unsafe Binding**: Performs pure ABI marshalling without business logic.
3. **Versioned C Adapter**: A C/C++ translation wrapper providing normalized, fixed-width scalars, opaque handles, and stable status codes (e.g., `limitly_native_v1_tls_connect`).

### What to Delegate
- **`std.net.tls`**: Platform TLS, OpenSSL, or BoringSSL adapter.
- **`std.crypto`**: Vetted cryptographic libraries for SHA, HMAC, AES, and secure random entropy.
- **`std.archive`**: zlib / zstd streaming compression adapters.
- **`std.regex`**: PCRE2 / RE2 engines.
- **`std.image`**: stb_image / libpng / libjpeg codecs.
- **`std.unicode`**: utf8proc / ICU normalization.

### What to Keep in Limitly
- **Pure Language Algorithms**: Collections, iterators, string parsers, URL logic, JSON/TOML decoders, math algorithms.
- **Runtime Cores**: Task scheduler, fiber lifecycles, memory regions, channels, and error propagation.
