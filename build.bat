@echo off
echo Building Limit Language using MSYS2/MinGW64...

:: Check if MSYS2 is installed in the default location
set MSYS2_PATH=C:\msys64
if not exist "%MSYS2_PATH%" (
    echo MSYS2 not found at %MSYS2_PATH%
    echo Please install MSYS2 from https://www.msys2.org/ or update this script with your MSYS2 path
    exit /b 1
)

:: Add MSYS2 MinGW64 to PATH temporarily
set PATH=%MSYS2_PATH%\mingw64\bin;%PATH%

:: Create output directory
if not exist "bin" mkdir bin

echo Compiling with g++...

:: Compile main executable
g++ -std=c++17 -Wall -Wextra -pedantic -o bin\limitly.exe ^
    main.cpp ^
    frontend\scanner.cpp ^
    frontend\parser.cpp ^
    backend\backend.cpp ^
    backend\vm.cpp ^
    backend\ast_printer.cpp ^
    debugger.cpp ^
    -I.

if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile limitly.exe
    exit /b 1
)

:: Compile test parser
g++ -std=c++17 -Wall -Wextra -pedantic -o bin\test_parser.exe ^
    test_parser.cpp ^
    frontend\scanner.cpp ^
    frontend\parser.cpp ^
    backend\backend.cpp ^
    backend\ast_printer.cpp ^
    debugger.cpp ^
    -I.

if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile test_parser.exe
    exit /b 1
)

:: Compile code formatter
g++ -std=c++17 -Wall -Wextra -pedantic -o bin\format_code.exe ^
    format_code.cpp ^
    frontend\scanner.cpp ^
    frontend\parser.cpp ^
    backend\code_formatter.cpp ^
    debugger.cpp ^
    -I.

if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile format_code.exe
    exit /b 1
)

echo.
echo Build completed successfully.
echo.
echo To run the main executable:
echo   bin\limitly.exe
echo.
echo To run the test parser:
echo   bin\test_parser.exe sample.lm
echo.
echo To run the code formatter:
echo   bin\format_code.exe sample.lm
echo.