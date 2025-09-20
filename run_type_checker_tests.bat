@echo off
echo Building and running type checker tests...

REM Create build directory if it doesn't exist
if not exist "build" mkdir build

REM Compile the type checker test
g++ -std=c++17 -I. -o build/type_checker_test.exe ^
    tests/unit/type_checker_test.cpp ^
    src/backend/type_checker.cpp ^
    src/backend/types.cpp ^
    src/backend/memory.cpp ^
    src/frontend/parser.cpp ^
    src/frontend/scanner.cpp ^
    src/debugger.cpp ^
    -DTEST_BUILD

if %ERRORLEVEL% neq 0 (
    echo Failed to compile type checker tests
    exit /b 1
)

echo Running type checker tests...
build\type_checker_test.exe

if %ERRORLEVEL% neq 0 (
    echo Type checker tests failed
    exit /b 1
)

echo Type checker tests completed successfully!