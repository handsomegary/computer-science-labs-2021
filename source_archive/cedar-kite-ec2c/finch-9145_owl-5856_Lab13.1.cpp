#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main()
{
    string number;
    string numb;
    double prize = 0;
    while (cin >> numb)
    {
        number = numb;
        char ch = getchar();
        if (ch == '\n')
        {
            break;
        }
    }
    int length = number.length();
    length = length -1;
    int counter = 0;
    string lists[100];
    int counter2 = 0;
    while (cin >> numb)
    {
        lists[counter2] = numb;
        counter2++;
        char ch = getchar();
        if (ch == '\n'){
            break;
        }
    }
    int counts = 0;
    while(counts < counter2)
    {
        for (int i = length-1; i >= 0; i--)
        {
            if (lists[counts][i] == number[i])
            {
                counter++;
                continue;
            }
            else
            {
                break;
            }
        }
        counter--;
        switch(counter)
        {
            case 2: prize += 200;cout << lists[counts] << " won 2 hundred dollars!" << endl;break;
            case 3: prize +=1000;cout << lists[counts] << " won 1 thousand dollars!" << endl;break;
            case 4: prize +=4000;cout << lists[counts] << " won 4 thousand dollars!" << endl;break;
            case 5: prize +=10000;cout << lists[counts] << " won 10 thousand dollars!" << endl;break;
            case 6: prize +=40000;cout << lists[counts] << " won 40 thousand dollars!" << endl;break;
            case 7: prize +=200000;cout << lists[counts] << " won 200 thousand dollars!" << endl;break;
            case 8: prize +=200000;cout << lists[counts] << " won 200 thousand dollars!" << endl;break;
        }
        counter = 0;
        counts++;
    }
    if (prize == 0)
    {
        cout << "Won nothing. But, less is more.";
    }
    else
    {
        cout << "You totally won " << prize << " dollars !!!";
    }
    return 0;
}
