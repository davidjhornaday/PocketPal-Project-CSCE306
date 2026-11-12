// CSCE 306
// Prof. Kim
// 11-02-2026

#ifndef POCKETPAL_H
#define POCKETPAL_H

#include <string>
#include "Wallet.h"

enum class Habitat { Water, Land, Air, ManMade };

std::string habitatName(Habitat h);

// A collectible creature.
// Invariants:
//   - name is never empty
//   - level stays in 1..100
//   - each stat stays in 1..100
//   - hp stays in a range 0 <= hp <= hp_max
// lifetime earnings can decrease and go negative

class PocketPal {
public:
    // [What does static do?]
    // [What does constexpr do?]
    static constexpr int kMinLevel = 1;     
    static constexpr int kMaxLevel = 100;
    static constexpr int kMinStat  = 1;
    static constexpr int kMaxStat  = 100;
    static constexpr int kMinHp    = 1;      // min of max (not min during game play)
    static constexpr int kMaxStartHp = 11;   // highest max HP at creation
    static constexpr int kHpPerLevel = 1;    // max HP gained on each level up
    static constexpr int kMaxHp = kMaxStartHp + (kMaxLevel - kMinLevel) * kHpPerLevel;  // = 110    
    


private:
    std::string name_;
    Habitat habitat_;
    Wallet wallet_;
    int hp_;         // hitpoints
    int hp_max_;     // max hitpoints
    int level_;      // invariant: 1..100; controls maxhp and how much max attack (bet) it can do
    int luck_;       // bonus 1..100  ex. dice rolls, number draws, etc
    int cunning_;    // bonus 1..100  ex. card draws, item draws, etc
    int reflex_;     // hand-eye bonus 1..100  ex. dart, slot, etc
    int earnings_;   // life time earnings so far.  IT CAN BE negative.

    static int clampStat(int s);
    static int clampHpMax(int h);
    static int clampStartHp(int h); 

public:
    PocketPal(std::string name, Habitat h, int hp_max, int luck, int cunning, int reflex);

    const std::string& name() const;
    Habitat habitat() const;
    int level() const;
    int hp() const;
    int hpMax() const;
    int luck() const;
    int cunning() const;
    int reflex() const;
    int earnings() const;

    void levelUp();                  // enforces cap; raises max HP
    void takeDamage(int amount);     // hp never drops below 0; ignores amounts <= 0
    void heal(int amount);           // hp never exceeds hp_max; ignores amounts <= 0
    bool isKnockedOut() const;       // true when hp is 0    

    bool pay(int amount);            // take coin from pal's wallet
    void receive(int amount);        // add coin to pal's wallet
    int coins() const;               // see how much coin it pas

    int value() const;               // derived from level stats 
};

#endif
