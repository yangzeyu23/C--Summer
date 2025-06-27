#include <iostream>
#include <ctime>
using namespace std;

//编写函数，重复生成52个随机数，并映射为每张扑克牌。说明：重复生成的典型原则是按照花色（梅花、方块、红桃、黑桃）和大小（2～10、J、Q、K、A）顺序进行映射，例如梅花2小于梅花3，……，梅花A小于方块2，……，黑桃K小于黑桃A。需要注意的是，一旦生成某张牌后，即不允许再次生成它。
void GenerateDeck(int deck[]);

int main() 
{
    srand(time(0)); 
    int deck[52];        
    GenerateDeck(deck);  
    
    cout << "生成的扑克牌对应的序号为: " << endl;
    
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

        cout << deck[i] << endl; 
    }
    cout << endl;
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