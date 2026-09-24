@echo off
rem ============================================================================
rem Lymar Build Script (Delegates to root Makefile)
rem ============================================================================

setlocal
cd /d "%~dp0\.."

echo [BUILD] Building Lymar via root Makefile...
make %*

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Build failed with exit code %ERRORLEVEL%.
    exit /b %ERRORLEVEL%
)

echo [OK] Build completed successfully. Output in bin/
exit /b 0