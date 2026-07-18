cmake_minimum_required(VERSION 3.10)
project(limitly CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)
include_directories(vendor/fyra/include)
include_directories(vendor/fyra/src)

if(WIN32)
    set(PLATFORM_LIBS -lws2_32)
    set(PLATFORM_EXE_EXT .exe)
    add_definitions(-DWIN32)
else()
    set(PLATFORM_LIBS -lpthread)
    set(PLATFORM_EXE_EXT "")
endif()

add_definitions(-DFYRA_AVAILABLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable")

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
    src/frontend/ast/printer.cpp
    src/frontend/type_checker/core.cpp
    src/frontend/type_checker/memory.cpp
    src/frontend/type_checker/utils.cpp
    src/frontend/type_checker/statements.cpp
    src/frontend/type_checker/patterns.cpp
    src/frontend/type_checker/expressions.cpp
    src/frontend/type_checker/declarations.cpp
    src/frontend/type_checker/types.cpp
    src/frontend/type_checker_factory.cpp
    src/frontend/memory_checker.cpp
    src/frontend/ast/optimizer.cpp
    src/frontend/module_manager.cpp
)

set(BACKEND_COMMON_SOURCES
    src/backend/symbol_table.cpp
    src/backend/value.cpp
    src/backend/vm/register.cpp
    src/backend/vm/register_helpers.cpp
    src/backend/vm/ops/arithmetic.cpp
    src/backend/vm/ops/comparison.cpp
    src/backend/vm/ops/collections.cpp
    src/backend/vm/ops/frames.cpp
    src/backend/vm/ops/control_flow.cpp
    src/backend/vm/ops/io.cpp
    src/backend/vm/ops/bitwise.cpp
    src/backend/vm/ops/concurrency.cpp
    src/backend/vm/ops/modules.cpp
    src/backend/vm/ops/objects.cpp
    src/backend/vm/ops/vm_strings.cpp
    src/backend/vm/ops/vm_calls.cpp
    src/backend/vm/ops/vm_cast.cpp
)

set(LIR_SOURCES
    src/lir/lir.cpp
    src/lir/lir_utils.cpp
    src/lir/functions.cpp
    src/lir/builtin_functions.cpp
    src/lir/lir_types.cpp
    src/lir/generator.cpp
    src/lir/generator/core.cpp
    src/lir/generator/statements.cpp
    src/lir/generator/expressions.cpp
    src/lir/generator/signatures.cpp
    src/lir/generator/oop.cpp
    src/lir/generator/concurrency.cpp
    src/lir/generator/modules.cpp
    src/lir/function_registry.cpp
    src/lir/optimizer.cpp
    src/lir/metrics.cpp
    src/lir/serializer.cpp
)

set(FYRA_BACKEND_SOURCES
    src/backend/fyra/fyra.cpp
    src/backend/fyra/fyra_ir_generator.cpp
    src/backend/fyra/builder.cpp
    src/backend/fyra/fyra_builtin_functions.cpp
)

set(ERROR_SOURCES
    src/error/debugger.cpp
)

set(RUNTIME_SOURCES
    src/runtime/runtime.c
    src/runtime/runtime_dict.c
    src/runtime/runtime_list.c
    src/runtime/runtime_string.c
    src/runtime/runtime_tuple.c
    src/runtime/runtime_value.c
)

set(MAIN_SOURCES
    src/main.cpp
    src/limitly.cpp
    src/formatter.cpp
    src/lsp.cpp
    ${FRONTEND_SOURCES}
    ${BACKEND_COMMON_SOURCES}
    ${LIR_SOURCES}
    ${FYRA_BACKEND_SOURCES}
    ${ERROR_SOURCES}
)

# Replace old Fyra source path with vendor path
file(GLOB_RECURSE FYRA_LIB_SOURCES 
    vendor/fyra/src/ir/*.cpp
    vendor/fyra/src/codegen/*.cpp
    vendor/fyra/src/target/*.cpp
    vendor/fyra/src/transforms/*.cpp
    vendor/fyra/src/parser/*.cpp
)

add_library(fyra STATIC ${FYRA_LIB_SOURCES})
target_include_directories(fyra PUBLIC vendor/fyra/include vendor/fyra/src)

add_library(limitly_runtime STATIC ${RUNTIME_SOURCES})
target_include_directories(limitly_runtime PUBLIC src)

add_executable(limitly ${MAIN_SOURCES})
target_link_libraries(limitly 
    PRIVATE 
    limitly_runtime
    fyra
    ${PLATFORM_LIBS}
)

set_target_properties(limitly PROPERTIES OUTPUT_NAME "limitly${PLATFORM_EXE_EXT}")

find_package(Threads REQUIRED)
