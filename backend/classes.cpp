#include "classes.hh"
#include <stdexcept>
#include <sstream>

namespace backend {

// ClassDefinition implementation
ClassDefinition::ClassDefinition(const std::string& className) : name(className) {}

ClassDefinition::ClassDefinition(const std::shared_ptr<AST::ClassDeclaration>& decl) 
    : name(decl->name) {
    
    // Convert fields
    for (const auto& field : decl->fields) {
        ClassField classField(field->name, field->type.value_or(nullptr), field->initializer);
        addField(classField);
    }
    
    // Note: Methods will be added after construction to avoid shared_from_this issues
}

void ClassDefinition::addField(const ClassField& field) {
    fieldIndex[field.name] = fields.size();
    fields.push_back(field);
}

bool ClassDefinition::hasField(const std::string& fieldName) const {
    return fieldIndex.find(fieldName) != fieldIndex.end();
}

const ClassField* ClassDefinition::getField(const std::string& fieldName) const {
    auto it = fieldIndex.find(fieldName);
    if (it != fieldIndex.end()) {
        return &fields[it->second];
    }
    return nullptr;
}

void ClassDefinition::addMethod(const ClassMethod& method) {
    methodIndex[method.name] = methods.size();
    methods.push_back(method);
}

bool ClassDefinition::hasMethod(const std::string& methodName) const {
    return methodIndex.find(methodName) != methodIndex.end();
}

const ClassMethod* ClassDefinition::getMethod(const std::string& methodName) const {
    auto it = methodIndex.find(methodName);
    if (it != methodIndex.end()) {
        return &methods[it->second];
    }
    return nullptr;
}

std::shared_ptr<FunctionImplementation> ClassDefinition::getMethodImplementation(const std::string& methodName) const {
    const ClassMethod* method = getMethod(methodName);
    return method ? method->implementation : nullptr;
}

void ClassDefinition::addInterface(const std::string& interfaceName) {
    interfaces.push_back(interfaceName);
}

bool ClassDefinition::implementsInterface(const std::string& interfaceName) const {
    return std::find(interfaces.begin(), interfaces.end(), interfaceName) != interfaces.end();
}

std::shared_ptr<FunctionImplementation> ClassDefinition::resolveMethod(const std::string& methodName) const {
    // First check this class
    auto impl = getMethodImplementation(methodName);
    if (impl) {
        return impl;
    }
    
    // Then check superclass
    if (superClass) {
        return superClass->resolveMethod(methodName);
    }
    
    return nullptr;
}

const ClassField* ClassDefinition::resolveField(const std::string& fieldName) const {
    // First check this class
    const ClassField* field = getField(fieldName);
    if (field) {
        return field;
    }
    
    // Then check superclass
    if (superClass) {
        return superClass->resolveField(fieldName);
    }
    
    return nullptr;
}

void ClassDefinition::initializeMethods(const std::vector<std::shared_ptr<AST::FunctionDeclaration>>& methodDecls) {
    // Convert methods
    for (const auto& method : methodDecls) {
        auto methodImpl = std::make_shared<ClassMethodImplementation>(method, shared_from_this());
        ClassMethod classMethod(method->name, methodImpl);
        addMethod(classMethod);
    }
}

std::shared_ptr<ObjectInstance> ClassDefinition::createInstance() const {
    return std::make_shared<ObjectInstance>(
        std::const_pointer_cast<ClassDefinition>(shared_from_this()));
}

bool ClassDefinition::isInstanceOf(const std::string& className) const {
    if (name == className) {
        return true;
    }
    
    if (superClass) {
        return superClass->isInstanceOf(className);
    }
    
    return false;
}

bool ClassDefinition::isSubclassOf(const std::string& className) const {
    if (superClass) {
        if (superClass->getName() == className) {
            return true;
        }
        return superClass->isSubclassOf(className);
    }
    
    return false;
}

// ObjectInstance implementation
ObjectInstance::ObjectInstance(std::shared_ptr<ClassDefinition> classDef) 
    : classDefinition(classDef) {
    initializeFields();
}

ValuePtr ObjectInstance::getField(const std::string& fieldName) const {
    auto it = fieldValues.find(fieldName);
    if (it != fieldValues.end()) {
        return it->second;
    }
    
    // Check if field exists in class definition
    const ClassField* field = classDefinition->resolveField(fieldName);
    if (field) {
        // Return null if field exists but not set
        return std::make_shared<Value>(nullptr);
    }
    
    // For dynamic fields that don't exist, throw an error
    throw std::runtime_error("Field '" + fieldName + "' not found in class '" + 
                            classDefinition->getName() + "'");
}

void ObjectInstance::setField(const std::string& fieldName, ValuePtr value) {
    // Allow dynamic field creation - just set the field value
    fieldValues[fieldName] = value;
}

bool ObjectInstance::hasField(const std::string& fieldName) const {
    // Check both dynamic fields and class-defined fields
    return fieldValues.find(fieldName) != fieldValues.end() || 
           classDefinition->resolveField(fieldName) != nullptr;
}

std::shared_ptr<FunctionImplementation> ObjectInstance::getMethod(const std::string& methodName) const {
    return classDefinition->resolveMethod(methodName);
}

ValuePtr ObjectInstance::callMethod(const std::string& methodName, const std::vector<ValuePtr>& args) {
    auto method = getMethod(methodName);
    if (!method) {
        throw std::runtime_error("Method '" + methodName + "' not found in class '" + 
                                classDefinition->getName() + "'");
    }
    
    // Add 'this' as first argument for instance methods
    std::vector<ValuePtr> methodArgs;
    auto objectType = std::make_shared<Type>(TypeTag::Object);
    methodArgs.push_back(std::make_shared<Value>(objectType, shared_from_this()));
    methodArgs.insert(methodArgs.end(), args.begin(), args.end());
    
    return method->execute(methodArgs);
}

bool ObjectInstance::isInstanceOf(const std::string& className) const {
    return classDefinition->isInstanceOf(className);
}

bool ObjectInstance::isInstanceOf(std::shared_ptr<ClassDefinition> classDef) const {
    return isInstanceOf(classDef->getName());
}

void ObjectInstance::initializeFields() {
    // Initialize all fields with default values
    const auto& fields = classDefinition->getFields();
    for (const auto& field : fields) {
        // Initialize to null by default
        fieldValues[field.name] = std::make_shared<Value>(nullptr);
    }
    
    // Initialize superclass fields
    if (classDefinition->hasSuperClass()) {
        auto superClass = classDefinition->getSuperClass();
        const auto& superFields = superClass->getFields();
        for (const auto& field : superFields) {
            if (fieldValues.find(field.name) == fieldValues.end()) {
                fieldValues[field.name] = std::make_shared<Value>(nullptr);
            }
        }
    }
}

std::string ObjectInstance::toString() const {
    std::ostringstream oss;
    oss << classDefinition->getName() << "@" << this;
    return oss.str();
}

// ClassMethodImplementation
ClassMethodImplementation::ClassMethodImplementation(
    const std::shared_ptr<AST::FunctionDeclaration>& decl,
    std::shared_ptr<ClassDefinition> owner) 
    : ownerClass(owner), body(decl->body) {
    
    signature = FunctionUtils::createSignature(decl);
}

ValuePtr ClassMethodImplementation::execute(const std::vector<ValuePtr>& args) {
    // This will be implemented by the VM when calling methods
    // For now, return null
    return std::make_shared<Value>(nullptr);
}

// ConstructorImplementation
ConstructorImplementation::ConstructorImplementation(
    std::shared_ptr<ClassDefinition> owner,
    const std::vector<Parameter>& params) 
    : ownerClass(owner) {
    
    signature.name = owner->getName();
    signature.parameters = params;
}

ValuePtr ConstructorImplementation::execute(const std::vector<ValuePtr>& args) {
    // Create new instance
    auto instance = ownerClass->createInstance();
    
    // TODO: Initialize fields with constructor arguments
    // For now, just return the instance
    auto objectType = std::make_shared<Type>(TypeTag::Object);
    return std::make_shared<Value>(objectType, instance);
}

// ClassRegistry implementation
void ClassRegistry::registerClass(const std::shared_ptr<AST::ClassDeclaration>& decl) {
    auto classDef = std::make_shared<ClassDefinition>(decl);
    classDef->initializeMethods(decl->methods);
    classes[decl->name] = classDef;
}

void ClassRegistry::registerClass(std::shared_ptr<ClassDefinition> classDef) {
    classes[classDef->getName()] = classDef;
}

std::shared_ptr<ClassDefinition> ClassRegistry::getClass(const std::string& name) const {
    auto it = classes.find(name);
    return (it != classes.end()) ? it->second : nullptr;
}

bool ClassRegistry::hasClass(const std::string& name) const {
    return classes.find(name) != classes.end();
}

std::vector<std::string> ClassRegistry::getClassNames() const {
    std::vector<std::string> names;
    for (const auto& pair : classes) {
        names.push_back(pair.first);
    }
    return names;
}

void ClassRegistry::clear() {
    classes.clear();
}

std::shared_ptr<ObjectInstance> ClassRegistry::createInstance(const std::string& className) const {
    auto classDef = getClass(className);
    if (!classDef) {
        throw std::runtime_error("Class '" + className + "' not found");
    }
    
    return classDef->createInstance();
}

bool ClassRegistry::isSubclass(const std::string& subclass, const std::string& superclass) const {
    auto subclassDef = getClass(subclass);
    if (!subclassDef) {
        return false;
    }
    
    return subclassDef->isSubclassOf(superclass);
}

bool ClassRegistry::implementsInterface(const std::string& className, const std::string& interfaceName) const {
    auto classDef = getClass(className);
    if (!classDef) {
        return false;
    }
    
    return classDef->implementsInterface(interfaceName);
}

// ClassUtils implementation
namespace ClassUtils {

std::shared_ptr<ClassDefinition> createClassDefinition(
    const std::shared_ptr<AST::ClassDeclaration>& decl) {
    return std::make_shared<ClassDefinition>(decl);
}

std::vector<ClassField> convertFields(
    const std::vector<std::shared_ptr<AST::VarDeclaration>>& fields) {
    
    std::vector<ClassField> result;
    for (const auto& field : fields) {
        ClassField classField(field->name, field->type.value_or(nullptr), field->initializer);
        result.push_back(classField);
    }
    return result;
}

std::vector<ClassMethod> convertMethods(
    const std::vector<std::shared_ptr<AST::FunctionDeclaration>>& methods,
    std::shared_ptr<ClassDefinition> ownerClass) {
    
    std::vector<ClassMethod> result;
    for (const auto& method : methods) {
        auto methodImpl = std::make_shared<ClassMethodImplementation>(method, ownerClass);
        ClassMethod classMethod(method->name, methodImpl);
        result.push_back(classMethod);
    }
    return result;
}

bool isMethodCompatible(const ClassMethod& baseMethod, const ClassMethod& derivedMethod) {
    // Check if method signatures are compatible for inheritance
    const auto& baseSig = baseMethod.implementation->getSignature();
    const auto& derivedSig = derivedMethod.implementation->getSignature();
    
    // Names must match
    if (baseSig.name != derivedSig.name) {
        return false;
    }
    
    // Parameter counts must match
    if (baseSig.parameters.size() != derivedSig.parameters.size()) {
        return false;
    }
    
    // TODO: Add more sophisticated type checking
    return true;
}

std::shared_ptr<FunctionImplementation> resolveMethodInHierarchy(
    std::shared_ptr<ClassDefinition> classDef, const std::string& methodName) {
    
    return classDef->resolveMethod(methodName);
}

bool validateInterfaceImplementation(std::shared_ptr<ClassDefinition> classDef,
                                   const std::string& interfaceName) {
    // TODO: Implement interface validation
    // For now, just check if class claims to implement the interface
    return classDef->implementsInterface(interfaceName);
}

} // namespace ClassUtils

} // namespace backend