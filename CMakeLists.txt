cmake_minimum_required(VERSION 3.10)
project(limitly LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
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
    src/backend/vm.cpp
    src/frontend/ast.cpp
    src/frontend/lexer.cpp
    src/frontend/parser.cpp
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
    src/frontend/scanner.cpp
    src/frontend/cst_parser.cpp
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

# Link libraries
target_link_libraries(limitly PRIVATE Threads::Threads)
target_link_libraries(test_parser PRIVATE Threads::Threads)
target_link_libraries(test_scanner PRIVATE Threads::Threads)
