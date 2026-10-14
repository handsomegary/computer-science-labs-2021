#include <iostream>
#include <iomanip>
using namespace std;

void find_mountain(int*const, int *const, int[]);
int peak = 0, height = 0, node = 0;
int main()
{
    int a[101] = {'\n'}, num = 0, length = 0;
    while(true)
    {
        cin >> a[height];
        height++;
        char ch = getchar();
        if(ch == '\n')
        {
            break;
        }
    }
    find_mountain(&num, &length, a);
    return 0;
}
void find_mountain(int *const num, int *const length, int a[])
{
    int mountainlength = 1;
    for(int i = 1; i < height - 2; i++)
    {
        if(a[i] < a[i + 1] && a[i + 1] > a[i + 2])
        {
            peak++;// how many mountains
            int backward = i + 1;
            cout << "a[" << backward << "]" << endl;
            while(a[backward] >= a[backward - 1] && backward >= 0)
            {
                backward--;
                mountainlength++;
            }
            cout << mountainlength << endl;
            int toward = i + 1;
            while(a[toward + 1] <= a[toward] && toward <= height)
            {
                toward++;
                mountainlength++;
            }
            cout << mountainlength << endl;
            cout << "mountainlength: " << mountainlength << endl;
            mountainlength = 0;
        }
    }
    cout << peak;
}
