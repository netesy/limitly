@echo off
echo Building performance benchmark tools...
echo =====================================

REM Build the project with benchmarks
mkdir build 2>nul
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make benchmark_parsers test_performance_optimization

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build successful! Running performance tests...
echo =============================================

REM Run trivia optimization tests
echo.
echo === Running Performance Optimization Tests ===
bin\test_performance_optimization.exe

REM Run parser benchmarks on test files
echo.
echo === Running Parser Benchmarks ===
bin\benchmark_parsers.exe

echo.
echo Performance benchmarks completed!
echo Check the output above for detailed performance metrics.
echo.
pause