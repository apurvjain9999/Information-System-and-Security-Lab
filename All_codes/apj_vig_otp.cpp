//Vigenere Cipher (One Time Pad)
//Made By: Apurv Jain
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

void encrypt(char **key, string P, ofstream &ofile, int kf) //Encryption
{
    string mod = "";
    int i = 0;
    int k = P.length();
    for(i=0; i<k; i++)
    {
        if (!(P[i] >= 'a' && P[i] <= 'z')) //Excluding special characters
        {
            continue;
        }

        else
        {
            mod.append(P.substr(i, 1));   
        }
    }
    char lett;
    int g = 0;
    int h = 0;
    key[kf] = new char[mod.length() + 1];
    for(i=0; i<mod.length(); i++) //Generating key of size of the plain text
    {
        key[kf][i] = (rand() % 26) + 65;

    }
    key[kf][i] = '\0';
    //cout<<key[kf]<<endl;
    for(i=0; i<mod.length(); i++) //Encryption Process
    {
        g = 0;
        h = 0;
        lett = mod[i];
        //cout<<lett;
        h = ((lett - 97) + key[kf][i] - 65) % 26; //Adding the subsequent characters
        //C[i] = h + 65;
        ofile<<(char)(h+65);
        cout<<(char)(h+65);
    }
    ofile<<"\n";
    cout<<"\n";
}

void decrypt(char **key, string C, ofstream &ofile, int kf) //Decryption
{
    int i = 0;
    int g = 0;
    int h = 0;
    char lett;
    //cout<<"\n"<<key[kf]<<endl;
    for(i=0; i<C.length(); i++) //Decryption Process
    {
        lett = C[i];
        //cout<<lett;
        //cout<<g;
        h = ((lett - 65) - (key[kf][i] - 65)) % 26; //Subtracting subsequent characters
        //cout<<h;
        if (h < 0)
            h += 26;
        ofile<<(char)(h+97);
        cout<<(char)(h+97);
    }
    ofile<<"\n";
    cout<<"\n";
}

int main()
{
    char **key;
    int kf = 0;
    int m;
    cout<<"------------ Vigenere Cipher (One Time Pad) -----------"<<endl;
    string input, output;
    cout<<"\nEnter input file name: "; //Input file
    cin>>input;
    cout<<"\nEnter output file name: "; //Output file
    cin>>output;
    char ans = 'A';
    int flag = 0;
    do 
    {
        char exi = 'E';
        while (ans != 'E' || ans != 'e' || ans != 'D' ||  ans != 'D') //User file
        {
            cout<<"\nPress E for Encryption"<<endl;
            cout<<"Press D for Decryption\n"<<endl;
            cin>>ans;
            if (ans == 'E' || ans == 'e' || ans == 'D' || ans == 'd')
            {
                if ((ans == 'D' || ans == 'd') && flag == 0)
                {
                    cout<<"\nFirst Encrypt the file\n";
                    continue;
                }
                flag = 1;
                break;
            }
            else
            {
                cout<<"\nPlease Press valid key\n";
            }
        } 
        if (ans == 'E' || ans == 'e')
        {
            ifstream fin;
            ofstream fout;
            fin.open(input.c_str());
            fout.open(output.c_str());
            cout<<"\nEncrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s);
                //s = "i am a student";
                //encrypt(key, s, fout, kf);
                kf++;
            }
            fin.close();
            fin.open(input.c_str());
            key = new char *[kf];
            kf = 0;
            while(fin)
            {
                string s;
                getline(fin, s);
                //s = "i am a student";
                encrypt(key, s, fout, kf);
                kf++;
            }
            kf = 0;
            fout.close();
        }
        else
        {
            ifstream fin;
            ofstream fout;
            fin.open(output.c_str());
            //fout.open(input.c_str());
            fout.open("de.txt");
            cout<<"\nDecrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s);
                //s = "OXDBLFDQBOQSWY";
                decrypt(key, s, fout, kf);
                kf++;
            }
            kf = 0;
            fin.close();
            fout.close();
            //flag = 0;
        }
        cout<<"\nWant to exit the program ? (Y/N)"<<endl;
        cin>>exi;
        if (exi == 'Y' || exi == 'y')
            break;
        
            
    }while(1);

    return 0;
}