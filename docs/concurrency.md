# Structured Concurrency in Limitly

Limitly has two deliberately separate structured-concurrency models:

- `parallel` is CPU-oriented, fork/join data parallelism. Mutable collections
  require compiler-proven linear slice capabilities.
- `concurrent` is task-oriented cooperative concurrency. Tasks and workers
  communicate through channels; mutable collection sharing is not permitted.

Neither construct exposes backend-specific threading primitives.

## `parallel`

```lm
parallel(
    cores = Auto | Int,
    timeout = Duration?,
    grace = Duration?,
    on_error = Stop | Continue | Partial
) {
    iter(i in 0..length(output)) {
        output[i] = transform(input[i]);
    }
}
```

### Configuration

| Option | Meaning |
|---|---|
| `cores` | `Auto` uses the host concurrency level; an integer must be 1–256. |
| `timeout` | Maximum duration for the structured operation. Durations accept `ns`, `us`, `ms`, or `s`. Zero disables the deadline. |
| `grace` | Cleanup window after cancellation. Durations use the same units. |
| `on_error=Stop` | Cancel remaining work and surface the first failure. |
| `on_error=Continue` | Continue independent work and report failures at the join. |
| `on_error=Partial` | Stop scheduling new work, join completed work, and retain completed results. |

Names are case-insensitive. Invalid values are compile errors rather than silent
fallbacks.

### Linear slice capability rules

For every mutable collection accessed by a parallel iterator, the compiler
creates a capability:

```text
(collection identity, iterator, begin, end, mutable)
```

The range is half-open. The capability is valid only when:

1. its bounds are compile-time integers;
2. `0 <= begin < end`;
3. every write is indexed by that iterator's own index variable; and
4. no simultaneously active mutable capability overlaps the collection.

Thus `output[i] = ...` is accepted, while `output[0] = ...` is rejected because
every iteration would receive authority to mutate the same element. Read-only
iterations do not need an exclusive capability.

Capabilities are frontend-owned metadata on `ParallelStatement`. Lowering
validates them again, preserves collection identity, emits the common
`ParallelInit`/`ParallelSync` LIR boundary, and rejoins ownership at the end of
the block. There is no implicit shared-memory box or copy-back step.

`task` and `worker` are not legal inside `parallel`; use `iter` so the compiler
can prove the mapping between iterations and owned slices.

## `concurrent`

```lm
var events = channel();
var results = channel();

concurrent(
    ch = events,
    cores = Auto,
    timeout = 30s,
    grace = 250ms,
    on_error = Stop,
    on_timeout = Partial
) {
    worker(event in events) {
        results.send(handle(event));
    }
}
```

### Why concurrent uses a different guarantee

A linear slice proof relies on a finite index space and a one-to-one mapping
from an iteration index to an element. Concurrent tasks may be created from
channels, timers, network events, and unbounded streams, so that proof does not
exist in general.

Instead, `concurrent` guarantees isolation by ownership transfer and channel
communication:

- task-local values may be mutated by their owning task;
- immutable values may be read by multiple tasks;
- channels may be shared for communication;
- an outer mutable collection may not be mutated by multiple tasks;
- a value sent through a channel crosses the task boundary explicitly.

Use `parallel` for finite indexed mutation and `concurrent` for asynchronous
message processing. The guarantees are complementary rather than weaker and
stronger versions of one mechanism.

### Tasks and workers

- `task(i in 1..10)` creates discrete scheduled jobs.
- `worker(item in source)` drains a channel or iterable.
- A worker with no input source does not receive a synthetic `nil` item.
- The structured block joins its scheduled work before the enclosing scope
  continues.

Resource-backed and pointer-backed channels have identical send, receive,
poll, and close semantics in the VM.

## Examples

### Valid parallel mutation

```lm
var output = [0, 0, 0, 0];
parallel(cores=2) {
    iter(i in 0..4) {
        output[i] = i * i;
    }
}
```

### Rejected parallel race

```lm
var output = [0, 0, 0, 0];
parallel(cores=2) {
    iter(i in 0..4) {
        output[0] = i; // error: all iterations target the same element
    }
}
```

### Concurrent channel pipeline

```lm
var output = channel();
concurrent(ch=output, cores=4, on_error=Continue) {
    task(i in 1..10) {
        output.send(process(i));
    }
}

iter (value in output) {
    consume(value);
}
```

## Backend contract

The LIR concurrency instructions are backend-neutral. Every backend must
preserve:

1. structured join behavior;
2. channel ordering and ownership transfer;
3. configured deadlines and error policy;
4. capability-approved collection identity; and
5. absence of data races for accepted programs.

A backend may use native threads, a work-stealing pool, fibers, or a cooperative
scheduler, but it may not weaken these observable semantics or introduce a
backend-only capability instruction.
