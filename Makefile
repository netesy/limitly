# Makefile - Build Limit Language on Linux

CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -pedantic -I.
LDFLAGS   += -L/usr/lib/gcc/x86_64-linux-gnu/12
LIBS      :=

# Binaries
BIN_DIR   := .

TARGETS   := limitly test_parser format_code

# Sources
COMMON_SRCS := src/frontend/scanner.cpp src/frontend/parser.cpp src/debugger.cpp
BACKEND_COMMON_SRCS := src/backend/backend.cpp src/backend/functions.cpp src/backend/classes.cpp src/backend/ast_printer.cpp
MAIN_SRCS   := src/main.cpp src/backend/vm.cpp $(BACKEND_COMMON_SRCS) $(COMMON_SRCS) src/backend/concurrency/scheduler.cpp src/backend/concurrency/thread_pool.cpp src/backend/concurrency/event_loop.cpp src/backend/concurrency/epoll_event_loop.cpp
TEST_SRCS   := src/test_parser.cpp $(BACKEND_COMMON_SRCS) $(COMMON_SRCS)
FORMAT_SRCS := src/format_code.cpp src/backend/code_formatter.cpp $(COMMON_SRCS)


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
limitly: $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

test_parser: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

format_code: $(FORMAT_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)


$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =============================
# Directories
# =============================
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# =============================
# Clean
# =============================
clean:
	rm -rf $(OBJ_DIR) $(TARGETS)
	@echo "🧹 Cleaned build artifacts."
