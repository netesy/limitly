# Makefile - Build Limit Language for Windows and Linux

# Platform detection
ifeq ($(OS),Windows_NT)
    PLATFORM := windows
    EXE_EXT := .exe
    MSYS2_PATH := C:/msys64
    CXX := $(MSYS2_PATH)/mingw64/bin/g++.exe
    CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -static-libgcc -static-libstdc++
    LIBS := -lws2_32
    LDFLAGS :=
else
    PLATFORM := linux
    EXE_EXT :=
    CXX := g++
    CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -I.
    LDFLAGS += -L/usr/lib/gcc/x86_64-linux-gnu/12
    LIBS :=
endif

# Binaries
BIN_DIR := bin

TARGETS := limitly$(EXE_EXT) test_parser$(EXE_EXT) benchmark_parsers$(EXE_EXT) test_performance_optimization$(EXE_EXT)

# Sources
COMMON_SRCS := src/frontend/scanner.cpp src/frontend/parser.cpp src/common/debugger.cpp
BACKEND_COMMON_SRCS := src/backend/backend.cpp src/backend/functions.cpp src/backend/classes.cpp src/backend/ast_printer.cpp src/backend/bytecode_printer.cpp src/backend/type_checker.cpp
ERROR_SRCS := src/error/error_formatter.cpp src/error/error_code_generator.cpp src/error/contextual_hint_provider.cpp src/error/source_code_formatter.cpp src/error/console_formatter.cpp src/error/error_catalog.cpp
CST_SRCS := src/frontend/cst_parser.cpp src/frontend/cst.cpp src/frontend/cst_printer.cpp src/frontend/cst_utils.cpp src/frontend/cst_utils_simple.cpp src/frontend/ast_builder.cpp

# Platform-specific concurrency sources
ifeq ($(PLATFORM),windows)
    CONCURRENCY_SRCS := src/backend/concurrency/scheduler.cpp src/backend/concurrency/thread_pool.cpp src/backend/concurrency/event_loop.cpp src/backend/concurrency/iocp_event_loop.cpp src/backend/concurrency/concurrency_runtime.cpp src/backend/concurrency/task_vm.cpp
else
    CONCURRENCY_SRCS := src/backend/concurrency/scheduler.cpp src/backend/concurrency/thread_pool.cpp src/backend/concurrency/event_loop.cpp src/backend/concurrency/epoll_event_loop.cpp src/backend/concurrency/concurrency_runtime.cpp
endif

MAIN_SRCS := src/main.cpp src/backend/vm.cpp $(BACKEND_COMMON_SRCS) $(COMMON_SRCS) $(CONCURRENCY_SRCS) src/backend/closure_impl.cpp src/common/builtin_functions.cpp $(ERROR_SRCS)
TEST_SRCS := src/test_parser.cpp $(CST_SRCS) $(BACKEND_COMMON_SRCS) $(COMMON_SRCS) $(ERROR_SRCS)
BENCHMARK_SRCS := src/benchmark_parsers.cpp src/frontend/parser_benchmark.cpp $(CST_SRCS) $(BACKEND_COMMON_SRCS) $(COMMON_SRCS) $(ERROR_SRCS)
PERF_OPT_SRCS := src/test_performance_optimization.cpp src/frontend/parser_benchmark.cpp src/frontend/trivia_optimizer.cpp $(CST_SRCS) $(BACKEND_COMMON_SRCS) $(COMMON_SRCS) $(ERROR_SRCS)


# Objects
OBJ_DIR := obj
MAIN_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))
BENCHMARK_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(BENCHMARK_SRCS))
PERF_OPT_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(PERF_OPT_SRCS))

.PHONY: all clean check-deps benchmarks performance-tests

all: check-deps $(TARGETS)

benchmarks: benchmark_parsers$(EXE_EXT) test_performance_optimization$(EXE_EXT)

performance-tests: benchmarks
	@echo "Running performance benchmarks..."
	$(BIN_DIR)/test_performance_optimization$(EXE_EXT)
	$(BIN_DIR)/benchmark_parsers$(EXE_EXT)

# =============================
# Dependency checks
# =============================
check-deps:
ifeq ($(PLATFORM),windows)
	@cmd /c "if not exist \"$(MSYS2_PATH)\" (echo Error: MSYS2 not found at $(MSYS2_PATH) && exit 1)"
	@cmd /c "if not exist \"$(CXX)\" (echo Error: g++ not found in MSYS2 && exit 1)"
else
	@command -v $(CXX) >/dev/null || (echo "Error: g++ not found." && exit 1)
endif
	@echo "✅ Dependencies OK for $(PLATFORM)."

# =============================
# Build rules
# =============================
limitly$(EXE_EXT): $(MAIN_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

test_parser$(EXE_EXT): $(TEST_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

benchmark_parsers$(EXE_EXT): $(BENCHMARK_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

test_performance_optimization$(EXE_EXT): $(PERF_OPT_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)


$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =============================
# Directories
# =============================
$(OBJ_DIR):
ifeq ($(PLATFORM),windows)
	@cmd /c "if not exist \"$(OBJ_DIR)\" mkdir $(OBJ_DIR)"
else
	mkdir -p $(OBJ_DIR)
endif

$(BIN_DIR):
ifeq ($(PLATFORM),windows)
	@cmd /c "if not exist \"$(BIN_DIR)\" mkdir $(BIN_DIR)"
else
	mkdir -p $(BIN_DIR)
endif

# =============================
# Clean
# =============================
clean:
ifeq ($(PLATFORM),windows)
	@cmd /c "if exist \"$(OBJ_DIR)\" rmdir /s /q $(OBJ_DIR)"
	@cmd /c "if exist \"$(BIN_DIR)\" (cd $(BIN_DIR) && del /q *.exe 2>nul)"
else
	rm -rf $(OBJ_DIR)
	rm -f $(BIN_DIR)/limitly $(BIN_DIR)/test_parser $(BIN_DIR)/benchmark_parsers $(BIN_DIR)/test_performance_optimization
endif
	@echo "🧹 Cleaned build artifacts."

# =============================
# Help
# =============================
help:
	@echo "Available targets:"
	@echo "  all                          - Build all main targets"
	@echo "  limitly$(EXE_EXT)           - Build main language interpreter"
	@echo "  test_parser$(EXE_EXT)       - Build parser testing utility"
	@echo "  benchmarks                   - Build performance benchmark tools"
	@echo "  benchmark_parsers$(EXE_EXT) - Build parser comparison tool"
	@echo "  test_performance_optimization$(EXE_EXT) - Build trivia optimization tester"
	@echo "  performance-tests            - Build and run all performance tests"
	@echo "  clean                        - Clean build artifacts"
	@echo "  check-deps                   - Check build dependencies"
	@echo ""
	@echo "Platform: $(PLATFORM)"
	@echo "Compiler: $(CXX)"
