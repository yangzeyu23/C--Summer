#ifndef BRIDGEGAME_H
#define BRIDGEGAME_H

#include <vector>
#include "Card.h"
#include "Player.h"

class BridgeGame {
private:
    std::vector<Card> deck;
    std::vector<Player> players;
    int dealtCards;

public:
    BridgeGame();
    void shuffleDeck();
    void dealCards();
    void showGameState() const;
};

#endif // BRIDGEGAME_H