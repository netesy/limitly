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

enum class TransformerKind { Map, Filter, Take, Skip };

struct StreamTransformer {
    TransformerKind kind;
    std::shared_ptr<Expression> arg;
    int line = 0;
};

enum class TerminalKind { Fold, ForEach, Collect, Count };

struct StreamTerminal {
    TerminalKind kind;
    std::shared_ptr<Expression> init;
    std::shared_ptr<Expression> func;
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
    lit->value = nullptr;
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

// Check for unsupported control flow inside lambda closures
static bool hasUnsupportedControlFlow(std::shared_ptr<Node> node) {
    if (!node) return false;

    if (auto lambda = std::dynamic_pointer_cast<LambdaExpr>(node)) {
        return hasUnsupportedControlFlow(lambda->body);
    } else if (auto block = std::dynamic_pointer_cast<BlockStatement>(node)) {
        for (size_t i = 0; i < block->statements.size(); ++i) {
            auto s = block->statements[i];
            if (auto ret = std::dynamic_pointer_cast<ReturnStatement>(s)) {
                // Return statement is only allowed as the last statement in top lambda block
                if (i != block->statements.size() - 1) return true;
                if (hasUnsupportedControlFlow(ret->value)) return true;
            } else {
                if (hasUnsupportedControlFlow(s)) return true;
            }
        }
        return false;
    } else if (std::dynamic_pointer_cast<BreakStatement>(node) || std::dynamic_pointer_cast<ContinueStatement>(node)) {
        return true;
    } else if (auto ifStmt = std::dynamic_pointer_cast<IfStatement>(node)) {
        if (hasUnsupportedControlFlow(ifStmt->condition)) return true;
        if (hasUnsupportedControlFlow(ifStmt->thenBranch)) return true;
        if (hasUnsupportedControlFlow(ifStmt->elseBranch)) return true;
    } else if (auto whileStmt = std::dynamic_pointer_cast<WhileStatement>(node)) {
        return true; // loops inside lambda not supported for simple stream inlining
    } else if (auto forStmt = std::dynamic_pointer_cast<ForStatement>(node)) {
        return true;
    } else if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(node)) {
        return hasUnsupportedControlFlow(exprStmt->expression);
    } else if (auto bin = std::dynamic_pointer_cast<BinaryExpr>(node)) {
        return hasUnsupportedControlFlow(bin->left) || hasUnsupportedControlFlow(bin->right);
    } else if (auto un = std::dynamic_pointer_cast<UnaryExpr>(node)) {
        return hasUnsupportedControlFlow(un->right);
    } else if (auto call = std::dynamic_pointer_cast<CallExpr>(node)) {
        if (hasUnsupportedControlFlow(call->callee)) return true;
        for (auto& arg : call->arguments) {
            if (hasUnsupportedControlFlow(arg)) return true;
        }
    }
    return false;
}

