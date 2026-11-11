//CSCE 306
// David Hornaday
// 11-02-2026

#include <iostream>
#include "Wallet.h"

// a shortened version of an if else statment
// if the start coins is less than 0 than it sets the value to 0
Wallet::Wallet(int start) : coins_(start < 0 ? 0 : start) {}

int Wallet::balance() const {
    return coins_;
}

void Wallet::deposit(int amount) {
    if (amount <= 0) return;
    coins_ += amount;
}

bool Wallet::withdraw(int amount) {
    if (amount <= 0 || amount > coins_) return false;
    coins_ -= amount;
    return true;
}