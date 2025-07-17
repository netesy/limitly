# Technology Stack

## Core Technologies
- **Language**: C++17
- **Build Systems**: CMake, Zig, Batch scripts
- **Architecture**: Compiler frontend + bytecode VM backend

## Build System Usage

### Primary Build Methods
1. **CMake** (recommended for cross-platform)
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

2. **Zig Build** (alternative build system)
   ```bash
   zig build
   zig build run
   zig build test-parser
   ```

3. **Windows Batch** (MSYS2/MinGW64)
   ```cmd
   build.bat
   ```

### Build Outputs
- `limitly.exe` / `limitly` - Main language interpreter
- `test_parser.exe` / `test_parser` - Parser testing utility

## Common Commands

### Running the Language
```bash
# Execute source file
./limitly sample.lm

# Print AST
./limitly -ast sample.lm

# Print tokens
./limitly -tokens sample.lm

# Print bytecode
./limitly -bytecode sample.lm

# Start REPL
./limitly -repl
```

### Development Commands
```bash
# Test parser
./test_parser sample.lm

# CMake custom targets
make run_limitly
make run_test_parser
```

## Code Standards
- C++17 standard compliance
- Header guards for all .hh files
- Namespace organization (AST, frontend, backend)
- RAII for memory management
- Smart pointers (std::shared_ptr, std::unique_ptr)
- STL containers and algorithms