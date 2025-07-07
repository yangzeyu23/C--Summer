#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int PLAYER_COUNT = 4;
const int CARD_COUNT = 52;
const int SUIT_COUNT = 4;
const int RANK_COUNT = 13;

const string SUITS[SUIT_COUNT] = {"梅花", "方块", "红桃", "黑桃"};
const string RANKS[RANK_COUNT] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const string PLAYER_NAMES[PLAYER_COUNT] = {"玩家1", "玩家2", "玩家3", "玩家4"};

// 卡牌类
class Card {
public:
    int suitIndex;
    int rankIndex;

    Card(int suit, int rank) : suitIndex(suit), rankIndex(rank) {}

    string getSuit() const {
        return SUITS[suitIndex];
    }

    string getRank() const {
        return RANKS[rankIndex];
    }

    int getValue() const {
        if (rankIndex >= 9 && rankIndex <= 12) {
            return rankIndex - 8;  // J=1, Q=2, K=3, A=4
        }
        return 0;  // 2-10 = 0
    }
};

// 玩家类
class Player {
private:
    string name;
    vector<Card> handCards;
    int score;

public:
    Player(string playerName) : name(playerName), score(0) {}

    void addCard(const Card& card) {
        handCards.push_back(card);
        score += card.getValue();
    }

    void showHand() const {
        cout << name << " (" << handCards.size() << "张牌, 大牌点值为" << score << "): ";
        if (handCards.empty()) {
            cout << "No cards";
        } else {
            for (const auto& card : handCards) {
                cout << card.getSuit() << card.getRank() << " ";
            }
        }
        cout << endl << endl;
    }

    int getScore() const {
        return score;
    }
};

// 游戏类
class BridgeGame {
private:
    vector<Card> deck;
    vector<Player> players;
    int dealtCards;

public:
    BridgeGame() : dealtCards(0) 
    {
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

    void shuffleDeck() {
        srand(static_cast<unsigned>(time(0)));
        for (size_t i = deck.size() - 1; i > 0; --i) {
            size_t j = rand() % (i + 1);
            swap(deck[i], deck[j]);
        }
    }

    void dealCards() {
        while (dealtCards < CARD_COUNT) {
            int currentPlayer = dealtCards % PLAYER_COUNT;
            players[currentPlayer].addCard(deck[dealtCards]);
            ++dealtCards;
        }
    }

    void showGameState() const {
        for (const auto& player : players) {
            player.showHand();
        }

        int team1Score = players[0].getScore() + players[1].getScore();
        int team2Score = players[2].getScore() + players[3].getScore();

        cout <<"------------------------------------------------" << endl;
        cout << "Team 1 总分: " << team1Score << endl;
        cout << "Team 2 总分: " << team2Score << endl;
        team1Score > team2Score ? cout << "Team 1 胜利！" : team1Score < team2Score ? cout << "Team 2 胜利！" : cout << "平局！" << endl;
    }
};


int main() {
    cout << "这是一个桥牌游戏。四个玩家每人将随机获得13张牌, 其中玩家1和玩家2属于Team 1, 玩家3和玩家4属于Team 2。" << endl;
    cout << "现在游戏开始------------------------------------" << endl << endl;

    BridgeGame game;
    game.dealCards();
    game.showGameState();

    return 0;
}