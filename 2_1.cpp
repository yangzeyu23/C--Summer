#include <iostream>
using namespace std;

/*使用循环结构打印下述图形，打印行数n由用户输入。图中每行事实上包括两部分，中间间隔空格字符数m也由用户输入：
    *    *********
   ***    *******
  *****    *****
 *******    ***
*********    *
*/
int main(){
    int n, m;
    cout << "请输入行数: ";
    cin >> n;
    cout << "请输入中间间隔空格字符数: ";
    cin >> m;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n-i-1; j++) {
            cout << " ";
        }
        
        for (int j = 0; j < 2*i+1 ; j++) {
            cout << "*";
        }
        
        for (int j = 0; j < m; j++) {
            cout << " ";
        }
        
        for (int j = 0; j < 2*n-1-2*i ; j++) {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}