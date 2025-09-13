Project TODO: Concurrency, match (pattern matching), working/runtime stability, and functional features
================================================================================

This TODO lays out concrete engineering steps to get the concurrency subsystem, the `match` pattern-matching feature, and the functional programming features (immutability, first-class functions, closures) fully implemented, robust, and regression-tested in the project.

High-level pillars
------------------
- Concurrency: channels, tasks, scheduler, event loop, synchronization primitives (atomics, mutexes), and graceful error handling in concurrent contexts.
- Pattern matching (`match`): parser, AST, type checking, exhaustiveness, compile-to-bytecode, runtime match dispatch, and pattern guards.
- Working/runtime stability: deterministic error propagation, informative diagnostics, controlled debug output, memory safety, and regression testing.
- Functional features: first-class functions, closures capturing environments, immutable data patterns, and higher-order utils.

Guiding principles
------------------
- Prefer small, local changes with clear contracts.
- Add unit and regression tests for each behavior change.
- Keep runtime and bytecode ABI stable where possible; add new opcodes sparingly.
- Guard optional verbose diagnostics behind a debug flag.

Concrete roadmap
----------------
1) Concurrency: channel and task primitives
   - Design and document channel semantics (bounded vs unbounded, blocking vs non-blocking behavior, close semantics).
   - Ensure `Channel<ValuePtr>` implementation is thread-safe and supports multiple senders/receivers.
   - Implement native functions: `channel()`, `send(ch, value)`, `receive(ch)`, `close(ch)` and register them in the runtime.
   - Add syntactic sugar mapping: `ch.send(x)` -> `send(ch, x)` and `v = ch.receive()` -> `receive(ch)` so method-style calls work.
   - Implement iteration over channels: `iter (v in ch)` -> iterator object backed by channel receive with stop-on-closed semantics.
   - Add concurrency constructs in AST/bytecode: `BEGIN_CONCURRENT`, `BEGIN_TASK`, `END_CONCURRENT`, task scheduling opcodes.
   - Implement scheduler and executor: thread pool, task queue, and join/wait semantics.
   - Implement error handling policies in concurrent blocks (e.g., Stop, Continue, Collect) and document semantics.
   - Add tests:
     - Smoke test (send/receive across tasks) — deterministic small test.
     - Close semantics test (sending after close, receiving after close).
     - Stress test: many tasks, many sends/receives.

2) Atomics and synchronization
   - Decide representation for atomic integers (AtomicValue wrapper vs new atomic opcodes).
   - Implement atomic operations (fetch_add, fetch_sub, compare_exchange) in VM or via dedicated opcodes.
   - Ensure STORE_VAR and compound assignments `x += 1` operate atomically when the target is atomic.
   - Add tests for atomic increment under heavy concurrency.

3) Method-call fallback and native function mapping
   - Robustly implement `VM::handleCall` extraction of callee and arguments.
   - Add fallback mapping rules: when callee is a member expression on a channel value, map to native `send/receive/close`.
   - Gate verbose diagnostics behind `debugMode` and keep essential diagnostics (UNWRAP_VALUE) concise.
   - Add tests for method-style channel calls and ensure behavior matches free-function calls.

4) Pattern matching (`match`)
   - Parser: add `match` syntax support including case arms, destructuring patterns, and guards.
   - AST: define MatchExpression/MatchArm nodes and pattern AST subnodes (literal patterns, variable capture, wildcard, tuple/list patterns, dict patterns, enum variant patterns).
   - Type checker: implement exhaustiveness checks for enums and sum types; validate capture bindings.
   - Bytecode: decide the lowering strategy (jump table vs sequence of checks) and add opcodes if necessary (MATCH_START, MATCH_CHECK, BIND, MATCH_END).
   - VM runtime: implement pattern matching dispatch and binding of captured variables in arm scopes.
   - Tests:
     - Simple literal pattern matching.
     - Enum/sum variant matching with capture.
     - Destructuring patterns for lists/dicts.
     - Guards and fallthrough semantics.

5) Functional features
   - Ensure closures capture lexical environment safely (values vs references where appropriate).
   - Support function values as `Value` variants; ensure proper invocation and arity checks.
   - Implement immutable container helpers (e.g., persistent lists/maps) if desired.
   - Add tests for closure capture, higher-order functions, and currying scenarios.

6) Diagnostics, error propagation and testing
   - Consolidate error propagation to propagate ErrorValue and ErrorUnion consistently across VM boundaries.
   - Keep `UNWRAP_VALUE` and other critical diagnostics; remove or gate noisy dumps.
   - Add regression test runner outputs for all concurrency/match/functional tests.
   - Add CI tasks to run full test suite including concurrency tests. Document any platform-specific caveats.

7) Performance and stress testing
   - Micro-benchmarks for channel send/receive latency and throughput.
   - Memory profiling (heap usage and allocation hotspots) and improvements (pooling, arenas) as needed.

8) Documentation and examples
   - Write `docs/concurrency.md` describing channel semantics, concurrent blocks, error policies.
   - Write `docs/match.md` with pattern examples and pitfalls.
   - Add cookbook examples under `examples/`.

Minimal immediate action items (next sprint)
-------------------------------------------
- Fix `VM::handleCall` method-call fallback to map `ch.send(x)` -> `send(ch,x)` reliably (high priority).
- Add unit/regression tests for method-style channel calls.
- Run and validate `tests/concurrency/concurrency_smoke.lm`.
- Add expected output files for the concurrency tests to regression suite.

If you want, I can create a smaller, prioritized checklist and start implementing the high-priority fixes (VM call mapping + tests) now.
