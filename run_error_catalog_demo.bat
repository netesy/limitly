@echo off
echo Building and running ErrorCatalog demonstration...
echo.

REM Create bin directory if it doesn't exist
if not exist "bin" mkdir bin

REM Compile the demonstration
echo Compiling error_catalog_demo...
g++ -std=c++17 -I. -o bin/error_catalog_demo.exe src/error_catalog_demo.cpp src/error_catalog.cpp src/error_code_generator.cpp

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b 1
)

echo Compilation successful!
echo.

REM Run the demonstration
bin\error_catalog_demo.exe

echo.
echo Demonstration completed!