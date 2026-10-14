#include <iostream>
#include<vector>
using namespace std;

int main()
{
    int size,med;
    cout << "Enter a number:" << endl;
    cin>>size;
    vector <int> arrey(size);
    for(int i=0;i<size;i++)
        cin>>arrey[i];
    for(int i=0;i<size;i++)
	{
		for(int j=size-1;j>i;j--)
		{
			if(arrey[j-1]>arrey[j])
			{
				int a=arrey[j-1];
				arrey[j-1]=arrey[j];
				arrey[j]=a;
			}
		}
	}
	cout<<"After sorting:"<<endl;
	for(auto n:arrey)
        cout<<n<<" ";
    if(size%2==0)
    med=(arrey[size/2-1]+arrey[size/2])/2;
    else
        med=arrey[(size+1)/2-1];
    cout<<"\nMedian value of this series is: "<<med;


    return 0;
}
