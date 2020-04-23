//Hill Cipher
//Made By: Apurv Jain
#include<iostream>
#include<fstream>
using namespace std;

int det(int k, int key[3][3]) //For calculating determinant
{
    int de = 0;
    if (k == 2)
    {
        de = (key[0][0] * key[1][1]) - (key[0][1] * key[1][0]);
        return de;
    }
    else
    {
        de = (key[0][0] * ((key[1][1] * key[2][2]) - (key[1][2] * key[2][1]))) -
             (key[0][1] * ((key[1][0] * key[2][2]) - (key[1][2] * key[2][0]))) +
             (key[0][2] * ((key[1][0] * key[2][1]) - (key[1][1] * key[2][0])));
        cout<<"\nDeterminant: "<<de<<endl;
        return de;
    }
}

void mul(int *calc, int key[3][3], int k, int *ans) //Multiply step in Hill Cipher
{
    int i = 0;
    int j = 0;
    int l = 0;
    cout<<"\n";
    for(i=0; i<k; i++)
    {
        ans[i] = 0;
        for(j=0; j<k; j++)
        {
            ans[i] += (calc[j] * key[j][i]);
        }
        //cout<<ans[i]<<endl;
        ans[i] %= 26;
        cout<<ans[i]<<"\t";
    }

}

void inverse (int key[3][3], int in[3][3], int k, int t) //Calculating Inverse of Matrix
{
    int temp[k][k];
    if (k == 2)
    {
        in[0][0] = key[1][1];
        in[0][1] = - key[0][1];
        in[1][0] = - key[1][0];
        in[1][1] = key[0][0];
        return;
    }
    else
    {
        int i = 0;
        int j = 0;

        for(i=0; i<3; i++)
        {
            temp[0][i] = ((key[1][(i+1)%3]) * (key[2][(i+2)%3])) - ((key[1][(i+2)%3]) * (key[2][(i+1)%3]));

        }

        for(i=0; i<3; i++)
        {
            temp[1][i] = ((key[0][(i+1)%3]) * (key[2][(i+2)%3])) - ((key[2][(i+1)%3]) * (key[0][(i+2)%3]));
        }

        for(i=0; i<3; i++)
        {
            temp[2][i] = ((key[0][(i+1)%3]) * (key[1][(i+2)%3])) - ((key[1][(i+1)%3]) * (key[0][(i+2)%3]));
        }
        cout<<"\n";
        for(i=0; i<3; i++)
        {
            for(j=0; j<3; j++)
            {
                in[i][j] = t *temp[j][i];
                //cout<<in[i][j]<<"\t";
            }
            cout<<"\n";
        }

        return;
    }

}

void encrypt(int key[3][3], string P, ofstream &ofile, int k)  //For Encryption
{
    //cout<<P<<"\n";
    string mod = "";
    char *C;
    long int i;
    long int kp = P.length();
    C = new char[kp];
    int flag = 0;
    long int j = 0;
    for(i=0; i<kp; i++)
    {
        if (!(P[i] >= 'a' && P[i] <= 'z'))      //Eliminating Special Characters
        {
            continue;
        }
        else                //Alphabets
        {
            mod.append(P.substr(i, 1));
            j++;
        }
    }
    //cout<<"\n"<<mod<<"\n";
    if (j%k != 0)   //Preparing the Plain Text
    {
        int s = j % k;
        if (k == 2)
            mod.push_back('x');

        else
        {
            if (s == 1)
            {
                mod.push_back('x');
                mod.push_back('x');
            }
            else
            {
                mod.push_back('x');
            }
        }
    }
    int *calc = new int[k];
    int l;
    for(i=0; i<mod.length(); i+=k)  //Encryption
    {
        l = i;
        for(j=0; j<k; j++)
        {
            calc[j] = mod[l] - 97;
            //cout<<calc[j]<<" ";
            l++;
        }
        cout<<"\n";
        int *ans = new int[k];
        mul(calc, key, k, ans);   //Multiplying key and plain text matrix
        for(j=0; j<k; j++)
        {
            C[i+j] = ans[j] + 65;
            cout<<C[i+j];
            ofile<<C[i+j];
            //cout<<ans[j];
        }
    }
    cout<<"\n";
    ofile<<"\n";
}

