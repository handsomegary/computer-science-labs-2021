#include <iostream>

using namespace std;

int main()
{
    float weight, height, BMI ;
    cout << "Please enter your weight: " ;
    cin >> weight ;
    cout << "Please enter your height: " ;
    cin >> height ;
    BMI = weight/(height*height);
    cout << "Your BMI is " << BMI << endl ;
    if (BMI < 18.5)
        cout << "You need to eat more" ;
    else if (BMI < 24)
        cout << "You are healthy" ;
    else
        cout << "You need to control your diet" ;
    return 0 ;
}
