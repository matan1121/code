#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Deck.hpp"

class Player {
private:
    std::string name;
    Deck hand;

public:
    Player();
    Player(const std::string& n);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player();

    std::string getName() const;
    void setName(const std::string& n);

    void receiveCard(const Card& c);
    Card playCard();

    bool hasCards() const;
    int getCardCount() const;
};

#endif
