@echo off
setlocal enabledelayedexpansion
echo ========================================
echo Running Limit Language Test Suite
echo ========================================

py tests\run_tests.py %*
