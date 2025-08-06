#include "../backend.hh"
#include "../debugger.hh"
#include "value.hh"
#include <iostream>

void BytecodeGenerator::visitInterpolatedStringExpr(const std::shared_ptr<AST::InterpolatedStringExpr>& expr) {
    // For each part of the interpolated string
    for (const auto& part : expr->parts) {
        std::visit(overloaded {
            // Handle string literal parts
            [&](const std::string& str) {
                // Push the string literal onto the stack
                emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, str);
            },
            // Handle expression parts
            [&](const std::shared_ptr<AST::Expression>& expr) {
                // Evaluate the expression
                visitExpression(expr);
                
                // Convert the result to a string using CONCAT with an empty string
                // This is a common pattern to convert any value to a string
                emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, "");
                emit(Opcode::CONCAT, expr->line);
            }
        }, part);
    }
    
    // Now concatenate all parts using the INTERPOLATE_STRING opcode
    // The number of parts is passed as an operand
    emit(Opcode::INTERPOLATE_STRING, expr->line, static_cast<int32_t>(expr->parts.size()));
}

// BytecodeGenerator implementation
void BytecodeGenerator::process(const std::shared_ptr<AST::Program>& program) {
    // Process each statement in the program
    for (const auto& stmt : program->statements) {
        visitStatement(stmt);
    }
}

void BytecodeGenerator::visitStatement(const std::shared_ptr<AST::Statement>& stmt) {
    // Dispatch to the appropriate visitor method based on statement type
    if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        visitVarDeclaration(varDecl);
    } else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
        visitFunctionDeclaration(funcDecl);
    } else if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(stmt)) {
        visitClassDeclaration(classDecl);
    } else if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        visitBlockStatement(blockStmt);
    } else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        visitIfStatement(ifStmt);
    } else if (auto forStmt = std::dynamic_pointer_cast<AST::ForStatement>(stmt)) {
        visitForStatement(forStmt);
    } else if (auto whileStmt = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
        visitWhileStatement(whileStmt);
    } else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
        visitReturnStatement(returnStmt);
    } else if (auto printStmt = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
        visitPrintStatement(printStmt);
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        visitExprStatement(exprStmt);
    } else if (auto attemptStmt = std::dynamic_pointer_cast<AST::AttemptStatement>(stmt)) {
        visitAttemptStatement(attemptStmt);
    } else if (auto parallelStmt = std::dynamic_pointer_cast<AST::ParallelStatement>(stmt)) {
        visitParallelStatement(parallelStmt);
    } else if (auto concurrentStmt = std::dynamic_pointer_cast<AST::ConcurrentStatement>(stmt)) {
        visitConcurrentStatement(concurrentStmt);
    } else if (auto importStmt = std::dynamic_pointer_cast<AST::ImportStatement>(stmt)) {
        visitImportStatement(importStmt);
    } else if (auto enumDecl = std::dynamic_pointer_cast<AST::EnumDeclaration>(stmt)) {
        visitEnumDeclaration(enumDecl);
    } else if (auto matchStmt = std::dynamic_pointer_cast<AST::MatchStatement>(stmt)) {
        visitMatchStatement(matchStmt);
    } else if (auto typeDecl = std::dynamic_pointer_cast<AST::TypeDeclaration>(stmt)) {
        // Type declarations are handled during semantic analysis, so we can skip them during code generation
        // They don't generate any bytecode
        return;
    } else if (auto iterStmt = std::dynamic_pointer_cast<AST::IterStatement>(stmt)) {
        visitIterStatement(iterStmt);
    } else if (auto moduleDecl = std::dynamic_pointer_cast<AST::ModuleDeclaration>(stmt)) {
        visitModuleDeclaration(moduleDecl);
    } else if (auto contractStmt = std::dynamic_pointer_cast<AST::ContractStatement>(stmt)) {
        visitContractStatement(contractStmt);
    } else {
        Debugger::error("Unknown statement type", stmt->line, 0, InterpretationStage::BYTECODE, "", "", "");
    }
}

void BytecodeGenerator::visitExpression(const std::shared_ptr<AST::Expression>& expr) {
    // Dispatch to the appropriate visitor method based on expression type
    if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else if (auto unaryExpr = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        visitLiteralExpr(literalExpr);
    } else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        visitVariableExpr(varExpr);
    } else if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        visitCallExpr(callExpr);
    } else if (auto assignExpr = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) {
        visitAssignExpr(assignExpr);
    } else if (auto groupingExpr = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) {
        visitGroupingExpr(groupingExpr);
    } else if (auto listExpr = std::dynamic_pointer_cast<AST::ListExpr>(expr)) {
        visitListExpr(listExpr);
    } else if (auto dictExpr = std::dynamic_pointer_cast<AST::DictExpr>(expr)) {
        visitDictExpr(dictExpr);
    } else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
        visitIndexExpr(indexExpr);
    } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
        visitMemberExpr(memberExpr);
    } else if (auto awaitExpr = std::dynamic_pointer_cast<AST::AwaitExpr>(expr)) {
        visitAwaitExpr(awaitExpr);
    } else if (auto rangeExpr = std::dynamic_pointer_cast<AST::RangeExpr>(expr)) {
        visitRangeExpr(rangeExpr);
    } else if (auto thisExpr = std::dynamic_pointer_cast<AST::ThisExpr>(expr)) {
        // Handle 'this' reference - load the current instance
        emit(Opcode::LOAD_THIS, expr->line);
    } else if (auto superExpr = std::dynamic_pointer_cast<AST::SuperExpr>(expr)) {
        // Handle 'super' reference - load the parent instance
        emit(Opcode::LOAD_SUPER, expr->line);
    } else if (auto interpolatedStr = std::dynamic_pointer_cast<AST::InterpolatedStringExpr>(expr)) {
        visitInterpolatedStringExpr(interpolatedStr);
    } else {
        Debugger::error("Unknown expression type", expr->line, 0, InterpretationStage::BYTECODE, "", "", "");
    }
}

