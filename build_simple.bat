@echo off
echo Building Limit Language using direct compilation...

:: Create output directory
if not exist "bin" mkdir bin

:: Check for available compilers
where cl >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Using MSVC compiler...
    
    :: Compile with MSVC
    cl /std:c++17 /EHsc /W4 /Fe:bin\limitly.exe ^
       main.cpp ^
       frontend\scanner.cpp ^
       frontend\parser.cpp ^
       backend\backend.cpp ^
       backend\vm.cpp ^
       debugger.cpp ^
       /I.
       
    cl /std:c++17 /EHsc /W4 /Fe:bin\test_parser.exe ^
       test_parser.cpp ^
       frontend\scanner.cpp ^
       frontend\parser.cpp ^
       backend\backend.cpp ^
       debugger.cpp ^
       /I.
) else (
    where g++ >nul 2>nul
    if %ERRORLEVEL% EQU 0 (
        echo Using G++ compiler...
        
        :: Compile with G++
        g++ -std=c++17 -Wall -Wextra -pedantic -o bin\limitly.exe ^
            main.cpp ^
            frontend\scanner.cpp ^
            frontend\parser.cpp ^
            backend\backend.cpp ^
            backend\vm.cpp ^
            debugger.cpp ^
            -I.
            
        g++ -std=c++17 -Wall -Wextra -pedantic -o bin\test_parser.exe ^
            test_parser.cpp ^
            frontend\scanner.cpp ^
            frontend\parser.cpp ^
            backend\backend.cpp ^
            debugger.cpp ^
            -I.
    ) else (
        echo No C++ compiler found. Please install Visual Studio or MinGW.
        exit /b 1
    )
)

echo.
echo Build completed.
echo.
echo To run the main executable:
echo   bin\limitly.exe
echo.
echo To run the test parser:
echo   bin\test_parser.exe sample.lm
echo.