@echo off
echo ========================================
echo Running Limit Language Test Suite
echo ========================================

set LIMITLY=.\bin\limitly.exe
set FAILED=0
set PASSED=0

echo.
echo === BASIC TESTS ===
call :run_test "basic\variables.lm"
call :run_test "basic\literals.lm"
call :run_test "basic\control_flow.lm"
call :run_test "basic\print_statements.lm"

echo.
echo === EXPRESSION TESTS ===
call :run_test "expressions\arithmetic.lm"
call :run_test "expressions\comparison.lm"
call :run_test "expressions\logical.lm"
call :run_test "expressions\ranges.lm"

echo.
echo === STRING TESTS ===
call :run_test "strings\interpolation.lm"
call :run_test "strings\operations.lm"

echo.
echo === LOOP TESTS ===
call :run_test "loops\for_loops.lm"
call :run_test "loops\iter_loops.lm"
call :run_test "loops\while_loops.lm"

echo.
echo === FUNCTION TESTS ===
call :run_test "functions\basic_functions.lm"
call :run_test "functions\advanced_functions.lm"

echo.
echo === CLASS TESTS ===
call :run_test "classes\basic_classes.lm"
call :run_test "classes\inheritance.lm"

echo.
echo === CONCURRENCY TESTS ===
call :run_test "concurrency\parallel_blocks.lm"
call :run_test "concurrency\concurrent_blocks.lm"

echo.
echo === INTEGRATION TESTS ===
call :run_test "integration\comprehensive.lm"
call :run_test "integration\error_handling.lm"

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