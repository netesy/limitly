@echo off
echo Compiling ContextualHintProvider tests...

g++ -std=c++17 -I../../src -o test_contextual_hint_provider.exe test_contextual_hint_provider.cpp ../../src/contextual_hint_provider.cpp

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b 1
)

echo Running ContextualHintProvider tests...
test_contextual_hint_provider.exe

if %ERRORLEVEL% neq 0 (
    echo Tests failed!
    exit /b 1
)

echo All tests passed!