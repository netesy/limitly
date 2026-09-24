@echo off
REM Optimizer Test Suite Runner
REM Runs all optimizer-specific tests

setlocal enabledelayedexpansion

echo ========================================
echo Running Limit Language Optimizer Tests
echo ========================================

set PASSED=0
set FAILED=0
set TOTAL=0

REM Test categories
set TESTS=^
    tests/optimizer/dead_code_elimination.lm ^
    tests/optimizer/constant_folding.lm ^
    tests/optimizer/return_value_preservation.lm ^
    tests/optimizer/instruction_combining.lm ^
    tests/optimizer/optimization_correctness.lm ^
    tests/optimizer/edge_cases.lm

echo.
echo === OPTIMIZER TESTS ===

for %%T in (%TESTS%) do (
    set /a TOTAL=!TOTAL!+1
    echo Running %%T...
    
    call bin\limitly.exe %%T >nul 2>&1
    if !errorlevel! equ 0 (
        echo   PASS: %%T
        set /a PASSED=!PASSED!+1
    ) else (
        echo   FAIL: %%T
        set /a FAILED=!FAILED!+1
    )
)

echo.
echo ========================================
echo Test Results:
echo   PASSED: %PASSED%
echo   FAILED: %FAILED%
echo   TOTAL:  %TOTAL%
echo ========================================

if %FAILED% equ 0 (
    exit /b 0
) else (
    exit /b 1
)
