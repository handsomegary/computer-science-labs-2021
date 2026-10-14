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
    // Variable to determine the movement
    // r = right, l = left, d = down, u = upper
    char move = 'r';
    // Array for matrix
    int spiralgraph[size][size] = {0};
    for (int i = 1; i < size * size + 1; i++)
    {
        // Assign the value
        spiralgraph[row][col] = i;
        // switch-case to determine the next index
        switch (move)
        {
            // If right, go right
            case 'r':
                col += 1;
                break;
            // if left, go left
            case 'l':
                col -= 1;
                break;
            // if up, go up
            case 'u':
                row -= 1;
                break;
            // if down, go down
            case 'd':
                row += 1;
                break;
        }
        // Check if the matrix
        // has reached array boundary
        if (i == boundary)
        {
            // Add the left size for the next boundary
            boundary += sizeLeft;
            // If 2 rotations has been made,
            // decrease the size left by 1
            if (flag != 2)
            {
                flag = 2;
            }
            else
            {
                flag = 1;
                sizeLeft -= 1;
            }
            // switch-case to rotate the movement
            switch (move)
            {
                // if right, rotate to down
                case 'r':
                    move = 'd';
                    break;
                // if down, rotate to left
                case 'd':
                    move = 'l';
                    break;
                // if left, rotate to up
                case 'l':
                    move = 'u';
                    break;
                // if up, rotate to right
                case 'u':
                    move = 'r';
                    break;
            }
        }
    }
    // Print the matrix(spiralgraph)
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
    // Get the size of size
    int size;
    while(size != -1)
    {
        cout << "Input dimension: ";
        cin >> size;
        cout << endl;
        // Print the Spiral Pattern
        printspiralgraph(size);
        cout << endl;
        if(size == -1)
        {
            return 0;
        }
    }
    return 0;
}
