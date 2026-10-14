#include <iostream>
using namespace std;
int b[100] = {0};
int c = 1;
int start = 0;
int cont = 0;
int mux = 0;
void find_mountain(int *const num, int *const length, int a[100])
{

        for(int i = 0; i <= 10; i++)
        {
            b[i]=1;
        }
        for(int i = 2; i <= 98; i++)
        {
            if(a[i - 1] < a[i] && a[i] >= a[i + 1])
            {
                cont++;
            }
            if(a[i - 1] > a[i] && a[i] < a[i + 1])
            {
                b[c] = i;
                c++;
            }
            if(a[i + 2] == 0 && a[i + 1] == 0 && a[i] > a[i-1])
            {
                cont--;
            }
        }
}
void comparison(int a[100])
{
    for(int i = 0; i <= 100; i++)
    {
        if((b[i + 1] - b[i]) > mux)
        {
            mux = b[i + 1] - b[i];
            start = b[i];
        }
    }
}
int main()
{
    int a[101] = {0}, digit = 1, num = 0, length = 0;
    while(true)
    {
        cin >> a[digit];
        digit++;
        char ch = getchar();
        if(ch == '\n')
        {
            break;
        }
    }
    find_mountain(&num, &length, a);
    cout << cont << endl;
    if(cont == 1)
    {
        cout << digit << endl;
        for(int i = 1; i < 101; i++)
        {
            cout << b[digit] <<" ";
        }
    }
    else if(cont != 1)
    {
        comparison(a);
        for(int i = 0; i <= mux; i++)
        {
            cout << a[start + i] <<" ";
        }
    }
    return 0;
}
