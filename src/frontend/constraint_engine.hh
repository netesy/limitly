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
#include <algorithm>

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

    static Interval multiply(const Interval& a, const Interval& b) {
        if (a.is_empty() || b.is_empty()) return {1, 0};
        int64_t inf = std::numeric_limits<int64_t>::max() / 2;
        int64_t ninf = std::numeric_limits<int64_t>::min() / 2;

        auto safe_mul_val = [&](int64_t x, int64_t y) -> int64_t {
            if (x == 0 || y == 0) return 0;
            if (x >= inf || y >= inf || x <= ninf || y <= ninf)
                return ((x > 0) == (y > 0)) ? inf : ninf;
            return x * y;
        };

        int64_t p1 = safe_mul_val(a.min_val, b.min_val);
        int64_t p2 = safe_mul_val(a.min_val, b.max_val);
        int64_t p3 = safe_mul_val(a.max_val, b.min_val);
        int64_t p4 = safe_mul_val(a.max_val, b.max_val);

        Interval res;
        res.min_val = std::min({p1, p2, p3, p4});
        res.max_val = std::max({p1, p2, p3, p4});
        return res;
    }

    static Interval square(const Interval& a) {
        if (a.is_empty()) return {1, 0};
        Interval res;
        if (a.min_val >= 0) {
            res.min_val = a.min_val * a.min_val;
            res.max_val = a.max_val * a.max_val;
        } else if (a.max_val <= 0) {
            res.min_val = a.max_val * a.max_val;
            res.max_val = a.min_val * a.min_val;
        } else {
            res.min_val = 0;
            res.max_val = std::max(a.min_val * a.min_val, a.max_val * a.max_val);
        }
        return res;
    }
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
