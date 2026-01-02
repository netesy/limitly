#include "value.hh"
#include "types.hh"
#include "env.hh"
#include <sstream>

// Helper function to check if a type is an integer type
static bool isIntegerType(TypePtr type) {
    return type->tag == TypeTag::Int || type->tag == TypeTag::Int8 ||
           type->tag == TypeTag::Int16 || type->tag == TypeTag::Int32 ||
           type->tag == TypeTag::Int64 || type->tag == TypeTag::Int128 ||
           type->tag == TypeTag::UInt || type->tag == TypeTag::UInt8 ||
           type->tag == TypeTag::UInt16 || type->tag == TypeTag::UInt32 ||
           type->tag == TypeTag::UInt64 || type->tag == TypeTag::UInt128;
}

// ClosureValue method implementations

ClosureValue::ClosureValue() : startAddress(0), endAddress(0) {}

ClosureValue::ClosureValue(const std::string &funcName, size_t start, size_t end, std::shared_ptr<Environment> capturedEnv, const std::vector<std::string> &capturedVars)
    : functionName(funcName), startAddress(start), endAddress(end),
    capturedEnvironment(capturedEnv), capturedVariables(capturedVars) {}

ClosureValue::ClosureValue(const ClosureValue &other)
    : functionName(other.functionName), startAddress(other.startAddress), endAddress(other.endAddress),
    capturedEnvironment(other.capturedEnvironment), capturedVariables(other.capturedVariables) {}

ClosureValue::ClosureValue(ClosureValue &&other) noexcept
    : functionName(std::move(other.functionName)), startAddress(other.startAddress), endAddress(other.endAddress),
    capturedEnvironment(std::move(other.capturedEnvironment)),
    capturedVariables(std::move(other.capturedVariables)) {}

ClosureValue &ClosureValue::operator=(const ClosureValue &other) {
    if (this != &other) {
        functionName = other.functionName;
        startAddress = other.startAddress;
        endAddress = other.endAddress;
        capturedEnvironment = other.capturedEnvironment;
        capturedVariables = other.capturedVariables;
    }
    return *this;
}

ClosureValue &ClosureValue::operator=(ClosureValue &&other) noexcept {
    if (this != &other) {
        functionName = std::move(other.functionName);
        startAddress = other.startAddress;
        endAddress = other.endAddress;
        capturedEnvironment = std::move(other.capturedEnvironment);
        capturedVariables = std::move(other.capturedVariables);
    }
    return *this;
}

bool ClosureValue::isValid() const {
    return !functionName.empty() && startAddress < endAddress;
}

ValuePtr ClosureValue::execute(const std::vector<ValuePtr> &args) {
    // This will be implemented by the VM when executing closures
    // For now, return nullptr as a placeholder
    if (functionName.empty()) {
        throw std::runtime_error("Cannot execute closure: function name is empty");
    }

    // The actual execution will be handled by the VM's closure execution mechanism
    // This is just a placeholder that will be called by the VM
    return nullptr;
}

size_t ClosureValue::getCapturedVariableCount() const {
    return capturedVariables.size();
}

bool ClosureValue::isVariableCaptured(const std::string &varName) const {
    return std::find(capturedVariables.begin(), capturedVariables.end(), varName)
    != capturedVariables.end();
}

std::string ClosureValue::getFunctionName() const {
    return functionName;
}

std::string ClosureValue::getClosureId() const {
    return functionName + "_" + std::to_string(reinterpret_cast<uintptr_t>(this));
}

void ClosureValue::cleanup() {
    // Clear captured environment to help with garbage collection
    if (capturedEnvironment) {
        // Remove references to captured variables to break potential cycles
        for (const auto& varName : capturedVariables) {
            try {
                capturedEnvironment->remove(varName);
            } catch (const std::runtime_error&) {
                // Variable might already be removed, continue cleanup
            }
        }
    }
    capturedVariables.clear();
}

bool ClosureValue::hasMemoryLeaks() const {
    if (!capturedEnvironment) return false;
    
    // Check if captured environment has circular references
    auto symbols = capturedEnvironment->getAllSymbols();
    for (const auto& [name, value] : symbols) {
        if (value && value->type && value->type->tag == TypeTag::Closure) {
            // Found another closure in captured variables - potential cycle
            return true;
        }
    }
    return false;
}

size_t ClosureValue::getMemoryUsage() const {
    size_t usage = sizeof(ClosureValue);
    usage += functionName.size();
    usage += capturedVariables.size() * sizeof(std::string);
    for (const auto& var : capturedVariables) {
        usage += var.size();
    }
    
    // Estimate captured environment size
    if (capturedEnvironment) {
        auto symbols = capturedEnvironment->getAllSymbols();
        usage += symbols.size() * (sizeof(std::string) + sizeof(ValuePtr));
    }
    
    return usage;
}

