#ifndef BIG_INT_H
#define BIG_INT_H

#include <vector>
#include <string>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <climits>
#include <type_traits>
#include <cstring>

#if defined(__SIZEOF_INT128__)
#define HAS_INT128 1
using int128_t = __int128;
using uint128_t = unsigned __int128;
#else
#error "Compiler does not support 128-bit integers"
#endif

class BigInt {
private:
    // Storage type enumeration
    enum StorageType : uint8_t {
        TYPE_I8,
        TYPE_U8,
        TYPE_I16,
        TYPE_U16,
        TYPE_I32,
        TYPE_U32,
        TYPE_I64,
        TYPE_U64,
        TYPE_I128,
        TYPE_LARGE
    };
    
    // Storage types
    struct LargeRep {
        std::vector<uint64_t> limbs; // Base 2^64 limbs
        bool is_negative;
        
        LargeRep() : is_negative(false) {}
        LargeRep(const LargeRep& other) : limbs(other.limbs), is_negative(other.is_negative) {}
        ~LargeRep() {}
    };
    
    StorageType storage_type;
    bool fixed_type;  // Flag to prevent automatic downgrades
    
    union {
        int8_t i8_val;
        uint8_t u8_val;
        int16_t i16_val;
        uint16_t u16_val;
        int32_t i32_val;
        uint32_t u32_val;
        int64_t i64_val;
        uint64_t u64_val;
        int128_t i128_val;
        LargeRep large_rep;
    };

    // Get current value as int128_t (for small types)
    int128_t get_small_value() const {
        switch (storage_type) {
            case TYPE_I8: return i8_val;
            case TYPE_U8: return u8_val;
            case TYPE_I16: return i16_val;
            case TYPE_U16: return u16_val;
            case TYPE_I32: return i32_val;
            case TYPE_U32: return u32_val;
            case TYPE_I64: return i64_val;
            case TYPE_U64: return static_cast<int128_t>(u64_val);
            case TYPE_I128: return i128_val;
            default: return 0;
        }
    }

    // Check if value fits in current type
    bool fits_in_current_type(int128_t value) const {
        switch (storage_type) {
            case TYPE_I8: return value >= INT8_MIN && value <= INT8_MAX;
            case TYPE_U8: return value >= 0 && value <= UINT8_MAX;
            case TYPE_I16: return value >= INT16_MIN && value <= INT16_MAX;
            case TYPE_U16: return value >= 0 && value <= UINT16_MAX;
            case TYPE_I32: return value >= INT32_MIN && value <= INT32_MAX;
            case TYPE_U32: return value >= 0 && value <= UINT32_MAX;
            case TYPE_I64: return value >= INT64_MIN && value <= INT64_MAX;
            case TYPE_U64: return value >= 0;
            case TYPE_I128: return true;
            case TYPE_LARGE: return false;
        }
        return false;
    }

    // Set value maintaining current type if fixed
    void set_value_respecting_type(int128_t value) {
        if (fixed_type && storage_type != TYPE_LARGE) {
            // Try to maintain current type
            if (fits_in_current_type(value)) {
                set_value_in_current_type(value);
                return;
            }
            // Value doesn't fit, need to upgrade
        }
        
        // Not fixed or doesn't fit, optimize storage
        set_small_value(value);
    }

    // Set value in the current type (assumes it fits)
    void set_value_in_current_type(int128_t value) {
        switch (storage_type) {
            case TYPE_I8: i8_val = static_cast<int8_t>(value); break;
            case TYPE_U8: u8_val = static_cast<uint8_t>(value); break;
            case TYPE_I16: i16_val = static_cast<int16_t>(value); break;
            case TYPE_U16: u16_val = static_cast<uint16_t>(value); break;
            case TYPE_I32: i32_val = static_cast<int32_t>(value); break;
            case TYPE_U32: u32_val = static_cast<uint32_t>(value); break;
            case TYPE_I64: i64_val = static_cast<int64_t>(value); break;
            case TYPE_U64: u64_val = static_cast<uint64_t>(value); break;
            case TYPE_I128: i128_val = value; break;
            default: break;
        }
    }

