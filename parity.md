# Limitly / Fyra AOT Binary Size Analysis & GCC Parity Roadmap

## 1. Comparative Analysis: Hello World AOT Application

Below is a size comparison of a standard "Hello World" application compiled with Limitly's **Fyra AOT backend** vs **GCC (C)** and **G++ (C++)**.

### Source Code
- **Limitly (`hello.lm`)**:
  ```limitly
  fn main() {
      print("Hello, world!");
  }
  ```
- **C (`hello.c`)**:
  ```c
  #include <stdio.h>
  int main() {
      puts("Hello, world!");
      return 0;
  }
  ```
- **C++ (`hello.cpp`)**:
  ```cpp
  #include <iostream>
  int main() {
      std::cout << "Hello, world!" << std::endl;
      return 0;
  }
  ```

### Binary Metrics Comparison Table

| Application | Compiler / Backend | Options / Flags | Binary File Size | `.text` (Code) | `.data` (Data) | `.bss` (Uninit) | Total Memory Footprint |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `hello_lm` (Original) | Limitly (Fyra AOT) | Default (`-O2`) | **1,083,880 B (~1.08 MB)** | 18,702 B | **1,048,778 B** | 0 B | ~1,067,480 B |
| `hello_lm` (Phase 1 Implemented) | Limitly (Fyra AOT) | Default (`-O2`) | **35,376 B (~35.3 KB)** | 18,702 B | **202 B** | 1,048,576 B | ~1,067,480 B |
| `hello_c` | GCC 11.4 | `-O2` | **15,960 B (~16 KB)** | 1,370 B | 600 B | 8 B | 1,978 B |
| `hello_c_stripped` | GCC 11.4 | `-O2 -s` | **14,472 B (~14.4 KB)** | 1,370 B | 600 B | 8 B | 1,978 B |
| `hello_cpp` | G++ 11.4 | `-O2` | **16,408 B (~16.4 KB)** | 2,307 B | 648 B | 280 B | 3,235 B |
| `hello_cpp_stripped` | G++ 11.4 | `-O2 -s` | **14,472 B (~14.4 KB)** | 2,307 B | 648 B | 280 B | 3,235 B |

---

## 2. Root Cause Analysis: Why is Fyra's Binary Size Bigger?

The initial Limitly Fyra AOT executable was **~75x larger** on disk than a GCC-compiled C executable. Detailed ELF section analysis (`readelf -S` and `objdump`) revealed four primary causes for this size inflation:

### Cause 1: 1MB Static Heap Buffer Emitted into `.data` (`SHT_PROGBITS`) Instead of `.bss` (`SHT_NOBITS`) [RESOLVED IN PHASE 1]
- **Impact**: **+1,048,576 Bytes (~1.00 MB)**
- **Mechanism**:
  In `vendor/fyra/src/codegen/CodeGen.cpp`, when a program uses heap functionality, dynamic allocation emits a fixed 1MB allocation buffer (`__fyra_heap`).
  Previously, the 1MB buffer of zeroes was emitted into `rodataAssembler` using a 1,048,576-byte loop (`rodataAssembler->emitByte(0)`).
  This placed the 1MB zeroes array into the `.data` section as `SHT_PROGBITS`.
  An ELF section marked `SHT_PROGBITS` forces the ELF writer to write all 1,048,576 zero bytes directly into the binary file on disk.
  In Phase 1, `__fyra_heap` was moved to `.bss` marked `SHT_NOBITS`. It now takes **0 bytes on disk** and is allocated at runtime by the OS kernel loader, dropping binary size from **1,083,880 B** down to **35,376 B**.

### Cause 2: Section Alignment Padding (0x1000 / 4096 Bytes Per Section)
- **Impact**: **+12 KB - 16 KB**
- **Mechanism**:
  In `vendor/fyra/src/target/artifact/executable/elf.cpp` (`layoutSectionsForExecutable`), every loadable section (`.text`, `.rodata`, `.data`, `.bss`) aligns both its memory address (`vma`) AND its file offset (`fileOffset`) to `pageSize_` (4096 bytes / `0x1000`).
  This introduces thousands of bytes of zero-padding between sections on disk.

