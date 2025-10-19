@echo off
echo === Building and Running Hierarchical CST Structure Tests ===

REM Compile the test
echo Compiling hierarchical CST test...
g++ -std=c++17 -I. -Isrc test_hierarchical_cst_structure.cpp ^
    src/frontend/scanner.cpp ^
    src/frontend/parser.cpp ^
    src/frontend/cst.cpp ^
    src/frontend/cst_printer.cpp ^
    src/frontend/cst_utils.cpp ^
    src/common/debugger.cpp ^
    -o test_hierarchical_cst_structure.exe

if %ERRORLEVEL% neq 0 (
    echo ❌ Compilation failed
    exit /b 1
)

echo ✓ Compilation successful

REM Run the test
echo.
echo Running hierarchical CST structure tests...
echo.
test_hierarchical_cst_structure.exe

if %ERRORLEVEL% neq 0 (
    echo ❌ Tests failed
    exit /b 1
)

echo.
echo ✓ All hierarchical CST tests completed