    // Set value with optimal storage type
    void set_small_value(int128_t value) {
        if (storage_type == TYPE_LARGE) {
            destroy_current();
        }
        
        // Try signed types first (for negative values)
        if (value >= INT8_MIN && value <= INT8_MAX) {
            storage_type = TYPE_I8;
            i8_val = static_cast<int8_t>(value);
        }
        else if (value >= 0 && value <= UINT8_MAX) {
            storage_type = TYPE_U8;
            u8_val = static_cast<uint8_t>(value);
        }
        else if (value >= INT16_MIN && value <= INT16_MAX) {
            storage_type = TYPE_I16;
            i16_val = static_cast<int16_t>(value);
        }
        else if (value >= 0 && value <= UINT16_MAX) {
            storage_type = TYPE_U16;
            u16_val = static_cast<uint16_t>(value);
        }
        else if (value >= INT32_MIN && value <= INT32_MAX) {
            storage_type = TYPE_I32;
            i32_val = static_cast<int32_t>(value);
        }
        else if (value >= 0 && value <= UINT32_MAX) {
            storage_type = TYPE_U32;
            u32_val = static_cast<uint32_t>(value);
        }
        else if (value >= INT64_MIN && value <= INT64_MAX) {
            storage_type = TYPE_I64;
            i64_val = static_cast<int64_t>(value);
        }
        else if (value >= 0) {
            storage_type = TYPE_U64;
            u64_val = static_cast<uint64_t>(value);
        }
        else {
            storage_type = TYPE_I128;
            i128_val = value;
        }
    }

    // Convert small to large representation
    void convert_to_large() {
        if (storage_type == TYPE_LARGE) return;
        
        int128_t value = get_small_value();
        destroy_current();
        
        storage_type = TYPE_LARGE;
        new (&large_rep) LargeRep();
        
        large_rep.is_negative = (value < 0);
        uint128_t abs_val = static_cast<uint128_t>(large_rep.is_negative ? -value : value);
        
        if (abs_val == 0) {
            large_rep.limbs.push_back(0);
            return;
        }
        
        while (abs_val > 0) {
            large_rep.limbs.push_back(static_cast<uint64_t>(abs_val));
            abs_val >>= 64;
        }
    }

    // Try to downgrade from large to smaller types (respects fixed_type)
    void try_downgrade() {
        if (storage_type != TYPE_LARGE || fixed_type) return;
        
        normalize_large();
        
        // Check if fits in 128-bit
        if (large_rep.limbs.size() > 2) return;
        
        uint128_t abs_val = 0;
        for (size_t i = 0; i < large_rep.limbs.size(); i++) {
            abs_val |= (static_cast<uint128_t>(large_rep.limbs[i]) << (64 * i));
        }
        
        // Check if fits in signed 128-bit
        constexpr uint128_t MAX_I128 = (static_cast<uint128_t>(1) << 127) - 1;
        
        int128_t value;
        if (large_rep.is_negative) {
            if (abs_val > MAX_I128 + 1) return;
            value = -static_cast<int128_t>(abs_val);
        } else {
            if (abs_val > MAX_I128) return;
            value = static_cast<int128_t>(abs_val);
        }
        
        // Successfully converted, now downgrade
        large_rep.~LargeRep();
        set_small_value(value);
    }

    // Normalize large representation
    void normalize_large() {
        while (large_rep.limbs.size() > 1 && large_rep.limbs.back() == 0) {
            large_rep.limbs.pop_back();
        }
        if (large_rep.limbs.size() == 1 && large_rep.limbs[0] == 0) {
            large_rep.is_negative = false;
        }
    }

