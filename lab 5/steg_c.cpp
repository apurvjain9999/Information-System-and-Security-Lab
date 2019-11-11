//
// Created by tanuj on 9/9/19.
//

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

////to run this code you need
//g++ -ggdb  stegnographyCPP.cpp `pkg-config --cflags opencv` -o stegnographyCPP `pkg-config --libs opencv`
bool isBitSet(char ch, int pos) {
	// 7 6 5 4 3 2 1 0
	ch = ch >> pos;
	return (ch & 1) != 0;
}

void cipher(const string &input_image_name, string text_name, string output_image_name) {
	// Stores original image
	Mat image = imread(input_image_name);
	if (image.empty()) {
		cout << "Image Error\n";
		exit(-1);
	}

	// Open file for text information
	ifstream file(text_name);
	if (!file.is_open()) {
		cout << "File Error\n";
		exit(-1);
	}

	// char to work on
	char ch;
	// reads the first char from the file
	file.get(ch);
	// contains information about which bit of char to work on
	int bit_count = 0;
	// to check whether file has ended
	bool last_null_char = false;
	// to check if the whole message is encoded or not
	bool encoded = false;

	/*
	To hide text into images. We are taking one char (8 bits) and each of the 8 bits are stored
	in the Least Significant Bits (LSB) of the pixel values (Red,Green,Blue).
	We are manipulating bits in such way that changing LSB of the pixel values will not make a huge difference.
	The image will still look similiar to the naked eye.
	*/

	for (int row = 0; row < image.rows; row++) {
		for (int col = 0; col < image.cols; col++) {
			for (int color = 0; color < 3; color++) {

				// stores the pixel details
				Vec3b pixel = image.at<Vec3b>(Point(row, col));

				// if bit is 1 : change LSB of present color value to 1.
				// if bit is 0 : change LSB of present color value to 0.
				if (isBitSet(ch, 7 - bit_count))
					pixel.val[color] |= 1;
				else
					pixel.val[color] &= ~1;

				// update the image with the changed pixel values
				image.at<Vec3b>(Point(row, col)) = pixel;

				// increment bit_count to work on next bit
				bit_count++;

				// if last_null_char is true and bit_count is 8, then our message is successfully encode.
				if (last_null_char && bit_count == 8) {
					encoded = true;
					goto OUT;
				}

				// if bit_count is 8 we pick the next char from the file and work on it
				if (bit_count == 8) {
					bit_count = 0;
					file.get(ch);

					// if EndOfFile(EOF) is encountered insert NULL char to the image
					if (file.eof()) {
						last_null_char = true;
						ch = '\0';
					}
				}

			}
		}
	}
	OUT:;

	// whole message was not encoded
	if (!encoded) {
		cout << "Message too big. Try with larger image.\n";
		exit(-1);
	}

	// Writes the stegnographic image
	imwrite(output_image_name, image);

	cout<<"\nSTEGNOGRAPHIC IMAGE GENERATED!"<<endl;
}


void deCipher(string image_name) {
	// Stores original image
	Mat image = imread(image_name);
	if (image.empty()) {
		cout << "Image Error\n";
		exit(-1);
	}

	// char to work on
	char ch = 0;
	// contains information about which bit of char to work on
	int bit_count = 0;

	/*
	To extract the message from the image, we will iterate through the pixels and extract the LSB of
	the pixel values (RGB) and this way we can get our message.
	*/
	for (int row = 0; row < image.rows; row++) {
		for (int col = 0; col < image.cols; col++) {
			for (int color = 0; color < 3; color++) {

				// stores the pixel details
				Vec3b pixel = image.at<Vec3b>(Point(row, col));

				// manipulate char bits according to the LSB of pixel values
				if (isBitSet(pixel.val[color], 0))
					ch |= 1;

				// increment bit_count to work on next bit
				bit_count++;

				// bit_count is 8, that means we got our char from the encoded image
				if (bit_count == 8) {

					// NULL char is encountered
					if (ch == '\0')
						goto OUT;

					bit_count = 0;
					cout << ch;
					ch = 0;
				} else {
					ch = ch << 1;
				}

			}
		}
	}
	OUT:;

}


int main() {
	string input_image_name,text_name, output_image_name, path_name = "/media/tanuj/Local Disk/Labs/ISS/";
	int choice;
	cout << "Choose your option:\n"
		 << "0. Exit" << endl
		 << "1. Cipher" << endl
		 << "2. Decipher" << endl
		 << "Enter choice: ";
	cin >> choice;

	while (choice > 0 && choice < 3) {
		string text;
		if (choice == 1) {
			cout << "Enter input image name to use: ";
			cin >> input_image_name;

			cout << "Enter text file name to encipher: ";
			cin >> text_name;

			cout << "Enter output image name: ";
			cin >> output_image_name;

			cipher(input_image_name, text_name,output_image_name);


		} else if (choice == 2) {
			cout << "Enter input image name: ";
			cin >> input_image_name;

			deCipher(input_image_name);
		}
		cout << "\nChoose your option:\n"
			 << "0. Exit" << endl
			 << "1. Cipher" << endl
			 << "2. Decipher" << endl
			 << "Enter choice: ";
		cin >> choice;
	}


	return 0;
}
