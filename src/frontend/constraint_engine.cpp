#include "constraint_engine.hh"
#include "ast.hh"
#include "scanner.hh"
#include <queue>
#include <algorithm>
#include <iostream>
#include <limits>

namespace LM {
namespace Frontend {

static bool safe_add(int64_t a, int64_t b, int64_t& res) {
#if defined(__GNUC__) || defined(__clang__)
    return !__builtin_add_overflow(a, b, &res);
#else
    res = a + b;
    return true;
#endif
}

static bool safe_sub(int64_t a, int64_t b, int64_t& res) {
#if defined(__GNUC__) || defined(__clang__)
    return !__builtin_sub_overflow(a, b, &res);
#else
    res = a - b;
    return true;
#endif
}

static bool safe_mul(int64_t a, int64_t b, int64_t& res) {
#if defined(__GNUC__) || defined(__clang__)
    return !__builtin_mul_overflow(a, b, &res);
#else
    res = a * b;
    return true;
#endif
}

static int64_t floor_div(int64_t a, int64_t b) {
    if (b < 0) {
        if (b == std::numeric_limits<int64_t>::min()) return 0;
        a = -a;
        b = -b;
    }
    if (b == 0) return 0;
    if (a >= 0) return a / b;
    return (a - b + 1) / b;
}

static int64_t ceil_div(int64_t a, int64_t b) {
    if (b < 0) {
        if (b == std::numeric_limits<int64_t>::min()) return 0;
        a = -a;
        b = -b;
    }
    if (b == 0) return 0;
    if (a >= 0) return (a + b - 1) / b;
    return a / b;
}

bool ConstraintEngine::add_constraint(const NormalizedConstraint& constraint) {
    constraints_.push_back(constraint);

    for (const auto& [var, _] : constraint.lhs.coeffs) {
        variables_.insert(var);
    }
    for (const auto& [var, _] : constraint.rhs.coeffs) {
        variables_.insert(var);
    }

    if (!update_intervals()) {
        contradiction_ = true;
        return false;
    }
    return true;
}

bool ConstraintEngine::update_intervals() {
    for (const auto& c : constraints_) {
        LinearTerm diff = c.lhs - c.rhs;

        if (diff.is_constant()) {
            int64_t offset = diff.constant_offset;
            bool satisfies = false;
            switch (c.op) {
                case RelationOp::Equal: satisfies = (offset == 0); break;
                case RelationOp::NotEqual: satisfies = (offset != 0); break;
                case RelationOp::LessThan: satisfies = (offset < 0); break;
                case RelationOp::LessEqual: satisfies = (offset <= 0); break;
                case RelationOp::GreaterThan: satisfies = (offset > 0); break;
                case RelationOp::GreaterEqual: satisfies = (offset >= 0); break;
            }
            if (!satisfies) {
                return false; // Direct constant contradiction!
            }
            continue;
        }

        VarId var;
        int64_t coeff = 0;

        if (diff.is_single_variable(var, coeff)) {
            int64_t offset = diff.constant_offset;
            if (offset == std::numeric_limits<int64_t>::min()) {
                return false; // Overflow protection for INT64_MIN
            }
            variables_.insert(var);
            Interval& iv = intervals_[var];

            if (coeff > 0) {
                switch (c.op) {
                    case RelationOp::LessEqual:
                        iv.max_val = std::min(iv.max_val, floor_div(-offset, coeff));
                        break;
                    case RelationOp::LessThan:
                        iv.max_val = std::min(iv.max_val, floor_div(-offset - 1, coeff));
                        break;
                    case RelationOp::GreaterEqual:
                        iv.min_val = std::max(iv.min_val, ceil_div(-offset, coeff));
                        break;
                    case RelationOp::GreaterThan:
                        iv.min_val = std::max(iv.min_val, ceil_div(-offset + 1, coeff));
                        break;
                    case RelationOp::Equal:
                        if ((-offset) % coeff != 0) {
                            return false; // No integer solution
                        }
                        iv.min_val = std::max(iv.min_val, (-offset) / coeff);
                        iv.max_val = std::min(iv.max_val, (-offset) / coeff);
                        break;
                    default:
                        break;
                }
            } else if (coeff < 0) {
                int64_t abs_coeff = -coeff;
                switch (c.op) {
                    case RelationOp::LessEqual:
                        iv.min_val = std::max(iv.min_val, ceil_div(offset, abs_coeff));
                        break;
                    case RelationOp::LessThan:
                        iv.min_val = std::max(iv.min_val, ceil_div(offset + 1, abs_coeff));
                        break;
                    case RelationOp::GreaterEqual:
                        iv.max_val = std::min(iv.max_val, floor_div(offset, abs_coeff));
                        break;
                    case RelationOp::GreaterThan:
                        iv.max_val = std::min(iv.max_val, floor_div(offset - 1, abs_coeff));
                        break;
                    case RelationOp::Equal:
                        if (offset % abs_coeff != 0) {
                            return false; // No integer solution
                        }
                        iv.min_val = std::max(iv.min_val, offset / abs_coeff);
                        iv.max_val = std::min(iv.max_val, offset / abs_coeff);
                        break;
                    default:
                        break;
                }
            }

            if (iv.is_empty()) {
                return false; // Contradiction detected
            }
        }
    }
    return true;
}

bool ConstraintEngine::check_difference_graph() const {
    std::set<VarId> all_vars = variables_;
    for (const auto& [var, _] : intervals_) {
        all_vars.insert(var);
    }
    for (const auto& c : constraints_) {
        for (const auto& [var, _] : c.lhs.coeffs) all_vars.insert(var);
        for (const auto& [var, _] : c.rhs.coeffs) all_vars.insert(var);
    }

    std::vector<VarId> nodes = {"__zero__"};
    nodes.insert(nodes.end(), all_vars.begin(), all_vars.end());

    std::unordered_map<VarId, size_t> node_map;
    for (size_t i = 0; i < nodes.size(); ++i) {
        node_map[nodes[i]] = i;
    }

    struct Edge {
        size_t u;
        size_t v;
        int64_t weight;
    };

    std::vector<Edge> edges;

    for (const auto& [var, iv] : intervals_) {
        auto it = node_map.find(var);
        if (it == node_map.end()) continue;
        size_t u = it->second;
        size_t zero = node_map.at("__zero__");
        if (iv.max_val < std::numeric_limits<int64_t>::max() / 2) {
            edges.push_back({zero, u, iv.max_val});
        }
        if (iv.min_val > std::numeric_limits<int64_t>::min() / 2) {
            edges.push_back({u, zero, -iv.min_val});
        }
    }

    for (const auto& c : constraints_) {
        LinearTerm diff = c.lhs - c.rhs;
        if (diff.coeffs.size() == 2) {
            auto it = diff.coeffs.begin();
            VarId v1 = it->first;
            int64_t c1 = it->second;
            ++it;
            VarId v2 = it->first;
            int64_t c2 = it->second;

            auto it1 = node_map.find(v1);
            auto it2 = node_map.find(v2);
            if (it1 == node_map.end() || it2 == node_map.end()) continue;

            size_t u1 = it1->second;
            size_t u2 = it2->second;
            int64_t rhs_val = -diff.constant_offset;

            if (c1 == 1 && c2 == -1) {
                if (c.op == RelationOp::LessEqual) {
                    edges.push_back({u2, u1, rhs_val});
                } else if (c.op == RelationOp::LessThan) {
                    edges.push_back({u2, u1, rhs_val - 1});
                } else if (c.op == RelationOp::GreaterEqual) {
                    edges.push_back({u1, u2, -rhs_val});
                } else if (c.op == RelationOp::GreaterThan) {
                    edges.push_back({u1, u2, -rhs_val - 1});
                } else if (c.op == RelationOp::Equal) {
                    edges.push_back({u2, u1, rhs_val});
                    edges.push_back({u1, u2, -rhs_val});
                }
            } else if (c1 == -1 && c2 == 1) {
                if (c.op == RelationOp::LessEqual) {
                    edges.push_back({u1, u2, rhs_val});
                } else if (c.op == RelationOp::LessThan) {
                    edges.push_back({u1, u2, rhs_val - 1});
                } else if (c.op == RelationOp::GreaterEqual) {
                    edges.push_back({u2, u1, -rhs_val});
                } else if (c.op == RelationOp::GreaterThan) {
                    edges.push_back({u2, u1, -rhs_val - 1});
                } else if (c.op == RelationOp::Equal) {
                    edges.push_back({u1, u2, rhs_val});
                    edges.push_back({u2, u1, -rhs_val});
                }
            }
        }
    }

    size_t n = nodes.size();
    if (n == 0) return true;

    std::vector<int64_t> dist(n, 0);
    std::vector<size_t> count(n, 0);
    std::vector<bool> in_queue(n, true);
    std::queue<size_t> q;

    for (size_t i = 0; i < n; ++i) {
        q.push(i);
    }

    while (!q.empty()) {
        size_t u = q.front();
        q.pop();
        in_queue[u] = false;

        for (const auto& edge : edges) {
            if (edge.u == u) {
                size_t v = edge.v;
                int64_t w = edge.weight;
                int64_t new_dist = 0;
                if (safe_add(dist[u], w, new_dist)) {
                    if (new_dist < dist[v]) {
                        dist[v] = new_dist;
                        count[v]++;
                        if (count[v] >= n) {
                            return false; // Negative cycle detected -> contradiction
                        }
                        if (!in_queue[v]) {
                            q.push(v);
                            in_queue[v] = true;
                        }
                    }
                }
            }
        }
    }

    return true; // No contradiction
}

bool ConstraintEngine::is_inconsistent() const {
    if (contradiction_) return true;
    for (const auto& [var, iv] : intervals_) {
        if (iv.is_empty()) return true;
    }
    return !check_difference_graph();
}

bool ConstraintEngine::is_difference_implied(const VarId& x, const VarId& y, int64_t bound) const {
    ConstraintEngine test_engine = *this;
    NormalizedConstraint negation;
    negation.op = RelationOp::GreaterThan;
    negation.lhs.add_term(x, 1);
    negation.rhs.add_term(y, 1);
    negation.rhs.constant_offset = bound;

    test_engine.add_constraint(negation);
    return test_engine.is_inconsistent();
}

NativeProofResult ConstraintEngine::verify_obligation(
    const NormalizedConstraint& target_constraint,
    const std::vector<NormalizedConstraint>& assumptions) {

    NativeProofResult result;

    ConstraintEngine proven_engine;
    for (const auto& asm_c : assumptions) {
        proven_engine.add_constraint(asm_c);
    }

    if (proven_engine.is_inconsistent()) {
        result.status = NativeProofStatus::Proven;
        result.message = "Inconsistent assumptions statically imply obligation";
        return result;
    }

    NormalizedConstraint negated_target = target_constraint;
    switch (target_constraint.op) {
        case RelationOp::Equal: negated_target.op = RelationOp::NotEqual; break;
        case RelationOp::NotEqual: negated_target.op = RelationOp::Equal; break;
        case RelationOp::LessThan: negated_target.op = RelationOp::GreaterEqual; break;
        case RelationOp::LessEqual: negated_target.op = RelationOp::GreaterThan; break;
        case RelationOp::GreaterThan: negated_target.op = RelationOp::LessEqual; break;
        case RelationOp::GreaterEqual: negated_target.op = RelationOp::LessThan; break;
    }

    proven_engine.add_constraint(negated_target);
    if (proven_engine.is_inconsistent()) {
        result.status = NativeProofStatus::Proven;
        result.message = "Obligation statically proven by native constraint engine";
        return result;
    }

    ConstraintEngine counter_engine;
    for (const auto& asm_c : assumptions) {
        counter_engine.add_constraint(asm_c);
    }
    counter_engine.add_constraint(target_constraint);
    if (counter_engine.is_inconsistent()) {
        result.status = NativeProofStatus::Counterexample;
        result.message = "Native constraint engine proved obligation is FALSE (Counterexample)";
        return result;
    }

    result.status = NativeProofStatus::Unknown;
    result.message = "Native constraint engine could not prove or disprove obligation";
    return result;
}

bool ConstraintBuilder::extract_expr_name(
    std::shared_ptr<AST::Expression> expr,
    std::string& out_name) {

    if (!expr) return false;

    if (auto var = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        out_name = var->name;
        return true;
    } else if (auto mem = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
        std::string base;
        if (extract_expr_name(mem->object, base)) {
            out_name = base + "." + mem->name;
            return true;
        }
    } else if (auto cast = std::dynamic_pointer_cast<AST::CastExpr>(expr)) {
        return extract_expr_name(cast->expression, out_name);
    }

    return false;
}

bool ConstraintBuilder::extract_linear_term(
    std::shared_ptr<AST::Expression> expr,
    LinearTerm& out_term) {

    if (!expr) return false;

    if (auto lit = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        if (lit->literalType == TokenType::STRING) return false;
        if (std::holds_alternative<std::string>(lit->value)) {
            try {
                out_term.constant_offset = std::stoll(std::get<std::string>(lit->value));
                return true;
            } catch (...) {
                return false;
            }
        }
        if (std::holds_alternative<bool>(lit->value)) {
            out_term.constant_offset = std::get<bool>(lit->value) ? 1 : 0;
            return true;
        }
    } else if (auto var = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        out_term.add_term(var->name, 1);
        return true;
    } else if (auto mem = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
        std::string name;
        if (extract_expr_name(mem, name)) {
            out_term.add_term(name, 1);
            return true;
        }
    } else if (auto cast = std::dynamic_pointer_cast<AST::CastExpr>(expr)) {
        return extract_linear_term(cast->expression, out_term);
    } else if (auto grp = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) {
        return extract_linear_term(grp->expression, out_term);
    } else if (auto un = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        if (un->op == TokenType::MINUS) {
            LinearTerm right_term;
            if (!extract_linear_term(un->right, right_term)) return false;
            out_term = right_term.scale(-1);
            return true;
        }
    } else if (auto bin = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        LinearTerm left_term, right_term;
        if (bin->op == TokenType::PLUS) {
            if (!extract_linear_term(bin->left, left_term)) return false;
            if (!extract_linear_term(bin->right, right_term)) return false;
            int64_t new_offset = 0;
            if (!safe_add(left_term.constant_offset, right_term.constant_offset, new_offset)) return false;
            out_term = left_term + right_term;
            out_term.constant_offset = new_offset;
            return true;
        } else if (bin->op == TokenType::MINUS) {
            if (!extract_linear_term(bin->left, left_term)) return false;
            if (!extract_linear_term(bin->right, right_term)) return false;
            int64_t new_offset = 0;
            if (!safe_sub(left_term.constant_offset, right_term.constant_offset, new_offset)) return false;
            out_term = left_term - right_term;
            out_term.constant_offset = new_offset;
            return true;
        } else if (bin->op == TokenType::STAR) {
            if (extract_linear_term(bin->left, left_term) && left_term.is_constant()) {
                if (!extract_linear_term(bin->right, right_term)) return false;
                int64_t new_offset = 0;
                if (!safe_mul(right_term.constant_offset, left_term.constant_offset, new_offset)) return false;
                out_term = right_term.scale(left_term.constant_offset);
                out_term.constant_offset = new_offset;
                return true;
            }
            if (extract_linear_term(bin->right, right_term) && right_term.is_constant()) {
                if (!extract_linear_term(bin->left, left_term)) return false;
                int64_t new_offset = 0;
                if (!safe_mul(left_term.constant_offset, right_term.constant_offset, new_offset)) return false;
                out_term = left_term.scale(right_term.constant_offset);
                out_term.constant_offset = new_offset;
                return true;
            }
            // Non-linear integer multiplication (where neither side is constant)
            // cannot be converted to a linear term with constant coefficients -> fail closed
            return false;
        } else if (bin->op == TokenType::SLASH || bin->op == TokenType::MODULUS) {
            // Non-constant division/modulo cannot be converted to a linear term -> fail closed
            return false;
        }
    }

    return false;
}

bool ConstraintBuilder::build_constraint(
    std::shared_ptr<AST::Expression> expr,
    NormalizedConstraint& out_constraint) {

    if (!expr) return false;

    if (auto bin = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        RelationOp op;
        switch (bin->op) {
            case TokenType::EQUAL_EQUAL: op = RelationOp::Equal; break;
            case TokenType::BANG_EQUAL: op = RelationOp::NotEqual; break;
            case TokenType::LESS: op = RelationOp::LessThan; break;
            case TokenType::LESS_EQUAL: op = RelationOp::LessEqual; break;
            case TokenType::GREATER: op = RelationOp::GreaterThan; break;
            case TokenType::GREATER_EQUAL: op = RelationOp::GreaterEqual; break;
            default: return false;
        }

        LinearTerm lhs_term, rhs_term;
        if (!extract_linear_term(bin->left, lhs_term)) return false;
        if (!extract_linear_term(bin->right, rhs_term)) return false;

        out_constraint.op = op;
        out_constraint.lhs = lhs_term;
        out_constraint.rhs = rhs_term;
        return true;
    }

    return false;
}

} // namespace Frontend
} // namespace LM
