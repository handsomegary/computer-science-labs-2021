// Based on the original and the prescribed sample_code_13_2.cpp variables.
#include <iostream>
#include <iomanip>
using namespace std;
struct bloodtype {
    char daddy_DNA, mommy_DNA;
    double A, B, O, AB;
};
void calculate(bloodtype *child, char MOM, char DAD) {
    if (MOM == 'i' && DAD == 'i') child->O += 0.25;
    else if ((MOM == 'A' && DAD == 'B') || (MOM == 'B' && DAD == 'A')) child->AB += 0.25;
    else if (MOM == 'A' || DAD == 'A') child->A += 0.25;
    else if (MOM == 'B' || DAD == 'B') child->B += 0.25;
}
int main() {
    struct bloodtype MOM = {}, DAD = {}, child = {};
    // The supplied unsized arrays were incomplete declarations: reserve two genes + NUL.
    char input1[3] = {}, input2[3] = {};
    if (!(cin >> setw(3) >> input1 >> setw(3) >> input2)) return 0;
    MOM.mommy_DNA = input1[0]; MOM.daddy_DNA = input1[1];
    DAD.mommy_DNA = input2[0]; DAD.daddy_DNA = input2[1];
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            calculate(&child, i == 0 ? MOM.mommy_DNA : MOM.daddy_DNA,
                      j == 0 ? DAD.mommy_DNA : DAD.daddy_DNA);
    cout << "\nA: " << child.A << "\nB: " << child.B << "\nO: " << child.O << "\nAB: " << child.AB << '\n';
}
