@echo off
REM Strict regression runner for error propagation tests
setlocal enabledelayedexpansion

REM Paths
set LIMITLY_BIN=%~dp0..\bin\limitly.exe
set TEST_FILE=tests\errors\common.lm
set OUT_FILE=tests\common_out.txt
set EXPECTED_FULL=tests\common_expected.txt
set EXPECTED_SHORT=tests\common_expected_short.txt

REM Run the interpreter and capture stdout/stderr
"%LIMITLY_BIN%" "%TEST_FILE%" > "%OUT_FILE%" 2>&1

REM Extract short output (everything before the memory report header) using a pure-batch loop
if exist "%OUT_FILE%.short" del "%OUT_FILE%.short" > nul 2>&1
for /f "usebackq delims=" %%L in ("%OUT_FILE%") do (
    echo %%L>>"%OUT_FILE%.short"
    echo %%L | findstr /c:"=== Memory Usage Report ===" > nul
    if not errorlevel 1 goto :AFTER_EXTRACT
)
:AFTER_EXTRACT

REM Compare short outputs
fc "%EXPECTED_SHORT%" "%OUT_FILE%.short" > nul
if %ERRORLEVEL% EQU 0 (
    echo [PASS] Short output matches expected. (Ignoring memory report differences)
    type "%OUT_FILE%"
    del "%OUT_FILE%.short" > nul 2>&1
    endlocal
    exit /b 0
) else (
    echo [FAIL] Short output does NOT match expected. Showing diffs.
    echo ----- Expected (short) -----
    type "%EXPECTED_SHORT%"
    echo ----- Actual (short) -----
    type "%OUT_FILE%.short"
    del "%OUT_FILE%.short" > nul 2>&1
    endlocal
    exit /b 1
)
