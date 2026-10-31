#include "stream_fusion.hh"
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace LM {
namespace Frontend {
namespace AST {

enum class SourceKind { Iter, Range };

struct StreamSource {
    SourceKind kind;
    std::shared_ptr<Expression> collection;
    std::shared_ptr<Expression> start;
    std::shared_ptr<Expression> end;
    int line = 0;
};

enum class TransformerKind { Map, Filter, Take, Skip, FlatMap };

struct StreamTransformer {
    TransformerKind kind;
    std::shared_ptr<Expression> arg;
    int line = 0;
};

enum class TerminalKind { Fold, ForEach, Collect, Count, CollectDict, ToDict };

struct StreamTerminal {
    TerminalKind kind;
    std::shared_ptr<Expression> init;
    std::shared_ptr<Expression> func;
    std::shared_ptr<Expression> val_func;
    int line = 0;
};

struct StreamPipeline {
    StreamSource source;
    std::vector<StreamTransformer> transformers;
    StreamTerminal terminal;
};

// AST construction helpers
static std::shared_ptr<VariableExpr> makeVarExpr(const std::string& name, int line) {
    auto v = std::make_shared<VariableExpr>();
    v->name = name;
    v->line = line;
    return v;
}

static std::shared_ptr<LiteralExpr> makeLiteralInt(int64_t val, int line) {
    auto lit = std::make_shared<LiteralExpr>();
    lit->value = std::to_string(val);
    lit->literalType = TokenType::INT_LITERAL;
    lit->inferred_type = std::make_shared<::Type>(::TypeTag::Int64);
    lit->line = line;
    return lit;
}

static std::shared_ptr<LiteralExpr> makeLiteralNil(int line) {
    auto lit = std::make_shared<LiteralExpr>();
    lit->value = std::string("nil");
    lit->literalType = TokenType::NIL;
    lit->inferred_type = std::make_shared<::Type>(::TypeTag::Nil);
    lit->line = line;
    return lit;
}

static std::shared_ptr<ListExpr> makeLiteralList(int line) {
    auto l = std::make_shared<ListExpr>();
    l->line = line;
    l->inferred_type = std::make_shared<::Type>(::TypeTag::List);
    return l;
}

static std::shared_ptr<DictExpr> makeLiteralDict(int line) {
    auto d = std::make_shared<DictExpr>();
    d->line = line;
    d->inferred_type = std::make_shared<::Type>(::TypeTag::Dict);
    return d;
}

static std::shared_ptr<AssignExpr> makeIndexAssign(std::shared_ptr<Expression> obj, std::shared_ptr<Expression> idx, std::shared_ptr<Expression> val, int line) {
    auto assign = std::make_shared<AssignExpr>();
    assign->object = obj;
    assign->index = idx;
    assign->value = val;
    assign->op = TokenType::EQUAL;
    assign->line = line;
    return assign;
}

static std::shared_ptr<VarDeclaration> makeVarDecl(const std::string& name, std::shared_ptr<Expression> init, int line) {
    auto decl = std::make_shared<VarDeclaration>();
    decl->name = name;
    decl->initializer = init;
    decl->line = line;
    return decl;
}

static std::shared_ptr<AssignExpr> makeAssign(const std::string& name, std::shared_ptr<Expression> val, int line) {
    auto assign = std::make_shared<AssignExpr>();
    assign->name = name;
    assign->value = val;
    assign->op = TokenType::EQUAL;
    assign->line = line;
    return assign;
}

static std::shared_ptr<BinaryExpr> makeBinary(std::shared_ptr<Expression> left, TokenType op, std::shared_ptr<Expression> right, int line) {
    auto bin = std::make_shared<BinaryExpr>();
    bin->left = left;
    bin->op = op;
    bin->right = right;
    bin->line = line;
    return bin;
}

static std::shared_ptr<UnaryExpr> makeUnary(TokenType op, std::shared_ptr<Expression> right, int line) {
    auto un = std::make_shared<UnaryExpr>();
    un->op = op;
    un->right = right;
    un->line = line;
    return un;
}

static std::shared_ptr<CallExpr> makeCall(std::shared_ptr<Expression> callee, std::vector<std::shared_ptr<Expression>> args, int line) {
    auto call = std::make_shared<CallExpr>();
    call->callee = callee;
    call->arguments = args;
    call->line = line;
    return call;
}

static std::shared_ptr<MemberExpr> makeMember(std::shared_ptr<Expression> obj, const std::string& member, int line) {
    auto mem = std::make_shared<MemberExpr>();
    mem->object = obj;
    mem->name = member;
    mem->line = line;
    return mem;
}

static std::shared_ptr<IndexExpr> makeIndex(std::shared_ptr<Expression> obj, std::shared_ptr<Expression> idx, int line) {
    auto idxExpr = std::make_shared<IndexExpr>();
    idxExpr->object = obj;
    idxExpr->index = idx;
    idxExpr->line = line;
    return idxExpr;
}

static std::shared_ptr<ExprStatement> makeExprStmt(std::shared_ptr<Expression> expr, int line) {
    auto stmt = std::make_shared<ExprStatement>();
    stmt->expression = expr;
    stmt->line = line;
    return stmt;
}

// Check for unsupported control flow (e.g. returns, loops, breaks) inside closure AST
static bool containsControlFlowOrReturn(std::shared_ptr<Node> node) {
    if (!node) return false;

    if (std::dynamic_pointer_cast<ReturnStatement>(node) ||
        std::dynamic_pointer_cast<BreakStatement>(node) ||
        std::dynamic_pointer_cast<ContinueStatement>(node) ||
        std::dynamic_pointer_cast<WhileStatement>(node) ||
        std::dynamic_pointer_cast<ForStatement>(node)) {
        return true;
    }

    if (auto block = std::dynamic_pointer_cast<BlockStatement>(node)) {
        for (auto& s : block->statements) {
            if (containsControlFlowOrReturn(s)) return true;
        }
    } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(node)) {
        if (containsControlFlowOrReturn(ifStmt->condition)) return true;
        if (containsControlFlowOrReturn(ifStmt->thenBranch)) return true;
        if (containsControlFlowOrReturn(ifStmt->elseBranch)) return true;
    } else if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(node)) {
        return containsControlFlowOrReturn(exprStmt->expression);
    } else if (auto bin = std::dynamic_pointer_cast<BinaryExpr>(node)) {
        return containsControlFlowOrReturn(bin->left) || containsControlFlowOrReturn(bin->right);
    } else if (auto un = std::dynamic_pointer_cast<UnaryExpr>(node)) {
        return containsControlFlowOrReturn(un->right);
    } else if (auto call = std::dynamic_pointer_cast<CallExpr>(node)) {
        if (containsControlFlowOrReturn(call->callee)) return true;
        for (auto& arg : call->arguments) {
            if (containsControlFlowOrReturn(arg)) return true;
        }
    } else if (auto varDecl = std::dynamic_pointer_cast<VarDeclaration>(node)) {
        if (containsControlFlowOrReturn(varDecl->initializer)) return true;
    }

    return false;
}

static bool hasUnsupportedControlFlow(std::shared_ptr<Node> node) {
    if (!node) return false;

    if (auto lambda = std::dynamic_pointer_cast<LambdaExpr>(node)) {
        if (!lambda->body) return false;
        const auto& stmts = lambda->body->statements;
        for (size_t i = 0; i < stmts.size(); ++i) {
            if (i == stmts.size() - 1) {
                // Trailing statement may be a return statement or expression
                if (auto ret = std::dynamic_pointer_cast<ReturnStatement>(stmts[i])) {
                    if (containsControlFlowOrReturn(ret->value)) return true;
                } else {
                    if (containsControlFlowOrReturn(stmts[i])) return true;
                }
            } else {
                if (containsControlFlowOrReturn(stmts[i])) return true;
            }
        }
        return false;
    }

    return containsControlFlowOrReturn(node);
}

// Substitute variable names in AST recursively across all expression/statement types
static std::shared_ptr<Expression> substituteExpr(std::shared_ptr<Expression> expr, const std::unordered_map<std::string, std::shared_ptr<Expression>>& subMap);
static std::shared_ptr<Statement> substituteStmt(std::shared_ptr<Statement> stmt, const std::unordered_map<std::string, std::shared_ptr<Expression>>& subMap);

static std::shared_ptr<Expression> substituteExpr(std::shared_ptr<Expression> expr, const std::unordered_map<std::string, std::shared_ptr<Expression>>& subMap) {
    if (!expr) return nullptr;

    if (auto var = std::dynamic_pointer_cast<VariableExpr>(expr)) {
        auto it = subMap.find(var->name);
        if (it != subMap.end()) return it->second;
        auto copy = std::make_shared<VariableExpr>();
        copy->name = var->name;
        copy->line = var->line;
        copy->inferred_type = var->inferred_type;
        return copy;
    } else if (auto bin = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        auto copy = std::make_shared<BinaryExpr>();
        copy->left = substituteExpr(bin->left, subMap);
        copy->op = bin->op;
        copy->right = substituteExpr(bin->right, subMap);
        copy->line = bin->line;
        copy->inferred_type = bin->inferred_type;
        return copy;
    } else if (auto un = std::dynamic_pointer_cast<UnaryExpr>(expr)) {
        auto copy = std::make_shared<UnaryExpr>();
        copy->op = un->op;
        copy->right = substituteExpr(un->right, subMap);
        copy->line = un->line;
        copy->inferred_type = un->inferred_type;
        return copy;
    } else if (auto call = std::dynamic_pointer_cast<CallExpr>(expr)) {
        auto copy = std::make_shared<CallExpr>();
        copy->callee = substituteExpr(call->callee, subMap);
        for (auto& a : call->arguments) copy->arguments.push_back(substituteExpr(a, subMap));
        copy->line = call->line;
        copy->inferred_type = call->inferred_type;
        return copy;
    } else if (auto closureCall = std::dynamic_pointer_cast<CallClosureExpr>(expr)) {
        auto copy = std::make_shared<CallClosureExpr>();
        copy->closure = substituteExpr(closureCall->closure, subMap);
        for (auto& a : closureCall->arguments) copy->arguments.push_back(substituteExpr(a, subMap));
        copy->line = closureCall->line;
        copy->inferred_type = closureCall->inferred_type;
        return copy;
    } else if (auto mem = std::dynamic_pointer_cast<MemberExpr>(expr)) {
        auto copy = std::make_shared<MemberExpr>();
        copy->object = substituteExpr(mem->object, subMap);
        copy->name = mem->name;
        copy->isSafeAccess = mem->isSafeAccess;
        copy->line = mem->line;
        copy->inferred_type = mem->inferred_type;
        return copy;
    } else if (auto idx = std::dynamic_pointer_cast<IndexExpr>(expr)) {
        auto copy = std::make_shared<IndexExpr>();
        copy->object = substituteExpr(idx->object, subMap);
        copy->index = substituteExpr(idx->index, subMap);
        copy->line = idx->line;
        copy->inferred_type = idx->inferred_type;
        return copy;
    } else if (auto assign = std::dynamic_pointer_cast<AssignExpr>(expr)) {
        auto copy = std::make_shared<AssignExpr>();
        copy->name = assign->name;
        if (subMap.count(assign->name)) {
            if (auto v = std::dynamic_pointer_cast<VariableExpr>(subMap.at(assign->name))) {
                copy->name = v->name;
            }
        }
        copy->object = substituteExpr(assign->object, subMap);
        copy->member = assign->member;
        copy->index = substituteExpr(assign->index, subMap);
        copy->value = substituteExpr(assign->value, subMap);
        copy->op = assign->op;
        copy->line = assign->line;
        copy->inferred_type = assign->inferred_type;
        return copy;
    } else if (auto grp = std::dynamic_pointer_cast<GroupingExpr>(expr)) {
        auto copy = std::make_shared<GroupingExpr>();
        copy->expression = substituteExpr(grp->expression, subMap);
        copy->line = grp->line;
        copy->inferred_type = grp->inferred_type;
        return copy;
    } else if (auto listExpr = std::dynamic_pointer_cast<ListExpr>(expr)) {
        auto copy = std::make_shared<ListExpr>();
        for (auto& elem : listExpr->elements) copy->elements.push_back(substituteExpr(elem, subMap));
        copy->line = listExpr->line;
        copy->inferred_type = listExpr->inferred_type;
        return copy;
    } else if (auto tupleExpr = std::dynamic_pointer_cast<TupleExpr>(expr)) {
        auto copy = std::make_shared<TupleExpr>();
        for (auto& elem : tupleExpr->elements) copy->elements.push_back(substituteExpr(elem, subMap));
        copy->line = tupleExpr->line;
        copy->inferred_type = tupleExpr->inferred_type;
        return copy;
    } else if (auto dictExpr = std::dynamic_pointer_cast<DictExpr>(expr)) {
        auto copy = std::make_shared<DictExpr>();
        for (auto& entry : dictExpr->entries) {
            copy->entries.push_back({substituteExpr(entry.first, subMap), substituteExpr(entry.second, subMap)});
        }
        copy->line = dictExpr->line;
        copy->inferred_type = dictExpr->inferred_type;
        return copy;
    } else if (auto objLit = std::dynamic_pointer_cast<ObjectLiteralExpr>(expr)) {
        auto copy = std::make_shared<ObjectLiteralExpr>();
        copy->constructorName = objLit->constructorName;
        for (auto& kv : objLit->properties) {
            copy->properties[kv.first] = substituteExpr(kv.second, subMap);
        }
        copy->line = objLit->line;
        copy->inferred_type = objLit->inferred_type;
        return copy;
    } else if (auto frameInst = std::dynamic_pointer_cast<FrameInstantiationExpr>(expr)) {
        auto copy = std::make_shared<FrameInstantiationExpr>();
        copy->frameName = frameInst->frameName;
        for (auto& arg : frameInst->positionalArgs) copy->positionalArgs.push_back(substituteExpr(arg, subMap));
        for (auto& kv : frameInst->namedArgs) copy->namedArgs[kv.first] = substituteExpr(kv.second, subMap);
        copy->line = frameInst->line;
        copy->inferred_type = frameInst->inferred_type;
        return copy;
    } else if (auto rng = std::dynamic_pointer_cast<RangeExpr>(expr)) {
        auto copy = std::make_shared<RangeExpr>();
        copy->start = substituteExpr(rng->start, subMap);
        copy->end = substituteExpr(rng->end, subMap);
        copy->step = substituteExpr(rng->step, subMap);
        copy->inclusive = rng->inclusive;
        copy->line = rng->line;
        copy->inferred_type = rng->inferred_type;
        return copy;
    } else if (auto interp = std::dynamic_pointer_cast<InterpolatedStringExpr>(expr)) {
        auto copy = std::make_shared<InterpolatedStringExpr>();
        for (auto& part : interp->parts) {
            if (std::holds_alternative<std::string>(part)) {
                copy->parts.push_back(part);
            } else {
                copy->parts.push_back(substituteExpr(std::get<std::shared_ptr<Expression>>(part), subMap));
            }
        }
        copy->line = interp->line;
        copy->inferred_type = interp->inferred_type;
        return copy;
    } else if (auto cast = std::dynamic_pointer_cast<CastExpr>(expr)) {
        auto copy = std::make_shared<CastExpr>();
        copy->expression = substituteExpr(cast->expression, subMap);
        copy->targetType = cast->targetType;
        copy->line = cast->line;
        copy->inferred_type = cast->inferred_type;
        return copy;
    } else if (auto fallible = std::dynamic_pointer_cast<FallibleExpr>(expr)) {
        auto copy = std::make_shared<FallibleExpr>();
        copy->expression = substituteExpr(fallible->expression, subMap);
        copy->elseHandler = substituteStmt(fallible->elseHandler, subMap);
        copy->elseVariable = fallible->elseVariable;
        copy->line = fallible->line;
        copy->inferred_type = fallible->inferred_type;
        return copy;
    } else if (auto ok = std::dynamic_pointer_cast<OkConstructExpr>(expr)) {
        auto copy = std::make_shared<OkConstructExpr>();
        copy->value = substituteExpr(ok->value, subMap);
        copy->line = ok->line;
        copy->inferred_type = ok->inferred_type;
        return copy;
    } else if (auto errCons = std::dynamic_pointer_cast<ErrorConstructExpr>(expr)) {
        auto copy = std::make_shared<ErrorConstructExpr>();
        copy->errorType = errCons->errorType;
        for (auto& arg : errCons->arguments) copy->arguments.push_back(substituteExpr(arg, subMap));
        copy->line = errCons->line;
        copy->inferred_type = errCons->inferred_type;
        return copy;
    } else if (auto some = std::dynamic_pointer_cast<SomeConstructExpr>(expr)) {
        auto copy = std::make_shared<SomeConstructExpr>();
        copy->value = substituteExpr(some->value, subMap);
        copy->line = some->line;
        copy->inferred_type = some->inferred_type;
        return copy;
    } else if (auto lit = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
        return lit;
    }
    return expr;
}

static std::shared_ptr<Statement> substituteStmt(std::shared_ptr<Statement> stmt, const std::unordered_map<std::string, std::shared_ptr<Expression>>& subMap) {
    if (!stmt) return nullptr;

    if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(stmt)) {
        auto copy = std::make_shared<ExprStatement>();
        copy->expression = substituteExpr(exprStmt->expression, subMap);
        copy->line = exprStmt->line;
        return copy;
    } else if (auto varDecl = std::dynamic_pointer_cast<VarDeclaration>(stmt)) {
        auto copy = std::make_shared<VarDeclaration>();
        copy->name = varDecl->name;
        copy->initializer = substituteExpr(varDecl->initializer, subMap);
        copy->line = varDecl->line;
        return copy;
    } else if (auto ret = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        auto copy = std::make_shared<ReturnStatement>();
        copy->value = substituteExpr(ret->value, subMap);
        copy->line = ret->line;
        return copy;
    } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        auto copy = std::make_shared<IfStatement>();
        copy->condition = substituteExpr(ifStmt->condition, subMap);
        copy->thenBranch = substituteStmt(ifStmt->thenBranch, subMap);
        copy->elseBranch = substituteStmt(ifStmt->elseBranch, subMap);
        copy->line = ifStmt->line;
        return copy;
    } else if (auto block = std::dynamic_pointer_cast<BlockStatement>(stmt)) {
        auto copy = std::make_shared<BlockStatement>();
        for (auto& s : block->statements) copy->statements.push_back(substituteStmt(s, subMap));
        copy->line = block->line;
        return copy;
    }
    return stmt;
}

