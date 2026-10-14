#include <iostream>

using namespace std;
void selectionsort(int *, const int, bool(*)(int, int), bool(*)(int, int));
bool big(int,int);
bool small(int,int);
void swap(int*,int*);
int main()
{
     int number[21]= {0};//des
     int copyarray[21]={0};//asd
     int num=0;

    while(1)
    {
        cin>>number[num++];
        if(getchar()=='\n')
            break;
    }

    for(int i=0;i<num;i++)
    {
        copyarray[i]=number[i];
    }

    selectionsort(number, num,big,small);
    selectionsort(copyarray, num,small,big);
    if(num%2==1)
    for(int i=0;i<num;i++)
    {
        if(number[i]!=copyarray[i])
        {
            cout<<number[i]<<" "<<copyarray[i]<<" ";
        }
        else if(number[i]==copyarray[i])
        {
            cout<<number[i];
           break;
        }

    }
    else
    for(int i=0;i<num/2;i++)
    {
        cout<<number[i]<<" "<<copyarray[i]<<" ";
    }



    return 0;
}
void selectionsort(int *arrayptr, const int size, bool(*compare)(int, int), bool(*compare2)(int, int))
{
  int smallorlarge;
  for(int i=0;i<size-1;i++)
  {
      smallorlarge=i;
      for(int index=i+1;index<size;index++)
          if(!(*compare)(arrayptr[smallorlarge],arrayptr[index]))
            smallorlarge=index;


      swap(&arrayptr[smallorlarge],&arrayptr[i]);
  }
}
bool big(int a,int b)
{
   return a>b;

}
bool small(int a,int b)
{
    return a<b;
}
void swap(int*ptr1,int*ptr2)
{
    int hold=*ptr1;
    *ptr1=*ptr2;
    *ptr2=hold;
}