// Statement visitors
void BytecodeGenerator::visitVarDeclaration(const std::shared_ptr<AST::VarDeclaration>& stmt) {
    // Generate bytecode for variable declaration
    
    // If there's an initializer, evaluate it
    if (stmt->initializer) {
        visitExpression(stmt->initializer);
    } else {
        // Default initialization based on type
        if (stmt->type && *stmt->type) {
            if ((*stmt->type)->typeName == "int") {
                emit(Opcode::PUSH_INT, stmt->line, 0);
            } else if ((*stmt->type)->typeName == "float") {
                emit(Opcode::PUSH_FLOAT, stmt->line, 0, 0.0f);
            } else if ((*stmt->type)->typeName == "str") {
                emit(Opcode::PUSH_STRING, stmt->line, 0, 0.0f, false, "");
            } else if ((*stmt->type)->typeName == "bool") {
                emit(Opcode::PUSH_BOOL, stmt->line, 0, 0.0f, false);
            } else {
                emit(Opcode::PUSH_NULL, stmt->line);
            }
        } else {
            emit(Opcode::PUSH_NULL, stmt->line);
        }
    }
    
    // Store the value in a variable
    emit(Opcode::STORE_VAR, stmt->line, 0, 0.0f, false, stmt->name);
}

void BytecodeGenerator::visitFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    // Generate bytecode for function declaration
    
    // Start function definition
    emit(Opcode::BEGIN_FUNCTION, stmt->line, 0, 0.0f, false, stmt->name);
    
    // Process parameters
    for (const auto& param : stmt->params) {
        emit(Opcode::DEFINE_PARAM, stmt->line, 0, 0.0f, false, param.first);
    }
    
    for (const auto& param : stmt->optionalParams) {
        emit(Opcode::DEFINE_OPTIONAL_PARAM, stmt->line, 0, 0.0f, false, param.first);
        
        // If there's a default value, evaluate it
        if (param.second.second) {
            visitExpression(param.second.second);
            emit(Opcode::SET_DEFAULT_VALUE, stmt->line);
        }
    }
    
    // Process function body
    visitBlockStatement(stmt->body);
    
    // If function doesn't end with an explicit return, add implicit nil return
    // This ensures all functions return a value
    emit(Opcode::PUSH_NULL, stmt->line);
    emit(Opcode::RETURN, stmt->line);
    
    // End function definition
    emit(Opcode::END_FUNCTION, stmt->line);
}

void BytecodeGenerator::visitClassDeclaration(const std::shared_ptr<AST::ClassDeclaration>& stmt) {
    // Generate bytecode for class declaration
    
    // Start class definition
    emit(Opcode::BEGIN_CLASS, stmt->line, 0, 0.0f, false, stmt->name);
    
    // Set superclass if there's inheritance
    if (!stmt->superClassName.empty()) {
        emit(Opcode::SET_SUPERCLASS, stmt->line, 0, 0.0f, false, stmt->superClassName);
    }
    
    // Process fields
    for (const auto& field : stmt->fields) {
        // For class fields, generate DEFINE_FIELD instead of STORE_VAR
        if (field->initializer) {
            // Evaluate the default value
            visitExpression(field->initializer);
        } else {
            // No default value, push null
            emit(Opcode::PUSH_NULL, field->line);
        }
        
        // Define the field
        emit(Opcode::DEFINE_FIELD, field->line, 0, 0.0f, false, field->name);
    }
    
    // Process methods
    for (const auto& method : stmt->methods) {
        visitFunctionDeclaration(method);
    }
    
    // End class definition
    emit(Opcode::END_CLASS, stmt->line);
}

void BytecodeGenerator::visitBlockStatement(const std::shared_ptr<AST::BlockStatement>& stmt) {
    // Generate bytecode for block statement
    
    // Start block scope
    emit(Opcode::BEGIN_SCOPE, stmt->line);
    
    // Process each statement in the block
    for (const auto& statement : stmt->statements) {
        visitStatement(statement);
    }
    
    // End block scope
    emit(Opcode::END_SCOPE, stmt->line);
}

