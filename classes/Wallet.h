// CSCE 306
// Prof. Kim
// 11-02-2026

#ifndef WALLET_H
#define WALLET_H

// A player's stash of PocketCoins.
// Invariant: the balance is never negative... 
// (unless you want to later implement a credit mechanism to lend/borrow money )
class Wallet {
    int coins_;

public:
    explicit Wallet(int start = 0);   // a negative start should becomes 0

    int balance() const;                // const after the function is a complier constraint, and will not let you compile if values are changed
    void deposit(int amount);           // ignores amounts <= 0
    bool withdraw(int amount);          // false if amount <= 0 or funds are short
};

#endif
