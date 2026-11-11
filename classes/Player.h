// CSCE 306
// Prof. Kim
// 11-02-2026

#ifndef PLAYER_H
#define PLAYER_H

#include <cstddef>
#include <string>

#include "Wallet.h"
#include "PocketPal.h"

// A player with a name, a wallet, and a collection of up to 5 PocketPals.
//
// Ownership rules:
//   - The Player OWNS every pal in its collection and deletes them in its destructor.
//   - addPal() takes ownership of a pal created with new, but ONLY if it returns
//     true. If it returns false (collection full, nullptr, or duplicate), the
//     caller still owns the pal and must delete it or give it to someone else.
//   - removePal() hands ownership back to the caller, who must then delete it
//     or give it to another Player with addPal().
//
// Copying is disabled: two Players holding the same pointers would both
// delete the same pals.
class Player {
public:
    static constexpr std::size_t kMaxPals = 5;   // most pals a player can hold

private:
    std::string name_;
    Wallet wallet_;
    PocketPal* collection_[kMaxPals];   // slots 0..size_-1 hold pals; the rest are nullptr
    std::size_t size_;                  // number of pals in the collection

public:
    explicit Player(std::string name, int startCoins = 100);  // empty name -> "Unnamed"
    ~Player();

    Player(const Player&) = delete;                           // copy constructor 
    Player& operator=(const Player&) = delete;                // copy assigment opperator

    const std::string& name() const;
    Wallet& wallet();                                         // returns the refrence object
    const Wallet& wallet() const;                             // returns the constant wallet refreance

    std::size_t palCount() const;                             // returns num of pocket pals
    bool isFull() const;                            // true when holding kMaxPals pals
    PocketPal* pal(std::size_t index);              // nullptr if out of range; Player keeps ownership
    const PocketPal* pal(std::size_t index) const;  // nullptr if out of range; Player keeps ownership

    bool addPal(PocketPal* p);                 // false if full, nullptr, or duplicate (caller keeps p)
    PocketPal* removePal(std::size_t index);   // caller takes ownership; nullptr if out of range

    friend bool trade(Player& a, std::size_t aIdx, Player& b, std::size_t bIdx);    // allows access to privte player data to other objects
};

// Swaps a's pal at aIdx with b's pal at bIdx; each pal lands in the other's slot.
// Returns false (and changes nothing) if either index is out of range or a and b
// are the same player. A one-for-one swap never changes either player's count,
// so it works even when both collections are full.
bool trade(Player& a, std::size_t aIdx, Player& b, std::size_t bIdx);

#endif