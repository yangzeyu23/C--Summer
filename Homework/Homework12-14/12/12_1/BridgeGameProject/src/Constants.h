#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const int PLAYER_COUNT = 4;
const int CARD_COUNT = 52;
const int SUIT_COUNT = 4;
const int RANK_COUNT = 13;

const std::string SUITS[SUIT_COUNT] = {"Clubs", "Diamonds", "Hearts", "Spades"};

const std::string RANKS[RANK_COUNT] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

const std::string PLAYER_NAMES[PLAYER_COUNT] = {"Player 1", "Player 2", "Player 3", "Player 4"};

#endif