/**
 * @file lm.hh
 * @brief Master header for the Limit Language compiler
 * 
 * This header includes all major components of the Limit language compiler
 * organized under the LM:: namespace hierarchy.
 */

#ifndef LM_HH
#define LM_HH

// ============================================================================
// Frontend Components
// ============================================================================

// Scanner and Parser
#include "frontend/scanner.hh"
#include "frontend/parser.hh"

// Concrete Syntax Tree (CST)
#include "frontend/cst/node.hh"
#include "frontend/cst/printer.hh"
#include "frontend/cst/utils.hh"

// Abstract Syntax Tree (AST)
#include "frontend/ast.hh"
#include "frontend/ast_builder.hh"

// Type Checking and Analysis
#include "frontend/type_checker.hh"
#include "frontend/memory_checker.hh"

// Optimization
#include "frontend/ast_optimizer.hh"

// ============================================================================
// Memory Management
// ============================================================================

#include "memory/model.hh"
#include "memory/compiler.hh"
#include "memory/runtime.hh"

// ============================================================================
// Backend Components
// ============================================================================

// Symbol Table and Values
#include "backend/symbol_table.hh"
#include "backend/value.hh"
#include "backend/types.hh"

// Memory Management (Backend utilities)
#include "backend/memory.hh"
#include "backend/env.hh"

// Concurrency Support
#include "backend/channel.hh"
#include "backend/fiber.hh"
#include "backend/task.hh"
#include "backend/scheduler.hh"
#include "backend/shared_cell.hh"

// Virtual Machine
#include "backend/vm/register.hh"

// JIT Compilation
#include "backend/jit/compiler.hh"
#include "backend/jit/backend.hh"

// Utilities
#include "backend/ast_printer.hh"
#include "backend/code_formatter.hh"

// ============================================================================
// LIR (Low-level Intermediate Representation)
// ============================================================================

#include "lir/instruction.hh"
#include "lir/utils.hh"
#include "lir/generator.hh"
#include "lir/functions.hh"
#include "lir/builtin_functions.hh"
#include "lir/types.hh"
#include "lir/function_registry.hh"

// ============================================================================
// Error Handling System
// ============================================================================

#include "error/formatter.hh"
#include "error/code_generator.hh"
#include "error/hint_provider.hh"
#include "error/source_formatter.hh"
#include "error/console_formatter.hh"
#include "error/catalog.hh"
#include "error/error_handling.hh"
#include "error/error_message.hh"
#include "error/enhanced_error_reporting.hh"
#include "error/ide_formatter.hh"

// ============================================================================
// Debug Support
// ============================================================================

#include "debug/debugger.hh"

#endif // LM_HH
