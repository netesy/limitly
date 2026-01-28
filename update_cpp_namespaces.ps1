# Update all .cpp files with namespace declarations
# This script adds proper namespace declarations to implementation files

param(
    [switch]$DryRun = $false,
    [switch]$Verbose = $false
)

$ErrorActionPreference = "Continue"

# Mapping of .cpp files to their namespaces and corresponding headers
$cppFiles = @{
    "src/lm/frontend/scanner.cpp" = @{ ns = "LM::Frontend"; header = "lm/frontend/scanner.hh" }
    "src/lm/frontend/parser.cpp" = @{ ns = "LM::Frontend"; header = "lm/frontend/parser.hh" }
    "src/lm/frontend/ast_builder.cpp" = @{ ns = "LM::Frontend"; header = "lm/frontend/ast_builder.hh" }
    "src/lm/frontend/type_checker.cpp" = @{ ns = "LM::Frontend"; header = "lm/frontend/type_checker.hh" }
    "src/lm/frontend/memory_checker.cpp" = @{ ns = "LM::Frontend"; header = "lm/frontend/memory_checker.hh" }
    "src/lm/frontend/ast_optimizer.cpp" = @{ ns = "LM::Frontend"; header = "lm/frontend/ast_optimizer.hh" }
    "src/lm/frontend/cst/node.cpp" = @{ ns = "LM::Frontend::CST"; header = "lm/frontend/cst/node.hh" }
    "src/lm/frontend/cst/printer.cpp" = @{ ns = "LM::Frontend::CST"; header = "lm/frontend/cst/printer.hh" }
    "src/lm/frontend/cst/utils.cpp" = @{ ns = "LM::Frontend::CST"; header = "lm/frontend/cst/utils.hh" }
    "src/lm/backend/symbol_table.cpp" = @{ ns = "LM::Backend"; header = "lm/backend/symbol_table.hh" }
    "src/lm/backend/value.cpp" = @{ ns = "LM::Backend"; header = "lm/backend/value.hh" }
    "src/lm/backend/ast_printer.cpp" = @{ ns = "LM::Backend"; header = "lm/backend/ast_printer.hh" }
    "src/lm/backend/code_formatter.cpp" = @{ ns = "LM::Backend"; header = "lm/backend/code_formatter.hh" }
    "src/lm/backend/vm/register.cpp" = @{ ns = "LM::Backend::VM"; header = "lm/backend/vm/register.hh" }
    "src/lm/backend/jit/backend.cpp" = @{ ns = "LM::Backend::JIT"; header = "lm/backend/jit/backend.hh" }
    "src/lm/backend/jit/compiler.cpp" = @{ ns = "LM::Backend::JIT"; header = "lm/backend/jit/compiler.hh" }
    "src/lm/lir/instruction.cpp" = @{ ns = "LM::LIR"; header = "lm/lir/instruction.hh" }
    "src/lm/lir/utils.cpp" = @{ ns = "LM::LIR"; header = "lm/lir/utils.hh" }
    "src/lm/lir/generator.cpp" = @{ ns = "LM::LIR"; header = "lm/lir/generator.hh" }
    "src/lm/lir/functions.cpp" = @{ ns = "LM::LIR"; header = "lm/lir/functions.hh" }
    "src/lm/lir/builtin_functions.cpp" = @{ ns = "LM::LIR"; header = "lm/lir/builtin_functions.hh" }
    "src/lm/lir/types.cpp" = @{ ns = "LM::LIR"; header = "lm/lir/types.hh" }
    "src/lm/lir/function_registry.cpp" = @{ ns = "LM::LIR"; header = "lm/lir/function_registry.hh" }
    "src/lm/error/formatter.cpp" = @{ ns = "LM::Error"; header = "lm/error/formatter.hh" }
    "src/lm/error/code_generator.cpp" = @{ ns = "LM::Error"; header = "lm/error/code_generator.hh" }
    "src/lm/error/hint_provider.cpp" = @{ ns = "LM::Error"; header = "lm/error/hint_provider.hh" }
    "src/lm/error/source_formatter.cpp" = @{ ns = "LM::Error"; header = "lm/error/source_formatter.hh" }
    "src/lm/error/console_formatter.cpp" = @{ ns = "LM::Error"; header = "lm/error/console_formatter.hh" }
    "src/lm/error/catalog.cpp" = @{ ns = "LM::Error"; header = "lm/error/catalog.hh" }
    "src/lm/error/error_handling.cpp" = @{ ns = "LM::Error"; header = "lm/error/error_handling.hh" }
    "src/lm/error/enhanced_error_reporting.cpp" = @{ ns = "LM::Error"; header = "lm/error/enhanced_error_reporting.hh" }
    "src/lm/error/ide_formatter.cpp" = @{ ns = "LM::Error"; header = "lm/error/ide_formatter.hh" }
    "src/lm/debug/debugger.cpp" = @{ ns = "LM::Debug"; header = "lm/debug/debugger.hh" }
}

