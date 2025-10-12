@echo off
echo Compiling trivia validation test...

g++ -std=c++17 -I. -o test_trivia_validation.exe test_trivia_validation.cpp ^
    src/frontend/scanner.cpp ^
    src/frontend/cst_parser.cpp ^
    src/frontend/cst.cpp ^
    src/common/debugger.cpp ^
    src/error/error_message.cpp

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo Compilation successful. Running trivia validation tests...
echo.

test_trivia_validation.exe

echo.
echo Test completed. Press any key to exit...
pause > nul