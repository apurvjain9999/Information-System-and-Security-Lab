#include<iostream>
#include<fstream>
using namespace std;

void encrypt(char key[5][5], string P, ofstream &ofile)
{
    
    //cout<<"\n"<<P;
    string mod = "";
    char *C;
    long int i;
    long int k = P.length();
    C = new char[k];
    int flag = 0;
    long int j = 0;
    for(i=0; i<k;)
    {
        if (P[i] == ' ')
        {
            i++;
            continue;
        }

        else
        {
            mod.append(P.substr(i, 1));
            if (P[i] == P[i+1] || (i+1) == k) 
            {
                mod.push_back('x');
                i++;
                j += 2;
                continue;
            } 
            else if (P[i+1] == ' ')   
            {
                int w = i+1;
                while (P[w] == ' ')
                    w++;
                
                mod.append(P.substr(w, 1));
                i = w+1;;
                j += 2;
            }
            else
            {
                mod.append(P.substr(i+1, 1));
                i += 2;
                j += 2;
            }
        }
    }
    //cout<<"\n"<<mod<<endl;
    int c1, r1;
    int c2, r2;
    int f1 = 0, f2 = 0;
    char s1, s2;
    for(i=0; i<mod.length(); i+=2)
    {
        s1 = mod[i];
        s2 = mod[i+1];
        if (mod[i] == 'j')
            s1 = 'i';
        if (mod[i+1] == 'j')
            s2 = 'i';
    
        f1 = 0;
        f2 = 0;
        for(j=0; j<5; j++)
        {
            for (k=0; k<5; k++)
            {
                if (s1 == key[j][k] + 32)
                {
                    r1 = j;
                    c1 = k;
                    f1 = 1;
                }
                else if (s2 == key[j][k] + 32)
                {
                    r2 = j;
                    c2 = k;
                    f2 = 1;
                }

                if (f1 == 1 && f2 == 1)
                    break;
            }
            if (f1 == 1 && f2 == 1)
                break;
        }
        
        if (r1 == r2)
        {
            if (c1 == 4)
                c1 = -1;
            if (c2 == 4)
                c2 = -1;
            
            C[i] = key[r1][c1 + 1];
            ofile<<C[i];
            cout<<C[i];
            C[i+1] = key[r2][c2 + 1];
            ofile<<C[i+1];
            cout<<C[i+1];
        }        

        else if (c1 == c2)
        {
            if (r1 == 4)
                r1 = -1;
            
            if (r2 == 4)
                r2 = -1;
            
            C[i] = key[r1 + 1][c1];
            ofile<<C[i];
            cout<<C[i];
            C[i+1] = key[r2 + 1][c2];
            ofile<<C[i+1];
            cout<<C[i+1];
        }

        else 
        {
            C[i] = key[r1][c2];
            ofile<<C[i];
            cout<<C[i];
            C[i+1] = key[r2][c1];
            ofile<<C[i+1];
            cout<<C[i+1];
        }
    }
    cout<<"\n";
    ofile<<"\n";
}

void decrypt(char key[5][5], string C_c, ofstream &ofile)
{
    //cout<<"\n"<<C_c;
    char *P;
    long int i;
    long int z = C_c.length();
    //cout<<"\n"<<z<<"\n";
    P = new char[z];
    const char *C = C_c.c_str();
    int flag = 0;
    long int j = 0;
    
    int c1, r1;
    int c2, r2;
    int f1 = 0, f2 = 0;
    char s1, s2;
    int k;
    for(i=0; i<z; i+=2)
    {
        s1 = C[i];
        s2 = C[i+1];

        f1 = 0;
        f2 = 0;
        for(j=0; j<5; j++)
        {
            for (k=0; k<5; k++)
            {
                if (s1 == key[j][k])
                {
                    r1 = j;
                    c1 = k;
                    f1 = 1;
                }
                else if (s2 == key[j][k])
                {
                    r2 = j;
                    c2 = k;
                    f2 = 1;
                }

                if (f1 == 1 && f2 == 1)
                    break;
            }
            if (f1 == 1 && f2 == 1)
                break;
        }
        
        if (r1 == r2)
        {
            if (c1 == 0)
                c1 = 5;
            if (c2 == 0)
                c2 = 5;
            
            P[i] = key[r1][c1 - 1] + 32;
            ofile<<P[i];
            cout<<P[i];
            P[i+1] = key[r2][c2 - 1] + 32;
            ofile<<P[i+1];
            cout<<P[i+1];
        }        

        else if (c1 == c2)
        {
            if (r1 == 0)
                r1 = 5;
            
            if (r2 == 0)
                r2 = 5;
            
            P[i] = key[r1 - 1][c1] + 32;
            ofile<<P[i];
            cout<<P[i];
            P[i+1] = key[r2 - 1][c2] + 32;
            ofile<<P[i+1];
            cout<<P[i+1];
        }

        else 
        {
            P[i] = key[r1][c2] + 32;
            ofile<<P[i];
            cout<<P[i];
            P[i+1] = key[r2][c1] + 32;
            ofile<<P[i+1];
            cout<<P[i+1];
        }
    }
    ofile<<"\n";
    cout<<"\n";
}

int main()
{
    string key;
    cout<<"------------ PlayFair Cipher -----------"<<endl;
    string input, output;
    cout<<"\nEnter input file name: ";
    cin>>input;
    cout<<"\nEnter output file name: ";
    cin>>output;
    char ans = 'A';
    int flag = 0;
    char mat[5][5];
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
            cout<<"\nEnter the key: ";
            cin>>key;
            int alp[26];
            int i;
            for(i=0; i<26; i++)
            {
                alp[i] = 0;
            }
            int j = 0, k = 0;
            for(i=0; i<key.length(); i++)
            {
                if (k == 5)
                {
                    k = 0;
                    j++;
                }

                if (alp[key[i] - 65] == 0)
                {
                    if (key[i] == 'I')
                        alp[key[i] - 65 + 1] = 1;
                    
                    if (key[i] == 'J')
                        alp[key[i] - 65 - 1] = 1;

                    if (key[i] == 'J')
                        mat[j][k] = 'I';
                    else
                        mat[j][k] = key[i];

                    k++;
                    alp[key[i] - 65] = 1;
                }
                else
                {
                    continue;
                }
            }
            /* cout<<"\n";
            for(i=0; i<5; i++)
            {
                for(j=0; j<5; j++)
                {
                    cout<<mat[i][j];
                }
                cout<<"\n";
            }*/

            for(i=0; i<26; i++)
            {
                if (k == 5)
                {
                    k = 0;
                    j++;
                }
                if(alp[i] == 0)
                {
                    if(i == (int)('I' - 65) && alp[i+1] == 1)
                        continue;
                    else if (i == (int)('J' - 65) && alp[i - 1] == 1)
                        continue;
                    else
                    {
                        alp[i] = 1;
                        mat[j][k] = i + 65;
                        k++;
                        if (i == (int)('I' - 65))
                            alp[i+1] = 1;
                        else if (i == (int)('J' - 65))
                            alp[i-1] = 1;
                    }
                    
                }
                else
                {
                    continue;
                }
                
            }
            cout<<"\n";
            for(i=0; i<5; i++)
            {
                for(j=0; j<5; j++)
                {
                    cout<<mat[i][j];
                }
                cout<<"\n";
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
                encrypt(mat, s, fout);
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
                decrypt(mat, s, fout);
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