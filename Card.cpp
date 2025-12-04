#include "Card.hpp"

Card::Card() : suit(Hearts), rank("Ace") {
}

Card::Card(Suit s, const std::string& r) : suit(s), rank(r) {
}

Card::Card(const Card& other) : suit(other.suit), rank(other.rank) {
}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        suit = other.suit;
        rank = other.rank;
    }
    return *this;
}

Card::~Card() {
}

Suit Card::getSuit() const {
    return suit;
}

std::string Card::getRank() const {
    return rank;
}

void Card::setSuit(Suit s) {
    suit = s;
}

void Card::setRank(const std::string& r) {
    rank = r;
}

// Very simple mapping: 2-10, Jack=11, Queen=12, King=13, Ace=14
int Card::getRankValue() const {
    if (rank == "2")  return 2;
    if (rank == "3")  return 3;
    if (rank == "4")  return 4;
    if (rank == "5")  return 5;
    if (rank == "6")  return 6;
    if (rank == "7")  return 7;
    if (rank == "8")  return 8;
    if (rank == "9")  return 9;
    if (rank == "10") return 10;
    if (rank == "Jack")  return 11;
    if (rank == "Queen") return 12;
    if (rank == "King")  return 13;
    if (rank == "Ace")   return 14;

    return 0; // in case of unknown rank
}
