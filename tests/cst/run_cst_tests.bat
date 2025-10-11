@echo off
setlocal enabledelayedexpansion
echo === CST Parser Test Suite ===
echo.

set TOTAL_TESTS=0
set PASSED_TESTS=0
set FAILED_TESTS=0

echo === CST Scanner Tests ===
for %%f in (tests\cst\scanner\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\test_parser.exe "%%f" > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

echo.
echo === CST Parser Tests ===
for %%f in (tests\cst\parser\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\test_parser.exe "%%f" > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

echo.
echo === CST AST Builder Tests ===
for %%f in (tests\cst\ast_builder\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\test_parser.exe "%%f" > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

echo.
echo === CST Integration Tests ===
for %%f in (tests\cst\integration\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\test_parser.exe "%%f" > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

echo.
echo ================================================
echo CST Test Summary:
echo   Total tests: %TOTAL_TESTS%
echo   Passed: %PASSED_TESTS%
echo   Failed: %FAILED_TESTS%
if %TOTAL_TESTS% GTR 0 (
    set /a SUCCESS_RATE=%PASSED_TESTS%*100/%TOTAL_TESTS%
    echo   Success rate: !SUCCESS_RATE!%%
)
echo ================================================