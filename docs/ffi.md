# Foreign Function Interface (FFI) & Native Delegation in Lymar (`std.ffi`)

---

## 1. Overview and Core Philosophy

Lymar uses FFI as an **implementation boundary**, not as the public standard-library API. Public modules retain Lymar-owned types, fallible results (`Type?`), deterministic resource lifetimes, and backend-neutral semantics. A small, versioned native adapter per dependency exposes a stable C ABI; that adapter, rather than arbitrary third-party headers, is loaded and invoked through `std.ffi`.

This architecture follows the proven design of mature systems:
- Rust hides platform bindings behind safe `std` abstractions.
- Swift imports C/Objective-C behind Swift value and error types.
- Dart places native calls behind safe Dart-facing libraries.

---

## 2. High-Level Public API

User code interacts with foreign shared libraries (`.so`, `.dll`, `.dylib`) within `unsafe` blocks:

```lymar
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

### Linking foreign native sources at build time

A project can compile its own `.c`/`.cpp` sources with the native toolchain and link
them into every AOT artifact, without any `dlopen` bookkeeping:

```sh
lymar build src/main.lm --native src/adapter.c \
    --native-include src/native --native-cflag -DUSE_SSE --native-link -lm
```

In a project, the same configuration lives in the manifest and needs no flags:

```nol
[native]
sources: ["src/adapter.c", "src/engine.cpp"]
include_dirs: ["src/native"]
link_libs: ["-lm"]
```

Each source is compiled with the target C/C++ driver (`gcc`/`g++`, cross-prefixed for
non-host targets, overridable with `LYMAR_AOT_CC`/`LYMAR_AOT_CXX`) and its object joins
the executable, static archive, shared library, or driver-mediated link. Note the
sources are only consumed by `lymar build` (the interpreter ignores them), and calling
a linked symbol from Lymar code still needs a binding (`declare`/`ForeignCall`, or the
runtime `lib.func(...)` above against the built image); see
[Automatic binding generation from headers](#automatic-binding-generation-from-headers)
for the `--bind-header` workflow.

### Automatic binding generation from headers

`lymar run` and `lymar build` accept `--bind-header` to parse a C `.h` file and
auto-generate an importable Lymar module with typed FFI wrappers:

```sh
lymar run src/main.lm \
    --bind-header include/mylib.h \
    --bind-lib ./libmylib.so
```

Or in the project manifest:

```nol
[native]
headers: ["include/mylib.h"]
bind_libs: ["./libmylib.so"]
```

The compiler writes a generated `.lm` to `.cache/bindings/mylib.lm` and adds that
directory to the module search path. User code simply imports the namespace:

```lymar
import mylib;

fn main() {
    var result = mylib.add(10, 32);
    print(result); // 42
}
```

Generated wrappers use `ffi.library_load` / `ffi.library_get_symbol` / typed call
helpers (`call_i64_0`/`1`/`2`, `call_f64_2`, `call_void_1`) for supported signatures,
and fall back to `ffi.foreign_call` for functions with >2 parameters or mixed types.

The parser handles function declarations, primitive C types (`int`, `float`, `double`,
fixed-width `stdint` types, `size_t`), pointer types, and `const`/`unsigned` qualifiers.
Struct/union/enum definitions, function-pointer parameters, and variadic functions are
skipped with a warning. Reserved keywords used as C parameter names are auto-renamed
with a `p_` prefix.

### Declarative `c:` imports (recommended)

The `--bind-header` workflow can be triggered directly from Lymar source with a
`"c:<header>"` scheme on the `import` statement. The header is parsed and a binding
module is generated at compile time, cached under `.cache/bindings/<ns>.lm`, and
loaded through the ordinary module machinery. No CLI flags are needed.

```lymar
// Full header, linked against a shared library
import "c:math_ops.h" from "libmath_ops" as math;

// Cherry-pick individual symbols (brace-select is sugar for `show`)
import "c:math_ops.h" from "libmath_ops" as math { Point2D, add_points };