    // Destroy current storage
    void destroy_current() {
        if (storage_type == TYPE_LARGE) {
            large_rep.~LargeRep();
        }
    }

public:
    // Constructors
    BigInt() : storage_type(TYPE_I8), fixed_type(false), i8_val(0) {}
    
    BigInt(int64_t n, bool fix_type = false) : fixed_type(fix_type) {
        set_small_value(static_cast<int128_t>(n));
    }
    
    BigInt(const std::string& s, bool fix_type = false) : storage_type(TYPE_I8), fixed_type(fix_type), i8_val(0) {
        from_string(s);
    }
    
    // Typed constructors for fixed types
    static BigInt i8(int8_t value) {
        BigInt result;
        result.storage_type = TYPE_I8;
        result.i8_val = value;
        result.fixed_type = true;
        return result;
    }
    
    static BigInt u8(uint8_t value) {
        BigInt result;
        result.storage_type = TYPE_U8;
        result.u8_val = value;
        result.fixed_type = true;
        return result;
    }
    
    static BigInt i16(int16_t value) {
        BigInt result;
        result.storage_type = TYPE_I16;
        result.i16_val = value;
        result.fixed_type = true;
        return result;
    }
    
    static BigInt u16(uint16_t value) {
        BigInt result;
        result.storage_type = TYPE_U16;
        result.u16_val = value;
        result.fixed_type = true;
        return result;
    }
    
    static BigInt i32(int32_t value) {
        BigInt result;
        result.storage_type = TYPE_I32;
        result.i32_val = value;
        result.fixed_type = true;
        return result;
    }
    
    static BigInt u32(uint32_t value) {
        BigInt result;
        result.storage_type = TYPE_U32;
        result.u32_val = value;
        result.fixed_type = true;
        return result;
    }
    
    static BigInt i64(int64_t value) {
        BigInt result;
        result.storage_type = TYPE_I64;
        result.i64_val = value;
        result.fixed_type = true;
        return result;
    }
    
    static BigInt u64(uint64_t value) {
        BigInt result;
        result.storage_type = TYPE_U64;
        result.u64_val = value;
        result.fixed_type = true;
        return result;
    }
    
    static BigInt i128(int128_t value) {
        BigInt result;
        result.storage_type = TYPE_I128;
        result.i128_val = value;
        result.fixed_type = true;
        return result;
    }
    
    static BigInt i128(const std::string& s) {
        BigInt result(s, false);
        if (result.storage_type != TYPE_LARGE) {
            result.storage_type = TYPE_I128;
            result.i128_val = result.get_small_value();
        }
        result.fixed_type = true;
        return result;
    }
    
    static BigInt large(const std::string& s) {
        BigInt result(s, false);
        result.convert_to_large();
        result.fixed_type = true;
        return result;
    }
    
    static BigInt large(int64_t value) {
        BigInt result;
        result.storage_type = TYPE_LARGE;
        new (&result.large_rep) LargeRep();
        result.large_rep.is_negative = (value < 0);
        uint64_t abs_val = (value < 0) ? -value : value;
        result.large_rep.limbs.push_back(abs_val);
        result.fixed_type = true;
        return result;
    }
    
    // Copy constructor
    BigInt(const BigInt& other) : storage_type(other.storage_type), fixed_type(other.fixed_type) {
        if (storage_type == TYPE_LARGE) {
            new (&large_rep) LargeRep(other.large_rep);
        } else {
            i128_val = other.i128_val;
        }
    }
    
    // Destructor
    ~BigInt() {
        destroy_current();
    }
    
    // Assignment operator
    BigInt& operator=(const BigInt& other) {
        if (this != &other) {
            destroy_current();
            storage_type = other.storage_type;
            fixed_type = other.fixed_type;
            
            if (storage_type == TYPE_LARGE) {
                new (&large_rep) LargeRep(other.large_rep);
            } else {
                i128_val = other.i128_val;
            }
        }
        return *this;
    }

