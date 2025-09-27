@echo off
echo Compiling ErrorFormatter demonstration...

g++ -std=c++17 -I. -o error_formatter_demo.exe ^
    src/error_formatter_demo.cpp ^
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

echo Running ErrorFormatter demonstration...
error_formatter_demo.exe

echo.
echo Cleaning up...
del error_formatter_demo.exe