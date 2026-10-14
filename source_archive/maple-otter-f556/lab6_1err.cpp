#include <iostream>
using namespace std;

int gcd(int x, int y){
    /*int a; b; r;*/
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
        b = a%b;
        a = r;
        /*r = a / b;
        a = b;
        b = r;*/
    }
    return a;
}

int fact(int a){
    int n;
    int c;

    /*n = -1;
    c = 0;*/
    n = 1;
    c = 1;

    while(n<=a){
        c = c * n;
        n = n + 1;
    }
    return c;
}

int main(){
    int ain = 6, bin = 12, din = 9/*cin = 9*/;
    cout << "Enter 3 nums: ";
    cin >> ain >> bin >> din/*cin*/;
    ain = fact(ain);
    bin = fact(bin);
    din/*cin*/ = fact(din/*cin*/);
    cout<< "GCD of " << ain << " and "<< bin << " and " << din/*cin*/ <<" is "<< gcd(ain, gcd(bin, din/*cin*/) );
    return 0;
}
