#include "../../src/source_code_formatter.hh"
#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace ErrorHandling;

// Test helper function to check if string contains expected content
bool contains(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}

// Test helper to print test results
void printTestResult(const std::string& testName, bool passed) {
    std::cout << "[" << (passed ? "PASS" : "FAIL") << "] " << testName << std::endl;
    if (!passed) {
        std::cout << "  Test failed!" << std::endl;
    }
}

void testSplitIntoLines() {
    std::cout << "\n=== Testing splitIntoLines ===" << std::endl;
    
    // Test basic line splitting
    {
        std::string code = "line1\nline2\nline3";
        auto lines = SourceCodeFormatter::splitIntoLines(code);
        bool passed = lines.size() == 3 && 
                     lines[0] == "line1" && 
                     lines[1] == "line2" && 
                     lines[2] == "line3";
        printTestResult("Basic line splitting", passed);
    }
    
    // Test empty string
    {
        std::string code = "";
        auto lines = SourceCodeFormatter::splitIntoLines(code);
        bool passed = lines.empty();
        printTestResult("Empty string", passed);
    }
    
    // Test single line
    {
        std::string code = "single line";
        auto lines = SourceCodeFormatter::splitIntoLines(code);
        bool passed = lines.size() == 1 && lines[0] == "single line";
        printTestResult("Single line", passed);
    }
    
    // Test with trailing newline
    {
        std::string code = "line1\nline2\n";
        auto lines = SourceCodeFormatter::splitIntoLines(code);
        bool passed = lines.size() == 2 && 
                     lines[0] == "line1" && 
                     lines[1] == "line2";
        printTestResult("Trailing newline", passed);
    }
}

void testExpandTabs() {
    std::cout << "\n=== Testing expandTabs ===" << std::endl;
    
    // Test basic tab expansion
    {
        std::string line = "hello\tworld";
        std::string expanded = SourceCodeFormatter::expandTabs(line, 4);
        bool passed = expanded == "hello   world"; // 3 spaces to reach next tab stop
        printTestResult("Basic tab expansion", passed);
    }
    
    // Test multiple tabs
    {
        std::string line = "a\tb\tc";
        std::string expanded = SourceCodeFormatter::expandTabs(line, 4);
        bool passed = expanded == "a   b   c"; // Each tab expands to 3 spaces
        printTestResult("Multiple tabs", passed);
    }
    
    // Test tab at beginning
    {
        std::string line = "\thello";
        std::string expanded = SourceCodeFormatter::expandTabs(line, 4);
        bool passed = expanded == "    hello"; // Tab at start expands to 4 spaces
        printTestResult("Tab at beginning", passed);
    }
    
    // Test no tabs
    {
        std::string line = "no tabs here";
        std::string expanded = SourceCodeFormatter::expandTabs(line, 4);
        bool passed = expanded == line;
        printTestResult("No tabs", passed);
    }
}

void testCalculateLineNumberWidth() {
    std::cout << "\n=== Testing calculateLineNumberWidth ===" << std::endl;
    
    // Test various line numbers
    {
        bool passed = SourceCodeFormatter::calculateLineNumberWidth(9) == 1 &&
                     SourceCodeFormatter::calculateLineNumberWidth(99) == 2 &&
                     SourceCodeFormatter::calculateLineNumberWidth(999) == 3 &&
                     SourceCodeFormatter::calculateLineNumberWidth(1000) == 4;
        printTestResult("Various line numbers", passed);
    }
    
    // Test edge cases
    {
        bool passed = SourceCodeFormatter::calculateLineNumberWidth(0) == 1 &&
                     SourceCodeFormatter::calculateLineNumberWidth(-1) == 1;
        printTestResult("Edge cases (0 and negative)", passed);
    }
}

void testGetDisplayWidth() {
    std::cout << "\n=== Testing getDisplayWidth ===" << std::endl;
    
    // Test basic text
    {
        std::string text = "hello";
        int width = SourceCodeFormatter::getDisplayWidth(text, 4);
        bool passed = width == 5;
        printTestResult("Basic text", passed);
    }
    
    // Test with tabs
    {
        std::string text = "a\tb"; // 'a' + tab + 'b'
        int width = SourceCodeFormatter::getDisplayWidth(text, 4);
        bool passed = width == 5; // 1 + 3 (to next tab stop) + 1
        printTestResult("Text with tabs", passed);
    }
    
    // Test empty string
    {
        std::string text = "";
        int width = SourceCodeFormatter::getDisplayWidth(text, 4);
        bool passed = width == 0;
        printTestResult("Empty string", passed);
    }
}

