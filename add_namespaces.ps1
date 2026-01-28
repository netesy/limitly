# PowerShell script to add namespace declarations to all LM files
# This script wraps file contents in appropriate namespace declarations

param(
    [switch]$DryRun = $false,
    [switch]$Verbose = $false
)

$ErrorActionPreference = "Stop"

# Mapping of files to their namespaces
$namespaceMap = @{
    # Frontend
    "src/lm/frontend/scanner.hh" = @{ ns = "LM::Frontend"; type = "header" }
    "src/lm/frontend/scanner.cpp" = @{ ns = "LM::Frontend"; type = "impl" }
    "src/lm/frontend/parser.hh" = @{ ns = "LM::Frontend"; type = "header" }
    "src/lm/frontend/parser.cpp" = @{ ns = "LM::Frontend"; type = "impl" }
    "src/lm/frontend/ast.hh" = @{ ns = "LM::Frontend"; type = "header" }
    "src/lm/frontend/ast_builder.hh" = @{ ns = "LM::Frontend"; type = "header" }
    "src/lm/frontend/ast_builder.cpp" = @{ ns = "LM::Frontend"; type = "impl" }
    "src/lm/frontend/type_checker.hh" = @{ ns = "LM::Frontend"; type = "header" }
    "src/lm/frontend/type_checker.cpp" = @{ ns = "LM::Frontend"; type = "impl" }
    "src/lm/frontend/memory_checker.hh" = @{ ns = "LM::Frontend"; type = "header" }
    "src/lm/frontend/memory_checker.cpp" = @{ ns = "LM::Frontend"; type = "impl" }
    "src/lm/frontend/ast_optimizer.hh" = @{ ns = "LM::Frontend"; type = "header" }
    "src/lm/frontend/ast_optimizer.cpp" = @{ ns = "LM::Frontend"; type = "impl" }
    
    # Frontend CST
    "src/lm/frontend/cst/node.hh" = @{ ns = "LM::Frontend::CST"; type = "header" }
    "src/lm/frontend/cst/node.cpp" = @{ ns = "LM::Frontend::CST"; type = "impl" }
    "src/lm/frontend/cst/printer.hh" = @{ ns = "LM::Frontend::CST"; type = "header" }
    "src/lm/frontend/cst/printer.cpp" = @{ ns = "LM::Frontend::CST"; type = "impl" }
    "src/lm/frontend/cst/utils.hh" = @{ ns = "LM::Frontend::CST"; type = "header" }
    "src/lm/frontend/cst/utils.cpp" = @{ ns = "LM::Frontend::CST"; type = "impl" }
    
    # Backend
    "src/lm/backend/symbol_table.hh" = @{ ns = "LM::Backend"; type = "header" }
    "src/lm/backend/symbol_table.cpp" = @{ ns = "LM::Backend"; type = "impl" }
    "src/lm/backend/value.hh" = @{ ns = "LM::Backend"; type = "header" }
    "src/lm/backend/value.cpp" = @{ ns = "LM::Backend"; type = "impl" }
    "src/lm/backend/ast_printer.hh" = @{ ns = "LM::Backend"; type = "header" }
    "src/lm/backend/ast_printer.cpp" = @{ ns = "LM::Backend"; type = "impl" }
    
    # Backend VM
    "src/lm/backend/vm/register.hh" = @{ ns = "LM::Backend::VM"; type = "header" }
    "src/lm/backend/vm/register.cpp" = @{ ns = "LM::Backend::VM"; type = "impl" }
    
    # Backend JIT
    "src/lm/backend/jit/backend.hh" = @{ ns = "LM::Backend::JIT"; type = "header" }
    "src/lm/backend/jit/backend.cpp" = @{ ns = "LM::Backend::JIT"; type = "impl" }
    "src/lm/backend/jit/compiler.hh" = @{ ns = "LM::Backend::JIT"; type = "header" }
    "src/lm/backend/jit/compiler.cpp" = @{ ns = "LM::Backend::JIT"; type = "impl" }
    
    # Memory
    "src/lm/memory/model.hh" = @{ ns = "LM::Memory"; type = "header" }
    "src/lm/memory/compiler.hh" = @{ ns = "LM::Memory"; type = "header" }
    "src/lm/memory/runtime.hh" = @{ ns = "LM::Memory"; type = "header" }
    
    # LIR
    "src/lm/lir/instruction.hh" = @{ ns = "LM::LIR"; type = "header" }
    "src/lm/lir/instruction.cpp" = @{ ns = "LM::LIR"; type = "impl" }
    "src/lm/lir/utils.hh" = @{ ns = "LM::LIR"; type = "header" }
    "src/lm/lir/utils.cpp" = @{ ns = "LM::LIR"; type = "impl" }
    "src/lm/lir/generator.hh" = @{ ns = "LM::LIR"; type = "header" }
    "src/lm/lir/generator.cpp" = @{ ns = "LM::LIR"; type = "impl" }
    "src/lm/lir/functions.hh" = @{ ns = "LM::LIR"; type = "header" }
    "src/lm/lir/functions.cpp" = @{ ns = "LM::LIR"; type = "impl" }
    "src/lm/lir/builtin_functions.hh" = @{ ns = "LM::LIR"; type = "header" }
    "src/lm/lir/builtin_functions.cpp" = @{ ns = "LM::LIR"; type = "impl" }
    "src/lm/lir/types.hh" = @{ ns = "LM::LIR"; type = "header" }
    "src/lm/lir/types.cpp" = @{ ns = "LM::LIR"; type = "impl" }
    "src/lm/lir/function_registry.hh" = @{ ns = "LM::LIR"; type = "header" }
    "src/lm/lir/function_registry.cpp" = @{ ns = "LM::LIR"; type = "impl" }
    
    # Error
    "src/lm/error/formatter.hh" = @{ ns = "LM::Error"; type = "header" }
    "src/lm/error/formatter.cpp" = @{ ns = "LM::Error"; type = "impl" }
    "src/lm/error/code_generator.hh" = @{ ns = "LM::Error"; type = "header" }
    "src/lm/error/code_generator.cpp" = @{ ns = "LM::Error"; type = "impl" }
    "src/lm/error/hint_provider.hh" = @{ ns = "LM::Error"; type = "header" }
    "src/lm/error/hint_provider.cpp" = @{ ns = "LM::Error"; type = "impl" }
    "src/lm/error/source_formatter.hh" = @{ ns = "LM::Error"; type = "header" }
    "src/lm/error/source_formatter.cpp" = @{ ns = "LM::Error"; type = "impl" }
    "src/lm/error/console_formatter.hh" = @{ ns = "LM::Error"; type = "header" }
    "src/lm/error/console_formatter.cpp" = @{ ns = "LM::Error"; type = "impl" }
    "src/lm/error/catalog.hh" = @{ ns = "LM::Error"; type = "header" }
    "src/lm/error/catalog.cpp" = @{ ns = "LM::Error"; type = "impl" }
    
    # Debug
    "src/lm/debug/debugger.hh" = @{ ns = "LM::Debug"; type = "header" }
    "src/lm/debug/debugger.cpp" = @{ ns = "LM::Debug"; type = "impl" }
}

