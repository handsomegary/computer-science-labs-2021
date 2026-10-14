#include <iostream>
#include <algorithm>
using namespace std;
bool isPrime(int n)
{
    for(int i = 2 ; i <= n/2 ; i++)
    {
        if(n%i==0)
            return false;
    }
    return true;
}
int main()
{
    int prime[10000], k = 1, num;
    prime[0] = 2;
    cout << "Input number: ";
    for(int i = 3 ; i < 50000 ; i++)
    {
        if(isPrime(i))
            prime[k++] = i;
    }
    int answer = 0;
    cin >> num;
    for(int i = 0 ; prime[i] <= num/2 ; i++)
    {
       int *p = find(prime, prime + 5133, num - prime[i]);
       if(p != prime + 5133)
        {
            answer++;
        }
    }
    cout<< "Number of combinations: " << answer << endl;
    return 0;
}
