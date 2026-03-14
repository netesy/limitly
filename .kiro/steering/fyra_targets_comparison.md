# Fyra Backend Targets Comparison

## Available Targets in Fyra Subproject

The Fyra backend (`src/backend/fyra/src/codegen/target/`) provides the following target implementations:

### Platform-Architecture Combinations

#### Windows
- **Windows_x64.cpp** - x86-64 (x64) architecture
- **Windows_AArch64.cpp** - ARM64 architecture

#### Linux (SystemV ABI)
- **SystemV_x64.cpp** - x86-64 (x64) architecture (System V AMD64 ABI)
- **AArch64.cpp** - ARM64 architecture
- **RiscV64.cpp** - RISC-V 64-bit architecture

#### macOS
- **MacOS_x64.cpp** - x86-64 (x64) architecture
- **MacOS_AArch64.cpp** - ARM64 architecture (Apple Silicon)

#### WebAssembly
- **Wasm32.cpp** - WebAssembly 32-bit target

### Base Classes
- **X86_64Base.cpp** - Common x86-64 implementation base
- **TargetInfo.h** - Abstract base class for all targets
- **FusionCoordinator.cpp** - Instruction fusion optimization

## Our Implementation Mapping

### Platform Enum → Fyra Target Class

```
Platform::Windows + Architecture::X86_64     → Windows_x64
Platform::Windows + Architecture::AArch64    → Windows_AArch64
Platform::Linux + Architecture::X86_64       → SystemV_x64
Platform::Linux + Architecture::AArch64      → AArch64
Platform::Linux + Architecture::RISCV64      → RiscV64
Platform::MacOS + Architecture::X86_64       → MacOS_x64
Platform::MacOS + Architecture::AArch64      → MacOS_AArch64
Platform::WASM + Architecture::WASM32        → Wasm32
```

## Target Triple Generation

Our `get_target_triple()` function generates LLVM-style target triples:

```
Architecture-Vendor-OS-Environment

Examples:
- x86_64-pc-windows-gnu       (Windows x64)
- x86_64-unknown-linux-gnu    (Linux x64)
- aarch64-apple-darwin        (macOS ARM64)
- wasm32-unknown-wasm         (WebAssembly)
- riscv64-unknown-linux-gnu   (Linux RISC-V)
```

## Output Formats

### Native Targets (Windows, Linux, macOS)
- **ELF Format** - Used for Linux and macOS
- **PE Format** - Used for Windows (not yet implemented)
- **Assembly Output** - `.s` files when `-d` flag is used

### WebAssembly
- **WASM Binary** - `.wasm` files (default)
- **WAT Text** - `.wat` files when `-d` flag is used

## Optimization Levels

All targets support optimization levels:
- **O0** - No optimization (debug builds)
- **O1** - Basic optimization
- **O2** - Standard optimization (default)
- **O3** - Aggressive optimization

## Key Features by Target

### Windows Targets
- PE/COFF object format
- Microsoft x64 calling convention (Windows_x64)
- ARM64 calling convention (Windows_AArch64)

### Linux Targets
- ELF object format
- System V AMD64 ABI (SystemV_x64)
- ARM64 EABI (AArch64)
- RISC-V 64-bit ABI (RiscV64)

### macOS Targets
- Mach-O object format (via ELF wrapper)
- x86-64 calling convention (MacOS_x64)
- ARM64 calling convention (MacOS_AArch64)

### WebAssembly
- WASM binary format
- WASI system interface support
- Text format (WAT) for debugging

## Integration with Main CLI

The command-line interface now properly maps user-specified targets to Fyra backend targets:

```bash
# Windows x64 (default)
limitly build -target windows file.lm

# Linux x64
limitly build -target linux file.lm

# macOS ARM64
limitly build -target macos file.lm

# WebAssembly
limitly build -target wasm file.lm

# Dump intermediate files
limitly build -target windows -d file.lm    # Outputs .s file
limitly build -target wasm -d file.lm       # Outputs .wat file
```

## Future Enhancements

1. **PE Format Support** - Implement PE generation for Windows targets
2. **WASM Binary Generation** - Implement WASM binary output
3. **WAT Text Generation** - Implement WAT text format output
4. **Cross-Compilation** - Support building for different targets on any platform
5. **Optimization Passes** - Leverage Fyra's optimization infrastructure
