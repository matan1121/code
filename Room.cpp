#include "Room.h"

Room::Room(string n) : name(n), north(nullptr), south(nullptr), east(nullptr), west(nullptr), monster(nullptr) {}

Room::~Room()
{
    for (size_t i = 0; i < items.size(); i++)
    {
        delete items[i];
    }
    if (monster)
        delete monster;
}

void Room::addItem(Item *item)
{
    items.push_back(item);
}

Item *Room::removeItem(string itemName)
{
    for (size_t i = 0; i < items.size(); i++)
    {
        if (items[i]->getName() == itemName)
        {
            Item *found = items[i];
            items.erase(items.begin() + i);
            return found;
        }
    }
    return nullptr;
}

void Room::setMonster(Monster *m)
{
    monster = m;
}