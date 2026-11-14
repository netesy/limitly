# GPU Programming in Lymar

Lymar has a first-class GPU programming model: stage functions are declared
with dedicated syntax, carried through the shared register-based LIR, and
executed today by the register VM as **single-pass emulation**. The same LIR
is the input to the Fyra/native lowering path, which is where hardware
execution will land. The software path is kept deliberately semantics-faithful
so it can serve as the **headless oracle** for GPU code: if a kernel produces
correct results under emulation, the lowering is correct when it produces the
same results on hardware.

This document describes the surface as implemented. Sections marked
*Status* call out what is real today versus what is parsed but not yet
lowered.

---

## 1. Stage declarations

GPU work is declared with stage-specific function syntax. `gpu` is a
**contextual** keyword — it is not reserved, so `import std.gpu as gpu`
remains valid and `gpu` can still be used as an ordinary identifier outside
GPU declarations.

```lymar
gpu task integrate(particles: [Particle], dt: float) threads(64, 1, 1) {
    val tid = gpu.thread_id();
    val i = tid.x;
    if (i < count) {
        var p = particles[i];
        p.pos = p.pos.add(p.vel.scale(dt));
        particles[i] = p;
    }
}

gpu vertex transform(in position: Vector3) : VertexOut { ... }
gpu pixel shade(in input: VertexOut) : Vector4 { ... }

gpu mesh emit(vertices: [Vector3]) threads(1, 1, 1)
    limits(vertices = 4, primitives = 2) { ... }
```

| Stage | Syntax | Requirements | Purpose |
|---|---|---|---|
| `gpu task` | `gpu task name(params) threads(x, y, z) { ... }` | `threads(x, y, z)` workgroup size is required | Compute kernel |
| `gpu vertex` | `gpu vertex name(in pos: Type, ...) : Ret { ... }` | Return type required; params may use `in` | Vertex shader |
| `gpu pixel` | `gpu pixel name(in input: Type, ...) : Ret { ... }` | Return type required; params may use `in` | Fragment/pixel shader |
| `gpu mesh` | `gpu mesh name(params) threads(x, y, z) limits(vertices = n, primitives = m) { ... }` | Both `threads` and `limits` required | Mesh/output stage |

Rules:

- `threads(x, y, z)` declares the workgroup (thread-block) size for `task`
  and `mesh` stages. The dispatch grid is expressed in **workgroups**, not
  threads.
- `limits(vertices = n, primitives = m)` on `gpu mesh` declares the maximum
  mesh output topology; `gpu.set_mesh_counts(v, p)` inside the body reports
  the actual emitted counts.
- `in` parameter prefixes on vertex/pixel stages mirror shader-stage input
  semantics; they are accepted by the parser and preserved for lowering.
- `gpu`, the stage names `task`/`vertex`/`pixel`/`mesh` (in this position),
  `threads`, `limits`, and `shared` are contextual identifiers, not reserved
  keywords.

### `gpu.shared` — workgroup-local storage

```lymar
gpu.shared var tile: [float];
gpu.shared var counter: int;
```

`gpu.shared var|val|const name: Type;` declares a binding that is intended to
be **workgroup-local**: one instance per workgroup, shared by all threads in
that group, with visibility governed by `gpu.sync(scope)` barriers.

*Status:* the declaration parses into a `gpuShared` AST flag and is carried
through checking, but the register-VM emulation currently treats it as an
ordinary function-local binding — each emulated thread invocation gets its own
copy, so cross-thread sharing through `gpu.shared` is **not** yet observable
under emulation. True shared-memory lowering (per-workgroup allocation,
barrier semantics) is pending in the hardware path.

---

## 2. Thread-space intrinsics

Inside a GPU body, thread-space queries go through `std.gpu` intrinsics,
which wrap the `gpu_*` builtins the register VM executes:

| Intrinsic | Returns | Meaning |
|---|---|---|
| `gpu.thread_id()` | `UVec3` | Global invocation id across the whole dispatched grid (`group_id * threads + local_id`) |
| `gpu.local_id()` | `UVec3` | Index within the current workgroup |
| `gpu.group_id()` | `UVec3` | Workgroup index within the dispatch grid |
| `gpu.num_groups()` | `UVec3` | Number of workgroups along each grid axis |
| `gpu.sync(scope)` | `nil` | Barrier; `scope` is `gpu.Scope.Workgroup`, `.Subgroup`, or `.Invocation` |
| `gpu.set_mesh_counts(v, p)` | `nil` | Report emitted mesh vertex/primitive counts (`gpu mesh` only) |

`UVec3`, `Extent2D`/`Extent3D` (`gpu.uvec3`, `gpu.extent2d`, `gpu.extent3d`),
and the enums `Scope`, `Stage`, `Access`, `CullMode`, `Topology`,
`TextureFormat`, `MemoryUsage` are re-exported from `std.gpu`.

*Status:* `thread_id`, `local_id`, `group_id`, `num_groups`, `sync`, and
`set_mesh_counts` are implemented in the VM (`src/backend/vm/ops/gpu.cpp`).
`sync` is a no-op under emulation (single-threaded execution needs no
barriers); it exists so kernels written against it lower correctly later.

---

## 3. Host execution model

Host code never calls a `gpu` function directly. It drives execution through
the `std.gpu` device/queue/encoder command model:

