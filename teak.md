| Area             | Current     | Suggested Improvement                 | Goal                  |
| ---------------- | ----------- | ------------------------------------- | --------------------- |
| Unions/Sums      | Exist       | Merge into single discriminated union | Simplify model        |
| Type Checking    | Structural  | Add flow-sensitive narrowing          | Fewer runtime checks  |
| Error Handling   | Typed `Err` | Add propagation + static enforcement  | Ergonomic + safe      |
| Refinement       | Partial     | Add value-based type constraints      | Domain precision      |
| Pattern Matching | Partial     | Exhaustive + tag binding              | Compile-time safety   |
| Inheritance      | None        | Use structural typing instead         | Bare-metal compatible |
| Generics         | ❌           | Not needed — use unions/refinement    | Keep system concrete  |
Refine our type syetem to use this table as a guide above, edit our docs/ to show this when done 