static std::shared_ptr<Expression> inlineUnaryLambdaOrCall(
    std::shared_ptr<Expression> fn,
    const std::string& arg_var_name,
    std::shared_ptr<BlockStatement> target_body,
    int line)
{
    if (auto lambda = std::dynamic_pointer_cast<LambdaExpr>(fn)) {
        std::unordered_map<std::string, std::shared_ptr<Expression>> sub;
        if (!lambda->params.empty()) {
            sub[lambda->params[0].first] = makeVarExpr(arg_var_name, line);
        }
        if (lambda->body && !lambda->body->statements.empty()) {
            for (size_t i = 0; i < lambda->body->statements.size(); ++i) {
                auto substituted = substituteStmt(lambda->body->statements[i], sub);
                if (i == lambda->body->statements.size() - 1) {
                    if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(substituted)) {
                        return exprStmt->expression;
                    } else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(substituted)) {
                        return retStmt->value;
                    } else {
                        target_body->statements.push_back(substituted);
                        return makeLiteralNil(line);
                    }
                } else {
                    target_body->statements.push_back(substituted);
                }
            }
        }
        return makeLiteralNil(line);
    }
    return makeCall(fn, {makeVarExpr(arg_var_name, line)}, line);
}

// Main optimization function
std::shared_ptr<Program> StreamFusionVisitor::optimizeProgram(std::shared_ptr<Program> program) {
    if (!program) return nullptr;
    StreamFusionVisitor visitor;
    for (auto& stmt : program->statements) {
        stmt = visitor.visitStatement(stmt);
    }
    return program;
}

