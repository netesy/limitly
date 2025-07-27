@echo off
echo ========================================
echo Running Limit Language Test Suite (Verbose)
echo ========================================

set LIMITLY=..\bin\limitly.exe
set FAILED=0
set PASSED=0

echo.
echo === BASIC TESTS ===
call :run_test_verbose "basic\variables.lm"
call :run_test_verbose "basic\literals.lm"
call :run_test_verbose "basic\control_flow.lm"
call :run_test_verbose "basic\print_statements.lm"

echo.
echo === EXPRESSION TESTS ===
call :run_test_verbose "expressions\arithmetic.lm"
call :run_test_verbose "expressions\comparison.lm"
call :run_test_verbose "expressions\logical.lm"
call :run_test_verbose "expressions\ranges.lm"

echo.
echo === STRING TESTS ===
call :run_test_verbose "strings\interpolation.lm"
call :run_test_verbose "strings\operations.lm"

echo.
echo === LOOP TESTS ===
call :run_test_verbose "loops\for_loops.lm"
call :run_test_verbose "loops\iter_loops.lm"

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

:run_test_verbose
set /a TOTAL+=1
echo.
echo ----------------------------------------
echo Running %~1
echo ----------------------------------------
%LIMITLY% %~1
if %ERRORLEVEL% EQU 0 (
    echo   RESULT: PASS
    set /a PASSED+=1
) else (
    echo   RESULT: FAIL
    set /a FAILED+=1
)
goto :eof