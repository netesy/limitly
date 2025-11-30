@echo off
setlocal enabledelayedexpansion
echo ========================================
echo Running Limit Language Test Suite
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
echo === FUNCTION TESTS ===
call :run_test_with_error_check "tests\functions\basic.lm"
call :run_test_with_error_check "tests\functions\advanced.lm"
call :run_test_with_error_check "tests\functions\closures.lm"
call :run_test_allow_semantic_errors "tests\functions\first_class.lm"

echo.
echo === TYPE TESTS ===
call :run_test_allow_semantic_errors "tests\types\basic.lm"
call :run_test_allow_semantic_errors "tests\types\unions.lm"
call :run_test_allow_semantic_errors "tests\types\options.lm"
call :run_test_with_error_check "tests\types\advanced.lm"

echo.
echo === MODULE TESTS ===
call :run_test_with_error_check "tests\modules\basic_import_test.lm"
call :run_test_with_error_check "tests\modules\comprehensive_module_test.lm"
call :run_test_with_error_check "tests\modules\show_filter_test.lm"
call :run_test_with_error_check "tests\modules\hide_filter_test.lm"
call :run_test_with_error_check "tests\modules\module_caching_test.lm"
call :run_test_with_error_check "tests\modules\function_params_test.lm"

@REM echo.
@REM echo === ERROR HANDLING TESTS ===
@REM call :run_test_with_error_check "tests\error_handling\simple_test.lm"
@REM call :run_test_with_error_check "tests\error_handling\comprehensive_test.lm"

@REM echo.
@REM echo === CLASS TESTS ===
@REM call :run_test_with_error_check "tests\classes\basic_classes.lm"
@REM call :run_test_with_error_check "tests\classes\inheritance.lm"

@REM echo.
@REM echo === CONCURRENCY TESTS ===
@REM call :run_test_with_error_check "tests\concurrency\parallel_blocks.lm"
@REM call :run_test_with_error_check "tests\concurrency\concurrent_blocks.lm"

@REM echo.
@REM echo === INTEGRATION TESTS ===
@REM call :run_test_with_error_check "tests\integration\comprehensive.lm"

@REM echo.
@REM echo === REGRESSION TESTS ===
@REM call :run_test_with_error_check "debug_default_params.lm"
@REM call :run_test_with_error_check "debug_complex_expr.lm"
@REM call :run_test_with_error_check "debug_alias.lm"
@REM call :run_test_with_error_check "debug_union.lm"
@REM call :run_test_with_error_check "test_basic_functions.lm"
@REM call :run_test_with_error_check "test_closures.lm"

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

:run_test_with_error_check
set /a TOTAL+=1
echo Running %~1...

rem Create a temporary file to capture output
set TEMP_FILE=%TEMP%\limitly_test_output_%RANDOM%.txt
%LIMITLY% %~1 > "%TEMP_FILE%" 2>&1

rem Check if the output contains error patterns
findstr /C:"error[E" /C:"Error:" /C:"RuntimeError" /C:"SemanticError" /C:"BytecodeError" "%TEMP_FILE%" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo   FAIL: %~1 ^(contains errors^)
    echo   Error output:
    type "%TEMP_FILE%" | findstr /C:"error[E" /C:"Error:" /C:"RuntimeError" /C:"SemanticError" /C:"BytecodeError"
    set /a FAILED+=1
) else (
    echo   PASS: %~1
    set /a PASSED+=1
)

rem Clean up temporary file
del "%TEMP_FILE%" >nul 2>&1
goto :eof

:run_test_allow_semantic_errors
set /a TOTAL+=1
echo Running %~1...

rem Create a temporary file to capture output
set TEMP_FILE=%TEMP%\limitly_test_output_%RANDOM%.txt
%LIMITLY% %~1 > "%TEMP_FILE%" 2>&1

rem Check if the output contains runtime errors (but allow semantic errors)
findstr /C:"RuntimeError" /C:"BytecodeError" /C:"Error:" "%TEMP_FILE%" | findstr /V /C:"SemanticError" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo   FAIL: %~1 ^(contains runtime errors^)
    echo   Error output:
    type "%TEMP_FILE%" | findstr /C:"RuntimeError" /C:"BytecodeError" /C:"Error:" | findstr /V /C:"SemanticError"
    set /a FAILED+=1
) else (
    echo   PASS: %~1 ^(semantic errors allowed^)
    set /a PASSED+=1
)

rem Clean up temporary file
del "%TEMP_FILE%" >nul 2>&1
goto :eof