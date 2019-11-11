#include<iostream>
#include<fstream>
#include<string.h>
#include<stdint-gcc.h>
using namespace std;

#define aff_t(x, s) ((int) ((x) << (s)) | ((x) >> (8 - (s))))

char Key[16][3]; //For storing key of a particular round
char round[11][33]; //For  storinf key of all rounds
int RC[10] = {1, 2, 4, 8, 16, 32, 64, 128, 27, 54}; //Round Count

//Forward Mix Column Multiplication Table
int F_MixCol[4][4] = {
    {2, 3, 1, 1} ,
    {1, 2, 3, 1} ,
    {1, 1, 2, 3} ,
    {3, 1, 1, 2}
};

//Reverse Mix Column Multiplication Table
int R_MixCol[4][4] = {
    {14, 11, 13, 9} ,
    {9, 14, 11, 13} ,
    {13, 9, 14, 11} ,
    {11, 13, 9, 14} 
};

int Exp[255] = {0}; //Exponential Table
int Log[255] = {0}; //Logarthimatic Table

//Decimal to Binary
void dec2bin(int a, int *p)
{
    int i;
    for(i=7; i>=0; i--)
    {
        p[i] = a % 2;
        a /= 2;
    }
}

//Binary to Decimal
int bin2dec(int *p)
{
    int l = 0;
    int i;
    int j = 128;
    for(i=0; i<8; i++)
    {
        l += (p[i] * j);
        j /= 2;
    }
    return l;
}

//Hexadecimal to Binary
void hex2bin(char *n1, char *num)
{
    string n = "";
    int i = 0;
    for(i=0; i<2; i++)
    {
        switch(n1[i])
        {
            case '0': n += "0000";
            break;
            case '1': n += "0001";
            break;
            case '2': n += "0010";
            break;
            case '3': n += "0011";
            break;
            case '4': n += "0100";
            break;
            case '5': n += "0101";
            break;
            case '6': n += "0110";
            break;
            case '7': n += "0111";
            break;
            case '8': n += "1000";
            break;
            case '9': n += "1001";
            break;
            case 'A': n += "1010";
            break;
            case 'B': n += "1011";
            break;
            case 'C': n += "1100";
            break;
            case 'D': n += "1101";
            break;
            case 'E': n += "1110";
            break;
            case 'F': n += "1111";
            break;
        }
    }
    strcpy(num, n.c_str());
    //cout<<n<<endl;
}

//Binary to Hexadecimal
void bin2hex(int *a, char *n3)
{
    int i, j, k = 0;
    string nm3 = "";
    int n = 8;
    int sum = 0;
    for(i=0; i<2; i++)
    {
        n = 8;
        sum = 0;
        for(j=0; j<4; j++)
        {
            sum += a[k] * n;
            k++;
            n /= 2;            
        }
        switch(sum)
        {
            case 0: nm3 += "0";
            break;
            case 1: nm3 += "1";
            break;
            case 2: nm3 += "2";
            break;
            case 3: nm3 += "3";
            break;
            case 4: nm3 += "4";
            break;
            case 5: nm3 += "5";
            break;
            case 6: nm3 += "6";
            break;
            case 7: nm3 += "7";
            break;
            case 8: nm3 += "8";
            break;
            case 9: nm3 += "9";
            break;
            case 10: nm3 += "A";
            break;
            case 11: nm3 += "B";
            break;
            case 12: nm3 += "C";
            break;
            case 13: nm3 += "D";
            break;
            case 14: nm3 += "E";
            break;
            case 15: nm3 += "F";
            break;
        }
    }
    strcpy(n3, nm3.c_str());
    //cout<<nm3<<endl;
}

//Character to Integer Binary array
void char_to_int(char *n, int *h, int r)
{
    int i=0;
    for(i=0; i<r; i++)
    {
        if(n[i] == '0')
            h[i] = 0;
        else
        {
            h[i] = 1;
        }
    }
}

