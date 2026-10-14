#include <iostream>
#include <string>
#include <vector>

using namespace std;
class encrypt
{
public:
    encrypt(string);
    void encryption();
    void decryption();
    void print_information();
private:
    string information;
    int key = 3;
};
encrypt::encrypt(string str)
{
    information=str;
}
void encrypt::encryption()
{
    for(int i=0;i<information.length();i++)
    {
        if(information[i]==32)
        continue;
        else
        {
            if(i%2==0)
                information[i]=information[i]+key*key;
            else
               information[i]=information[i]-key;
        }
    }
}
void encrypt::decryption()
{
    for(int i=0;i<information.length();i++)
    {
        if(information[i]==32)
        continue;
        else
        {
            if(i%2==0)
                information[i]=information[i]-key*key;
            else
               information[i]=information[i]+key;
        }
    }
}
void encrypt::print_information()
{
    cout<<information<<endl;
}

int main()
{
    int control;

    string str;
    cout << "Welcome to encryption system!" << endl;
    cout<<"Enter 1 to encrypt"<<endl;
    cout<<"Enter 2 to decrypt"<<endl;
    (cin>>control).get();
    cout<<endl;
    cout<<"Input information: ";
    getline(cin,str);
    encrypt no1(str);
    if(control==1)
    {
        cout<<"Encrypted information: ";
        no1.encryption();
        no1.print_information();
    }
    else
    {
        cout<<"Decrypted information: ";
        no1.decryption();
        no1.print_information();
    }
    return 0;
}