void BytecodeGenerator::visitIfStatement(const std::shared_ptr<AST::IfStatement>& stmt) {
    // Generate bytecode for if statement
    
    // Evaluate condition
    visitExpression(stmt->condition);
    
    // Jump to else branch if condition is false
    size_t jumpToElseIndex = bytecode.size();
    emit(Opcode::JUMP_IF_FALSE, stmt->line);
    
    // Process then branch
    visitStatement(stmt->thenBranch);
    
    // Jump over else branch
    size_t jumpOverElseIndex = bytecode.size();
    emit(Opcode::JUMP, stmt->line);
    
    // Update jump to else branch instruction - jump to start of else branch or end if no else
    size_t elseStartIndex = bytecode.size();
    bytecode[jumpToElseIndex].intValue = static_cast<int32_t>(elseStartIndex - jumpToElseIndex - 1);
    
    // Process else branch if it exists
    if (stmt->elseBranch) {
        visitStatement(stmt->elseBranch);
    }
    
    // Update jump over else branch instruction - jump to end of if statement
    size_t endIndex = bytecode.size();
    bytecode[jumpOverElseIndex].intValue = static_cast<int32_t>(endIndex - jumpOverElseIndex - 1);
}

void BytecodeGenerator::visitForStatement(const std::shared_ptr<AST::ForStatement>& stmt) {
    // Generate bytecode for for statement
    
    // Start loop scope
    emit(Opcode::BEGIN_SCOPE, stmt->line);
    
    if (stmt->isIterableLoop) {
        // Iterable-based for loop
        
        // Evaluate iterable
        visitExpression(stmt->iterable);
        
        // Get iterator
        emit(Opcode::GET_ITERATOR, stmt->line);
        
        // Start of loop
        size_t loopStartIndex = bytecode.size();
        
        // Check if iterator has next
        emit(Opcode::ITERATOR_HAS_NEXT, stmt->line);
        
        // Jump to end if no more items
        size_t jumpToEndIndex = bytecode.size();
        emit(Opcode::JUMP_IF_FALSE, stmt->line);
        
        // Get next item(s) from iterator
        if (stmt->loopVars.size() == 1) {
            // Single variable (key or value)
            emit(Opcode::ITERATOR_NEXT, stmt->line);
            emit(Opcode::STORE_VAR, stmt->line, 0, 0.0f, false, stmt->loopVars[0]);
        } else if (stmt->loopVars.size() == 2) {
            // Two variables (key and value)
            emit(Opcode::ITERATOR_NEXT_KEY_VALUE, stmt->line);
            emit(Opcode::STORE_VAR, stmt->line, 0, 0.0f, false, stmt->loopVars[0]); // Store key
            emit(Opcode::STORE_VAR, stmt->line, 0, 0.0f, false, stmt->loopVars[1]); // Store value
        }
        
        // Process loop body
        visitStatement(stmt->body);
        
        // Jump back to start of loop
        emit(Opcode::JUMP, stmt->line, static_cast<int32_t>(loopStartIndex) - static_cast<int32_t>(bytecode.size()) - 1);
        
        // Update jump to end instruction
        size_t endIndex = bytecode.size();
        bytecode[jumpToEndIndex].intValue = static_cast<int32_t>(endIndex - jumpToEndIndex - 1);
    } else {
        // Traditional for loop
        
        // Process initializer if it exists
        if (stmt->initializer) {
            visitStatement(stmt->initializer);
        }
        
        // Start of loop
        size_t loopStartIndex = bytecode.size();
        
        // Evaluate condition if it exists
        if (stmt->condition) {
            visitExpression(stmt->condition);
        } else {
            // If no condition, use true
            emit(Opcode::PUSH_BOOL, stmt->line, 0, 0.0f, true);
        }
        
        // Jump to end if condition is false
        size_t jumpToEndIndex = bytecode.size();
        emit(Opcode::JUMP_IF_FALSE, stmt->line);
        
        // Process loop body
        visitStatement(stmt->body);
        
        // Process increment if it exists
        if (stmt->increment) {
            visitExpression(stmt->increment);
            emit(Opcode::POP, stmt->line); // Discard result of increment expression
        }
        
        // Jump back to start of loop
        emit(Opcode::JUMP, stmt->line, static_cast<int32_t>(loopStartIndex) - static_cast<int32_t>(bytecode.size()) - 1);
        
        // Update jump to end instruction
        size_t endIndex = bytecode.size();
        bytecode[jumpToEndIndex].intValue = static_cast<int32_t>(endIndex - jumpToEndIndex - 1);
    }
    
    // End loop scope
    emit(Opcode::END_SCOPE, stmt->line);
}

void BytecodeGenerator::visitWhileStatement(const std::shared_ptr<AST::WhileStatement>& stmt) {
    // Generate bytecode for while statement
    
    // Start of loop
    size_t loopStartIndex = bytecode.size();
    
    // Evaluate condition
    visitExpression(stmt->condition);
    
    // Jump to end if condition is false
    size_t jumpToEndIndex = bytecode.size();
    emit(Opcode::JUMP_IF_FALSE, stmt->line);
    
    // Process loop body
    visitStatement(stmt->body);
    
    // Jump back to start of loop
    emit(Opcode::JUMP, stmt->line, static_cast<int32_t>(loopStartIndex) - static_cast<int32_t>(bytecode.size()) - 1);
    
    // Update jump to end instruction
    size_t endIndex = bytecode.size();
    bytecode[jumpToEndIndex].intValue = static_cast<int32_t>(endIndex - jumpToEndIndex - 1);
}

