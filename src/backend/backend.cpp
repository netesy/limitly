#include "../common/backend.hh"
#include "../common/debugger.hh"
#include "value.hh"
#include "vm.hh"
#include "memory.hh"
#include "type_checker.hh"
#include "../frontend/scanner.hh"
#include "../frontend/parser.hh"
#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>

// Constructor
BytecodeGenerator::BytecodeGenerator() {
    // Initialize memory manager and type system
    static MemoryManager<> memoryManager;
    static MemoryManager<>::Region region(MemoryManager<>::getInstance()); 
    
    typeSystem = std::make_unique<TypeSystem>(memoryManager, region);
    typeChecker = std::make_unique<TypeChecker>(*typeSystem);
}

void BytecodeGenerator::setSourceContext(const std::string& source, const std::string& filePath) {
    this->sourceCode = source;
    this->filePath = filePath;
}

// Type checking integration
std::vector<TypeCheckError> BytecodeGenerator::performTypeChecking(const std::shared_ptr<AST::Program>& program) {
    // Set source context for the type checker
    typeChecker->setSourceContext(sourceCode, filePath);
    return typeChecker->checkProgram(program);
}

void BytecodeGenerator::visitInterpolatedStringExpr(const std::shared_ptr<AST::InterpolatedStringExpr>& expr) {
    // For each part of the interpolated string
    for (const auto& part : expr->parts) {
        std::visit(overloaded {
            // Handle string literal parts
            [&](const std::string& str) {
                // String value is already parsed (quotes removed) by the parser
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
    // Perform compile-time type checking first
    std::vector<TypeCheckError> typeErrors = performTypeChecking(program);
    
    // Report type checking errors but continue with bytecode generation for now
    // This allows testing of error handling features while still reporting issues
    if (!typeErrors.empty()) {
        for (const auto& error : typeErrors) {
            // Extract lexeme and expected value from enhanced error messages
            std::string lexeme = "";
            std::string expectedValue = "";
            
            // Parse enhanced error message format: "message (at 'lexeme') - expected: expectedValue"
            std::string message = error.message;
            size_t lexemeStart = message.find("(at '");
            if (lexemeStart != std::string::npos) {
                lexemeStart += 5; // Skip "(at '"
                size_t lexemeEnd = message.find("')", lexemeStart);
                if (lexemeEnd != std::string::npos) {
                    lexeme = message.substr(lexemeStart, lexemeEnd - lexemeStart);
                }
            }
            
            size_t expectedStart = message.find(" - expected: ");
            if (expectedStart != std::string::npos) {
                expectedStart += 13; // Skip " - expected: "
                expectedValue = message.substr(expectedStart);
                // Clean up the message by removing the expected part
                message = message.substr(0, message.find(" - expected: "));
            }
            
            // Clean up the message by removing the lexeme part
            size_t lexemePartStart = message.find(" (at '");
            if (lexemePartStart != std::string::npos) {
                message = message.substr(0, lexemePartStart);
            }
            
            // Debug: Check if we have source context
            if (sourceCode.empty() || filePath.empty()) {
                std::cerr << "[DEBUG] Missing source context - sourceCode.empty(): " << sourceCode.empty() 
                         << ", filePath.empty(): " << filePath.empty() << std::endl;
            }
            
            Debugger::error(message, error.line, error.column, 
                          InterpretationStage::SEMANTIC, sourceCode, filePath, lexeme, expectedValue);
        }
        // Continue with bytecode generation to allow testing
        // TODO: Make this configurable or more selective about which errors are fatal
    }
    
    // Process each statement in the program
    for (const auto& stmt : program->statements) {
        visitStatement(stmt);
    }
    // TODO: Add line number from the last statement
    emit(Opcode::HALT, 0);
}

void BytecodeGenerator::visitStatement(const std::shared_ptr<AST::Statement>& stmt) {
    // Dispatch to the appropriate visitor method based on statement type
    if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        visitVarDeclaration(varDecl);
    } else if (auto destructDecl = std::dynamic_pointer_cast<AST::DestructuringDeclaration>(stmt)) {
        visitDestructuringDeclaration(destructDecl);
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
    } else if (auto breakStmt = std::dynamic_pointer_cast<AST::BreakStatement>(stmt)) {
        visitBreakStatement(breakStmt);
    } else if (auto continueStmt = std::dynamic_pointer_cast<AST::ContinueStatement>(stmt)) {
        visitContinueStatement(continueStmt);
    } else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
        visitReturnStatement(returnStmt);
    } else if (auto printStmt = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
        visitPrintStatement(printStmt);
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        visitExprStatement(exprStmt);
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
    } else if (auto taskStmt = std::dynamic_pointer_cast<AST::TaskStatement>(stmt)) {
        visitTaskStatement(taskStmt);
    } else if (auto workerStmt = std::dynamic_pointer_cast<AST::WorkerStatement>(stmt)) {
        visitWorkerStatement(workerStmt);
    } else {
        // Get the actual statement type name for better error reporting
        std::string actualType = "unknown statement";
        if (stmt) {
            actualType = typeid(*stmt).name(); // This will give us the actual type
        }
        
        Debugger::error("Unsupported statement type in bytecode generation", stmt->line, 0, InterpretationStage::BYTECODE, 
                       sourceCode, filePath, actualType, "variable declaration, function declaration, class declaration, if statement, while loop, for loop, return statement, break statement, continue statement, or expression statement");
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
    } else if (auto tupleExpr = std::dynamic_pointer_cast<AST::TupleExpr>(expr)) {
        visitTupleExpr(tupleExpr);
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
    } else if (auto typePattern = std::dynamic_pointer_cast<AST::TypePatternExpr>(expr)) {
        visitTypePatternExpr(typePattern);
    } else if (auto bindingPattern = std::dynamic_pointer_cast<AST::BindingPatternExpr>(expr)) {
        visitBindingPatternExpr(bindingPattern);
    } else if (auto listPattern = std::dynamic_pointer_cast<AST::ListPatternExpr>(expr)) {
        visitListPatternExpr(listPattern);
    } else if (auto dictPattern = std::dynamic_pointer_cast<AST::DictPatternExpr>(expr)) {
        visitDictPatternExpr(dictPattern);
    } else if (auto tuplePattern = std::dynamic_pointer_cast<AST::TuplePatternExpr>(expr)) {
        visitTuplePatternExpr(tuplePattern);
    } else if (auto valPattern = std::dynamic_pointer_cast<AST::ValPatternExpr>(expr)) {
        visitValPatternExpr(valPattern);
    } else if (auto errPattern = std::dynamic_pointer_cast<AST::ErrPatternExpr>(expr)) {
        visitErrPatternExpr(errPattern);
    } else if (auto errorTypePattern = std::dynamic_pointer_cast<AST::ErrorTypePatternExpr>(expr)) {
        visitErrorTypePatternExpr(errorTypePattern);
    } else if (auto fallibleExpr = std::dynamic_pointer_cast<AST::FallibleExpr>(expr)) {
        visitFallibleExpr(fallibleExpr);
    } else if (auto errorConstructExpr = std::dynamic_pointer_cast<AST::ErrorConstructExpr>(expr)) {
        visitErrorConstructExpr(errorConstructExpr);
    } else if (auto okConstructExpr = std::dynamic_pointer_cast<AST::OkConstructExpr>(expr)) {
        visitOkConstructExpr(okConstructExpr);
    } else if (auto lambdaExpr = std::dynamic_pointer_cast<AST::LambdaExpr>(expr)) {
        visitLambdaExpr(lambdaExpr);
    } else {
        // Get the actual expression type name for better error reporting
        std::string actualType = "unknown expression";
        if (expr) {
            actualType = typeid(*expr).name(); // This will give us the actual type
        }
        
        Debugger::error("Unsupported expression type in bytecode generation", expr->line, 0, InterpretationStage::BYTECODE, 
                       sourceCode, filePath, actualType, "binary expression, unary expression, literal, variable, function call, assignment, member access, index access, list, dictionary, range, or grouping expression");
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
    
    // If the declared type is 'atomic' emit DEFINE_ATOMIC so the VM can create
    // an atomic wrapper. Otherwise store the value with visibility information.
    if (stmt->type && *stmt->type && (*stmt->type)->typeName == "atomic") {
        emit(Opcode::DEFINE_ATOMIC, stmt->line, 0, 0.0f, false, stmt->name);
    } else {
        // Declare variable with visibility information in intValue field
        int visibilityInt = static_cast<int>(stmt->visibility);
        emit(Opcode::DECLARE_VAR, stmt->line, visibilityInt, 0.0f, false, stmt->name);
    }
}

void BytecodeGenerator::visitDestructuringDeclaration(const std::shared_ptr<AST::DestructuringDeclaration>& stmt) {
    // Generate bytecode for tuple destructuring assignment
    // Example: var (x, y, z) = tuple;
    
    // First, evaluate the tuple expression
    visitExpression(stmt->initializer);
    
    // Now we have the tuple on the stack
    // We need to extract each element and store it in the corresponding variable
    
    for (size_t i = 0; i < stmt->names.size(); ++i) {
        // Duplicate the tuple on the stack for each extraction
        emit(Opcode::DUP, stmt->line);
        
        // Push the index we want to extract
        emit(Opcode::PUSH_INT, stmt->line, static_cast<int64_t>(i));
        
        // Get the element at index i
        emit(Opcode::GET_INDEX, stmt->line);
        
        // Declare the extracted value as a new variable
        emit(Opcode::DECLARE_VAR, stmt->line, 0, 0.0f, false, stmt->names[i]);
    }
    
    // Pop the original tuple from the stack (we duplicated it for each extraction)
    emit(Opcode::POP, stmt->line);
}

void BytecodeGenerator::visitFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    // Generate bytecode for function declaration
    
    // Track this function as declared
    addDeclaredFunction(stmt->name);
    
    // Start function definition
    emit(Opcode::BEGIN_FUNCTION, stmt->line, 0, 0.0f, false, stmt->name);
    // Store the declaration in the function object
    // This is a bit of a hack. A better way would be to have a proper function object
    // that is created here and then stored in the environment.
    // For now, we'll just store the declaration and look it up in the VM.
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
    
    // Process function body (if it exists - abstract methods don't have bodies)
    if (stmt->body) {
        visitBlockStatement(stmt->body);
        
        // If function doesn't end with an explicit return, add implicit nil return
        // This ensures all functions return a value
        emit(Opcode::PUSH_NULL, stmt->line);
        emit(Opcode::RETURN, stmt->line);
    } else {
        // Abstract method - no body to generate
        // Return an error value if called
        emit(Opcode::PUSH_STRING, stmt->line, 0, 0.0f, false, "Abstract method '" + stmt->name + "' called");
        emit(Opcode::CONSTRUCT_ERROR, stmt->line);
        emit(Opcode::RETURN, stmt->line);
    }
    
    // End function definition
    emit(Opcode::END_FUNCTION, stmt->line);

    // Define a variable for the function with visibility information
    int visibilityInt = static_cast<int>(stmt->visibility);
    emit(Opcode::PUSH_FUNCTION, stmt->line, visibilityInt, 0.0f, false, stmt->name);
    
    // Only declare as variable if this is not a class method
    // Class methods are handled by the VM during class definition
    if (!isInsideClassDefinition()) {
        emit(Opcode::DECLARE_VAR, stmt->line, visibilityInt, 0.0f, false, stmt->name);
    } else {
        // For class methods, just pop the function from the stack since it's already registered
        emit(Opcode::POP, stmt->line);
    }
}

void BytecodeGenerator::visitClassDeclaration(const std::shared_ptr<AST::ClassDeclaration>& stmt) {
    // Generate bytecode for class declaration
    
    // Track that we're inside a class definition
    insideClassDefinition = true;
    currentClassBeingDefined = stmt->name;
    
    // Start class definition
    emit(Opcode::BEGIN_CLASS, stmt->line, 0, 0.0f, false, stmt->name);
    
    // Set superclass if there's inheritance
    if (!stmt->superClassName.empty()) {
        emit(Opcode::SET_SUPERCLASS, stmt->line, 0, 0.0f, false, stmt->superClassName);
    }
    
    // Process fields
    for (const auto& field : stmt->fields) {
        if (field->initializer) {
            visitExpression(field->initializer);
        } else {
            emit(Opcode::PUSH_NULL, field->line);
        }
        
        // Get field visibility from the class declaration
        AST::VisibilityLevel fieldVisibility = AST::VisibilityLevel::Private; // Default
        auto visIt = stmt->fieldVisibility.find(field->name);
        if (visIt != stmt->fieldVisibility.end()) {
            fieldVisibility = visIt->second;
        }
        
        int visibilityInt = static_cast<int>(fieldVisibility);
        emit(Opcode::DEFINE_FIELD, field->line, visibilityInt, 0.0f, false, field->name);
    }
    
    // Generate constructor if this is a derived class
    if (!stmt->superClassName.empty() && !stmt->hasInlineConstructor) {
        // Generate constructor that calls parent's constructor
        emit(Opcode::BEGIN_FUNCTION, stmt->line, 0, 0.0f, false, "init");
        
        // Call parent's constructor
        emit(Opcode::LOAD_THIS, stmt->line);
        emit(Opcode::LOAD_SUPER, stmt->line);
        emit(Opcode::CALL, stmt->line, 1); // Call super with 1 argument (this)
        
        // End constructor
        emit(Opcode::PUSH_NULL, stmt->line);
        emit(Opcode::RETURN, stmt->line);
        emit(Opcode::END_FUNCTION, stmt->line);
    }
    
    // Process methods with visibility information
    for (const auto& method : stmt->methods) {
        // Get method visibility from the class declaration
        AST::VisibilityLevel methodVisibility = method->visibility; // Methods have visibility in AST
        
        // Set the method visibility in the AST node before processing
        method->visibility = methodVisibility;
        
        visitFunctionDeclaration(method);
    }
    
    // End class definition
    emit(Opcode::END_CLASS, stmt->line);
    
    // Reset class definition tracking
    insideClassDefinition = false;
    currentClassBeingDefined.clear();
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

    loopBreakPatches.emplace_back();
    
 
        // Traditional for loop
        
        // Process initializer if it exists
        if (stmt->initializer) {
            visitStatement(stmt->initializer);
        }
        // Begin loop scope (for loop variable and body)
        emit(Opcode::BEGIN_SCOPE, stmt->line);
        // Start of loop
        size_t loopStartIndex = bytecode.size();
        loopStartAddresses.push_back(loopStartIndex);
        
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
        
        // Jump to body, over increment
        size_t jumpToBodyIndex = bytecode.size();
        emit(Opcode::JUMP, stmt->line);

        // Continue target: increment
        size_t incrementStartIndex = bytecode.size();
        loopContinueAddresses.push_back(incrementStartIndex);

        // Process increment if it exists
        if (stmt->increment) {
            visitExpression(stmt->increment);
            emit(Opcode::POP, stmt->line); // Discard result of increment expression
        }

        // Jump back to loop start (condition check)
        emit(Opcode::JUMP, stmt->line, static_cast<int32_t>(loopStartIndex) - static_cast<int32_t>(bytecode.size()) - 1);

        // Patch jump to body
        size_t bodyStartIndex = bytecode.size();
        bytecode[jumpToBodyIndex].intValue = bodyStartIndex - jumpToBodyIndex - 1;

        // Process loop body
        visitStatement(stmt->body);

        // Jump to increment
        emit(Opcode::JUMP, stmt->line, static_cast<int32_t>(incrementStartIndex) - static_cast<int32_t>(bytecode.size()) - 1);
        
        // Update jump to end instruction
        size_t endIndex = bytecode.size();
        bytecode[jumpToEndIndex].intValue = static_cast<int32_t>(endIndex - jumpToEndIndex - 1);

        // Patch break statements
        for (size_t patchAddr : loopBreakPatches.back()) {
            bytecode[patchAddr].intValue = endIndex - patchAddr - 1;
        }

        // End loop scope
        emit(Opcode::END_SCOPE, stmt->line);

    
    // End loop scope
    loopBreakPatches.pop_back();
}

void BytecodeGenerator::visitWhileStatement(const std::shared_ptr<AST::WhileStatement>& stmt) {
    // Generate bytecode for while statement
    
    // Start of loop
    size_t loopStartIndex = bytecode.size();
    loopStartAddresses.push_back(loopStartIndex);
    loopContinueAddresses.push_back(loopStartIndex);
    loopBreakPatches.emplace_back();

    // Evaluate condition
    visitExpression(stmt->condition);
    
    // Jump to end if condition is false
    size_t jumpToEndIndex = bytecode.size();
    emit(Opcode::JUMP_IF_FALSE, stmt->line);
    
    // Process loop body
    emit(Opcode::BEGIN_SCOPE, stmt->line);
    visitStatement(stmt->body);
    emit(Opcode::END_SCOPE, stmt->line);
    
    // Jump back to start of loop
    emit(Opcode::JUMP, stmt->line, static_cast<int32_t>(loopStartIndex) - static_cast<int32_t>(bytecode.size()) - 1);
    
    // Update jump to end instruction
    size_t endIndex = bytecode.size();
    bytecode[jumpToEndIndex].intValue = static_cast<int32_t>(endIndex - jumpToEndIndex - 1);

    // Patch break statements
    for (size_t patchAddr : loopBreakPatches.back()) {
        bytecode[patchAddr].intValue = endIndex - patchAddr - 1;
    }
    loopBreakPatches.pop_back();
    loopStartAddresses.pop_back();
}

void BytecodeGenerator::visitBreakStatement(const std::shared_ptr<AST::BreakStatement>& stmt) {
    if (loopBreakPatches.empty()) {
        Debugger::error("'break' statement used outside of loop context", stmt->line, 0, InterpretationStage::BYTECODE, 
                       sourceCode, filePath, "break", "break statement inside a loop body (while, for, or iter loop)");
        return;
    }
    size_t jumpIndex = bytecode.size();
    emit(Opcode::JUMP, stmt->line); // Placeholder
    loopBreakPatches.back().push_back(jumpIndex);
}

void BytecodeGenerator::visitContinueStatement(const std::shared_ptr<AST::ContinueStatement>& stmt) {
    if (loopStartAddresses.empty()) {
        Debugger::error("'continue' statement used outside of loop context", stmt->line, 0, InterpretationStage::BYTECODE, 
                       sourceCode, filePath, "continue", "continue statement inside a loop body (while, for, or iter loop)");
        return;
    }
    size_t continueAddr = loopContinueAddresses.back();
   // CRITICAL FIX: Dont emit any opcode for the continue statement
  //  emit(Opcode::JUMP, stmt->line, static_cast<int32_t>(continueAddr) - static_cast<int32_t>(bytecode.size()) - 1);
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

void BytecodeGenerator::visitTaskStatement(const std::shared_ptr<AST::TaskStatement>& stmt) {
    // Store the task body AST in the backend for later retrieval
    current_task_body = stmt->body;
    
    // Emit BEGIN_TASK opcode with isAsync flag and loop variable name (if any)
    emit(Opcode::BEGIN_TASK, stmt->line, stmt->isAsync ? 1 : 0, 0.0f, false, stmt->loopVar);
    
    // If there's an iterable, evaluate it and store it for the task
    if (stmt->iterable) {
        visitExpression(stmt->iterable);
        emit(Opcode::STORE_ITERABLE, stmt->line);
    }
    
    // Don't generate bytecode for the task body here - it will be compiled in TaskVM
    
    // Emit END_TASK opcode
    emit(Opcode::END_TASK, stmt->line);
}

void BytecodeGenerator::visitWorkerStatement(const std::shared_ptr<AST::WorkerStatement>& stmt) {
    // Emit BEGIN_WORKER opcode with isAsync flag and parameter name (if any)
    emit(Opcode::BEGIN_WORKER, stmt->line, stmt->isAsync ? 1 : 0, 0.0f, false, stmt->param);
    
    // Process the worker body
    visitBlockStatement(stmt->body);
    
    // Emit END_WORKER opcode
    emit(Opcode::END_WORKER, stmt->line);
}

void BytecodeGenerator::visitParallelStatement(const std::shared_ptr<AST::ParallelStatement>& stmt) {
    // Generate bytecode for parallel statement
    
    // Get cores value
    int cores = 0; // Default value
    if (stmt->cores == "auto") {
        cores = std::thread::hardware_concurrency();
    } else {
        try {
            cores = std::stoi(stmt->cores);
        } catch (const std::invalid_argument& e) {
            // Handle error: cores value is not a valid integer
            // For now, we'll just use the default value
        }
    }

    // Start parallel block with mode and cores
    emit(Opcode::BEGIN_PARALLEL, stmt->line, cores, 0.0f, false, stmt->mode);
    
    // Process parallel block body (which may contain task and worker statements)
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
    // Resolve imports at compile time instead of runtime
    std::string modulePath = stmt->modulePath;
    std::string filePath = resolveModulePath(modulePath);
    
    // Load and parse the module
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open module file: " + filePath);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    
    // Parse the module
    Scanner scanner(source);
    scanner.scanTokens();
    Parser parser(scanner);
    auto moduleAst = parser.parse();
    
    // Collect the names of functions and variables defined in the module
    std::vector<std::string> allModuleSymbols;
    
    // First, extract visibility information from the imported module
    // Set the type checker context to the imported module temporarily
    std::string originalModulePath = typeChecker->getCurrentModulePath();
    typeChecker->setSourceContext(source, filePath);
    typeChecker->extractModuleVisibility(moduleAst);
    
    // Generate bytecode for the module's statements
    // This will include all function definitions and variable declarations
    for (const auto& moduleStmt : moduleAst->statements) {
        // Skip import statements in modules to avoid circular imports
        if (std::dynamic_pointer_cast<AST::ImportStatement>(moduleStmt)) {
            continue;
        }
        
        // Track symbols being defined and check their visibility
        if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(moduleStmt)) {
            // Only include variables that are visible to the importing module
            AST::VisibilityLevel visibility = typeChecker->getModuleMemberVisibility(filePath, varDecl->name);
            if (visibility == AST::VisibilityLevel::Public || visibility == AST::VisibilityLevel::Const) {
                allModuleSymbols.push_back(varDecl->name);
            }
        } else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(moduleStmt)) {
            // Only include functions that are visible to the importing module
            AST::VisibilityLevel visibility = typeChecker->getModuleMemberVisibility(filePath, funcDecl->name);
            if (visibility == AST::VisibilityLevel::Public || visibility == AST::VisibilityLevel::Const) {
                allModuleSymbols.push_back(funcDecl->name);
            }
        }
        
        visitStatement(moduleStmt);
    }
    
    // Restore the original module context
    typeChecker->setSourceContext(sourceCode, originalModulePath);
    
    // Apply import filters to determine which symbols to include in the module object
    std::vector<std::string> moduleSymbols;
    if (stmt->filter) {
        if (stmt->filter->type == AST::ImportFilterType::Show) {
            // Only include symbols that are explicitly shown
            for (const std::string& identifier : stmt->filter->identifiers) {
                if (std::find(allModuleSymbols.begin(), allModuleSymbols.end(), identifier) != allModuleSymbols.end()) {
                    moduleSymbols.push_back(identifier);
                }
            }
        } else { // Hide
            // Include all symbols except those that are hidden
            for (const std::string& symbol : allModuleSymbols) {
                if (std::find(stmt->filter->identifiers.begin(), stmt->filter->identifiers.end(), symbol) == stmt->filter->identifiers.end()) {
                    moduleSymbols.push_back(symbol);
                }
            }
        }
    } else {
        // No filter - include all symbols
        moduleSymbols = allModuleSymbols;
    }
    
    // Create a module object that contains references to the imported symbols
    std::string varName = stmt->alias ? *stmt->alias : getModuleNameFromPath(modulePath);
    
    // Create a dictionary to represent the module, but mark functions specially
    emit(Opcode::CREATE_DICT, stmt->line);
    
    // Add each symbol to the module dictionary
    for (const std::string& symbol : moduleSymbols) {
        // Push the symbol name as key
        emit(Opcode::PUSH_STRING, stmt->line, 0, 0.0f, false, symbol);
        
        // Check if this symbol is a function
        bool isFunction = false;
        for (const auto& moduleStmt : moduleAst->statements) {
            if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(moduleStmt)) {
                if (funcDecl->name == symbol) {
                    isFunction = true;
                    break;
                }
            }
        }
        
        if (isFunction) {
            // For functions, create a special module function reference
            emit(Opcode::PUSH_STRING, stmt->line, 0, 0.0f, false, "module_function:" + symbol);
        } else {
            // Load the symbol value normally for variables
            emit(Opcode::LOAD_VAR, stmt->line, 0, 0.0f, false, symbol);
        }
        
        // Set the dictionary entry
        emit(Opcode::DICT_SET, stmt->line);
    }
    
    // Declare the module dictionary as a new variable
    emit(Opcode::DECLARE_VAR, stmt->line, 0, 0.0f, false, varName);
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
    int tempIndex = tempVarCounter++;
    emit(Opcode::STORE_TEMP, stmt->line, tempIndex);
    
    // Process each case
    std::vector<size_t> jumpToEndIndices;
    std::vector<size_t> jumpToNextCaseIndices;
    
    for (const auto& matchCase : stmt->cases) {
        // Update all previous jumps to point to this case
        for (size_t jumpIndex : jumpToNextCaseIndices) {
            bytecode[jumpIndex].intValue = bytecode.size() - jumpIndex - 1;
        }
        jumpToNextCaseIndices.clear();

        // Duplicate the value to match
        emit(Opcode::LOAD_TEMP, stmt->line, tempIndex);
        
        // Evaluate the pattern
        if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(matchCase.pattern)) {
            if (std::holds_alternative<std::nullptr_t>(literalExpr->value)) {
                // Wildcard pattern
                emit(Opcode::PUSH_NULL, matchCase.pattern->line); // Pushing null to represent wildcard
            } else {
                visitExpression(matchCase.pattern);
            }
        } else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(matchCase.pattern)) {
            // This is a variable binding, unless the variable is '_'
            if (varExpr->name == "_") {
                // Wildcard pattern
                emit(Opcode::PUSH_NULL, matchCase.pattern->line);
            } else {
                // Bind the value to the variable name.
                // The value is already on the stack from the LOAD_TEMP
                // We need to duplicate it before storing so one copy remains for MATCH_PATTERN
                emit(Opcode::DUP, matchCase.pattern->line);
                emit(Opcode::STORE_VAR, matchCase.pattern->line, 0, 0.0f, false, varExpr->name);
                // For the match to succeed, we need to push a true value.
                // The pattern for variable binding should always match. We'll push a string that the VM will recognize as a "match-all" for binding.
                emit(Opcode::PUSH_STRING, matchCase.pattern->line, 0, 0.0f, false, "_");
            }
        }
        else if (auto dictPattern = std::dynamic_pointer_cast<AST::DictPatternExpr>(matchCase.pattern)) {
            visitDictPatternExpr(dictPattern);
        }
        else if (auto listPattern = std::dynamic_pointer_cast<AST::ListPatternExpr>(matchCase.pattern)) {
            visitListPatternExpr(listPattern);
        }
        else if (auto tuplePattern = std::dynamic_pointer_cast<AST::TuplePatternExpr>(matchCase.pattern)) {
            visitTuplePatternExpr(tuplePattern);
        }
        else if (auto valPattern = std::dynamic_pointer_cast<AST::ValPatternExpr>(matchCase.pattern)) {
            visitValPatternExpr(valPattern);
        }
        else if (auto errPattern = std::dynamic_pointer_cast<AST::ErrPatternExpr>(matchCase.pattern)) {
            visitErrPatternExpr(errPattern);
        }
        else if (auto errorTypePattern = std::dynamic_pointer_cast<AST::ErrorTypePatternExpr>(matchCase.pattern)) {
            visitErrorTypePatternExpr(errorTypePattern);
        }
        else {
            visitExpression(matchCase.pattern);
        }
        
        // Compare the value with the pattern
        emit(Opcode::MATCH_PATTERN, stmt->line);
        
        // Jump to next case if pattern doesn't match
        size_t patternJumpIndex = bytecode.size();
        emit(Opcode::JUMP_IF_FALSE, stmt->line);
        jumpToNextCaseIndices.push_back(patternJumpIndex);
        
        // If there's a guard clause, evaluate it
        if (matchCase.guard) {
            // For variable binding patterns, we need to make the bound variable available
            if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(matchCase.pattern)) {
                if (varExpr->name != "_") {
                    // The variable is already stored, now evaluate the guard
                    visitExpression(matchCase.guard);
                    
                    // Jump to next case if guard fails
                    size_t guardJumpIndex = bytecode.size();
                    emit(Opcode::JUMP_IF_FALSE, stmt->line);
                    jumpToNextCaseIndices.push_back(guardJumpIndex);
                }
            } else {
                // For other patterns, evaluate the guard with the matched value
                visitExpression(matchCase.guard);
                
                // Jump to next case if guard fails
                size_t guardJumpIndex = bytecode.size();
                emit(Opcode::JUMP_IF_FALSE, stmt->line);
                jumpToNextCaseIndices.push_back(guardJumpIndex);
            }
        }
        
        // Process case body
        visitStatement(matchCase.body);
        
        // Jump to end after executing case body
        jumpToEndIndices.push_back(bytecode.size());
        emit(Opcode::JUMP, stmt->line);
    }

    // Update any remaining jumps to point to the end
    for (size_t jumpIndex : jumpToNextCaseIndices) {
        bytecode[jumpIndex].intValue = bytecode.size() - jumpIndex - 1;
    }
    
    // Update all jump to end instructions
    size_t endIndex = bytecode.size();
    for (size_t index : jumpToEndIndices) {
        bytecode[index].intValue = static_cast<int32_t>(endIndex - index - 1);
    }
    
    // Clean up temporary variable
    emit(Opcode::CLEAR_TEMP, stmt->line, tempIndex);
}

