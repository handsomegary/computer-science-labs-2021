#include <iostream>
using namespace std;

struct bloodtype
{
    char daddy_DNA, mommy_DNA;
	double A, B, O, AB;//the chances of the blood type
};
void calculate(bloodtype *child, char MOM, char DAD);

int main()
{
    float A=0,B=0,O=0,AB=0;
    char bloodtype[3][3];
    char bloodtype1[3][3];
    cin.getline(bloodtype[1],4);
    cin.getline(bloodtype[2],4);
    for(int i=1;i<=2;i++)
    {
        for(int j=0;j<2;j++)
        {
            if(bloodtype[i][j]=='A')bloodtype1[i][j]=1;
            if(bloodtype[i][j]=='B')bloodtype1[i][j]=3;
            if(bloodtype[i][j]=='i')bloodtype1[i][j]=0;
        }
    }
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            switch(bloodtype1[1][i]+bloodtype1[2][j])
            {
            case 0:O+=0.25;break;
            case 1:A+=0.25;;break;
            case 2:A+=0.25;;break;
            case 3:B+=0.25;;break;
            case 4:AB+=0.25;;break;
            case 6:B+=0.25;;break;
            default:break;
            }
        }
    }
    cout<<endl;
    cout<<"A: "<<A<<endl;
    cout<<"B: "<<B<<endl;
    cout<<"O: "<<O<<endl;
    cout<<"AB: "<<AB<<endl;

    return 0;
}
void calculate(bloodtype *child, char MOM, char DAD)
{
    return;
}
