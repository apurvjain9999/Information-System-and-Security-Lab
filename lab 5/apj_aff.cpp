//Affine Cipher
//Made By: Apurv Jain 
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    gcd(b%a, a);
}

void encrypt(int a, int b, string P, ofstream &ofile) //Encryption
{
    string mod = "";
    int i = 0;
    int k = P.length();
    for(i=0; i<k; i++)
    {
        if (!(P[i] >= 'a' && P[i] <= 'z')) //Eliminating Special Characters
        {
            continue;
        }

        else
        {
            mod.append(P.substr(i, 1));   
        }
    }
    char lett;
    int p = 0;
    int h = 0;
    //cout<<mod<<"\n";
    for(i=0; i<mod.length(); i++) //Encryption
    {
       lett = mod[i];
       p = lett - 97;
       h = ((a * p) + b) % 26;
       ofile<<(char)(h+65);
       cout<<(char)(h+65);
    }
    ofile<<"\n";
    cout<<"\n";
}

void decrypt(int a, int b, string C, ofstream &ofile) //Decryption
{
    int i = 0;
    int g = 0;
    int h = 0;
    char lett;
    int j = 0;
    int l = 0;
    for(j=1; j<=a; j++)
    {
        if((((a*j)-1) % 26) == 0)
        {
            g = j;
            break;
        }
    }
    //cout<<g;
    for(i=0; i<C.length(); i++)
    {
        lett = C[i];
        h = lett - 65;
        l = (g * (h - b)) % 26;
        if (l < 0)
            l += 26;
        ofile<<(char)(l + 97);
        cout<<(char)(l + 97);
    }
    ofile<<"\n";
    cout<<"\n";
}



int main()
{
    int key[10];
    int a;
    int b;
    cout<<"------------ Affine Cipher -----------"<<endl;
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
            int i = 0;
            int t = 0;
            int v = -1;
            int j = 0;
            int g = 0;
            for(i=0; i<10;)
            {
                t = rand() % 26;
                v = gcd(t, 26);
                g = 0;
                if (v != 1)
                    continue;
                else
                {
                    for(j=1; j<=t; j++)
                    {
                        if ((((t*j) - 1) % 26) == 0)
                        {
                            g = j;
                            break;
                        }
                    }

                    if (g != 0)
                    {
                        key[i] = t;
                        i++;
                        continue;
                    }
                    else
                    {
                        continue;
                    }
                    
                }
            }
            /*for(i=0; i<10; i++)
            {
                cout<<"\n"<<a[i];
            }
            cout<<endl;*/
            a = key[2];
            //cout<<endl<<a<<endl;
            while(1)
            {
                cout<<"\nEnter the value of b: ";
                cin>>b;
                if (b > a)
                {
                    cout<<"\nPlease enter another value";
                    continue;
                }
                else
                {
                    break;
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
                //s = "i am a student";
                encrypt(a, b, s, fout);
            }  
            fin.close();
            fout.close();
        }

        else //Decryption
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
                decrypt(a, b, s, fout);
            }
            
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