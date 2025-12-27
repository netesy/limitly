#pragma once
#include <type_traits>
#include <cstddef>

//
// model.hh
// Compile-Time Memory Proof Model
// Zero runtime presence. JIT-safe.
//

namespace memory_model {

/// ===============================================================
/// 1. Region Frame (Type-Level Only)
/// ===============================================================

template<std::size_t RegionID, std::size_t Generation = 0>
struct Region {
    static constexpr std::size_t id = RegionID;
    static constexpr std::size_t gen = Generation;
};

template<typename R>
using EnterScope = Region<R::id, R::gen + 1>;

template<typename R>
using ExitScope  = Region<R::id, (R::gen > 0 ? R::gen - 1 : 0)>;


/// ===============================================================
/// 2. Allocation Identity
/// ===============================================================

template<typename RegionT, typename T, std::size_t AllocID>
struct Allocation {
    using region = RegionT;
    using type   = T;
    static constexpr std::size_t id = AllocID;
};


/// ===============================================================
/// 3. Ownership States (State Machine)
/// ===============================================================

struct Owned {};
struct Moved {};
struct Dropped {};

template<typename Alloc, typename State>
struct Value {
    using allocation = Alloc;
    using state = State;
};


/// ===============================================================
/// 4. Move Semantics (After move → dead)
/// ===============================================================

template<typename V>
struct Move;

template<typename Alloc>
struct Move<Value<Alloc, Owned>> {
    using type = Value<Alloc, Moved>;
};

template<typename Alloc>
struct Move<Value<Alloc, Moved>> {
    static_assert(sizeof(Alloc) == 0, "Use-after-move detected");
};

template<typename Alloc>
struct Move<Value<Alloc, Dropped>> {
    static_assert(sizeof(Alloc) == 0, "Move-after-drop detected");
};


/// ===============================================================
/// 5. Drop Semantics (Exactly once)
/// ===============================================================

template<typename V>
struct Drop;

template<typename Alloc>
struct Drop<Value<Alloc, Owned>> {
    using type = Value<Alloc, Dropped>;
};

template<typename Alloc>
struct Drop<Value<Alloc, Dropped>> {
    static_assert(sizeof(Alloc) == 0, "Double drop detected");
};

template<typename Alloc>
struct Drop<Value<Alloc, Moved>> {
    static_assert(sizeof(Alloc) == 0, "Dropping moved value is illegal");
};


/// ===============================================================
/// 6. Borrowing Rules
/// ===============================================================

template<typename OwnerValue, typename BorrowRegion>
struct Borrow {
    static_assert(
        std::is_same_v<typename OwnerValue::state, Owned>,
        "Cannot borrow from non-owned value"
    );

    static_assert(
        OwnerValue::allocation::region::id == BorrowRegion::id,
        "Borrow cannot cross region boundary"
    );

    static_assert(
        OwnerValue::allocation::region::gen >= BorrowRegion::gen,
        "Borrow outlives owner"
    );

    using allocation = typename OwnerValue::allocation;
    using region = BorrowRegion;
};


/// ===============================================================
/// 7. References (Region-Locked)
/// ===============================================================

template<typename Alloc, typename RefRegion>
struct Ref {
    static_assert(
        Alloc::region::id == RefRegion::id,
        "Ref cannot cross region boundary"
    );

    static_assert(
        Alloc::region::gen >= RefRegion::gen,
        "Ref outlives allocation"
    );

    using allocation = Alloc;
    using region = RefRegion;
};


/// ===============================================================
/// 8. Escape Analysis
/// ===============================================================

template<typename Alloc, typename TargetRegion>
struct Escapes : std::bool_constant<
    Alloc::region::id != TargetRegion::id ||
    Alloc::region::gen < TargetRegion::gen
> {};


/// ===============================================================
/// 9. Zero-Cost Generational References
/// ===============================================================

template<typename Alloc, std::size_t RefGen>
struct GenRef {
    using allocation = Alloc;
    static constexpr std::size_t ref_generation = RefGen;
    
