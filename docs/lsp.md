# Language server with incremental document synchronization

Run the server with `limitly -lsp`. It implements JSON-RPC 2.0 framing with
`Content-Length` headers and supports `initialize`, `shutdown`, `exit`,
`textDocument/didOpen`, incremental `textDocument/didChange`,
`textDocument/didClose`, diagnostics, and completion.

Each open URI has an independent versioned source snapshot. Range changes are
applied to that snapshot without rereading the file, stale versions are
discarded, and only the changed document is rescanned and type checked. The
analysis itself is currently whole-document: it does not yet reuse tokens,
syntax subtrees, or type-check results within that document. Closing a document
releases its snapshot and clears its diagnostics.

## Typed holes

`?` in expression position is a typed hole. The type checker propagates the
contextual expected type into the hole and emits a focused `typed hole:
expected ...` diagnostic, which prevents incomplete programs from reaching a
backend.

Completion at a hole consumes the type checker's typed-hole query to rank
literal inhabitants and compatible bindings. For a
refinement alias such as `type Positive = int where value > 0`, completion
constructs a literal witness satisfying the supported linear predicate and
labels it only after the compiler's `SMTVerifier` proves the candidate.
Candidate enumeration derives integer witnesses from predicate bounds but does
not yet carry branch-local proof assumptions or request solver models, so this
is not complete synthesis for every inhabited refinement.
