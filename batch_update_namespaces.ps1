# Batch update all header files with namespace declarations
# This script processes all .hh files in src/lm and adds proper namespaces

param(
    [switch]$DryRun = $false,
    [switch]$Verbose = $false
)

$ErrorActionPreference = "Continue"

# Namespace mapping for each file
$fileNamespaces = @{
    "src/lm/frontend/ast.hh" = "LM::Frontend"
    "src/lm/frontend/ast_builder.hh" = "LM::Frontend"
    "src/lm/frontend/type_checker.hh" = "LM::Frontend"
    "src/lm/frontend/memory_checker.hh" = "LM::Frontend"
    "src/lm/frontend/ast_optimizer.hh" = "LM::Frontend"
    "src/lm/frontend/cst/node.hh" = "LM::Frontend::CST"
    "src/lm/frontend/cst/printer.hh" = "LM::Frontend::CST"
    "src/lm/frontend/cst/utils.hh" = "LM::Frontend::CST"
    "src/lm/backend/symbol_table.hh" = "LM::Backend"
    "src/lm/backend/value.hh" = "LM::Backend"
    "src/lm/backend/ast_printer.hh" = "LM::Backend"
    "src/lm/backend/types.hh" = "LM::Backend"
    "src/lm/backend/memory.hh" = "LM::Backend"
    "src/lm/backend/env.hh" = "LM::Backend"
    "src/lm/backend/channel.hh" = "LM::Backend"
    "src/lm/backend/fiber.hh" = "LM::Backend"
    "src/lm/backend/task.hh" = "LM::Backend"
    "src/lm/backend/scheduler.hh" = "LM::Backend"
    "src/lm/backend/shared_cell.hh" = "LM::Backend"
    "src/lm/backend/register_value.hh" = "LM::Backend"
    "src/lm/backend/memory_analyzer.hh" = "LM::Backend"
    "src/lm/backend/code_formatter.hh" = "LM::Backend"
    "src/lm/backend/vm/register.hh" = "LM::Backend::VM"
    "src/lm/backend/jit/backend.hh" = "LM::Backend::JIT"
    "src/lm/backend/jit/compiler.hh" = "LM::Backend::JIT"
    "src/lm/memory/model.hh" = "LM::Memory"
    "src/lm/memory/compiler.hh" = "LM::Memory"
    "src/lm/memory/runtime.hh" = "LM::Memory"
    "src/lm/lir/instruction.hh" = "LM::LIR"
    "src/lm/lir/utils.hh" = "LM::LIR"
    "src/lm/lir/generator.hh" = "LM::LIR"
    "src/lm/lir/functions.hh" = "LM::LIR"
    "src/lm/lir/builtin_functions.hh" = "LM::LIR"
    "src/lm/lir/types.hh" = "LM::LIR"
    "src/lm/lir/function_registry.hh" = "LM::LIR"
    "src/lm/error/formatter.hh" = "LM::Error"
    "src/lm/error/code_generator.hh" = "LM::Error"
    "src/lm/error/hint_provider.hh" = "LM::Error"
    "src/lm/error/source_formatter.hh" = "LM::Error"
    "src/lm/error/console_formatter.hh" = "LM::Error"
    "src/lm/error/catalog.hh" = "LM::Error"
    "src/lm/error/error_handling.hh" = "LM::Error"
    "src/lm/error/error_message.hh" = "LM::Error"
    "src/lm/error/enhanced_error_reporting.hh" = "LM::Error"
    "src/lm/error/ide_formatter.hh" = "LM::Error"
    "src/lm/debug/debugger.hh" = "LM::Debug"
}

function Get-HeaderGuard {
    param([string]$Namespace)
    
    $parts = $Namespace -split "::"
    $guard = "LM_" + ($parts -join "_").ToUpper() + "_HH"
    return $guard
}

function Update-HeaderFile {
    param(
        [string]$FilePath,
        [string]$Namespace
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
    
    # Get header guard
    $guard = Get-HeaderGuard $Namespace
    
    # Parse namespace parts
    $nsParts = $Namespace -split "::"
    
    # Build namespace opening
    $nsOpen = ($nsParts | ForEach-Object { "namespace $_ {" }) -join "`n"
    
    # Build namespace closing
    $nsClose = ($nsParts | ForEach-Object { "} // namespace $_" }) -join "`n"
    
    # Update header guard
    $content = $content -replace "#ifndef\s+\w+", "#ifndef $guard"
    $content = $content -replace "#define\s+\w+\s*$", "#define $guard"
    
    # Remove old endif
    $content = $content -replace "#endif\s*//.*$", ""
    
    # Find insertion point (after includes)
    $lines = $content -split "`n"
    $insertIdx = 0
    
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -match "#include" -or $lines[$i] -match "^$") {
            $insertIdx = $i + 1
        } elseif ($lines[$i].Trim() -ne "" -and $lines[$i] -notmatch "#ifndef" -and $lines[$i] -notmatch "#define") {
            break
        }
    }
    
    # Reconstruct
    $before = $lines[0..($insertIdx - 1)] -join "`n"
    $after = $lines[$insertIdx..($lines.Count - 1)] -join "`n"
    
    $newContent = "$before`n`n$nsOpen`n`n$after`n`n$nsClose`n`n#endif // $guard`n"
    
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
Write-Host "║  Batch Update: Adding Namespaces to Header Files              ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

if ($DryRun) {
    Write-Host "🔍 DRY RUN MODE - No changes will be made" -ForegroundColor Yellow
    Write-Host ""
}

$updated = 0
$skipped = 0
$notfound = 0

foreach ($file in $fileNamespaces.Keys) {
    $ns = $fileNamespaces[$file]
    $result = Update-HeaderFile -FilePath $file -Namespace $ns
    
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
    Write-Host "✅ Batch update complete!" -ForegroundColor Green
}
