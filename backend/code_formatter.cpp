#include "code_formatter.hh"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <vector>

CodeFormatter::CodeFormatter() {
    // Initialize with default settings
}

std::string CodeFormatter::format(const std::shared_ptr<AST::Program>& program) {
    return format(program, "");
}

std::string CodeFormatter::format(const std::shared_ptr<AST::Program>& program, const std::string& sourceText) {
    output.str("");
    output.clear();
    currentIndent = 0;
    
    // Store the original source text for fallback formatting
    originalSource = sourceText;
    sourceLines.clear();
    
    // Split source into lines for easy access
    if (!sourceText.empty()) {
        std::istringstream stream(sourceText);
        std::string line;
        while (std::getline(stream, line)) {
            sourceLines.push_back(line);
        }
    }
    
    if (!program) {
        return "";
    }
    
    // Format all statements in the program
    for (size_t i = 0; i < program->statements.size(); ++i) {
        if (i > 0) {
            writeLine(); // Add blank line between top-level statements
        }
        formatStatement(program->statements[i]);
    }
    
    return output.str();
}

std::string CodeFormatter::getIndent() const {
    if (useSpaces) {
        return std::string(currentIndent * indentSize, ' ');
    } else {
        return std::string(currentIndent, '\t');
    }
}

void CodeFormatter::increaseIndent() {
    currentIndent++;
}

void CodeFormatter::decreaseIndent() {
    if (currentIndent > 0) {
        currentIndent--;
    }
}

void CodeFormatter::writeLine(const std::string& line) {
    if (!line.empty()) {
        output << getIndent() << line;
    }
    output << "\n";
}

void CodeFormatter::write(const std::string& text) {
    output << text;
}

void CodeFormatter::writeIndented(const std::string& text) {
    output << getIndent() << text;
}

void CodeFormatter::formatStatement(const std::shared_ptr<AST::Statement>& stmt) {
    if (!stmt) return;
    
    try {
        // Handle different statement types
        if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
            formatVarDeclaration(varDecl);
        } else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            formatFunctionDeclaration(funcDecl);
        } else if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(stmt)) {
            formatClassDeclaration(classDecl);
        } else if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
            formatBlockStatement(blockStmt);
        } else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
            formatIfStatement(ifStmt);
        } else if (auto forStmt = std::dynamic_pointer_cast<AST::ForStatement>(stmt)) {
            formatForStatement(forStmt);
        } else if (auto whileStmt = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
            formatWhileStatement(whileStmt);
        } else if (auto iterStmt = std::dynamic_pointer_cast<AST::IterStatement>(stmt)) {
            formatIterStatement(iterStmt);
        } else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
            formatReturnStatement(returnStmt);
        } else if (auto printStmt = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
            formatPrintStatement(printStmt);
        } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
            formatExprStatement(exprStmt);
        } else if (auto attemptStmt = std::dynamic_pointer_cast<AST::AttemptStatement>(stmt)) {
            formatAttemptStatement(attemptStmt);
        } else if (auto parallelStmt = std::dynamic_pointer_cast<AST::ParallelStatement>(stmt)) {
            formatParallelStatement(parallelStmt);
        } else if (auto concurrentStmt = std::dynamic_pointer_cast<AST::ConcurrentStatement>(stmt)) {
            formatConcurrentStatement(concurrentStmt);
        } else if (auto matchStmt = std::dynamic_pointer_cast<AST::MatchStatement>(stmt)) {
            formatMatchStatement(matchStmt);
        } else if (auto enumDecl = std::dynamic_pointer_cast<AST::EnumDeclaration>(stmt)) {
            formatEnumDeclaration(enumDecl);
        } else {
            // Unknown statement type - output original with comment
            outputUnformattedStatement(stmt, "Unknown statement type");
        }
    } catch (const std::exception& e) {
        // Formatting failed - output original with error comment
        outputUnformattedStatement(stmt, std::string("Formatting error: ") + e.what());
    } catch (...) {
        // Unknown error - output original with generic comment
        outputUnformattedStatement(stmt, "Unknown formatting error");
    }
}