    // Type management
    void fix_type() { fixed_type = true; }
    void unfix_type() { fixed_type = false; }
    bool is_fixed_type() const { return fixed_type; }
    
    // Comparison operators (public)
    bool operator==(const BigInt& other) const {
        if (storage_type == TYPE_LARGE || other.storage_type == TYPE_LARGE) {
            if (storage_type != other.storage_type) {
                BigInt this_copy = *this;
                BigInt other_copy = other;
                this_copy.convert_to_large();
                other_copy.convert_to_large();
                return this_copy.large_rep.is_negative == other_copy.large_rep.is_negative &&
                       this_copy.compare_magnitude(other_copy.large_rep.limbs) == 0;
            }
            return large_rep.is_negative == other.large_rep.is_negative &&
                   compare_magnitude(other.large_rep.limbs) == 0;
        }
        
        // Both are small types
        int128_t this_val = get_small_value();
        int128_t other_val = other.get_small_value();
        return this_val == other_val;
    }
    
    bool operator!=(const BigInt& other) const {
        return !(*this == other);
    }
    
    bool operator<(const BigInt& other) const {
        if (storage_type == TYPE_LARGE || other.storage_type == TYPE_LARGE) {
            if (storage_type != other.storage_type) {
                BigInt this_copy = *this;
                BigInt other_copy = other;
                this_copy.convert_to_large();
                other_copy.convert_to_large();
                
                if (this_copy.large_rep.is_negative != other_copy.large_rep.is_negative) {
                    return this_copy.large_rep.is_negative && !other_copy.large_rep.is_negative;
                }
                if (this_copy.large_rep.is_negative) {
                    return this_copy.compare_magnitude(other_copy.large_rep.limbs) > 0;
                } else {
                    return this_copy.compare_magnitude(other_copy.large_rep.limbs) < 0;
                }
            }
            
            if (large_rep.is_negative != other.large_rep.is_negative) {
                return large_rep.is_negative && !other.large_rep.is_negative;
            }
            if (large_rep.is_negative) {
                return compare_magnitude(other.large_rep.limbs) > 0;
            } else {
                return compare_magnitude(other.large_rep.limbs) < 0;
            }
        }
        
        // Both are small types
        int128_t this_val = get_small_value();
        int128_t other_val = other.get_small_value();
        return this_val < other_val;
    }
    
    bool operator>(const BigInt& other) const {
        return other < *this;
    }
    
    bool operator<=(const BigInt& other) const {
        return !(other < *this);
    }
    
    bool operator>=(const BigInt& other) const {
        return !(*this < other);
    }
    
    // Comparison with integer types
    bool operator>(int value) const {
        return *this > BigInt(value);
    }
    
    bool operator!=(int value) const {
        return *this != BigInt(value);
    }
    
    // Conversion to int64_t
    int64_t to_int64() const {
        if (storage_type == TYPE_LARGE) {
            // For large numbers, try to convert if possible
            int128_t val = get_small_value();
            if (val >= INT64_MIN && val <= INT64_MAX) {
                return static_cast<int64_t>(val);
            }
            throw std::overflow_error("BigInt too large for int64_t");
        }
        int128_t val = get_small_value();
        if (val >= INT64_MIN && val <= INT64_MAX) {
            return static_cast<int64_t>(val);
        }
        throw std::overflow_error("BigInt too large for int64_t");
    }
    
    // Get storage type name (for debugging)
    std::string get_type() const {
        std::string type;
        switch (storage_type) {
            case TYPE_I8: type = "i8"; break;
            case TYPE_U8: type = "u8"; break;
            case TYPE_I16: type = "i16"; break;
            case TYPE_U16: type = "u16"; break;
            case TYPE_I32: type = "i32"; break;
            case TYPE_U32: type = "u32"; break;
            case TYPE_I64: type = "i64"; break;
            case TYPE_U64: type = "u64"; break;
            case TYPE_I128: type = "i128"; break;
            case TYPE_LARGE: type = "large"; break;
            default: type = "unknown"; break;
        }
        return type + (fixed_type ? " (fixed)" : " (auto)");
    }

