# Lymar ABI contracts

Lymar's version baseline is **0.0.1**, the hosted native ABI is **1**, and
serialized canonical LIR is **1**. These are separate contracts; a performance
optimization does not by itself require changing any of them.

## Hosted precompiled modules

`src/backend/native/abi.hh` defines the authoritative `Api` and exported entry:

```cpp
LmValue entry(const Api*, void* vm_context, const LmValue* arguments, size_t count);
```

`LmValue` is a 64-bit tagged value. Low bits distinguish pointers, immediate
integers, and nil/booleans. Immediate integers occupy the signed 61-bit range;
larger integers and floats use heap representations where required. See
`src/backend/vm/vm_value_base.hh` and `vm_value.hh`, not an assumed C integer ABI.

The host table carries version/size, generic helper dispatch, numeric conversion,
comparison, truthiness, and string access. Modules export
`lymar_module_abi_version`; the resolver checks it before native dispatch.
`DirectOperations` is a separately validated private feature negotiated through
the existing helper table. It does not change `Api` layout.

Heap pointers belong to the executing VM's lifetime system. A module cannot
free a borrowed object, bypass reference permissions, retain an unpromoted
temporary, or treat an arbitrary pointer as a valid frame. Exceptions and native
scope cleanup preserve region exit obligations. Unknown operations retain the
checked runtime path.

Private generated functions may keep floats unboxed and scalar-replace proven
read-only tuple results. Exported values retain their tagged representation.
These private representations are not ABI fields or serialized LIR types.

## Object layouts and standalone execution

Hosted objects use the concrete structs in `src/backend/vm`: `ObjHeader`,
`LmStringHeader`, lists, dictionaries, tuples, and `LmFrame`. Use `offsetof` and
the target compiler's layout rather than hard-coded offsets. `ObjHeader` is
currently two 32-bit fields; it is not a universal 32-byte object header.

Standalone Fyra lowers canonical LIR using its own internal layouts and
`src/memory/aot_runtime.cpp`. For example, its frame field-address helper is
distinct from the hosted VM's `checked_frame`. These objects are not directly
interchangeable with hosted tagged heap objects. Shared language semantics do
not require identical private runtime representation.

Ordinary foreign calls use their declared C signatures and calling convention,
not the hosted module entry ABI. Conversions, callback lifetimes, alignment,
integer width, reference validity, and explicit foreign cleanup remain required.
See [FFI](ffi.md) and [shared-memory contracts](shared-memory-contracts.md).

## Artifact validation

Sidecar metadata records module identity, target/architecture/OS, artifact kind,
source and dependency hashes, exported names/signatures, and runtime semantics.
The current marker is `lymar-0.0.1-abi1-lir1-ownership-nullable`.
Shared modules must match the executing host. Source signatures available during
loading are checked against declarations; declared dependencies must resolve.
Moved artifacts bind to the adjacent binary, not an old build-machine path.

An accepted sidecar does not prove every export exists. Missing individual
symbols can fall back to source execution. `LYMAR_DISABLE_INTERPRETER_FALLBACK=1`
turns missing intended native dispatch into an error; use it in native benchmarks.
ABI mismatch is an explicit rebuild error, not permission to interpret values
using a different layout.

## Change policy and tests

Change ABI 1 only when a public table, exported calling contract, or shared
layout actually changes. Change serialized LIR independently when its format
changes. Obsolete experimental artifacts may be rebuilt; version numbers do not
represent optimization levels.

Validate source/native outputs, ownership negatives, frame/reference permissions,
serialization restoration, VM/Fyra O0/O1/O2, hosted-native tests, sanitizers, and
artifact rejection/fallback. Atomic access ordering needs its own evidence; an
ordinary load is not sufficient merely because non-concurrent parity tests pass.

See [native optimization plan](native-optimization.md) and
[installation and releases](installation.md).