//Check if array contains all zeroes
bool checkarr(int *a)
{
    int i;
    for(i=0; i<8; i++)
    {
        if (a[i] != 0)
            return true;
    }
    return false;
}

//Xor
void xor_m(int *x, int *y)
{
    int i;
    for(i=0; i<8; i++)
    {
        x[i] ^= y[i];
    }
}

//Left Shift
void l_shift(int *a)
{
    int i;
    for(i=0; i<7; i++)
    {
        a[i] = a[i+1];
    }
    a[7] = 0;
}

//Right Shift
void r_shift(int *a)
{
    int i;
    for(i=7; i>0; i--)
    {
        a[i] = a[i-1];
    }
    a[0] = 0;
}

//Left Cirular Shift
int l_c_shift(int d, int s)
{
    int i, j;
    int p[8];
    dec2bin(d, p);
    int a;
    for(i=0; i<s; i++)
    {
        a = p[0];
        for(j=1; j<8; j++)
        {
            p[j-1] = p[j];
        }
        p[7] = a;
    }
    a = bin2dec(p);
    return a;
}

//Multiplication Algorithm
int* mul(int *a, int *b, int *p)
{
    
    int i = 0;
    int carry = 0;
    i = 0;
    int k[8] = {0,0,0,1,1,0,1,1};
    int j;
    //Peasant's algorithm
    while(i < 8)
    {
        if (b[7] == 1)
            xor_m(p, a);
        r_shift(b);
        carry = a[0];
        l_shift(a);
        if (carry == 1)
            xor_m(a, k);
        i++;
    }
    return p;
}

//Multiplication Function
void multi(char n1[3], char n2[3], char n3[3])
{
    //cout<<n1<<n2;
    char nm1[9];
    char nm2[9];
    hex2bin(n1, nm1);
    hex2bin(n2, nm2);
    //cout<<nm1<<" "<<nm2<<endl;
    int p[8] = {0};
    int a[8];
    int b[8];
    char_to_int(nm1, a, 8);
    char_to_int(nm2, b, 8);
    mul(a,b, p);
    bin2hex(p, n3);
}

//Calculating Log and Exp tables
void inv()
{
    int i;
    int t = 1;
    int g = 3; //Generator g = 0x03 
    for(i=0; i<255; i++)
    {
        Exp[i] = t;
        int e[8];
        int f[8];
        int l[8] = {0};
        dec2bin(t, e);
        dec2bin(g, f);
        mul(e,f,l);
        t = bin2dec(l);
    }
    for(i=0; i<255; i++)
    {
        Log[Exp[i]] = i;
    }
    Log[0] = 0;
}

//Sbox
void sbox(char n1[3], char n2[3])
{
    int iv;
    char nm1[9];
    hex2bin(n1, nm1);
    int a[8];
    char_to_int(nm1, a, 8);
    if (bin2dec(a) != 0)
        iv = Exp[(255 - Log[(bin2dec(a))]) % 255];
    else 
        iv = 0;
    //cout<<iv;
    int op = iv ^ aff_t(iv, 1) ^ aff_t(iv, 2) ^ aff_t(iv, 3) ^ aff_t(iv, 4);
    op = op ^ 99;
    //cout<<op;
    int y[8];
    dec2bin(op, y);
    bin2hex(y, n2);
    //cout<<"\nThe output of the sbox is: "<<n2<<endl;
}

//Inverse Sbox
void i_sbox(char n1[3], char n2[3])
{
    char nm1[9];
    hex2bin(n1, nm1);
    int a[8];
    char_to_int(nm1, a, 8);
    int iv;
    iv = bin2dec(a);
    //cout<<iv<<endl;
    int u;
    int op1, op2, op3;
    int op;
    op = l_c_shift(iv, 1);
    op1 = l_c_shift(iv, 3);
    op2 = l_c_shift(iv, 6);
    u = op ^ op1 ^ op2;
    u = u ^ 5;
    //cout<<op<<" "<<op1<<" "<<op2<<" "<<u<<endl;
    if (u != 0)
        iv = Exp[(255 - Log[u]) % 255];
    else
        iv = 0;
    //cout<<op<<endl;
    //cout<<iv<<endl;
    int y[8];
    dec2bin(iv, y);
    bin2hex(y, n2);
    //cout<<"\nThe output of the Inverse sbox is: "<<n2<<endl;
}