void CodeFormatter::formatVarDeclaration(const std::shared_ptr<AST::VarDeclaration>& stmt) {
    writeIndented("var " + stmt->name);
    
    if (stmt->type.has_value()) {
        write(": " + formatTypeAnnotation(stmt->type.value()));
    }
    
    if (stmt->initializer) {
        write(" = " + formatExpression(stmt->initializer));
    }
    
    write(";");
    writeLine();
}

void CodeFormatter::formatFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    writeIndented("fn " + stmt->name + "(");
    
    // Format parameters
    bool first = true;
    for (const auto& param : stmt->params) {
        if (!first) write(", ");
        write(param.first);
        if (param.second) {
            write(": " + formatTypeAnnotation(param.second));
        }
        first = false;
    }
    
    // Format optional parameters
    for (const auto& param : stmt->optionalParams) {
        if (!first) write(", ");
        write(param.first);
        if (param.second.first) {
            write(": " + formatTypeAnnotation(param.second.first));
        }
        if (param.second.second) {
            write(" = " + formatExpression(param.second.second));
        }
        first = false;
    }
    
    write(")");
    
    if (stmt->returnType) {
        write(": " + formatTypeAnnotation(stmt->returnType.value()));
    }
    
    if (stmt->throws) {
        write(" throws");
    }
    
    writeLine(" {");
    increaseIndent();
    formatBlockStatement(stmt->body);
    decreaseIndent();
    writeLine("}");
}

void CodeFormatter::formatClassDeclaration(const std::shared_ptr<AST::ClassDeclaration>& stmt) {
    writeIndented("class " + stmt->name);
    
    // Note: superclass field may not exist in current AST structure
    // if (stmt->superclass) {
    //     write(" extends " + formatExpression(stmt->superclass));
    // }
    
    writeLine(" {");
    increaseIndent();
    
    // Format fields
    for (const auto& field : stmt->fields) {
        formatStatement(field);
    }
    
    if (!stmt->fields.empty() && !stmt->methods.empty()) {
        writeLine(); // Blank line between fields and methods
    }
    
    // Format methods
    for (const auto& method : stmt->methods) {
        formatStatement(method);
        writeLine(); // Blank line after each method
    }
    
    decreaseIndent();
    writeLine("}");
}

void CodeFormatter::formatBlockStatement(const std::shared_ptr<AST::BlockStatement>& stmt) {
    for (const auto& statement : stmt->statements) {
        formatStatement(statement);
    }
}

void CodeFormatter::formatIfStatement(const std::shared_ptr<AST::IfStatement>& stmt) {
    writeIndented("if (" + formatExpression(stmt->condition) + ") {");
    writeLine();
    increaseIndent();
    formatStatement(stmt->thenBranch);
    decreaseIndent();
    
    if (stmt->elseBranch) {
        writeLine("} else {");
        increaseIndent();
        formatStatement(stmt->elseBranch);
        decreaseIndent();
    }
    
    writeLine("}");
}

void CodeFormatter::formatForStatement(const std::shared_ptr<AST::ForStatement>& stmt) {
    writeIndented("for (");
    
    if (stmt->initializer) {
        // For statement initializer is a statement, not expression
        // We'll need to handle this differently - for now, skip complex formatting
        write("/* initializer */");
    }
    write("; ");
    
    if (stmt->condition) {
        write(formatExpression(stmt->condition));
    }
    write("; ");
    
    if (stmt->increment) {
        write(formatExpression(stmt->increment));
    }
    
    writeLine(") {");
    increaseIndent();
    formatStatement(stmt->body);
    decreaseIndent();
    writeLine("}");
}

void CodeFormatter::formatWhileStatement(const std::shared_ptr<AST::WhileStatement>& stmt) {
    writeIndented("while (" + formatExpression(stmt->condition) + ") {");
    writeLine();
    increaseIndent();
    formatStatement(stmt->body);
    decreaseIndent();
    writeLine("}");
}

