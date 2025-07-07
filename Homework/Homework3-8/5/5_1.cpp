#include <iostream>
#include <ctime>
using namespace std;

//编写函数，返回1～52之间的随机数。
int getRandomNumber(); 

int main() {
    srand(time(0)); 
    int randomNumber = getRandomNumber();
    cout << "随机数是: " << randomNumber << endl;
    return 0;
}

int getRandomNumber() {
    return rand() % 52 + 1; 
}