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
	LIBS := -lws2_32
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
	CXXFLAGS := -std=c++20 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -Ivendor/fyra/include -Ivendor/fyra/src $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
	CFLAGS := -std=c99 -g -fPIC -I.
else
	CXXFLAGS := -std=c++20 -O3 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -Ivendor/fyra/include -Ivendor/fyra/src $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
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
FRONT_SRCS := src/frontend/scanner.cpp src/frontend/parser.cpp \
              src/frontend/parser/statements.cpp src/frontend/parser/expressions.cpp \
              src/frontend/parser/types.cpp src/frontend/parser/patterns.cpp \
              src/frontend/cst.cpp src/frontend/cst/printer.cpp src/frontend/cst/utils.cpp \
              src/frontend/ast/builder.cpp src/frontend/ast/printer.cpp src/frontend/type_checker.cpp src/frontend/type_checker_factory.cpp src/frontend/memory_checker.cpp \
              src/frontend/ast/optimizer.cpp src/frontend/module_manager.cpp

BACK_SRCS := src/backend/fyra/fyra.cpp src/backend/fyra/fyra_ir_generator.cpp src/backend/fyra/builder.cpp src/backend/fyra/fyra_builtin_functions.cpp

FYRA_DIR := vendor/fyra
FYRA_SRCS := $(wildcard $(FYRA_DIR)/src/ir/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/debug/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/target/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/execgen/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/objectgen/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/profiling/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/codegen/validation/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/transforms/*.cpp) \
             $(wildcard $(FYRA_DIR)/src/parser/*.cpp)

FYRA_OBJS := $(patsubst vendor/fyra/src/%.cpp,$(OBJ_DIR)/fyra/%.o,$(FYRA_SRCS))
FYRA_LIB := $(OBJ_DIR)/libfyra.a

# =============================
# Lyra Package Manager
# =============================
LYRA_DIR := vendor/lyra
LYRA_SRCS := $(wildcard $(LYRA_DIR)/src/*.cpp)
LYRA_OBJS := $(patsubst $(LYRA_DIR)/src/%.cpp,$(OBJ_DIR)/lyra/%.o,$(LYRA_SRCS))
LYRA_BIN := $(BIN_DIR)/lyra$(EXE_EXT)

REGISTER_SRCS := src/backend/vm/register.cpp

LIR_CORE_SRCS := src/lir/lir.cpp src/lir/lir_utils.cpp src/lir/functions.cpp \
                 src/lir/builtin_functions.cpp src/lir/lir_types.cpp src/lir/generator.cpp \
                 src/lir/generator/core.cpp src/lir/generator/statements.cpp src/lir/generator/expressions.cpp \
                 src/lir/generator/signatures.cpp src/lir/generator/oop.cpp src/lir/generator/concurrency.cpp \
                 src/lir/generator/modules.cpp src/lir/function_registry.cpp \
                 src/lir/optimizer.cpp src/lir/metrics.cpp src/lir/serializer.cpp

BACKEND_COMMON_SRCS := src/backend/symbol_table.cpp src/backend/value.cpp 

ERROR_SRCS := src/error/debugger.cpp

LIB_LIMITLY_SRCS := src/limitly.cpp src/formatter.cpp src/lsp.cpp $(BACKEND_COMMON_SRCS) $(BACK_SRCS) $(ERROR_SRCS) \
             $(FRONT_SRCS) $(REGISTER_SRCS) $(LIR_CORE_SRCS)

MAIN_SRCS := src/main.cpp

TEST_SRCS := src/test_parser.cpp $(BACKEND_COMMON_SRCS) $(LIR_CORE_SRCS) $(ERROR_SRCS) \
             $(FRONT_SRCS)

# =============================
# Objects and response files
# =============================
LIB_LIMITLY_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(LIB_LIMITLY_SRCS))
MAIN_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

MAIN_RSP := $(RSP_DIR)/build_main.rsp
TEST_RSP := $(RSP_DIR)/build_test.rsp

# =============================
# Phony targets
# =============================
.PHONY: all clean clear clean-lm check-deps windows linux release debug runtime tests aot-tests

# =============================
# Default target
# =============================
all: check-deps liblimitly $(PLATFORM)

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

# Exclude src/backend/fyra from general rule - they're handled separately
$(OBJ_DIR)/src/backend/fyra/%.o: src/backend/fyra/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/fyra/%.o: vendor/fyra/src/%.cpp | $(OBJ_DIR)
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
# Fyra library configuration
# =============================
FYRA_DIR := src/backend/fyra
FYRA_LIB := $(OBJ_DIR)/libfyra.a

# Build Fyra using Makefile (excluding problematic debug files)
$(FYRA_LIB): $(FYRA_OBJS)
	@echo "🔨 Building Fyra library with Makefile..."
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	@echo "✅ Fyra library built: $@"

# =============================
# Lyra Package Manager
# =============================
$(LYRA_BIN): $(LYRA_OBJS) liblimitly | $(BIN_DIR)
	@echo "🔨 Building Lyra package manager..."
	$(CXX) -std=c++20 -Wall -Wextra -I$(LYRA_DIR)/include -I. $(LYRA_OBJS) $(OBJ_DIR)/libLimitly.a $(RUNTIME_LIB) $(FYRA_LIB) -o $@ -lpthread
	@echo "✅ Lyra built: $@"

# Lyra object compilation
$(OBJ_DIR)/lyra/%.o: $(LYRA_DIR)/src/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) -std=c++17 -Wall -Wextra -I$(LYRA_DIR)/include -c $< -o $@

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
liblimitly: $(OBJ_DIR)/libLimitly.a

$(OBJ_DIR)/libLimitly.a: $(LIB_LIMITLY_OBJS) $(RUNTIME_LIB) $(FYRA_LIB)
	@echo "🔨 Building libLimitly.a ..."
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $(LIB_LIMITLY_OBJS)

windows: $(BIN_DIR) $(MAIN_RSP) liblimitly $(LYRA_BIN)
	@echo "🔨 Linking limitly.exe ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) @$(MAIN_RSP) $(OBJ_DIR)/libLimitly.a $(RUNTIME_LIB) $(FYRA_LIB) -o $(BIN_DIR)/limitly$(EXE_EXT) $(LIBS)
	@echo "✅ limitly.exe built."

linux: $(BIN_DIR) $(MAIN_RSP) liblimitly $(LYRA_BIN)
	@echo "🔨 Linking limitly ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) @$(MAIN_RSP) $(OBJ_DIR)/libLimitly.a $(RUNTIME_LIB) $(FYRA_LIB) -o $(BIN_DIR)/limitly$(EXE_EXT) $(LIBS) -lpthread
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
	@powershell -Command "if (Test-Path '$(FYRA_DIR)/build') { Remove-Item -Recurse -Force '$(FYRA_DIR)/build' }"
else
	rm -rf build bin $(FYRA_DIR)/build
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
# Parser Test Target
# =============================
parser: $(BIN_DIR) $(TEST_RSP)
	@echo "🔨 Building test_parser$(EXE_EXT)...."
	$(CXX) $(CXXFLAGS) @$(TEST_RSP) -o $(BIN_DIR)/test_parser$(EXE_EXT) $(LIBS)
	@echo "✅ $(BIN_DIR)/test_parser$(EXE_EXT) built."

# =============================
# Test Target
# =============================
tests: $(PLATFORM)
	@echo "Running project formatting test..."
	./bin/lyra format
	@echo "========================================"
	@echo "Running Limit Language Test Suite"
	@echo "========================================"
	@echo
	@FAILED=0; \
	PASSED=0; \
	TOTAL=0; \
	run_test() { \
		TOTAL=$$((TOTAL + 1)); \
		echo "Running $$1..."; \
		if [ "$(PLATFORM)" = "windows" ]; then \
			TEMP_FILE=$$(powershell -Command "Get-Content -Path 'env:TEMP'")/limitly_test_output_$$(powershell -Command "Get-Random").txt; \
			./bin/limitly.exe "$$1" > "$$TEMP_FILE" 2>&1; \
			if grep -q -i -E "segmentation fault|segfault" "$$TEMP_FILE"; then \
				echo "  FAIL: $$1 (segmentation fault detected in output)"; \
				echo "  Output:"; \
				cat "$$TEMP_FILE"; \
				FAILED=$$((FAILED + 1)); \
			elif grep -q -E "error\\[E|Error:|RuntimeError|SemanticError|BytecodeError" "$$TEMP_FILE"; then \
				echo "  FAIL: $$1 (contains errors)"; \
				echo "  Error output:"; \
				grep -E "error\\[E|Error:|RuntimeError|SemanticError|BytecodeError" "$$TEMP_FILE"; \
				FAILED=$$((FAILED + 1)); \
			else \
				echo "  PASS: $$1"; \
				PASSED=$$((PASSED + 1)); \
			fi; \
			rm "$$TEMP_FILE"; \
		else \
			TEMP_FILE=$$(mktemp); \
			./bin/limitly "$$1" > "$$TEMP_FILE" 2>&1; \
			if grep -q -E "segmentation fault|segfault" "$$TEMP_FILE"; then \
				echo "  FAIL: $$1 (segmentation fault detected in output)"; \
				echo "  Output:"; \
				cat "$$TEMP_FILE"; \
				FAILED=$$((FAILED + 1)); \
			elif grep -q -E "error\\[E|Error:|RuntimeError|SemanticError|BytecodeError" "$$TEMP_FILE"; then \
				echo "  FAIL: $$1 (contains errors)"; \
				echo "  Error output:"; \
				grep -E "error\\[E|Error:|RuntimeError|SemanticError|BytecodeError" "$$TEMP_FILE"; \
				FAILED=$$((FAILED + 1)); \
			else \
				echo "  PASS: $$1"; \
				PASSED=$$((PASSED + 1)); \
			fi; \
			rm "$$TEMP_FILE"; \
		fi; \
	}; \
	run_test_allow_semantic() { \
		run_test "$$1"; \
	}; \
	echo "=== BASIC TESTS ==="; \
	run_test "tests/basic/variables.lm"; \
	run_test "tests/basic/literals.lm"; \
	run_test "tests/basic/control_flow.lm"; \
	run_test "tests/basic/print_statements.lm"; \
	if [ "$(PLATFORM)" = "windows" ]; then run_test "tests/basic/list_dict_tuple.lm"; fi; \
	echo; \
	echo "=== EXPRESSION TESTS ==="; \
	run_test "tests/expressions/arithmetic.lm"; \
	run_test "tests/expressions/logical.lm"; \
	run_test "tests/expressions/ranges.lm"; \
	if [ "$(PLATFORM)" = "windows" ]; then \
		run_test "tests/expressions/scientific_notation.lm"; \
		run_test "tests/expressions/large_literals.lm"; \
	fi; \
	echo; \
	echo "=== STRING TESTS ==="; \
	run_test "tests/strings/interpolation.lm"; \
	run_test "tests/strings/operations.lm"; \
	echo; \
	echo "=== LOOP TESTS ==="; \
	run_test "tests/loops/for_loops.lm"; \
	run_test "tests/loops/iter_loops.lm"; \
	run_test "tests/loops/while_loops.lm"; \
	echo; \
	echo "=== FUNCTION TESTS ==="; \
	run_test "tests/functions/basic.lm"; \
	run_test "tests/functions/advanced.lm"; \
	run_test "tests/functions/closures.lm"; \
	run_test_allow_semantic "tests/functions/first_class.lm"; \
	echo; \
	echo "=== TYPE TESTS ==="; \
	run_test "tests/types/basic.lm"; \
	run_test "tests/types/unions.lm"; \
	run_test "tests/types/options.lm"; \
	run_test "tests/types/advanced.lm"; \
	run_test "tests/types/enums.lm"; \
	run_test "tests/types/refined_types.lm"; \
	echo; \
	echo "=== MODULE TESTS ==="; \
	run_test "tests/modules/basic_import_test.lm"; \
	if [ "$(PLATFORM)" = "linux" ]; then run_test "tests/modules/comprehensive_module_test.lm"; fi; \
	run_test "tests/modules/show_filter_test.lm"; \
	run_test "tests/modules/hide_filter_test.lm"; \
	run_test "tests/modules/module_caching_test.lm"; \
	run_test "tests/modules/function_params_test.lm"; \
	run_test "tests/modules/alias_import_test.lm"; \
	run_test "tests/modules/multiple_imports_test.lm"; \
	echo; \
	echo "=== OOP TESTS ==="; \
	run_test "tests/oop/frame_declaration.lm"; \
	run_test "tests/oop/traits_dynamic.lm"; \
	run_test "tests/oop/traits_inheritance.lm"; \
	run_test "tests/oop/visibility_test.lm"; \
	if [ "$(PLATFORM)" = "windows" ]; then run_test_allow_semantic "tests/oop/composition_test.lm"; else run_test_allow_semantic "tests/oop/composition_test.lm"; fi; \
	echo; \
	echo "=== CONCURRENCY TESTS ==="; \
	run_test "tests/concurrency/parallel_blocks.lm"; \
	run_test "tests/concurrency/concurrent_blocks.lm"; \
	echo; \
	echo "========================================"; \
	echo "Test Results:"; \
	echo "  PASSED: $$PASSED"; \
	echo "  FAILED: $$FAILED"; \
	echo "  TOTAL:  $$TOTAL"; \
	echo "========================================"; \
	if [ $$FAILED -gt 0 ]; then \
		echo "Some tests failed!"; \
		exit 1; \
	else \
		echo "All tests passed!"; \
		exit 0; \
	fi

# =============================
# AOT Test Target
# =============================
aot-tests: $(PLATFORM)
	@echo "========================================"
	@echo "Running Limit AOT Test Suite (Fyra Backend)"
	@echo "========================================"
	@echo
	@FAILED=0; \
	PASSED=0; \
	TOTAL=0; \
	run_aot_test() { \
		TOTAL=$$((TOTAL + 1)); \
		SOURCE_FILE=$$1; \
		echo "Running AOT Test: $$SOURCE_FILE..."; \
		if [ "$(PLATFORM)" = "windows" ]; then \
			EXE_FILE="$${SOURCE_FILE%.lm}.exe"; \
		else \
			EXE_FILE="$${SOURCE_FILE%.lm}"; \
		fi; \
		rm -f "$$EXE_FILE"; \
		if [ "$(PLATFORM)" = "windows" ]; then \
			./bin/limitly.exe build windows x86_64 2 "$$SOURCE_FILE"; \
		else \
			./bin/limitly build linux x86_64 2 "$$SOURCE_FILE"; \
		fi; \
		BUILD_STATUS=$$?; \
		if [ $$BUILD_STATUS -ne 0 ]; then \
			echo "  FAIL: $$SOURCE_FILE (AOT compilation failed)"; \
			FAILED=$$((FAILED + 1)); \
			return; \
		fi; \
		if [ ! -f "$$EXE_FILE" ]; then \
			echo "  FAIL: $$SOURCE_FILE (Executable not produced)"; \
			FAILED=$$((FAILED + 1)); \
			return; \
		fi; \
		TEMP_FILE=$$(mktemp); \
		if [ "$(PLATFORM)" = "windows" ]; then \
			chmod +x "$$EXE_FILE"; \
			powershell -Command "& '$(PWD)/$$EXE_FILE'" > "$$TEMP_FILE" 2>&1; \
		else \
			chmod +x "$$EXE_FILE"; \
			./"$$EXE_FILE" > "$$TEMP_FILE" 2>&1; \
		fi; \
		RUN_STATUS=$$?; \
		if [ $$RUN_STATUS -ne 0 ]; then \
			echo "  FAIL: $$SOURCE_FILE (Runtime crash with status $$RUN_STATUS)"; \
			echo "  Output:"; \
			cat "$$TEMP_FILE"; \
			FAILED=$$((FAILED + 1)); \
		else \
			echo "  PASS: $$SOURCE_FILE"; \
			PASSED=$$((PASSED + 1)); \
		fi; \
		rm "$$TEMP_FILE"; \
		rm "$$EXE_FILE"; \
	}; \
	echo "=== BASIC AOT TESTS ==="; \
	run_aot_test "tests/basic/variables.lm"; \
	run_aot_test "tests/basic/literals.lm"; \
	run_aot_test "tests/basic/control_flow.lm"; \
	run_aot_test "tests/basic/print_statements.lm"; \
	echo; \
	echo "=== EXPRESSION AOT TESTS ==="; \
	run_aot_test "tests/expressions/arithmetic.lm"; \
	run_aot_test "tests/expressions/logical.lm"; \
	echo; \
	echo "=== LOOP AOT TESTS ==="; \
	run_aot_test "tests/loops/for_loops.lm"; \
	run_aot_test "tests/loops/while_loops.lm"; \
	echo; \
	echo "=== FUNCTION AOT TESTS ==="; \
	run_aot_test "tests/functions/basic.lm"; \
	echo; \
	echo "========================================"; \
	echo "AOT Test Results:"; \
	echo "  PASSED: $$PASSED"; \
	echo "  FAILED: $$FAILED"; \
	echo "  TOTAL:  $$TOTAL"; \
	echo "========================================"; \
	if [ $$FAILED -gt 0 ]; then \
		echo "Some AOT tests failed!"; \
		exit 1; \
	else \
		echo "All AOT tests passed!"; \
		exit 0; \
	fi