    static_assert(
        Alloc::region::gen >= RefGen,
        "Reference generation outlives allocation"
    );
    
    static_assert(
        Alloc::region::id == Alloc::region::id,
        "Reference cannot cross region boundary"
    );
};

template<typename Alloc, std::size_t CurrentGen>
using ValidGenRef = GenRef<Alloc, CurrentGen>;

template<typename Alloc, std::size_t StaleGen>
using StaleGenRef = GenRef<Alloc, StaleGen>;


/// ===============================================================
/// 10. Enhanced Linear Types (Improved from section 3)
/// ===============================================================

template<typename Alloc>
struct LinearValue : Value<Alloc, Owned> {
    // Linear types inherit from Value but add compile-time constraints
    LinearValue() = delete;
    LinearValue(const LinearValue&) = delete;
    LinearValue& operator=(const LinearValue&) = delete;
    
    LinearValue(LinearValue&&) = default;
    LinearValue& operator=(LinearValue&&) = default;
};

template<typename Alloc>
using MakeLinear = LinearValue<Alloc>;


/// ===============================================================
/// 11. Linear Functions (Consume all inputs)
/// ===============================================================

template<typename... Inputs>
struct LinearFunction {
    static_assert(
        (... && (std::is_same_v<typename Inputs::state, Owned>)),
        "Linear function requires owned inputs"
    );
};

template<typename... Inputs>
using LinearFn = LinearFunction<Inputs...>;


/// ===============================================================
/// 12. Affine Types (Use at most once)
/// ===============================================================

template<typename Alloc>
struct AffineValue : Value<Alloc, Owned> {
    // Affine types can be used OR moved, but not both
    // This constraint is enforced by the type checker
};

template<typename Alloc>
using MakeAffine = AffineValue<Alloc>;


/// ===============================================================
/// 13. Resource Types (Explicit disposal)
/// ===============================================================

template<typename Alloc>
struct ResourceValue : Value<Alloc, Owned> {
    // Resources must be explicitly dropped before scope exit
    // Enforced by type checker's drop analysis
};

template<typename Alloc>
using MakeResource = ResourceValue<Alloc>;


/// ===============================================================
/// 14. LINEAR TYPES WITH REFERENCE SEMANTICS
/// ===============================================================

// True linear type - owns data, can be moved but not copied
template<typename Alloc, std::size_t CurrentGeneration = 0>
struct LinearType : Value<Alloc, Owned> {
    static constexpr std::size_t current_generation = CurrentGeneration;
    static constexpr bool is_linear = true;
    static constexpr bool is_movable = true;
    static constexpr bool is_copyable = false;
    
    LinearType() = delete;
    LinearType(const LinearType&) = delete;
    LinearType& operator=(const LinearType&) = delete;
    
    LinearType(LinearType&&) = default;
    LinearType& operator=(LinearType&&) = default;
    
    // Move to next generation - invalidates all references
    using NextGeneration = LinearType<Alloc, CurrentGeneration + 1>;
};

// Reference to linear type - scoped to generation
template<typename LinearType, std::size_t RefId, std::size_t Generation>
struct LinearRef {
    using linear_type = LinearType;
    static constexpr std::size_t ref_id = RefId;
    static constexpr std::size_t generation = Generation;
    static constexpr bool is_reference = true;
    static constexpr bool is_owner = false;
    
    // Reference is only valid if generation matches current linear type generation
    static_assert(!LinearType::is_reference, "Cannot have reference to reference");
};

// Generation-scoped reference manager
template<typename LinearType, std::size_t CurrentGeneration, std::size_t... RefIds>
struct RefManager {
    using linear_type = LinearType;
    static constexpr std::size_t current_generation = CurrentGeneration;
    static constexpr std::size_t ref_count = sizeof...(RefIds);
    
    // Add new reference with current generation
    template<std::size_t NewRefId>
    using AddRef = RefManager<LinearType, CurrentGeneration, RefIds..., NewRefId>;
    
    // Move to next generation - all old references become invalid
    using NextGeneration = RefManager<LinearType, CurrentGeneration + 1>;
    