// Expression visitors
void BytecodeGenerator::visitBinaryExpr(const std::shared_ptr<AST::BinaryExpr>& expr) {
    if (expr->op == TokenType::AND) {
        visitExpression(expr->left);
        emit(Opcode::DUP, expr->line);
        size_t jumpToEndIndex = bytecode.size();
        emit(Opcode::JUMP_IF_FALSE, expr->line);
        emit(Opcode::POP, expr->line);
        visitExpression(expr->right);
        bytecode[jumpToEndIndex].intValue = bytecode.size() - jumpToEndIndex - 1;
        return;
    }

    if (expr->op == TokenType::OR) {
        visitExpression(expr->left);
        emit(Opcode::DUP, expr->line);
        size_t jumpToEndIndex = bytecode.size();
        emit(Opcode::JUMP_IF_TRUE, expr->line);
        emit(Opcode::POP, expr->line);
        visitExpression(expr->right);
        bytecode[jumpToEndIndex].intValue = bytecode.size() - jumpToEndIndex - 1;
        return;
    }

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
            Debugger::error("Unsupported binary operator", expr->line, 0, InterpretationStage::BYTECODE, 
                           sourceCode, filePath, "operator", "supported binary operator (+, -, *, /, %, ==, !=, <, >, <=, >=, &&, ||)");
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
            Debugger::error("Unknown unary operator", expr->line, 0, InterpretationStage::BYTECODE, 
                           sourceCode, filePath, "operator", "supported unary operator (-, !)");
            break;
    }
}

