@echo off
setlocal enabledelayedexpansion
echo ========================================
echo Running Limit Language Test Suite
echo ========================================

python tests\run_tests.py %*
