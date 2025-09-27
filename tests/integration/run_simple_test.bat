@echo off
echo Building and running simple error reporting test...

REM Compile the test
g++ -std=c++17 -I. -o simple_error_test.exe ^
    tests/integration/simple_error_test.cpp ^
    src/common/debugger.cpp ^
    src/error/error_formatter.cpp ^
    src/error/error_code_generator.cpp ^
    src/error/contextual_hint_provider.cpp ^
    src/error/source_code_formatter.cpp ^
    src/error/console_formatter.cpp ^
    src/error/error_catalog.cpp

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b 1
)

echo Running test...
simple_error_test.exe

REM Clean up
del simple_error_test.exe

echo Test completed.