# Runtime memory ownership

The VM identifies each region entry by a fresh invocation ID. Lexical IDs remain
in the existing LIR `imm` operand: recursion cannot reuse an active region's
allocation bucket. `RegionMove` promotes a reachable object graph to an active
ancestor; target zero denotes the caller's region. Promotion never shortens a
lifetime. Stores promote children to the container's lifetime, permitting the
VM to skip traversal of graphs already owned by an older region.

Allocation membership and type information live in VM sidecars. The public
`ObjHeader` remains eight bytes and lists and tuples remain 32 bytes, with
data, size and capacity at offsets 8, 16 and 24. Adding intrusive pointers to
the public header would change this ABI. Region cleanup visits its own bucket
and frees each allocation shallowly, so aliases and cycles do not cause recursive
double frees. Frame destructors run before physical reclamation and are
idempotent. Raw payloads, callbacks and resources have separate ownership records.
VM reset and destruction revoke callbacks and release the remaining allocations.

Compiler heap constants have process ownership. Executing VMs cache independent
copies of supported constants in region zero; reset discards those copies.
Unsupported heap constant kinds fail explicitly. Worker VMs borrow parent
objects and publish escaping graphs to parent ownership. Published objects
remain alive until parent teardown; this is deliberately conservative.

Native modules use the existing host helper table for allocation registration
and region operations. A `runtime_semantics=regions-v2` metadata marker prevents
reuse of modules emitted with the old region convention. Object layout and
native API versions are unchanged.

## Standalone Fyra regions

Linux x86_64 executables now lower `RegionEnter`, `RegionExit`, `RegionMove`
and `FrameCallDeinit` to a private standalone ownership runtime. Fyra emits the
machine code; the host linker adds `liblymar_aot.a` and normal process teardown.
The executable does not contain a VM executor. The installer copies this archive
beside the compiler. Object/static-library consumers must link the archive too.
`LYMAR_AOT_CXX` selects the linker driver and `LYMAR_AOT_RUNTIME` selects an
alternate, target-built or instrumented runtime archive.

Dynamic region instances distinguish recursive entries with the same lexical ID.
A typed shadow map records pointer-bearing stack/heap slots without changing
public headers or tagging the standalone backend's existing raw scalar values.
Stores into older containers and globals promote reachable allocation graphs.
Copy/resize preserve outgoing edges; overwriting a pointer with a scalar clears
its metadata. Region cleanup calls frame destructors before shallow reclamation,
handles cycles, and finalizes each frame once. Return and explicit process exit
release remaining ownership through C++ thread-local teardown.

Fyra's x64 object path now preserves incoming arguments across helper calls,
passes mixed floating/integer and stack arguments correctly, materializes spill
addresses, and uses the native stack for IR local allocations. ELF relocations
retain their source sections. Optimizations retain external side effects and
capability metadata, and only promote stack addresses that do not escape. SSA
renaming observes loads and stores in program order.

Automatic standalone runtime linking is currently supported on Linux x86_64.
Other executable targets fail explicitly rather than producing an image without
ownership support. The complete font AOT benchmark remains blocked by the
separate unimplemented `Param` LIR operation in `std.io.file.open`; region lowering
is no longer its blocker. Native shared modules continue to use the C++ emitter
and VM host ownership machinery.

## Validation

`make aot-region-tests` checks private AOT ownership and compares generated
executables against the VM at optimization levels 0, 1 and 2. It covers recursive
returns, indirect calls, strings, nested graphs, cycles, list growth, destructors, mixed argument calls,
and explicit failure/exit behavior.

`make memory-tests` checks recursion, escaping graphs, cycles, globals, constants,
raw allocations, callback revocation, VM reuse and dictionary resizing/order.
`python3 tests/run_tests.py` runs the language regression suite.
`PYTHONPATH=tests/precompiled python3 -m unittest discover -s tests/precompiled -p test_collections_native.py`
checks native collection/font bridging and output parity.

Use separate build directories with `SANITIZERS=address,undefined` to instrument
the compiler, runtime and Fyra dependency. Set `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1`
and `UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1`; select that compiler with
`LYMAR_EXECUTABLE` and increase runner timeouts using `LYMAR_TEST_TIMEOUT_SCALE`.
The legacy negative-test runner currently has invalid Python indentation and
cannot be used as a validation entry point without repair. Use
`python3 tests/memory/run_negative_validation.py` instead; it rejects crashes
and sanitizer failures and recognizes the intentional nil-bounds success cases.

The 2026-10-07 validation on `dev` passed 102 language regressions, all 84
negative-suite cases, and the C++ runtime lifetime checks under ASan/UBSan/LSan.
All ten collection/font bridging and benchmark-validation tests passed both
regularly and with an instrumented compiler and generated native modules.
Leak detection was enabled. Two null dereferences in type-checker diagnostic
recovery and the regex/font native resource leaks were repaired during this run.
Parser grammar was unchanged; the regex regression's import spelling was fixed.

The 2026-10-08 follow-up passed all 102 language regressions and all ten native
collection/font and benchmark-validation tests, including the latter with an
instrumented compiler and native modules under ASan/UBSan with leak detection.
Standalone VM/AOT output parity
passed at `-O0`, `-O1` and `-O2`, including destructor execution on explicit exit.
The private runtime tests, instrumented compiler, and AOT executables linked to
an instrumented runtime passed ASan/UBSan with leak detection enabled. Fyra's object, multiarchitecture
object, SSA, composition, inliner and new object-execution regressions passed.
The new object-execution regression also passed under ASan/UBSan with leak
detection after repairing SCCP's unchecked downcast of floating constants to
integer constants.
The sanitizer runtime checks instrument the private C++ runtime; generated Fyra
machine-code loads/stores are not themselves ASan/UBSan-instrumented.

## Why the precompiled speed appeared to disappear

Native dispatch still works: the benchmark verifies all 50 precompiled width
calls. The glyph metric and kerning cache builders repeatedly concatenated a
single-element list onto a growing list. These quadratic loops already existed
in the font source; graph ownership tracking amplified the cost of their many
temporary arrays. A phase probe measured roughly 12 seconds loading the font,
while the width loop took less than the probe's one-second clock resolution.
Changing those three growing-list expressions to in-place append removed the
copies without changing results or API/ABI.

The three-run font benchmark (`--runs 3 --skip-aot`) now measures these end-to-end
means with DejaVuSans, 50 iterations and identical total width 23337.500000:

| Mode | Before, milliseconds | After, milliseconds |
| --- | ---: | ---: |
| A: interpreted | 11693.99 | 261.46 |
| B: VM plus native font | 11621.91 | 292.86 |
| D: STB C oracle | 65.53 | 68.61 |

These include startup and font loading. Native B is still slightly slower than A
for this small width workload; native compilation alone does not eliminate module
loading and bridge costs. Earlier benchmark code ignored process failures,
did not validate results or native dispatch, and estimated timing phases, so
its historical numbers cannot establish a valid performance regression.

The `regions-v2` metadata marker deliberately invalidates older precompiled
artifacts whose ownership behavior is incompatible. Rebuild those modules against
the current runtime; reusing old binaries would bypass the memory corrections.
