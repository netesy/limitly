#ifndef ENV_HH
#define ENV_HH

#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>
#include "../frontend/ast.hh"
#include "value.hh"

class Environment : public std::enable_shared_from_this<Environment> {
public:
    Environment(std::shared_ptr<Environment> enclosing = nullptr) : enclosing(enclosing) {}
    
    void define(const std::string& name, const ValuePtr& value) {
        std::lock_guard<std::mutex> lock(mutex);
        values[name] = value;
        // Default to private visibility for module-level variables
        visibility[name] = AST::VisibilityLevel::Private;
    }
    
    void define(const std::string& name, const ValuePtr& value, AST::VisibilityLevel vis) {
        std::lock_guard<std::mutex> lock(mutex);
        values[name] = value;
        visibility[name] = vis;
    }
    
    ValuePtr get(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex);
        
        // Check captured variables first for closures
        auto capturedIt = capturedVariables.find(name);
        if (capturedIt != capturedVariables.end()) {
            return capturedIt->second;
        }
        
        // Check local variables
        auto it = values.find(name);
        if (it != values.end()) {
            return it->second;
        }
        
        // Check closure parent if this is a closure environment
        if (closureParent) {
            try {
                return closureParent->get(name);
            } catch (const std::runtime_error&) {
                // Continue to check enclosing environment
            }
        }
        
        if (enclosing) {
            // The recursive call will lock the enclosing environment
            return enclosing->get(name);
        }
        
        throw std::runtime_error("Undefined variable '" + name + "'");
    }
    
    // Visibility-aware get method for module access
    ValuePtr get(const std::string& name, bool isExternalAccess) {
        if (!isExternalAccess) {
            return get(name); // Internal access - use normal get
        }
        
        std::lock_guard<std::mutex> lock(mutex);
        
        // Check if variable exists and is accessible externally
        auto it = values.find(name);
        if (it != values.end()) {
            auto visIt = visibility.find(name);
            if (visIt != visibility.end()) {
                // Only allow public access from external modules
                if (visIt->second == AST::VisibilityLevel::Public || 
                    visIt->second == AST::VisibilityLevel::Const) {
                    return it->second;
                } else {
                    throw std::runtime_error("Cannot access private variable '" + name + "' from external module");
                }
            }
            return it->second; // No visibility info - allow access (backward compatibility)
        }
        
        // Check enclosing environments
        if (enclosing) {
            return enclosing->get(name, isExternalAccess);
        }
        
        throw std::runtime_error("Undefined variable '" + name + "'");
    }

   
    void assign(const std::string& name, const ValuePtr& value) {
        std::lock_guard<std::mutex> lock(mutex);
        
        // Check captured variables first for closures
        auto capturedIt = capturedVariables.find(name);
        if (capturedIt != capturedVariables.end()) {
            capturedIt->second = value;
            return;
        }
        
        // Check local variables
        auto it = values.find(name);
        if (it != values.end()) {
            it->second = value;
            return;
        }
        
        // Check closure parent if this is a closure environment
        if (closureParent) {
            try {
                closureParent->assign(name, value);
                return;
            } catch (const std::runtime_error&) {
                // Continue to check enclosing environment
            }
        }
        
        if (enclosing) {
            // The recursive call will lock the enclosing environment
            enclosing->assign(name, value);
            return;
        }
        
        throw std::runtime_error("Undefined variable '" + name + "'");
    }
    
    // Assign to variable in current scope only (no parent scope search)
    // This is used for variable shadowing to ensure we update the correct scope
    void assignInCurrentScope(const std::string& name, const ValuePtr& value) {
        std::lock_guard<std::mutex> lock(mutex);
        
        // Check captured variables first for closures
        auto capturedIt = capturedVariables.find(name);
        if (capturedIt != capturedVariables.end()) {
            capturedIt->second = value;
            return;
        }
        
        // Check local variables in current scope only
        auto it = values.find(name);
        if (it != values.end()) {
            it->second = value;
            return;
        }
        
        throw std::runtime_error("Variable '" + name + "' not found in current scope");
    }
    
    std::unordered_map<std::string, ValuePtr> getAllSymbols() {
        std::lock_guard<std::mutex> lock(mutex);
        return values; // Return a copy
    }
    
    void remove(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = values.find(name);
        if (it != values.end()) {
            values.erase(it);
        } else {
            throw std::runtime_error("Symbol '" + name + "' not found");
        }
    }
    
    // Closure support methods
    std::shared_ptr<Environment> createClosureEnvironment(
        const std::vector<std::string>& capturedVars) {
        auto closureEnv = std::make_shared<Environment>();
        closureEnv->closureParent = shared_from_this();
        
        // Capture specified variables
        for (const auto& varName : capturedVars) {
            try {
                ValuePtr value = get(varName);
                closureEnv->captureVariable(varName, value);
            } catch (const std::runtime_error&) {
                // Variable not found, skip it
                // This allows for forward references or optional captures
            }
        }
        
        return closureEnv;
    }
    
    void captureVariable(const std::string& name, ValuePtr value) {
        std::lock_guard<std::mutex> lock(mutex);
        capturedVariables[name] = value;
    }
    
    bool isVariableCaptured(const std::string& name) const {
        std::lock_guard<std::mutex> lock(mutex);
        return capturedVariables.find(name) != capturedVariables.end();
    }
    
    // Get visibility level of a variable
    AST::VisibilityLevel getVisibility(const std::string& name) const {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = visibility.find(name);
        return (it != visibility.end()) ? it->second : AST::VisibilityLevel::Private;
    }
    
    // Check if a variable can be accessed externally
    bool canAccessExternally(const std::string& name) const {
        AST::VisibilityLevel vis = getVisibility(name);
        return vis == AST::VisibilityLevel::Public || vis == AST::VisibilityLevel::Const;
    }
    
    // Check if a variable exists in the current scope only (not parent scopes)
    bool existsInCurrentScope(const std::string& name) const {
        std::lock_guard<std::mutex> lock(mutex);
        return values.find(name) != values.end();
    }
    
    std::shared_ptr<Environment> enclosing;
    
private:
    std::unordered_map<std::string, ValuePtr> values;
    std::unordered_map<std::string, ValuePtr> capturedVariables;  // Captured variables for closures
    std::unordered_map<std::string, AST::VisibilityLevel> visibility; // Variable visibility levels
    std::shared_ptr<Environment> closureParent;  // Parent environment for closures
    mutable std::mutex mutex;
};

#endif // ENV_HH
