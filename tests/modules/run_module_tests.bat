@echo off
echo ========================================
echo Running Comprehensive Module Test Suite
echo ========================================
echo.

set LIMITLY=..\..\bin\limitly.exe
cd /d "%~dp0"
set PASSED=0
set FAILED=0
set TOTAL=0

echo Test 1: Basic Import Test
echo ----------------------------------------
%LIMITLY% basic_import_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Basic Import Test
    set /a PASSED+=1
) else (
    echo [FAIL] Basic Import Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 2: Alias Import Test
echo ----------------------------------------
%LIMITLY% alias_import_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Alias Import Test
    set /a PASSED+=1
) else (
    echo [FAIL] Alias Import Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 3: Show Filter Test
echo ----------------------------------------
%LIMITLY% show_filter_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Show Filter Test
    set /a PASSED+=1
) else (
    echo [FAIL] Show Filter Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 4: Hide Filter Test
echo ----------------------------------------
%LIMITLY% hide_filter_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Hide Filter Test
    set /a PASSED+=1
) else (
    echo [FAIL] Hide Filter Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 5: Nested Import Test
echo ----------------------------------------
%LIMITLY% nested_import_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Nested Import Test
    set /a PASSED+=1
) else (
    echo [FAIL] Nested Import Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 6: Multiple Imports Test
echo ----------------------------------------
%LIMITLY% multiple_imports_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Multiple Imports Test
    set /a PASSED+=1
) else (
    echo [FAIL] Multiple Imports Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 7: Error Cases Test
echo ----------------------------------------
%LIMITLY% error_cases_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Error Cases Test
    set /a PASSED+=1
) else (
    echo [FAIL] Error Cases Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 8: Module Caching Test
echo ----------------------------------------
%LIMITLY% module_caching_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Module Caching Test
    set /a PASSED+=1
) else (
    echo [FAIL] Module Caching Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo ========================================
echo Module Test Suite Results
echo ========================================
echo Total Tests: %TOTAL%
echo Passed: %PASSED%
echo Failed: %FAILED%
echo ========================================

if %FAILED% EQU 0 (
    echo ALL TESTS PASSED!
    exit /b 0
) else (
    echo SOME TESTS FAILED!
    exit /b 1
)