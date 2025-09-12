lembed — Embedding precompiled bytecode into Limitly

Summary
-------
This document records the work done to add a "lembed" facility to the Limitly project: a workflow and tooling to take a Limitly source file, produce bytecode for the VM, convert that bytecode into C++ that registers the bytecode at program startup, and finally build a standalone interpreter binary containing the embedded bytecode.

What we implemented
-------------------
- Runtime embed registry (`src/lembed.hh` / `src/lembed.cpp`)
  - API: `lembed::registerEmbed(name, bytecode)`, `lembed::getEmbeddedBytecode(name)`, `lembed::listEmbeddedNames()`.
  - Allows generated code to register one or more embedded bytecode blobs for lookup at runtime.

- Builtin example embed (`src/lembed_builtin.cpp`)
  - A small example embed (push-string, print, halt) with an explicit `registerBuiltinEmbeds()` function.
  - We intentionally avoid static initialization registration and instead call explicit registration functions at startup to avoid static-init order problems.

- Generator script (`tools/goembed.py`)
  - Python script to convert a textual bytecode dump (the `.lm.bytecode.txt` produced by `limitly -bytecode`) into `src/lembed_generated.cpp` and `src/lembed_generated.hh`.
  - The generated C++ defines `registerGeneratedEmbeds()` which calls `lembed::registerEmbed()` for each embedded module.

- Lembed generator tool (`src/lembed_tool.cpp`)
  - Small standalone generator that orchestrates the workflow:
    1. Calls `bin\limitly -bytecode <src>` to emit textual bytecode.
    2. Runs `python tools/goembed.py <bytecode> <name> src/lembed_generated` to produce C++ registration sources.
    3. Optionally calls `tools/make_embedded.bat` or `tools/make_embedded.sh` to build a new interpreter binary including the generated `src/lembed_generated.cpp`.
  - This tool intentionally avoids linking the full frontend/backend/VM; it uses the existing `limitly` binary to produce bytecode to prevent heavy linker dependencies.

- Helper to fix opcode names (`tools/fix_generated_opcodes.py`)
  - A helper that maps numeric or placeholder OP_XX tokens in a generated C++ file to the real `Opcode::<NAME>` enum identifiers when necessary. Used to avoid compile errors from malformed generator output.

- Build script updates
  - `build.bat` and `build.sh` were updated to build a small `bin\lembed.exe` / `bin/lembed` generator tool rather than compiling generated embeddeds into the main interpreter by default.
  - Added `tools/make_embedded.bat` and `tools/make_embedded.sh` which compile a standalone interpreter binary named `bin/limitly_<name>` that includes `src/lembed_generated.cpp`.

Expected outcomes
-----------------
- Developer workflow
  1. Build the main `limitly` interpreter and the `lembed` generator tool using the normal `build.bat` / `build.sh`.
  2. Run the generator to produce an embedded interpreter:
     - bin\lembed -embed-source examples/foo.lm foo -build
     - This will produce `src/lembed_generated.cpp` and then call `tools/make_embedded.bat foo` to produce `bin\limitly_foo.exe`.
  3. Running `bin\limitly_foo.exe` executes the embedded bytecode directly (the binary performs registration of the embedded bytecode at startup and dispatches to it, depending on runtime CLI behavior).

- Why this design
  - Keeping the generator small avoids linking the entire compiler stack into the generator binary and avoids unresolved linker dependencies for concurrency, scheduler, or VM internals.
  - Reusing the already-built `limitly` to produce textual bytecode keeps the generator simpler and more robust.

What failed and why
-------------------
- Early attempt: linking full frontend/backend into the `lembed` tool
  - Problem: The `lembed` tool originally tried to compile and link `Scanner`, `Parser`, and `BytecodeGenerator` directly. This pulled in large subsystems (Scheduler, ThreadPool, VM code) and produced numerous undefined references (vtable/linker errors) because the generator's linkline did not include certain object files or because of missing platform-specific concurrency implementations (e.g. IO completion ports). This made the `lembed` binary heavy and brittle.
  - Mitigation: We pivoted to an orchestration approach where `lembed` invokes the existing `limitly` CLI to produce bytecode instead of linking the whole compiler.

- Generator output format issues
  - Problem: A few generator runs produced invalid C++ tokens like `OP_90` in the generated file. These identifiers don't exist in the `Opcode` enum and caused compiler errors.
  - Mitigation: Added `tools/fix_generated_opcodes.py` and adjusted the generator to emit either valid enum names or explicit numeric casts to `Opcode`. We also added a check in `tools/make_embedded.*` to fail early when `src/lembed_generated.cpp` is missing.

- Build script pitfalls
  - Problem: Original attempts inserted conditional file references and exist-checks inline inside the g++ command which resulted in malformed argument lists and compiler errors.
  - Mitigation: Refactored `build.bat` to compile the `lembed` generator as a minimal binary (only `src/lembed_tool.cpp`, `src/lembed.cpp`, and `src/lembed_builtin.cpp` plus generated file when present). The embedded-executable builders are now separate helper scripts in `tools/`.

Current status / What was disabled
---------------------------------
- The main `build.bat` and `build.sh` no longer attempt to build interpreter binaries with arbitrary generated embeds by default.
  - The embedding path is handled by `bin\lembed.exe` (generator) and the `tools/make_embedded.*` scripts which explicitly include `src/lembed_generated.cpp` when present.
- This change effectively "disabled" automatic embedding into the main `limitly` build to avoid the earlier linker and generation failures. Developers must now explicitly create embedded interpreter binaries via the `lembed` tool (or run `tools/make_embedded.*` directly).

How to reproduce the intended workflow
-------------------------------------
1. Build the project (Windows example):

```powershell
cmd /c build.bat
```

2. Use `lembed` to produce an embedded interpreter from a source file:

```powershell
bin\lembed.exe -embed-source examples\myprog.lm myprog -build
```

3. Run the embedded interpreter:

```powershell
bin\limitly_myprog.exe
```

Notes and next steps
--------------------
- Improve generator robustness: make `tools/goembed.py` emit enum-qualified `Opcode::NAME` tokens consistently or use `static_cast<Opcode>(N)` to avoid name mismatches.
- Add unit tests for the generator and a smoke-test that builds a small embedded interpreter and runs it in CI.
- Consider providing an alternative internal API that produces bytecode directly (e.g., a small static library target that exposes BytecodeGenerator without pulling scheduler/concurrency pieces) so `lembed` can be compiled as a self-contained generator without invoking `limitly`.

Contact
-------
If you need edits, ask for an update to this document or for the generator script to be improved to guarantee valid generated C++ output.