void BytecodeGenerator::visitReturnStatement(const std::shared_ptr<AST::ReturnStatement>& stmt) {
    // Generate bytecode for return statement
    
    // Evaluate return value if it exists
    if (stmt->value) {
        visitExpression(stmt->value);
    } else {
        // If no return value, return null
        emit(Opcode::PUSH_NULL, stmt->line);
    }
    
    // Return from function
    emit(Opcode::RETURN, stmt->line);
}

void BytecodeGenerator::visitPrintStatement(const std::shared_ptr<AST::PrintStatement>& stmt) {
    // Generate bytecode for print statement
    
    // Evaluate each argument
    for (const auto& arg : stmt->arguments) {
        visitExpression(arg);
    }
    
    // Print the values
    emit(Opcode::PRINT, stmt->line, stmt->arguments.size());
}

void BytecodeGenerator::visitExprStatement(const std::shared_ptr<AST::ExprStatement>& stmt) {
    // Generate bytecode for expression statement
    
    // Evaluate the expression
    visitExpression(stmt->expression);
    
    // Discard the result
    emit(Opcode::POP, stmt->line);
}

void BytecodeGenerator::visitAttemptStatement(const std::shared_ptr<AST::AttemptStatement>& stmt) {
    // Generate bytecode for attempt-handle statement
    
    // Start try block
    emit(Opcode::BEGIN_TRY, stmt->line);
    
    // Process try block
    visitBlockStatement(stmt->tryBlock);
    
    // Jump over handlers if no exception
    size_t jumpOverHandlersIndex = bytecode.size();
    emit(Opcode::JUMP, stmt->line);
    
    // Process handlers
    for (const auto& handler : stmt->handlers) {
        // Start handler
        emit(Opcode::BEGIN_HANDLER, stmt->line, 0, 0.0f, false, handler.errorType);
        
        // Store error in variable if specified
        if (!handler.errorVar.empty()) {
            emit(Opcode::STORE_EXCEPTION, stmt->line, 0, 0.0f, false, handler.errorVar);
        }
        
        // Process handler body
        visitBlockStatement(handler.body);
        
        // End handler
        emit(Opcode::END_HANDLER, stmt->line);
    }
    
    // Update jump over handlers instruction
    size_t endIndex = bytecode.size();
    bytecode[jumpOverHandlersIndex].intValue = static_cast<int32_t>(endIndex - jumpOverHandlersIndex - 1);
    
    // End try block
    emit(Opcode::END_TRY, stmt->line);
}

void BytecodeGenerator::visitParallelStatement(const std::shared_ptr<AST::ParallelStatement>& stmt) {
    // Generate bytecode for parallel statement
    
    // Start parallel block
    emit(Opcode::BEGIN_PARALLEL, stmt->line);
    
    // Process parallel block body
    visitBlockStatement(stmt->body);
    
    // End parallel block
    emit(Opcode::END_PARALLEL, stmt->line);
}

void BytecodeGenerator::visitConcurrentStatement(const std::shared_ptr<AST::ConcurrentStatement>& stmt) {
    // Generate bytecode for concurrent statement
    
    // Start concurrent block
    emit(Opcode::BEGIN_CONCURRENT, stmt->line);
    
    // Process concurrent block body
    visitBlockStatement(stmt->body);
    
    // End concurrent block
    emit(Opcode::END_CONCURRENT, stmt->line);
}

void BytecodeGenerator::visitImportStatement(const std::shared_ptr<AST::ImportStatement>& stmt) {
    // Generate bytecode for import statement
    emit(Opcode::IMPORT, stmt->line, 0, 0.0f, false, stmt->module);
}

void BytecodeGenerator::visitEnumDeclaration(const std::shared_ptr<AST::EnumDeclaration>& stmt) {
    // Generate bytecode for enum declaration
    
    // Start enum definition
    emit(Opcode::BEGIN_ENUM, stmt->line, 0, 0.0f, false, stmt->name);
    
    // Process enum variants
    for (const auto& variant : stmt->variants) {
        if (variant.second && *variant.second) {
            // Variant with type
            emit(Opcode::DEFINE_ENUM_VARIANT_WITH_TYPE, stmt->line, 0, 0.0f, false, variant.first);
        } else {
            // Simple variant
            emit(Opcode::DEFINE_ENUM_VARIANT, stmt->line, 0, 0.0f, false, variant.first);
        }
    }
    
    // End enum definition
    emit(Opcode::END_ENUM, stmt->line);
}

