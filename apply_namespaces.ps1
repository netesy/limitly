# Simple and reliable namespace application script
# Processes files one by one with proper error handling

param(
    [string]$Component = "all",  # all, frontend, backend, lir, error, memory, debug
    [switch]$DryRun = $false
)

$ErrorActionPreference = "Continue"

# Define namespace mappings
$namespaces = @{
    "scanner.hh" = @{ ns = "LM::Frontend"; guard = "LM_SCANNER_HH" }
    "parser.hh" = @{ ns = "LM::Frontend"; guard = "LM_PARSER_HH" }
    "ast.hh" = @{ ns = "LM::Frontend"; guard = "LM_AST_HH" }
    "ast_builder.hh" = @{ ns = "LM::Frontend"; guard = "LM_AST_BUILDER_HH" }
    "type_checker.hh" = @{ ns = "LM::Frontend"; guard = "LM_TYPE_CHECKER_HH" }
    "memory_checker.hh" = @{ ns = "LM::Frontend"; guard = "LM_MEMORY_CHECKER_HH" }
    "ast_optimizer.hh" = @{ ns = "LM::Frontend"; guard = "LM_AST_OPTIMIZER_HH" }
    "node.hh" = @{ ns = "LM::Frontend::CST"; guard = "LM_CST_NODE_HH" }
    "printer.hh" = @{ ns = "LM::Frontend::CST"; guard = "LM_CST_PRINTER_HH" }
    "utils.hh" = @{ ns = "LM::Frontend::CST"; guard = "LM_CST_UTILS_HH" }
    "symbol_table.hh" = @{ ns = "LM::Backend"; guard = "LM_SYMBOL_TABLE_HH" }
    "value.hh" = @{ ns = "LM::Backend"; guard = "LM_VALUE_HH" }
    "ast_printer.hh" = @{ ns = "LM::Backend"; guard = "LM_AST_PRINTER_HH" }
    "register.hh" = @{ ns = "LM::Backend::VM"; guard = "LM_REGISTER_HH" }
    "backend.hh" = @{ ns = "LM::Backend::JIT"; guard = "LM_JIT_BACKEND_HH" }
    "compiler.hh" = @{ ns = "LM::Backend::JIT"; guard = "LM_JIT_COMPILER_HH" }
    "model.hh" = @{ ns = "LM::Memory"; guard = "LM_MEMORY_MODEL_HH" }
    "compiler.hh" = @{ ns = "LM::Memory"; guard = "LM_MEMORY_COMPILER_HH" }
    "runtime.hh" = @{ ns = "LM::Memory"; guard = "LM_MEMORY_RUNTIME_HH" }
    "instruction.hh" = @{ ns = "LM::LIR"; guard = "LM_LIR_INSTRUCTION_HH" }
    "generator.hh" = @{ ns = "LM::LIR"; guard = "LM_LIR_GENERATOR_HH" }
    "functions.hh" = @{ ns = "LM::LIR"; guard = "LM_LIR_FUNCTIONS_HH" }
    "builtin_functions.hh" = @{ ns = "LM::LIR"; guard = "LM_LIR_BUILTIN_FUNCTIONS_HH" }
    "types.hh" = @{ ns = "LM::LIR"; guard = "LM_LIR_TYPES_HH" }
    "function_registry.hh" = @{ ns = "LM::LIR"; guard = "LM_LIR_FUNCTION_REGISTRY_HH" }
    "formatter.hh" = @{ ns = "LM::Error"; guard = "LM_ERROR_FORMATTER_HH" }
    "code_generator.hh" = @{ ns = "LM::Error"; guard = "LM_ERROR_CODE_GENERATOR_HH" }
    "hint_provider.hh" = @{ ns = "LM::Error"; guard = "LM_ERROR_HINT_PROVIDER_HH" }
    "source_formatter.hh" = @{ ns = "LM::Error"; guard = "LM_ERROR_SOURCE_FORMATTER_HH" }
    "console_formatter.hh" = @{ ns = "LM::Error"; guard = "LM_ERROR_CONSOLE_FORMATTER_HH" }
    "catalog.hh" = @{ ns = "LM::Error"; guard = "LM_ERROR_CATALOG_HH" }
    "debugger.hh" = @{ ns = "LM::Debug"; guard = "LM_DEBUGGER_HH" }
}

