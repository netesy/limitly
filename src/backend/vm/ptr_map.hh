#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

// Open-addressing tables for pointer-sized keys, used by the VM ownership
// hot path (allocation tracking, promotion, reclamation). Unlike
// std::unordered_map they store entries inline in a flat array: no per-node
// allocation and far fewer cache misses per probe.
//
// Keys are real object pointers (>= 16 byte aligned); 0 is the empty
// sentinel and is never a valid key for these tables.

template <typename V>
class PtrMap {
public:
    struct Entry {
        uintptr_t first;
        V second;
    };

    class const_iterator;
    class iterator {
        Entry* cur_ = nullptr;
        Entry* end_ = nullptr;
        void skip_empty() { while (cur_ != end_ && cur_->first == 0) ++cur_; }
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Entry;
        using difference_type = std::ptrdiff_t;
        using pointer = Entry*;
        using reference = Entry&;
        iterator() = default;
        iterator(Entry* cur, Entry* end) : cur_(cur), end_(end) { skip_empty(); }
        reference operator*() const { return *cur_; }
        pointer operator->() const { return cur_; }
        iterator& operator++() { ++cur_; skip_empty(); return *this; }
        iterator operator++(int) { iterator t = *this; ++(*this); return t; }
        bool operator==(const iterator& o) const { return cur_ == o.cur_; }
        bool operator!=(const iterator& o) const { return cur_ != o.cur_; }
        friend class const_iterator;
    };
    class const_iterator {
        const Entry* cur_ = nullptr;
        const Entry* end_ = nullptr;
        void skip_empty() { while (cur_ != end_ && cur_->first == 0) ++cur_; }
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Entry;
        using difference_type = std::ptrdiff_t;
        using pointer = const Entry*;
        using reference = const Entry&;
        const_iterator() = default;
        const_iterator(const Entry* cur, const Entry* end) : cur_(cur), end_(end) { skip_empty(); }
        const_iterator(const iterator& it) : cur_(it.cur_), end_(it.end_) {}
        reference operator*() const { return *cur_; }
        pointer operator->() const { return cur_; }
        const_iterator& operator++() { ++cur_; skip_empty(); return *this; }
        const_iterator operator++(int) { const_iterator t = *this; ++(*this); return t; }
        bool operator==(const const_iterator& o) const { return cur_ == o.cur_; }
        bool operator!=(const const_iterator& o) const { return cur_ != o.cur_; }
    };

    PtrMap() = default;
    ~PtrMap() { std::free(slots_); }
    PtrMap(const PtrMap& o) { copy_from(o); }
    PtrMap& operator=(const PtrMap& o) { if (this != &o) { clear_storage(); copy_from(o); } return *this; }
    PtrMap(PtrMap&& o) noexcept { steal(o); }
    PtrMap& operator=(PtrMap&& o) noexcept { if (this != &o) { clear_storage(); steal(o); } return *this; }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    void clear() {
        if (slots_) std::memset(slots_, 0, cap_ * sizeof(Entry));
        size_ = 0;
    }

    iterator begin() { return iterator(slots_, slots_ + cap_); }
    iterator end() { return iterator(slots_ + cap_, slots_ + cap_); }
    const_iterator begin() const { return const_iterator(slots_, slots_ + cap_); }
    const_iterator end() const { return const_iterator(slots_ + cap_, slots_ + cap_); }

    iterator find(uintptr_t key) {
        if (!slots_) return end();
        size_t i = home(key);
        while (slots_[i].first) {
            if (slots_[i].first == key) return iterator(&slots_[i], slots_ + cap_);
            i = (i + 1) & mask_;
        }
        return end();
    }
    const_iterator find(uintptr_t key) const {
        if (!slots_) return end();
        size_t i = home(key);
        while (slots_[i].first) {
            if (slots_[i].first == key) return const_iterator(&slots_[i], slots_ + cap_);
            i = (i + 1) & mask_;
        }
        return end();
    }
    size_t count(uintptr_t key) const { return find(key) != end() ? 1 : 0; }

    V& at(uintptr_t key) {
        auto it = find(key);
        if (it == end()) throw std::out_of_range("PtrMap::at");
        return it->second;
    }
    const V& at(uintptr_t key) const {
        auto it = find(key);
        if (it == end()) throw std::out_of_range("PtrMap::at");
        return it->second;
    }

    V& operator[](uintptr_t key) {
        if (!slots_) grow(8);
        else if ((size_ + 1) * 4 > cap_ * 3) grow(cap_ * 2);
        size_t i = home(key);
        while (slots_[i].first) {
            if (slots_[i].first == key) return slots_[i].second;
            i = (i + 1) & mask_;
        }
        slots_[i].first = key;
        slots_[i].second = V();
        ++size_;
        return slots_[i].second;
    }

