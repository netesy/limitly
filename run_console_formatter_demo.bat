@echo off
echo Compiling ConsoleFormatter demonstration...

g++ -std=c++17 -I. -o console_formatter_demo.exe ^
    src/console_formatter_demo.cpp ^
    src/console_formatter.cpp

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b 1
)

echo Running ConsoleFormatter demonstration...
console_formatter_demo.exe

echo.
echo Cleaning up...
del console_formatter_demo.exe