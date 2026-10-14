#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void Hanoi(int disk, int depart, int terminal)
{
    int temp;
    switch (depart+terminal)
    {
        case 3:
            temp = 3;
            break;
        case 4:
            temp = 2;
            break;
        default:
            temp = 1;
            break;
    }
    if(disk == 1)
    {
        cout << "move disk 1 from " << depart <<" to "<< terminal << endl;
    }
    else
    {
        Hanoi(disk-1,depart,temp);
        cout << "move disk 1 from " << depart <<" to "<< terminal << endl;
        Hanoi(disk-1,temp,terminal);
    }

}
int main()
{
    int disk;
    cout << "Please enter the number: ";
    cin >> disk;
    Hanoi(disk, 1, 3);
    return 0;
}

