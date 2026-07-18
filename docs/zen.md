# The Zen of Limit

*Explicit is better than implicit.*

*Errors are not exceptions; they are values to be handled.*

*Concurrency should be structured, not chaotic.*

*Safety should not be a sacrifice for performance.*

*Clarity is king; code is read more often than it is written.*

*The absence of a value is a state to be handled explicitly, not a source of crashes.*

*If the implementation is hard to explain, it's a bad idea.*

*If the implementation is easy to explain, it may be a good idea.*

*Modules are one honking great idea -- let's do more of those.*

*Readability counts.*

*Special cases aren't special enough to break the rules.*

*Although practicality beats purity.*

*In the face of ambiguity, refuse the temptation to guess.*

*There should be one-- and preferably only one --obvious way to do it.*

*Although that way may not be obvious at first unless you're a Limiter.*

*Now is better than never.*

*Although never is often better than *right* now.*

---

## Philosophy Mapping

- **Explicit vs Implicit**: Enforced by `TypeChecker::is_type_compatible` (especially for decimal types) and strict type annotations in `src/frontend/type_checker/`.
- **Errors as Values**: Implemented via the unified `Type?` system, `ok()` and `err()` constructors, and `match` statement patterns (`val` and `err`).
- **Structured Concurrency**: Enforced by `parallel` and `concurrent` scope-bound blocks in the parser and LIR generator, ensuring task lifetimes are bound to their lexical scope.
- **Safety**: Managed by the region-based deterministic memory model, where allocations are tied to scopes and destroyed in reverse order.
- **Modules**: Implemented in `src/frontend/module_manager.cpp` and `src/frontend/type_checker_factory.cpp`, enforcing encapsulation and reachability.