//Forward Substitute Bytes
string F_SubBytes(string p)
{
    //cout<<"SubBytes"<<endl;
    char q[3];
    int i;
    char r[3];
    string t = "";
    for(i=0; i<32; i+=2)
    {
        p.copy(q,2,i);
        sbox(q,r);
        //cout<<q<<" "<<r<<" "<<endl;
        t.push_back(r[0]);
        t.push_back(r[1]);
    }
    //cout<<t<<endl;
    //cout<<t<<" ";
    return t; 
}

//Reverse Substitute Bytes
string R_SubBytes(string c)
{
    char q[3];
    int i;
    char r[3];
    string t = "";
    for(i=0; i<32; i+=2)
    {
        c.copy(q,2,i);
        i_sbox(q,r);
        t.push_back(r[0]);
        t.push_back(r[1]);
    }
    //cout<<t<<" ";
    return t; 
}

//Forward Shift (Left Circular Shift)
void f_shift(char *a)
{
    char c1, c2;
    c1 = a[0];
    c2 = a[1];
    int i;
    for(i=0; i<6; i+=2)
    {
        a[i] = a[i+2];
        a[i+1] = a[i+3];
    }
    a[6] = c1;
    a[7] = c2;
}

//Reverse Shift (Right Circular Shift)
void r_shift(char a[9])
{
    char b[9];
    char c1, c2;
    c1 = a[6];
    c2 = a[7];
    int i;
    for(i=0; i<8; i++)
    {
        b[i] = a[i];
    }
    for(i=2; i<8; i+=2)
    {
        a[i] = b[i-2];
        a[i+1] = b[i-1];
    }
    a[0] = c1;
    a[1] = c2;
}

//Forward Shift Rows
string F_ShiftR(string p)
{
    char q[4][9];
    int i;
    int j=0;
    for(i=0; i<4; i++)
    {
        p.copy(q[i],8,j);
        q[i][8] = '\0'; 
        j+=8;
    }
    char t[4][9];
    int k = 0, m = 0;
    for(i=0; i<8; i+=2)
    {
        for(j=0; j<4; j++)
        {
            t[j][i] = q[k][m];
            t[j][i+1] = q[k][m+1];
            m += 2;
        }
        if (m == 8)
        {
            m = 0;
            k++;
        }
    }
    for(i=0; i<4; i++)
    {
        t[i][8] = '\0';
    }
    for(i=1; i<4; i++)
    {
        for(j=0; j<i; j++)
        {
            f_shift(t[i]);
        }
    }
    k = 0, m = 0;
    for(i=0; i<4; i++)
    {
        k = 0;
        for(j=0; j<8; j+=2)
        {
            q[i][j] = t[k][m];
            q[i][j+1] = t[k][m+1];
            k++;
        }
        m += 2;
    }
    string x = "";
    for(i=0; i<4; i++) 
    {
        for(j=0; j<8; j++)
        {
            x.push_back(q[i][j]);
        }
    }   
    //cout<<x<<" ";
    return x;
}

//Reverse Shift Rows
string R_ShiftR(string p)
{
    char q[4][9];
    int i;
    int j=0;
    for(i=0; i<4; i++)
    {
        p.copy(q[i],8,j);
        q[i][8] = '\0'; 
        j+=8;
    }

    char t[4][9];
    int k = 0, m = 0;
    for(i=0; i<8; i+=2)
    {
        for(j=0; j<4; j++)
        {
            t[j][i] = q[k][m];
            t[j][i+1] = q[k][m+1];
            m += 2;
        }
        if (m == 8)
        {
            m = 0;
            k++;
        }
    }
    for(i=0; i<4; i++)
    {
        t[i][8] = '\0';
    }
    for(i=1; i<4; i++)
    {
        for(j=0; j<i; j++)
        {
            r_shift(t[i]);
        }
        
    }
    k = 0, m = 0;
    for(i=0; i<4; i++)
    {
        k = 0;
        for(j=0; j<8; j+=2)
        {
            q[i][j] = t[k][m];
            q[i][j+1] = t[k][m+1];
            k++;
        }
        m += 2;
    }
    string x = "";
    for(i=0; i<4; i++) 
    {
        for(j=0; j<8; j++)
        {
            x.push_back(q[i][j]);
        }
    }   
    //cout<<x<<" ";
    return x;
}

