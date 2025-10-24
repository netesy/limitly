# PowerShell test runner that properly detects errors
Write-Host "========================================"
Write-Host "Running Limit Language Test Suite"
Write-Host "========================================"

$LIMITLY = ".\bin\limitly.exe"
$FAILED = 0
$PASSED = 0
$TOTAL = 0

function Run-Test {
    param($TestFile)
    
    $TOTAL++
    Write-Host "Running $TestFile..." -NoNewline
    
    # Capture both stdout and stderr
    $output = & $LIMITLY $TestFile 2>&1
    $exitCode = $LASTEXITCODE
    
    # Check if there are any error messages in the output
    $hasErrors = $false
    foreach ($line in $output) {
        if ($line -match "error\[E\d+\]" -or $line -match "Error:" -or $line -match "RuntimeError" -or $line -match "SemanticError") {
            $hasErrors = $true
            break
        }
    }
    
    if ($hasErrors -or $exitCode -ne 0) {
        Write-Host " FAIL" -ForegroundColor Red
        Write-Host "  Output:" -ForegroundColor Yellow
        $output | ForEach-Object { Write-Host "    $_" -ForegroundColor Gray }
        $script:FAILED++
    } else {
        Write-Host " PASS" -ForegroundColor Green
        $script:PASSED++
    }
}

Write-Host ""
Write-Host "=== BASIC TESTS ==="
Run-Test "tests\basic\variables.lm"
Run-Test "tests\basic\literals.lm"
Run-Test "tests\basic\control_flow.lm"
Run-Test "tests\basic\print_statements.lm"

Write-Host ""
Write-Host "=== EXPRESSION TESTS ==="
Run-Test "tests\expressions\arithmetic.lm"
Run-Test "tests\expressions\comparison.lm"
Run-Test "tests\expressions\logical.lm"
Run-Test "tests\expressions\ranges.lm"

Write-Host ""
Write-Host "=== STRING TESTS ==="
Run-Test "tests\strings\interpolation.lm"
Run-Test "tests\strings\operations.lm"

Write-Host ""
Write-Host "=== LOOP TESTS ==="
Run-Test "tests\loops\for_loops.lm"
Run-Test "tests\loops\iter_loops.lm"
Run-Test "tests\loops\while_loops.lm"

Write-Host ""
Write-Host "=== FUNCTION TESTS ==="
Run-Test "tests\functions\basic_functions.lm"
Run-Test "tests\functions\advanced_functions.lm"

Write-Host ""
Write-Host "========================================"
Write-Host "Test Results:"
Write-Host "  PASSED: $PASSED" -ForegroundColor Green
Write-Host "  FAILED: $FAILED" -ForegroundColor Red
Write-Host "  TOTAL:  $TOTAL"
Write-Host "========================================"

if ($FAILED -gt 0) {
    Write-Host "Some tests failed!" -ForegroundColor Red
    exit 1
} else {
    Write-Host "All tests passed!" -ForegroundColor Green
    exit 0
}