#include <iostream>

using namespace std;
void selectionSort(int*,const int,bool(*)(int,int),bool(*)(int,int));
void swap(int *const,int *const);
bool ascending(int,int);
bool descending(int,int);

int main()
{
    const int arraysize=20;
    int m=0;
    int inputvalue[arraysize]={0};
    int n;
    while(1){
        cin>>n;
        inputvalue[m]=n;
        m++;

        if(cin.get()=='\n')
            break;

    }
    const int arraySize=m;
    selectionSort(inputvalue,arraySize,descending,ascending);


    int x=0;
    int odd=arraySize-1;
    int even=0;
/*
    for(int i=0;i<arraySize;i++){
        cout<<inputvalue[i]<<" ";

    }
    cout<<endl;
*/
    while(x<arraySize){


        if(x%2==0){
            cout <<inputvalue[even]<<" ";
            even++;
        }
        else{
            cout <<inputvalue[odd]<<" ";
            odd--;
        }
        x++;
    }



    return 0;
}

void selectionSort(int* work ,const int size,bool(*compare)(int,int),bool(*useless)(int,int)){

    int smallestOrLargest;

    for(int i=0;i<size-1;i++){
        smallestOrLargest = i;

        for(int index=i+1;index<size;index++)
            if(!(*compare)(work[smallestOrLargest],work[index]))
                smallestOrLargest = index;

        swap(&work[smallestOrLargest],&work[i]);

    }

}
void swap(int * const element1Ptr,int *const element2Ptr){
    int hold= *element1Ptr;
    *element1Ptr=*element2Ptr;
    *element2Ptr=hold;

}
bool ascending(int a,int b){
    return a<b;
}
bool descending(int a,int b){
    return a>b;
}