//Forward Mix Columns
string F_MixC(string p)
{
    char q[16][3];
    int i;
    int j=0;
    for(i=0; i<16; i++)
    {
        p.copy(q[i],2,j);
        j+=2;
        q[i][2] = '\0';
        //cout<<q[i]<<" ";
    }
    //cout<<endl;
    char r[16][9];
    int k=0;
    for(i=0; i<16; i++)
    {
        hex2bin(q[i], r[i]);
    }
    int h[16][8];
    for(i=0; i<16; i++)
    {
        char_to_int(r[i], h[i], 8);
    }
    
    int w[4][4];
    int l[8];
    int f[8];
    int u;
    int y = 0;
    int m = 0;
    int n = 0;
    int o=0; 
    for(i=0; i<4; i++)
    {
        m = 0;
        for(j=0; j<4; j++)
        {
            w[i][j] = 0;
            for(k=0; k<4; k++)
            {
                int l[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                int v[8];
                dec2bin(F_MixCol[i][k], f);
                for(n=0; n<8; n++)
                    v[n] = h[m][n];
                mul(f, v, l);
                u = bin2dec(l);       
                w[i][j] ^= u;
                m++;
            }
        }
    }
    k = 0;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            dec2bin(w[i][j], h[k]);
            k++;
        }
    }
    for(i=0; i<16; i++)
    {
        bin2hex(h[i], r[i]);
    }
    string x = "";
    y = 0;
    for(i=0; i<16; i+=4)
    {
        for(j=y; j<=(y+12); j+=4)
        {
            for(k=0; k<2; k++)
            {
                x.push_back(r[j][k]);
            }
        }
        y++;
    }
    //cout<<x<<endl;
    //cout<<x<<" ";
    return x;
}

//Reverse Mix Columns
string R_MixC(string p)
{
    char q[16][3];
    int i;
    int j=0;
    for(i=0; i<16; i++)
    {
        p.copy(q[i],2,j);
        j+=2;
        q[i][2] = '\0';
        //cout<<q[i]<<" ";
    }
    //cout<<endl;
    char r[16][9];
    int k=0;
    for(i=0; i<16; i++)
    {
        hex2bin(q[i], r[i]);
    }
    int h[16][8];
    for(i=0; i<16; i++)
    {
        char_to_int(r[i], h[i], 8);
    }
    
    int w[4][4];
    int l[8];
    int f[8];
    int u;
    int y = 0;
    int m = 0;
    int n = 0;
    int o=0; 
    for(i=0; i<4; i++)
    {
        m = 0;
        for(j=0; j<4; j++)
        {
            w[i][j] = 0;
            for(k=0; k<4; k++)
            {
                int l[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                int v[8];
                dec2bin(R_MixCol[i][k], f);
                for(n=0; n<8; n++)
                    v[n] = h[m][n];
                mul(f, v, l);
                u = bin2dec(l);       
                w[i][j] ^= u;
                m++;
            }
        }
    }
    k = 0;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            dec2bin(w[i][j], h[k]);
            k++;
        }
    }
    for(i=0; i<16; i++)
    {
        bin2hex(h[i], r[i]);
    }
    string x = "";
    y = 0;
    for(i=0; i<16; i+=4)
    {
        for(j=y; j<=(y+12); j+=4)
        {
            for(k=0; k<2; k++)
            {
                x.push_back(r[j][k]);
            }
        }
        y++;
    }
    //cout<<x<<endl;
    //cout<<x<<" ";
    return x;
}

