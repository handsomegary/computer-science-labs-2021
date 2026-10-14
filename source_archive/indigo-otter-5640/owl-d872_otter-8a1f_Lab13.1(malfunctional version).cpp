#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int i = 7, matched_numbers = 0, totalprize = 0;
    char blabla[40], invoicelist[90], lottery[8], *invoices;
    cin.getline(blabla, 41);
    for(int i = 30, j = 0; i <= 37, j <= 7; i++, j++)
    {
        lottery[j] = blabla[i];
        //cout << blabla[i];
    }cin.getline(invoicelist, 91);
    invoices = strtok(invoicelist, " ");
    while(invoices[i] == lottery[i]&&i>=0)
    {
        i--;matched_numbers++;
    }//cout << matched_numbers;
    switch (matched_numbers)
    {
        case 0: break;
        case 3: totalprize+=200; cout << invoices << " won 2 hundred dollars!" << endl; break;
        case 4: totalprize+=1000; cout << invoices << " won 1 thousand dollars!" << endl; break;
        case 5: totalprize+=4000; cout << invoices << " won 4 thousand dollars!" << endl; break;
        case 6: totalprize+=10000; cout << invoices << " won 10 thousand dollars!" << endl; break;
        case 7: totalprize+=40000; cout << invoices << " won 40 thousand dollars!" << endl; break;
        case 8: totalprize+=200000; cout << invoices << " won 200 thousand dollars!" << endl; break;
        default:break;
    }
    while(invoicelist != NULL)
    {
        invoices = strtok(NULL, " ");
        while(invoices[i] == lottery[i]&&i>=0)
        {
            i--;matched_numbers++;
        }//cout<<matched_numbers<<endl;
        switch (matched_numbers)
        {
            case 0: break;
            case 3: totalprize+=200; cout << invoices << " won 2 hundred dollars!" << endl; break;
            case 4: totalprize+=1000; cout << invoices << " won 1 thousand dollars!" << endl; break;
            case 5: totalprize+=4000; cout << invoices << " won 4 thousand dollars!" << endl; break;
            case 6: totalprize+=10000; cout << invoices << " won 10 thousand dollars!" << endl; break;
            case 7: totalprize+=40000; cout << invoices << " won 40 thousand dollars!" << endl; break;
            case 8: totalprize+=200000; cout << invoices << " won 200 thousand dollars!" << endl; break;
            default: break;
        }
    }
    if(totalprize == 0)cout<<endl<<"Won nothing. But, less is more.";
    else cout<<"You totally won "<<totalprize<<" dollars !!!";
    return 0;
}
