# Vendored Fyra directory

This directory is now vendored directly in the repository instead of being a Git submodule.

## Contents
- `include/fyra_embed.h`: embedded C API used by Limitly backend.
- `src/fyra_embed.c`: current shim implementation used to build `libfyra.a` during local builds.

## Replacing with real Fyra
To switch from shim to full Fyra:
1. Copy full Fyra sources into this directory.
2. Keep a compatible `fyra_compile_ir_to_file(...)` symbol (or adapt `src/backend/fyra.cpp`).
3. Update build rules if Fyra requires additional objects/libraries.
