#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "Character.h"

using namespace std;

class Room
{
public:
    string name;
    Room *north;
    Room *south;
    Room *east;
    Room *west;

    vector<Item *> items;
    Monster *monster;

    Room(string n);
    ~Room();

    void addItem(Item *item);
    Item *removeItem(string itemName);
    void setMonster(Monster *m);
};

// Linked List Node
struct Node
{
    Room *data;
    Node *next;
};