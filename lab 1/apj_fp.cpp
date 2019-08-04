#include<iostream>
using namespace std;

void encrypt(string key[5][5], string P, ofstream &ofile, int **space, int k)
{
    int len = P.length();
    int i = 0;
    int c = 0;
    for(i=0; i<len; i++)
    {
        if(P[i] == ' ')
            space[k][i] = 1;
        else
        {
            c++;
        }
    }
    if (c % 2 == 0)
    {
        space[k][len] = 0;
    }
    else
    {
        space[k][len] = 1;
    }
    string C = "";
    for(i=0; i<len; i++)
    {
        if (P[i] == ' ')
            continue;
        else
        {
            C.push_back(P[i]);
        }
    }
    if (c % 2 != 0)
        C.push_back('z');
    int j, l;
    int row_1 = -1;
    int flag = -1;
    int f = -1;
    int col_1;
    int row_2, col_2;
    for(i=0; i<c; i=i+2)
    {
        for(j=0; j<5; j++)
        {
            for(l=0; l<5; i++)
            {
                if (key[j][l] == C[i])
                {
                    row_1 = j;
                    col_1 = l;
                }

                if (key[j][l] == C[i+1])
                {
                    row_2 = j;
                    col_2 = l;
                }
            }
        }

        if (row_1 == row_2)
        {
            if (col_1 == 4)
                col_1 = -1;
            if (col_2 == 4)
                col_2 = -1;
            
            C[i] = key[row_1][col_1 + 1];
            ofile<<C[i];
            cout<<C[i];
            C[i+1] = key[row_2][col_2 + 1];
            ofile<<C[i+1];
            cout<<C[i+1];
        }        

        else if (col_1 == col_2)
        {
            if (row_1 == 4)
                row_1 = -1;
            
            if (row_2 == 4)
                row_2 = -1;
            
            C[i] = key[row_1 + 1][col_1];
            ofile<<C[i];
            cout<<C[i];
            C[i+1] = key[row_2 + 1][col_2];
            ofile<<C[i+1];
            cout<<C[i+1];
        }

        else 
        {
            C[i] = key[row_1][col_2];
            ofile<<C[i];
            cout<<C[i];
            C[i+1] = key[row_2][col_1];
            ofile<<C[i+1];
            cout<<C[i+1];
        }
    }

    
}

int main()
{
    cout<<"------- Fair Play Cipher --------"<<endl;
    string key[5][5];
    int arr[26];
    int i=0;
    for(i=0; i<26; i++)
        arr[i] = 0;
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
            int j = 0;
            char g;
            int h;
            while (f == 0)
            {
                cout<<"\nEnter the key: ";
                for(i=0; i<5; i++)
                {
                    for(j=0; j<5; j++)
                    {
                        cin.get(g);
                        h = g - 65;
                        if (arr[h] == 1)
                        {
                            cout<<"\nPlease enter unique alphabets as key only\n";
                            f = 0;
                            break;
                        }
                        else
                        {
                            arr[h] = 1;
                            key[i][j].push_back(g);
                            f = 1;
                        }
                    }
                }    
            }
            ifstream fin;
            ofstream fout;
            fin.open(input.c_str());
            fout.open(output.c_str());
            cout<<"\nEncrypted text: ";
            int max = 0;
            int l_c = 0;
            while(fin)
            {
                string s;
                getline(fin, s);
                l_c++;
                if (s.length() > max)
                    max = s.length();
            }
            fin.clear();
            fin.seekg(0, ios::beg);
            int **space;
            space = new int*[l_c];
            for(i=0; i<l_c; i++)
            {
                space[i] = new int[max+1];
                for(j=0; j<(max+1); j++)
                    space[i][j] = 0;
            }
            int k=0;
            while(fin)
            {
                string s;
                getline(fin, s);
                encrypt(key, s, fout, space, k);
                k++;
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