#include "ast.hh"
#include <stdexcept>
#include <cmath>

namespace AST {

// Helper function to create boolean literals
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
    // Set inferred type for string
    result->inferred_type = std::make_shared<::Type>(::TypeTag::String);
    return result;
}

// Helper function to create numeric literals
std::shared_ptr<LiteralExpr> createNumericLiteral(const std::string& value, int line) {
    auto result = std::make_shared<LiteralExpr>();
    result->value = value;
    result->line = line;
    // Set inferred type for numeric (Int64)
    result->inferred_type = std::make_shared<::Type>(::TypeTag::Int64);
    return result;
}

// ============================================================================
// MAIN OPTIMIZATION ENTRY POINT
// ============================================================================

std::shared_ptr<Program> ASTOptimizer::optimizeProgram(std::shared_ptr<Program> program) {
    if (!program) return nullptr;
    
    // Run optimizations in a loop until stable
    bool changed = true;
    int iterations = 0;
    const int max_iterations = 10; // Prevent infinite loops
    
    while (changed && iterations < max_iterations) {
        changed = false;
        iterations++;
        
        // Optimize all statements in the program
        for (auto& stmt : program->statements) {
            auto old_stmt = stmt;
            stmt = optimizeStatement(stmt);
            if (stmt != old_stmt) changed = true;
        }
    }
    
    return program;
}

std::shared_ptr<Expression> ASTOptimizer::optimizeExpression(std::shared_ptr<Expression> expr) {
    if (!expr) return nullptr;
    
    // Apply optimizations based on expression type
    if (auto binary = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        return optimizeBinaryExpr(binary);
    } else if (auto unary = std::dynamic_pointer_cast<UnaryExpr>(expr)) {
        return optimizeUnaryExpr(unary);
    } else if (auto interp = std::dynamic_pointer_cast<InterpolatedStringExpr>(expr)) {
        return optimizeInterpolatedStringExpr(interp);
    } else if (auto literal = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
        return optimizeLiteralExpr(literal);
    } else if (auto variable = std::dynamic_pointer_cast<VariableExpr>(expr)) {
        return optimizeVariableExpr(variable);
    } else if (auto call = std::dynamic_pointer_cast<CallExpr>(expr)) {
        return optimizeCallExpr(call);
    } else if (auto ternary = std::dynamic_pointer_cast<TernaryExpr>(expr)) {
        return optimizeTernaryExpr(ternary);
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
        return optimizeIfStatement(ifStmt);
    } else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        return optimizeWhileStatement(whileStmt);
    } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
        return optimizeForStatement(forStmt);
    } else if (auto returnStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        return optimizeReturnStatement(returnStmt);
    }
    
    return stmt;
}

// ============================================================================
// EXPRESSION OPTIMIZATIONS
// ============================================================================

std::shared_ptr<BinaryExpr> ASTOptimizer::optimizeBinaryExpr(std::shared_ptr<BinaryExpr> expr) {
    if (!expr) return nullptr;
    
    // Optimize left and right operands first
    expr->left = optimizeExpression(expr->left);
    expr->right = optimizeExpression(expr->right);
    
    // Apply constant folding
    auto folded = foldConstants(expr);
    if (folded != expr) {
        return std::dynamic_pointer_cast<BinaryExpr>(folded);
    }
    
    // Apply algebraic simplification
    auto simplified = simplifyAlgebraic(expr);
    if (simplified != expr) {
        return std::dynamic_pointer_cast<BinaryExpr>(simplified);
    }
    
    return expr;
}

std::shared_ptr<UnaryExpr> ASTOptimizer::optimizeUnaryExpr(std::shared_ptr<UnaryExpr> expr) {
    if (!expr) return nullptr;
    
    // Optimize the operand first
    expr->right = optimizeExpression(expr->right);
    
    // Apply constant folding
    auto folded = foldConstants(expr);
    if (folded != expr) {
        return std::dynamic_pointer_cast<UnaryExpr>(folded);
    }
    
    return expr;
}

