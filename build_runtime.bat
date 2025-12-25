@echo off
echo Building runtime string library...

# Compile runtime_string.c into object file
gcc -c runtime_string.c -o runtime_string.o

if %ERRORLEVEL% neq 0 (
    echo Error: Failed to compile runtime_string.c
    exit /b 1
)

# Create static library
ar rcs limitly_runtime.a runtime_string.o

if %ERRORLEVEL% neq 0 (
    echo Error: Failed to create static library
    exit /b 1
)

echo Runtime string library built successfully: limitly_runtime.a
