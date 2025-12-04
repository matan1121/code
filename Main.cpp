#include <iostream>
#include <fstream>
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"

int main() {
    // Initialize the main deck for the game
    Deck mainDeck;

    // Populate the deck from the file
    mainDeck.populateDeckFromFile("deck.txt");

    // Shuffle the main deck before starting
    mainDeck.shuffle();

    // Create two players
    Player player1("Alice");
    Player player2("Bob");

    // Distribute cards to each player from the main deck
    while (!mainDeck.isEmpty()) {
        player1.receiveCard(mainDeck.draw());
        if (!mainDeck.isEmpty()) {
            player2.receiveCard(mainDeck.draw());
        }
    }

    // Initialize the game with the two players
    Game warGame(player1, player2);

    // Start the game
    warGame.start();

    // Main game loop
    bool gameRunning = true;
    while (gameRunning) {
        // Play a round
        warGame.playRound();

        // Check for a winner
        int winner = warGame.checkWinner();
        if (winner != 0) {
            gameRunning = false;
            std::cout << "Player " << winner << " wins the game!" << std::endl;
        }
    }

    return 0;
}