// Selective filter with the `show` clause
import "c:math_ops.h" from "libmath_ops" as math show safe_divide;

// System header: no `from` clause -> ffi.library_load("") resolves against the
// process handle (GetModuleHandleA(NULL) / dlopen(NULL, ...)), which is enough
// for CRT symbols in the linked executable.
import "c:stdio.h" as cstdio;
```

Grammar (relative to the base `import` statement):

```
importStmt  ::= "import" ( IDENT ("." IDENT)* | STRING )
                [ "from" STRING ]
                [ "as" IDENT ]
                [ ( "show"|"hide" IDENT ("," IDENT)* | "{" IDENT ("," IDENT)* "}" ) ]
                [ ";" ] ;
```

Header lookup order:
1. Directory of the importing source file.
2. `--native-include` CLI paths and `[native].include_dirs` from the manifest.
3. Directories reported by `gcc -E -Wp,-v -x c -` (when `gcc` is available).
4. `LYMAR_HOME/include`, plus MinGW / `/usr/local/include` / `/usr/include` fallbacks.

Bindings are regenerated only when the header's mtime is newer than the cached `.lm`,
or when a symbol filter is applied (the filter result is not cached to keep the
namespace mapping unambiguous). Cache invalidation matches the `--bind-header` 2b
pipeline exactly, so mixing CLI `--bind-header` with `import "c:..."` on the same
header yields a single shared `.cache/bindings/<ns>.lm`.

Proof: `tests/native/verify_cimport.py` exercises the four variants above plus the
cache-reuse guarantee.

---

## 3. ABI Type Mapping Table

| Lymar Type Identification (`std.ffi`) | Native C Type | C++ Type |
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

```lymar
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

```lymar
var c_str = ffi.string_to_cstring("Hello C");
var ret_len = strlen_func.call(c_str.ptr);
ffi.cstring_free(c_str);
```

For foreign strings whose allocation is not controlled by Lymar, use `cstring_to_string_bounded(ptr, capacity)` to prevent buffer overruns if a NUL terminator is absent.

### Memory Ownership Summary
| Value / Boundary | Allocator | Owner | Freeing Rule |
|---|---|---|---|
| Lymar String (`str`) | Lymar Runtime / VM | Lymar VM | Managed by Lymar VM; passed as read-only pointer across FFI |
| `ffi.string_to_cstring()` | Host `malloc()` via `std.ffi` | Lymar `CString` holder | Explicitly freed via `ffi.cstring_free()` |
| Native C Allocation | Native C Library | Native C Library | Native library owns and frees |

---

## 6. Standard-Library Delegation Architecture

Every FFI-backed standard module follows a strict 3-tier layering model:

1. **Safe Lymar Facade**: Validates arguments, owns native resource handles, exposes typed fallible returns (`Type?`), and never exposes raw pointers to user code.
2. **Private Unsafe Binding**: Performs pure ABI marshalling without business logic.
3. **Versioned C Adapter**: A C/C++ translation wrapper providing normalized, fixed-width scalars, opaque handles, and stable status codes (e.g., `lymar_native_v1_tls_connect`).

### What to Delegate
- **`std.net.tls`**: Platform TLS, OpenSSL, or BoringSSL adapter.
- **`std.crypto`**: Vetted cryptographic libraries for SHA, HMAC, AES, and secure random entropy.
- **`std.archive`**: zlib / zstd streaming compression adapters.
- **`std.regex`**: PCRE2 / RE2 engines.
- **`std.image`**: stb_image / libpng / libjpeg codecs.
- **`std.unicode`**: utf8proc / ICU normalization.

### What to Keep in Lymar
- **Pure Language Algorithms**: Collections, iterators, string parsers, URL logic, JSON/TOML decoders, math algorithms.
- **Runtime Cores**: Task scheduler, fiber lifecycles, memory regions, channels, and error propagation.
