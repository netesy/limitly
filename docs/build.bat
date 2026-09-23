@echo off
rem ============================================================================
rem Limitly Build Script (Delegates to root Makefile)
rem ============================================================================

setlocal
cd /d "%~dp0\.."

echo [BUILD] Building Limitly via root Makefile...
make %*

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Build failed with exit code %ERRORLEVEL%.
    exit /b %ERRORLEVEL%
)

echo [OK] Build completed successfully. Output in bin/
exit /b 0