std::shared_ptr<InterpolatedStringExpr> ASTOptimizer::optimizeInterpolatedStringExpr(std::shared_ptr<InterpolatedStringExpr> expr) {
    if (!expr) return nullptr;
    
    // Optimize all expression parts
    for (auto& part : expr->parts) {
        if (auto exprPart = std::get_if<std::shared_ptr<Expression>>(&part)) {
            *exprPart = optimizeExpression(*exprPart);
        }
    }
    
    // Apply interpolation lowering
    auto lowered = lowerInterpolation(expr);
    if (lowered != expr) {
        return std::dynamic_pointer_cast<InterpolatedStringExpr>(lowered);
    }
    
    return expr;
}

std::shared_ptr<LiteralExpr> ASTOptimizer::optimizeLiteralExpr(std::shared_ptr<LiteralExpr> expr) {
    // Literals are already optimal, just return as-is
    return expr;
}

std::shared_ptr<VariableExpr> ASTOptimizer::optimizeVariableExpr(std::shared_ptr<VariableExpr> expr) {
    if (!expr) return nullptr;
    
    // Apply constant propagation
    auto propagated = propagateConstants(expr);
    if (propagated != expr) {
        return std::dynamic_pointer_cast<VariableExpr>(propagated);
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

// ============================================================================
// STATEMENT OPTIMIZATIONS
// ============================================================================

std::shared_ptr<VarDeclaration> ASTOptimizer::optimizeVarDeclaration(std::shared_ptr<VarDeclaration> stmt) {
    if (!stmt) return nullptr;
    
    // Optimize initializer if present
    if (stmt->initializer) {
        stmt->initializer = optimizeExpression(stmt->initializer);
        
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

std::shared_ptr<IfStatement> ASTOptimizer::optimizeIfStatement(std::shared_ptr<IfStatement> stmt) {
    if (!stmt) return nullptr;
    
    // Optimize condition
    stmt->condition = optimizeExpression(stmt->condition);
    
    // Apply branch simplification
    if (isCompileTimeTrue(stmt->condition)) {
        // Condition is always true, keep only then branch
        context.stats.branches_simplified++;
        return std::dynamic_pointer_cast<IfStatement>(optimizeStatement(stmt->thenBranch));
    } else if (isCompileTimeFalse(stmt->condition)) {
        // Condition is always false, keep only else branch
        context.stats.branches_simplified++;
        if (stmt->elseBranch) {
            return std::dynamic_pointer_cast<IfStatement>(optimizeStatement(stmt->elseBranch));
        } else {
            return nullptr; // Remove the entire if statement
        }
    }
    
    // Optimize branches
    stmt->thenBranch = optimizeStatement(stmt->thenBranch);
    if (stmt->elseBranch) {
        stmt->elseBranch = optimizeStatement(stmt->elseBranch);
    }
    
    return stmt;
}

std::shared_ptr<WhileStatement> ASTOptimizer::optimizeWhileStatement(std::shared_ptr<WhileStatement> stmt) {
    if (!stmt) return nullptr;
    
    // Optimize condition
    stmt->condition = optimizeExpression(stmt->condition);
    
    // Apply branch simplification
    if (isCompileTimeFalse(stmt->condition)) {
        // Condition is always false, remove the while loop
        context.stats.branches_simplified++;
        return nullptr;
    }
    
    // Optimize body
    stmt->body = optimizeStatement(stmt->body);
    
    return stmt;
}

std::shared_ptr<ForStatement> ASTOptimizer::optimizeForStatement(std::shared_ptr<ForStatement> stmt) {
    if (!stmt) return nullptr;
    
    // Optimize initializer, condition, increment, and body
    if (stmt->initializer) {
        stmt->initializer = optimizeStatement(stmt->initializer);
    }
    if (stmt->condition) {
        stmt->condition = optimizeExpression(stmt->condition);
    }
    if (stmt->increment) {
        stmt->increment = optimizeExpression(stmt->increment);
    }
    stmt->body = optimizeStatement(stmt->body);
    
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
    
    // Handle variable references
    if (auto variable = std::dynamic_pointer_cast<VariableExpr>(expr)) {
        if (context.isConstant(variable->name)) {
            auto constant = context.getConstant(variable->name);
            if (constant) {
                // Create a copy of the constant to avoid modifying the original
                auto copy = std::make_shared<LiteralExpr>(*std::dynamic_pointer_cast<LiteralExpr>(constant));
                if (copy) {
                    // Preserve the variable's inferred type
                    copy->inferred_type = variable->inferred_type;
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
    
    // Check if all parts are string literals
    bool allStringParts = true;
    for (const auto& part : expr->parts) {
        if (!std::holds_alternative<std::string>(part)) {
            allStringParts = false;
            break;
        }
    }
    
    // If all parts are string literals, concatenate them
    if (allStringParts) {
        std::string result;
        for (const auto& part : expr->parts) {
            if (auto strPart = std::get_if<std::string>(&part)) {
                result += *strPart;
            }
        }
        
        auto literal = createStringLiteral(result, expr->line);
        context.stats.interpolations_lowered++;
        return literal;
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
                auto leftStr = std::get_if<std::string>(&leftLiteral->value);
                auto rightStr = std::get_if<std::string>(&rightLiteral->value);
                
                if (leftStr && rightStr) {
                    // Merge adjacent string literals
                    auto merged = createStringLiteral(*leftStr + *rightStr, expr->line);
                    context.stats.strings_canonicalized++;
                    return merged;
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
    
    // Handle string concatenation
    if (op == TokenType::PLUS) {
        auto leftStr = std::get_if<std::string>(&leftLiteral->value);
        auto rightStr = std::get_if<std::string>(&rightLiteral->value);
        
        if (leftStr && rightStr) {
            return createStringLiteral(*leftStr + *rightStr, left->line);
        }
    }
    
    // Handle numeric operations
    auto leftStr = std::get_if<std::string>(&leftLiteral->value);
    auto rightStr = std::get_if<std::string>(&rightLiteral->value);
    
    if (leftStr && rightStr) {
        try {
            double leftNum = std::stod(*leftStr);
            double rightNum = std::stod(*rightStr);
            double result = 0.0;
            
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
                    if (rightNum == 0.0) return nullptr; // Division by zero
                    result = leftNum / rightNum;
                    break;
                case TokenType::MODULUS:
                    if (rightNum == 0.0) return nullptr; // Modulo by zero
                    result = std::fmod(leftNum, rightNum);
                    break;
                case TokenType::LESS:
                    return createBoolLiteral(leftNum < rightNum, left->line);
                case TokenType::LESS_EQUAL:
                    return createBoolLiteral(leftNum <= rightNum, left->line);
                case TokenType::GREATER:
                    return createBoolLiteral(leftNum > rightNum, left->line);
                case TokenType::GREATER_EQUAL:
                    return createBoolLiteral(leftNum >= rightNum, left->line);
                case TokenType::EQUAL_EQUAL:
                    return createBoolLiteral(std::abs(leftNum - rightNum) < 1e-10, left->line);
                case TokenType::BANG_EQUAL:
                    return createBoolLiteral(std::abs(leftNum - rightNum) >= 1e-10, left->line);
                default:
                    return nullptr;
            }
            
            auto resultLiteral = createNumericLiteral(std::to_string(result), left->line);
            return resultLiteral;
            
        } catch (const std::invalid_argument&) {
            // Not numeric, fall through
        } catch (const std::out_of_range&) {
            // Numeric overflow, fall through
        }
    }
    
    // Handle boolean operations
    auto leftBool = std::get_if<bool>(&leftLiteral->value);
    auto rightBool = std::get_if<bool>(&rightLiteral->value);
    
    if (leftBool && rightBool) {
        switch (op) {
            case TokenType::EQUAL_EQUAL:
                return createBoolLiteral(*leftBool == *rightBool, left->line);
            case TokenType::BANG_EQUAL:
                return createBoolLiteral(*leftBool != *rightBool, left->line);
            case TokenType::AND:
                return createBoolLiteral(*leftBool && *rightBool, left->line);
            case TokenType::OR:
                return createBoolLiteral(*leftBool || *rightBool, left->line);
            default:
                return nullptr;
        }
    }
    // This would require proper numeric type support in LiteralExpr
    
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
                double num = std::stod(*strVal);
                return createNumericLiteral(std::to_string(-num), right->line);
            } catch (const std::invalid_argument&) {
                // Not numeric, fall through
            } catch (const std::out_of_range&) {
                // Numeric overflow, fall through
            }
        }
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

} // namespace AST
