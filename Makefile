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
	LIBS :=
endif

# =============================
# Build mode
# =============================
MODE ?= release

ifeq ($(MODE),debug)
	CXXFLAGS := -std=c++20 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -Isrc/backend/jit -Isrc/backend/fyra/include $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
	CFLAGS := -std=c99 -g -fPIC -I.
else
	CXXFLAGS := -std=c++20 -O3 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -Isrc/backend/jit -Isrc/backend/fyra/include $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
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
# Sources
# =============================
FRONT_SRCS := src/frontend/scanner.cpp src/frontend/parser.cpp  \
              src/frontend/cst.cpp src/frontend/cst/printer.cpp src/frontend/cst/utils.cpp \
              src/frontend/ast/builder.cpp src/frontend/ast/printer.cpp src/frontend/type_checker.cpp src/frontend/memory_checker.cpp \
              src/frontend/ast/optimizer.cpp 

BACK_SRCS :=  src/backend/jit/jit.cpp src/backend/fyra.cpp src/backend/fyra_ir_generator.cpp

FYRA_DIR := src/backend/fyra
FYRA_SRCS := $(wildcard $(FYRA_DIR)/src/ir/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/target/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/execgen/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/objectgen/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/debug/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/profiling/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/validation/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/transforms/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/parser/*.cpp)

FYRA_OBJS := $(patsubst src/backend/fyra/src/%.cpp,$(OBJ_DIR)/fyra/%.o,$(FYRA_SRCS))
FYRA_LIB := $(OBJ_DIR)/libfyra.a

REGISTER_SRCS := src/backend/vm/register.cpp

LIR_CORE_SRCS := src/lir/lir.cpp src/lir/lir_utils.cpp src/lir/functions.cpp \
                 src/lir/builtin_functions.cpp src/lir/lir_types.cpp src/lir/generator.cpp src/lir/function_registry.cpp

BACKEND_COMMON_SRCS := src/backend/symbol_table.cpp src/backend/value.cpp 

ERROR_SRCS := src/error/debugger.cpp

MAIN_SRCS := src/main.cpp $(BACKEND_COMMON_SRCS) $(BACK_SRCS) $(ERROR_SRCS) \
             $(FRONT_SRCS) $(REGISTER_SRCS) $(LIR_CORE_SRCS) 

TEST_SRCS := src/test_parser.cpp $(BACKEND_COMMON_SRCS) $(LIR_CORE_SRCS) $(ERROR_SRCS) \
             $(FRONT_SRCS)

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

$(OBJ_DIR)/fyra:
	@mkdir -p $@

# =============================
# Object compilation - C++ files
# =============================
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/fyra/%.o: src/backend/fyra/src/%.cpp | $(OBJ_DIR)/fyra
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
# Fyra library
# =============================
fyra: $(FYRA_LIB)

$(FYRA_LIB): $(FYRA_OBJS)
	@echo "Building fyra library: $@"
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	@echo "✅ Fyra library built: $@"

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

linux: $(BIN_DIR) $(MAIN_RSP) $(RUNTIME_LIB) $(FYRA_LIB)
	@echo "🔨 Linking limitly ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) @$(MAIN_RSP) $(RUNTIME_LIB) $(FYRA_LIB) -o $(BIN_DIR)/limitly$(EXE_EXT) $(LIBS) -lpthread
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