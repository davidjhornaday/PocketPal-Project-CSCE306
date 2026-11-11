//CSCE 306
// David Hornaday
// 11-04-2026

#include <iostream>
#include <utility>
#include "Player.h"

// constructor
// checks the name and if its empty it assigns the name of "Unnamed"
// sets the coin value to zero
// the for loop removes all obj points from the player array
Player::Player(std::string name, int startCoins): name_(name.empty() ? 
"Unnamed":std::move(name)),
wallet_(startCoins), size_(0) {
    for (std::size_t i = 0; i < kMaxPals; i++) {
        collection_[i] = nullptr;}
}

// deconstructor
// a for loop that goes through the aray and deletes the objects
Player::~Player() {
    for(std::size_t i = 0; i < size_; i++) {
        delete collection_[i];
        collection_[i] = nullptr;}
}


//getters
const std::string& Player::name() const {return name_;}
Wallet& Player::wallet() {return wallet_;}
const Wallet& Player::wallet() const {return wallet_;}
std::size_t Player::palCount() const {return size_;}

// methods
bool Player::isFull() const {return size_ == kMaxPals;}

PocketPal* Player::pal(std::size_t index) { 
    if(index >= size_) {return nullptr; }
    return collection_[index];
}

const PocketPal* Player::pal(std::size_t index) const {
    if(index >= size_) {return nullptr;}
    return collection_[index];
}

// Pal managment
bool Player::addPal(PocketPal* pal) {
    if(pal == nullptr || isFull()) {return false;}
    // chechking for dups
    for(std::size_t i = 0; i < size_; i++) {
        if (collection_[i] == pal) {return false;}
    }
    collection_[size_] = pal;
    size_++;
    return true;
}

PocketPal* Player::removePal(std::size_t index ) { 
    if (index >= size_) {return nullptr;}
    // varible to hold pal so it wont get mixed up in the for loop
    PocketPal* palThatGotRemoved = collection_[index];
    // removing the pal at the index and moving every thing back in order
    for (std::size_t i = index; i + 1 < size_; i++) {
        collection_[i] = collection_[i + 1];}
    size_ --;
    collection_[size_] = nullptr;
    return palThatGotRemoved;
}

bool trade(Player& a, std::size_t aIndex, Player& b, std::size_t bIndex) {
    if (&a == &b || aIndex >= a.size_ || bIndex >= b.size_) {return false;}
    // varible to hold the pal so we dont lose it while trading
    PocketPal* p1PreTradePal = a.collection_[aIndex]; 

    a.collection_[aIndex] = b.collection_[bIndex];
    b.collection_[bIndex] = p1PreTradePal;
    return true;
}