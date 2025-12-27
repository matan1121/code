#include "Game.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

Game::Game() : roomListHead(nullptr), startRoom(nullptr), currentRoom(nullptr), player(nullptr) {}

Game::~Game()
{
    Node *current = roomListHead;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
    if (player)
        delete player;
}

void Game::addRoomToList(Room *r)
{
    Node *newNode = new Node;
    newNode->data = r;
    newNode->next = nullptr;

    if (!roomListHead)
    {
        roomListHead = newNode;
    }
    else
    {
        Node *temp = roomListHead;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

Room *Game::findRoom(string name)
{
    Node *temp = roomListHead;
    while (temp)
    {
        if (temp->data->name == name)
            return temp->data;
        temp = temp->next;
    }
    return nullptr;
}

void Game::log(string message)
{
    outputLog.push_back(message);
}

void Game::loadFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        size_t firstChar = line.find_first_not_of(" \t");
        if (firstChar != string::npos && line.substr(firstChar, 2) == "//")
            continue;

        size_t commentPos = line.find("//");
        if (commentPos != string::npos)
        {
            line = line.substr(0, commentPos);
        }

        if (!line.empty())
            pendingCommands.push_back(line);
    }
    file.close();
}

void Game::outputFinalState(string filename)
{
    ofstream file(filename);
    for (size_t i = 0; i < outputLog.size(); i++)
    {
        file << outputLog[i] << endl;
    }
    file.close();
}

void Game::executeCommands()
{
    for (size_t i = 0; i < pendingCommands.size(); i++)
    {
        stringstream ss(pendingCommands[i]);
        string action;
        ss >> action;

        if (action == "create" || action == "Create")
            executeCreate(ss);
        else if (action == "Set")
            executeSet(ss);
        else if (action == "Connect")
            executeConnect(ss);
        else if (action == "Place")
            executePlace(ss);
        else if (action == "Enter")
            executeEnter(ss);
        else if (action == "Move")
            executeMove(ss);
        else if (action == "Fight")
            executeFight(ss);
        else if (action == "PickUp")
            executePickUp(ss);
    }
}

void Game::executeCreate(stringstream &ss)
{
    string type, name;
    ss >> type >> name;

    if (type == "Room" || type == "room")
    {
        addRoomToList(new Room(name));
    }
    else
    {
        if (type == "warrior")
            player = new Warrior(name);
        else if (type == "mage")
            player = new Mage(name);
        else if (type == "thief")
            player = new Thief(name);
    }
}

void Game::executeSet(stringstream &ss)
{
    string dummy, roomName;
    ss >> dummy >> roomName;
    startRoom = findRoom(roomName);
}

void Game::executeConnect(stringstream &ss)
{
    string r1Name, r2Name, dir;
    ss >> r1Name >> r2Name >> dir;

    Room *r1 = findRoom(r1Name);
    Room *r2 = findRoom(r2Name);

    if (r1 && r2)
    {
        if (dir == "North")
            r1->north = r2;
        else if (dir == "South")
            r1->south = r2;
        else if (dir == "East")
            r1->east = r2;
        else if (dir == "West")
            r1->west = r2;
    }
}

void Game::executePlace(stringstream &ss)
{
    string type;
    ss >> type;

    if (type == "Item")
    {
        string itemName, roomName;
        int hp, str, def;
        ss >> itemName >> roomName >> hp >> str >> def;

        Room *r = findRoom(roomName);
        if (r)
        {
            // Determine if Potion or Equipment based on Name
            if (itemName.find("Potion") != string::npos)
            {
                string pType = "Defense";
                int effect = def;
                if (str > 0)
                {
                    pType = "Strength";
                    effect = str;
                }
                if (hp > 0)
                {
                    pType = "Health";
                    effect = hp;
                }

                r->addItem(new Potion(itemName, pType, effect));
            }
            else
            {
                int baseHp = 0, baseStr = 0, baseDef = 0;
                if (itemName == "Sword")
                {
                    baseStr = 5;
                    baseDef = 10;
                }
                else if (itemName == "Dagger")
                {
                    baseStr = 7;
                    baseDef = 3;
                }
                else if (itemName == "Wand")
                {
                    baseStr = 10;
                    baseDef = 0;
                }
                else if (itemName == "Shield")
                {
                    baseDef = 5;
                }

                r->addItem(new Equipment(itemName, baseHp + hp, baseStr + str, baseDef + def));
            }
        }
    }
    else if (type == "Monster")
    {
        string mName, roomName;
        int hp, str, def;
        ss >> mName >> roomName >> hp >> str >> def;
        Room *r = findRoom(roomName);
        if (r)
        {
            r->setMonster(new Monster(mName, hp, str, def));
        }
    }
}

void Game::executeEnter(stringstream &ss)
{
    string dummy, charName;
    ss >> dummy >> charName;
    if (startRoom && player)
    {
        currentRoom = startRoom;
        log(player->getName() + " enters the dungeon at " + currentRoom->name + ".");
    }
    else
    {
        log("Error: StartRoom or Player not defined.");
    }
}

void Game::executeMove(stringstream &ss)
{
    string charName, dir;
    ss >> charName >> dir;

    if (!currentRoom)
        return;

    Room *nextRoom = nullptr;
    if (dir == "North")
        nextRoom = currentRoom->north;
    else if (dir == "South")
        nextRoom = currentRoom->south;
    else if (dir == "East")
        nextRoom = currentRoom->east;
    else if (dir == "West")
        nextRoom = currentRoom->west;

    if (nextRoom)
    {
        currentRoom = nextRoom;
        log(charName + " moves " + dir + " to " + currentRoom->name + ".");
    }
    else
    {
        log(charName + " tries to move " + dir + " but cannot.");
    }
}

void Game::executeFight(stringstream &ss)
{
    string charName, monsterName;
    ss >> charName >> monsterName;

    if (!currentRoom || !currentRoom->monster || currentRoom->monster->name != monsterName)
    {
        log("Fight failed: No such monster here.");
        return;
    }

    Monster *m = currentRoom->monster;

    while (player->isAlive() && m->isAlive())
    {
        int pDmg = max(1, player->getStrength() - m->defense);
        m->takeDamage(pDmg);

        if (!m->isAlive())
        {
            log(charName + " fights " + monsterName + ": Victory");
            delete currentRoom->monster;
            currentRoom->monster = nullptr;
            return;
        }

        int mDmg = max(1, m->strength - player->getDefense());
        player->takeDamage(mDmg);

        if (!player->isAlive())
        {
            log(charName + " fights " + monsterName + ": Lose");
            return;
        }
    }
}

void Game::executePickUp(stringstream &ss)
{
    string charName, itemName;
    ss >> charName >> itemName;

    if (!currentRoom)
        return;

    // Check if item exists in room
    // Note: We "peek" first to check if we CAN pick it up before removing it
    // because if we fail class check, it should stay on floor.
    // However, for simplicity with linked list vectors, we remove then add back if fail.

    Item *item = currentRoom->removeItem(itemName);
    if (item)
    {
        // If it's equipment, check if valid class
        if (item->getType() == EQUIPMENT)
        {
            Equipment *eq = static_cast<Equipment *>(item);
            if (!player->canEquip(eq))
            {
                log(charName + " tries to pick up " + itemName + ": Failed (invalid class).");
                currentRoom->addItem(item); // Put it back
                return;
            }
        }

        string result = player->pickUp(item);
        log(charName + result);
    }
    else
    {
        log(charName + " tries to pick up " + itemName + ": Failed (item not in room).");
    }
}