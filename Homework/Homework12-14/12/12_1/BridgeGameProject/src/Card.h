#ifndef CARD_H
#define CARD_H

#include "Constants.h" // 引入常量定义
#include <string>

class Card {
private:
    int suitIndex;
    int rankIndex;

public:
    Card(int suit, int rank); // 仅声明构造函数
    std::string getSuit() const;
    std::string getRank() const;
    int getValue() const;
};

#endif // CARD_H