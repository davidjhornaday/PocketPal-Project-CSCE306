// CSCE 306
// Prof. Kim
// this includes code to help you with
// 1. display functions (print)
// 2. creating random PocketPals

#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <utility>

#include "PalBox.h"
#include "Player.h"
#include "PocketPal.h"


constexpr std::size_t kCenterCapacity = 20;   // room for 20...
constexpr std::size_t kStartingPals   = 12;   // ...but create 12 to start
constexpr std::size_t kPalsPerPlayer  = 5;

const std::string kNames[kStartingPals] = { //use some ripoff names 
    "Pikachew",    "Charmandork", "Bulbasnore",  "Squirdle",
    "Jigglypuffy", "Meowthful",   "Psyduct",     "Snorelax",
    "Geodud",      "Eeveeish",    "Gengarlic",   "Onyxious"
};

int randomInt(int lo, int hi) {
    // same pattern we did in previous lecture
    static std::mt19937 engine{std::random_device{}()};
    std::uniform_int_distribution<int> dist(lo, hi); // includes both lo and hi
    return dist(engine);
}

Habitat randomHabitat() {
    switch (randomInt(0, 3)) {
        case 0:  return Habitat::Water;
        case 1:  return Habitat::Land;
        case 2:  return Habitat::Air;
        default: return Habitat::ManMade;  // covers case 3, and keeps the compiler from complaining about
	                                   // unhandle dcases
    }
}

std::unique_ptr<PocketPal> makeRandomPal(const std::string& name) {
    return std::make_unique<PocketPal>(
        name,
        randomHabitat(),
        randomInt(PocketPal::kMinHp,   PocketPal::kMaxStartHp),
        randomInt(PocketPal::kMinStat, PocketPal::kMaxStat),    // luck
        randomInt(PocketPal::kMinStat, PocketPal::kMaxStat),    // cunning
        randomInt(PocketPal::kMinStat, PocketPal::kMaxStat));   // reflex
}

void printPlayer(const Player& player) {
    std::cout << "\n  " << player.name() << " (" << player.palCount()
              << "/" << Player::kMaxPals << " pals)\n"
              << "  " << std::left
              << std::setw(4)  << "#"
              << std::setw(14) << "Name"
              << std::setw(10) << "Habitat"
              << std::right
              << std::setw(5)  << "Lvl"
              << std::setw(9)  << "HP"
              << std::setw(7)  << "Luck"
              << std::setw(9)  << "Cunning"
              << std::setw(8)  << "Reflex" << '\n'
              << "  " << std::string(66, '-') << '\n';

    for (int i = 0; i < player.palCount(); ++i) {
        const PocketPal& p = *player.pal(i);
        std::string hp = std::to_string(p.hp()) + "/" + std::to_string(p.hpMax());
        std::cout << "  " << std::left
                  << std::setw(4)  << i
                  << std::setw(14) << p.name()
                  << std::setw(10) << habitatName(p.habitat())
                  << std::right
                  << std::setw(5)  << p.level()
                  << std::setw(9)  << hp
                  << std::setw(7)  << p.luck()
                  << std::setw(9)  << p.cunning()
                  << std::setw(8)  << p.reflex() << '\n';
    }
}

// Moves pals from the front of the PalBox to the player.
void transferPals(PalBox& pc, Player& player, int count) {
    for (int i = 0; i < count; ++i) {
        std::unique_ptr<PocketPal> pal = pc.remove(0);
        if (!pal) {
            std::cout << "  PalCenter is empty!\n";
            return;
        }
        if (!player.addPal(std::move(pal))) {  //check for nullptr
            pc.add(std::move(pal));   // add failed, so we still own it: put it back
            std::cout << "  " << player.name() << " can't take any more pals.\n";
            return;
        }
    }
}

void check(const std::string& label, bool passed) {
    std::cout << "  [" << (passed ? "PASS" : "FAIL") << "] " << label << '\n';
}


int main() {
    // 1. PalCenter with room for 20 pals, stocked with 12.
    PalBox PalCenter(kCenterCapacity);
    for (const std::string& name : kNames) { // add all 12 named pals with random stats
        PalCenter.add(makeRandomPal(name));
    }
    std::cout << "PalCenter stocked with " << PalCenter.size() << " of "
              << PalCenter.capacity() << " pals.\n";

    // 2. Two players.
    Player dash("Dash");
    Player nisty("Nisty");

    // 3. Five pals each from PalCenter.
    transferPals(PalCenter, dash,  kPalsPerPlayer);
    transferPals(PalCenter, nisty, kPalsPerPlayer);

    std::cout << "\n============================= Before the trade\n";
    printPlayer(dash);
    printPlayer(nisty);
    std::cout << "\n  Pals left in PalCenter: " << PalCenter.size() << '\n';

    // 4. Trade Dash's first pal for Nisty's last pal.
    int dashIdx  = 0;
    int nistyIdx = nisty.palCount() - 1;

    // Remember the actual objects so we can confirm they swapped places.
    //
    // Study notes:
    // there are two versions of the .pal function in Player class
    // which one do these use??
    // ansewr:  it uses the NON constant one because dash is not a const Player
    //  the overload does not care about what the result is being stored into (left side)
    //  it cares about the object's type that you are calling the functoin on
    // Finally, the resulting PocketPal* is converted to a const PocketPal* (allowed)
    //  the reverse of going from const to a non-const is NOT allowed
    const PocketPal* dashGives  = dash.pal(dashIdx);
    const PocketPal* nistyGives = nisty.pal(nistyIdx);
    
        
    std::cout << "\n=========== Trading " << dash.name() << "'s " << dashGives->name()
              << " (slot " << dashIdx << ") for " << nisty.name() << "'s "
              << nistyGives->name() << " (slot " << nistyIdx << ")\n";

    bool traded = trade(dash, dashIdx, nisty, nistyIdx);

    printPlayer(dash);
    printPlayer(nisty);

    // Checks
    std::cout << "\n======================== Checks \n";
    check("PalCenter started with 12 pals and has 2 left",
          PalCenter.size() == kStartingPals - 2 * kPalsPerPlayer);
    check("trade() returned true", traded);
    check("Dash's slot 0 now holds Nisty's old pal", dash.pal(dashIdx) == nistyGives); 
    check("Nisty's last slot now holds Dash's old pal", nisty.pal(nistyIdx) == dashGives); 
    check("Both players still have 5 pals",
          dash.palCount() == kPalsPerPlayer && nisty.palCount() == kPalsPerPlayer);
    check("Trading with yourself is rejected", !trade(dash, 0, dash, 1));
    check("Out-of-range index is rejected", !trade(dash, 0, nisty, 99));

    return 0;
}