```lymar
import std.gpu as gpu;

val dev = gpu.Device();
val queue = dev.default_queue();
val enc = queue.encoder();
enc.dispatch(step_particles, gpu.extent3d(2, 1, 1), [parts, DT, len(parts)]);
val cmd = enc.finish();
queue.submit(cmd);          // returns a Fence
// or: queue.submit_and_wait(cmd);
```

Frames (`std/gpu/`):

- **`Device`** (`gpu.Device()` / `gpu.device()`) — represents the GPU device.
  `info()` → `Info` (name, `backend` string — currently
  `"register-vm-emulation"`), `is_valid()`, `default_queue()`.
  `create_compute_pipeline(kernel, threads?)` → `ComputePipeline?Error` and
  `create_mesh_pipeline(mesh, pixel, max_vertices, max_primitives)` →
  `MeshPipeline?Error` produce immutable pipeline descriptors that a hardware
  backend lowers to shader bytecode. *Status:* descriptors only; no bytecode
  is emitted yet.
- **`Queue`** — `encoder()` creates an `Encoder`; `submit(cmd)` returns a
  `Fence`; `submit_and_wait(cmd)` blocks until completion.
- **`Encoder`** — records work into a `CommandBuffer`: `dispatch(kernel,
  grid: Extent3D, args)` / `dispatch_dims(kernel, gx, gy, gz, args)` for
  compute, `barrier()`, and `finish()` which seals and returns the
  `CommandBuffer`.
- **`CommandBuffer`** — `execute()` runs recorded dispatches;
  `is_empty()` reports whether anything was recorded.
- **`Fence`** — `wait()`, `is_signaled()`. Under emulation submission is
  synchronous, so fences are already signaled when returned.
- **`Error`** — fallible payload for pipeline creation (`Error(code,
  message)`).

Dispatch arguments (`args: [any]`) are marshalled positionally into the
task's parameters; the grid extent counts **workgroups**, and each workgroup
runs `threads(x, y, z)` invocations.

---

## 4. Execution semantics (register-VM emulation)

Today every GPU dispatch executes on the register VM
(`src/backend/vm/ops/gpu.cpp`, opcode path `gpu_dispatch`):

- The dispatcher looks up the named `gpu task` in the function table,
  verifies `gpu_stage == task` and positive grid dims, then iterates the
  dispatch grid × workgroup size, invoking the kernel once per thread with
  `gpu_local_id_`/`gpu_group_id_`/`gpu_thread_dims_` set accordingly.
- `thread_id()` is computed as `group_id * thread_dims + local_id` — the
  standard GPU global-invocation formula.
- Dispatch is **synchronous and single-pass**: `queue.submit` completes
  before returning, so `Fence`s are trivially satisfied and `sync()` needs no
  work.
- Arguments are passed by the VM's normal calling convention; mutations to
  reference-type arguments (lists, frames) are visible to the host after
  submit — this is what makes `particle_sim.lm`'s assertions work.

Because emulation is single-threaded and synchronous, it cannot reproduce
hardware behaviors that depend on true parallelism, memory-model races, or
`gpu.shared` visibility. It **can** verify indexing math, algorithmic
correctness, argument marshalling, and stage plumbing — which is exactly the
oracle role it serves for the lowering work.

---

## 5. Compilation path

```
.gpu stage fn ──► AST (gpu_stage, gpu_threads, limits) ──► type checker
             ──► shared register LIR (FunctionInfo.gpu_stage/gpu_threads)
             ──► register VM  : gpu_dispatch emulation (today, oracle)
             ──► Fyra lowering: hardware shader/dispatch codegen (planned)
```

- Stage metadata lives on `LIR::FunctionInfo` (`gpu_stage`: 0 ordinary,
  1 task, 2 vertex, 3 pixel, 4 mesh; `gpu_threads[3]`; mesh limits), so every
  downstream backend sees the same stage information without re-parsing.
- `gpu vertex`/`gpu pixel`/`gpu mesh` declarations parse and type-check, and
  pipeline descriptors accept them, but the VM has **no dispatch path** for
  them yet — only `gpu task` executes under emulation. Vertex/pixel/mesh
  execution arrives with the graphics lowering, not before.
- `gpu.shared` bindings parse and check but have no workgroup-local lowering
  (see §1).

---

## 6. Status and limitations

| Feature | Status |
|---|---|
| `gpu task` + `threads(x,y,z)` | Implemented; emulated on register VM |
| `gpu.thread_id/local_id/group_id/num_groups` | Implemented (VM emulation) |
| `gpu.sync(scope)` | Parsed/executed as no-op under emulation |
| `gpu.set_mesh_counts` | Implemented as state setter; consumed by mesh path (pending) |
| `Device`/`Queue`/`Encoder`/`CommandBuffer`/`Fence` | Implemented as synchronous emulation model |
| `create_compute_pipeline` / `create_mesh_pipeline` | Descriptor records only; no shader bytecode yet |
| `gpu vertex` / `gpu pixel` | Parse + type-check; no execution path yet |
| `gpu mesh` + `limits(...)` | Parse + type-check; no execution path yet |
| `gpu.shared` workgroup-local storage | Parses; treated as function-local under emulation |
| Hardware GPU execution | Not implemented; Fyra/native lowering is the target path |
| True parallelism / memory model | Not modeled by emulation (by design — oracle, not simulator) |

See also: `docs/language.md` §7 (syntax summary), `AGENTS.md` "GPU Stage
Syntax" (agent rules), `tests/gpu/particle_sim.lm` (working end-to-end
compute example), `tests/gpu/stages.lm` (stage-declaration coverage).
