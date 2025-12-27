#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Room.h"
#include "Character.h"

using namespace std;

class Game
{
private:
    Node *roomListHead;
    Room *startRoom;
    Room *currentRoom;
    Character *player;

    vector<string> pendingCommands;
    vector<string> outputLog;

    void addRoomToList(Room *r);
    Room *findRoom(string name);
    void log(string message);

    void executeCreate(stringstream &ss);
    void executeSet(stringstream &ss);
    void executeConnect(stringstream &ss);
    void executePlace(stringstream &ss);
    void executeEnter(stringstream &ss);
    void executeMove(stringstream &ss);
    void executeFight(stringstream &ss);
    void executePickUp(stringstream &ss);

public:
    Game();
    ~Game();

    void loadFromFile(string filename);
    void executeCommands();
    void outputFinalState(string filename);
};