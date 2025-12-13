@echo off
echo Building Limit Language using MSYS2/MinGW64 with CMake...

:: Check if MSYS2 is installed in the default location
set MSYS2_PATH=C:\msys64
if not exist "%MSYS2_PATH%" (
    echo MSYS2 not found at %MSYS2_PATH%
    echo Please install MSYS2 from https://www.msys2.org/ or update this script with your MSYS2 path
    exit /b 1
)

:: Add MSYS2 MinGW64 to PATH temporarily
set PATH=%MSYS2_PATH%\mingw64\bin;%PATH%

:: Create build directory
if not exist "build" mkdir build
cd build

:: Configure CMake
cmake -G "MinGW Makefiles" ..

if %ERRORLEVEL% NEQ 0 (
    echo Failed to configure CMake
    cd ..
    exit /b 1
)

:: Build the project
cmake --build .

if %ERRORLEVEL% NEQ 0 (
    echo Failed to build project
    cd ..
    exit /b 1
)

cd ..

echo.
echo Build completed successfully.
echo.
echo To run the main executable:
echo   build\limitly.exe
echo.
echo To run the test parser:
echo   build\test_parser.exe sample.lm
echo.