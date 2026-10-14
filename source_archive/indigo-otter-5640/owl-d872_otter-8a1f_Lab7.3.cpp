#include <iostream>

using namespace std;


int number_of_addition = 1;
int number_of_subtracttion = 1;

void add(int &number, int &number_of_addition)
{
	number = number + number_of_addition;
}
void sub(int &number, int &number_of_substracttion)
{
	number = number - number_of_subtracttion;
}
void factorization(int number)
{
	if(number <= 0)
    {
        cout << "No factorization" << endl;
    }
    else
    {
        int i;
        cout << number << " = ";
        for (i = number; i >= 2; i --)
        {
            if(number%i == 0)
            {
                cout << number/i << ",";
            }
        }
        cout << number << endl;
    }

}

int main()
{
    int number = 0, choose;
    while(true)
        {
            cout << "The number now is " << number << endl;
            cout << "Choose a function:" << endl;
            cout << "1. Add    2. Sub    3. Factorization    4. Exit" << endl << endl ;
            cin >> choose;
            while(choose != 1 && choose != 2 && choose != 3 && choose != 4)
            {
                cout << "Enter error!!" << endl << "The number now is " << number << endl;
                cout << "Choose a function:" << endl;
                cout << "1. Add    2. Sub    3. Factorization    4. Exit" << endl <<endl ;
                cin >> choose;
            }
            if (choose == 1)
            {
                add(number, number_of_addition);
                number_of_addition ++;
            }
            else if (choose == 2)
            {
                sub(number, number_of_subtracttion);
                number_of_subtracttion ++;
            }
            else if (choose == 3)
            {
                factorization(number);
            }
            else if (choose == 4)
            {
                return 0;
            }
            else{}

        }
        return 0;
}

