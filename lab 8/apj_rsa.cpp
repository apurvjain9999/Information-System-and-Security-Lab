#include<iostream>
#include<math.h>
#include<fstream>
#include<cstdlib>
using namespace std;

unsigned long long int primeList[100];
unsigned long long int listE[100];
unsigned long long int p, q;
unsigned long long int n, phi;
unsigned long long int e, d;
unsigned long long int range;

//GCD
unsigned long long int gcd(unsigned long long int a, unsigned long long int b)
{
    if (b==0)
        return a;

    unsigned long long int temp;
    if (b>a)
    {   
        temp = a;
        a = b;
        b = temp;
    }
    unsigned long long int i;
    while(b>0)
    {
        temp = a;
        a = b;
        b = temp%b;
    }
    return a;
}

//Check Prime
unsigned long long int prime(unsigned long long int a) 
{
    unsigned long long int f = 1;
    unsigned long long int i;
    for(i=2; i<a/2; i++)
    {
        if (a % i == 0)
        {
            f = 0;
            break;
        }
    }
    return f;
}

//Compute e
unsigned long long int compute_e()
{
    unsigned long long int i,j,k;
    unsigned long long int f = 0;
    k = 0;
    for(i=2; i<phi; i++)
    {
        if (phi % i == 0)
            continue;
        f = gcd(i, phi);
        if (f == 1 && i != p && i != q)
        {
            listE[k] = i;
            k++;
        }
        if (k == 99)
        {
            break;
        }
    }
    return k;
}

//Compute d
//Extended Euclidean Algorithm
void compute_d()
{
    unsigned long int i = 1;
    while(1)
    {
        i += phi;
        if (i % e == 0)
        {
            d = i/e;
            return;
        }
    }
}

//Generating the key
void key()
{
    unsigned long long int i, j, count, val = 0;
    for(count=0; count<100;)
    {
        val = (rand()%600) + 1;
        unsigned long long int f = 0;
        for(i=2; i<val/2; i++)
        {
            if (val % i == 0)
            {
                f = 1;
                break;
            }
        }
        if (f == 0 && val != 1)
        {
            if (count != 0)
            {
                unsigned long long int g = 0;
                for(j=0; j<count; j++)
                {
                    if (primeList[j] == val)
                    {
                        g = 1;
                        break;
                    }
                }
                if (g == 1)
                    continue; 
            }
            primeList[count] = val;
            count++;
        }
    }
    p = primeList[rand()%99];
    q = primeList[rand()%99];
    //p = 17, q  = 11;
    n = p * q;
    phi = (p-1) * (q-1);
    range = compute_e();
    e = listE[rand()%range];
    compute_d();
    //e = 7, d = 23;
    //cout<<e<<" "<<d<<endl;
    cout<<"Key generated successfully\n";
}

//For encryption
void encrypt()
{
    ifstream ip;
    ofstream op;
    string file;
    cout<<"\nEnter Plaintext filename: ";
    cin>>file;
    ip.open(file.c_str());
    cout<<"\nEnter Ciphertext filename: ";
    cin>>file;
    op.open(file.c_str()); 
    int r;
    ip.seekg(0, ios::end);
    r = ip.tellg();
    ip.seekg(0, ios::beg);
    //cout<<r<<endl;
    if (r % 2 != 0)
    {
        cout<<"\nThe range of plaintext must be even\n";
        return;
    }
    unsigned long long int i = 0;
    int fg  = 0;
    char dig;
    int h;
    int u = 10;
    unsigned long long int k = 1;
    while(ip.tellg()!=r)
    {
        h = 0;
        u = 10;
        k = 1;
        //cout<<ip.tellg()<<endl;
        for(i=0; i<2; i++)
        {
            ip>>dig;
            h += (u * (dig - '0'));
            u /= 10;
        }
            
        for(i=0; i<e; i++)
        {
            k = k * h;
            k = k % n;
        }
        op<<k;
    }
    ip.close();
    op.close();
}

//For decryption
void decrypt()
{
    ifstream ip;
    ofstream op;
    string file;
    cout<<"\nEnter Ciphertext filename: ";
    cin>>file;
    ip.open(file.c_str());
    cout<<"\nEnter Plaintext filename: ";
    cin>>file;
    op.open(file.c_str()); 
    int r;
    ip.seekg(0, ios::end);
    r = ip.tellg();
    ip.seekg(0, ios::beg);
    int flag = 0;
    if (r % 2 != 0)
    {
        cout<<"\nThe length of the ciphertext must be even\n";
        return;
    }
    unsigned long long int i = 0;
    int fg  = 0;
    char dig;
    int h;
    int u = 10;
    unsigned long long int k = 1;
    while(ip.tellg()!=r)
    {
        h = 0;
        u = 10;
        k = 1;
        //cout<<ip.tellg()<<endl;
        for(i=0; i<2; i++)
        {
            ip>>dig;
            h += (u * (dig - '0'));
            u /= 10;
        }
            
        for(i=0; i<d; i++)
        {
            k = k * h;
            k = k % n;
        }
        op<<k;
    }
}

int main()
{
    cout<<"\n--------- RSA Algorithm ---------\n";
    int ans = 1;
    int f = 0;
    do
    {
        cout<<"\nSelect a option\n";
        cout<<"0. Exit\n1. Key Generation\n2. Encryption\n3. Decryption\n";
        cout<<"Enter your choice: ";
        cin>>ans;
        switch(ans)
        {
            case 0: break;
            case 1: 
            {
                key();
                f = 1;
            }
            break;
            case 2: 
            if (f == 0)
            {
                cout<<"\nFirst generate key";
            }
            else
            {
                encrypt();
            }
            break;
            case 3: 
            if (f == 0)
            {
                cout<<"\nFirst generate key";
            }
            else
            {
                decrypt();
            }
            break;
            default: cout<<"\nChoose correct option\n";
        }
    }while (ans != 0);
    
    return 0;
}