void decrypt(int key[3][3], int k, const char C[], int l, ostream &ofile) //For decryption
{
    char *P = new char[k+1];
    int i=0;
    int j;
    int *temp = new int[k];
    int *ans = new int[k];
    for(i=0; i<l; i += k)     //Preparing Cipher Text
    {
        for(j=0; j<k; j++)
        {
            temp[j] = 0;
            ans[j] = 0;
            temp[j] = C[i+j] - 65;
        }

        mul(temp, key, k, ans);  //Multiplying key and cipher text matrix

        for(j=0; j<k; j++)      //Getting Plain text
        {
            P[i+j] = ans[j] + 97;
            ofile<<P[i+j];      //Writing to a file
            cout<<P[i+j];
        }
    }
    cout<<"\n";
}

int main()
{
    int k;
    string kf;
    cout<<"------------ Hill Cipher -----------"<<endl;
    string input, output;
    cout<<"\nEnter input file name: ";  //Input file name
    cin>>input;
    cout<<"\nEnter output file name: "; //Output file name
    cin>>output;
    char ans = 'A';
    int flag = 0;
    int key[3][3];
    int dete;
    do
    {
        char exi = 'E';
        while (ans != 'E' || ans != 'e' || ans != 'D' ||  ans != 'D') 
        {
            cout<<"\nPress E for Encryption"<<endl;
            cout<<"Press D for Decryption\n"<<endl;
            cin>>ans;
            if (ans == 'E' || ans == 'e' || ans == 'D' || ans == 'd') //Checking for ans
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
            cout<<"\nEnter the size of the key: ";   //Size of the key
            cin>>k;
            cout<<"\nEnter file name for the key: ";  //File name to get the key
            cin>>kf;
            ifstream inf;
            inf.open(kf.c_str());   
            /**key = new int[k];
            int m = 0;
            for(m=0; m<k; m++)
            {
                key[m] = new int[k];
            }*/
            int check[k*k];         //For checking the key
            int i=-1, j=0;
            int kt = 0;
            /*while(inf)
            {
                kt = 0;

            }*/
            int l = 0;
            int fl = 0;
            //cout<<"Enter the key matrix: (Enter -1 to end)"<<endl;
            i = 0;
            while(inf>>kt)  //Getting the key
            {
                if (i != k*k)
                {
                    check[i] = kt;
                    i++;
                }
                else
                {
                    cout<<"\nThe matrix is not a square matrix\n";
                    fl = 1;
                    flag = 0;
                    cout<<"\n Try again!\n";
                    break;
                }
            }
            if (i < k*k)
            {
                cout<<"\n Too few numbers in key\n";
                fl = 1;
                flag = 0;
                cout<<"\n Try again!\n";
            }
            if (fl == 1)
                continue;
            for(i=0; i<k; i++)
            {
                for(j=0; j<k; j++)
                {
                    key[i][j] = check[l];   //Preparing key matrix
                    l++;
                }
            }

            dete = det(k, key);     //Getting the determinant
            if (dete == 0)          //Checking for Inverse
            {
                fl = 1;
                flag = 0;
                cout<<"\nThe Inverse of this matrix is not possible\n";
                cout<<"Try Again!\n";
            }

            if (fl == 1)
                continue;

            ifstream fin;
            ofstream fout;
            fin.open(input.c_str());
            fout.open(output.c_str());
            cout<<"\nEncrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s);    //Getting data line by line
                //s = "i am a student";
                encrypt(key, s, fout, k);
            }

            fin.close();
            fout.close();
        }
        else
        {
            int inv[3][3];
            //*inv = new int[k];
            int i;
            /*for(i=0; i<k; i++)
            {
                inv[i] = new int[k];
            }*/
            int temp = dete % 26;   
            for (i=1; i<=temp; i++)
            {
                if ((((temp*i) - 1) % 26) == 0)
                {
                    temp = i;
                    break;
                }
            }
            inverse(key, inv, k, temp); //Caluculating inverse 

            ifstream fin;
            ofstream fout;
            fin.open(output.c_str());
            //fout.open(input.c_str());
            fout.open("de.txt");
            cout<<"\nDecrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s);    //Getting line by line data
                //s = "OXDBLFDQBOQSWY";
                decrypt(inv, k, s.c_str(), s.length(), fout);
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