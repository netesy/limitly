#ifndef STREAM_FUSION_HH
#define STREAM_FUSION_HH

#include "../ast.hh"
#include <memory>

namespace LM {
namespace Frontend {
namespace AST {

class StreamFusionVisitor {
public:
    StreamFusionVisitor() = default;
    ~StreamFusionVisitor() = default;

    // Main entry point: optimizes all stream pipeline chains in the program.
    static std::shared_ptr<Program> optimizeProgram(std::shared_ptr<Program> program);

    std::shared_ptr<Statement> visitStatement(std::shared_ptr<Statement> stmt);
    std::shared_ptr<Expression> visitExpression(std::shared_ptr<Expression> expr);

private:
    uint64_t stream_id_counter = 0;

    std::shared_ptr<Expression> tryFusePipeline(std::shared_ptr<CallExpr> terminal_call);
};

} // namespace AST
} // namespace Frontend
} // namespace LM

#endif // STREAM_FUSION_HH