void CodeFormatter::formatIterStatement(const std::shared_ptr<AST::IterStatement>& stmt) {
    writeIndented("iter (");
    
    // Format loop variables
    for (size_t i = 0; i < stmt->loopVars.size(); ++i) {
        if (i > 0) write(", ");
        write(stmt->loopVars[i]);
    }
    
    write(" in " + formatExpression(stmt->iterable) + ") {");
    writeLine();
    increaseIndent();
    formatStatement(stmt->body);
    decreaseIndent();
    writeLine("}");
}

void CodeFormatter::formatReturnStatement(const std::shared_ptr<AST::ReturnStatement>& stmt) {
    writeIndented("return");
    if (stmt->value) {
        write(" " + formatExpression(stmt->value));
    }
    write(";");
    writeLine();
}

void CodeFormatter::formatPrintStatement(const std::shared_ptr<AST::PrintStatement>& stmt) {
    writeIndented("print(");
    
    for (size_t i = 0; i < stmt->arguments.size(); ++i) {
        if (i > 0) write(", ");
        write(formatExpression(stmt->arguments[i]));
    }
    
    write(");");
    writeLine();
}

void CodeFormatter::formatExprStatement(const std::shared_ptr<AST::ExprStatement>& stmt) {
    writeIndented(formatExpression(stmt->expression));
    write(";");
    writeLine();
}

void CodeFormatter::formatAttemptStatement(const std::shared_ptr<AST::AttemptStatement>& stmt) {
    writeIndented("attempt {");
    writeLine();
    increaseIndent();
    formatStatement(stmt->tryBlock);
    decreaseIndent();
    
    for (const auto& handler : stmt->handlers) {
        writeLine("} handle " + handler.errorType + " {");
        increaseIndent();
        formatStatement(handler.body);
        decreaseIndent();
    }
    
    writeLine("}");
}

void CodeFormatter::formatParallelStatement(const std::shared_ptr<AST::ParallelStatement>& stmt) {
    writeIndented("parallel {");
    writeLine();
    increaseIndent();
    formatStatement(stmt->body);
    decreaseIndent();
    writeLine("}");
}

void CodeFormatter::formatConcurrentStatement(const std::shared_ptr<AST::ConcurrentStatement>& stmt) {
    writeIndented("concurrent {");
    writeLine();
    increaseIndent();
    formatStatement(stmt->body);
    decreaseIndent();
    writeLine("}");
}

void CodeFormatter::formatMatchStatement(const std::shared_ptr<AST::MatchStatement>& stmt) {
    writeIndented("match (" + formatExpression(stmt->value) + ") {");
    writeLine();
    increaseIndent();
    
    for (const auto& matchCase : stmt->cases) {
        writeIndented("case " + formatExpression(matchCase.pattern) + " => {");
        writeLine();
        increaseIndent();
        formatStatement(matchCase.body);
        decreaseIndent();
        writeLine("}");
    }
    
    decreaseIndent();
    writeLine("}");
}

void CodeFormatter::formatEnumDeclaration(const std::shared_ptr<AST::EnumDeclaration>& stmt) {
    writeIndented("enum " + stmt->name + " {");
    writeLine();
    increaseIndent();
    
    for (size_t i = 0; i < stmt->variants.size(); ++i) {
        writeIndented(stmt->variants[i].first);
        if (stmt->variants[i].second.has_value()) {
            write(": " + formatTypeAnnotation(stmt->variants[i].second.value()));
        }
        if (i < stmt->variants.size() - 1) {
            write(",");
        }
        writeLine();
    }
    
    decreaseIndent();
    writeLine("}");
}

