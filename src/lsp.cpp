#include "limitly.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/type_checker.hh"
#include "frontend/module_manager.hh"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <optional>

namespace LM {

struct DocumentSnapshot {
    std::string uri;
    int version = 0;
    std::string content;
    std::vector<Frontend::Token> tokens;
    std::shared_ptr<Frontend::AST::Program> ast;
    bool is_valid = false;
    bool type_check_valid = false;
    std::optional<Frontend::TypeCheckResult> last_check_result;

    void update_range(size_t start_offset, size_t end_offset, const std::string& text) {
        if (start_offset <= content.size() && end_offset <= content.size() && start_offset <= end_offset) {
            content.replace(start_offset, end_offset - start_offset, text);
        } else {
            content = text;
        }
        version++;
        type_check_valid = false;
        relex();
    }

    void relex() {
        Frontend::Scanner scanner(content);
        tokens = scanner.scanTokens();
        try {
            Frontend::Parser parser(scanner, false);
            ast = parser.parse();
            is_valid = (ast != nullptr);
        } catch (...) {
            is_valid = false;
        }
    }
};

class LSPDependencyGraph {
public:
    std::unordered_map<std::string, std::vector<std::string>> file_dependencies;

    void record_import(const std::string& file_uri, const std::string& imported_path) {
        file_dependencies[imported_path].push_back(file_uri);
    }

    void invalidate(const std::string& changed_uri, std::unordered_map<std::string, DocumentSnapshot>& snapshots) {
        auto it = snapshots.find(changed_uri);
        if (it != snapshots.end()) {
            it->second.type_check_valid = false;
        }
        auto dep_it = file_dependencies.find(changed_uri);
        if (dep_it != file_dependencies.end()) {
            for (const auto& dependent : dep_it->second) {
                if (snapshots.count(dependent)) {
                    snapshots[dependent].type_check_valid = false;
                }
            }
        }
    }
};

struct CompletionCandidate {
    std::string label;
    std::string detail;
    int score = 0;
    bool proven = false;
};

class ProofAwareCompletionEngine {
public:
    static std::vector<CompletionCandidate> complete_hole(
        const Frontend::AST::TypedHoleExpr& hole,
        const std::shared_ptr<TypeSystem>& ts) {

        std::vector<CompletionCandidate> results;
        if (!ts) return results;

        for (const auto& [name, type] : hole.lexical_bindings) {
            if (!type) continue;
            CompletionCandidate cand;
            cand.label = name;
            cand.detail = type->toString();

            if (hole.expected_type) {
                if (type->toString() == hole.expected_type->toString()) {
                    cand.score = 100;
                    cand.proven = true;
                } else if (ts->isCompatible(hole.expected_type, type)) {
                    cand.score = 80;
                    cand.proven = true;
                } else {
                    cand.score = 10;
                    cand.proven = false;
                }

                if (hole.expected_type->tag == ::TypeTag::Refined) {
                    if (const auto* refined = std::get_if<RefinedType>(&hole.expected_type->extra)) {
                        auto var_expr = std::make_shared<Frontend::AST::VariableExpr>();
                        var_expr->name = name;
                        Frontend::SMTProofResult proof = Frontend::SMTVerifier::verify_refinement(refined->condition, var_expr);
                        if (proof.status == Frontend::SMTProofStatus::Proven) {
                            cand.score += 20;
                            cand.proven = true;
                        } else if (proof.status == Frontend::SMTProofStatus::Counterexample) {
                            cand.score = 0;
                            cand.proven = false;
                        }
                    }
                }
            } else {
                cand.score = 50;
            }
            results.push_back(cand);
        }

        std::sort(results.begin(), results.end(), [](const CompletionCandidate& a, const CompletionCandidate& b) {
            return a.score > b.score;
        });

        return results;
    }
};

static std::unordered_map<std::string, DocumentSnapshot> g_document_snapshots;
static LSPDependencyGraph g_dependency_graph;