void testFormatLineNumber() {
    std::cout << "\n=== Testing formatLineNumber ===" << std::endl;
    
    SourceCodeFormatter::FormatOptions options;
    options.useColors = false; // Disable colors for easier testing
    options.useUnicode = false; // Use ASCII characters
    
    // Test normal line
    {
        std::string formatted = SourceCodeFormatter::formatLineNumber(42, 3, false, options);
        bool passed = contains(formatted, "42") && contains(formatted, "|");
        printTestResult("Normal line formatting", passed);
    }
    
    // Test error line
    {
        std::string formatted = SourceCodeFormatter::formatLineNumber(42, 3, true, options);
        bool passed = contains(formatted, "42") && contains(formatted, ">");
        printTestResult("Error line formatting", passed);
    }
    
    // Test with line numbers disabled
    {
        SourceCodeFormatter::FormatOptions noLineNumbers = options;
        noLineNumbers.showLineNumbers = false;
        std::string formatted = SourceCodeFormatter::formatLineNumber(42, 3, false, noLineNumbers);
        bool passed = formatted.empty();
        printTestResult("Line numbers disabled", passed);
    }
}

void testCreateCaretLine() {
    std::cout << "\n=== Testing createCaretLine ===" << std::endl;
    
    SourceCodeFormatter::FormatOptions options;
    options.useColors = false;
    options.useUnicode = false;
    
    // Test caret at column 1
    {
        std::string caret = SourceCodeFormatter::createCaretLine(1, 2, options);
        bool passed = contains(caret, "^") && !contains(caret, "  ^"); // No leading spaces
        printTestResult("Caret at column 1", passed);
    }
    
    // Test caret at column 5
    {
        std::string caret = SourceCodeFormatter::createCaretLine(5, 2, options);
        bool passed = contains(caret, "    ^"); // 4 spaces + caret
        printTestResult("Caret at column 5", passed);
    }
}

void testCreateUnderline() {
    std::cout << "\n=== Testing createUnderline ===" << std::endl;
    
    SourceCodeFormatter::FormatOptions options;
    options.useColors = false;
    options.useUnicode = false;
    
    // Test single character underline
    {
        std::string underline = SourceCodeFormatter::createUnderline(3, 3, 2, options);
        bool passed = contains(underline, "  ~"); // 2 spaces + single tilde
        printTestResult("Single character underline", passed);
    }
    
    // Test multi-character underline
    {
        std::string underline = SourceCodeFormatter::createUnderline(3, 6, 2, options);
        bool passed = contains(underline, "  ~~~~"); // 2 spaces + 4 tildes
        printTestResult("Multi-character underline", passed);
    }
}

void testFormatSourceContext() {
    std::cout << "\n=== Testing formatSourceContext ===" << std::endl;
    
    std::string sourceCode = "line 1\nline 2 with error\nline 3\nline 4";
    SourceCodeFormatter::FormatOptions options;
    options.useColors = false;
    options.useUnicode = false;
    options.contextLinesBefore = 1;
    options.contextLinesAfter = 1;
    
    // Test basic context formatting
    {
        auto context = SourceCodeFormatter::formatSourceContext(sourceCode, 2, 8, options);
        bool passed = context.size() >= 4 && // At least 4 lines (before, error, caret, after)
                     contains(context[0], "line 1") &&
                     contains(context[1], "line 2 with error") &&
                     contains(context[2], "^") && // Caret line
                     contains(context[3], "line 3");
        printTestResult("Basic context formatting", passed);
    }
    
    // Test error at first line
    {
        auto context = SourceCodeFormatter::formatSourceContext(sourceCode, 1, 3, options);
        bool passed = !context.empty() && contains(context[0], "line 1");
        printTestResult("Error at first line", passed);
    }
    
    // Test error at last line
    {
        auto context = SourceCodeFormatter::formatSourceContext(sourceCode, 4, 3, options);
        bool passed = !context.empty() && contains(context[0], "line 3") &&
                     contains(context[1], "line 4");
        printTestResult("Error at last line", passed);
    }
    
    // Test invalid line number
    {
        auto context = SourceCodeFormatter::formatSourceContext(sourceCode, 10, 3, options);
        bool passed = context.empty();
        printTestResult("Invalid line number", passed);
    }
}

void testFormatTokenContext() {
    std::cout << "\n=== Testing formatTokenContext ===" << std::endl;
    
    std::string sourceCode = "let x = 42;\nlet y = hello;\nprint(y);";
    SourceCodeFormatter::FormatOptions options;
    options.useColors = false;
    options.useUnicode = false;
    options.contextLinesBefore = 1;
    options.contextLinesAfter = 1;
    
    // Test token highlighting
    {
        auto context = SourceCodeFormatter::formatTokenContext(sourceCode, 2, 9, 5, options); // "hello" token
        bool passed = !context.empty() && 
                     std::any_of(context.begin(), context.end(), 
                                [](const std::string& line) { return contains(line, "let y = hello"); });
        printTestResult("Token highlighting", passed);
    }
    
    // Test single character token
    {
        auto context = SourceCodeFormatter::formatTokenContext(sourceCode, 1, 5, 1, options); // "x" token
        bool passed = !context.empty();
        printTestResult("Single character token", passed);
    }
}

