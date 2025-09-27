@echo off
echo Building and testing ErrorCodeGenerator...

:: Create bin directory if it doesn't exist
if not exist "..\..\bin" mkdir "..\..\bin"

:: Compile the test
g++ -std=c++17 -I../../src -o ../../bin/test_error_code_generator.exe test_error_code_generator.cpp ../../src/error_code_generator.cpp

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b 1
)

echo Compilation successful. Running tests...
echo.

:: Run the test
..\..\bin\test_error_code_generator.exe

echo.
echo Test execution completed.