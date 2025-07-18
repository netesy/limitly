#include "../backend.hh"
#include "../debugger.hh"
#include <iostream>

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
    } else {
        Debugger::error("Unknown statement type", 0, 0, InterpretationStage::COMPILATION);
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
    } else {
        Debugger::error("Unknown expression type", 0, 0, InterpretationStage::COMPILATION);
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
    
    // End function definition
    emit(Opcode::END_FUNCTION, stmt->line);
}

void BytecodeGenerator::visitClassDeclaration(const std::shared_ptr<AST::ClassDeclaration>& stmt) {
    // Generate bytecode for class declaration
    
    // Start class definition
    emit(Opcode::BEGIN_CLASS, stmt->line, 0, 0.0f, false, stmt->name);
    
    // Process fields
    for (const auto& field : stmt->fields) {
        visitVarDeclaration(field);
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
    
    // Update jump to else branch instruction
    bytecode[jumpToElseIndex].intValue = bytecode.size() - jumpToElseIndex;
    
    // Process else branch if it exists
    if (stmt->elseBranch) {
        visitStatement(stmt->elseBranch);
    }
    
    // Update jump over else branch instruction
    bytecode[jumpOverElseIndex].intValue = bytecode.size() - jumpOverElseIndex;
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
        emit(Opcode::JUMP, stmt->line, loopStartIndex - bytecode.size());
        
        // Update jump to end instruction
        bytecode[jumpToEndIndex].intValue = bytecode.size() - jumpToEndIndex;
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
        emit(Opcode::JUMP, stmt->line, loopStartIndex - bytecode.size());
        
        // Update jump to end instruction
        bytecode[jumpToEndIndex].intValue = bytecode.size() - jumpToEndIndex;
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
    emit(Opcode::JUMP, stmt->line, loopStartIndex - bytecode.size());
    
    // Update jump to end instruction
    bytecode[jumpToEndIndex].intValue = bytecode.size() - jumpToEndIndex;
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
    bytecode[jumpOverHandlersIndex].intValue = bytecode.size() - jumpOverHandlersIndex;
    
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
        bytecode[jumpToNextCaseIndex].intValue = bytecode.size() - jumpToNextCaseIndex;
    }
    
    // Update all jump to end instructions
    for (size_t index : jumpToEndIndices) {
        bytecode[index].intValue = bytecode.size() - index;
    }
    
    // Clean up temporary variable
    emit(Opcode::CLEAR_TEMP, stmt->line);
}

// Expression visitors
void BytecodeGenerator::visitBinaryExpr(const std::shared_ptr<AST::BinaryExpr>& expr) {
    // Generate bytecode for binary expression
    
    // Evaluate left operand
    visitExpression(expr->left);
    
    // Evaluate right operand
    visitExpression(expr->right);
    
    // Perform operation based on operator type
    switch (expr->op) {
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
        case TokenType::AND:
            emit(Opcode::AND, expr->line);
            break;
        case TokenType::OR:
            emit(Opcode::OR, expr->line);
            break;
        default:
            Debugger::error("Unknown binary operator", expr->line, 0, InterpretationStage::COMPILATION);
            break;
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
        case TokenType::BANG:
            emit(Opcode::NOT, expr->line);
            break;
        default:
            Debugger::error("Unknown unary operator", expr->line, 0, InterpretationStage::COMPILATION);
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
    emit(Opcode::LOAD_VAR, expr->line, 0, 0.0f, false, expr->name);
}

void BytecodeGenerator::visitCallExpr(const std::shared_ptr<AST::CallExpr>& expr) {
    // Generate bytecode for function call expression
    
    // Evaluate callee
    visitExpression(expr->callee);
    
    // Evaluate positional arguments
    for (const auto& arg : expr->arguments) {
        visitExpression(arg);
    }
    
    // Evaluate named arguments
    for (const auto& [name, arg] : expr->namedArgs) {
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, name);
        visitExpression(arg);
    }
    
    // Call function
    emit(Opcode::CALL, expr->line, expr->arguments.size(), 0.0f, false, std::to_string(expr->namedArgs.size()));
}

void BytecodeGenerator::visitAssignExpr(const std::shared_ptr<AST::AssignExpr>& expr) {
    // Generate bytecode for assignment expression
    
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
                Debugger::error("Unknown compound assignment operator", expr->line, 0, InterpretationStage::COMPILATION);
                break;
        }
    } else {
        // Regular assignment
        visitExpression(expr->value);
    }
    
    // Duplicate value (for assignment expressions that return the assigned value)
    emit(Opcode::DUP, expr->line);
    
    // Store value in variable
    emit(Opcode::STORE_VAR, expr->line, 0, 0.0f, false, expr->name);
}

void BytecodeGenerator::visitGroupingExpr(const std::shared_ptr<AST::GroupingExpr>& expr) {
    // Generate bytecode for grouping expression
    visitExpression(expr->expression);
}