//Add Round Key
string Add_Round_Key(string p, char key[16][3])
{
    char q[16][3];
    int i;
    int j=0;
    for(i=0; i<16; i++)
    {
        p.copy(q[i],2,j);
        q[i][2] = '\0';
        j+=2;
    }
    char r[16][9];
    int k=0;
    for(i=0; i<16; i++)
    {
        hex2bin(q[i], r[i]);
    }
    int h[16][8];
    for(i=0; i<16; i++)
    {
        char_to_int(r[i], h[i], 8);
    }
    char ky[16][9];
    for(i=0; i<16; i++)
    {
        hex2bin(key[i], ky[i]);
    }
    int w[16][8];
    for(i=0; i<16; i++)
    {
        char_to_int(ky[i], w[i], 8);
    }
    int y[16][8];
    k = 0;
    for(i=0; i<16; i++)
    {
        for(j=0; j<8; j++)
        {
            y[i][j] = h[i][j] ^ w[i][j];
        }
    }
    for(i=0; i<16; i++)
    {
        bin2hex(y[i], q[i]);
    }
    string x = "";
    for(i=0; i<16; i++)
    {
        for(j=0; j<2; j++)
        {
            x.push_back(q[i][j]);
        }
    }
    //cout<<x<<" ";
    return x;
}

//g Function
void g(int h[4], int f[4], int rnd)
{
    int i;
    int p[4];
    for(i=0; i<4; i++)
        p[i] = h[i];
    int t = p[0];
    for(i=0; i<3; i++)
        p[i] = p[i+1];
    p[3] = t;
    int l[8] ={0, 0, 0, 0, 0, 0, 0, 0};
    char n1[3];
    char n2[3];
    char k[9];
    for(i=0; i<4; i++)
    {
        dec2bin(p[i],l);
        bin2hex(l,n1);
        //cout<<n1<<endl;
        sbox(n1, n2);
        hex2bin(n2, k);
        char_to_int(k, l, 8);
        f[i] = bin2dec(l);
        //cout<<f[i]<<" ";
    }
    f[0] ^= RC[rnd];
}

//Key Expansion
void Key_Exp(char q[16][3], int rnd)
{
    char r[16][9];
    int i=0;
    for(i=0; i<16; i++)
    {
        hex2bin(q[i], r[i]);
    }
    int h[16][8];
    for(i=0; i<16; i++)
    {
        char_to_int(r[i], h[i], 8);
    }
    int p[4][4];
    int j,k=0;
    int f[4];
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            p[i][j] = bin2dec(h[k]);
            k++;
        }
    }
    g(p[3], f, rnd);
    for(i=0; i<4; i++)
    {
        p[0][i] = p[0][i] ^ f[i];
    }
    for(i=1; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            p[i][j] = p[i][j] ^ p[i-1][j];
        }
    }
    k=0;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            dec2bin(p[i][j], h[k]);
            k++;
        }
    }
    for(i=0; i<16; i++)
    {
        bin2hex(h[i], q[i]);
        //cout<<q[i]<<endl;
    }
}

//Key Generation for each round
void key_generation()
{
    string k;
    cout<<"\nEnter the string in Hexadecimal to generate the key: ";
    cin>>k;
    //k = "0F1571C947D9E8590CB7ADD6AF7F6798";
    int i,j;
    k.copy(round[0], 32, 0);
    j = 0;
    for(i=0; i<16; i++)
    {
        k.copy(Key[i],2,j);
        Key[i][2] = '\0';
        j+=2;
    }
    int m = 0;
    i = 1;
    for(i=1; i<11; i++)
    {
        Key_Exp(Key, i-1);
        m = 0;
        for(j=0; j<16; j++)
        {
            round[i][m] = Key[j][0];
            round[i][m+1] = Key[j][1];
            m += 2; 
        }
        round[i][32] = '\0';
    }
}