    // Insert only when absent; returns {iterator, inserted}.
    std::pair<iterator, bool> emplace(uintptr_t key, const V& value) {
        if (!slots_) grow(8);
        else if ((size_ + 1) * 4 > cap_ * 3) grow(cap_ * 2);
        size_t i = home(key);
        while (slots_[i].first) {
            if (slots_[i].first == key) return {iterator(&slots_[i], slots_ + cap_), false};
            i = (i + 1) & mask_;
        }
        slots_[i].first = key;
        slots_[i].second = value;
        ++size_;
        return {iterator(&slots_[i], slots_ + cap_), true};
    }
    std::pair<iterator, bool> insert(const Entry& entry) { return emplace(entry.first, entry.second); }

    size_t erase(uintptr_t key) {
        auto it = find(key);
        if (it == end()) return 0;
        erase(it);
        return 1;
    }
    iterator erase(iterator pos) {
        if (pos == end()) return end();
        erase_slot(const_cast<Entry*>(&*pos));
        return pos;
    }
    const_iterator erase(const_iterator pos) {
        if (pos == end()) return end();
        erase_slot(const_cast<Entry*>(&*pos));
        return pos;
    }

private:
    Entry* slots_ = nullptr;
    size_t cap_ = 0, mask_ = 0, shift_ = 0, size_ = 0;

    size_t home(uintptr_t key) const {
        return static_cast<size_t>((key * 0x9E3779B97F4A7C15ULL) >> shift_);
    }
    void erase_slot(Entry* victim) {
        // Backward-shift deletion keeps probe chains intact without tombstones.
        size_t i = static_cast<size_t>(victim - slots_);
        size_t j = i;
        for (;;) {
            j = (j + 1) & mask_;
            if (!slots_[j].first) break;
            size_t home_j = home(slots_[j].first);
            // Move slots_[j] into the gap at i when its probe chain passes i.
            if ((i < j) ? (home_j <= i || home_j > j) : (home_j <= i && home_j > j)) {
                slots_[i] = slots_[j];
                i = j;
            }
        }
        slots_[i].first = 0;
        slots_[i].second = V();
        --size_;
    }
    void clear_storage() {
        std::free(slots_);
        slots_ = nullptr; cap_ = mask_ = shift_ = size_ = 0;
    }
    void steal(PtrMap& o) {
        slots_ = o.slots_; cap_ = o.cap_; mask_ = o.mask_; shift_ = o.shift_; size_ = o.size_;
        o.slots_ = nullptr; o.cap_ = o.mask_ = o.shift_ = o.size_ = 0;
    }
    void copy_from(const PtrMap& o) {
        for (const auto& e : o) emplace(e.first, e.second);
    }
    void grow(size_t new_cap) {
        Entry* old = slots_;
        size_t old_cap = cap_;
        slots_ = static_cast<Entry*>(std::calloc(new_cap, sizeof(Entry)));
        if (!slots_) throw std::bad_alloc();
        cap_ = new_cap; mask_ = cap_ - 1;
        shift_ = 64 - __builtin_ctzll(static_cast<unsigned long long>(cap_));
        size_ = 0;
        if (old) {
            for (size_t i = 0; i < old_cap; ++i) {
                if (!old[i].first) continue;
                size_t j = home(old[i].first);
                while (slots_[j].first) j = (j + 1) & mask_;
                slots_[j] = old[i];
                ++size_;
            }
            std::free(old);
        }
    }
};

class PtrSet {
public:
    class const_iterator;
    class iterator {
        uintptr_t* cur_ = nullptr;
        uintptr_t* end_ = nullptr;
        void skip_empty() { while (cur_ != end_ && *cur_ == 0) ++cur_; }
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = uintptr_t;
        using difference_type = std::ptrdiff_t;
        using pointer = uintptr_t*;
        using reference = uintptr_t&;
        iterator() = default;
        iterator(uintptr_t* cur, uintptr_t* end) : cur_(cur), end_(end) { skip_empty(); }
        reference operator*() const { return *cur_; }
        pointer operator->() const { return cur_; }
        iterator& operator++() { ++cur_; skip_empty(); return *this; }
        iterator operator++(int) { iterator t = *this; ++(*this); return t; }
        bool operator==(const iterator& o) const { return cur_ == o.cur_; }
        bool operator!=(const iterator& o) const { return cur_ != o.cur_; }
        friend class const_iterator;
    };
    class const_iterator {
        const uintptr_t* cur_ = nullptr;
        const uintptr_t* end_ = nullptr;
        void skip_empty() { while (cur_ != end_ && *cur_ == 0) ++cur_; }
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = uintptr_t;
        using difference_type = std::ptrdiff_t;
        using pointer = const uintptr_t*;
        using reference = const uintptr_t&;
        const_iterator() = default;
        const_iterator(const uintptr_t* cur, const uintptr_t* end) : cur_(cur), end_(end) { skip_empty(); }
        const_iterator(const iterator& it) : cur_(it.cur_), end_(it.end_) {}
        reference operator*() const { return *cur_; }
        pointer operator->() const { return cur_; }
        const_iterator& operator++() { ++cur_; skip_empty(); return *this; }
        const_iterator operator++(int) { const_iterator t = *this; ++(*this); return t; }
        bool operator==(const const_iterator& o) const { return cur_ == o.cur_; }
        bool operator!=(const const_iterator& o) const { return cur_ != o.cur_; }
    };

