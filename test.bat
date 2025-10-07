@echo off
echo Building CST Test Runner using MSYS2/MinGW64...

:: Check if MSYS2 is installed in the default location
set MSYS2_PATH=C:\msys64
if not exist "%MSYS2_PATH%" (
    echo MSYS2 not found at %MSYS2_PATH%
    echo Please install MSYS2 from https://www.msys2.org/ or update this script with your MSYS2 path
    exit /b 1
)

:: Create output directory
if not exist "bin" mkdir bin

echo Compiling with g++...

:: Compile debugger first as a separate object file to ensure it's available
echo Compiling debugger...
"%MSYS2_PATH%\mingw64\bin\g++.exe" -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -c -o bin\debugger.o src\common\debugger.cpp -I.

if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile src\debugger.cpp
    exit /b 1
)

:: Compile CST test runner
echo Compiling CST test runner...
"%MSYS2_PATH%\mingw64\bin\g++.exe" -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -o bin\test_parser.exe ^
    src\test_parser.cpp ^
    src\frontend\scanner.cpp ^
    src\frontend\cst_parser.cpp ^
    src\frontend\cst.cpp ^
    src\frontend\cst_printer.cpp ^
    src\frontend\ast_builder.cpp ^
    src\frontend\parser.cpp ^
    src\backend\type_checker.cpp ^
    src\backend\backend.cpp ^
    src\backend\ast_printer.cpp ^
    src\backend\bytecode_printer.cpp ^
    src\backend\functions.cpp ^
    src\backend\closure_impl.cpp ^
    src\backend\classes.cpp ^
    src\error\error_formatter.cpp ^
    src\error\error_code_generator.cpp ^
    src\error\contextual_hint_provider.cpp ^
    src\error\source_code_formatter.cpp ^
    src\error\console_formatter.cpp ^
    src\error\error_catalog.cpp ^
    bin\debugger.o ^
    -I. -static-libgcc -static-libstdc++

if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile test_parser.exe
    exit /b 1
)

:: Clean up object file
del bin\debugger.o

echo.
echo ========================================
echo CST Test Runner build completed successfully!
echo ========================================
echo.
echo Available executable:
echo   bin\test_parser.exe  - CST Parser test runner
echo.
echo Usage examples:
echo   bin\test_parser.exe tests\basic\variables.lm
echo   bin\test_parser.exe tests\basic\
echo   bin\test_parser.exe tests\
echo.