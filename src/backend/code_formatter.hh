#ifndef CODE_FORMATTER_HH
#define CODE_FORMATTER_HH

#include "../frontend/ast.hh"
#include <string>
#include <sstream>
#include <vector>

class CodeFormatter {
public:
    CodeFormatter();
    
    // Main formatting function
    std::string format(const std::shared_ptr<AST::Program>& program);
    std::string format(const std::shared_ptr<AST::Program>& program, const std::string& sourceText);
    
    // Configuration options
    void setIndentSize(int size) { indentSize = size; }
    void setUseSpaces(bool spaces) { useSpaces = spaces; }
    void setMaxLineLength(int length) { maxLineLength = length; }
    
private:
    // Formatting state
    int currentIndent = 0;
    int indentSize = 4;
    bool useSpaces = true;
    int maxLineLength = 100;
    std::ostringstream output;
    
    // Source text for fallback formatting
    std::string originalSource;
    std::vector<std::string> sourceLines;
    
    // Helper methods
    std::string getIndent() const;
    void increaseIndent();
    void decreaseIndent();
    void writeLine(const std::string& line = "");
    void write(const std::string& text);
    void writeIndented(const std::string& text);
    
    // Statement formatting
    void formatStatement(const std::shared_ptr<AST::Statement>& stmt);
    void formatVarDeclaration(const std::shared_ptr<AST::VarDeclaration>& stmt);
    void formatFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt);
    void formatClassDeclaration(const std::shared_ptr<AST::ClassDeclaration>& stmt);
    void formatBlockStatement(const std::shared_ptr<AST::BlockStatement>& stmt);
    void formatIfStatement(const std::shared_ptr<AST::IfStatement>& stmt);
    void formatForStatement(const std::shared_ptr<AST::ForStatement>& stmt);
    void formatWhileStatement(const std::shared_ptr<AST::WhileStatement>& stmt);
    void formatIterStatement(const std::shared_ptr<AST::IterStatement>& stmt);
    void formatReturnStatement(const std::shared_ptr<AST::ReturnStatement>& stmt);
    void formatPrintStatement(const std::shared_ptr<AST::PrintStatement>& stmt);
    void formatExprStatement(const std::shared_ptr<AST::ExprStatement>& stmt);
    void formatAttemptStatement(const std::shared_ptr<AST::AttemptStatement>& stmt);
    void formatParallelStatement(const std::shared_ptr<AST::ParallelStatement>& stmt);
    void formatConcurrentStatement(const std::shared_ptr<AST::ConcurrentStatement>& stmt);
    void formatMatchStatement(const std::shared_ptr<AST::MatchStatement>& stmt);
    void formatEnumDeclaration(const std::shared_ptr<AST::EnumDeclaration>& stmt);
    
    // Expression formatting
    std::string formatExpression(const std::shared_ptr<AST::Expression>& expr);
    std::string formatBinaryExpr(const std::shared_ptr<AST::BinaryExpr>& expr);
    std::string formatUnaryExpr(const std::shared_ptr<AST::UnaryExpr>& expr);
    std::string formatLiteralExpr(const std::shared_ptr<AST::LiteralExpr>& expr);
    std::string formatVariableExpr(const std::shared_ptr<AST::VariableExpr>& expr);
    std::string formatCallExpr(const std::shared_ptr<AST::CallExpr>& expr);
    std::string formatAssignExpr(const std::shared_ptr<AST::AssignExpr>& expr);
    std::string formatTernaryExpr(const std::shared_ptr<AST::TernaryExpr>& expr);
    std::string formatGroupingExpr(const std::shared_ptr<AST::GroupingExpr>& expr);
    std::string formatIndexExpr(const std::shared_ptr<AST::IndexExpr>& expr);
    std::string formatMemberExpr(const std::shared_ptr<AST::MemberExpr>& expr);
    std::string formatListExpr(const std::shared_ptr<AST::ListExpr>& expr);
    std::string formatDictExpr(const std::shared_ptr<AST::DictExpr>& expr);
    std::string formatRangeExpr(const std::shared_ptr<AST::RangeExpr>& expr);
    std::string formatAwaitExpr(const std::shared_ptr<AST::AwaitExpr>& expr);
    std::string formatInterpolatedStringExpr(const std::shared_ptr<AST::InterpolatedStringExpr>& expr);
    
    // Type formatting
    std::string formatTypeAnnotation(const std::shared_ptr<AST::TypeAnnotation>& type);
    
    // Utility methods
    std::string escapeString(const std::string& str);
    std::string tokenTypeToString(TokenType type);
    bool needsParentheses(const std::shared_ptr<AST::Expression>& expr, const std::shared_ptr<AST::Expression>& parent);
    int getOperatorPrecedence(const std::string& op);
    
    // Fallback formatting methods
    void outputUnformattedStatement(const std::shared_ptr<AST::Statement>& stmt, const std::string& reason);
    std::string getUnformattedExpression(const std::shared_ptr<AST::Expression>& expr, const std::string& reason);
    std::string getOriginalText(const std::shared_ptr<AST::Node>& node);
    std::string generateStatementPlaceholder(const std::shared_ptr<AST::Statement>& stmt);
    std::string generateExpressionPlaceholder(const std::shared_ptr<AST::Expression>& expr);
};

#endif // CODE_FORMATTER_HH