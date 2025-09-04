# Makefile - Build Limit Language on Linux

CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -pedantic -I.
LDFLAGS   += -L/usr/lib/gcc/x86_64-linux-gnu/12
LIBS      := -lgccjit

# Binaries
BIN_DIR   := bin

TARGETS   := $(BIN_DIR)/limitly $(BIN_DIR)/test_parser $(BIN_DIR)/format_code

# Sources
COMMON_SRCS := src/frontend/scanner.cpp src/frontend/parser.cpp src/debugger.cpp
BACKEND_COMMON_SRCS := src/backend/backend.cpp src/backend/functions.cpp src/backend/classes.cpp src/backend/ast_printer.cpp
MAIN_SRCS   := src/main.cpp arc/backend/vm.cpp $(BACKEND_COMMON_SRCS) $(COMMON_SRCS)
TEST_SRCS   := src/test_parser.cpp $(BACKEND_COMMON_SRCS) $(COMMON_SRCS)
FORMAT_SRCS := src/format_code.cpp backend/code_formatter.cpp $(COMMON_SRCS)


# Objects
OBJ_DIR    := obj
MAIN_OBJS   := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS   := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))
FORMAT_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(FORMAT_SRCS))

.PHONY: all clean check-deps

all: check-deps $(TARGETS)

# =============================
# Dependency checks
# =============================
check-deps:
	@command -v $(CXX) >/dev/null || (echo "Error: g++ not found." && exit 1)
	@echo "✅ Dependencies OK."

# =============================
# Build rules
# =============================
$(BIN_DIR)/limitly: $(MAIN_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

$(BIN_DIR)/test_parser: $(TEST_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

$(BIN_DIR)/format_code: $(FORMAT_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)


$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =============================
# Directories
# =============================
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# =============================
# Clean
# =============================
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "🧹 Cleaned build artifacts."
