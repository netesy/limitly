@echo off
REM tools\make_embedded.bat <embed_name>
if "%1"=="" (
  echo Usage: make_embedded.bat <embed_name>
  exit /b 1
)
set NAME=%1

echo Generating embedded interpreter for %NAME%

:: Ensure generated C++ exists
if not exist src\lembed_generated.cpp (
  echo src\lembed_generated.cpp not found. Please run lembed -embed-source <src> <name> first.
  exit /b 1
)

set MSYS2_PATH=C:\msys64
if not exist "%MSYS2_PATH%" (
  echo MSYS2 not found at %MSYS2_PATH%
  exit /b 1
)


if not exist bin mkdir bin

set EXTRA_LEMBED=
if exist src\lembed.cpp set EXTRA_LEMBED=src\lembed.cpp
if exist src\lembed_builtin.cpp set EXTRA_LEMBED=%EXTRA_LEMBED% src\lembed_builtin.cpp

"%MSYS2_PATH%\mingw64\bin\g++.exe" -std=c++17 -O2 -Wall -Wextra -o bin\limitly_%NAME%.exe ^
  src\main.cpp ^
  src\frontend\scanner.cpp ^
  src\frontend\parser.cpp ^
  src\backend\backend.cpp ^
  src\backend\vm.cpp ^
  src\backend\ast_printer.cpp ^
  src\backend\functions.cpp ^
  src\backend\classes.cpp ^
  %EXTRA_LEMBED% ^
  src\lembed_generated.cpp ^
  bin\debugger.o ^
  -I. -lws2_32 -static-libgcc -static-libstdc++

if %ERRORLEVEL% NEQ 0 (
  echo Failed to compile embedded interpreter
  exit /b %ERRORLEVEL%
)
echo Built bin\limitly_%NAME%.exe
exit /b 0
