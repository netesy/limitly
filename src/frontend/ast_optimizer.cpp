#include "ast.hh"
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace AST {

// Helper function to infer type of a literal value (similar to type checker)
TypePtr inferLiteralType(const std::variant<std::string, bool, std::nullptr_t>& value) {
    if (std::holds_alternative<std::string>(value)) {
        const std::string& str = std::get<std::string>(value);
        
        // Check if it's a numeric string
        bool is_numeric = !str.empty() && (str[0] == '-' || str[0] == '+' || 
                          (str[0] >= '0' && str[0] <= '9'));
        for (size_t i = 1; i < str.size() && is_numeric; i++) {
            if (str[i] != '.' && !(str[i] >= '0' && str[i] <= '9')) {
                is_numeric = false;
            }
        }
        
        if (is_numeric) {
            // Check if it contains a decimal point to determine if it's a float
            bool is_float = false;
            for (size_t i = 0; i < str.size(); i++) {
                if (str[i] == '.') {
                    is_float = true;
                    break;
                }
            }
            
            if (is_float) {
                return std::make_shared<::Type>(::TypeTag::Float64);
            } else {
                return std::make_shared<::Type>(::TypeTag::Int64);
            }
        } else {
            return std::make_shared<::Type>(::TypeTag::String);
        }
    } else if (std::holds_alternative<bool>(value)) {
        return std::make_shared<::Type>(::TypeTag::Bool);
    } else if (std::holds_alternative<std::nullptr_t>(value)) {
        return std::make_shared<::Type>(::TypeTag::Nil);
    }
    
    return std::make_shared<::Type>(::TypeTag::Any);
}
std::shared_ptr<LiteralExpr> createBoolLiteral(bool value, int line) {
    auto result = std::make_shared<LiteralExpr>();
    result->value = value;
    result->line = line;
    // Set inferred type for boolean
    result->inferred_type = std::make_shared<::Type>(::TypeTag::Bool);
    return result;
}

// Helper function to create string literals
std::shared_ptr<LiteralExpr> createStringLiteral(const std::string& value, int line) {
    auto result = std::make_shared<LiteralExpr>();
    result->value = value;
    result->line = line;
    result->literalType = TokenType::STRING;
    result->inferred_type = std::make_shared<::Type>(::TypeTag::String);
    return result;
}

// Helper function to create numeric literals
std::shared_ptr<LiteralExpr> createNumericLiteral(const std::string& value, int line) {
    auto result = std::make_shared<LiteralExpr>();
    result->value = value;  // Preserve the original string representation
    result->line = line;
    
    // Set the appropriate literal type and inferred type based on content
    bool hasDecimal = value.find('.') != std::string::npos;
    bool hasScientific = value.find('e') != std::string::npos || value.find('E') != std::string::npos;
    
    if (hasDecimal || hasScientific) {
        result->literalType = hasScientific ? TokenType::SCIENTIFIC_LITERAL : TokenType::FLOAT_LITERAL;
        result->inferred_type = std::make_shared<::Type>(::TypeTag::Float64);
    } else {
        // For integers, try to determine if it should be unsigned based on size
        try {
            unsigned long long uval = std::stoull(value);
            if (uval > 9223372036854775807ULL) {  // Larger than INT64_MAX
                result->literalType = TokenType::INT_LITERAL;
                result->inferred_type = std::make_shared<::Type>(::TypeTag::UInt64);
            } else {
                result->literalType = TokenType::INT_LITERAL;
                result->inferred_type = std::make_shared<::Type>(::TypeTag::Int64);
            }
        } catch (const std::exception&) {
            // If parsing fails, default to int64
            result->literalType = TokenType::INT_LITERAL;
            result->inferred_type = std::make_shared<::Type>(::TypeTag::Int64);
        }
    }
    
    return result;
}

// ============================================================================
// MAIN OPTIMIZATION ENTRY POINT
// ============================================================================

std::shared_ptr<Program> ASTOptimizer::optimizeProgram(std::shared_ptr<Program> program) {
    if (!program) return nullptr;
    
    // CRITICAL FIX: Pre-analysis pass to identify all reassigned variables
    // This prevents constant propagation of variables that will be reassigned later
    preAnalyzeReassignments(program);
    
    // Run optimizations in a loop until stable
    bool changed = true;
    int iterations = 0;
    const int max_iterations = 3; // Run at least 3 times to allow propagation + folding
    
    while (changed && iterations < max_iterations) {
        changed = false;
        iterations++;
        
        // Optimize all statements in the program
        for (auto& stmt : program->statements) {
            auto old_stmt = stmt;
            stmt = optimizeStatement(stmt);
            if (stmt != old_stmt) {
                changed = true;
            }
        }
    }
    
    return program;
}

std::shared_ptr<Expression> ASTOptimizer::optimizeExpression(std::shared_ptr<Expression> expr) {
    if (!expr) return nullptr;

    // Apply optimizations based on expression type
    if (auto binary = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        auto result = optimizeBinaryExpr(binary);
        // If optimization resulted in a different type (like literal), return it directly
        if (result != binary) {
            return std::dynamic_pointer_cast<Expression>(result);
        }
        return binary;
    } else if (auto unary = std::dynamic_pointer_cast<UnaryExpr>(expr)) {
        auto result = optimizeUnaryExpr(unary);
        if (result != unary) {
            return std::dynamic_pointer_cast<Expression>(result);
        }
        return unary;
    } else if (auto interpolated = std::dynamic_pointer_cast<InterpolatedStringExpr>(expr)) {
        auto result = optimizeInterpolatedStringExpr(interpolated);
        if (result != interpolated) {
            return std::dynamic_pointer_cast<Expression>(result);
        }
        return interpolated;
    } else if (auto literal = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
        return optimizeLiteralExpr(literal);
    } else if (auto variable = std::dynamic_pointer_cast<VariableExpr>(expr)) {
        auto result = optimizeVariableExpr(variable);
        // Check if constant propagation happened
        auto propagated = propagateConstants(variable);
        if (propagated != variable) {
            return propagated;  // Return the literal from constant propagation
        }
        return variable;
    } else if (auto grouping = std::dynamic_pointer_cast<GroupingExpr>(expr)) {
        return optimizeGroupingExpr(grouping);
    } else if (auto ternary = std::dynamic_pointer_cast<TernaryExpr>(expr)) {
        return optimizeTernaryExpr(ternary);
    } else if (auto assign = std::dynamic_pointer_cast<AssignExpr>(expr)) {
        return optimizeAssignExpr(assign);
    }
    
    return expr;
}

std::shared_ptr<Statement> ASTOptimizer::optimizeStatement(std::shared_ptr<Statement> stmt) {
    if (!stmt) return nullptr;
    
    // Apply optimizations based on statement type
    if (auto varDecl = std::dynamic_pointer_cast<VarDeclaration>(stmt)) {
        return optimizeVarDeclaration(varDecl);
    } else if (auto block = std::dynamic_pointer_cast<BlockStatement>(stmt)) {
        return optimizeBlockStatement(block);
    } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        auto optimized = optimizeIfStatement(ifStmt);
        // If the if statement was optimized away (null), return null
        // The caller (like optimizeBlockStatement) should handle this
        return optimized;
    } else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        return optimizeWhileStatement(whileStmt);
    } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
        return optimizeForStatement(forStmt);
    } else if (auto returnStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        return optimizeReturnStatement(returnStmt);
    } else if (auto printStmt = std::dynamic_pointer_cast<PrintStatement>(stmt)) {
        return optimizePrintStatement(printStmt);
    }
    
    return stmt;
}

