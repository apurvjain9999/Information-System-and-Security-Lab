#include<iostream>
#include<fstream>
#include<cstdlib>
#include<bits/stdc++.h>
using namespace std;

bool isValid(vector <int> key)
{
    vector <int> k;
    int i;
    int v[key.size()];
    for(i=0; i<key.size(); i++)
    {
        v[i] = 0;
        k.push_back(key[i]);
    }
    int flag = 0;
    sort(k.begin(), k.end());
    if(k[0] == 0)
        return false;
    for(i=0; i<k.size(); i++)
    {
        if (v[k[i] - 1] == 0)
        {
            v[k[i] - 1] = 1;
        }
        else
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        return true;
    else
    {
        return false;
    }
    
}

void encrypt(vector <int> key, string P, ofstream &ofile)
{
    string mod = "";
    int i = 0;
    int kp = P.length();
    for(i=0; i<kp; i++)
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
    int kl = key.size();
    int pl = mod.length();
    int r = (pl % kl == 0) ? pl/kl : pl/kl + 1;
    //cout<<"\n"<<r<<"\n";
    char mat[r][kl];
    char lett;
    int j = 0;
    int k = 0;
    for(i=0; i<r; i++)
    {
        for(j=0; j<kl; j++)
        {
            if (k < pl)
            {
                lett = mod[k];
                mat[i][j] = lett;
                k++;
            }
            else
            {
                mat[i][j] = 'x';
            }
        }
    }
    /*for(i=0; i<r; i++)
    {
        for(j=0; j<kl; j++)
        {
            cout<<mat[i][j];
        }
    }*/
    int check[kl];
    int l = 0 ;
    cout<<"\n";
    for(i=1; i<=kl; i++)
    {
        for(j=0; j<kl; j++)
        {
            if (key[j] == i)
            {
                check[l] = j;
                //cout<<check[l];
                l++;
                break;
            }
        }
    }
    l = 0;
    cout<<"\n";
    for(l=0; l<kl; l++)
    {
        for(i=0; i<r; i++)
        {
            ofile<<(char)(mat[i][check[l]]-32);
            cout<<(char)(mat[i][check[l]]-32);
        }
    }
    cout<<"\n";
    ofile<<"\n";
}

void decrypt(vector <int>key, string C, ofstream &ofile)
{
    int i = 0;
    int kl = key.size();
    int cl = C.length();
    int r = (cl % kl == 0) ? cl/kl : cl/kl + 1;
    int j=0;
    int check[kl];
    int l = 0 ;
    cout<<"\n";
    for(i=1; i<=kl; i++)
    {
        for(j=0; j<kl; j++)
        {
            if (key[j] == i)
            {
                check[l] = j;
                //cout<<check[l];
                l++;
                break;
            }
        }
    }
    int mat[r][kl];
    l = 0;
    int q = 0;
    char lett;
    for(i=0; i<kl; i++)
    {
        for(j=0; j<r; j++)
        {
            lett = C[l];
            mat[j][check[q]] = lett;
            l++;
        }
        q++;
    }
    l = 0;
    for(i=0; i<r; i++)
    {
        for(j=0; j<kl; j++)
        {
            ofile<<(char)(mat[i][j] + 32);
            cout<<(char)(mat[i][j] + 32);
        }
    }
    ofile<<"\n";
    cout<<"\n";
}

int main()
{
    vector <int> key;
    int kf = 0;
    int m;
    cout<<"------------ Rail Fence Cipher -----------"<<endl;
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
            int i=0;
            if (ka == 'n' || ka == 'N')
            {
                int h = 1;
                int f3 = 1;
                while(f3 == 1)
                {
                    cout<<"\nEnter the key (Enter -1 to stop): \n";
                    while(h)
                    {
                        cin>>i;
                        if (i == -1)
                            break;
                        key.push_back(i);
                    }
                    bool v = isValid(key);
                    if (v == false)
                    {
                        cout<<"\nEnter valid Key\n";
                        continue;
                    }    
                    else
                    {
                        f3 = 0;
                        break;
                    }
                }
            }
            else
            {
                int i=0;
                int h = 0;
                int j=0;
                cout<<"\nKey:";
                for(i=0; i<5;)
                {
                    h = (rand() % 5) + 1;
                    if(i == 0)
                    {
                        key.push_back(h);
                        cout<<key[i];
                        i++;
                    }
                    else
                    {
                        int f4 = 1;
                        vector<int>::iterator it; 
                        while(f4 == 1)
                        {
                            it = find(key.begin(), key.end(), h);
                            if (it == key.end())
                            {
                                f4 = 0;
                                break;
                            }
                            else
                            {
                                h = (rand() % 5) + 1; 
                            }
                        }
                        key.push_back(h);
                        //cout<<key[i];
                        i++;
                    }
                    
                    
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
                encrypt(key, s, fout);
            }
            
            fout.close();
            fin.close();
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
                decrypt(key, s, fout);
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