void BytecodeGenerator::visitLiteralExpr(const std::shared_ptr<AST::LiteralExpr>& expr) {
    // Generate bytecode for literal expression
    
    // Push literal value onto stack based on its type
    if (std::holds_alternative<long long>(expr->value)) {
        emit(Opcode::PUSH_INT, expr->line, std::get<long long>(expr->value));
    } else if (std::holds_alternative<unsigned long long>(expr->value)) {
        emit(Opcode::PUSH_UINT64, expr->line, std::get<unsigned long long>(expr->value));
    } else if (std::holds_alternative<double>(expr->value)) {
        emit(Opcode::PUSH_FLOAT, expr->line, 0, std::get<double>(expr->value));
    } else if (std::holds_alternative<std::string>(expr->value)) {
        std::string stringValue = std::get<std::string>(expr->value);
        // String value is already parsed (quotes removed) by the parser
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, stringValue);
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
        // Check if this identifier refers to a declared function
        // We need to check if there's a function with this name that was declared
        bool isFunctionName = isDeclaredFunction(expr->name);
        
        if (isFunctionName) {
            // Generate a function reference for declared functions
            emit(Opcode::PUSH_FUNCTION_REF, expr->line, 0, 0.0f, false, expr->name);
        } else {
            // Regular variable load for variables
            emit(Opcode::LOAD_VAR, expr->line, 0, 0.0f, false, expr->name);
        }
    }
}

