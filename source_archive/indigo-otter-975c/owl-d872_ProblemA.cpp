#include <iostream>
using namespace std;

int main()
{
    int heads, feet;
    int chicks, rabbits;
    cin >> heads >> feet;
    while(true)
    {
        if (heads == 0 || feet == 0)
        {
            cout << "Bye";
            return 0;
        }
        chicks = (4*heads - feet)/2;
        rabbits = (feet - 2*heads)/2;
        if ((4*heads - feet)%2 != 0 || (feet - 2*heads)%2 != 0)
        {
            cout << "no" << endl;
            cin >> heads >> feet;
        }
        else
        {
            cout << "Chick " << chicks << " Rabbit " << rabbits << endl;
            cin >> heads >> feet;
        }
    }
}