    // Arithmetic operators
    BigInt& operator+=(const BigInt& other) {
        if (storage_type != TYPE_LARGE && other.storage_type != TYPE_LARGE) {
            int128_t a = get_small_value();
            int128_t b = other.get_small_value();
            
            constexpr int128_t MAX_I128 = (static_cast<int128_t>(1) << 126);
            constexpr int128_t MIN_I128 = -(static_cast<int128_t>(1) << 126);
            
            bool will_overflow = false;
            if (b > 0 && a > MAX_I128 - b) will_overflow = true;
            if (b < 0 && a < MIN_I128 - b) will_overflow = true;
            
            if (will_overflow) {
                convert_to_large();
                BigInt other_copy = other;
                other_copy.convert_to_large();
                add_large(other_copy.large_rep);
            } else {
                int128_t result = a + b;
                if (fixed_type && !fits_in_current_type(result)) {
                    // Overflow in fixed type, need to upgrade
                    convert_to_large();
                    BigInt other_copy = other;
                    other_copy.convert_to_large();
                    add_large(other_copy.large_rep);
                } else {
                    set_value_respecting_type(result);
                }
            }
        } else {
            convert_to_large();
            BigInt other_copy = other;
            other_copy.convert_to_large();
            add_large(other_copy.large_rep);
            try_downgrade();
        }
        return *this;
    }
    
    BigInt operator+(const BigInt& other) const {
        BigInt result = *this;
        result += other;
        return result;
    }
    
    BigInt& operator-=(const BigInt& other) {
        if (storage_type != TYPE_LARGE && other.storage_type != TYPE_LARGE) {
            int128_t a = get_small_value();
            int128_t b = other.get_small_value();
            
            constexpr int128_t MAX_I128 = (static_cast<int128_t>(1) << 126);
            constexpr int128_t MIN_I128 = -(static_cast<int128_t>(1) << 126);
            
            bool will_overflow = false;
            if (b < 0 && a > MAX_I128 + b) will_overflow = true;
            if (b > 0 && a < MIN_I128 + b) will_overflow = true;
            
            if (will_overflow) {
                convert_to_large();
                BigInt other_copy = other;
                other_copy.convert_to_large();
                subtract_large(other_copy.large_rep);
            } else {
                int128_t result = a - b;
                if (fixed_type && !fits_in_current_type(result)) {
                    convert_to_large();
                    BigInt other_copy = other;
                    other_copy.convert_to_large();
                    subtract_large(other_copy.large_rep);
                } else {
                    set_value_respecting_type(result);
                }
            }
        } else {
            convert_to_large();
            BigInt other_copy = other;
            other_copy.convert_to_large();
            subtract_large(other_copy.large_rep);
            try_downgrade();
        }
        return *this;
    }
    
    BigInt operator-(const BigInt& other) const {
        BigInt result = *this;
        result -= other;
        return result;
    }
    
    BigInt& operator*=(const BigInt& other) {
        if (storage_type != TYPE_LARGE && other.storage_type != TYPE_LARGE) {
            int128_t a = get_small_value();
            int128_t b = other.get_small_value();
            
            if (a != 0 && b != 0) {
                int128_t result = a * b;
                if (result / a != b) {
                    convert_to_large();
                    BigInt other_copy = other;
                    other_copy.convert_to_large();
                    multiply_large(other_copy.large_rep);
                } else if (fixed_type && !fits_in_current_type(result)) {
                    convert_to_large();
                    BigInt other_copy = other;
                    other_copy.convert_to_large();
                    multiply_large(other_copy.large_rep);
                } else {
                    set_value_respecting_type(result);
                }
            } else {
                set_value_respecting_type(0);
            }
        } else {
            convert_to_large();
            BigInt other_copy = other;
            other_copy.convert_to_large();
            multiply_large(other_copy.large_rep);
            try_downgrade();
        }
        return *this;
    }
    