std::shared_ptr<PrintStatement> ASTOptimizer::optimizePrintStatement(std::shared_ptr<PrintStatement> stmt) {
    if (!stmt) return nullptr;
    
    // Optimize all arguments
    for (auto& arg : stmt->arguments) {
        arg = optimizeExpression(arg);
    }
    
    return stmt;
}

// ============================================================================
// EXPRESSION OPTIMIZATIONS
// ============================================================================

std::shared_ptr<Expression> ASTOptimizer::optimizeBinaryExpr(std::shared_ptr<BinaryExpr> expr) {
    if (!expr) return nullptr;
    
    // Optimize operands first
    expr->left = optimizeExpression(expr->left);
    expr->right = optimizeExpression(expr->right);
    
    // Apply string canonicalization FIRST (only for actual strings)
    auto canonicalized = canonicalizeStrings(expr);
    if (canonicalized != expr) {
        return canonicalized;
    }
    
    // Apply constant folding (for numeric operations)
    auto folded = evaluateBinaryOp(expr->op, expr->left, expr->right);
    if (folded) {
        context.stats.constant_folds++;
        // Return the folded literal directly
        return folded;
    } else {
    }
    
    // Apply algebraic simplification
    auto simplified = simplifyAlgebraic(expr);
    if (simplified != expr) {
        return simplified;
    }
    
    return expr;
}

std::shared_ptr<Expression> ASTOptimizer::optimizeUnaryExpr(std::shared_ptr<UnaryExpr> expr) {
    if (!expr) return nullptr;
    
    // Optimize the operand first
    expr->right = optimizeExpression(expr->right);
    
    // Apply constant folding
    auto folded = foldConstants(expr);
    if (folded != expr) {
        // folded is now a LiteralExpr, return it directly
        return folded;
    }
    
    return expr;
}

std::shared_ptr<Expression> ASTOptimizer::optimizeInterpolatedStringExpr(std::shared_ptr<InterpolatedStringExpr> expr) {
    if (!expr) return nullptr;

    std::cout << "DEBUG: optimizeInterpolatedStringExpr called with " << expr->parts.size() << " parts" << std::endl;

    // Optimize all expression parts
    for (auto& part : expr->parts) {
        if (auto exprPart = std::get_if<std::shared_ptr<Expression>>(&part)) {
            *exprPart = optimizeExpression(*exprPart);
        }
    }

    // Apply interpolation lowering
    auto lowered = lowerInterpolation(expr);
    if (lowered != expr) {
        std::cout << "DEBUG: Interpolation was lowered to literal" << std::endl;
        return lowered;  // Return the lowered expression (could be a literal)
    }

    std::cout << "DEBUG: Interpolation was not lowered, returning original" << std::endl;
    return expr;
}

std::shared_ptr<LiteralExpr> ASTOptimizer::optimizeLiteralExpr(std::shared_ptr<LiteralExpr> expr) {
    if (!expr) return nullptr;
    
    // CRITICAL: Set inferred type using type inference if not already set
    if (!expr->inferred_type) {
        expr->inferred_type = inferLiteralType(expr->value);
    }
    
    // Literals are already constants - no need for constant propagation
    return expr;
}

std::shared_ptr<VariableExpr> ASTOptimizer::optimizeVariableExpr(std::shared_ptr<VariableExpr> expr) {
    if (!expr) return nullptr;
    
    // Variable expressions don't need optimization themselves
    // Constant propagation is handled in the main optimizeExpression dispatcher
    return expr;
}

std::shared_ptr<Expression> ASTOptimizer::optimizeGroupingExpr(std::shared_ptr<GroupingExpr> expr) {
    if (!expr) return nullptr;
    
    // Optimize the grouped expression
    expr->expression = optimizeExpression(expr->expression);
    
    // If the grouped expression is a literal, remove the grouping
    if (auto literal = std::dynamic_pointer_cast<LiteralExpr>(expr->expression)) {
        return literal;
    }
    
    return expr;
}

