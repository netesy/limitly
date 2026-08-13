#!/bin/bash
echo "Building Fyra verify tool..."
g++ -std=c++17 -Ivendor/fyra/include -Ivendor/fyra/src scripts/verify_fyra_output.cpp vendor/fyra/build/libfyra.a -o scripts/verify_fyra_output

FAILED=0
PASSED=0
echo "Running differential verification on tests/fyra/*.fyra..."

for f in tests/fyra/*.fyra; do
    ./scripts/verify_fyra_output "$f" > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        ((PASSED++))
    else
        ((FAILED++))
        echo "FAILED verification: $f"
    fi
done

echo ""
echo "FYRA DIFFERENTIAL VERIFICATION"
echo "Tests: $((PASSED + FAILED))"
echo "Passed: $PASSED"
echo "Failed: $FAILED"
