@echo off
REM Negative Test Runner for Lymar Language (Windows)
REM Tests that programs SHOULD FAIL compilation/execution

setlocal enabledelayedexpansion

if not exist "bin\lymar.exe" (
    echo Error: bin\lymar.exe not found
    exit /b 1
)

REM Run negative tests with Python
python tests\negative\run_negative_tests.py %*
exit /b !ERRORLEVEL!
