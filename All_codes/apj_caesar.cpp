//Caeser Cipher
//Made By: Apurv Jain
#include<iostream>
#include<fstream>

using namespace std;

void encrypt(int K, string P, ofstream &ofile)
{
    string C = "";
    int i;
    int length = P.length();
    if (K > 0)  //For positive key
    {
        //cout<<"Hi";
        for(i=0; i<length; i++)
        {
            //cout<<i;
            if (!(P[i] >= 'a' && P[i] <= 'z'))  //Checking for special characters
            {
                C[i] = P[i];
            }
            else                                //For alphabets
            {
                int j;
                for(j=1; j<=K; j++)             //Encryption Process
                {
                    if ((P[i]+1) > 122)
                    {
                        P[i] = 97;
                    }
                    else
                    {
                        P[i] = P[i] + 1;
                    }
                }
                C[i] = P[i] - 32;
            }
            cout<<C[i];
            ofile<<C[i];    //Writing to a file
        }
        ofile<<"\n";
    }
    else if (K < 0)     //For negative key
    {
        for(i=0; i<length; i++)
        {
            if (!(P[i] >= 'a' && P[i] <= 'z')) //Checking for special characters
            {
                C[i] = P[i];
            }
            else                           //For alphabets
            {
                int j;
                for(j=1; j<=(-K); j++)     //Encryption process
                {
                    if ((P[i]-1) < 97)
                    {
                        P[i] = 122;
                    }
                    else
                    {
                        P[i] = P[i] - 1;
                    }
                }
                C[i] = P[i] - 32;
            }
            cout<<C[i];
            ofile<<C[i];        //Writing to the file
        }
        ofile<<"\n";
    }
   
}

void decrypt(int K, string C, ofstream &ofile)
{   
    string P = "";  
    int i;
    int length = C.length();
    if (K > 0)              //For positive key
    {
        for(i=0; i<length; i++)
        {
            if (!(C[i] >= 'a' && C[i] <= 'z')) //Checking for special characters
            {
               P[i] = C[i];
            }
            else                            //For alphabets
            {
                int j;
                for(j=1; j<=K; j++)         //Decryption Process
                {
                    if ((C[i]-1) < 65)
                    {
                        C[i] = 90;
                    }
                    else
                    {
                        C[i] = C[i] - 1;
                    }
                }
                P[i] = C[i] + 32;
                
            }
            cout<<P[i];         
            ofile<<P[i];    //Writing to file
        }
        ofile<<"\n";
    }
    else if (K < 0)     //For negative key
    {
        for(i=0; i<length; i++)
        {
            if (!(C[i] >= 'a' && C[i] <= 'z')) //Checking for special characters
            {
                P[i] = C[i];
            }
            else            //For alphabets
            {
                int j;
                
                for(j=1; j<=(-K); j++)      //Decryption process
                {
                    if ((C[i]+1) > 90)
                    {
                        C[i] = 65;
                    }
                    else
                    {
                        C[i] = C[i] + 1;
                    }
                }
                P[i] = C[i] + 32;
                
            }
            cout<<P[i];
            ofile<<P[i];        //Writing to file
        }
        ofile<<"\n";
    }
}

int main()
{
    int key;
    cout<<"----------- Caesar Cipher -----------"<<endl;
    string input, output;
    cout<<"\nEnter input file name: ";  //Input file name
    cin>>input;
    cout<<"\nEnter output file name: "; //Output file name
    cin>>output;
    char ans = 'A';
    int flag = 0;
    do 
    {
        char exi = 'E';
        while (ans != 'E' || ans != 'e' || ans != 'D' ||  ans != 'D') //Checking ans of the user
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
        if (ans == 'E' || ans == 'e')   //Encrpytion Process
        {
            cout<<"\nEnter the key: ";
            cin>>key;
            ifstream fin;
            ofstream fout;
            fin.open(input.c_str());
            fout.open(output.c_str());
            cout<<"\nEncrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s);    //Getting line by line data
                encrypt(key, s, fout);
            }
            
            fin.close();
            fout.close();
        }
        else                                //Decryption process
        {
            ifstream fin;
            ofstream fout;
            fin.open(output.c_str());
            fout.open(input.c_str());
            cout<<"\nDecrypted text: ";
            while(fin)
            {
                string s;
                getline(fin, s);    //Getting line by line data
                
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