void BytecodeGenerator::visitMatchStatement(const std::shared_ptr<AST::MatchStatement>& stmt) {
    // Generate bytecode for match statement
    
    // Evaluate the value to match
    visitExpression(stmt->value);
    
    // Store the value in a temporary variable
    emit(Opcode::STORE_TEMP, stmt->line);
    
    // Process each case
    std::vector<size_t> jumpToEndIndices;
    
    for (const auto& matchCase : stmt->cases) {
        // Duplicate the value to match
        emit(Opcode::LOAD_TEMP, stmt->line);
        
        // Evaluate the pattern
        visitExpression(matchCase.pattern);
        
        // Compare the value with the pattern
        emit(Opcode::MATCH_PATTERN, stmt->line);
        
        // Jump to next case if pattern doesn't match
        size_t jumpToNextCaseIndex = bytecode.size();
        emit(Opcode::JUMP_IF_FALSE, stmt->line);
        
        // Process case body
        visitStatement(matchCase.body);
        
        // Jump to end after executing case body
        jumpToEndIndices.push_back(bytecode.size());
        emit(Opcode::JUMP, stmt->line);
        
        // Update jump to next case instruction
        size_t nextCaseIndex = bytecode.size();
        bytecode[jumpToNextCaseIndex].intValue = static_cast<int32_t>(nextCaseIndex - jumpToNextCaseIndex - 1);
    }
    
    // Update all jump to end instructions
    size_t endIndex = bytecode.size();
    for (size_t index : jumpToEndIndices) {
        bytecode[index].intValue = static_cast<int32_t>(endIndex - index - 1);
    }
    
    // Clean up temporary variable
    emit(Opcode::CLEAR_TEMP, stmt->line);
}

// Expression visitors
void BytecodeGenerator::visitBinaryExpr(const std::shared_ptr<AST::BinaryExpr>& expr) {
    // For compound assignment operators, we need to handle them specially
    // by first evaluating the left-hand side as an lvalue
    bool isCompoundAssignment = false;
    TokenType baseOp = expr->op;
    
    // Handle compound assignment operators by converting them to their base form
    switch (expr->op) {
        case TokenType::PLUS_EQUAL:   baseOp = TokenType::PLUS;   isCompoundAssignment = true; break;
        case TokenType::MINUS_EQUAL:  baseOp = TokenType::MINUS;  isCompoundAssignment = true; break;
        case TokenType::STAR_EQUAL:   baseOp = TokenType::STAR;   isCompoundAssignment = true; break;
        case TokenType::SLASH_EQUAL:  baseOp = TokenType::SLASH;  isCompoundAssignment = true; break;
        case TokenType::MODULUS_EQUAL:baseOp = TokenType::MODULUS;isCompoundAssignment = true; break;
        default: break;
    }
    
    // For compound assignments, we need to evaluate the left-hand side twice:
    // 1. First as an lvalue (to get the address for assignment)
    // 2. Then as an rvalue (to get the current value)
    if (isCompoundAssignment) {
        // Evaluate the left-hand side as an lvalue first
        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->left)) {
            // For simple variables, just emit a LOAD for the current value
            // First load the variable value
            visitVariableExpr(varExpr);
        } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr->left)) {
            // For member expressions, evaluate the object and member name
            visitExpression(memberExpr->object);
            // For member expressions, we'll just load the value for now
            // The VM will need to handle the actual member access
            visitExpression(memberExpr);
        } else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(expr->left)) {
            // For index expressions, we'll just load the value for now
            // The VM will need to handle the actual index access
            visitExpression(indexExpr);
        }
        
        // Now evaluate the left-hand side as an rvalue
        visitExpression(expr->left);
    } else {
        // Normal binary expression, just evaluate both operands
        visitExpression(expr->left);
    }
    
    // Evaluate the right-hand side
    visitExpression(expr->right);
    
    // Perform operation based on operator type
    switch (baseOp) {
        // Arithmetic operators
        case TokenType::PLUS:
            emit(Opcode::ADD, expr->line);
            break;
        case TokenType::MINUS:
            emit(Opcode::SUBTRACT, expr->line);
            break;
        case TokenType::STAR:
            emit(Opcode::MULTIPLY, expr->line);
            break;
        case TokenType::SLASH:
            emit(Opcode::DIVIDE, expr->line);
            break;
        case TokenType::MODULUS:
            emit(Opcode::MODULO, expr->line);
            break;
        case TokenType::POWER:
            emit(Opcode::POWER, expr->line);
            break;
            
        // Comparison operators
        case TokenType::EQUAL_EQUAL:
            emit(Opcode::EQUAL, expr->line);
            break;
        case TokenType::BANG_EQUAL:
            emit(Opcode::NOT_EQUAL, expr->line);
            break;
        case TokenType::LESS:
            emit(Opcode::LESS, expr->line);
            break;
        case TokenType::LESS_EQUAL:
            emit(Opcode::LESS_EQUAL, expr->line);
            break;
        case TokenType::GREATER:
            emit(Opcode::GREATER, expr->line);
            break;
        case TokenType::GREATER_EQUAL:
            emit(Opcode::GREATER_EQUAL, expr->line);
            break;
            
        // Logical operators
        case TokenType::AND:
            emit(Opcode::AND, expr->line);
            break;
        case TokenType::OR:
            emit(Opcode::OR, expr->line);
            break;
            
        // Bitwise operators
        // case TokenType::AMPERSAND:
        //     emit(Opcode::BIT_AND, expr->line);
        //     break;
        // case TokenType::PIPE:
        //     emit(Opcode::BIT_OR, expr->line);
        //     break;
        // case TokenType::CARET:
        //     emit(Opcode::BIT_XOR, expr->line);
        //     break;
        // case TokenType::LESS_LESS:
        //     emit(Opcode::BIT_SHL, expr->line);
        //     break;
        // case TokenType::GREATER_GREATER:
        //     emit(Opcode::BIT_SHR, expr->line);
        //     break;
            
        default:
            Debugger::error("Unsupported binary operator", expr->line, 0, InterpretationStage::BYTECODE, "", "", "");
            return;
    }
    
    // For compound assignments, store the result back to the lvalue
    if (isCompoundAssignment) {
        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->left)) {
            // For simple variables, emit a STORE_VAR
            emit(Opcode::STORE_VAR, expr->line, 0, 0.0f, false, varExpr->name);
        } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr->left)) {
            // For member expressions, we'll just use the member expression directly
            // The VM will need to handle the actual member store
            visitExpression(memberExpr);
            emit(Opcode::STORE_MEMBER, expr->line, 0, 0.0f, false, memberExpr->name);
        } else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(expr->left)) {
            // For index expressions, we'll just use the index expression directly
            // The VM will need to handle the actual index store
            visitExpression(indexExpr);
            emit(Opcode::SET_INDEX, expr->line);
        }
    }
}

