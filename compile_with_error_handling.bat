@echo off
REM Compile script that includes all necessary error handling files
REM Usage: compile_with_error_handling.bat <source_file> <output_name>
REM Example: compile_with_error_handling.bat test_cst_parser_foundation.cpp test_cst_parser_foundation.exe

if "%~1"=="" (
    echo Usage: %0 ^<source_file^> ^<output_name^>
    echo Example: %0 test_cst_parser_foundation.cpp test_cst_parser_foundation.exe
    exit /b 1
)

if "%~2"=="" (
    echo Usage: %0 ^<source_file^> ^<output_name^>
    echo Example: %0 test_cst_parser_foundation.cpp test_cst_parser_foundation.exe
    exit /b 1
)

set SOURCE_FILE=%1
set OUTPUT_NAME=%2

echo Compiling %SOURCE_FILE% with full error handling support...

REM Core source files
set CORE_FILES=src/frontend/cst_parser.cpp src/frontend/cst.cpp src/frontend/scanner.cpp src/common/debugger.cpp

REM All error handling files
set ERROR_FILES=src/error/console_formatter.cpp src/error/error_formatter.cpp src/error/error_catalog.cpp src/error/contextual_hint_provider.cpp src/error/error_code_generator.cpp src/error/source_code_formatter.cpp src/error/enhanced_error_reporting.cpp src/error/ide_formatter.cpp

REM Compile command
g++ -std=c++17 -I. %SOURCE_FILE% %CORE_FILES% %ERROR_FILES% -o %OUTPUT_NAME%

if %ERRORLEVEL% EQU 0 (
    echo ✓ Compilation successful: %OUTPUT_NAME%
) else (
    echo ✗ Compilation failed
    exit /b 1
)