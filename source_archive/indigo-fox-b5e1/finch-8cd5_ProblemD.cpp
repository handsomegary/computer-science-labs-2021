#include <iostream>
#include <string>


using namespace std;

int main() {
    int counter = 0;

    string aa;
    string bb;

    cin >> aa;
    cin >> bb;

    int array1[26] = {};
    int array2[26] = {};

    for (int i = 0;i < aa.length();i++) {
        if (aa[i] == 'a') {
            array1[0] += 1;
        }
        if (aa[i] == 'b') {
            array1[1] += 1;
        }
        if (aa[i] == 'c') {
            array1[2] += 1;
        }
        if (aa[i] == 'd') {
            array1[3] += 1;
        }
        if (aa[i] == 'e') {
            array1[4] += 1;
        }
        if (aa[i] == 'f') {
            array1[5] += 1;
        }
        if (aa[i] == 'g') {
            array1[6] += 1;
        }
        if (aa[i] == 'h') {
            array1[7] += 1;
        }
        if (aa[i] == 'i') {
            array1[8] += 1;
        }
        if (aa[i] == 'j') {
            array1[9] += 1;
        }
        if (aa[i] == 'k') {
            array1[10] += 1;
        }
        if (aa[i] == 'l') {
            array1[11] += 1;
        }
        if (aa[i] == 'm') {
            array1[12] += 1;
        }
        if (aa[i] == 'n') {
            array1[13] += 1;
        }
        if (aa[i] == 'o') {
            array1[14] += 1;
        }
        if (aa[i] == 'p') {
            array1[15] += 1;
        }
        if (aa[i] == 'q') {
            array1[16] += 1;
        }
        if (aa[i] == 'r') {
            array1[17] += 1;
        }
        if (aa[i] == 's') {
            array1[18] += 1;
        }
        if (aa[i] == 't') {
            array1[19] += 1;
        }
        if (aa[i] == 'u') {
            array1[20] += 1;
        }
        if (aa[i] == 'v') {
            array1[21] += 1;
        }
        if (aa[i] == 'w') {
            array1[22] += 1;
        }
        if (aa[i] == 'x') {
            array1[23] += 1;
        }
        if (aa[i] == 'y') {
            array1[24] += 1;
        }
        if (aa[i] == 'z') {
            array1[25] += 1;
        }
    }
    for (int i = 0;i < bb.length();i++) {
        if (bb[i] == 'a') {
            array2[0] += 1;
        }
        if (bb[i] == 'b') {
            array2[1] += 1;
        }
        if (bb[i] == 'c') {
            array2[2] += 1;
        }
        if (bb[i] == 'd') {
            array2[3] += 1;
        }
        if (bb[i] == 'e') {
            array2[4] += 1;
        }
        if (bb[i] == 'f') {
            array2[5] += 1;
        }
        if (bb[i] == 'g') {
            array2[6] += 1;
        }
        if (bb[i] == 'h') {
            array2[7] += 1;
        }
        if (bb[i] == 'i') {
            array2[8] += 1;
        }
        if (bb[i] == 'j') {
            array2[9] += 1;
        }
        if (bb[i] == 'k') {
            array2[10] += 1;
        }
        if (bb[i] == 'l') {
            array2[11] += 1;
        }
        if (bb[i] == 'm') {
            array2[12] += 1;
        }
        if (bb[i] == 'n') {
            array2[13] += 1;
        }
        if (bb[i] == 'o') {
            array2[14] += 1;
        }
        if (bb[i] == 'p') {
            array2[15] += 1;
        }
        if (bb[i] == 'q') {
            array2[16] += 1;
        }
        if (bb[i] == 'r') {
            array2[17] += 1;
        }
        if (bb[i] == 's') {
            array2[18] += 1;
        }
        if (bb[i] == 't') {
            array2[19] += 1;
        }
        if (bb[i] == 'u') {
            array2[20] += 1;
        }
        if (bb[i] == 'v') {
            array2[21] += 1;
        }
        if (bb[i] == 'w') {
            array2[22] += 1;
        }
        if (bb[i] == 'x') {
            array2[23] += 1;
        }
        if (bb[i] == 'y') {
            array2[24] += 1;
        }
        if (bb[i] == 'z') {
            array2[25] += 1;
        }
    }
    for (int i = 0;i < 26;i++) {
        if (array1[i] == array2[i] && array1[i] > 0) {
            counter += array1[i];
        }
    }

    if (counter == aa.length()) {
        cout << "Yes! It's anagram.";
    }
    else {
        cout << "No! It is not anagram.";
    }
    return 0;
}
