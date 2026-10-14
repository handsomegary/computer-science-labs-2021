#include <iostream>
#include <cmath>
using namespace std;
bool Primecheck(int n)
{
    for(int i = 2 ; i <= pow(n,0.5) ; i++)
    {
        if(n%i == 0)
            return false;
    }
    return true;
}
int main()
{
    int prime[5133], k = 1, num;//4~50000只有5132個質數
    prime[0] = 2;
    cout << "Input number: ";
    for(int i = 3; i < 25000; i++)
    {
        if(Primecheck(i))
        {
            prime[k++] = i;
        }
    }
    cin >> num;
    int combinations = 0;
    for(int i = 0 ; prime[i] <= num/2 ; i++)
    {
        if(Primecheck(num-prime[i]))
        {
            combinations++;
        }
    }
    cout<< "Number of combinations: " << combinations <<endl;
    return 0;
}
