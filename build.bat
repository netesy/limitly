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
"%MSYS2_PATH%\mingw64\bin\g++.exe" -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -c -o bin\debugger.o debugger.cpp -I.

if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile debugger.cpp
    exit /b 1
)

:: Compile main executable
echo Compiling main executable...
"%MSYS2_PATH%\mingw64\bin\g++.exe" -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -o bin\limitly.exe ^
    main.cpp ^
    frontend\scanner.cpp ^
    frontend\parser.cpp ^
    backend\backend.cpp ^
    backend\vm.cpp ^
    backend\ast_printer.cpp ^
    backend\functions.cpp ^
    backend\classes.cpp ^
    backend\concurrency\scheduler.cpp ^
    backend\concurrency\thread_pool.cpp ^
    backend\concurrency\event_loop.cpp ^
    backend\concurrency\iocp_event_loop.cpp ^
    bin\debugger.o ^
    -I. -lws2_32 -static-libgcc -static-libstdc++

if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile limitly.exe
    exit /b 1
)

:: Compile test parser
echo Compiling test parser...
"%MSYS2_PATH%\mingw64\bin\g++.exe" -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -o bin\test_parser.exe ^
    test_parser.cpp ^
    frontend\scanner.cpp ^
    frontend\parser.cpp ^
    backend\backend.cpp ^
    backend\ast_printer.cpp ^
    backend\functions.cpp ^
    backend\classes.cpp ^
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
        format_code.cpp ^
        frontend\scanner.cpp ^
        frontend\parser.cpp ^
        backend\code_formatter.cpp ^
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
echo Usage examples:
echo   bin\limitly.exe test_match_concurrent.lm
echo   bin\limitly.exe -ast sample.lm
echo   bin\limitly.exe -bytecode sample.lm
echo   bin\test_parser.exe sample.lm
echo.