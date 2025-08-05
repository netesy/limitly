#ifndef CLASSES_HH
#define CLASSES_HH

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include "../frontend/ast.hh"
#include "value.hh"
#include "functions.hh"

namespace backend {

// Forward declarations
class ClassRegistry;
class ObjectInstance;
class ClassDefinition;

// Class field definition
struct ClassField {
    std::string name;
    std::shared_ptr<AST::TypeAnnotation> type;
    std::shared_ptr<AST::Expression> defaultValue;
    bool isPrivate = false;
    bool isProtected = false;
    bool isStatic = false;
    
    ClassField(const std::string& n, std::shared_ptr<AST::TypeAnnotation> t,
               std::shared_ptr<AST::Expression> def = nullptr)
        : name(n), type(t), defaultValue(def) {}
};

// Class method definition
struct ClassMethod {
    std::string name;
    std::shared_ptr<FunctionImplementation> implementation;
    bool isPrivate = false;
    bool isProtected = false;
    bool isStatic = false;
    bool isVirtual = false;
    bool isAbstract = false;
    
    ClassMethod(const std::string& n, std::shared_ptr<FunctionImplementation> impl)
        : name(n), implementation(impl) {}
};

// Class definition containing fields and methods
class ClassDefinition : public std::enable_shared_from_this<ClassDefinition> {
private:
    std::string name;
    std::vector<ClassField> fields;
    std::vector<ClassMethod> methods;
    std::unordered_map<std::string, size_t> fieldIndex;
    std::unordered_map<std::string, size_t> methodIndex;
    std::shared_ptr<ClassDefinition> superClass;
    std::vector<std::string> interfaces;
    
public:
    ClassDefinition(const std::string& className);
    ClassDefinition(const std::shared_ptr<AST::ClassDeclaration>& decl);
    
    // Basic accessors
    const std::string& getName() const { return name; }
    const std::vector<ClassField>& getFields() const { return fields; }
    const std::vector<ClassMethod>& getMethods() const { return methods; }
    
    // Field management
    void addField(const ClassField& field);
    bool hasField(const std::string& fieldName) const;
    const ClassField* getField(const std::string& fieldName) const;
    size_t getFieldCount() const { return fields.size(); }
    
    // Method management
    void addMethod(const ClassMethod& method);
    bool hasMethod(const std::string& methodName) const;
    const ClassMethod* getMethod(const std::string& methodName) const;
    std::shared_ptr<FunctionImplementation> getMethodImplementation(const std::string& methodName) const;
    
    // Inheritance
    void setSuperClass(std::shared_ptr<ClassDefinition> super) { superClass = super; }
    std::shared_ptr<ClassDefinition> getSuperClass() const { return superClass; }
    bool hasSuperClass() const { return superClass != nullptr; }
    
    // Interface implementation
    void addInterface(const std::string& interfaceName);
    const std::vector<std::string>& getInterfaces() const { return interfaces; }
    bool implementsInterface(const std::string& interfaceName) const;
    
    // Method resolution (including inheritance)
    std::shared_ptr<FunctionImplementation> resolveMethod(const std::string& methodName) const;
    const ClassField* resolveField(const std::string& fieldName) const;
    
    // Instance creation
    std::shared_ptr<ObjectInstance> createInstance() const;
    
    // Initialize methods after construction (to avoid shared_from_this issues)
    void initializeMethods(const std::vector<std::shared_ptr<AST::FunctionDeclaration>>& methods);
    
    // Type checking
    bool isInstanceOf(const std::string& className) const;
    bool isSubclassOf(const std::string& className) const;
};

// Object instance representing a runtime object
class ObjectInstance : public std::enable_shared_from_this<ObjectInstance> {
private:
    std::shared_ptr<ClassDefinition> classDefinition;
    std::unordered_map<std::string, ValuePtr> fieldValues;
    
public:
    ObjectInstance(std::shared_ptr<ClassDefinition> classDef);
    
    // Basic accessors
    std::shared_ptr<ClassDefinition> getClassDefinition() const { return classDefinition; }
    const std::string& getClassName() const { return classDefinition->getName(); }
    
