#ifndef type_system_hh
#define type_system_hh

#include "types.hh"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class TypeSystem {
public:
    const TypePtr ANY_TYPE;
    const TypePtr NIL_TYPE;
    const TypePtr BOOL_TYPE;
    const TypePtr INT_TYPE;
    const TypePtr INT64_TYPE;
    const TypePtr UINT64_TYPE;
    const TypePtr FLOAT64_TYPE;
    const TypePtr STRING_TYPE;
    const TypePtr FUNCTION_TYPE;
    const TypePtr OBJECT_TYPE;
    const TypePtr MODULE_TYPE;

    TypeSystem()
        : ANY_TYPE(std::make_shared<NewType>(AnyType{}))
        , NIL_TYPE(std::make_shared<NewType>(NilType{}))
        , BOOL_TYPE(std::make_shared<NewType>(PrimitiveType{"bool"}))
        , INT_TYPE(std::make_shared<NewType>(PrimitiveType{"int"}))
        , INT64_TYPE(std::make_shared<NewType>(PrimitiveType{"int64"}))
        , UINT64_TYPE(std::make_shared<NewType>(PrimitiveType{"uint64"}))
        , FLOAT64_TYPE(std::make_shared<NewType>(PrimitiveType{"float64"}))
        , STRING_TYPE(std::make_shared<NewType>(PrimitiveType{"string"}))
        , FUNCTION_TYPE(std::make_shared<NewType>(FunctionType{{}, ANY_TYPE, {}}))
        , OBJECT_TYPE(std::make_shared<NewType>(UserDefinedType{"object"}))
        , MODULE_TYPE(std::make_shared<NewType>(ModuleType{"module"}))
    {
        primitiveTypes["any"] = ANY_TYPE;
        primitiveTypes["nil"] = NIL_TYPE;
        primitiveTypes["bool"] = BOOL_TYPE;
        primitiveTypes["int"] = INT_TYPE;
        primitiveTypes["int64"] = INT64_TYPE;
        primitiveTypes["uint64"] = UINT64_TYPE;
        primitiveTypes["float64"] = FLOAT64_TYPE;
        primitiveTypes["string"] = STRING_TYPE;
        primitiveTypes["function"] = FUNCTION_TYPE;
        primitiveTypes["object"] = OBJECT_TYPE;
        primitiveTypes["module"] = MODULE_TYPE;
    }

    TypePtr getType(const std::string& name) {
        if (primitiveTypes.count(name)) {
            return primitiveTypes.at(name);
        }
        return NIL_TYPE;
    }

    TypePtr createTypedListType(TypePtr elementType) {
        return std::make_shared<NewType>(ListType{elementType});
    }

    TypePtr createTypedDictType(TypePtr keyType, TypePtr valueType) {
        return std::make_shared<NewType>(DictType{keyType, valueType});
    }

    TypePtr createTupleType(const std::vector<TypePtr>& elementTypes) {
        return std::make_shared<NewType>(TupleType{elementTypes});
    }

    TypePtr createFunctionType(const std::vector<TypePtr>& paramTypes, TypePtr returnType) {
        return std::make_shared<NewType>(FunctionType{paramTypes, returnType, {}});
    }

    TypePtr createUnionType(const std::vector<TypePtr>& types) {
        return std::make_shared<NewType>(UnionType{types});
    }

    TypePtr createErrorUnionType(TypePtr successType, const std::vector<std::string>& errorTypes, bool isGeneric) {
        return std::make_shared<NewType>(ErrorUnionType{successType, errorTypes, isGeneric});
    }

    void registerTypeAlias(const std::string& alias, TypePtr type) {
        typeAliases[alias] = type;
    }

    TypePtr resolveTypeAlias(const std::string& alias) {
        if (typeAliases.count(alias)) {
            return typeAliases.at(alias);
        }
        return nullptr;
    }

    bool isCompatible(TypePtr from, TypePtr to) {
        if (from == to || std::holds_alternative<AnyType>(to->data)) {
            return true;
        }
        if (std::holds_alternative<ListType>(from->data) && std::holds_alternative<ListType>(to->data)) {
            auto fromList = std::get<ListType>(from->data);
            auto toList = std::get<ListType>(to->data);
            return isCompatible(fromList.elementType, toList.elementType);
        }
        return from->toString() == to->toString();
    }

    TypePtr getCommonType(TypePtr t1, TypePtr t2) {
        if (isCompatible(t1, t2)) return t2;
        if (isCompatible(t2, t1)) return t1;
        // Basic numeric promotion
        if (std::holds_alternative<PrimitiveType>(t1->data) && std::holds_alternative<PrimitiveType>(t2->data)) {
            auto p1 = std::get<PrimitiveType>(t1->data).name;
            auto p2 = std::get<PrimitiveType>(t2->data).name;
            if ((p1 == "float64" || p2 == "float64") && (isNumericType(t1) && isNumericType(t2))) return FLOAT64_TYPE;
            if ((p1 == "uint64" || p2 == "uint64") && (isNumericType(t1) && isNumericType(t2))) return UINT64_TYPE;
            if ((p1 == "int64" || p2 == "int64") && (isNumericType(t1) && isNumericType(t2))) return INT64_TYPE;
        }
        return ANY_TYPE;
    }

    bool isNumericType(const TypePtr& type) {
        if (auto* p = std::get_if<PrimitiveType>(&type->data)) {
            return p->name == "int" || p->name == "int64" || p->name == "uint64" || p->name == "float64";
        }
        return false;
    }


private:
    std::unordered_map<std::string, TypePtr> primitiveTypes;
    std::unordered_map<std::string, TypePtr> typeAliases;
};

#endif