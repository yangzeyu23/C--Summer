#include <iostream>
#include "BridgeGame.h"

int main() 
{
    std::cout << "Welcome to the Bridge Game! Four players will each receive 13 random cards. Player 1 and Player 2 belong to Team 1, while Player 3 and Player 4 belong to Team 2." << std::endl;
    std::cout << "Game starts------------------------------------" << std::endl << std::endl;

    BridgeGame game;
    game.dealCards();
    game.showGameState();

    return 0;
}