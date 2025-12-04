#include "Player.hpp"

Player::Player() : name("Unknown"), hand() {}

Player::Player(const std::string& n) : name(n), hand() {}

Player::Player(const Player& other) : name(other.name), hand(other.hand) {}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        name = other.name;
        hand = other.hand;
    }
    return *this;
}

Player::~Player() {}

std::string Player::getName() const {
    return name;
}

void Player::setName(const std::string& n) {
    name = n;
}

void Player::receiveCard(const Card& c) {
    hand.addCard(c);
}

Card Player::playCard() {
    return hand.draw();
}

bool Player::hasCards() const {
    return !hand.isEmpty();
}

int Player::getCardCount() const {
    return hand.getCardCount();
}
