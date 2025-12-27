#include "Item.h"

// --- Base Item ---
Item::Item(string n, ItemType t) : name(n), type(t) {}

string Item::getName() const { return name; }
ItemType Item::getType() const { return type; }

// --- Equipment ---
Equipment::Equipment(string n, int hp, int str, int def)
    : Item(n, EQUIPMENT), healthBonus(hp), strengthBonus(str), defenseBonus(def) {}

int Equipment::getHealthBonus() const { return healthBonus; }
int Equipment::getStrengthBonus() const { return strengthBonus; }
int Equipment::getDefenseBonus() const { return defenseBonus; }
int Equipment::getTotalStats() const { return healthBonus + strengthBonus + defenseBonus; }

// --- Potion ---
Potion::Potion(string n, string t, int amount)
    : Item(n, POTION), pType(t), effectAmount(amount) {}

string Potion::getPotionType() const { return pType; }
int Potion::getEffect() const { return effectAmount; }