#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "BridgeGame.h"
#include "Player.h"
#include "Card.h"

using namespace std;

BridgeGame::BridgeGame() : dealtCards(0) {
    for (const auto& name : PLAYER_NAMES) {
        players.emplace_back(name);
    }

    for (int suit = 0; suit < SUIT_COUNT; ++suit) {
        for (int rank = 0; rank < RANK_COUNT; ++rank) {
            deck.emplace_back(suit, rank);
        }
    }

    shuffleDeck();
}

void BridgeGame::shuffleDeck() {
    srand(static_cast<unsigned>(time(0)));
    for (size_t i = deck.size() - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        swap(deck[i], deck[j]);
    }
}

void BridgeGame::dealCards() {
    while (dealtCards < CARD_COUNT) {
        int currentPlayer = dealtCards % PLAYER_COUNT;
        players[currentPlayer].addCard(deck[dealtCards]);
        ++dealtCards;
    }
}

void BridgeGame::showGameState() const 
{
    for (const auto& player : players) {
        player.showHand();
    }

    int team1Score = players[0].getScore() + players[1].getScore();
    int team2Score = players[2].getScore() + players[3].getScore();

    cout << "------------------------------------------------" << endl;
    cout << "Team 1 total points: " << team1Score << endl;
    cout << "Team 2 total points: " << team2Score << endl;
    team1Score > team2Score ? cout << "Team 1 wins!" : team1Score < team2Score ? cout << "Team 2 wins!" : cout << "It's a tie!" << endl;
}