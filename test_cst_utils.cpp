#include "src/frontend/cst.hh"
#include "src/frontend/cst_utils.hh"
#include "src/frontend/cst_printer.hh"
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
    std::string reconstructed = TextUtils::getText(root.get());
    std::cout << "Reconstructed text: '" << reconstructed << "'\n";
    assert(reconstructed == "varx:int;");
    
    // Test token extraction
    auto tokens = TokenUtils::getTokens(root.get());
    std::cout << "Total tokens: " << tokens.size() << "\n";
    assert(tokens.size() == 5);
    
    // Test tree traversal
    size_t nodeCount = 0;
    Traversal::forEachDescendant(root.get(), [&](const Node* node) {
        nodeCount++;
    });
    std::cout << "Total nodes (including root): " << nodeCount << "\n";
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
    auto validationResult = Validation::validateCST(root.get());
    std::cout << "Validation result: " << (validationResult.isValid ? "VALID" : "INVALID") << "\n";
    std::cout << "Error count: " << validationResult.errors.size() << "\n";
    std::cout << "Warning count: " << validationResult.warnings.size() << "\n";
    
    // Should have errors due to error node
    assert(!validationResult.isValid);
    
    std::cout << "CST validation tests passed!\n\n";
}

void testCSTAnalysis() {
    std::cout << "Testing CST analysis...\n";
    
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
    
    // Test analysis
    auto stats = Analysis::analyzeTree(root.get());
    std::cout << "Total nodes: " << stats.totalNodes << "\n";
    std::cout << "Total tokens: " << stats.totalTokens << "\n";
    std::cout << "Max depth: " << stats.maxDepth << "\n";
    
    assert(stats.totalNodes == 3); // root + funcDecl + block
    assert(stats.totalTokens == 4); // fn, test, {, }
    assert(stats.maxDepth == 2);    // root -> funcDecl -> block
    
    std::cout << "CST analysis tests passed!\n\n";
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
    std::string treeOutput = printCSTAsTree(root.get());
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
    std::string fullText = TextUtils::reconstructSource(root.get());
    std::cout << "Full reconstruction: '" << fullText << "'\n";
    assert(fullText == "  // test comment\nprint");
    
    // Test reconstruction without comments
    TextUtils::ReconstructionOptions noComments;
    noComments.preserveComments = false;
    std::string noCommentsText = TextUtils::reconstructSource(root.get(), noComments);
    std::cout << "Without comments: '" << noCommentsText << "'\n";
    assert(noCommentsText == "  \nprint");
    
    // Test reconstruction without whitespace
    TextUtils::ReconstructionOptions noWhitespace;
    noWhitespace.preserveWhitespace = false;
    std::string noWhitespaceText = TextUtils::reconstructSource(root.get(), noWhitespace);
    std::cout << "Without whitespace: '" << noWhitespaceText << "'\n";
    assert(noWhitespaceText == "// test comment\nprint");
    
    std::cout << "Source reconstruction tests passed!\n\n";
}

int main() {
    std::cout << "=== CST Utilities Test Suite ===\n\n";
    
    try {
        testBasicCST();
        testCSTValidation();
        testCSTAnalysis();
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