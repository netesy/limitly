@echo off
echo === Running Hierarchical CST Structure Tests ===

set TEST_DIR=tests\cst
set PARSER=bin\test_parser.exe

if not exist %PARSER% (
    echo ❌ Parser executable not found: %PARSER%
    echo Please build the project first
    exit /b 1
)

echo Testing hierarchical CST structure with various language constructs...
echo.

REM Test each hierarchical structure file
echo --- Testing If Blocks ---
%PARSER% %TEST_DIR%\hierarchical_if_blocks.lm --cst
if %ERRORLEVEL% neq 0 (
    echo ❌ If blocks test failed
    exit /b 1
)
echo ✓ If blocks test passed
echo.

echo --- Testing Loops ---
%PARSER% %TEST_DIR%\hierarchical_loops.lm --cst
if %ERRORLEVEL% neq 0 (
    echo ❌ Loops test failed
    exit /b 1
)
echo ✓ Loops test passed
echo.

echo --- Testing Functions ---
%PARSER% %TEST_DIR%\hierarchical_functions.lm --cst
if %ERRORLEVEL% neq 0 (
    echo ❌ Functions test failed
    exit /b 1
)
echo ✓ Functions test passed
echo.

echo --- Testing Classes ---
%PARSER% %TEST_DIR%\hierarchical_classes.lm --cst
if %ERRORLEVEL% neq 0 (
    echo ❌ Classes test failed
    exit /b 1
)
echo ✓ Classes test passed
echo.

echo --- Testing Modules ---
%PARSER% %TEST_DIR%\hierarchical_modules.lm --cst
if %ERRORLEVEL% neq 0 (
    echo ❌ Modules test failed
    exit /b 1
)
echo ✓ Modules test passed
echo.

echo --- Testing Expressions ---
%PARSER% %TEST_DIR%\hierarchical_expressions.lm --cst
if %ERRORLEVEL% neq 0 (
    echo ❌ Expressions test failed
    exit /b 1
)
echo ✓ Expressions test passed
echo.

echo === All Hierarchical CST Tests Passed ===

REM Validate CST output files for proper hierarchy
echo.
echo --- Validating CST Output Files ---

for %%f in (%TEST_DIR%\*.lm.cst.txt) do (
    echo Checking %%f for hierarchical structure...
    
    REM Check that statements appear as children, not at root level
    findstr /C:"+ Node: BLOCK_STATEMENT" "%%f" >nul
    if %ERRORLEVEL% equ 0 (
        echo ✓ Found block statements in %%f
    )
    
    findstr /C:"+ Node: IF_STATEMENT" "%%f" >nul
    if %ERRORLEVEL% equ 0 (
        echo ✓ Found if statements in %%f
    )
    
    findstr /C:"+ Node: FUNCTION_DECLARATION" "%%f" >nul
    if %ERRORLEVEL% equ 0 (
        echo ✓ Found function declarations in %%f
    )
)

echo.
echo ✓ All hierarchical CST structure tests completed successfully