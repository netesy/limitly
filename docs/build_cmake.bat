@echo off
rem ============================================================================
rem Limitly CMake Build Script
rem ============================================================================

setlocal
cd /d "%~dp0\.."

set MSYS2_PATH=C:\msys64
if exist "%MSYS2_PATH%\mingw64\bin" (
    set PATH=%MSYS2_PATH%\mingw64\bin;%PATH%
)

if not exist "build_cmake" mkdir build_cmake
cd build_cmake

cmake -G "MinGW Makefiles" ..
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Failed to configure CMake.
    exit /b 1
)

cmake --build .
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake build failed.
    exit /b 1
)

cd ..
echo [OK] Build completed successfully.
exit /b 0