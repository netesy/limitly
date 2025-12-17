#include "ast_printer.hh"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace {
    std::string escapeString(const std::string& str) {
        std::ostringstream out;
        for (char c : str) {
            switch (c) {
                case '\n': out << "\\n"; break;
                case '\r': out << "\\r"; break;
                case '\t': out << "\\t"; break;
                case '\\': out << "\\\\"; break;
                case '"': out << "\\\""; break;
                default: out << c; break;
            }
        }
        return out.str();
    }
}

namespace {
    std::string typeToString(const std::shared_ptr<AST::TypeAnnotation>& type) {
        if (!type) return "<unknown>";
        
        std::string result = type->typeName;
        

        // Handle error union types
        if (type->isFallible) {
            result += "?";
            if (!type->errorTypes.empty()) {
                for (size_t i = 0; i < type->errorTypes.size(); ++i) {
                    if (i > 0) result += ", ";
                    result += type->errorTypes[i];
                }
            }
        } else if (type->isOptional) {
            result += "?";
        }
        
        // Handle list types
        if (type->isList && type->elementType) {
            result = "[" + typeToString(type->elementType) + "]";
        }
        
        // Handle function types
        if (type->isFunction) {
            result = "(";
            for (size_t i = 0; i < type->functionParams.size(); ++i) {
                if (i > 0) result += ", ";
                result += typeToString(type->functionParams[i]);
            }
            result += ") : ";
            if (type->returnType) {
                result += typeToString(type->returnType);
            } else {
                result += "nil";
            }
        }
        
        return result;
    }
}

void ASTPrinter::process(const std::shared_ptr<AST::Program>& program) {
    std::cout << "AST Dump:" << std::endl;
    std::cout << "==========" << std::endl;
    
    for (const auto& stmt : program->statements) {
        printNode(stmt);
    }
}