void BytecodeGenerator::visitUnaryExpr(const std::shared_ptr<AST::UnaryExpr>& expr) {
    // Generate bytecode for unary expression
    
    // Evaluate operand
    visitExpression(expr->right);
    
    // Perform operation based on operator type
    switch (expr->op) {
        case TokenType::MINUS:
            emit(Opcode::NEGATE, expr->line);
            break;
        case TokenType::PLUS:
            // Unary plus is a no-op, value is already on stack
            break;
        case TokenType::BANG:
            emit(Opcode::NOT, expr->line);
            break;
        default:
            Debugger::error("Unknown unary operator", expr->line, 0, InterpretationStage::BYTECODE, "", "", "");
            break;
    }
}

void BytecodeGenerator::visitLiteralExpr(const std::shared_ptr<AST::LiteralExpr>& expr) {
    // Generate bytecode for literal expression
    
    // Push literal value onto stack based on its type
    if (std::holds_alternative<int>(expr->value)) {
        emit(Opcode::PUSH_INT, expr->line, std::get<int>(expr->value));
    } else if (std::holds_alternative<double>(expr->value)) {
        emit(Opcode::PUSH_FLOAT, expr->line, 0, std::get<double>(expr->value));
    } else if (std::holds_alternative<std::string>(expr->value)) {
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, std::get<std::string>(expr->value));
    } else if (std::holds_alternative<bool>(expr->value)) {
        emit(Opcode::PUSH_BOOL, expr->line, 0, 0.0f, std::get<bool>(expr->value));
    } else if (std::holds_alternative<std::nullptr_t>(expr->value)) {
        emit(Opcode::PUSH_NULL, expr->line);
    }
}

void BytecodeGenerator::visitVariableExpr(const std::shared_ptr<AST::VariableExpr>& expr) {
    // Generate bytecode for variable expression
    if (expr->name == "super") {
        emit(Opcode::LOAD_SUPER, expr->line);
    } else if (expr->name == "this" || expr->name == "self") {
        emit(Opcode::LOAD_THIS, expr->line);
    } else {
        emit(Opcode::LOAD_VAR, expr->line, 0, 0.0f, false, expr->name);
    }
}

void BytecodeGenerator::visitCallExpr(const std::shared_ptr<AST::CallExpr>& expr) {
    // Generate bytecode for function call expression
    
    // Evaluate positional arguments (push them onto stack)
    for (const auto& arg : expr->arguments) {
        visitExpression(arg);
    }
    
    // Handle different types of callees
    std::string functionName;
    if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee)) {
        // Simple function call: functionName(args)
        functionName = varExpr->name;
    } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr->callee)) {
        // Method call: object.methodName(args)
        // First evaluate the object
        visitExpression(memberExpr->object);
        
        // Then call the method on the object
        functionName = memberExpr->name;
        
        // Check if this is a super method call
        bool isSuperCall = false;
        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(memberExpr->object)) {
            if (varExpr->name == "super") {
                isSuperCall = true;
            }
        }
        
        // For method calls, we need to use a different approach
        // The object is already on the stack, so we need to handle this differently
        std::string callPrefix = isSuperCall ? "super:" : "method:";
        emit(Opcode::CALL, expr->line, static_cast<int32_t>(expr->arguments.size() + 1), 0.0f, false, callPrefix + functionName);
        return;
    } else {
        // For other complex callees, we'd need to evaluate them
        // For now, just use a placeholder
        functionName = "unknown";
    }
    
    // TODO: Handle named arguments properly
    if (!expr->namedArgs.empty()) {
        Debugger::error("Named arguments not yet supported", expr->line, 0, InterpretationStage::BYTECODE, "", "", "");
    }
    
    // Call function
    emit(Opcode::CALL, expr->line, static_cast<int32_t>(expr->arguments.size()), 0.0f, false, functionName);
}

