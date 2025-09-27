@echo off
echo Building and running ErrorCatalog unit tests...
echo.

REM Create bin directory if it doesn't exist
if not exist "bin" mkdir bin

REM Compile the test
echo Compiling test_error_catalog...
g++ -std=c++17 -I. -o bin/test_error_catalog.exe tests/unit/test_error_catalog.cpp src/error_catalog.cpp

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b 1
)

echo Compilation successful!
echo.

REM Run the test
echo Running ErrorCatalog tests...
echo =============================
bin\test_error_catalog.exe

if %ERRORLEVEL% neq 0 (
    echo Tests failed!
    exit /b 1
)

echo.
echo All tests completed successfully!