void ASTPrinter::printNode(const std::shared_ptr<AST::Node>& node, int indent) {
    std::string indentation = getIndentation(indent);
    
    if (!node) {
        std::cout << indentation << "(null)\n";
        return;
    }
    
    if (auto program = std::dynamic_pointer_cast<AST::Program>(node)) {
        std::cout << indentation << "Program:" << std::endl;
        for (const auto& stmt : program->statements) {
            printNode(stmt, indent + 1);
        }
    }
    else if (auto varDecl = std::dynamic_pointer_cast<AST::VarDeclaration>(node)) {
        std::cout << indentation << "VarDeclaration: ";
        
        // Show visibility modifiers
        auto getVisibilityString = [](AST::VisibilityLevel vis) -> std::string {
            switch (vis) {
                case AST::VisibilityLevel::Private: return "private";
                case AST::VisibilityLevel::Protected: return "prot";
                case AST::VisibilityLevel::Public: return "pub";
                case AST::VisibilityLevel::Const: return "const";
                default: return "unknown";
            }
        };
        
        std::cout << "[" << getVisibilityString(varDecl->visibility) << "] ";
        if (varDecl->isStatic) {
            std::cout << "[static] ";
        }
        
        std::cout << varDecl->name << std::endl;
        
        if (varDecl->type) {
            std::cout << indentation << "  Type: " << typeToString(*varDecl->type) << std::endl;
        }
        
        if (varDecl->initializer) {
            std::cout << indentation << "  Initializer:" << std::endl;
            printNode(varDecl->initializer, indent + 2);
        }
    }
    else if (auto destructDecl = std::dynamic_pointer_cast<AST::DestructuringDeclaration>(node)) {
        std::cout << indentation << "DestructuringDeclaration: (";
        for (size_t i = 0; i < destructDecl->names.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << destructDecl->names[i];
        }
        std::cout << ")" << std::endl;
        
        if (destructDecl->initializer) {
            std::cout << indentation << "  Initializer:" << std::endl;
            printNode(destructDecl->initializer, indent + 2);
        }
    }
    else if (auto funcDecl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(node)) {
        std::cout << indentation << "FunctionDeclaration: ";
        
        // Show visibility modifiers
        auto getVisibilityString = [](AST::VisibilityLevel vis) -> std::string {
            switch (vis) {
                case AST::VisibilityLevel::Private: return "private";
                case AST::VisibilityLevel::Protected: return "prot";
                case AST::VisibilityLevel::Public: return "pub";
                case AST::VisibilityLevel::Const: return "const";
                default: return "unknown";
            }
        };
        
        std::cout << "[" << getVisibilityString(funcDecl->visibility) << "] ";
        if (funcDecl->isStatic) {
            std::cout << "[static] ";
        }
        if (funcDecl->isAbstract) {
            std::cout << "[abstract] ";
        }
        if (funcDecl->isFinal) {
            std::cout << "[final] ";
        }
        
        std::cout << funcDecl->name << std::endl;
        
        if (!funcDecl->genericParams.empty()) {
            std::cout << indentation << "  GenericParams: <";
            for (size_t i = 0; i < funcDecl->genericParams.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << funcDecl->genericParams[i];
            }
            std::cout << ">" << std::endl;
        }
        
        if (!funcDecl->params.empty() || !funcDecl->optionalParams.empty()) {
            std::cout << indentation << "  Parameters:" << std::endl;
            
            // Required parameters
            for (const auto& [name, type] : funcDecl->params) {
                std::cout << indentation << "    " << name;
                if (type) {
                    std::cout << ": " << typeToString(type);
                }
                std::cout << std::endl;
            }
            
            // Optional parameters
            for (const auto& [name, param] : funcDecl->optionalParams) {
                std::cout << indentation << "    " << name << " (optional)";
                if (param.first) {
                    std::cout << ": " << typeToString(param.first);
                }
                std::cout << std::endl;
                
                if (param.second) {
                    std::cout << indentation << "      Default value:" << std::endl;
                    printNode(param.second, indent + 3);
                }
            }
        }
        
        if (funcDecl->returnType) {
            std::cout << indentation << "  ReturnType: " << typeToString(funcDecl->returnType.value()) << std::endl;
        }
        
        if (funcDecl->throws) {
            std::cout << indentation << "  Throws: true" << std::endl;
        }
        
        if (funcDecl->body) {
            std::cout << indentation << "  Body:" << std::endl;
            printNode(funcDecl->body, indent + 2);
        }
    }
    else if (auto classDecl = std::dynamic_pointer_cast<AST::ClassDeclaration>(node)) {
        std::cout << indentation << "ClassDeclaration: " << classDecl->name;
        
        // Show class modifiers
        if (classDecl->isAbstract) std::cout << " (abstract)";
        if (classDecl->isFinal) std::cout << " (final)";
        if (classDecl->isDataClass) std::cout << " (data)";
        
        // Show inheritance information
        if (!classDecl->superClassName.empty()) {
            std::cout << " : " << classDecl->superClassName;
            if (!classDecl->superConstructorArgs.empty()) {
                std::cout << "(";
                for (size_t i = 0; i < classDecl->superConstructorArgs.size(); ++i) {
                    if (i > 0) std::cout << ", ";
                    std::cout << "arg" << i; // Simplified - could print actual expressions
                }
                std::cout << ")";
            }
        }
        
        // Show inline constructor parameters
        if (classDecl->hasInlineConstructor && !classDecl->constructorParams.empty()) {
            std::cout << " (inline constructor: ";
            for (size_t i = 0; i < classDecl->constructorParams.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << classDecl->constructorParams[i].first;
            }
            std::cout << ")";
        }
        
        std::cout << std::endl;
        
        // Helper function to get visibility string
        auto getVisibilityString = [](AST::VisibilityLevel vis) -> std::string {
            switch (vis) {
                case AST::VisibilityLevel::Private: return "private";
                case AST::VisibilityLevel::Protected: return "prot";
                case AST::VisibilityLevel::Public: return "pub";
                case AST::VisibilityLevel::Const: return "const";
                default: return "unknown";
            }
        };
        
        if (!classDecl->fields.empty()) {
            std::cout << indentation << "  Fields:" << std::endl;
            for (const auto& field : classDecl->fields) {
                std::cout << indentation << "    ";
                
                // Show field visibility
                auto visIt = classDecl->fieldVisibility.find(field->name);
                if (visIt != classDecl->fieldVisibility.end()) {
                    std::cout << "[" << getVisibilityString(visIt->second) << "] ";
                }
                
                // Show static modifier
                if (classDecl->staticMembers.count(field->name)) {
                    std::cout << "[static] ";
                }
                
                // Show read-only modifier
                if (classDecl->readOnlyFields.count(field->name)) {
                    std::cout << "[readonly] ";
                }
                
                std::cout << std::endl;
                printNode(field, indent + 2);
            }
        }
        
        if (!classDecl->methods.empty()) {
            std::cout << indentation << "  Methods:" << std::endl;
            for (const auto& method : classDecl->methods) {
                std::cout << indentation << "    ";
                
                // Show method visibility
                auto visIt = classDecl->methodVisibility.find(method->name);
                if (visIt != classDecl->methodVisibility.end()) {
                    std::cout << "[" << getVisibilityString(visIt->second) << "] ";
                }
                
                // Show method modifiers
                if (classDecl->staticMembers.count(method->name)) {
                    std::cout << "[static] ";
                }
                if (classDecl->abstractMethods.count(method->name)) {
                    std::cout << "[abstract] ";
                }
                if (classDecl->finalMethods.count(method->name)) {
                    std::cout << "[final] ";
                }
                
                std::cout << std::endl;
                printNode(method, indent + 2);
            }
        }
    }
    else if (auto blockStmt = std::dynamic_pointer_cast<AST::BlockStatement>(node)) {
        std::cout << indentation << "BlockStatement:" << std::endl;
        for (const auto& stmt : blockStmt->statements) {
            printNode(stmt, indent + 1);
        }
    }
    else if (auto ifStmt = std::dynamic_pointer_cast<AST::IfStatement>(node)) {
        std::cout << indentation << "IfStatement:" << std::endl;
        
        std::cout << indentation << "  Condition:" << std::endl;
        printNode(ifStmt->condition, indent + 2);
        
        std::cout << indentation << "  Then:" << std::endl;
        printNode(ifStmt->thenBranch, indent + 2);
        
        if (ifStmt->elseBranch) {
            std::cout << indentation << "  Else:" << std::endl;
            printNode(ifStmt->elseBranch, indent + 2);
        }
    }
    else if (auto forStmt = std::dynamic_pointer_cast<AST::ForStatement>(node)) {
        std::cout << indentation << "ForStatement (traditional):" << std::endl;
        
        if (forStmt->initializer) {
            std::cout << indentation << "  Initializer:" << std::endl;
            printNode(forStmt->initializer, indent + 2);
        }
        
        if (forStmt->condition) {
            std::cout << indentation << "  Condition:" << std::endl;
            printNode(forStmt->condition, indent + 2);
        }
        
        if (forStmt->increment) {
            std::cout << indentation << "  Increment:" << std::endl;
            printNode(forStmt->increment, indent + 2);
        }
        
        if (forStmt->body) {
            std::cout << indentation << "  Body:" << std::endl;
            printNode(forStmt->body, indent + 2);
        }
    }
    else if (auto whileStmt = std::dynamic_pointer_cast<AST::WhileStatement>(node)) {
        std::cout << indentation << "WhileStatement:" << std::endl;
        
        std::cout << indentation << "  Condition:" << std::endl;
        printNode(whileStmt->condition, indent + 2);
        
        std::cout << indentation << "  Body:" << std::endl;
        printNode(whileStmt->body, indent + 2);
    }
    // Handle ReturnStatement and PrintStatement in their respective cases below
    else if (auto parallelStmt = std::dynamic_pointer_cast<AST::ParallelStatement>(node)) {
        std::cout << indentation << "ParallelStatement:" << std::endl;
        printNode(parallelStmt->body, indent + 1);
    }
    else if (auto concurrentStmt = std::dynamic_pointer_cast<AST::ConcurrentStatement>(node)) {
        std::cout << indentation << "ConcurrentStatement:" << std::endl;
        printNode(concurrentStmt->body, indent + 1);
    }
    else if (auto importStmt = std::dynamic_pointer_cast<AST::ImportStatement>(node)) {
        std::cout << indentation << "ImportStatement: " << importStmt->modulePath;
        if (importStmt->alias) {
            std::cout << " as " << *importStmt->alias;
        }
        if (importStmt->filter) {
            if (importStmt->filter->type == AST::ImportFilterType::Show) {
                std::cout << " show ";
            } else {
                std::cout << " hide ";
            }
            for (size_t i = 0; i < importStmt->filter->identifiers.size(); ++i) {
                std::cout << importStmt->filter->identifiers[i] << (i < importStmt->filter->identifiers.size() - 1 ? ", " : "");
            }
        }
        std::cout << std::endl;
    }
    else if (auto enumDecl = std::dynamic_pointer_cast<AST::EnumDeclaration>(node)) {
        std::cout << indentation << "EnumDeclaration: " << enumDecl->name << std::endl;
        for (const auto& variant : enumDecl->variants) {
            std::cout << indentation << "  Variant: " << variant.first;
            if (variant.second) {
                std::cout << " (type: " << typeToString(*variant.second) << ")";
            }
            std::cout << std::endl;
        }
    }
    else if (auto matchStmt = std::dynamic_pointer_cast<AST::MatchStatement>(node)) {
        std::cout << indentation << "MatchStatement:" << std::endl;
        std::cout << indentation << "  Value:" << std::endl;
        printNode(matchStmt->value, indent + 2);
        
        std::cout << indentation << "  Cases:" << std::endl;
        for (const auto& matchCase : matchStmt->cases) {
            std::cout << indentation << "    Case:" << std::endl;
            std::cout << indentation << "      Pattern:" << std::endl;
            printNode(matchCase.pattern, indent + 3);
            std::cout << indentation << "      Body:" << std::endl;
            printNode(matchCase.body, indent + 3);
        }
    }
    else if (auto typeDecl = std::dynamic_pointer_cast<AST::TypeDeclaration>(node)) {
        std::cout << indentation << "TypeDeclaration: " << typeDecl->name << " = " 
                  << typeToString(typeDecl->type) << std::endl;
    }
    else if (auto traitDecl = std::dynamic_pointer_cast<AST::TraitDeclaration>(node)) {
        std::cout << indentation << "TraitDeclaration: " << traitDecl->name;
        if (traitDecl->isOpen) std::cout << " (open)";
        std::cout << std::endl;
        
        if (!traitDecl->methods.empty()) {
            std::cout << indentation << "  Methods:" << std::endl;
            for (const auto& method : traitDecl->methods) {
                printNode(method, indent + 2);
            }
        }
    }
    else if (auto interfaceDecl = std::dynamic_pointer_cast<AST::InterfaceDeclaration>(node)) {
        std::cout << indentation << "InterfaceDeclaration: " << interfaceDecl->name;
        if (interfaceDecl->isOpen) std::cout << " (open)";
        std::cout << std::endl;
        
        if (!interfaceDecl->methods.empty()) {
            std::cout << indentation << "  Methods:" << std::endl;
            for (const auto& method : interfaceDecl->methods) {
                printNode(method, indent + 2);
            }
        }
    }
    else if (auto moduleDecl = std::dynamic_pointer_cast<AST::ModuleDeclaration>(node)) {
        std::cout << indentation << "ModuleDeclaration: " << moduleDecl->name << std::endl;
        
        if (!moduleDecl->publicMembers.empty()) {
            std::cout << indentation << "  Public Members:" << std::endl;
            for (const auto& member : moduleDecl->publicMembers) {
                printNode(member, indent + 2);
            }
        }
        
        if (!moduleDecl->protectedMembers.empty()) {
            std::cout << indentation << "  Protected Members:" << std::endl;
            for (const auto& member : moduleDecl->protectedMembers) {
                printNode(member, indent + 2);
            }
        }
        
        if (!moduleDecl->privateMembers.empty()) {
            std::cout << indentation << "  Private Members:" << std::endl;
            for (const auto& member : moduleDecl->privateMembers) {
                printNode(member, indent + 2);
            }
        }
    }
    else if (auto iterStmt = std::dynamic_pointer_cast<AST::IterStatement>(node)) {
        std::cout << indentation << "IterStatement:" << std::endl;
        std::cout << indentation << "  Variables:";
        for (const auto& var : iterStmt->loopVars) {
            std::cout << " " << var;
        }
        std::cout << std::endl;
        
        std::cout << indentation << "  Iterable:" << std::endl;
        printNode(iterStmt->iterable, indent + 2);
        
        std::cout << indentation << "  Body:" << std::endl;
        printNode(iterStmt->body, indent + 2);
    }
    else if (auto unsafeStmt = std::dynamic_pointer_cast<AST::UnsafeStatement>(node)) {
        std::cout << indentation << "UnsafeStatement:" << std::endl;
        printNode(unsafeStmt->body, indent + 1);
    }
    else if (auto contractStmt = std::dynamic_pointer_cast<AST::ContractStatement>(node)) {
        std::cout << indentation << "ContractStatement:" << std::endl;
        std::cout << indentation << "  Condition:" << std::endl;
        printNode(contractStmt->condition, indent + 2);
        
        if (contractStmt->message) {
            std::cout << indentation << "  Message:" << std::endl;
            printNode(contractStmt->message, indent + 2);
        }
    }
    else if (auto comptimeStmt = std::dynamic_pointer_cast<AST::ComptimeStatement>(node)) {
        std::cout << indentation << "ComptimeStatement:" << std::endl;
        if (comptimeStmt->declaration) {
            printNode(comptimeStmt->declaration, indent + 1);
        }
    }
    // Consolidated ReturnStatement case
    else if (auto returnStmt = std::dynamic_pointer_cast<AST::ReturnStatement>(node)) {
        std::cout << indentation << "ReturnStatement";
        if (returnStmt->value) {
            std::cout << ":" << std::endl << indentation << "  Value:" << std::endl;
            printNode(returnStmt->value, indent + 2);
        } else {
            std::cout << std::endl;
        }
    }
    // Consolidated PrintStatement case
    else if (auto printStmt = std::dynamic_pointer_cast<AST::PrintStatement>(node)) {
        std::cout << indentation << "PrintStatement:" << std::endl;
        for (const auto& arg : printStmt->arguments) {
            printNode(arg, indent + 1);
        }
    }
    else if (auto binaryExpr = std::dynamic_pointer_cast<AST::BinaryExpr>(node)) {
        std::cout << indentation << "BinaryExpression: " << tokenTypeToString(binaryExpr->op) << std::endl;
        
        std::cout << indentation << "  Left:" << std::endl;
        printNode(binaryExpr->left, indent + 2);
        
        std::cout << indentation << "  Operator: " << tokenTypeToString(binaryExpr->op) << std::endl;
        
        std::cout << indentation << "  Right:" << std::endl;
        printNode(binaryExpr->right, indent + 2);
    }
    else if (auto unaryExpr = std::dynamic_pointer_cast<AST::UnaryExpr>(node)) {
        std::cout << indentation << "UnaryExpression: " << tokenTypeToString(unaryExpr->op) << std::endl;
        
        std::cout << indentation << "  Operand:" << std::endl;
        printNode(unaryExpr->right, indent + 2);
    }
    else if (auto literalExpr = std::dynamic_pointer_cast<AST::LiteralExpr>(node)) {
        std::cout << indentation << "Literal: " << valueToString(literalExpr->value) << std::endl;
    }
    else if (auto interpolatedExpr = std::dynamic_pointer_cast<AST::InterpolatedStringExpr>(node)) {
        std::cout << indentation << "InterpolatedString:" << std::endl;
        for (size_t i = 0; i < interpolatedExpr->parts.size(); ++i) {
            if (std::holds_alternative<std::string>(interpolatedExpr->parts[i])) {
                std::cout << indentation << "  String: \"" << escapeString(std::get<std::string>(interpolatedExpr->parts[i])) << "\"" << std::endl;
            } else {
                std::cout << indentation << "  Expression:" << std::endl;
                printNode(std::get<std::shared_ptr<AST::Expression>>(interpolatedExpr->parts[i]), indent + 2);
            }
        }
    }
    else if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(node)) {
        std::cout << indentation << "Variable: " << varExpr->name << std::endl;
    }
    else if (auto callExpr = std::dynamic_pointer_cast<AST::CallExpr>(node)) {
        std::cout << indentation << "CallExpression:" << std::endl;
        
        std::cout << indentation << "  Callee:" << std::endl;
        printNode(callExpr->callee, indent + 2);
        
        if (!callExpr->arguments.empty()) {
            std::cout << indentation << "  Arguments:" << std::endl;
            for (const auto& arg : callExpr->arguments) {
                printNode(arg, indent + 2);
            }
        }
        
        if (!callExpr->namedArgs.empty()) {
            std::cout << indentation << "  Named Arguments:" << std::endl;
            for (const auto& [name, arg] : callExpr->namedArgs) {
                std::cout << indentation << "    " << name << ":" << std::endl;
                printNode(arg, indent + 3);
            }
        }
    }
    else if (auto exprStmt = std::dynamic_pointer_cast<AST::ExprStatement>(node)) {
        std::cout << indentation << "ExpressionStatement:" << std::endl;
        printNode(exprStmt->expression, indent + 1);
    }
    else if (auto thisExpr = std::dynamic_pointer_cast<AST::ThisExpr>(node)) {
        std::cout << indentation << "This" << std::endl;
    }
    else if (auto superExpr = std::dynamic_pointer_cast<AST::SuperExpr>(node)) {
        std::cout << indentation << "Super" << std::endl;
    }
    else if (auto assignExpr = std::dynamic_pointer_cast<AST::AssignExpr>(node)) {
        std::cout << indentation << "Assignment: " << tokenTypeToString(assignExpr->op) << std::endl;
        if (!assignExpr->name.empty()) {
            std::cout << indentation << "  Target: " << assignExpr->name << std::endl;
        } else if (assignExpr->member) {
            std::cout << indentation << "  Member: " << *assignExpr->member << std::endl;
            if (assignExpr->object) {
                std::cout << indentation << "  Object:" << std::endl;
                printNode(assignExpr->object, indent + 2);
            }
        } else if (assignExpr->index) {
            std::cout << indentation << "  Index:" << std::endl;
            printNode(assignExpr->index, indent + 1);
            if (assignExpr->object) {
                std::cout << indentation << "  Object:" << std::endl;
                printNode(assignExpr->object, indent + 2);
            }
        }
        std::cout << indentation << "  Value:" << std::endl;
        printNode(assignExpr->value, indent + 1);
    }
    else if (auto ternaryExpr = std::dynamic_pointer_cast<AST::TernaryExpr>(node)) {
        std::cout << indentation << "TernaryExpression:" << std::endl;
        std::cout << indentation << "  Condition:" << std::endl;
        printNode(ternaryExpr->condition, indent + 2);
        std::cout << indentation << "  Then:" << std::endl;
        printNode(ternaryExpr->thenBranch, indent + 2);
        std::cout << indentation << "  Else:" << std::endl;
        printNode(ternaryExpr->elseBranch, indent + 2);
    }
    else if (auto groupExpr = std::dynamic_pointer_cast<AST::GroupingExpr>(node)) {
        std::cout << indentation << "Grouping:" << std::endl;
        printNode(groupExpr->expression, indent + 1);
    }
    else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(node)) {
        std::cout << indentation << "IndexExpression:" << std::endl;
        std::cout << indentation << "  Object:" << std::endl;
        printNode(indexExpr->object, indent + 2);
        std::cout << indentation << "  Index:" << std::endl;
        printNode(indexExpr->index, indent + 2);
    }
    else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(node)) {
        std::cout << indentation << "MemberExpression: ." << memberExpr->name << std::endl;
        std::cout << indentation << "  Object:" << std::endl;
        printNode(memberExpr->object, indent + 2);
    }
    else if (auto listExpr = std::dynamic_pointer_cast<AST::ListExpr>(node)) {
        std::cout << indentation << "ListExpression: [" << listExpr->elements.size() << " elements]" << std::endl;
        for (const auto& element : listExpr->elements) {
            // Convert Expression to Node using static_pointer_cast since Expression inherits from Node
            printNode(std::static_pointer_cast<AST::Node>(element), indent + 1);
        }
    }
    else if (auto dictExpr = std::dynamic_pointer_cast<AST::DictExpr>(node)) {
        std::cout << indentation << "DictionaryExpression: {" << dictExpr->entries.size() << " entries}" << std::endl;
        for (const auto& [key, value] : dictExpr->entries) {
            std::cout << indentation << "  Key:" << std::endl;
            printNode(std::static_pointer_cast<AST::Node>(key), indent + 2);
            std::cout << indentation << "  Value:" << std::endl;
            printNode(std::static_pointer_cast<AST::Node>(value), indent + 2);
        }
    }
    else if (auto rangeExpr = std::dynamic_pointer_cast<AST::RangeExpr>(node)) {
        std::cout << indentation << "RangeExpression:" << std::endl;
        std::cout << indentation << "  Start:" << std::endl;
        printNode(rangeExpr->start, indent + 2);
        std::cout << indentation << "  End:" << std::endl;
        printNode(rangeExpr->end, indent + 2);
        if (rangeExpr->step) {
            std::cout << indentation << "  Step:" << std::endl;
            printNode(rangeExpr->step, indent + 2);
        }
        std::cout << indentation << "  Inclusive: " << (rangeExpr->inclusive ? "true" : "false") << std::endl;
    }
    else if (auto awaitExpr = std::dynamic_pointer_cast<AST::AwaitExpr>(node)) {
        std::cout << indentation << "AwaitExpression:" << std::endl;
        printNode(awaitExpr->expression, indent + 1);
    }
    else if (auto breakStmt = std::dynamic_pointer_cast<AST::BreakStatement>(node)) {
        std::cout << indentation << "BreakStatement" << std::endl;
    }
    else if (auto continueStmt = std::dynamic_pointer_cast<AST::ContinueStatement>(node)) {
        std::cout << indentation << "ContinueStatement" << std::endl;
    }
    else if (auto taskStmt = std::dynamic_pointer_cast<AST::TaskStatement>(node)) {
        std::cout << indentation << "TaskStatement";
        if (taskStmt->isAsync) std::cout << " (async)";
        std::cout << std::endl;
        
        if (!taskStmt->loopVar.empty()) {
            std::cout << indentation << "  LoopVar: " << taskStmt->loopVar << std::endl;
            if (taskStmt->iterable) {
                std::cout << indentation << "  Iterable:" << std::endl;
                printNode(taskStmt->iterable, indent + 2);
            }
        }
        
        if (taskStmt->body) {
            std::cout << indentation << "  Body:" << std::endl;
            printNode(taskStmt->body, indent + 2);
        }
    }
    else if (auto workerStmt = std::dynamic_pointer_cast<AST::WorkerStatement>(node)) {
        std::cout << indentation << "WorkerStatement";
        if (workerStmt->isAsync) std::cout << " (async)";
        std::cout << std::endl;
        
        if (!workerStmt->param.empty()) {
            std::cout << indentation << "  Parameter: " << workerStmt->param << std::endl;
        }
        
        if (workerStmt->body) {
            std::cout << indentation << "  Body:" << std::endl;
            printNode(workerStmt->body, indent + 2);
        }
    }
    else if (auto asyncFuncDecl = std::dynamic_pointer_cast<AST::AsyncFunctionDeclaration>(node)) {
        std::cout << indentation << "AsyncFunctionDeclaration: ";
        
        // Show visibility modifiers
        auto getVisibilityString = [](AST::VisibilityLevel vis) -> std::string {
            switch (vis) {
                case AST::VisibilityLevel::Private: return "private";
                case AST::VisibilityLevel::Protected: return "prot";
                case AST::VisibilityLevel::Public: return "pub";
                case AST::VisibilityLevel::Const: return "const";
                default: return "unknown";
            }
        };
        
        std::cout << "[" << getVisibilityString(asyncFuncDecl->visibility) << "] ";
        if (asyncFuncDecl->isStatic) {
            std::cout << "[static] ";
        }
        if (asyncFuncDecl->isAbstract) {
            std::cout << "[abstract] ";
        }
        if (asyncFuncDecl->isFinal) {
            std::cout << "[final] ";
        }
        
        std::cout << asyncFuncDecl->name << std::endl;
        
        if (!asyncFuncDecl->genericParams.empty()) {
            std::cout << indentation << "  GenericParams: <";
            for (size_t i = 0; i < asyncFuncDecl->genericParams.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << asyncFuncDecl->genericParams[i];
            }
            std::cout << ">" << std::endl;
        }
        
        if (!asyncFuncDecl->params.empty() || !asyncFuncDecl->optionalParams.empty()) {
            std::cout << indentation << "  Parameters:" << std::endl;
            
            // Required parameters
            for (const auto& [name, type] : asyncFuncDecl->params) {
                std::cout << indentation << "    " << name;
                if (type) {
                    std::cout << ": " << typeToString(type);
                }
                std::cout << std::endl;
            }
            
            // Optional parameters
            for (const auto& [name, param] : asyncFuncDecl->optionalParams) {
                std::cout << indentation << "    " << name << " (optional)";
                if (param.first) {
                    std::cout << ": " << typeToString(param.first);
                }
                std::cout << std::endl;
                
                if (param.second) {
                    std::cout << indentation << "      Default value:" << std::endl;
                    printNode(param.second, indent + 3);
                }
            }
        }
        
        if (asyncFuncDecl->returnType) {
            std::cout << indentation << "  ReturnType: " << typeToString(*asyncFuncDecl->returnType) << std::endl;
        }
        
        if (asyncFuncDecl->throws) {
            std::cout << indentation << "  Throws: true" << std::endl;
        }
        
        if (asyncFuncDecl->body) {
            std::cout << indentation << "  Body:" << std::endl;
            printNode(asyncFuncDecl->body, indent + 2);
        }
    }
    else if (auto typePatternExpr = std::dynamic_pointer_cast<AST::TypePatternExpr>(node)) {
        std::cout << indentation << "TypePattern: " << typeToString(typePatternExpr->type) << std::endl;
    }
    else if (auto bindingPatternExpr = std::dynamic_pointer_cast<AST::BindingPatternExpr>(node)) {
        std::cout << indentation << "BindingPattern: " << bindingPatternExpr->typeName;
        if (!bindingPatternExpr->variableName.empty()) {
            std::cout << "(" << bindingPatternExpr->variableName << ")";
        }
        std::cout << std::endl;
    }
    else if (auto listPatternExpr = std::dynamic_pointer_cast<AST::ListPatternExpr>(node)) {
        std::cout << indentation << "ListPattern: [" << listPatternExpr->elements.size() << " elements";
        if (listPatternExpr->restElement) {
            std::cout << ", ..." << *listPatternExpr->restElement;
        }
        std::cout << "]" << std::endl;
        
        for (const auto& element : listPatternExpr->elements) {
            printNode(element, indent + 1);
        }
    }
    else if (auto dictPatternExpr = std::dynamic_pointer_cast<AST::DictPatternExpr>(node)) {
        std::cout << indentation << "DictPattern: {" << dictPatternExpr->fields.size() << " fields";
        if (dictPatternExpr->hasRestElement) {
            std::cout << ", ...";
            if (dictPatternExpr->restBinding) {
                std::cout << *dictPatternExpr->restBinding;
            }
        }
        std::cout << "}" << std::endl;
        
        for (const auto& field : dictPatternExpr->fields) {
            std::cout << indentation << "  Field: " << field.key;
            if (field.binding && field.binding != field.key) {
                std::cout << " -> " << *field.binding;
            }
            std::cout << std::endl;
        }
    }
    else if (auto tuplePatternExpr = std::dynamic_pointer_cast<AST::TuplePatternExpr>(node)) {
        std::cout << indentation << "TuplePattern: (" << tuplePatternExpr->elements.size() << " elements)" << std::endl;
        
        for (const auto& element : tuplePatternExpr->elements) {
            printNode(element, indent + 1);
        }
    }
    else if (auto fallibleExpr = std::dynamic_pointer_cast<AST::FallibleExpr>(node)) {
        std::cout << indentation << "FallibleExpression:" << std::endl;
        std::cout << indentation << "  Expression:" << std::endl;
        printNode(fallibleExpr->expression, indent + 2);
        
        if (fallibleExpr->elseHandler) {
            std::cout << indentation << "  ElseHandler:" << std::endl;
            if (!fallibleExpr->elseVariable.empty()) {
                std::cout << indentation << "    ErrorVariable: " << fallibleExpr->elseVariable << std::endl;
            }
            printNode(fallibleExpr->elseHandler, indent + 2);
        }
    }
    else if (auto errorExpr = std::dynamic_pointer_cast<AST::ErrorConstructExpr>(node)) {
        std::cout << indentation << "ErrorConstruct: " << errorExpr->errorType << std::endl;
        
        if (!errorExpr->arguments.empty()) {
            std::cout << indentation << "  Arguments:" << std::endl;
            for (const auto& arg : errorExpr->arguments) {
                printNode(arg, indent + 2);
            }
        }
    }
    else if (auto okExpr = std::dynamic_pointer_cast<AST::OkConstructExpr>(node)) {
        std::cout << indentation << "OkConstruct:" << std::endl;
        std::cout << indentation << "  Value:" << std::endl;
        printNode(okExpr->value, indent + 2);
    }
    else if (auto lambdaExpr = std::dynamic_pointer_cast<AST::LambdaExpr>(node)) {
        std::cout << indentation << "LambdaExpression:" << std::endl;
        
        if (!lambdaExpr->params.empty()) {
            std::cout << indentation << "  Parameters:" << std::endl;
            for (const auto& [name, type] : lambdaExpr->params) {
                std::cout << indentation << "    " << name;
                if (type) {
                    std::cout << ": " << typeToString(type);
                }
                std::cout << std::endl;
            }
        }
        
        if (lambdaExpr->returnType) {
            std::cout << indentation << "  ReturnType: " << typeToString(*lambdaExpr->returnType) << std::endl;
        }
        
        if (lambdaExpr->body) {
            std::cout << indentation << "  Body:" << std::endl;
            printNode(lambdaExpr->body, indent + 2);
        }
        
        if (!lambdaExpr->capturedVars.empty()) {
            std::cout << indentation << "  CapturedVars:";
            for (const auto& var : lambdaExpr->capturedVars) {
                std::cout << " " << var;
            }
            std::cout << std::endl;
        }
    }
    else {
        std::cout << indentation << "Unknown node type" << std::endl;
    }
}

