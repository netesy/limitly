# Standard-library FFI delegation plan

## Decision

Limitly should use FFI as an **implementation boundary**, not as the public
standard-library API. Public modules keep Limitly-owned types, fallible results,
resource lifetimes, and backend-neutral semantics. A small native adapter per
dependency exposes a stable C ABI; the adapter, rather than arbitrary third-party
headers, is called through `std.ffi`.

This is the broad separation used by mature systems: Rust hides platform
bindings behind safe `std` APIs, Swift imports C/Objective-C behind Swift value
and error types, and Dart places native calls behind Dart-facing libraries. The
lesson is the boundary, not that every standard-library operation should become
a dynamic-library call.

Callback trampolines remove an important blocker for libraries that report
events, stream data, or enumerate results. They do **not** solve ownership,
struct layout, thread attachment, cancellation, or backend parity.

## Priority 0: harden the boundary

Before migrating another module, make these facilities supported contracts:

1. Fixed-width scalars, pointers, C strings, length-delimited byte buffers, and
   `void` must round-trip on every backend.
2. Document native structs, out parameters, nullable pointers, arrays, and
   platform-sized integers. Prefer opaque handles and adapter functions when
   aggregate ABI details vary by platform.
3. Every native allocation identifies its allocator and exactly one matching
   destructor. A Limitly resource/frame owns the handle and makes `close`
   idempotent.
4. Convert native status codes, `errno`, and library error objects at the adapter
   boundary into typed Limitly fallible errors.
5. Callback handles pin their Limitly callable/context until deregistration.
   Define foreign-thread entry, re-entrancy, shutdown, and the rule that errors
   never unwind through C.
6. Library and symbol loading reports errors instead of representing every
   failure as pointer `0`.

The current public surface has scalar type IDs and opaque integer pointers, while
the high-level call accepts `[any]`. That supports experiments, but is not yet a
safe system-library substrate. The trampoline API also requires explicit
destruction, so wrappers must own its handle rather than return a bare pointer.

## What to delegate

### Priority 1: best immediate candidates

These modules have complex, security-sensitive, or optimized native
implementations and relatively clean handle/buffer boundaries.

| Limitly module | Native implementation behind a C adapter | Why now | Required output checks |
|---|---|---|---|
| `std.net.tls` | platform TLS, OpenSSL, BoringSSL, or rustls C ABI | The current module is explicitly unencrypted TCP passthrough. An unavailable feature is safer than fake TLS. | Handshake status, hostname/peer verification, chain, negotiated protocol, byte counts, close-notify, and error stack. |
| `std.crypto.hash`, `std.crypto.hmac`, `std.crypto.random` | vetted platform or cryptographic library | Avoid custom security primitives and obtain constant-time, audited implementations. Entropy may remain a native runtime resource. | Exact digest/entropy length, algorithm allow-list, unbiased bounded integers, and secret-context zeroization. |
| `std.archive` and compression | zlib/zstd/libarchive adapter | Streaming compression has a compact handle/buffer API and mature implementations. | Expanded-size limit, bytes consumed/produced, checksum, truncation, archive path traversal/link/device entries, and partial-failure cleanup. |
| `std.regex` | PCRE2 or RE2 adapter | Mature engines outperform and out-correct a partial implementation. | Compile offset, subject/offset bounds, UTF mode, match-vector length, resource limits, and no-match versus failure. |
| `std.image` codecs | stb, libpng/libjpeg, or platform codecs | The repository already demonstrates the pattern, but ownership and bounds need completion. | Non-negative dimensions, overflow-safe pixel size, decoded length, channel/format constraints, and codec-specific free. |
| `std.unicode` | ICU or utf8proc adapter | Normalization and categories are data-heavy evolving standards. | UTF policy, byte length, normalization form, data version, and allocator ownership. |
| `std.time.timezone` | ICU/tzdb adapter | Zone rules change independently of the compiler. | Zone existence, ambiguous/nonexistent local times, offset/transition bounds, and data version. |

Prefer one project-owned C adapter with versioned symbols such as
`limitly_native_v1_tls_connect` over direct third-party binding. This normalizes
Windows/POSIX types, prevents macro/struct ABI leakage, and allows static linking
where dynamic loading is undesirable.

### Priority 2: delegate selectively

| Area | Recommendation | Reason |
|---|---|---|
| HTTP client and WebSocket | Consider libcurl or another mature client below the existing request/response API after TLS and byte streams are sound. | Redirects, proxies, HTTP/2/3, decompression, certificate policy, cancellation, streaming, and progress are substantial. |
| DNS | Keep the simple runtime resource; optionally add c-ares/getaddrinfo adapters for asynchronous resolution. | DNS must integrate with cancellation and the scheduler, not accidentally block an executor. |
| File watching | Adapt inotify/kqueue/FSEvents/ReadDirectoryChangesW into normalized callback events. | It is platform-specific and callback-oriented; overflow and rename pairing need explicit semantics. |
| Processes and pipes | Use a platform adapter but retain `std.process` ownership/error types. | Windows and POSIX quoting, inheritance, signals, and wait status are incompatible raw APIs. |
| SQLite | Add `std.database.sqlite` using SQLite's C API. | It is a mature handle API; callbacks enable busy, trace, collation, and user-function hooks. |
| OS credential storage | Use capability-aware platform adapters. | Native security stores are preferable to portable plaintext, but availability and permissions vary. |
| Audio/video codecs | Use native codec adapters when these modules are unfrozen. | Codecs are complex and performance-sensitive; licensing and deployment must be decided first. |

