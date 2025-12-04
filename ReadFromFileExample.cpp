void Deck::populateDeckFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        // Parse the line to extract suit and rank
        // Validate the extracted suit and rank
        // If valid, create a Card object and add it to the deck
    }
    file.close();
}