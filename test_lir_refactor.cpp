#include "src/lir/lir.hh"
#include "src/lir/lir_generator.hh"
#include "src/backend/register/register_vm.hh"
#include "src/backend/jit/lir_jit_backend.hh"
#include <iostream>
#include <memory>

// Simple AST node stubs for testing
namespace AST {
    struct Expression {
        virtual ~Expression() = default;
    };
    
    struct LiteralExpr : Expression {
        std::variant<int64_t, double, bool, std::string, std::nullptr_t> value;
        LiteralExpr(int64_t val) : value(val) {}
        LiteralExpr(const std::string& val) : value(val) {}
    };
    
    struct BinaryExpr : Expression {
        std::unique_ptr<Expression> left;
        std::unique_ptr<Expression> right;
        TokenType op; // Assuming TokenType is defined elsewhere
        
        BinaryExpr(std::unique_ptr<Expression> left, TokenType op, std::unique_ptr<Expression> right)
            : left(std::move(left)), right(std::move(right)), op(op) {}
    };
    
    struct Statement {
        virtual ~Statement() = default;
    };
    
    struct ExprStatement : Statement {
        std::unique_ptr<Expression> expression;
        ExprStatement(std::unique_ptr<Expression> expr) : expression(std::move(expr)) {}
    };
    
    struct VarDeclaration : Statement {
        std::string name;
        std::unique_ptr<Expression> initializer;
        VarDeclaration(const std::string& name, std::unique_ptr<Expression> init)
            : name(name), initializer(std::move(init)) {}
    };
    
    struct Program {
        std::vector<std::unique_ptr<Statement>> statements;
    };
}

// Test the refactored LIR system
int main() {
    std::cout << "Testing Refactored Register-Based LIR System\\n";
    std::cout << "============================================\\n\\n";
    
    // Create a simple AST: x = 42; y = x + 8;
    auto program = std::make_unique<AST::Program>();
    
    // x = 42
    program->statements.push_back(
        std::make_unique<AST::VarDeclaration>(
            "x", 
            std::make_unique<AST::LiteralExpr>(42)
        )
    );
    
    // y = x + 8
    program->statements.push_back(
        std::make_unique<AST::VarDeclaration>(
            "y",
            std::make_unique<AST::BinaryExpr>(
                std::make_unique<AST::LiteralExpr>(8), // Note: simplified, should be VariableExpr
                TokenType::PLUS,
                std::make_unique<AST::LiteralExpr>(42) // Note: simplified, should be VariableExpr
            )
        )
    );
    
    // Test LIR generation
    std::cout << "1. Testing LIR Generation\\n";
    std::cout << "--------------------------\\n";
    
    LIR::LIRGenerator generator;
    auto lir_function = generator.generate_program(*program);
    
    if (generator.has_errors()) {
        std::cout << "LIR Generation Errors:\\n";
        for (const auto& error : generator.get_errors()) {
            std::cout << "  " << error << "\\n";
        }
        return 1;
    }
    
    std::cout << "Generated LIR:\\n";
    std::cout << lir_function->to_string() << "\\n";
    
    // Test LIR interpretation
    std::cout << "\\n2. Testing LIR Interpretation\\n";
    std::cout << "-----------------------------\\n";
    
    Register::RegisterVM interpreter;
    interpreter.execute_function(*lir_function);
    
    std::cout << "Interpretation completed. Final register state:\\n";
    for (uint32_t i = 0; i < lir_function->register_count; ++i) {
        const auto& value = interpreter.get_register(i);
        std::cout << "  r" << i << " = " << interpreter.register_value_to_string(value) << "\\n";
    }
    
    // Test LIR JIT compilation
    std::cout << "\\n3. Testing LIR JIT Compilation\\n";
    std::cout << "------------------------------\\n";
    
    try {
        LirJitBackend jit_backend;
        jit_backend.process_function(*lir_function);
        
        if (jit_backend.has_errors()) {
            std::cout << "JIT Compilation Errors:\\n";
            for (const auto& error : jit_backend.get_errors()) {
                std::cout << "  " << error << "\\n";
            }
        } else {
            std::cout << "JIT compilation successful!\\n";
            
            // Test interpretation through JIT backend
            std::cout << "\\n4. Testing Interpretation via JIT Backend\\n";
            std::cout << "----------------------------------------\\n";
            jit_backend.interpret_function(*lir_function);
        }
    } catch (const std::exception& e) {
        std::cout << "JIT compilation failed with exception: " << e.what() << "\\n";
    }
    
    std::cout << "\\nTest completed!\\n";
    return 0;
}
