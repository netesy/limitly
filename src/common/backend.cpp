#include "backend.hh"
#include <iostream>

BytecodeGenerator::BytecodeGenerator() {
    // We need to initialize the typeSystem and typeChecker here
    memoryManager = std::make_unique<MemoryManager<>>();
    region = std::make_unique<MemoryManager<>::Region>(*memoryManager);
    typeSystem = std::make_unique<TypeSystem>(*memoryManager, *region);
    typeChecker = std::make_unique<TypeChecker>(*typeSystem);
}


void BytecodeGenerator::process(const std::shared_ptr<AST::Program>& program) {
    for (const auto& stmt : program->statements) {
        visitStatement(stmt);
    }
}

void BytecodeGenerator::setSourceContext(const std::string& source, const std::string& filePath) {
    this->sourceCode = source;
    this->filePath = filePath;
    typeChecker->setSourceContext(source, filePath);
}

std::vector<TypeCheckError> BytecodeGenerator::performTypeChecking(const std::shared_ptr<AST::Program>& program) {
    return typeChecker->checkProgram(program);
}

void BytecodeGenerator::visitStatement(const std::shared_ptr<AST::Statement>& stmt) {
    if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        visitVarDeclaration(varDecl);
    } else if (auto printStmt = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
        visitPrintStatement(printStmt);
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        visitExprStatement(exprStmt);
    }
    // Add other statement types here
}

void BytecodeGenerator::visitExpression(const std::shared_ptr<AST::Expression>& expr) {
    if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        visitLiteralExpr(literalExpr);
    } else if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else if (auto variableExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        visitVariableExpr(variableExpr);
    }
    // Add other expression types here
}

void BytecodeGenerator::visitVarDeclaration(const std::shared_ptr<AST::VarDeclaration>& stmt) {
    if (stmt->initializer) {
        visitExpression(stmt->initializer);
    } else {
        emit(Opcode::PUSH_NULL, stmt->line);
    }
    emit(Opcode::STORE_VAR, stmt->line, 0, 0.0f, false, stmt->name);
}

void BytecodeGenerator::visitPrintStatement(const std::shared_ptr<AST::PrintStatement>& stmt) {
    visitExpression(stmt->expression);
    emit(Opcode::PRINT, stmt->line);
}

void BytecodeGenerator::visitExprStatement(const std::shared_ptr<AST::ExprStatement>& stmt) {
    visitExpression(stmt->expression);
    emit(Opcode::POP, stmt->line);
}

void BytecodeGenerator::visitBinaryExpr(const std::shared_ptr<AST::BinaryExpr>& expr) {
    visitExpression(expr->left);
    visitExpression(expr->right);
    switch (expr->op) {
        case TokenType::PLUS: emit(Opcode::ADD, expr->line); break;
        case TokenType::MINUS: emit(Opcode::SUBTRACT, expr->line); break;
        case TokenType::STAR: emit(Opcode::MULTIPLY, expr->line); break;
        case TokenType::SLASH: emit(Opcode::DIVIDE, expr->line); break;
        default:
            // Handle other binary operators
            break;
    }
}

void BytecodeGenerator::visitLiteralExpr(const std::shared_ptr<AST::LiteralExpr>& expr) {
    std::visit([this, expr](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, long long>) {
            emit(Opcode::PUSH_INT, expr->line, arg);
        } else if constexpr (std::is_same_v<T, unsigned long long>) {
            emit(Opcode::PUSH_UINT64, expr->line, arg);
        } else if constexpr (std::is_same_v<T, double>) {
            emit(Opcode::PUSH_FLOAT, expr->line, 0, static_cast<float>(arg));
        } else if constexpr (std::is_same_v<T, std::string>) {
            emit(Opcode::PUSH_STRING, expr->line, 0, 0.0f, false, arg);
        } else if constexpr (std::is_same_v<T, bool>) {
            emit(Opcode::PUSH_BOOL, expr->line, 0, 0.0f, arg);
        } else if constexpr (std::is_same_v<T, std::nullptr_t>) {
            emit(Opcode::PUSH_NULL, expr->line);
        }
    }, expr->value);
}

void BytecodeGenerator::visitVariableExpr(const std::shared_ptr<AST::VariableExpr>& expr) {
    emit(Opcode::LOAD_VAR, expr->line, 0, 0.0f, false, expr->name);
}

void BytecodeGenerator::emit(Opcode op, uint32_t lineNumber, int64_t intValue, float floatValue, bool boolValue, const std::string& stringValue) {
    bytecode.push_back({op, lineNumber, intValue, floatValue, boolValue, stringValue});
}

void BytecodeGenerator::emit(Opcode op, uint32_t lineNumber, uint64_t uint64Value) {
    bytecode.push_back({op, lineNumber, 0, 0.0f, false, "", uint64Value});
}
