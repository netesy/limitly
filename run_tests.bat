@echo off
echo ========================================
echo Running Limit Language Test Suite
echo ========================================

set LIMITLY=.\bin\limitly.exe
set FAILED=0
set PASSED=0

echo.
echo === BASIC TESTS ===
call :run_test "tests\basic\variables.lm"
call :run_test "tests\basic\literals.lm"
call :run_test "tests\basic\control_flow.lm"
call :run_test "tests\basic\print_statements.lm"

echo.
echo === EXPRESSION TESTS ===
call :run_test "tests\expressions\arithmetic.lm"
call :run_test "tests\expressions\comparison.lm"
call :run_test "tests\expressions\logical.lm"
call :run_test "tests\expressions\ranges.lm"

echo.
echo === STRING TESTS ===
call :run_test "tests\strings\interpolation.lm"
call :run_test "tests\strings\operations.lm"

echo.
echo === LOOP TESTS ===
call :run_test "tests\loops\for_loops.lm"
call :run_test "tests\loops\iter_loops.lm"
call :run_test "tests\loops\while_loops.lm"

echo.
echo === FUNCTION TESTS ===
call :run_test "tests\functions\basic_functions.lm"
call :run_test "tests\functions\advanced_functions.lm"

echo.
echo === CLASS TESTS ===
call :run_test "tests\classes\basic_classes.lm"
call :run_test "tests\classes\inheritance.lm"

echo.
echo === CONCURRENCY TESTS ===
call :run_test "tests\concurrency\parallel_blocks.lm"
call :run_test "tests\concurrency\concurrent_blocks.lm"

echo.
echo === INTEGRATION TESTS ===
call :run_test "tests\integration\comprehensive.lm"
call :run_test "tests\integration\error_handling.lm"

echo.
echo ========================================
echo Test Results:
echo   PASSED: %PASSED%
echo   FAILED: %FAILED%
echo   TOTAL:  %TOTAL%
echo ========================================

if %FAILED% GTR 0 (
    echo Some tests failed!
    exit /b 1
) else (
    echo All tests passed!
    exit /b 0
)

:run_test
set /a TOTAL+=1
echo Running %~1...
%LIMITLY% %~1 >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo   PASS: %~1
    set /a PASSED+=1
) else (
    echo   FAIL: %~1
    set /a FAILED+=1
)
goto :eof