    BigInt operator*(const BigInt& other) const {
        BigInt result = *this;
        result *= other;
        return result;
    }

    // String conversion
    std::string to_string() const {
        if (storage_type != TYPE_LARGE) {
            int128_t value = get_small_value();
            if (value == 0) return "0";
            
            bool negative = value < 0;
            if (negative) value = -value;
            
            char buffer[64];
            char* p = buffer + sizeof(buffer) - 1;
            *p = '\0';
            
            while (value > 0) {
                *--p = '0' + (value % 10);
                value /= 10;
            }
            
            if (negative) *--p = '-';
            return std::string(p);
        } else {
            return to_string_large();
        }
    }

private:
    // String parsing
    void from_string(const std::string& s) {
        if (s.empty()) return;
        
        const char* p = s.c_str();
        bool negative = false;
        
        if (*p == '-') {
            negative = true;
            p++;
        } else if (*p == '+') {
            p++;
        }
        
        if (!*p || !isdigit(*p)) return;
        
        if (try_small_rep(p, negative)) {
            return;
        }
        
        parse_large_rep(s.c_str(), negative);
    }

    bool try_small_rep(const char* p, bool negative) {
        int128_t value = 0;
        constexpr int128_t MAX_I128 = (static_cast<int128_t>(1) << 126);
        
        while (isdigit(*p)) {
            int digit = *p - '0';
            
            if (value > MAX_I128 / 10) {
                return false;
            }
            
            value = value * 10;
            
            if (value > MAX_I128 - digit) {
                return false;
            }
            
            value += digit;
            p++;
        }
        
        set_small_value(negative ? -value : value);
        return true;
    }

    void parse_large_rep(const char* s, bool negative) {
        destroy_current();
        storage_type = TYPE_LARGE;
        new (&large_rep) LargeRep();
        
        const char* p = s;
        if (*p == '-' || *p == '+') p++;
        
        large_rep.limbs.clear();
        large_rep.limbs.push_back(0);
        large_rep.is_negative = negative;
        
        while (isdigit(*p)) {
            int digit = *p - '0';
            
            uint64_t carry = digit;
            for (size_t i = 0; i < large_rep.limbs.size(); i++) {
                uint128_t prod = static_cast<uint128_t>(large_rep.limbs[i]) * 10 + carry;
                large_rep.limbs[i] = static_cast<uint64_t>(prod);
                carry = static_cast<uint64_t>(prod >> 64);
            }
            
            if (carry > 0) {
                large_rep.limbs.push_back(carry);
            }
            
            p++;
        }
        
        normalize_large();
        try_downgrade();
    }

    // Large number operations
    void add_large(const LargeRep& other) {
        if (large_rep.is_negative == other.is_negative) {
            add_magnitude(other.limbs);
        } else {
            if (compare_magnitude(other.limbs) >= 0) {
                subtract_magnitude(other.limbs);
            } else {
                LargeRep temp = other;
                std::swap(large_rep.limbs, temp.limbs);
                large_rep.is_negative = other.is_negative;
                subtract_magnitude(temp.limbs);
            }
        }
        normalize_large();
    }
    
    void subtract_large(const LargeRep& other) {
        LargeRep negated = other;
        negated.is_negative = !negated.is_negative;
        add_large(negated);
    }
    