std::shared_ptr<Statement> StreamFusionVisitor::visitStatement(std::shared_ptr<Statement> stmt) {
    if (!stmt) return nullptr;

    if (auto funcDecl = std::dynamic_pointer_cast<FunctionDeclaration>(stmt)) {
        if (funcDecl->body) funcDecl->body = std::dynamic_pointer_cast<BlockStatement>(visitStatement(funcDecl->body));
    } else if (auto frameDecl = std::dynamic_pointer_cast<FrameDeclaration>(stmt)) {
        for (auto& m : frameDecl->methods) {
            if (m->body) m->body = std::dynamic_pointer_cast<BlockStatement>(visitStatement(m->body));
        }
        if (frameDecl->init && frameDecl->init->body) {
            frameDecl->init->body = std::dynamic_pointer_cast<BlockStatement>(visitStatement(frameDecl->init->body));
        }
        if (frameDecl->deinit && frameDecl->deinit->body) {
            frameDecl->deinit->body = std::dynamic_pointer_cast<BlockStatement>(visitStatement(frameDecl->deinit->body));
        }
    } else if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(stmt)) {
        exprStmt->expression = visitExpression(exprStmt->expression);
    } else if (auto varDecl = std::dynamic_pointer_cast<VarDeclaration>(stmt)) {
        if (varDecl->initializer) varDecl->initializer = visitExpression(varDecl->initializer);
    } else if (auto block = std::dynamic_pointer_cast<BlockStatement>(stmt)) {
        for (auto& s : block->statements) s = visitStatement(s);
    } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(stmt)) {
        if (ifStmt->condition) ifStmt->condition = visitExpression(ifStmt->condition);
        if (ifStmt->thenBranch) ifStmt->thenBranch = visitStatement(ifStmt->thenBranch);
        if (ifStmt->elseBranch) ifStmt->elseBranch = visitStatement(ifStmt->elseBranch);
    } else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(stmt)) {
        if (whileStmt->condition) whileStmt->condition = visitExpression(whileStmt->condition);
        if (whileStmt->body) whileStmt->body = visitStatement(whileStmt->body);
    } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(stmt)) {
        if (forStmt->initializer) forStmt->initializer = visitStatement(forStmt->initializer);
        if (forStmt->condition) forStmt->condition = visitExpression(forStmt->condition);
        if (forStmt->increment) forStmt->increment = visitExpression(forStmt->increment);
        if (forStmt->body) forStmt->body = visitStatement(forStmt->body);
    } else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt)) {
        if (retStmt->value) retStmt->value = visitExpression(retStmt->value);
    }
    return stmt;
}

