#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//To run this code please use:
//g++ -ggdb  stegc.cpp `pkg-config --cflags opencv` -o a `pkg-config --libs opencv`

//Returns whether bit at position pos is 0 or 1
bool isBitSet(char ch, int pos) 
{
	// 7 6 5 4 3 2 1 0
	ch = ch >> pos;
	return (ch & 1) != 0;
}

//Encryption
void encrypt(const string &ip_img, string fname, string op_img) 
{
	//Stores original image
	Mat image = imread(ip_img);
	if (image.empty()) 
    {
		cout<<"Error while opening image file\n";
		exit(1);
	}

	//Open file for message to be encrypted
	ifstream file(fname);
	if (!file.is_open()) 
    {
		cout<<"Error while opening text file\n";
		exit(1);
	}

	//To store the character of the message
	char ch;
	//reads the first char from the file
	file.get(ch);
	//stores which bit of char to be worked on
	int bit_count = 0;
	//to check whether file has ended
	bool eof_ch = false;
	//to check if the whole message is encrypted or not
	bool enc = false;
	
	/*To hide text into an image, one char (8 bits) at a time and each of the 8 bits are stored
	in the LSB of the pixel values (RGB).
	The image cannot be differentiated just by looking after encryption. */

	for (int r = 0; r < image.rows; r++) 
    {
		for (int c = 0; c < image.cols; c++) 
        {
			for (int colour = 0; colour < 3; colour++) 
            {

				//stores the pixel details
				Vec3b pixel = image.at<Vec3b>(Point(r, c));

				// if bit is 1 : change LSB of present colour value to 1.
				// if bit is 0 : change LSB of present colour value to 0.
				if (isBitSet(ch, 7 - bit_count))
					pixel.val[colour] |= 1;
				else
					pixel.val[colour] &= ~1;

				//update the image with the new pixel values
				image.at<Vec3b>(Point(r, c)) = pixel;

				//increment bit_count to work on next bit
				bit_count++;

				//if eof_ch is true and bit_count is 8, then our message is successfully encoded.
				if (eof_ch && bit_count == 8) 
                {
					enc = true;
					break;
				}

				//if bit_count is 8, we pick the next char from the file and work on it
				if (bit_count == 8) 
                {
					bit_count = 0;
					file.get(ch);

					//if EOF is encountered insert NULL char to the image, to denote end of the message
					if (file.eof()) 
                    {
						eof_ch = true;
						ch = '\0';
					}
				}
			}
            if(enc == true)
                break;
		}
        if(enc == true)
                break;
    }

    file.close();
	//if whole message was not encrypted due to image of small size
	if(!enc) 
    {
		cout<<"Message is too big. Try with larger image.\n";
		exit(1);
	}

	//Writes the stegnographic image
	imwrite(op_img, image);

	cout<<"\nStegnography performed successfully"<<endl;
}


void decrypt(string image_name, string fname) 
{
	//Stores original image
	Mat image = imread(image_name);
	if (image.empty()) 
    {
		cout<<"Error while opening image file\n";
		exit(1);
	}

	//char to work on
	char ch = 0;
	//contains information about which bit of char to work on
	int bit_count = 0;


    /*To extract the message from the image, we will iterate through the pixels and extract the LSB of
	the pixel values (RGB) and this way we can get our message.*/

    ofstream file(fname);
	for (int r = 0; r < image.rows; r++) 
    {
		for (int c = 0; c < image.cols; c++) 
        {
			for (int colour = 0; colour < 3; colour++) 
            {

				//stores the pixel details
				Vec3b pixel = image.at<Vec3b>(Point(r, c));

				//manipulating char bits accolourding to the LSB of pixel values
				if (isBitSet(pixel.val[colour], 0))
					ch |= 1;

				//increment bit_count to work on next bit
				bit_count++;

				//bit_count is 8, that means we have got our char from the encoded image
				if (bit_count == 8) 
                {

					//if NULL char is encountered
					if (ch == '\0')
					{
						file.close();
						cout<<"\nDecryption performed successfully"<<endl;
						return;
					}
					bit_count = 0;
					//cout<<ch;
                    file<<ch;
					ch = 0;
				} 
                else
                {
					ch = ch << 1;
				}

			}
		}
	}
}


int main() 
{
	string ip_img,fname, op_img;
	int ans;
    cout<<"\n------- Steganography in C++ ---------\n";
	do
    {
        cout<<"Choose your option:\n"
		    <<"0. Exit"<<endl
		    <<"1. Encryption"<<endl
		    <<"2. Decryption"<<endl
		    <<"Enter your ans: ";
	    cin>>ans;
		string text;
		if (ans == 1) 
        {
			cout<<"Enter input image file name: ";
			cin>>ip_img;

			cout<<"Enter text file name to encrypt: ";
			cin>>fname;

			cout<<"Enter output image name: ";
			cin>>op_img;

			encrypt(ip_img, fname,op_img);
		} 
        else if (ans == 2) 
        {
			cout<<"Enter input image name: ";
			cin>>ip_img;
            
            cout<<"Enter text file name to store decrypted data: ";
			cin>>fname;

			decrypt(ip_img, fname);
		}
        else if (ans == 0)\
        {
            break;
        }
        else
        {
            cout<<"\nPlease select correct option\n";
        }

	}while(ans!=0);

	return 0;
}

	