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
    CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -I.
    LDFLAGS += -L/usr/lib/gcc/x86_64-linux-gnu/12
    LIBS :=
endif

# Binaries
BIN_DIR := bin

TARGETS := limitly$(EXE_EXT) test_parser$(EXE_EXT)

# Sources
FRONT_SRCS := src/frontend/scanner.cpp src/frontend/parser.cpp src/common/debugger.cpp src/frontend/cst.cpp src/frontend/cst_printer.cpp src/frontend/cst_utils.cpp src/frontend/ast_builder.cpp
BACK_SRCS := src/backend/vm.cpp
COMMON_SRCS := src/common/builtin_functions.cpp
BACKEND_COMMON_SRCS := src/backend/backend.cpp src/backend/value.cpp src/backend/ast_printer.cpp src/backend/bytecode_printer.cpp src/backend/functions.cpp src/backend/closure_impl.cpp src/backend/classes.cpp src/backend/type_checker.cpp src/backend/function_types.cpp 
ERROR_SRCS := src/error/error_formatter.cpp src/error/error_code_generator.cpp src/error/contextual_hint_provider.cpp src/error/source_code_formatter.cpp src/error/console_formatter.cpp src/error/error_catalog.cpp
CST_SRCS := src/frontend/cst.cpp src/frontend/cst_printer.cpp src/frontend/cst_utils.cpp src/frontend/ast_builder.cpp

# Platform-specific concurrency sources
ifeq ($(PLATFORM),windows)
    CONCURRENCY_SRCS := src/backend/concurrency/scheduler.cpp src/backend/concurrency/thread_pool.cpp src/backend/concurrency/event_loop.cpp src/backend/concurrency/iocp_event_loop.cpp src/backend/concurrency/concurrency_runtime.cpp src/backend/concurrency/task_vm.cpp
else
    CONCURRENCY_SRCS := src/backend/concurrency/scheduler.cpp src/backend/concurrency/thread_pool.cpp src/backend/concurrency/event_loop.cpp src/backend/concurrency/epoll_event_loop.cpp src/backend/concurrency/concurrency_runtime.cpp src/backend/concurrency/task_vm.cpp
endif

MAIN_SRCS := src/main.cpp $(BACKEND_COMMON_SRCS) $(BACK_SRCS) $(COMMON_SRCS) $(CONCURRENCY_SRCS) $(ERROR_SRCS) $(FRONT_SRCS)

TEST_SRCS := src/test_parser.cpp $(BACKEND_COMMON_SRCS) $(ERROR_SRCS) $(FRONT_SRCS)

# Objects
OBJ_DIR := obj
MAIN_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

.PHONY: all clean clear check-deps linux windows

all: check-deps $(TARGETS)

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
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $\ $(LIBS)

test_parser$(EXE_EXT): $(TEST_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $\ $(LIBS)


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
	rm -f $(BIN_DIR)/limitly $(BIN_DIR)/test_parser
endif
	@echo "🧹 Cleaned build artifacts."

# Clear generated files (.ast.txt, .bytecode.txt, .cst.txt, .tokens.txt)
clear:
ifeq ($(PLATFORM),windows)
	@echo "🧹 Cleaning generated .txt files (keeping CMakeLists.txt)..."
	@cmd /c "for /r . %%f in (*.ast.txt) do @del \"%%f\" 2>nul"
	@cmd /c "for /r . %%f in (*.bytecode.txt) do @del \"%%f\" 2>nul"
	@cmd /c "for /r . %%f in (*.cst.txt) do @del \"%%f\" 2>nul"
	@cmd /c "for /r . %%f in (*.tokens.txt) do @del \"%%f\" 2>nul"
else
	@echo "🧹 Cleaning generated .txt files (keeping CMakeLists.txt)..."
	@find . -name "*.ast.txt" -type f -delete 2>/dev/null || true
	@find . -name "*.bytecode.txt" -type f -delete 2>/dev/null || true
	@find . -name "*.cst.txt" -type f -delete 2>/dev/null || true
	@find . -name "*.tokens.txt" -type f -delete 2>/dev/null || true
endif
	@echo "✅ Generated files cleaned."

# =============================
# Platform-specific builds using build script commands
# =============================

# Windows build 
windows:
	@echo "🔨 Building for Windows ..."
	@echo "Compiling main executable..."

	g++ -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -lws2_32 -static-libgcc -static-libstdc++ -o $(BIN_DIR)/limitly.exe \
    $(MAIN_SRCS) 
	@echo "✅ limitly built successfully."
	
	@echo "Compiling test parser..."

	g++ -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I. -lws2_32 -static-libgcc -static-libstdc++ -o $(BIN_DIR)/test_parser.exe $(TEST_SRCS)	
	@echo "✅ test_parser built successfully."

	@echo ""
	@echo "Available executables:"
	@echo "  bin/limitly.exe      - Main language interpreter"
	@echo "  bin/test_parser.exe  - Parser testing utility"

# Linux build using build.sh commands
linux: | $(BIN_DIR)
	@echo "🔨 Building for Linux using build.sh commands..."
	@echo "Checking dependencies..."
	@command -v g++ >/dev/null || (echo "Error: g++ not found." && exit 1)
	@echo "✅ All dependencies found."
	
	@echo "Compiling main executable..."
	g++ -std=c++17 -Wall -Wextra -pedantic -I. -o $(BIN_DIR)/limitly \
    $(MAIN_SRCS) 
	@echo "✅ limitly built successfully."
	
	@echo "Compiling test parser..."
	g++ -std=c++17 -Wall -Wextra -pedantic -I. -o $(BIN_DIR)/test_parser \
    $(TEST_SRCS)	
	@echo "✅ test_parser built successfully."
	
	@echo "Cleaning up object file..."
	rm -f $(BIN_DIR)/debugger.o
	
	@echo ""
	@echo "✅ Linux build completed successfully!"
	@echo ""
	@echo "Available executables:"
	@echo "  $(BIN_DIR)/limitly      - Main language interpreter"
	@echo "  $(BIN_DIR)/test_parser  - Parser testing utility"

# =============================
# Help
# =============================
help:
	@echo "Available targets:"
	@echo "  all                          - Build all main targets"
	@echo "  limitly$(EXE_EXT)           - Build main language interpreter"
	@echo "  test_parser$(EXE_EXT)       - Build parser testing utility"
	@echo "  clean                        - Clean build artifacts (obj/, bin/)"
	@echo "  clear                        - Clear generated .txt files (.ast, .bytecode, .cst, .tokens)"
	@echo "  windows                      - Build (Windows only)"
	@echo "  linux                        - Build (Linux only)"
	@echo "  check-deps                   - Check build dependencies"
	@echo ""
	@echo "Platform: $(PLATFORM)"
	@echo "Compiler: $(CXX)"