void testFormatRangeContext() {
    std::cout << "\n=== Testing formatRangeContext ===" << std::endl;
    
    std::string sourceCode = "function test() {\n    return 42;\n}";
    SourceCodeFormatter::FormatOptions options;
    options.useColors = false;
    options.useUnicode = false;
    options.contextLinesBefore = 1;
    options.contextLinesAfter = 1;
    
    // Test range highlighting
    {
        auto context = SourceCodeFormatter::formatRangeContext(sourceCode, 1, 1, 8, options); // "function" range
        bool passed = !context.empty() && 
                     std::any_of(context.begin(), context.end(), 
                                [](const std::string& line) { return contains(line, "function test()"); });
        printTestResult("Range highlighting", passed);
    }
    
    // Test invalid range
    {
        auto context = SourceCodeFormatter::formatRangeContext(sourceCode, 1, 10, 5, options); // end < start
        bool passed = !context.empty(); // Should still work, just not highlight
        printTestResult("Invalid range (end < start)", passed);
    }
}

void testWriteFormattedContext() {
    std::cout << "\n=== Testing writeFormattedContext ===" << std::endl;
    
    std::vector<std::string> contextLines = {
        " 1 | line one",
        " 2 > line two with error",
        "   |     ^",
        " 3 | line three"
    };
    
    std::ostringstream oss;
    SourceCodeFormatter::FormatOptions options;
    SourceCodeFormatter::writeFormattedContext(oss, contextLines, options);
    
    std::string output = oss.str();
    bool passed = contains(output, "line one") && 
                 contains(output, "line two with error") &&
                 contains(output, "^") &&
                 contains(output, "line three");
    printTestResult("Write formatted context", passed);
}

void testEdgeCases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    // Test empty source code
    {
        auto context = SourceCodeFormatter::formatSourceContext("", 1, 1);
        bool passed = context.empty();
        printTestResult("Empty source code", passed);
    }
    
    // Test single character source
    {
        auto context = SourceCodeFormatter::formatSourceContext("x", 1, 1);
        bool passed = !context.empty();
        printTestResult("Single character source", passed);
    }
    
    // Test very long line
    {
        std::string longLine(1000, 'x');
        auto context = SourceCodeFormatter::formatSourceContext(longLine, 1, 500);
        bool passed = !context.empty();
        printTestResult("Very long line", passed);
    }
    
    // Test column beyond line length
    {
        auto context = SourceCodeFormatter::formatSourceContext("short", 1, 100);
        bool passed = !context.empty();
        printTestResult("Column beyond line length", passed);
    }
}

void testUnicodeAndColors() {
    std::cout << "\n=== Testing Unicode and Colors ===" << std::endl;
    
    SourceCodeFormatter::FormatOptions unicodeOptions;
    unicodeOptions.useUnicode = true;
    unicodeOptions.useColors = true;
    
    // Test Unicode characters
    {
        std::string caret = SourceCodeFormatter::createCaretLine(1, 2, unicodeOptions);
        bool passed = !caret.empty(); // Just check it doesn't crash
        printTestResult("Unicode characters", passed);
    }
    
    // Test color formatting
    {
        std::string sourceCode = "let x = 42;";
        auto context = SourceCodeFormatter::formatSourceContext(sourceCode, 1, 5, unicodeOptions);
        bool passed = !context.empty(); // Just check it doesn't crash
        printTestResult("Color formatting", passed);
    }
    
    // Test ASCII fallback
    {
        SourceCodeFormatter::FormatOptions asciiOptions;
        asciiOptions.useUnicode = false;
        asciiOptions.useColors = false;
        
        std::string caret = SourceCodeFormatter::createCaretLine(1, 2, asciiOptions);
        bool passed = contains(caret, "^") && contains(caret, "|");
        printTestResult("ASCII fallback", passed);
    }
}

int main() {
    std::cout << "Running SourceCodeFormatter Unit Tests" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    testSplitIntoLines();
    testExpandTabs();
    testCalculateLineNumberWidth();
    testGetDisplayWidth();
    testFormatLineNumber();
    testCreateCaretLine();
    testCreateUnderline();
    testFormatSourceContext();
    testFormatTokenContext();
    testFormatRangeContext();
    testWriteFormattedContext();
    testEdgeCases();
    testUnicodeAndColors();
    
    std::cout << "\n=======================================" << std::endl;
    std::cout << "SourceCodeFormatter tests completed!" << std::endl;
    
    return 0;
}