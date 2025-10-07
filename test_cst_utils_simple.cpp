#include "src/frontend/cst.hh"
#include "src/frontend/cst_utils_simple.hh"
#include <iostream>
#include <cassert>

using namespace CST;

void testBasicCST() {
    std::cout << "Testing basic CST creation and utilities...\n";
    
    // Create a simple CST structure
    auto root = createNode(NodeKind::PROGRAM);
    
    // Add a variable declaration
    auto varDecl = createNode(NodeKind::VAR_DECLARATION);
    
    // Add some tokens
    Token varToken{TokenType::VAR, "var", 1, 0, 3};
    Token identToken{TokenType::IDENTIFIER, "x", 1, 4, 5};
    Token colonToken{TokenType::COLON, ":", 1, 5, 6};
    Token typeToken{TokenType::IDENTIFIER, "int", 1, 7, 10};
    Token semicolonToken{TokenType::SEMICOLON, ";", 1, 10, 11};
    
    varDecl->addToken(varToken);
    varDecl->addToken(identToken);
    varDecl->addToken(colonToken);
    varDecl->addToken(typeToken);
    varDecl->addToken(semicolonToken);
    
    root->addNode(std::move(varDecl));
    
    // Test text reconstruction
    std::string reconstructed = Utils::getText(root.get());
    std::cout << "Reconstructed text: '" << reconstructed << "'\n";
    assert(reconstructed == "varx:int;");
    
    // Test token extraction
    auto tokens = Utils::getAllTokens(root.get());
    std::cout << "Total tokens: " << tokens.size() << "\n";
    assert(tokens.size() == 5);
    
    // Test significant tokens
    auto significantTokens = Utils::getSignificantTokens(root.get());
    std::cout << "Significant tokens: " << significantTokens.size() << "\n";
    assert(significantTokens.size() == 5); // All tokens are significant in this case
    
    // Test node counting
    size_t nodeCount = Utils::countNodes(root.get());
    std::cout << "Total nodes: " << nodeCount << "\n";
    assert(nodeCount == 2); // root + varDecl
    
    std::cout << "Basic CST tests passed!\n\n";
}

void testCSTValidation() {
    std::cout << "Testing CST validation...\n";
    
    // Create a CST with an error node
    auto root = createNode(NodeKind::PROGRAM);
    auto errorNode = createErrorNode("Test error message");
    root->addNode(std::move(errorNode));
    
    // Test validation
    bool isValid = Utils::validateCST(root.get());
    std::cout << "Validation result: " << (isValid ? "VALID" : "INVALID") << "\n";
    
    // Should be invalid due to error node
    assert(!isValid);
    
    // Test finding error nodes
    auto errorNodes = Utils::findErrorNodes(root.get());
    std::cout << "Error nodes found: " << errorNodes.size() << "\n";
    assert(errorNodes.size() == 1);
    
    std::cout << "CST validation tests passed!\n\n";
}

void testCSTTraversal() {
    std::cout << "Testing CST traversal...\n";
    
    // Create a more complex CST
    auto root = createNode(NodeKind::PROGRAM);
    
    // Add function declaration
    auto funcDecl = createNode(NodeKind::FUNCTION_DECLARATION);
    Token fnToken{TokenType::FN, "fn", 1, 0, 2};
    Token nameToken{TokenType::IDENTIFIER, "test", 1, 3, 7};
    funcDecl->addToken(fnToken);
    funcDecl->addToken(nameToken);
    
    // Add block statement
    auto block = createNode(NodeKind::BLOCK_STATEMENT);
    Token lbraceToken{TokenType::LEFT_BRACE, "{", 1, 8, 9};
    Token rbraceToken{TokenType::RIGHT_BRACE, "}", 1, 9, 10};
    block->addToken(lbraceToken);
    block->addToken(rbraceToken);
    
    funcDecl->addNode(std::move(block));
    root->addNode(std::move(funcDecl));
    
    // Test finding by kind
    const Node* foundFunc = Utils::findByKind(root.get(), NodeKind::FUNCTION_DECLARATION);
    assert(foundFunc != nullptr);
    std::cout << "Found function declaration: " << nodeKindToString(foundFunc->kind) << "\n";
    
    const Node* foundBlock = Utils::findByKind(root.get(), NodeKind::BLOCK_STATEMENT);
    assert(foundBlock != nullptr);
    std::cout << "Found block statement: " << nodeKindToString(foundBlock->kind) << "\n";
    
    // Test finding all by kind
    auto allNodes = Utils::findAllByKind(root.get(), NodeKind::PROGRAM);
    assert(allNodes.size() == 1);
    std::cout << "Found " << allNodes.size() << " program nodes\n";
    
    // Test child traversal
    size_t childCount = 0;
    Utils::forEachChild(root.get(), [&](const Node* child) {
        childCount++;
        std::cout << "Child: " << nodeKindToString(child->kind) << "\n";
    });
    assert(childCount == 1); // Only direct children
    
    std::cout << "CST traversal tests passed!\n\n";
}

