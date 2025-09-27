@echo off
echo Building Limit Language using MSYS2/MinGW64...

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

:: Compile main executable
echo Compiling main executable...
"%MSYS2_PATH%\mingw64\bin\g++.exe" -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -o bin\limitly.exe ^
    src\main.cpp ^
    src\frontend\scanner.cpp ^
    src\frontend\parser.cpp ^
    src\backend\backend.cpp ^
    src\backend\vm.cpp ^
    src\backend\ast_printer.cpp ^
    src\backend\bytecode_printer.cpp ^
    src\backend\functions.cpp ^
    src\backend\classes.cpp ^
    src\backend\type_checker.cpp ^
    src\backend\concurrency\scheduler.cpp ^
    src\backend\concurrency\thread_pool.cpp ^
    src\backend\concurrency\event_loop.cpp ^
    src\backend\concurrency\iocp_event_loop.cpp ^
    src\backend\concurrency\concurrency_runtime.cpp ^
    src\backend\concurrency\task_vm.cpp ^
    src\error\error_formatter.cpp ^
    src\error\error_code_generator.cpp ^
    src\error\contextual_hint_provider.cpp ^
    src\error\source_code_formatter.cpp ^
    src\error\console_formatter.cpp ^
    src\error\error_catalog.cpp ^
    bin\debugger.o ^
    -I. -lws2_32 -static-libgcc -static-libstdc++


if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile limitly.exe
    exit /b 1
)

:: Compile test parser
echo Compiling test parser...
"%MSYS2_PATH%\mingw64\bin\g++.exe" -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -o bin\test_parser.exe ^
    src\test_parser.cpp ^
    src\frontend\scanner.cpp ^
    src\frontend\parser.cpp ^
    src\backend\type_checker.cpp ^
    src\backend\backend.cpp ^
    src\backend\ast_printer.cpp ^
    src\backend\bytecode_printer.cpp ^
    src\backend\functions.cpp ^
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

:: Compile code formatter (optional)
if exist "format_code.cpp" (
    echo Compiling code formatter...
    "%MSYS2_PATH%\mingw64\bin\g++.exe" -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -o bin\format_code.exe ^
        src\format_code.cpp ^
        src\frontend\scanner.cpp ^
        src\frontend\parser.cpp ^
        src\backend\code_formatter.cpp ^
        bin\debugger.o ^
        -I. -static-libgcc -static-libstdc++
    
    if %ERRORLEVEL% EQU 0 (
        echo Code formatter compiled successfully.
    ) else (
        echo Warning: Failed to compile code formatter.
    )
)

:: Clean up object file
del bin\debugger.o

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Available executables:
echo   bin\limitly.exe      - Main language interpreter
echo   bin\test_parser.exe  - Parser testing utility
if exist "bin\format_code.exe" echo   bin\format_code.exe  - Code formatter
echo.
echo Note: embedding targets are intentionally disabled from this build.
echo Use the generator and tools in `tools/` to produce embedded interpreters.
echo
:: Building embedded interpreters is disabled in the default build.
echo Note: the lembed generator and embedding targets are disabled by default.
echo To generate embedded interpreters, use the `lembed` generator and the
echo `tools\make_embedded.bat` / `tools/make_embedded.sh` helpers manually.
echo