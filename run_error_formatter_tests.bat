@echo off
echo Compiling ErrorFormatter integration tests...

REM Compile the test
g++ -std=c++17 -I. -o test_error_formatter.exe ^
    tests/unit/test_error_formatter.cpp ^
    src/error_formatter.cpp ^
    src/error_code_generator.cpp ^
    src/contextual_hint_provider.cpp ^
    src/source_code_formatter.cpp ^
    src/error_catalog.cpp ^
    src/debugger.cpp

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b 1
)

echo Running ErrorFormatter integration tests...
test_error_formatter.exe

if %ERRORLEVEL% neq 0 (
    echo Tests failed!
    exit /b 1
)

echo All tests passed!
del test_error_formatter.exe