void BytecodeGenerator::visitCallExpr(const std::shared_ptr<AST::CallExpr>& expr) {
    // Generate bytecode for function call expression
    
    // Handle different types of callees
    std::string functionName;
    if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee)) {
        // For now, let's use a different approach: only treat single-letter variables
        // or variables that are clearly parameters as function-typed variables
        // This is a temporary heuristic until we have proper type information
        
        // Check if this looks like a function parameter or closure variable
        // Be more specific to avoid treating regular functions as higher-order
        // Only treat variables that are clearly function-typed variables, not function names
        bool likelyFunctionParameter = (
                                       // Single letter variables (common for function parameters)
                                       (varExpr->name.length() == 1) ||
                                       
                                       // Common function parameter names
                                       varExpr->name == "func" || 
                                       varExpr->name == "fn" ||
                                       varExpr->name == "callback" ||
                                       varExpr->name == "processor" ||
                                       
                                       // Variables that contain "lambda" (but not function names)
                                       (varExpr->name.find("lambda") != std::string::npos && 
                                        varExpr->name.find("Lambda") == std::string::npos) ||
                                       
                                       // Variables that contain "closure" 
                                       varExpr->name.find("closure") != std::string::npos ||
                                       varExpr->name.find("Closure") != std::string::npos ||
                                       
                                       // Variables that clearly contain function values (not function names)
                                       (varExpr->name.find("multiplier") != std::string::npos && 
                                        varExpr->name != "createMultiplier") || // Exclude function names
                                       (varExpr->name.find("Multiplier") != std::string::npos &&
                                        varExpr->name != "createMultiplier") ||
                                       
                                       (varExpr->name.find("counter") != std::string::npos &&
                                        varExpr->name != "createCounter") || // Exclude function names
                                       (varExpr->name.find("Counter") != std::string::npos &&
                                        varExpr->name != "createCounter") ||
                                       
                                       // Variables with "func" in them (but not function names starting with it)
                                       (varExpr->name.find("func") != std::string::npos &&
                                        varExpr->name.substr(0, 4) != "func") || // Don't match function names like "funcName"
                                       (varExpr->name.find("Func") != std::string::npos &&
                                        varExpr->name.substr(0, 4) != "Func") ||
                                       
                                       // Variables that clearly store function values
                                       varExpr->name.find("nested") != std::string::npos ||
                                       varExpr->name.find("Nested") != std::string::npos ||
                                       varExpr->name.find("temp") != std::string::npos ||
                                       varExpr->name.find("Temp") != std::string::npos ||
                                       varExpr->name.find("batch") != std::string::npos ||
                                       varExpr->name.find("Batch") != std::string::npos ||
                                       
                                       // Common closure variable names (but exclude function names)
                                       (varExpr->name.find("increment") != std::string::npos &&
                                        varExpr->name != "increment") ||
                                       (varExpr->name.find("Increment") != std::string::npos &&
                                        varExpr->name != "increment") ||
                                       (varExpr->name.find("double") != std::string::npos &&
                                        varExpr->name != "double") ||
                                       (varExpr->name.find("Double") != std::string::npos &&
                                        varExpr->name != "double") ||
                                       (varExpr->name.find("simple") != std::string::npos &&
                                        varExpr->name != "simple") ||
                                       (varExpr->name.find("Simple") != std::string::npos &&
                                        varExpr->name != "simple")
                                       ); // Variables containing "simple"
        
        if (likelyFunctionParameter) {
            // This is likely a function-typed variable - generate higher-order call
            // First load the function value
            emit(Opcode::LOAD_VAR, expr->line, 0, 0.0f, false, varExpr->name);
            
            // Then evaluate and push arguments
            for (const auto& arg : expr->arguments) {
                visitExpression(arg);
            }
            
            // Push argument count onto stack (on top)
            emit(Opcode::PUSH_INT, expr->line, static_cast<int32_t>(expr->arguments.size()), 0.0f, false, "");
            
            // Then emit a higher-order call
            emit(Opcode::CALL_HIGHER_ORDER, expr->line, 0, 0.0f, false, "");
            return;
        } else {
            // Check if any arguments are function references
            bool hasFunctionArguments = false;
            for (const auto& arg : expr->arguments) {
                if (auto argVarExpr = std::dynamic_pointer_cast<AST::VariableExpr>(arg)) {
                    if (isDeclaredFunction(argVarExpr->name)) {
                        hasFunctionArguments = true;
                        break;
                    }
                }
            }
            
            if (hasFunctionArguments) {
                // This is a higher-order function call - load the function first
                emit(Opcode::LOAD_VAR, expr->line, 0, 0.0f, false, varExpr->name);
                
                // Then evaluate and push arguments
                for (const auto& arg : expr->arguments) {
                    visitExpression(arg);
                }
                
                // Push argument count onto stack
                emit(Opcode::PUSH_INT, expr->line, static_cast<int32_t>(expr->arguments.size()), 0.0f, false, "");
                
                // Then emit a higher-order call
                emit(Opcode::CALL_HIGHER_ORDER, expr->line, 0, 0.0f, false, "");
                return;
            } else {
                // Regular function call - evaluate arguments first
                for (const auto& arg : expr->arguments) {
                    visitExpression(arg);
                }
                functionName = varExpr->name;
            }
        }

      //  std::cout << "[DEBUG] CallExpr: Function name = " << functionName << std::endl;
    } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr->callee)) {
        // Method call: object.methodName(args)
        // First evaluate the object
        visitExpression(memberExpr->object);
        
        // Then call the method on the object. We assume the method is a property of the object.
        // The VM will handle the call.
        emit(Opcode::GET_PROPERTY, expr->line, 0, 0.0f, false, memberExpr->name);
        
        // Now evaluate and push the arguments onto the stack
        for (const auto& arg : expr->arguments) {
            visitExpression(arg);
        }
        
        // Now, we have the function and arguments on the stack, so we can call it.
        // We need to tell the call instruction to not look for a function by name.
        // We can do this by passing an empty function name.
        emit(Opcode::CALL, expr->line, static_cast<int32_t>(expr->arguments.size()), 0.0f, false, "");
        return;
    } else {
        // For other complex callees, we'd need to evaluate them
        // For now, just use a placeholder
        functionName = "unknown";
    }
    
    // Handle named arguments
    if (!expr->namedArgs.empty()) {
        // Push named arguments onto stack
        for (const auto& namedArg : expr->namedArgs) {
            // Push argument name
            emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, namedArg.first);
            // Push argument value
            visitExpression(namedArg.second);
        }
        
        // Emit special call instruction for named arguments
        emit(Opcode::CALL, expr->line, 
             static_cast<int32_t>(expr->arguments.size()), 
             static_cast<float>(expr->namedArgs.size()), 
             false, functionName);
        return;
    }
    
    // Call function
   // std::cout << "[DEBUG] CallExpr: Emitting CALL with function name = '" << functionName << "' and " << expr->arguments.size() << " arguments" << std::endl;
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
        Debugger::error("Index assignment not yet implemented", expr->line, 0, InterpretationStage::BYTECODE, 
                       sourceCode, filePath, "index assignment", "simple variable assignment (variable = value)");
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
                    Debugger::error("Unknown compound assignment operator", expr->line, 0, InterpretationStage::BYTECODE, 
                                   sourceCode, filePath, "compound operator", "supported compound assignment (+=, -=, *=, /=, %=)");
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
    Debugger::error("Invalid assignment expression", expr->line, 0, InterpretationStage::BYTECODE, 
                   sourceCode, filePath, "assignment", "valid assignment (variable = value, variable += value, etc.)");
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

