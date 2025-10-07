@echo off
echo === CST Parser Test Suite ===
echo.

set TOTAL_TESTS=0
set PASSED_TESTS=0
set FAILED_TESTS=0

echo Testing existing files with CST parser...
echo.

REM Test basic files
echo === Testing Basic Files ===
for %%f in (tests\basic\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\test_parser.exe "%%f" --cst > nul 2>&1
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
    .\bin\test_parser.exe "%%f" --cst > nul 2>&1
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
    .\bin\test_parser.exe "%%f" --cst > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

echo.
echo === Testing String Files ===
for %%f in (tests\strings\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\test_parser.exe "%%f" --cst > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

echo.
echo === Testing Loop Files ===
for %%f in (tests\loops\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\test_parser.exe "%%f" --cst > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

echo.
echo === CST-Specific Tests ===
for %%f in (tests\cst\scanner\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\test_parser.exe "%%f" --cst > nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        echo   ✓ PASS
        set /a PASSED_TESTS+=1
    ) else (
        echo   ❌ FAIL
        set /a FAILED_TESTS+=1
    )
)

for %%f in (tests\cst\parser\*.lm) do (
    echo Testing: %%f
    set /a TOTAL_TESTS+=1
    .\bin\test_parser.exe "%%f" --cst > nul 2>&1
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