void BytecodeGenerator::visitAssignExpr(const std::shared_ptr<AST::AssignExpr>& expr) {
    // Generate bytecode for assignment expression
    
    // Check if this is a member assignment (obj.field = value)
    if (expr->object && expr->member.has_value()) {
        // Member assignment: obj.field = value
        
        // First evaluate the object
        visitExpression(expr->object);
        
        // Then evaluate the value
        visitExpression(expr->value);
        
        // Set the property
        emit(Opcode::SET_PROPERTY, expr->line, 0, 0.0f, false, expr->member.value());
        
        // Assignment expressions should return the assigned value
        // SET_PROPERTY should leave the value on the stack for this
        return;
    }
    
    // Check if this is an index assignment (arr[i] = value)
    if (expr->object && expr->index) {
        // Index assignment: arr[i] = value
        // TODO: Implement index assignment
        Debugger::error("Index assignment not yet implemented", expr->line, 0, InterpretationStage::BYTECODE, "", "", "");
        return;
    }
    
    // Variable assignment: name = value
    if (!expr->name.empty()) {
        // For compound assignments (+=, -=, etc.), load the variable first
        if (expr->op != TokenType::EQUAL) {
            emit(Opcode::LOAD_VAR, expr->line, 0, 0.0f, false, expr->name);
            visitExpression(expr->value);
            
            // Perform the operation based on the operator
            switch (expr->op) {
                case TokenType::PLUS_EQUAL:
                    emit(Opcode::ADD, expr->line);
                    break;
                case TokenType::MINUS_EQUAL:
                    emit(Opcode::SUBTRACT, expr->line);
                    break;
                case TokenType::STAR_EQUAL:
                    emit(Opcode::MULTIPLY, expr->line);
                    break;
                case TokenType::SLASH_EQUAL:
                    emit(Opcode::DIVIDE, expr->line);
                    break;
                case TokenType::MODULUS_EQUAL:
                    emit(Opcode::MODULO, expr->line);
                    break;
                default:
                    Debugger::error("Unknown compound assignment operator", expr->line, 0, InterpretationStage::BYTECODE, "", "", "");
                    break;
            }
        } else {
            // Regular assignment
            visitExpression(expr->value);
        }
        
        // Store value in variable (STORE_VAR now pops the value)
        // But assignment expressions should return the assigned value, so duplicate first
        emit(Opcode::DUP, expr->line);
        emit(Opcode::STORE_VAR, expr->line, 0, 0.0f, false, expr->name);
        return;
    }
    
    // If we get here, it's an invalid assignment
    Debugger::error("Invalid assignment expression", expr->line, 0, InterpretationStage::BYTECODE, "", "", "");
}

void BytecodeGenerator::visitGroupingExpr(const std::shared_ptr<AST::GroupingExpr>& expr) {
    // Generate bytecode for grouping expression
    visitExpression(expr->expression);
}

void BytecodeGenerator::visitListExpr(const std::shared_ptr<AST::ListExpr>& expr) {
    // Generate bytecode for list literal expression
    
    // Evaluate each element and push onto stack
    for (const auto& element : expr->elements) {
        visitExpression(element);
    }
    
    // Create list with all elements on stack
    emit(Opcode::CREATE_LIST, expr->line, static_cast<int32_t>(expr->elements.size()));
}

void BytecodeGenerator::visitDictExpr(const std::shared_ptr<AST::DictExpr>& expr) {
    // Generate bytecode for dictionary literal expression
    
    // Evaluate each key-value pair and push onto stack
    for (const auto& [key, value] : expr->entries) {
        visitExpression(key);
        visitExpression(value);
    }
    
    // Create dictionary with all key-value pairs on stack
    emit(Opcode::CREATE_DICT, expr->line, static_cast<int32_t>(expr->entries.size()));
}

void BytecodeGenerator::visitIndexExpr(const std::shared_ptr<AST::IndexExpr>& expr) {
    // Generate bytecode for index expression
    
    // Evaluate object
    visitExpression(expr->object);
    
    // Evaluate index
    visitExpression(expr->index);
    
    // Get item at index
    emit(Opcode::GET_INDEX, expr->line);
}

void BytecodeGenerator::visitMemberExpr(const std::shared_ptr<AST::MemberExpr>& expr) {
    // Generate bytecode for member access expression
    
    // Evaluate object
    visitExpression(expr->object);
    
    // Get member
    emit(Opcode::GET_PROPERTY, expr->line, 0, 0.0f, false, expr->name);
}

void BytecodeGenerator::visitAwaitExpr(const std::shared_ptr<AST::AwaitExpr>& expr) {
    // Generate bytecode for await expression
    
    // Evaluate expression
    visitExpression(expr->expression);
    
    // Await result
    emit(Opcode::AWAIT, expr->line);
}

