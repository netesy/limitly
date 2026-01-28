# Comprehensive script to update all files with namespaces
# This script handles both header and implementation files

param(
    [switch]$DryRun = $false
)

$ErrorActionPreference = "Continue"

# File mapping with namespace info
$files = @(
    # Frontend
    @{ path = "src/lm/frontend/scanner.hh"; ns = "LM::Frontend"; guard = "LM_SCANNER_HH" }
    @{ path = "src/lm/frontend/scanner.cpp"; ns = "LM::Frontend"; include = "lm/frontend/scanner.hh" }
    @{ path = "src/lm/frontend/parser.hh"; ns = "LM::Frontend"; guard = "LM_PARSER_HH" }
    @{ path = "src/lm/frontend/parser.cpp"; ns = "LM::Frontend"; include = "lm/frontend/parser.hh" }
    @{ path = "src/lm/frontend/ast.hh"; ns = "LM::Frontend"; guard = "LM_AST_HH" }
    @{ path = "src/lm/frontend/ast_builder.hh"; ns = "LM::Frontend"; guard = "LM_AST_BUILDER_HH" }
    @{ path = "src/lm/frontend/ast_builder.cpp"; ns = "LM::Frontend"; include = "lm/frontend/ast_builder.hh" }
    @{ path = "src/lm/frontend/type_checker.hh"; ns = "LM::Frontend"; guard = "LM_TYPE_CHECKER_HH" }
    @{ path = "src/lm/frontend/type_checker.cpp"; ns = "LM::Frontend"; include = "lm/frontend/type_checker.hh" }
    @{ path = "src/lm/frontend/memory_checker.hh"; ns = "LM::Frontend"; guard = "LM_MEMORY_CHECKER_HH" }
    @{ path = "src/lm/frontend/memory_checker.cpp"; ns = "LM::Frontend"; include = "lm/frontend/memory_checker.hh" }
    @{ path = "src/lm/frontend/ast_optimizer.hh"; ns = "LM::Frontend"; guard = "LM_AST_OPTIMIZER_HH" }
    @{ path = "src/lm/frontend/ast_optimizer.cpp"; ns = "LM::Frontend"; include = "lm/frontend/ast_optimizer.hh" }
    
    # Frontend CST
    @{ path = "src/lm/frontend/cst/node.hh"; ns = "LM::Frontend::CST"; guard = "LM_CST_NODE_HH" }
    @{ path = "src/lm/frontend/cst/node.cpp"; ns = "LM::Frontend::CST"; include = "lm/frontend/cst/node.hh" }
    @{ path = "src/lm/frontend/cst/printer.hh"; ns = "LM::Frontend::CST"; guard = "LM_CST_PRINTER_HH" }
    @{ path = "src/lm/frontend/cst/printer.cpp"; ns = "LM::Frontend::CST"; include = "lm/frontend/cst/printer.hh" }
    @{ path = "src/lm/frontend/cst/utils.hh"; ns = "LM::Frontend::CST"; guard = "LM_CST_UTILS_HH" }
    @{ path = "src/lm/frontend/cst/utils.cpp"; ns = "LM::Frontend::CST"; include = "lm/frontend/cst/utils.hh" }
    
    # Backend
    @{ path = "src/lm/backend/symbol_table.hh"; ns = "LM::Backend"; guard = "LM_SYMBOL_TABLE_HH" }
    @{ path = "src/lm/backend/symbol_table.cpp"; ns = "LM::Backend"; include = "lm/backend/symbol_table.hh" }
    @{ path = "src/lm/backend/value.hh"; ns = "LM::Backend"; guard = "LM_VALUE_HH" }
    @{ path = "src/lm/backend/value.cpp"; ns = "LM::Backend"; include = "lm/backend/value.hh" }
    @{ path = "src/lm/backend/ast_printer.hh"; ns = "LM::Backend"; guard = "LM_AST_PRINTER_HH" }
    @{ path = "src/lm/backend/ast_printer.cpp"; ns = "LM::Backend"; include = "lm/backend/ast_printer.hh" }
    
    # Backend VM
    @{ path = "src/lm/backend/vm/register.hh"; ns = "LM::Backend::VM"; guard = "LM_REGISTER_HH" }
    @{ path = "src/lm/backend/vm/register.cpp"; ns = "LM::Backend::VM"; include = "lm/backend/vm/register.hh" }
    
    # Backend JIT
    @{ path = "src/lm/backend/jit/backend.hh"; ns = "LM::Backend::JIT"; guard = "LM_JIT_BACKEND_HH" }
    @{ path = "src/lm/backend/jit/backend.cpp"; ns = "LM::Backend::JIT"; include = "lm/backend/jit/backend.hh" }
    @{ path = "src/lm/backend/jit/compiler.hh"; ns = "LM::Backend::JIT"; guard = "LM_JIT_COMPILER_HH" }
    @{ path = "src/lm/backend/jit/compiler.cpp"; ns = "LM::Backend::JIT"; include = "lm/backend/jit/compiler.hh" }
    
    # Memory
    @{ path = "src/lm/memory/model.hh"; ns = "LM::Memory"; guard = "LM_MEMORY_MODEL_HH" }
    @{ path = "src/lm/memory/compiler.hh"; ns = "LM::Memory"; guard = "LM_MEMORY_COMPILER_HH" }
    @{ path = "src/lm/memory/runtime.hh"; ns = "LM::Memory"; guard = "LM_MEMORY_RUNTIME_HH" }
    
    # LIR
    @{ path = "src/lm/lir/instruction.hh"; ns = "LM::LIR"; guard = "LM_LIR_INSTRUCTION_HH" }
    @{ path = "src/lm/lir/instruction.cpp"; ns = "LM::LIR"; include = "lm/lir/instruction.hh" }
    @{ path = "src/lm/lir/utils.hh"; ns = "LM::LIR"; guard = "LM_LIR_UTILS_HH" }
    @{ path = "src/lm/lir/utils.cpp"; ns = "LM::LIR"; include = "lm/lir/utils.hh" }
    @{ path = "src/lm/lir/generator.hh"; ns = "LM::LIR"; guard = "LM_LIR_GENERATOR_HH" }
    @{ path = "src/lm/lir/generator.cpp"; ns = "LM::LIR"; include = "lm/lir/generator.hh" }
    @{ path = "src/lm/lir/functions.hh"; ns = "LM::LIR"; guard = "LM_LIR_FUNCTIONS_HH" }
    @{ path = "src/lm/lir/functions.cpp"; ns = "LM::LIR"; include = "lm/lir/functions.hh" }
    @{ path = "src/lm/lir/builtin_functions.hh"; ns = "LM::LIR"; guard = "LM_LIR_BUILTIN_FUNCTIONS_HH" }
    @{ path = "src/lm/lir/builtin_functions.cpp"; ns = "LM::LIR"; include = "lm/lir/builtin_functions.hh" }
    @{ path = "src/lm/lir/types.hh"; ns = "LM::LIR"; guard = "LM_LIR_TYPES_HH" }
    @{ path = "src/lm/lir/types.cpp"; ns = "LM::LIR"; include = "lm/lir/types.hh" }
    @{ path = "src/lm/lir/function_registry.hh"; ns = "LM::LIR"; guard = "LM_LIR_FUNCTION_REGISTRY_HH" }
    @{ path = "src/lm/lir/function_registry.cpp"; ns = "LM::LIR"; include = "lm/lir/function_registry.hh" }
    
    # Error
    @{ path = "src/lm/error/formatter.hh"; ns = "LM::Error"; guard = "LM_ERROR_FORMATTER_HH" }
    @{ path = "src/lm/error/formatter.cpp"; ns = "LM::Error"; include = "lm/error/formatter.hh" }
    @{ path = "src/lm/error/code_generator.hh"; ns = "LM::Error"; guard = "LM_ERROR_CODE_GENERATOR_HH" }
    @{ path = "src/lm/error/code_generator.cpp"; ns = "LM::Error"; include = "lm/error/code_generator.hh" }
    @{ path = "src/lm/error/hint_provider.hh"; ns = "LM::Error"; guard = "LM_ERROR_HINT_PROVIDER_HH" }
    @{ path = "src/lm/error/hint_provider.cpp"; ns = "LM::Error"; include = "lm/error/hint_provider.hh" }
    @{ path = "src/lm/error/source_formatter.hh"; ns = "LM::Error"; guard = "LM_ERROR_SOURCE_FORMATTER_HH" }
    @{ path = "src/lm/error/source_formatter.cpp"; ns = "LM::Error"; include = "lm/error/source_formatter.hh" }
    @{ path = "src/lm/error/console_formatter.hh"; ns = "LM::Error"; guard = "LM_ERROR_CONSOLE_FORMATTER_HH" }
    @{ path = "src/lm/error/console_formatter.cpp"; ns = "LM::Error"; include = "lm/error/console_formatter.hh" }
    @{ path = "src/lm/error/catalog.hh"; ns = "LM::Error"; guard = "LM_ERROR_CATALOG_HH" }
    @{ path = "src/lm/error/catalog.cpp"; ns = "LM::Error"; include = "lm/error/catalog.hh" }
    
    # Debug
    @{ path = "src/lm/debug/debugger.hh"; ns = "LM::Debug"; guard = "LM_DEBUGGER_HH" }
    @{ path = "src/lm/debug/debugger.cpp"; ns = "LM::Debug"; include = "lm/debug/debugger.hh" }
)

