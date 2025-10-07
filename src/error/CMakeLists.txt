# Error Handling Library CMake Configuration
# This file defines the error handling library that can be linked
# to prevent dependency issues

cmake_minimum_required(VERSION 3.10)

# Define the error handling library
add_library(error_handling STATIC
    console_formatter.cpp
    error_formatter.cpp
    error_catalog.cpp
    contextual_hint_provider.cpp
    error_code_generator.cpp
    source_code_formatter.cpp
    enhanced_error_reporting.cpp
    ide_formatter.cpp
    error_handling.cpp
)

# Set include directories
target_include_directories(error_handling PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# Set C++ standard
target_compile_features(error_handling PUBLIC cxx_std_17)

# Export the library for use by other targets
set_target_properties(error_handling PROPERTIES
    EXPORT_NAME ErrorHandling
    OUTPUT_NAME error_handling
)

# Create an alias for easier linking
add_library(ErrorHandling::ErrorHandling ALIAS error_handling)

# Installation rules (optional)
install(TARGETS error_handling
    EXPORT ErrorHandlingTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES
    error_handling.hh
    error_message.hh
    error_formatter.hh
    console_formatter.hh
    source_code_formatter.hh
    ide_formatter.hh
    error_catalog.hh
    error_code_generator.hh
    contextual_hint_provider.hh
    enhanced_error_reporting.hh
    DESTINATION include/error
)