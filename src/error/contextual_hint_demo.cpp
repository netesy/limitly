#include "contextual_hint_provider.hh"
#include <iostream>
#include <vector>

using namespace ErrorHandling;

void demonstrateHintGeneration() {
    std::cout << "=== ContextualHintProvider Demo ===" << std::endl;
    
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    provider.initialize();
    
    // Demo scenarios
    struct DemoScenario {
        std::string errorMessage;
        ErrorContext context;
        std::string description;
    };
    
    std::vector<DemoScenario> scenarios = {
        {
            "Unterminated string",
            ErrorContext("example.lm", 5, 15, "let message = 'Hello world", "'", "", InterpretationStage::SCANNING),
            "Lexical Error: Unterminated String"
        },
        {
            "Unexpected closing brace",
            ErrorContext("example.lm", 12, 1, "fn test() { let x = 5; } }", "}", "", InterpretationStage::PARSING),
            "Syntax Error: Extra Closing Brace"
        },
        {
            "Variable not found",
            ErrorContext("example.lm", 8, 10, "let result = unknownVar + 5;", "unknownVar", "", InterpretationStage::SEMANTIC),
            "Semantic Error: Undefined Variable"
        },
        {
            "Division by zero",
            ErrorContext("example.lm", 15, 20, "let result = x / 0;", "0", "", InterpretationStage::INTERPRETING),
            "Runtime Error: Division by Zero"
        }
    };
    
    // Add block context to one scenario
    scenarios[1].context.blockContext = BlockContext("function", 10, 1, "fn test()");
    
    for (const auto& scenario : scenarios) {
        std::cout << "\n--- " << scenario.description << " ---" << std::endl;
        std::cout << "Error: " << scenario.errorMessage << std::endl;
        std::cout << "Location: " << scenario.context.filePath << ":" << scenario.context.line << ":" << scenario.context.column << std::endl;
        
        std::string hint = provider.generateHint(scenario.errorMessage, scenario.context);
        if (!hint.empty()) {
            std::cout << "Hint: " << hint << std::endl;
        }
        
        std::string suggestion = provider.generateSuggestion(scenario.errorMessage, scenario.context);
        if (!suggestion.empty()) {
            std::cout << "Suggestion: " << suggestion << std::endl;
        }
        
        std::string educationalHint = provider.generateEducationalHint(scenario.errorMessage, scenario.context);
        if (!educationalHint.empty()) {
            std::cout << "Educational: " << educationalHint << std::endl;
        }
        
        std::string commonCauses = provider.explainCommonCauses(scenario.errorMessage, scenario.context);
        if (!commonCauses.empty()) {
            std::cout << "Common Causes: " << commonCauses << std::endl;
        }
        
        std::string causedBy = provider.generateCausedByMessage(scenario.context);
        if (!causedBy.empty()) {
            std::cout << "Caused By: " << causedBy << std::endl;
        }
        
        if (provider.isBeginnerError(scenario.errorMessage, scenario.context)) {
            std::cout << "Note: This appears to be a common beginner error." << std::endl;
        }
    }
}

void demonstrateLanguageFeatures() {
    std::cout << "\n\n=== Language Feature Explanations ===" << std::endl;
    
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    
    std::vector<std::string> features = {
        "variables", "functions", "types", "modules", "error_handling", "strings", "iterators"
    };
    
    for (const std::string& feature : features) {
        std::string explanation = provider.getLanguageFeatureExplanation(feature);
        if (!explanation.empty()) {
            std::cout << "\n" << feature << ": " << explanation << std::endl;
        }
    }
}

void demonstrateCustomPatterns() {
    std::cout << "\n\n=== Custom Pattern Demo ===" << std::endl;
    
    ContextualHintProvider& provider = ContextualHintProvider::getInstance();
    
    // Add a custom pattern for a project-specific error
    bool success = provider.addCustomHintPattern(
        "Custom validation error",
        [](const ErrorContext& ctx) {
            return "This is a custom validation error. Check your input data at line " + 
                   std::to_string(ctx.line) + ".";
        }
    );
    
    if (success) {
        std::cout << "Custom pattern added successfully." << std::endl;
        
        ErrorContext context("custom.lm", 25, 8, "validate(data)", "data", "", InterpretationStage::SEMANTIC);
        std::string hint = provider.generateHint("Custom validation error", context);
        
        std::cout << "Custom hint: " << hint << std::endl;
    }
    
    // Clean up
    provider.clearCustomPatterns();
    std::cout << "Custom patterns cleared." << std::endl;
}

int main() {
    try {
        demonstrateHintGeneration();
        demonstrateLanguageFeatures();
        demonstrateCustomPatterns();
        
        std::cout << "\n=== Demo Complete ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Demo failed with exception: " << e.what() << std::endl;
        return 1;
    }
}