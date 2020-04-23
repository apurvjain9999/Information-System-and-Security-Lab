#include<bits/stdc++.h>
using namespace std;

//Power function to avoid overflow
unsigned long long int power(unsigned long long int a, unsigned long long int b)
{
    unsigned long long int i;
    unsigned long long int s = 1;
    for(i=0; i<b; i++)
    {
        s *= a;
    }
    return s;
}

//Calculating Primitive Root 
unsigned long long int PrimRoot(unsigned long long int q)
{
    unsigned long long int alpha = 1;
    unsigned long long int prt[q-1];
    unsigned long long int i,j;

    for(i=1; i<q; i++)
    {
        for(j=0; j<q-1; j++)
        {
            prt[j] = ((unsigned long long int)power(i,j))%q;
        }
        
        sort(prt, prt+q-1);

        unsigned long long int f=0; 

        for(j=0; j<q-1; j++)
        {
            if(prt[j] != j+1)
            {
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            alpha = i;
            break;
        }
    }
    return alpha;
}

//Genertaing Key
void key()
{
    unsigned long long int i, j, count, val = 0;
    unsigned long long int primeList[100];
    //srand(time(NULL));
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
    unsigned long long int q;
    q = primeList[rand()%99];
    //cout<<"\nq = "<<q<<"\n";
    unsigned long long int alpha;
    alpha = PrimRoot(q);
    //cout<<"Primitive Root: "<<alpha<<"\n";

    unsigned long long int xa, xb;
    xa = (rand()%(q-1)) + 1;
    xb = (rand()%(q-1)) + 1;
    //cout<<"Xa = "<<xa<<" Xb = "<<xb<<"\n";
    cout<<"Xa and Xb generated successfully\n";
    unsigned long long int ya, yb;
    ya = ((unsigned long long int)power(alpha, xa))%q;
    yb = ((unsigned long long int)power(alpha, xb))%q;

    cout<<"Ya = "<<ya<<"\n";
    cout<<"Yb = "<<yb<<"\n";

    unsigned long long int k1,k2;
    k1=((unsigned long long int)power(yb,xa))%q;
    k2=((unsigned long long int)power(ya,xb))%q;
    if (k1 <= 0)
        k1 += q;
    if (k2 <= 0)
        k2 += q;
    cout<<"K1 = "<<k1<<"\n";
    cout<<"K2 = "<<k2<<"\n";
}

int main()
{
    cout<<"\n------- Diffie - Hellmann Key Exchange -------\n";
    unsigned long long int ans = 1;
    do
    {
        cout<<"\nSelect a option: \n";
        cout<<"0. Exit\n1. Key Generation\n";
        cout<<"\nEnter your choice: ";
        cin>>ans;
        switch(ans)
        {
            case 0: break;
            case 1: key();
            break;
            default: cout<<"\nEnter correct choice\n";
        }
    } while (ans != 0);
    
    return 0;
}