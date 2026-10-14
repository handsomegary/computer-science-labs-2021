#include <iostream>
using namespace std;

int gcd(int x, int y){
    int a, b, r;
    if(x > y){
        a = x;
        b = y;
    }
    else{
        a = y;
        b = x;
    }
    while(b != 0){
        r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int fact(int a){
    int n=1;
    int c=1;

    while(n<=a){
        c = c * n;
        n = n + 1;
    }
    return c;
}

int main(){
    int ain , bin , Cin ;
    cout << "Enter 3 nums: ";
    cin >> ain >> bin >> Cin;
    ain = fact(ain);
    bin = fact(bin);
    Cin = fact(Cin);
    cout<< "GCD of " << ain << " and "<< bin << " and " << Cin <<" is "<< gcd(ain, gcd(bin, Cin) );
    return 0;
}
