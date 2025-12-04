#ifndef DECK_HPP
#define DECK_HPP

#include <string>
#include "Card.hpp"

class Deck {
private:
    Card* cards;    // array of 52 cards
    int cardCount;  // how many cards are currently in the deck

public:
    Deck();
    Deck(const Deck& other);
    Deck& operator=(const Deck& other);
    ~Deck();

    void populateDeckFromFile(const std::string& filename);
    void shuffle();
    Card draw();
    void addCard(const Card& c);


    bool isEmpty() const;
    int getCardCount() const;
};

#endif
