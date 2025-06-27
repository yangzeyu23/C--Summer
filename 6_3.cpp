#include <iostream>
#include <ctime>
using namespace std;

//将去除大小王的52张扑克牌平均分配给四个玩家，每家13张牌。为描述问题方便，2～9的牌张使用对应字符‘2’～‘9’，字符‘T’表示10，‘J’、‘Q’、‘K’、‘A’表示四类大牌。记每张2～10为0点，J为1点，Q为2点，K为3点，A为4点，统计每家大牌点值。上述牌点计算方法主要用于桥牌游戏。
void GenerateDeck(int deck[]);

int main() 
{
    srand(time(0)); 
    int deck[52];        
    GenerateDeck(deck);  
    
    cout << "先来洗牌。洗完后各牌对应的顺序为: " << endl;
    
    for (int i = 0; i < 52; i++) {

        if (i < 13) {
            cout << "梅花"; 
        } else if (i < 26) {
            cout << "方块"; 
        } else if (i < 39) {
            cout << "红桃"; 
        } else {
            cout << "黑桃"; 
        }

        if (i % 13 == 9) {
            cout << "J: "; 
        } else if (i % 13 == 10) {
            cout << "Q: "; 
        } else if (i % 13 == 11) {
            cout << "K: "; 
        } else if (i % 13 == 12) {
            cout << "A: "; 
        } else {
            cout << i % 13 + 2 << ": "; 
        }

        cout << deck[i] ;
        (i % 4 == 3)? cout << endl : cout << "    "; 
    }
    cout << endl;

    cout << "再来分牌，每个玩家按从1到52的顺序轮流从牌堆摸取, 共13张牌。最后的摸牌结果为: " << endl;

    for (int n=1; n <= 4; n++)
    {
        cout << "玩家"<< n << "摸到的牌为：" << endl;

        int m, j=0;    // m 用于调整玩家4的序号(4 % 4 = 0), j 用于记录玩家的牌点值
        
        m = (n==4) ?  0 : n;

        for (int i = 0; i < 52; i++) {
    
            if (deck[i] % 4 == m )
            {
                if (i < 13) {
                    cout << "梅花"; 
                } else if (i < 26) {
                    cout << "方块"; 
                } else if (i < 39) {
                    cout << "红桃"; 
                } else {
                    cout << "黑桃"; 
                }

                if (i % 13 == 9) {
                    cout << "J";
                    j += 1; 
                } 
                else if (i % 13 == 10) {
                    cout << "Q"; 
                    j += 2;
                } 
                else if (i % 13 == 11) {
                    cout << "K"; 
                    j += 3;
                } 
                else if (i % 13 == 12) {
                    cout << "A"; 
                    j += 4;
                } 
                else {
                    cout << i % 13 + 2 ; 
                }
                cout << "   "; 
            }     
        }
        cout << endl << "经计算，玩家" << n << "的大牌点值为: " << j << endl; 
        cout << endl;  
    }

    return 0;
}

void GenerateDeck(int deck[]) {
    for (int i = 0; i < 52; i++) {
        deck[i] = i + 1; 
    }
    
    for (int i = 51; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        swap(deck[i], deck[j]);
    }
}