//Vigenere Cipher
//Made By: Apurv Jain 
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

void encrypt(const char *key, string P, ofstream &ofile, int m) //Encryption
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
    int g = 0;
    int h = 0;
    //cout<<mod<<"\n";
    for(i=0; i<mod.length(); i++) //Encryption
    {
        g = 0;
        h = 0;
        lett = mod[i];
        //cout<<lett;
        g = i % m;
        h = ((lett - 97) + key[g] - 65) % 26;
        //C[i] = h + 65;
        ofile<<(char)(h+65);
        cout<<(char)(h+65);
    }
    ofile<<"\n";
    cout<<"\n";
}

void decrypt(const char *key, string C, ofstream &ofile, int m) //Decryption
{
    int i = 0;
    int g = 0;
    int h = 0;
    char lett;
    for(i=0; i<C.length(); i++)
    {
        lett = C[i];
        g = i % m;
        //cout<<lett;
        //cout<<g;
        h = ((lett - 65) - (key[g] - 65)) % 26;
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
    string key;
    int m;
    cout<<"------------ Vigenere Cipher -----------"<<endl;
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
            cout<<"\nShall I generate a key for encryption ? (Y/N) : "; //Asking for key
            cin>>ka;
            if (ka == 'n' || ka == 'N')
            {
                cout<<"\nEnter the key: "; //Getting key from user
                cin>>key;
            }
            else //Generating a key of size 5
            { 
                int g;
                int i; 
                for (i=0; i<5; i++)
                {
                    g = (rand() % 26);
                    key.push_back(g + 65);
                }
                cout<<"\nWe have generated a key for you\n";
                //cout<<key<<endl;
            }
            
            
            ifstream fin;
            ofstream fout;
            fin.open(input.c_str());
            fout.open(output.c_str());
            cout<<"\nEncrypted text: ";
            m = key.length();
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
        
            
    }while(1);

    return 0;
}