# Makefile - Build Limit Language (Windows + Linux)

# =============================
# Platform detection
# =============================
ifeq ($(OS),Windows_NT)
	PLATFORM := windows
	EXE_EXT := .exe
	MSYS2_PATH := C:/msys64
	CXX := $(MSYS2_PATH)/mingw64/bin/g++.exe
	CC := $(MSYS2_PATH)/mingw64/bin/gcc.exe
	AR := $(MSYS2_PATH)/mingw64/bin/ar.exe
	LIBS := -lws2_32 -lgccjit
else
	PLATFORM := linux
	EXE_EXT :=
	CXX := g++
	CC := gcc
	AR := ar
	LIBS := -lgccjit
	LIBGCCJIT_PATH := $(shell find /usr -name libgccjit.so 2>/dev/null)
	ifneq ($(LIBGCCJIT_PATH),)
		LDFLAGS := -L$(shell dirname $(LIBGCCJIT_PATH))
	endif
endif

# =============================
# Build mode
# =============================
MODE ?= release

ifeq ($(MODE),debug)
	CXXFLAGS := -std=c++20 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -Isrc/backend/jit $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
	CFLAGS := -std=c99 -g -fPIC -I.
else
	CXXFLAGS := -std=c++20 -O3 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -Isrc/backend/jit $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
	CFLAGS := -std=c99 -O3 -fPIC -I.
endif

ifeq ($(PLATFORM),windows)
	LDFLAGS += -Wl,--stack,16777216
endif

# =============================
# Directories
# =============================
BIN_DIR := bin
OBJ_DIR := build/obj/$(MODE)
RSP_DIR := build/rsp

