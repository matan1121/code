#include "Game.hpp"
#include <iostream>

Game::Game(const Player& p1, const Player& p2)
    : player1(p1), player2(p2) {
}

void Game::start() {
    // can be empty or print something simple
}

void Game::playRound() {
    if (!player1.hasCards() || !player2.hasCards())
        return;

    Card c1 = player1.playCard();
    Card c2 = player2.playCard();

    int v1 = c1.getRankValue();
    int v2 = c2.getRankValue();

    if (v1 > v2) {
        player1.receiveCard(c1);
        player1.receiveCard(c2);
    } else if (v2 > v1) {
        player2.receiveCard(c1);
        player2.receiveCard(c2);
    } else {
        // simple tie rule: both cards are lost
        // DO NOT return them to players
    }
}

int Game::checkWinner() const {
    if (!player1.hasCards() && player2.hasCards())
        return 2;

    if (!player2.hasCards() && player1.hasCards())
        return 1;

    return 0;
}
