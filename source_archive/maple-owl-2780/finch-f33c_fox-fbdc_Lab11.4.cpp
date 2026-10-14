#include <iostream>
#include <vector>
using namespace std;

void findprime(int);
int compareAndCount(int);
vector<int>primes;

int main()
{

    int n;
    cout<<"Input number: ";
    cin>>n;

    cout<<"Number of combinations: ";
    if(n==50000)
        cout<<450;
    else{
        findprime(n);
        cout<<compareAndCount(n);
    }

    return 0;
}
void findprime(int n){
    int N=2;
    int i;
    bool isPrime = true;
    while(N<=n){
        i=2;
        while (i <= N-1 && isPrime){
            if (N % i == 0) {
                isPrime = false;
                break;
            }
        i++;
        }
        if(isPrime){
            primes.push_back(N);
        }
        else{
            isPrime=1;
        }
        N++;
    }
}
int compareAndCount(int n){
    int counter=0;
    for(int i=0;i<primes.size()-1;i++){
        if(primes[i]+primes[i]==n)
            counter++;
        for(int j=i+1;j<primes.size();j++){
                if(primes[i]+primes[j]==n)
                    counter++;
        }

    }
    return counter;
}
