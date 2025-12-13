# Makefile - Build Limit Language (Windows + Linux)

# =============================
# Platform detection
# =============================
ifeq ($(OS),Windows_NT)
    PLATFORM := windows
    EXE_EXT := .exe
    MSYS2_PATH := C:/msys64
    CXX := $(MSYS2_PATH)/mingw64/bin/g++.exe
    LIBS := -lws2_32
else
    PLATFORM := linux
    EXE_EXT :=
    CXX := g++
    LIBS := -lgccjit
    # TODO: Find a more portable way to link libgccjit
    GCCJIT_PATH := /usr/lib/gcc/x86_64-linux-gnu/14/libgccjit.so
    ifeq ($(wildcard $(GCCJIT_PATH)),)
        $(error "libgccjit.so not found at $(GCCJIT_PATH). Please install libgccjit-14-dev")
    endif
    LDFLAGS := -L$(shell dirname $(GCCJIT_PATH))
endif

# =============================
# Build mode
# =============================
MODE ?= release
ifeq ($(MODE),debug)
    CXXFLAGS := -std=c++17 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
else
    CXXFLAGS := -std=c++17 -O3 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. $(if $(filter windows,$(PLATFORM)),-static-libgcc -static-libstdc++)
endif

# =============================
# Directories
# =============================
BIN_DIR := bin
OBJ_DIR := obj/$(MODE)
RSP_DIR := rsp

# =============================
# Sources
# =============================
FRONT_SRCS := src/frontend/scanner.cpp src/frontend/parser.cpp src/common/debugger.cpp src/frontend/cst.cpp src/frontend/cst_printer.cpp src/frontend/cst_utils.cpp src/frontend/ast_builder.cpp
BACK_SRCS := src/backend/vm.cpp src/backend/jit_backend.cpp
COMMON_SRCS := src/common/builtin_functions.cpp
BACKEND_COMMON_SRCS := src/backend/backend.cpp src/backend/symbol_table.cpp src/backend/value.cpp src/backend/ast_printer.cpp src/backend/bytecode_printer.cpp src/backend/functions.cpp src/backend/closure_impl.cpp src/backend/classes.cpp src/backend/type_checker.cpp src/backend/function_types.cpp 
ERROR_SRCS := src/error/error_formatter.cpp src/error/error_code_generator.cpp src/error/contextual_hint_provider.cpp src/error/source_code_formatter.cpp src/error/console_formatter.cpp src/error/error_catalog.cpp

ifeq ($(PLATFORM),windows)
    CONCURRENCY_SRCS := src/backend/concurrency/scheduler.cpp src/backend/concurrency/thread_pool.cpp src/backend/concurrency/event_loop.cpp src/backend/concurrency/iocp_event_loop.cpp src/backend/concurrency/concurrency_runtime.cpp src/backend/concurrency/task_vm.cpp
else
    CONCURRENCY_SRCS := src/backend/concurrency/scheduler.cpp src/backend/concurrency/thread_pool.cpp src/backend/concurrency/event_loop.cpp src/backend/concurrency/epoll_event_loop.cpp src/backend/concurrency/concurrency_runtime.cpp src/backend/concurrency/task_vm.cpp
endif

MAIN_SRCS := src/main.cpp $(BACKEND_COMMON_SRCS) $(BACK_SRCS) $(COMMON_SRCS) $(CONCURRENCY_SRCS) $(ERROR_SRCS) $(FRONT_SRCS)
TEST_SRCS := src/test_parser.cpp $(BACKEND_COMMON_SRCS) $(ERROR_SRCS) $(FRONT_SRCS)

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
.PHONY: all clean clear check-deps windows linux release debug

# =============================
# Default target
# =============================
all: check-deps windows

# =============================
# Dependency check
# =============================
check-deps:
ifeq ($(PLATFORM),windows)
	@powershell -Command "if (-not (Test-Path '$(MSYS2_PATH)')) { Write-Error 'MSYS2 not found at $(MSYS2_PATH)'; exit 1 }"
	@powershell -Command "if (-not (Test-Path '$(CXX)')) { Write-Error 'g++ not found in MSYS2'; exit 1 }"
endif
	@echo "✅ Dependencies OK for $(PLATFORM) in $(MODE) mode."

# =============================
# Object compilation
# =============================
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

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
# Response files generation
# =============================
$(MAIN_RSP): $(MAIN_OBJS) | $(RSP_DIR)
	@echo "Generating $(MAIN_RSP)..."
	@echo $(MAIN_OBJS) > $(MAIN_RSP)
	@echo $(LIBS) >> $(MAIN_RSP)

$(TEST_RSP): $(TEST_OBJS) | $(RSP_DIR)
	@echo "Generating $(TEST_RSP)..."
	@echo $(TEST_OBJS) > $(TEST_RSP)
	@echo $(LIBS) >> $(TEST_RSP)

# =============================
# Build targets
# =============================
windows: $(BIN_DIR) $(MAIN_RSP) $(TEST_RSP)
	@echo "🔨 Linking limitly.exe ..."
	$(CXX) $(CXXFLAGS) @$(MAIN_RSP) -o $(BIN_DIR)/limitly$(EXE_EXT)
	@echo "✅ limitly.exe built."

	@echo "🔨 Linking test_parser.exe ..."
	$(CXX) $(CXXFLAGS) @$(TEST_RSP) -o $(BIN_DIR)/test_parser$(EXE_EXT)
	@echo "✅ test_parser.exe built."

linux: $(BIN_DIR) $(MAIN_RSP) $(TEST_RSP)
	@echo "🔨 Linking limitly ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) @$(MAIN_RSP) -o $(BIN_DIR)/limitly $(LIBS)
	@echo "✅ limitly built."

	@echo "🔨 Linking test_parser ..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) @$(TEST_RSP) -o $(BIN_DIR)/test_parser $(LIBS)
	@echo "✅ test_parser built."

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
	@powershell -Command "if (Test-Path 'obj') { Remove-Item -Recurse -Force 'obj' }"
	@powershell -Command "if (Test-Path 'rsp') { Remove-Item -Recurse -Force 'rsp' }"
	@powershell -Command "if (Test-Path 'bin') { Remove-Item -Recurse -Force 'bin\*.exe' }"
else
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(RSP_DIR)
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