function Get-HeaderGuardName {
    param([string]$FilePath, [string]$Namespace)
    
    $filename = Split-Path $FilePath -Leaf
    $name = $filename.ToUpper() -replace '\W', '_'
    return "LM_$name"
}

function Add-NamespaceToHeader {
    param(
        [string]$FilePath,
        [string]$Namespace,
        [string]$HeaderGuard
    )
    
    $content = Get-Content $FilePath -Raw
    
    # Check if already has namespace
    if ($content -match "namespace LM") {
        Write-Host "⚠️  Already has namespace: $FilePath" -ForegroundColor Yellow
        return $false
    }
    
    # Extract includes and other content
    $lines = $content -split "`n"
    $headerGuardLine = -1
    $defineGuardLine = -1
    $firstContentLine = -1
    
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -match "#ifndef") { $headerGuardLine = $i }
        if ($lines[$i] -match "#define" -and $headerGuardLine -ge 0 -and $defineGuardLine -lt 0) { $defineGuardLine = $i }
        if ($firstContentLine -lt 0 -and $i -gt $defineGuardLine -and $lines[$i].Trim() -ne "") { $firstContentLine = $i }
    }
    
    if ($firstContentLine -lt 0) { $firstContentLine = $defineGuardLine + 1 }
    
    # Build new content
    $newLines = @()
    
    # Add header guard
    $newLines += "#ifndef $HeaderGuard"
    $newLines += "#define $HeaderGuard"
    $newLines += ""
    
    # Add includes and other content before namespace
    for ($i = $defineGuardLine + 1; $i -lt $firstContentLine; $i++) {
        $newLines += $lines[$i]
    }
    
    # Add namespace opening
    $newLines += ""
    $nsparts = $Namespace -split "::"
    foreach ($ns in $nsparts) {
        $newLines += "namespace $ns {"
    }
    $newLines += ""
    
    # Add content
    for ($i = $firstContentLine; $i -lt $lines.Count - 1; $i++) {
        if ($lines[$i] -notmatch "#endif") {
            $newLines += $lines[$i]
        }
    }
    
    # Add namespace closing
    $newLines += ""
    for ($i = $nsparts.Count - 1; $i -ge 0; $i--) {
        $newLines += "} // namespace $($nsparts[$i])"
    }
    $newLines += ""
    $newLines += "#endif // $HeaderGuard"
    
    $newContent = $newLines -join "`n"
    
    if (-not $DryRun) {
        Set-Content $FilePath $newContent -NoNewline
        Write-Host "✓ Updated: $FilePath" -ForegroundColor Green
    } else {
        Write-Host "📝 Would update: $FilePath" -ForegroundColor Cyan
    }
    
    return $true
}

