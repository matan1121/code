#ifndef CARD_HPP
#define CARD_HPP

#include <string>

enum Suit {
    Hearts,
    Spades,
    Diamonds,
    Clubs
};

class Card {
private:
    Suit suit;
    std::string rank;

public:
    Card();
    Card(Suit s, const std::string& r);
    Card(const Card& other);
    Card& operator=(const Card& other);
    ~Card();

    Suit getSuit() const;
    std::string getRank() const;
    void setSuit(Suit s);
    void setRank(const std::string& r);

    int getRankValue() const; // for comparing cards in the game
};

#endif