std::shared_ptr<CallExpr> ASTOptimizer::optimizeCallExpr(std::shared_ptr<CallExpr> expr) {
    if (!expr) return nullptr;
    
    // Optimize callee and arguments
    expr->callee = optimizeExpression(expr->callee);
    for (auto& arg : expr->arguments) {
        arg = optimizeExpression(arg);
    }
    for (auto& [name, arg] : expr->namedArgs) {
        arg = optimizeExpression(arg);
    }
    
    return expr;
}

std::shared_ptr<TernaryExpr> ASTOptimizer::optimizeTernaryExpr(std::shared_ptr<TernaryExpr> expr) {
    if (!expr) return nullptr;
    
    // Optimize condition, then, and else branches
    expr->condition = optimizeExpression(expr->condition);
    expr->thenBranch = optimizeExpression(expr->thenBranch);
    expr->elseBranch = optimizeExpression(expr->elseBranch);
    
    // Apply branch simplification
    auto simplified = simplifyBranches(expr);
    if (simplified != expr) {
        return std::dynamic_pointer_cast<TernaryExpr>(simplified);
    }
    
    return expr;
}

std::shared_ptr<AssignExpr> ASTOptimizer::optimizeAssignExpr(std::shared_ptr<AssignExpr> expr) {
    if (!expr) return nullptr;
    
    // Optimize the right-hand side value first
    expr->value = optimizeExpression(expr->value);
    
    // Mark the variable as reassigned to prevent constant propagation
    // This is crucial for loop variables like i = i + 1
    context.markReassigned(expr->name);
    
    return expr;
}

// ============================================================================
// STATEMENT OPTIMIZATIONS
// ============================================================================

std::shared_ptr<VarDeclaration> ASTOptimizer::optimizeVarDeclaration(std::shared_ptr<VarDeclaration> stmt) {
    if (!stmt) return nullptr;
    
    // Optimize initializer if present
    if (stmt->initializer) {
        stmt->initializer = optimizeExpression(stmt->initializer);
        
        // If optimization resulted in nullptr, create an empty string literal to preserve the initializer
        if (!stmt->initializer) {
            stmt->initializer = createStringLiteral("", stmt->line);
        }
        
        // If this is a constant variable, track it for propagation
        if (stmt->initializer && isLiteralConstant(stmt->initializer)) {
            context.setConstant(stmt->name, stmt->initializer);
            context.stats.constant_propagations++;
        }
    }
    
    return stmt;
}

std::shared_ptr<BlockStatement> ASTOptimizer::optimizeBlockStatement(std::shared_ptr<BlockStatement> stmt) {
    if (!stmt) return nullptr;
    
    // Enter new scope
    context.pushScope();
    
    // Optimize all statements
    std::vector<std::shared_ptr<Statement>> optimized_stmts;
    for (auto& s : stmt->statements) {
        auto optimized = optimizeStatement(s);
        
        // Apply dead code elimination
        if (!isUnreachableCode(optimized)) {
            optimized_stmts.push_back(optimized);
        } else {
            context.stats.dead_code_eliminated++;
        }
    }
    
    stmt->statements = std::move(optimized_stmts);
    
    // Exit scope
    context.popScope();
    
    return stmt;
}

std::shared_ptr<Statement> ASTOptimizer::optimizeIfStatement(std::shared_ptr<IfStatement> stmt) {
    if (!stmt) return nullptr;
    
    // Optimize condition first
    stmt->condition = optimizeExpression(stmt->condition);
    
    // Optimize branches
    stmt->thenBranch = optimizeStatement(stmt->thenBranch);
    if (stmt->elseBranch) {
        stmt->elseBranch = optimizeStatement(stmt->elseBranch);
    }
    
    // Apply branch simplification for compile-time constant conditions
    if (isCompileTimeTrue(stmt->condition)) {
        // Condition is always true, keep only then branch
        context.stats.branches_simplified++;
        return stmt->thenBranch;
    } else if (isCompileTimeFalse(stmt->condition)) {
        // Condition is always false, keep only else branch
        context.stats.branches_simplified++;
        if (stmt->elseBranch) {
            return stmt->elseBranch;
        } else {
            // No else branch, remove entire if statement
            return nullptr;
        }
    }
    
    return stmt;
}

std::shared_ptr<WhileStatement> ASTOptimizer::optimizeWhileStatement(std::shared_ptr<WhileStatement> stmt) {
    if (!stmt) return nullptr;
    
    // Set in_loop flag and optimize body and condition
    context.in_loop = true;
    stmt->body = optimizeStatement(stmt->body);
    stmt->condition = optimizeExpression(stmt->condition);
    context.in_loop = false;
    
    // Apply branch simplification
    if (isCompileTimeFalse(stmt->condition)) {
        // Condition is always false, remove the while loop
        context.stats.branches_simplified++;
        return nullptr;
    }
    
    return stmt;
}

std::shared_ptr<ForStatement> ASTOptimizer::optimizeForStatement(std::shared_ptr<ForStatement> stmt) {
    if (!stmt) return nullptr;
    
    // Optimize initializer first (outside loop)
    if (stmt->initializer) {
        stmt->initializer = optimizeStatement(stmt->initializer);
    }
    
    // Then set in_loop=true and optimize rest
    context.in_loop = true;
    stmt->body = optimizeStatement(stmt->body);
    if (stmt->increment) {
        stmt->increment = optimizeExpression(stmt->increment);
    }
    if (stmt->condition) {
        stmt->condition = optimizeExpression(stmt->condition);
    }
    context.in_loop = false;
    
    return stmt;
}

std::shared_ptr<ReturnStatement> ASTOptimizer::optimizeReturnStatement(std::shared_ptr<ReturnStatement> stmt) {
    if (!stmt) return nullptr;
    
    // Optimize return value if present
    if (stmt->value) {
        stmt->value = optimizeExpression(stmt->value);
    }
    
    return stmt;
}

// ============================================================================
// CORE OPTIMIZATION UTILITIES
// ============================================================================

