#include "Deck.hpp"
#include <fstream>
#include <cstdlib>
#include <ctime>

static std::string trim(const std::string& s) {
    int start = 0;
    while (start < (int)s.size() && (s[start] == ' ' || s[start] == '\t'))
        start++;

    int end = (int)s.size() - 1;
    while (end >= 0 && (s[end] == ' ' || s[end] == '\t'))
        end--;

    if (end < start) return "";
    return s.substr(start, end - start + 1);
}

static Suit stringToSuit(const std::string& suitStr) {
    if (suitStr == "Hearts")   return Hearts;
    if (suitStr == "Spades")   return Spades;
    if (suitStr == "Diamonds") return Diamonds;
    return Clubs; // default if something is wrong
}

Deck::Deck() {
    cards = new Card[52];
    cardCount = 0;
    std::srand((unsigned)std::time(nullptr));
}

Deck::Deck(const Deck& other) {
    cards = new Card[52];
    cardCount = other.cardCount;
    for (int i = 0; i < cardCount; i++) {
        cards[i] = other.cards[i];
    }
}

Deck& Deck::operator=(const Deck& other) {
    if (this != &other) {
        cardCount = other.cardCount;
        for (int i = 0; i < cardCount; i++) {
            cards[i] = other.cards[i];
        }
    }
    return *this;
}

Deck::~Deck() {
    delete[] cards;
}

bool Deck::isEmpty() const {
    return cardCount == 0;
}

int Deck::getCardCount() const {
    return cardCount;
}

void Deck::populateDeckFromFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file) {
        return; // simple handling: do nothing if file not found
    }

    std::string line;
    cardCount = 0;

    while (std::getline(file, line) && cardCount < 52) {
        if (line.empty())
            continue;

        int commaPos = (int)line.find(',');
        if (commaPos == -1)
            continue;

        std::string suitStr = trim(line.substr(0, commaPos));
        std::string rankStr = trim(line.substr(commaPos + 1));

        Suit s = stringToSuit(suitStr);
        Card c(s, rankStr);
        cards[cardCount] = c;
        cardCount++;
    }

    file.close();
}

void Deck::shuffle() {
    for (int i = 0; i < cardCount; i++) {
        int j = std::rand() % cardCount;
        Card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

void Deck::addCard(const Card& c) {
    if (cardCount >= 52) return; // simple safety

    cards[cardCount] = c;
    cardCount++;
}


Card Deck::draw() {
    // assume not empty
    cardCount--;
    return cards[cardCount];
}
