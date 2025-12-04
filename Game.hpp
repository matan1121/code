#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"

class Game {
private:
    Player player1;
    Player player2;

public:
    Game(const Player& p1, const Player& p2);

    void start();
    void playRound();
    int checkWinner() const;
};

#endif