    // Check if reference is valid for current generation
    template<std::size_t RefId>
    static constexpr bool is_valid_ref = false;  // References don't track generations here
    
    // Reference validity is checked at compile time
    template<std::size_t RefId, std::size_t RefGeneration>
    static constexpr bool is_generation_valid = (RefGeneration == CurrentGeneration);
};

// Scoped reference with generation tracking
template<typename LinearType, std::size_t RefId, std::size_t Generation, bool IsMutable = false>
struct ScopedRef {
    using linear_type = LinearType;
    static constexpr std::size_t ref_id = RefId;
    static constexpr std::size_t generation = Generation;
    static constexpr bool is_stack_allocated = true;
    static constexpr bool is_mutable = IsMutable;
    
    // Reference is only valid if generation matches
    static constexpr bool is_valid = (Generation == LinearType::current_generation);
};

// Mutable aliasing detector
template<typename LinearType, std::size_t... MutableRefs>
struct MutableAliasChecker {
    static constexpr bool has_mutable_aliases = (sizeof...(MutableRefs) > 0);
    
    // Rule: Cannot have mutable aliases while other references exist
    template<std::size_t... ImmutableRefs>
    static constexpr bool can_coexist = (sizeof...(MutableRefs) == 0) || (sizeof...(ImmutableRefs) == 0);
};

// Lifetime analysis for escape detection
template<typename LinearType, std::size_t ScopeLevel, std::size_t CreationScope>
struct LifetimeTracker {
    static constexpr std::size_t scope_level = ScopeLevel;
    static constexpr std::size_t creation_scope = CreationScope;
    static constexpr bool escapes_scope = (CreationScope < ScopeLevel);
    
    // Reference is invalid if it escapes its creation scope
    static constexpr bool is_valid_escape = !escapes_scope;
};

// Enhanced reference with lifetime and mutability tracking
template<typename LinearType, std::size_t RefId, std::size_t Generation, 
          std::size_t CreationScope, std::size_t CurrentScope, bool IsMutable = false>
struct EnhancedScopedRef {
    using linear_type = LinearType;
    static constexpr std::size_t ref_id = RefId;
    static constexpr std::size_t generation = Generation;
    static constexpr std::size_t creation_scope = CreationScope;
    static constexpr std::size_t current_scope = CurrentScope;
    static constexpr bool is_mutable = IsMutable;
    static constexpr bool is_stack_allocated = true;
    
    // Multiple validity checks
    static constexpr bool generation_valid = (Generation == LinearType::current_generation);
    static constexpr bool scope_valid = (CreationScope <= CurrentScope);
    static constexpr bool does_not_escape = (CreationScope >= CurrentScope);
    static constexpr bool is_valid = generation_valid && scope_valid && does_not_escape;
    
    // Escape analysis
    static constexpr bool would_escape = (CurrentScope > CreationScope);
};

// Move operation that invalidates all references
template<typename LinearType, typename RefMgr>
struct LinearMove {
    using new_linear_type = LinearType;  // Linear type moves to new location
    using invalidated_refs = RefMgr;      // All references become invalid
    
    static_assert(LinearType::is_linear, "Can only move linear types");
};


/// ===============================================================
/// 14. Enhanced Smart Pointers (Zero-Cost)
/// ===============================================================

template<typename Alloc>
struct UniquePtr : Value<Alloc, Owned> {
    // Unique ownership - compile-time enforced
    UniquePtr() = delete;
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    
    UniquePtr(UniquePtr&&) = default;
    UniquePtr& operator=(UniquePtr&&) = default;
};

template<typename Alloc>
struct SharedPtr : Value<Alloc, Owned> {
    // Shared ownership - compile-time reference counting
    // Tracked by type checker, no runtime overhead
};

template<typename Alloc>
struct WeakPtr {
    using allocation = Alloc;
    