    void multiply_large(const LargeRep& other) {
        std::vector<uint64_t> result(large_rep.limbs.size() + other.limbs.size(), 0);
        
        for (size_t i = 0; i < large_rep.limbs.size(); i++) {
            uint64_t carry = 0;
            for (size_t j = 0; j < other.limbs.size(); j++) {
                uint128_t prod = static_cast<uint128_t>(large_rep.limbs[i]) * other.limbs[j];
                prod += result[i + j] + carry;
                result[i + j] = static_cast<uint64_t>(prod);
                carry = static_cast<uint64_t>(prod >> 64);
            }
            if (carry > 0) {
                result[i + other.limbs.size()] += carry;
            }
        }
        
        large_rep.limbs = result;
        large_rep.is_negative = (large_rep.is_negative != other.is_negative);
        normalize_large();
    }

    void add_magnitude(const std::vector<uint64_t>& other) {
        size_t max_size = std::max(large_rep.limbs.size(), other.size());
        large_rep.limbs.resize(max_size, 0);
        
        uint64_t carry = 0;
        for (size_t i = 0; i < max_size; i++) {
            uint128_t sum = static_cast<uint128_t>(large_rep.limbs[i]) + carry;
            if (i < other.size()) {
                sum += other[i];
            }
            large_rep.limbs[i] = static_cast<uint64_t>(sum);
            carry = static_cast<uint64_t>(sum >> 64);
        }
        
        if (carry > 0) {
            large_rep.limbs.push_back(carry);
        }
    }
    
    void subtract_magnitude(const std::vector<uint64_t>& other) {
        int64_t borrow = 0;
        for (size_t i = 0; i < large_rep.limbs.size(); i++) {
            int128_t diff = static_cast<int128_t>(large_rep.limbs[i]) - borrow;
            if (i < other.size()) {
                diff -= other[i];
            }
            
            if (diff < 0) {
                diff += (static_cast<int128_t>(1) << 64);
                borrow = 1;
            } else {
                borrow = 0;
            }
            
            large_rep.limbs[i] = static_cast<uint64_t>(diff);
        }
    }
    
    int compare_magnitude(const std::vector<uint64_t>& other) const {
        if (large_rep.limbs.size() != other.size()) {
            return large_rep.limbs.size() > other.size() ? 1 : -1;
        }
        
        for (int i = large_rep.limbs.size() - 1; i >= 0; i--) {
            if (large_rep.limbs[i] != other[i]) {
                return large_rep.limbs[i] > other[i] ? 1 : -1;
            }
        }
        
        return 0;
    }

    std::string to_string_large() const {
        if (large_rep.limbs.empty() || (large_rep.limbs.size() == 1 && large_rep.limbs[0] == 0)) {
            return "0";
        }
        
        std::vector<uint64_t> temp = large_rep.limbs;
        std::string result;
        
        while (temp.size() > 1 || temp[0] > 0) {
            uint64_t remainder = 0;
            for (int i = temp.size() - 1; i >= 0; i--) {
                uint128_t current = (static_cast<uint128_t>(remainder) << 64) | temp[i];
                temp[i] = static_cast<uint64_t>(current / 10);
                remainder = static_cast<uint64_t>(current % 10);
            }
            
            result.push_back('0' + remainder);
            
            while (temp.size() > 1 && temp.back() == 0) {
                temp.pop_back();
            }
        }
        
        if (large_rep.is_negative && result != "0") {
            result.push_back('-');
        }
        
        std::reverse(result.begin(), result.end());
        return result;
    }
};

// Example usage
// int main() {
//     std::cout << "=== Fixed Type Mode ===\n\n";
    
//     // Create fixed i32 values
//     BigInt a = BigInt::i32(100);
//     BigInt b = BigInt::i32(50);
//     std::cout << "a = " << a.to_string() << " | Storage: " << a.get_type() << "\n";
//     std::cout << "b = " << b.to_string() << " | Storage: " << b.get_type() << "\n";
    
//     BigInt c = a - b;  // Result stays i32 (50)
//     std::cout << "a - b = " << c.to_string() << " | Storage: " << c.get_type() << "\n";
    
//     BigInt d = c * BigInt::i32(2);  // Still i32 (100)
//     std::cout << "c * 2 = " << d.to_string() << " | Storage: " << d.get_type() << "\n";
    
