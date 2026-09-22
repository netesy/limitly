# Implementation audit: verification, parallelism, and language tooling

Audit date: 2026-09-22

This document records what is implemented in the current tree and, equally
importantly, what is not. Passing smoke tests is not treated as evidence of a
complete subsystem.

## Executive result

| Area | Status | What exists | Completion blockers |
| --- | --- | --- | --- |
| Refinements and contracts | **Partial** | Native linear-integer constraint propagation, Boolean composition, counterexample rejection, and strict/hybrid policy | No external SMT solver, quantified/nonlinear/collection theories, path-sensitive VC generation, proof cache, models, or proof certificates |
| Linear parallel capabilities | **Partial** | AST capability metadata with element types, a capability type, canonical acquire/release LIR, frontend index-pattern checks, and VM overlap checks | Capabilities are not split per worker/core; arbitrary affine partitions and read capabilities are absent |
| Parallel execution | **Incomplete** | Configuration is encoded and structured boundaries are emitted | `parallel` bodies are emitted inline and execute serially; `cores` does not create workers |
| VM/Fyra parity | **Incomplete** | Both backends accept the concurrency opcodes | VM executes tasks serially and validates capability tokens; Fyra represents schedulers as lists, treats release as a no-op, and does not implement equivalent timeout/capability behavior |
| Deterministic reduction/failure | **Partial** | VM scheduler visits task contexts in creation order; channel folding after a join is deterministic under that serial scheduler | No canonical reduction instruction/tree; no parallel commit buffer; no cross-backend failure-order conformance tests |
| Incremental LSP | **Partial** | JSON-RPC framing, versioned open-document snapshots, ranged text synchronization, diagnostics, and completion | Every edit rescans, reparses, resolves, and rechecks the entire document; no syntax/type dependency graph, invalidation cache, cancellation, or cross-file incremental analysis |
| Typed holes | **Partial** | First-class hole AST node, contextual expected-type diagnostics, and exported typed-hole query results | Stable source spans and richer lexical environments are absent |
| Proof-aware completion | **Partial** | Completion consumes typed-hole results, derives candidates from predicate bounds, and validates witnesses with `SMTVerifier` | It cannot yet use branch/path assumptions and witness synthesis is not complete for nonlinear or non-integer refinements |
| E-graphs/equality saturation | **Not implemented** | Existing phase-ordered AST/LIR optimizers only | Requires e-class representation, rewrite rules, extraction cost model, and pipeline integration |
| Algebraic effects/handlers | **Not implemented** | Scheduler/task state-machine runtime remains | Requires effect typing, handler syntax/AST, continuation LIR, lowering, and both backend implementations |
| Data-parallel layout decoupling | **Not implemented** | Fixed frame offsets are calculated during LIR generation | Requires logical layout types, layout selection, access-path LIR, ABI rules, and backend lowering |

## Evidence and acceptance criteria

### Verification

`SMTVerifier` is currently a facade over `ConstraintEngine`, whose supported
fragment is normalized linear integer relations. Unsupported AST forms return
`Unsupported`; there is no SMT process/library integration. Strict mode is
useful because it fails closed, but describing the current engine as a complete
push-button SMT implementation is inaccurate.

Completion requires:

1. A VC generator carrying branch assumptions, function pre/postconditions,
   refinement environments, and contract obligations.
2. A real SMT backend with deterministic time/resource limits and explicit
   `sat`/`unsat`/`unknown` mapping.
3. Hybrid runtime lowering only for `unknown`/unsupported obligations and
   strict rejection for every non-`unsat` negated VC.
4. Tests for assumptions, nonlinear rejection, solver timeout, model reporting,
   interprocedural contracts, and backend erasure of proven checks.

### Parallel capabilities and execution

The frontend recognizes writes of the form `collection[index_variable]` and
attaches one range capability. The generator then emits the original body
directly between `ParallelInit` and `ParallelSync`; it does not outline the
loop, partition its range, or schedule chunks. Therefore current behavior is
race-free primarily because it is serial, not because multiple cores receive
disjoint tokens.

Completion requires:

1. Canonical LIR instructions for split, worker launch, ordered join, failure
   records, and deterministic reduction.
2. An outlined worker function receiving a linear child capability that cannot
   escape, alias, or be reused after join.
3. A deterministic partition function for static and runtime bounds.
4. Genuine VM worker-pool execution and equivalent Fyra runtime calls.
5. Backend conformance tests that run the same LIR and compare values, ordered
   failures, timeouts, cancellation, and capability violations.

### LSP and typed holes

The server incrementally synchronizes text, but `diagnostics_for` constructs a
new scanner, parser, module resolution, and type checker for the complete
document after every accepted edit. Completion consumes compiler-produced typed
hole results and validates refinement witnesses through `SMTVerifier`, but it
still reruns whole-document analysis and uses predicate-guided candidate
enumeration rather than a solver model.

Completion requires:

1. Persistent token/green-tree storage and range-based relex/reparse.
2. Declaration and module dependency graphs with targeted type-check
   invalidation.
3. Stable diagnostic identity and accurate source ranges.
4. A compiler query returning each hole's expected type, lexical environment,
   refinements, and proof assumptions.
5. Completion candidates checked through the same type compatibility and SMT
   APIs used by compilation, with cancellation and request-version guards.

## Test interpretation

The existing tests establish syntax acceptance, selected diagnostics, serial
observable ordering, and presence of capability opcodes. They do **not** prove
multicore execution, VM/Fyra equivalence, semantic incremental recomputation,
or general SMT-backed completion. Future tests should measure those properties
directly rather than inferring them from opcode presence or successful smoke
runs.
