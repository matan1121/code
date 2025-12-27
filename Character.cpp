#include "Character.h"
#include <iostream>

// --- Character Base ---
Character::Character(string n, CharacterClass cType, int hp, int str, int def)
    : name(n), classType(cType), health(hp), strength(str), defense(def) {}

Character::~Character()
{
    for (size_t i = 0; i < inventory.size(); i++)
    {
        delete inventory[i];
    }
    inventory.clear();
}

string Character::getName() const { return name; }
int Character::getHealth() const { return health; }
int Character::getStrength() const { return strength; }
int Character::getDefense() const { return defense; }

void Character::takeDamage(int dmg) { health -= dmg; }
void Character::heal(int amount) { health += amount; }
void Character::buffStrength(int amount) { strength += amount; }
void Character::buffDefense(int amount) { defense += amount; }
bool Character::isAlive() const { return health > 0; }

bool Character::canEquip(Equipment *item)
{
    string iName = item->getName();

    // Logic based on enum (No virtual functions needed)
    if (classType == WARRIOR)
    {
        return (iName == "Sword" || iName == "Shield");
    }
    else if (classType == THIEF)
    {
        return (iName == "Dagger");
    }
    else if (classType == MAGE)
    {
        return (iName == "Wand");
    }
    return false;
}

string Character::pickUp(Item *item)
{
    if (item->getType() == POTION)
    {
        // Safe cast because we checked type
        Potion *p = static_cast<Potion *>(item);

        if (p->getPotionType() == "Health")
            heal(p->getEffect());
        else if (p->getPotionType() == "Strength")
            buffStrength(p->getEffect());
        else if (p->getPotionType() == "Defense")
            buffDefense(p->getEffect());

        string msg = " drank " + p->getName() + ".";
        delete item; // Potion consumed immediately
        return msg;
    }
    else if (item->getType() == EQUIPMENT)
    {
        Equipment *eq = static_cast<Equipment *>(item);
        if (!canEquip(eq))
        {
            return " cannot equip " + eq->getName() + ".";
        }
        string msg = "";
        equipItem(eq, msg);
        return msg;
    }
    return " found an unknown item.";
}

void Character::equipItem(Equipment *newItem, string &logMsg)
{
    // Check for duplicate in protected inventory
    for (size_t i = 0; i < inventory.size(); i++)
    {
        if (inventory[i]->getType() == EQUIPMENT)
        {
            Equipment *current = static_cast<Equipment *>(inventory[i]);

            if (current->getName() == newItem->getName())
            {
                // Duplicate found-compare stats
                if (newItem->getTotalStats() > current->getTotalStats())
                {
                    logMsg = " swapped " + current->getName() + " for a better one.";

                    // Remove old stats
                    health -= current->getHealthBonus();
                    strength -= current->getStrengthBonus();
                    defense -= current->getDefenseBonus();

                    delete inventory[i];
                    inventory[i] = newItem;

                    // Add new stats
                    health += newItem->getHealthBonus();
                    strength += newItem->getStrengthBonus();
                    defense += newItem->getDefenseBonus();
                }
                else
                {
                    logMsg = " found a " + newItem->getName() + " but it was not better.";
                    delete newItem; // Discard new one
                }
                return;
            }
        }
    }

    // New item type
    inventory.push_back(newItem);
    health += newItem->getHealthBonus();
    strength += newItem->getStrengthBonus();
    defense += newItem->getDefenseBonus();
    logMsg = " picked up " + newItem->getName() + ".";
}

Warrior::Warrior(string n) : Character(n, WARRIOR, 100, 15, 10) {}
Mage::Mage(string n) : Character(n, MAGE, 40, 25, 5) {}
Thief::Thief(string n) : Character(n, THIEF, 60, 20, 7) {}

Monster::Monster(string n, int hp, int str, int def)
    : name(n), health(hp), strength(str), defense(def) {}
void Monster::takeDamage(int dmg) { health -= dmg; }
bool Monster::isAlive() const { return health > 0; }