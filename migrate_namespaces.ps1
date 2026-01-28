# PowerShell script to migrate namespaces to LM:: hierarchy
# This script updates header guards, includes, and namespace declarations

param(
    [switch]$DryRun = $false,
    [switch]$Verbose = $false
)

$ErrorActionPreference = "Stop"

# Mapping of old includes to new includes
$includeMap = @{
    '"frontend/scanner.hh"' = '"lm/frontend/scanner.hh"'
    '"frontend/parser.hh"' = '"lm/frontend/parser.hh"'
    '"frontend/ast.hh"' = '"lm/frontend/ast.hh"'
    '"frontend/ast_builder.hh"' = '"lm/frontend/ast_builder.hh"'
    '"frontend/type_checker.hh"' = '"lm/frontend/type_checker.hh"'
    '"frontend/memory_checker.hh"' = '"lm/frontend/memory_checker.hh"'
    '"frontend/ast_optimizer.hh"' = '"lm/frontend/ast_optimizer.hh"'
    '"frontend/cst.hh"' = '"lm/frontend/cst/node.hh"'
    '"frontend/cst_printer.hh"' = '"lm/frontend/cst/printer.hh"'
    '"frontend/cst_utils.hh"' = '"lm/frontend/cst/utils.hh"'
    '"backend/symbol_table.hh"' = '"lm/backend/symbol_table.hh"'
    '"backend/value.hh"' = '"lm/backend/value.hh"'
    '"backend/ast_printer.hh"' = '"lm/backend/ast_printer.hh"'
    '"backend/types.hh"' = '"lm/backend/types.hh"'
    '"backend/memory.hh"' = '"lm/backend/memory.hh"'
    '"backend/env.hh"' = '"lm/backend/env.hh"'
    '"backend/channel.hh"' = '"lm/backend/channel.hh"'
    '"backend/fiber.hh"' = '"lm/backend/fiber.hh"'
    '"backend/task.hh"' = '"lm/backend/task.hh"'
    '"backend/scheduler.hh"' = '"lm/backend/scheduler.hh"'
    '"backend/shared_cell.hh"' = '"lm/backend/shared_cell.hh"'
    '"backend/register_value.hh"' = '"lm/backend/register_value.hh"'
    '"backend/memory_analyzer.hh"' = '"lm/backend/memory_analyzer.hh"'
    '"backend/code_formatter.hh"' = '"lm/backend/code_formatter.hh"'
    '"backend/register/register.hh"' = '"lm/backend/vm/register.hh"'
    '"backend/jit/jit_backend.hh"' = '"lm/backend/jit/backend.hh"'
    '"backend/jit/jit.hh"' = '"lm/backend/jit/compiler.hh"'
    '"memory/model.hh"' = '"lm/memory/model.hh"'
    '"memory/compiler.hh"' = '"lm/memory/compiler.hh"'
    '"memory/runtime.hh"' = '"lm/memory/runtime.hh"'
    '"lir/lir.hh"' = '"lm/lir/instruction.hh"'
    '"lir/lir_utils.hh"' = '"lm/lir/utils.hh"'
    '"lir/generator.hh"' = '"lm/lir/generator.hh"'
    '"lir/functions.hh"' = '"lm/lir/functions.hh"'
    '"lir/builtin_functions.hh"' = '"lm/lir/builtin_functions.hh"'
    '"lir/lir_types.hh"' = '"lm/lir/types.hh"'
    '"lir/function_registry.hh"' = '"lm/lir/function_registry.hh"'
    '"error/error_formatter.hh"' = '"lm/error/formatter.hh"'
    '"error/error_code_generator.hh"' = '"lm/error/code_generator.hh"'
    '"error/contextual_hint_provider.hh"' = '"lm/error/hint_provider.hh"'
    '"error/source_code_formatter.hh"' = '"lm/error/source_formatter.hh"'
    '"error/console_formatter.hh"' = '"lm/error/console_formatter.hh"'
    '"error/error_catalog.hh"' = '"lm/error/catalog.hh"'
    '"error/error_handling.hh"' = '"lm/error/error_handling.hh"'
    '"error/error_message.hh"' = '"lm/error/error_message.hh"'
    '"error/enhanced_error_reporting.hh"' = '"lm/error/enhanced_error_reporting.hh"'
    '"error/ide_formatter.hh"' = '"lm/error/ide_formatter.hh"'
    '"common/debugger.hh"' = '"lm/debug/debugger.hh"'
}