std::shared_ptr<Expression> ASTOptimizer::foldConstants(std::shared_ptr<Expression> expr) {
    if (!expr) return nullptr;
    
    // Handle binary expressions
    if (auto binary = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        if (isLiteralConstant(binary->left) && isLiteralConstant(binary->right)) {
            auto result = evaluateBinaryOp(binary->op, binary->left, binary->right);
            if (result) {
                context.stats.constant_folds++;
                return result;
            }
        }
    }
    
    // Handle unary expressions
    if (auto unary = std::dynamic_pointer_cast<UnaryExpr>(expr)) {
        if (isLiteralConstant(unary->right)) {
            auto result = evaluateUnaryOp(unary->op, unary->right);
            if (result) {
                context.stats.constant_folds++;
                return result;
            }
        }
    }
    
    return expr;
}

std::shared_ptr<Expression> ASTOptimizer::propagateConstants(std::shared_ptr<Expression> expr) {
    if (!expr) return nullptr;
    
    // Don't propagate inside loops
    if (context.in_loop) {
        return expr;
    }
    
    // Handle variable references
    if (auto variable = std::dynamic_pointer_cast<VariableExpr>(expr)) {
        // Don't propagate reassigned variables (like loop counters)
        if (context.reassigned_vars.find(variable->name) != context.reassigned_vars.end()) {
            return expr;
        }
        
        // CRITICAL FIX: Only propagate if the variable is truly constant (never reassigned)
        // This prevents propagating initial values when variables are later reassigned
        if (context.isConstant(variable->name)) {
            auto constant = context.getConstant(variable->name);
            if (constant) {
                // Create a copy of the constant to avoid modifying the original
                if (auto literal = std::dynamic_pointer_cast<LiteralExpr>(constant)) {
                    auto copy = std::make_shared<LiteralExpr>(*literal);
                    
                    std::cout << "[DEBUG] Constant propagation for variable '" << variable->name << "':" << std::endl;
                    std::cout << "  - Variable has inferred_type: " << (variable->inferred_type ? "YES" : "NO") << std::endl;
                    std::cout << "  - Literal has inferred_type: " << (literal->inferred_type ? "YES" : "NO") << std::endl;
                    if (variable->inferred_type) {
                        std::cout << "  - Variable type tag: " << static_cast<int>(variable->inferred_type->tag) << std::endl;
                    }
                    if (literal->inferred_type) {
                        std::cout << "  - Literal type tag: " << static_cast<int>(literal->inferred_type->tag) << std::endl;
                    }
                    
                    // CRITICAL FIX: Preserve the variable's declared type instead of the literal's inferred type
                    // This ensures that u64 variables keep their u64 type during constant propagation
                    if (variable->inferred_type) {
                        std::cout << "[DEBUG] Constant propagation: variable '" << variable->name 
                                  << "' has inferred_type tag: " << static_cast<int>(variable->inferred_type->tag) << std::endl;
                        copy->inferred_type = variable->inferred_type;
                    } else if (literal->inferred_type) {
                        std::cout << "[DEBUG] Constant propagation: variable '" << variable->name 
                                  << "' has no inferred_type, using literal's type tag: " << static_cast<int>(literal->inferred_type->tag) << std::endl;
                        copy->inferred_type = literal->inferred_type;
                    } else {
                        std::cout << "[DEBUG] Constant propagation: variable '" << variable->name 
                                  << "' has no type info, inferring from value" << std::endl;
                        // If neither has a type, infer it
                        copy->inferred_type = inferLiteralType(copy->value);
                    }
                    context.stats.constant_propagations++;
                    return copy;
                }
            }
        }
    }
    
    return expr;
}

std::shared_ptr<Expression> ASTOptimizer::simplifyBranches(std::shared_ptr<Expression> expr) {
    if (!expr) return nullptr;
    
    // Handle ternary expressions
    if (auto ternary = std::dynamic_pointer_cast<TernaryExpr>(expr)) {
        if (isCompileTimeTrue(ternary->condition)) {
            return ternary->thenBranch;
        } else if (isCompileTimeFalse(ternary->condition)) {
            return ternary->elseBranch;
        }
    }
    
    return expr;
}

std::shared_ptr<Expression> ASTOptimizer::simplifyAlgebraic(std::shared_ptr<Expression> expr) {
    if (!expr) return nullptr;
    
    // Handle binary expressions
    if (auto binary = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        // x + 0 -> x
        if (binary->op == TokenType::PLUS && isLiteralConstant(binary->right)) {
            if (auto rightLiteral = std::dynamic_pointer_cast<LiteralExpr>(binary->right)) {
                if (std::get_if<std::string>(&rightLiteral->value)) {
                    auto strVal = std::get<std::string>(rightLiteral->value);
                    if (strVal == "0") {
                        context.stats.algebraic_simplifications++;
                        return binary->left;
                    }
                }
            }
        }
        
        // x * 1 -> x
        if (binary->op == TokenType::STAR && isLiteralConstant(binary->right)) {
            if (auto rightLiteral = std::dynamic_pointer_cast<LiteralExpr>(binary->right)) {
                if (std::get_if<std::string>(&rightLiteral->value)) {
                    auto strVal = std::get<std::string>(rightLiteral->value);
                    if (strVal == "1") {
                        context.stats.algebraic_simplifications++;
                        return binary->left;
                    }
                }
            }
        }
        
        // x * 0 -> 0
        if (binary->op == TokenType::STAR && isLiteralConstant(binary->right)) {
            if (auto rightLiteral = std::dynamic_pointer_cast<LiteralExpr>(binary->right)) {
                if (std::get_if<std::string>(&rightLiteral->value)) {
                    auto strVal = std::get<std::string>(rightLiteral->value);
                    if (strVal == "0") {
                        context.stats.algebraic_simplifications++;
                        return binary->right;
                    }
                }
            }
        }
    }
    
    return expr;
}