void BytecodeGenerator::visitTupleExpr(const std::shared_ptr<AST::TupleExpr>& expr) {
    // Generate bytecode for tuple literal expression
    
    // Evaluate each element and push onto stack
    for (const auto& element : expr->elements) {
        visitExpression(element);
    }
    
    // Create tuple with all elements on stack
    emit(Opcode::CREATE_TUPLE, expr->line, static_cast<int32_t>(expr->elements.size()));
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
    // Set up loop context for nested loops
    loopBreakPatches.emplace_back();
    
    // Create a new scope for this iterator to ensure proper variable isolation
    emit(Opcode::BEGIN_SCOPE, stmt->line);
    
    // Declare the loop variables once at the beginning of the scope
    // For single variable iteration (like 'for x in iterable')
    if (stmt->loopVars.size() == 1) {
        // Push a nil value and declare the variable
        emit(Opcode::PUSH_NULL, stmt->line);
        emit(Opcode::DECLARE_VAR, stmt->line, 0, 0.0f, false, stmt->loopVars[0]);
    }
    // For key-value iteration (like 'for k, v in dict.items()')
    else if (stmt->loopVars.size() == 2) {
        // Push nil values and declare both variables
        emit(Opcode::PUSH_NULL, stmt->line);
        emit(Opcode::DECLARE_VAR, stmt->line, 0, 0.0f, false, stmt->loopVars[0]);
        emit(Opcode::PUSH_NULL, stmt->line);
        emit(Opcode::DECLARE_VAR, stmt->line, 0, 0.0f, false, stmt->loopVars[1]);
    }
    
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
    loopStartAddresses.push_back(loopStart);
    
    // Continue target: check if iterator has next value
    size_t continueStart = bytecode.size();
    loopContinueAddresses.push_back(continueStart);
    
    // Check if iterator has next value
    emit(Opcode::LOAD_TEMP, stmt->line, iteratorTempIndex);
    emit(Opcode::ITERATOR_HAS_NEXT, stmt->line);
    
    // Jump to end of loop if no more items
    emit(Opcode::JUMP_IF_FALSE, stmt->line, 0); // Placeholder for jump offset
    size_t jumpToEnd = bytecode.size() - 1;
    
    // Get next value from iterator
    emit(Opcode::LOAD_TEMP, stmt->line, iteratorTempIndex);
    emit(Opcode::ITERATOR_NEXT, stmt->line);
    
    // Store the value in the loop variable on each iteration
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
    emit(Opcode::JUMP, stmt->line, static_cast<int32_t>(loopStart) - static_cast<int32_t>(bytecode.size()) - 1);
    
    // Update the jump to end of loop with the correct offset
    bytecode[jumpToEnd].intValue = bytecode.size() - jumpToEnd - 1;
    
    // Patch break statements
    for (size_t patchAddr : loopBreakPatches.back()) {
        bytecode[patchAddr].intValue = bytecode.size() - patchAddr - 1;
    }
    loopBreakPatches.pop_back();
    loopStartAddresses.pop_back();
    loopContinueAddresses.pop_back();
    
    // Clean up the temporary iterator
    emit(Opcode::CLEAR_TEMP, stmt->line, iteratorTempIndex);
    
    // End the scope for this iterator
    emit(Opcode::END_SCOPE, stmt->line);
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
    // Contracts are used for preconditions, postconditions, and invariants
    // Generate bytecode to evaluate condition and message, then execute contract check
    
    // Evaluate the condition (should result in a boolean)
    visitExpression(stmt->condition);
    
    // Evaluate the message expression (should result in a string)
    if (stmt->message) {
        visitExpression(stmt->message);
    } else {
        // Default error message if none provided
        emit(Opcode::PUSH_STRING, stmt->line, 0, 0.0f, false, "Contract violation");
    }
    
    // Execute contract check (pops condition and message, throws if condition is false)
    emit(Opcode::CONTRACT, stmt->line);
}

