#include <iostream>
#include "PalBox.h"
#include <vector>
#include <utility>

PalBox::PalBox(size_t capacity)
    : capacity_(capacity) {
    pals_.reserve(capacity_);}

// getters for the box
size_t PalBox::size() const {return pals_.size();}
size_t PalBox::capacity() const {return capacity_;}

bool PalBox::isFull() const {if(pals_.size() >= capacity_) {return true;}}

// making changes to the box
bool PalBox::add(std::unique_ptr<PocketPal>&& pal) {
    if(isFull()) {return false;}
    pals_.push_back(std::move(pal));
    return true;
}

std::unique_ptr<PocketPal> PalBox::remove(size_t i) {
    if(i > size()) {return nullptr;}
    // temp var
    std::unique_ptr<PocketPal> removed = std::move(pals_[i]);
    
    pals_.erase(pals_.begin() + i);
    return removed;
}

PocketPal& PalBox:: at(size_t i) {
    if (i >= size()) {throw std::out_of_range("PallBox at index is invalid");}
    return *pals_[i];
}

const PocketPal& PalBox:: at(size_t i) const {
    if (i >= size()) {throw std::out_of_range("PallBox at index is invalid");}
    return *pals_[i];
}

// trading Pals
bool PalBox::swapWith(size_t i, PalBox& other, size_t j) {
    if (i >= size() || j >= other.size()) {return false;}
    pals_[i].swap(other.pals_[j]);
    return true;
}