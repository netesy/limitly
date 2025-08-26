#!/bin/bash

LOG_FILE="parser_test.log"
# Clear log file
> $LOG_FILE

# Find all .lm files in the tests directory
files=$(find tests -name "*.lm")

# Counter for failed tests
failed_count=0
total_count=0

# Loop through each file and run the test_parser
for file in $files; do
    total_count=$((total_count + 1))
    echo "Testing $file..." | tee -a $LOG_FILE
    # run test_parser and redirect stdout and stderr to log file
    ./bin/test_parser "$file" >> $LOG_FILE 2>&1
    # Check the exit code of the last command
    if [ $? -ne 0 ]; then
        echo "----------------------------------------" | tee -a $LOG_FILE
        echo "ERROR: test_parser failed for $file" | tee -a $LOG_FILE
        echo "----------------------------------------" | tee -a $LOG_FILE
        failed_count=$((failed_count + 1))
    fi
done

echo "========================================" | tee -a $LOG_FILE
echo "          Test Summary" | tee -a $LOG_FILE
echo "========================================" | tee -a $LOG_FILE
echo "Total tests: $total_count" | tee -a $LOG_FILE
echo "Failed tests: $failed_count" | tee -a $LOG_FILE

# Exit with a non-zero status code if any tests failed
if [ $failed_count -ne 0 ]; then
    exit 1
fi