std::string ASTPrinter::getIndentation(int indent) const {
    return std::string(indent * 2, ' ');
}

std::string ASTPrinter::tokenTypeToString(TokenType type) const {
    switch (type) {
        // Delimiters
        case TokenType::LEFT_PAREN: return "(";
        case TokenType::RIGHT_PAREN: return ")";
        case TokenType::LEFT_BRACE: return "{";
        case TokenType::RIGHT_BRACE: return "}";
        case TokenType::LEFT_BRACKET: return "[";
        case TokenType::RIGHT_BRACKET: return "]";
        case TokenType::COMMA: return ",";
        case TokenType::DOT: return ".";
        case TokenType::SEMICOLON: return ";";
        case TokenType::QUESTION: return "?";
        case TokenType::ELVIS: return "?:";
        case TokenType::SAFE: return "?.";
        case TokenType::ARROW: return "->";
        case TokenType::RANGE: return "..";
        case TokenType::ELLIPSIS: return "...";
        case TokenType::AT_SIGN: return "@";
        
        // Operators
        case TokenType::PLUS: return "+";
        case TokenType::PLUS_EQUAL: return "+=";
        case TokenType::MINUS: return "-";
        case TokenType::MINUS_EQUAL: return "-=";
        case TokenType::SLASH: return "/";
        case TokenType::SLASH_EQUAL: return "/=";
        case TokenType::MODULUS: return "%";
        case TokenType::MODULUS_EQUAL: return "%=";
        case TokenType::STAR: return "*";
        case TokenType::STAR_EQUAL: return "*=";
        case TokenType::BANG: return "!";
        case TokenType::BANG_EQUAL: return "!=";
        case TokenType::EQUAL: return "=";
        case TokenType::EQUAL_EQUAL: return "==";
        case TokenType::GREATER: return ">";
        case TokenType::GREATER_EQUAL: return ">=";
        case TokenType::LESS: return "<";
        case TokenType::LESS_EQUAL: return "<=";
        case TokenType::AMPERSAND: return "&";
        case TokenType::PIPE: return "|";
        case TokenType::CARET: return "^";
        case TokenType::TILDE: return "~";
        case TokenType::POWER: return "**";
        
        // Literals
        case TokenType::IDENTIFIER: return "identifier";
        case TokenType::STRING: return "string";
        case TokenType::NUMBER: return "number";
        
        // Types
        case TokenType::INT_TYPE: return "int";
        case TokenType::INT8_TYPE: return "i8";
        case TokenType::INT16_TYPE: return "i16";
        case TokenType::INT32_TYPE: return "i32";
        case TokenType::INT64_TYPE: return "i64";
        case TokenType::UINT_TYPE: return "uint";
        case TokenType::UINT8_TYPE: return "u8";
        case TokenType::UINT16_TYPE: return "u16";
        case TokenType::UINT32_TYPE: return "u32";
        case TokenType::UINT64_TYPE: return "u64";
        case TokenType::FLOAT_TYPE: return "float";
        case TokenType::FLOAT32_TYPE: return "f32";
        case TokenType::FLOAT64_TYPE: return "f64";
        case TokenType::STR_TYPE: return "str";
        case TokenType::BOOL_TYPE: return "bool";
        case TokenType::USER_TYPE: return "user_type";
        case TokenType::FUNCTION_TYPE: return "fn";
        case TokenType::LIST_TYPE: return "list";
        case TokenType::DICT_TYPE: return "dict";
        case TokenType::ARRAY_TYPE: return "array";
        case TokenType::ENUM_TYPE: return "enum";
        case TokenType::SUM_TYPE: return "sum";
        case TokenType::UNION_TYPE: return "union";
        case TokenType::OPTION_TYPE: return "option";
        case TokenType::RESULT_TYPE: return "result";
        case TokenType::ANY_TYPE: return "any";
        case TokenType::NIL_TYPE: return "nil";
        case TokenType::CHANNEL_TYPE: return "channel";
        case TokenType::ATOMIC_TYPE: return "atomic";
        
        // Keywords
        case TokenType::AND: return "and";
        case TokenType::CLASS: return "class";
        case TokenType::FALSE: return "false";
        case TokenType::FN: return "fn";
        case TokenType::ELSE: return "else";
        case TokenType::FOR: return "for";
        case TokenType::WHILE: return "while";
        case TokenType::MATCH: return "match";
        case TokenType::IF: return "if";
        case TokenType::IN: return "in";
        case TokenType::ITER: return "iter";
        
        // Add more keywords as needed...
        
        default: return "<unknown>";
    }
}

