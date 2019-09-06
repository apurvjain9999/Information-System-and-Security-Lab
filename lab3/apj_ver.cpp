#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

void decToBinary(int n, int *a, int m)
{
    int i=0;
    int k=0;
    int j=0;
    cout<<"\n";
    for(i=m-1; i>=0; i--)
    {
        j = n >> i;
        if (j & 1)
            a[k] = 1;
        else
        {
            a[k] = 0;
        }
        k++;
        cout<<a[k];
    }
}

int binaryToDecimal(int *b, int m)
{
    int a = 0;
    int i = 0;
    int k = 16;
    int t = 0;
    cout<<"\n";
    for(i=0; i<m; i++)
    {
        t = k * b[i];
        a += t;
        k /= 2;
        cout<<b[k];
    }
    return a;
}

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
    int a[m];
    int b[m];
    int j;
    int c;
    int d[m];
    for(i=0; i<mod.length(); i++)
    {
        lett = mod[i];
        n = lett - 97;
        decToBinary(n, a, m);
        decToBinary(key[i] - 97, d, m);
        for(j=0; j<m; j++)
        {
            b[j] = a[j] ^ d[j]; 
            //cout<<b[j];
            cout<<"\n"<<b[j];
        }
        //cout<<"\t";
        c = binaryToDecimal(b, m);
        //cout<<"\t"<<c<<"\t";
        //if (c >= 26)
            //c -= 26;
        //cout<<"\t"<<c<<"\t"
        c = (c % 74) + 48;
        cout<<"\n";
        cout<<(char)(c);
        cout<<"\n";
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
    int a[m];
    int b[m];
    int d[m];
    int j;
    int p;
    for(i=0; i<C.length(); i++)
    {
        lett = C[i];
        n = lett;
        decToBinary(n, a, m);
        decToBinary(key[i] - 97, d, m);
        for(j=0; j<m; j++)
        {
            b[j] = a[j] ^ d[j]; 
            //cout<<b[j];
        }
        //cout<<"\t";
        p = binaryToDecimal(b, m);
        //cout<<"\t"<<c<<"\t";
        //if (p >= 26)
            //p -= 26;
        //cout<<"\t"<<c<<"\t";
        p = (p % 74) + 48;
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