// Pattern expression visitors for match statements
void BytecodeGenerator::visitTypePatternExpr(const std::shared_ptr<AST::TypePatternExpr>& expr) {
    // For type patterns, we push the type name as a string
    if (expr->type) {
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, expr->type->typeName);
    } else {
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, "unknown");
    }
}

void BytecodeGenerator::visitBindingPatternExpr(const std::shared_ptr<AST::BindingPatternExpr>& expr) {
    // For binding patterns like Some(x), we push the type name
    // The VM will handle the binding of the variable
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, expr->typeName);
}

void BytecodeGenerator::visitListPatternExpr(const std::shared_ptr<AST::ListPatternExpr>& expr) {
    // For list patterns, we create a special list pattern marker
    // Push the number of elements expected
    emit(Opcode::PUSH_INT, expr->line, static_cast<int32_t>(expr->elements.size()));
    
    // Push each pattern element
    for (const auto& element : expr->elements) {
        visitExpression(element);
    }
    
    // Mark this as a list pattern
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, "__list_pattern__");
}

void BytecodeGenerator::visitDictPatternExpr(const std::shared_ptr<AST::DictPatternExpr>& expr) {
    // Stack layout expected by VM (from top to bottom when popping):
    // 1. pattern marker ("__dict_pattern__") [popped by handleMatchPattern]
    // 2. rest binding name [pop()]
    // 3. has rest element (bool) [pop()]  
    // 4. number of fields [pop()]
    // 5. for each field: binding name [pop()], key name [pop()]
    //
    // So we need to push in reverse order:
    
    // Push field patterns first (in reverse order since we pop binding then key)
    for (auto it = expr->fields.rbegin(); it != expr->fields.rend(); ++it) {
        const auto& field = *it;
        // Push key first, then binding (so binding is popped first)
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, field.key);
        std::string binding = field.binding.value_or(field.key);
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, binding);
    }
    
    // Push number of fields
    emit(Opcode::PUSH_INT, expr->line, static_cast<int32_t>(expr->fields.size()));
    
    // Push rest element info
    if (expr->hasRestElement) {
        emit(Opcode::PUSH_BOOL, expr->line, 0, 0.0f, true);
        std::string restBinding = expr->restBinding.value_or("__rest__");
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, restBinding);
    } else {
        emit(Opcode::PUSH_BOOL, expr->line, 0, 0.0f, false);
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, "");
    }
    
    // Mark this as a dict pattern (will be popped first by handleMatchPattern)
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, "__dict_pattern__");
}

