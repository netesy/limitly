#!/bin/bash
# 1. Formatter accuracy
echo 'fn add(a:int,b:int):int{return a+b;}' > tests/acc_test.lm
./bin/limitly -format tests/acc_test.lm > tests/acc_fmt.lm
# Formatter adds spaces and newlines
grep -q "fn add ( a : int , b : int ) : int {" tests/acc_fmt.lm
if [ $? -eq 0 ]; then echo "Formatter accuracy: PASS"; else echo "Formatter accuracy: FAIL"; cat tests/acc_fmt.lm; fi

# 2. LSP accuracy
echo 'var x : int = "str";' | ./bin/limitly -lsp > tests/acc_lsp.json 2>/dev/null
grep -q "\"success\": false" tests/acc_lsp.json
if [ $? -eq 0 ]; then echo "LSP accuracy: PASS"; else echo "LSP accuracy: FAIL"; cat tests/acc_lsp.json; fi

rm tests/acc_test.lm tests/acc_fmt.lm tests/acc_lsp.json
