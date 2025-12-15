#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <cstring>
#include <cstddef>
#include "memory.hh"  // Your region-based memory allocator

struct limitly_string_builder {
    char* buffer;           // Pointer to the allocated buffer
    size_t capacity;        // Total allocated capacity
    size_t length;          // Current used length
    MemoryManager<>::Region* region;   // Memory region for allocation

    // Initialize builder with a memory region
    void init(MemoryManager<>::Region* reg, size_t initialCapacity = 128) {
        region = reg;
        capacity = initialCapacity;
        length = 0;
        // Access the manager through the region - need to add a getManager method or make manager public
        // For now, let's use a simpler approach with malloc
        buffer = (char*)malloc(capacity);
        if (!buffer) {
            // handle allocation failure
            capacity = 0;
        }
        buffer[0] = '\0';
    }

    // Ensure buffer has enough space
    void ensure_capacity(size_t additional) {
        if (length + additional + 1 > capacity) {
            size_t newCapacity = capacity * 2;
            while (length + additional + 1 > newCapacity)
                newCapacity *= 2;

            char* newBuffer = (char*)malloc(newCapacity);
            if (!newBuffer) return; // allocation failed

            std::memcpy(newBuffer, buffer, length);
            free(buffer); // Free old buffer
            buffer = newBuffer;
            capacity = newCapacity;
        }
    }

    // Append raw C-string
    void append(const char* str) {
        size_t n = std::strlen(str);
        ensure_capacity(n);
        std::memcpy(buffer + length, str, n);
        length += n;
        buffer[length] = '\0';
    }

    // Append a single character
    void append(char c) {
        ensure_capacity(1);
        buffer[length++] = c;
        buffer[length] = '\0';
    }

    // Append integer
    void append(int value) {
        char temp[32];
        int n = std::snprintf(temp, sizeof(temp), "%d", value);
        if (n > 0) append(temp);
    }

    // Append size_t
    void append(size_t value) {
        char temp[32];
        int n = std::snprintf(temp, sizeof(temp), "%zu", value);
        if (n > 0) append(temp);
    }

    // Append float/double
    void append(double value) {
        char temp[64];
        int n = std::snprintf(temp, sizeof(temp), "%g", value);
        if (n > 0) append(temp);
    }

    // Reset builder (does not free memory, can reuse)
    void clear() {
        length = 0;
        if (buffer) buffer[0] = '\0';
    }

    // Get final C-string
    char* c_str() {
        return buffer;
    }

    // Get current length
    size_t size() const {
        return length;
    }
};

#endif // STRING_BUILDER_H