// Substitute variable names in AST
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
    }
    return stmt;
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
        pipeline.terminal = {TerminalKind::Fold, terminal_call->arguments[0], terminal_call->arguments[1], line};
    } else if (term_name == "for_each" && terminal_call->arguments.size() == 1) {
        pipeline.terminal = {TerminalKind::ForEach, nullptr, terminal_call->arguments[0], line};
    } else if (term_name == "collect" && terminal_call->arguments.size() == 0) {
        pipeline.terminal = {TerminalKind::Collect, nullptr, nullptr, line};
    } else if (term_name == "count" && terminal_call->arguments.size() == 0) {
        pipeline.terminal = {TerminalKind::Count, nullptr, nullptr, line};
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
                } else if (mem->name == "iter" && call->arguments.size() == 0) {
                    pipeline.source = {SourceKind::Iter, mem->object, nullptr, nullptr, call->line};
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
        if (t.kind == TransformerKind::Map || t.kind == TransformerKind::Filter) {
            if (hasUnsupportedControlFlow(t.arg)) return nullptr;
        }
    }
    if (pipeline.terminal.func && hasUnsupportedControlFlow(pipeline.terminal.func)) return nullptr;

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

    // Transformer processing
    int trans_step = 1;
    for (const auto& t : pipeline.transformers) {
        std::string next_item_name = "__stream_item" + id_str + "_" + std::to_string(trans_step++);

        if (t.kind == TransformerKind::Map) {
            std::shared_ptr<Expression> map_eval;
            if (auto lambda = std::dynamic_pointer_cast<LambdaExpr>(t.arg)) {
                std::unordered_map<std::string, std::shared_ptr<Expression>> sub;
                if (!lambda->params.empty()) {
                    sub[lambda->params[0].first] = makeVarExpr(curr_item_name, line);
                }
                if (lambda->body && !lambda->body->statements.empty()) {
                    for (size_t i = 0; i < lambda->body->statements.size(); ++i) {
                        auto substituted = substituteStmt(lambda->body->statements[i], sub);
                        if (i == lambda->body->statements.size() - 1) {
                            if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(substituted)) {
                                map_eval = exprStmt->expression;
                            } else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(substituted)) {
                                map_eval = retStmt->value;
                            } else {
                                while_body->statements.push_back(substituted);
                                map_eval = makeLiteralNil(line);
                            }
                        } else {
                            while_body->statements.push_back(substituted);
                        }
                    }
                } else {
                    map_eval = makeLiteralNil(line);
                }
            } else {
                map_eval = makeCall(t.arg, {makeVarExpr(curr_item_name, line)}, line);
            }
            while_body->statements.push_back(makeVarDecl(next_item_name, map_eval, line));
            curr_item_name = next_item_name;
        } else if (t.kind == TransformerKind::Filter) {
            std::shared_ptr<Expression> filter_eval;
            if (auto lambda = std::dynamic_pointer_cast<LambdaExpr>(t.arg)) {
                std::unordered_map<std::string, std::shared_ptr<Expression>> sub;
                if (!lambda->params.empty()) {
                    sub[lambda->params[0].first] = makeVarExpr(curr_item_name, line);
                }
                if (lambda->body && !lambda->body->statements.empty()) {
                    for (size_t i = 0; i < lambda->body->statements.size(); ++i) {
                        auto substituted = substituteStmt(lambda->body->statements[i], sub);
                        if (i == lambda->body->statements.size() - 1) {
                            if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(substituted)) {
                                filter_eval = exprStmt->expression;
                            } else if (auto retStmt = std::dynamic_pointer_cast<ReturnStatement>(substituted)) {
                                filter_eval = retStmt->value;
                            } else {
                                while_body->statements.push_back(substituted);
                                filter_eval = makeLiteralNil(line);
                            }
                        } else {
                            while_body->statements.push_back(substituted);
                        }
                    }
                } else {
                    filter_eval = makeLiteralNil(line);
                }
            } else {
                filter_eval = makeCall(t.arg, {makeVarExpr(curr_item_name, line)}, line);
            }

            // if (!filter_eval) continue;
            auto not_filter = makeUnary(TokenType::BANG, filter_eval, line);
            auto cont_stmt = std::make_shared<ContinueStatement>();
            cont_stmt->line = line;

            auto if_not = std::make_shared<IfStatement>();
            if_not->condition = not_filter;
            if_not->thenBranch = cont_stmt;
            if_not->line = line;

            while_body->statements.push_back(if_not);
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

            while_body->statements.push_back(if_take);

            // take_cnt = take_cnt + 1;
            auto inc_take = makeAssign(take_cnt_name, makeBinary(makeVarExpr(take_cnt_name, line), TokenType::PLUS, makeLiteralInt(1, line), line), line);
            while_body->statements.push_back(makeExprStmt(inc_take, line));
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

            while_body->statements.push_back(if_skip);
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
                            while_body->statements.push_back(substituted);
                            fold_eval = makeLiteralNil(line);
                        }
                    } else {
                        while_body->statements.push_back(substituted);
                    }
                }
            } else {
                fold_eval = makeLiteralNil(line);
            }
        } else {
            fold_eval = makeCall(pipeline.terminal.func, {makeVarExpr(acc_var_name, line), makeVarExpr(curr_item_name, line)}, line);
        }

        auto update_acc = makeAssign(acc_var_name, fold_eval, line);
        while_body->statements.push_back(makeExprStmt(update_acc, line));
    } else if (pipeline.terminal.kind == TerminalKind::ForEach) {
        if (auto lambda = std::dynamic_pointer_cast<LambdaExpr>(pipeline.terminal.func)) {
            std::unordered_map<std::string, std::shared_ptr<Expression>> sub;
            if (!lambda->params.empty()) sub[lambda->params[0].first] = makeVarExpr(curr_item_name, line);
            if (lambda->body) {
                for (auto& s : lambda->body->statements) {
                    while_body->statements.push_back(substituteStmt(s, sub));
                }
            }
        } else {
            auto foreach_call = makeCall(pipeline.terminal.func, {makeVarExpr(curr_item_name, line)}, line);
            while_body->statements.push_back(makeExprStmt(foreach_call, line));
        }
    } else if (pipeline.terminal.kind == TerminalKind::Collect) {
        auto append_call = makeCall(makeMember(makeVarExpr(res_var_name, line), "append", line), {makeVarExpr(curr_item_name, line)}, line);
        while_body->statements.push_back(makeExprStmt(append_call, line));
    } else if (pipeline.terminal.kind == TerminalKind::Count) {
        auto inc_cnt = makeAssign(cnt_var_name, makeBinary(makeVarExpr(cnt_var_name, line), TokenType::PLUS, makeLiteralInt(1, line), line), line);
        while_body->statements.push_back(makeExprStmt(inc_cnt, line));
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
    } else if (pipeline.terminal.kind == TerminalKind::Collect) {
        res_expr = makeVarExpr(res_var_name, line);
    } else {
        res_expr = makeLiteralNil(line);
    }

    staged_block->statements.push_back(makeExprStmt(res_expr, line));

    auto staged_expr = std::make_shared<StagedExpr>();
    staged_expr->block = staged_block;
    staged_expr->line = line;

    return staged_expr;
}

} // namespace AST
} // namespace Frontend
} // namespace LM