std::shared_ptr<Expression> ASTOptimizer::lowerInterpolation(std::shared_ptr<InterpolatedStringExpr> expr) {
    if (!expr) return nullptr;

    std::cout << "DEBUG: lowerInterpolation called with " << expr->parts.size() << " parts" << std::endl;

    // Check if all parts are string literals (either direct strings or literal expressions)
    bool allStringParts = true;
    std::string concatenated_result;

    for (size_t i = 0; i < expr->parts.size(); ++i) {
        const auto& part = expr->parts[i];
        std::cout << "DEBUG: Processing part " << i << std::endl;
        
        if (auto strPart = std::get_if<std::string>(&part)) {
            // Direct string literal part
            std::cout << "DEBUG: Direct string part: '" << *strPart << "'" << std::endl;
            concatenated_result += *strPart;
        } else if (auto exprPart = std::get_if<std::shared_ptr<Expression>>(&part)) {
            std::cout << "DEBUG: Expression part found";
            if (*exprPart) {
                std::cout << ", type: " << typeid(*(*exprPart)).name() << std::endl;
            } else {
                std::cout << ", but it's null!" << std::endl;
                allStringParts = false;
                break;
            }
            // Check if this expression part is now a literal after optimization
            if (auto literal = std::dynamic_pointer_cast<LiteralExpr>(*exprPart)) {
                std::cout << "DEBUG: Expression part is a literal" << std::endl;
                if (std::holds_alternative<std::string>(literal->value)) {
                    // It's a string literal - add it to the result
                    concatenated_result += std::get<std::string>(literal->value);
                    std::cout << "DEBUG: Added string literal: '" << std::get<std::string>(literal->value) << "'" << std::endl;
                } else {
                    // It's a non-string literal (number, bool) - convert to string
                    if (std::holds_alternative<bool>(literal->value)) {
                        concatenated_result += std::get<bool>(literal->value) ? "true" : "false";
                        std::cout << "DEBUG: Added bool literal" << std::endl;
                    } else if (std::holds_alternative<std::nullptr_t>(literal->value)) {
                        concatenated_result += "nil";
                        std::cout << "DEBUG: Added nil literal" << std::endl;
                    } else {
                        // For any other type, try to convert to string representation
                        // This should handle numeric literals stored as strings
                        if (auto strVal = std::get_if<std::string>(&literal->value)) {
                            concatenated_result += *strVal;
                            std::cout << "DEBUG: Added string literal value: '" << *strVal << "'" << std::endl;
                        }
                    }
                }
            } else {
                std::cout << "DEBUG: Expression part is not a literal, can't fold" << std::endl;
                // Not a literal - can't fold completely
                allStringParts = false;
                break;
            }
        } else {
            std::cout << "DEBUG: Unknown part type" << std::endl;
            // Unknown part type
            allStringParts = false;
            break;
        }
    }

    // If all parts can be concatenated into a constant string, return a literal
    if (allStringParts) {
        std::cout << "DEBUG: All parts are literals, creating string: '" << concatenated_result << "'" << std::endl;
        auto literal = createStringLiteral(concatenated_result, expr->line);
        context.stats.interpolations_lowered++;
        return literal;
    } else {
        std::cout << "DEBUG: Not all parts are literals, can't fold" << std::endl;
    }
    
    // Convert interpolation to concatenation of string literals and expressions
    std::shared_ptr<Expression> result = nullptr;
    
    for (const auto& part : expr->parts) {
        std::shared_ptr<Expression> current = nullptr;
        
        if (auto strPart = std::get_if<std::string>(&part)) {
            if (!strPart->empty()) {
                current = createStringLiteral(*strPart, expr->line);
            }
        } else if (auto exprPart = std::get_if<std::shared_ptr<Expression>>(&part)) {
            current = *exprPart;
            // If the expression is not a string, convert it to string
            if (current && current->inferred_type && 
                current->inferred_type->tag != ::TypeTag::String) {
                // Create a to_string call (simplified - in reality would need function lookup)
                // For now, we'll just leave it as is and let LIR handle conversion
            }
        }
        
        if (current) {
            if (!result) {
                result = current;
            } else {
                // Create concatenation
                auto concat = std::make_shared<BinaryExpr>();
                concat->left = result;
                concat->right = current;
                concat->op = TokenType::PLUS;
                concat->line = expr->line;
                concat->inferred_type = std::make_shared<::Type>(::TypeTag::String);
                result = concat;
            }
        }
    }
    
    if (result) {
        context.stats.interpolations_lowered++;
        return result;
    }
    
    return expr;
}

std::shared_ptr<Expression> ASTOptimizer::canonicalizeStrings(std::shared_ptr<Expression> expr) {
    if (!expr) return nullptr;
    
    // Handle binary string concatenation
    if (auto binary = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        if (binary->op == TokenType::PLUS) {
            auto leftLiteral = std::dynamic_pointer_cast<LiteralExpr>(binary->left);
            auto rightLiteral = std::dynamic_pointer_cast<LiteralExpr>(binary->right);
            
            if (leftLiteral && rightLiteral) {
                // Concatenate if either is a string (string + anything)
                bool leftIsString = leftLiteral->inferred_type && 
                                   leftLiteral->inferred_type->tag == TypeTag::String;
                bool rightIsString = rightLiteral->inferred_type && 
                                    rightLiteral->inferred_type->tag == TypeTag::String;
                
                if (leftIsString || rightIsString) {
                    auto leftStr = std::get_if<std::string>(&leftLiteral->value);
                    auto rightStr = std::get_if<std::string>(&rightLiteral->value);
                    
                    if (leftStr && rightStr) {
                        // Merge string literals
                        auto merged = createStringLiteral(*leftStr + *rightStr, expr->line);
                        context.stats.strings_canonicalized++;
                        return merged;
                    }
                }
            }
        }
    }
    
    return expr;
}

