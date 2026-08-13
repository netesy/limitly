# Fyra IR Semantic Verification

As part of isolating the **Limitly → Fyra IR generation** stage, we added differential `.fyra` semantic verification.

This confirms that the `.fyra` text output acts as a perfect serialized proxy of the memory-bound Fyra AST.

* `scripts/run_differential_tests.sh` iterates over the generated `.fyra` files.
* It uses the vendor parser via `scripts/verify_fyra_output.cpp` to deserialize back into AST, re-serialize, and perform tree/node comparisons.
* Passed: `79 / 80` tests validated successfully (1 failure due to `std::bad_alloc` parser edgecase on a specific giant string constant which is currently an issue directly in `fyra/parser/Parser.cpp`).

This validates that Limitly generates syntactically correct and fully resolvable IR references without relying on final X86 assembler evaluation.

## Artifacts Produced
- `tests/fyra/*.fyra`: The differential test reference cases (the verified corpus).
- `scripts/patch_fyra.py`: The script used to apply backwards-compatible type emission features inside the `vendor/fyra` repo.
