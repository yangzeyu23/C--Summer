#include <iostream>
#include <iomanip> 
using namespace std;

/*按照下述格式打印2016年1月日历：

Calendar 2016-01
--------------------------
Su  Mo  Tu  We  Th  Fr  Sa
--------------------------
                     1   2
 3   4   5   6   7   8   9
10  11  12  13  14  15  16
17  18  19  20  21  22  23
24  25  26  27  28  29  30
31
--------------------------
*/
int main() {
    cout << "Calendar 2016-01" << endl;
    cout << "--------------------------" << endl;
    cout << "Su  Mo  Tu  We  Th  Fr  Sa" << endl;
    cout << "--------------------------" << endl;
    cout << "                     1";

   for (int i = 2; i <= 31 ; i++) 
    {
        if (i% 7 == 3) 
            cout << endl << i;
         else   
            cout << "  " << i;
        
   }
    return 0;
}