void BytecodeGenerator::visitRangeExpr(const std::shared_ptr<AST::RangeExpr>& expr) {
    // Generate bytecode for range expression
    
    // Evaluate start expression
    visitExpression(expr->start);
    
    // Evaluate end expression
    visitExpression(expr->end);
    
    // Create range object
    emit(Opcode::CREATE_RANGE, expr->line, 0, 0.0f, expr->inclusive);
    
    // If there's a step value, evaluate and set it
    if (expr->step) {
        // Duplicate range reference
        emit(Opcode::DUP, expr->line);
        
        // Evaluate step
        visitExpression(expr->step);
        
        // Set step value
        emit(Opcode::SET_RANGE_STEP, expr->line);
    }
}

void BytecodeGenerator::visitIterStatement(const std::shared_ptr<AST::IterStatement>& stmt) {
    // Allocate a unique temporary variable for this iterator
    int iteratorTempIndex = tempVarCounter++;
    
    // Push the iterable onto the stack
    visitExpression(stmt->iterable);
    
    // Create an iterator from the iterable
    emit(Opcode::GET_ITERATOR, stmt->line);
    
    // Store the iterator in a temporary variable
    emit(Opcode::STORE_TEMP, stmt->line, iteratorTempIndex);
    
    // Start of loop
    size_t loopStart = bytecode.size();
    
    // Check if iterator has next value
    emit(Opcode::LOAD_TEMP, stmt->line, iteratorTempIndex);
    emit(Opcode::ITERATOR_HAS_NEXT, stmt->line);
    
    // Jump to end of loop if no more items
    emit(Opcode::JUMP_IF_FALSE, stmt->line, 0); // Placeholder for jump offset
    size_t jumpToEnd = bytecode.size() - 1;
    
    // Get next value from iterator
    emit(Opcode::LOAD_TEMP, stmt->line, iteratorTempIndex);
    emit(Opcode::ITERATOR_NEXT, stmt->line);
    
    // Store the value in the loop variable
    // For single variable iteration (like 'for x in iterable')
    if (stmt->loopVars.size() == 1) {
        // The value is already on the stack, just need to store it
        emit(Opcode::STORE_VAR, stmt->line, 0, 0.0f, false, stmt->loopVars[0]);
    }
    // For key-value iteration (like 'for k, v in dict.items()')
    else if (stmt->loopVars.size() == 2) {
        // The key-value pair is on the stack as [key, value]
        // Store the value first (it's on top of the stack)
        emit(Opcode::STORE_VAR, stmt->line, 0, 0.0f, false, stmt->loopVars[1]);
        // Then store the key
        emit(Opcode::STORE_VAR, stmt->line, 0, 0.0f, false, stmt->loopVars[0]);
    }
    
    // Generate code for the loop body
    visitStatement(stmt->body);
    
    // Jump back to the start of the loop
    emit(Opcode::JUMP, stmt->line, loopStart - bytecode.size() - 1);
    
    // Update the jump to end of loop with the correct offset
    bytecode[jumpToEnd].intValue = bytecode.size() - jumpToEnd - 1;
    
    // Clean up the temporary iterator
    emit(Opcode::CLEAR_TEMP, stmt->line, iteratorTempIndex);
}

void BytecodeGenerator::visitModuleDeclaration(const std::shared_ptr<AST::ModuleDeclaration>& stmt) {
    // For now, we'll just process the module body as a block
    // In a real implementation, we might want to handle module-level scoping
    
    // Create a new scope for the module
    emit(Opcode::BEGIN_SCOPE, stmt->line);
    
    // Process all public members of the module
    for (const auto& member : stmt->publicMembers) {
        visitStatement(member);
    }
    
    // Process all protected members of the module
    for (const auto& member : stmt->protectedMembers) {
        visitStatement(member);
    }
    
    // Process all private members of the module
    for (const auto& member : stmt->privateMembers) {
        visitStatement(member);
    }
    
    // End the module scope
    emit(Opcode::END_SCOPE, stmt->line);
}

void BytecodeGenerator::visitContractStatement(const std::shared_ptr<AST::ContractStatement>& stmt) {
    // Contracts are typically used for preconditions, postconditions, and invariants
    // In the bytecode, we'll generate code to check the condition and possibly throw an exception if it fails
    
    // Evaluate the condition
    visitExpression(stmt->condition);
    
    // If the condition is false, throw an exception with the message
    emit(Opcode::JUMP_IF_TRUE, stmt->line, 5); // Skip the next 5 instructions if condition is true
    
    // Evaluate the message expression (should result in a string)
    if (stmt->message) {
        visitExpression(stmt->message);
    } else {
        // Default error message if none provided
        emit(Opcode::PUSH_STRING, stmt->line, 0, 0.0f, false, "Contract violation");
    }
    
    // Throw an exception with the message
    emit(Opcode::THROW, stmt->line);
}

void BytecodeGenerator::emit(Opcode op, uint32_t lineNumber, int32_t intValue, float floatValue, bool boolValue, const std::string& stringValue) {
    // Create and push instruction onto bytecode vector
    Instruction instruction;
    instruction.opcode = op;
    instruction.line = lineNumber;
    instruction.intValue = intValue;
    instruction.floatValue = floatValue;
    instruction.boolValue = boolValue;
    instruction.stringValue = stringValue;
    
    bytecode.push_back(instruction);
}