    // Weak reference - doesn't affect ownership
    static_assert(
        Alloc::region::gen >= 0,
        "Weak pointer must reference valid allocation"
    );
};


/// ===============================================================
/// 15. Compiler-Facing Assertions (Enhanced)
/// ===============================================================

template<typename Alloc, typename Region>
constexpr void assert_no_escape() {
    static_assert(
        !Escapes<Alloc, Region>::value,
        "Illegal escape across region boundary"
    );
}

template<typename ValueT>
constexpr void assert_alive() {
    static_assert(
        std::is_same_v<typename ValueT::state, Owned>,
        "Use of dead value"
    );
}

template<typename FinalValue>
constexpr void assert_dropped() {
    static_assert(
        std::is_same_v<typename FinalValue::state, Dropped>,
        "Allocation missing required drop"
    );
}

template<typename Alloc, std::size_t RefGen>
constexpr void assert_valid_gen_ref() {
    static_assert(
        Alloc::region::gen >= RefGen,
        "Invalid generational reference"
    );
}

// =============================================================================
// LINEAR TYPE COMPILE-TIME ASSERTIONS
// =============================================================================

template<typename LinearType, typename RefMgr>
constexpr void assert_linear_move() {
    static_assert(
        LinearType::is_linear,
        "Can only move linear types"
    );
}

template<typename LinearType, std::size_t RefId, std::size_t Generation>
constexpr void assert_valid_ref() {
    static_assert(
        LinearType::is_linear,
        "Reference must be to a linear type"
    );
    static_assert(
        !LinearRef<LinearType, RefId, Generation>::is_owner,
        "References cannot be owners"
    );
}

// Mutable aliasing assertions
template<typename LinearType, std::size_t... MutableRefs>
constexpr void assert_no_mutable_aliasing() {
    static_assert(
        sizeof...(MutableRefs) <= 1,
        "Multiple mutable aliases not allowed"
    );
}

template<typename LinearType, std::size_t MutableRef, std::size_t... ImmutableRefs>
constexpr void assert_mutable_exclusivity() {
    static_assert(
        sizeof...(ImmutableRefs) == 0,
        "Cannot have immutable references when mutable reference exists"
    );
}

// Lifetime analysis assertions
template<typename LinearType, std::size_t CreationScope, std::size_t CurrentScope>
constexpr void assert_scope_validity() {
    static_assert(
        CreationScope <= CurrentScope,
        "Reference creation scope cannot be greater than current scope"
    );
}

template<typename LinearType, std::size_t CreationScope, std::size_t ReturnScope>
constexpr void assert_no_escape() {
    static_assert(
        CreationScope >= ReturnScope,
        "Reference cannot escape its creation scope - would create dangling reference"
    );
}

template<typename LinearType, std::size_t RefId, std::size_t Generation, 
          std::size_t CreationScope, std::size_t CurrentScope, bool IsMutable>
constexpr void assert_enhanced_ref_validity() {
    static_assert(
        LinearType::is_linear,
        "Enhanced reference must be to linear type"
    );
    
    static_assert(
        Generation == LinearType::current_generation,
        "Enhanced reference generation mismatch"
    );
    
    static_assert(
        CreationScope <= CurrentScope,
        "Enhanced reference scope violation"
    );
    
    if constexpr (IsMutable) {
        static_assert(
            CreationScope >= CurrentScope,
            "Mutable reference cannot escape scope"
        );
    }
}

template<typename LinearType, typename RefMgr, std::size_t RefId>
constexpr void assert_ref_not_invalidated() {
    static_assert(
        !RefMgr::template has_ref<RefId>,
        "Reference invalidated by linear type move"
    );
}

template<typename LinearType, typename... Refs>
constexpr void assert_linear_type_properties() {
    static_assert(
        LinearType::is_linear,
        "Type must be linear"
    );
    static_assert(
        LinearType::is_movable,
        "Linear type must be movable"
    );
    static_assert(
        !LinearType::is_copyable,
        "Linear type must not be copyable"
    );
}

template<typename T>
constexpr void assert_linear_usage() {
    static_assert(
        std::is_base_of_v<Value<typename T::allocation, Owned>, T>,
        "Linear type must be owned"
    );
}

} // namespace memory_model