std::string ASTPrinter::valueToString(const std::variant<std::string, bool, std::nullptr_t>& value) const {
    if (std::holds_alternative<std::string>(value)) {
        return "\"" + std::get<std::string>(value) + "\"";
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    } else if (std::holds_alternative<std::nullptr_t>(value)) {
        return "nil";
    }
    return "<unknown>";
}

std::string ASTPrinter::typeToString(const std::shared_ptr<AST::TypeAnnotation>& type) const {
    if (!type) return "<unknown>";
    
    std::string result = type->typeName;
    
    // Handle optional type
    if (type->isOptional) {
        result += "?";
    }
    
    // Handle list type
    if (type->isList && type->elementType) {
        return "[" + typeToString(type->elementType) + "]";
    }
    
    // Handle dictionary type
    if (type->isDict && type->keyType && type->valueType) {
        return "{" + typeToString(type->keyType) + ": " + typeToString(type->valueType) + "}";
    }
    
    // Handle function type
    if (type->isFunction) {
        result = "(";
        for (size_t i = 0; i < type->functionParams.size(); ++i) {
            if (i > 0) result += ", ";
            result += typeToString(type->functionParams[i]);
        }
        result += ") -> ";
        if (type->returnType) {
            result += typeToString(type->returnType);
        } else {
            result += "void";
        }
        return result;
    }
    
    // Handle union type
    if (type->isUnion && !type->unionTypes.empty()) {
        result = "";
        for (size_t i = 0; i < type->unionTypes.size(); ++i) {
            if (i > 0) result += " | ";
            result += typeToString(type->unionTypes[i]);
        }
        return result;
    }
    
    // Handle intersection type
    if (type->isIntersection) {
        // For structural types, show the fields
        if (type->isStructural && !type->structuralFields.empty()) {
            result = "{";
            for (size_t i = 0; i < type->structuralFields.size(); ++i) {
                if (i > 0) result += ", ";
                result += type->structuralFields[i].name + ": " + 
                         typeToString(type->structuralFields[i].type);
            }
            if (type->hasRest) {
                if (!type->structuralFields.empty()) result += ", ";
                result += "...";
            }
            result += "}";
            return result;
        }
        // For named intersection types
        else if (!type->baseRecords.empty()) {
            result = "";
            for (size_t i = 0; i < type->baseRecords.size(); ++i) {
                if (i > 0) result += " & ";
                result += type->baseRecords[i];
            }
            return result;
        }
    }
    
    // Handle refined types
    if (type->isRefined && type->refinementCondition) {
        // In a real implementation, we might want to print the refinement condition
        return result + " where <condition>";
    }
    
    return result;
}
