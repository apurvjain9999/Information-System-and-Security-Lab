#include<bits/stdc++.h>
#include<stdlib.h>
#include<fstream>


using namespace std;

//GCD with recursion
int gcdr(int a, int b)
{
    if (b == 0)
        return a;
    int temp = 0;
    if (b>a)
    {   
        temp = a;
        a = b;
        b = temp;
    }
    return gcdr(b, a%b);
}

//GCD without recursion
int gcd(int a, int b)
{
    if (b==0)
        return a;

    int temp;
    if (b>a)
    {   
        temp = a;
        a = b;
        b = temp;
    }
    int i;
    while(b>0)
    {
        temp = a;
        a = b;
        b = temp%b;
    }
    return a;
}
int main()
{
    int a1[100], a2[100];
    int i;
    ifstream ip;
    ofstream op;
    string fname;
    string gname;
    int min = 1;
    int max = 1000;	
    for(i=0; i<100; i++)
    {
        a1[i] = (rand()%max) + min;
        a2[i] = (rand()%max) + min;
    }

    int ans = 0;
    do
    {
        cout<<"\nSelect a option: ";
        cout<<"\n1.Generate Numbers"
            <<"\n2.Compute GCD without recursion"
            <<"\n3.Compute GCD with recursion"
            <<"\n4.Exit";
        cout<<"\nEnter your choice: ";
        cin>>ans;   
        if (ans == 4)
            break;
        if (ans == 1)
        {
            cout<<"\nEnter file name to store the numbers: ";
            cin>>fname;
            op.open(fname.c_str());
            int i;
            for(i=0; i<100; i++)
            {
                op<<a1[i]<<" "<<a2[i]<<"\n";
            }
            op.close();
        }
        if (ans == 3)
        {
            cout<<"\nEnter file name to store the numbers and their gcd: ";
            cin>>gname;
            op.open(gname.c_str());
            int i;
            char c;
            int a,b;
            int h;
            for(i=0; i<100; i++)
            {
                a = a1[i];
                b = a2[i];
                h = gcdr(a1[i], a2[i]);
                op<<a<<" "<<b<<"->"<<h<<"\n";
            }
            op.close();
        }
        if (ans == 2)
        {
            cout<<"\nEnter file name to store the numbers and their gcd: ";
            cin>>gname;
            op.open(gname.c_str());
            int i;
            int a,b;
            int h;
            for(i=0; i<100; i++)
            {
                a = a1[i];
                b = a2[i];
                h = gcd(a,b);
                op<<a<<" "<<b<<"->"<<h<<"\n";
            }
            op.close();
        }
        else
        {
            cout<<"\nEnter correct option";
        }

    }while (ans != 4);
    return 0;
}