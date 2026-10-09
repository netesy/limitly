# Makefile - Build Lymar Language (Windows + Linux)

# =============================
# Platform detection
# =============================
ifeq ($(OS),Windows_NT)
	PLATFORM := windows
	EXE_EXT := .exe
	SO_EXT := .dll
	A_EXT := .lib
	MSYS2_PATH := C:/msys64
	CXX := $(MSYS2_PATH)/mingw64/bin/g++.exe
	CC := $(MSYS2_PATH)/mingw64/bin/gcc.exe
	AR := $(MSYS2_PATH)/mingw64/bin/ar.exe
	LIBS := -lws2_32 -lffi -lgdi32 -luser32 -lshell32
	STB_IMAGE_LIB := bin/libstb_image.dll
	STB_SHARED_FLAGS := -shared -static -static-libgcc
	LYMAR_SSL_LIB := bin/liblymar_ssl.dll
	SSL_SHARED_FLAGS := -shared -O2 -I $(MSYS2_PATH)/mingw64/include -L $(MSYS2_PATH)/mingw64/lib
	SSL_LIBS := -lssl -lcrypto -lz -lregex -lcrypt32 -lws2_32
else ifeq ($(shell uname),Darwin)
	PLATFORM := linux
	EXE_EXT :=
	SO_EXT := .dylib
	A_EXT := .a
	CXX := g++
	CC := gcc
	AR := ar
	LIBS := -lffi -ldl
	STB_IMAGE_LIB := bin/libstb_image.dylib
	STB_SHARED_FLAGS := -shared -fPIC
	LYMAR_SSL_LIB := bin/liblymar_ssl.dylib
	SSL_SHARED_FLAGS := -shared -fPIC -O2
	SSL_LIBS := -lssl -lcrypto -lz
else
	PLATFORM := linux
	EXE_EXT :=
	SO_EXT := .so
	A_EXT := .a
	CXX := g++
	CC := gcc
	AR := ar
	LIBS := -lffi -ldl
	STB_IMAGE_LIB := bin/libstb_image.so
	STB_SHARED_FLAGS := -shared -fPIC
	LYMAR_SSL_LIB := bin/liblymar_ssl.so
	SSL_SHARED_FLAGS := -shared -fPIC -O2
	SSL_LIBS := -lssl -lcrypto -lz
endif

# =============================
# Build mode
# =============================
MODE ?= release

ifeq ($(MODE),debug)
	CXXFLAGS := -std=c++20 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -Isrc -Ivendor/sokol -Ivendor/stb -Ivendor/lyra/include $(if $(wildcard vendor/fyra/include/ir/Module.h),-DFYRA_AVAILABLE -Ivendor/fyra/include -Ivendor/fyra/src) $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
	CFLAGS := -std=c99 -g -fPIC -I. -Isrc -Ivendor/sokol -Ivendor/stb
else
	CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -Isrc -Ivendor/sokol -Ivendor/stb -Ivendor/lyra/include $(if $(wildcard vendor/fyra/include/ir/Module.h),-DFYRA_AVAILABLE -Ivendor/fyra/include -Ivendor/fyra/src) $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
	CFLAGS := -std=c99 -O2 -fPIC -I. -Isrc -Ivendor/sokol -Ivendor/stb
endif

ifeq ($(PLATFORM),windows)
	LDFLAGS += -Wl,--stack,16777216
endif

# Keep incremental installations correct when C++ headers change.
CXXFLAGS += -MMD -MP
ifneq ($(SANITIZERS),)
CXXFLAGS += -O1 -g -fno-omit-frame-pointer -fsanitize=$(SANITIZERS)
CFLAGS += -O1 -g -fno-omit-frame-pointer -fsanitize=$(SANITIZERS)
LDFLAGS += -fsanitize=$(SANITIZERS)
endif

# =============================
# Directories
# =============================
BIN_DIR := bin
OBJ_DIR := build/obj/$(MODE)
RSP_DIR := build/rsp

# =============================
# Precompilation configuration
# =============================
PRECOMPILE_MODULES ?= std.font std.ui