std::string CodeFormatter::formatExpression(const std::shared_ptr<AST::Expression>& expr) {
    if (!expr) return "";
    
    try {
        if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
            return formatBinaryExpr(binaryExpr);
        } else if (auto unaryExpr = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
            return formatUnaryExpr(unaryExpr);
        } else if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
            return formatLiteralExpr(literalExpr);
        } else if (auto variableExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
            return formatVariableExpr(variableExpr);
        } else if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
            return formatCallExpr(callExpr);
        } else if (auto assignExpr = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) {
            return formatAssignExpr(assignExpr);
        } else if (auto ternaryExpr = std::dynamic_pointer_cast<AST::TernaryExpr>(expr)) {
            return formatTernaryExpr(ternaryExpr);
        } else if (auto groupingExpr = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) {
            return formatGroupingExpr(groupingExpr);
        } else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
            return formatIndexExpr(indexExpr);
        } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
            return formatMemberExpr(memberExpr);
        } else if (auto listExpr = std::dynamic_pointer_cast<AST::ListExpr>(expr)) {
            return formatListExpr(listExpr);
        } else if (auto dictExpr = std::dynamic_pointer_cast<AST::DictExpr>(expr)) {
            return formatDictExpr(dictExpr);
        } else if (auto rangeExpr = std::dynamic_pointer_cast<AST::RangeExpr>(expr)) {
            return formatRangeExpr(rangeExpr);
        } else if (auto awaitExpr = std::dynamic_pointer_cast<AST::AwaitExpr>(expr)) {
            return formatAwaitExpr(awaitExpr);
        } else if (auto interpolatedStringExpr = std::dynamic_pointer_cast<AST::InterpolatedStringExpr>(expr)) {
            return formatInterpolatedStringExpr(interpolatedStringExpr);
        } else {
            // Unknown expression type - return placeholder with type info
            return getUnformattedExpression(expr, "Unknown expression type");
        }
    } catch (const std::exception& e) {
        // Formatting failed - return placeholder with error info
        return getUnformattedExpression(expr, std::string("Formatting error: ") + e.what());
    } catch (...) {
        // Unknown error - return placeholder with generic error
        return getUnformattedExpression(expr, "Unknown formatting error");
    }
}

std::string CodeFormatter::formatBinaryExpr(const std::shared_ptr<AST::BinaryExpr>& expr) {
    std::string left = formatExpression(expr->left);
    std::string right = formatExpression(expr->right);
    
    // Add parentheses if needed based on precedence
    if (needsParentheses(expr->left, expr)) {
        left = "(" + left + ")";
    }
    if (needsParentheses(expr->right, expr)) {
        right = "(" + right + ")";
    }
    
    return left + " " + tokenTypeToString(expr->op) + " " + right;
}

std::string CodeFormatter::formatUnaryExpr(const std::shared_ptr<AST::UnaryExpr>& expr) {
    std::string operand = formatExpression(expr->right);
    
    if (needsParentheses(expr->right, expr)) {
        operand = "(" + operand + ")";
    }
    
    return tokenTypeToString(expr->op) + operand;
}

std::string CodeFormatter::formatLiteralExpr(const std::shared_ptr<AST::LiteralExpr>& expr) {
    return std::visit([this](const auto& value) -> std::string {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<T, int>) {
            return std::to_string(value);
        } else if constexpr (std::is_same_v<T, double>) {
            return std::to_string(value);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return "\"" + escapeString(value) + "\"";
        } else if constexpr (std::is_same_v<T, bool>) {
            return value ? "true" : "false";
        } else if constexpr (std::is_same_v<T, std::nullptr_t>) {
            return "nil";
        }
        return "<unknown literal>";
    }, expr->value);
}

std::string CodeFormatter::formatVariableExpr(const std::shared_ptr<AST::VariableExpr>& expr) {
    return expr->name;
}

std::string CodeFormatter::formatCallExpr(const std::shared_ptr<AST::CallExpr>& expr) {
    std::string result = formatExpression(expr->callee) + "(";
    
    for (size_t i = 0; i < expr->arguments.size(); ++i) {
        if (i > 0) result += ", ";
        result += formatExpression(expr->arguments[i]);
    }
    
    result += ")";
    return result;
}