function Add-NamespaceToHeader {
    param(
        [string]$FilePath,
        [string]$Namespace,
        [string]$Guard
    )
    
    if (-not (Test-Path $FilePath)) {
        Write-Host "✗ File not found: $FilePath" -ForegroundColor Red
        return $false
    }
    
    $content = Get-Content $FilePath -Raw
    
    # Check if already has namespace
    if ($content -match "namespace LM\s*\{") {
        Write-Host "⏭️  Already has namespace: $FilePath" -ForegroundColor Cyan
        return $false
    }
    
    # Parse namespace parts
    $nsParts = $Namespace -split "::"
    
    # Build namespace opening
    $nsOpen = ""
    foreach ($part in $nsParts) {
        $nsOpen += "namespace $part {`n"
    }
    
    # Build namespace closing
    $nsClose = ""
    for ($i = $nsParts.Count - 1; $i -ge 0; $i--) {
        $nsClose += "} // namespace $($nsParts[$i])`n"
    }
    
    # Replace header guard
    $content = $content -replace "#ifndef\s+\w+", "#ifndef $Guard"
    $content = $content -replace "#define\s+\w+\s+", "#define $Guard`n"
    
    # Find where to insert namespace (after includes)
    $lines = $content -split "`n"
    $insertPoint = 0
    
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -match "#include" -or $lines[$i] -match "^$") {
            $insertPoint = $i + 1
        } else {
            if ($lines[$i].Trim() -ne "" -and $lines[$i] -notmatch "#ifndef" -and $lines[$i] -notmatch "#define" -and $lines[$i] -notmatch "#include") {
                break
            }
        }
    }
    
    # Reconstruct content
    $before = $lines[0..($insertPoint - 1)] -join "`n"
    $after = $lines[$insertPoint..($lines.Count - 1)] -join "`n"
    
    # Remove old endif
    $after = $after -replace "#endif\s*//.*$", ""
    
    $newContent = "$before`n`n$nsOpen`n$after`n$nsClose`n#endif // $Guard`n"
    
    if (-not $DryRun) {
        Set-Content $FilePath $newContent -NoNewline -Encoding UTF8
        Write-Host "✓ Updated: $FilePath" -ForegroundColor Green
    } else {
        Write-Host "📝 Would update: $FilePath" -ForegroundColor Yellow
    }
    
    return $true
}

function Add-NamespaceToImpl {
    param(
        [string]$FilePath,
        [string]$Namespace,
        [string]$HeaderPath
    )
    
    if (-not (Test-Path $FilePath)) {
        Write-Host "✗ File not found: $FilePath" -ForegroundColor Red
        return $false
    }
    
    $content = Get-Content $FilePath -Raw
    
    # Check if already has namespace
    if ($content -match "namespace LM\s*\{") {
        Write-Host "⏭️  Already has namespace: $FilePath" -ForegroundColor Cyan
        return $false
    }
    
    # Parse namespace parts
    $nsParts = $Namespace -split "::"
    
    # Build namespace opening
    $nsOpen = ""
    foreach ($part in $nsParts) {
        $nsOpen += "namespace $part {`n"
    }
    
    # Build namespace closing
    $nsClose = ""
    for ($i = $nsParts.Count - 1; $i -ge 0; $i--) {
        $nsClose += "} // namespace $($nsParts[$i])`n"
    }
    
    # Update include path
    $content = $content -replace '#include\s+"[^"]*"', "#include `"$HeaderPath`""
    
    # Find where to insert namespace (after includes)
    $lines = $content -split "`n"
    $insertPoint = 0
    
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -match "#include") {
            $insertPoint = $i + 1
        } else {
            if ($lines[$i].Trim() -ne "" -and $lines[$i] -notmatch "#include") {
                break
            }
        }
    }
    
    # Reconstruct content
    $before = $lines[0..($insertPoint - 1)] -join "`n"
    $after = $lines[$insertPoint..($lines.Count - 1)] -join "`n"
    
    $newContent = "$before`n`n$nsOpen`n$after`n$nsClose`n"
    
    if (-not $DryRun) {
        Set-Content $FilePath $newContent -NoNewline -Encoding UTF8
        Write-Host "✓ Updated: $FilePath" -ForegroundColor Green
    } else {
        Write-Host "📝 Would update: $FilePath" -ForegroundColor Yellow
    }
    
    return $true
}

# Main execution
Write-Host "╔════════════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║  Applying Namespace Declarations                              ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

if ($DryRun) {
    Write-Host "🔍 DRY RUN MODE - No changes will be made" -ForegroundColor Yellow
    Write-Host ""
}

$updated = 0
$skipped = 0

# Process header files
Write-Host "Processing header files..." -ForegroundColor Cyan
$headerFiles = Get-ChildItem -Path "src/lm" -Recurse -Filter "*.hh" | Where-Object { $_.Name -ne "lm.hh" }

foreach ($file in $headerFiles) {
    $filename = $file.Name
    if ($namespaces.ContainsKey($filename)) {
        $config = $namespaces[$filename]
        if (Add-NamespaceToHeader -FilePath $file.FullName -Namespace $config.ns -Guard $config.guard) {
            $updated++
        } else {
            $skipped++
        }
    }
}

Write-Host ""
Write-Host "Summary:" -ForegroundColor Green
Write-Host "  Updated: $updated files" -ForegroundColor Green
Write-Host "  Skipped: $skipped files" -ForegroundColor Yellow
Write-Host ""

if ($DryRun) {
    Write-Host "✅ Dry run complete. Run without -DryRun to apply changes." -ForegroundColor Green
} else {
    Write-Host "✅ Namespace application complete!" -ForegroundColor Green
}