// ============================================================================
// UTILITY METHODS
// ============================================================================

bool ASTOptimizer::isLiteralConstant(std::shared_ptr<Expression> expr) {
    return std::dynamic_pointer_cast<LiteralExpr>(expr) != nullptr;
}

std::shared_ptr<Expression> ASTOptimizer::evaluateBinaryOp(TokenType op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
    auto leftLiteral = std::dynamic_pointer_cast<LiteralExpr>(left);
    auto rightLiteral = std::dynamic_pointer_cast<LiteralExpr>(right);
    
    if (!leftLiteral || !rightLiteral) return nullptr;
    
    // Check if both operands are numeric (int or float)
    bool leftIsNumeric = leftLiteral->inferred_type && 
                        (leftLiteral->inferred_type->tag == TypeTag::Int64 ||
                         leftLiteral->inferred_type->tag == TypeTag::Int32 ||
                         leftLiteral->inferred_type->tag == TypeTag::Float64 ||
                         leftLiteral->inferred_type->tag == TypeTag::Float32);
                         
    bool rightIsNumeric = rightLiteral->inferred_type && 
                         (rightLiteral->inferred_type->tag == TypeTag::Int64 ||
                          rightLiteral->inferred_type->tag == TypeTag::Int32 ||
                          rightLiteral->inferred_type->tag == TypeTag::Float64 ||
                          rightLiteral->inferred_type->tag == TypeTag::Float32);
    
    // If both are numeric, do numeric operations
    if (leftIsNumeric && rightIsNumeric) {
        auto leftStr = std::get_if<std::string>(&leftLiteral->value);
        auto rightStr = std::get_if<std::string>(&rightLiteral->value);
        
        if (leftStr && rightStr) {
            try {
                long double leftNum = std::stold(*leftStr);
                long double rightNum = std::stold(*rightStr);
                long double result = 0.0;
                bool isArithmetic = (op == TokenType::PLUS || op == TokenType::MINUS || 
                                   op == TokenType::STAR || op == TokenType::SLASH || 
                                   op == TokenType::MODULUS);
                
                switch (op) {
                    case TokenType::PLUS:
                        result = leftNum + rightNum;
                        break;
                    case TokenType::MINUS:
                        result = leftNum - rightNum;
                        break;
                    case TokenType::STAR:
                        result = leftNum * rightNum;
                        break;
                    case TokenType::SLASH:
                        if (rightNum == 0.0) return nullptr;  // Division by zero
                        result = leftNum / rightNum;
                        break;
                    case TokenType::MODULUS:
                        if (rightNum == 0.0) return nullptr;  // Modulus by zero
                        result = std::fmod(leftNum, rightNum);
                        break;
                    // Comparison operations - return boolean results
                    case TokenType::GREATER:
                        return createBoolLiteral(leftNum > rightNum, left->line);
                    case TokenType::GREATER_EQUAL:
                        return createBoolLiteral(leftNum >= rightNum, left->line);
                    case TokenType::LESS:
                        return createBoolLiteral(leftNum < rightNum, left->line);
                    case TokenType::LESS_EQUAL:
                        return createBoolLiteral(leftNum <= rightNum, left->line);
                    case TokenType::EQUAL_EQUAL:
                        return createBoolLiteral(leftNum == rightNum, left->line);
                    case TokenType::BANG_EQUAL:
                        return createBoolLiteral(leftNum != rightNum, left->line);
                    default:
                        return nullptr;
                }
                
                // Only create arithmetic result for arithmetic operations
                if (!isArithmetic) {
                    return nullptr;
                }
                
                // Determine result type (prefer float if either operand is float)
                TypePtr resultType = leftLiteral->inferred_type;
                if (leftLiteral->inferred_type->tag == TypeTag::Float64 || 
                    leftLiteral->inferred_type->tag == TypeTag::Float32 ||
                    rightLiteral->inferred_type->tag == TypeTag::Float64 || 
                    rightLiteral->inferred_type->tag == TypeTag::Float32) {
                    resultType = std::make_shared<::Type>(::TypeTag::Float64);
                }
                
                // Create the folded literal with higher precision
                auto foldedLiteral = std::make_shared<LiteralExpr>();
                
                // Use higher precision formatting
                std::ostringstream oss;
                oss << std::setprecision(17) << result;
                foldedLiteral->value = oss.str();
                
                foldedLiteral->line = left->line;
                foldedLiteral->inferred_type = resultType;
                
                // Set the appropriate literal type based on the result type
                if (resultType->tag == TypeTag::Float64 || resultType->tag == TypeTag::Float32) {
                    foldedLiteral->literalType = TokenType::FLOAT_LITERAL;
                } else {
                    foldedLiteral->literalType = TokenType::INT_LITERAL;
                }
                
                return foldedLiteral;
                
            } catch (const std::exception&) {
                return nullptr;  // Failed to parse numbers
            }
        }
    }
    
    // Handle boolean logic operations
    bool leftIsBool = leftLiteral->inferred_type && 
                      leftLiteral->inferred_type->tag == TypeTag::Bool;
    bool rightIsBool = rightLiteral->inferred_type && 
                       rightLiteral->inferred_type->tag == TypeTag::Bool;
    
    if (leftIsBool && rightIsBool) {
        auto leftBool = std::get_if<bool>(&leftLiteral->value);
        auto rightBool = std::get_if<bool>(&rightLiteral->value);
        
        if (leftBool && rightBool) {
            bool result = false;
            
            switch (op) {
                case TokenType::AND:
                    result = *leftBool && *rightBool;
                    break;
                case TokenType::OR:
                    result = *leftBool || *rightBool;
                    break;
                default:
                    return nullptr; // Not a boolean logic operator
            }
            
            return createBoolLiteral(result, left->line);
        }
    }
    
    // Handle string concatenation if both are strings
    bool leftIsString = leftLiteral->inferred_type && 
                       leftLiteral->inferred_type->tag == TypeTag::String;
    bool rightIsString = rightLiteral->inferred_type && 
                        rightLiteral->inferred_type->tag == TypeTag::String;
    
    if (leftIsString && rightIsString && op == TokenType::PLUS) {
        auto leftStr = std::get_if<std::string>(&leftLiteral->value);
        auto rightStr = std::get_if<std::string>(&rightLiteral->value);
        
        if (leftStr && rightStr) {
            return createStringLiteral(*leftStr + *rightStr, left->line);
        }
    }
    
    return nullptr;
}

