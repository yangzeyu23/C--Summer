#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Card.h"

class Player 
{
private:
    std::string name;
    std::vector<Card> handCards;
    int score;

public:
    Player(const std::string& playerName);
    void addCard(const Card& card);
    void showHand() const;
    int getScore() const;
};

#endif // PLAYER_H