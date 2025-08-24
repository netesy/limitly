#include "jit_backend.hh"
#include <iostream>

JitBackend::JitBackend() {
    ctxt = gcc_jit_context_acquire();
    if (!ctxt) {
        // Handle error
        std::cerr << "Failed to acquire JIT context" << std::endl;
        return;
    }
    // Set up options if needed
}

JitBackend::~JitBackend() {
    if (ctxt) {
        gcc_jit_context_release(ctxt);
    }
}

void JitBackend::process(const std::shared_ptr<AST::Program>& program) {
    // Create a main function for the top-level code
    gcc_jit_function* main_func = gcc_jit_context_new_function(
        ctxt,
        nullptr,
        GCC_JIT_FUNCTION_EXPORTED,
        gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT),
        "main",
        0,
        nullptr,
        0
    );

    gcc_jit_block* block = gcc_jit_function_new_block(main_func, "initial");

    for (const auto& stmt : program->statements) {
        if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            visitFunctionDeclaration(funcDecl);
        } else {
            visitStatement(stmt, main_func, block);
        }
    }

    gcc_jit_rvalue* zero = gcc_jit_context_new_rvalue_from_int(ctxt, gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT), 0);
    gcc_jit_block_end_with_return(block, nullptr, zero);
}

void JitBackend::compile(const char* output_filename) {
    if (!ctxt) return;
    gcc_jit_context_compile_to_file(ctxt, GCC_JIT_OUTPUT_KIND_EXECUTABLE, output_filename);
}

gcc_jit_type* JitBackend::to_jit_type(const std::shared_ptr<AST::TypeAnnotation>& type) {
    if (!type) {
        return gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID);
    }
    if (type->typeName == "int") {
        return gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT);
    }
    // Add other type conversions here
    return gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_VOID);
}

void JitBackend::visitFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt) {
    std::cout << "Visiting function: " << stmt->name << std::endl;
    std::vector<gcc_jit_param*> params;
    for (const auto& p : stmt->params) {
        params.push_back(gcc_jit_context_new_param(ctxt, nullptr, to_jit_type(p.second), p.first.c_str()));
    }

    gcc_jit_function* func = gcc_jit_context_new_function(
        ctxt,
        nullptr,
        GCC_JIT_FUNCTION_EXPORTED,
        to_jit_type(stmt->returnType.value_or(nullptr)),
        stmt->name.c_str(),
        params.size(),
        params.data(),
        0
    );

    gcc_jit_block* block = gcc_jit_function_new_block(func, "initial");

    for (const auto& s : stmt->body->statements) {
        visitStatement(s, func, block);
    }

    gcc_jit_block_end_with_void_return(block, nullptr);
}

// Other visitor implementations will go here

gcc_jit_rvalue* JitBackend::visitExpression(const std::shared_ptr<AST::Expression>& expr, gcc_jit_function* func, gcc_jit_block* block) {
    // Dummy implementation
    return nullptr;
}

void JitBackend::visitStatement(const std::shared_ptr<AST::Statement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    std::cout << "Visiting statement, line: " << stmt->line << std::endl;
    if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        visitVarDeclaration(varDecl, func, block);
    } else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        visitExprStatement(exprStmt, func, block);
    } else if (auto printStmt = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
        visitPrintStatement(printStmt, func, block);
    } else if (auto whileStmt = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
        visitWhileStatement(whileStmt, func, block);
    }
    // Add other statement visitors here
}

void JitBackend::visitPrintStatement(const std::shared_ptr<AST::PrintStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block) {
    // Dummy implementation for now
}