std::string CodeFormatter::formatAssignExpr(const std::shared_ptr<AST::AssignExpr>& expr) {
    std::string target;
    if (expr->object) {
        // Member or index assignment
        target = formatExpression(expr->object);
        if (expr->member) {
            target += "." + expr->member.value();
        } else if (expr->index) {
            target += "[" + formatExpression(expr->index) + "]";
        }
    } else {
        // Simple variable assignment
        target = expr->name;
    }
    
    return target + " " + tokenTypeToString(expr->op) + " " + formatExpression(expr->value);
}

std::string CodeFormatter::formatTernaryExpr(const std::shared_ptr<AST::TernaryExpr>& expr) {
    return formatExpression(expr->condition) + " ? " + 
           formatExpression(expr->thenBranch) + " : " + 
           formatExpression(expr->elseBranch);
}

std::string CodeFormatter::formatGroupingExpr(const std::shared_ptr<AST::GroupingExpr>& expr) {
    return "(" + formatExpression(expr->expression) + ")";
}

std::string CodeFormatter::formatIndexExpr(const std::shared_ptr<AST::IndexExpr>& expr) {
    return formatExpression(expr->object) + "[" + formatExpression(expr->index) + "]";
}

std::string CodeFormatter::formatMemberExpr(const std::shared_ptr<AST::MemberExpr>& expr) {
    return formatExpression(expr->object) + "." + expr->name;
}

std::string CodeFormatter::formatListExpr(const std::shared_ptr<AST::ListExpr>& expr) {
    std::string result = "[";
    
    for (size_t i = 0; i < expr->elements.size(); ++i) {
        if (i > 0) result += ", ";
        result += formatExpression(expr->elements[i]);
    }
    
    result += "]";
    return result;
}

std::string CodeFormatter::formatDictExpr(const std::shared_ptr<AST::DictExpr>& expr) {
    std::string result = "{";
    
    for (size_t i = 0; i < expr->entries.size(); ++i) {
        if (i > 0) result += ", ";
        result += formatExpression(expr->entries[i].first) + ": " + formatExpression(expr->entries[i].second);
    }
    
    result += "}";
    return result;
}

std::string CodeFormatter::formatRangeExpr(const std::shared_ptr<AST::RangeExpr>& expr) {
    return formatExpression(expr->start) + ".." + formatExpression(expr->end);
}

std::string CodeFormatter::formatAwaitExpr(const std::shared_ptr<AST::AwaitExpr>& expr) {
    return "await " + formatExpression(expr->expression);
}

std::string CodeFormatter::formatInterpolatedStringExpr(const std::shared_ptr<AST::InterpolatedStringExpr>& expr) {
    std::string result = "\"";
    
    for (const auto& part : expr->parts) {
        if (std::holds_alternative<std::string>(part)) {
            // String literal part - escape it properly
            result += escapeString(std::get<std::string>(part));
        } else if (std::holds_alternative<std::shared_ptr<AST::Expression>>(part)) {
            // Expression part - format it within braces
            result += "{" + formatExpression(std::get<std::shared_ptr<AST::Expression>>(part)) + "}";
        }
    }
    
    result += "\"";
    return result;
}