    // Field access
    ValuePtr getField(const std::string& fieldName) const;
    void setField(const std::string& fieldName, ValuePtr value);
    bool hasField(const std::string& fieldName) const;
    
    // Method calls
    std::shared_ptr<FunctionImplementation> getMethod(const std::string& methodName) const;
    ValuePtr callMethod(const std::string& methodName, const std::vector<ValuePtr>& args);
    
    // Type checking
    bool isInstanceOf(const std::string& className) const;
    bool isInstanceOf(std::shared_ptr<ClassDefinition> classDef) const;
    
    // Initialize fields with default values
    void initializeFields();
    
    // String representation
    std::string toString() const;
};

// Class method implementation for user-defined methods
class ClassMethodImplementation : public FunctionImplementation {
private:
    FunctionSignature signature;
    std::shared_ptr<AST::BlockStatement> body;
    std::shared_ptr<ClassDefinition> ownerClass;
    
public:
    ClassMethodImplementation(const std::shared_ptr<AST::FunctionDeclaration>& decl,
                             std::shared_ptr<ClassDefinition> owner);
    
    const FunctionSignature& getSignature() const override { return signature; }
    ValuePtr execute(const std::vector<ValuePtr>& args) override;
    bool isNative() const override { return false; }
    std::shared_ptr<AST::BlockStatement> getBody() const override { return body; }
    
    std::shared_ptr<ClassDefinition> getOwnerClass() const { return ownerClass; }
};

// Constructor implementation
class ConstructorImplementation : public FunctionImplementation {
private:
    FunctionSignature signature;
    std::shared_ptr<ClassDefinition> ownerClass;
    
public:
    ConstructorImplementation(std::shared_ptr<ClassDefinition> owner,
                             const std::vector<Parameter>& params = {});
    
    const FunctionSignature& getSignature() const override { return signature; }
    ValuePtr execute(const std::vector<ValuePtr>& args) override;
    bool isNative() const override { return false; }
    
    std::shared_ptr<ClassDefinition> getOwnerClass() const { return ownerClass; }
};

// Class registry for managing all classes
class ClassRegistry {
private:
    std::unordered_map<std::string, std::shared_ptr<ClassDefinition>> classes;
    
public:
    // Register a class
    void registerClass(const std::shared_ptr<AST::ClassDeclaration>& decl);
    void registerClass(std::shared_ptr<ClassDefinition> classDef);
    
    // Get class by name
    std::shared_ptr<ClassDefinition> getClass(const std::string& name) const;
    
    // Check if class exists
    bool hasClass(const std::string& name) const;
    
    // Get all class names
    std::vector<std::string> getClassNames() const;
    
    // Clear all classes
    void clear();
    
    // Create instance of a class
    std::shared_ptr<ObjectInstance> createInstance(const std::string& className) const;
    
    // Type checking utilities
    bool isSubclass(const std::string& subclass, const std::string& superclass) const;
    bool implementsInterface(const std::string& className, const std::string& interfaceName) const;
};

// Class utilities
namespace ClassUtils {
    // Convert AST class declaration to ClassDefinition
    std::shared_ptr<ClassDefinition> createClassDefinition(
        const std::shared_ptr<AST::ClassDeclaration>& decl);
    
    // Convert AST field declarations to ClassField objects
    std::vector<ClassField> convertFields(
        const std::vector<std::shared_ptr<AST::VarDeclaration>>& fields);
    
    // Convert AST method declarations to ClassMethod objects
    std::vector<ClassMethod> convertMethods(
        const std::vector<std::shared_ptr<AST::FunctionDeclaration>>& methods,
        std::shared_ptr<ClassDefinition> ownerClass);
    
    // Check method signature compatibility (for inheritance)
    bool isMethodCompatible(const ClassMethod& baseMethod, const ClassMethod& derivedMethod);
    
    // Resolve method in inheritance hierarchy
    std::shared_ptr<FunctionImplementation> resolveMethodInHierarchy(
        std::shared_ptr<ClassDefinition> classDef, const std::string& methodName);
    
    // Check if class implements all required interface methods
    bool validateInterfaceImplementation(std::shared_ptr<ClassDefinition> classDef,
                                        const std::string& interfaceName);
}

} // namespace backend

#endif // CLASSES_HH