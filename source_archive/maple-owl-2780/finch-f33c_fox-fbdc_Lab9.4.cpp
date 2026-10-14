#include <iostream>
#include<iomanip>
using namespace std;
void spiral_pattern(int,int);
int main()
{
    int d;
    while(1){
        cout<<"Input dimension: ";
        cin>>d;


        if(d==-1){
            break;
        }
        int a,counter=0;
        a=d*d;
        while(a!=0){


            a/=10;
            counter++;
        }
      spiral_pattern(d,counter);


    }
    return 0;
}
void spiral_pattern(int size,int counter){
	cout<<endl;
    int row = 0, col = 0;

    int boundary = size - 1;
    int sizeLeft = size - 1;
    int flag = 1;
    bool shrink=false;
    enum Move{r, l, u, d};
    Move move = r;

  
    int matrix[size][size] = {0};

    for (int i = 1; i < size * size + 1; i++)
    {

       
        matrix[row][col] = i;
      
        switch (move)
        {
        
            case r:
                col ++;
                break;
         
            case l:
                col --;
                break;
          
            case u:
                row --;
                break;
            
            case d:
                row ++;
                break;
        }

        
        if (i == boundary)
        {

            boundary += sizeLeft;

            if (shrink==0)
            {
                shrink= true;
            }
            else
            {
                shrink= false;
                sizeLeft --;
            }

            switch (move)
            {
                case r:
                    move = d;
                    break;

                case d:
                    move = l;
                    break;

                case l:
                    move = u;
                    break;

                case u:
                    move = r;
                    break;
            }
        }
    }

    for (row = 0; row < size; row++)
    {
        for (col = 0; col < size; col++)
        {

            int n = matrix[row][col];

                cout <<setfill('0')<<setw(counter)<< n << " ";

        }

        cout << endl;
    }
	cout<<endl;
}