function Add-NamespaceToImpl {
    param(
        [string]$FilePath,
        [string]$Namespace
    )
    
    $content = Get-Content $FilePath -Raw
    
    # Check if already has namespace
    if ($content -match "namespace LM") {
        Write-Host "⚠️  Already has namespace: $FilePath" -ForegroundColor Yellow
        return $false
    }
    
    $lines = $content -split "`n"
    $firstIncludeLine = -1
    $firstContentLine = -1
    
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -match "#include" -and $firstIncludeLine -lt 0) { $firstIncludeLine = $i }
        if ($firstContentLine -lt 0 -and $i -gt $firstIncludeLine -and $lines[$i].Trim() -ne "" -and $lines[$i] -notmatch "#include") { 
            $firstContentLine = $i 
        }
    }
    
    if ($firstIncludeLine -lt 0) { $firstIncludeLine = 0 }
    if ($firstContentLine -lt 0) { $firstContentLine = $firstIncludeLine + 1 }
    
    # Build new content
    $newLines = @()
    
    # Add includes
    for ($i = 0; $i -lt $firstContentLine; $i++) {
        $newLines += $lines[$i]
    }
    
    # Add namespace opening
    $newLines += ""
    $nsparts = $Namespace -split "::"
    foreach ($ns in $nsparts) {
        $newLines += "namespace $ns {"
    }
    $newLines += ""
    
    # Add content
    for ($i = $firstContentLine; $i -lt $lines.Count; $i++) {
        $newLines += $lines[$i]
    }
    
    # Add namespace closing
    $newLines += ""
    for ($i = $nsparts.Count - 1; $i -ge 0; $i--) {
        $newLines += "} // namespace $($nsparts[$i])"
    }
    
    $newContent = $newLines -join "`n"
    
    if (-not $DryRun) {
        Set-Content $FilePath $newContent -NoNewline
        Write-Host "✓ Updated: $FilePath" -ForegroundColor Green
    } else {
        Write-Host "📝 Would update: $FilePath" -ForegroundColor Cyan
    }
    
    return $true
}

# Main execution
Write-Host "Starting namespace addition..." -ForegroundColor Cyan
Write-Host ""

$updated = 0
$skipped = 0

foreach ($file in $namespaceMap.Keys) {
    if (-not (Test-Path $file)) {
        Write-Host "⚠️  File not found: $file" -ForegroundColor Yellow
        continue
    }
    
    $config = $namespaceMap[$file]
    $ns = $config.ns
    $type = $config.type
    
    if ($type -eq "header") {
        $guard = Get-HeaderGuardName $file $ns
        if (Add-NamespaceToHeader -FilePath $file -Namespace $ns -HeaderGuard $guard) {
            $updated++
        } else {
            $skipped++
        }
    } else {
        if (Add-NamespaceToImpl -FilePath $file -Namespace $ns) {
            $updated++
        } else {
            $skipped++
        }
    }
}

Write-Host ""
if ($DryRun) {
    Write-Host "✅ Dry run complete. Use without -DryRun to apply changes." -ForegroundColor Green
} else {
    Write-Host "✅ Namespace addition complete!" -ForegroundColor Green
}
Write-Host "  Updated: $updated files"
Write-Host "  Skipped: $skipped files"
