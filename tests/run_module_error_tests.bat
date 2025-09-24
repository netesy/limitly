@echo off
echo ===== Module and Function Error Handling Test Suite =====
echo.

echo Running comprehensive error tests...
..\bin\limitly.exe tests\modules\comprehensive_error_tests.lm
echo.

echo Running memory management tests...
..\bin\limitly.exe tests\modules\memory_management_tests.lm
echo.

echo Running performance tests...
..\bin\limitly.exe tests\modules\performance_tests.lm
echo.

echo ===== Testing Error Conditions =====
echo.

echo Testing missing function (should show error):
..\bin\limitly.exe test_missing_function.lm
echo.

echo Testing missing variable (should show error):
..\bin\limitly.exe test_missing_variable.lm
echo.

echo Testing wrong parameter count (should show error):
..\bin\limitly.exe test_wrong_parameters.lm
echo.

echo Testing too many parameters (should show error):
..\bin\limitly.exe test_too_many_parameters.lm
echo.

echo Testing missing return value (should show error):
..\bin\limitly.exe test_missing_return.lm
echo.

echo ===== All Module Error Tests Complete =====