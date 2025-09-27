@echo off
echo Building and running enhanced error reporting integration test...

REM Compile the test
g++ -std=c++17 -I. -o test_enhanced_error_reporting.exe ^
    tests/integration/test_enhanced_error_reporting.cpp ^
    src/frontend/scanner.cpp ^
    src/frontend/parser.cpp ^
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
test_enhanced_error_reporting.exe

REM Clean up
del test_enhanced_error_reporting.exe

echo Test completed.