std::shared_ptr<Expression> StreamFusionVisitor::visitExpression(std::shared_ptr<Expression> expr) {
    if (!expr) return nullptr;

    if (auto call = std::dynamic_pointer_cast<CallExpr>(expr)) {
        // Recursively optimize callee & arguments first
        call->callee = visitExpression(call->callee);
        for (auto& arg : call->arguments) arg = visitExpression(arg);

        // Attempt stream fusion
        auto fused = tryFusePipeline(call);
        if (fused) return fused;
    } else if (auto bin = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        bin->left = visitExpression(bin->left);
        bin->right = visitExpression(bin->right);
    } else if (auto un = std::dynamic_pointer_cast<UnaryExpr>(expr)) {
        un->right = visitExpression(un->right);
    } else if (auto assign = std::dynamic_pointer_cast<AssignExpr>(expr)) {
        if (assign->value) assign->value = visitExpression(assign->value);
        if (assign->object) assign->object = visitExpression(assign->object);
        if (assign->index) assign->index = visitExpression(assign->index);
    } else if (auto mem = std::dynamic_pointer_cast<MemberExpr>(expr)) {
        mem->object = visitExpression(mem->object);
    } else if (auto idx = std::dynamic_pointer_cast<IndexExpr>(expr)) {
        idx->object = visitExpression(idx->object);
        idx->index = visitExpression(idx->index);
    } else if (auto staged = std::dynamic_pointer_cast<StagedExpr>(expr)) {
        if (staged->expression) staged->expression = visitExpression(staged->expression);
        if (staged->block) staged->block = std::dynamic_pointer_cast<BlockStatement>(visitStatement(staged->block));
    }
    return expr;
}

