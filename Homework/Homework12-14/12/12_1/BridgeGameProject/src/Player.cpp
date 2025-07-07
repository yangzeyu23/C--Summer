#include "Player.h"
#include <iostream>

Player::Player(const std::string& playerName) : name(playerName), score(0) {}

void Player::addCard(const Card& card) 
{
    handCards.push_back(card);
    score += card.getValue();
}

void Player::showHand() const 
{
    std::cout << name << " (" << handCards.size() << " cards, total points: " << score << "): ";

    if (handCards.empty()) 
    {
        std::cout << "No cards";
    } 
    else {
        for (const auto& card : handCards) {
            std::cout << card.getSuit() << card.getRank() << " ";
        }
    }
    
    std::cout << std::endl << std::endl;
}

int Player::getScore() const {
    return score;
}