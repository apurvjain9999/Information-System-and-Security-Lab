//Monoalphabetic Cipher
//Made By: Apurv Jain
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
        if (!(P[i] >= 'a' && P[i] <= 'z')) //Checking for special characters
            C[i] = P[i];
        else                               //For alphabets
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
            C[i] = K[g];    //Encrypting
        }
        ofile<<C[i];    //Storing the data
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
        if (!(C[i] >= 'a' && C[i] <= 'z')) //Checking for special characters
            P[i] = C[i];
        else                               //For alphabets
        {
            g = C[i];   
            for(j=0; j<26; j++)            //Decryption
            {
                if (g == K[j])
                {
                    P[i] = 97 + j;
                    break;
                }
            }
        }
        ofile<<P[i];                       //Writing to the file
        cout<<P[i];
    }
    ofile<<"\n";
}

int main()
{
    string key;
    cout<<"----------- Monoalphabetic Cipher -----------"<<endl;
    string input, output;
    cout<<"\nEnter input file name: ";  //Input file name
    cin>>input;
    cout<<"\nEnter output file name: "; //Output file name
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
            if (ans == 'E' || ans == 'e' || ans == 'D' || ans == 'd') //Checking ans given by user
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
                cout<<"\nPlease Press valid key\n"; //Only valid ans allowed
            }
        } 
        if (ans == 'E' || ans == 'e') //Encryption 
        {
            int f = 0;
            int i = 0;
            while (f == 0)
            {
                //cout<<"\nEnter the key: ";
                //cin>>key;
                string key_f;
                cout<<"\nEnter file name of key: "; //File name for the key
                cin>>key_f;
                ifstream kf;
                kf.open(key_f.c_str()); //opening the file to get the key
                kf>>key;
                //Checking or pre-processing the key
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
            fin.open(input.c_str()); //File to be encrypted
            fout.open(output.c_str()); //File where encrypted text will be stored
            cout<<"\nEncrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s);    //Get data line by line
                encrypt(key, s, fout); //Encryption function
            }
            
            fin.close();
            fout.close();
        }
        else
        {
            ifstream fin;
            ofstream fout;
            fin.open(output.c_str()); //File to be decrypted
            fout.open(input.c_str()); //File where decrypted text will be stored
            cout<<"\nDecrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s); //Get data line by line
                
                decrypt(key, s, fout); //Decryption function
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
