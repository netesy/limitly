#pragma once

//
// compiler_memory.hh  
// Pure Compile-Time Memory Safety
// Zero runtime presence - all safety verified at compile-time
//

// This file contains ONLY compile-time utilities for the compiler
// No runtime code is generated - all safety is compile-time proven

namespace compiler_memory {

/// ===============================================================
/// COMPILE-TIME REGION TRACKING (FOR COMPILER USE ONLY)
/// ===============================================================

// These are used by the type checker to track regions during compilation
// They generate NO runtime code

struct CompileTimeRegion {
    std::size_t id;
    std::size_t generation;
    int scope_depth;
    
    constexpr CompileTimeRegion(std::size_t region_id, std::size_t gen, int depth)
        : id(region_id), generation(gen), scope_depth(depth) {}
};

struct CompileTimeAllocation {
    std::size_t region_id;
    std::size_t generation;
    bool is_linear;
    bool is_moved;
    
    constexpr CompileTimeAllocation(std::size_t rid, std::size_t gen, bool linear = false)
        : region_id(rid), generation(gen), is_linear(linear), is_moved(false) {}
};

/// ===============================================================
/// COMPILE-TIME VALIDATION (STATIC ASSERTIONS)
/// ===============================================================

// These functions are used by the type checker to validate memory safety
// They compile away to nothing in the final binary

template<typename T>
constexpr bool is_linear_type() {
    // Determine if a type should be linear based on its properties
    // This is a compile-time decision
    return std::is_class_v<T> && !std::is_trivially_copyable_v<T>;
}

constexpr bool can_reference_escape(int creation_scope, int target_scope) {
    return creation_scope > target_scope;
}

constexpr bool is_generation_valid(std::size_t ref_gen, std::size_t current_gen) {
    return ref_gen == current_gen;
}

/// ===============================================================
/// COMPILER DIRECTIVES (NO RUNTIME CODE)
/// ===============================================================

// These macros are used by the compiler to insert appropriate cleanup code
// In release builds, they compile to nothing or simple instructions

#ifdef LIMITLY_DEBUG_MEMORY
    #define LIMITLY_REGION_ENTER(id) /* Debug: track region entry */
    #define LIMITLY_REGION_EXIT(id)  /* Debug: track region exit */  
    #define LIMITLY_LINEAR_MOVE(var) /* Debug: track move */
    #define LIMITLY_LINEAR_DROP(var) /* Debug: track drop */
#else
    #define LIMITLY_REGION_ENTER(id) /* No-op in release */
    #define LIMITLY_REGION_EXIT(id)  /* No-op in release */
    #define LIMITLY_LINEAR_MOVE(var) /* No-op in release */
    #define LIMITLY_LINEAR_DROP(var) /* No-op in release */
#endif

} // namespace compiler_memory

/// ===============================================================
/// WHAT THE COMPILER ACTUALLY GENERATES
/// ===============================================================

// The compiler generates regular, efficient code:
//
// 1. Regular allocations (malloc, stack allocation, etc.)
// 2. Regular cleanup (free, destructors, scope exit)
// 3. Regular moves (memcpy, register moves)
// 4. NO runtime safety checks
// 5. NO reference counting
// 6. NO generation tracking
//
// All safety is PROVEN at compile-time using model.hh

/// ===============================================================
/// OPTIONAL: MINIMAL ALLOCATOR INTERFACE
/// ===============================================================

// If the user wants custom allocation, they can provide these functions
// The compiler will call them instead of malloc/free
// This is OPTIONAL - defaults to system malloc/free

extern "C" {
    // Optional custom allocator (user can provide)
    void* limitly_alloc(size_t size) __attribute__((weak));
    void limitly_free(void* ptr) __attribute__((weak));
    
    // Optional panic handler (user can provide)  
    void limitly_panic(const char* message) __attribute__((weak, noreturn));
}

// Default implementations (weak symbols - user can override)
inline void* limitly_alloc(size_t size) {
    return malloc(size);
}

inline void limitly_free(void* ptr) {
    free(ptr);
}

inline void limitly_panic(const char* message) {
    fprintf(stderr, "Limitly panic: %s\n", message);
    abort();
}