#include<iostream>
#include<string.h>
#include<stdint-gcc.h>
using namespace std;

#define aff_t(x, s) ((int) ((x) << (s)) | ((x) >> (8 - (s))))

int Exp[255] = {0}; //To store the exponenets
int Log[255] = {0}; //To store the log values

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

//Hexadeciaml to Binary
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

//Character to Integer array
void char_to_int(char *n, int *h)
{
    int i=0;
    for(i=0; i<8; i++)
    {
        if(n[i] == '0')
            h[i] = 0;
        else
        {
            h[i] = 1;
        }
    }
}

//Check array if it contains all zeroes
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

//Xor two binary arrays
void xor_m(int *x, int *y)
{
    int i;
    for(i=0; i<8; i++)
    {
        x[i] ^= y[i];
    }
}

//Left shift 
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

//To add two numbers
void add()
{
    char n1[3];
    char n2[3];
    cout<<"\nEnter the number 1 in hexadecimal : ";
    cin>>n1;
    cout<<"\nEnter the number 2 in hexadecimal : ";
    cin>>n2;
    //cout<<n1<<n2;
    char nm1[9];
    char nm2[9];
    hex2bin(n1, nm1);
    hex2bin(n2, nm2);
    //cout<<nm1<<" "<<nm2<<endl;
    int add[8] = {0};
    int i;
    //Adding the coefficients with mod 2
    for(i=0; i<8; i++)
    {
        add[i] = ((nm1[i] - 48) + (nm2[i] - 48)) % 2;
    }
    char n3[3];
    bin2hex(add, n3);
    cout<<"The resultant hexadecimal number is: "<<n3<<endl;
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

//Multiplication function
void multi()
{
    char n1[3];
    char n2[3];
    cout<<"\nEnter the number 1 in hexadecimal : ";
    cin>>n1;
    cout<<"\nEnter the number 2 in hexadecimal : ";
    cin>>n2;
    //cout<<n1<<n2;
    char nm1[9];
    char nm2[9];
    hex2bin(n1, nm1);
    hex2bin(n2, nm2);
    //cout<<nm1<<" "<<nm2<<endl;
    int p[8] = {0};
    int a[8];
    int b[8];
    char_to_int(nm1, a);
    char_to_int(nm2, b);
    mul(a,b, p);
    char n3[3];
    bin2hex(p, n3);
    cout<<"The resultant hexadecimal number is: "<<n3<<endl;
}

//Calculating Exp and Log arrays (tables)
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
    /*for(i=0; i<255; i++)
    {
        cout<<i<<" "<<Exp[i]<<" "<<Log[i]<<endl;
    }*/
    Log[0] = 0;
}

//Multiplicative Inverse in GF(2^8)
void inverse()
{
    char n1[3];
    cout<<"\nEnter the number in hexadecimal : ";
    cin>>n1;
    int iv;
    char nm1[9];
    hex2bin(n1, nm1);
    int a[8];
    char_to_int(nm1, a);
    //cout<<bin2dec(a)<<endl;
    //cout<<Log[(bin2dec(a))]<<endl;
    if (bin2dec(a) != 0)
        iv = Exp[(255 - Log[(bin2dec(a))]) % 255];
    else 
        iv = 0;
    char n2[3];
    //cout<<iv<<endl;
    int y[8];
    dec2bin(iv, y);
    bin2hex(y, n2);
    cout<<"The multiplictive inverse is: "<<n2<<endl;
}

//Polynomial Representation
void poly()
{
    char n1[3];
    cout<<"\nEnter the number in hexadecimal : ";
    cin>>n1;
    char nm1[9];
    hex2bin(n1, nm1);
    int a[8];
    char_to_int(nm1, a);
    int i;
    int f = 0;
    int y = 0;
    cout<<"The polynomial representation is: ";
    for(i=0; i<7; i++)
    {
        if(a[i] == 1)
        {
            if (y == 0)
                y = 1;
            else
            {
                cout<<" + ";
            }
            cout<<"x^"<<(7-i);
            if (f == 0)
                f = 1;
        }
    }
    if (a[7] == 1)
    {
        f = 1;
        if (y == 1)
            cout<<" + ";
        cout<<"1";
    }
    if (f == 0)
        cout<<"0";
    cout<<"\n";
}

//Sbox
void sbox()
{
    char n1[3];
    cout<<"\nEnter the number in hexadecimal : ";
    cin>>n1;
    int iv;
    char nm1[9];
    hex2bin(n1, nm1);
    int a[8];
    char_to_int(nm1, a);
    if (bin2dec(a) != 0)
        iv = Exp[(255 - Log[(bin2dec(a))]) % 255];
    else 
        iv = 0;
    //cout<<iv;
    char n2[3];
    int op = iv ^ aff_t(iv, 1) ^ aff_t(iv, 2) ^ aff_t(iv, 3) ^ aff_t(iv, 4);
    op = op ^ 99;
    //cout<<op;
    int y[8];
    dec2bin(op, y);
    bin2hex(y, n2);
    cout<<"\nThe output of the sbox is: "<<n2<<endl;
}

//Main
int main()
{
    inv();
    cout<<"------------- S-Box (AES) Implementation -------------\n";
    cout<<"\nEnter numbers in Hexadecimal from 00 to FF and in XY format only\n";
    cout<<"\nSelect an option: \n";
    cout<<"0. Exit\n";
    cout<<"1. Addition\n";
    cout<<"2. Multiplication\n";
    cout<<"3. Multiplicative inverse\n";
    cout<<"4. Polynomial Representation\n";
    cout<<"5. S-box output\n";
    int ans;
    cin>>ans;
    switch(ans)
    {
        case 0: break;
        case 1: add();
        break;
        case 2: multi();
        break;
        case 3: inverse();
        break;
        case 4: poly();
        break;
        case 5: sbox();
        break;
    }
    return 0;
}