#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double a = 0, b = 0, c = 0;
    int score[3];
    cout << "Please enter the scores of three students:" << endl;
    cin >> a >> b >> c;
    cout << "avg = " << fixed << setprecision(3) << (a + b + c)/3 <<  endl;
    score[0] = a;
    score[1] = b;
    score[2] = c;
    if(a < 60 || b < 60 || c < 60)
    {
        cout << "fail:" << endl;
        if(score[0] < 60)
        {
            cout << "1: " << score[0] << endl;
        }
        else{}
        if(score[1] < 60)
        {
            cout << "2: " << score[1] << endl;
        }
        else{}
        if(score[2] < 60)
        {
            cout << "3: " << score[2] << endl;
        }
        else{}
    }
    return 0;


}