function Update-CppFile {
    param(
        [string]$FilePath,
        [string]$Namespace,
        [string]$HeaderPath
    )
    
    if (-not (Test-Path $FilePath)) {
        if ($Verbose) { Write-Host "⚠️  Not found: $FilePath" -ForegroundColor Yellow }
        return $false
    }
    
    $content = Get-Content $FilePath -Raw
    
    # Check if already has namespace
    if ($content -match "namespace LM\s*\{") {
        if ($Verbose) { Write-Host "⏭️  Already updated: $FilePath" -ForegroundColor Cyan }
        return $false
    }
    
    # Parse namespace parts
    $nsParts = $Namespace -split "::"
    
    # Build namespace opening
    $nsOpen = ($nsParts | ForEach-Object { "namespace $_ {" }) -join "`n"
    
    # Build namespace closing
    $nsClose = ($nsParts | ForEach-Object { "} // namespace $_" }) -join "`n"
    
    # Update include path - find and replace the main header include
    $content = $content -replace '#include\s+"[^"]*\.hh"', "#include `"$HeaderPath`""
    
    # Find insertion point (after includes)
    $lines = $content -split "`n"
    $insertIdx = 0
    
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -match "#include") {
            $insertIdx = $i + 1
        } elseif ($lines[$i].Trim() -ne "" -and $lines[$i] -notmatch "#include") {
            break
        }
    }
    
    # Reconstruct
    $before = $lines[0..($insertIdx - 1)] -join "`n"
    $after = $lines[$insertIdx..($lines.Count - 1)] -join "`n"
    
    $newContent = "$before`n`n$nsOpen`n`n$after`n`n$nsClose`n"
    
    if (-not $DryRun) {
        Set-Content $FilePath $newContent -NoNewline -Encoding UTF8
        Write-Host "✓ $FilePath" -ForegroundColor Green
    } else {
        Write-Host "📝 $FilePath" -ForegroundColor Yellow
    }
    
    return $true
}

# Main execution
Write-Host "╔════════════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║  Phase 6: Updating Implementation Files with Namespaces       ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

if ($DryRun) {
    Write-Host "🔍 DRY RUN MODE - No changes will be made" -ForegroundColor Yellow
    Write-Host ""
}

$updated = 0
$skipped = 0
$notfound = 0

foreach ($file in $cppFiles.Keys) {
    $config = $cppFiles[$file]
    $result = Update-CppFile -FilePath $file -Namespace $config.ns -HeaderPath $config.header
    
    if ($result -eq $true) {
        $updated++
    } elseif ($result -eq $false) {
        if (Test-Path $file) {
            $skipped++
        } else {
            $notfound++
        }
    }
}

Write-Host ""
Write-Host "╔════════════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║  Summary                                                       ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host "  Updated:  $updated files" -ForegroundColor Green
Write-Host "  Skipped:  $skipped files (already updated)" -ForegroundColor Cyan
Write-Host "  Not found: $notfound files" -ForegroundColor Yellow
Write-Host ""

if ($DryRun) {
    Write-Host "✅ Dry run complete. Run without -DryRun to apply changes." -ForegroundColor Green
} else {
    Write-Host "✅ Implementation file update complete!" -ForegroundColor Green
}