### Keep in Limitly or the backend runtime

Do **not** migrate code merely because FFI exists:

- Keep collection algorithms, iterators, parsing policy, validation, URL logic,
  JSON/TOML/YAML object mapping, base16/base64, pure math, and public data models
  in Limitly. They are portable, inspectable language behavior.
- Keep scheduling, tasks, channels, garbage collection, strings, collection
  representation, and error propagation compiler/runtime-owned. Native libraries
  must never receive pointers to movable VM internals.
- Keep lowest-level file, socket, clock, environment, and entropy operations as
  backend resource/LIR operations where they already exist. They require uniform
  sandboxing, async behavior, and cross-backend equivalence. A backend may call
  OS C APIs internally without exposing those APIs through `std.ffi`.
- Keep UI frozen. These boundary rules can be applied later without putting UI
  types in the FFI ABI now.

## Mandatory input and output validation

Every FFI-backed module should have three layers:

1. **Safe Limitly facade** validates inputs, owns native resources, exposes typed
   fallible results, and never exposes a raw pointer.
2. **Private unsafe binding** performs marshalling only, with no business policy.
3. **Versioned C adapter** maps the dependency/platform ABI to fixed-width
   scalars, opaque handles, `(pointer, length)` buffers, and stable status codes.

### Inputs

- Reject embedded NULs for C strings, or use `(pointer, length)` for binary data.
- Validate enum/type IDs, ranges, offsets, alignments, and buffer lengths.
- Use overflow-checked allocation and element-count arithmetic.
- Enforce path, network, process, and library-loading capabilities first.
- Pin or copy memory for a synchronous call. Transfer asynchronous buffers into
  stable native ownership until completion.
- Register callbacks and context atomically; reject destroyed handles and cap
  callback recursion/re-entry where necessary.

### Outputs

- Check native status before reading out parameters.
- Reject `(null, nonzero_length)`, negative/oversized counts, invalid enum tags,
  invalid UTF, and unterminated strings.
- Bound every scan/copy by trusted capacity; never scan arbitrary foreign memory
  indefinitely to discover a string length.
- Copy validated foreign bytes into compiler-owned values, or retain an opaque
  native buffer with its destructor.
- Convert errors while thread-local error state remains valid.
- Close partially constructed handles and buffers exactly once.
- In callbacks, revalidate pointers/lengths, attach foreign threads if supported,
  capture failures, and return a documented sentinel. Never unwind through C.

## Verification gate for every migration

A module is not migrated until all of these pass on VM and Fyra:

1. **Adapter ABI tests:** symbol version, scalar widths, handle lifetime,
   nullability, buffers, out parameters, and callback lifecycle.
2. **Round trips:** every scalar plus empty, binary, UTF, minimum, and maximum
   buffer values cross Limitly -> C -> Limitly.
3. **Negative cases:** nulls, missing library/symbol, invalid UTF/tags, short or
   oversized output, double close, callback-after-destroy, and native errors map
   to deterministic Limitly errors.
4. **Ownership:** sanitizers and leak checks cover success, early returns, partial
   initialization, and callback teardown.
5. **Concurrency:** test foreign-thread callbacks, simultaneous calls,
   cancellation, shutdown races, and re-entrancy, or explicitly reject them.
6. **Differential behavior:** compare the previous implementation and compare VM
   with Fyra values and errors.
7. **Fuzzing:** fuzz safe facade and adapter for parsers/codecs/TLS framing, with
   allocation limits for decompression/decode bombs.
8. **Deployment:** reproduce dependency discovery, static/dynamic linkage,
   minimum versions, missing optional dependencies, and OS packaging.
9. **Benchmarks:** measure calls, throughput, allocations, and callback overhead;
   do not migrate tiny pure functions where boundary overhead dominates.

## Recommended sequence

1. Complete the FFI contract and cross-backend conformance suite.
2. Replace `std.net.tls` passthrough with real verified TLS.
3. Migrate crypto/hash/HMAC and compression/archive.
4. Harden the image proof of concept into an owned, bounded codec API.
5. Add regex, Unicode, and time-zone adapters.
6. Evaluate HTTP/WebSocket, async DNS, file watching, process control, and SQLite
   only after callback-thread and cancellation semantics are proven.

This order targets correctness and security gaps first, retains portable language
semantics in Limitly, and prevents FFI from becoming a backend-specific second
standard library.
