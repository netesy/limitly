cmake_minimum_required(VERSION 3.10)
project(limitly CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(src)
include_directories(src/backend/fyra/include)
include_directories(src/backend/fyra/src)

# Platform detection
if(WIN32)
    set(PLATFORM_LIBS -lws2_32)
    set(PLATFORM_EXE_EXT .exe)
    add_definitions(-DWIN32)
else()
    set(PLATFORM_LIBS -lpthread)
    set(PLATFORM_EXE_EXT "")
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable")

# Source files
set(FRONTEND_SOURCES
    src/frontend/scanner.cpp
    src/frontend/parser.cpp
    src/frontend/parser/statements.cpp
    src/frontend/parser/expressions.cpp
    src/frontend/parser/types.cpp
    src/frontend/parser/patterns.cpp
    src/frontend/cst.cpp
    src/frontend/cst/printer.cpp
    src/frontend/cst/utils.cpp
    src/frontend/ast/builder.cpp
    src/frontend/ast/printer.cpp
    src/frontend/type_checker.cpp
    src/frontend/memory_checker.cpp
    src/frontend/ast/optimizer.cpp
)

set(BACKEND_COMMON_SOURCES
    src/backend/symbol_table.cpp
    src/backend/value.cpp
    src/backend/vm/register.cpp
)

set(LIR_SOURCES
    src/lir/lir.cpp
    src/lir/lir_utils.cpp
    src/lir/functions.cpp
    src/lir/builtin_functions.cpp
    src/lir/lir_types.cpp
    src/lir/generator.cpp
    src/lir/function_registry.cpp
)

set(FYRA_BACKEND_SOURCES
    src/backend/fyra.cpp
    src/backend/fyra_ir_generator.cpp
)

set(ERROR_SOURCES
    src/error/debugger.cpp
)

set(RUNTIME_SOURCES
    src/runtime/*.c
)

# Main executable sources
set(MAIN_SOURCES
    src/main.cpp
    ${FRONTEND_SOURCES}
    ${BACKEND_COMMON_SOURCES}
    ${LIR_SOURCES}
    ${FYRA_BACKEND_SOURCES}
    ${ERROR_SOURCES}
)

# Build Fyra as a separate library first
add_subdirectory(src/backend/fyra)

# Create runtime library
add_library(limitly_runtime STATIC ${RUNTIME_SOURCES})
target_include_directories(limitly_runtime PUBLIC src)

# Main executable
add_executable(limitly ${MAIN_SOURCES})
target_link_libraries(limitly 
    PRIVATE 
    limitly_runtime
    fyra
    ${PLATFORM_LIBS}
)

# Set output name
set_target_properties(limitly PROPERTIES OUTPUT_NAME "limitly${PLATFORM_EXE_EXT}")

# Test executable
add_executable(test_parser 
    src/test_parser.cpp
    ${FRONTEND_SOURCES}
    ${BACKEND_COMMON_SOURCES}
    ${LIR_SOURCES}
    ${ERROR_SOURCES}
)
target_link_libraries(test_parser 
    PRIVATE 
    limitly_runtime
    ${PLATFORM_LIBS}
)
set_target_properties(test_parser PROPERTIES OUTPUT_NAME "test_parser${PLATFORM_EXE_EXT}")

# Custom targets
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Clean all build artifacts"
)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

# Find required packages
find_package(Threads REQUIRED)

# Add executable
add_executable(limitly
    src/backend/ast_printer.cpp
    src/backend/backend.cpp
    src/backend/bytecode.cpp
    src/backend/compiler.cpp
    src/backend/constant_pool.cpp
    src/backend/debugger.cpp
    src/backend/debugger_ui.cpp
    src/backend/error_handling.cpp
    src/backend/function.cpp
    src/backend/imports.cpp
    src/backend/instruction.cpp
    src/backend/interpreter.cpp
    src/backend/module.cpp
    src/backend/opcodes.cpp
    src/backend/parser.cpp
    src/backend/scope.cpp
    src/backend/stack_trace.cpp
    src/backend/type_checker.cpp
    src/backend/type_system.cpp
    src/backend/value.cpp
    src/frontend/lexer.cpp
    src/frontend/ast.cpp
    ${FRONTEND_SOURCES}
    src/common/builtin_functions.cpp
    src/backend.hh
    src/compile.cpp
    src/constants.hh
    src/debug.hh
    src/limit.hh
    src/limitly.cpp
    src/opcodes.hh
    src/token.hh
    src/types.hh
    src/utf8.hh
)

# Add test_parser executable
add_executable(test_parser
    src/test_parser.cpp
    ${FRONTEND_SOURCES}
    src/frontend/ast_builder.cpp
    src/backend/ast_printer.cpp
    src/backend/bytecode_printer.cpp
    src/backend/vm.cpp
    src/backend/value.cpp
    src/backend/function.cpp
    src/backend/instruction.cpp
    src/backend/opcodes.cpp
    src/backend/type_system.cpp
    src/backend/type_checker.cpp
    src/backend/scope.cpp
    src/backend/compiler.cpp
    src/backend/constant_pool.cpp
    src/backend/interpreter.cpp
    src/backend/module.cpp
    src/backend/imports.cpp
    src/backend/stack_trace.cpp
    src/backend/error_handling.cpp
    src/backend/debugger.cpp
    src/backend/debugger_ui.cpp
    src/common/builtin_functions.cpp
    src/common/debugger.cpp
    src/error/error_handling.cpp
    src/error/error_formatter.cpp
    src/error/contextual_hint_provider.cpp
    src/frontend/ast.cpp
    src/frontend/parser.cpp
    src/frontend/lexer.cpp
)

# Add scanner test executable
add_executable(test_scanner
    src/test_scanner.cpp
    src/frontend/scanner.cpp
    src/common/debugger.cpp
    src/error/error_handling.cpp
    src/error/error_formatter.cpp
    src/error/contextual_hint_provider.cpp
    src/frontend/ast.cpp
    src/frontend/parser.cpp
    src/frontend/lexer.cpp
)

# Add benchmark executables
add_executable(benchmark_parsers
    src/benchmark_parsers.cpp
    src/frontend/parser_benchmark.cpp
    ${FRONTEND_SOURCES}
    # cst_parser.cpp functionality now integrated into parser.cpp
    src/frontend/cst.cpp
    src/frontend/ast_builder.cpp
    src/backend/ast_printer.cpp
    src/backend/bytecode_printer.cpp
    src/backend/vm.cpp
    src/backend/value.cpp
    src/backend/function.cpp
    src/backend/instruction.cpp
    src/backend/opcodes.cpp
    src/backend/type_system.cpp
    src/backend/type_checker.cpp
    src/backend/scope.cpp
    src/backend/compiler.cpp
    src/backend/constant_pool.cpp
    src/backend/interpreter.cpp
    src/backend/module.cpp
    src/backend/imports.cpp
    src/backend/stack_trace.cpp
    src/backend/error_handling.cpp
    src/backend/debugger.cpp
    src/backend/debugger_ui.cpp
    src/common/builtin_functions.cpp
    src/common/debugger.cpp
    src/error/error_handling.cpp
    src/error/error_formatter.cpp
    src/error/contextual_hint_provider.cpp
    src/frontend/ast.cpp
    src/frontend/lexer.cpp
)

# Add performance optimization test executable
add_executable(test_performance_optimization
    src/test_performance_optimization.cpp
    src/frontend/parser_benchmark.cpp
    src/frontend/trivia_optimizer.cpp
    ${FRONTEND_SOURCES}
    # cst_parser.cpp functionality now integrated into parser.cpp
    src/frontend/ast_builder.cpp
    src/backend/ast_printer.cpp
    src/backend/bytecode_printer.cpp
    src/backend/vm.cpp
    src/backend/value.cpp
    src/backend/function.cpp
    src/backend/instruction.cpp
    src/backend/opcodes.cpp
    src/backend/type_system.cpp
    src/backend/type_checker.cpp
    src/backend/scope.cpp
    src/backend/compiler.cpp
    src/backend/constant_pool.cpp
    src/backend/interpreter.cpp
    src/backend/module.cpp
    src/backend/imports.cpp
    src/backend/stack_trace.cpp
    src/backend/error_handling.cpp
    src/backend/debugger.cpp
    src/backend/debugger_ui.cpp
    src/common/builtin_functions.cpp
    src/common/debugger.cpp
    src/error/error_handling.cpp
    src/error/error_formatter.cpp
    src/error/contextual_hint_provider.cpp
    src/frontend/ast.cpp
    src/frontend/lexer.cpp
)

# Link libraries
target_link_libraries(limitly PRIVATE Threads::Threads)
target_link_libraries(test_parser PRIVATE Threads::Threads)
target_link_libraries(test_scanner PRIVATE Threads::Threads)
target_link_libraries(benchmark_parsers PRIVATE Threads::Threads)
target_link_libraries(test_performance_optimization PRIVATE Threads::Threads)
