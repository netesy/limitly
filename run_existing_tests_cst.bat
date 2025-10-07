@echo off
echo === Running Existing Tests with Regular Parser ===
echo This tests the existing language features to ensure CST development doesn't break core functionality
echo.

set TOTAL_TESTS=0
set PASSED_TESTS=0
set FAILED_TESTS=0

echo === Testing Basic Files ===
for %%f in (tests\basic\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\limitly.exe "%%f" > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

echo.
echo === Testing Expression Files ===
for %%f in (tests\expressions\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\limitly.exe "%%f" > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

echo.
echo === Testing Function Files ===
for %%f in (tests\functions\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\limitly.exe "%%f" > nul 2>&1
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
echo Test Summary:
echo   Total tests: %TOTAL_TESTS%
echo   Passed: %PASSED_TESTS%
echo   Failed: %FAILED_TESTS%
if %TOTAL_TESTS% GTR 0 (
    set /a SUCCESS_RATE=%PASSED_TESTS%*100/%TOTAL_TESTS%
    echo   Success rate: !SUCCESS_RATE!%%
)
echo ================================================
echo.
echo Note: These tests use the existing parser to verify core functionality
echo CST parser integration is in development and will be tested separately