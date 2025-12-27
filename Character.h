#pragma once
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

enum CharacterClass
{
    WARRIOR,
    MAGE,
    THIEF
};

class Character
{
protected: // Protected allows us to manage these variables inside this class and derived ones
    string name;
    CharacterClass classType;
    int health;
    int strength;
    int defense;
    vector<Item *> inventory;

public:
    Character(string n, CharacterClass cType, int hp, int str, int def);
    ~Character();

    string getName() const;
    int getHealth() const;
    int getStrength() const;
    int getDefense() const;

    void takeDamage(int dmg);
    void heal(int amount);
    void buffStrength(int amount);
    void buffDefense(int amount);
    bool isAlive() const;

    // These replace the virtual functions
    bool canEquip(Equipment *item);
    string pickUp(Item *item);

private:
    void equipItem(Equipment *newItem, string &logMsg);
};

// Derived classes inherit the protected members
class Warrior : public Character
{
public:
    Warrior(string n);
};

class Mage : public Character
{
public:
    Mage(string n);
};

class Thief : public Character
{
public:
    Thief(string n);
};

class Monster
{
public:
    string name;
    int health;
    int strength;
    int defense;

    Monster(string n, int hp, int str, int def);
    void takeDamage(int dmg);
    bool isAlive() const;
};