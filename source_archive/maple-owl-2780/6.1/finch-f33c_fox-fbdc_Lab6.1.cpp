#include <iostream>
using namespace std;

int gcd(long long int x, long long int y){
    long long int a, b, r;
    if(x > y){
        a = x;
        b = y;
    }
    else{
        a = y;
        b = x;
    }
    while(b != 0){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int fact(int a){
    int n;
    int c;

    n = 1;
    c = 1;

    while(n<=a){
        c = c * n;
        n = n + 1;
    }
    return c;
}

int main(){
   long long int ain = 6, bin = 12, c = 9;
    cout << "Enter 3 nums: ";
    cin >> ain >> bin >> c;
    ain = fact(ain);
    bin = fact(bin);
    c = fact(c);
    cout<< "GCD of " << ain << " and "<< bin << " and " << c <<" is "<< gcd(ain, gcd(bin, c) );
    return 0;
}
