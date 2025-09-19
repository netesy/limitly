@echo off
echo ========================================
echo Running Comprehensive Module Test Suite
echo ========================================
echo.

set PASSED=0
set FAILED=0
set TOTAL=0

echo Test 1: Basic Import Test
echo ----------------------------------------
.\bin\limitly.exe tests\modules\basic_import_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Basic Import Test
    set /a PASSED+=1
) else (
    echo [FAIL] Basic Import Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 2: Show Filter Test
echo ----------------------------------------
.\bin\limitly.exe tests\modules\show_filter_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Show Filter Test
    set /a PASSED+=1
) else (
    echo [FAIL] Show Filter Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 3: Hide Filter Test
echo ----------------------------------------
.\bin\limitly.exe tests\modules\hide_filter_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Hide Filter Test
    set /a PASSED+=1
) else (
    echo [FAIL] Hide Filter Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 4: Module Caching Test
echo ----------------------------------------
.\bin\limitly.exe tests\modules\module_caching_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Module Caching Test
    set /a PASSED+=1
) else (
    echo [FAIL] Module Caching Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 5: Comprehensive Module Test
echo ----------------------------------------
.\bin\limitly.exe tests\modules\comprehensive_module_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Comprehensive Module Test
    set /a PASSED+=1
) else (
    echo [FAIL] Comprehensive Module Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 6: Error Cases Test
echo ----------------------------------------
.\bin\limitly.exe tests\modules\error_cases_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Error Cases Test
    set /a PASSED+=1
) else (
    echo [FAIL] Error Cases Test
    set /a FAILED+=1
)
set /a TOTAL+=1
echo.

echo Test 7: Function Parameters Test
echo ----------------------------------------
.\bin\limitly.exe tests\modules\function_params_test.lm
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Function Parameters Test
    set /a PASSED+=1
) else (
    echo [FAIL] Function Parameters Test
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