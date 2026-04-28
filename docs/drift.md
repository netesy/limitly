# Drift Analysis (drift.md)

## 1. Documentation Drift

### Beginner Risk (learn.md)
- **Keyword Mismatch**: `learn.md` teaches `class` for defining objects, but the compiler only accepts `frame`.
- **Method Syntax**: `learn.md` shows `class Greeter { fn say_hello() ... }` without visibility modifiers, but the default is `private`.
- **Initialization**: `learn.md` mentions `randint(min, max)` and `read_line()` which are not verified to exist in `std/`.

### User Risk (guide.md)
- **Keyword Mismatch**: Continues to use `class` in several sections while correctly identifying `frame` in others.
- **Planned Features**: Documents ternary operator (`? :`) and range steps (`0..10..2`) as "planned but not yet implemented", which is honest but creates a gap between guide and reality.
- **Abstract/Final Classes**: Documents `abstract class` and `final class`, but the parser only handles these as modifiers for `frame`.

## 2. Philosophical Drift (zen.md)
- **"Modules are one honking great idea"**: Fully enforced in `src/frontend/module_manager.cpp`.
- **"Explicit is better than implicit"**: Mostly enforced, but `learn.md` downplays the necessity of type annotations which are often required by the `TypeChecker`.

## 3. Spec Drift
- **language.md**: Missing. Formal specification of syntax and semantics is absent.
- **stdlib.md**: Missing. Library functions like `print` and `assert` are used but not formally documented.

## 4. Runtime Drift
- **`class` keyword**: The scanner recognizes `class` but the parser does not use it for declarations.
- **`this` vs `self`**: The parser accepts both, but tests exclusively use `this`. `learn.md` uses `self` and `this` inconsistently.

## 5. Classification Summary

| Drift Type | Risk Level | Description |
|------------|------------|-------------|
| **Doc Drift** | **HIGH** | `learn.md` teaches `class` which is invalid syntax. |
| **Philosophical**| **LOW** | Philosophy matches implementation well. |
| **Spec Drift** | **MEDIUM**| Missing formal spec files. |
| **Runtime Drift**| **LOW** | Minor inconsistencies in keyword support (`this`/`self`). |