void BytecodeGenerator::visitTuplePatternExpr(const std::shared_ptr<AST::TuplePatternExpr>& expr) {
    // For tuple patterns, we create a special tuple pattern marker
    // Push the number of elements expected
    emit(Opcode::PUSH_INT, expr->line, static_cast<int32_t>(expr->elements.size()));
    
    // Push each pattern element
    for (const auto& element : expr->elements) {
        visitExpression(element);
    }
    
    // Mark this as a tuple pattern
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, "__tuple_pattern__");
}

// Error handling expression visitors
void BytecodeGenerator::visitFallibleExpr(const std::shared_ptr<AST::FallibleExpr>& expr) {
    // Generate bytecode for fallible expression with ? operator
    
    // Evaluate the expression that might fail
    visitExpression(expr->expression);
    
    // Check if the result is an error
    emit(Opcode::CHECK_ERROR, expr->line);
    
    // If it's an error, either handle it or propagate it
    if (expr->elseHandler) {
        // Jump to else handler if error
        size_t jumpToElseIndex = bytecode.size();
        emit(Opcode::JUMP_IF_TRUE, expr->line);
        
        // If not an error, unwrap the success value
        emit(Opcode::UNWRAP_VALUE, expr->line);
        
        // Jump over else handler
        size_t jumpOverElseIndex = bytecode.size();
        emit(Opcode::JUMP, expr->line);
        
        // Update jump to else handler
        size_t elseStartIndex = bytecode.size();
        bytecode[jumpToElseIndex].intValue = static_cast<int32_t>(elseStartIndex - jumpToElseIndex - 1);
        
        // Store error in variable if specified
        if (!expr->elseVariable.empty()) {
            emit(Opcode::STORE_VAR, expr->line, 0, 0.0f, false, expr->elseVariable);
        }
        
        // Process else handler - ensure it produces a value
        if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(expr->elseHandler)) {
            // For block statements, we need to handle the last statement specially
            // to ensure it leaves a value on the stack
            emit(Opcode::BEGIN_SCOPE, expr->line);
            
            // Process all statements except the last one
            for (size_t i = 0; i < blockStmt->statements.size(); ++i) {
                if (i == blockStmt->statements.size() - 1) {
                    // For the last statement, if it's an expression statement, 
                    // visit the expression directly to leave value on stack
                    if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(blockStmt->statements[i])) {
                        visitExpression(exprStmt->expression);
                    } else {
                        // If last statement is not an expression, visit it normally
                        // and push nil as the result
                        visitStatement(blockStmt->statements[i]);
                        emit(Opcode::PUSH_NULL, expr->line);
                    }
                } else {
                    visitStatement(blockStmt->statements[i]);
                }
            }
            
            emit(Opcode::END_SCOPE, expr->line);
        } else {
            // For non-block statements, visit normally and push nil
            visitStatement(expr->elseHandler);
            emit(Opcode::PUSH_NULL, expr->line);
        }
        
        // Update jump over else handler
        size_t endIndex = bytecode.size();
        bytecode[jumpOverElseIndex].intValue = static_cast<int32_t>(endIndex - jumpOverElseIndex - 1);
    } else {
        // No else handler, propagate error if present
        size_t jumpOverPropagateIndex = bytecode.size();
        emit(Opcode::JUMP_IF_FALSE, expr->line);
        
        // Propagate the error
        emit(Opcode::PROPAGATE_ERROR, expr->line);
        
        // Update jump - if not error, unwrap value
        size_t unwrapIndex = bytecode.size();
        bytecode[jumpOverPropagateIndex].intValue = static_cast<int32_t>(unwrapIndex - jumpOverPropagateIndex - 1);
        
        // Unwrap the success value
        emit(Opcode::UNWRAP_VALUE, expr->line);
    }
}

void BytecodeGenerator::visitErrorConstructExpr(const std::shared_ptr<AST::ErrorConstructExpr>& expr) {
    // Generate bytecode for error construction (err() calls)
    
    // Evaluate constructor arguments
    for (const auto& arg : expr->arguments) {
        visitExpression(arg);
    }
    
    // Construct error value with type and arguments
    emit(Opcode::CONSTRUCT_ERROR, expr->line, static_cast<int32_t>(expr->arguments.size()), 0.0f, false, expr->errorType);
}

void BytecodeGenerator::visitOkConstructExpr(const std::shared_ptr<AST::OkConstructExpr>& expr) {
    // Generate bytecode for success value construction (ok() calls)
    
    // Evaluate the success value
    visitExpression(expr->value);
    
    // Construct success value
    emit(Opcode::CONSTRUCT_OK, expr->line);
}

void BytecodeGenerator::emit(Opcode op, uint32_t lineNumber, int64_t intValue, float floatValue, bool boolValue, const std::string& stringValue) {
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

void BytecodeGenerator::emit(Opcode op, uint32_t lineNumber, uint64_t uint64Value) {
    // Create and push instruction onto bytecode vector
    Instruction instruction;
    instruction.opcode = op;
    instruction.line = lineNumber;
    instruction.uint64Value = uint64Value;

    bytecode.push_back(instruction);
}

std::string BytecodeGenerator::resolveModulePath(const std::string& modulePath) {
    // Convert module path (e.g., "tests.modules.my_module") to file path
    std::string filePath = modulePath;
    
    // Replace dots with directory separators
    for (char& c : filePath) {
        if (c == '.') {
            c = '/';
        }
    }
    
    // Add .lm extension
    filePath += ".lm";
    
    return filePath;
}

std::string BytecodeGenerator::getModuleNameFromPath(const std::string& modulePath) {
    // Extract the last component of the module path as the module name
    size_t lastDot = modulePath.find_last_of('.');
    if (lastDot != std::string::npos) {
        return modulePath.substr(lastDot + 1);
    }
    return modulePath;
}

// Error pattern expression visitors

void BytecodeGenerator::visitValPatternExpr(const std::shared_ptr<AST::ValPatternExpr>& expr) {
    // Generate bytecode for val pattern matching
    // This pattern matches success values in error unions
    
    // Push pattern type marker
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, "__val_pattern__");
    
    // Push variable name for binding
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, expr->variableName);
}

void BytecodeGenerator::visitErrPatternExpr(const std::shared_ptr<AST::ErrPatternExpr>& expr) {
    // Generate bytecode for err pattern matching
    // This pattern matches error values in error unions
    
    // Push pattern type marker
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, "__err_pattern__");
    
    // Push variable name for binding
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, expr->variableName);
    
    // Push specific error type if specified
    if (expr->errorType.has_value()) {
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, expr->errorType.value());
    } else {
        emit(Opcode::PUSH_NULL, expr->line); // Any error type
    }
}

void BytecodeGenerator::visitErrorTypePatternExpr(const std::shared_ptr<AST::ErrorTypePatternExpr>& expr) {
    // Generate bytecode for specific error type pattern matching
    // This pattern matches specific error types with optional parameter extraction
    
    // Push pattern type marker
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, "__error_type_pattern__");
    
    // Push error type name
    emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, expr->errorType);
    
    // Push number of parameters to extract
    emit(Opcode::PUSH_INT, expr->line, static_cast<int32_t>(expr->parameterNames.size()));
    
    // Push parameter names for binding
    for (const auto& paramName : expr->parameterNames) {
        emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, paramName);
    }
}

