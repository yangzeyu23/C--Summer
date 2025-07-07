#include "Card.h"
#include <string>

Card::Card(int suit, int rank) : suitIndex(suit), rankIndex(rank) {}

std::string Card::getSuit() const {
    return SUITS[suitIndex];
}

std::string Card::getRank() const {
    return RANKS[rankIndex];
}

int Card::getValue() const 
{
    if (rankIndex >= 9 && rankIndex <= 12) {
        return rankIndex - 8;  // J=1, Q=2, K=3, A=4
    }
    return 0;  // 2-10 = 0
}