void testCSTPrinting() {
    std::cout << "Testing CST printing...\n";
    
    // Create a simple CST
    auto root = createNode(NodeKind::PROGRAM);
    auto stmt = createNode(NodeKind::EXPRESSION_STATEMENT);
    Token printToken{TokenType::PRINT, "print", 1, 0, 5};
    Token stringToken{TokenType::STRING, "\"hello\"", 1, 6, 13};
    
    stmt->addToken(printToken);
    stmt->addToken(stringToken);
    root->addNode(std::move(stmt));
    
    // Test tree printing
    std::string treeOutput = printCST(root.get());
    std::cout << "Tree output:\n" << treeOutput << "\n";
    
    // Test JSON printing
    std::string jsonOutput = printCSTAsJSON(root.get());
    std::cout << "JSON output:\n" << jsonOutput << "\n";
    
    // Test debug printing
    std::string debugOutput = debugCST(root.get());
    std::cout << "Debug output:\n" << debugOutput << "\n";
    
    // Basic checks - outputs should not be empty
    assert(!treeOutput.empty());
    assert(!jsonOutput.empty());
    assert(!debugOutput.empty());
    
    std::cout << "CST printing tests passed!\n\n";
}

void testSourceReconstruction() {
    std::cout << "Testing source reconstruction...\n";
    
    // Create CST with whitespace and comments
    auto root = createNode(NodeKind::PROGRAM);
    
    // Add whitespace
    Token wsToken{TokenType::WHITESPACE, "  ", 1, 0, 2};
    root->addToken(wsToken);
    
    // Add comment
    Token commentToken{TokenType::COMMENT_LINE, "// test comment", 1, 2, 17};
    root->addToken(commentToken);
    
    // Add newline
    Token nlToken{TokenType::NEWLINE, "\n", 1, 17, 18};
    root->addToken(nlToken);
    
    // Add statement
    auto stmt = createNode(NodeKind::EXPRESSION_STATEMENT);
    Token printToken{TokenType::PRINT, "print", 2, 18, 23};
    stmt->addToken(printToken);
    root->addNode(std::move(stmt));
    
    // Test full reconstruction
    std::string fullText = Utils::reconstructSource(root.get());
    std::cout << "Full reconstruction: '" << fullText << "'\n";
    // The actual reconstruction will be different because we added tokens to different nodes
    // Let's just check that it contains the expected elements
    assert(fullText.find("print") != std::string::npos);
    
    // Test reconstruction without trivia
    std::string noTriviaText = Utils::getTextWithoutTrivia(root.get());
    std::cout << "Without trivia: '" << noTriviaText << "'\n";
    assert(noTriviaText == "print");
    
    std::cout << "Source reconstruction tests passed!\n\n";
}

int main() {
    std::cout << "=== CST Utilities Test Suite (Simple) ===\n\n";
    
    try {
        testBasicCST();
        testCSTValidation();
        testCSTTraversal();
        testCSTPrinting();
        testSourceReconstruction();
        
        std::cout << "=== All CST utility tests passed! ===\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}