# Helper to find all precompilable modules (directories in std/ containing index.lm)
ALL_PRECOMPILE_MODULES := $(patsubst std/%/,std.%,$(dir $(wildcard std/*/index.lm)))

# =============================
# Sources
# =============================
FRONT_SRCS := src/frontend/scanner.cpp src/frontend/parser.cpp \
              src/frontend/parser/statements.cpp src/frontend/parser/expressions.cpp \
              src/frontend/parser/types.cpp src/frontend/parser/patterns.cpp \
              src/frontend/cst.cpp src/frontend/cst/printer.cpp src/frontend/cst/utils.cpp \
              src/frontend/ast/printer.cpp src/frontend/type_checker/core.cpp src/frontend/type_checker/expressions.cpp src/frontend/type_checker/statements.cpp src/frontend/type_checker/declarations.cpp src/frontend/type_checker/types.cpp src/frontend/type_checker/patterns.cpp src/frontend/type_checker/utils.cpp src/frontend/type_checker_factory.cpp src/frontend/memory_checker.cpp src/memory/ownership.cpp src/frontend/constraint_engine.cpp src/frontend/module_graph.cpp src/frontend/declaration_resolver.cpp \
              src/frontend/ast/optimizer.cpp src/frontend/module_manager.cpp

# Recursive wildcard function for pure GNU Make file discovery
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

BACK_SRCS := $(if $(wildcard vendor/fyra/include/ir/Module.h),src/backend/fyra/fyra.cpp src/backend/fyra/fyra_ir_generator.cpp src/backend/fyra/builder.cpp src/backend/fyra/fyra_builtin_functions.cpp src/backend/fyra/capability_mapper.cpp src/backend/fyra/region_lowering.cpp src/backend/fyra/runtime_linker.cpp,)

FYRA_DIR := vendor/fyra
FYRA_SRCS := $(if $(wildcard $(FYRA_DIR)/include/ir/Module.h),\
             $(call rwildcard,$(FYRA_DIR)/src,*.cpp),)

FYRA_OBJS := $(patsubst $(FYRA_DIR)/src/%.cpp,$(OBJ_DIR)/fyra/%.o,$(FYRA_SRCS))
FYRA_LIB := $(OBJ_DIR)/libfyra.a

# =============================
# Lyra Package Manager Library
# =============================
LYRA_DIR := vendor/lyra
LYRA_ALL_SRCS := $(if $(wildcard $(LYRA_DIR)/src),\
                 $(call rwildcard,$(LYRA_DIR)/src,*.cpp),)
LYRA_LIB_SRCS := $(filter-out $(LYRA_DIR)/src/main.cpp,$(LYRA_ALL_SRCS))
LYRA_LIB_OBJS := $(patsubst $(LYRA_DIR)/src/%.cpp,$(OBJ_DIR)/lyra/%.o,$(LYRA_LIB_SRCS))
LYRA_LIB := $(OBJ_DIR)/liblyra.a
LYRA_BIN := $(BIN_DIR)/lyra$(EXE_EXT)

REGISTER_SRCS := src/backend/native/abi.cpp src/backend/native/emitter.cpp src/backend/vm/resource_manager.cpp src/runtime/sokol/sokol_app_runtime.cpp src/runtime/lymarrt/lymarrt.cpp src/backend/vm/register.cpp src/backend/vm/ops/arithmetic.cpp src/backend/vm/ops/comparison.cpp src/backend/vm/ops/collections.cpp src/backend/vm/ops/frames.cpp src/backend/vm/ops/control_flow.cpp src/backend/vm/ops/io.cpp src/backend/vm/ops/bitwise.cpp src/backend/vm/ops/concurrency.cpp src/backend/vm/ops/modules.cpp src/backend/vm/ops/objects.cpp src/backend/vm/ops/vm_strings.cpp src/backend/vm/ops/vm_calls.cpp src/backend/vm/ops/vm_cast.cpp src/backend/vm/ops/memory.cpp src/backend/vm/ops/construction.cpp src/backend/vm/ops/marshal.cpp src/backend/vm/ops/ffi.cpp src/backend/vm/vm_dict.cpp src/backend/vm/vm_image.cpp src/backend/vm/vm_list.cpp src/backend/vm/vm_runtime.cpp src/backend/vm/vm_string.cpp src/backend/vm/vm_tuple.cpp src/backend/vm/vm_value.cpp

LIR_CORE_SRCS := src/lir/lir.cpp src/lir/lir_utils.cpp src/lir/functions.cpp \
                 src/lir/builtin_functions.cpp src/lir/intrinsic_registry.cpp src/lir/verifier.cpp src/lir/lir_types.cpp src/lir/generator.cpp \
                 src/lir/generator/core.cpp src/lir/generator/statements.cpp src/lir/generator/expressions.cpp \
                 src/lir/generator/signatures.cpp src/lir/generator/oop.cpp src/lir/generator/concurrency.cpp \
                 src/lir/generator/modules.cpp src/lir/function_registry.cpp \
                 src/lir/analysis.cpp src/lir/optimizer.cpp src/lir/algebraic_simplifier.cpp src/lir/metrics.cpp src/lir/serializer.cpp

BACKEND_COMMON_SRCS := src/backend/symbol_table.cpp src/frontend/value.cpp src/backend/utf8.cpp 

ERROR_SRCS := src/error/debugger.cpp

LIB_LYMAR_SRCS := src/lymar.cpp src/formatter.cpp src/lsp.cpp $(BACKEND_COMMON_SRCS) $(BACK_SRCS) $(ERROR_SRCS) \
             $(FRONT_SRCS) $(REGISTER_SRCS) $(LIR_CORE_SRCS)

MAIN_SRCS := src/main.cpp

TEST_SRCS := src/test_parser.cpp $(BACKEND_COMMON_SRCS) $(LIR_CORE_SRCS) $(ERROR_SRCS) \
             $(FRONT_SRCS)

# LIR round-trip test (C17)
LIR_TEST_SRCS := tests/lir/test_round_trip.cpp
LIR_TEST_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(LIR_TEST_SRCS))

# =============================
# Objects and response files
# =============================
LIB_LYMAR_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(LIB_LYMAR_SRCS)) $(FYRA_OBJS)
MAIN_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

MAIN_RSP := $(RSP_DIR)/build_main.rsp
TEST_RSP := $(RSP_DIR)/build_test.rsp

# =============================
# Phony targets
# =============================
.PHONY: all clean clear clean-lm check-deps windows linux release debug runtime tests aot-tests stb-image stb-image-test precompile precompile-all

# =============================
# Default target
# =============================
all: check-deps liblymar $(PLATFORM) stb-image

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

# =============================
# Object compilation - C++ files
# =============================
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Exclude src/backend/fyra from general rule
$(OBJ_DIR)/src/backend/fyra/%.o: src/backend/fyra/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) --param ggc-min-expand=20 --param ggc-min-heapsize=32768 -c $< -o $@

$(OBJ_DIR)/fyra/%.o: vendor/fyra/src/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =============================
# Fyra library configuration
# =============================
FYRA_DIR := vendor/fyra
FYRA_LIB := $(OBJ_DIR)/libfyra.a

FYRA_AVAILABLE := $(if $(wildcard $(FYRA_DIR)/include/ir/Module.h),yes,no)

ifeq ($(FYRA_AVAILABLE),yes)
$(FYRA_LIB): $(FYRA_OBJS)
	@echo "[BUILD] Building Fyra library with Makefile..."
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	@echo "[OK] Fyra library built: $@"
else
$(FYRA_LIB):
	@echo "[WARN]  Fyra not found at $(FYRA_DIR) - AOT/WASM compilation disabled"
	@mkdir -p $(dir $@)
	@touch $@
endif

# =============================
# Lyra Package Manager Library & CLI
# =============================
$(LYRA_LIB): $(LYRA_LIB_OBJS)
	@echo "[BUILD] Building Lyra static library ($@)..."
	@mkdir -p $(dir $@)
	@rm -f $@
	$(AR) rcs $@ $^
	@echo "[OK] Lyra library built: $@"

$(LYRA_BIN): $(OBJ_DIR)/lyra/main.o $(LYRA_LIB) | $(BIN_DIR)
	@echo "[BUILD] Building thin Lyra CLI binary..."
	$(CXX) $(CXXFLAGS) $< $(LYRA_LIB) -o $@ -lssl -lcrypto -lpthread
	@echo "[OK] Lyra binary built: $@"

$(OBJ_DIR)/lyra/%.o: $(LYRA_DIR)/src/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(LYRA_DIR)/include -c $< -o $@

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
.PHONY: liblyra
liblyra: $(LYRA_LIB)

liblymar: $(OBJ_DIR)/liblymar.a $(LYRA_LIB)

$(OBJ_DIR)/liblymar.a: $(LIB_LYMAR_OBJS) $(FYRA_LIB) $(LYRA_LIB)
	@echo "[BUILD] Building liblymar.a ..."
	@mkdir -p $(dir $@)
	@rm -f $@
	$(AR) rcs $@ $(LIB_LYMAR_OBJS) $(LYRA_LIB_OBJS)

windows: $(BIN_DIR) $(MAIN_RSP) liblymar $(LYRA_BIN) $(BIN_DIR)/liblymar_aot.a
	@echo "[BUILD] Linking lymar.exe ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) @$(MAIN_RSP) $(OBJ_DIR)/liblymar.a $(FYRA_LIB) $(LYRA_LIB) -o $(BIN_DIR)/lymar$(EXE_EXT) $(LIBS) -lssl -lcrypto
	@echo "[OK] lymar.exe built."

linux: $(BIN_DIR) $(MAIN_RSP) liblymar ssl-lib $(LYRA_BIN) $(BIN_DIR)/liblymar_aot.a
	@echo "[BUILD] Linking lymar ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) @$(MAIN_RSP) $(OBJ_DIR)/liblymar.a $(FYRA_LIB) $(LYRA_LIB) -o $(BIN_DIR)/lymar$(EXE_EXT) $(LIBS) -lssl -lcrypto -lpthread
	@echo "[OK] lymar built."

$(BIN_DIR)/liblymar_aot.a: $(OBJ_DIR)/src/memory/aot_runtime.o Makefile | $(BIN_DIR)
	$(RM) $@.tmp
	$(AR) rcs $@.tmp $<
	mv $@.tmp $@

# =============================
# Precompilation targets
# =============================
precompile: $(PLATFORM)
	@for mod in $(PRECOMPILE_MODULES); do \
		mod_path="std/$$(echo $$mod | sed 's/std\.//')/index.lm"; \
		lib_name="lib$$(echo $$mod | sed 's/std\.//')"; \
		sh_out="bin/$${lib_name}$(SO_EXT)"; \
		st_out="bin/$${lib_name}$(A_EXT)"; \
		rebuild=0; \
		if [ ! -f "$$sh_out" ] || [ ! -f "$$st_out" ] || [ ! -f "$$sh_out.meta" ]; then rebuild=1; \
		else \
			src_dir="std/$$(echo $$mod | sed 's/std\.//')"; \
			if [ -n "$$(find $$src_dir -type f -newer $$sh_out 2>/dev/null)" ]; then rebuild=1; fi; \
		fi; \
		if [ $$rebuild -eq 1 ]; then \
			echo "[PRECOMPILE] Building precompiled module $$mod -> $$sh_out and $$st_out ..."; \
			./bin/lymar$(EXE_EXT) build -shared $$mod_path -o $$sh_out || exit 1; \
			./bin/lymar$(EXE_EXT) build -static $$mod_path -o $$st_out || exit 1; \
		else \
			echo "[PRECOMPILE] Module $$mod is up-to-date."; \
		fi \
	done

precompile-all: $(PLATFORM)
	@$(MAKE) precompile PRECOMPILE_MODULES="$(ALL_PRECOMPILE_MODULES)"

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
	@echo "[CLEAN] Cleaned build artifacts."

clear:
ifeq ($(PLATFORM),windows)
	@echo "[CLEAN] Cleaning generated .txt files..."
	@powershell -Command "Get-ChildItem -Recurse -Include *.ast.txt,*.bytecode.txt,*.cst.txt,*.tokens.txt | Remove-Item -Force -ErrorAction SilentlyContinue"
else
	@echo "[CLEAN] Cleaning generated .txt files..."
	@find . -name "*.ast.txt" -type f -delete 2>/dev/null || true
	@find . -name "*.bytecode.txt" -type f -delete 2>/dev/null || true
	@find . -name "*.cst.txt" -type f -delete 2>/dev/null || true
	@find . -name "*.tokens.txt" -type f -delete 2>/dev/null || true
endif
	@echo "[OK] Generated files cleaned."

clean-lm:
ifeq ($(PLATFORM),windows)
	@echo "[CLEAN] Cleaning .lm files from root folder..."
	@powershell -Command "Get-ChildItem -Path . -Filter *.lm -File | Remove-Item -Force -ErrorAction SilentlyContinue"
else
	@echo "[CLEAN] Cleaning .lm files from root folder..."
	@find . -maxdepth 1 -name "*.lm" -type f -delete 2>/dev/null || true
endif
	@echo "[OK] Root .lm files cleaned (std/ and tests/ preserved)."

# =============================
# Parser Test Target
# =============================
parser: $(BIN_DIR) $(TEST_RSP)
	@echo "[BUILD] Building test_parser$(EXE_EXT)...."
	$(CXX) $(CXXFLAGS) @$(TEST_RSP) -o $(BIN_DIR)/test_parser$(EXE_EXT) $(LIBS)
	@echo "[OK] $(BIN_DIR)/test_parser$(EXE_EXT) built."

# =============================
# LIR Round-Trip Test Target (C17)
# =============================
.PHONY: lir-test
lir-test: $(BIN_DIR) $(OBJ_DIR)/liblymar.a $(LIR_TEST_OBJS)
	@echo "[BUILD] Linking lir_test ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIR_TEST_OBJS) $(OBJ_DIR)/liblymar.a -o $(BIN_DIR)/lir_test $(LIBS) -lpthread
	@echo "[OK] lir_test built."
	@echo "[RUN] Running lir_test ..."
	$(BIN_DIR)/lir_test$(EXE_EXT)

# =============================
# Test Target
# =============================
tests: $(PLATFORM) stb-image
	@python3 tests/run_tests.py || python tests/run_tests.py

# =============================
# STB Image shared library
# =============================
stb-image: $(BIN_DIR) $(STB_IMAGE_LIB)

$(STB_IMAGE_LIB): tests/ffi/stb_wrapper.c vendor/stb/stb_image.h vendor/stb/stb_image_write.h
	@echo "[BUILD] Building STB image shared library beside lymar in bin/ -> $@"
	$(CC) $(STB_SHARED_FLAGS) \
		-Ivendor/stb \
		-o $@ \
		tests/ffi/stb_wrapper.c \
		-lm
	@echo "[OK] $@ built."

ANDROID_API ?= 24
ANDROID_TARGET ?= aarch64-linux-android
ifeq ($(strip $(ANDROID_NDK)),)
	ANDROID_CC := $(CC)
else
	ANDROID_CC := $(ANDROID_NDK)/toolchains/llvm/prebuilt/windows-x86_64/bin/$(ANDROID_TARGET)$(ANDROID_API)-clang
endif

stb-image-android: tests/ffi/stb_wrapper.c vendor/stb/stb_image.h vendor/stb/stb_image_write.h
	@echo "[BUILD] Building STB image shared library for Android in bin/ -> bin/libstb_image.so"
	$(ANDROID_CC) -shared -fPIC \
		-Ivendor/stb \
		-o bin/libstb_image.so \
		tests/ffi/stb_wrapper.c \
		-lm
	@echo "[OK] bin/libstb_image.so built for Android."

stb-image-test: $(PLATFORM) stb-image
	@echo "[TEST] Running std.image integration test ..."
ifeq ($(PLATFORM),windows)
	./bin/lymar.exe run tests/ffi/test_image_lib.lm
	./bin/lymar.exe run tests/ffi/test_image_fluent.lm
else
	./bin/lymar run tests/ffi/test_image_lib.lm
	./bin/lymar run tests/ffi/test_image_fluent.lm
endif
	@echo "[OK] std.image integration test finished."

# =============================
# OpenSSL TLS & Crypto shared library
# =============================
ssl-lib: $(BIN_DIR) $(LYMAR_SSL_LIB)

$(LYMAR_SSL_LIB): src/native/openssl_wrapper.c
	@echo "[BUILD] Building OpenSSL native bridge beside lymar in bin/ -> $@"
	$(CC) $(SSL_SHARED_FLAGS) -o $@ src/native/openssl_wrapper.c $(SSL_LIBS)
	@echo "[OK] $@ built."

ssl-lib-android: src/native/openssl_wrapper.c
	@echo "[BUILD] Building OpenSSL native bridge for Android in bin/ -> bin/liblymar_ssl.so"
	$(ANDROID_CC) -shared -fPIC -O2 -o bin/liblymar_ssl.so src/native/openssl_wrapper.c -lssl -lcrypto
	@echo "[OK] bin/liblymar_ssl.so built for Android."

ssl-test: $(PLATFORM) ssl-lib
	@echo "[TEST] Running OpenSSL TLS & Crypto tests ..."
ifeq ($(PLATFORM),windows)
	./bin/lymar.exe run tests/crypto/test_crypto.lm
	./bin/lymar.exe run tests/net/test_tls.lm
else
	./bin/lymar run tests/crypto/test_crypto.lm
	./bin/lymar run tests/net/test_tls.lm
endif
	@echo "[OK] OpenSSL TLS & Crypto tests passed."

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
			./bin/lymar.exe build -target windows -arch x86_64 -O 2 "$$SOURCE_FILE"; \
		else \
			./bin/lymar build -target linux -arch x86_64 -O 2 "$$SOURCE_FILE"; \
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

# Dependency files are optional on the first build.
-include $(OBJ_DIR)/src/memory/aot_runtime.d $(BIN_DIR)/test_memory_contracts.d $(BIN_DIR)/test_reference_lowering.d
-include $(LIB_LYMAR_OBJS:.o=.d) $(MAIN_OBJS:.o=.d) $(TEST_OBJS:.o=.d) $(LYRA_LIB_OBJS:.o=.d) $(OBJ_DIR)/lyra/main.d $(LIR_TEST_OBJS:.o=.d)

# Runtime lifetime tests also support SANITIZERS=address,undefined and an
# isolated BIN_DIR/OBJ_DIR/RSP_DIR, just like the compiler build.
$(BIN_DIR)/test_runtime_lifetimes$(EXE_EXT): tests/memory/test_runtime_lifetimes.cpp $(OBJ_DIR)/liblymar.a $(FYRA_LIB) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(OBJ_DIR)/liblymar.a $(FYRA_LIB) -o $@ $(LIBS) -lpthread

.PHONY: memory-tests
memory-tests: $(PLATFORM) $(BIN_DIR)/test_source_ownership$(EXE_EXT) $(BIN_DIR)/test_runtime_lifetimes$(EXE_EXT) $(BIN_DIR)/test_memory_contracts$(EXE_EXT) $(BIN_DIR)/test_reference_lowering$(EXE_EXT) $(BIN_DIR)/liblymar_aot.a
	$(BIN_DIR)/test_runtime_lifetimes$(EXE_EXT)
	$(BIN_DIR)/test_memory_contracts$(EXE_EXT)
	LYMAR_EXECUTABLE=$(abspath $(BIN_DIR)/lymar$(EXE_EXT)) python3 tests/memory/test_frontend_ownership.py
	LYMAR_SOURCE_OWNERSHIP_EXECUTABLE=$(abspath $(BIN_DIR)/test_source_ownership$(EXE_EXT)) LYMAR_AOT_SANITIZERS="$(SANITIZERS)" python3 tests/memory/test_source_ownership.py
	LYMAR_EXECUTABLE=$(abspath $(BIN_DIR)/lymar$(EXE_EXT)) LYMAR_AOT_CXX=$(abspath tests/memory/aot_linker.py) LYMAR_AOT_SANITIZERS="$(SANITIZERS)" CXX="$(CXX)" python3 tests/memory/test_unified_ownership.py
	LYMAR_REFERENCE_TEST_EXECUTABLE=$(abspath $(BIN_DIR)/test_reference_lowering$(EXE_EXT)) LYMAR_AOT_SANITIZERS="$(SANITIZERS)" CXX="$(CXX)" python3 tests/memory/test_reference_lowering.py

# Private standalone AOT runtime tests; no VM or public ABI additions.
$(BIN_DIR)/test_aot_regions$(EXE_EXT): tests/memory/test_aot_regions.cpp $(BIN_DIR)/liblymar_aot.a | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(BIN_DIR)/liblymar_aot.a -o $@ $(LIBS)

.PHONY: aot-region-tests
aot-region-tests: $(PLATFORM) $(BIN_DIR)/test_aot_regions$(EXE_EXT)
	$(BIN_DIR)/test_aot_regions$(EXE_EXT)
	LYMAR_EXECUTABLE=$(abspath $(BIN_DIR)/lymar$(EXE_EXT)) LYMAR_AOT_CXX=$(abspath tests/memory/aot_linker.py) LYMAR_AOT_SANITIZERS="$(SANITIZERS)" CXX="$(CXX)" python3 tests/memory/test_standalone_regions.py
	LYMAR_EXECUTABLE=$(abspath $(BIN_DIR)/lymar$(EXE_EXT)) LYMAR_AOT_SANITIZERS="$(SANITIZERS)" CXX="$(CXX)" python3 tests/memory/test_target_runtime.py

$(BIN_DIR)/test_memory_contracts$(EXE_EXT): tests/memory/test_memory_contracts.cpp src/memory/memory.hh src/memory/contracts.hh src/memory/model.hh | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@ $(LIBS)

$(BIN_DIR)/test_reference_lowering$(EXE_EXT): tests/memory/test_reference_lowering.cpp $(OBJ_DIR)/liblymar.a $(FYRA_LIB) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(OBJ_DIR)/liblymar.a $(FYRA_LIB) -o $@ $(LIBS) -lpthread

$(BIN_DIR)/test_source_ownership$(EXE_EXT): tests/memory/test_source_ownership.cpp $(OBJ_DIR)/liblymar.a $(FYRA_LIB) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(OBJ_DIR)/liblymar.a $(FYRA_LIB) -o $@ $(LIBS) -lpthread
