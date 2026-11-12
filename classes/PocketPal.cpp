// 11-02-2026
// David Hornaday

#include <iostream>
#include <utility>
#include "PocketPal.h"

std::string habitatName(Habitat h) {
    switch (h) {
        case Habitat::Water: return "Water";
        case Habitat::Land: return "Land";
        case Habitat::Air: return "Air";
        case Habitat::ManMade: return "Man-made";
    }
    return "Unknown";
}

int PocketPal::clampStat(int s) {
    if (s < kMinStat) return kMinStat;
    if (s > kMaxStat) return kMaxStat;
    return s;
}

int PocketPal::clampHpMax(int h) {
    if (h < kMinHp) return kMinHp;
    if (h > kMaxHp) return kMaxHp;
    return h;
}

int PocketPal::clampStartHp(int h) {
    if (h < kMinHp) return kMinHp;
    if (h > kMaxStartHp) return kMaxStartHp;
    return h;
}

PocketPal::PocketPal(std::string name, Habitat h, int hp_max, int luck, int cunning, int reflex)
    : name_(name.empty() ? "Unnamed" : std::move(name)),
    habitat_(h),
    wallet_(0),
    hp_(clampStartHp(hp_max)),
    hp_max_(clampStartHp(hp_max)),
    level_(kMinLevel),
    luck_(clampStat(luck)),
    cunning_(clampStat(cunning)),
    reflex_(clampStat(reflex)),
    earnings_(0) {}

//getters
const std::string& PocketPal::name() const {return name_;}
Habitat PocketPal::habitat() const {return habitat_;}

int PocketPal::level() const {return level_;}
int PocketPal::hp() const {return hp_;}
int PocketPal::hpMax() const {return hp_max_;}
int PocketPal::luck() const {return luck_;}
int PocketPal::cunning() const {return cunning_;}
int PocketPal::reflex() const {return reflex_;}
int PocketPal::earnings() const {return earnings_;}

// pal methods
void PocketPal::levelUp() {
    if(level_ < kMaxLevel) 
    {level_ ++, hp_max_ += kHpPerLevel;}
}

void PocketPal::takeDamage(int amount) {
    if (amount > 0) { 
        if (amount > hp_) {amount = hp_;}
    hp_ -= amount;
    }
}

void PocketPal::heal(int amount) {
    if(amount < 0) {amount = 0;}
    hp_ += amount;
    if(hp_ >= hp_max_) {hp_ = hp_max_;}

    if(isKnockedOut()) {hp_ = amount;}
}

bool PocketPal::isKnockedOut() const {return hp_ <= 0 ;}

// wallet related methods
bool PocketPal::pay(int amount) {
    if (wallet_.withdraw(amount)) {
    earnings_ -= amount;
    return true; 
    }
    return false;
}

void PocketPal::receive(int amount) {
    if (amount >= 0) {
        wallet_.deposit(amount), 
        earnings_ += amount;
    }
}

// getter method coins from the wallet
int PocketPal::coins() const {return wallet_.balance();}

// custom value calulation that uses all attributes with an emphasis on level
// could not find a match for test1 value calulations
int PocketPal::value() const {return (level_ * 5) + luck_ + cunning_ + reflex_;}