std::shared_ptr<Expression> StreamFusionVisitor::tryFusePipeline(std::shared_ptr<CallExpr> terminal_call) {
    if (!terminal_call) return nullptr;

    StreamPipeline pipeline;
    int line = terminal_call->line;

    // 1. Identify Terminal Consumer
    auto mem_callee = std::dynamic_pointer_cast<MemberExpr>(terminal_call->callee);
    if (!mem_callee) return nullptr;

    std::string term_name = mem_callee->name;
    if (term_name == "fold" && terminal_call->arguments.size() == 2) {
        pipeline.terminal = {TerminalKind::Fold, terminal_call->arguments[0], terminal_call->arguments[1], nullptr, line};
    } else if (term_name == "for_each" && terminal_call->arguments.size() == 1) {
        pipeline.terminal = {TerminalKind::ForEach, nullptr, terminal_call->arguments[0], nullptr, line};
    } else if (term_name == "collect" && terminal_call->arguments.size() == 0) {
        pipeline.terminal = {TerminalKind::Collect, nullptr, nullptr, nullptr, line};
    } else if (term_name == "count" && terminal_call->arguments.size() == 0) {
        pipeline.terminal = {TerminalKind::Count, nullptr, nullptr, nullptr, line};
    } else if (term_name == "collect_dict" && terminal_call->arguments.size() == 0) {
        pipeline.terminal = {TerminalKind::CollectDict, nullptr, nullptr, nullptr, line};
    } else if (term_name == "to_dict") {
        if (terminal_call->arguments.size() == 0) {
            pipeline.terminal = {TerminalKind::ToDict, nullptr, nullptr, nullptr, line};
        } else if (terminal_call->arguments.size() == 1) {
            pipeline.terminal = {TerminalKind::ToDict, nullptr, terminal_call->arguments[0], nullptr, line};
        } else if (terminal_call->arguments.size() == 2) {
            pipeline.terminal = {TerminalKind::ToDict, nullptr, terminal_call->arguments[0], terminal_call->arguments[1], line};
        } else {
            return nullptr;
        }
    } else {
        return nullptr; // Not a recognized terminal consumer
    }

    // 2. Trace upstream chain
    std::shared_ptr<Expression> current = mem_callee->object;
    bool source_found = false;

    while (current) {
        if (auto group = std::dynamic_pointer_cast<GroupingExpr>(current)) {
            current = group->expression;
            continue;
        }
        if (auto call = std::dynamic_pointer_cast<CallExpr>(current)) {
            if (auto mem = std::dynamic_pointer_cast<MemberExpr>(call->callee)) {
                if (mem->name == "map" && call->arguments.size() == 1) {
                    pipeline.transformers.push_back({TransformerKind::Map, call->arguments[0], call->line});
                    current = mem->object;
                } else if (mem->name == "filter" && call->arguments.size() == 1) {
                    pipeline.transformers.push_back({TransformerKind::Filter, call->arguments[0], call->line});
                    current = mem->object;
                } else if (mem->name == "take" && call->arguments.size() == 1) {
                    pipeline.transformers.push_back({TransformerKind::Take, call->arguments[0], call->line});
                    current = mem->object;
                } else if (mem->name == "skip" && call->arguments.size() == 1) {
                    pipeline.transformers.push_back({TransformerKind::Skip, call->arguments[0], call->line});
                    current = mem->object;
                } else if (mem->name == "flat_map" && call->arguments.size() == 1) {
                    pipeline.transformers.push_back({TransformerKind::FlatMap, call->arguments[0], call->line});
                    current = mem->object;
                } else if (mem->name == "flatten" && call->arguments.size() == 0) {
                    auto id_lambda = std::make_shared<LambdaExpr>();
                    id_lambda->line = call->line;
                    id_lambda->params = {{"__flat_elem", nullptr}};
                    auto ret_stmt = std::make_shared<ReturnStatement>();
                    ret_stmt->line = call->line;
                    ret_stmt->value = makeVarExpr("__flat_elem", call->line);
                    auto body_block = std::make_shared<BlockStatement>();
                    body_block->line = call->line;
                    body_block->statements.push_back(ret_stmt);
                    id_lambda->body = body_block;
                    pipeline.transformers.push_back({TransformerKind::FlatMap, id_lambda, call->line});
                    current = mem->object;
                } else if (mem->name == "iter" && call->arguments.size() == 0) {
                    std::shared_ptr<Expression> src_coll = mem->object;
                    if (std::dynamic_pointer_cast<DictExpr>(src_coll) ||
                        (src_coll && src_coll->inferred_type && src_coll->inferred_type->tag == TypeTag::Dict)) {
                        src_coll = makeCall(makeMember(src_coll, "items", call->line), {}, call->line);
                    }
                    pipeline.source = {SourceKind::Iter, src_coll, nullptr, nullptr, call->line};
                    source_found = true;
                    break;
                } else if (mem->name == "items" && call->arguments.size() == 0) {
                    pipeline.source = {SourceKind::Iter, current, nullptr, nullptr, call->line};
                    source_found = true;
                    break;
                } else if (mem->name == "range" && call->arguments.size() == 2) {
                    pipeline.source = {SourceKind::Range, nullptr, call->arguments[0], call->arguments[1], call->line};
                    source_found = true;
                    break;
                } else {
                    break;
                }
            } else if (auto varCallee = std::dynamic_pointer_cast<VariableExpr>(call->callee)) {
                if (varCallee->name == "range" && call->arguments.size() == 2) {
                    pipeline.source = {SourceKind::Range, nullptr, call->arguments[0], call->arguments[1], call->line};
                    source_found = true;
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        } else if (auto range = std::dynamic_pointer_cast<RangeExpr>(current)) {
            pipeline.source = {SourceKind::Range, nullptr, range->start, range->end, range->line};
            source_found = true;
            break;
        } else {
            break;
        }
    }

    if (!source_found) return nullptr;

    // Reverse transformers so they run in source-to-terminal order
    std::reverse(pipeline.transformers.begin(), pipeline.transformers.end());

    // 3. Check for unsupported control flow in closure arguments
    for (auto& t : pipeline.transformers) {
        if (t.kind == TransformerKind::Map || t.kind == TransformerKind::Filter || t.kind == TransformerKind::FlatMap) {
            if (hasUnsupportedControlFlow(t.arg)) return nullptr;
        }
    }
    if (pipeline.terminal.func && hasUnsupportedControlFlow(pipeline.terminal.func)) return nullptr;
    if (pipeline.terminal.val_func && hasUnsupportedControlFlow(pipeline.terminal.val_func)) return nullptr;

    // 4. Synthesize Flat While Loop AST
    uint64_t id = stream_id_counter++;
    std::string id_str = "_" + std::to_string(id);

    auto staged_block = std::make_shared<BlockStatement>();
    staged_block->line = line;

    // Names for variables
    std::string src_var_name = "__stream_src" + id_str;
    std::string idx_var_name = "__stream_idx" + id_str;
    std::string len_var_name = "__stream_len" + id_str;
    std::string end_var_name = "__stream_end" + id_str;
    std::string acc_var_name = "__stream_acc" + id_str;
    std::string cnt_var_name = "__stream_cnt" + id_str;
    std::string res_var_name = "__stream_res" + id_str;

    // Prologue setup
    std::shared_ptr<Expression> loop_cond;

    if (pipeline.source.kind == SourceKind::Iter) {
        staged_block->statements.push_back(makeVarDecl(src_var_name, pipeline.source.collection, line));
        staged_block->statements.push_back(makeVarDecl(idx_var_name, makeLiteralInt(0, line), line));
        auto len_call = makeCall(makeMember(makeVarExpr(src_var_name, line), "len", line), {}, line);
        staged_block->statements.push_back(makeVarDecl(len_var_name, len_call, line));

        loop_cond = makeBinary(makeVarExpr(idx_var_name, line), TokenType::LESS, makeVarExpr(len_var_name, line), line);
    } else { // Range
        staged_block->statements.push_back(makeVarDecl(idx_var_name, pipeline.source.start, line));
        staged_block->statements.push_back(makeVarDecl(end_var_name, pipeline.source.end, line));

        loop_cond = makeBinary(makeVarExpr(idx_var_name, line), TokenType::LESS, makeVarExpr(end_var_name, line), line);
    }

    // Terminal accumulator / result setup in prologue
    if (pipeline.terminal.kind == TerminalKind::Fold) {
        staged_block->statements.push_back(makeVarDecl(acc_var_name, pipeline.terminal.init, line));
    } else if (pipeline.terminal.kind == TerminalKind::Count) {
        staged_block->statements.push_back(makeVarDecl(cnt_var_name, makeLiteralInt(0, line), line));
    } else if (pipeline.terminal.kind == TerminalKind::Collect) {
        staged_block->statements.push_back(makeVarDecl(res_var_name, makeLiteralList(line), line));
    } else if (pipeline.terminal.kind == TerminalKind::CollectDict || pipeline.terminal.kind == TerminalKind::ToDict) {
        staged_block->statements.push_back(makeVarDecl(res_var_name, makeLiteralDict(line), line));
    }

    // Loop Body
    auto while_body = std::make_shared<BlockStatement>();
    while_body->line = line;

    // Fetch initial element
    std::string curr_item_name = "__stream_elem" + id_str + "_0";
    if (pipeline.source.kind == SourceKind::Iter) {
        auto fetch_idx = makeIndex(makeVarExpr(src_var_name, line), makeVarExpr(idx_var_name, line), line);
        while_body->statements.push_back(makeVarDecl(curr_item_name, fetch_idx, line));
    } else {
        while_body->statements.push_back(makeVarDecl(curr_item_name, makeVarExpr(idx_var_name, line), line));
    }

    // Increment index counter
    auto inc_idx = makeAssign(idx_var_name, makeBinary(makeVarExpr(idx_var_name, line), TokenType::PLUS, makeLiteralInt(1, line), line), line);
    while_body->statements.push_back(makeExprStmt(inc_idx, line));

    auto current_body = while_body;

    // Transformer processing
    int trans_step = 1;
    for (const auto& t : pipeline.transformers) {
        std::string next_item_name = "__stream_item" + id_str + "_" + std::to_string(trans_step++);

        if (t.kind == TransformerKind::Map) {
            auto map_eval = inlineUnaryLambdaOrCall(t.arg, curr_item_name, current_body, line);
            current_body->statements.push_back(makeVarDecl(next_item_name, map_eval, line));
            curr_item_name = next_item_name;
        } else if (t.kind == TransformerKind::Filter) {
            auto filter_eval = inlineUnaryLambdaOrCall(t.arg, curr_item_name, current_body, line);
            auto not_filter = makeUnary(TokenType::BANG, filter_eval, line);
            auto cont_stmt = std::make_shared<ContinueStatement>();
            cont_stmt->line = line;

            auto if_not = std::make_shared<IfStatement>();
            if_not->condition = not_filter;
            if_not->thenBranch = cont_stmt;
            if_not->line = line;

            current_body->statements.push_back(if_not);
        } else if (t.kind == TransformerKind::Take) {
            std::string take_cnt_name = "__stream_take_cnt" + id_str + "_" + std::to_string(trans_step);
            staged_block->statements.push_back(makeVarDecl(take_cnt_name, makeLiteralInt(0, line), line));

            // if (take_cnt >= limit) break;
            auto cond = makeBinary(makeVarExpr(take_cnt_name, line), TokenType::GREATER_EQUAL, t.arg, line);
            auto brk_stmt = std::make_shared<BreakStatement>();
            brk_stmt->line = line;

            auto if_take = std::make_shared<IfStatement>();
            if_take->condition = cond;
            if_take->thenBranch = brk_stmt;
            if_take->line = line;

            current_body->statements.push_back(if_take);

            // take_cnt = take_cnt + 1;
            auto inc_take = makeAssign(take_cnt_name, makeBinary(makeVarExpr(take_cnt_name, line), TokenType::PLUS, makeLiteralInt(1, line), line), line);
            current_body->statements.push_back(makeExprStmt(inc_take, line));
        } else if (t.kind == TransformerKind::Skip) {
            std::string skip_cnt_name = "__stream_skip_cnt" + id_str + "_" + std::to_string(trans_step);
            staged_block->statements.push_back(makeVarDecl(skip_cnt_name, makeLiteralInt(0, line), line));

            // if (skip_cnt < target) { skip_cnt = skip_cnt + 1; continue; }
            auto cond = makeBinary(makeVarExpr(skip_cnt_name, line), TokenType::LESS, t.arg, line);
            auto skip_block = std::make_shared<BlockStatement>();
            skip_block->line = line;

            auto inc_skip = makeAssign(skip_cnt_name, makeBinary(makeVarExpr(skip_cnt_name, line), TokenType::PLUS, makeLiteralInt(1, line), line), line);
            skip_block->statements.push_back(makeExprStmt(inc_skip, line));

            auto cont_stmt = std::make_shared<ContinueStatement>();
            cont_stmt->line = line;
            skip_block->statements.push_back(cont_stmt);

            auto if_skip = std::make_shared<IfStatement>();
            if_skip->condition = cond;
            if_skip->thenBranch = skip_block;
            if_skip->line = line;

            current_body->statements.push_back(if_skip);
        } else if (t.kind == TransformerKind::FlatMap) {
            auto inner_eval = inlineUnaryLambdaOrCall(t.arg, curr_item_name, current_body, line);

            std::string inner_id_str = id_str + "_inner_" + std::to_string(trans_step);
            std::string inner_src_name = "__stream_inner_src" + inner_id_str;
            std::string inner_idx_name = "__stream_inner_idx" + inner_id_str;
            std::string inner_len_name = "__stream_inner_len" + inner_id_str;
            std::string inner_end_name = "__stream_inner_end" + inner_id_str;
            std::string inner_elem_name = "__stream_inner_elem" + inner_id_str;

            auto inner_while_body = std::make_shared<BlockStatement>();
            inner_while_body->line = line;

            auto unwrapped_inner = inner_eval;
            while (auto g = std::dynamic_pointer_cast<GroupingExpr>(unwrapped_inner)) {
                unwrapped_inner = g->expression;
            }

            std::shared_ptr<Expression> inner_loop_cond;

            if (auto range = std::dynamic_pointer_cast<RangeExpr>(unwrapped_inner)) {
                current_body->statements.push_back(makeVarDecl(inner_idx_name, range->start, line));
                current_body->statements.push_back(makeVarDecl(inner_end_name, range->end, line));
                inner_loop_cond = makeBinary(makeVarExpr(inner_idx_name, line), TokenType::LESS, makeVarExpr(inner_end_name, line), line);

                inner_while_body->statements.push_back(makeVarDecl(inner_elem_name, makeVarExpr(inner_idx_name, line), line));
            } else {
                current_body->statements.push_back(makeVarDecl(inner_src_name, inner_eval, line));
                current_body->statements.push_back(makeVarDecl(inner_idx_name, makeLiteralInt(0, line), line));
                auto len_call = makeCall(makeMember(makeVarExpr(inner_src_name, line), "len", line), {}, line);
                current_body->statements.push_back(makeVarDecl(inner_len_name, len_call, line));
                inner_loop_cond = makeBinary(makeVarExpr(inner_idx_name, line), TokenType::LESS, makeVarExpr(inner_len_name, line), line);

                auto fetch_idx = makeIndex(makeVarExpr(inner_src_name, line), makeVarExpr(inner_idx_name, line), line);
                inner_while_body->statements.push_back(makeVarDecl(inner_elem_name, fetch_idx, line));
            }

            auto inc_inner_idx = makeAssign(inner_idx_name, makeBinary(makeVarExpr(inner_idx_name, line), TokenType::PLUS, makeLiteralInt(1, line), line), line);
            inner_while_body->statements.push_back(makeExprStmt(inc_inner_idx, line));

            auto inner_while = std::make_shared<WhileStatement>();
            inner_while->condition = inner_loop_cond;
            inner_while->body = inner_while_body;
            inner_while->line = line;

            current_body->statements.push_back(inner_while);
            current_body = inner_while_body;
            curr_item_name = inner_elem_name;
        }
    }

    // Terminal consumer loop action
    if (pipeline.terminal.kind == TerminalKind::Fold) {
        std::shared_ptr<Expression> fold_eval;
        if (auto lambda = std::dynamic_pointer_cast<LambdaExpr>(pipeline.terminal.func)) {
            std::unordered_map<std::string, std::shared_ptr<Expression>> sub;
            if (lambda->params.size() >= 1) sub[lambda->params[0].first] = makeVarExpr(acc_var_name, line);
            if (lambda->params.size() >= 2) sub[lambda->params[1].first] = makeVarExpr(curr_item_name, line);

            if (lambda->body && !lambda->body->statements.empty()) {
                for (size_t i = 0; i < lambda->body->statements.size(); ++i) {
                    auto substituted = substituteStmt(lambda->body->statements[i], sub);
                    if (i == lambda->body->statements.size() - 1) {
                        if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(substituted)) {
                            fold_eval = exprStmt->expression;
                        } else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(substituted)) {
                            fold_eval = retStmt->value;
                        } else {
                            current_body->statements.push_back(substituted);
                            fold_eval = makeLiteralNil(line);
                        }
                    } else {
                        current_body->statements.push_back(substituted);
                    }
                }
            } else {
                fold_eval = makeLiteralNil(line);
            }
        } else {
            fold_eval = makeCall(pipeline.terminal.func, {makeVarExpr(acc_var_name, line), makeVarExpr(curr_item_name, line)}, line);
        }

        auto update_acc = makeAssign(acc_var_name, fold_eval, line);
        current_body->statements.push_back(makeExprStmt(update_acc, line));
    } else if (pipeline.terminal.kind == TerminalKind::ForEach) {
        if (auto lambda = std::dynamic_pointer_cast<LambdaExpr>(pipeline.terminal.func)) {
            std::unordered_map<std::string, std::shared_ptr<Expression>> sub;
            if (!lambda->params.empty()) sub[lambda->params[0].first] = makeVarExpr(curr_item_name, line);
            if (lambda->body) {
                for (auto& s : lambda->body->statements) {
                    current_body->statements.push_back(substituteStmt(s, sub));
                }
            }
        } else {
            auto foreach_call = makeCall(pipeline.terminal.func, {makeVarExpr(curr_item_name, line)}, line);
            current_body->statements.push_back(makeExprStmt(foreach_call, line));
        }
    } else if (pipeline.terminal.kind == TerminalKind::Collect) {
        auto append_call = makeCall(makeMember(makeVarExpr(res_var_name, line), "append", line), {makeVarExpr(curr_item_name, line)}, line);
        current_body->statements.push_back(makeExprStmt(append_call, line));
    } else if (pipeline.terminal.kind == TerminalKind::Count) {
        auto inc_cnt = makeAssign(cnt_var_name, makeBinary(makeVarExpr(cnt_var_name, line), TokenType::PLUS, makeLiteralInt(1, line), line), line);
        current_body->statements.push_back(makeExprStmt(inc_cnt, line));
    } else if (pipeline.terminal.kind == TerminalKind::CollectDict) {
        auto key_expr = makeIndex(makeVarExpr(curr_item_name, line), makeLiteralInt(0, line), line);
        auto val_expr = makeIndex(makeVarExpr(curr_item_name, line), makeLiteralInt(1, line), line);
        auto assign = makeIndexAssign(makeVarExpr(res_var_name, line), key_expr, val_expr, line);
        current_body->statements.push_back(makeExprStmt(assign, line));
    } else if (pipeline.terminal.kind == TerminalKind::ToDict) {
        if (!pipeline.terminal.func) {
            auto key_expr = makeIndex(makeVarExpr(curr_item_name, line), makeLiteralInt(0, line), line);
            auto val_expr = makeIndex(makeVarExpr(curr_item_name, line), makeLiteralInt(1, line), line);
            auto assign = makeIndexAssign(makeVarExpr(res_var_name, line), key_expr, val_expr, line);
            current_body->statements.push_back(makeExprStmt(assign, line));
        } else if (!pipeline.terminal.val_func) {
            std::string kv_name = "__stream_kv" + id_str + "_" + std::to_string(trans_step++);
            auto kv_eval = inlineUnaryLambdaOrCall(pipeline.terminal.func, curr_item_name, current_body, line);
            current_body->statements.push_back(makeVarDecl(kv_name, kv_eval, line));
            auto key_expr = makeIndex(makeVarExpr(kv_name, line), makeLiteralInt(0, line), line);
            auto val_expr = makeIndex(makeVarExpr(kv_name, line), makeLiteralInt(1, line), line);
            auto assign = makeIndexAssign(makeVarExpr(res_var_name, line), key_expr, val_expr, line);
            current_body->statements.push_back(makeExprStmt(assign, line));
        } else {
            std::string k_name = "__stream_k" + id_str + "_" + std::to_string(trans_step++);
            auto k_eval = inlineUnaryLambdaOrCall(pipeline.terminal.func, curr_item_name, current_body, line);
            current_body->statements.push_back(makeVarDecl(k_name, k_eval, line));

            std::string v_name = "__stream_v" + id_str + "_" + std::to_string(trans_step++);
            auto v_eval = inlineUnaryLambdaOrCall(pipeline.terminal.val_func, curr_item_name, current_body, line);
            current_body->statements.push_back(makeVarDecl(v_name, v_eval, line));

            auto assign = makeIndexAssign(makeVarExpr(res_var_name, line), makeVarExpr(k_name, line), makeVarExpr(v_name, line), line);
            current_body->statements.push_back(makeExprStmt(assign, line));
        }
    }

    // Assemble while statement
    auto while_stmt = std::make_shared<WhileStatement>();
    while_stmt->condition = loop_cond;
    while_stmt->body = while_body;
    while_stmt->line = line;

    staged_block->statements.push_back(while_stmt);

    // Epilogue result expression
    std::shared_ptr<Expression> res_expr;
    if (pipeline.terminal.kind == TerminalKind::Fold) {
        res_expr = makeVarExpr(acc_var_name, line);
    } else if (pipeline.terminal.kind == TerminalKind::Count) {
        res_expr = makeVarExpr(cnt_var_name, line);
    } else if (pipeline.terminal.kind == TerminalKind::Collect ||
               pipeline.terminal.kind == TerminalKind::CollectDict ||
               pipeline.terminal.kind == TerminalKind::ToDict) {
        res_expr = makeVarExpr(res_var_name, line);
    } else {
        res_expr = makeLiteralNil(line);
    }

    staged_block->statements.push_back(makeExprStmt(res_expr, line));

    auto staged_expr = std::make_shared<StagedExpr>();
    staged_expr->block = staged_block;
    staged_expr->line = line;
    // Signal to the LIR generator that every ListIndex inside this block is
    // provably in-bounds (stream_fusion emits `while (idx < len(src))` and
    // rejects pipelines whose body would grow/shrink `src`), so the backend
    // can lower a straight-line, vectorizable loop body.
    staged_expr->synthesized = true;

    return staged_expr;
}

} // namespace AST
} // namespace Frontend
} // namespace LM