//Encryption
void encrypt()
{
    key_generation();
    string file;
    string P;
    cout<<"\nEnter the file name of the input file: ";
    cin>>file;
    //file = "ip.txt";
    ifstream ip;
    ip.open(file.c_str());
    getline(ip, P);
    //cout<<P<<endl;
    int i;
    int k=0;
    for(i=0; i<16; i++)
    {
        Key[i][0] = round[0][k];
        Key[i][1] = round[0][k+1];
        Key[i][2] = '\0';
        k += 2;
    }
    k = 0;
    int j;
    P = Add_Round_Key(P, Key);
    for(i=1; i<10; i++)
    {
        P = F_SubBytes(P);
        P = F_ShiftR(P);
        P = F_MixC(P);
        k = 0; 
        for(j=0; j<16; j++)
        {
            Key[j][0] = round[i][k];
            Key[j][1] = round[i][k+1];
            Key[j][2] = '\0';
            k += 2;
        }
        P = Add_Round_Key(P, Key);
    }
    P = F_SubBytes(P);
    P = F_ShiftR(P);
    k = 0;
    for(j=0; j<16; j++)
    {
        Key[j][0] = round[i][k];
        Key[j][1] = round[i][k+1];
        Key[j][2] = '\0';
        k += 2;
    }
    P = Add_Round_Key(P, Key);
    ip.close();
    cout<<"\nEnter the name of the output file: ";
    cin>>file;
    ofstream op;
    op.open(file.c_str());
    op<<P;
    op.close();
}

//Decryption
void decrypt()
{
    key_generation();
    string file;
    string P;
    cout<<"\nEnter the file name of the input file: ";
    cin>>file;
    //file = "op.txt";
    ifstream ip;
    ip.open(file.c_str());
    getline(ip, P);
    //cout<<P<<endl;
    int i;
    int k=0;
    /*for(i=0; i<11; i++)
    {
        cout<<round[10-i]<<endl;
    }*/
    for(i=0; i<16; i++)
    {
        Key[i][0] = round[10][k];
        Key[i][1] = round[10][k+1];
        Key[i][2] = '\0';
        k += 2;
    }
    /*for(i=0; i<16; i++)
    {
        cout<<Key[i]<<" ";
    }
    cout<<endl;*/
    k = 0;
    int j;
    P = Add_Round_Key(P, Key);
    //cout<<endl;
    //cout<<"Round 0: "<<P<<endl;
    i = 1;
    for(i=1; i<10; i++)
    {
        P = R_ShiftR(P);
        P = R_SubBytes(P);
        k = 0; 
        for(j=0; j<16; j++)
        {
            Key[j][0] = round[10-i][k];
            Key[j][1] = round[10-i][k+1];
            Key[j][2] = '\0';
            k += 2;
        }
        P = Add_Round_Key(P, Key);
        P = R_MixC(P);
        //cout<<endl;
        //cout<<"Round"<<i<<": "<<P<<endl;
    }
    P = R_ShiftR(P);
    P = R_SubBytes(P);
    k = 0;
    for(j=0; j<16; j++)
    {
        Key[j][0] = round[10-i][k];
        Key[j][1] = round[10-i][k+1];
        Key[j][2] = '\0';
        k += 2;
    }
    P = Add_Round_Key(P, Key);
    //cout<<endl;
    //cout<<"Round "<<i<<": "<<P<<endl;
    ip.close();
    cout<<"\nEnter the name of the output file: ";
    cin>>file;
    ofstream op;
    op.open(file.c_str());
    op<<P;
    op.close();
}

//Main
int main()
{
    cout<<"\n---------- AES (128 Bits) -----------\n";
    int ans = -1;
    inv();
    do
    {
        cout<<"\nSelect your choice\n";
        cout<<"1. Encryption\n2. Decryption\n3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>ans;
        //ans = 1;
        switch(ans)
        {
            case 1: encrypt();
            break;
            case 2: decrypt();
            break;
            case 3: break;
            default: cout<<"Please enter correct choice\n";
        }
    } while (ans != 3);
    return 0;
}