std::string CodeFormatter::formatTypeAnnotation(const std::shared_ptr<AST::TypeAnnotation>& type) {
    if (!type) return "";
    
    std::string result = type->typeName;
    
    // Handle optional types
    if (type->isOptional) {
        result += "?";
    }
    
    // Handle list types
    if (type->isList && type->elementType) {
        result = "[" + formatTypeAnnotation(type->elementType) + "]";
    }
    
    // Handle union types
    if (type->isUnion && !type->unionTypes.empty()) {
        result = "";
        for (size_t i = 0; i < type->unionTypes.size(); ++i) {
            if (i > 0) result += " | ";
            result += formatTypeAnnotation(type->unionTypes[i]);
        }
    }
    
    // Handle intersection types (if supported)
    // Note: intersectionTypes field may not exist in current AST structure
    
    // Handle function types
    if (type->isFunction) {
        result = "(";
        for (size_t i = 0; i < type->functionParams.size(); ++i) {
            if (i > 0) result += ", ";
            result += formatTypeAnnotation(type->functionParams[i]);
        }
        result += ") -> ";
        if (type->returnType) {
            result += formatTypeAnnotation(type->returnType);
        } else {
            result += "void";
        }
    }
    
    // Handle structural types
    if (type->isStructural && !type->structuralFields.empty()) {
        result = "{";
        for (size_t i = 0; i < type->structuralFields.size(); ++i) {
            if (i > 0) result += ", ";
            result += type->structuralFields[i].name + ": " + formatTypeAnnotation(type->structuralFields[i].type);
        }
        // Note: isExtensible field may not exist in current AST structure
        result += "}";
    }
    
    return result;
}

std::string CodeFormatter::escapeString(const std::string& str) {
    std::ostringstream out;
    for (char c : str) {
        switch (c) {
            case '\n': out << "\\n"; break;
            case '\r': out << "\\r"; break;
            case '\t': out << "\\t"; break;
            case '\\': out << "\\\\"; break;
            case '"': out << "\\\""; break;
            default: out << c; break;
        }
    }
    return out.str();
}

std::string CodeFormatter::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::PLUS: return "+";
        case TokenType::MINUS: return "-";
        case TokenType::STAR: return "*";
        case TokenType::SLASH: return "/";
        case TokenType::MODULUS: return "%";
        case TokenType::EQUAL_EQUAL: return "==";
        case TokenType::BANG_EQUAL: return "!=";
        case TokenType::LESS: return "<";
        case TokenType::LESS_EQUAL: return "<=";
        case TokenType::GREATER: return ">";
        case TokenType::GREATER_EQUAL: return ">=";
        case TokenType::AND: return "and";
        case TokenType::OR: return "or";
        case TokenType::BANG: return "!";
        case TokenType::EQUAL: return "=";
        case TokenType::PLUS_EQUAL: return "+=";
        case TokenType::MINUS_EQUAL: return "-=";
        case TokenType::STAR_EQUAL: return "*=";
        case TokenType::SLASH_EQUAL: return "/=";
        default: return "?";
    }
}

bool CodeFormatter::needsParentheses(const std::shared_ptr<AST::Expression>& expr, const std::shared_ptr<AST::Expression>& parent) {
    // Simple precedence check - can be expanded
    if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        if (auto binaryParent = std::dynamic_pointer_cast<AST::BinaryExpr>(parent)) {
            int exprPrec = getOperatorPrecedence(tokenTypeToString(binaryExpr->op));
            int parentPrec = getOperatorPrecedence(tokenTypeToString(binaryParent->op));
            return exprPrec < parentPrec;
        }
    }
    return false;
}

int CodeFormatter::getOperatorPrecedence(const std::string& op) {
    // Operator precedence (higher number = higher precedence)
    if (op == "or") return 1;
    if (op == "and") return 2;
    if (op == "==" || op == "!=" || op == "<" || op == "<=" || op == ">" || op == ">=") return 3;
    if (op == "+" || op == "-") return 4;
    if (op == "*" || op == "/" || op == "%") return 5;
    if (op == "!") return 6;
    return 0;
}

void CodeFormatter::outputUnformattedStatement(const std::shared_ptr<AST::Statement>& stmt, const std::string& reason) {
    // Try to get original source text if available
    std::string originalText = getOriginalText(stmt);
    
    if (originalText.empty()) {
        // Fallback: generate a placeholder
        originalText = generateStatementPlaceholder(stmt);
    }
    
    // Output the original text
    writeIndented(originalText);
    writeLine();
    
    // Add explanatory comment
    writeIndented("// FORMATTER: Could not format - " + reason);
    writeLine();
}