std::string ClosureValue::toString() const {
    std::ostringstream oss;
    oss << "Closure(" << functionName << ", captures: [";
    for (size_t i = 0; i < capturedVariables.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << capturedVariables[i];
    }
    oss << "])";
    return oss.str();
}
// ErrorValue method implementations

std::string ErrorValue::toString() const {
    std::ostringstream oss;
    oss << "Error(" << errorType;
    if (!message.empty()) {
        oss << ": " << message;
    }
    if (!arguments.empty()) {
        oss << ", args: [";
        for (size_t i = 0; i < arguments.size(); ++i) {
            if (i > 0) oss << ", ";
            if (arguments[i]) {
                oss << arguments[i]->toString();
            } else {
                oss << "null";
            }
        }
        oss << "]";
    }
    oss << ")";
    return oss.str();
}

// TupleType toString implementation
std::string TupleType::toString() const {
    std::ostringstream oss;
    oss << "(";
    for (size_t i = 0; i < elementTypes.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << (elementTypes[i] ? elementTypes[i]->toString() : "unknown");
    }
    oss << ")";
    return oss.str();
}

// TupleValue toString implementation
std::string TupleValue::toString() const {
    std::ostringstream oss;
    oss << "(";
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i > 0) oss << ", ";
        if (elements[i]) {
            oss << elements[i]->toString();
        } else {
            oss << "nil";
        }
    }
    oss << ")";
    return oss.str();
}

bool IteratorValue::hasNext() const {
    if (type == IteratorType::RANGE) {
        // Convert strings to int64 for comparisons
        int64_t step = ValueConverters::toInt64(rangeStep).value_or(1);
        int64_t current = ValueConverters::toInt64(rangeCurrent).value_or(0);
        int64_t end = ValueConverters::toInt64(rangeEnd).value_or(0);
        
        return (step > 0) ? (current < end) : (current > end);
    } else if (iterable) {
        if (type == IteratorType::LIST) {
            if (auto list = std::get_if<ListValue>(&iterable->complexData)) {
                return currentIndex < list->elements.size();
            }
        } else if (type == IteratorType::CHANNEL) {
            // If we already buffered a value, we have next
            if (hasBuffered) return true;

            // Attempt to receive from the channel (this will block until value or closed)
            try {
                if (auto chPtr = std::get_if<std::shared_ptr<Channel<ValuePtr>>>(&iterable->complexData)) {
                    ValuePtr v;
                    bool ok = (*chPtr)->receive(v);
                    if (ok) {
                        bufferedValue = v;
                        hasBuffered = true;
                        return true;
                    }
                    return false; // channel closed and no value
                }
            } catch (...) {
                return false;
            }
        }
    }
    // Add DICT handling here if needed

    return false;
}

ValuePtr IteratorValue::next() {
    if (!hasNext()) {
        throw std::runtime_error("No more elements in iterator");
    }

    if (type == IteratorType::RANGE) {
        // Create value on-demand
        int64_t value = ValueConverters::toInt64(rangeCurrent).value_or(0);
        
        // Increment current by step (convert to int64, add, convert back to string)
        int64_t step = ValueConverters::toInt64(rangeStep).value_or(1);
        int64_t newCurrent = value + step;
        rangeCurrent = std::to_string(newCurrent);

        // OPTIMIZATION: Reuse a single Value object per thread
        // Note: This is safe because the value is immediately consumed by the VM
        static thread_local ValuePtr cachedRangeValue = nullptr;

        if (!cachedRangeValue) {
            // Create initial cached value with correct type
            auto int64Type = std::make_shared<Type>(TypeTag::Int64);
            cachedRangeValue = std::make_shared<Value>(int64Type, value);
        } else {
            // Reuse existing value by updating data
            cachedRangeValue->data = value;
        }

        return cachedRangeValue;
    }


    if (type == IteratorType::LIST) {
        if (auto list = std::get_if<ListValue>(&iterable->complexData)) {
            if (currentIndex < list->elements.size()) {
                return list->elements[currentIndex++];
            }
        }
        throw std::runtime_error("Invalid list iterator state");
    } else if (type == IteratorType::CHANNEL) {
        if (hasBuffered) {
            auto res = bufferedValue;
            bufferedValue = nullptr;
            hasBuffered = false;
            return res;
        }
        // As a fallback, try to receive directly
        if (auto chPtr = std::get_if<std::shared_ptr<Channel<ValuePtr>>>(&iterable->complexData)) {
            ValuePtr v;
            bool ok = (*chPtr)->receive(v);
            if (ok) return v;
            throw std::runtime_error("No more elements in iterator");
        }
        throw std::runtime_error("Invalid channel iterator state");
    }
    // Add DICT handling here if needed

    throw std::runtime_error("Invalid iterator type");
}