std::shared_ptr<Expression> ASTOptimizer::evaluateUnaryOp(TokenType op, std::shared_ptr<Expression> right) {
    auto rightLiteral = std::dynamic_pointer_cast<LiteralExpr>(right);
    if (!rightLiteral) return nullptr;
    
    // Handle boolean negation
    if (op == TokenType::BANG) {
        auto boolVal = std::get_if<bool>(&rightLiteral->value);
        if (boolVal) {
            return createBoolLiteral(!*boolVal, right->line);
        }
    }
    
    // Handle numeric negation
    if (op == TokenType::MINUS) {
        auto strVal = std::get_if<std::string>(&rightLiteral->value);
        if (strVal) {
            try {
                // Check if the original literal was an integer or float
                bool shouldBeFloat = (rightLiteral->literalType == TokenType::FLOAT_LITERAL || 
                                    rightLiteral->literalType == TokenType::SCIENTIFIC_LITERAL ||
                                    rightLiteral->inferred_type->tag == TypeTag::Float64 ||
                                    rightLiteral->inferred_type->tag == TypeTag::Float32);
                
                if (shouldBeFloat) {
                    long double num = std::stold(*strVal);
                    // Use higher precision formatting for long double
                    std::ostringstream oss;
                    oss << std::setprecision(17) << (num * -1.0L);
                    return createNumericLiteral(oss.str(), right->line);
                } else {
                    // Handle as integer - check if it's unsigned
                    if (rightLiteral->inferred_type->tag == TypeTag::UInt64 || 
                        rightLiteral->inferred_type->tag == TypeTag::UInt32 ||
                        rightLiteral->inferred_type->tag == TypeTag::UInt16 ||
                        rightLiteral->inferred_type->tag == TypeTag::UInt8) {
                        // For unsigned, we need to be careful with negation
                        unsigned long long num = std::stoull(*strVal);
                        // Convert to signed for negation
                        long long signedResult = -static_cast<long long>(num);
                        return createNumericLiteral(std::to_string(signedResult), right->line);
                    } else {
                        // Handle as signed integer
                        long long num = std::stoll(*strVal);
                        return createNumericLiteral(std::to_string(-num), right->line);
                    }
                }
            } catch (const std::invalid_argument&) {
                // Not numeric, fall through
            } catch (const std::out_of_range&) {
                // Numeric overflow, fall through
            }
        }
    }
    
    // Handle numeric positive (no-op, but ensure it's a literal)
    if (op == TokenType::PLUS) {
        // For positive, just return the operand as-is if it's already a literal
        return rightLiteral;
    }
    
    return nullptr;
}

bool ASTOptimizer::isCompileTimeFalse(std::shared_ptr<Expression> expr) {
    if (auto literal = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
        if (auto boolVal = std::get_if<bool>(&literal->value)) {
            return !*boolVal;
        }
        if (auto strVal = std::get_if<std::string>(&literal->value)) {
            return *strVal == "false" || *strVal == "0" || strVal->empty();
        }
    }
    return false;
}

bool ASTOptimizer::isCompileTimeTrue(std::shared_ptr<Expression> expr) {
    if (auto literal = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
        if (auto boolVal = std::get_if<bool>(&literal->value)) {
            return *boolVal;
        }
        if (auto strVal = std::get_if<std::string>(&literal->value)) {
            return *strVal == "true" && *strVal != "0" && !strVal->empty();
        }
    }
    return false;
}

bool ASTOptimizer::isUnreachableCode(std::shared_ptr<Statement> stmt) {
    // Check for statements after return statements
    if (!stmt) return true; // null statement is unreachable
    
    // In a real implementation, this would require control flow analysis
    // For now, we'll do basic unreachable code detection
    
    // Statements that are always unreachable:
    // - Statements after a return in the same block
    // - Statements in a block that follows a return statement
    // - Statements in an if branch where the condition is always false
    // - Statements in a while loop where the condition is always false
    
    // This is a simplified implementation - a full implementation would
    // require building a control flow graph and analyzing reachability
    
    return false; // Conservative approach - assume reachable
}