function Update-File {
    param(
        [string]$FilePath,
        [string]$ComponentName,
        [string]$Namespace
    )
    
    if (-not (Test-Path $FilePath)) {
        Write-Host "⚠️  File not found: $FilePath" -ForegroundColor Yellow
        return
    }
    
    $content = Get-Content $FilePath -Raw
    $originalContent = $content
    
    # Update includes
    foreach ($oldInclude in $includeMap.Keys) {
        $newInclude = $includeMap[$oldInclude]
        $content = $content -replace [regex]::Escape("#include $oldInclude"), "#include $newInclude"
    }
    
    # Update header guard
    $oldGuard = $ComponentName.ToUpper() + "_H"
    $newGuard = "LM_" + $ComponentName.ToUpper() + "_HH"
    $content = $content -replace "#ifndef $oldGuard", "#ifndef $newGuard"
    $content = $content -replace "#define $oldGuard", "#define $newGuard"
    $content = $content -replace "#endif // $oldGuard", "#endif // $newGuard"
    
    if ($content -ne $originalContent) {
        if (-not $DryRun) {
            Set-Content $FilePath $content -NoNewline
            Write-Host "✓ Updated: $FilePath" -ForegroundColor Green
        } else {
            Write-Host "📝 Would update: $FilePath" -ForegroundColor Cyan
        }
    }
}

# Process all files in src/lm
Write-Host "Starting namespace migration..." -ForegroundColor Cyan
Write-Host ""

$files = @(
    @{ Path = "src/lm/frontend/scanner.hh"; Component = "SCANNER"; Namespace = "LM::Frontend" }
    @{ Path = "src/lm/frontend/parser.hh"; Component = "PARSER"; Namespace = "LM::Frontend" }
    @{ Path = "src/lm/frontend/ast.hh"; Component = "AST"; Namespace = "LM::Frontend" }
    @{ Path = "src/lm/frontend/ast_builder.hh"; Component = "AST_BUILDER"; Namespace = "LM::Frontend" }
    @{ Path = "src/lm/frontend/type_checker.hh"; Component = "TYPE_CHECKER"; Namespace = "LM::Frontend" }
    @{ Path = "src/lm/frontend/memory_checker.hh"; Component = "MEMORY_CHECKER"; Namespace = "LM::Frontend" }
    @{ Path = "src/lm/frontend/ast_optimizer.hh"; Component = "AST_OPTIMIZER"; Namespace = "LM::Frontend" }
    @{ Path = "src/lm/backend/symbol_table.hh"; Component = "SYMBOL_TABLE"; Namespace = "LM::Backend" }
    @{ Path = "src/lm/backend/value.hh"; Component = "VALUE"; Namespace = "LM::Backend" }
    @{ Path = "src/lm/backend/ast_printer.hh"; Component = "AST_PRINTER"; Namespace = "LM::Backend" }
    @{ Path = "src/lm/backend/types.hh"; Component = "TYPES"; Namespace = "LM::Backend" }
    @{ Path = "src/lm/lir/instruction.hh"; Component = "LIR"; Namespace = "LM::LIR" }
    @{ Path = "src/lm/lir/utils.hh"; Component = "LIR_UTILS"; Namespace = "LM::LIR" }
    @{ Path = "src/lm/lir/generator.hh"; Component = "GENERATOR"; Namespace = "LM::LIR" }
    @{ Path = "src/lm/error/formatter.hh"; Component = "ERROR_FORMATTER"; Namespace = "LM::Error" }
    @{ Path = "src/lm/debug/debugger.hh"; Component = "DEBUGGER"; Namespace = "LM::Debug" }
)

foreach ($file in $files) {
    Update-File -FilePath $file.Path -ComponentName $file.Component -Namespace $file.Namespace
}

Write-Host ""
if ($DryRun) {
    Write-Host "✅ Dry run complete. Use without -DryRun to apply changes." -ForegroundColor Green
} else {
    Write-Host "✅ Namespace migration complete!" -ForegroundColor Green
}