void BytecodeGenerator::visitListExpr(const std::shared_ptr<AST::ListExpr>& expr) {
    // Generate bytecode for list literal expression
    
    // Create empty list
    emit(Opcode::CREATE_LIST, expr->line);
    
    // Evaluate and add each element
    for (const auto& element : expr->elements) {
        // Duplicate list reference
        emit(Opcode::DUP, expr->line);
        
        // Evaluate element
        visitExpression(element);
        
        // Add element to list
        emit(Opcode::LIST_APPEND, expr->line);
    }
}

void BytecodeGenerator::visitDictExpr(const std::shared_ptr<AST::DictExpr>& expr) {
    // Generate bytecode for dictionary literal expression
    
    // Create empty dictionary
    emit(Opcode::CREATE_DICT, expr->line);
    
    // Evaluate and add each entry
    for (const auto& [key, value] : expr->entries) {
        // Duplicate dictionary reference
        emit(Opcode::DUP, expr->line);
        
        // Evaluate key
        visitExpression(key);
        
        // Evaluate value
        visitExpression(value);
        
        // Add entry to dictionary
        emit(Opcode::DICT_SET, expr->line);
    }
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

// ASTPrinter implementation
void ASTPrinter::process(const std::shared_ptr<AST::Program>& program) {
    std::cout << "AST Structure:" << std::endl;
    printNode(program);
}

void ASTPrinter::printNode(const std::shared_ptr<AST::Node>& node, int indent) {
    std::string indentation = getIndentation(indent);
    
    if (auto program = std::dynamic_pointer_cast<AST::Program>(node)) {
        std::cout << indentation << "Program:" << std::endl;
        for (const auto& stmt : program->statements) {
            printNode(stmt, indent + 1);
        }
    } 
    else if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(node)) {
        std::cout << indentation << "VarDeclaration: " << varDecl->name;
        if (varDecl->type && *varDecl->type) {
            std::cout << " : " << (*varDecl->type)->typeName;
            if ((*varDecl->type)->isOptional) std::cout << "?";
        }
        std::cout << std::endl;
        
        if (varDecl->initializer) {
            std::cout << indentation << "  Initializer:" << std::endl;
            printNode(varDecl->initializer, indent + 2);
        }
    }
    else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(node)) {
        std::cout << indentation << "FunctionDeclaration: " << funcDecl->name << std::endl;
        
        std::cout << indentation << "  Parameters:" << std::endl;
        for (const auto& param : funcDecl->params) {
            std::cout << indentation << "    " << param.first << " : " << param.second->typeName << std::endl;
        }
        
        for (const auto& param : funcDecl->optionalParams) {
            std::cout << indentation << "    " << param.first << " : " << param.second.first->typeName << "? (optional)" << std::endl;
        }
        
        if (funcDecl->returnType && *funcDecl->returnType) {
            std::cout << indentation << "  ReturnType: " << (*funcDecl->returnType)->typeName << std::endl;
        }
        
        std::cout << indentation << "  Body:" << std::endl;
        printNode(funcDecl->body, indent + 2);
    }
    else if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(node)) {
        std::cout << indentation << "ClassDeclaration: " << classDecl->name << std::endl;
        
        std::cout << indentation << "  Fields:" << std::endl;
        for (const auto& field : classDecl->fields) {
            printNode(field, indent + 2);
        }
        
        std::cout << indentation << "  Methods:" << std::endl;
        for (const auto& method : classDecl->methods) {
            printNode(method, indent + 2);
        }
    }
    else if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(node)) {
        std::cout << indentation << "BlockStatement:" << std::endl;
        for (const auto& stmt : blockStmt->statements) {
            printNode(stmt, indent + 1);
        }
    }
    else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(node)) {
        std::cout << indentation << "IfStatement:" << std::endl;
        
        std::cout << indentation << "  Condition:" << std::endl;
        printNode(ifStmt->condition, indent + 2);
        
        std::cout << indentation << "  ThenBranch:" << std::endl;
        printNode(ifStmt->thenBranch, indent + 2);
        
        if (ifStmt->elseBranch) {
            std::cout << indentation << "  ElseBranch:" << std::endl;
            printNode(ifStmt->elseBranch, indent + 2);
        }
    }
    else if (auto forStmt = std::dynamic_pointer_cast<AST::ForStatement>(node)) {
        if (forStmt->isIterableLoop) {
            std::cout << indentation << "ForStatement (iterable):" << std::endl;
            
            std::cout << indentation << "  Variables:";
            for (const auto& var : forStmt->loopVars) {
                std::cout << " " << var;
            }
            std::cout << std::endl;
            
            std::cout << indentation << "  Iterable:" << std::endl;
            printNode(forStmt->iterable, indent + 2);
        } else {
            std::cout << indentation << "ForStatement (traditional):" << std::endl;
            
            if (forStmt->initializer) {
                std::cout << indentation << "  Initializer:" << std::endl;
                printNode(forStmt->initializer, indent + 2);
            }
            
            if (forStmt->condition) {
                std::cout << indentation << "  Condition:" << std::endl;
                printNode(forStmt->condition, indent + 2);
            }
            
            if (forStmt->increment) {
                std::cout << indentation << "  Increment:" << std::endl;
                printNode(forStmt->increment, indent + 2);
            }
        }
        
        std::cout << indentation << "  Body:" << std::endl;
        printNode(forStmt->body, indent + 2);
    }
    else if (auto whileStmt = std::dynamic_pointer_cast<AST::WhileStatement>(node)) {
        std::cout << indentation << "WhileStatement:" << std::endl;
        
        std::cout << indentation << "  Condition:" << std::endl;
        printNode(whileStmt->condition, indent + 2);
        
        std::cout << indentation << "  Body:" << std::endl;
        printNode(whileStmt->body, indent + 2);
    }
    else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(node)) {
        std::cout << indentation << "ReturnStatement:" << std::endl;
        
        if (returnStmt->value) {
            std::cout << indentation << "  Value:" << std::endl;
            printNode(returnStmt->value, indent + 2);
        }
    }
    else if (auto printStmt = std::dynamic_pointer_cast<AST::PrintStatement>(node)) {
        std::cout << indentation << "PrintStatement:" << std::endl;
        
        std::cout << indentation << "  Arguments:" << std::endl;
        for (const auto& arg : printStmt->arguments) {
            printNode(arg, indent + 2);
        }
    }
    else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(node)) {
        std::cout << indentation << "ExpressionStatement:" << std::endl;
        printNode(exprStmt->expression, indent + 1);
    }
    else if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(node)) {
        std::cout << indentation << "BinaryExpression:" << std::endl;
        
        std::cout << indentation << "  Left:" << std::endl;
        printNode(binaryExpr->left, indent + 2);
        
        std::cout << indentation << "  Operator: ";
        switch (binaryExpr->op) {
            case TokenType::PLUS: std::cout << "+"; break;
            case TokenType::MINUS: std::cout << "-"; break;
            case TokenType::STAR: std::cout << "*"; break;
            case TokenType::SLASH: std::cout << "/"; break;
            case TokenType::MODULUS: std::cout << "%"; break;
            case TokenType::EQUAL_EQUAL: std::cout << "=="; break;
            case TokenType::BANG_EQUAL: std::cout << "!="; break;
            case TokenType::LESS: std::cout << "<"; break;
            case TokenType::LESS_EQUAL: std::cout << "<="; break;
            case TokenType::GREATER: std::cout << ">"; break;
            case TokenType::GREATER_EQUAL: std::cout << ">="; break;
            case TokenType::AND: std::cout << "and"; break;
            case TokenType::OR: std::cout << "or"; break;
            default: std::cout << "unknown"; break;
        }
        std::cout << std::endl;
        
        std::cout << indentation << "  Right:" << std::endl;
        printNode(binaryExpr->right, indent + 2);
    }
    else if (auto unaryExpr = std::dynamic_pointer_cast<AST::UnaryExpr>(node)) {
        std::cout << indentation << "UnaryExpression:" << std::endl;
        
        std::cout << indentation << "  Operator: ";
        switch (unaryExpr->op) {
            case TokenType::MINUS: std::cout << "-"; break;
            case TokenType::BANG: std::cout << "!"; break;
            default: std::cout << "unknown"; break;
        }
        std::cout << std::endl;
        
        std::cout << indentation << "  Operand:" << std::endl;
        printNode(unaryExpr->right, indent + 2);
    }
    else if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(node)) {
        std::cout << indentation << "LiteralExpression: ";
        
        if (std::holds_alternative<int>(literalExpr->value)) {
            std::cout << std::get<int>(literalExpr->value) << " (int)";
        } else if (std::holds_alternative<double>(literalExpr->value)) {
            std::cout << std::get<double>(literalExpr->value) << " (float)";
        } else if (std::holds_alternative<std::string>(literalExpr->value)) {
            std::cout << "\"" << std::get<std::string>(literalExpr->value) << "\" (string)";
        } else if (std::holds_alternative<bool>(literalExpr->value)) {
            std::cout << (std::get<bool>(literalExpr->value) ? "true" : "false") << " (bool)";
        } else if (std::holds_alternative<std::nullptr_t>(literalExpr->value)) {
            std::cout << "None (null)";
        }
        
        std::cout << std::endl;
    }
    else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(node)) {
        std::cout << indentation << "VariableExpression: " << varExpr->name << std::endl;
    }
    else if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(node)) {
        std::cout << indentation << "CallExpression:" << std::endl;
        
        std::cout << indentation << "  Callee:" << std::endl;
        printNode(callExpr->callee, indent + 2);
        
        std::cout << indentation << "  Arguments:" << std::endl;
        for (const auto& arg : callExpr->arguments) {
            printNode(arg, indent + 2);
        }
        
        if (!callExpr->namedArgs.empty()) {
            std::cout << indentation << "  NamedArguments:" << std::endl;
            for (const auto& [name, arg] : callExpr->namedArgs) {
                std::cout << indentation << "    " << name << ":" << std::endl;
                printNode(arg, indent + 3);
            }
        }
    }
    else {
        std::cout << indentation << "Unknown node type" << std::endl;
    }
}

std::string ASTPrinter::getIndentation(int indent) const {
    return std::string(indent * 2, ' ');
}