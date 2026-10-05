@echo off
setlocal enabledelayedexpansion
echo ========================================
echo Running Lymar Language Test Suite
echo ========================================

py tests\run_tests.py %*