std::shared_ptr<Statement> ASTOptimizer::eliminateDeadCode(std::shared_ptr<Statement> stmt) {
    if (!stmt) return nullptr;
    
    // Handle different statement types for dead code elimination
    
    if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        // Optimize condition first
        ifStmt->condition = optimizeExpression(ifStmt->condition);
        
        // Check if condition is compile-time constant
        if (isCompileTimeTrue(ifStmt->condition)) {
            // Keep only then branch
            context.stats.dead_code_eliminated++;
            return optimizeStatement(ifStmt->thenBranch);
        } else if (isCompileTimeFalse(ifStmt->condition)) {
            // Keep only else branch
            context.stats.dead_code_eliminated++;
            if (ifStmt->elseBranch) {
                return optimizeStatement(ifStmt->elseBranch);
            } else {
                return nullptr; // Remove entire if statement
            }
        }
        
        // Optimize both branches
        ifStmt->thenBranch = optimizeStatement(ifStmt->thenBranch);
        if (ifStmt->elseBranch) {
            ifStmt->elseBranch = optimizeStatement(ifStmt->elseBranch);
        }
        
        return ifStmt;
    }
    
    if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        // Optimize condition
        whileStmt->condition = optimizeExpression(whileStmt->condition);
        
        // Check if condition is compile-time false
        if (isCompileTimeFalse(whileStmt->condition)) {
            context.stats.dead_code_eliminated++;
            return nullptr; // Remove while loop entirely
        }
        
        // Optimize body
        whileStmt->body = optimizeStatement(whileStmt->body);
        
        return whileStmt;
    }
    
    if (auto blockStmt = std::dynamic_pointer_cast<BlockStatement>(stmt)) {
        context.pushScope();
        
        std::vector<std::shared_ptr<Statement>> optimizedStatements;
        bool foundReturn = false;
        
        for (auto& s : blockStmt->statements) {
            // If we've already seen a return, everything after is dead code
            if (foundReturn) {
                context.stats.dead_code_eliminated++;
                continue;
            }
            
            auto optimized = optimizeStatement(s);
            
            // Check if this is a return statement
            if (std::dynamic_pointer_cast<ReturnStatement>(optimized)) {
                foundReturn = true;
            }
            
            // Only add non-null statements
            if (optimized) {
                optimizedStatements.push_back(optimized);
            }
        }
        
        blockStmt->statements = std::move(optimizedStatements);
        context.popScope();
        
        return blockStmt;
    }
    
    // For other statement types, just optimize their expressions
    if (auto returnStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        if (returnStmt->value) {
            returnStmt->value = optimizeExpression(returnStmt->value);
        }
    }
    
    if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(stmt)) {
        if (exprStmt->expression) {
            exprStmt->expression = optimizeExpression(exprStmt->expression);
            
            // Remove expression statements that have no side effects
            // (like pure literal expressions)
            if (isLiteralConstant(exprStmt->expression)) {
                context.stats.dead_code_eliminated++;
                return nullptr;
            }
        }
    }
    
    if (auto varDecl = std::dynamic_pointer_cast<VarDeclaration>(stmt)) {
        if (varDecl->initializer) {
            varDecl->initializer = optimizeExpression(varDecl->initializer);
        }
    }
    
    return stmt;
}

// ============================================================================
// PRE-ANALYSIS FOR REASSIGNMENT DETECTION
// ============================================================================

void ASTOptimizer::preAnalyzeReassignments(std::shared_ptr<Program> program) {
    if (!program) return;
    
    // Walk through all statements and identify variables that get reassigned
    for (auto& stmt : program->statements) {
        preAnalyzeStatement(stmt);
    }
}

void ASTOptimizer::preAnalyzeStatement(std::shared_ptr<Statement> stmt) {
    if (!stmt) return;
    
    if (auto varDecl = std::dynamic_pointer_cast<VarDeclaration>(stmt)) {
        // Variable declarations don't count as reassignments
        if (varDecl->initializer) {
            preAnalyzeExpression(varDecl->initializer);
        }
    } else if (auto block = std::dynamic_pointer_cast<BlockStatement>(stmt)) {
        for (auto& s : block->statements) {
            preAnalyzeStatement(s);
        }
    } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        preAnalyzeExpression(ifStmt->condition);
        preAnalyzeStatement(ifStmt->thenBranch);
        if (ifStmt->elseBranch) {
            preAnalyzeStatement(ifStmt->elseBranch);
        }
    } else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        preAnalyzeExpression(whileStmt->condition);
        preAnalyzeStatement(whileStmt->body);
    } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
        if (forStmt->initializer) {
            preAnalyzeStatement(forStmt->initializer);
        }
        if (forStmt->condition) {
            preAnalyzeExpression(forStmt->condition);
        }
        if (forStmt->increment) {
            preAnalyzeExpression(forStmt->increment);
        }
        preAnalyzeStatement(forStmt->body);
    } else if (auto returnStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        if (returnStmt->value) {
            preAnalyzeExpression(returnStmt->value);
        }
    } else if (auto printStmt = std::dynamic_pointer_cast<PrintStatement>(stmt)) {
        for (auto& arg : printStmt->arguments) {
            preAnalyzeExpression(arg);
        }
    } else if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(stmt)) {
        preAnalyzeExpression(exprStmt->expression);
    }
}

void ASTOptimizer::preAnalyzeExpression(std::shared_ptr<Expression> expr) {
    if (!expr) return;
    
    if (auto assign = std::dynamic_pointer_cast<AssignExpr>(expr)) {
        // This is a reassignment - mark the variable as reassigned
        context.markReassigned(assign->name);
        preAnalyzeExpression(assign->value);
    } else if (auto binary = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        preAnalyzeExpression(binary->left);
        preAnalyzeExpression(binary->right);
    } else if (auto unary = std::dynamic_pointer_cast<UnaryExpr>(expr)) {
        preAnalyzeExpression(unary->right);
    } else if (auto interpolated = std::dynamic_pointer_cast<InterpolatedStringExpr>(expr)) {
        for (const auto& part : interpolated->parts) {
            if (auto exprPart = std::get_if<std::shared_ptr<Expression>>(&part)) {
                preAnalyzeExpression(*exprPart);
            }
        }
    } else if (auto grouping = std::dynamic_pointer_cast<GroupingExpr>(expr)) {
        preAnalyzeExpression(grouping->expression);
    } else if (auto ternary = std::dynamic_pointer_cast<TernaryExpr>(expr)) {
        preAnalyzeExpression(ternary->condition);
        preAnalyzeExpression(ternary->thenBranch);
        preAnalyzeExpression(ternary->elseBranch);
    } else if (auto call = std::dynamic_pointer_cast<CallExpr>(expr)) {
        preAnalyzeExpression(call->callee);
        for (auto& arg : call->arguments) {
            preAnalyzeExpression(arg);
        }
        for (auto& [name, arg] : call->namedArgs) {
            preAnalyzeExpression(arg);
        }
    }
    // Other expression types (literals, variables) don't need pre-analysis
}

} // namespace AST