    void LSP::run() {
        std::cerr << "Limitly LSP started (JSON Protocol)..." << std::endl;
        std::string line;
        std::string active_uri = "file://active.lm";

        while (std::getline(std::cin, line)) {
            if (line == "exit") break;
            if (line.empty()) continue;

            try {
                auto& snapshot = g_document_snapshots[active_uri];
                snapshot.uri = active_uri;
                snapshot.update_range(0, snapshot.content.size(), line);
                g_dependency_graph.invalidate(active_uri, g_document_snapshots);

                if (!snapshot.type_check_valid) {
                    if (snapshot.ast) {
                        Frontend::ModuleManager::getInstance().resolve_all(snapshot.ast, "lsp");
                        snapshot.last_check_result = Frontend::TypeCheckerFactory::check_program(
                            snapshot.ast, snapshot.content, "lsp-input");
                    }
                    snapshot.type_check_valid = true;
                }

                auto res = snapshot.last_check_result.value_or(Frontend::TypeCheckResult{nullptr, nullptr, false, {}});

                std::cout << "{" << std::endl;
                std::cout << "  \"success\": " << (res.success ? "true" : "false") << "," << std::endl;
                std::cout << "  \"version\": " << snapshot.version << "," << std::endl;
                std::cout << "  \"errors\": [" << std::endl;
                for (size_t i = 0; i < res.errors.size(); ++i) {
                    std::string err = res.errors[i];
                    size_t pos = 0;
                    while ((pos = err.find('\"', pos)) != std::string::npos) {
                        err.replace(pos, 1, "\\\"");
                        pos += 2;
                    }
                    std::cout << "    { \"message\": \"" << err << "\" }" << (i + 1 < res.errors.size() ? "," : "") << std::endl;
                }
                std::cout << "  ]";

                if (snapshot.ast) {
                    struct HoleVisitor {
                        const Frontend::AST::TypedHoleExpr* hole = nullptr;
                        void visit(const std::shared_ptr<Frontend::AST::Statement>& stmt) {
                            if (!stmt) return;
                            if (auto expr_stmt = std::dynamic_pointer_cast<Frontend::AST::ExprStatement>(stmt)) {
                                visit_expr(expr_stmt->expression);
                            } else if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
                                for (const auto& s : block->statements) visit(s);
                            } else if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
                                if (var_decl->initializer) visit_expr(var_decl->initializer);
                            }
                        }
                        void visit_expr(const std::shared_ptr<Frontend::AST::Expression>& expr) {
                            if (!expr) return;
                            if (auto h = std::dynamic_pointer_cast<Frontend::AST::TypedHoleExpr>(expr)) {
                                hole = h.get();
                            } else if (auto bin = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(expr)) {
                                visit_expr(bin->left);
                                visit_expr(bin->right);
                            } else if (auto assign = std::dynamic_pointer_cast<Frontend::AST::AssignExpr>(expr)) {
                                visit_expr(assign->value);
                            }
                        }
                    } visitor;

                    for (const auto& stmt : snapshot.ast->statements) {
                        visitor.visit(stmt);
                    }

                    if (visitor.hole) {
                        auto candidates = ProofAwareCompletionEngine::complete_hole(*visitor.hole, res.type_system);
                        std::cout << "," << std::endl << "  \"completions\": [" << std::endl;
                        for (size_t i = 0; i < candidates.size(); ++i) {
                            std::cout << "    { \"label\": \"" << candidates[i].label
                                      << "\", \"detail\": \"" << candidates[i].detail
                                      << "\", \"score\": " << candidates[i].score
                                      << ", \"proven\": " << (candidates[i].proven ? "true" : "false")
                                      << " }" << (i + 1 < candidates.size() ? "," : "") << std::endl;
                        }
                        std::cout << "  ]";
                    }
                }

                std::cout << std::endl << "}" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "{ \"success\": false, \"errors\": [{ \"message\": \"" << e.what() << "\" }] }" << std::endl;
            }
            std::cout << std::endl;
        }
    }
}
