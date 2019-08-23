#include<iostream>
#include<fstream>

using namespace std;

void encrypt(string K, string P, ofstream &ofile)
{
    string C = "";
    int i;
    int length = P.length();
    int g;
    int j;
    for(i=0; i<length; i++)
    {
        if (P[i] == ' ')
            C[i] = P[i];
        else 
        {
            g = P[i] - 32 - 65;;
            /*for(j=0; j<26; j++)
            {
                if (g == K[j])
                {
                    C[i] = K[j];
                    break;
                }
            }*/
            C[i] = K[g];
        }
        ofile<<C[i];
        cout<<C[i];
    }
    ofile<<"\n";
}

void decrypt(string K, string C, ofstream &ofile)
{   
    string P = "";
    int i;
    int length = C.length();
    char g;
    int j;
    for(i=0; i<length; i++)
    {
        if (C[i] == ' ')
            P[i] = C[i];
        else 
        {
            g = C[i];
            for(j=0; j<26; j++)
            {
                if (g == K[j])
                {
                    P[i] = 97 + j;
                    break;
                }
            }
        }
        ofile<<P[i];
        cout<<P[i];
    }
    ofile<<"\n";
}

int main()
{
    string key;
    cout<<"----------- Caesar Cipher -----------"<<endl;
    string input, output;
    cout<<"\nEnter input file name: ";
    cin>>input;
    cout<<"\nEnter output file name: ";
    cin>>output;
    char ans = 'A';
    int flag = 0;
    do 
    {
        char exi = 'E';
        while (ans != 'E' || ans != 'e' || ans != 'D' ||  ans != 'D')
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
            int f = 0;
            int i = 0;
            while (f == 0)
            {
                //cout<<"\nEnter the key: ";
                //cin>>key;
                string key_f;
                cout<<"\nEnter file name of key: ";
                cin>>key_f;
                ifstream kf;
                kf.open(key_f.c_str());
                kf>>key;
                int arr[26];
                for(i=0; i<26; i++)
                    arr[i] = 0;
                if (key.length() != 26)
                {
                    cout<<"\nThe Key must be of exactly 26 alphabets\n";
                    f = 0;
                }
                else
                {
                    int g = 0;
                    for(i=0; i<26; i++)
                    {
                        g = key[i] - 65;
                        if (arr[g] == 0)
                        {
                            arr[g] = 1;
                            f = 1;
                        }
                        else 
                        {
                            cout<<"The key cannot contain repeated alphabets";
                            f = 0;
                        }
                    }
                }
                
            }
            ifstream fin;
            ofstream fout;
            fin.open(input.c_str());
            fout.open(output.c_str());
            cout<<"\nEncrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s);
                encrypt(key, s, fout);
            }
            
            fin.close();
            fout.close();
        }
        else
        {
            ifstream fin;
            ofstream fout;
            fin.open(output.c_str());
            fout.open(input.c_str());
            cout<<"\nDecrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s);
                
                decrypt(key, s, fout);
            }
            
            fin.close();
            fout.close();
        }
        cout<<"\nWant to exit the program ? (Y/N)"<<endl;
        cin>>exi;
        if (exi == 'Y' || exi == 'y')
            break; 
            
    }while(1);
    return 0;
}
