# Fyra Vendor Modifications

The following modifications were applied to `vendor/fyra` to ensure complete ELF/PE generation and AOT backend compatibility:

1. **Backwards-compatible Type Emission and Function Printing**:
   - `src/ir/Function.cpp`: Pre-pass naming for unnamed instructions and parameters during printing.
   - `src/ir/Instruction.cpp`: Added type printing checks for non-void typed instructions.
   - `src/ir/Module.cpp` and `include/ir/Module.h`: Added `print(std::ostream& os)` support for module string constant initialization and top-level IR serialization.

2. **Symbol Resolution in ELF Generator**:
   - `src/target/artifact/executable/elf.cpp`: Handled relocation symbol lookup for defined/local symbols and section labels cleanly without throwing unknown symbol relocation errors during ELF generation.
