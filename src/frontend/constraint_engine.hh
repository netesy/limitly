#ifndef LIMITLY_CONSTRAINT_ENGINE_HH
#define LIMITLY_CONSTRAINT_ENGINE_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include <set>
#include <optional>
#include <limits>
#include <cstdint>

namespace LM {
namespace Frontend {

namespace AST {
    struct Expression;
}

enum class NativeProofStatus {
    Proven,
    Counterexample, // Definite violation
    Unknown,
    Unsupported,
    SolverError
};

struct NativeProofResult {
    NativeProofStatus status = NativeProofStatus::Unknown;
    std::string message;
};

using VarId = std::string;

struct LinearTerm {
    int64_t constant_offset = 0;
    std::map<VarId, int64_t> coeffs;

    bool is_constant() const { return coeffs.empty(); }
    bool is_single_variable(VarId& out_var, int64_t& out_coeff) const {
        if (coeffs.size() == 1) {
            out_var = coeffs.begin()->first;
            out_coeff = coeffs.begin()->second;
            return true;
        }
        return false;
    }

    void add_term(const VarId& var, int64_t coeff) {
        if (coeff == 0) return;
        coeffs[var] += coeff;
        if (coeffs[var] == 0) {
            coeffs.erase(var);
        }
    }

    LinearTerm operator+(const LinearTerm& other) const {
        LinearTerm res = *this;
        res.constant_offset += other.constant_offset;
        for (const auto& [var, coeff] : other.coeffs) {
            res.add_term(var, coeff);
        }
        return res;
    }

    LinearTerm operator-(const LinearTerm& other) const {
        LinearTerm res = *this;
        res.constant_offset -= other.constant_offset;
        for (const auto& [var, coeff] : other.coeffs) {
            res.add_term(var, -coeff);
        }
        return res;
    }

    LinearTerm scale(int64_t factor) const {
        LinearTerm res;
        res.constant_offset = constant_offset * factor;
        for (const auto& [var, coeff] : coeffs) {
            res.add_term(var, coeff * factor);
        }
        return res;
    }
};

enum class RelationOp {
    Equal,
    NotEqual,
    LessThan,
    LessEqual,
    GreaterThan,
    GreaterEqual
};

struct NormalizedConstraint {
    RelationOp op = RelationOp::Equal;
    LinearTerm lhs;
    LinearTerm rhs;
};

struct Interval {
    int64_t min_val = std::numeric_limits<int64_t>::min();
    int64_t max_val = std::numeric_limits<int64_t>::max();

    bool is_empty() const { return min_val > max_val; }
};

class ConstraintEngine {
public:
    ConstraintEngine() = default;

    bool add_constraint(const NormalizedConstraint& constraint);

    // Core proof query: does the current set of constraints imply target?
    static NativeProofResult verify_obligation(
        const NormalizedConstraint& target_constraint,
        const std::vector<NormalizedConstraint>& assumptions = {});

    // Utility query for difference constraints: x - y <= bound
    bool is_difference_implied(const VarId& x, const VarId& y, int64_t bound) const;
    bool is_inconsistent() const;

private:
    std::vector<NormalizedConstraint> constraints_;
    std::unordered_map<VarId, Interval> intervals_;
    std::set<VarId> variables_;
    bool contradiction_ = false;

    bool update_intervals();
    bool check_difference_graph() const;
};

class ConstraintBuilder {
public:
    static bool build_constraint(
        std::shared_ptr<AST::Expression> expr,
        NormalizedConstraint& out_constraint);

    static bool extract_linear_term(
        std::shared_ptr<AST::Expression> expr,
        LinearTerm& out_term);

    static bool extract_expr_name(
        std::shared_ptr<AST::Expression> expr,
        std::string& out_name);
};

} // namespace Frontend
} // namespace LM

#endif // LIMITLY_CONSTRAINT_ENGINE_HH
