#include <iostream>

using namespace std;


int main()
{
    long long int a[2];long long int b[2];
    cout << "Enter rows and columns for first matrix:" << endl;
    cin >>*a>>*(a+1);
    cout << "Enter rows and columns for second matrix:" << endl;
    cin>>*b>>*(b+1);

    if(*(a+1)==*b and (a[0]!=0 && a[1]!=0 && b[0]!=0 && b[1]!=0)){
       long long int m1[*a][*(a+1)];long long int m2[*b][*(b+1)];
        cout<<"\nEnter matrix 1:"<<endl;
        for(int i=0;i<(*a);i++){
            for(int j=0;j<*(a+1);j++)
                cin>>*(*(m1+i)+j);

        }

        cout<<"\nEnter matrix 2:"<<endl;
        for(int i=0;i<(*b);i++){
            for(int j=0;j<*(b+1);j++)
                cin>>*(*(m2+i)+j);

        }

        cout<<"\nOutput Matrix:"<<endl;
        long long int c[*a][*(b+1)];
        for(int i=0;i<*a;i++){

            for(int j=0;j<*(b+1);j++){
                *(*(c+i)+j) =0;

            }

        }

        for(int i=0;i<*a;i++){

            for(int j=0;j<*(b+1);j++){
                *(*(c+i)+j) =0;
                for(int k=0;k<*(b);k++)
                    *(*(c+i)+j) += (*(*(m1+i)+k) * *(*(m2+k)+i));

            }

        }
        for(int i=0;i<*a;i++)
        {
            for(int j=0;j<*(b+1);j++)
            {
                cout<<*(*(c+i)+j)<<" ";
            }
            cout<<"\n";
        }

        }
    else{
        cout<<"Cannot multiply these two matrixes."<<endl;
    }










    return 0;
}
