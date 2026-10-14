#include <iostream>
using namespace std;

int main()
{
    int n1, n2, total = 0;
    int i[4][9]  = {{0,0,0,0,0,0,0,0,0},{0,40,40,55,55,60,60,55,55},{0,55,55,60,70,85,95,100,110},{0,85,100,100,100,0,0,0,0}};
    cout << "-----Menu-----" << endl;
    do
    {
        cin >> n1;
        if(n1 == 0)
            break;
        cin >> n2;
        if(n2 == 0)
            break;
        total +=i[n1][n2];
    }while(true);
    cout << "Total Cost: " << total;
    return 0;
}