std::string IteratorValue::toString() const {
    std::ostringstream oss;
    oss << "<iterator type=";
    
    switch (type) {
    case IteratorType::LIST:
        oss << "list";
        break;
    case IteratorType::DICT:
        oss << "dict";
        break;
    case IteratorType::CHANNEL:
        oss << "channel";
        break;
    case IteratorType::RANGE:
        oss << "range";
        break;
    default:
        oss << "unknown";
    }
    
    // Show the iterable content if available
    if (iterable) {
        oss << " over=" << iterable->toString();
    } else if (type == IteratorType::RANGE) {
        oss << " range=(" << rangeStart << ".." << rangeEnd;
        // Convert step to int64 for comparison and display
        int64_t stepValue = ValueConverters::toInt64(rangeStep).value_or(1);
        if (stepValue != 1) {
            oss << " step=" << rangeStep;
        }
        oss << ")";
    }
    
    // Show current position
    if (type == IteratorType::RANGE) {
        oss << " current=" << rangeCurrent;
    } else if (iterable) {
        oss << " index=" << currentIndex;
        
        // Show current element if available
        if (type == IteratorType::LIST) {
            if (auto list = std::get_if<ListValue>(&iterable->complexData)) {
                if (currentIndex < list->elements.size()) {
                    oss << " current=" << list->elements[currentIndex]->toString();
                }
            }
        } else if (type == IteratorType::DICT) {
            if (auto dict = std::get_if<DictValue>(&iterable->complexData)) {
                size_t i = 0;
                for (const auto& [key, value] : dict->elements) {
                    if (i == currentIndex) {
                        oss << " current=(" << key->toString() << ": " << value->toString() << ")";
                        break;
                    }
                    i++;
                }
            }
        }
    }
    
    if (hasBuffered) {
        oss << " hasBuffered=true";
    }
    
    oss << ">";
    return oss.str();
}

std::string Value::toString() const {
    std::ostringstream oss;
    
    // Safety check for null type
    if (!type) {
        return "<unknown>";
    }
    
    // Handle primitive types using the data string member
    if (type->tag == TypeTag::Nil) {
        oss << "nil";
    } else if (type->tag == TypeTag::Bool) {
        oss << (as<bool>() ? "true" : "false");
    } else if (type->tag == TypeTag::String) {
        oss << '"' << data << '"'; // Add quotes for string representation
    } else if (isIntegerType(type)) {
        // Handle all integer types - check if it's unsigned
        try {
            if (type->tag == TypeTag::UInt || type->tag == TypeTag::UInt8 || 
                type->tag == TypeTag::UInt16 || type->tag == TypeTag::UInt32 || 
                type->tag == TypeTag::UInt64 || type->tag == TypeTag::UInt128) {
                // For unsigned types, use uint64_t conversion
                uint64_t val = as<uint64_t>();
                std::cout << "[DEBUG] Value::toString() unsigned: data='" << data << "' val=" << val << std::endl;
                oss << val;
            } else {
                // For signed types, use int64_t conversion
                int64_t val = as<int64_t>();
                std::cout << "[DEBUG] Value::toString() signed: data='" << data << "' val=" << val << std::endl;
                oss << val;
            }
        } catch (const std::exception& e) {
            std::cout << "[DEBUG] Value::toString() exception: " << e.what() << " data='" << data << "'" << std::endl;
            oss << "<error>";
        }
    } else if (type->tag == TypeTag::Float32 || type->tag == TypeTag::Float64) {
        // Handle all float types
        try {
            oss << as<double>();
        } catch (...) {
            oss << "<error>";
        }
    } else {
        // Handle complex types using complexData
        std::visit(overloaded{
                   [&](const ListValue& lv) {
                       oss << "[";
                       for (size_t i = 0; i < lv.elements.size(); ++i) {
                           if (i > 0) oss << ", ";
                           oss << lv.elements[i]->toString();
                       }
                       oss << "]";
                   },
                   [&](const DictValue& dv) {
                       oss << "{";
                       bool first = true;
                       for (const auto& [key, value] : dv.elements) {
                           if (!first) oss << ", ";
                           first = false;
                           oss << key->toString() << ": " << value->toString();
                       }
                       oss << "}";
                   },
                   [&](const TupleValue& tv) {
                       oss << tv.toString();
                   },
                   [&](const SumValue& sv) {
                       oss << "Sum(" << sv.activeVariant << ", " << sv.value->toString() << ")";
                   },
                   [&](const EnumValue& ev) { oss << ev.toString(); },
                   [&](const ErrorValue& erv) { oss << erv.toString(); },
                   [&](const UserDefinedValue& udv) {
                       oss << udv.variantName << "{";
                       bool first = true;
                       for (const auto& [field, value] : udv.fields) {
                           if (!first) oss << ", ";
                           first = false;
                           oss << field << ": " << value->toString();
                       }
                       oss << "}";
                   },
                   [&](const IteratorValuePtr& iter) {
                       if (iter) {
                           oss << iter->toString();
                       } else {
                           oss << "<null iterator>";
                       }
                   },
                   [&](const std::shared_ptr<Channel<ValuePtr>>&){
                       oss << "<channel>";
                   },
                   [&](const AtomicValue& av) {
                       if (av.inner) {
                           oss << av.inner->load();
                       } else {
                           oss << "<atomic(nil)>";
                       }
                   },
                   [&](const ObjectInstancePtr& obj) {
                       oss << "<object>";
                   },
                   [&](const std::shared_ptr<backend::ClassDefinition>&) {
                       oss << "<class>";
                   },
                   [&](const ModuleValue&) {
                       oss << "<module>";
                   },
                   [&](const std::shared_ptr<backend::UserDefinedFunction>&) {
                       oss << "<function>";
                   },
                   [&](const backend::Function& func) {
                       oss << "<function:" << func.name << ">";
                   },
                   [&](const ClosureValue& closure) {
                       oss << closure.toString();
                   },
                   [&](const auto&) {
                       oss << "<unknown>";
                   }
               }, complexData);
    }
    return oss.str();
}

