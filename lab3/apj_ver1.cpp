#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
void encrypt(const char *key, string P, ofstream &ofile, int m)
{
    string mod = "";
    int i = 0;
    int k = P.length();
    for(i=0; i<k; i++)
    {
        if (P[i] == ' ')
        {
            continue;
        }

        else
        {
            mod.append(P.substr(i, 1));   
        }
    }
    char lett;
    int n;
    int c;
    int j = 0;
    for(i=0; i<mod.length(); i++)
    {
        lett = mod[i];
        n = lett - 97;
        
        //cout<<"\t";
        c = n ^ (int)key[j];
        j++;
        if (j == m)
            j = 0;
        //cout<<"\t"<<c<<"\t";
        //if (c >= 26)
            //c -= 26;
        //cout<<"\t"<<c<<"\t;
        cout<<(char)(c);
        ofile<<(char)(c);
    }
    cout<<"\n";
    ofile<<"\n";
}

void decrypt(const char *key, string C, ofstream &ofile, int m)
{
    int i = 0;
    char lett;
    int n;
    int j = 0;
    int p;
    for(i=0; i<C.length(); i++)
    {
        lett = C[i];
        n = lett;

        //cout<<"\t";
            
        //cout<<"\t"<<c<<"\t";
        //if (p >= 26)
            //p -= 26;
        //cout<<"\t"<<c<<"\t";
        p = n ^ key[j];
        j++;
        if (j == m)
            j = 0;
        cout<<(char)(p + 97);
        ofile<<(char)(p + 97);
    }
    cout<<"\n";
    ofile<<"\n";
}

int main()
{
    string key;
    int m = 0;
    int i; 
    cout<<"------------ Vernam Cipher -----------"<<endl;
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
            char ka = 'A';
            cout<<"\nShall I generate a key for encryption ? (Y/N) : ";
            cin>>ka;
            if (ka == 'n' || ka == 'N')
            {
                cout<<"\nEnter the key: \n";
                cin>>key;
                m = key.length();
                    /*p = binaryToDecimal(key);
                    if (p >= 26)
                    {
                        cout<<"\nYou entered incorrect key\n";
                        cout<<"Please enter the key again\n";
                        h = 1;
                    }*/    
                
            }
            else
            {
                int g;
                for (i=0; i<8; i++)
                {
                    g = (rand() % 256);
                    key.push_back((char)g);
                }
                m = 8;
                cout<<"\nWe have generated a key for you\n";
                //cout<<key<<endl;
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
                //s = "i am a student";
                encrypt(key.c_str(), s, fout, m);
            }
            
            fin.close();
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
                decrypt(key.c_str(), s, fout, m);
            }
            
            fin.close();
            fout.close();
            //flag = 0;
        }
        cout<<"\nWant to exit the program ? (Y/N)"<<endl;
        cin>>exi;
        if (exi == 'Y' || exi == 'y')
            break;
        else
        {
            continue;
        }
        
        
            
    }while(1);

    return 0;
}