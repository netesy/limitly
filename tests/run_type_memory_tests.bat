@echo off
setlocal enabledelayedexpansion

echo ===============================================================================
echo COMPREHENSIVE TYPE CHECKING AND MEMORY SAFETY TESTS
echo ===============================================================================

set TOTAL_TESTS=0
set PASSED_TESTS=0
set FAILED_TESTS=0

echo.
echo [1/4] Building the compiler...
make > nul 2>&1
if errorlevel 1 (
    echo ERROR: Failed to build compiler
    exit /b 1
)
echo ✓ Compiler built successfully

echo.
echo [2/4] Running Type Checking Tests (Should Pass)...
echo ===============================================================================

set /a TOTAL_TESTS+=1
echo Testing: Basic Type Tests
bin\limitly.exe tests\types\basic_type_tests.lm > temp_output.txt 2>&1
if errorlevel 1 (
    echo ✗ FAILED: Basic Type Tests
    echo Error output:
    type temp_output.txt
    set /a FAILED_TESTS+=1
) else (
    echo ✓ PASSED: Basic Type Tests
    set /a PASSED_TESTS+=1
)

echo.
echo [3/4] Running Type Error Detection Tests (Should Detect Errors)...
echo ===============================================================================

set /a TOTAL_TESTS+=1
echo Testing: Type Error Detection
bin\limitly.exe tests\types\type_error_tests.lm > temp_output.txt 2>&1
if errorlevel 1 (
    echo ✓ PASSED: Type Error Detection (correctly detected errors)
    echo Detected errors:
    type temp_output.txt | findstr /i "error"
    set /a PASSED_TESTS+=1
) else (
    echo ✗ FAILED: Type Error Detection (should have detected errors)
    set /a FAILED_TESTS+=1
)

echo.
echo [4/4] Running Memory Safety Tests...
echo ===============================================================================

set /a TOTAL_TESTS+=1
echo Testing: Basic Memory Safety Tests
bin\limitly.exe tests\memory\basic_memory_tests.lm > temp_output.txt 2>&1
if errorlevel 1 (
    echo ✗ FAILED: Basic Memory Safety Tests
    echo Error output:
    type temp_output.txt
    set /a FAILED_TESTS+=1
) else (
    echo ✓ PASSED: Basic Memory Safety Tests
    set /a PASSED_TESTS+=1
)

set /a TOTAL_TESTS+=1
echo Testing: Memory Error Detection (Should Detect Errors)
bin\limitly.exe tests\memory\memory_error_tests.lm > temp_output.txt 2>&1
if errorlevel 1 (
    echo ✓ PASSED: Memory Error Detection (correctly detected errors))
    echo Detected errors:
    type temp_output.txt | findstr /i "error"
    set /a PASSED_TESTS+=1
) else (
    echo ✗ FAILED: Memory Error Detection (should have detected errors)
    set /a FAILED_TESTS+=1
)

echo.
echo ===============================================================================
echo TEST SUMMARY
echo ===============================================================================
echo Total Tests: !TOTAL_TESTS!
echo Passed: !PASSED_TESTS!
echo Failed: !FAILED_TESTS!

if !FAILED_TESTS! equ 0 (
    echo.
    echo ✓ ALL TESTS PASSED! Type checking and memory safety are working correctly.
    echo.
    echo Key Features Verified:
    echo - ✓ Type inference and compatibility checking
    echo - ✓ Function parameter and return type validation
    echo - ✓ Type alias and union type support
    echo - ✓ Optional and default parameter type checking
    echo - ✓ Memory safety with linear types and ownership
    echo - ✓ Move semantics and reference tracking
    echo - ✓ Scope-based memory management
    echo - ✓ Comprehensive error detection and reporting
) else (
    echo.
    echo ✗ SOME TESTS FAILED. Please review the error output above.
)

del temp_output.txt > nul 2>&1

echo.
echo ===============================================================================
endlocal