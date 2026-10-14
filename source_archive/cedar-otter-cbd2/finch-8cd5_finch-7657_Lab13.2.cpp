#include<iostream>

using namespace std;

struct bloodtype {
    char daddy_DNA, mommy_DNA;
    double A = 0;
    double B = 0;
    double O = 0;
    double AB = 0;//the chances of the blood type
};

void calculate(bloodtype& child, char MOM[], char DAD[]) {
    if (MOM[1] == 'A') {
        if (DAD[1] == 'A') {
            child.A += 0.25;
        }
        if (DAD[0] == 'A') {
            child.A += 0.25;
        }
        if (DAD[0] == 'i') {
            child.A += 0.25;
        }
        if (DAD[1] == 'i') {
            child.A += 0.25;
        }
        if (DAD[1] == 'B') {
            child.AB += 0.25;
        }
        if (DAD[0] == 'B') {
            child.AB += 0.25;
        }
    }
    if (MOM[0] == 'A') {
        if (DAD[1] == 'A') {
            child.A += 0.25;
        }
        if (DAD[0] == 'A') {
            child.A += 0.25;
        }
        if (DAD[0] == 'i') {
            child.A += 0.25;
        }
        if (DAD[1] == 'i') {
            child.A += 0.25;
        }
        if (DAD[1] == 'B') {
            child.AB += 0.25;
        }
        if (DAD[0] == 'B') {
            child.AB += 0.25;
        }
    }
    if (MOM[0] == 'B') {
        if (DAD[1] == 'A') {
            child.AB += 0.25;
        }
        if (DAD[0] == 'A') {
            child.AB += 0.25;
        }
        if (DAD[0] == 'i') {
            child.B += 0.25;
        }
        if (DAD[1] == 'i') {
            child.B += 0.25;
        }
        if (DAD[1] == 'B') {
            child.B += 0.25;
        }
        if (DAD[0] == 'B') {
            child.B += 0.25;
        }
    }
    if (MOM[1] == 'B') {
        if (DAD[1] == 'A') {
            child.AB += 0.25;
        }
        if (DAD[0] == 'A') {
            child.AB += 0.25;
        }
        if (DAD[0] == 'i') {
            child.B += 0.25;
        }
        if (DAD[1] == 'i') {
            child.B += 0.25;
        }
        if (DAD[1] == 'B') {
            child.B += 0.25;
        }
        if (DAD[0] == 'B') {
            child.B += 0.25;
        }
    }
    if (MOM[0] == 'i') {
        if (DAD[1] == 'A') {
            child.A += 0.25;
        }
        if (DAD[0] == 'A') {
            child.A += 0.25;
        }
        if (DAD[0] == 'i') {
            child.O += 0.25;
        }
        if (DAD[1] == 'i') {
            child.O += 0.25;
        }
        if (DAD[1] == 'B') {
            child.B += 0.25;
        }
        if (DAD[0] == 'B') {
            child.B += 0.25;
        }
    }
    if (MOM[1] == 'i') {
        if (DAD[1] == 'A') {
            child.A += 0.25;
        }
        if (DAD[0] == 'A') {
            child.A += 0.25;
        }
        if (DAD[0] == 'i') {
            child.O += 0.25;
        }
        if (DAD[1] == 'i') {
            child.O += 0.25;
        }
        if (DAD[1] == 'B') {
            child.B += 0.25;
        }
        if (DAD[0] == 'B') {
            child.B += 0.25;
        }
    }
}
struct bloodtype MOM, DAD, child;
int main() {
    char input1[2], input2[2];
    cin >> input1[0] >> input1[1];
    cin >> input2[0] >> input2[1];
    calculate(child, input1, input2);
    cout << endl;
    cout << "A: " << child.A << endl;
    cout << "B: " << child.B << endl;
    cout << "O: " << child.O << endl;
    cout << "AB: " << child.AB << endl;
    return 0;
}
