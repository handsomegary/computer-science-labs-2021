#include<iostream>
using namespace std;

struct bloodtype
{
    char daddy_DNA, mommy_DNA;
    double A, B, O, AB;//the chances of the blood type
};

void calculate(bloodtype *child, char mom, char dad)
{
    if((mom==65&&dad==66)||(mom==66&&dad==65))  //ab
    {
        child->AB=child->AB+1;
    }
    else if(mom==105&&dad==105)       //o
    {
        child->O=child->O+1;
    }
    else if((mom==65&&dad==105)||(mom==105&&dad==65)||(mom==65&&dad==65))   //a
    {
        child->A=child->A+1;
    }
    else
    {
        child->B=child->B+1;
    }
}

int main()
{
    struct bloodtype MOM, DAD, child;
    child.A=0;
    child.AB=0;
    child.B=0;
    child.O=0;
    char input1[3], input2[3];
    cin>>input1>>input2;
    cout<<input1<<"   "<<input2<<endl;
    calculate(&child, input1[0], input2[0]);
    calculate(&child, input1[0], input2[1]);
    calculate(&child, input1[1], input2[0]);
    calculate(&child, input1[1], input2[1]);
    cout<<"A: "<<child.A/4<<endl;
    cout<<"B: "<<child.B/4<<endl;
    cout<<"O: "<<child.O/4<<endl;
    cout<<"AB: "<<child.AB/4<<endl;
    return 0;
}