std::string CodeFormatter::getUnformattedExpression(const std::shared_ptr<AST::Expression>& expr, const std::string& reason) {
    // Try to get original source text if available
    std::string originalText = getOriginalText(expr);
    
    if (originalText.empty()) {
        // Fallback: generate a placeholder
        originalText = generateExpressionPlaceholder(expr);
    }
    
    // Return original text with inline comment
    return originalText + " /* FORMATTER: Could not format - " + reason + " */";
}

std::string CodeFormatter::getOriginalText(const std::shared_ptr<AST::Node>& node) {
    if (!node || sourceLines.empty()) {
        return "";
    }
    
    // Get the line number from the AST node (1-based)
    int lineNumber = node->line;
    
    // Convert to 0-based index and check bounds
    if (lineNumber < 1 || lineNumber > static_cast<int>(sourceLines.size())) {
        return "";
    }
    
    // Return the original line from the source
    return sourceLines[lineNumber - 1];
}

std::string CodeFormatter::generateStatementPlaceholder(const std::shared_ptr<AST::Statement>& stmt) {
    // Generate a descriptive placeholder based on statement type
    if (std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        return "/* variable declaration */";
    } else if (std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
        return "/* function declaration */";
    } else if (std::dynamic_pointer_cast<AST::ClassDeclaration>(stmt)) {
        return "/* class declaration */";
    } else if (std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        return "/* if statement */";
    } else if (std::dynamic_pointer_cast<AST::ForStatement>(stmt)) {
        return "/* for statement */";
    } else if (std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
        return "/* while statement */";
    } else if (std::dynamic_pointer_cast<AST::IterStatement>(stmt)) {
        return "/* iter statement */";
    } else if (std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
        return "/* return statement */";
    } else if (std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
        return "/* print statement */";
    } else if (std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        return "/* expression statement */";
    } else if (std::dynamic_pointer_cast<AST::AttemptStatement>(stmt)) {
        return "/* attempt statement */";
    } else if (std::dynamic_pointer_cast<AST::ParallelStatement>(stmt)) {
        return "/* parallel statement */";
    } else if (std::dynamic_pointer_cast<AST::ConcurrentStatement>(stmt)) {
        return "/* concurrent statement */";
    } else if (std::dynamic_pointer_cast<AST::MatchStatement>(stmt)) {
        return "/* match statement */";
    } else if (std::dynamic_pointer_cast<AST::EnumDeclaration>(stmt)) {
        return "/* enum declaration */";
    } else if (std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        return "/* block statement */";
    }
    
    return "/* unknown statement */";
}

std::string CodeFormatter::generateExpressionPlaceholder(const std::shared_ptr<AST::Expression>& expr) {
    // Generate a descriptive placeholder based on expression type
    if (std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        return "/* binary expression */";
    } else if (std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        return "/* unary expression */";
    } else if (std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        return "/* literal expression */";
    } else if (std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        return "/* variable expression */";
    } else if (std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        return "/* call expression */";
    } else if (std::dynamic_pointer_cast<AST::AssignExpr>(expr)) {
        return "/* assignment expression */";
    } else if (std::dynamic_pointer_cast<AST::TernaryExpr>(expr)) {
        return "/* ternary expression */";
    } else if (std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) {
        return "/* grouping expression */";
    } else if (std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
        return "/* index expression */";
    } else if (std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
        return "/* member expression */";
    } else if (std::dynamic_pointer_cast<AST::ListExpr>(expr)) {
        return "/* list expression */";
    } else if (std::dynamic_pointer_cast<AST::DictExpr>(expr)) {
        return "/* dictionary expression */";
    } else if (std::dynamic_pointer_cast<AST::RangeExpr>(expr)) {
        return "/* range expression */";
    } else if (std::dynamic_pointer_cast<AST::AwaitExpr>(expr)) {
        return "/* await expression */";
    }
    
    return "/* unknown expression */";
}