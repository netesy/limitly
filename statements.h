//statements.h
#include <iostream>
#include <variant>
#include <vector>

// Structure for variable declaration statement
struct VarDeclaration {
    std::string type;   // Type of the variable
    std::string name;   // Name of the variable
    // Optional: Expression for variable initialization
    // Additional fields as needed
};

// Structure for function declaration statement
struct FnDeclaration
{
    std::string returnType;                 // Return type of the function
    std::string name;                       // Name of the function
    std::vector<std::pair<std::string, std::string>> parameters; // Parameter list (name, type)
    // List of statements for the function body
    // Additional fields as needed
};

// Structure for return statement
struct ReturnStatement {
    // Expression to be returned
    // Additional fields as needed
};

// Structure for if statement
struct IfStatement {
    // Condition expression
    // List of statements for the 'if' block
    // List of statements for the 'else' block (optional)
    // Additional fields as needed
};

// Structure for for statement
struct ForStatement {
    // Optional: Initialization expression
    // Optional: Condition expression
    // Optional: Increment expression
    // List of statements for the loop body
    // Additional fields as needed
};

// Structure for while statement
struct WhileStatement {
    // Condition expression
    // List of statements for the loop body
    // Additional fields as needed
};

// Structure for print statement
struct PrintStatement {
    // Expression to be printed
    // Additional fields as needed
};

// Structure for expression statement
struct ExpressionStatement {
    // Expression
    // Additional fields as needed
};

// Define StatementResult
struct StatementResult {
    std::variant<VarDeclaration,
                 FnDeclaration,
                 ReturnStatement,
                 IfStatement,
                 ForStatement,
                 WhileStatement,
                 PrintStatement,
                 ExpressionStatement>
        result;

    // Constructor
    explicit StatementResult(std::variant<VarDeclaration,
                                          FnDeclaration,
                                          ReturnStatement,
                                          IfStatement,
                                          ForStatement,
                                          WhileStatement,
                                          PrintStatement,
                                          ExpressionStatement> res)
        : result(std::move(res))
    {}
};