function Update-File {
    param(
        [hashtable]$FileInfo,
        [bool]$DryRun
    )
    
    $path = $FileInfo.path
    $ns = $FileInfo.ns
    
    if (-not (Test-Path $path)) {
        Write-Host "⚠️  Not found: $path" -ForegroundColor Yellow
        return $false
    }
    
    $content = Get-Content $path -Raw
    
    # Check if already has namespace
    if ($content -match "namespace LM") {
        Write-Host "⏭️  Already updated: $path" -ForegroundColor Cyan
        return $false
    }
    
    if ($path -match "\.hh$") {
        # Header file
        $guard = $FileInfo.guard
        
        # Extract namespace parts
        $nsParts = $ns -split "::"
        $nsOpen = ($nsParts | ForEach-Object { "namespace $_ {" }) -join "`n"
        $nsClose = ($nsParts | ForEach-Object { "} // namespace $_" }) -join "`n"
        
        # Remove old header guard
        $content = $content -replace "#ifndef\s+\w+_H\s*\n#define\s+\w+_H", "#ifndef $guard`n#define $guard"
        $content = $content -replace "#endif\s*//\s*\w+_H\s*$", ""
        
        # Add namespace after includes
        $lines = $content -split "`n"
        $lastIncludeLine = -1
        for ($i = 0; $i -lt $lines.Count; $i++) {
            if ($lines[$i] -match "#include") {
                $lastIncludeLine = $i
            }
        }
        
        if ($lastIncludeLine -ge 0) {
            $before = $lines[0..$lastIncludeLine] -join "`n"
            $after = $lines[($lastIncludeLine + 1)..($lines.Count - 1)] -join "`n"
            $content = "$before`n`n$nsOpen`n`n$after`n`n$nsClose`n`n#endif // $guard`n"
        }
    } else {
        # Implementation file
        $include = $FileInfo.include
        
        # Extract namespace parts
        $nsParts = $ns -split "::"
        $nsOpen = ($nsParts | ForEach-Object { "namespace $_ {" }) -join "`n"
        $nsClose = ($nsParts | ForEach-Object { "} // namespace $_" }) -join "`n"
        
        # Update include path
        $content = $content -replace "#include\s+[""<].*?["">\s]", "#include `"$include`""
        
        # Add namespace after includes
        $lines = $content -split "`n"
        $lastIncludeLine = -1
        for ($i = 0; $i -lt $lines.Count; $i++) {
            if ($lines[$i] -match "#include") {
                $lastIncludeLine = $i
            }
        }
        
        if ($lastIncludeLine -ge 0) {
            $before = $lines[0..$lastIncludeLine] -join "`n"
            $after = $lines[($lastIncludeLine + 1)..($lines.Count - 1)] -join "`n"
            $content = "$before`n`n$nsOpen`n`n$after`n`n$nsClose`n"
        }
    }
    
    if (-not $DryRun) {
        Set-Content $path $content -NoNewline
        Write-Host "✓ Updated: $path" -ForegroundColor Green
    } else {
        Write-Host "📝 Would update: $path" -ForegroundColor Cyan
    }
    
    return $true
}

# Main execution
Write-Host "╔════════════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║  Updating all files with namespace declarations               ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

$updated = 0
$skipped = 0
$notfound = 0

foreach ($file in $files) {
    $result = Update-File -FileInfo $file -DryRun $DryRun
    if ($result -eq $true) {
        $updated++
    } elseif ($result -eq $false) {
        if (Test-Path $file.path) {
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
Write-Host "  Updated: $updated files" -ForegroundColor Green
Write-Host "  Skipped: $skipped files (already updated)" -ForegroundColor Yellow
Write-Host "  Not found: $notfound files" -ForegroundColor Red
Write-Host ""

if ($DryRun) {
    Write-Host "✅ Dry run complete. Run without -DryRun to apply changes." -ForegroundColor Green
} else {
    Write-Host "✅ Namespace update complete!" -ForegroundColor Green
}
