#include "error_handling.hh"

/**
 * Error Handling Implementation File
 * 
 * This file provides utility functions and ensures proper initialization
 * of the error handling system. The actual linking is handled by the
 * build system using the provided compile script.
 */

namespace ErrorHandling {
    
    // Static initialization to ensure error handling is ready
    static bool errorHandlingInitialized = false;
    
    void ensureInitialized() {
        if (!errorHandlingInitialized) {
            initializeErrorHandling();
            errorHandlingInitialized = true;
        }
    }
    
    // Force initialization when this module is loaded
    static struct ErrorHandlingInitializer {
        ErrorHandlingInitializer() {
            // Only initialize if components are available
            try {
                ensureInitialized();
            } catch (...) {
                // Silently fail if error handling components aren't available
                // This allows graceful degradation
            }
        }
    } initializer;
    
} // namespace ErrorHandling