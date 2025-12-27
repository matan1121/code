#pragma once
#include <string>
#include <iostream>

using namespace std;

enum ItemType
{
    GENERIC,
    EQUIPMENT,
    POTION
};

class Item
{
protected:
    string name;
    ItemType type;

public:
    Item(string n, ItemType t);
    string getName() const;
    ItemType getType() const;
};

class Equipment : public Item
{
private:
    int healthBonus;
    int strengthBonus;
    int defenseBonus;

public:
    Equipment(string n, int hp, int str, int def);

    int getHealthBonus() const;
    int getStrengthBonus() const;
    int getDefenseBonus() const;
    int getTotalStats() const;
};

class Potion : public Item
{
private:
    string pType; // "Health", "Strength", or "Defense"
    int effectAmount;

public:
    Potion(string n, string t, int amount);
    string getPotionType() const;
    int getEffect() const;
};