# =============================
# Runtime library configuration
# =============================
RUNTIME_DIR := src/runtime
RUNTIME_LIB := $(OBJ_DIR)/limitly_runtime.a
RUNTIME_SRCS := $(wildcard $(RUNTIME_DIR)/*.c)
RUNTIME_OBJS := $(patsubst $(RUNTIME_DIR)/%.c,$(OBJ_DIR)/runtime/%.o,$(RUNTIME_SRCS))

# =============================
# Sources (New LM:: namespace structure)
# =============================
FRONT_SRCS := src/lm/frontend/scanner.cpp src/lm/frontend/parser.cpp src/lm/debug/debugger.cpp \
              src/lm/frontend/cst/node.cpp src/lm/frontend/cst/printer.cpp src/lm/frontend/cst/utils.cpp \
              src/lm/frontend/ast_builder.cpp src/lm/frontend/type_checker.cpp src/lm/frontend/memory_checker.cpp \
              src/lm/frontend/ast_optimizer.cpp src/lm/lir/generator.cpp

BACK_SRCS := src/lm/backend/jit/backend.cpp src/lm/backend/jit/compiler.cpp

REGISTER_SRCS := src/lm/backend/vm/register.cpp

LIR_CORE_SRCS := src/lm/lir/instruction.cpp src/lm/lir/utils.cpp src/lm/lir/functions.cpp \
                 src/lm/lir/builtin_functions.cpp src/lm/lir/types.cpp

BACKEND_COMMON_SRCS := src/lm/backend/symbol_table.cpp src/lm/backend/value.cpp src/lm/backend/ast_printer.cpp

ERROR_SRCS := src/lm/error/formatter.cpp src/lm/error/code_generator.cpp \
              src/lm/error/hint_provider.cpp src/lm/error/source_formatter.cpp \
              src/lm/error/console_formatter.cpp src/lm/error/catalog.cpp

MAIN_SRCS := src/main.cpp $(BACKEND_COMMON_SRCS) $(BACK_SRCS) $(ERROR_SRCS) \
             $(FRONT_SRCS) $(REGISTER_SRCS) $(LIR_CORE_SRCS) src/lm/lir/function_registry.cpp

TEST_SRCS := src/test_parser.cpp $(BACKEND_COMMON_SRCS) $(LIR_CORE_SRCS) $(ERROR_SRCS) \
             $(FRONT_SRCS) src/lm/lir/function_registry.cpp

# =============================
# Objects and response files
# =============================
MAIN_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

MAIN_RSP := $(RSP_DIR)/build_main.rsp
TEST_RSP := $(RSP_DIR)/build_test.rsp

# =============================
# Phony targets
# =============================
.PHONY: all clean clear clean-lm check-deps windows linux release debug runtime

# =============================
# Default target
# =============================
all: check-deps $(PLATFORM)

# =============================
# Dependency check
# =============================
check-deps:
ifeq ($(PLATFORM),windows)
	@powershell -Command "if (-not (Test-Path '$(MSYS2_PATH)')) { Write-Error 'MSYS2 not found at $(MSYS2_PATH)'; exit 1 }"
	@powershell -Command "if (-not (Test-Path '$(CXX)')) { Write-Error 'g++ not found in MSYS2'; exit 1 }"
endif
	@echo "Dependencies OK for $(PLATFORM) in $(MODE) mode."

# =============================
# Directories
# =============================
$(OBJ_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@

$(RSP_DIR):
	@mkdir -p $@

$(OBJ_DIR)/runtime:
	@mkdir -p $@

# =============================
# Object compilation - C++ files
# =============================
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =============================
# Object compilation - Runtime C files
# =============================
$(OBJ_DIR)/runtime/%.o: $(RUNTIME_DIR)/%.c | $(OBJ_DIR)/runtime
	@echo "Compiling runtime: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# =============================
# Runtime library
# =============================
runtime: $(RUNTIME_LIB)

$(RUNTIME_LIB): $(RUNTIME_OBJS)
	@echo "Building runtime library: $@"
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	@echo "✅ Runtime library built: $@"

# =============================
# Response files generation
# =============================
$(MAIN_RSP): $(MAIN_OBJS) | $(RSP_DIR)
	@echo "Generating $(MAIN_RSP)..."
	@echo $(MAIN_OBJS) > $(MAIN_RSP)

$(TEST_RSP): $(TEST_OBJS) | $(RSP_DIR)
	@echo "Generating $(TEST_RSP)..."
	@echo $(TEST_OBJS) > $(TEST_RSP)

# =============================
# Build targets
# =============================
windows: $(BIN_DIR) $(MAIN_RSP) $(RUNTIME_LIB)
	@echo "🔨 Linking limitly.exe ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) @$(MAIN_RSP) $(RUNTIME_LIB) -o $(BIN_DIR)/limitly$(EXE_EXT) $(LIBS)
	@echo "✅ limitly.exe built."

linux: $(BIN_DIR) $(MAIN_RSP) $(RUNTIME_LIB)
	@echo "🔨 Linking limitly ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) @$(MAIN_RSP) $(RUNTIME_LIB) -o $(BIN_DIR)/limitly$(EXE_EXT) $(LIBS)
	@echo "✅ limitly built."

# =============================
# Build modes
# =============================
release:
	@$(MAKE) MODE=release all

debug:
	@$(MAKE) MODE=debug all

# =============================
# Clean
# =============================
clean:
ifeq ($(PLATFORM),windows)
	@powershell -Command "if (Test-Path 'build') { Remove-Item -Recurse -Force 'build' }"
	@powershell -Command "if (Test-Path 'bin') { Remove-Item -Recurse -Force 'bin' }"
else
	rm -rf build bin
endif
	@echo "🧹 Cleaned build artifacts."

# Clear generated text files
clear:
ifeq ($(PLATFORM),windows)
	@echo "🧹 Cleaning generated .txt files..."
	@powershell -Command "Get-ChildItem -Recurse -Include *.ast.txt,*.bytecode.txt,*.cst.txt,*.tokens.txt | Remove-Item -Force -ErrorAction SilentlyContinue"
else
	@echo "🧹 Cleaning generated .txt files..."
	@find . -name "*.ast.txt" -type f -delete 2>/dev/null || true
	@find . -name "*.bytecode.txt" -type f -delete 2>/dev/null || true
	@find . -name "*.cst.txt" -type f -delete 2>/dev/null || true
	@find . -name "*.tokens.txt" -type f -delete 2>/dev/null || true
endif
	@echo "✅ Generated files cleaned."

# Clean .lm files from root folder only
clean-lm:
ifeq ($(PLATFORM),windows)
	@echo "🧹 Cleaning .lm files from root folder..."
	@powershell -Command "Get-ChildItem -Path . -Filter *.lm -File | Remove-Item -Force -ErrorAction SilentlyContinue"
else
	@echo "🧹 Cleaning .lm files from root folder..."
	@find . -maxdepth 1 -name "*.lm" -type f -delete 2>/dev/null || true
endif
	@echo "✅ Root .lm files cleaned (std/ and tests/ preserved)."

# =============================
# JIT Test Target
# =============================
test-jit: $(BIN_DIR) $(RUNTIME_LIB)
	@echo "🔨 Building JIT test..."
	$(CXX) $(CXXFLAGS) -I. test_jit_operations.cpp src/backend/jit/jit.cpp src/lir/lir.cpp \
		src/lir/lir_utils.cpp $(RUNTIME_LIB) -o $(BIN_DIR)/test_jit$(EXE_EXT) $(LIBS)
	@echo "✅ JIT test built."
	@echo "🧪 Running JIT test..."
	$(BIN_DIR)/test_jit$(EXE_EXT)

# =============================
# Parser Test Target
# =============================
parser: $(BIN_DIR) $(TEST_RSP)
	@echo "🔨 Building test_parser$(EXE_EXT)...."
	$(CXX) $(CXXFLAGS) @$(TEST_RSP) -o $(BIN_DIR)/test_parser$(EXE_EXT) $(LIBS)
	@echo "✅ $(BIN_DIR)/test_parser$(EXE_EXT) built."