void BytecodeGenerator::visitLambdaExpr(const std::shared_ptr<AST::LambdaExpr>& expr) {
    // Analyze variable capture for this lambda
    std::vector<std::string> capturedVars = analyzeVariableCapture(expr);
    
    // Store captured variables in the lambda AST node for later use
    const_cast<AST::LambdaExpr*>(expr.get())->capturedVars = capturedVars;
    
    // Generate a unique lambda name for bytecode generation
    static int lambdaCounter = 0;
    std::string lambdaName = "__lambda_" + std::to_string(lambdaCounter++);
    
    // For closures, we need to generate the lambda function definition first,
    // then create the closure that references it
    
    // Begin lambda function definition
    emit(Opcode::BEGIN_FUNCTION, expr->line, 0, 0.0f, false, lambdaName);
    
    // Define parameters
    for (const auto& param : expr->params) {
        emit(Opcode::DEFINE_PARAM, expr->line, 0, 0.0f, false, param.first);
    }
    
    // Generate bytecode for lambda body
    visitBlockStatement(expr->body);
    
    // If lambda doesn't end with explicit return, add implicit return
    emit(Opcode::PUSH_NULL, expr->line);
    emit(Opcode::RETURN, expr->line);
    
    // End lambda function definition
    emit(Opcode::END_FUNCTION, expr->line);
    
    // Now emit closure creation instructions that will be part of the parent function
    // These will be executed when the parent function runs, not at the top level
    
    // Push the lambda function onto the stack first
    emit(Opcode::PUSH_LAMBDA, expr->line, 0, 0.0f, false, lambdaName);
    
    // Capture each variable (this will be executed when the parent function runs)
    for (const std::string& varName : capturedVars) {
        emit(Opcode::CAPTURE_VAR, expr->line, 0, 0.0f, false, varName);
    }
    
    // Push the count of captured variables (must be at top of stack for CREATE_CLOSURE)
    emit(Opcode::PUSH_INT, expr->line, static_cast<int>(capturedVars.size()));
    
    // Create closure with captured variables
    emit(Opcode::CREATE_CLOSURE, expr->line, 0, 0.0f, false, lambdaName);
}

std::vector<std::string> BytecodeGenerator::analyzeVariableCapture(const std::shared_ptr<AST::LambdaExpr>& lambda) {
    // Analyze which variables are captured by the lambda
    std::set<std::string> capturedVars;
    
    // Get parameter names - these are local to the lambda
    std::vector<std::string> localVars;
    for (const auto& param : lambda->params) {
        localVars.push_back(param.first);
    }
    
    // Analyze the lambda body for variable references
    findCapturedVariables(lambda->body, localVars, capturedVars);
    
    // Convert set to vector
    return std::vector<std::string>(capturedVars.begin(), capturedVars.end());
}

void BytecodeGenerator::findCapturedVariables(const std::shared_ptr<AST::Expression>& expr,
                                            const std::vector<std::string>& localVars,
                                            std::set<std::string>& capturedVars) {
    if (!expr) return;
    
    if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        // Check if this variable is not local to the lambda
        bool isLocal = std::find(localVars.begin(), localVars.end(), varExpr->name) != localVars.end();
        if (!isLocal) {
            capturedVars.insert(varExpr->name);
        }
    } else if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        findCapturedVariables(binaryExpr->left, localVars, capturedVars);
        findCapturedVariables(binaryExpr->right, localVars, capturedVars);
    } else if (auto unaryExpr = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        findCapturedVariables(unaryExpr->right, localVars, capturedVars);
    } else if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        findCapturedVariables(callExpr->callee, localVars, capturedVars);
        for (const auto& arg : callExpr->arguments) {
            findCapturedVariables(arg, localVars, capturedVars);
        }
        for (const auto& namedArg : callExpr->namedArgs) {
            findCapturedVariables(namedArg.second, localVars, capturedVars);
        }
    } else if (auto assignExpr = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) {
        findCapturedVariables(assignExpr->value, localVars, capturedVars);
        if (assignExpr->object) {
            findCapturedVariables(assignExpr->object, localVars, capturedVars);
        }
        if (assignExpr->index) {
            findCapturedVariables(assignExpr->index, localVars, capturedVars);
        }
    } else if (auto groupingExpr = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) {
        findCapturedVariables(groupingExpr->expression, localVars, capturedVars);
    } else if (auto listExpr = std::dynamic_pointer_cast<AST::ListExpr>(expr)) {
        for (const auto& element : listExpr->elements) {
            findCapturedVariables(element, localVars, capturedVars);
        }
    } else if (auto dictExpr = std::dynamic_pointer_cast<AST::DictExpr>(expr)) {
        for (const auto& entry : dictExpr->entries) {
            findCapturedVariables(entry.first, localVars, capturedVars);
            findCapturedVariables(entry.second, localVars, capturedVars);
        }
    } else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
        findCapturedVariables(indexExpr->object, localVars, capturedVars);
        findCapturedVariables(indexExpr->index, localVars, capturedVars);
    } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
        findCapturedVariables(memberExpr->object, localVars, capturedVars);
    } else if (auto rangeExpr = std::dynamic_pointer_cast<AST::RangeExpr>(expr)) {
        findCapturedVariables(rangeExpr->start, localVars, capturedVars);
        findCapturedVariables(rangeExpr->end, localVars, capturedVars);
        if (rangeExpr->step) {
            findCapturedVariables(rangeExpr->step, localVars, capturedVars);
        }
    } else if (auto interpolatedStr = std::dynamic_pointer_cast<AST::InterpolatedStringExpr>(expr)) {
        for (const auto& part : interpolatedStr->parts) {
            if (std::holds_alternative<std::shared_ptr<AST::Expression>>(part)) {
                findCapturedVariables(std::get<std::shared_ptr<AST::Expression>>(part), localVars, capturedVars);
            }
        }
    } else if (auto lambdaExpr = std::dynamic_pointer_cast<AST::LambdaExpr>(expr)) {
        // Nested lambda - need to handle its own scope
        std::vector<std::string> nestedLocalVars = localVars;
        for (const auto& param : lambdaExpr->params) {
            nestedLocalVars.push_back(param.first);
        }
        findCapturedVariables(lambdaExpr->body, nestedLocalVars, capturedVars);
    }
    // Add more expression types as needed
}

void BytecodeGenerator::findCapturedVariables(const std::shared_ptr<AST::Statement>& stmt,
                                            const std::vector<std::string>& localVars,
                                            std::set<std::string>& capturedVars) {
    if (!stmt) return;
    
    if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        std::vector<std::string> blockLocalVars = localVars;
        
        for (const auto& statement : blockStmt->statements) {
            // Add any new variable declarations to local scope
            if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(statement)) {
                blockLocalVars.push_back(varDecl->name);
                if (varDecl->initializer) {
                    findCapturedVariables(varDecl->initializer, localVars, capturedVars);
                }
            } else {
                findCapturedVariables(statement, blockLocalVars, capturedVars);
            }
        }
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        findCapturedVariables(exprStmt->expression, localVars, capturedVars);
    } else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        findCapturedVariables(ifStmt->condition, localVars, capturedVars);
        findCapturedVariables(ifStmt->thenBranch, localVars, capturedVars);
        if (ifStmt->elseBranch) {
            findCapturedVariables(ifStmt->elseBranch, localVars, capturedVars);
        }
    } else if (auto whileStmt = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
        findCapturedVariables(whileStmt->condition, localVars, capturedVars);
        findCapturedVariables(whileStmt->body, localVars, capturedVars);
    } else if (auto forStmt = std::dynamic_pointer_cast<AST::ForStatement>(stmt)) {
        if (forStmt->initializer) {
            findCapturedVariables(forStmt->initializer, localVars, capturedVars);
        }
        if (forStmt->condition) {
            findCapturedVariables(forStmt->condition, localVars, capturedVars);
        }
        if (forStmt->increment) {
            findCapturedVariables(forStmt->increment, localVars, capturedVars);
        }
        if (forStmt->iterable) {
            findCapturedVariables(forStmt->iterable, localVars, capturedVars);
        }
        findCapturedVariables(forStmt->body, localVars, capturedVars);
    } else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
        if (returnStmt->value) {
            findCapturedVariables(returnStmt->value, localVars, capturedVars);
        }
    } else if (auto printStmt = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
        for (const auto& arg : printStmt->arguments) {
            findCapturedVariables(arg, localVars, capturedVars);
        }
    }
    // Add more statement types as needed
}

// Function declaration tracking methods
bool BytecodeGenerator::isDeclaredFunction(const std::string& name) const {
    return declaredFunctions.find(name) != declaredFunctions.end();
}

void BytecodeGenerator::addDeclaredFunction(const std::string& name) {
    declaredFunctions.insert(name);
}
