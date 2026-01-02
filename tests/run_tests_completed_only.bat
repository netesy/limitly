@echo off
setlocal enabledelayedexpansion
echo ========================================
echo Running Limit Language Test Suite (Completed Features Only)
echo ========================================

set LIMITLY=.\bin\limitly.exe
set FAILED=0
set PASSED=0
set TOTAL=0

echo.
echo === BASIC TESTS ===
call :run_test_with_error_check "tests\basic\variables.lm"
call :run_test_with_error_check "tests\basic\literals.lm"
call :run_test_with_error_check "tests\basic\control_flow.lm"
call :run_test_with_error_check "tests\basic\print_statements.lm"

echo.
echo === EXPRESSION TESTS ===
call :run_test_with_error_check "tests\expressions\arithmetic.lm"
call :run_test_with_error_check "tests\expressions\logical.lm"
call :run_test_with_error_check "tests\expressions\ranges.lm"
call :run_test_with_error_check "tests\expressions\scientific_notation.lm"
call :run_test_with_error_check "tests\expressions\large_literals.lm"

echo.
echo === STRING TESTS ===
call :run_test_with_error_check "tests\strings\interpolation.lm"
call :run_test_with_error_check "tests\strings\operations.lm"

echo.
echo === LOOP TESTS ===
call :run_test_with_error_check "tests\loops\for_loops.lm"
call :run_test_with_error_check "tests\loops\iter_loops.lm"
call :run_test_with_error_check "tests\loops\while_loops.lm"

echo.
echo === FUNCTION TESTS (COMPLETED FEATURES ONLY) ===
call :run_test_with_error_check "tests\functions\basic.lm"
call :run_test_with_error_check "tests\functions\advanced.lm"
@REM Closures disabled - first-class functions not implemented yet
@REM call :run_test_with_error_check "tests\functions\closures.lm"
@REM First-class functi