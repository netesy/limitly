# Drift Analysis (drift.md) — 2026-06-23

## Status: Resolved (current snapshot)

This document tracks drift between the language spec, the implementation, and the standard library. The 2026-06-23 audit and fix pass resolved the CRITICAL and HIGH findings from the drift audit.

## 1. Documentation Drift (Resolved)
- **Keyword alignment**: All occurrences of `class` have been replaced with `frame`. `this` has been replaced with `self`. `@annotation` forms (`@public`, `@protected`, `@private`, `@property`, `@cache`, `@open`) have been removed — use `pub`/`prot` directly. Declarations are private by default when neither `pub` nor `prot` is specified (no explicit `private` keyword).
- **Member access**: Canonical is `self` (not `this`).
- **Paths**: Updated `limitly` execution paths to `./bin/limitly run <file>`.

## 2. Spec Drift (Resolved)
- **language.md**: Updated to v0.2 reflecting the current scanner/parser/type-checker surface.
- **stdlib.md**: Updated to document `core.lm`, `parse.lm`, `encoding.lm`, `io.lm`, `ffi.lm` with the `Encoding`/`Parse`/`File`/`Console` frames and the `map`/`map_err` methods on Result types.

## 3. Philosophical Drift (Resolved)
- **Zen of Limit**: Updated to reflect the practical implementation of `nil` while maintaining the core "absence as state" philosophy.

## 4. Runtime Drift (Resolved)
- Verified that documented examples in `learn.md` and `guide.md` compile and run against the current parser implementation.

## 5. Removed Features (2026-06-23)

The following were removed per user direction:
- **`loop` keyword** — `for`, `while`, and `iter` cover all loop use cases. Use `while (true)` for infinite loops.
- **`private` keyword** — declarations are private by default when neither `pub` nor `prot` is specified.
- **`data` frame modifier** — traits cover the same ground. Use plain `frame` declarations.
- **`@annotation` syntax** — use `pub`/`prot` visibility keywords directly.
- **`this` keyword** — use `self`.
- **`class` keyword** — use `frame`.
- **Long-form visibility** (`public`/`protected`) — use short forms `pub`/`prot`.

## 6. Added Features (2026-06-23)

- **`const` / `val` declarations** — immutable bindings parallel to `var`. Both produce a `VarDeclaration` with `isConst=true`; initializer is required.
- **`::` namespace operator** — scanned as `COLON_COLON` token.
- **`?:` (elvis) and `?.` (safe member)** — scanned as `ELVIS` and `SAFE` tokens.
- **`task` / `worker` keywords** — for structured concurrency. The `name in` part is optional.
- **OR-patterns** — `A | B | C` in match cases via `OrPatternExpr`.
- **Method modifiers** — `static`, `abstract`, `final` on frame methods (parallel to visibility, not interchangeable).
- **`from X import Y`** — Python-style import form.

## 7. Implementation Stubs (Status)

The following were previously documentation-only hints and are now either implemented or marked as stubs that return real errors:
- **Frame modifiers `abstract`/`final`**: Recognized by the parser and stored on `FrameDeclaration`. Type-checker enforcement is partial.
- **Method modifiers `static`/`abstract`/`final`**: Parsed and stored on `FrameMethod`. Type-checker enforcement is partial.
- **`iter` loop type-checking**: Implemented — element types are inferred for list, dict, range, and channel iterables.
- **LIR serializer**: Round-trips every instruction field via a tagged binary format.
- **LIR opcode names**: All 226 opcodes have string representations via X-macro.
- **VM dispatch**: Throws on unknown opcodes instead of silently continuing.
- **ResourceManager**: Implements factories for FILE, STDOUT, STDERR, SOCKET, CHANNEL, MEMORY, ENTROPY.
- **Stdlib stubs**: `process`, `env`, `archive`, `net/dns`, `http/*`, `io.create_directory`, `io.list_directory` return real errors rather than silently succeeding.

## 8. Known Remaining Issues

- **`list_dict_tuple.lm` test**: Pre-existing test bug — iterates over a tuple (`iter (fruit in fruites)` where `fruites` is a tuple), which the type checker now correctly rejects. The test needs fixing.
- **Concurrency tests**: `parallel_blocks.lm` and `concurrent_blocks.lm` have runtime issues with channel/task scheduling that are not yet fully wired.
- **Crypto hashes**: `crypto/hash.lm` uses non-cryptographic rolling hashes for SHA-256/MD5/SHA-1/SHA-512. Rename to `*_insecure` or implement real algorithms in a follow-up.
- **`image.lm`**: Uses wrong symbol names vs `runtime_image.c`; needs FFI symbol alignment.
- **Algorithm module dedup**: `algorithm.lm`, `algorithms.lm`, `sort.lm`, `search.lm` overlap and should be consolidated in a follow-up PR.
- **Trait method dispatch**: `FrameCallMethod`, `FrameCallInit`, `FrameCallDeinit`, `MakeTraitObject`, `TraitCallMethod` opcodes are no-ops in the VM (don't throw, but don't do real dispatch yet). Full trait vtable is deferred.
