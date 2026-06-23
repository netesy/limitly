# Drift Analysis (drift.md) — 2026-06-23

## Status: Partially Resolved (updated 2026-06-23)

This document tracks drift between the language spec, the implementation, and the standard library. A second audit pass addressed stdlib syntax drift and documentation residuals.

## 1. Documentation Drift (Mostly Resolved)
- **Keyword alignment**: All occurrences of `class` have been replaced with `frame`. `this` has been replaced with `self` in language.md. `@annotation` forms removed. Declarations are private by default when neither `pub` nor `prot` is specified (no explicit `private` keyword).
- **Member access**: Canonical is `self` (not `this`). Fixed in guide.md.
- **guide.md**: Replaced remaining `this` references with `self`, removed `@public`/`@protected`/`@private` annotations, replaced frame inheritance examples with trait-based composition.
- **learn.md**: Replaced `loop {` with `while (true) {`.
- **evolution.md**: Removed `loop` from implemented loops list.
- **README.md**: Fixed C++17 → C++20 to match Makefile.
- **Paths**: README shows `./limitly sample.lm` (no `run` subcommand); Makefile test target uses `./bin/limitly "$1"`.

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

## 9. Stdlib Syntax Drift (Fixed 2026-06-23)

A second audit found the std/ library files using syntax not supported by the parser/scanner. All fixes applied:

- **`null` → `nil`**: `app.lm` used `null` (not a keyword). Replaced all 6 occurrences with `nil`.
- **`if...then...else` ternary → `? :` operator**: 9 occurrences across `strings.lm`, `hashmap.lm`, `collections.lm`, `data_structures.lm`, `graph.lm`, `priority_queue.lm`, `async.lm`. The `then` keyword is not part of the ternary/if syntax; converted to `cond ? expr1 : expr2`.
- **`pub var` inside method bodies**: ~80+ occurrences across `strings.lm`, `async.lm`, `hashmap.lm`, `collections.lm`, `data_structures.lm`, `graph.lm`, `priority_queue.lm`. Visibility modifiers are only valid on frame-level and top-level declarations, not local variables.
- **Frame fields missing `var` keyword**: `gg.lm` and `image.lm` declared frame fields as `pub name: str;` instead of `pub var name: str;`. The parser requires the `var` keyword.
- **`delete dict[key]`**: `ffi.lm` used `delete` as a statement (not a supported keyword). Replaced with `dict[key] = 0;`.
- **`match` on error-union return**: `fs.lm` used `match` to destructure error-union types. Converted to `if (result == nil)` pattern consistent with the rest of the stdlib.

## 10. Graphics Module Issues (Fixed 2026-06-23)

- **`gg.lm`**: Fixed frame field declarations (added `var`), removed unused `import std.ffi as ffi;`. Note: all intrinsic hooks remain stubs — no LIR intrinsics or runtime support exist yet.
- **`image.lm`**: Fixed frame field declarations (added `var`).
- **`color.lm`**: `to_hex()` was a placeholder returning `"#000000"`. Implemented proper hex conversion with clamping and a `hex_byte` helper.
- **`geometry.lm`**: `Circle::area()` used hardcoded `3.1415926535` instead of `math.PI`. Fixed to use `math.PI`.