std::string Value::getRawString() const {
    std::ostringstream oss;
    
    // Handle primitive types using the data string member
    if (type->tag == TypeTag::Nil) {
        oss << "nil";
    } else if (type->tag == TypeTag::Bool) {
        oss << (as<bool>() ? "true" : "false");
    } else if (type->tag == TypeTag::String) {
        oss << data; // No quotes for raw string
    } else if (isIntegerType(type)) {
        // Handle all integer types
        oss << as<int64_t>();
    } else if (type->tag == TypeTag::Float32 || type->tag == TypeTag::Float64) {
        // Handle all float types
        oss << as<double>();
    } else {
        // Handle complex types using complexData
        std::visit(overloaded{
                   [&](const ListValue& lv) {
                       oss << "[";
                       for (size_t i = 0; i < lv.elements.size(); ++i) {
                           if (i > 0) oss << ", ";
                           oss << lv.elements[i]->getRawString();
                       }
                       oss << "]";
                   },
                   [&](const DictValue& dv) {
                       oss << "{";
                       bool first = true;
                       for (const auto& [key, value] : dv.elements) {
                           if (!first) oss << ", ";
                           first = false;
                           oss << key->getRawString() << ": " << value->getRawString();
                       }
                       oss << "}";
                   },
                   [&](const TupleValue& tv) {
                       oss << "(";
                       for (size_t i = 0; i < tv.elements.size(); ++i) {
                           if (i > 0) oss << ", ";
                           oss << tv.elements[i]->getRawString();
                       }
                       oss << ")";
                   },
                   [&](const SumValue& sv) {
                       oss << "Sum(" << sv.activeVariant << ", " << sv.value->getRawString() << ")";
                   },
                   [&](const EnumValue& ev) {
                       oss << ev.toString(); // Use existing enum toString
                   },
                   [&](const ErrorValue& erv) {
                       oss << erv.toString();
                   },
                   [&](const UserDefinedValue& udv) {
                       oss << udv.variantName << "{";
                       bool first = true;
                       for (const auto& [field, value] : udv.fields) {
                           if (!first) oss << ", ";
                           first = false;
                           oss << field << ": " << value->getRawString();
                       }
                       oss << "}";
                   },
                   [&](const IteratorValuePtr& iter) {
                       if (iter) {
                           oss << iter->toString();
                       } else {
                           oss << "<null iterator>";
                       }
                   },
                   [&](const std::shared_ptr<Channel<ValuePtr>>&){
                       oss << "<channel>";
                   },
                   [&](const AtomicValue& av) {
                       // Print the current atomic integer value
                       if (av.inner) {
                           oss << av.inner->load();
                       } else {
                           oss << "<atomic(nil)>";
                       }
                   },
                   [&](const ObjectInstancePtr& obj) {
                       oss << "<object>";
                   },
                   [&](const std::shared_ptr<backend::ClassDefinition>&) {
                       oss << "<class>";
                   },
                   [&](const ModuleValue&) {
                       oss << "<module>";
                   },
                   [&](const std::shared_ptr<backend::UserDefinedFunction>&) {
                       oss << "<function>";
                   },
                   [&](const backend::Function& func) {
                       oss << "<function:" << func.name << ">";
                   },
                   [&](const ClosureValue& closure) {
                       oss << closure.toString();
                   },
                   [&](const auto&) {
                       oss << "<unknown>";
                   }
               }, complexData);
    }
    return oss.str();
}
