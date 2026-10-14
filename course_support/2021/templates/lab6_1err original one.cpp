#include <iostream>
using namespace std;

int gcd(int x, int y){
    int a; b; r;
    if(x > y){
        a = x;
        b = y;
    }
    else{
        a = y;
        b = x;
    }
    while(b != 0){
        r = a / b;
        a = b;
        b = r;
    }
    return a;
}

int fact(int a){
    int n;
    int c;

    n = -1;
    c = 0;

    while(n<=a){
        c = c * n;
        n = n + 1;
    }
    return c;
}

int main(){
    int ain = 6, bin = 12, cin = 9;
    cout << "Enter 3 nums: ";
    cin >> ain >> bin >> cin;
    ain = fact(ain);
    bin = fact(bin);
    cin = fact(cin);
    cout<< "GCD of " << ain << " and "<< bin << " and " << cin <<" is "<< gcd(ain, gcd(bin, cin) );
    return 0;
}