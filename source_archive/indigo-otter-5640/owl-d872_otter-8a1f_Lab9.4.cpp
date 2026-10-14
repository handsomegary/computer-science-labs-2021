#include <iostream>
#include <iomanip>
using namespace std;

void printspiralgraph(int size)
{
    // Create row and col
    // to traverse rows and columns
    int row = 0, col = 0;
    int boundary = size - 1;
    int sizeLeft = size - 1;
    int flag = 1;
    char move = 'r';
    int spiralgraph[size][size] = {0};
    for (int i = 1; i < size * size + 1; i++)
    {
        spiralgraph[row][col] = i;
        switch (move)
        {
            case 'r':
                col += 1;
                break;
            case 'l':
                col -= 1;
                break;
            case 'u':
                row -= 1;
                break;
            case 'd':
                row += 1;
                break;
        }
        if (i == boundary)
        {
            boundary += sizeLeft;
            if (flag != 2)
            {
                flag = 2;
            }
            else
            {
                flag = 1;
                sizeLeft -= 1;
            }
            switch (move)
            {
                case 'r':
                    move = 'd';
                    break;
                case 'd':
                    move = 'l';
                    break;
                case 'l':
                    move = 'u';
                    break;
                case 'u':
                    move = 'r';
                    break;
            }
        }
    }
    if(size < 4)
    {
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                int n = spiralgraph[row][col];
                cout << n << " ";
            }
        cout << endl;
        }
    }
    else if(size < 10 && size > 3)
    {
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                int n = spiralgraph[row][col];
                cout << setfill('0') << setw(2) << n << " ";
            }
        cout << endl;
        }
    }
    else
    {
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                int n = spiralgraph[row][col];
                cout << setfill('0') << setw(3) << n << " ";
            }
        cout << endl;
        }
    }
}
int main()
{
    int size;
    while(size != -1)
    {
        cout << "Input dimension: ";
        cin >> size;
        cout << endl;
        printspiralgraph(size);
        cout << endl;
        if(size == -1)
        {
            return 0;
        }
    }
    return 0;
}
