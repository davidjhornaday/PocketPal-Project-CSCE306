// CSCE 306
// Prof. Kim

#ifndef PALBOX_H
#define PALBOX_H

#include <cstddef>   // size_t
#include <memory>    // std::unique_ptr
#include <utility>   // std::move
#include <vector>
#include "PocketPal.h"

// A fixed-capacity box that OWNS its PocketPals (use of unique_ptr).
// Each pal lives on the heap behind a unique_ptr, so ownership is always
// clear and whatever is left in the box is freed automatically.
class PalBox {
    std::vector<std::unique_ptr<PocketPal>> pals_;    // with vector use: we don't need to keep track of how many are actually in the array
    size_t capacity_;  // how many PocketPals is ALLOWEd to be held in this box


public:
    explicit PalBox(size_t capacity);

    // Move-only: two boxes must never own the same PocketPal.
    PalBox(const PalBox&) = delete;            
    PalBox& operator=(const PalBox&) = delete;
    PalBox(PalBox&&) noexcept = default;
    PalBox& operator=(PalBox&&) noexcept = default;
    ~PalBox() = default;

    size_t size() const;
    size_t capacity() const;
    bool isFull() const;

    bool add(std::unique_ptr<PocketPal>&& pal);   // takes ownership ONLY on success;
                                                  // false if full or nullptr (pal untouched)
    std::unique_ptr<PocketPal> remove(size_t i);  // caller takes ownership; nullptr if i is invalid

    PocketPal& at(size_t i);                      // throws std::out_of_range if i is invalid
    const PocketPal& at(size_t i) const;          // throws std::out_of_range if i is invalid

    // Exchanges this box's pal at i with other's pal at j.
    // False (nothing changes) if either index is invalid.
    bool swapWith(size_t i, PalBox& other, size_t j);
};

#endif // PALBOX_H