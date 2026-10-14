#include<iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int main(){
 	int a[50] = {0}, show[50] = {0}, number = 0, sum = 0;
 	while(true)
    {
        cin >> a[number];
        number++;
        char ch = getchar();
        if(ch == '\n')
        {
            break;
        }
    }
 	sort(a, a + number);
 	for(int i = 0; i <= number; i++)
    {
        sum = sum + a[i];
    }
 	for(int i = 0,j = 0; i < number; i+=2, j++)
    {
        show[i] = *max_element(a + j, a + number - j);
        show[i+1] = *min_element(a + j, a + number - j);
    }
    for(int i = 0; i < number; i++)
    {
        cout << show[i] << " ";
 	}
	return 0;
}