    PtrSet() = default;
    ~PtrSet() { std::free(slots_); }
    PtrSet(const PtrSet& o) { copy_from(o); }
    PtrSet& operator=(const PtrSet& o) { if (this != &o) { std::free(slots_); slots_ = nullptr; cap_ = mask_ = shift_ = size_ = 0; copy_from(o); } return *this; }
    PtrSet(PtrSet&& o) noexcept { steal(o); }
    PtrSet& operator=(PtrSet&& o) noexcept { if (this != &o) { std::free(slots_); steal(o); } return *this; }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    size_t capacity() const { return cap_; }
    void clear() {
        if (slots_) std::memset(slots_, 0, cap_ * sizeof(uintptr_t));
        size_ = 0;
    }

    iterator begin() { return iterator(slots_, slots_ + cap_); }
    iterator end() { return iterator(slots_ + cap_, slots_ + cap_); }
    const_iterator begin() const { return const_iterator(slots_, slots_ + cap_); }
    const_iterator end() const { return const_iterator(slots_ + cap_, slots_ + cap_); }

    bool contains(uintptr_t key) const {
        if (!slots_) return false;
        size_t i = home(key);
        while (slots_[i]) {
            if (slots_[i] == key) return true;
            i = (i + 1) & mask_;
        }
        return false;
    }
    size_t count(uintptr_t key) const { return contains(key) ? 1 : 0; }

    std::pair<iterator, bool> insert(uintptr_t key) {
        if (key == 0) return {end(), false};
        if (!slots_) grow(8);
        else if ((size_ + 1) * 4 > cap_ * 3) grow(cap_ * 2);
        size_t i = home(key);
        while (slots_[i]) {
            if (slots_[i] == key) return {iterator(&slots_[i], slots_ + cap_), false};
            i = (i + 1) & mask_;
        }
        slots_[i] = key;
        ++size_;
        return {iterator(&slots_[i], slots_ + cap_), true};
    }
    size_t erase(uintptr_t key) {
        if (!slots_) return 0;
        size_t i = home(key);
        while (slots_[i]) {
            if (slots_[i] == key) {
                // Backward-shift deletion.
                size_t j = i;
                for (;;) {
                    j = (j + 1) & mask_;
                    if (!slots_[j]) break;
                    size_t home_j = home(slots_[j]);
                    if ((i < j) ? (home_j <= i || home_j > j) : (home_j <= i && home_j > j)) {
                        slots_[i] = slots_[j];
                        i = j;
                    }
                }
                slots_[i] = 0;
                --size_;
                return 1;
            }
            i = (i + 1) & mask_;
        }
        return 0;
    }

private:
    uintptr_t* slots_ = nullptr;
    size_t cap_ = 0, mask_ = 0, shift_ = 0, size_ = 0;

    size_t home(uintptr_t key) const {
        return static_cast<size_t>((key * 0x9E3779B97F4A7C15ULL) >> shift_);
    }
    void steal(PtrSet& o) {
        slots_ = o.slots_; cap_ = o.cap_; mask_ = o.mask_; shift_ = o.shift_; size_ = o.size_;
        o.slots_ = nullptr; o.cap_ = o.mask_ = o.shift_ = o.size_ = 0;
    }
    void copy_from(const PtrSet& o) {
        for (auto key : o) insert(key);
    }
    void grow(size_t new_cap) {
        uintptr_t* old = slots_;
        size_t old_cap = cap_;
        slots_ = static_cast<uintptr_t*>(std::calloc(new_cap, sizeof(uintptr_t)));
        if (!slots_) throw std::bad_alloc();
        cap_ = new_cap; mask_ = cap_ - 1;
        shift_ = 64 - __builtin_ctzll(static_cast<unsigned long long>(cap_));
        size_ = 0;
        if (old) {
            for (size_t i = 0; i < old_cap; ++i) {
                if (!old[i]) continue;
                size_t j = home(old[i]);
                while (slots_[j]) j = (j + 1) & mask_;
                slots_[j] = old[i];
                ++size_;
            }
            std::free(old);
        }
    }
};

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
