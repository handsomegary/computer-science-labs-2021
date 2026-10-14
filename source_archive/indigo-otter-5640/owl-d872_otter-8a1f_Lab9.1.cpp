#include <iostream>
#include <string>
using namespace std;

int main()
{
    char sentence1[100] = {0},sentence2[100] = {0};
    cout << "Input Line1: " ;
    cin.getline(sentence1,101);
    cout << "Input Line2: " ;
    cin.getline(sentence2,101);
    sentence1[0] = sentence1[0] - 32;
    sentence2[0] = sentence2[0] - 32;
    for(int i = 1; i < 100; i++)
    {
        if(sentence1[i] == 32)
        sentence1[i+1] = sentence1[i+1] - 32;
    }
    for(int i = 1; i < 100; i++)
    {
        if(sentence2[i] == 32)
        sentence2[i+1] = sentence2[i+1] - 32;
    }
    cout<<"Output Line: ";
    for(int i = 0; i < 100; i++)
    {
        if(sentence1[i]!=0)cout << (char)sentence1[i];
    }
    cout << " ";
    for(int i = 0; i < 100; i++)
    {
        if(sentence2[i]!=0)cout << (char)sentence2[i];
    }
    return 0;
}