### Cause 3: Unstripped Debug Symbols and String Tables (`.symtab` & `.strtab`)
- **Impact**: **+10 KB - 15 KB**
- **Mechanism**:
  Fyra embeds a full `.symtab` symbol table and `.strtab` string table containing internal register symbols, runtime helper functions, and relocation targets.
  There is currently no symbol stripping mechanism (equivalent to `strip` or `gcc -s`) during final ELF binary generation.

### Cause 4: Monolithic Runtime Helper Inclusion (Lack of Function-Level DCE)
- **Impact**: **+15 KB - 20 KB**
- **Mechanism**:
  Fyra currently embeds standard built-in functions into the generated ELF binary's `.text` section regardless of whether they are referenced by `main()`.

---

## 3. Detailed Steps & Plan to Achieve Parity with GCC

To reduce Limitly Fyra AOT binary size from **35.3 KB** down to **~14 KB** (achieving 1:1 parity with GCC), execute the following technical plan:

### Phase 1: Eliminate the 1MB Data Payload (COMPLETED)
1. **Refactor `__fyra_heap` Emitting Logic in `vendor/fyra/src/codegen/CodeGen.cpp`**:
   - Separate `.data` (initialized data, PROGBITS) and `.bss` (uninitialized/zero data, NOBITS) sections in `CodeGen`.
   - Do not emit 1,048,576 physical `0` bytes into the byte stream for `__fyra_heap`.
   - Register `__fyra_heap` as a `.bss` section symbol with `size = 1048576`.
2. **Update ELF Generator `vendor/fyra/src/target/artifact/executable/elf.cpp`**:
   - Ensure `.bss` section header `sh_type` is set to `SHT_NOBITS` (0x8).
   - In `writeSectionData`, skip seeking and writing byte data for sections with `sh_type == SHT_NOBITS`.
   - Ensure program header `p_filesz` excludes the `.bss` size while `p_memsz` includes it.
   - **Result**: Binary file size dropped from **1,083,880 B** to **35,376 B (~35.3 KB)**.

### Phase 2: Optimize File Layout & Alignment (Target: ~20 KB)
1. **Differentiate Disk File Offset Alignment vs Virtual Memory Alignment**:
   - Virtual memory alignment must remain `0x1000` (4096 bytes) for page protection (`PF_R`, `PF_W`, `PF_X`).
   - File offset alignment (`fileOffset`) for adjacent sections inside the same ELF segment (or packed file layout) can be tightened to 8 or 16 bytes.
2. **Combine Read-Only Data (`.rodata`) into Code (`.text`) Segment**:
   - Merge string literals and rodata into the `.text` PT_LOAD segment or pack them continuously to eliminate page-size padding gaps on disk.

### Phase 3: Binary Stripping & Dead Code Elimination (Target: ~14 KB - GCC Parity)
1. **Implement Binary Stripping Support (`-s` / `--strip`)**:
   - Add a command-line flag `-s` / `--strip` to `limitly build`.
   - When stripping is enabled, omit `.symtab` and `.strtab` sections from the output ELF file, retaining only essential ELF headers.
2. **Implement Link-Time / CodeGen Dead Code Elimination (DCE)**:
   - Perform reachability analysis on the Fyra IR graph starting from `main()`.
   - Eliminate unused builtin functions and runtime helpers prior to binary assembly.
   - **Target Result**: Final stripped executable size **~14 KB - 15 KB** (100% parity with `gcc -O2 -s`).

---

## 4. Summary Roadmap Checklist

- [x] Phase 0: Baseline measurement & metrics logging (Completed)
- [x] Phase 1: Convert `__fyra_heap` to `.bss` / `SHT_NOBITS` (Completed: **35.3 KB**)
- [ ] Phase 2: Optimize ELF section packing & page alignment on disk (Target: ~20 KB)
- [ ] Phase 3: Add symbol stripping (`-s`) and dead code elimination (Target: ~14 KB)
