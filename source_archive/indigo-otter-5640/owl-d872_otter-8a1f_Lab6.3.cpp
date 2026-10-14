#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
using namespace std;

int main()
{
    int A = 0;
    int B = 0;
    int C = 0;
    int D = 0;
    int F = 0;

    int score = 1;
    double sample = 0;
    double sum = 0;
    double average = 0;
    double sd1 = 0;
    double sd = 0;

    cout << "Enter # of sample: ";
    cin >> sample;
    for(int roll = 1; roll <= sample; roll++)
    {
        score = rand()%101;
        sum = sum + score;
        if (90 <= score && score <= 100)
        {
            ++A;
        }
        else{}
        if (80 <= score && score < 90)
        {
            ++B;
        }
        else{}
        if (70 <= score && score < 80)
        {
            ++C;
        }
        else{}
        if (60 <= score && score < 70)
        {
            ++D;
        }
        else{}
        if (score < 60)
        {
            ++F;
        }
        else{}
        sd1 = sd1 + score*score;
    }
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << "C: " << C << endl;
    cout << "D: " << D << endl;
    cout << "F: " << F << endl;
    average = sum/sample;
    sd = pow(sd1/sample - average*average,0.5);
    cout << "Mean: " << setprecision(4) << average << endl;
    cout << "STD Deviation: " << setprecision(4) << sd <<endl;
    return 0;
}
