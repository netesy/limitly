
## Standard-library boundary

Collection implementations live in `std/collections` and related standard-library modules. The scanner, parser, type checker, LIR, and VM continue to parse and type-check collection shorthand syntax, but they do not own the standard collection algorithms or data-structure implementations.

## Parser conformance audit notes

The current standard-library expansion intentionally avoids scanner, parser, type-checker, VM, and runtime changes. New APIs use existing frame declarations, function declarations, concrete list shorthand types, function type annotations, `self`, `nil`, block `if` statements, `while` loops, and existing bitwise operators.