//     // Overflow forces upgrade
//     std::cout << "\n=== Overflow in Fixed Type ===\n";
//     BigInt e = BigInt::i8(100);
//     BigInt f = BigInt::i8(50);
//     std::cout << "e = " << e.to_string() << " | Storage: " << e.get_type() << "\n";
//     std::cout << "f = " << f.to_string() << " | Storage: " << f.get_type() << "\n";
    
//     BigInt g = e + f;  // 150, exceeds i8, upgrades
//     std::cout << "e + f = " << g.to_string() << " | Storage: " << g.get_type() << "\n";
    
//     // Automatic mode (default)
//     std::cout << "\n=== Automatic Type Mode ===\n";
//     BigInt x(1000);
//     BigInt y(900);
//     std::cout << "x = " << x.to_string() << " | Storage: " << x.get_type() << "\n";
//     std::cout << "y = " << y.to_string() << " | Storage: " << y.get_type() << "\n";
    
//     BigInt z = x - y;  // Result is 100, downgrades to u8
//     std::cout << "x - y = " << z.to_string() << " | Storage: " << z.get_type() << "\n";
    
//     // Mixed fixed and auto
//     std::cout << "\n=== Mixed Mode Operations ===\n";
//     BigInt fixed_val = BigInt::u32(1000);
//     BigInt auto_val(50);
//     std::cout << "fixed_val = " << fixed_val.to_string() << " | Storage: " << fixed_val.get_type() << "\n";
//     std::cout << "auto_val = " << auto_val.to_string() << " | Storage: " << auto_val.get_type() << "\n";
    
//     BigInt mixed = fixed_val + auto_val;
//     std::cout << "fixed + auto = " << mixed.to_string() << " | Storage: " << mixed.get_type() << "\n";
    
//     // Fixed 128-bit operations
//     std::cout << "\n=== Fixed 128-bit Type ===\n";
//     BigInt big128 = BigInt::i128("12345678901234567890");
//     std::cout << "big128 = " << big128.to_string() << " | Storage: " << big128.get_type() << "\n";
    
//     BigInt big128_2 = BigInt::i128(static_cast<int128_t>(1000000000000LL));
//     std::cout << "big128_2 = " << big128_2.to_string() << " | Storage: " << big128_2.get_type() << "\n";
    
//     BigInt sum128 = big128 + big128_2;
//     std::cout << "big128 + big128_2 = " << sum128.to_string() << " | Storage: " << sum128.get_type() << "\n";
    
//     // Fixed large (arbitrary precision)
//     std::cout << "\n=== Fixed Large (Arbitrary Precision) ===\n";
//     BigInt huge1 = BigInt::large("999999999999999999999999999999999999999999");
//     BigInt huge2 = BigInt::large("111111111111111111111111111111111111111111");
//     std::cout << "huge1 = " << huge1.to_string() << " | Storage: " << huge1.get_type() << "\n";
//     std::cout << "huge2 = " << huge2.to_string() << " | Storage: " << huge2.get_type() << "\n";
    
//     BigInt huge_sum = huge1 + huge2;
//     std::cout << "huge1 + huge2 = " << huge_sum.to_string() << " | Storage: " << huge_sum.get_type() << "\n";
    
//     // Demonstrate type preservation
//     std::cout << "\n=== Type Preservation Demo ===\n";
//     BigInt large_val = BigInt::large(1000);
//     std::cout << "large_val (initially 1000) = " << large_val.to_string() << " | Storage: " << large_val.get_type() << "\n";
    
//     BigInt large_result = large_val - BigInt::large(500);
//     std::cout << "large_val - 500 = " << large_result.to_string() << " | Storage: " << large_result.get_type() << "\n";
//     // std::cout << "  ^ Stays
    
//     return 0;
//     }

#endif // BIG_INT_H
